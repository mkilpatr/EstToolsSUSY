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

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]                   = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    if(splitTF){
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");
    }

    printVec(yields["_pred"], "Final prediction", true);
  }

  void predAllEras(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar-2016", "ttbar-2017RunBtoE", "ttbar-2017RunF", "ttbar-2018preHEM", "ttbar-2018postHEM"}, "ttbar");
    sumYields({"wjets-2016", "wjets-2017RunBtoE", "wjets-2017RunF", "wjets-2018preHEM", "wjets-2018postHEM"}, "wjets");
    sumYields({"tW-2016", "tW-2017RunBtoE", "tW-2017RunF", "tW-2018preHEM", "tW-2018postHEM"}, "tW");
    sumYields({"ttW-2016", "ttW-2017RunBtoE", "ttW-2017RunF", "ttW-2018preHEM", "ttW-2018postHEM"}, "ttW");
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");

    sumYields({"ttbar-2016-sr", "ttbar-2017RunBtoE-sr", "ttbar-2017RunF-sr", "ttbar-2018preHEM-sr", "ttbar-2018postHEM-sr"}, "ttbar-sr");
    sumYields({"wjets-2016-sr", "wjets-2017RunBtoE-sr", "wjets-2017RunF-sr", "wjets-2018preHEM-sr", "wjets-2018postHEM-sr"}, "wjets-sr");
    sumYields({"tW-2016-sr", "tW-2017RunBtoE-sr", "tW-2017RunF-sr", "tW-2018preHEM-sr", "tW-2018postHEM-sr"}, "tW-sr");
    sumYields({"ttW-2016-sr", "ttW-2017RunBtoE-sr", "ttW-2017RunF-sr", "ttW-2018preHEM-sr", "ttW-2018postHEM-sr"}, "ttW-sr");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    sumYields({"ttZ-2016-sr", "ttZ-2017RunBtoE-sr", "ttZ-2017RunF-sr", "ttZ-2018preHEM-sr", "ttZ-2018postHEM-sr"}, "ttZ-sr");
    sumYields({"diboson-2016-sr", "diboson-2017RunBtoE-sr", "diboson-2017RunF-sr", "diboson-2018preHEM-sr", "diboson-2018postHEM-sr"}, "diboson-sr");

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]                   = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    if(splitTF){
      sumYields({"ttbar-2016-sr-int", "ttbar-2017RunBtoE-sr-int", "ttbar-2017RunF-sr-int", "ttbar-2018preHEM-sr-int", "ttbar-2018postHEM-sr-int"}, "ttbar-sr-int");
      sumYields({"wjets-2016-sr-int", "wjets-2017RunBtoE-sr-int", "wjets-2017RunF-sr-int", "wjets-2018preHEM-sr-int", "wjets-2018postHEM-sr-int"}, "wjets-sr-int");
      sumYields({"tW-2016-sr-int", "tW-2017RunBtoE-sr-int", "tW-2017RunF-sr-int", "tW-2018preHEM-sr-int", "tW-2018postHEM-sr-int"}, "tW-sr-int");
      sumYields({"ttW-2016-sr-int", "ttW-2017RunBtoE-sr-int", "ttW-2017RunF-sr-int", "ttW-2018preHEM-sr-int", "ttW-2018postHEM-sr-int"}, "ttW-sr-int");
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");
    }

    printVec(yields["_pred"], "Final prediction", true);
  }

  void prepDatacard(){
    convertYields("ttbarplusw-sr",  "",       "ttbarplusw");
    convertYields("ttbarplusw",     "lepcr",  "lepcr_ttbarplusw");
    convertYields("singlelep",      "lepcr",  "lepcr_data");
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

  // whether to split TF when making prediction tables
  bool splitTF = false;
  bool data2018 = false;
};


}

#endif /*ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_*/
