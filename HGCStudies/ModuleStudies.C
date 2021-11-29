#if !defined(__CINT__) || defined(__MAKECINT__)
#include "../utils/Estimator.hh"
#include "../utils/HistGetter.hh"
#include "../SUSYNano19/SRParameters.hh"
#include "../utils/json.hpp"
#include "ModuleConstants.hpp"

#include <TRandom.h>
#include <TH2Poly.h>
#include "TPaletteAxis.h"
#include <math.h> 
#include <map>
#include <iomanip>
#include <numeric>
#include<bits/stdc++.h> 

using namespace std;
using namespace EstTools;
using json = nlohmann::json;

TString baseDir = "Gaussian_PCBplus000_Kaptonplus000_senTokap185_midSensor";
void print2DPlots(TH2Poly *hc, TString geometry, TString BinLatex = "", TString name = "testHoneycomb", double width = 0.2);
void print2DPlots(TH2D *hc, TString geometry, TString BinLatex = "", TString name = "testHoneycomb");
void module2DTolerances();
void module1DTolerances();
void moduleFitTolerances();
void printToleranceTableLatex(json jtot, TString outputfile="/tmp/yields.tex");
void RedoLatexTable(TString geo = "Full");
#endif

void ModuleStudies(){
  //module2DTolerances();
  module1DTolerances();
  moduleFitTolerances();
  RedoLatexTable("Semi");
}

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}  

float Round(float var, float decimal = 1000.){ 
    float value = (int)(var * decimal + .5); 
    return (float)value / decimal; 
} 

void printToleranceTableLatex(json jtot, json jbad, TString outputfile){
  ofstream outfile(outputfile);
  Quantity::printStyle = Quantity::LATEX;
  outfile << R"(\documentclass[12pt,notitlepage]{revtex4-1})" << endl;
  outfile << R"(\usepackage{amsmath,mathrsfs})" << endl;
  outfile << R"(\usepackage{graphicx})" << endl;
  outfile << R"(\usepackage{amsmath})" << endl;
  outfile << R"(\usepackage{siunitx})" << endl;
  outfile << R"(\usepackage{graphicx})" << endl;
  outfile << R"(\usepackage{indentfirst})" << endl;
  outfile << R"(\usepackage{amssymb})" << endl;
  outfile << R"(\usepackage{natbib})" << endl;
  outfile << R"(\usepackage{longtable})" << endl;
  outfile << R"(\usepackage[hidelinks]{hyperref})" << endl;
  outfile << R"(\usepackage{listings})" << endl;
  outfile << R"(\usepackage{rotating})" << endl;
  outfile << R"(\usepackage{multirow})" << endl;
  outfile << R"(\usepackage[utf8]{inputenc})" << endl;
  outfile << R"(\usepackage[english]{babel})" << endl;
  outfile << R"(\usepackage[usenames, dvipsnames]{color})" << endl;
  outfile << R"(\pagenumbering{gobble})" << endl;
  outfile << R"(\def\arraystretch{0.5})" << endl;
  outfile << R"(\usepackage[margin=1cm]{geometry})" << endl;
  outfile << R"(\begin{document})" << endl;

  assert(jtot);
  assert(jbad);

  outfile << R"(\newpage)" << endl;
  outfile << R"(\begin{center})" << endl;
  outfile << R"(\begin{longtable}{| c | c | c | c | c | c |})" << endl;
  outfile << R"(\hline )" << endl;

  //key for value type
  outfile << "Widths & \t Sensor Placement & \t Sensor & \t Kapton & \t Baseplate & \t PCB \t" << R"( \\)" << endl;
  outfile << R"(\hline)" << endl;
  for (int i = 0; i != (signed)constants::Order.size(); i++){
    for (json::iterator comp = jbad["Worst"]["Bad Components"].begin(); comp != jbad["Worst"]["Bad Components"].end(); ++comp) {
      if(!TString(comp.key()).Contains(constants::Order[i])) continue;
      if(TString(comp.key()).Contains("Nominal")) continue;
      TString multi = "";
      TString buff = TString(comp.key());
      buff.ReplaceAll("Sensor", "SplitSensor");
      buff.ReplaceAll("Gaussian_", "");
      if(outputfile.Contains("Full")) buff.ReplaceAll("_Peak1", "");
  
      if(constants::debug) cout << comp.key() << " " << buff << endl;
      //if(buff.Contains("mid")) multi = R"( \multirow{2}{*}{\shortstack{)";
      outfile << multi << translateString(buff, constants::latexMap, "_", ", ") << " & \t " 
	<< round(float(jbad["Worst"]["Bad Components"][comp.key()]["Sensor"])) << " & \t " 
    	<< round(float(jbad["Worst"]["Bad Components"][comp.key()]["Kapton"])) << " & \t "
    	<< round(float(jbad["Worst"]["Bad Components"][comp.key()]["Baseplate"])) << " & \t "
    	<< round(float(jbad["Worst"]["Bad Components"][comp.key()]["PCB"])) << R"( \\)" << endl;
    }//for comparison
  }//for Order
  outfile << R"(\end{longtable})" << endl;
  outfile << R"(\end{center})" << endl;

  //For total Bad Overlaps
  outfile << R"(\newpage)" << endl;
  outfile << R"(\begin{center})" << endl;
  outfile << R"(\resizebox*{1.0\textwidth}{!}{)" << endl;
  outfile << R"(\begin{tabular}{| c | c | c | c | c | c | c | c | c |})" << endl;
  outfile << R"(\hline )" << endl;

  //key for value type
  outfile << "Widths & \t Sensor Placement";
  for(int i = 0; i != (signed)constants::whichPlot.size(); i++) if(constants::whichPlot[i].Contains("stack_hist")) outfile << " & \t " << constants::nameMap[constants::whichPlot[i]];
  outfile << R"( \\)" << endl;
  outfile << R"(\hline)" << endl;
  for (int i = 0; i != (signed)constants::Order.size(); i++){
    for (json::iterator comp = jbad["Worst"]["Bad Overlaps"].begin(); comp != jbad["Worst"]["Bad Overlaps"].end(); ++comp) {
      if(!TString(comp.key()).Contains(constants::Order[i])) continue;
      if(TString(comp.key()).Contains("Nominal")) continue;
      TString multi = "";
      TString buff = TString(comp.key());
      buff.ReplaceAll("Sensor", "SplitSensor");
      buff.ReplaceAll("Gaussian_", "");
      if(outputfile.Contains("Full")) buff.ReplaceAll("_Peak1", "");
  
      if(constants::debug) cout << comp.key() << " " << buff << endl;
      outfile << multi << translateString(buff, constants::latexMap, "_", ", "); 
      for(int i = 0; i != (signed)constants::whichPlot.size(); i++){ 
        if(constants::debug) cout << constants::nameMap[constants::whichPlot[i]] << endl;
        if(constants::whichPlot[i].Contains("stack_hist")) outfile << " & \t " << round(float(jbad["Worst"]["Bad Overlaps"][comp.key()][constants::nameMap[constants::whichPlot[i]]]));
      }
      outfile << R"( \\)" << endl;

    }//for comparison
  }//for Order
  outfile << R"(\end{tabular}})" << endl;
  outfile << R"(\end{center})" << endl;

  for (json::iterator type = jtot.begin(); type != jtot.end(); ++type){
    if(type.key() == "BinNum") continue;
    if(type.key() == "Fit") continue;
    if(type.key() == "Worst") continue;
    outfile << R"(\newpage)" << endl;
    outfile << R"(\begin{center})" << endl;
    outfile << R"(\resizebox*{1.0\textwidth}{!}{)" << endl;
    outfile << R"(\begin{tabular}{| c | c | c | c | c | c |})" << endl;
    outfile << R"(\hline )" << endl;

    int ncols = 5;
    //key for value type
    outfile << "Widths & \t Sensor Placement & \t Nominal " << R"([$\mu m]$)" << " & \t Fitted " << R"($[\mu m]$)" << " & \t Worst " << R"($[\mu m]$)" << R"( \\)" << endl;
    for (json::iterator dist = jtot["BinNum"].begin(); dist != jtot["BinNum"].end(); ++dist) {
      //key for overlap comparison
      outfile << R"(\hline)" << endl << R"(\multicolumn{)"+to_string(ncols)+R"(}{c}{$\vcenter{)" + dist.key() + R"(}$} \\)" << endl << R"(\hline)" << endl;
      for (int i = 0; i != (signed)constants::Order.size(); i++){
        for (json::iterator comp = jtot[type.key()].begin(); comp != jtot[type.key()].end(); ++comp) {
          if(!TString(comp.key()).Contains(constants::Order[i])) continue;
          if(TString(comp.key()).Contains("Nominal")) continue;
          if(TString(comp.key()).Contains("_max")) continue;
          TString multi = "";
          TString buff = TString(comp.key());
          buff.ReplaceAll("Sensor", "SplitSensor");
          buff.ReplaceAll("Gaussian_", "");
          if(outputfile.Contains("Full")) buff.ReplaceAll("_Peak1", "");

          if(constants::debug) cout << type.key() << " " << comp.key() << " " << dist.key() << endl;
          outfile << multi << translateString(buff, constants::latexMap, "_", ", "); 
          outfile << " & \t " << Round(jtot["Fit"][dist.key()][comp.key() + "_Nominal"][0]) 
                  << " & \t " << Round(jtot["Fit"][dist.key()][comp.key()][0]) << R"( $\pm$ )"   << Round(jtot["Fit"][dist.key()][comp.key()][1]);
          outfile << " & \t " << Round(jtot["Worst"][dist.key()][comp.key()][0], 1.0) << R"( $\pm$ )" << Round(jtot["Worst"][dist.key()][comp.key()][1], 1.0)
            	         << R"( $N_{mod} = $)" << Round(jtot["Worst"][dist.key()][comp.key()][2], 100000.)*30000  << R"( \\)" << endl;

        }//for comparison
      }//for constants::Order
    }//for overlap

    outfile << R"(\hline)" << endl;
    outfile << R"(\end{tabular}})" << endl;
    outfile << R"(\end{center})" << endl;
  }

  outfile << R"(\newpage)" << endl;
  outfile << R"(\begin{center})" << endl;
  outfile << R"(\resizebox*{1.0\textwidth}{!}{)" << endl;
  outfile << R"(\begin{tabular}{| c | c | c | c ||})" << endl;
  outfile << R"(\hline )" << endl;

  int ncols = 4;
  //key for value type
  outfile << R"(Widths & \t Sensor Placement & 20 $[\mu m]$ & 200 $[\mu m]$ \\)" << endl;
  for (json::iterator dist = jtot["BinNum"].begin(); dist != jtot["BinNum"].end(); ++dist) {
    //key for overlap comparison
    outfile << R"(\hline)" << endl << R"(\multicolumn{)"+to_string(ncols)+R"(}{c}{$\vcenter{)" + dist.key() + R"(}$} \\)" << endl << R"(\hline)" << endl;
    for (int i = 0; i != (signed)constants::Order.size(); i++){
      for (json::iterator comp = jtot["Distribution"].begin(); comp != jtot["Distribution"].end(); ++comp) {
        if(!TString(comp.key()).Contains(constants::Order[i])) continue;
        if(TString(comp.key()).Contains("Nominal")) continue;
        if(TString(comp.key()).Contains("Peak")) continue;
        TString multi = "";
        TString buff = TString(comp.key());
        buff.ReplaceAll("Sensor", "SplitSensor");
        buff.ReplaceAll("Gaussian_", "");
        buff.ReplaceAll("_max", "");

        if(constants::debug) cout << comp.key() << " " << dist.key() << endl;
        outfile << multi << translateString(buff, constants::latexMap, "_", ", ") << " & \t " 
	<< Round(jtot["Worst"]["Probability"][dist.key()][comp.key()]["0.020000"], 100000.) << " & \t " 
    	<< Round(jtot["Worst"]["Probability"][dist.key()][comp.key()]["0.200000"], 100000.) << R"( \\)" << endl;

      }//for comparison
    }//for constants::Order
  }//for overlap

  outfile << R"(\hline)" << endl;
  outfile << R"(\end{tabular}})" << endl;
  outfile << R"(\end{center})" << endl;

  outfile << R"(\end{document})" << endl;

  outfile.close();
}//for country!

json merge( const json &a, const json &b )
{
    
    json result = a.flatten();
    json tmp = b.flatten();
    for ( auto it = tmp.begin(); it != tmp.end(); ++it )
        result[it.key()] = it.value();
    return result.unflatten();
}

json mergeJSONBadModuleLatex(TString geo){
  json j;
  for(auto &type_str : constants::Dist){
    //Bad Components
    std::ifstream i(constants::eosDir + "/" + type_str + "_" + geo + "/" + geo + "_BadmoduleTolerances.json");
    json jbuff;
    i >> jbuff;


    j["Worst"]["Bad Components"][type_str]["Baseplate"] = jbuff["Worst"]["Bad Components"][type_str]["Baseplate"];
    j["Worst"]["Bad Components"][type_str]["Kapton"] = jbuff["Worst"]["Bad Components"][type_str]["Kapton"];
    j["Worst"]["Bad Components"][type_str]["PCB"] = jbuff["Worst"]["Bad Components"][type_str]["PCB"];
    j["Worst"]["Bad Components"][type_str]["Sensor"] = jbuff["Worst"]["Bad Components"][type_str]["Sensor"];
    j["Worst"]["Bad Components"][type_str]["Total"] = jbuff["Worst"]["Bad Components"][type_str]["Total"];

    for(int i = 0; i != (signed)constants::whichComp.size(); i++){
      j["Worst"]["Bad Overlaps"][type_str][constants::nameMap[constants::whichComp[i]]] = jbuff["Worst"][type_str][constants::nameMap[constants::whichComp[i]]];
    }
  }

  return j;
}

