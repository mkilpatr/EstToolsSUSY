#ifndef ESTTOOLS_ESTMETHODS_ZNUNUESTIMATOR_HH_
#define ESTTOOLS_ESTMETHODS_ZNUNUESTIMATOR_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "../utils/Estimator.hh"

using namespace std;
#endif

namespace EstTools{
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ZnunuEstimator : public BaseEstimator {
public:
  ZnunuEstimator() {}
  ZnunuEstimator(TString outputdir, TString outputfile = "znunu_output.root") :
    BaseEstimator(outputdir, outputfile) {}
  ZnunuEstimator(const BaseConfig &config) :
    BaseEstimator(config) {}

  virtual ~ZnunuEstimator() {}

  Quantity calcRz(const TString &extraCutForNorm = ""){
    return calcRzRt(extraCutForNorm).first;
  }

  Quantity calcRt(const TString &extraCutForNorm = ""){
    return calcRzRt(extraCutForNorm).second;
  }

  pair<Quantity, Quantity> calcRzRt(const TString &extraCutForNorm = ""){
    cerr << "\n--->" << __func__ << ": " << extraCutForNorm << endl;

    TString extra = extraCutForNorm=="" ? "" : " && " + extraCutForNorm;

    auto doublelep_sample = zllcr_cfg.samples.at("doublelep");
    auto dyll_sample      = zllcr_cfg.samples.at("dyll");
    auto ttbar_sample     = zllcr_cfg.samples.at("ttbar");

    auto cat = zllcr_cfg.catMaps.at("on-z");
    auto cut = zllcr_cfg.sel + extra + " && " + cat.cut;
    auto data_peak = getYields(doublelep_sample.tree, doublelep_sample.wgtvar, cut + doublelep_sample.sel);
    auto dy_peak   = getYields(dyll_sample.tree, dyll_sample.wgtvar, cut + dyll_sample.sel);
    auto tt_peak   = getYields(ttbar_sample.tree, ttbar_sample.wgtvar, cut + ttbar_sample.sel);

    cat = zllcr_cfg.catMaps.at("off-z");
    cut = zllcr_cfg.sel + extra + " && " + cat.cut;
    auto data_off = getYields(doublelep_sample.tree, doublelep_sample.wgtvar, cut + doublelep_sample.sel);
    auto dy_off   = getYields(dyll_sample.tree, dyll_sample.wgtvar, cut + dyll_sample.sel);
    auto tt_off   = getYields(ttbar_sample.tree, ttbar_sample.wgtvar, cut + ttbar_sample.sel);

    auto z_sf = dileptonZtoLLScaleFactorHelper(data_peak, dy_peak, tt_peak, data_off, dy_off, tt_off);
    auto t_sf = dileptonTTbarScaleFactorHelper(data_peak, dy_peak, tt_peak, data_off, dy_off, tt_off);

    cout << fixed << setprecision(2);
    cout << "[ZLL SF]   " << " = " << z_sf << " PEAK: ---> dilep: " << data_peak << ", ttbar: " << tt_peak << ", dy: " << dy_peak << endl;
    cout << "[TTbar SF] " << " = " << t_sf << " OFF:  ---> dilep: " << data_off  << ", ttbar: " << tt_off  << ", dy: " << dy_off  << endl;

    return {z_sf, t_sf};
  }

  void calcSgamma(){

    pho_normScale.clear();
    cerr << "\n--->" << "Calc photon normalization factors..." << endl;
    auto photon_sample = config.samples.at("photon");
    auto singlepho_sample = config.samples.at("singlepho");
    for (const auto &norm : phocr_normMap){
      TString normCut = norm.second;
      // norm factor
      cout << " ... Photon norm cut " << normCut << endl;
      auto cut = addCuts({config.sel, normCut});
      auto mc_total = getYields(photon_sample.tree, photon_sample.wgtvar, cut + photon_sample.sel);
      auto data_total = getYields(singlepho_sample.tree, singlepho_sample.wgtvar, cut + singlepho_sample.sel);
      pho_normScale[norm.first] = data_total/mc_total;
      cout << "    ... norm factor ---> " << pho_normScale.at(norm.first) << endl;
    }

    yields["_phoNormScale"] = vector<Quantity>();
    for (auto &cat_name : config.categories){
      cerr << "\n--->" << __func__ << " " << cat_name << endl;
      // find norm category
      TString normKey = ""; // default to empty: no extra cut
      for (const auto &norm : phocr_normMap){
        if (cat_name.BeginsWith(norm.first)){
          normKey = norm.first;
        }
      }
      Quantity norm_factor(1, 0);
      if (normKey != ""){
        cout << " ... Using normalization from _" << normKey << "_" << endl;
        norm_factor = pho_normScale.at(normKey);
      }
      for (unsigned i=0; i<config.catMaps.at(cat_name).bin.nbins; ++i){
        yields["_phoNormScale"].emplace_back(norm_factor.value);
      }
    }

    auto data = yields.at("singlepho");
    Quantity::removeZeroes(data, 0.001, 1.8);
    yields["_photon-scaled"] = yields.at("_phoNormScale")*yields.at("photon");
    yields["_Sgamma"] = data / yields.at("_photon-scaled");
  }

  void pred(){

    cerr << "\n--->" << "Running Znunu prediction..." << endl << endl;

    // Yields
    calcYields();
    for (auto &q : yields.at("photon")){//FIXME
      if (q.value<0.0001){
        cerr << "MC yields <0.0001!" << endl;
        q.value = 0.0001;
        q.error = 0.0001;
      }
    }

    // Sgamma
    calcSgamma();

    // Rz
    zll_Rz.clear();
    yields["_Rz"] = vector<Quantity>();
    for (const auto &norm : zll_normMap){
      zll_Rz[norm.first] = calcRz(norm.second);
    }

    for (auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);
      for (unsigned ibin = 0; ibin < cat.bin.nbins; ++ibin){
        // find norm category
        for (const auto &norm : zll_normMap){
          if (cat_name.Contains(norm.first))
            yields["_Rz"].push_back(zll_Rz.at(norm.first));
        }
      }
    }

    yields["_TF"] = yields.at("znunu-sr") / yields.at("_photon-scaled") * yields.at("_Rz");

    yields["_pred"] = yields.at("znunu-sr") * yields.at("_Sgamma") * yields.at("_Rz");
    printVec(yields["_pred"], "Final prediction", true);

    cout << " ========== Info for Datacard ==========" << endl;
    {
      cout << "Extra weight on znunu [from Rz]:" << endl;
      bool isFirst = true;
      for (const auto &norm : zll_normMap){
        if(isFirst) {isFirst=false;}
        else cout << "+";
        cout << zll_Rz.at(norm.first).value << "*(" << norm.second << ")";
      }
      cout << endl;
    }

    {
      cout << "Extra weight on photon-mc [from Sgamma]:" << endl;
      bool isFirst = true;
      for (const auto &norm : phocr_normMap){
        if(isFirst) {isFirst=false;}
        else cout << "+";
        cout << pho_normScale.at(norm.first).value << "*(" << norm.second << ")";
      }
      cout << endl;
    }
    cout << " ==========      End Info     ==========" << endl;

  }

