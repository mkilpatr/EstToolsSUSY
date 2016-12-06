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
        const auto &data_nb1 = yields["singlelep"].at(ibin);
        const auto &data_nb2 = yields["singlelep"].at(ibin_nb2);
        const auto &tf_nb1 = yields["_TF"].at(ibin);
        const auto &tf_nb2 = yields["_TF"].at(ibin_nb2);
        const auto &pred_nb1 = yields["_pred"].at(ibin);
        const auto &pred_nb2 = yields["_pred"].at(ibin_nb2);
        cout << p << " & " << fixed << setprecision(0) << setw(0) << data_nb1.value << " & " << fixed << setprecision(2) << setw(10) << tf_nb1 << " & " << fixed << setprecision(2) << setw(10) << pred_nb1 << " & " << fixed << setprecision(0) << setw(10) << data_nb2 << " & " << fixed << setprecision(2) << setw(10) << tf_nb2 << " & " << fixed << setprecision(2) << setw(10) << pred_nb2 << " \\\\" << endl;
       ibin++;
      }
    }

  }


};


}

#endif /*ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_*/