void RedoLatexTable(TString geo){
    //json jbad = mergeJSONBadModuleLatex(geo);
    //Bad Components
    std::ifstream i(constants::localDir+"/Test" + geo + "/" + geo + "_BadmoduleTolerances.json");
    json jbad;
    i >> jbad;
    //Fit and Worst Components
    std::ifstream myBadFile(constants::localDir+"/Test" + geo + "/" + geo + "_moduleTolerances.json");
    json jtot;
    myBadFile >> jtot;

    printToleranceTableLatex(jtot, jbad, constants::localDir+"/Test" + geo + +"/" + geo + "_moduleTolerances.tex");
}

double GetWidthToA(double width){
  //width/2 == a/2*tan(pi/6)
  return width*TMath::Tan(TMath::Pi()/6);
}

double GetAToWidth(double a){
  return a/TMath::Tan(TMath::Pi()/6);
}

double getBacksideHeight(double cutoff, double delta = 0.){
  double cut = cutoff - 2*TMath::Sqrt(3)*delta;
  double h = (cut/TMath::Sqrt(3) - 6.5024)/TMath::Sqrt(3);
  return h;
}

double getCutoffWidth(double width, double cutoff, double delta = 0.){
  //B = sqrt(3)/3*(6*width - cutoff) + 2*delta
  //return (TMath::Sqrt(3)/3)*(6*width - cutoff) + 2*delta;
  double h = getBacksideHeight(cutoff, delta);
  return width - (h*2);
}

pair<double, double> GetPolar(TString name, double x1, double y1, double x0, double y0){
  double r = TMath::Sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
  double phi = TMath::ATan((y1 - y0)/(x1 - x0));
  if((x1 - x0) < 0) phi += TMath::Pi();
  if((x1 - x0) >= 0 && (y1 - y0) < 0) phi += 2*TMath::Pi();

  return make_pair(r, phi);
}

pair<double, double> GetCartesian(TString name, double r, double phi, double x0, double y0){
  double x1 = r*TMath::Cos(phi) + x0;
  double y1 = r*TMath::Sin(phi) + y0;
  
  return make_pair(x1, y1);
}

vector<double> findHighXbin(TH1D* h, bool swi = false){
  double mod = -999., belowZero = 0., width = 0.;;
  vector<double> output;
  int nbins = h->GetNbinsX();
  bool isFirst = true;
  if(swi){
    for(int bin = nbins; bin >= 1; bin--) {
      if(h->GetBinLowEdge(bin) > 0 && !isFirst) break;
      if(h->GetBinContent(bin) > 0 && isFirst){
        width = h->GetBinWidth(bin);
        mod = h->GetBinLowEdge(bin);
        isFirst = false;
      }
      if(h->GetBinLowEdge(bin) < 0){
        belowZero = h->GetBinContent(bin);
      }
    }
  } else {
    for(int bin = 1; bin <= nbins; bin++) {
      if(h->GetBinLowEdge(bin) > 0 && !isFirst) break;
      if(h->GetBinContent(bin) > 0 && isFirst){
        width = h->GetBinWidth(bin);
        mod = h->GetBinLowEdge(bin);
        isFirst = false;
      }
      if(h->GetBinLowEdge(bin) < 0){
        belowZero = h->GetBinContent(bin);
      }
    }
  }
  output.push_back((mod + width/2)*1000);
  output.push_back(width*1000);
  output.push_back(mod == -999. ? 0. : belowZero);
  return output;
}

map<string, double>  findProbabilities(TH1D* h){
  vector<double> xValue  = {
      	-0.185,
      	-0.175,
      	-0.150,
      	-0.125,
      	-0.100,
      	-0.075,
      	-0.050,
      	-0.025,
      	 0.000,
      	 0.010,
      	 0.020,
      	 0.025,
      	 0.050,
      	 0.075,
      	 0.100,
      	 0.125,
      	 0.150,
      	 0.175,
      	 0.200,
      	 0.225,
      	 0.250,
      	 0.275,
      	 0.300,
      	 0.325,
      	 0.350,
      	 0.375,
      };
  map<string, double> output;
  int nbins = h->GetNbinsX();
  //for(std::map<string,TH2Poly*>::iterator iter = overlap.begin(); iter != overlap.end(); ++iter){
  for(auto x : xValue){
    int ibin = h->FindBin(x);
    output.insert(std::pair<string, double>(to_string(x), h->GetBinContent(ibin)));
  }
  return output;
}

vector<TH1*> IntegrateHex(TH2Poly* h, TString geo, TString type, pair < double, double > center, double width, double axis, double binSize, int nPeaks, double width_backY = 0.){
  float min = -1. * binSize * 300;
  if((geo == "Semi" || geo == "Half")) min = -1. * binSize * 200;
  if(geo == "Three") min = -1. * binSize * 100;
  float max = binSize * 650;
  if(geo == "Semi" || geo == "Three") max += binSize * 50;
  if(geo == "Half") max += binSize * 150;
  int nbins = (axis - 0.1)/binSize*4;
  int nbins_1D = int(((max + width_backY) - min)/binSize);
  vector<TH1*> hist = {};
  for(auto iP = 0; iP != nPeaks + 1; iP++){
    delete gROOT->FindObject(TString(h->GetName()) + "_Peak" + to_string(iP));
    hist.push_back(new TH1D(TString(h->GetName()) + "_Peak" + to_string(iP), ";" + type + " Diff Width [mm]; Modules", nbins_1D, min, max + width_backY));
  }

  vector<double> angle = {0., TMath::Pi()/3, TMath::Pi()*2/3, TMath::Pi(), TMath::Pi()*4/3, TMath::Pi()*5/3};
  if(geo == "Five" || geo == "Semi") angle = {0., TMath::Pi()/2, TMath::Pi(), TMath::Pi()*4/3, TMath::Pi()*5/3};
  else if(geo == "Half") angle = {0., TMath::Pi()*2/3, TMath::Pi()*4/3, TMath::Pi()*5/3};
  else if(geo == "Three") angle = {TMath::Pi()/2, TMath::Pi()*4/3, TMath::Pi()*5/3};
  vector<int> index = {1, 1, 1, 1, 1, 1};
  if(geo == "Five" || geo == "Semi") index = {1, 2, 1, 3, 3};
  else if(geo == "Half") index = {1, 2, 1, 2};
  else if(geo == "Three") index = {1, 2, 2};
  for(int iA = 0; iA != (signed)angle.size(); iA++){
    for(auto iB = 0; iB != nbins; iB++){
      double shift = 0.;
      pair<double, double> cart = GetCartesian("", (binSize*iB + (width/2 - 300*binSize) + shift), angle[iA], center.first, center.second);
      pair<double, double> polar = GetPolar("", cart.first, cart.second, center.first, center.second);
      int bin = h->FindBin(cart.first, cart.second);
      if(bin == -5) continue;
      double binValue = h->GetBinContent(bin);

      //get distance to the edge
      double r = TMath::Sqrt(cart.first*cart.first + cart.second*cart.second) - width/2 + shift;
      double dr_center = center.first*TMath::Cos(angle[iA]) + center.second*TMath::Sin(angle[iA]);
           if(geo == "Five" && iA == 1) r += width/2 - GetWidthToA(width)/2;
      else if(geo == "Semi" && iA == 1) r += width/2;
      else if(geo == "half" && iA == 1) r += width/2;
      else if(geo == "Three" && iA == 0) r += width/2 + GetWidthToA(width)/2;
      r += dr_center;
      r += (width_backY/2);

      double bin1d = hist[index[iA]]->GetXaxis()->FindBin(r);
      double tot = hist[index[iA]]->GetBinContent(bin1d);
      hist[index[iA]]->SetBinContent(bin1d, tot + binValue);
      //fill plot with total
      bin1d = hist[0]->GetXaxis()->FindBin(r);
      tot = hist[0]->GetBinContent(bin1d);
      hist[0]->SetBinContent(bin1d, tot + binValue);
    }
  }

  return hist;
}

vector < pair <double, pair <double, double> > > newShapeInput(){
  double baseplate_w = 166.94;
  vector<double> baseplateInput = {6.572557, 6.573377, 6.573227, 6.568969, 6.56959, 6.569731, 
				  6.568373, 6.569033, 6.56842, 6.572988, 6.572592, 6.57396, 
				  6.573593, 6.573748, 6.573184, 6.572817, 6.572886, 6.573836, 
				  6.573114, 6.573073, 6.573021, 6.568787, 6.56881, 6.569536, 
				  6.569422, 6.569377, 6.569091, 6.573068, 6.573528, 6.573849, 
				  6.573138, 6.573199, 6.573384, 6.572994, 6.573926, 6.573588, 
				  6.568979, 6.569386, 6.569742};

  vector<double> kaptonInput = {6.573537, 6.571026, 6.569803, 6.569896, 6.572914, 6.570429,
         			6.571285, 6.569886, 6.572366, 6.570863, 6.569884, 6.57224,
                  		6.573037, 6.571025, 6.569289, 6.571091, 6.569678, 6.572536,
 				6.573057, 6.570624, 6.569357, 6.573133, 6.570727, 6.569481, 
   				6.57096,  6.569481, 6.572649, 6.571264, 6.569811, 6.572641
                               };
  vector<double> PCBBaseplateInput = {6.556401, 6.555577, 6.555663, 6.555603, 6.556096, 6.555644,
				6.558309, 6.558489, 6.558413, 6.557552, 6.557295, 6.557938,
				6.554244, 6.555199, 6.5551,   6.555635, 6.555705, 6.555156,
				6.556504, 6.556046, 6.556088, 6.554441, 6.5542,   6.55515,
				6.559327, 6.555097, 6.559529, 6.558453, 6.555274, 6.557107,
				6.56,     6.555561, 6.559438, 6.559253, 6.555536, 6.559403,
				6.559719, 6.555871, 6.558826
                               };

  vector<double> convert;
  //TH1* PCBBaseplate_meas_hist = new TH1D("PCBBaseplate", ";Measured Width [mm]; Modules", 50, 166.76, 167.09);
  TH1* baseplate_meas_hist = new TH1D("Baseplate", ";Measured Width [mm]; Modules", 50, 166.76, 167.09);
  TH1* kapton_meas_hist = new TH1D("Kapton", ";Measured Width [mm]; Modules", 50, 166.76, 167.09);
  //for(auto c: PCBBaseplateInput){
  //  PCBBaseplate_meas_hist->Fill(c*25.4);
  //}
  for(auto c: baseplateInput){
    baseplate_meas_hist->Fill(c*25.4);
  }
  for(auto c: kaptonInput){
    kapton_meas_hist->Fill(c*25.4);
  }

  //PCBBaseplate_meas_hist->Fit("gausn");
  //TF1 *PCBBaseplate_meas_avg_param = (TF1*)PCBBaseplate_meas_hist->GetFunction("gausn");
  baseplate_meas_hist->Fit("gausn");
  TF1 *baseplate_meas_avg_param = (TF1*)baseplate_meas_hist->GetFunction("gausn");
  kapton_meas_hist->Fit("gausn");
  TF1 *kapton_meas_avg_param = (TF1*)kapton_meas_hist->GetFunction("gausn");

  //prepHists({PCBBaseplate_meas_hist, baseplate_meas_hist, kapton_meas_hist}, false, false, false, {kMagenta, kRed, kBlue});
  //auto leg = prepLegends({baseplate_meas_hist, kapton_meas_hist, PCBBaseplate_meas_hist}, {baseplate_meas_hist->GetName(), kapton_meas_hist->GetName(), PCBBaseplate_meas_hist->GetName()}, "L");
  prepHists({baseplate_meas_hist, kapton_meas_hist}, false, false, false, {kRed, kBlue});
  auto leg = prepLegends({baseplate_meas_hist, kapton_meas_hist}, {baseplate_meas_hist->GetName(), kapton_meas_hist->GetName()}, "L");
  leg->SetTextSize(0.03);
  leg->SetY1NDC(leg->GetY2NDC() - 0.3);
  TCanvas* c = drawCompMatt({baseplate_meas_hist, kapton_meas_hist}, leg, -1., nullptr, "hist", true);
  gStyle->SetOptStat(0);
  TString name = "measured_dist";
  c->SetTitle(name);
  c->Print(constants::outputDir+"/"+name+".pdf");

  vector < pair <double, pair <double, double> > > avg_param;
  avg_param.push_back(make_pair(baseplate_meas_avg_param->GetParameter(0), make_pair(baseplate_meas_hist->GetMean(), baseplate_meas_hist->GetStdDev())));
  avg_param.push_back(make_pair(kapton_meas_avg_param->GetParameter(0), make_pair(kapton_meas_hist->GetMean(), kapton_meas_hist->GetStdDev())));
  //avg_param.push_back(make_pair(PCBBaseplate_meas_avg_param->GetParameter(0), make_pair(PCBBaseplate_meas_hist->GetMean(), PCBBaseplate_meas_hist->GetStdDev())));

  return avg_param;
}

