#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"

using namespace EstTools;

void srYields(){

  auto config = lepConfig();
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
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);


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
  TString baseline_plus = "nJets30 >=2 && SVFit_Pt[SVIndex[0]] > 100 && SVFit_dijetMass > 300";
  //TString baseline_emuChan = " && HiggsSVFit_channel == 5";
  config.sel = baseline;

  LOG_YMIN = 10.;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString region = "Tau_training_032221";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> sig_samples = {"ggHto2tau", "ggHHto2b2tau", "vbfHto2tau"};
  vector<TString> mc_samples = {"diboson", "wjets", "dyll"};
  //vector<TString> mc_samples = {"local"};

  //const TString Lead_lepmuonChannel   = "(SVFit_channel[SVIndex[0]] == 0 && SVFit_PassTight[SVIndex[0]] && SVFit_tau1_muMT[SVIndex[0]] < 50)";
  //const TString Lead_elechadChannel   = "(SVFit_channel[SVIndex[0]] == 1 && SVFit_PassTight[SVIndex[0]] && SVFit_tau1_elecMT[SVIndex[0]] < 50)";
  //const TString Lead_hadhadChannel    = "(SVFit_channel[SVIndex[0]] == 2 && SVFit_PassTight[SVIndex[0]] && SVFit_ditauDR[SVIndex[0]] > 0.5 && SVFit_ditauPt[SVIndex[0]] > 50)";
  //const TString Lead_emuChannel       = "(SVFit_channel[SVIndex[0]] == 5 && SVFit_DZeta[SVIndex[0]] > -35 && SVFit_elecMuonMT[SVIndex[0]] < 60)";

  vector< pair<TString, TString> > channel = {
    make_pair("allChannel_elec", "(" + Lead_elechadChannel + ")"),
    make_pair("allChannel_muon", "(" + Lead_lepmuonChannel + ")"),
    make_pair("allChannel_had", "(" + Lead_hadhadChannel  + ")"),
    make_pair("allChannel_emu", "(" + Lead_emuChannel     + ")"),
    make_pair("allOther", "1 == 1"),
    //make_pair("Lead_emu_", Lead_emuChannel),
    //make_pair("Lead_lephad_", Lead_lephadChannel),
    //make_pair("Lead_hadhad_", Lead_hadhadChannel),
    //make_pair("SubLead_emu_", SubLead_emuChannel),
    //make_pair("SubLead_lephad_", SubLead_lephadChannel),
    //make_pair("SubLead_hadhad_", SubLead_hadhadChannel),
  };

  TString hName = "Lead_tauChannel";
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
      z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018_linear", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, Category::dummy_category(), true, false, false, &plotextra, false, -1., hName);
      //z.resetSelection();
      //z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018_norm", "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      //z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, Category::dummy_category(), true, true, true, &plotextra, false, -1., hName);
      //z.resetSelection();
      //z.setSelection(baseline_plus +  " && " + chan.second, chan.first + "baseline_2018_linear_norm", "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
      //z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, Category::dummy_category(), true, false, true, &plotextra, false, -1., hName);
    }
  }
}

void HiggsEstimator(){
  plotHtoTaus();
}
