/*
 *
 *  Created on: Nov 11, 2019
 *      Author: mkilpatr
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include "../utils/json.hpp"
using json = nlohmann::json;

#include "../EstMethods/LLBEstimator.hh"
#include "SRParameters.hh"

using namespace EstTools;

json readFile(std::string FILENAME){
//std::pair< std::pair<vector<TString>, vector<double> >, std::pair<vector<TString>, vector<double> > > readFile(std::string FILENAME){
  std::ifstream file(FILENAME);
  std::vector<double> val_up, val_down;
  string arr[4];
  int i = 0;
  json j;
  bool isFirst = true;
  double up = 1., down = 1.;
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      // using printf() in all tests for consistency
      //cout << line << endl;
      string arr[4];
      int i = 0;
      stringstream ssin(line);
      std::string::size_type sz;
      while (ssin.good() && i < 4){
      	ssin >> arr[i];
      	++i;
      }
      string s = arr[1];
      const std::string ext("_Down");
      if ( s != ext &&
        s.size() > ext.size() &&
        s.substr(s.size() - ext.size()) == "_Down" )
      {
        // if so then strip them off
        s = s.substr(0, s.size() - ext.size());
      }
      
      TString test = TString(arr[1]);
      if(test.Contains("Up")){
      	up = std::stod(arr[3],&sz);
      } else if(test.Contains("Down")){
      	down = std::stod(arr[3],&sz);
      } else{
      	up = std::stod(arr[3],&sz);
      	down = 2-std::stod(arr[3],&sz);
      }
      if(!test.Contains("Up")){ 
      	if((down > 1 && up > 1) || (down < 1 && up < 1)){
      	  float sign = up >= 1 ? 1. : -1.;
      	  double val = 0.5 * (abs(up - 1) + abs(1 - down));
      	  j[s][arr[2]][arr[0]] = {1 - val, 1 + val};
      	} else {
      	  j[s][arr[2]][arr[0]] = {down, up};
          }
      	up = 1., down = 1.;
      }
    }
    file.close();
  }
  return j;
}

std::vector<std::string> readFileTotal(std::string FILENAME){
  std::ifstream file(FILENAME);
  std::vector<std::string> filenames;
  int i = 0;
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
        // using printf() in all tests for consistency
	cout << line << endl;
	filenames.push_back(line);
    }
    file.close();
  }
  return filenames;
}

void confToRoot(std::string indir_ = "values_unc_val_2016"){

  std::string indir = indir_ + "/";
  std::vector<std::string> files = readFileTotal(indir + "values_files.txt");
  std::vector<TString> rootFiles;
  std::vector<double> val_up_total, val_down_total;
  json j, j_bin, jtot;
  std::ofstream jout;
  jout.open(indir+"/uncert.json");
  for(unsigned i = 0; i != files.size(); i++){
    j = readFile(indir + files[i]);
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
      jtot[it.key()] = it.value();
      
    }
  }
  jout << jtot.dump(3);
  jout.close();

  std::ifstream bin(indir+"/binlist.json");
  bin >> j_bin;

  for (json::iterator unc = jtot.begin(); unc != jtot.end(); ++unc) {
    vector<TH1*> hUp, hDown, hdiv, hTotal;
    vector<double> hist_up(j_bin["binNum"].size()), hist_down(j_bin["binNum"].size());
    TString type = TString(unc.key());
    rootFiles.push_back(type);
    cout << type << endl;
    for (json::iterator back = jtot[unc.key()].begin(); back != jtot[unc.key()].end(); ++back) {
      TString bkg = TString(back.key());
      for (json::iterator bin = j_bin["binNum"].begin(); bin != j_bin["binNum"].end(); ++bin) {
	string binstr = j_bin["binNum"][bin.key()];
        int binnum = stoi(binstr, nullptr, 0);
	if (jtot[unc.key()][back.key()][bin.key()][1] != nullptr){
          double up = jtot[unc.key()][back.key()][bin.key()][1];
	  if(up > 5.){ 
            cout << "LARGE ERROR: " << type << " " << bkg << " " << bin.key() << endl;
          }
          hist_up.at(binnum) = jtot[unc.key()][back.key()][bin.key()][1];
          hist_down.at(binnum) = jtot[unc.key()][back.key()][bin.key()][0];
        } else {
	  //cout << unc.key() << ": " << back.key() << ": " << bin.key() << endl;
          hist_up.at(binnum) = 1.;
          hist_down.at(binnum) = 1.;
        }
      }
      if(j_bin["binNum"].size() > 100){
        hUp.push_back(convertToHist(hist_up, bkg + "_Up", ";Search Region; Systematics " + type, nullptr));
        hDown.push_back(convertToHist(hist_down, bkg + "_Down", ";Search Region; Systematics " + type, nullptr));
      } else{
        hUp.push_back(convertToHist(hist_up, bkg + "_Up", ";Validation Region; Systematics " + type, nullptr));
        hDown.push_back(convertToHist(hist_down, bkg + "_Down", ";Validation Region; Systematics " + type, nullptr));
      }
    }

    prepHists(hUp, false, false, false);
    prepHists(hDown, false, false, false);

    for(int h = 0; h != hUp.size(); h++){
      TH1* hDiv = (TH1*)hUp[h]->Clone();
      hDiv->Divide(hDown[h]);
      hDiv->SetLineWidth(2);
      hTotal.push_back(hUp[h]);
      hTotal.push_back(hDown[h]);
      hdiv.push_back(hDiv);
    }
    prepHists({hdiv}, false, false, false);

    auto leg = prepLegends({}, {""}, "l");
    for(int h = 0; h != hUp.size(); h++){
      appendLegends(leg, {hUp[h]}, {hUp[h]->GetName()}, "l");
      //appendLegends(leg, {hDown[h]}, {hDown[h]->GetName()}, "l");
    }
    leg->SetTextSize(0.04);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    TCanvas* c = drawCompAndRatio(hTotal, hdiv, leg, "Up/Down", 0.749, 1.249, false, -1., -1., true);
    c->SetTitle(type);
    c->Print(indir+type+".pdf");
    c->Print(indir+type+".C");

    TFile *outFile = new TFile(indir+type+".root", "RECREATE");
    for(int h = 0; h != hUp.size(); h++){
      hUp[h]->Write();
      hDown[h]->Write();
    }
    outFile->Close();

    delete gROOT->FindObject("hUp");
    delete gROOT->FindObject("hDown");
  }

  //for(unsigned i = 0; i != val_up_total.size(); i++){
  //  val_up_total.at(i) = 1+TMath::Sqrt(val_up_total.at(i));
  //  val_down_total.at(i) = 1-TMath::Sqrt(val_down_total.at(i));
  //}

  //TString totalName = "";
  //if(rootFiles[0].Contains("ll")) totalName = "ll";
  //else				  totalName = "qcd";

  //TH1* hUp = nullptr;
  //TH1* hDown = nullptr;
  //if(val_up_total.size() > 100){
  //  hUp = convertToHist(val_up_total, "Up", ";Search Region; Systematics " + totalName, nullptr);
  //  hDown = convertToHist(val_down_total, "Down", ";Search Region; Systematics " + totalName, nullptr);
  //} else{
  //  hUp = convertToHist(val_up_total, "Up", ";Validation Region; Systematics " + totalName, nullptr);
  //  hDown = convertToHist(val_down_total, "Down", ";Validation Region; Systematics " + totalName, nullptr);
  //}

  //prepHists({hUp, hDown}, false, false, false, {kRed, kBlue});

  //TH1* hDiv = (TH1*)hUp->Clone();
  //hDiv->Divide(hDown);
  //hDiv->SetLineWidth(2);
  //prepHists({hDiv}, false, false, false, {kRed});

  //auto leg = prepLegends({}, {""}, "l");
  //appendLegends(leg, {hUp}, {totalName + " Up"}, "l");
  //appendLegends(leg, {hDown}, {totalName + " Down"}, "l");
  //leg->SetTextSize(0.05);
  //leg->SetY1NDC(leg->GetY2NDC() - 0.2);
  //TCanvas* c = drawCompAndRatio({hUp, hDown}, {hDiv}, leg, "Up/Down", 0.749, 1.999, false, -1., -1., true);
  //c->SetTitle(totalName);
  //c->Print(indir+totalName+".pdf");
  //c->Print(indir+totalName+".C");

  //TFile *outFile = new TFile(indir+totalName+".root", "RECREATE");
  //hUp->Write();
  //hDown->Write();
  //outFile->Close();

  //delete gROOT->FindObject("hUp");
  //delete gROOT->FindObject("hDown");
}