json makeJSONModuleLatex(vector< pair< pair< string, string>, pair< double, double > > >& fit, vector< pair< pair< string, string>, pair< pair< double, double >, double > > >& worst,
                         vector< pair< pair< string, string>, pair< string, double> > >& prob){
  json j;
  int binnum = 0;
  for ( const auto &it : fit ) {
    j["Fit"][it.first.second][it.first.first] = {it.second.first*1000, it.second.second*1000};
    if(TString(it.first.first).Contains("Gaussian") && j["BinNum"].find(it.first.second) == j["BinNum"].end()){
      j["BinNum"][it.first.second] = binnum;
      binnum++;
    }
    if(!TString(it.first.first).Contains("Nominal")){
      j["Distribution"][it.first.first] = it.first.first;
    }
  }
  for ( const auto & it : worst ) {
    j["Worst"][it.first.second][it.first.first] = {it.second.first.first*1000, it.second.first.second*1000, it.second.second};
  }
  for ( const auto & it : prob ) {
    if(TString(it.first.first).Contains("_max")){
      j["Distribution"][it.first.first] = it.first.first;
    }
    j["Worst"]["Probability"][it.first.second][it.first.first][it.second.first] = it.second.second;
  }

  return j;
}

json makeJSONBadModuleLatex(vector< pair< pair< string, string>, pair< pair< pair< double, double >, pair< double, double > >, double > > >& worst, vector< pair< pair< string, string>, double > >& badOverlap){
  json j;
  for ( const auto & it : worst ) {
    j["Worst"][it.first.second][it.first.first]["Sensor"] = it.second.first.first.first;
    j["Worst"][it.first.second][it.first.first]["Kapton"] = it.second.first.first.second;
    j["Worst"][it.first.second][it.first.first]["Baseplate"] = it.second.first.second.first;
    j["Worst"][it.first.second][it.first.first]["PCB"] = it.second.first.second.second;
    j["Worst"][it.first.second][it.first.first]["Total"] = it.second.second;
  }
  for( const auto & it : badOverlap ){
    j["Worst"]["Bad Overlaps"][it.first.first][it.first.second] = it.second;
  }

  return j;
}

double getRandomValue(double width, double error, TString type){
  double rand = 0.;
  if(type.Contains("Gaus"))
    rand = gRandom->Gaus(width, error/3);
  else if(type.Contains("Flat"))
    rand = gRandom->Uniform(width - error, width + error);

  return rand;
}

pair < double, double >  getPolyCenter(vector<pair<double, double> > p){
  double xf = 0., yf = 0., div = 0.;
  for(int i = 0; i < (signed)p.size(); i++){
    int n0 = i, n1 = (i + 1) % p.size();
    xf += (p[n0].first + p[n1].first)*(p[n0].first*p[n1].second - p[n1].first*p[n0].second);
    yf += (p[n0].second + p[n1].second)*(p[n0].first*p[n1].second - p[n1].first*p[n0].second);
    div += (p[n0].first*p[n1].second - p[n1].first*p[n0].second);
  }

  return {xf/(3*div), yf/(3*div)};
}

vector<pair<double, double> > GetPoints(TString geo, double a_in, double width){
  double x[6], y[6];
  if(geo == "Full"){
    x[0] = -1*width/2;
    y[0] = -1*a_in/2;
    x[1] = x[0];
    y[1] = y[0] + a_in;
    x[2] = x[1] + a_in*TMath::Sqrt(3)/2.0;
    y[2] = y[1] + a_in/2.0;
    x[3] = x[2] + a_in*TMath::Sqrt(3)/2.0;
    y[3] = y[1];
    x[4] = x[3];
    y[4] = y[0];
    x[5] = x[2];
    y[5] = y[4] - a_in/2.0;
  } else if(geo == "Five"){
    x[0] = -1*width/2;
    y[0] = -1*a_in/2;
    x[1] = x[0];
    y[1] = y[0] + a_in;
    x[2] = x[1] + a_in*TMath::Sqrt(3);
    y[2] = y[1];
    x[3] = x[2];
    y[3] = y[0];
    x[4] = x[1] + a_in*TMath::Sqrt(3)/2.0;
    y[4] = y[3] - a_in/2.0;
  } else if(geo == "Semi"){
    x[0] = -1*width/2;
    y[0] = -1*a_in/2;
    x[1] = x[0];
    y[1] = y[0] + a_in/2;
    x[2] = x[1] + a_in*TMath::Sqrt(3);
    y[2] = y[1];
    x[3] = x[2];
    y[3] = y[0];
    x[4] = x[1] + a_in*TMath::Sqrt(3)/2.0;
    y[4] = y[3] - a_in/2.0;
  } else if(geo == "Half"){
    x[0] = -1*width/2;
    y[0] = -1*a_in/2;
    x[1] = x[0] + a_in*TMath::Sqrt(3);
    y[1] = y[0] + a_in;
    x[2] = x[1];
    y[2] = y[0];
    x[3] = x[0] + a_in*TMath::Sqrt(3)/2.0;
    y[3] = y[2] - a_in/2.0;
  } else if(geo == "Three"){
    x[0] = -1*width/2;
    y[0] = -1*a_in/2;
    x[1] = x[0] + a_in*TMath::Sqrt(3);
    y[1] = y[0];
    x[2] = x[0] + a_in*TMath::Sqrt(3)/2.0;
    y[2] = y[0] - a_in/2.0;
  }

  vector<pair<double, double> > points;
  int nPoints = 6;
  if(geo == "Five" or geo == "Semi") nPoints = 5;
  else if(geo == "Half") nPoints = 4;
  else if(geo == "Three") nPoints = 3;
  for(auto i = 0; i < nPoints; i++){
    points.push_back(make_pair(x[i], y[i]));
  }

  return points;
}

pair < double, double > HoneycombCustom(TString geo, TH2Poly* hc, Double_t a, double width, double a_in = 96.67, int steps = 10){
  // Add the bins
  vector<pair<double, double> >  points = GetPoints(geo, a_in, width);
  pair < double, double > center = getPolyCenter(points);
  Double_t xloop[4], yloop[4];
  //Radius of points
  vector<double> radius, angle, ratio;
  float rMin = 9999999.;
  for(int i = 0; i < (signed)points.size(); i++){
    points.at(i).first = points.at(i).first - center.first;
    points.at(i).second = points.at(i).second - center.second;
    pair<double, double> polar = GetPolar(TString(hc->GetName()), points.at(i).first, points.at(i).second, 0., 0.);
    radius.push_back(polar.first);
    angle.push_back(polar.second);
    if(polar.first < rMin) rMin = polar.first;
  }
  for(int i = 0; i < (signed)points.size(); i++) ratio.push_back(radius[i]/rMin);
  for(int theta = 0; theta != (signed)angle.size(); theta++){
    int first = theta % angle.size();
    int second = (theta + 1) % angle.size();
    for(int neg = 0; neg < 2; neg++){
      xloop[0] = points.at(first).first;
      yloop[0] = points.at(first).second;
      xloop[1] = points.at(second).first;
      yloop[1] = points.at(second).second;
      double sign = neg ? -1. : 1.;
      int count = 0;
      for(auto ibin = 1; ibin < steps; ibin++){
        pair<double, double> cart = GetCartesian(TString(hc->GetName()), radius[first] + sign*a*ibin*ratio[first], angle[first], 0., 0.);
        xloop[3] = cart.first;
        yloop[3] = cart.second;
        cart = GetCartesian(TString(hc->GetName()), radius[second] + sign*a*ibin*ratio[second], angle[second], 0., 0.);
        xloop[2] = cart.first;
        yloop[2] = cart.second;
        if(count == 300 && neg == 1) break;
        if((geo == "Semi" || geo == "Half" || geo == "Three") && count == 200 && neg == 1) break;
        if(geo == "Three" && count == 100 && neg == 1) break;
        hc->AddBin(4, xloop, yloop);
        xloop[0] = xloop[3];
        yloop[0] = yloop[3];
        xloop[1] = xloop[2];
        yloop[1] = yloop[2];
        count++;
      }
    }
  }
  return center;
}

double ScaleSide(TString geo, int side, double width){
  double newSide = width;

       if(geo == "Five"  && side == 1) newSide = width*TMath::Sqrt(3)/2;
  else if(geo == "Five"  && side == 2) newSide = width*3/4;
  else if(geo == "Semi"  && side == 1) newSide = GetWidthToA(width);
  else if(geo == "Semi"  && side == 2) newSide = GetWidthToA(width)*TMath::Sqrt(3)/2;
  else if(geo == "Half"  && side == 0) newSide = GetWidthToA(width)*3/2;
  else if(geo == "Half"  && side == 1) newSide = width*3/4;
  else if(geo == "Three" && side == 0) newSide = GetWidthToA(width)/2;
  else if(geo == "Three" && side > 0)  newSide = (GetWidthToA(width)*TMath::Sqrt(3))/4; 

  return newSide;
}

