/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/LLBEstimator.hh"
#include "LMParameters.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPred(){
  auto config = lepConfig();

  LLBEstimator z(config);

  z.pred();
  z.yields["_TF"] = z.yields.at("ttbarplusw-sr")/z.yields.at("ttbarplusw");

  z.printYields();

  return z.yields.at("_pred");
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

  vars = {"mtcsv12met", "j1lpt", "csvj1pt", "njets" ,"met"};
  for (auto v : vars){
    z.setPostfix("baseline_nb0");
    z.plotComp(varDict.at(v), {"ttbarplusw-0b", "tt_revert-0b", "tt_lepcr-0b"}, {"dummy"});
    z.setPostfix("baseline_nb1");
    z.plotComp(varDict.at(v), {"ttbarplusw-1b", "tt_revert-1b", "tt_lepcr-1b"}, {"dummy"});
  }

  z.config.sel = addCuts({baseline,mtb});
  vars = {"j1lpt", "csvj1pt", "njets", "met"};
  for (auto v : vars){
    z.setPostfix("srsel_nb1");
    z.plotComp(varDict.at(v), {"ttbarplusw-1b", "tt_revert-1b", "tt_lepcr-1b"}, {"dummy"});
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void compSLep(){

  map<TString, vector<Quantity>> sLeps;

  {
    ADD_LEP_TO_MET = true;

    auto config = lepConfig();
    LLBEstimator z(config);
    z.pred();
    sLeps["addback"] = z.yields.at("_SLep");
  }

  {
    ADD_LEP_TO_MET = false;

    auto config = lepConfig();
    LLBEstimator z(config);
    z.pred();
    sLeps["noaddback"] = z.yields.at("_SLep");

  }

  map<TString, TString> labelMap = {
      {"addback", "#slash{E}_{T}+#vec{p}_{T}^{lep}"},
      {"noaddback", "Traditional"}
  };

  auto leg = initLegend();
  vector<TH1*> hists, hnum;
  TH1* href = nullptr;
  for (auto &p : sLeps){
    cout << p.first << p.second << endl;
    auto h = convertToHist(p.second, p.first, ";SR;");
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


// ~~~~~~~
void DoubleRatios(bool srsel=false){

  map<TString, TString> normMap = {{"inc", "nbjets>=0"}};

  map<TString, TString> labels = {
      {"inc", ""}, {"nb0", " N_{B}=0"}, {"nb1", " N_{B}#geq1, N_{B}^{L}=1"}, {"nb2", " N_{B}#geq1, N_{B}^{L}#geq2"}
  };

  vector<TString> vars = {"mtcsv12met", "j1lpt", "csvj1pt", "njets", "met", "nlbjets", "ptb12", "leptonpt"};
//  vector<TString> vars = {"leptonpt", "origmet", "leptonptovermet"};
//  vector<TString> vars = {"leptonpt"};
  map<TString, vector<TH1*>> hists;

  {
    ADD_LEP_TO_MET = false;

    auto config = lepConfig();
    LLBEstimator z(config.outputdir);
    z.setConfig(config);

    for (auto &norm : normMap){
      if (srsel) {
        z.config.sel = addCuts({baseline, norm.second, mtb});
        z.setPostfix("noaddback_"+norm.first+"_srsel");
      } else{
        z.config.sel = addCuts({baseline, norm.second});
        z.setPostfix("noaddback_"+norm.first+"_baseline");
      }

      for (auto var : vars){
        hists["noaddback_"+norm.first].push_back(z.plotDataMC(varDict.at(var), {"ttbar", "wjets", "tW", "ttW"}, "singlelep", Category::dummy_category(), false));
      }
    }

  }

  {
    ADD_LEP_TO_MET = true;

    auto config = lepConfig();
    LLBEstimator z(config.outputdir);
    z.setConfig(config);

    for (auto &norm : normMap){
      if (srsel) {
        z.config.sel = addCuts({baseline, norm.second, mtb});
        z.setPostfix("addback_"+norm.first+"_srsel");
      } else{
        z.config.sel = addCuts({baseline, norm.second});
        z.setPostfix("addback_"+norm.first+"_baseline");
      }

      for (auto var : vars){
        hists["addback_"+norm.first].push_back(z.plotDataMC(varDict.at(var), {"ttbar", "wjets", "tW", "ttW"}, "singlelep", Category::dummy_category(), false));
      }
    }

  }

  for (auto &norm : normMap){
    for (unsigned i=0; i<vars.size(); ++i){
      auto h0 = hists["noaddback_"+norm.first].at(i);
      auto h1 = hists["addback_"+norm.first].at(i);
      h0->SetYTitle("Data/Simulation");
      h1->SetYTitle("Data/Simulation");
      h0->SetLineColor(kBlack); h0->SetMarkerColor(kBlack);
      h1->SetLineColor(kRed); h1->SetMarkerColor(kRed);

      auto leg = prepLegends({h0, h1}, {"Traditional"+labels.at(norm.first), "#slash{E}_{T}+#vec{p}_{T}^{lep}"+labels.at(norm.first)});
      auto c = drawCompAndRatio({h0, h1}, {makeRatioHists(h1, h0)}, leg, "#frac{#slash{E}_{T}+#vec{p}_{T}^{lep}}{Traditional}");

      c->SaveAs(lepConfig().outputdir+"/llb_cmp_"+vars.at(i)+(srsel?"_srsel":"_baseline")+"_"+norm.first+".pdf");

    }
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
  config.addSample("qcd-sr",         "QCD",           "sr/qcd",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu-sr",       "znunu",         "sr/znunu",           lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);

  config.addSample("T2fbd_375_355",  "T2fbd_375_355",  "signals/T2fbd_375_355",  lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T2fbd_375_325",  "T2fbd_375_325",  "signals/T2fbd_375_325",  lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T2fbd_375_295",  "T2fbd_375_295",  "signals/T2fbd_375_295",  lepvetowgt, datasel + trigSR + vetoes);

  BaseEstimator z(config.outputdir);
  z.setConfig(config);
//  z.config.sel = "met>250 && njets>=2 && njl>=1 && nbjets>=1 && dphij1met>0.5 && dphij2met>0.15 && dphij3met>0.15 && metovsqrtht>10 && j1lpt>250 && dphij1lmet>2 && mtcsv12met<100";

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG", "T2fbd_375_295", "T2fbd_375_325", "T2fbd_375_355"});

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lepcrYields(){

  auto config = lepConfig();

  BaseEstimator z(config);

  z.calcYieldsExcludes({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "rare-sr"});
  z.printYields();
  z.sumYields({"ttbar", "wjets", "tW", "ttW"}, "Total BKG");
  z.printYieldsTable({"ttbar", "wjets", "tW", "ttW", "Total BKG", "singlelep"});

}
