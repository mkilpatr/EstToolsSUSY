/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/ZnunuEstimator.hh"

#include "SRParameters.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> ZnunuPred(){

  auto phocfg = phoConfig();
  ZnunuEstimator z(phocfg);

  z.zllcr_cfg = zllConfig();
  z.zll_normMap = normMap;
  z.phocr_normMap = phoNormMap;

  z.pred();
  z.printYields();

  z.writeRzUnc("/tmp/values_0l_unc_znunu.conf");

  std::map<TString,int> digits;
  //dig["data"] = 0; // indicate it's data for proper formatting
  z.printYieldsTableLatex({"znunu-sr", "_Rz", "_Sgamma", "_pred"}, labelMap, "/tmp/yields_znunu_lm.tex","lm", digits);
  z.printYieldsTableLatex({"znunu-sr", "_Rz", "_Sgamma", "_pred"}, labelMap, "/tmp/yields_znunu_hm.tex","hm", digits);

  return z.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Yields(){
  auto config = phoConfig();

  BaseEstimator z(config);

  z.calcYields();
  z.printYields();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotSgamma(){
  TString region = ICHEPCR ? "phocr_ichep" : "phocr";

  auto config = phoConfig();
  config.outputdir = config.outputdir+"/"+region;

  config.catMaps = phoCatMap();
//  TString phocorrwgt = "*(1.47911-0.000621058*phopt)";
  config.addSample("gjets",       "#gamma+jets",    "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  config.addSample("qcd-fake",    "Fake",           "photoncr/qcd-fake",   phowgt, datasel + trigPhoCR + phoBadEventRemoval);
  config.addSample("qcd-frag",    "Fragmentation",  "photoncr/qcd-frag",   phowgt, datasel + trigPhoCR + phoBadEventRemoval);
  config.addSample("ttg",         "t#bar{t}#gamma", "photoncr/ttg",        phowgt, datasel + trigPhoCR);

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"gjets", "qcd-fake", "qcd-frag", "ttg"};
  TString data_sample = "singlepho";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.72); };
    TString norm_cut = "";
    for (const auto &nb : phoNormMap) {
      if(cat.name.Contains(nb.first)) {
        norm_cut = nb.second;
        break;
      }
    }
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, true, addCuts({z.config.sel, norm_cut}), false, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotRz(){
  auto config = zllConfig();

  ZnunuEstimator z(config.outputdir);
  z.setConfig(config);
  z.zllcr_cfg = config;

  for (const auto &norm : normMap){
    cout << "\n---> " << norm.first << "\n";
    z.setSelection(norm.second, norm.first, "");
    z.plotDataMC({"dyll", "ttbar"}, "doublelep");
    z.calcRz(norm.second);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RzExtrapolation(){

  auto metbin = BinInfo("met", "#slash{E}_{T}", vector<int>{100, 125, 150, 175, 200, 250, 300, 400, 500}, "GeV");

  auto config = zllConfig();
  auto zsel = config.sel;
  ZnunuEstimator z(config);
  z.zllcr_cfg = config;

  for (const auto &norm : normMap){
    cout << "\n---> " << norm.first << "\n";
    z.setSelection("", norm.first, "");
    auto incRZ = z.calcRz(norm.second);
    TH1D *hRZ = new TH1D("hRZ"+norm.first, ";MET;", metbin.plotbins.size()-1, metbin.plotbins.data());
    int ibin = 0;
    for (auto &c : metbin.cuts){
      ++ibin;
      setHistBin(hRZ, ibin, z.calcRz(addCuts({norm.second, c})));
    }
    auto c = MakeCanvas();
    c->SetTitle(norm.first);
    hRZ->Fit("pol1");
    hRZ->Draw();

    const auto &dy = config.samples.at("dyll");
    auto avgMet = getYields(dy.tree, dy.wgtvar+"*met", z.config.sel + dy.sel + " && met>200 && " + norm.second)/getYields(dy.tree, dy.wgtvar, z.config.sel + dy.sel + " && met>200 && " + norm.second);
    auto fit = (TF1*)hRZ->GetListOfFunctions()->At(0);
    double diff = fit->Eval(avgMet.value) - incRZ.value;
    cout << "\n\n ---> " << norm.first << "\n";
    cout << "====== Rz syst = " << diff <<  "======\n\n";
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ZvsGamma(){

  auto config = phoConfig();
  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();
  config.samples.clear();

  COLOR_MAP["-nb1"] = kGreen+3;
  COLOR_MAP["-nb2"] = kRed-4;
  COLOR_MAP.erase("znunu");

//  config.addSample("photon-nb1",     "#gamma+jets N_{B}=1",             "photoncr/singlepho",     wgtvar, datasel + trigPhoCR + " && nbjets==1");
//  config.addSample("photon-nb2",     "#gamma+jets N_{B}#geq2",          "photoncr/singlepho",     wgtvar, datasel + trigPhoCR + " && nbjets>=2");
  config.addSample("photon",         "#gamma+jets N_{B}#geq1",          "photoncr/singlepho",     wgtvar, datasel + trigPhoCR + " && nbjets>=1");
  config.addSample("gjets",          "#gamma+jets only N_{B}#geq1",     "photoncr/gjets",      wgtvar, datasel + trigPhoCR + " && nbjets>=1");
  config.addSample("znunu-nb1",      "Z#rightarrow#nu#nu N_{B}=1",      "sr/znunu",            wgtvar, datasel + trigSR + vetoes + " && nbjets==1");
  config.addSample("znunu-nb2",      "Z#rightarrow#nu#nu N_{B}#geq2",   "sr/znunu",            wgtvar, datasel + trigSR + vetoes + " && nbjets>=2");

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> vars;

  vars = {"mtcsv12met", "njets", "nt", "nw", "met"};
  for (auto v : vars){
    z.setPostfix("baseline");
//    z.plotComp(varDict.at(v), {"photon", "gjets", "znunu-nb1", "znunu-nb2"}, {"dummy"});
    z.plotComp(varDict.at(v), {"photon", "gjets"}, {"dummy"});
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void compIVF(){

  auto config = phoConfig();
  config.sel = addCuts({baseline, cutMap.at("lm")});
  config.categories.clear();
  config.catMaps.clear();
  config.catMaps["inclusive"] = Category("inclusive", "1==1", "N_{SV}#geq0");
  config.catMaps["nivf0"] = Category("nivf0", "nivf==0", "N_{SV}=0");
  config.catMaps["nivf1"] = Category("nivf1", "nivf>=1", "N_{SV}#geq1");

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> vars {"njets", "metgx", "ak8isrpt", "csvj1pt"};

  for (auto v : vars){
    z.setSelection("nbjets==0", "nb0", "");
    z.plotComp(varDict.at(v), {"photon", "znunu-sr"}, {"nivf0", "nivf1"}, false);
    z.setSelection("nbjets==1", "nb1", "");
    z.plotComp(varDict.at(v), {"photon", "znunu-sr"}, {"nivf0", "nivf1"}, false);
  }


}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void DoubleRatios(TString region = "hm", bool normalized = true, TString extraCut = "", TString suffix = ""){

  map<TString, TString> nbcutMap{
    {"nb0",       "nbjets==0"},
    {"nb1",       "nbjets==1"},
    {"nb2",       "nbjets>=2"},
    {"nbgeq0",    "nbjets>=0"},
    {"nbgeq1",    "nbjets>=1"},
  };

  TString drbase;
  vector<TString> drNorms;
  if (region=="hm"){
    drbase = "njets>=5";
    drNorms = {"nbgeq1"};
  }else{
    drbase = "njets>=2 && ak8isrpt>200 && dphiisrmet>2 && metovsqrtht>10";
//    drNorms = {"nb0", "nbgeq1"};
    drNorms = {"nbgeq0"};
  }
  std::map<TString, TString> DRNormMap;
  std::map<TString, TString> labels = {
      {"nb0", "N_{B} = 0"},
      {"nbgeq0", "N_{B} #geq 0"},
      {"nb1", "N_{B} = 1"},
      {"nbgeq1", "N_{B} #geq 1"},
      {"nb2", "N_{B} #geq 2"},
  };
  for (auto n : drNorms) {
    DRNormMap[n] = createCutString(n, nbcutMap);
  }

  vector<TString> vars = {"metzg"};
//  vector<TString> vars = {"ak8isrpt", "njets", "metzg"};
//  vector<TString> vars = {"origmet"};
  map<TString, vector<TH1*>> hists;

  {
    // photon
    auto config = phoConfig();
    config.catMaps = phoCatMap();
    config.addSample("gjets",       "#gamma+jets",    "photoncr/gjets",      phowgt, datasel + trigPhoCR);
    config.addSample("qcd-fake",    "Fake",           "photoncr/qcd-fake",   phowgt, datasel + trigPhoCR + phoBadEventRemoval);
    config.addSample("qcd-frag",    "Fragmentation",  "photoncr/qcd-frag",   phowgt, datasel + trigPhoCR + phoBadEventRemoval);
    config.addSample("ttg",         "t#bar{t}#gamma", "photoncr/ttg",        phowgt, datasel + trigPhoCR);

    ZnunuEstimator z(config);

    for (auto &norm : DRNormMap){
      if (extraCut != "") {
        z.config.sel = addCuts({drbase, norm.second, extraCut});
        z.setPostfix("pho_"+norm.first+suffix);
      } else{
        z.config.sel = addCuts({drbase, norm.second});
        z.setPostfix("pho_"+norm.first+"_baseline");
      }

      for (auto var : vars){
        auto phoDataMC = z.plotDataMC(varDict.at(var), {"gjets", "qcd-fake", "qcd-frag", "ttg"}, "singlepho", Category::dummy_category(), normalized);
        hists["pho_"+norm.first].push_back(phoDataMC);
      }
    }


  }

  {
    // z->ll

    auto config = zllConfig();
    config.sel = drbase;
    ZnunuEstimator z(config.outputdir);
    z.setConfig(config);

    z.zllcr_cfg = config;
    z.zll_normMap = DRNormMap;

    for (auto &norm : DRNormMap){
      Quantity RT = (norm.first=="") ? Quantity(1, 0) : z.calcRt(norm.second);

      if (extraCut != "") {
        z.config.sel = addCuts({drbase, zllCatMap["on-z"].cut, norm.second, extraCut});
        z.setPostfix("z_"+norm.first+suffix);
      } else{
        z.config.sel = addCuts({drbase, zllCatMap["on-z"].cut, norm.second});
        z.setPostfix("z_"+norm.first+"_baseline");
      }

      for (auto var : vars){
        const auto &v = varDict.at(var);

        z.plotDataMC(v, {"dyll", "ttbar"}, "doublelep", Category::dummy_category(), true);

        auto hdata = z.getHistogram(v, "doublelep", Category::dummy_category());
        auto hdyll = z.getHistogram(v, "dyll", Category::dummy_category());
        auto httbar = z.getHistogram(v, "ttbar", Category::dummy_category());

        for (int ib=0; ib<=httbar->GetNbinsX()+1; ++ib){
          auto q = RT * getHistBin(httbar, ib);
          setHistBin(httbar, ib, q);
        }
        hdata->Add(httbar, -1);

        double normFactor = hdata->Integral(0, hdata->GetNbinsX()+1)/hdyll->Integral(0, hdyll->GetNbinsX()+1);
        if(normalized) hdyll->Scale( normFactor );
        hdata->Divide(hdyll);

        hists["z_"+norm.first].push_back(hdata);
      }
    }
  }

  for (auto &norm : DRNormMap){

    for (unsigned i=0; i<vars.size(); ++i){
      auto h0 = hists["pho_"+norm.first].at(i);
      auto h1 = hists["z_"+norm.first].at(i);
      h0->SetYTitle("Data/Simulation");
      h1->SetYTitle("Data/Simulation");
      h0->SetLineColor(kViolet+2); h0->SetMarkerColor(kViolet+2);
      h1->SetLineColor(kRed); h1->SetMarkerColor(kRed);

      auto leg = prepLegends({h0, h1}, {"#gamma+jets", "Z#rightarrowll"});
      auto hDR = makeRatioHists(h1, h0);
      auto c = drawCompAndRatio({h0, h1}, {hDR}, leg, "#frac{Z#rightarrowll}{#gamma+jets}", 0.5, 1.499);
      drawTLatexNDC((region=="hm"?"High #DeltaM, ":"Low #DeltaM, ") +  labels.at(norm.first), 0.2, 0.73, 0.032);

      c->SaveAs(phoConfig().outputdir+"/znunu_"+region+"_DR_cmp_"+vars.at(i)+(extraCut!=""?suffix:"_baseline")+"_"+(normalized?"":"normalizedToLumi")+"_"+norm.first+".pdf");

      cout << "\n--------\n Double ratios: " << norm.first << endl;
      for (int i=1; i<hDR->GetNbinsX()+1; ++i){
        cout << hDR->GetBinLowEdge(i) << "->" << hDR->GetBinLowEdge(i+1) << ": " << getHistBin(hDR, i) << endl;
      }


    }
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotPhotonInclusive(){
  COLOR_MAP.erase("photon");

  auto config = phoConfig();
  config.outputdir = "/tmp/plots/phocr_inclusive";
  config.sel = "met>200";

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  config.addSample("gjets",       "#gamma+jets",    "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  config.addSample("qcd-fake",    "Fake",           "photoncr/qcd-fake",   phowgt, datasel + trigPhoCR);
  config.addSample("qcd-frag",    "Fragmentation",  "photoncr/qcd-frag",   phowgt, datasel + trigPhoCR);
  config.addSample("ttg",         "t#bar{t}#gamma", "photoncr/ttg",        phowgt, datasel + trigPhoCR);

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"gjets", "qcd-fake", "qcd-frag", "ttg"};
  TString data_sample = "singlepho";

  map<TString, BinInfo> varDict {
    {"met",       BinInfo("met", "#slash{E}_{T}", 16, 250, 800, "GeV")},
//    {"origmet",   BinInfo("origmet", "Original #slash{E}_{T}", 40, 0, 400, "GeV")},
//    {"njets",     BinInfo("njets", "N_{j}", 12, -0.5, 11.5)},
//    {"nt",        BinInfo("nsdtoploose", "N_{t}", 2, -0.5, 1.5)},
//    {"nw",        BinInfo("nsdwloose", "N_{W}", 2, -0.5, 1.5)},
//    {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
//    {"nbjets",    BinInfo("nbjets",  "N_{B}^{medium}", 5, -0.5, 4.5)},
//    {"dphij1met", BinInfo("dphij1met", "#Delta#phi(j_{1},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij2met", BinInfo("dphij2met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij3met", BinInfo("dphij3met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
//    {"phopt",     BinInfo("phopt", "p_{T}^{#gamma} [GeV]", 16, 0, 800)},
//    {"phoeta",    BinInfo("phoeta", "#eta_{#gamma}", 25, -2.5, 2.5)},
////    {"drphotonparton",    BinInfo("drphotonparton", "min#DeltaR(#gamma, q)", 20, 0, 2)},
//    {"dphij1lmet",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
//    {"njl",       BinInfo("njl", "N_{j}^{ISR}", 5, -0.5, 4.5)},
//    {"j1lpt",     BinInfo("j1lpt", "p_{T}(j_{1}^{ISR}) [GeV]", 20, 0, 1000)},
//    {"csvj1pt",   BinInfo("csvj1pt", "p_{T}(b_{1}) [GeV]", 8, 20, 100)},

//    {"j1csv",    BinInfo("j1csv", "CSV(j_{1})", 20, 0, 1)},
//    {"j2csv",    BinInfo("j2csv", "CSV(j_{2})", 20, 0, 1)},
//    {"j1csv_wp",    BinInfo("j1csv/1", "CSV(j_{1})", vector<double>{0, 0.460, 0.800, 1})},
//    {"j2csv_wp",    BinInfo("j2csv/1", "CSV(j_{2})", vector<double>{0, 0.460, 0.800, 1})},
//    {"b1csv",    BinInfo("b1csv", "CSV(b_{1})", 20, 0, 1)},
//    {"b2csv",    BinInfo("b2csv", "CSV(b_{2})", 20, 0, 1)},
  };

  for (auto &var : varDict){
    z.resetSelection();
    //z.setSelection("njets>=2", "njgeq2", "");
    //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
    z.setSelection("njets>=5", "njgeq5", "");
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", false);
  }

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void plotZllInclusive(){
  auto config = zllConfig();

  config.categories = {"on-z"};

  config.sel = "met>200 && njets>=5";

  BaseEstimator z(config);

  vector<TString> mc_samples = {"ttbar", "dyll"};
  TString data_sample = "doublelep";

  map<TString, BinInfo> varDict {
    {"met",       BinInfo("met", "#slash{E}_{T}", 16, 200, 1000, "GeV")},
//    {"npv",       BinInfo("npv", "Number of Primary Vertices", 40, -0.5, 39.5)},
//    {"origmet",   BinInfo("origmet", "Original #slash{E}_{T}", 40, 0, 400, "GeV")},
//    {"njets",     BinInfo("njets", "N_{j}", 12, -0.5, 11.5)},
//    {"nt",        BinInfo("nsdtoploose", "N_{t}", 2, -0.5, 1.5)},
//    {"nw",        BinInfo("nsdwloose", "N_{W}", 2, -0.5, 1.5)},
    {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
    {"nbjets",    BinInfo("nbjets",  "N_{B}^{medium}", 5, -0.5, 4.5)},
//    {"dphij1met", BinInfo("dphij1met", "#Delta#phi(j_{1},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij2met", BinInfo("dphij2met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij3met", BinInfo("dphij3met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
//    {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 16, 0, 800)},
//    {"leptoneta", BinInfo("leptoneta", "#eta_{lep}", 25, -2.5, 2.5)},
//    {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 16, 0, 800)},
//    {"dileppt",   BinInfo("dileppt", "p_{T}^{ll} [GeV]", 20, 0, 1000)},
//    {"dilepmass",   BinInfo("dilepmass", "m_{ll} [GeV]", 16, 70, 110)},
//    {"metovsqrtht",BinInfo("metovsqrtht", "#slash{E}_{T}/#sqrt{H_{T}}", 10, 0, 20)},
//    {"dphij1lmet",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
//    {"njl",       BinInfo("njl", "N_{j}^{ISR}", 5, -0.5, 4.5)},
//    {"j1lpt",     BinInfo("j1lpt", "p_{T}(j_{1}^{ISR}) [GeV]", 20, 0, 1000)},
//    {"csvj1pt",   BinInfo("csvj1pt", "p_{T}(b_{1}) [GeV]", 8, 20, 100)}
  };


  for (auto &var : varDict){
 //     z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true);
    z.plotDataMC(var.second, mc_samples, data_sample, z.config.catMaps.at("on-z"), false, "", false);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void diffZnunu(){

  auto config = phoConfig();
  config.crCatMaps.clear();
  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();
  config.samples.clear();

  config.sel = "njets>=2 && met>200";

  COLOR_MAP["-74x"] = kGreen+3;
  COLOR_MAP["-80x"] = kRed-4;
  COLOR_MAP.erase("znunu");

  config.addSample("znunu-74x",      "Z#rightarrow#nu#nu 74X",      "74X/znunu",  lumistr+"*weight", " && nvetolep==0 && nvetotau==0");
  config.addSample("znunu-80x",      "Z#rightarrow#nu#nu 80X",      "sr/znunu",   lumistr+"*weight", " && nvetolep==0 && nvetotau==0");

  BaseEstimator z(config);

  vector<TString> vars;

  vars = {"mtcsv12met", "nbjets", "nlbjets", "met"};
  z.plotComp(varDict.at("njets"), {"znunu-74x", "znunu-80x"}, {"dummy"}, true, false);

  for (auto v : vars){
    z.resetSelection();
    z.plotComp(varDict.at(v), {"znunu-74x", "znunu-80x"}, {"dummy"}, true, false);
    z.setSelection("njets==3", "nj3", "nj==3");
    z.plotComp(varDict.at(v), {"znunu-74x", "znunu-80x"}, {"dummy"}, true, false);
    z.setSelection("njets==4", "nj4", "nj==4");
    z.plotComp(varDict.at(v), {"znunu-74x", "znunu-80x"}, {"dummy"}, true, false);
    z.setSelection("njets>=5", "njgeq5", "nj>=5");
    z.plotComp(varDict.at(v), {"znunu-74x", "znunu-80x"}, {"dummy"}, true, false);
  }

}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
