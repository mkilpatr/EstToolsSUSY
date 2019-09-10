/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>

//#include "SRParameters.hh"
#include "SRParameters_2016.hh"

#include "../EstMethods/LLBEstimator.hh"
#include "../utils/Estimator.hh"

using namespace EstTools;

void BkgPredHM_LL(){

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();
  s.printYields();

  //auto hdata = convertToHist(s.yields.at("data-sr"),"data",";Search Region;Events");
  vector<TH1*> mc;
  //for (const auto &sig : s.yields){
  //  if (sig.first != "data-sr")
  //    mc.push_back(convertToHist(sig.second, sig.first, ";Search Region;Events"));
  //}

  EstTools::ADD_LEP_TO_MET = false;
  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.pred2016();
  l.printYields();
cout << "Made it here 3" << endl;
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));

  auto convert = [](const ToyCombination &c, vector<TH1*> &hists, vector<TGraphAsymmErrors*> &graphs){
    for(const auto &s : c.bkgs){
      hists.push_back(convertToHist(c.getPrediction(s.first), s.first, ";Search Region;Events"));
      graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(s.first), s.first+"_gr", ";Search Region;Events"));
    }
    graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(), "pred_total_gr", ";Search Region;Events"));
  };
cout << "Made it here 4" << endl;

  ToyCombination tc;
  tc.addBackground("ttbarplusw_pred",   &l.yields.at("singlelep"), &l.yields.at("_TF"));
  tc.combine();
cout << "Made it here 5" << endl;

  vector<TH1*> pred;
  vector<TGraphAsymmErrors*> predGraphs;
  convert(tc, pred, predGraphs);

  mc.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";Search Region;Events"));

  vector<TString> bkglabels = {"t#bar{t}/W"};
  vector<TString> datalabel = {"Data"};

  auto plot = [&](const vector<TH1*> &vpred, const vector<TGraphAsymmErrors*> &vgraphs,TString outputBase) {
    // plot pred and data
    //prepHists(vpred, false, false, true);
    prepHists(mc, false, false, true);
    //prepHists({hdata}, false, false, false, {kBlack});

    auto leg = prepLegends(vpred, bkglabels, "F");
    //appendLegends(leg, {hdata}, datalabel, "LP");
    leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
    vector<TH1*> sig;
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    auto c = drawStack(vpred, sig, true, leg);
    c->SetTitle(outputBase);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    for (auto *h : vpred) h->Write();
    for (auto *g : vgraphs) g->Write();
    for (auto *h : mc)   h->Write();
    //hdata->Write();
    output->Close();
  };

  plot(pred, predGraphs, "std_pred_trad");

  cout << "\n\n Traditional \n";
  for (const auto &b : tc.bkgs){
    s.printVec(tc.getPrediction(b.first),b.first);
  }
  s.printVec(tc.getPrediction(),"total_bkg");
  cout << "\n Summary Traditional \n";
  s.printSummary({l.yields.at("_pred"), l.yields.at("ttZ-sr"), l.yields.at("diboson-sr")}, s.yields.at("data-sr"));
}
