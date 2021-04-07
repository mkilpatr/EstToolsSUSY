#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"

using namespace EstTools;

void srYields(){

  auto config = sigConfig();
  config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("ttbar-sr",       "t#bar{t}",      "ttbar",        lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "wjets",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "t#bar{t}W",           "ttW",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("qcd-sr",         "QCD",           "qcd",    lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu-sr",       "znunu",         "znunu",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T1tttt-sr",	     "T1tttt(2000, 100)", "T1tttt_2000_100", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("T2tt_850_100-sr","T2tt(850, 100)","T2tt_850_100", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("T2tt_500_325-sr","T2tt(500, 325)","T2tt_500_325", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);


  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["Total BKG"] = -3;
  digits["T1tttt-sr"] = -3;
  digits["T2tt_850_100-sr"] = -3;
  digits["T2tt_500_325-sr"] = -3;

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"});
  z.printYieldsTableLatex({"Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"}, labelMap, "yields_llb_hm_raw.tex", "hm", digits);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotHtoTaus(){
  auto config = sigConfig();
  //TString baseline_plus = "nJets30 >=2 && SVFit_Pt > 100 && JetTau_dijetMass > 300 && SVFit_Mass > 0";
  TString baseline_plus = "nJets30 >=2 && SVFit_Pt[SVFit_Index[0]] > 100 && SVFit_dijetMass > 300";
  baseline_plus = "1 == 1";
  //TString baseline_emuChan = " && HiggsSVFit_channel == 5";
  config.sel = baseline;

  LOG_YMIN = 10.;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString region = "Tau_training_040621_comp";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> sig_samples = {"ggHto2tau", "ggHHto2b2tau", "vbfHto2tau"};
  vector<TString> sig_samples_old = {"old_ggHto2tau", "old_ggHHto2b2tau", "old_vbfHto2tau"};
  vector<TString> mc_samples = {"diboson", "wjets", "dyll"};
  vector<TString> mc_samples_old = {"old_diboson", "old_wjets", "old_dyll"};

  vector< pair<TString, TString> > channel = {
    make_pair("allBaseline", "(" + Lead_emuChannel + "||" + Lead_elechadChannel + "||" + Lead_muonhadChannel + "||" + Lead_hadhadChannel + ")"),
    //make_pair("Lead_emu_", Lead_emuChannel),
    //make_pair("Lead_elechad_", Lead_elechadChannel),
    //make_pair("Lead_muonhad_", Lead_muonhadChannel),
    //make_pair("Lead_hadhad_", Lead_hadhadChannel),
    //make_pair("SubLead_emu_", SubLead_emuChannel),
    //make_pair("SubLead_elechad_", SubLead_elechadChannel),
    //make_pair("SubLead_muonhad_", SubLead_muonhadChannel),
    //make_pair("SubLead_hadhad_", SubLead_hadhadChannel),
  };

  TString hName = "Lead_higgsMass";
  auto varDictSmall = varDict.at(hName);

  std::function<void(TCanvas*)> plotextra;
  //for (auto &var : varDictSmall){
  for( const pair<TString, TString> &chan : channel){
    if(chan.first.BeginsWith(hName(0,3)) || chan.first.Contains("all")){
      z.resetSelection();
      z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, Category::dummy_category(), true, true, false, &plotextra, false, -1., hName);
      z.resetSelection();
      z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018_old", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      z.plotSigVsBkg(varDictSmall, mc_samples_old, sig_samples_old, Category::dummy_category(), true, true, false, &plotextra, false, -1., hName);
      z.resetSelection();
      z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018_linear", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, Category::dummy_category(), true, false, false, &plotextra, false, -1., hName);
      z.resetSelection();
      z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018_old_linear", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      z.plotSigVsBkg(varDictSmall, mc_samples_old, sig_samples_old, Category::dummy_category(), true, false, false, &plotextra, false, -1., hName);
    }
  }
}

void HiggsEstimator(){
  plotHtoTaus();
}
