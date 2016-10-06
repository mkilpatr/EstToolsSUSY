/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/LLBEstimator.hh"

#include "HMParameters.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPred(){

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.pred();

  l.printYields();

  return l.yields.at("_pred");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotLepCR(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  TString region = ADD_LEP_TO_MET ? "lepcr" : "lepcr_from_sr";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar", "wjets", "tW", "ttW"};
  TString data_sample = "singlelep";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.7); };
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ZeroVsOneLep(){

  auto config = lepConfig();
  config.samples.clear();
  config.addSample("tt_lepcr-0b",  "1L (#slash{E}_{T}+#vec{p}_{T}^{lep}) N_{B}=0",      "lepcr/ttbarplusw",     lepselwgt, datasel + trigLepCR + lepcrsel + " && nbjets==0");
  config.addSample("tt_revert-0b", "1L (Traditional) N_{B}=0",                          "sr/ttbarplusw",        lepselwgt, datasel + trigSR + revert_vetoes + " && nbjets==0");
  config.addSample("ttbarplusw-0b",        "0L N_{B}=0",                                        "sr/ttbarplusw",        lepvetowgt,datasel + trigSR + vetoes + " && nbjets==0");

  config.addSample("tt_lepcr-1b",  "1L (#slash{E}_{T}+#vec{p}_{T}^{lep}) N_{B}#geq1",   "lepcr/ttbarplusw",     lepselwgt, datasel + trigLepCR + lepcrsel + " && nbjets>=1");
  config.addSample("tt_revert-1b", "1L (Traditional) N_{B}#geq1",                       "sr/ttbarplusw",        lepselwgt, datasel + trigSR + revert_vetoes + " && nbjets>=1");
  config.addSample("ttbarplusw-1b",        "0L N_{B}#geq1",                                     "sr/ttbarplusw",        lepvetowgt,datasel + trigSR + vetoes + " && nbjets>=1");

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  COLOR_MAP["lepcr-"] = kGreen+3;
  COLOR_MAP["revert-"] = kRed-4;

  BaseEstimator z(config.outputdir);
  z.setConfig(config);
  z.setSaveHists();

  vector<TString> vars;

  vars = {"mtcsv12met"};
  for (auto v : vars){
    z.setPostfix("baseline_nb0");
    z.plotComp(varDict.at(v), {"ttbarplusw-0b", "tt_revert-0b", "tt_lepcr-0b"}, {"dummy"});
    z.setPostfix("baseline_nb1");
    z.plotComp(varDict.at(v), {"ttbarplusw-1b", "tt_revert-1b", "tt_lepcr-1b"}, {"dummy"});
  }

  z.config.sel = addCuts({baseline,highmt});
  vars = {"j1lpt", "csvj1pt", "njets", "met"};
  for (auto v : vars){
    z.setPostfix("srsel_nb1");
    z.plotComp(varDict.at(v), {"ttbarplusw-1b", "tt_revert-1b", "tt_lepcr-1b"}, {"dummy"});
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

void DoubleRatios(bool srsel=false){

  vector<TString> vars = {"mtcsv12met", "met"};
//  vector<TString> vars = {"leptonpt", "origmet", "leptonptovermet"};
//  vector<TString> vars = {"csvj1pt_1"};
  map<TString, vector<TH1*>> hists;

  {
    ADD_LEP_TO_MET = false;

    auto config = lepConfig();
    LLBEstimator z(config.outputdir);
    z.setConfig(config);

    if (srsel) {
      z.config.sel = addCuts({baseline, highmt});
      z.setPostfix("noaddback_srsel");
    } else{
      z.config.sel = baseline;
      z.setPostfix("noaddback_baseline");
    }

    for (auto var : vars){
      hists["noaddback"].push_back(z.plotDataMC(varDict.at(var), {"ttbar", "wjets", "tW", "ttW"}, "singlelep", Category::dummy_category(), false));
    }

  }

  {
    ADD_LEP_TO_MET = true;

    auto config = lepConfig();
    LLBEstimator z(config.outputdir);
    z.setConfig(config);

    if (srsel) {
      z.config.sel = addCuts({baseline, highmt});
      z.setPostfix("addback_srsel");
    } else{
      z.config.sel = baseline;
      z.setPostfix("addback_baseline");
    }

    for (auto var : vars){
      hists["addback"].push_back(z.plotDataMC(varDict.at(var), {"ttbar", "wjets", "tW", "ttW"}, "singlelep", Category::dummy_category(), false));
    }

  }

  for (unsigned i=0; i<vars.size(); ++i){
    auto h0 = hists["noaddback"].at(i);
    auto h1 = hists["addback"].at(i);
    h0->SetYTitle("Data/Simulation");
    h1->SetYTitle("Data/Simulation");
    h0->SetLineColor(kBlack); h0->SetMarkerColor(kBlack);
    h1->SetLineColor(kRed); h1->SetMarkerColor(kRed);

    auto leg = prepLegends({h0, h1}, {"Traditional", "#slash{E}_{T}+#vec{p}_{T}^{lep}"});
    auto c = drawCompAndRatio({h0, h1}, {makeRatioHists(h1, h0)}, leg, "#frac{#slash{E}_{T}+#vec{p}_{T}^{lep}}{Traditional}");

    c->SaveAs(lepConfig().outputdir+"/llb_cmp_"+vars.at(i)+(srsel?"_srsel":"_baseline")+".pdf");

  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void srYields(){

  auto config = lepConfig();
  config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("ttbar-sr",       "t#bar{t}",      "sr/ttbar-mg",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "sr/wjets-ht",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "sr/tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "sr/ttW",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("qcd-sr",         "QCD",           "qcd-std/qcd",    lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu-sr",       "znunu",         "sr/znunu",           lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);

  BaseEstimator z(config);

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG"});

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lepcrYields(){

  auto config = lepConfig();

  config.samples.clear();
  config.addSample("singlelep",   "Data",          "lepcr/singlelep",       "1.0",     datasel + trigLepCR + lepcrsel);
  config.addSample("ttbar",       "t#bar{t}",      "lepcr/ttbar-mg",        lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("wjets",       "W+jets",        "lepcr/wjets-ht",        lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("tW",          "tW",            "lepcr/tW",              lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("ttW",         "ttW",           "lepcr/ttW",             lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("qcd",         "QCD",           "lepcr/qcd",             lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("ww",          "WW",            "sr/ww",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("wz",          "WZ",            "sr/wz",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("zz",          "ZZ",            "sr/zz",                 lepselwgt, datasel + trigLepCR + lepcrsel);

  BaseEstimator z(config);

  z.calcYields();
  z.printYields();
  z.sumYields({"ttbar", "wjets", "tW", "ttW", "qcd"}, "Total BKG");
  z.printYieldsTable({"ttbar", "wjets", "tW", "ttW", "qcd", "Total BKG", "singlelep"});

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusive(){
  auto config = lepConfig();
  config.sel = "met>200";

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar", "wjets", "tW", "ttW"};
  TString data_sample = "singlelep";

  map<TString, BinInfo> varDict {
//    {"met",       BinInfo("met", "#slash{E}_{T}", 16, 0, 800, "GeV")},
//    {"origmet",   BinInfo("origmet", "Original #slash{E}_{T}", 40, 0, 400, "GeV")},
//    {"njets",     BinInfo("njets", "N_{j}", 12, -0.5, 11.5)},
//    {"ncttstd",   BinInfo("ncttstd", "N_{CTT}", 3, -0.5, 2.5)},
//    {"nt",        BinInfo("nsdtoploose", "N_{t}", 2, -0.5, 1.5)},
//    {"nw",        BinInfo("nsdwloose", "N_{W}", 2, -0.5, 1.5)},
//    {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
//    {"nbjets",    BinInfo("nbjets",  "N_{B}^{medium}", 5, -0.5, 4.5)},
//    {"dphij1met", BinInfo("dphij1met", "#Delta#phi(j_{1},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij2met", BinInfo("dphij2met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij3met", BinInfo("dphij3met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
//    {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 16, 0, 800)},
//    {"leptoneta", BinInfo("leptoneta", "#eta_{lep}", 25, -2.5, 2.5)},
//    {"leptonptovermet",  BinInfo("leptonpt/met", "p_{T}^{lep}/#slash{E}_{T}", 20, 0, 1.)},
//    {"lp",  BinInfo("lp", "L_{P}", 40, -2, 2.)},

    {"j1csv",    BinInfo("j1csv", "CSV(j_{1})", 20, 0, 1)},
    {"j2csv",    BinInfo("j2csv", "CSV(j_{2})", 20, 0, 1)},
    {"j1csv_wp",    BinInfo("j1csv/1", "CSV(j_{1})", vector<double>{0, 0.460, 0.800, 1})},
    {"j2csv_wp",    BinInfo("j2csv/1", "CSV(j_{2})", vector<double>{0, 0.460, 0.800, 1})},
    {"b1csv",    BinInfo("b1csv", "CSV(b_{1})", 20, 0, 1)},
    {"b2csv",    BinInfo("b2csv", "CSV(b_{2})", 20, 0, 1)},

  };

  for (auto &var : varDict){

    z.resetSelection();
    z.setSelection("njets>=2", "njgeq2", "");
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
    z.setSelection("njets>=5", "njgeq5", "");
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);

//      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false);
  }

}

