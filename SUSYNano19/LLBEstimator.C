/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"

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

  l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "yields_llb_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep", "_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "yields_llb_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "yields_llb_hm.tex", "hm", digits);
  }

  return l.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotLepCR(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_2016";
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
  config.addSample("ttbar-sr",       "t#bar{t}",      "ttbar",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "wjets",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "ttW",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("qcd-sr",         "QCD",           "qcd",    lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu-sr",       "znunu",         "znunu",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T1tttt-sr",	     "T1tttt(2000, 100)", "T1tttt_2000_100", lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T2tt_850_100-sr","T2tt(850, 100)","T2tt_850_100", lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T2tt_500_325-sr","T2tt(500, 325)","T2tt_500_325", lepvetowgt, datasel + trigSR + vetoes);

  config.addSample("ttbar-sr-iso",       "t#bar{t}",      "ttbar",        lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("wjets-sr-iso",       "W+jets",        "wjets",        lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("tW-sr-iso",          "tW",            "tW",              lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("ttW-sr-iso",         "ttW",           "ttW",             lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("qcd-sr-iso",         "QCD",           "qcd",    lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("znunu-sr-iso",       "znunu",         "znunu",           lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("T1tttt-sr-iso",	 "T1tttt(2000, 100)", "T1tttt_2000_100", lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("T2tt_850_100-sr-iso","T2tt(850, 100)","T2tt_850_100", lepvetowgt, datasel + trigSR + vetoes_iso);
  config.addSample("T2tt_500_325-sr-iso","T2tt(500, 325)","T2tt_500_325", lepvetowgt, datasel + trigSR + vetoes_iso);
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);

  std::map<TString,int> digits;
  digits["Total BKG"] = -3; // indicate it's data for proper formatting
  digits["Total BKG ISO"] = -3;
  digits["T1tttt-sr"] = -3;
  digits["T2tt_850_100-sr"] = -3;
  digits["T2tt_500_325-sr"] = -3;
  digits["T1tttt-sr-iso"] = -3;
  digits["T2tt_850_100-sr-iso"] = -3;
  digits["T2tt_500_325-sr-iso"] = -3;

  BaseEstimator z(config);

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.sumYields({"ttbar-sr-iso", "wjets-sr-iso", "tW-sr-iso", "ttW-sr-iso", "qcd-sr-iso", "znunu-sr-iso"}, "Total BKG ISO");
  //z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"});
  //z.printYieldsTable({"ttbar-sr-iso", "wjets-sr-iso", "tW-sr-iso", "ttW-sr-iso", "qcd-sr-iso", "znunu-sr-iso", "Total BKG ISO", "T1tttt-sr-iso", "T2tt_850_100-sr-iso", "T2tt_500_325-sr-iso"});
  z.printYieldsTableLatex({"Total BKG", "Total BKG ISO", "T1tttt-sr", "T1tttt-sr-iso", "T2tt_850_100-sr", "T2tt_850_100-sr-iso", "T2tt_500_325-sr", "T2tt_500_325-sr-iso"}, labelMap, "yields_sr_hm_2016.tex", "hm", digits);

  //z.plotSigVsBkg(const BinInfo& var_info, const vector<TString>& mc_samples, const vector<TString>& sig_sample, const Category& category, bool showSigma = true,  bool plotlog = false, std::function<void(TCanvas*)> *plotextra = nullptr)

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lepcrYields(){

  auto config = lepConfig();

  config.samples.clear();
  config.addSample("singlelep",   "Data",          "lepcr/singlelep",       "1.0",     datasel + trigLepCR + lepcrsel);
  config.addSample("ttbar",       "t#bar{t}",      "lepcr/ttbar",        lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("wjets",       "W+jets",        "lepcr/wjets",        lepselwgt, datasel + trigLepCR + lepcrsel);
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
  //config.sel = "MET_pt > 200";
  //TString LLCR_high = " && Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM && Stop0l_nVetoElecMuon == 1";
  TString LLCR_high = " && Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  config.sel = baseline + LLCR_high;

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-tau", "wjets-tau", "tW-tau", "ttW-tau"};
  TString data_sample = "singlelep-tau";

  map<TString, BinInfo> varDict {
    {"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
    {"njets",     BinInfo("Stop0l_nJets", "N_{j}", 11, -0.5, 10.5)},
    //{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},

  };
  vector< pair< TString, TString> > jetpt_bin = {
	make_pair("Jet_pt[0] > 30 && Jet_pt[0] < 50", "j1pt30to50"),
	make_pair("Jet_pt[0] > 50 && Jet_pt[0] < 100", "j1pt50to100"),
						};

  //for(int iJ = 0; iJ != jetpt_bin.size(); iJ++){
    for (auto &var : varDict){

      z.resetSelection();
      //z.setSelection("Stop0l_nJets>=2", "njgeq2_2016", "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      //z.setSelection("Stop0l_nJets>=5", "njgeq5_2016", "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      //z.setSelection("Pass_LLCR_lowDM && " + jetpt_bin[iJ].first, "njgeq2_" + jetpt_bin[iJ].second, "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      //z.setSelection("Pass_LLCR_highDM && " + jetpt_bin[iJ].first, "njgeq5_" + jetpt_bin[iJ].second, "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      //#z.setSelection("Pass_LLCR_lowDM", "njgeq2_2016", "");
      //#z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      z.setSelection(config.sel + " && (Stop0l_nVetoElecMuon == 1 || nTauMVA_71 == 1)", "njgeq5_taumvaLep_2016", "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      z.setSelection(config.sel + " && (Stop0l_nVetoElecMuon == 1 || Stop0l_nIsoTracksHad == 1)", "njgeq5_isotrkLep_2016", "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      z.setSelection(config.sel + " && nTauMVA_71 == 1", "njgeq5_taumva_2016", "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
      z.setSelection(config.sel + " && Stop0l_nIsoTracksHad == 1", "njgeq5_isotrk_2016", "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);

    }
  //}

}