pair<double, double> FillAllSides(TString geo, double max, TH2Poly* hc, TH1D* hMin, TH1D* hMax, double nom, 
		vector<double> rand, double shift_x, double shift_y, 
		double width_new, pair < double, double > cen_base,
		vector<double> comp = {}, double min = 0.,
		vector<double> comp2 = {}, 
                pair<double, double> backside_x_err = make_pair(0.0, 0.0), pair<double, double> backside_y_err = make_pair(0.0, 0.0), TString coordAxis = "", double comp_shift_x = 0., double comp_shift_y = 0., double comp2_shift_x = 0., double comp2_shift_y = 0., 
                pair<double, double> BasToCas_shift = make_pair(0.0, 0.0), vector<pair<double, double>> AdjBasToCas_shift = {make_pair(0., 0.), make_pair(0., 0.), make_pair(0., 0.), make_pair(0., 0.), make_pair(0., 0.), make_pair(0., 0.)})
{
  //Widths
  vector<pair<pair<double, double>, double>> location;
  double dx = (shift_x), dy = (shift_y);
  pair<double, double> rOut;
  vector<double> forward = {0., TMath::Pi()/3, TMath::Pi()*2/3, TMath::Pi(), TMath::Pi()*4/3, TMath::Pi()*5/3};
  if(geo == "Five" || geo == "Semi") forward = {0., TMath::Pi()/2, TMath::Pi(), TMath::Pi()*4/3, TMath::Pi()*5/3};
  else if(geo == "Half") forward = {0., TMath::Pi()*2/3, TMath::Pi()*4/3, TMath::Pi()*5/3};
  else if(geo == "Three") forward = {TMath::Pi()/2, TMath::Pi()*4/3, TMath::Pi()*5/3};
  vector<int> index = {0, 1, 2, 0, 1, 2};
  if(geo == "Five" || geo == "Semi") index = {0, 1, 0, 2, 2};
  else if(geo == "Half") index = {0, 1, 0, 1};
  else if(geo == "Three") index = {0, 1, 2};
  double r_out = 0.;
  double minValue = min;
  double minR =  9999999.;
  double maxR = -9999999.;
  for(int iF = 0; iF != (signed)forward.size(); iF++){
    double secondary = ScaleSide(geo, index[iF], nom);
    double third = 0.;
    if(comp.size() > 0) secondary = comp[index[iF]];
    if(comp2.size() > 0) third = comp2[index[iF]];
 
    double r_out = 0., r_out1 = 0., r_out2 = 0., dr = 0.;
    if(TString(hc->GetName()).Contains("sen_pcb_kap")){
      // Get test values
      // rand = pcb_backside
      // secondary = sensor_backside
      // third = kapton_backside
      //shift_xy = PcbToBas_shift
      //comp_shift_xy = SenToBas_shift
      //comp2_shift_xy = SenToKap_shift
      double r_ps = (rand[index[iF]] - secondary)/2; // pcb - sensor
      double dr_pk = (shift_x - (comp_shift_x + comp2_shift_x))*TMath::Cos(forward[iF]) + (shift_y - (comp_shift_y + comp2_shift_y))*TMath::Sin(forward[iF]); // shift is x/y directions
      double dr_ps = (shift_x - comp_shift_x)*TMath::Cos(forward[iF]) + (shift_y - comp_shift_y)*TMath::Sin(forward[iF]); // shift is x/y directions
      double dr_sk = comp2_shift_x*TMath::Cos(forward[iF]) + comp2_shift_y*TMath::Sin(forward[iF]); // shift is x/y directions
      double r_sk = (secondary - third)/2;
      double r_pk = (rand[index[iF]] - third)/2;

      if(coordAxis.Contains("Y")){
        double pad_y = 0.5*TMath::Sin(TMath::Pi()/6);
        if((r_sk + dr_sk) < minValue) {r_out = r_sk; dr = dr_sk;}
        else if((r_ps + dr_ps) < 0.) {r_out = r_ps; minValue = 0.; dr = dr_ps;}
        else {r_out = r_pk; dr = dr_pk;}
      }

      if(coordAxis.Contains("X")){
        double pad_x = 0.5*TMath::Cos(TMath::Pi()/6);
        double pad_min = min*TMath::Cos(TMath::Pi()/6);
        if((r_pk + dr_pk + pad_x) < pad_min) {r_out = r_pk + dr_pk + pad_x; minValue = pad_min;}
        else if((r_pk + dr_pk - pad_x) > 1.750) {r_out = 2.0 - (r_pk + dr_pk - pad_x); minValue = pad_min;}
        else if((r_sk + dr_sk) < 0.250) {r_out = r_sk + dr_sk; minValue = pad_min;}
        else {r_out = r_pk + dr_pk; minValue = pad_min;}
        dr = 0.;
      }

      if(constants::debug && TString(hc->GetName()).Contains(constants::whichOverlap)){ 
        cout << hc->GetName() << endl;
        cout << r_ps << " = (" << rand[index[iF]] << " - " << secondary << ")/2" << endl;
        cout << r_sk << " = (" << secondary << " - " << third << ")/2" << endl;
        cout << r_pk << " = (" << rand[index[iF]] << " - " << third << ")/2" << endl;
        cout << "r_out: " << r_out << endl;
      }

    } else if(TString(hc->GetName()).Contains("bas_kap_sen_stack_hist")){
      // rand = kapton 
      // secondary = baseplate
      // third = sensor
      //shift_xy = SenToBas_shift
      //comp_shift_xy = SenToKap_shift
      // Get test values
      r_out1 = (rand[index[iF]] - secondary)/2;
      r_out2 = (nom - third)/2;
      //r_out2 = (rand[index[iF]] - third)/2;
      r_out = r_out1 + r_out2;
      dr = (shift_x + comp_shift_x)*TMath::Cos(forward[iF]) + (shift_y + comp_shift_y)*TMath::Sin(forward[iF]);
    } else {
      r_out = (rand[index[iF]] - secondary)/2;
      if(constants::debug && TString(hc->GetName()).Contains(constants::whichOverlap)) cout << hc->GetName() << ": " << r_out << " = (" << rand[index[iF]] << " - " << secondary << ")/2" << endl;
      dr = dx*TMath::Cos(forward[iF]) + dy*TMath::Sin(forward[iF]);
    }
    double dr_cen = cen_base.first*TMath::Cos(forward[iF]) + cen_base.second*TMath::Sin(forward[iF]);

    if(geo == "Five" && index[iF] == 1) {
      r_out += GetWidthToA(width_new)/2;
    } else if(geo == "Three" && index[iF] == 0) {
      r_out -= GetWidthToA(width_new)/2;
    } else if(!(geo == "Semi" && index[iF] == 1) && !(geo == "Half" && forward[iF] == TMath::Pi()*2/3)){
      r_out += width_new/2;
    }
    if(constants::debug && TString(hc->GetName()).Contains(constants::whichOverlap) && (r_out + dr - dr_cen - minValue - 0.7) > 0.254 && (r_out + dr - dr_cen - minValue - 0.7) < 0.258){ 
      cout << hc->GetName() << ": " << r_out + dr - dr_cen - minValue << " = " << r_out << " + " << dr << " + " << dr_cen << endl;
      cout << "shifts = (" << dx << ", " << dy << ")" << endl;
    }   

    rOut = GetCartesian(TString(hc->GetName()), r_out + dr - dr_cen - minValue, forward[iF], 0., 0.);
    hc->Fill(rOut.first, rOut.second);

    //Check Negative
    double r = TMath::Sqrt(rOut.first*rOut.first + rOut.second*rOut.second) - width_new/2;
    double dr_cen_base = cen_base.first*TMath::Cos(forward[iF]) + cen_base.second*TMath::Sin(forward[iF]);
    double cassetteR = 0.;
    if(TString(hc->GetName()).Contains("bas_kap_stack_hist")) cassetteR = (BasToCas_shift.first + AdjBasToCas_shift[iF].first)*TMath::Cos(forward[iF]) + (BasToCas_shift.second + AdjBasToCas_shift[iF].second)*TMath::Sin(forward[iF]);
    
         if(geo == "Five" && iF == 1) r += width_new/2 - GetWidthToA(width_new)/2;
    else if(geo == "Semi" && iF == 1) r += width_new/2;
    else if(geo == "half" && iF == 1) r += width_new/2;
    else if(geo == "Three" && iF == 0) r += width_new/2 + GetWidthToA(width_new)/2;
    r += dr_cen_base;
    minR = std::min(minR, r);
    maxR = std::max(maxR, r + cassetteR);
  }
  if(hMin) hMin->Fill(minR, constants::weight);
  if(hMax) hMax->Fill(maxR, constants::weight);
  return make_pair(minR, maxR);
}

void AddLineNomHex(double width, TString geo = "Full"){
   double a_in = GetWidthToA(width);
   // Add the bins
  vector<pair<double, double> >  points = GetPoints(geo, a_in, width);
  pair < double, double > center = getPolyCenter(points);
  for(int i = 0; i < (signed)points.size(); i++){
    points.at(i).first = points.at(i).first - center.first;
    points.at(i).second = points.at(i).second - center.second;
  }

  for(int iS = 0; iS < (signed)points.size(); iS++){
    int first = iS % points.size();
    int second = (iS + 1) % points.size();
    TLine *line = new TLine(points.at(first).first, points.at(first).second, points.at(second).first, points.at(second).second);
    line->SetLineColor(kBlack);
    line->Draw();
  }
}

void ExtendPlots(TString geo){
  //int nbins = 650;
  //double axis = width_new/2 + nbins*step + 0.1;
  if(geo == "Semi"){
    constants::axis  = constants::width_new/2 + constants::nbins*constants::step + 0.1 + 0.5;
    constants::nbins = 700;
  } else if(geo == "Half"){
    constants::axis  = constants::width_new/2 + constants::nbins*constants::step + 0.1 + 1.5;
    constants::nbins = 800;
  } else if(geo == "Three"){
    constants::axis  = constants::width_new/2 + constants::nbins*constants::step + 0.1 + 1.4;
    constants::nbins = 700;
  }
}

void WhichGeometry(TString geo){
  if(geo == "Semi"){
    constants::pcb_w = GetAToWidth(constants::pcb_a_const_semi);
    constants::sensor_w = GetAToWidth(constants::sensor_a_const_semi);
    constants::kapton_w = GetAToWidth(constants::kapton_a_const_semi);
    constants::baseplate_w = GetAToWidth(constants::baseplate_a_const_semi);
  } else {
    constants::pcb_w = constants::pcb_w_const;
    constants::sensor_w = constants::sensor_w_const;
    constants::kapton_w = constants::kapton_w_const;
    constants::baseplate_w = constants::baseplate_w_const;
  }
}

void ExtendWidths(TString par, TString geo){
      WhichGeometry(geo);
      vector<TString> ext = splitString(par, "_");
      bool ispcb = false, iskap = false, issen = false, issenkap = false;
      for(int iS = 0; iS != (signed)ext.size(); iS++){
        TString par = ext[iS];
        if(par.Contains("otherCenter")){
          constants::baseplate_err = 0.029;
        }

        if(par.Contains("PCB")){
          TString buffer = par;
          TString pcb_new_shift_str = buffer.ReplaceAll("PCBplus", "");
          pcb_new_shift_str.ReplaceAll("PCBminus", "");
          float pcb_new_shift = pcb_new_shift_str.Atof()/1000;
         
          if(par.Contains("plus"))  constants::pcb_w += pcb_new_shift;
          if(par.Contains("minus")) constants::pcb_w -= pcb_new_shift;
          ispcb = true;
        }

        if(par.Contains("Kapton")){
          TString buffer = par;
          TString kapton_new_shift_str = buffer.ReplaceAll("Kaptonplus", "");
          kapton_new_shift_str.ReplaceAll("Kaptonminus", "");
          float kapton_new_shift = kapton_new_shift_str.Atof()/1000;
         
          if(par.Contains("plus"))  constants::kapton_w += kapton_new_shift;
          if(par.Contains("minus")) constants::kapton_w -= kapton_new_shift;
          iskap = true;
        }

        if(par.Contains("senTokap")){
          TString buffer = par;
          TString kapton_new_shift_str = buffer.ReplaceAll("senTokap", "");
          float kapton_new_shift = kapton_new_shift_str.Atof()/1000;
         
          constants::senToKap_min = kapton_new_shift;
          constants::base_kap_min = kapton_new_shift;
          issenkap = true;
        } else if(!issenkap) {constants::senToKap_min = 0.0; constants::base_kap_min = 0.100;}

        if(par.Contains("Sensor")){
          if(par.Contains("new")){ 
            constants::sensor_shift_x = 0.050; 
            constants::sensor_shift_y = 0.050;
          } else if(par.Contains("mid")) {
            constants::sensor_shift_x = 0.100;
            constants::sensor_shift_y = 0.050;
          } else if(par.Contains("old")) {
            constants::sensor_shift_x = 0.200;
            constants::sensor_shift_y = 0.050;
          }
          issen = true;
        } else if(!issen){
          constants::sensor_shift_x = 0.200;
          constants::sensor_shift_y = 0.050;
        }  
      }
}

