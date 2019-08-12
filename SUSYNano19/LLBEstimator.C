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
  //l.pred();
  l.predAllEras();

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
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", true, &plotextra);
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
  vector<TString> data_sample = {"singlelep-2016", "singlelep-2017RunBtoE", "singlelep-2017RunF", "singlelep-2018preHEM", "singlelep-2018postHEM"};

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

//void plot1LepInclusive(){
//  auto config = lepConfig();
//  //config.sel = "MET_pt > 200";
//  TString LLCR = "Pass_dPhiMETLowDM";
//  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
//  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
//  TString LLCR30 = "Stop0l_nJets30>=2 && Pass_dPhiMETLowDM30";
//  TString LLCR30_LM = "Stop0l_nJets30>=2 && Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM30";
//  TString LLCR30_HM = "Stop0l_nJets30>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM30";
//  config.sel = baseline + " && Stop0l_nJets >= 2";
//
//  config.categories.clear();
//  config.catMaps.clear();
//  config.categories.push_back("dummy");
//  config.catMaps["dummy"] = Category::dummy_category();
//
//  BaseEstimator z(config.outputdir);
//  z.setConfig(config);
//
//  vector<TString> mc_samples = {"ttbar", "wjets", "tW", "ttW", "ttZ", "diboson", "qcd"};
//  vector<TString> mc_samples30 = {"ttbar30", "wjets30", "tW30", "ttW30", "ttZ30", "diboson30", "qcd30"};
//  TString data_sample = "singlelep";
//  vector<TString> mc_samples_HEM = {"ttbar-HEM", "wjets-HEM", "tW-HEM", "ttW-HEM", "ttZ-HEM", "diboson-HEM", "qcd-HEM"};
//  vector<TString> mc_samples30_HEM = {"ttbar30-HEM", "wjets30-HEM", "tW30-HEM", "ttW30-HEM", "ttZ30-HEM", "diboson30-HEM", "qcd30-HEM"};
//  TString data_sample_preHEM    = "singlelep-preHEM";
//  TString data_sample_postHEM   = "singlelep-postHEM";
//  TString data_sample30_preHEM  = "singlelep30-preHEM";
//  TString data_sample30_postHEM = "singlelep30-postHEM";
//  TString data_sample_RunBtoE   = "singlelep-RunBtoE";
//  TString data_sample_RunF      = "singlelep-RunF";
//  TString data_sample30_RunBtoE = "singlelep30-RunBtoE";
//  TString data_sample30_RunF    = "singlelep30-RunF";
//
//  map<TString, BinInfo> varDict {
//	{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
//	{"njets",     BinInfo("Stop0l_nJets", "N_{j}", 11, -0.5, 10.5)},
//	{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
//	{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
//  };
//  vector< pair< TString, TString> > npv_bin = {
//	make_pair(" && 1 == 1", 				"_allPU"),
//	//make_pair(" && PV_npvsGood >= 0 && PV_npvsGood < 10", 	"_PU0to10"),
//	//make_pair(" && PV_npvsGood >= 10 && PV_npvsGood < 20", 	"_PU10to20"),
//	//make_pair(" && PV_npvsGood >= 20 && PV_npvsGood < 30", 	"_PU20to30"),
//	//make_pair(" && PV_npvsGood >= 30 && PV_npvsGood < 40", 	"_PU30to40"),
//	//make_pair(" && PV_npvsGood >= 40", 			"_PUgeq40"),
//  };
//
//  TString data_sample_ = "", data_sample30_ = "";
//  vector<TString> mc_samples_, mc_samples30_;
//  TString plotName = "";
//  if(process == "pre"){
//      if(is2017){
//        plotName = "_RunBtoE_2017";
//      } else if(is2018){
//        plotName = "_PreHEM_2018";
//      }
//
//      if(is2017){
//        data_sample_ = data_sample_RunBtoE;
//	mc_samples_  = mc_samples;
//      } else if(is2018){
//	data_sample_ = data_sample_preHEM;
//	mc_samples_  = mc_samples;
//      } else{
//	data_sample_ = data_sample;
//	mc_samples_  = mc_samples;
//      }
//      if(is2017){
//        data_sample30_ = data_sample30_RunBtoE;
//	mc_samples30_  = mc_samples30;
//      } else if(is2018){
//	data_sample30_ = data_sample30_preHEM;
//	mc_samples30_  = mc_samples30;
//      } else{
//	data_sample30_ = data_sample;
//	mc_samples30_  = mc_samples;
//      }
//  } else if(process == "post"){
//      if(is2017){
//        plotName = "_RunF_2017";
//      } else if(is2018){
//        plotName = "_PostHEM_2018";
//      }
//
//      if(is2017){
//        data_sample_ = data_sample_RunF;
//        mc_samples_  = mc_samples;
//      } else if(is2018){
//        data_sample_ = data_sample_postHEM;
//        mc_samples_  = mc_samples_HEM;
//      } else{
//        data_sample_ = data_sample;
//        mc_samples_  = mc_samples;
//      }
//      if(is2017){
//        data_sample30_ = data_sample30_RunF;
//        mc_samples30_  = mc_samples30;
//      } else if(is2018){
//        data_sample30_ = data_sample30_postHEM;
//        mc_samples30_  = mc_samples30_HEM;
//      } else{
//        data_sample30_ = data_sample;
//        mc_samples30_  = mc_samples;
//      }
//  }
//
//  //std::function<void(TCanvas*)> plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
//  //std::function<void(TCanvas*)> plotextra30 = [&](TCanvas *c){ c->cd(); drawTLatexNDC("N_{j}(p_{T} #geq 30)", 0.2, 0.72); };
//  std::function<void(TCanvas*)> plotextra;
//  std::function<void(TCanvas*)> plotextra30;
//  for(int iPU = 0; iPU != npv_bin.size(); iPU++){
//    for (auto &var : varDict){
//      z.resetSelection();
//      z.setSelection(LLCR + npv_bin[iPU].first, "llcr" + plotName + npv_bin[iPU].second, "");
//      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
//      z.plotDataMC(var.second, mc_samples_, data_sample_, Category::dummy_category(), false, "", true, &plotextra);
//      z.setSelection(LLCR_HM + npv_bin[iPU].first, "llcr_hm" + plotName + npv_bin[iPU].second, "");
//      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR HM N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
//      z.plotDataMC(var.second, mc_samples_, data_sample_, Category::dummy_category(), false, "", true, &plotextra);
//      z.setSelection(LLCR_LM + npv_bin[iPU].first, "llcr_lm" + plotName + npv_bin[iPU].second, "");
//      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR LM N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
//      z.plotDataMC(var.second, mc_samples_, data_sample_, Category::dummy_category(), false, "", true, &plotextra);
//
//      z.setSelection(LLCR30 + npv_bin[iPU].first, "llcr_njets30" + plotName + npv_bin[iPU].second, "");
//      plotextra30 = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR N_{j}(p_{T} #geq 30)", 0.2, 0.72); };
//      z.plotDataMC(var.second, mc_samples30_, data_sample30_, Category::dummy_category(), false, "", true, &plotextra30);
//      z.setSelection(LLCR30_HM + npv_bin[iPU].first, "llcr_njets30_hm" + plotName + npv_bin[iPU].second, "");
//      plotextra30 = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR HM N_{j}(p_{T} #geq 30)", 0.2, 0.72); };
//      z.plotDataMC(var.second, mc_samples30_, data_sample30_, Category::dummy_category(), false, "", true, &plotextra30);
//      z.setSelection(LLCR30_LM + npv_bin[iPU].first, "llcr_njets30_lm" + plotName + npv_bin[iPU].second, "");
//      plotextra30 = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR LM N_{j}(p_{T} #geq 30)", 0.2, 0.72); };
//      z.plotDataMC(var.second, mc_samples30_, data_sample30_, Category::dummy_category(), false, "", true, &plotextra30);
//
//    }
//  }
//  
//}

