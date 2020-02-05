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

  vector<Quantity> calcSLepEra(TString era = ""){
    // calculate correction factors from single lepton control regions

    cerr << "\n--->" << __func__ << endl;

    auto data = yields.at("singlelep-" + era);
    Quantity::removeZeroes(data, 0.001, 1.8);
    auto mc   = yields.at("ttbarplusw-" + era);

    auto s_lep = data / mc;
    cout << "    ---> " << s_lep << endl;
    return s_lep;

  }

  void predYear(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    if(doLepSyst){
      sumYields({"ttbar-event-sr", "wjets-event-sr", "tW-event-sr", "ttW-event-sr"}, "ttbarplusw-event-sr");
      sumYields({"ttbar-eventsf-sr", "wjets-eventsf-sr", "tW-eventsf-sr", "ttW-eventsf-sr"}, "ttbarplusw-eventsf-sr");
      yields["lepSF_"] = (yields.at("ttbarplusw-sr") + (yields.at("ttbarplusw-event-sr") - yields.at("ttbarplusw-eventsf-sr")))/yields.at("ttbarplusw-sr"); 
    }


    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    if(doLepSyst) yields["_TF"]     = yields.at("lepSF_")*yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    else          yields["_TF"]     = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    if(splitTF){
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");
    }

    printVec(yields["_pred"], "Final prediction", true);
  }

  void predYearlep(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    sumYields({"ttbar-event-sr", "wjets-event-sr", "tW-event-sr", "ttW-event-sr"}, "ttbarplusw-event-sr");
    sumYields({"ttbar-eventsf-sr", "wjets-eventsf-sr", "tW-eventsf-sr", "ttW-eventsf-sr"}, "ttbarplusw-eventsf-sr");
    yields["lepSF_"] = (yields.at("ttbarplusw-sr") + (yields.at("ttbarplusw-event-sr") - yields.at("ttbarplusw-eventsf-sr")))/yields.at("ttbarplusw-sr"); 


    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]     = yields.at("lepSF_")*yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    if(splitTF){
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");
    }

    printVec(yields["_pred"], "Final prediction", true);
  }

  void pred(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar-2016", "ttbar-2017", "ttbar-2018"}, "ttbar");
    sumYields({"wjets-2016", "wjets-2017", "wjets-2018"}, "wjets");
    sumYields({"tW-2016", "tW-2017", "tW-2018"}, "tW");
    sumYields({"ttW-2016", "ttW-2017", "ttW-2018"}, "ttW");
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");

    sumYields({"ttbar-2016-sr", "ttbar-2017-sr", "ttbar-2018-sr"}, "ttbar-sr");
    sumYields({"wjets-2016-sr", "wjets-2017-sr", "wjets-2018-sr"}, "wjets-sr");
    sumYields({"tW-2016-sr", "tW-2017-sr", "tW-2018-sr"}, "tW-sr");
    sumYields({"ttW-2016-sr", "ttW-2017-sr", "ttW-2018-sr"}, "ttW-sr");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    sumYields({"ttZ-2016-sr", "ttZ-2017-sr", "ttZ-2018-sr"}, "ttZ-sr");
    sumYields({"diboson-2016-sr", "diboson-2017-sr", "diboson-2018-sr"}, "diboson-sr");

    if(doLepSyst){
      sumYields({"ttbar-2016-event-sr", "ttbar-2017-event-sr", "ttbar-2018-event-sr"}, "ttbar-event-sr");
      sumYields({"wjets-2016-event-sr", "wjets-2017-event-sr", "wjets-2018-event-sr"}, "wjets-event-sr");
      sumYields({"tW-2016-event-sr", "tW-2017-event-sr", "tW-2018-event-sr"}, "tW-event-sr");
      sumYields({"ttW-2016-event-sr", "ttW-2017-event-sr", "ttW-2018-event-sr"}, "ttW-event-sr");
      sumYields({"ttbar-event-sr", "wjets-event-sr", "tW-event-sr", "ttW-event-sr"}, "ttbarplusw-event-sr");

      sumYields({"ttZ-2016-event-sr", "ttZ-2017-event-sr", "ttZ-2018-event-sr"}, "ttZ-event-sr");
      sumYields({"diboson-2016-event-sr", "diboson-2017-event-sr", "diboson-2018-event-sr"}, "diboson-event-sr");
      
      sumYields({"ttbar-2016-eventsf-sr", "ttbar-2017-eventsf-sr", "ttbar-2018-eventsf-sr"}, "ttbar-eventsf-sr");
      sumYields({"wjets-2016-eventsf-sr", "wjets-2017-eventsf-sr", "wjets-2018-eventsf-sr"}, "wjets-eventsf-sr");
      sumYields({"tW-2016-eventsf-sr", "tW-2017-eventsf-sr", "tW-2018-eventsf-sr"}, "tW-eventsf-sr");
      sumYields({"ttW-2016-eventsf-sr", "ttW-2017-eventsf-sr", "ttW-2018-eventsf-sr"}, "ttW-eventsf-sr");
      sumYields({"ttbar-eventsf-sr", "wjets-eventsf-sr", "tW-eventsf-sr", "ttW-eventsf-sr"}, "ttbarplusw-eventsf-sr");

      sumYields({"ttZ-2016-eventsf-sr", "ttZ-2017-eventsf-sr", "ttZ-2018-eventsf-sr"}, "ttZ-eventsf-sr");
      sumYields({"diboson-2016-eventsf-sr", "diboson-2017-eventsf-sr", "diboson-2018-eventsf-sr"}, "diboson-eventsf-sr");
      yields["lepSF_"] = (yields.at("ttbarplusw-sr") + (yields.at("ttbarplusw-event-sr") - yields.at("ttbarplusw-eventsf-sr")))/yields.at("ttbarplusw-sr"); 
    }

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    if(doLepSyst) yields["_TF"]     = yields.at("lepSF_")*yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    else          yields["_TF"]     = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    if(splitTF){
      sumYields({"ttbar-2016-sr-int", "ttbar-2017-sr-int", "ttbar-2018-sr-int"}, "ttbar-sr-int");
      sumYields({"wjets-2016-sr-int", "wjets-2017-sr-int", "wjets-2018-sr-int"}, "wjets-sr-int");
      sumYields({"tW-2016-sr-int", "tW-2017-sr-int", "tW-2018-sr-int"}, "tW-sr-int");
      sumYields({"ttW-2016-sr-int", "ttW-2017-sr-int", "ttW-2018-sr-int"}, "ttW-sr-int");
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");
    }

    printVec(yields["_pred"], "Final prediction", true);
  }

  void predlep(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar-2016", "ttbar-2017", "ttbar-2018"}, "ttbar");
    sumYields({"wjets-2016", "wjets-2017", "wjets-2018"}, "wjets");
    sumYields({"tW-2016", "tW-2017", "tW-2018"}, "tW");
    sumYields({"ttW-2016", "ttW-2017", "ttW-2018"}, "ttW");
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");

    sumYields({"ttbar-2016-sr", "ttbar-2017-sr", "ttbar-2018-sr"}, "ttbar-sr");
    sumYields({"wjets-2016-sr", "wjets-2017-sr", "wjets-2018-sr"}, "wjets-sr");
    sumYields({"tW-2016-sr", "tW-2017-sr", "tW-2018-sr"}, "tW-sr");
    sumYields({"ttW-2016-sr", "ttW-2017-sr", "ttW-2018-sr"}, "ttW-sr");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    sumYields({"ttZ-2016-sr", "ttZ-2017-sr", "ttZ-2018-sr"}, "ttZ-sr");
    sumYields({"diboson-2016-sr", "diboson-2017-sr", "diboson-2018-sr"}, "diboson-sr");

    sumYields({"ttbar-2016-event-sr", "ttbar-2017-event-sr", "ttbar-2018-event-sr"}, "ttbar-event-sr");
    sumYields({"wjets-2016-event-sr", "wjets-2017-event-sr", "wjets-2018-event-sr"}, "wjets-event-sr");
    sumYields({"tW-2016-event-sr", "tW-2017-event-sr", "tW-2018-event-sr"}, "tW-event-sr");
    sumYields({"ttW-2016-event-sr", "ttW-2017-event-sr", "ttW-2018-event-sr"}, "ttW-event-sr");
    sumYields({"ttbar-event-sr", "wjets-event-sr", "tW-event-sr", "ttW-event-sr"}, "ttbarplusw-event-sr");

    sumYields({"ttZ-2016-event-sr", "ttZ-2017-event-sr", "ttZ-2018-event-sr"}, "ttZ-event-sr");
    sumYields({"diboson-2016-event-sr", "diboson-2017-event-sr", "diboson-2018-event-sr"}, "diboson-event-sr");
    
    sumYields({"ttbar-2016-eventsf-sr", "ttbar-2017-eventsf-sr", "ttbar-2018-eventsf-sr"}, "ttbar-eventsf-sr");
    sumYields({"wjets-2016-eventsf-sr", "wjets-2017-eventsf-sr", "wjets-2018-eventsf-sr"}, "wjets-eventsf-sr");
    sumYields({"tW-2016-eventsf-sr", "tW-2017-eventsf-sr", "tW-2018-eventsf-sr"}, "tW-eventsf-sr");
    sumYields({"ttW-2016-eventsf-sr", "ttW-2017-eventsf-sr", "ttW-2018-eventsf-sr"}, "ttW-eventsf-sr");
    sumYields({"ttbar-eventsf-sr", "wjets-eventsf-sr", "tW-eventsf-sr", "ttW-eventsf-sr"}, "ttbarplusw-eventsf-sr");

    sumYields({"ttZ-2016-eventsf-sr", "ttZ-2017-eventsf-sr", "ttZ-2018-eventsf-sr"}, "ttZ-eventsf-sr");
    sumYields({"diboson-2016-eventsf-sr", "diboson-2017-eventsf-sr", "diboson-2018-eventsf-sr"}, "diboson-eventsf-sr");
    yields["lepSF_"] = (yields.at("ttbarplusw-sr") + (yields.at("ttbarplusw-event-sr") - yields.at("ttbarplusw-eventsf-sr")))/yields.at("ttbarplusw-sr"); 
    cout << "lepSF: " << yields["lepSF_"] << endl;

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]     = yields.at("lepSF_")*yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    if(splitTF){
      sumYields({"ttbar-2016-sr-int", "ttbar-2017-sr-int", "ttbar-2018-sr-int"}, "ttbar-sr-int");
      sumYields({"wjets-2016-sr-int", "wjets-2017-sr-int", "wjets-2018-sr-int"}, "wjets-sr-int");
      sumYields({"tW-2016-sr-int", "tW-2017-sr-int", "tW-2018-sr-int"}, "tW-sr-int");
      sumYields({"ttW-2016-sr-int", "ttW-2017-sr-int", "ttW-2018-sr-int"}, "ttW-sr-int");
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");
    }

    printVec(yields["_pred"], "Final prediction", true);
  }

  void predSeparate(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar-2016", "ttbar-2017", "ttbar-2018"}, "ttbar");
    sumYields({"wjets-2016", "wjets-2017", "wjets-2018"}, "wjets");
    sumYields({"tW-2016", "tW-2017", "tW-2018"}, "tW");
    sumYields({"ttW-2016", "ttW-2017", "ttW-2018"}, "ttW");
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");

    sumYields({"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"}, "ttbarplusw-2016");
    sumYields({"ttbar-2017", "wjets-2017", "tW-2017", "ttW-2017"}, "ttbarplusw-2017");
    sumYields({"ttbar-2018", "wjets-2018", "tW-2018", "ttW-2018"}, "ttbarplusw-2018");

    sumYields({"ttbar-2016-sr", "ttbar-2017-sr", "ttbar-2018-sr"}, "ttbar-sr");
    sumYields({"wjets-2016-sr", "wjets-2017-sr", "wjets-2018-sr"}, "wjets-sr");
    sumYields({"tW-2016-sr", "tW-2017-sr", "tW-2018-sr"}, "tW-sr");
    sumYields({"ttW-2016-sr", "ttW-2017-sr", "ttW-2018-sr"}, "ttW-sr");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");

    sumYields({"ttbar-2016-sr", "wjets-2016-sr", "tW-2016-sr", "ttW-2016-sr"}, "ttbarplusw-2016-sr");
    sumYields({"ttbar-2017-sr", "wjets-2017-sr", "tW-2017-sr", "ttW-2017-sr"}, "ttbarplusw-2017-sr");
    sumYields({"ttbar-2018-sr", "wjets-2018-sr", "tW-2018-sr", "ttW-2018-sr"}, "ttbarplusw-2018-sr");

    sumYields({"ttZ-2016-sr", "ttZ-2017-sr", "ttZ-2018-sr"}, "ttZ-sr");
    sumYields({"diboson-2016-sr", "diboson-2017-sr", "diboson-2018-sr"}, "diboson-sr");

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]                   = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");

    yields["_SLep-2016"] = calcSLepEra("2016");
    yields["_TF-2016"]              = yields.at("ttbarplusw-2016-sr")/yields.at("ttbarplusw-2016");
    yields["_pred-2016"]            = yields.at("singlelep-2016") * yields.at("_TF-2016");

    yields["_SLep-2017"] = calcSLepEra("2017");
    yields["_TF-2017"]              = yields.at("ttbarplusw-2017-sr")/yields.at("ttbarplusw-2017");
    yields["_pred-2017"]            = yields.at("singlelep-2017") * yields.at("_TF-2017");

    yields["_SLep-2018"] = calcSLepEra("2018");
    yields["_TF-2018"]              = yields.at("ttbarplusw-2018-sr")/yields.at("ttbarplusw-2018");
    yields["_pred-2018"]            = yields.at("singlelep-2018") * yields.at("_TF-2018");

    if(splitTF){
      sumYields({"ttbar-2016-sr-int", "ttbar-2017-sr-int", "ttbar-2018-sr-int"}, "ttbar-sr-int");
      sumYields({"wjets-2016-sr-int", "wjets-2017-sr-int", "wjets-2018-sr-int"}, "wjets-sr-int");
      sumYields({"tW-2016-sr-int", "tW-2017-sr-int", "tW-2018-sr-int"}, "tW-sr-int");
      sumYields({"ttW-2016-sr-int", "ttW-2017-sr-int", "ttW-2018-sr-int"}, "ttW-sr-int");
      sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");
      yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
      yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");

      sumYields({"ttbar-2016-sr-int", "wjets-2016-sr-int", "tW-2016-sr-int", "ttW-2016-sr-int"}, "ttbarplusw-2016-sr-int");
      sumYields({"ttbar-2017-sr-int", "wjets-2017-sr-int", "tW-2017-sr-int", "ttW-2017-sr-int"}, "ttbarplusw-2017-sr-int");
      sumYields({"ttbar-2018-sr-int", "wjets-2018-sr-int", "tW-2018-sr-int", "ttW-2018-sr-int"}, "ttbarplusw-2018-sr-int");
      yields["_TF_CR_to_SR_noextrap-2016"] = yields.at("ttbarplusw-2016-sr-int")/yields.at("ttbarplusw-2016");
      yields["_TF_SR_extrap-2016"]         = yields.at("ttbarplusw-2016-sr")/yields.at("ttbarplusw-2016-sr-int");

      yields["_TF_CR_to_SR_noextrap-2017"] = yields.at("ttbarplusw-2017-sr-int")/yields.at("ttbarplusw-2017");
      yields["_TF_SR_extrap-2017"]         = yields.at("ttbarplusw-2017-sr")/yields.at("ttbarplusw-2017-sr-int");

      yields["_TF_CR_to_SR_noextrap-2018"] = yields.at("ttbarplusw-2018-sr-int")/yields.at("ttbarplusw-2018");
      yields["_TF_SR_extrap-2018"]         = yields.at("ttbarplusw-2018-sr")/yields.at("ttbarplusw-2018-sr-int");
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
  bool doLepSyst = false;
  bool data2018 = false;
};


}

#endif /*ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_*/
