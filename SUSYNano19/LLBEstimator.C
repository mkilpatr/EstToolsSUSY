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
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);


  BaseEstimator z(config);

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"});

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
  TString LLCR = "Pass_dPhiMETLowDM";
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  //TString LepSel = " && Stop0l_nVetoElecMuon > 0 && Stop0l_MtLepMET < 100";
  TString LepSel = " && nLeptonVeto > 0 && Stop0l_MtLepMET < 100";
  config.sel = baseline + datasel + trigSR + LepSel;

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-inc", "wjets-inc", "tW-inc", "ttW-inc"};
  //TString data_sample = "singlelep-inc";
  vector<TString> data_sample = {"singlelep-inc", "singlelep_HEM-inc"};

  map<TString, BinInfo> varDict {
    //{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
    {"njets",     BinInfo("Stop0l_nJets", "N_{j}", 11, -0.5, 10.5)},
    //{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},

  };
  vector< pair< TString, TString> > npv_bin = {
	make_pair(" && 1 == 1", 				"_allPU"),
	//make_pair(" && PV_npvsGood >= 0 && PV_npvsGood < 10", 	"_PU0to10"),
	//make_pair(" && PV_npvsGood >= 10 && PV_npvsGood < 20", 	"_PU10to20"),
	//make_pair(" && PV_npvsGood >= 20 && PV_npvsGood < 30", 	"_PU20to30"),
	//make_pair(" && PV_npvsGood >= 30 && PV_npvsGood < 40", 	"_PU30to40"),
	//make_pair(" && PV_npvsGood >= 40", 			"_PUgeq40"),
						};

  for(int iPU = 0; iPU != npv_bin.size(); iPU++){
    for (auto &var : varDict){

      z.resetSelection();
      z.setSelection(LLCR + npv_bin[iPU].first, "llcr_custom_2016" + npv_bin[iPU].second, "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
      z.setSelection(LLCR_HM + npv_bin[iPU].first, "llcr_custom_hm_2016" + npv_bin[iPU].second, "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
      z.setSelection(LLCR_LM + npv_bin[iPU].first, "llcr_custom_lm_2016" + npv_bin[iPU].second, "");
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
      
      //z.setSelection("Pass_LLCR" + npv_bin[iPU].first, "llcr_2016" + npv_bin[iPU].second, "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
      //z.setSelection("Pass_LLCR_highDM" + npv_bin[iPU].first, "llcr_hm_2016" + npv_bin[iPU].second, "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
      //z.setSelection("Pass_LLCR_lowDM" + npv_bin[iPU].first, "llcr_lm_2016" + npv_bin[iPU].second, "");
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
    }
  }

}

