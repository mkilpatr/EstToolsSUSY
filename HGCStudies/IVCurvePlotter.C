/*
 *
 *  Created on: Nov 11, 2019
 *      Author: mkilpatr
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <functional>
#include <numeric>
#include <glob.h>

#include "../utils/json.hpp"
using json = nlohmann::json;

#include "../utils/EstHelper.hh"

using namespace EstTools;

//files format
//time     bias voltage           meas current               meas voltage

map<TString, string> nLeg {
  {"Module805 Original", "Module805 Original"},
  {"16Apr21", "1 Cycle"},
  {"19Apr21", "2 Cycles"},
  {"19Apr21_n2", "3 Cycles"},
  {"21Apr21", "4 Cycles"},
  {"26Apr21_3", "5 Cycles"},
  {"28Apr21_10thermalcycles", "10 Cycles"},
  {"30Apr21_15thermalcycles", "15 Cycles"},
  {"JMay2821_20thermalcycles", "20 Cycles"},
  {"Jun0121_30thermalcycles", "30 Cycles"},
  {"Jun0221_40thermalcycles", "40 Cycles"},
  {"Jun0321_50thermalcycles", "50 Cycles"},
  {"1Cycle", "1 Cycle"},
  {"2Cycles", "2 Cycles"},
  {"3Cycles", "3 Cycles"},
  {"4Cycles", "4 Cycles"},
  {"5Cycles", "5 Cycles"},
  {"6Cycles", "6 Cycles"},
  {"10Cycles", "10 Cycles, Bad IV"},
  {"11Cycles", "11 Cycles, Fix HV Connection"},
  {"1_Cycle", "1 Cycle"},
};

map<TString, Color_t> nColor {
  {"Module805 Original", kBlack},
  {"16Apr21", kRed-9},
  {"19Apr21", kAzure+6},
  {"19Apr21_n2", kRed},
  {"21Apr21", kGreen},
  {"26Apr21_3", 606},
  {"28Apr21_10thermalcycles", kViolet+2},
  {"30Apr21_15thermalcycles", kSpring-8},
  {"JMay2821_20thermalcycles", kOrange-3},
  {"Jun0121_30thermalcycles",  kYellow-9},
  {"Jun0221_40thermalcycles", kGreen+3},
  {"Jun0321_50thermalcycles", kOrange},
  {"1Cycle", kRed-9},
  {"2Cycles", kAzure+6},
  {"3Cycles", kSpring-8},
  {"4Cycles", kGreen},
  {"5Cycles", 606},
  {"6Cycles", COLOR_MAP["color_comp1"]},
  {"10Cycles", COLOR_MAP["color_comp1"]},
  {"11Cycles", COLOR_MAP["color_comp2"]},
  {"1_Cycle", kAzure+6},
};

double strToDouble(string s){
  std::string::size_type sz;
  return std::stod(s,&sz);
}

json readFile(std::string FILENAME){
  std::ifstream file(FILENAME);
  string arr[4];
  int i = 0;
  json j;
  double biasV = 0., measV = 0., measC = 0., measR = 0.;
  double nAvg = 0.;
  if (file.is_open()) {
    std::string line;
    double prevVol = 0.;
    while (getline(file, line)) {
      string arr[4];
      int i = 0;
      stringstream ssin(line);
      std::string::size_type sz;
      while (ssin.good() && i < 4){
      	ssin >> arr[i];
      	++i;
      }

      int isEnd = ssin.rdbuf()->in_avail();

      if(isEnd != 0) biasV = strToDouble(arr[1]);
      if((biasV != prevVol && nAvg > 0) || isEnd == 0){ 
        if((measV/nAvg)/(measC/nAvg) < 0) measR = 0;
        else measR = (measV/measC);
        if(isnan(measV/nAvg) || isnan(measC/nAvg) || isnan(measR)){
          cout << "Measured Current or Voltage was NULL in file " << FILENAME << "!!!" << endl;
          cout << "(MeasV, MeasC, measR, nAvg) = (" << measV << ", " << measC << ", " << measR << ", " << nAvg << ")" << endl;
        } else j[FILENAME][to_string(prevVol)] = {measV/nAvg, measC/nAvg, measR};
        measC = 0.;
        measV = 0.;
        nAvg  = 0.;
      }
      if(biasV == prevVol && isEnd != 0){
        measC += strToDouble(arr[2]);
        measV += strToDouble(arr[3]);
        nAvg++;
      }
      prevVol = biasV;
    }
    file.close();
  }
  return j;
}

std::vector<std::string> readFileTotal(const string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

inline bool exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void IVCurvePlotter(std::string indir_ = "testDir", string suffix_ = "module805", TString label = "Module X"){
  gROOT->SetBatch(1);

  TString suffix = TString(suffix_);
  std::string indir = indir_ + "/*";
  std::vector<std::string> files = readFileTotal(indir);
  std::vector<double> val_up_total, val_down_total;
  json j, jtot, j_orig;
  std::ofstream jout;
  jout.open(indir_ + "/" + suffix + ".json");
  for(unsigned i = 0; i != files.size(); i++){
    TString name = TString(files[i]);
    if(!name.Contains("txt")) continue;
    cout << files[i] << endl;
    j = readFile(files[i]);
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
      jtot[it.key()] = it.value();
      
    }
  }
  jout << jtot.dump(3);
  jout.close();

  vector<Color_t> colors;
  vector<TH1*> hTotal, hRTotal;
  if(exists(suffix_ + "Master.json")){
    std::ifstream orig(suffix + "Master.json");
    orig >> j_orig;

    for (json::iterator unc = j_orig.begin(); unc != j_orig.end(); ++unc) {
      TString type = TString(unc.key());
      TH1D* hIV = new TH1D(type, ";Voltage (V);Current (#muA)", 32, 0, 800);
      TH1D* hRes = new TH1D(type, ";Voltage (V);Resistance (k#Omega)", 32, 0, 800);
      cout << type << endl;
      TAxis *xaxis = hIV->GetXaxis();
      for (json::iterator bin = j_orig[unc.key()].begin(); bin != j_orig[unc.key()].end(); ++bin) {
        int binnum = xaxis->FindBin(strToDouble(bin.key()));
        hIV->SetBinContent(binnum, double(j_orig[unc.key()][bin.key()][1])*1000000);
        hIV->SetBinError(binnum, 0.);
        hRes->SetBinContent(binnum, double(j_orig[unc.key()][bin.key()][2])/1000);
        hRes->SetBinError(binnum, 0.);
      }
      hTotal.push_back(hIV);
      hRTotal.push_back(hRes);
      TString colName = hIV->GetName();
      colName.ReplaceAll(indir_ + "/data_IVCurve_Neg30_", "");
      colName.ReplaceAll("sec", "s ");
      colName.ReplaceAll(".txt", "");
      colName.ReplaceAll("_25Vper10s", "");
      colors.push_back(nColor[colName]);
    }
  }

  for (json::iterator unc = jtot.begin(); unc != jtot.end(); ++unc) {
    TString type = TString(unc.key());
    TH1D* hIV = new TH1D(type, ";Voltage (V);Current (#muA)", 32, 0, 800);
    TH1D* hRes = new TH1D(type + "Resistance", ";Voltage (V);Resistance (k#Omega)", 32, 0, 800);
    TAxis *xaxis = hIV->GetXaxis();
    for (json::iterator bin = jtot[unc.key()].begin(); bin != jtot[unc.key()].end(); ++bin) {
      int binnum = xaxis->FindBin(strToDouble(bin.key()));
      hIV->SetBinContent(binnum, double(jtot[unc.key()][bin.key()][1])*1000000);
      hIV->SetBinError(binnum, 0.);
      hRes->SetBinContent(binnum, double(jtot[unc.key()][bin.key()][2])/1000);
      hRes->SetBinError(binnum, 0.);
    }
    hTotal.push_back(hIV);
    hRTotal.push_back(hRes);

    vector<TString> vec = splitString(hIV->GetName(), "_");
    TString colName = "";
    for (unsigned i=0; i<vec.size(); ++i){
      if(vec.at(i).Contains("Cycle")) colName = TString(vec.at(i));
    }

    colors.push_back(nColor[colName]);
  }

  prepHists(hTotal, false, false, false, colors);
  prepHists(hRTotal, false, false, false, colors);

  for(auto* h : hTotal) h->SetMarkerStyle(8);
  for(auto* h : hRTotal) h->SetMarkerStyle(8);

  auto leg = prepLegends({}, {""}, "l");
  for(unsigned h = 0; h != hTotal.size(); h++){
    cout << hTotal[h]->GetName() << endl;
    vector<TString> vec = splitString(hTotal[h]->GetName(), "_");
    TString rlt = "";
    bool isfirst = true;
    for (unsigned i=0; i<vec.size(); ++i){
      TString buff = "";
      if(!vec.at(i).Contains("data") && !vec.at(i).Contains("IVCurve") && !vec.at(i).Contains("Neg30") && !vec.at(i).Contains("21")){
        if(vec.at(i).Contains("Cycle")) buff = nLeg[vec.at(i)];
        else buff = vec.at(i);
        if (isfirst){
          rlt = buff;
          isfirst = false;
        }else{
          rlt = rlt + ", " + buff;
        }
      }
    }
    rlt.ReplaceAll(".txt", "");
    appendLegends(leg, {hTotal[h]}, {rlt}, "P");
  }

  std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(label, 0.2, 0.94, 0.04); };
  //Legend information
  setLegend(leg, 1, 0.2, 0.65, 0.94, 0.90);
  leg->SetTextSize(0.04);
  leg->SetY1NDC(leg->GetY2NDC() - 0.2);

  //Create plots for Current vs Voltage
  TCanvas* c = drawCompMatt(hTotal, leg, -1., &plotextra, "P", true);
  TString typeName = "IVCurves_"+suffix;
  c->SetTitle(typeName);
  c->Print(indir_+"/"+typeName+".pdf");
  c = drawCompMatt(hTotal, leg, 0.001, nullptr, "P", true);
  c->SetTitle(typeName + "_log");
  c->Print(indir_+"/"+typeName+"_log.pdf");

  //Create plots for Resistance vs Voltage
  c = drawCompMatt(hRTotal, leg, -1., &plotextra, "P", true);
  typeName = "Resistance_"+suffix;
  c->SetTitle(typeName);
  c->Print(indir_+"/"+typeName+".pdf");
  c = drawCompMatt(hRTotal, leg, 0.001, nullptr, "P", true);
  c->SetTitle(typeName + "_log");
  c->Print(indir_+"/"+typeName+"_log.pdf");

  TFile *outFile = new TFile(indir_+"/"+typeName+".root", "RECREATE");
  for(auto* h : hTotal) h->Write();
  for(auto* h : hRTotal) h->Write();
  outFile->Close();

}
