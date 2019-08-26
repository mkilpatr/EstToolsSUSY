/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"
//#include "SRParameters_Inc.hh"
//#include "SRParameters_qcd_small.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPred(){

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  l.pred();

  l.printYields();

  std::map<TString,int> digits;
  digits["singlelep"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap"] = -3;
  digits["_TF_SR_extrap"] = -3;

  l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "yields_llb_all_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep", "_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "yields_llb_all_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "yields_llb_all_hm.tex", "hm", digits);
  }

  return l.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPredSeparate(){

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  l.predSeparate();

  l.printYields();

  std::map<TString,int> digits;
  digits["singlelep"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap"] = -3;
  digits["_TF_SR_extrap"] = -3;
  digits["singlelep-2016"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2016"] = -3;
  digits["_TF_SR_extrap-2016"] = -3;
  digits["singlelep-2017RunBtoE"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2017RunBtoE"] = -3;
  digits["_TF_SR_extrap-2017RunBtoE"] = -3;
  digits["singlelep-2017RunF"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2017RunF"] = -3;
  digits["_TF_SR_extrap-2017RunF"] = -3;
  digits["singlelep-2018preHEM"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2018preHEM"] = -3;
  digits["_TF_SR_extrap-2018preHEM"] = -3;
  digits["singlelep-2018postHEM"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2018postHEM"] = -3;
  digits["_TF_SR_extrap-2018postHEM"] = -3;

  l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "yields_llb_all_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep", "_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "yields_llb_all_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "yields_llb_all_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2016", "_TF-2016", "_pred-2016"}, labelMap, "yields_llb_2016_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2016", "_TF-2016", "_TF_CR_to_SR_noextrap-2016", "_TF_SR_extrap-2016", "_pred-2016"}, labelMap, "yields_llb_2016_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2016", "_TF-2016", "_pred-2016"}, labelMap, "yields_llb_2016_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2017RunBtoE", "_TF-2017RunBtoE", "_pred-2017RunBtoE"}, labelMap, "yields_llb_2017RunBtoE_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2017RunBtoE", "_TF-2017RunBtoE", "_TF_CR_to_SR_noextrap-2017RunBtoE", "_TF_SR_extrap-2017RunBtoE", "_pred-2017RunBtoE"}, labelMap, "yields_llb_2017RunBtoE_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2017RunBtoE", "_TF-2017RunBtoE", "_pred-2017RunBtoE"}, labelMap, "yields_llb_2017RunBtoE_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2017RunF", "_TF-2017RunF", "_pred-2017RunF"}, labelMap, "yields_llb_2017RunF_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2017RunF", "_TF-2017RunF", "_TF_CR_to_SR_noextrap-2017RunF", "_TF_SR_extrap-2017RunF", "_pred-2017RunF"}, labelMap, "yields_llb_2017RunF_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2017RunF", "_TF-2017RunF", "_pred-2017RunF"}, labelMap, "yields_llb_2017RunF_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2018preHEM", "_TF-2018preHEM", "_pred-2018preHEM"}, labelMap, "yields_llb_2018preHEM_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2018preHEM", "_TF-2018preHEM", "_TF_CR_to_SR_noextrap-2018preHEM", "_TF_SR_extrap-2018preHEM", "_pred-2018preHEM"}, labelMap, "yields_llb_2018preHEM_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2018preHEM", "_TF-2018preHEM", "_pred-2018preHEM"}, labelMap, "yields_llb_2018preHEM_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2018postHEM", "_TF-2018postHEM", "_pred-2018postHEM"}, labelMap, "yields_llb_2018postHEM_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2018postHEM", "_TF-2018postHEM", "_TF_CR_to_SR_noextrap-2018postHEM", "_TF_SR_extrap-2018postHEM", "_pred-2018postHEM"}, labelMap, "yields_llb_2018postHEM_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2018postHEM", "_TF-2018postHEM", "_pred-2018postHEM"}, labelMap, "yields_llb_2018postHEM_hm.tex", "hm", digits);
  }

  auto hAll = convertToHist(l.yields.at("_TF"),"TF All",";Search Region;Events");
  auto h2016 = convertToHist(l.yields.at("_TF-2016"),"TF 2016",";Search Region;Events");
  auto h2017RunBtoE = convertToHist(l.yields.at("_TF-2017RunBtoE"),"TF 2017RunBtoE",";Search Region;Events");
  auto h2017RunF = convertToHist(l.yields.at("_TF-2017RunF"),"TF 2017RunF",";Search Region;Events");
  auto h2018preHEM = convertToHist(l.yields.at("_TF-2018preHEM"),"TF 2018preHEM",";Search Region;Events");
  auto h2018postHEM = convertToHist(l.yields.at("_TF-2018postHEM"),"TF 2018postHEM",";Search Region;Events");

  prepHists({hAll}, false, false, false, {kBlack});
  prepHists({h2016}, false, false, false, {kRed});
  prepHists({h2017RunBtoE}, false, false, false, {kBlue});
  prepHists({h2017RunF}, false, false, false, {kGreen});
  prepHists({h2018preHEM}, false, false, false, {kAzure});
  prepHists({h2018postHEM}, false, false, false, {kMagenta});

  TH1* h2016_div = (TH1*)h2016->Clone();
  h2016_div->Divide(hAll);
  h2016_div->SetLineWidth(2);
  prepHists({h2016_div}, false, false, false, {kRed});

  TH1* h2017RunBtoE_div = (TH1*)h2017RunBtoE->Clone();
  h2017RunBtoE_div->Divide(hAll);
  h2017RunBtoE_div->SetLineWidth(2);
  prepHists({h2017RunBtoE_div}, false, false, false, {kBlue});

  TH1* h2017RunF_div = (TH1*)h2017RunF->Clone();
  h2017RunF_div->Divide(hAll);
  h2017RunF_div->SetLineWidth(2);
  prepHists({h2017RunF_div}, false, false, false, {kGreen});

  TH1* h2018preHEM_div = (TH1*)h2018preHEM->Clone();
  h2018preHEM_div->Divide(hAll);
  h2018preHEM_div->SetLineWidth(2);
  prepHists({h2018preHEM_div}, false, false, false, {kAzure});

  TH1* h2018postHEM_div = (TH1*)h2018postHEM->Clone();
  h2018postHEM_div->Divide(hAll);
  h2018postHEM_div->SetLineWidth(2);
  prepHists({h2018postHEM_div}, false, false, false, {kMagenta});

  auto leg = prepLegends({}, {""}, "L");
  appendLegends(leg, {hAll}, {"TF All"}, "L");
  appendLegends(leg, {h2016}, {"TF 2016"}, "L");
  appendLegends(leg, {h2017RunBtoE}, {"TF 2017 RunBtoE"}, "L");
  appendLegends(leg, {h2017RunF}, {"TF 2017 RunF"}, "L");
  appendLegends(leg, {h2018preHEM}, {"TF 2018 preHEM"}, "L");
  appendLegends(leg, {h2018postHEM}, {"TF 2018 postHEM"}, "L");
  leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
  leg->SetY1NDC(leg->GetY2NDC() - 0.2);
  auto c = drawStackAndRatio({hAll, h2016, h2017RunBtoE, h2017RunF, h2018preHEM, h2018postHEM}, {h2016_div, h2017RunBtoE_div, h2017RunF_div, h2018preHEM_div, h2018postHEM_div}, leg, true, "TF_{era}/TF_{All}", 0.001, 2.999);
  c->SetTitle("LostLepton_TF_Comparison");
  c->Print(l.config.outputdir+"/LostLepton_TF_Comparison.pdf");
  c->Print(l.config.outputdir+"/LostLepton_TF_Comparison.C");

  TFile *output = new TFile(l.config.outputdir+"/LostLepton_TF_Comparison.root", "RECREATE");
  hAll->Write();
  h2016->Write();
  h2017RunBtoE->Write();
  h2017RunF->Write();
  h2018preHEM->Write();
  h2018postHEM->Write();
  output->Close();

  return l.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotLepCR(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_2017";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar", "wjets", "tW", "ttW"};
  TString data_sample = "singlelep";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.72); };
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotLepCRAllEras(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_allEras";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017RunBtoE", "ttbar-2017RunF", "ttbar-2018preHEM", "ttbar-2018postHEM", "wjets-2016", "wjets-2017RunBtoE", "wjets-2017RunF", "wjets-2018preHEM", "wjets-2018postHEM", 
				"tW-2016", "tW-2017RunBtoE", "tW-2017RunF", "tW-2018preHEM", "tW-2018postHEM", "ttW-2016", "ttW-2017RunBtoE", "ttW-2017RunF", "ttW-2018preHEM", "ttW-2018postHEM"};
  TString data_sample = "singlelep";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.72); };
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void compSLep2(){

  map<TString, vector<Quantity>> sLeps;
  map<TString, vector<Quantity>> pred;

  {
    ICHEPCR = true;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["ichepcr"] = z.yields.at("_SLep");
    pred["ichepcr"] = z.yields.at("_pred");
  }

  {
    ICHEPCR = false;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["newcr"] = z.yields.at("_SLep");
    pred["newcr"] = z.yields.at("_pred");

  }

  map<TString, TString> labelMap = {
      {"ichepcr", "ichep cr"},
      {"newcr", "new cr"}
      //{"addback", "#slash{E}_{T}+#vec{p}_{T}^{lep}"},
      //{"noaddback", "Traditional"}
  };

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : sLeps){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Correction");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "newcr") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);
    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio", 0., 2., true, -1., 2.);
    c->SaveAs(lepConfig().outputdir+"/llb_crs_sf_cmp.pdf");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_sf_cmp.root");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_sf_cmp.C");
  }

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : pred){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Events");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "newcr") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);

    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio", 0., 2., true, 0.01);
    c->SaveAs(lepConfig().outputdir+"/llb_crs_pred_cmp.pdf");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_pred_cmp.root");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_pred_cmp.C");
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void compSLep(){

  map<TString, vector<Quantity>> sLeps;
  map<TString, vector<Quantity>> pred;

  {
    ADD_LEP_TO_MET = true;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["addback"] = z.yields.at("_SLep");
    pred["addback"] = z.yields.at("_pred");
  }

  {
    ADD_LEP_TO_MET = false;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["noaddback"] = z.yields.at("_SLep");
    pred["noaddback"] = z.yields.at("_pred");

  }

  map<TString, TString> labelMap = {
      {"addback", "#slash{E}_{T}+#vec{p}_{T}^{lep}"},
      {"noaddback", "Traditional"}
  };

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : sLeps){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Correction");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "noaddback") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);

    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio");
    c->SaveAs(lepConfig().outputdir+"/llb_sf_cmp.pdf");
  }

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : pred){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Events");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "noaddback") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);

    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio");
    c->SaveAs(lepConfig().outputdir+"/llb_pred_cmp.pdf");
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void srYields(){

  auto config = lepConfig();
  config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("ttbar-sr",       "t#bar{t}",      "ttbar",        lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "wjets",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "ttW",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("qcd-sr",         "QCD",           "qcd",    lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu-sr",       "znunu",         "znunu",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T1tttt-sr",	     "T1tttt(2000, 100)", "T1tttt_2000_100", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("T2tt_850_100-sr","T2tt(850, 100)","T2tt_850_100", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("T2tt_500_325-sr","T2tt(500, 325)","T2tt_500_325", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);


  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["Total BKG"] = -3;
  digits["T1tttt-sr"] = -3;
  digits["T2tt_850_100-sr"] = -3;
  digits["T2tt_500_325-sr"] = -3;

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"});
  z.printYieldsTableLatex({"Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"}, labelMap, "yields_llb_hm_raw.tex", "hm", digits);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lepcrYields(){

  auto config = lepConfig();

  config.samples.clear();
  config.addSample("singlelep",   "Data",          "met",       		"1.0",     datasel + trigLepCR + lepcrsel);
  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        		lepselwgt+"*ISRWeight", datasel + trigLepCR + lepcrsel);
  config.addSample("wjets",       "W+jets",        "wjets",        		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("tW",          "tW",            "tW",              		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("ttW",         "ttW",           "ttW",             		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("qcd",         "QCD",           "qcd",             		lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("ww",          "WW",            "sr/ww",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("wz",          "WZ",            "sr/wz",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("zz",          "ZZ",            "sr/zz",                 lepselwgt, datasel + trigLepCR + lepcrsel);

  BaseEstimator z(config);

  z.calcYields();
  z.printYields();
  z.sumYields({"ttbar", "wjets", "tW", "ttW", "qcd"}, "Total BKG");
  z.sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw-cr");
  z.printYieldsTable({"ttbar", "wjets", "tW", "ttW", "qcd", "Total BKG", "singlelep"});

  vector<TH1*> mc;
  mc.push_back(convertToHist(z.yields.at("ttbar"),"ttbar_cr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("wjets"),"wjets",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("tW"),"tW_cr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("ttW"),"ttWcr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("ttbarplusw-cr"),"ttbarplusw_cr",";Search Region;Events"));
  
  auto hdata = convertToHist(z.yields.at("singlelep"),"data",";Search Region;Events");

  TFile *output = new TFile(z.config.outputdir+"/llcr_yields.root", "RECREATE");
  for (auto *h : mc)   h->Write();
  hdata->Write();
  output->Close();

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusive(){
  auto config = lepConfig();
  //config.sel = "MET_pt > 200";
  TString LLCR = "Pass_dPhiMETLowDM";
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_LMMed = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETMedDM";
  TString LLCR_LM_NoMed = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  config.sel = baseline + " && Stop0l_nJets >= 2";

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017RunBtoE", "ttbar-2017RunF", "ttbar-2018preHEM", "ttbar-2018postHEM", "wjets-2016", "wjets-2017RunBtoE", "wjets-2017RunF", "wjets-2018preHEM", "wjets-2018postHEM", 
				"tW-2016", "tW-2017RunBtoE", "tW-2017RunF", "tW-2018preHEM", "tW-2018postHEM", "ttW-2016", "ttW-2017RunBtoE", "ttW-2017RunF", "ttW-2018preHEM", "ttW-2018postHEM"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_samples_2017RunBtoE = {"ttbar-2017RunBtoE", "wjets-2017RunBtoE", "tW-2017RunBtoE", "ttW-2017RunBtoE"};
  vector<TString> mc_samples_2017RunF = {"ttbar-2017RunF", "wjets-2017RunF", "tW-2017RunF", "ttW-2017RunF"};
  vector<TString> mc_samples_2018preHEM = {"ttbar-2018preHEM", "wjets-2018preHEM", "tW-2018preHEM", "ttW-2018preHEM"};
  vector<TString> mc_samples_2018postHEM = {"ttbar-2018postHEM", "wjets-2018postHEM", "tW-2018postHEM", "ttW-2018postHEM"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017RunBtoE = "singlelep-2017RunBtoE";
  TString data_sample_2017RunF = "singlelep-2017RunF";
  TString data_sample_2018preHEM = "singlelep-2018preHEM";
  TString data_sample_2018postHEM = "singlelep-2018postHEM";

  map<TString, BinInfo> varDict {
	//{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"njets",     BinInfo("Stop0l_nJets", "N_{j}", 11, -0.5, 10.5)},
	//{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
	//{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
	{"dphij1met", BinInfo("Jet_dPhiMET[0]", "#Delta#phi(j_{1},#slash{E}_{T})", 30, 0, 3)},
	{"dphij2met", BinInfo("Jet_dPhiMET[1]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
	{"dphij3met", BinInfo("Jet_dPhiMET[2]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
  };
  vector< pair< TString, TString> > npv_bin = {
	make_pair(" && 1 == 1", 				"_allPU"),
	//make_pair(" && PV_npvsGood >= 0 && PV_npvsGood < 10", 	"_PU0to10"),
	//make_pair(" && PV_npvsGood >= 10 && PV_npvsGood < 20", 	"_PU10to20"),
	//make_pair(" && PV_npvsGood >= 20 && PV_npvsGood < 30", 	"_PU20to30"),
	//make_pair(" && PV_npvsGood >= 30 && PV_npvsGood < 40", 	"_PU30to40"),
	//make_pair(" && PV_npvsGood >= 40", 			"_PUgeq40"),
  };

  std::function<void(TCanvas*)> plotextra;
  std::function<void(TCanvas*)> plotextra30;
  for(int iPU = 0; iPU != npv_bin.size(); iPU++){
    for (auto &var : varDict){
      z.resetSelection();
      z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2016" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR LM Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", false, &plotextra);
      z.setSelection(LLCR_LM_NoMed + npv_bin[iPU].first, "llcr_lm_nomed_2016" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR LM No Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", false, &plotextra);
      z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2017RunBtoE" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017RunBtoE LLCR LM Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2017RunBtoE, data_sample_2017RunBtoE, Category::dummy_category(), false, "", false, &plotextra);
      z.setSelection(LLCR_LM_NoMed + npv_bin[iPU].first, "llcr_lm_nomed_2017RunBtoE" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017RunBtoE LLCR LM No Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2017RunBtoE, data_sample_2017RunBtoE, Category::dummy_category(), false, "", false, &plotextra);
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2017RunF" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017RunF LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples_2017RunF, data_sample_2017RunF, Category::dummy_category(), false, "", false, &plotextra);
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2018preHEM" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2018preHEM LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples_2018preHEM, data_sample_2018preHEM, Category::dummy_category(), false, "", false, &plotextra);
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2018postHEM" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2018postHEM LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples_2018postHEM, data_sample_2018postHEM, Category::dummy_category(), false, "", false, &plotextra);
      //
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_AllEras" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", false, &plotextra);
    }
  }
  
}

