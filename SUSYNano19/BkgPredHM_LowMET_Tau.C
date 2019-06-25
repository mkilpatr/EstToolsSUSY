/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>

#include "SRParameters_Tau_HM.hh"
//#include "LowMET_HM_Parameters.hh"

#include "../EstMethods/LLBEstimator.hh"

using namespace EstTools;

void BkgPredHM_LowMET_LL(){
  auto start = chrono::steady_clock::now();

  vector<std::string> bkgnames  = {"ttbarplusw_pred", "ttbarplusw_pred-iso"};
  //vector<TString> bkglabels = {"Z#rightarrow#nu#nu", "t#bar{t}", "W+jets"};
  vector<TString> bkglabels = {""};
  vector<TString> datalabel = {"Data"};

  auto convert = [&bkgnames](const ToyCombination &c, vector<TH1*> &hists, vector<TGraphAsymmErrors*> &graphs){
    for(const auto &s : bkgnames){
      hists.push_back(convertToHist(c.getPrediction(s), s, ";Search Region;Events"));
      graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(s), s+"_gr", ";Search Region;Events"));
    }
    graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(), "pred_total_gr", ";Search Region;Events"));
  };

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();

  auto hT1tttt = convertToHist(s.yields.at("T1tttt-sr"),"T1tttt_2000_100",";Search Region;Events");
  auto hT2tt_500_325 = convertToHist(s.yields.at("T2tt_500_325-sr"),"T2tt_500_325",";Search Region;Events");
  auto hT2tt_850_100 = convertToHist(s.yields.at("T2tt_850_100-sr"),"T2tt_850_100",";Search Region;Events");
  auto hT1tttt_iso = convertToHist(s.yields.at("T1tttt-sr-iso"),"T1tttt_2000_100-iso",";Search Region;Events");
  auto hT2tt_500_325_iso = convertToHist(s.yields.at("T2tt_500_325-sr-iso"),"T2tt_500_325-iso",";Search Region;Events");
  auto hT2tt_850_100_iso = convertToHist(s.yields.at("T2tt_850_100-sr-iso"),"T2tt_850_100-iso",";Search Region;Events");

  auto plot = [&](TString outputBase) {
    prepHists({hT1tttt, hT2tt_500_325, hT2tt_850_100, hT1tttt_iso, hT2tt_500_325_iso, hT2tt_850_100_iso}, false, false, false, {kRed-7, kMagenta-10, kBlue, kRed-5, kMagenta-8, kAzure-4});

    // plot raw MC - w/o top/W SF
    TH1 *hmcnosf = nullptr;
    vector<TString> mcnosf = {"znunu-raw-sr","ttbar-raw-sr","wjets-raw-sr","tW-raw-sr","ttW-raw-sr","qcd-raw-sr","ttZ-raw-sr","diboson-raw-sr"};
    for (auto &sname : mcnosf){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf) hmcnosf = (TH1*)hmc->Clone();
      else hmcnosf->Add(hmc);
    }
    TH1 *hmcnosf_iso = nullptr;
    vector<TString> mcnosf_iso = {"znunu-raw-sr-iso","ttbar-raw-sr-iso","wjets-raw-sr-iso","tW-raw-sr-iso","ttW-raw-sr-iso","qcd-raw-sr-iso","ttZ-raw-sr-iso","diboson-raw-sr-iso"};
    for (auto &sname : mcnosf_iso){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf_iso) hmcnosf_iso = (TH1*)hmc->Clone();
      else hmcnosf_iso->Add(hmc);
    }

    prepHists({hmcnosf}, false, false, false, {kAzure+6});
    prepHists({hmcnosf_iso}, false, false, false, {kSpring-9});

    TH1* hmcnosf_div = (TH1*)hmcnosf->Clone();
    hmcnosf_div->Divide(hmcnosf_iso);
    hmcnosf_div->SetLineWidth(2);
    prepHists({hmcnosf_div}, false, false, false, {kAzure+6});

    TH1* hT1tttt_div = (TH1*)hT1tttt->Clone();
    hT1tttt_div->Divide(hT1tttt_iso);
    hT1tttt_div->SetLineWidth(2);
    prepHists({hT1tttt_div}, false, false, false, {kRed-7});

    TH1* hT2tt_850_100_div = (TH1*)hT2tt_850_100->Clone();
    hT2tt_850_100_div->Divide(hT2tt_850_100_iso);
    hT2tt_850_100_div->SetLineWidth(2);
    prepHists({hT2tt_850_100_div}, false, false, false, {kBlue});

    TH1* hT2tt_500_325_div = (TH1*)hT2tt_500_325->Clone();
    hT2tt_500_325_div->Divide(hT2tt_500_325_iso);
    hT2tt_500_325_div->SetLineWidth(2);
    prepHists({hT2tt_500_325_div}, false, false, false, {kMagenta-10});

    auto leg = prepLegends({}, bkglabels, "F");
    appendLegends(leg, {hT1tttt}, {"T1tttt(2000, 100) MVA"}, "L");
    appendLegends(leg, {hT1tttt_iso}, {"T1tttt(2000, 100) IsoTrack"}, "L");
    appendLegends(leg, {hT2tt_500_325}, {"T2tt(500, 325) MVA"}, "L");
    appendLegends(leg, {hT2tt_500_325_iso}, {"T2tt(500, 325) IsoTrack"}, "L");
    appendLegends(leg, {hT2tt_850_100}, {"T2tt(850, 100) MVA"}, "L");
    appendLegends(leg, {hT2tt_850_100_iso}, {"T2tt(850, 100) IsoTrack"}, "L");
    appendLegends(leg, {hmcnosf}, {"MC MVA"}, "L");
    appendLegends(leg, {hmcnosf_iso}, {"MC Iso"}, "L");
    leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    auto c = drawCompAndRatio({hT1tttt, hT2tt_500_325, hT2tt_850_100, hT1tttt_iso, hT2tt_500_325_iso, hT2tt_850_100_iso, hmcnosf, hmcnosf_iso}, {hmcnosf_div, hT1tttt_div, hT2tt_500_325_div, hT2tt_850_100_div}, leg, "N_{mva}/N_{iso}", 0.501, 1.499, false, 0.001);
    c->SetTitle(outputBase);
    c->SetCanvasSize(800, 600);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");
    c->Print(s.config.outputdir+"/" + outputBase +"_canvas.root");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    hmcnosf->Write();
    hmcnosf_iso->Write();
    hmcnosf_div->Write();
    hT1tttt->Write();
    hT2tt_500_325->Write();
    hT2tt_850_100->Write();
    hT1tttt_iso->Write();
    hT2tt_500_325_iso->Write();
    hT2tt_850_100_iso->Write();
    hT1tttt_div->Write();
    hT2tt_500_325_div->Write();
    hT2tt_850_100_div->Write();
    output->Close();
  };

  //plot("std_pred_trad_TauValHM");
  plot("std_pred_trad_allHM");


  cout << "\n\n Traditional \n";
  //for (const auto &b : lc.bkgs){
  //  s.printVec(lc.getPrediction(b.first),b.first);
  //}
  //s.printVec(lc.getPrediction(),"total_bkg");
  cout << "\n Summary Traditional \n";
  //s.printSummary({s.yields.at("_pred"), l.yields.at("ttZ-sr"), l.yields.at("diboson-sr")}, s.yields.at("data-sr"));


  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double> (diff).count() << " s" << endl;

}
