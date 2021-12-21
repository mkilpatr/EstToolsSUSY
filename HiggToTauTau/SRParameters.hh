#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"
#include "binDefinitions.hh"

namespace EstTools{

const TString inputdir = "root://cmseos.fnal.gov//eos/uscms/store/user/mkilpatr/13TeV";
const TString inputdir_local = "/uscms/home/mkilpatr/nobackup/CMSSW_10_2_22/src/PhysicsTools/NanoSUSYTools/python/processors";
const TString inputdir_2018 = "nanoaod_2018_diHiggs_09Dec21_LundVar/";
//const TString inputdir_2018 = "";

const TString outputdir = ".";

const TString datadir = "nanoaod_2018_diHiggs_09Dec21_LundVar/";

TString lumistr = "59.699489";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// lumi and base weight
const TString basic_wgt = "*Stop0l_evtWeight";
const TString wgtvar = lumistr+"*1000"+basic_wgt;// //2016

// photon trigger eff.
const TString phowgt = wgtvar;
//const TString phowgt = wgtvar + "*qcdRespTailWeight";

// No Lepton SF
//const TString lepvetowgt = wgtvar;
//const TString lepselwgt  = wgtvar;
//const TString vetoes = " && nvetolep==0 && nvetotau==0";

// Tag-and-Probe Lepton SF
const TString lepvetowgt =      	wgtvar		+ "*Stop0l_trigger_eff_MET_loose_baseline*MuonLooseSRSF*ElectronVetoSRSF*TauSRSF";
const TString lepselwgt  =      	wgtvar		+ "*Stop0l_trigger_eff_MET_loose_baseline*MuonLooseCRSF*ElectronVetoCRSF";
const TString vetoes = " && Pass_LeptonVeto";

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// sr weight w/o top/W SF

// 1Lep LLB method
bool ADD_LEP_TO_MET = false;
bool ICHEPCR = false;

bool addTTZRare = true;
bool SPLITTF = true; // split TF to CR-SR and SR-extrapolation
const TString revert_vetoes = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && (run < 319077 || (run >= 319077 && Pass_exHEMVetoElec30))";
const TString invert_genLep = " && genMatchedLep";

// MET+LEP LL method
//bool ADD_LEP_TO_MET = true;
const TString lepcrsel = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && MET_pt>100";
const TString ttznorm = "1.214";
//TString binMap_ = "lm_nb2_lowmtb_highptisr_lowptb12";
TString binMap_ = "allBins";
TString binMap() { return binMap_;}

// lepton trigger eff.
//const TString trigLepCR = " && (passtrige || passtrigmu)";
//const TString onelepcrwgt  = lepselwgt + "*trigEleWeight*trigMuWeight";

const TString trigLepCR = "";
const TString onelepcrwgt  = lepselwgt;

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(0.85*(Stop0l_nSoftb>=1) + 1.0*(Stop0l_nSoftb==0))";
const TString sigwgt = lepvetowgt;

//Separate channel cuts
const TString Lead_muonhadChannel   = "(SVFit_channel[SVFit_Index[0]] == 0 && SVFit_PassTight[SVFit_Index[0]] && SVFit_tau1_muMT[SVFit_Index[0]] < 50)";
const TString Lead_elechadChannel   = "(SVFit_channel[SVFit_Index[0]] == 1 && SVFit_PassTight[SVFit_Index[0]] && SVFit_tau1_elecMT[SVFit_Index[0]] < 50)";
const TString Lead_hadhadChannel    = "(SVFit_channel[SVFit_Index[0]] == 2 && SVFit_PassTight[SVFit_Index[0]] && SVFit_ditauDR[SVFit_Index[0]] > 0.5 && SVFit_ditauPt[SVFit_Index[0]] > 50)";
const TString Lead_emuChannel       = "(SVFit_channel[SVFit_Index[0]] == 5 && SVFit_DZeta[SVFit_Index[0]] > -35 && SVFit_elecMuonMT[SVFit_Index[0]] < 60)";
const TString SubLead_muonhadChannel= "(SVFit_channel[SVFit_Index[1]] == 0 && SVFit_PassTight[SVFit_Index[1]] && SVFit_tau1_muMT[SVFit_Index[1]] < 50)";
const TString SubLead_elechadChannel= "(SVFit_channel[SVFit_Index[1]] == 1 && SVFit_PassTight[SVFit_Index[1]] && SVFit_tau1_elecMT[SVFit_Index[1]] < 50)";
const TString SubLead_hadhadChannel = "(SVFit_channel[SVFit_Index[1]] == 2 && SVFit_PassTight[SVFit_Index[1]] && SVFit_ditauDR[SVFit_Index[1]] > 0.5 && SVFit_ditauPt[SVFit_Index[1]] > 50)";
const TString SubLead_emuChannel    = "(SVFit_channel[SVFit_Index[1]] == 5 && SVFit_DZeta[SVFit_Index[1]] > -35 && SVFit_elecMuonMT[SVFit_Index[1]] < 60)";

// triggers
const TString dibosonBadEventRemoval = " && event != 237972";
const TString trigSR = " && Pass_trigger_MET";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && Pass_EventFilter && Pass_JetID";
const TString qcdSpikeRemovals = "";
const TString dphi_invert = " && Pass_dPhiQCD";
const TString dphi_cut = " && ( ((Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETLowDM) || (!(Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETHighDM) )"; // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "Pass_NJets30 && SVFitMET_isValid && SVFit_PassBaseline && SVFit_PassLepton";

std::map<TString, TString> cutMap = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
        {"lowptisr",    "Stop0l_ISRJetPt>=300 && Stop0l_ISRJetPt<500"},
        {"noextrap",    "1 == 1"},
    };

    return cmap;
}();


