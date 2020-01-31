/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: mkilpatr
 */

#include <fstream>

#include "LowMET_Parameters.hh"

#include "../EstMethods/LLBEstimator.hh"
#include "../EstMethods/ZnunuEstimator.hh"
#include "../EstMethods/QCDEstimator.hh"

using namespace EstTools;

void BkgPredHM_LowMET(){
  auto start = chrono::steady_clock::now();

  auto phocfg = phoConfig();
  ZnunuEstimator z(phocfg);
  z.zllcr_cfg = zllConfig();
  z.zll_normMap = normMap;
  z.phocr_normMap = phoNormMap;
  z.pred();
  z.printYields();

  auto qcdcfg = qcdConfig();
  QCDEstimator q(qcdcfg);
//  q.runBootstrapping = false;
  q.pred();
  q.printYields();


  vector<std::string> bkgnames  = {"qcd_pred", "diboson_pred", "ttZ_pred", "ttbarplusw_pred", "znunu_pred"};
  vector<TString> bkglabels = {"QCD", "Diboson", "ttZ", "t#bar{t}/W", "Z#rightarrow#nu#nu"};
  vector<TString> datalabel = {"Data"};

  auto convert = [&bkgnames](const ToyCombination &c, vector<TH1*> &hists, vector<TGraphAsymmErrors*> &graphs){
    for(const auto &s : bkgnames){
      hists.push_back(convertToHist(c.getPrediction(s), s, ";Search Region;Events"));
      graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(s), s+"_gr", ";Search Region;Events"));
    }
    graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(), "pred_total_gr", ";Search Region;Events"));
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
  lc.addBackground("znunu_pred",        &z.yields.at("singlepho"), &z.yields.at("_TF"));
  lc.addBackground("ttbarplusw_pred",   &l.yields.at("singlelep"), &l.yields.at("_TF"));
  lc.addBackground("qcd_pred",          &q.yields.at("_DATA"), &q.yields.at("_TF"));
//  lc.addBackground("qcd_pred",          nullptr, nullptr, &l.yields.at("qcd-sr"));
  lc.addBackground("diboson_pred",      nullptr, nullptr, &l.yields.at("diboson-sr"));
  lc.addBackground("ttZ_pred",          nullptr, nullptr, &l.yields.at("ttZ-sr"));
//  lc.addBackground("rare_pred",         nullptr, nullptr, &l.yields.at("rare-sr"));
  lc.combine();

  vector<TH1*> altpred;
  vector<TGraphAsymmErrors*> altgraphs;
  convert(lc, altpred, altgraphs);

  vector<TH1*> mc;
  mc.push_back(convertToHist(q.yields.at("qcd-withveto-sr"),"qcd_mc",";Search Region;Events"));
//  mc.push_back(convertToHist(l.yields.at("qcd-sr"),"qcd_mc",";Search Region;Events"));
  mc.push_back(convertToHist(l.yields.at("ttZ-sr"),"ttZ_mc",";Search Region;Events"));
  mc.push_back(convertToHist(l.yields.at("diboson-sr"),"diboson_mc",";Search Region;Events"));
  //  mc.push_back(convertToHist(l.yields.at("rare-sr"),"rare_mc",";Search Region;Events"));
  mc.push_back(convertToHist(l.yields.at("ttbarplusw-sr"),"ttbarplusw_mc",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("znunu-sr"),"znunu_mc",";Search Region;Events"));

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();

  auto hdata = convertToHist(s.yields.at("data-sr"),"data",";Search Region;Events");

  auto plot = [&](const vector<TH1*> &vpred, const vector<TGraphAsymmErrors*> &vgraphs,TString outputBase) {
    // plot pred and data
    prepHists(vpred, false, false, true);
    prepHists({hdata}, false, false, false, {kBlack});

    // plot raw MC - w/ SF
    TH1 *hmctotal = nullptr;
    for(auto &hmc : mc){
      if (!hmctotal) hmctotal = (TH1*) hmc->Clone();
      else hmctotal->Add(hmc);
    }
    TH1* hDataRawMC = (TH1*)hdata->Clone("hDataRawMC");
    hDataRawMC->Divide(hmctotal);
    hDataRawMC->SetLineWidth(2);
    prepHists({hDataRawMC}, false, false, false, {kOrange});

    // plot raw MC - w/o top/W SF
    TH1 *hmcnosf = nullptr;
    vector<TString> mcnosf = {"znunu-raw-sr","ttbar-raw-sr","wjets-raw-sr","tW-raw-sr","ttW-raw-sr","qcd-raw-sr","ttZ-raw-sr","diboson-raw-sr"};
    for (auto &sname : mcnosf){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf) hmcnosf = (TH1*)hmc->Clone();
      else hmcnosf->Add(hmc);
    }
    TH1* hDataMCNoSF = (TH1*)hdata->Clone("hDataMCNoSF");
    hDataMCNoSF->Divide(hmcnosf);
    hDataMCNoSF->SetLineWidth(2);
    prepHists({hDataMCNoSF}, false, false, false, {kPink-2});

    auto leg = prepLegends(vpred, bkglabels, "F");
    appendLegends(leg, {hdata}, datalabel, "LP");
    appendLegends(leg, {hDataRawMC}, {"Simulation"}, "L");
    appendLegends(leg, {hDataMCNoSF}, {"MC (w/o top/W SF)"}, "L");
    leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    auto c = drawStackAndRatio(vpred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, 0, -1, {}, nullptr, {hDataRawMC, hDataMCNoSF});
    c->SetTitle(outputBase);
    c->SetCanvasSize(800, 600);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");
    c->Print(s.config.outputdir+"/" + outputBase +"_canvas.root");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    for (auto *h : vpred) h->Write();
    for (auto *g : vgraphs) g->Write();
    for (auto *h : mc)   h->Write();
    hDataMCNoSF->Write();
    hdata->Write();
    output->Close();
  };

  plot(altpred, altgraphs, "std_pred_trad");


  cout << "\n\n Traditional \n";
  for (const auto &b : lc.bkgs){
    s.printVec(lc.getPrediction(b.first),b.first);
  }
  s.printVec(lc.getPrediction(),"total_bkg");
  cout << "\n Summary Traditional \n";
  s.printSummary({z.yields.at("_pred"), l.yields.at("_pred"), q.yields.at("_pred"), l.yields.at("ttZ-sr"), l.yields.at("diboson-sr")}, s.yields.at("data-sr"));


  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double> (diff).count() << " s" << endl;

}
