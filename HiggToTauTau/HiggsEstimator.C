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

void lepcrYields(){

  auto config = lepConfig();

  config.samples.clear();
  config.addSample("singlelep",   "Data",          "met",       		"1.0",     datasel + trigLepCR + lepcrsel);
  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        		lepselwgt+"*ISRWeight", datasel + trigLepCR + lepcrsel);
  config.addSample("wjets",       "W+jets",        "wjets",        		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("tW",          "tW",            "tW",              		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("ttW",         "t#bar{t}W",           "ttW",             		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("qcd",         "QCD",           "qcd",             		lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("ww",          "WW",            "sr/ww",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("wz",          "WZ",            "sr/wz",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("zz",          "ZZ",            "sr/zz",                 lepselwgt, datasel + trigLepCR + lepcrsel);

  BaseEstimator z(config);

  z.calcYields();
  z.printYields();
  z.sumYields({"ttbar", "wjets", "tW", "ttW", "qcd"}, "Total BKG");
  z.sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw-cr");
  z.printYieldsTable({"ttbar", "wjets", "tW", "ttW", "qcd", "Total BKG", "singlelep"});

  vector<TH1*> mc;
  mc.push_back(convertToHist(z.yields.at("ttbar"),"ttbar_cr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("wjets"),"wjets",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("tW"),"tW_cr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("ttW"),"ttWcr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("ttbarplusw-cr"),"ttbarplusw_cr",";Search Region;Events"));

  auto hdata = convertToHist(z.yields.at("singlelep"),"data",";Search Region;Events");

  TFile *output = new TFile(z.config.outputdir+"/llcr_yields.root", "RECREATE");
  for (auto *h : mc)   h->Write();
  hdata->Write();
  output->Close();

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotHtoTaus(){
  auto config = sigConfig();
  //TString baseline_plus = "nJets30 >=2 && SVFit_Pt > 100 && JetTau_dijetMass > 300 && SVFit_Mass > 0";
  TString baseline_plus = "nJets30 >=2 && HiggsSVFit_PassBaseline";
  config.sel = baseline;

  LOG_YMIN = 10.;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString region = "Tau_training_010821";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> sig_samples = {"GluGluHToTauTau", "GluGluToHHTo2B2Tau", "VBFHToTauTau"};
  vector<TString> mc_samples = {"diboson", "wjets", "dyll"};
  TString data_sample_2016 = "";

  map<TString, BinInfo> varDict {
	{"tauChannel",	BinInfo("HiggsSVFit_channel",   "Tau channel", 5, 0, 5)},
	{"higgsPt",	BinInfo("HiggsSVFit_Pt",  	"p_{T}(H) [GeV]", 12, 100, 1000)},
	{"higgsEta",	BinInfo("HiggsSVFit_Eta", 	"#eta(H)", 16, -4, 4)},
	{"higgsPhi",	BinInfo("HiggsSVFit_Phi", 	"#phi(H)", 64, -3.2, 3.2)},
	{"higgsMass",	BinInfo("HiggsSVFit_Mass",	"M_{H}", 25, 0, 500)},
	{"higgsTransverseMass",	BinInfo("HiggsSVFit_TransverseMass",	"M_{T}^{H}", 25, 0, 500)},
	{"tau1Pt",	BinInfo("HiggsSVFit_tau1Pt",  	"p_{T}(#tau_{1}) [GeV]", 20, 0, 200)},
	{"tau1Eta",	BinInfo("HiggsSVFit_tau1Eta", 	"#eta(#tau_{1})", 16, -4, 4)},
	{"tau1Phi",	BinInfo("HiggsSVFit_tau1Phi", 	"#phi(#tau_{1})", 64, -3.2, 3.2)},
	{"tau1Mass",	BinInfo("HiggsSVFit_tau1Mass",	"M_{#tau_{1}}", 20, 0, 4)},
	{"tau1pdgid",	BinInfo("HiggsSVFit_tau1pdgId",	"pdgId #tau_{1}", 6, -0.5, 5.5)},
	{"tau1DM",	BinInfo("HiggsSVFit_tau1DM",	"Decay Mode #tau_{1}", 16, -0.5, 15.5)},
	{"tau2Pt",	BinInfo("HiggsSVFit_tau2Pt",  	"p_{T}(#tau_{2}) [GeV]", 20, 0, 200)},
	{"tau2Eta",	BinInfo("HiggsSVFit_tau2Eta", 	"#eta(#tau_{2})", 16, -4, 4)},
	{"tau2Phi",	BinInfo("HiggsSVFit_tau2Phi", 	"#phi(#tau_{2})", 64, -3.2, 3.2)},
	{"tau2Mass",	BinInfo("HiggsSVFit_tau2Mass",	"M_{#tau_{2}}", 20, 0, 4)},
	{"tau2pdgid",	BinInfo("HiggsSVFit_tau2pdgId",	"pdgId #tau_{2}", 6, -0.5, 5.5)},
	{"tau2DM",	BinInfo("HiggsSVFit_tau2DM",	"Decay Mode #tau_{2}", 16, -0.5, 15.5)},
	{"ht",		BinInfo("HiggsSVFit_HT",        "H_{T}", vector<int>{0, 50, 150, 250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	{"elecMuonMT",	BinInfo("HiggsSVFit_elecMuonMT","M_{T}^{e+#mu}", 20, 0, 200)},
	{"elecMT_tau1",	BinInfo("HiggsSVFit_tau1_elecMT","M_{T}^{e}", 20, 0, 200)},
	{"muonMT_tau1",	BinInfo("HiggsSVFit_tau1_muMT",  "M_{T}^{#mu}", 20, 0, 200)},
	{"tauMT_tau1",	BinInfo("HiggsSVFit_tau1_hadMT", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"muonMT_tau2",	BinInfo("HiggsSVFit_tau2_muMT",  "M_{T}^{#mu}", 20, 0, 200)},
	{"tauMT_tau2",	BinInfo("HiggsSVFit_tau2_hadMT", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"ditauMass",	BinInfo("HiggsSVFit_ditauMass",  "M_{#tau#tau}", 20, 0, 200)},
	{"ditauPt",	BinInfo("HiggsSVFit_ditauPt",    "p_{T}^{#tau#tau+miss} [GeV]", 25, 0, 600)},
	{"ditau_dR",	BinInfo("HiggsSVFit_ditauDR",    "#DeltaR(#tau_{1}, #tau_{2})", 30, 0, 6)},
	{"elecMuon_dR",	BinInfo("HiggsSVFit_deltaREMu",  "#DeltaR(e, #mu)", 30, 0, 6)},
	{"njets",	BinInfo("nJets30",      	 "N_{j}", 8, 1.5, 9.5)}, 
	{"bj1Pt",	BinInfo("HiggsSVFit_bj1Pt",  	 "p_{T}(b_{1}) [GeV]", 20, 0, 200)},
	{"bj2Pt",	BinInfo("HiggsSVFit_bj2Pt",  	 "p_{T}(b_{2}) [GeV]", 20, 0, 200)},
	{"j1Pt",	BinInfo("HiggsSVFit_j1Pt",  	 "p_{T}(j_{1}) [GeV]", 40, 0, 400)},
	{"j1Eta",	BinInfo("HiggsSVFit_j1Eta", 	 "#eta(j_{1})", 16, -4, 4)},
	{"j1Phi",	BinInfo("HiggsSVFit_j1Phi", 	 "#phi(j_{1})", 64, -3.2, 3.2)},
	{"j1Mass",	BinInfo("HiggsSVFit_j1Mass",	 "M_{j_{1}}", 20, 0, 40)},
	{"j2Pt",	BinInfo("HiggsSVFit_j2Pt",  	 "p_{T}(j_{2}) [GeV]", 40, 0, 400)},
	{"j2Eta",	BinInfo("HiggsSVFit_j2Eta", 	 "#eta(j_{2})", 26, -4, 4)},
	{"j2Phi",	BinInfo("HiggsSVFit_j2Phi", 	 "#phi(j_{2})", 64, -3.2, 3.2)},
	{"j2Mass",	BinInfo("HiggsSVFit_j2Mass",	 "M_{j_{2}}", 20, 0, 40)},
	{"j3Pt",	BinInfo("HiggsSVFit_j3Pt",  	 "p_{T}(j_{3}) [GeV]", 40, 0, 400)},
	{"j3Eta",	BinInfo("HiggsSVFit_j3Eta", 	 "#eta(j_{3})", 36, -4, 4)},
	{"j3Phi",	BinInfo("HiggsSVFit_j3Phi", 	 "#phi(j_{3})", 64, -3.2, 3.2)},
	{"j3Mass",	BinInfo("HiggsSVFit_j3Mass",	 "M_{j_{3}}", 20, 0, 40)},
	{"dijetMass",	BinInfo("HiggsSVFit_dijetMass",  "M_{jj}", 25, 0, 1500)},
	{"dijetPt",	BinInfo("HiggsSVFit_dijetPt",    "p_{T}^{jj}", 25, 0, 400)},
	{"ditaudijetMass",BinInfo("HiggsSVFit_2tau2jetPt", 	"p_{T}^{#tau#taujj+miss}", 25, 0, 400)},
	{"dijet_dR",	BinInfo("HiggsSVFit_dijetDR",    "#DeltaR(j_{1}, j_{2})", 30, 0, 6)},
	{"dijet_dEta",	BinInfo("HiggsSVFit_dijetDEta",  "#Delta#eta(j_{1}, j_{2})", 30, 0, 6)},
	{"met",         BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{0, 50, 150, 250, 350, 450, 550, 650, 750, 1000}, "GeV")},
  };

  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    //z.resetSelection();
    //z.setSelection(baseline_plus, "baseline_2018", "");
    //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
    //z.plotSigVsBkg(var.second, mc_samples, sig_samples, Category::dummy_category(), true, true, false, &plotextra);
    z.resetSelection();
    z.setSelection(baseline_plus, "baseline_2018_linear", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
    z.plotSigVsBkg(var.second, mc_samples, sig_samples, Category::dummy_category(), true, false, false, &plotextra);
  }
}