void module2DTolerances(){
  SetStyle();
  TDR_EXTRA_LABEL_ = "";
  TDR_EXTRA_LABEL_2 = "";

  for(auto &geo_str : constants::Geometry){
    TString geo = TString(geo_str);
    constants::outputDir = baseDir + "/" + baseDir + "_" + geo;
    gSystem->mkdir(constants::outputDir, true);
    TFile *outFile = new TFile(constants::outputDir+"/"+geo+"_2Doverlap.root", "RECREATE");
    gRandom = new TRandom3(0);

    int nPeaks = 1;
         if(geo == "Five" || geo == "Semi") nPeaks = 3;
    else if(geo == "Half" || geo == "Three") nPeaks = 2;

    map<TString, pair<double, double> > center;
    vector < pair < double, double > > points = GetPoints(geo, GetWidthToA(constants::width_new), constants::width_new);
    center.emplace("new", getPolyCenter(points));

    vector< pair< pair< string, string>, pair< pair< pair< double, double >, pair< double, double > >, double > > > bad_values = {};
    vector< pair< pair< string, string>, double > > badOverlap = {};

    int iBad = 0;
    TH1D* hBad = new TH1D(geo + "_Bad", "Bad" + geo, constants::Dist.size(), 0, constants::Dist.size());
    for(auto &type_str: constants::Dist){
      TString type = TString(type_str);
      if(!type.Contains(baseDir)) continue;
      gSystem->mkdir(constants::outputDir+"/"+type, true);
      double nBadModules = 0.;

      double sigma = 1., mean = 1., kapton_sigma = 1., kapton_mean = 1.;
      if(type.Contains("Custom")){
        vector < pair <double, pair<double, double> > > custom = newShapeInput();
        sigma = custom[0].second.second/constants::baseplate_w_err;
        mean = custom[0].second.first/constants::baseplate_w;
        kapton_sigma = custom[1].second.second/constants::kapton_w_err;
        kapton_mean = custom[1].second.first/constants::kapton_w;
        constants::baseValue_total *= mean;
      }

      ExtendPlots(geo);
      ExtendWidths(type, geo);

      vector<double> howBad = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
      vector<double> pcb, kapton, baseplate, sensor, pcb_bond, kapton_bond, sensor_bond, pcb_backside, kapton_backside, sensor_backside, pcb_backside_x, kapton_backside_x, sensor_backside_x;
      double KapToBas_x_shift = 0., SenToKap_x_shift = 0., KapToBas_y_shift = 0., SenToKap_y_shift = 0.;
      map<TString, TH2Poly*> components, overlap;
      map<TString, TH1D*> overlapMin, overlapMax;
      components.clear();
      overlap.clear();

      components = {
      	{"pcb", new TH2Poly(geo + "_" + type + "pcb_2d", ";" + geo + " " + type + " Width [mm];Width [mm];Components", -1*constants::axis, constants::axis, -1*constants::axis, constants::axis)},
      	{"kap", new TH2Poly(geo + "_" + type + "kap_2d", ";" + geo + " " + type + " Width [mm];Width [mm];Components", -1*constants::axis, constants::axis, -1*constants::axis, constants::axis)},
      	{"sen", new TH2Poly(geo + "_" + type + "sen_2d", ";" + geo + " " + type + " Width [mm];Width [mm];Components", -1*constants::axis, constants::axis, -1*constants::axis, constants::axis)},
      	{"bas", new TH2Poly(geo + "_" + type + "bas_2d", ";" + geo + " " + type + " Width [mm];Width [mm];Components", -1*constants::axis, constants::axis, -1*constants::axis, constants::axis)},
      };

      for(int i = 0; i != (signed)constants::whichComp.size(); i++){
        overlap.insert(pair<TString, TH2Poly*>(constants::whichComp[i], new TH2Poly(geo+"_"+type+constants::whichComp[i], ";"+geo+" "+type+" Diff Width [mm];Diff Width [mm];Overlaps", -1*constants::axis, 1*constants::axis, -1*constants::axis, 1*constants::axis)));
        overlapMin.insert(pair<TString, TH1D*>(constants::whichComp[i], new TH1D(geo+"_"+type+constants::whichComp[i]+"_min", ";"+geo+" "+type+" Diff Width [mm];Overlaps", (constants::axis - 0.1)/constants::step*4, -1.*constants::step*300, constants::step*650)));
        overlapMax.insert(pair<TString, TH1D*>(constants::whichComp[i], new TH1D(geo+"_"+type+constants::whichComp[i]+"_max", ";"+geo+" "+type+" Diff Width [mm];Overlaps", (constants::axis - 0.1)/constants::step*4, -1.*constants::step*300, constants::step*650)));
      }
       
      TH2D* corr = new TH2D(geo + "_" + type + "correlation", "correlation" + geo, overlap.size(), 0, overlap.size(), overlap.size(), 0, overlap.size());     
      TH1D* hBadComp = new TH1D(geo + "_" + type + "_BadComponents", "BadComponents" + geo, 4, 0, 4);

      for(std::map<TString,TH2Poly*>::iterator iter = components.begin(); iter != components.end(); ++iter)
        HoneycombCustom(geo, iter->second, constants::step, constants::width_new, GetWidthToA(constants::width_new), constants::nbins);
      for(std::map<TString,TH2Poly*>::iterator iter = overlap.begin(); iter != overlap.end(); ++iter)
        HoneycombCustom(geo, iter->second, constants::step, constants::width_new, GetWidthToA(constants::width_new), constants::nbins);

      for(auto i = 0; i != constants::max; i++){
        pcb.clear();
        kapton.clear();
        baseplate.clear();
        sensor.clear();
        if(i == 0){
          cout << "baseplate: " << constants::baseplate_w*mean << " +/- " << constants::baseplate_w_err*sigma << endl;
          cout << "pcb: " << constants::pcb_w*kapton_mean << " +/- " << constants::pcb_w_err*kapton_sigma << endl;
          cout << "kapton: " << constants::kapton_w*kapton_mean << " +/- " << constants::kapton_w_err*kapton_sigma << endl;
          cout << "sensor: " << constants::sensor_w*kapton_mean << " +/- " << constants::sensor_w_err*kapton_sigma << endl;
          cout << "center: " << constants::baseplate_err << endl;
          cout << "PCB shift: " << constants::PcbToBas_shift_r<< endl;
          cout << "Sensor shift: " << constants::sensor_shift_x << endl;
	}
	//Get widths for each component and each side
        int sides = 3;
        if(geo == "Half") sides = 2;
        for(auto iS = 0; iS != sides; iS++){
          double pcb_w_new = ScaleSide(geo, iS, constants::pcb_w*kapton_mean);
          double kapton_w_new = ScaleSide(geo, iS, constants::kapton_w*kapton_mean);
          double baseplate_w_new = ScaleSide(geo, iS, constants::baseplate_w*mean);
          double sensor_w_new = ScaleSide(geo, iS, constants::sensor_w*kapton_mean);
          pcb.push_back(getRandomValue(pcb_w_new, constants::pcb_w_err*kapton_sigma, type));
          kapton.push_back(getRandomValue(kapton_w_new, constants::kapton_w_err*kapton_sigma, type));
          baseplate.push_back(getRandomValue(baseplate_w_new, constants::baseplate_w_err*sigma, type));
          sensor.push_back(getRandomValue(sensor_w_new, constants::sensor_w_err*kapton_sigma, type));
          kapton_bond.push_back(kapton.at(iS) - (constants::gold_size - 0.650)*2);
          sensor_bond.push_back(sensor.at(iS) - (constants::gold_size - 0.730)*2);
          pcb_bond.push_back(pcb.at(iS) - constants::gold_size*2);
          // Y tolerance
          sensor_backside.push_back(getCutoffWidth(sensor.at(iS), 15.590));
          pcb_backside.push_back(getCutoffWidth(pcb.at(iS), 15.590, 0.540));
          kapton_backside.push_back(kapton.at(iS) - 3.302*2);
          // X tolerance
          // Ac = a - (2*6.5024)
          sensor_backside_x.push_back(GetWidthToA(sensor.at(iS)) - (2*6.5024));
          pcb_backside_x.push_back(GetWidthToA(pcb.at(iS)) - (2*6.2648));
          kapton_backside_x.push_back(GetWidthToA(kapton.at(iS)) - (2*7.2393));
        }//get three random sides
        //Get shift in x and y, soon add theta also
        pair<double, double> SenToBas_shift = GetCartesian("", getRandomValue(0, constants::baseplate_err, type), getRandomValue(0, constants::PcbToBas_shift_theta, type), 0., 0.);
        pair<double, double> BasToCas_shift = GetCartesian("", getRandomValue(0, constants::cassette_err, type), getRandomValue(0, constants::PcbToBas_shift_theta, type), 0., 0.);
        vector<pair<double, double> > AdjBasToCas_shift = {};
        for(int i = 0; i != 6; i++) AdjBasToCas_shift.push_back(GetCartesian("", getRandomValue(0, constants::cassette_err, type), getRandomValue(0, constants::PcbToBas_shift_theta, type), 0., 0.));
        pair<double, double> PcbToBas_shift = GetCartesian("", getRandomValue(0, constants::PcbToBas_shift_r, type), getRandomValue(0, constants::PcbToBas_shift_theta, type), 0., 0.);
        SenToKap_x_shift = getRandomValue(0, constants::sensor_shift_x, type);
        SenToKap_y_shift = getRandomValue(0, constants::sensor_shift_y, type);

//pair<double, double> FillAllSides(TString geo, double max, TH2Poly* hc, TH1D* hMin, TH1D* hMax, double nom, 
//		vector<double> rand, double shift_x, double shift_y, 
//		double width_new, pair < double, double > cen_base,
//		vector<double> comp = {}, double min = 0.,
//		vector<double> comp2 = {}, 
//                pair<double, double> backside_x_err = make_pair(0.0, 0.0), pair<double, double> backside_y_err = make_pair(0.0, 0.0), TString coordAxis = "", double comp_shift_x = 0., double comp_shift_y = 0., double comp2_shift_x = 0., double comp2_shift_y = 0.){
        //Component values
        vector<pair<double, double>> isNegative = {};
        FillAllSides(geo, double(constants::max), components["bas"], nullptr, nullptr, constants::baseValue_total, baseplate, SenToBas_shift.first,     SenToBas_shift.second,      constants::width_new, center["new"]);
        FillAllSides(geo, double(constants::max), components["kap"], nullptr, nullptr, constants::baseValue_total,    kapton, SenToBas_shift.first,     SenToBas_shift.second,      constants::width_new, center["new"]);
        FillAllSides(geo, double(constants::max), components["sen"], nullptr, nullptr, constants::baseValue_total,    sensor, SenToKap_x_shift,     SenToKap_y_shift,      constants::width_new, center["new"]);
        FillAllSides(geo, double(constants::max), components["pcb"], nullptr, nullptr, constants::baseValue_total, 	 pcb, PcbToBas_shift.first, PcbToBas_shift.second, constants::width_new, center["new"]);
        //Overlap Values
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["sen_kap_stack_hist"], overlapMin["sen_kap_stack_hist"], overlapMax["sen_kap_stack_hist"], constants::baseValue_total,    kapton, SenToKap_x_shift, SenToKap_y_shift, constants::width_new, center["new"], sensor, constants::senToKap_min));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["sen_bas_stack_hist"], overlapMin["sen_bas_stack_hist"], overlapMax["sen_bas_stack_hist"], constants::baseValue_total, baseplate, SenToBas_shift.first, SenToBas_shift.second, constants::width_new, center["new"], sensor));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["bas_kap_stack_hist"], overlapMin["bas_kap_stack_hist"], overlapMax["bas_kap_stack_hist"], constants::baseValue_total,    kapton, SenToKap_x_shift - SenToBas_shift.first, SenToKap_y_shift - SenToBas_shift.second, constants::width_new, center["new"], baseplate, 0., {}, make_pair(0., 0.), make_pair(0.0, 0.0), "", 0., 0., 0., 0., BasToCas_shift, AdjBasToCas_shift));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["bas_kap_sen_stack_hist"], overlapMin["bas_kap_sen_stack_hist"], overlapMax["bas_kap_sen_stack_hist"], constants::kapton_w_const,     kapton, SenToBas_shift.first, SenToBas_shift.second, constants::width_new, center["new"], baseplate, constants::base_kap_min, sensor, make_pair(0.0, 0.0), make_pair(0.0, 0.0), "", SenToKap_x_shift, SenToKap_y_shift));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["sen_pcb_stack_hist"], overlapMin["sen_pcb_stack_hist"], overlapMax["sen_pcb_stack_hist"], constants::baseValue_total,       pcb, PcbToBas_shift.first - SenToBas_shift.first, PcbToBas_shift.second - SenToBas_shift.second, constants::width_new, center["new"], sensor));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["pcb_bas_stack_hist"], overlapMin["pcb_bas_stack_hist"], overlapMax["pcb_bas_stack_hist"], constants::baseValue_total, baseplate, PcbToBas_shift.first, PcbToBas_shift.second, constants::width_new, center["new"], pcb));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["pcb_kap_stack_hist"], overlapMin["pcb_kap_stack_hist"], overlapMax["pcb_kap_stack_hist"], constants::baseValue_total,    kapton, SenToKap_x_shift + (PcbToBas_shift.first - SenToBas_shift.first), SenToKap_y_shift + (PcbToBas_shift.second - SenToBas_shift.second), constants::width_new, center["new"], pcb));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["kap_pcb_hist"],       overlapMin["kap_pcb_hist"],       overlapMax["kap_pcb_hist"],       constants::baseValue_total, kapton_bond, SenToKap_x_shift + (PcbToBas_shift.first - SenToBas_shift.first), SenToKap_y_shift + (PcbToBas_shift.second - SenToBas_shift.second), constants::width_new, center["new"], pcb_bond, constants::gold_min));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["sen_pcb_hist"],       overlapMin["sen_pcb_hist"],       overlapMax["sen_pcb_hist"],       constants::baseValue_total, sensor_bond, PcbToBas_shift.first - SenToBas_shift.first, PcbToBas_shift.second - SenToBas_shift.second, constants::width_new, center["new"], pcb_bond, constants::gold_min));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["sen_pcb_kap_x_hist"], overlapMin["sen_pcb_kap_x_hist"], overlapMax["sen_pcb_kap_x_hist"], constants::baseValue_total,    pcb_backside_x, PcbToBas_shift.first, PcbToBas_shift.second, constants::width_new, center["new"], sensor_backside_x, constants::backside_min, kapton_backside_x, constants::backside_x_err, constants::backside_y_err, "X", SenToBas_shift.first, SenToBas_shift.second, SenToKap_x_shift, SenToKap_y_shift));
        isNegative.push_back(FillAllSides(geo, double(constants::max), overlap["sen_pcb_kap_y_hist"], overlapMin["sen_pcb_kap_y_hist"], overlapMax["sen_pcb_kap_y_hist"], constants::baseValue_total,    pcb_backside, PcbToBas_shift.first, PcbToBas_shift.second, constants::width_new - constants::width_backY, center["new"], sensor_backside, constants::backside_min, kapton_backside, constants::backside_x_err, constants::backside_y_err, "Y", SenToBas_shift.first, SenToBas_shift.second, SenToKap_x_shift, SenToKap_y_shift));

        bool isBad = false;
        vector<int> xCorr, yCorr;
        vector<int> xBadComp;
        // 0 = sensor, 1 = kapton, 2 = baseplate, 3 = pcb
        // 0 = sen to kap, 1 = sen to base, 2 = base to kap, 3 = sen to pcb, 4 = pcb to base, 5 = pcb to kap, 6 = Shield Bond, 7 = Guard Bond, 8 = Backside X, 9 = Backside Y
        bool isSen = false, isKap = false, isBase = false, isPcb = false;
        double minRtot = 9999999.;
        double maxRtot = -9999999.;
        for(int i = 0; i != (signed)isNegative.size(); i++){
          minRtot = std::min(minRtot, isNegative[i].first);
          maxRtot = std::max(maxRtot, isNegative[i].second);
          if(isNegative[i].first >= 0) continue;
          isBad = true;
          xCorr.push_back(i);
          yCorr.push_back(i);
          howBad.at(i) += constants::weight;
          if(!isSen){
            xBadComp.push_back(0); 
            isSen = true;
          } 
          if(!isKap){
            xBadComp.push_back(1); 
            isKap = true;
          } 
          if(!isBase && (i >= 1)){
            xBadComp.push_back(2); 
            isBase = true;
          } 
          if(!isPcb && (i >= 3)){
            xBadComp.push_back(3); 
            isPcb = true;
          }
          if(isPcb) break;
        }
        if(isBad){
          nBadModules += constants::weight;
          hBad->Fill(iBad, constants::weight);
          for(int iX = 0; iX != (signed)xBadComp.size(); iX++) {hBadComp->Fill(xBadComp[iX], constants::weight); /*cout << constants::whichComp[iX] << ": " << xBadComp[iX] << endl;*/}
          for(int iX = 0; iX != (signed)xCorr.size(); iX++){
            for(int iY = 0; iY != (signed)yCorr.size(); iY++){
              //cout << "(x,y) = (" << xCorr[iX] << "," << yCorr[iY] << ")" << endl;
              corr->Fill(xCorr[iX], yCorr[iY], constants::weight);
            }
          }
        }
      }//for all modules
      iBad++;
      bad_values.push_back(make_pair(make_pair(type_str, "Bad Components"), 
      make_pair(make_pair(make_pair(hBadComp->GetBinContent(1), hBadComp->GetBinContent(2)), 
	                  make_pair(hBadComp->GetBinContent(3), hBadComp->GetBinContent(4))), nBadModules)));
      
      for(int i = 0; i != (signed)constants::whichComp.size(); i++)
        badOverlap.push_back(make_pair(make_pair(type_str, constants::nameMap[constants::whichComp[i]]), howBad[i]));

      vector<TString> binLabels = {
        TString(constants::nameMap["sen_kap_stack_hist"]), 
        TString(constants::nameMap["sen_bas_stack_hist"]), 
        TString(constants::nameMap["bas_kap_stack_hist"]), 
        TString(constants::nameMap["bas_kap_sen_stack_hist"]), 
        TString(constants::nameMap["sen_pcb_stack_hist"]), 
        TString(constants::nameMap["pcb_bas_stack_hist"]), 
        TString(constants::nameMap["pcb_kap_stack_hist"]), 
        TString(constants::nameMap["kap_pcb_hist"]),        
        TString(constants::nameMap["sen_pcb_hist"]),        
        TString(constants::nameMap["sen_pcb_kap_x_hist"]), 
        TString(constants::nameMap["sen_pcb_kap_y_hist"])
        };

      for(std::map<TString,TH2Poly*>::iterator iter = components.begin(); iter != components.end(); ++iter){
        print2DPlots(iter->second, geo, TString(constants::nameMap[iter->first]), type+"/"+geo + "_" + type + "_Width_" + iter->first, constants::width_new);
        iter->second->Write();
        delete iter->second;
      }
      for(std::map<TString,TH2Poly*>::iterator iter = overlap.begin(); iter != overlap.end(); ++iter){
        print2DPlots(iter->second, geo,	TString(constants::nameMap[iter->first]), type+"/"+geo + "_" + type + "_Diff_Width_" + iter->first, constants::width_new);
        iter->second->Write();
        delete iter->second;
      }
      for(std::map<TString,TH1D*>::iterator iter = overlapMin.begin(); iter != overlapMin.end(); ++iter){
        prepHists({overlapMin[iter->first]}, false, false, false, {constants::colors[iter->first]});
        iter->second->Write();
        delete iter->second;
      }
      for(std::map<TString,TH1D*>::iterator iter = overlapMax.begin(); iter != overlapMax.end(); ++iter){
        prepHists({overlapMax[iter->first]}, false, false, false, {constants::colors[iter->first]});
        iter->second->Write();
        delete iter->second;
      }
      //Save and print correlation plot
      setBinLabelsYX(corr, binLabels);
      print2DPlots(corr, geo, "", type+"/"+geo + "_" + type + "_corr");
      corr->Write();
      delete gROOT->FindObject("correlation");
      //Save bad components
      setBinLabels(hBadComp, {"Sensor", "Kapton", "Baseplate", "PCB"});
      hBadComp->Write();
      auto leg_BadComp = prepLegends({hBadComp}, {hBadComp->GetName()}, "P");
      leg_BadComp->SetTextSize(0.03);
      leg_BadComp->SetY1NDC(leg_BadComp->GetY2NDC() - 0.3);
      TCanvas* BadComp = drawCompMatt({hBadComp}, leg_BadComp, -1., nullptr, "hist", true);
      BadComp->Update();
      BadComp->Print(constants::outputDir+"/" + type + "/" + geo + "_" + type + "_BadComponents.pdf");
      delete gROOT->FindObject(geo + "_" + type + "_BadComponents");
    }//Different distribution type

    std::ofstream jout;
    jout.open(constants::outputDir+"/" + geo + "_BadmoduleTolerances.json");
    json jtot = makeJSONBadModuleLatex(bad_values, badOverlap);
    jout << jtot.dump(3);
    jout.close();

    //Save bad components
    hBad->Write();
    auto leg_Bad = prepLegends({hBad}, {hBad->GetName()}, "P");
    leg_Bad->SetTextSize(0.03);
    leg_Bad->SetY1NDC(leg_Bad->GetY2NDC() - 0.3);
    TCanvas* Bad = drawCompMatt({hBad}, leg_Bad, -1., nullptr, "hist", true);
    Bad->Update();
    Bad->Print(constants::outputDir+"/"+geo + "_Bad.pdf");
    delete gROOT->FindObject(geo + "_Bad");
    outFile->Close();
  }// for Geometry
}

