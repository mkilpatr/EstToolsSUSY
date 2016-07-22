#ifndef ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_
#define ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "../utils/Estimator.hh"

using namespace std;
#endif

namespace EstTools{

class LLBEstimator : public BaseEstimator {
public:
  LLBEstimator() {}
  LLBEstimator(TString outputdir, TString outputfile = "LLB_output.root") :
    BaseEstimator(outputdir, outputfile) {}
  LLBEstimator(const BaseConfig &config) :
    BaseEstimator(config) {}

  virtual ~LLBEstimator() {}

  vector<Quantity> calcSLep(){
    // calculate correction factors from single lepton control regions

    cerr << "\n--->" << __func__ << endl;

    auto data = yields.at("singlelep");
    Quantity::removeZeroes(data, 0.001, 1.8);
    auto mc   = yields.at("ttbarplusw");

    auto s_lep = data / mc;
    cout << "    ---> " << s_lep << endl;
    return s_lep;

  }

  void pred(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    yields["_SLep"] = calcSLep();
    yields["_TF"] = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");

    yields["_pred"] = yields.at("singlelep") * yields.at("_TF");
    printVec(yields["_pred"], "Final prediction", true);

  }

};


}

#endif /*ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_*/
