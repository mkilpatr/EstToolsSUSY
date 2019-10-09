#include "../EstMethods/QCDEstimator.hh"

//#include "SRParameters.hh"
#include "2016/SRParameters_2016_qcdsmall.hh"

using namespace EstTools;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> QCDPred(){
  auto config = qcdConfig();

  QCDEstimator z(config);

  z.runBootstrapping = true;
  z.splitTF = SPLITTF;

  //z.pred();
  z.pred2016();
  z.naiveTF();
  z.printYields();

  std::map<TString,int> digits;
  digits["_DATA"] = 0; // indicate it's data for proper formatting
  digits["_QCDTF_CR_to_SR_noextrap"] = -3;
  digits["_QCDTF_SR_extrap"] = -3;

  z.printYieldsTableLatex({"_DATA", "_TF", "_pred"}, labelMap, "yields_qcd_lm.tex","lm", digits); //LM
  if(z.splitTF){
    z.printYieldsTableLatex({"_DATA", "_TF", "_QCDTF_CR_to_SR_noextrap", "_QCDTF_SR_extrap", "_pred"}, labelMap, "yields_qcd_hm.tex","hm", digits);
  }else{
    z.printYieldsTableLatex({"_DATA", "_TF", "_pred"}, labelMap, "yields_qcd_hm.tex","hm", digits);
  }

  return z.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotQCDCR2016(){
  auto config = qcdConfig();
  config.catMaps = config.crCatMaps;

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  z.plotDataMC({"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr", "znunu-cr", "qcd-withveto-cr"}, "data-cr", false);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotQCDCR(){
  auto config = qcdConfig();
  config.catMaps = config.crCatMaps;

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016-cr", "ttbar-2017RunBtoE-cr", "ttbar-2017RunF-cr", "ttbar-2018preHEM-cr", "ttbar-2018postHEM-cr", "wjets-2016-cr", "wjets-2017RunBtoE-cr", "wjets-2017RunF-cr", "wjets-2018preHEM-cr", "wjets-2018postHEM-cr",
				"tW-2016-cr", "tW-2017RunBtoE-cr", "tW-2017RunF-cr", "tW-2018preHEM-cr", "tW-2018postHEM-cr", "ttW-2016-cr", "ttW-2017RunBtoE-cr", "ttW-2017RunF-cr", "ttW-2018preHEM-cr", "ttW-2018postHEM-cr",
				"znunu-2016-cr", "znunu-2017RunBtoE-cr", "znunu-2017RunF-cr", "znunu-2018preHEM-cr", "znunu-2018postHEM-cr", "qcd-2016-withveto-cr", "qcd-2017RunBtoE-withveto-cr", "qcd-2017RunF-withveto-cr", "qcd-2018preHEM-withveto-cr", "qcd-2018postHEM-withveto-cr"};

  z.plotDataMC(mc_samples, "data-cr", false);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotQCDInclusive(){
  auto config = qcdConfig();
  //BaseEstimator z(config);

  vector<TString> mc_samples = {"qcd-cr", "ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr", "znunu-cr"};
  TString data_sample = "data-cr";

  map<TString, BinInfo> varDict {
    //{"met",       BinInfo("MET_pt", "#slash{E}_{T}", 16, 0, 800, "GeV")},
    //{"ht",        BinInfo("Stop0l_HT",  "H_{T}", 100, 0, 2000, "GeV")},
    {"njets",     BinInfo("Stop0l_nJets", "N_{j}", 12, -0.5, 11.5)},
  };

  TString QCDCR    = "1 == 1";
  TString QCDCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10";
  TString QCDCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1";
  config.sel = baseline + " && Stop0l_nJets >= 2";
  
  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();
  
  BaseEstimator z(config.outputdir);
  z.setConfig(config);
  
  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    z.resetSelection();
    z.setSelection(QCDCR, "qcdcr", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("QCDCR N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(QCDCR_LM, "qcdcr_lm", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("QCDCR LM N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(QCDCR_HM, "qcdcr_hm", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("QCDCR HM N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
