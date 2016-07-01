#ifndef ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_
#define ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "../utils/Estimator.hh"
#include "../utils/HistGetter.hh"

using namespace std;
#endif

namespace EstTools{

class QCDEstimator : public BaseEstimator {
public:
  QCDEstimator() {}
  QCDEstimator(TString outputdir, TString outputfile = "QCD_output.root") :
    BaseEstimator(outputdir, outputfile) {}
  QCDEstimator(const BaseConfig &config) :
    BaseEstimator(config) {}

  virtual ~QCDEstimator() {}

  void naiveTF(){
    yields["_NaiveTF"] = yields.at("qcd-sr-withveto") / yields.at("qcd-cr-withveto");
  }

  void calcTF(){
    // calculate transfer factors

    cerr << "\n--->" << __func__ << endl;

    if (!runBootstrapping){
      cerr << "... Do NOT run bootstrapping ..." << endl;
      yields["_TF"] = yields.at("qcd-sr") / yields.at("qcd-cr");
      return;
    }

    cerr << "... Running bootstrapping ..." << endl;

    std::vector<Quantity> transfer_factors;

    auto qcd = config.samples.at("qcd-sr");
    auto qcdcr = config.samples.at("qcd-cr");

    for (auto &cat_name : config.categories){
      cerr << cat_name << endl;

      const auto & cat = config.catMaps.at(cat_name);
      const auto & crcat = config.crCatMaps.at(cat_name);
      auto SRsel = config.sel + " && " + cat.cut + qcd.sel;
      auto CRsel = config.sel + " && " + crcat.cut + qcdcr.sel;

      cerr << "SRsel: " << SRsel << endl;
      cerr << "CRsel: " << CRsel << endl;

      auto metGetter = HistogramGetter(cat.bin.var, cat.bin.var, cat.bin.label, cat.bin.nbins, cat.bin.plotbins.data());
      metGetter.setNBS(50);
      auto nom = metGetter.getTFAndCov(qcd.tree, SRsel, qcd.wgtvar, CRsel, qcdcr.wgtvar, "TF_"+cat.name);

      for (int ibin=1; ibin<=nom->GetNbinsX(); ++ibin){
        auto tf = getHistBin(nom, ibin);
        if (tf.error>tf.value) tf.error = tf.value;
        transfer_factors.push_back(tf);
        cout << tf << endl;
      }
    }

    yields["_TF"] = transfer_factors;

  }

  void calcDataCorr(){

    cerr << "\n--->" << __func__ << endl;

    vector<TString> otherbkg_samples = {"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr"};
    vector<TString> norm_samples = {"ttbar-norm", "wjets-norm", "tW-norm", "ttW-norm", "qcd-norm"};
    calcYieldsExcludes(norm_samples);
    sumYields(otherbkg_samples, "non-qcd");
    yields["otherbkgs-noznunu"] = yields.at("non-qcd");

    yields["_SubNormCorr"] = std::vector<Quantity>();
    unsigned ibin = 0;
    for (auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);

      auto samp = config.samples.at("data-norm");
      auto norm_datayield = getYields(samp.tree, samp.wgtvar, config.sel + " && " + cat.cut + samp.sel);
      Quantity norm_bkgtotal(0, 0);
      for (auto &s : norm_samples){
        samp = config.samples.at(s);
        norm_bkgtotal = norm_bkgtotal + getYields(samp.tree, samp.wgtvar, config.sel + " && " + cat.cut + samp.sel);
      }
      Quantity norm_factor = norm_datayield / norm_bkgtotal;
      cerr << endl << "~~~" << cat_name << ": data(norm) = " << norm_datayield << ", total bkg (norm) = " << norm_bkgtotal << endl << endl;

      for (auto &c : cat.bin.cuts){
        yields.at("_SubNormCorr").push_back(norm_factor);
        yields.at("otherbkgs-noznunu").at(ibin) = yields.at("otherbkgs-noznunu").at(ibin) * norm_factor;
        ++ibin;
      }
    }

    yields["otherbkgs"] = yields.at("otherbkgs-noznunu") + yields.at("znunu-cr");

    auto vdata = yields.at("data-cr");
    Quantity::removeZeroes(vdata);

    yields["_DataCorr"] = std::vector<Quantity>();
    yields["_DATA"] = std::vector<Quantity>();
    for (unsigned i=0; i<vdata.size(); ++i){
      double otherVal = yields.at("otherbkgs").at(i).value;
      double dataVal = vdata.at(i).value;
      if (dataVal<10) dataVal = yields.at("qcd-cr-withveto").at(i).value + otherVal;
      double sub = otherVal/dataVal;
      Quantity corr(1-sub, sub*(1-sub)); // 100% unc on the subtraction: FIXME?
      yields.at("_DataCorr").push_back(corr);
      yields.at("_DATA").push_back(vdata.at(i) * corr);
    }

  }

  void pred(){
    cerr << "\n--->" << "Running QCD prediction..." << endl << endl;

    calcDataCorr();
    calcTF();

    yields["_pred"] = yields.at("_DATA") * yields.at("_TF");
    printVec(yields["_pred"], "QCD prediction", true);

  }


  // whether run bootstrapping for QCD uncertainty or not
  bool runBootstrapping = true;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


}

#endif /*ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_*/
