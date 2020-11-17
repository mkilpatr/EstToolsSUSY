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
  TString baseline_plus = "nJets30 >=2 && HiggsCand_pt > 100 && JetTau_dijetMass > 300 && Tau_dijetMass != -9";
  config.sel = baseline;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString region = "Tau_training_111320";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> sig_samples = {"GluGluHToTauTau", "VBFHToTauTau"};
  vector<TString> mc_samples = {"diboson"};
  TString data_sample_2016 = "";

  map<TString, BinInfo> varDict {
	{"njets",	BinInfo("nJets30",      	"N_{j}", 10, -0.5, 9.5)}, 
	{"tauChannel",	BinInfo("Tau_channel",   	"Tau channel", 5, 0, 5)},
	{"tauMatch",	BinInfo("nTauMatch",     	"Matched N_{#tau}", 4, -0.5, 3.5)},
	{"tauHadDecay_1",	BinInfo("Tau_hadDecayFlag1", 	"Type of Decay", 3, -0.5, 2.5)},
	{"tauHadDecay_2",	BinInfo("Tau_hadDecayFlag2", 	"Type of Decay", 3, -0.5, 2.5)},
	{"jetMass",	BinInfo("JetTau_dijetMass", 	"M_{jj}", 16, 0, 800)},
	{"tauMass",	BinInfo("Tau_dijetMass", 	"M_{#tau#tau}", 100, 0, 50)},
	{"jetDeltaR",	BinInfo("JetTau_deltaR",    	"#DeltaR(j_{1}, j_{2})", 25, 0, 5)},
	{"tauDeltaR",	BinInfo("Tau_deltaR",    	"#DeltaR(#tau_{1}, #tau_{2})", 25, 0, 5)},
	{"higgsPt",	BinInfo("HiggsCand_pt",  	"p_T(H) [GeV]", 12, 0, 1000)},
	{"higgsEta",	BinInfo("HiggsCand_eta", 	"#eta(H)", 10, 0, 10)},
	{"higgsPhi",	BinInfo("HiggsCand_phi", 	"#phi(H)", 64, -3.2, 3.2)},
	{"higgsMass",	BinInfo("HiggsCand_mass",	"M(H)", 30, 0, 300)},
	{"ht",	BinInfo("Tau_HT",        	"H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	{"j1pt",	BinInfo("JetTau_matchPt_1"  , 	"p_T(j_{1}) [GeV]", 12, 400, 1000)},	
	{"j1eta",	BinInfo("JetTau_matchEta_1" , 	"#eta(j_{1})", 10, 0, 10)},         	
	{"j1phi",	BinInfo("JetTau_matchPhi_1" , 	"#phi(j_{1})", 64, -3.2, 3.2)},     	
	{"jimass",	BinInfo("JetTau_matchMass_1", 	"M(j_{1})", 30, 0, 300)},           	
	{"j2pt",	BinInfo("JetTau_matchPt_2"  , 	"p_T(j_{2}) [GeV]", 12, 400, 1000)},	
	{"j2eta",	BinInfo("JetTau_matchEta_2" , 	"#eta(j_{2})", 10, 0, 10)},         	
	{"j2phi",	BinInfo("JetTau_matchPhi_2" , 	"#phi(j_{2})", 64, -3.2, 3.2)},     	
	{"j2mass",	BinInfo("JetTau_matchMass_2", 	"M(j_{2})", 30, 0, 300)},           	
	{"j3pt",	BinInfo("JetTau_matchPt_3"  , 	"p_T(j_{3}) [GeV]", 12, 400, 1000)},	
	{"j3eta",	BinInfo("JetTau_matchEta_3" , 	"#eta(j_{3})", 10, 0, 10)},         	
	{"j3phi",	BinInfo("JetTau_matchPhi_3" , 	"#phi(j_{3})", 64, -3.2, 3.2)},     	
	{"j3mass",	BinInfo("JetTau_matchMass_3", 	"M(j_{3})", 30, 0, 300)},           	
	{"nlep",	BinInfo("Tau_nLep",  		"N_{lep}", 4, -0.5, 3.5)},
	{"lep1pt",	BinInfo("Tau_LeptonPt_1", 	"p_T(l_{1}) [GeV]", 12, 400, 1000)},
	{"lep1eta",	BinInfo("Tau_LeptonEta_1", 	"#eta(l_{1})", 10, 0, 10)},
	{"lep1phi",	BinInfo("Tau_LeptonPhi_1", 	"#phi(l_{1})", 64, -3.2, 3.2)},
	{"lep1charge",	BinInfo("Tau_LeptonCharge_1", 	"Charge l_{1}", 3, -1.5, 1.5)},
	{"lep1pdgid",	BinInfo("Tau_LeptonPdgId_1", 	"PdgId l_{1}", 31, -15.5, 15.5)},
	{"lep2pt",	BinInfo("Tau_LeptonPt_2", 	"p_T(l_{2}) [GeV]", 12, 400, 1000)},
	{"lep2eta",	BinInfo("Tau_LeptonEta_2", 	"#eta(l_{2})", 10, 0, 10)},
	{"lep2phi",	BinInfo("Tau_LeptonPhi_2", 	"#phi(l_{2})", 64, -3.2, 3.2)},
	{"lep2charge",	BinInfo("Tau_LeptonCharge_2", 	"M(l_{2})", 30, 0, 300)},
	{"lep2pdgid",	BinInfo("Tau_LeptonPdgId_2",    "PdgId l_{2}", 31, -15.5, 15.5)},	
	{"met",         BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
  };

  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    z.resetSelection();
    z.setSelection(baseline_plus, "baseline_2018", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 baseline}{}", 0.2, 0.75); };
    //plotSigVsBkg(const BinInfo& var_info, const vector<TString>& mc_samples, const vector<TString>& sig_sample, const Category& category, bool showSigma = true,  bool plotlog = false, std::function<void(TCanvas*)> *plotextra = nullptr)
    z.plotSigVsBkg(var.second, mc_samples, sig_samples, Category::dummy_category(), true, false, false, &plotextra);
  }
}

