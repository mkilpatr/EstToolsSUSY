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
    cerr << "\n--->" << __func__ << endl;

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

  vector<Quantity> calcSgamma(const Category& cat, TString extraCutForNorm = ""){

    cerr << "\n--->" << __func__ << " " << cat.name << endl;

    TString extra = extraCutForNorm=="" ? "" : " && " + extraCutForNorm;

    auto photon_sample = config.samples.at("photon");
    auto singlepho_sample = config.samples.at("singlepho");

    // norm factor
    auto mc_total = getYields(photon_sample.tree, photon_sample.wgtvar, config.sel + extra + photon_sample.sel);
    auto data_total = getYields(singlepho_sample.tree, singlepho_sample.wgtvar, config.sel + extra + singlepho_sample.sel);
    auto norm_factor = (data_total/mc_total).value;

    auto cut = config.sel + " && " + cat.cut;
    auto mc   = getYieldVector(photon_sample.tree,    photon_sample.wgtvar,    cut + photon_sample.sel,    cat.bin);
    auto data = getYieldVector(singlepho_sample.tree, singlepho_sample.wgtvar, cut + singlepho_sample.sel, cat.bin);

    Quantity::removeZeroes(data, 0.001, 1.8);

    auto s_gamma = data / (mc * norm_factor);
    cout << "    ... norm factor ---> " << norm_factor << endl;
    cout << "    ... sgamma ---> " << s_gamma << endl;
    return s_gamma;

  }

  void pred(){

    cerr << "\n--->" << "Running Znunu prediction..." << endl << endl;

    // Yields
    calcYields();

    // Sgamma
    yields["_Sgamma"] = vector<Quantity>();
    for (auto &cat_name : config.categories){
      // find norm category
      TString normCut = ""; // default to empty: no extra cut
      for (const auto &norm : phocr_normMap){
        if (cat_name.Contains(norm.first))
          normCut = norm.second;
      }
      const auto & cat = config.catMaps.at(cat_name);
      auto sgamma = calcSgamma(config.crCatMaps.at(cat_name), normCut);
      assert(sgamma.size()==1 || sgamma.size()==cat.bin.nbins); // FIXME: only handle size==1 and same size now
      for (unsigned ibin = 0; ibin < cat.bin.nbins; ++ibin){
        yields["_Sgamma"].push_back(sgamma.at( ibin%sgamma.size() ));
      }
    }

    // Rz
    yields["_Rz"] = vector<Quantity>();
    map<TString, Quantity> rzs;
    for (const auto &norm : zll_normMap){
      rzs[norm.first] = calcRz(norm.second);
    }

    for (auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);
      for (unsigned ibin = 0; ibin < cat.bin.nbins; ++ibin){
        // find norm category
        for (const auto &norm : zll_normMap){
          if (cat_name.Contains(norm.first))
            yields["_Rz"].push_back(rzs.at(norm.first));
        }
      }
    }

    yields["_pred"] = yields.at("znunu-sr") * yields.at("_Sgamma") * yields.at("_Rz");
    printVec(yields["_pred"], "Final prediction", true);

  }

  BaseConfig zllcr_cfg;
  std::map<TString, TString> zll_normMap; // Rz categories, e.g., nb0, nb1, nb2
  std::map<TString, TString> phocr_normMap; // Sgamma normalization cuts (normalize pho mc to data after baseline + extra cut, e.g., nlb0)

};

}

#endif /*ESTTOOLS_ESTMETHODS_ZNUNUESTIMATOR_HH_*/
