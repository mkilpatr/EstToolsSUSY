/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>

#include "LMParameters.hh"

#include "../EstMethods/LLBEstimator.hh"
#include "../EstMethods/ZnunuEstimator.hh"
#include "../EstMethods/QCDEstimator.hh"

using namespace EstTools;

void BkgPredLM(){
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

  auto qcdcfg = qcdConfig();
  QCDEstimator q(qcdcfg);
//  q.runBootstrapping = false;
  q.pred();
  q.printYields();

  vector<TH1*> pred;
  pred.push_back(convertToHist(q.yields.at("_pred"),"qcd_pred",";Search Region;Events"));
//  pred.push_back(convertToHist(l.yields.at("qcd-sr"),"qcd_pred",";Search Region;Events"));
  pred.push_back(convertToHist(l.yields.at("_pred"),"ttbarplusw_pred",";Search Region;Events"));
  pred.push_back(convertToHist(z.yields.at("_pred"),"znunu_pred",";Search Region;Events"));

  // traditional method for LLB
  EstTools::ADD_LEP_TO_MET = false;
  auto altllbcfg = lepConfig();
  LLBEstimator alt(altllbcfg);
  alt.pred();
  alt.printYields();

  vector<TH1*> altpred;
  altpred.push_back(convertToHist(q.yields.at("_pred"),"qcd_pred",";Search Region;Events"));
//  altpred.push_back(convertToHist(alt.yields.at("qcd-sr"),"qcd_pred",";Search Region;Events"));
  altpred.push_back(convertToHist(alt.yields.at("_pred"),"ttbarplusw_pred",";Search Region;Events"));
  altpred.push_back(convertToHist(z.yields.at("_pred"),"znunu_pred",";Search Region;Events"));


  vector<TH1*> mc;
  mc.push_back(convertToHist(q.yields.at("qcd-sr-withveto"),"qcd_mc",";Search Region;Events"));
//  mc.push_back(convertToHist(l.yields.at("qcd-sr"),"qcd_mc",";Search Region;Events"));
  mc.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("znunu-sr"),"znunu_mc",";Search Region;Events"));

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();

  auto hdata = convertToHist(s.yields.at("data-sr"),"data",";Search Region;Events");

  vector<TString> bkglabels = {"QCD", "t#bar{t}/W", "Z#rightarrow#nu#nu"};
  vector<TString> datalabel = {"Data"};

  auto plot = [&](const vector<TH1*> &vpred, TString outputBase) {
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
    for (auto *h : mc)   h->Write();
    hdata->Write();
    output->Close();
  };

  plot(pred, "fbd_pred_lepplusmet");
  plot(altpred, "fbd_pred_trad");

  cout << "\n\n Summary Lep+MET \n";
  s.printSummary({z.yields.at("_pred"), l.yields.at("_pred"), q.yields.at("_pred")}, s.yields.at("data-sr"));

  cout << "\n\n Summary Traditional \n";
  s.printSummary({z.yields.at("_pred"), alt.yields.at("_pred"), q.yields.at("_pred")}, s.yields.at("data-sr"));
}