std::vector<TH2Poly*> GetHistograms(TFile *f, TString geo, TString type) {
   std::vector<TH2Poly*> hists;

   //Get an iterator to and loop over the list of keys in the file.
   TIter keyIter(f->GetListOfKeys());
   TKey *key;
   while ((key = (TKey*)keyIter())) {
      //Get the objects name.
      std::string hName = key->GetName();
      if(!TString(key->GetClassName()).Contains("TH2Poly")) continue;
      if(!TString(hName).Contains(type) || TString(hName).Contains("correlation") || TString(hName).Contains("_2d") || TString(hName).Contains("_Bad")) continue;

      //Try to cast the object to a TTree.
      //TH2Poly* hist = dynamic_cast<TH2Poly*>(key->ReadObj());
      TH2Poly* hist = (TH2Poly*)f->Get(key->GetName());
      if (hist) hists.push_back(hist);
   }

   return hists;
}

std::vector<TH1D*> GetHistograms1D(TFile *f, TString geo, TString type, TString skip = "") {
   std::vector<TH1D*> hists;

   //Get an iterator to and loop over the list of keys in the file.
   TIter keyIter(f->GetListOfKeys());
   TKey *key;
   while ((key = (TKey*)keyIter())) {
      //Get the objects name.
      std::string hName = key->GetName();
      if(TString(key->GetClassName()).Contains("TH2Poly") || TString(hName).Contains("correlation")) continue;
      if(!TString(hName).Contains(type) || TString(hName).Contains("Peak0") || TString(hName).Contains("BadComponents")) continue;

      //Try to cast the object to a TTree.
      //TH1D* hist = dynamic_cast<TH1D*>(key->ReadObj());
      TH1D* hist = (TH1D*)f->Get(key->GetName());
      if (hist) hists.push_back(hist);
   }

   return hists;
}

void module1DTolerances(){
  lumistr = "";
  SetStyle();
  TDR_EXTRA_LABEL_ = "";
  TDR_EXTRA_LABEL_2 = "";

  for(auto &geo_str : constants::Geometry){
    TString geo = TString(geo_str);
    constants::outputDir = constants::localDir + "/Test" + geo;
    gSystem->mkdir(constants::outputDir, true);

    int nPeaks = 1;
         if(geo == "Five" || geo == "Semi") nPeaks = 3;
    else if(geo == "Half" || geo == "Three") nPeaks = 2;

    map<TString, pair<double, double> > center;
    vector < pair < double, double > > points = GetPoints(geo, GetWidthToA(constants::width_new), constants::width_new);
    center.emplace("new", getPolyCenter(points));

    ExtendPlots(geo);

    TFile *outFile = new TFile(constants::outputDir+"/"+geo+"_1Doverlap.root", "RECREATE");
    for(auto &type_str: constants::Dist){
      TString type = TString(type_str);
      gSystem->mkdir(constants::outputDir+"/"+type, true);
      map<TString, TH2Poly*> overlap;

      TFile *file = TFile::Open(constants::eosDir + "/" + type + "_" + geo + "/" + geo + "_2Doverlap.root");
      file->cd();
      vector<TH2Poly*> AllHists = GetHistograms(file, geo, type);

      //Get an iterator to and loop over the list of keys in the file.
      for (int iH = 0; iH != (signed)AllHists.size(); iH++){
        //Get the objects name.
        TH2Poly* h = (TH2Poly*)AllHists[iH];
        TString hName = TString(h->GetName());

        hName.ReplaceAll(geo + "_" + type,"");
        overlap.insert(pair<TString, TH2Poly*>(hName,(TH2Poly*)h));
      }

      map<TString, TH1D*> overlap_1D, overlap_1D_integrate;
      for(std::map<TString,TH2Poly*>::iterator iter = overlap.begin(); iter != overlap.end(); ++iter){
        double width_buff = 0.;
        if(TString(iter->first).Contains("sen_pcb_kap_y_hist")) width_buff = constants::width_backY;
        vector<TH1*> hist = IntegrateHex(iter->second, geo, type, center["new"], constants::width_new, constants::axis, constants::step, nPeaks, width_buff);
        vector<TH1*> histNorm = {};
        for(auto iH = 0; iH != (signed)hist.size(); iH++){ 
          TH1* h = (TH1 *)hist[iH]->Clone(TString(hist[iH]->GetName()) + "_norm");
          histNorm.push_back(h);
        }
        prepHists(histNorm, true, false, false);
        prepHists(hist, false, false, false);
        vector<TH1*> intHist = getIntegratedHist(histNorm, TString(histNorm[0]->GetName()).Contains("max"), false, false);
        for(auto iP = 1; iP != nPeaks + 1; iP++){
          hist[iP]->SetTitle(";Overhang [mm];Modules");
          intHist[iP]->SetTitle(";Overhang [mm];Probability");
          overlap_1D.insert(pair<TString, TH1D*>(iter->first + "_Peak" + to_string(iP), (TH1D*)hist[iP]));
          overlap_1D_integrate.insert(pair<TString, TH1D*>(iter->first + "_integrate_Peak" + to_string(iP), (TH1D*)intHist[iP]));
        }
      }// for integrate 2d hist

      TFile *file1D = TFile::Open(constants::eosDir + "/" + type + "_" + geo + "/" + geo + "_2Doverlap.root");
      file1D->cd();
      vector<TH1D*> AllHists1D = GetHistograms1D(file1D, geo, type);

      for(auto * hist : AllHists1D){
        TH1* histNorm = (TH1 *)hist->Clone(TString(hist->GetName())+"_norm");
        prepHists({hist}, false, false, false);
        prepHists({histNorm}, true, false, false);
        TH1* intHist = getIntegratedHist(histNorm, TString(histNorm->GetName()).Contains("max"), false, false);
        hist->SetTitle(";Overhang [mm];Modules");
        intHist->SetTitle(";Overhang [mm];Probability");
        overlap_1D.insert(pair<TString, TH1D*>(TString(hist->GetName()) + "_Peak" + to_string(1), (TH1D*)hist));
        overlap_1D_integrate.insert(pair<TString, TH1D*>(TString(hist->GetName()) + "_integrate_Peak" + to_string(1), (TH1D*)intHist));
      }// for integrate 1d hist

      TString name = "";
      for(auto iP = 1; iP != nPeaks + 1; iP++){
        TString pName = "_Peak" + to_string(iP);
        prepHists({overlap_1D["pcb_bas_stack_hist" + pName], overlap_1D["pcb_kap_stack_hist" + pName], overlap_1D["bas_kap_sen_stack_hist" + pName], overlap_1D["bas_kap_stack_hist" + pName]}, false, false, false, 
        	{constants::colors["pcb_bas_stack_hist"], constants::colors["pcb_kap_stack_hist"], constants::colors["bas_kap_sen_stack_hist"], constants::colors["bas_kap_stack_hist"]});
        prepHists({overlap_1D_integrate["pcb_bas_stack_hist_integrate" + pName], overlap_1D_integrate["pcb_kap_stack_hist_integrate" + pName], overlap_1D_integrate["bas_kap_sen_stack_hist_integrate" + pName], overlap_1D_integrate["bas_kap_stack_hist_integrate" + pName]}, false, false, false, 
        	{constants::colors["pcb_bas_stack_hist"], constants::colors["pcb_kap_stack_hist"], constants::colors["bas_kap_sen_stack_hist"], constants::colors["bas_kap_stack_hist"]});

        auto leg_diff = prepLegends({overlap_1D["pcb_bas_stack_hist" + pName], overlap_1D["pcb_kap_stack_hist" + pName], overlap_1D["bas_kap_sen_stack_hist" + pName], overlap_1D["bas_kap_stack_hist" + pName]}, 
                                    {constants::nameMap["pcb_bas_stack_hist"], constants::nameMap["pcb_kap_stack_hist"], constants::nameMap["bas_kap_sen_stack_hist"], constants::nameMap["bas_kap_stack_hist"]}, "L");
        leg_diff->SetTextSize(0.03);
        leg_diff->SetY1NDC(leg_diff->GetY2NDC() - 0.3);
        setLegend(leg_diff, 1, 0.2, 0.7, 0.94, 0.87);
        TCanvas* diff = drawCompMatt({overlap_1D["pcb_bas_stack_hist" + pName], overlap_1D["pcb_kap_stack_hist" + pName], overlap_1D["bas_kap_sen_stack_hist" + pName], overlap_1D["bas_kap_stack_hist" + pName]}, leg_diff, 0.00001, nullptr, "hist", true, -0.2, 0.4);
        name = geo + "_" + type + "_diff" + pName;
        diff->Update();
        diff->SetTitle(name);
        diff->Print(constants::outputDir+"/"+type+"/"+name+".pdf");
        //integral
        TCanvas* diff_int = drawCompMatt({overlap_1D_integrate["pcb_bas_stack_hist_integrate" + pName], overlap_1D_integrate["pcb_kap_stack_hist_integrate" + pName], overlap_1D_integrate["bas_kap_sen_stack_hist_integrate" + pName], overlap_1D_integrate["bas_kap_stack_hist_integrate" + pName]}, leg_diff, 0.00001, nullptr, "hist", true, -0.2, 0.4);
        name = geo + "_" + type + "_diff_integral" + pName;
        diff_int->Update();
        diff_int->SetTitle(name);
        diff_int->Print(constants::outputDir+"/"+type+"/"+name+".pdf");

        prepHists({overlap_1D["sen_bas_stack_hist" + pName], overlap_1D["sen_pcb_stack_hist" + pName], overlap_1D["sen_kap_stack_hist" + pName]}, false, false, false, 
        	{constants::colors["sen_bas_stack_hist"], constants::colors["sen_pcb_stack_hist"], constants::colors["sen_kap_stack_hist"]});
        prepHists({overlap_1D_integrate["sen_bas_stack_hist_integrate" + pName], overlap_1D_integrate["sen_pcb_stack_hist_integrate" + pName], overlap_1D_integrate["sen_kap_stack_hist_integrate" + pName]}, false, false, false, 
        	{constants::colors["sen_bas_stack_hist"], constants::colors["sen_pcb_stack_hist"], constants::colors["sen_kap_stack_hist"]});
        auto leg_sen_diff = prepLegends({overlap_1D["sen_bas_stack_hist" + pName], overlap_1D["sen_pcb_stack_hist" + pName], overlap_1D["sen_kap_stack_hist" + pName]}, 
                                        {constants::nameMap["sen_bas_stack_hist"], constants::nameMap["sen_pcb_stack_hist"], constants::nameMap["sen_kap_stack_hist"]}, "L");
        leg_sen_diff->SetTextSize(0.03);
        leg_sen_diff->SetY1NDC(leg_sen_diff->GetY2NDC() - 0.3);
        setLegend(leg_sen_diff, 1, 0.2, 0.7, 0.94, 0.87);
        TCanvas* sen_diff = drawCompMatt({overlap_1D["sen_bas_stack_hist" + pName], overlap_1D["sen_pcb_stack_hist" + pName], overlap_1D["sen_kap_stack_hist" + pName]}, leg_sen_diff, 0.00001, nullptr, "hist", true, -0.2, 0.4);
        name = geo + "_" + type + "_sen_diff" + pName;
        sen_diff->Update();
        sen_diff->SetTitle(name);
        sen_diff->Print(constants::outputDir+"/"+type+"/"+name+".pdf");
        //integral
        TCanvas* sen_diff_int = drawCompMatt({overlap_1D_integrate["sen_bas_stack_hist_integrate" + pName], overlap_1D_integrate["sen_pcb_stack_hist_integrate" + pName], overlap_1D_integrate["sen_kap_stack_hist_integrate" + pName]}, leg_sen_diff, 0.00001, nullptr, "hist", true, -0.2, 0.4);
        name = geo + "_" + type + "_sen_diff_integral" + pName;
        sen_diff_int->Update();
        sen_diff_int->SetTitle(name);
        sen_diff_int->Print(constants::outputDir+"/"+type+"/"+name+".pdf");

        prepHists({overlap_1D["sen_pcb_hist" + pName], overlap_1D["kap_pcb_hist" + pName], overlap_1D["sen_pcb_kap_x_hist" + pName], overlap_1D["sen_pcb_kap_y_hist" + pName]}, false, false, false, 
        	{constants::colors["sen_pcb_hist"], constants::colors["kap_pcb_hist"], constants::colors["sen_pcb_kap_x_hist"], constants::colors["sen_pcb_kap_y_hist"]});
        prepHists({overlap_1D_integrate["sen_pcb_hist_integrate" + pName], overlap_1D_integrate["kap_pcb_hist_integrate" + pName], overlap_1D_integrate["sen_pcb_kap_x_hist_integrate" + pName], overlap_1D_integrate["sen_pcb_kap_y_hist_integrate" + pName]}, false, false, false, 
        	{constants::colors["sen_pcb_hist"], constants::colors["kap_pcb_hist"], constants::colors["sen_pcb_kap_x_hist"], constants::colors["sen_pcb_kap_y_hist"]});
        auto leg_bond_diff = prepLegends({overlap_1D["sen_pcb_hist" + pName], overlap_1D["kap_pcb_hist" + pName], overlap_1D["sen_pcb_kap_x_hist" + pName], overlap_1D["sen_pcb_kap_y_hist" + pName]},
                                         {constants::nameMap["sen_pcb_hist"], constants::nameMap["kap_pcb_hist"], constants::nameMap["sen_pcb_kap_x_hist"], constants::nameMap["sen_pcb_kap_y_hist"]}, "L");
        leg_bond_diff->SetTextSize(0.03);
        leg_bond_diff->SetY1NDC(leg_bond_diff->GetY2NDC() - 0.3);
        setLegend(leg_bond_diff, 1, 0.2, 0.7, 0.94, 0.87);
        TCanvas* bond_diff = drawCompMatt({overlap_1D["sen_pcb_kap_y_hist" + pName], overlap_1D["sen_pcb_hist" + pName], overlap_1D["kap_pcb_hist" + pName], overlap_1D["sen_pcb_kap_x_hist" + pName]}, leg_bond_diff, 0.00001, nullptr, "hist", true, 0., 2.5);
        name = geo + "_" + type + "_bond_diff" + pName;
        bond_diff->Update();
        bond_diff->SetTitle(name);
        bond_diff->Print(constants::outputDir+"/"+type+"/"+name+".pdf");
        //integral
        TCanvas* bond_diff_int = drawCompMatt({overlap_1D_integrate["sen_pcb_kap_y_hist_integrate" + pName], overlap_1D_integrate["sen_pcb_hist_integrate" + pName], overlap_1D_integrate["kap_pcb_hist_integrate" + pName], overlap_1D_integrate["sen_pcb_kap_x_hist_integrate" + pName]}, leg_bond_diff, 0.00001, nullptr, "hist", true, 0., 2.5);
        name = geo + "_" + type + "_bond_diff_integral" + pName;
        bond_diff_int->Update();
        bond_diff_int->SetTitle(name);
        bond_diff_int->Print(constants::outputDir+"/"+type+"/"+name+".pdf");
      }// for plot 1D hists

      outFile->cd();
      for(std::map<TString,TH1D*>::iterator iter = overlap_1D.begin(); iter != overlap_1D.end(); ++iter){
        iter->second->Write();
        delete iter->second;
      }
      for(std::map<TString,TH1D*>::iterator iter = overlap_1D_integrate.begin(); iter != overlap_1D_integrate.end(); ++iter){
        iter->second->Write();
        //delete iter->second;
      }
      file->Close();
    }//Different distribution type
    outFile->Close();
  }// for Geometry
}

