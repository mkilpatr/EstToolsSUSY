/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: mkilpatr
 */

#include <fstream>

#include "LowMET_Parameters.hh"

#include "../EstMethods/LLBEstimator.hh"

using namespace EstTools;

void BkgPred_LowMET_LL(){
  auto start = chrono::steady_clock::now();

  vector<std::string> bkgnames  = {"ttbarplusw_pred"};
  vector<TString> bkglabels = {"t#bar{t}/W"};
  vector<TString> datalabel = {"Data"};

  auto convert = [&bkgnames](const ToyCombination &c, vector<TH1*> &hists, vector<TGraphAsymmErrors*> &graphs, TString region = "", int start = 0, int manualBins = 0){
    for(const auto &s : bkgnames){
      hists.push_back(convertToHist(c.getPrediction(s), s, ";" + region + " #Deltam Validation Region;Events", nullptr, start, manualBins));
      graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(s), s+"_gr", ";" + region + " #Deltam Validation Region;Events"));
    }
    graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(), "pred_total_gr", ";" + region + " #Deltam Validation Region;Events"));
  };

  // traditional method for LLB
  EstTools::ADD_LEP_TO_MET = false;
  auto altllbcfg = lepConfig();
  LLBEstimator l(altllbcfg);
  l.pred();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));

  ToyCombination lc;
  lc.addBackground("ttbarplusw_pred",   &l.yields.at("singlelep"), &l.yields.at("_TF"));
  lc.combine();

  vector<TH1*> altpred_low;
  vector<TGraphAsymmErrors*> altgraphs_low;
  convert(lc, altpred_low, altgraphs_low, "Low", 0, 19);

  vector<TH1*> altpred;
  vector<TGraphAsymmErrors*> altgraphs;
  convert(lc, altpred, altgraphs);

  vector<TH1*> altpred_high;
  vector<TGraphAsymmErrors*> altgraphs_high;
  convert(lc, altpred_high, altgraphs_high, "High", 19, 24);

  vector<TH1*> mc_low;
  mc_low.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";Low #Deltam Validation Region;Events", nullptr, 0, 19));
  vector<TH1*> lepcr_low;
  lepcr_low.push_back(convertToHist(l.yields.at("ttbarplusw"),"ttbarplusw_mc_cr",";Low #Deltam Validation Region;Events", nullptr, 0, 19));
  lepcr_low.push_back(convertToHist(l.yields.at("singlelep"),"data_cr",";Low #Deltam Validation Region;Events", nullptr, 0, 19));

  vector<TH1*> mc;
  mc.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";#Deltam Validation Region;Events", nullptr));
  vector<TH1*> lepcr;
  lepcr.push_back(convertToHist(l.yields.at("ttbarplusw"),"ttbarplusw_mc_cr",";#Deltam Validation Region;Events", nullptr));
  lepcr.push_back(convertToHist(l.yields.at("singlelep"),"data_cr",";#Deltam Validation Region;Events", nullptr));

  vector<TH1*> mc_high;
  mc_high.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";High #Deltam Validation Region;Events", nullptr, 19, 24));
  vector<TH1*> lepcr_high;
  lepcr_high.push_back(convertToHist(l.yields.at("ttbarplusw"),"ttbarplusw_mc_cr",";High #Deltam Validation Region;Events", nullptr, 19, 24));
  lepcr_high.push_back(convertToHist(l.yields.at("singlelep"),"data_cr",";High #Deltam Validation Region;Events", nullptr, 19, 24));

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();

  auto hdata     = convertToHist(s.yields.at("data-sr"),"data",";#Deltam Validation Region;Events", nullptr);
  auto hdata_low = convertToHist(s.yields.at("data-sr"),"data",";Low #Deltam Validation Region;Events", nullptr, 0, 19);
  auto hdata_high = convertToHist(s.yields.at("data-sr"),"data",";High #Deltam Validation Region;Events", nullptr, 19, 24);

  auto plot = [&](const vector<TH1*> &vpred, const vector<TGraphAsymmErrors*> &vgraphs, const vector<TH1*> &vraw, vector<TH1*> &vcr,TString outputBase, TString region = "") {
    // plot pred and data
    prepHists(vpred, false, false, true);
    if(region == "Low") prepHists({hdata_low}, false, false, false, {kBlack});
    else if(region == "High") prepHists({hdata_high}, false, false, false, {kBlack});
    else                      prepHists({hdata}, false, false, false, {kBlack});

    // plot raw MC - w/ SF
    TH1 *hmctotal = nullptr;
    for(auto &hmc : vraw){
      if (!hmctotal) hmctotal = (TH1*) hmc->Clone();
      else hmctotal->Add(hmc);
    }

    vcr.push_back(hmctotal);
    prepHists(vcr, false, false, false, {kRed, kMagenta, kOrange});

    TH1* hPredRawMC = (TH1*)vpred[0]->Clone("hPredRawMC");
    hPredRawMC->Divide(hmctotal);
    hPredRawMC->SetLineWidth(2);
    prepHists({hPredRawMC}, false, false, false, {kOrange});

    auto leg = prepLegends(vpred, bkglabels, "F");
    appendLegends(leg, {hdata_low}, datalabel, "LP");
    appendLegends(leg, {hPredRawMC}, {"ttbar MC"}, "L");
    leg->SetTextSize(0.03);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    TCanvas* c = nullptr;
    if(region == "Low")       c = drawStackAndRatio(vpred, hdata_low, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, 0, -1, vcr, nullptr, {hPredRawMC});
    else if(region == "High") c = drawStackAndRatio(vpred, hdata_high, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, 0, -1, vcr, nullptr, {hPredRawMC});
    else                      c = drawStackAndRatio(vpred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, 0, -1, vcr, nullptr, {hPredRawMC});
    c->SetTitle(outputBase);
    c->SetCanvasSize(800, 600);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");
    c->Print(s.config.outputdir+"/" + outputBase +"_canvas.root");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    for (auto *h : vpred) h->Write();
    for (auto *g : vgraphs) g->Write();
    for (auto *h : vraw)   h->Write();
    hPredRawMC->Write();
    if(region == "Low") hdata_low->Write();
    else if(region == "High") hdata_high->Write();
    else hdata->Write();
    output->Close();
  };

  plot(altpred, altgraphs, mc, lepcr, "std_pred_trad_Run2");
  plot(altpred_low, altgraphs_low, mc_low, lepcr_low, "std_pred_trad_LM_Run2", "Low");
  plot(altpred_high, altgraphs_high, mc_high, lepcr_high, "std_pred_trad_HM_Run2", "High");


  cout << "\n\n Traditional \n";
  for (const auto &b : lc.bkgs){
    s.printVec(lc.getPrediction(b.first),b.first);
  }
  s.printVec(lc.getPrediction(),"total_bkg");
  cout << "\n Summary Traditional \n";
  s.printSummary({l.yields.at("_pred"), l.yields.at("ttZ-sr"), l.yields.at("diboson-sr")}, s.yields.at("data-sr"));


  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double> (diff).count() << " s" << endl;

}
