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

  vector<Quantity> calcSLep2017(){
    // calculate correction factors from single lepton control regions

    cerr << "\n--->" << __func__ << endl;

    auto data = yields.at("singlelep-2017");
    Quantity::removeZeroes(data, 0.001, 1.8);
    auto mc   = yields.at("ttbarplusw-2017");

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

  void predComparison(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar",         "wjets"},         "ttbarplusw");
    sumYields({"ttbar-sr",      "wjets-sr"},      "ttbarplusw-sr");
    sumYields({"ttbar-2017",    "wjets-2017"},    "ttbarplusw-2017");
    sumYields({"ttbar-sr-2017", "wjets-sr-2017"}, "ttbarplusw-sr-2017");

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_SLep-2017"] = calcSLep2017(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]                        = yields.at("ttbarplusw-sr")     /yields.at("ttbarplusw");
    yields["_TF-2017"]                   = yields.at("ttbarplusw-sr-2017")/yields.at("ttbarplusw-2017");
    yields["_pred"]                      = yields.at("singlelep") * yields.at("_TF");
    yields["_pred-2017"]                 = yields.at("singlelep-2017") * yields.at("_TF-2017");
    yields["_TF_Comp"]			 = yields.at("_TF")/yields.at("_TF-2017");

    if(splitTF){
      //sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      sumYields({"ttbar-sr-int",      "wjets-sr-int"},      "ttbarplusw-sr-int");
      sumYields({"ttbar-sr-int-2017", "wjets-sr-int-2017"}, "ttbarplusw-sr-int-2017");
      yields["_TF_CR_to_SR_noextrap"]      = yields.at("ttbarplusw-sr-int")     /yields.at("ttbarplusw");
      yields["_TF_CR_to_SR_noextrap-2017"] = yields.at("ttbarplusw-sr-int-2017")/yields.at("ttbarplusw-2017");
      yields["_TF_CR_to_SR_noextrap_Comp"] = yields.at("_TF_CR_to_SR_noextrap") /yields.at("_TF_CR_to_SR_noextrap-2017");
      yields["_TF_SR_extrap"]              = yields.at("ttbarplusw-sr")         /yields.at("ttbarplusw-sr-int");
      yields["_TF_SR_extrap-2017"]         = yields.at("ttbarplusw-sr-2017")    /yields.at("ttbarplusw-sr-int-2017");
      yields["_TF_SR_extrap_Comp"]	   = yields.at("_TF_SR_extrap")         /yields.at("_TF_SR_extrap-2017");
      std::cout << std::endl;
      std::cout << "_TF_SR_extrap-2017: " << yields["_TF_SR_extrap-2017"] << std::endl;
      std::cout << std::endl;
      std::cout << "yields for _TF_SR_extrap-2017: " << std::endl;
      std::cout << yields.at("ttbarplusw-sr-2017") << "/" << std::endl;
      std::cout << yields.at("ttbarplusw-sr-int-2017") << std::endl;
      std::cout << std::endl;
      //sumYields({"ttbar-sr-int-2017", "wjets-sr-int-2017", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int-2017");
    }

    printVec(yields["_pred"], "Final prediction", true);
    printVec(yields["_pred-2017"], "Final prediction-2017", true);
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
  bool isValidate = false;
};


}

#endif /*ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_*/