TString groupString(TString name, TString remove, TString splitBy = "_", bool flip = false){
  auto vec = splitString(name, splitBy);
  TString rlt = "";
  for (unsigned i=0; i<vec.size(); ++i){
    if(vec.at(i).Contains(remove)){
      if(flip) return vec.at(i);
      else continue;
    }
    if (i==0){
      rlt = vec.at(i);
    }else{
      rlt = rlt + splitBy + vec.at(i);
    }
  }
  return rlt;
}

TH1D* rebinAxis(TH1D* h, bool flip = false){
  TString name = !TString(h->GetName()).Contains("_integrate")  ? ";Overhang [#mum];Modules" : ";Overhang [#mum];Probability";
  double xMin = flip ?-400. :-200.;
  double xMax = flip ? 200. : 400.;
  TH1D* hRebin = new TH1D(TString(h->GetName()) + "_rebin", name, 300, xMin, xMax);
  
  for(int ibin = 0; ibin != h->GetNbinsX() + 1; ibin++){
    double x = h->GetXaxis()->GetBinCenter(ibin);
    double y = h->GetBinContent(ibin);
    x *= 1000;
    if(flip) x *= -1.;
    hRebin->SetBinContent(hRebin->FindBin(x), y);
  }

  return hRebin;
}

void moduleFitTolerances(){
  lumistr = "";
  SetStyle();
  TDR_EXTRA_LABEL_ = "";
  TDR_EXTRA_LABEL_2 = "";

  for(auto &geo_str : constants::Geometry){
    //vector( pair( pair(       ,       ), pair( pair( pair(       ,        ), pair(       ,       )), pair( pair(      ,       ), ))));
    vector< pair< pair< string, string>, pair< string, double> > > prob_values = {};
    vector< pair< pair< string, string>, pair< pair< double, double >, double > > > worst_values = {};
    vector< pair< pair< string, string>, pair< double, double > > > fit_values = {};
    TString geo = TString(geo_str);
    constants::outputDir = constants::localDir + "/Test" + geo;

    int nPeaks = 1;
         if(geo == "Five" || geo == "Semi") nPeaks = 3;
    else if(geo == "Half" || geo == "Three") nPeaks = 2;

    TFile *file = TFile::Open(constants::outputDir + "/" + geo + "_1Doverlap.root");
    map<TString, TH1D*> overlap_1D_integrate_minus = {};
    map<TString, TH1D*> overlap_1D_minus = {};
    vector<TString> overlap_1D_integrate_minus_split = {};
    vector<TString> overlap_1D_integrate_minus_kind = {};
    for(auto &type_str: constants::Dist){
      TString type = TString(type_str);
      gSystem->mkdir(constants::outputDir+"/"+type, true);

      ExtendWidths(type, geo);

      file->cd();
      vector<TH1D*> AllHists = GetHistograms1D(file, geo, type);

      //Get an iterator to and loop over the list of keys in the file.
      map<TString, TH1D*> overlap_1D, overlap_1D_integrate;
      for (auto& h : AllHists){
        //Get the objects name.
        TString hName = TString(h->GetName());
        TString swi = hName;
        hName.ReplaceAll(geo + "_" + type,"");
        hName.ReplaceAll("_norm", "");
        TString prefix = "max";
        if(hName.Contains("Peak")) continue;
        if(hName.Contains("min")) prefix = "min";
        TString group = groupString(type, "Kaptonplus");
        TString groupPCB = groupString(type, "PCBplus");
        TString stackType = "";
        for(auto iS = 0; iS != (signed)constants::whichPlot.size(); iS++) if (hName.Contains(constants::whichPlot[iS])) stackType = constants::whichPlot[iS];
        if(stackType == "") continue;

        if(!hName.Contains("_integrate")) overlap_1D.insert(pair<TString, TH1D*>(hName,(TH1D*)h));
        else                              overlap_1D_integrate.insert(pair<TString, TH1D*>(hName,(TH1D*)h));
        //BasToKap
        if(hName.Contains(stackType) && type.Contains("Kaptonplus")){
          TString kaptonType = TString(prefix+"_" + constants::compMap[stackType]+ "_" + type + "_" + hName);
          TH1D* hRebin = rebinAxis(h, stackType.Contains("pcb_bas_stack_hist") || stackType.Contains("sen_pcb_stack_hist"));
          if(swi.Contains("_integrate")) overlap_1D_integrate_minus.insert(pair<TString, TH1D*>(kaptonType, (TH1D*)hRebin));
          else overlap_1D_minus.insert(pair<TString, TH1D*>(kaptonType, (TH1D*)hRebin));
          if(type.Contains("Kaptonplus150")){
            overlap_1D_integrate_minus_split.push_back(prefix+"_" + constants::compMap[stackType]+ "_" + group);
            overlap_1D_integrate_minus_kind.push_back(constants::compMap[stackType]);
          }
          if(type.Contains("PCBplus100")) overlap_1D_integrate_minus_split.push_back(prefix+"_" + constants::compMap[stackType]+ "_" + groupPCB);
        }
      }

      int sides = 1;
      vector<double> pcb_nom, kapton_nom, baseplate_nom, sensor_nom, pcb_bond_nom, kapton_bond_nom, sensor_bond_nom, pcb_backside_nom, sensor_backside_nom, kapton_backside_nom, pcb_backside_x_nom, sensor_backside_x_nom, kapton_backside_x_nom;
           if(geo == "Half" || geo == "Three") sides = 2;                                                               
      else if(geo == "Five" || geo == "Semi")  sides = 3;                                                               
      for(auto iS = 0; iS != sides; iS++){
        string peak = "";
             if(iS == 0) peak = "_Peak1";
        else if(iS == 1) peak = "_Peak2";
        else if(iS == 2) peak = "_Peak3";

        double pcb_w_new = ScaleSide(geo, iS, constants::pcb_w);
        double kapton_w_new = ScaleSide(geo, iS, constants::kapton_w);
        double baseplate_w_new = ScaleSide(geo, iS, constants::baseplate_w);
        double sensor_w_new = ScaleSide(geo, iS, constants::sensor_w);
        pcb_nom.push_back(pcb_w_new);
        kapton_nom.push_back(kapton_w_new);
        baseplate_nom.push_back(baseplate_w_new);
        sensor_nom.push_back(sensor_w_new);
        kapton_bond_nom.push_back(kapton_w_new - (constants::gold_size - 0.650)*2);
        sensor_bond_nom.push_back(sensor_w_new - (constants::gold_size - 0.730)*2);
        pcb_bond_nom.push_back(pcb_w_new - constants::gold_size*2);
        // Y tolerance
        pcb_backside_nom.push_back(getBacksideHeight(15.590, 0.540));
        // X tolerance
        // Ac = a - (2*6.5024)
        pcb_backside_x_nom.push_back(GetWidthToA(pcb_nom.at(iS)) - (2*6.2648));
        kapton_backside_x_nom.push_back(GetWidthToA(kapton_nom.at(iS)) - (2*7.2393));

        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["sen_pcb_hist"]), 	make_pair((sensor_bond_nom[iS] - pcb_bond_nom[iS])/2 - constants::gold_min, 0.0))); 
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["kap_pcb_hist"]), 	make_pair((kapton_bond_nom[iS] - pcb_bond_nom[iS])/2 - constants::gold_min, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["sen_pcb_kap_y_hist"]),make_pair(3.302 - pcb_backside_nom[iS] - constants::backside_min, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["sen_pcb_kap_x_hist"]),make_pair((pcb_backside_x_nom[iS] - kapton_backside_x_nom[iS])/2 - constants::backside_min, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["pcb_bas_stack_hist"]),make_pair((baseplate_nom[iS] - pcb_nom[iS])/2, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["sen_bas_stack_hist"]),make_pair((baseplate_nom[iS] - sensor_nom[iS])/2, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["pcb_kap_stack_hist"]),make_pair((kapton_nom[iS] - pcb_nom[iS])/2, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["bas_kap_sen_stack_hist"]),make_pair((kapton_nom[iS] - baseplate_nom[iS])/2 + 0.185 - constants::base_kap_min, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["bas_kap_stack_hist"]),make_pair((kapton_nom[iS] - baseplate_nom[iS])/2, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["sen_kap_stack_hist"]),make_pair((kapton_nom[iS] - sensor_nom[iS])/2, 0.0)));
        fit_values.push_back(make_pair(make_pair(type_str + peak + "_Nominal", constants::nameMap["sen_pcb_stack_hist"]),make_pair((pcb_nom[iS] - sensor_nom[iS])/2, 0.0)));
      }// for nominal fit values

      for(std::map<TString,TH1D*>::iterator iter = overlap_1D.begin(); iter != overlap_1D.end(); ++iter){
        if(TString(iter->first).Contains("_Peak0")) continue;
        if(TString(iter->first).Contains("_max")) continue;
        if(TString(iter->first).Contains("_min")) continue;

        TString name_buff = iter->first;
        name_buff.ReplaceAll("_Peak1", "");
        string name = constants::nameMap[name_buff];
        string peak = "_Peak1";

        //Get Fit
        iter->second->Fit("gausn", "Q");
        TF1* avg_param = (TF1*)iter->second->GetFunction("gausn");
        if(name_buff.Contains("bas_kap")) cout << name << " " << iter->second->GetName() << ": " << avg_param->GetParameter(1)*1000 << " +/- " << avg_param->GetParameter(2)*1000 << endl;
        if(!isnan(avg_param->GetParameter(1))) fit_values.push_back(make_pair(make_pair(type_str + peak, name), make_pair(avg_param->GetParameter(1), avg_param->GetParameter(2))));
        else fit_values.push_back(make_pair(make_pair(type_str + peak, name), make_pair(0., 0.)));
      }//for actual fit values

      for(std::map<TString,TH1D*>::iterator iter = overlap_1D_integrate.begin(); iter != overlap_1D_integrate.end(); ++iter){
        if(TString(iter->first).Contains("_Peak0")) continue;

        vector<double> max_tol = findHighXbin(iter->second);
        map<string, double> prob = findProbabilities(iter->second);
        TString name_buff = iter->first;
        string prefix = "_max";
        if(name_buff.Contains("Peak1_integrate")) prefix = "_Peak1";
        if(name_buff.Contains("min_integrate")) prefix = "_min";
        name_buff.ReplaceAll(prefix + "_integrate", "");
        string name = constants::nameMap[name_buff];
        string peak = "";
             if(iter->first.Contains("Peak1")) peak = "_Peak1";
        else if(iter->first.Contains("Peak2")) peak = "_Peak2";
        else if(iter->first.Contains("Peak3")) peak = "_Peak3";

        worst_values.push_back(make_pair(make_pair(type_str + prefix, name), make_pair(make_pair(max_tol[0]/1000, max_tol[1]/1000), max_tol[2])));
        for(std::map<string,double>::iterator iter = prob.begin(); iter != prob.end(); ++iter)
          prob_values.push_back(make_pair(make_pair(type_str + prefix, name), make_pair(iter->first, iter->second)));
      }// for worst possible value
    }//Different distribution type

    for(auto iP = 1; iP != nPeaks + 1; iP++){
      for(auto iK = 0; iK != (signed)overlap_1D_integrate_minus_split.size(); iK++){
        TString KaptonSplit = overlap_1D_integrate_minus_split[iK];
        TString grp = "Kaptonplus";
        if(constants::debug) cout << KaptonSplit << endl;
        TString pName = "_Peak" + to_string(iP);
        vector<TH1*> plots;
        auto leg = prepLegends({}, {}, "P");
        TString groupName = "";
        if(KaptonSplit.Contains("Kaptonplus")) grp = "PCBplus";
          for(std::map<TString,TH1D*>::iterator iter = overlap_1D_integrate_minus.begin(); iter != overlap_1D_integrate_minus.end(); ++iter){
            groupName = groupString(iter->first, grp);
            if(!TString(groupName).Contains(KaptonSplit)) continue;
            if(constants::debug) cout << groupName << " " << KaptonSplit << endl;
            if(constants::debug) cout << iter->first << " " << iter->second->GetName() << endl;
            iter->second->SetLineWidth(3);
            addLegendEntry(leg, iter->second, translateString(groupString(iter->first, grp, "_", true), constants::plotMap, "_", ", "), "L");
            plots.push_back(iter->second);
          }
        leg->SetTextSize(0.03);
        leg->SetY1NDC(leg->GetY2NDC() - 0.3);
        prepHists(plots, false, false, false, {kAzure+6, kSpring-9, 797, kOrange-3, kGreen+3});
        //integral
        setLegend(leg, 1, 0.2, 0.7, 0.94, 0.87);
        TString label = "";
             if(KaptonSplit.Contains("Kaptonplus")) label = "Kaptonplus";
        else if(KaptonSplit.Contains("PCBplus")) label = "PCBplus";
        TString addString = groupString(KaptonSplit, label);
        double xMin = -200.;
        double xMax = 400.;
        if(overlap_1D_integrate_minus_kind[iK].Contains("PCBToBas") || overlap_1D_integrate_minus_kind[iK].Contains("SenToPCB")){
          xMin = -400.;
          xMax = 200.;
        }
        addString.ReplaceAll("Peak1_", "");
        addString.ReplaceAll("min_", "");
        addString.ReplaceAll("_senTokap185", "");
        addString.ReplaceAll("max_", "");
        std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(translateString(addString, constants::plotMap, "_", ", ", true), 0.22, 0.66); };
        TCanvas* diff = drawCompMatt(plots, leg, 0.00001, &plotextra, "hist", true, xMin, xMax, overlap_1D_integrate_minus_kind[iK].Contains("BasToKap"));
        TString name = geo + "_" + KaptonSplit + "_integral_diff_kaptonAll" + pName;
        diff->Update();
        diff->SetTitle(name);
        diff->Print(constants::outputDir+"/"+name+".pdf");
        //norm
        plots = {};
        leg = prepLegends({}, {}, "P");
          for(std::map<TString,TH1D*>::iterator iter = overlap_1D_minus.begin(); iter != overlap_1D_minus.end(); ++iter){
            groupName = groupString(iter->first, grp);
            if(!TString(groupName).Contains(KaptonSplit)) continue;
            if(constants::debug) cout << iter->first << " " << iter->second->GetName() << endl;
            iter->second->SetLineWidth(3);
            addLegendEntry(leg, iter->second, translateString(groupString(iter->first, grp, "_", true), constants::plotMap, "_", ", "), "L");
            plots.push_back(iter->second);
          }
        leg->SetTextSize(0.03);
        leg->SetY1NDC(leg->GetY2NDC() - 0.3);
        prepHists(plots, false, false, false, {kAzure+6, kSpring-9, 797, kOrange-3, kGreen+3});
        //integral
        setLegend(leg, 1, 0.2, 0.7, 0.94, 0.87);
        diff = drawCompMatt(plots, leg, 0.1, &plotextra, "hist", true, xMin, xMax, overlap_1D_integrate_minus_kind[iK].Contains("BasToKap"));
        name = geo + "_" + KaptonSplit + "_diff_kaptonAll" + pName;
        diff->Update();
        diff->SetTitle(name);
        diff->Print(constants::outputDir+"/"+name+".pdf");
      }// for all kapton widths
    }// for all kapton peaks 
    file->Close();

    std::ofstream jout;
    jout.open(constants::outputDir+"/" + geo + "_moduleTolerances.json");
    json jtot = makeJSONModuleLatex(fit_values, worst_values, prob_values);
    jout << jtot.dump(3);
    jout.close();
  }// for Geometry
}