  void prepDatacard(){
    yields["_znunu-scaled"] = vector<Quantity>();
    for (unsigned i=0; i<yields.at("znunu-sr").size(); ++i){
      yields.at("_znunu-scaled").push_back( yields.at("znunu-sr").at(i) * yields.at("_Rz").at(i).value ); // discard Rz unc!
    }
    convertYields("_znunu-scaled",  "",       "znunu");
    convertYields("_photon-scaled", "phocr",  "phocr_gjets");
    convertYields("singlepho",      "phocr",  "phocr_data");
  }

  void writeRzUnc(std::string output){
    if (zll_normMap.empty()) { cout << "Need to run prediction first!" << endl; return; }

    cout << "Writing Rz unc to " << output << endl;

    ofstream outfile(output);
    for (const auto &rz : zll_Rz){
      outfile << "% " << rz.first << ": " << rz.second << endl;
    }
    for (const auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);
      TString uncName;
      double unc = 1;
      for (const auto &norm : zll_normMap){
        if (cat_name.Contains(norm.first)){
          auto rz = zll_Rz.at(norm.first);
          unc = 1+rz.error/rz.value;
          uncName = norm.first;
        }
      }

      for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
        auto xlow = toString(cat.bin.plotbins.at(ix), 0);
        auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
        auto binname = "bin_" + cat_name + "_" + cat.bin.var + xlow + "to" + xhigh;
        outfile << binname << "\t" << "znunu_rzunc_"+uncName << "\t" << "znunu" << "\t" << unc << endl;
      }
    }

    outfile.close();
  }

  void printTable(bool doLM) {
    Quantity::printStyle = Quantity::LATEX;

    int ibin = 0, ibin_nb2 = 0;
    for (const auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);
      if((doLM && (cat_name.Contains("highnj") || cat_name.Contains("medptb"))) || (!doLM && cat_name.Contains("nb2"))) {
        ibin += cat.bin.cuts.size();
        continue;
      }
      TString cat_name_nb2 = cat_name;
      if(!doLM) cat_name_nb2.ReplaceAll("nb1","nb2");
      else {
        cat_name_nb2.ReplaceAll("lownj","highnj");
        cat_name_nb2.ReplaceAll("lowptb","medptb");
      }
      cout << setw(30) << cat.label << endl;
      auto metlabels = convertBinRangesToLabels(cat.bin.plotbins, true);
      for (const auto &p : metlabels){
        if(cat_name.Contains("mtb0")) ibin_nb2 = ibin + 8;
        else if(cat_name.Contains("mtb175")) ibin_nb2 = ibin + 22;
        else ibin_nb2 = ibin + 4;
        const auto &sgamma_nb1 = yields["_Sgamma"].at(ibin);
        const auto &sgamma_nb2 = yields["_Sgamma"].at(ibin_nb2);
        const auto &znunumc_nb1 = yields["znunu-sr"].at(ibin);
        const auto &znunumc_nb2 = yields["znunu-sr"].at(ibin_nb2);
        const auto &pred_nb1 = yields["_pred"].at(ibin);
        const auto &pred_nb2 = yields["_pred"].at(ibin_nb2);
        cout << p << " & " << fixed << setprecision(2) << setw(0) << sgamma_nb1 << " & " << fixed << setprecision(2) << setw(10) << znunumc_nb1 << " & " << fixed << setprecision(2) << setw(10) << pred_nb1 << " & " << fixed << setprecision(2) << setw(10) << sgamma_nb2 << " & " << fixed << setprecision(2) << setw(10) << znunumc_nb2 << " & " << fixed << setprecision(2) << setw(10) << pred_nb2 << " \\\\" << endl;
       ibin++;
      }
    }

  }

  BaseConfig zllcr_cfg;
  std::map<TString, TString> zll_normMap; // Rz categories, e.g., nb0, nb1, nb2
  std::map<TString, TString> phocr_normMap; // Sgamma normalization cuts (normalize pho mc to data after baseline + extra cut, e.g., nlb0)

  std::map<TString, Quantity> zll_Rz; // zll normalization factors [Rz]
  std::map<TString, Quantity> pho_normScale; // photon MC normalization factors

};

}

#endif /*ESTTOOLS_ESTMETHODS_ZNUNUESTIMATOR_HH_*/
