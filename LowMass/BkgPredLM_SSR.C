/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>

#include "LMParameters_SSR.hh"

#include "../EstMethods/LLBEstimator.hh"
#include "../EstMethods/ZnunuEstimator.hh"
#include "../EstMethods/QCDEstimator.hh"

using namespace EstTools;

void BkgPredLM_SSR(){

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();
  s.printYields();

  auto hdata = convertToHist(s.yields.at("data-sr"),"data",";Search Region;Events");
  vector<TH1*> mc;
  for (const auto &sig : s.yields){
    if (sig.first != "data-sr")
      mc.push_back(convertToHist(sig.second, sig.first, ";Search Region;Events"));
  }

  auto phocfg = phoConfig();
  ZnunuEstimator z(phocfg);
  z.zllcr_cfg = zllConfig();
  z.zll_normMap = normMap;
  z.phocr_normMap = phoNormMap;
  z.pred();
  z.printYields();

  EstTools::ADD_LEP_TO_MET = true;
  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.pred();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("rare-sr"));

  auto qcdcfg = qcdConfig();
  QCDEstimator q(qcdcfg);
//  q.runBootstrapping = false;
  q.pred();
  q.printYields();

  auto convert = [](const ToyCombination &c, vector<TH1*> &hists, vector<TGraphAsymmErrors*> &graphs){
    for(const auto &s : c.bkgs){
      hists.push_back(convertToHist(c.getPrediction(s.first), s.first, ";Search Region;Events"));
      graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(s.first), s.first+"_gr", ";Search Region;Events"));
    }
    graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(), "pred_total_gr", ";Search Region;Events"));
  };

  ToyCombination tc;
  tc.addBackground("znunu_pred",        &z.yields.at("singlepho"), &z.yields.at("_TF"));
  tc.addBackground("ttbarplusw_pred",   &l.yields.at("singlelep"), &l.yields.at("_TF"));
  tc.addBackground("qcd_pred",          &q.yields.at("_DATA"), &q.yields.at("_TF"));
  tc.addBackground("rare_pred",         nullptr, nullptr, &l.yields.at("rare-sr"));
  tc.combine();

  vector<TH1*> pred;
  vector<TGraphAsymmErrors*> predGraphs;
  convert(tc, pred, predGraphs);

  // traditional method for LLB
  EstTools::ADD_LEP_TO_MET = false;
  auto altllbcfg = lepConfig();
  LLBEstimator alt(altllbcfg);
  alt.pred();
  alt.printYields();
  Quantity::removeNegatives(alt.yields.at("rare-sr"));

  ToyCombination lc;
  lc.addBackground("znunu_pred",        &z.yields.at("singlepho"), &z.yields.at("_TF"));
  lc.addBackground("ttbarplusw_pred",   &alt.yields.at("singlelep"), &alt.yields.at("_TF"));
  lc.addBackground("qcd_pred",          &q.yields.at("_DATA"), &q.yields.at("_TF"));
  lc.addBackground("rare_pred",         nullptr, nullptr, &alt.yields.at("rare-sr"));
  lc.combine();

  vector<TH1*> altpred;
  vector<TGraphAsymmErrors*> altgraphs;
  convert(lc, altpred, altgraphs);

  mc.push_back(convertToHist(q.yields.at("qcd-withveto-sr"),"qcd_mc",";Search Region;Events"));
//  mc.push_back(convertToHist(l.yields.at("qcd-sr"),"qcd_mc",";Search Region;Events"));
  mc.push_back(convertToHist(l.yields.at("rare-sr"),"rare_mc",";Search Region;Events"));
  mc.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("znunu-sr"),"znunu_mc",";Search Region;Events"));

  vector<TString> bkglabels = {"QCD", "Rare", "t#bar{t}/W", "Z#rightarrow#nu#nu"};
  vector<TString> datalabel = {"Data"};

  auto plot = [&](const vector<TH1*> &vpred, const vector<TGraphAsymmErrors*> &vgraphs,TString outputBase) {
    // plot pred and data
    prepHists(vpred, false, false, true);
    prepHists({hdata}, false, false, false, {kBlack});

    auto leg = prepLegends(vpred, bkglabels, "F");
    appendLegends(leg, {hdata}, datalabel, "LP");
    leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    auto c = drawStackAndRatio(vpred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999);
    c->SetTitle(outputBase);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    for (auto *h : vpred) h->Write();
    for (auto *g : vgraphs) g->Write();
    for (auto *h : mc)   h->Write();
    hdata->Write();
    output->Close();
  };

  plot(pred, predGraphs, "fbd_pred_lepplusmet");
  plot(altpred, altgraphs, "fbd_pred_trad");

  cout << "\n\n Lep+MET \n";
  for (const auto &b : tc.bkgs){
    s.printVec(tc.getPrediction(b.first),b.first);
  }
  s.printVec(tc.getPrediction(),"total_bkg");
  cout << "\n Summary Lep+MET \n";
  s.printSummary({z.yields.at("_pred"), l.yields.at("_pred"), q.yields.at("_pred"), l.yields.at("rare-sr")}, s.yields.at("data-sr"));


  cout << "\n\n Traditional \n";
  for (const auto &b : lc.bkgs){
    s.printVec(lc.getPrediction(b.first),b.first);
  }
  s.printVec(lc.getPrediction(),"total_bkg");
  cout << "\n Summary Traditional \n";
  s.printSummary({z.yields.at("_pred"), alt.yields.at("_pred"), q.yields.at("_pred"), alt.yields.at("rare-sr")}, s.yields.at("data-sr"));
}