float getMinimum(TH1F* p_Hist){
  float min = p_Hist->GetMinimum(0);
  float temp_min = 99999.;
  return min;
}

float histYield(TH1F* hist){
  return hist->Integral(0, hist->GetNbinsX() + 1);
}

void setTitleOffset(TCanvas *c, double xOff = .950, double yOff = 1.400){
  TList * list = c->GetListOfPrimitives();
  for(auto iP = 0; iP < list->GetSize(); ++iP){
    TH1 * h = dynamic_cast<TH1*>(list->At(iP));
    if(h == 0) continue;
   h->GetXaxis()->SetTitleOffset(xOff);
    h->GetYaxis()->SetTitleOffset(yOff);
  }
}

void print2DPlots(TH2Poly *hc, TString geometry, TString BinLatex, TString name, double width){
  TString hName = TString(hc->GetName()) + "_c";
  TCanvas* canvas;
  delete gROOT->FindObject(hName);

  canvas = new TCanvas(hName, "2Dhist", 500, 500);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetRightMargin(0.19);
  canvas->SetTopMargin(0.08);
  canvas->SetLeftMargin(0.14);
  canvas->SetBottomMargin(0.14);
  int NCont = 255;
  double stops[5] = {0.00, 0.34, 0.61, 0.84, 1.00};
  double red[5]= {0.50, 0.50, 1.00, 1.00, 1.00};
  double green[5] = {0.50, 1.00, 1.00, 0.60, 0.50};
  double blue[5] = {1.00, 1.00, 0.50, 0.40, 0.50};
  TColor::CreateGradientColorTable(5, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

  canvas->cd();
  hc->Draw("colz");

  gPad->Update();
  TGaxis::SetMaxDigits(2);
  TPaletteAxis* palette = (TPaletteAxis*)hc->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(1.-0.18);
  palette->SetY1NDC(0.14);
  palette->SetX2NDC(1.-0.13);
  palette->SetY2NDC(1.-0.08);
  palette->SetLabelFont(42);
  palette->SetLabelSize(0.035);
  canvas->Modified();
  if(BinLatex != ""){
    TLatex *tl = new TLatex();
    tl->SetTextSize(0.03);
    tl->DrawLatexNDC(0.17, 0.87, BinLatex);
  }

  AddLineNomHex(width, geometry);

  setTitleOffset(canvas, .950, .950);
  canvas->Update();
  canvas->SaveAs(constants::outputDir + "/" + name + ".pdf");
  delete gROOT->FindObject(hName);
}

void print2DPlots(TH2D *hc, TString geometry, TString BinLatex, TString name){
  TString hName = TString(hc->GetName()) + "_c";
  TCanvas* canvas;
  delete gROOT->FindObject(hName);

  canvas = new TCanvas(hName, "2Dhist", 500, 500);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetRightMargin(0.19);
  canvas->SetTopMargin(0.08);
  canvas->SetLeftMargin(0.14);
  canvas->SetBottomMargin(0.14);
  int NCont = 255;
  double stops[5] = {0.00, 0.34, 0.61, 0.84, 1.00};
  double red[5]= {0.50, 0.50, 1.00, 1.00, 1.00};
  double green[5] = {0.50, 1.00, 1.00, 0.60, 0.50};
  double blue[5] = {1.00, 1.00, 0.50, 0.40, 0.50};
  TColor::CreateGradientColorTable(5, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

  canvas->cd();
  hc->Draw("colz");

  gPad->Update();
  TGaxis::SetMaxDigits(4);
  TPaletteAxis* palette = (TPaletteAxis*)hc->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(1.-0.18);
  palette->SetY1NDC(0.14);
  palette->SetX2NDC(1.-0.13);
  palette->SetY2NDC(1.-0.08);
  palette->SetLabelFont(42);
  palette->SetLabelSize(0.030);
  canvas->Modified();
  if(BinLatex != ""){
    TLatex *tl = new TLatex();
    tl->SetTextSize(0.03);
    tl->DrawLatexNDC(0.17, 0.87, BinLatex);
  }

  setTitleOffset(canvas, .950, .950);
  canvas->Update();
  canvas->SaveAs(constants::outputDir + "/" + name + ".pdf");
  delete gROOT->FindObject(hName);
}
