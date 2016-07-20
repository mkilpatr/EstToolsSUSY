/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/ZnunuEstimator.hh"

#include "LMParameters.hh"

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
  auto config = phoConfig();
  config.catMaps = phoCatMap();
  config.addSample("gjets",       "#gamma+jets",    "photoncr/gjets",      wgtvar, datasel + trigPhoCR);
  config.addSample("qcd-fake",    "Fake",           "photoncr/qcd-fake",   wgtvar, datasel + trigPhoCR);
  config.addSample("qcd-frag",    "Fragmentation",  "photoncr/qcd-frag",   wgtvar, datasel + trigPhoCR);

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"gjets", "qcd-fake", "qcd-frag"};
  TString data_sample = "singlepho";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.7); };
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

void ZvsGamma(){

  auto config = phoConfig();
  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();
  config.samples.clear();

  COLOR_MAP["-nlb"] = kOrange+2;

  config.addSample("photon",          "#gamma+jets",      "photoncr/photon",     wgtvar, datasel + trigPhoCR);

  config.addSample("photon-nlb1",     "#gamma+jets N_{B}^{L}#geq1",      "photoncr/photon",     wgtvar, datasel + trigPhoCR + " && nlbjets>=1");
  config.addSample("photon-nb1",      "#gamma+jets N_{B}#geq1",          "photoncr/photon",     wgtvar, datasel + trigPhoCR + " && nbjets>=1");
  config.addSample("znunu-nb1",       "Z#rightarrow#nu#nu N_{B}#geq1",   "sr/znunu",            wgtvar, datasel + trigSR + vetoes + " && nbjets>=1");

  config.addSample("photon-nlb0",     "#gamma+jets N_{B}^{L}=0",         "photoncr/photon",     wgtvar, datasel + trigPhoCR + " && nlbjets==0");
  config.addSample("photon-nb0",      "#gamma+jets N_{B}=0",             "photoncr/photon",     wgtvar, datasel + trigPhoCR + " && nbjets==0");
  config.addSample("znunu-nb0",       "Z#rightarrow#nu#nu N_{B}=0",      "sr/znunu",            wgtvar, datasel + trigSR + vetoes + " && nbjets==0");

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> vars;

  vars = {"metgx"};
//  vars = {"mtcsv12met", "j1lpt", "csvj1pt", "njets", "met"};
  for (auto v : vars){
    z.setPostfix("baseline_nb0");
    z.plotComp(varDict.at(v), {"znunu-nb0", "photon-nlb0", "photon-nb0"}, {"dummy"});
    z.setPostfix("baseline_nb1");
    z.plotComp(varDict.at(v), {"znunu-nb1", "photon-nlb1", "photon-nb1"}, {"dummy"});
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void DoubleRatios(TString extraCut = "", TString suffix = ""){

  const TString drbase = baseline;

  vector<TString> nbcat = {"nb0", "nbgeq1"};
  map<TString, TString> zllNormMap = {{"nb0","nbjets==0"}, {"nbgeq1","nbjets>=1"}};
  vector<TString> phoNormCuts = {"nlbjets==0", "nlbjets>=1"};
  vector<TString> zlllabels = {"N_{B}=0", "N_{B}#geq1"};
  vector<TString> pholabels = {"N_{B}^{L}=0", "N_{B}^{L}#geq1"};

//  vector<TString> nbcat = {"inc"};
//  map<TString, TString> zllNormMap = {{"inc","nbjets>=0"}};
//  vector<TString> phoNormCuts = {"nlbjets>=0"};
//  vector<TString> zlllabels = {"N_{B}#geq0"};
//  vector<TString> pholabels = {"N_{B}^{L}#geq0"};


//  vector<TString> vars = {"metzg"};
  vector<TString> vars = {"metzg", "j1lpt", "csvj1pt", "ptb12", "njets"};
  map<TString, vector<TH1*>> hists;

  {
    // photon
    auto config = phoConfig();
    config.catMaps = phoCatMap();
    config.addSample("gjets",       "#gamma+jets",    "photoncr/gjets",      phowgt, datasel + trigPhoCR);
    config.addSample("qcd-fake",    "Fake",           "photoncr/qcd-fake",   phowgt, datasel + trigPhoCR);
    config.addSample("qcd-frag",    "Fragmentation",  "photoncr/qcd-frag",   phowgt, datasel + trigPhoCR);

    ZnunuEstimator z(config);

    for (unsigned i=0; i<nbcat.size(); ++i){
      if (extraCut != "") {
        z.config.sel = addCuts({drbase, phoNormCuts.at(i), extraCut});
        z.setPostfix("pho_"+nbcat.at(i)+suffix);
      } else{
        z.config.sel = addCuts({drbase, phoNormCuts.at(i)});
        z.setPostfix("pho_"+nbcat.at(i)+"_baseline");
      }

      for (auto var : vars){
        hists["pho_"+nbcat.at(i)].push_back(z.plotDataMC(varDict.at(var), {"gjets", "qcd-fake", "qcd-frag"}, "singlepho", Category::dummy_category(), true));
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
    z.zll_normMap = zllNormMap;

    for (auto &norm : zllNormMap){
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
        hdyll->Scale( normFactor );
        hdata->Divide(hdyll);

        hists["z_"+norm.first].push_back(hdata);
      }
    }
  }

  for (unsigned ib=0; ib<nbcat.size(); ++ib){
    auto nb = nbcat.at(ib);

    for (unsigned i=0; i<vars.size(); ++i){
      auto h0 = hists["pho_"+nb].at(i);
      auto h1 = hists["z_"+nb].at(i);
      h0->SetYTitle("Data/Simulation");
      h1->SetYTitle("Data/Simulation");
      h0->SetLineColor(kViolet+2); h0->SetMarkerColor(kViolet+2);
      h1->SetLineColor(kRed); h1->SetMarkerColor(kRed);

      auto leg = prepLegends({h0, h1}, {"#gamma+jets "+pholabels.at(ib), "Z#rightarrowll "+zlllabels.at(ib)});
      auto c = drawCompAndRatio({h0, h1}, {makeRatioHists(h1, h0)}, leg, "#frac{Z#rightarrowll}{#gamma+jets}");

      c->SaveAs(phoConfig().outputdir+"/znunu_DR_cmp_"+vars.at(i)+(extraCut!=""?suffix:"_baseline")+"_"+nb+".pdf");

    }
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

