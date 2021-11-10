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

  //TString baseline_plus = "nJets30 >=2 && SVFit_Pt[SVFit_Index[0]] > 100 && SVFit_dijetMass > 300";
  TString baseline_plus = "nJets30 >=2 && SVFit_dijetMass > 300";
  config.sel = baseline;

  LOG_YMIN = 1.;

  TString region = "Tau_training_040621_comp";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> sig_samples = {"ggHHto2b2tau", "ggHto2tau", "vbfHto2tau"};
  vector<TString> mc_samples = {"diboson", "wjets", "dyll"};

  vector< pair<TString, TString> > channel = {
    //make_pair("allBaseline_djgt300", "nJets30 >=2 && SVFit_dijetMass > 300"),
    make_pair("allBaseline_djgt300_channels", "(" + Lead_emuChannel + "||" + Lead_elechadChannel + "||" + Lead_muonhadChannel + "||" + Lead_hadhadChannel + ") && " + baseline_plus),
    make_pair("Lead_emu_djgt300", Lead_emuChannel + " && " + baseline_plus),
    make_pair("Lead_elechad_djgt300", Lead_elechadChannel + " && " + baseline_plus),
    make_pair("Lead_muonhad_djgt300", Lead_muonhadChannel + " && " + baseline_plus),
    make_pair("Lead_hadhad_djgt300", Lead_hadhadChannel + " && " + baseline_plus),
    //make_pair("SubLead_emu_djgt300", SubLead_emuChannel + " && nJets30 >=2 && SVFit_Pt[SVFit_Index[0]] > 100 && SVFit_dijetMass > 300"),
    //make_pair("SubLead_elechad_djgt300", SubLead_elechadChannel + " && nJets30 >=2 && SVFit_Pt[SVFit_Index[0]] > 100 && SVFit_dijetMass > 300"),
    //make_pair("SubLead_muonhad_djgt300", SubLead_muonhadChannel + " && nJets30 >=2 && SVFit_Pt[SVFit_Index[0]] > 100 && SVFit_dijetMass > 300"),
    //make_pair("SubLead_hadhad_djgt300", SubLead_hadhadChannel + " && nJets30 >=2 && SVFit_Pt[SVFit_Index[0]] > 100 && SVFit_dijetMass > 300"),
  };

  TString hName = "Lead_higgsMass";
  auto varDictSmall = varDict.at(hName);

  map<TString, Category> cmap;
  for( const pair<TString, TString> &chan : channel){
    if(chan.first.BeginsWith(hName(0,3)) || chan.first.Contains("all"))
      cmap[chan.first] = Category(chan.first, chan.second, translateString(chan.first, plotLabelMap, "_", ", ", true), varDictSmall);
  }

  for( const pair<TString, TString> &chan : channel){
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{" + cmap[chan.first].label + "}", 0.23, 0.75); };
    z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, cmap[chan.first], true,  true, false, &plotextra, false, -1., hName);
    //z.plotSigVsBkg(varDictSmall, mc_samples, sig_samples, cmap[chan.first], true, false, false, &plotextra, false, -1., hName);
  }

}

void HiggsEstimator(){
  plotHtoTaus();
}