std::map<TString, TString> labelMap{
  {"hptgt100", R"(p_{T}(H) > 100)"},
  {"djgt300", R"(M_{jj} > 300)"},
  {"emu",    R"(e\mu)"},
  {"elechad",    R"(e\tau_{h})"},
  {"muonhad",    R"(\mu\tau_{h})"},
  {"hadhad",    R"(\tau_{h}\tau_{h})"},
  {"Lead",    R"()"},
  {"SubLead",    R"()"},
  {"channels",    R"()"},
  {"allBaseline",    R"()"},
  {"comp1",    R"()"},
  {"comp2",    R"()"},
  {"comp3",    R"()"},
  {"comp4",    R"()"},
  {"comp5",    R"()"},
  {"comp6",    R"()"},
  {"comp7",    R"()"},
  {"comp8",    R"()"},
  {"comp9",    R"()"},
};

std::map<TString, TString> plotLabelMap{
  {"hptgt100", R"(p_{T}(H) > 100)"},
  {"djgt300", R"(M_{jj} > 300)"},
  {"emu",    R"(e#mu)"},
  {"elechad",    R"(e#tau_{h})"},
  {"muonhad",    R"(#mu#tau_{h})"},
  {"hadhad",    R"(#tau_{h}#tau_{h})"},
  {"Lead",    R"()"},
  {"SubLead",    R"()"},
  {"channels",    R"()"},
  {"allBaseline",    R"()"},
  {"comp1",    R"()"},
  {"comp2",    R"()"},
  {"comp3",    R"()"},
  {"comp4",    R"()"},
  {"comp5",    R"()"},
  {"comp6",    R"()"},
  {"comp7",    R"()"},
  {"comp8",    R"()"},
  {"comp9",    R"()"},
};

std::map<TString, TString> srcuts = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins){
      if(name != binMap() && binMap() != "allBins") continue;
      cuts[name] = createCutString(name, cutMap);
    }
    return cuts;
}();

std::map<TString, TString> srlabels = []{
    std::map<TString, TString> cmap;
    for (auto s: srbins){
      if(s != binMap() && binMap() != "allBins") continue;
      cmap[s] = s;
    }
    return cmap;
}();

std::map<TString, TString> lepcrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping){
      if(sr2cr.first != binMap() && binMap() != "allBins") continue;
      TString sr2crCut = sr2cr.first;
      cuts[sr2crCut] = createCutString(sr2cr.second, cutMap);
    }
    return cuts;
}();

