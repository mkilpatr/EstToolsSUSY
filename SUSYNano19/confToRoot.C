/*
 *
 *  Created on: Nov 11, 2019
 *      Author: mkilpatr
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include "../EstMethods/LLBEstimator.hh"
#include "SRParameters.hh"

using namespace EstTools;

std::pair< std::pair<vector<TString>, vector<double> >, std::pair<vector<TString>, vector<double> > > readFile(std::string FILENAME){
  std::ifstream file(FILENAME);
  std::vector<TString> binName_Up, binName_Down;
  std::vector<double> val_up, val_down;
  string arr[4];
  int i = 0;
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
        TString test = TString(arr[1]);
	if(test.Contains("up")){
		binName_Up.push_back(arr[0]);
		     if(arr[3] == "-nan") val_up.push_back(1.);
		else if(arr[3] == "inf")  val_up.push_back(2.);
		else 		          val_up.push_back(std::stod(arr[3],&sz));
	} else{
		binName_Down.push_back(arr[0]);
		     if(arr[3] == "-nan") val_down.push_back(1.);
		else if(arr[3] == "inf")  val_down.push_back(0.001);
		else 		          val_down.push_back(std::stod(arr[3],&sz));
	}
    }
    file.close();
  }
  //for(int i = 0; i != val_up.size(); i++) cout << "bin: " << binName_Up[i] << ", " << binName_Down[i] << ", val up: " << val_up[i] << ", down: " << val_down[i] << endl;
  return make_pair(make_pair(binName_Up, val_up), make_pair(binName_Down, val_down));
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
  for(int i = 0; i != files.size(); i++){
    std::pair< std::pair<vector<TString>, vector<double> >, std::pair<vector<TString>, vector<double> > > output = readFile(indir + files[i]);
    std::vector<TString> binName_Up, binName_Down;
    std::vector<double> val_up, val_down;

    binName_Up = output.first.first;
    binName_Down = output.second.first;
    val_up = output.first.second;
    val_down = output.second.second;

    for(unsigned int j = 0; j != val_up.size(); j++){
      if((val_up[j] > 1 && val_down[j] > 1) || (val_up[j] < 1 && val_down[j] < 1)){
	float sign = val_up[j] > 1 ? 1 : -1;
	float value = 0.5 * (std::abs(val_up[j] - 1) + std::abs(1 - val_down[j]));
	val_up.at(j) = 1 + sign*value;
	val_down.at(j) = 1 - sign*value;
      }
    }

    for(int j = 0; j != val_up.size(); j++){
      if(i == 0){
        val_up_total.push_back((1-val_up[j])*(1-val_up[j]));
        val_down_total.push_back((1-val_down[j])*(1-val_down[j]));
      } else{
        val_up_total.at(j) += (1-val_up[j])*(1-val_up[j]);
        val_down_total.at(j) += (1-val_down[j])*(1-val_down[j]);
      }
      //cout << "val_up[" << j << "]: " << val_up[j] << endl;
      //cout << "val_up_total[" << j << "]: " << val_up_total[j] << endl;
      //cout << "val_down[" << j << "]: " << val_down[j] << endl;
      //cout << "val_down_total[" << j << "]: " << val_down_total[j] << endl;
    }

    size_t lastindex = files[i].find_last_of("."); 
    string rawname = files[i].substr(0, lastindex); 
    std::string toErase = "values_unc_";
    size_t pos = rawname.find(toErase);
    if (pos != std::string::npos) rawname.erase(pos, toErase.length());
    TString type = TString(rawname);
    rootFiles.push_back(type);

    TH1* hUp = nullptr;
    TH1* hDown = nullptr;
    if(val_up.size() > 100){
      hUp = convertToHist(val_up, "Up", ";Search Region; Systematics " + type, nullptr);
      hDown = convertToHist(val_down, "Down", ";Search Region; Systematics " + type, nullptr);
    } else{
      hUp = convertToHist(val_up, "Up", ";Validation Region; Systematics " + type, nullptr);
      hDown = convertToHist(val_down, "Down", ";Validation Region; Systematics " + type, nullptr);
    }

    prepHists({hUp, hDown}, false, false, false, {kRed, kBlue});

    TH1* hDiv = (TH1*)hUp->Clone();
    hDiv->Divide(hDown);
    hDiv->SetLineWidth(2);
    prepHists({hDiv}, false, false, false, {kRed});

    auto leg = prepLegends({}, {""}, "l");
    appendLegends(leg, {hUp}, {type + " Up"}, "l");
    appendLegends(leg, {hDown}, {type + " Down"}, "l");
    leg->SetTextSize(0.05);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    TCanvas* c = drawCompAndRatio({hUp, hDown}, {hDiv}, leg, "Up/Down", 0.749, 1.249, false, -1., -1., true);
    c->SetTitle(type);
    c->Print("LLB/"+indir+type+".pdf");
    c->Print("LLB/"+indir+type+".C");

    TFile *outFile = new TFile("LLB/"+indir+type+".root", "RECREATE");
    hUp->Write();
    hDown->Write();
    outFile->Close();

    delete gROOT->FindObject("hUp");
    delete gROOT->FindObject("hDown");
  }

  for(int i = 0; i != val_up_total.size(); i++){
    val_up_total.at(i) = 1+TMath::Sqrt(val_up_total.at(i));
    val_down_total.at(i) = 1-TMath::Sqrt(val_down_total.at(i));
  }

  TString totalName = "";
  if(rootFiles[0].Contains("ll")) totalName = "ll";
  else				  totalName = "qcd";

  TH1* hUp = nullptr;
  TH1* hDown = nullptr;
  if(val_up_total.size() > 100){
    hUp = convertToHist(val_up_total, "Up", ";Search Region; Systematics " + totalName, nullptr);
    hDown = convertToHist(val_down_total, "Down", ";Search Region; Systematics " + totalName, nullptr);
  } else{
    hUp = convertToHist(val_up_total, "Up", ";Validation Region; Systematics " + totalName, nullptr);
    hDown = convertToHist(val_down_total, "Down", ";Validation Region; Systematics " + totalName, nullptr);
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
  c->Print("LLB/"+indir+totalName+".pdf");
  c->Print("LLB/"+indir+totalName+".C");

  TFile *outFile = new TFile("LLB/"+indir+totalName+".root", "RECREATE");
  hUp->Write();
  hDown->Write();
  outFile->Close();

  delete gROOT->FindObject("hUp");
  delete gROOT->FindObject("hDown");
}
