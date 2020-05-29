/*
 *
 *  Created on: Nov 11, 2019
 *      Author: mkilpatr
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

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
      if(TString(s).Contains("mcstats_signal")) s = "mcstats_signal";
      
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
      	j[s][arr[2]][arr[0]] = {down, up};
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
	filenames.push_back(line);
    }
    file.close();
  }
  return filenames;
}

std::pair<double, double> doLogNorm(vector<double> p_down, vector<double> p_up){
  double log_syst_up_sum = 0., log_syst_down_sum = 0.;
  double log_syst_up_total = 0., log_syst_down_total = 0.;
  double log_final_up = 0., log_final_down = 0.;
  for(unsigned p = 0; p != p_down.size(); p++){
    double log_syst_up     = p_up[p];
    double log_syst_down   = p_down[p];
    if ((log_syst_up > 1 && log_syst_down > 1) || (log_syst_up < 1 && log_syst_down < 1)){
      double geometric_mean = TMath::Sqrt(log_syst_up * log_syst_down);
      log_syst_up   /= geometric_mean;
      log_syst_down /= geometric_mean;
    }
    if (log_syst_up > 1 || log_syst_down < 1){
        log_syst_up_sum     += pow(TMath::Log(log_syst_up), 2);
        log_syst_down_sum   += pow(TMath::Log(log_syst_down), 2);
    } else{
        log_syst_up_sum     += pow(TMath::Log(log_syst_down), 2);
        log_syst_down_sum   += pow(TMath::Log(log_syst_up), 2);
    }
    log_syst_up_total   = TMath::Exp( TMath::Sqrt(log_syst_up_sum));
    log_syst_down_total = TMath::Exp(-TMath::Sqrt(log_syst_down_sum)); // Minus sign is needed because this is the *down* ratio
    log_final_up   = log_syst_up_total;
    log_final_down = log_syst_down_total;
  }

  return make_pair(log_final_down, log_final_up);
}

void confToRoot(std::string indir_ = "values_unc_val_2016"){

  std::string indir = indir_ + "/";
  std::vector<std::string> files = readFileTotal(indir + "values_files.txt");
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

  std::ifstream bin("binlist.json");
  bin >> j_bin;

  string binName = "";
       if(TString(indir_).Contains("SR"))      binName = "binNum_SUSYNano";
  else if(TString(indir_).Contains("nb12"))    binName = "binNum_SUSYNano_HM_nb12";
  else if(TString(indir_).Contains("CR"))      binName = "binNum_SUSYNano_lepcr";
  else if(TString(indir_).Contains("LowMET"))  binName = "binNum_Validation";
  else if(TString(indir_).Contains("Moriond")) binName = "binNum_Moriond17";

  for (json::iterator unc = jtot.begin(); unc != jtot.end(); ++unc) {
    vector<TH1*> hUp, hDown, hdiv, hTotal;
    vector<double> hist_up(j_bin[binName].size()), hist_down(j_bin[binName].size());
    TString type = TString(unc.key());
    cout << type << endl;
    for (json::iterator back = jtot[unc.key()].begin(); back != jtot[unc.key()].end(); ++back) {
      TString bkg = TString(back.key());
      for (json::iterator bin = j_bin[binName].begin(); bin != j_bin[binName].end(); ++bin) {
	string binstr = j_bin[binName][bin.key()];
        int binnum = stoi(binstr, nullptr, 0);
        if(TString(indir_).Contains("nb12")) binnum -= 53;
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
      if(j_bin[binName].size() > 120){
        hUp.push_back(convertToHist(hist_up, bkg + "_Up", ";Search Region; Systematics " + type, nullptr));
        hDown.push_back(convertToHist(hist_down, bkg + "_Down", ";Search Region; Systematics " + type, nullptr));
      } else if(j_bin[binName].size() > 100){
        hUp.push_back(convertToHist(hist_up, bkg + "_Up", ";Control Region; Systematics " + type, nullptr));
        hDown.push_back(convertToHist(hist_down, bkg + "_Down", ";Control Region; Systematics " + type, nullptr));
      } else if(TString(indir_).Contains("nb12")){
        hUp.push_back(convertToHist(hist_up, bkg + "_Up", ";Search Region; Systematics " + type, nullptr));
        hDown.push_back(convertToHist(hist_down, bkg + "_Down", ";Search Region; Systematics " + type, nullptr));
      } else{
        hUp.push_back(convertToHist(hist_up, bkg + "_Up", ";Validation Region; Systematics " + type, nullptr));
        hDown.push_back(convertToHist(hist_down, bkg + "_Down", ";Validation Region; Systematics " + type, nullptr));
      }
    }

    if(hUp.size() == 1){
      prepHists(hUp, false, false, false, {kRed});
      prepHists(hDown, false, false, false, {kBlue});
    } else {
      prepHists(hUp, false, false, false);
      prepHists(hDown, false, false, false);
    }

    for(unsigned h = 0; h != hUp.size(); h++){
      TH1* hDiv = (TH1*)hUp[h]->Clone();
      hDiv->Divide(hDown[h]);
      hDiv->SetLineWidth(2);
      hTotal.push_back(hUp[h]);
      hTotal.push_back(hDown[h]);
      hdiv.push_back(hDiv);
    }
    if(hUp.size() == 1) prepHists({hdiv}, false, false, false, {kRed});
    else		prepHists({hdiv}, false, false, false);

    auto leg = prepLegends({}, {""}, "l");
    for(unsigned h = 0; h != hUp.size(); h++){
      TString legName = hUp[h]->GetName();
      if(hUp.size() > 1) legName.ReplaceAll("_Up","");
      appendLegends(leg, {hUp[h]}, {legName}, "l");
      if(hUp.size() == 1) appendLegends(leg, {hDown[h]}, {hDown[h]->GetName()}, "l");
    }
    leg->SetTextSize(0.04);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    TCanvas* c = drawCompAndRatio(hTotal, hdiv, leg, "Up/Down", 0.749, 1.249, false, -1., -1., true);
    c->SetTitle(type);
    c->Print(indir+type+".pdf");
    c->Print(indir+type+".C");

    TFile *outFile = new TFile(indir+type+".root", "RECREATE");
    for(unsigned h = 0; h != hUp.size(); h++){
      hUp[h]->Write();
      hDown[h]->Write();
    }
    outFile->Close();

    delete gROOT->FindObject("hUp");
    delete gROOT->FindObject("hDown");
  }

  vector<double> hist_up_total(j_bin[binName].size()), hist_down_total(j_bin[binName].size());
  for (json::iterator bin = j_bin[binName].begin(); bin != j_bin[binName].end(); ++bin) {
    vector<double> hUp, hDown;
    string binstr = j_bin[binName][bin.key()];
    int binnum = stoi(binstr, nullptr, 0);
    for (json::iterator unc = jtot.begin(); unc != jtot.end(); ++unc) {
      for (json::iterator back = jtot[unc.key()].begin(); back != jtot[unc.key()].end(); ++back) {
        TString bkg = TString(back.key());
        if (jtot[unc.key()][back.key()][bin.key()][1] != nullptr){
          double up = jtot[unc.key()][back.key()][bin.key()][1];
          if(up > 5.) continue;
          hUp.push_back(jtot[unc.key()][back.key()][bin.key()][1]);
          hDown.push_back(jtot[unc.key()][back.key()][bin.key()][0]);
        } 
      }
    }
    pair<double, double> comb = doLogNorm(hDown, hUp);
    hist_down_total.at(binnum) = std::isnan(comb.first) ? 0.001 : comb.first;
    hist_up_total.at(binnum) = comb.second;
  }

  TString totalName = "Total";
  TH1* hUp = nullptr;
  TH1* hDown = nullptr;
  if(j_bin[binName].size() > 120){
    hUp = convertToHist(hist_up_total, "Up", ";Search Region; Systematics", nullptr);
    hDown = convertToHist(hist_down_total, "Down", ";Search Region; Systematics", nullptr);
  } else if(j_bin[binName].size() > 100){
    hUp = convertToHist(hist_up_total, "Up", ";Control Region; Systematics", nullptr);
    hDown = convertToHist(hist_down_total, "Down", ";Control Region; Systematics", nullptr);
  } else{
    hUp = convertToHist(hist_up_total, "Up", ";Validation Region; Systematics", nullptr);
    hDown = convertToHist(hist_down_total, "Down", ";Validation Region; Systematics", nullptr);
  }

  prepHists({hUp, hDown}, false, false, false, {kRed, kBlue});

  TH1* hDiv = (TH1*)hUp->Clone();
  hDiv->Divide(hDown);
  hDiv->SetLineWidth(2);
  prepHists({hDiv}, false, false, false, {kRed});

  auto leg = prepLegends({}, {""}, "l");
  appendLegends(leg, {hUp}, {totalName + " Up"}, "l");
  appendLegends(leg, {hDown}, {totalName + " Down"}, "l");
  leg->SetTextSize(0.05);
  leg->SetY1NDC(leg->GetY2NDC() - 0.2);
  TCanvas* c = drawCompAndRatio({hUp, hDown}, {hDiv}, leg, "Up/Down", 0.749, 1.999, false, -1., -1., true);
  c->SetTitle(totalName);
  c->Print(indir+totalName+".pdf");
  c->Print(indir+totalName+".C");

  TFile *outFile = new TFile(indir+totalName+".root", "RECREATE");
  hUp->Write();
  hDown->Write();
  outFile->Close();

  delete gROOT->FindObject("hUp");
  delete gROOT->FindObject("hDown");
}