std::map<TString, TString> lepcrlabels = lepcrMapping;
std::map<TString, std::vector<int>> lepcrMETbins_small { {binMap(), srMETbins[binMap()]} };
std::map<TString, std::vector<int>> lepcrMETbins = (binMap() == "allBins") ? srMETbins : lepcrMETbins_small;

map<TString, Category> srCatMap(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    if(name != binMap() && binMap() != "allBins") continue;
    auto nameMet = name;
    cmap[name] = Category(name, srcuts.at(name), srlabels.at(name), BinInfo("MET_pt", "p^{miss}_{T}", srMETbins.at(nameMet), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "p^{miss}_{T}";
  map<TString, Category> cmap;
  //map<TString, TString> labels;
  const auto &cuts = ICHEPCR ? srcuts: lepcrCuts;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    if(name != binMap() && binMap() != "allBins") continue;
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig sigConfig(){
  BaseConfig     config;

  //config.inputdir = inputdir_local;
  config.inputdir = inputdir;
  config.outputdir = outputdir+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  //signal
  config.addSample("ggHHto2b2tau",     "gg#rightarrowHH#rightarrowbb#tau#tau",   inputdir_2018+"ggHHto2b2tau", "(1/12)*"+wgtvar,  datasel);
  config.addSample("ggHto2tau",        "gg#rightarrowH#rightarrow#tau#tau",      inputdir_2018+"ggHto2tau",    wgtvar,  datasel);
  config.addSample("vbfHto2tau",       "VBF#rightarrowH#rightarrow#tau#tau",     inputdir_2018+"vbfHto2tau",   wgtvar,  datasel);
  //background
  config.addSample("qcd",              "QCD",                                    inputdir_2018+"qcd",          wgtvar,  datasel);
  config.addSample("diboson",          "VV",                                     inputdir_2018+"diboson",      wgtvar,  datasel);
  config.addSample("wjets",            "W+jets",                                 inputdir_2018+"wjets",        wgtvar,  datasel);
  config.addSample("dyll",             "DY+jets",                                inputdir_2018+"dyll",         wgtvar,  datasel);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

map<TString, BinInfo> varDict {
	{"LundTau1M",		BinInfo("SVFit_LundTau1M",    "#tau_{1} ln(m)", 40, -2, 6)},
	{"LundTau1KT",		BinInfo("SVFit_LundTau1KT",   "#tau_{1} ln(k_{T})", 40, -2, 6)},
	{"LundTau1Z",		BinInfo("SVFit_LundTau1Z",    "#tau_{1} ln(z)", 40, -2, 6)},
	{"LundTau1Delta",	BinInfo("SVFit_LundTau1Delta","#tau_{1} ln(#Delta)", 40, -2, 6)},
	{"LundTau1Kappa",	BinInfo("SVFit_LundTau1Kappa","#tau_{1} ln(#kappa)", 40, -2, 6)},
	{"LundTau1Psi",		BinInfo("SVFit_LundTau1Psi",  "#tau_{1} #psi", 40, -2, 6)},
	{"LundTau2M",		BinInfo("SVFit_LundTau2M",    "#tau_{2} ln(m)", 40, -2, 6)},
	{"LundTau2KT",		BinInfo("SVFit_LundTau2KT",   "#tau_{2} ln(k_{T})", 40, -2, 6)},
	{"LundTau2Z",		BinInfo("SVFit_LundTau2Z",    "#tau_{2} ln(z)", 40, -2, 6)},
	{"LundTau2Delta",	BinInfo("SVFit_LundTau2Delta","#tau_{2} ln(#Delta)", 40, -2, 6)},
	{"LundTau2Kappa",	BinInfo("SVFit_LundTau2Kappa","#tau_{2} ln(#kappa)", 40, -2, 6)},
	{"LundTau2Psi",		BinInfo("SVFit_LundTau2Psi",  "#tau_{2} #psi", 40, -2, 6)},
	{"LundHiggsM",		BinInfo("SVFit_LundHiggsM",    "Higgs ln(m)", 40, -2, 6)},
	{"LundHiggsKT",		BinInfo("SVFit_LundHiggsKT",   "Higgs ln(k_{T})", 40, -2, 6)},
	{"LundHiggsZ",		BinInfo("SVFit_LundHiggsZ",    "Higgs ln(z)", 40, -2, 6)},
	{"LundHiggsDelta",	BinInfo("SVFit_LundHiggsDelta","Higgs ln(#Delta)", 40, -2, 6)},
	{"LundHiggsKappa",	BinInfo("SVFit_LundHiggsKappa","Higgs ln(#kappa)", 40, -2, 6)},
	{"LundHiggsPsi",	BinInfo("SVFit_LundHiggsPsi",  "Higgs #psi", 40, -2, 6)},
	{"Lead_tauChannel",	BinInfo("SVFit_channel[SVFit_Index[0]]",   "Tau channel", 6, -0.5, 5.5)},
	{"Lead_higgsPt",	BinInfo("SVFit_Pt[SVFit_Index[0]]",  	"p_{T}(H) [GeV]", 20, 0, 500)},
	{"Lead_higgsEta",	BinInfo("SVFit_Eta[SVFit_Index[0]]", 	"#eta(H)", 16, -4, 4)},
	{"Lead_higgsPhi",	BinInfo("SVFit_Phi[SVFit_Index[0]]", 	"#phi(H)", 64, -3.2, 3.2)},
	{"Lead_higgsMass",	BinInfo("SVFit_Mass[SVFit_Index[0]]",	"M_{H}", 25, 0, 500)},
	{"Lead_higgsTransverseMass",	BinInfo("SVFit_TransverseMass[SVFit_Index[0]]",	"M_{T}^{H}", 25, 0, 500)},
	{"Lead_tau1nuPx",	BinInfo("SVFit_tau1nuPx[SVFit_Index[0]]",  	"p_{x}(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"Lead_tau1nuPy",	BinInfo("SVFit_tau1nuPy[SVFit_Index[0]]",  	"p_{y}(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"Lead_tau1nuPz",	BinInfo("SVFit_tau1nuPz[SVFit_Index[0]]",  	"p_{z}(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"Lead_tau1nuE",	BinInfo("SVFit_tau1nuE[SVFit_Index[0]]",  	"E(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"Lead_tau1Pt",	BinInfo("SVFit_tau1Pt[SVFit_Index[0]]",  	"p_{T}(#tau_{1}) [GeV]", 20, 0, 200)},
	{"Lead_tau1Eta",	BinInfo("SVFit_tau1Eta[SVFit_Index[0]]", 	"#eta(#tau_{1})", 16, -4, 4)},
	{"Lead_tau1Phi",	BinInfo("SVFit_tau1Phi[SVFit_Index[0]]", 	"#phi(#tau_{1})", 64, -3.2, 3.2)},
	{"Lead_tau1Mass",	BinInfo("SVFit_tau1Mass[SVFit_Index[0]]",	"M_{#tau_{1}}", 20, 0, 4)},
	{"Lead_tau1pdgid",	BinInfo("SVFit_tau1pdgId[SVFit_Index[0]]",	"pdgId #tau_{1}", 6, -0.5, 5.5)},
	{"Lead_tau1DM",	BinInfo("SVFit_tau1DM[SVFit_Index[0]]",	"Decay Mode #tau_{1}", 16, -0.5, 15.5)},
	{"Lead_tau2nuPx",	BinInfo("SVFit_tau2nuPx[SVFit_Index[0]]",  	"p_{x}(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"Lead_tau2nuPy",	BinInfo("SVFit_tau2nuPy[SVFit_Index[0]]",  	"p_{y}(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"Lead_tau2nuPz",	BinInfo("SVFit_tau2nuPz[SVFit_Index[0]]",  	"p_{z}(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"Lead_tau2nuE",	BinInfo("SVFit_tau2nuE[SVFit_Index[0]]",  	"E(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"Lead_tau2Pt",	BinInfo("SVFit_tau2Pt[SVFit_Index[0]]",  	"p_{T}(#tau_{2}) [GeV]", 20, 0, 200)},
	{"Lead_tau2Eta",	BinInfo("SVFit_tau2Eta[SVFit_Index[0]]", 	"#eta(#tau_{2})", 16, -4, 4)},
	{"Lead_tau2Phi",	BinInfo("SVFit_tau2Phi[SVFit_Index[0]]", 	"#phi(#tau_{2})", 64, -3.2, 3.2)},
	{"Lead_tau2Mass",	BinInfo("SVFit_tau2Mass[SVFit_Index[0]]",	"M_{#tau_{2}}", 20, 0, 4)},
	{"Lead_tau2pdgid",	BinInfo("SVFit_tau2pdgId[SVFit_Index[0]]",	"pdgId #tau_{2}", 6, -0.5, 5.5)},
	{"Lead_tau2DM",	BinInfo("SVFit_tau2DM[SVFit_Index[0]]",	"Decay Mode #tau_{2}", 16, -0.5, 15.5)},
	{"Lead_ht",		BinInfo("SVFit_HT",        "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000, 1500}, "GeV")},
	{"Lead_elecMuonMT",	BinInfo("SVFit_elecMuonMT[SVFit_Index[0]]","M_{T}^{e+#mu}", 20, 0, 200)},
	{"Lead_elecMT_tau1",	BinInfo("SVFit_tau1_elecMT[SVFit_Index[0]]","M_{T}^{e}", 20, 0, 200)},
	{"Lead_muonMT_tau1",	BinInfo("SVFit_tau1_muMT[SVFit_Index[0]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"Lead_tauMT_tau1",	BinInfo("SVFit_tau1_hadMT[SVFit_Index[0]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"Lead_muonMT_tau2",	BinInfo("SVFit_tau2_muMT[SVFit_Index[0]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"Lead_tauMT_tau2",	BinInfo("SVFit_tau2_hadMT[SVFit_Index[0]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"Lead_ditauMass",	BinInfo("SVFit_ditauMass[SVFit_Index[0]]",  "M_{#tau#tau}", 50, 0, 500)},
	{"Lead_ditauPt",	BinInfo("SVFit_ditauPt[SVFit_Index[0]]",    "p_{T}^{#tau#tau+miss} [GeV]", 25, 0, 600)},
	{"Lead_ditau_dR",	BinInfo("SVFit_ditauDR[SVFit_Index[0]]",    "#DeltaR(#tau_{1}, #tau_{2})", 30, 0, 6)},
	{"Lead_elecMuon_dR",	BinInfo("SVFit_deltaREMu[SVFit_Index[0]]",  "#DeltaR(e, #mu)", 30, 0, 6)},
	{"Lead_ditaudijetMass",BinInfo("SVFit_2tau2jetPt[SVFit_Index[0]]", 	"p_{T}^{#tau#taujj+miss}", 40, 0, 1000)},
	{"Lead_maxdR_bjettau",BinInfo("SVFit_MaxbjetTauDR[SVFit_Index[0]]",    "max(#DeltaR(b, #tau)", 30, 0, 6)},
	{"Lead_mindR_bjettau",BinInfo("SVFit_MinbjetTauDR[SVFit_Index[0]]",    "min(#DeltaR(b, #tau)", 30, 0, 6)},
	{"Lead_DZeta",	BinInfo("SVFit_DZeta[SVFit_Index[0]]",  "D_{#zeta}", 24, -40, 200)},
	{"SubLead_tauChannel",	BinInfo("SVFit_channel[SVFit_Index[1]]",   "Tau channel", 5, 0, 5)},
	{"SubLead_higgsPt",	BinInfo("SVFit_Pt[SVFit_Index[1]]",  	"p_{T}(H) [GeV]", 12, 100, 1000)},
	{"SubLead_higgsEta",	BinInfo("SVFit_Eta[SVFit_Index[1]]", 	"#eta(H)", 16, -4, 4)},
	{"SubLead_higgsPhi",	BinInfo("SVFit_Phi[SVFit_Index[1]]", 	"#phi(H)", 64, -3.2, 3.2)},
	{"SubLead_higgsMass",	BinInfo("SVFit_Mass[SVFit_Index[1]]",	"M_{H}", 25, 0, 500)},
	{"SubLead_higgsTransverseMass",	BinInfo("SVFit_TransverseMass[SVFit_Index[1]]",	"M_{T}^{H}", 25, 0, 500)},
	{"SubLead_tau1nuPx",	BinInfo("SVFit_tau1nuPx[SVFit_Index[1]]",  	"p_{x}(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau1nuPy",	BinInfo("SVFit_tau1nuPy[SVFit_Index[1]]",  	"p_{y}(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau1nuPz",	BinInfo("SVFit_tau1nuPz[SVFit_Index[1]]",  	"p_{z}(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau1nuE",	BinInfo("SVFit_tau1nuE[SVFit_Index[1]]",  	"E(#nu_{#tau_{1}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau1Pt",	BinInfo("SVFit_tau1Pt[SVFit_Index[1]]",  	"p_{T}(#tau_{1}) [GeV]", 20, 0, 200)},
	{"SubLead_tau1Eta",	BinInfo("SVFit_tau1Eta[SVFit_Index[1]]", 	"#eta(#tau_{1})", 16, -4, 4)},
	{"SubLead_tau1Phi",	BinInfo("SVFit_tau1Phi[SVFit_Index[1]]", 	"#phi(#tau_{1})", 64, -3.2, 3.2)},
	{"SubLead_tau1Mass",	BinInfo("SVFit_tau1Mass[SVFit_Index[1]]",	"M_{#tau_{1}}", 20, 0, 4)},
	{"SubLead_tau1pdgid",	BinInfo("SVFit_tau1pdgId[SVFit_Index[1]]",	"pdgId #tau_{1}", 6, -0.5, 5.5)},
	{"SubLead_tau1DM",	BinInfo("SVFit_tau1DM[SVFit_Index[1]]",	"Decay Mode #tau_{1}", 16, -0.5, 15.5)},
	{"SubLead_tau2nuPx",	BinInfo("SVFit_tau2nuPx[SVFit_Index[1]]",  	"p_{x}(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau2nuPy",	BinInfo("SVFit_tau2nuPy[SVFit_Index[1]]",  	"p_{y}(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau2nuPz",	BinInfo("SVFit_tau2nuPz[SVFit_Index[1]]",  	"p_{z}(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau2nuE",	BinInfo("SVFit_tau2nuE[SVFit_Index[1]]",  	"E(#nu_{#tau_{2}}) [GeV]", 20, 0, 200)},
	{"SubLead_tau2Pt",	BinInfo("SVFit_tau2Pt[SVFit_Index[1]]",  	"p_{T}(#tau_{2}) [GeV]", 20, 0, 200)},
	{"SubLead_tau2Eta",	BinInfo("SVFit_tau2Eta[SVFit_Index[1]]", 	"#eta(#tau_{2})", 16, -4, 4)},
	{"SubLead_tau2Phi",	BinInfo("SVFit_tau2Phi[SVFit_Index[1]]", 	"#phi(#tau_{2})", 64, -3.2, 3.2)},
	{"SubLead_tau2Mass",	BinInfo("SVFit_tau2Mass[SVFit_Index[1]]",	"M_{#tau_{2}}", 20, 0, 4)},
	{"SubLead_tau2pdgid",	BinInfo("SVFit_tau2pdgId[SVFit_Index[1]]",	"pdgId #tau_{2}", 6, -0.5, 5.5)},
	{"SubLead_tau2DM",	BinInfo("SVFit_tau2DM[SVFit_Index[1]]",	"Decay Mode #tau_{2}", 16, -0.5, 15.5)},
	{"SubLead_ht",		BinInfo("SVFit_HT",        "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000, 1500}, "GeV")},
	{"SubLead_elecMuonMT",	BinInfo("SVFit_elecMuonMT[SVFit_Index[1]]","M_{T}^{e+#mu}", 20, 0, 200)},
	{"SubLead_elecMT_tau1",	BinInfo("SVFit_tau1_elecMT[SVFit_Index[1]]","M_{T}^{e}", 20, 0, 200)},
	{"SubLead_muonMT_tau1",	BinInfo("SVFit_tau1_muMT[SVFit_Index[1]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"SubLead_tauMT_tau1",	BinInfo("SVFit_tau1_hadMT[SVFit_Index[1]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"SubLead_muonMT_tau2",	BinInfo("SVFit_tau2_muMT[SVFit_Index[1]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"SubLead_tauMT_tau2",	BinInfo("SVFit_tau2_hadMT[SVFit_Index[1]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"SubLead_ditauMass",	BinInfo("SVFit_ditauMass[SVFit_Index[1]]",  "M_{#tau#tau}", 50, 0, 500)},
	{"SubLead_ditauPt",	BinInfo("SVFit_ditauPt[SVFit_Index[1]]",    "p_{T}^{#tau#tau+miss} [GeV]", 25, 0, 600)},
	{"SubLead_ditau_dR",	BinInfo("SVFit_ditauDR[SVFit_Index[1]]",    "#DeltaR(#tau_{1}, #tau_{2})", 30, 0, 6)},
	{"SubLead_elecMuon_dR",	BinInfo("SVFit_deltaREMu[SVFit_Index[1]]",  "#DeltaR(e, #mu)", 30, 0, 6)},
	{"SubLead_ditaudijetMass",BinInfo("SVFit_2tau2jetPt[SVFit_Index[1]]", 	"p_{T}^{#tau#taujj+miss}", 40, 0, 1000)},
	{"SubLead_maxdR_bjettau",BinInfo("SVFit_MaxbjetTauDR[SVFit_Index[1]]",    "max(#DeltaR(b, #tau)", 30, 0, 6)},
	{"SubLead_mindR_bjettau",BinInfo("SVFit_MinbjetTauDR[SVFit_Index[1]]",    "min(#DeltaR(b, #tau)", 30, 0, 6)},
	{"SubLead_DZeta",	BinInfo("SVFit_DZeta[SVFit_Index[1]]",  "D_{#zeta}", 24, -40, 200)},
	{"njets",	BinInfo("nJets30",      	 "N_{j}", 8, 1.5, 9.5)}, 
	{"bj1Pt",	BinInfo("SVFit_bj1Pt",  	 "p_{T}(b_{1}) [GeV]", 20, 0, 200)},
	{"bj2Pt",	BinInfo("SVFit_bj2Pt",  	 "p_{T}(b_{2}) [GeV]", 20, 0, 200)},
	{"j1Pt",	BinInfo("SVFit_j1Pt",  	 "p_{T}(j_{1}) [GeV]", 40, 0, 400)},
	{"j1Eta",	BinInfo("SVFit_j1Eta", 	 "#eta(j_{1})", 16, -4, 4)},
	{"j1Phi",	BinInfo("SVFit_j1Phi", 	 "#phi(j_{1})", 64, -3.2, 3.2)},
	{"j1Mass",	BinInfo("SVFit_j1Mass",	 "M_{j_{1}}", 20, 0, 40)},
	{"j2Pt",	BinInfo("SVFit_j2Pt",  	 "p_{T}(j_{2}) [GeV]", 40, 0, 400)},
	{"j2Eta",	BinInfo("SVFit_j2Eta", 	 "#eta(j_{2})", 26, -4, 4)},
	{"j2Phi",	BinInfo("SVFit_j2Phi", 	 "#phi(j_{2})", 64, -3.2, 3.2)},
	{"j2Mass",	BinInfo("SVFit_j2Mass",	 "M_{j_{2}}", 20, 0, 40)},
	{"j3Pt",	BinInfo("SVFit_j3Pt",  	 "p_{T}(j_{3}) [GeV]", 40, 0, 400)},
	{"j3Eta",	BinInfo("SVFit_j3Eta", 	 "#eta(j_{3})", 36, -4, 4)},
	{"j3Phi",	BinInfo("SVFit_j3Phi", 	 "#phi(j_{3})", 64, -3.2, 3.2)},
	{"j3Mass",	BinInfo("SVFit_j3Mass",	 "M_{j_{3}}", 20, 0, 40)},
	{"dijetMass",	BinInfo("SVFit_dijetMass",  "M_{jj}", 20, 300, 1500)},
	{"dijetPt",	BinInfo("SVFit_dijetPt",    "p_{T}^{jj}", 25, 0, 400)},
	{"dijet_dR",	BinInfo("SVFit_dijetDR",    "#DeltaR(j_{1}, j_{2})", 30, 0, 6)},
	{"dijet_dEta",	BinInfo("SVFit_dijetDEta",  "#Delta#eta(j_{1}, j_{2})", 30, 0, 6)},
	{"met",         BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{0, 50, 150, 250, 350, 450, 550, 650, 750, 1000}, "GeV")},
};

}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
