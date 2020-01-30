#ifndef ESTTOOLS_SRPARAMETERS_HH_
#define ESTTOOLS_SRPARAMETERS_HH_

#include "../../utils/EstHelper.hh"

namespace EstTools{

TString sys_name = "nominal";
TString inputdir = "root://cmsxrootd.fnal.gov//store/user/mkilpatr/13TeV/";
TString inputdir_2016 = "nanoaod_all_skim_2016_011020_limits/";
TString inputdir_2017 = "nanoaod_all_skim_2017_011020_limits/";
TString inputdir_2018 = "nanoaod_all_skim_2018_011020_limits/";
TString outputdir() {return "syst/"+sys_name;}

const TString datadir = "nanoaod_data_all_skim_011020_limits/";

const TString lumistr = "136.722688";
const TString lumistr_2016 = "35.815165"; //Units are in pb
const TString lumistr_2017 = "41.208034";
const TString lumistr_2018PreHEM  = "21.068576";
const TString lumistr_2018PostHEM = "38.630913";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}
// systematics weights
TString wtagwgt = "WtagSF";
TString sdmvawgt = "TopSF"; // top/W
TString restopwgt = "restopSF";
TString softbwgt = "SoftBSF";

TString puwgt = "puWeight"; // PU

TString muonwgt = "MuonLooseCRSF"; // tnp (el/mu)
TString elewgt = "ElectronVetoCRSF";
TString tauwgt = "TauCRSF";
TString muonvetowgt = "MuonLooseSRSF"; // tnp (el/mu)
TString elevetowgt = "ElectronVetoSRSF";
TString tauvetowgt = "TauSRSF";

TString sepmuonvetowgt = "MuonLooseSRSF"; // tnp (el/mu)
TString sepelevetowgt = "ElectronVetoSRSF";
TString septauvetowgt = "TauSRSF";
TString nolepmuonvetowgt = "MuonLooseSRSF"; // tnp (el/mu)
TString nolepelevetowgt = "ElectronVetoSRSF";
TString noleptauvetowgt = "TauSRSF";

TString isrwgt = "ISRWeight";

TString btagwgt = "BTagWeight"; // btag

TString prefirewgt = "PrefireWeight"; //prefire

TString pdfwgt = "1";

TString triggerwgt = "Stop0l_trigger_eff_MET_loose_baseline";
TString triggerwgtqcd = "Stop0l_trigger_eff_MET_loose_baseline_QCD";

TString mcwgt = "1000*Stop0l_evtWeight"; // ttbarnorm / wjetsnorm

TString qcdrestail = "qcdRespTailWeight"; //qcd response tail

// lumi and base weight
TString HEMVeto()     { return "(" + lumistr_2018PostHEM + "*(Pass_exHEMVeto30" + jes_postfix + ") + " + lumistr_2018PreHEM + "*(!Pass_exHEMVeto30" + jes_postfix + "))";}
TString HEMVetoElec() { return "(" + lumistr_2018PostHEM + "*(Pass_exHEMVetoElec30" + jes_postfix + ") + " + lumistr_2018PreHEM + "*(!Pass_exHEMVetoElec30" + jes_postfix + "))";}

TString isrwgtvar()     { return isrwgt; }
TString wgtvar()        { return lumistr_2016+"*"+mcwgt+"*"+puwgt+"*"+btagwgt+"*"+prefirewgt+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt+"*"+pdfwgt; }
TString wgtvar_2017()   { return lumistr_2017+"*"+mcwgt+"*"+puwgt+"*"+btagwgt+"*"+prefirewgt+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt+"*"+pdfwgt; }
TString wgtvar_2018() { return HEMVeto()+"*"+mcwgt+"*"+puwgt+"*"+btagwgt+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt+"*"+pdfwgt; }

// photon trigger eff.
TString phowgt() { return wgtvar(); }
//TString phowgt = wgtvar + "*qcdRespTailWeight";

TString jes_postfix = "";
bool doLepSyst = false;

// No Lepton SF
//TString lepvetowgt() {return wgtvar();}
//TString lepselwgt()  {return wgtvar();}
//const TString vetoes = " && nvetolep==0 && nvetotau==0";

TString seplepvetowgt()      		{ return wgtvar() +"*"+triggerwgt+"*"+sepmuonvetowgt+"*"+sepelevetowgt+"*"+septauvetowgt;}
TString seplepvetowgt_2017()      	{ return wgtvar_2017() +"*"+triggerwgt+"*"+sepmuonvetowgt+"*"+sepelevetowgt+"*"+septauvetowgt;}
TString seplepvetowgt_2018()      	{ return wgtvar_2018() +"*"+triggerwgt+"*"+sepmuonvetowgt+"*"+sepelevetowgt+"*"+septauvetowgt;}
TString nolepvetowgt()      		{ return wgtvar() +"*"+triggerwgt+"*"+nolepmuonvetowgt+"*"+nolepelevetowgt+"*"+noleptauvetowgt;}
TString nolepvetowgt_2017()      	{ return wgtvar_2017() +"*"+triggerwgt+"*"+nolepmuonvetowgt+"*"+nolepelevetowgt+"*"+noleptauvetowgt;}
TString nolepvetowgt_2018()      	{ return wgtvar_2018() +"*"+triggerwgt+"*"+nolepmuonvetowgt+"*"+nolepelevetowgt+"*"+noleptauvetowgt;}

// Tag-and-Probe Lepton SF
TString lepvetowgt() 	     { return wgtvar() +"*"+triggerwgt+"*"+muonvetowgt+"*"+elevetowgt+"*"+tauvetowgt; }
TString lepselwgt()  	     { return wgtvar() +"*"+triggerwgt+"*"+muonwgt+"*"+elewgt; }
TString lepvetowgt_2017() { return wgtvar_2017() +"*"+triggerwgt+"*"+muonvetowgt+"*"+elevetowgt+"*"+tauvetowgt; }
TString lepselwgt_2017()  { return wgtvar_2017() +"*"+triggerwgt+"*"+muonwgt+"*"+elewgt; }
TString lepvetowgt_2018()  { return wgtvar_2018() +"*"+triggerwgt+"*"+muonvetowgt+"*"+elevetowgt+"*"+tauvetowgt; }
TString lepselwgt_2018()   { return wgtvar_2018() +"*"+HEMVetoElec()+"*"+triggerwgt+"*"+muonwgt+"*"+elewgt; }
TString vetoes()	     { return  " && Pass_LeptonVeto"+jes_postfix; }

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// 1Lep LLB method
bool ADD_LEP_TO_MET = false;
bool ICHEPCR = false;
TString lepsel = "ElecVeto";
TString revert_vetoes() { return " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100"; }
TString revert_vetoes_sep() {return " && Pass_" + lepsel + " == 0"; }
//TString revert_vetoes_() {return " && Pass_MuonVeto == 0"; }
//TString revert_vetoes_()  {return " && Pass_IsoTrkVeto == 0 && Pass_TauVeto == 0"; }

// MET+LEP LL method
//bool ADD_LEP_TO_MET = true;
TString lepcrsel = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && MET_pt>100";

// lepton trigger eff.
//const TString trigLepCR = " && (passtrige || passtrigmu)";
//const TString onelepcrwgt  = lepselwgt + "*trigEleWeight*trigMuWeight";

const TString trigLepCR = " && passtriglepOR";
TString onelepcrwgt() {return lepselwgt();}

// qcd weights
TString qcdwgt()             {return wgtvar() +"*"+triggerwgtqcd+"*" + qcdrestail;}
TString qcdwgt_2017()        {return wgtvar_2017() +"*"+triggerwgtqcd+"*" + qcdrestail;}
TString qcdwgt_2018()        {return wgtvar_2018() +"*"+triggerwgtqcd+"*" + qcdrestail;}
TString qcdvetowgt()         {return lepvetowgt() +"*"+triggerwgt+"*" + qcdrestail;}
TString qcdvetowgt_2017()    {return lepvetowgt_2017() +"*"+triggerwgt+"*" + qcdrestail;}
TString qcdvetowgt_2018()    {return lepvetowgt_2018() +"*"+triggerwgt+"*" + qcdrestail;}
TString sepqcdvetowgt()      {return seplepvetowgt() +"*"+triggerwgt+"*" + qcdrestail;}
TString sepqcdvetowgt_2017() {return seplepvetowgt_2017() +"*"+triggerwgt+"*" + qcdrestail;}
TString sepqcdvetowgt_2018() {return seplepvetowgt_2018() +"*"+triggerwgt+"*" + qcdrestail;}

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(1.0*(mtcsv12met<=175)+sdtopFastSimWeight*sdwFastSimWeight*(mtcsv12met>175))";
TString sigwgt() {return lepvetowgt();}

// triggers
TString trigSR() { return " && Pass_trigger_MET"+jes_postfix;}
TString trigPhoCR = " && passtrigphoOR && origmet<200";
TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
TString datasel() { return " && Pass_EventFilter"+jes_postfix+" && Pass_HT"+jes_postfix+" && Pass_JetID"+jes_postfix+" && Pass_CaloMETRatio"+jes_postfix+" && (run < 319077 || (run >= 319077 && Pass_exHEMVeto30"+jes_postfix+")) && Pass_LHETTbar"+jes_postfix; }
TString qcdSpikeRemovals = "";
TString dphi_invert() {return " && Pass_dPhiQCD"+jes_postfix;}
TString dphi_cut() { return  " && ( ((Stop0l_Mtb"+jes_postfix+"<175 && Stop0l_nTop"+jes_postfix+"==0 && Stop0l_nW"+jes_postfix+"==0 && Stop0l_nResolved"+jes_postfix+"==0) && Pass_dPhiMETLowDM"+jes_postfix+") || (!(Stop0l_Mtb"+jes_postfix+"<175 && Stop0l_nTop"+jes_postfix+"==0 && Stop0l_nW"+jes_postfix+"==0 && Stop0l_nResolved"+jes_postfix+"==0) && Pass_dPhiMETHighDM"+jes_postfix+") )"; } // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

// ------------------------------------------------------------------------
// search regions and control regions

TString baseline() {return "Pass_MET"+jes_postfix+" && Pass_NJets30"+jes_postfix+""; }

std::map<TString, TString> cutMap = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt"+jes_postfix+">=300 && Stop0l_Mtb"+jes_postfix+" < 175 && Stop0l_nTop"+jes_postfix+"==0 && Stop0l_nW"+jes_postfix+"==0 && Stop0l_nResolved"+jes_postfix+"==0 && Stop0l_METSig"+jes_postfix+">=10"},
        {"dPhiLM",      "Pass_dPhiMETLowDM"+jes_postfix+""},
        {"hmNoDPhi",    "Stop0l_nJets"+jes_postfix+">=5 && Stop0l_nbtags"+jes_postfix+">=1"},
        {"dPhiHM",      "Pass_dPhiMETHighDM"+jes_postfix+""},
        {"invertDPhi",  "Pass_dPhiQCD"+jes_postfix+""},
 
        {"nb0",         "Stop0l_nbtags"+jes_postfix+"==0"},
        {"nb1",         "Stop0l_nbtags"+jes_postfix+"==1"},
        {"nbgeq1",      "Stop0l_nbtags"+jes_postfix+">=1"},
        {"nb2",         "Stop0l_nbtags"+jes_postfix+">=2"},
        {"nbeq2",       "Stop0l_nbtags"+jes_postfix+"==2"},
        {"nb3",         "Stop0l_nbtags"+jes_postfix+">=3"},
        {"nivf0",       "Stop0l_nSoftb"+jes_postfix+"==0"},
        {"nivf1",       "Stop0l_nSoftb"+jes_postfix+">=1"},
        {"lowptisr",    "Stop0l_ISRJetPt"+jes_postfix+">=300 && Stop0l_ISRJetPt"+jes_postfix+"<500"},
        {"medptisr",    "Stop0l_ISRJetPt"+jes_postfix+">=300"},
        {"highptisr",   "Stop0l_ISRJetPt"+jes_postfix+">=500"},
        {"nj2to5",      "Stop0l_nJets"+jes_postfix+">=2 && Stop0l_nJets"+jes_postfix+"<=5"},
        {"nj6",         "Stop0l_nJets"+jes_postfix+">=6"},
        {"nj7",         "Stop0l_nJets"+jes_postfix+">=7"},
        {"lowmtb",      "Stop0l_Mtb"+jes_postfix+"<175"},
        {"highmtb",     "Stop0l_Mtb"+jes_postfix+">=175"},
        {"lowptb",      "Stop0l_Ptb"+jes_postfix+"<40"},
        {"medptb",      "Stop0l_Ptb"+jes_postfix+">=40 && Stop0l_Ptb"+jes_postfix+"<70"},
        {"highptb",     "Stop0l_Ptb"+jes_postfix+">=70"},
        {"lowptb12",    "Stop0l_Ptb"+jes_postfix+"<80"},
        {"medptb12",    "Stop0l_Ptb"+jes_postfix+">=80 && Stop0l_Ptb"+jes_postfix+"<140"},
        {"highptb12",   "Stop0l_Ptb"+jes_postfix+">=140"},
        {"nt0",         "Stop0l_nTop"+jes_postfix+"==0"},
        {"nt1",         "Stop0l_nTop"+jes_postfix+"==1"},
        {"nt2",         "Stop0l_nTop"+jes_postfix+"==2"},
        {"ntgeq1",      "Stop0l_nTop"+jes_postfix+">=1"},
        {"nw0",         "Stop0l_nW"+jes_postfix+"==0"},
        {"nw1",         "Stop0l_nW"+jes_postfix+"==1"},
        {"nw2",         "Stop0l_nW"+jes_postfix+"==2"},
        {"nwgeq1",      "Stop0l_nW"+jes_postfix+">=1"},
        {"nrt0",        "Stop0l_nResolved"+jes_postfix+"==0"},
        {"nrt1",        "Stop0l_nResolved"+jes_postfix+"==1"},
        {"nrt2",        "Stop0l_nResolved"+jes_postfix+"==2"},
        {"nrtgeq1",     "Stop0l_nResolved"+jes_postfix+">=1"},
        {"nrtntnwgeq2", "(Stop0l_nTop"+jes_postfix+"+Stop0l_nResolved"+jes_postfix+"+Stop0l_nW"+jes_postfix+") >= 2"},
        {"nrtntnwgeq3", "(Stop0l_nTop"+jes_postfix+"+Stop0l_nResolved"+jes_postfix+"+Stop0l_nW"+jes_postfix+") >= 3"},
        {"htgt1000",    "Stop0l_HT"+jes_postfix+">=1000"},
        {"htlt1000",    "Stop0l_HT"+jes_postfix+"<1000"},
        {"ht1000to1500","Stop0l_HT"+jes_postfix+">=1000 && Stop0l_HT"+jes_postfix+"<1500"},
        {"htgt1500",    "Stop0l_HT"+jes_postfix+">=1500"},
        {"htlt1300",    "Stop0l_HT"+jes_postfix+"<1300"},
        {"htgt1300",    "Stop0l_HT"+jes_postfix+">=1300"},

    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();

std::map<TString, TString> cutMap_JESUp = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt_JESUp>=300 && Stop0l_Mtb_JESUp < 175 && Stop0l_nTop_JESUp==0 && Stop0l_nW_JESUp==0 && Stop0l_nResolved_JESUp==0 && Stop0l_METSig_JESUp>=10"},
        {"dPhiLM",      "Pass_dPhiMETLowDM_JESUp"},
        {"hmNoDPhi",    "Stop0l_nJets_JESUp>=5 && Stop0l_nbtags_JESUp>=1"},
        {"dPhiHM",      "Pass_dPhiMETHighDM_JESUp"},
        {"invertDPhi",  "Pass_dPhiQCD_JESUp"},
 
        {"nb0",         "Stop0l_nbtags_JESUp==0"},
        {"nb1",         "Stop0l_nbtags_JESUp==1"},
        {"nbgeq1",      "Stop0l_nbtags_JESUp>=1"},
        {"nb2",         "Stop0l_nbtags_JESUp>=2"},
        {"nbeq2",       "Stop0l_nbtags_JESUp==2"},
        {"nb3",         "Stop0l_nbtags_JESUp>=3"},
        {"nivf0",       "Stop0l_nSoftb==0"},
        {"nivf1",       "Stop0l_nSoftb>=1"},
        {"lowptisr",    "Stop0l_ISRJetPt_JESUp>=300 && Stop0l_ISRJetPt_JESUp<500"},
        {"medptisr",    "Stop0l_ISRJetPt_JESUp>=300"},
        {"highptisr",   "Stop0l_ISRJetPt_JESUp>=500"},
        {"nj2to5",      "Stop0l_nJets_JESUp>=2 && Stop0l_nJets_JESUp<=5"},
        {"nj6",         "Stop0l_nJets_JESUp>=6"},
        {"nj7",         "Stop0l_nJets_JESUp>=7"},
        {"lowmtb",      "Stop0l_Mtb_JESUp<175"},
        {"highmtb",     "Stop0l_Mtb_JESUp>=175"},
        {"lowptb",      "Stop0l_Ptb_JESUp<40"},
        {"medptb",      "Stop0l_Ptb_JESUp>=40 && Stop0l_Ptb_JESUp<70"},
        {"highptb",     "Stop0l_Ptb_JESUp>=70"},
        {"lowptb12",    "Stop0l_Ptb_JESUp<80"},
        {"medptb12",    "Stop0l_Ptb_JESUp>=80 && Stop0l_Ptb_JESUp<140"},
        {"highptb12",   "Stop0l_Ptb_JESUp>=140"},
        {"nt0",         "Stop0l_nTop_JESUp==0"},
        {"nt1",         "Stop0l_nTop_JESUp==1"},
        {"nt2",         "Stop0l_nTop_JESUp==2"},
        {"ntgeq1",      "Stop0l_nTop_JESUp>=1"},
        {"nw0",         "Stop0l_nW_JESUp==0"},
        {"nw1",         "Stop0l_nW_JESUp==1"},
        {"nw2",         "Stop0l_nW_JESUp==2"},
        {"nwgeq1",      "Stop0l_nW_JESUp>=1"},
        {"nrt0",        "Stop0l_nResolved_JESUp==0"},
        {"nrt1",        "Stop0l_nResolved_JESUp==1"},
        {"nrt2",        "Stop0l_nResolved_JESUp==2"},
        {"nrtgeq1",     "Stop0l_nResolved_JESUp>=1"},
        {"nrtntnwgeq2", "(Stop0l_nTop_JESUp+Stop0l_nResolved_JESUp+Stop0l_nW_JESUp) >= 2"},
        {"nrtntnwgeq3", "(Stop0l_nTop_JESUp+Stop0l_nResolved_JESUp+Stop0l_nW_JESUp) >= 3"},
        {"htgt1000",    "Stop0l_HT_JESUp>=1000"},
        {"htlt1000",    "Stop0l_HT_JESUp<1000"},
        {"ht1000to1500","Stop0l_HT_JESUp>=1000 && Stop0l_HT_JESUp<1500"},
        {"htgt1500",    "Stop0l_HT_JESUp>=1500"},
        {"htlt1300",    "Stop0l_HT_JESUp<1300"},
        {"htgt1300",    "Stop0l_HT_JESUp>=1300"},

    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();

std::map<TString, TString> cutMap_JESDown = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt_JESDown>=300 && Stop0l_Mtb_JESDown < 175 && Stop0l_nTop_JESDown==0 && Stop0l_nW_JESDown==0 && Stop0l_nResolved_JESDown==0 && Stop0l_METSig_JESDown>=10"},
        {"dPhiLM",      "Pass_dPhiMETLowDM_JESDown"},
        {"hmNoDPhi",    "Stop0l_nJets_JESDown>=5 && Stop0l_nbtags_JESDown>=1"},
        {"dPhiHM",      "Pass_dPhiMETHighDM_JESDown"},
        {"invertDPhi",  "Pass_dPhiQCD_JESDown"},
 
        {"nb0",         "Stop0l_nbtags_JESDown==0"},
        {"nb1",         "Stop0l_nbtags_JESDown==1"},
        {"nbgeq1",      "Stop0l_nbtags_JESDown>=1"},
        {"nb2",         "Stop0l_nbtags_JESDown>=2"},
        {"nbeq2",       "Stop0l_nbtags_JESDown==2"},
        {"nb3",         "Stop0l_nbtags_JESDown>=3"},
        {"nivf0",       "Stop0l_nSoftb==0"},
        {"nivf1",       "Stop0l_nSoftb>=1"},
        {"lowptisr",    "Stop0l_ISRJetPt_JESDown>=300 && Stop0l_ISRJetPt_JESDown<500"},
        {"medptisr",    "Stop0l_ISRJetPt_JESDown>=300"},
        {"highptisr",   "Stop0l_ISRJetPt_JESDown>=500"},
        {"nj2to5",      "Stop0l_nJets_JESDown>=2 && Stop0l_nJets_JESDown<=5"},
        {"nj6",         "Stop0l_nJets_JESDown>=6"},
        {"nj7",         "Stop0l_nJets_JESDown>=7"},
        {"lowmtb",      "Stop0l_Mtb_JESDown<175"},
        {"highmtb",     "Stop0l_Mtb_JESDown>=175"},
        {"lowptb",      "Stop0l_Ptb_JESDown<40"},
        {"medptb",      "Stop0l_Ptb_JESDown>=40 && Stop0l_Ptb_JESDown<70"},
        {"highptb",     "Stop0l_Ptb_JESDown>=70"},
        {"lowptb12",    "Stop0l_Ptb_JESDown<80"},
        {"medptb12",    "Stop0l_Ptb_JESDown>=80 && Stop0l_Ptb_JESDown<140"},
        {"highptb12",   "Stop0l_Ptb_JESDown>=140"},
        {"nt0",         "Stop0l_nTop_JESDown==0"},
        {"nt1",         "Stop0l_nTop_JESDown==1"},
        {"nt2",         "Stop0l_nTop_JESDown==2"},
        {"ntgeq1",      "Stop0l_nTop_JESDown>=1"},
        {"nw0",         "Stop0l_nW_JESDown==0"},
        {"nw1",         "Stop0l_nW_JESDown==1"},
        {"nw2",         "Stop0l_nW_JESDown==2"},
        {"nwgeq1",      "Stop0l_nW_JESDown>=1"},
        {"nrt0",        "Stop0l_nResolved_JESDown==0"},
        {"nrt1",        "Stop0l_nResolved_JESDown==1"},
        {"nrt2",        "Stop0l_nResolved_JESDown==2"},
        {"nrtgeq1",     "Stop0l_nResolved_JESDown>=1"},
        {"nrtntnwgeq2", "(Stop0l_nTop_JESDown+Stop0l_nResolved_JESDown+Stop0l_nW_JESDown) >= 2"},
        {"nrtntnwgeq3", "(Stop0l_nTop_JESDown+Stop0l_nResolved_JESDown+Stop0l_nW_JESDown) >= 3"},
        {"htgt1000",    "Stop0l_HT_JESDown>=1000"},
        {"htlt1000",    "Stop0l_HT_JESDown<1000"},
        {"ht1000to1500","Stop0l_HT_JESDown>=1000 && Stop0l_HT_JESDown<1500"},
        {"htgt1500",    "Stop0l_HT_JESDown>=1500"},
        {"htlt1300",    "Stop0l_HT_JESDown<1300"},
        {"htgt1300",    "Stop0l_HT_JESDown>=1300"},

    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();

std::map<TString, TString> cutMap_METUnClustUp = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt_METUnClustUp>=300 && Stop0l_Mtb_METUnClustUp < 175 && Stop0l_nTop_METUnClustUp==0 && Stop0l_nW_METUnClustUp==0 && Stop0l_nResolved_METUnClustUp==0 && Stop0l_METSig_METUnClustUp>=10"},
        {"dPhiLM",      "Pass_dPhiMETLowDM_METUnClustUp"},
        {"hmNoDPhi",    "Stop0l_nJets_METUnClustUp>=5 && Stop0l_nbtags_METUnClustUp>=1"},
        {"dPhiHM",      "Pass_dPhiMETHighDM_METUnClustUp"},
        {"invertDPhi",  "Pass_dPhiQCD_METUnClustUp"},
 
        {"nb0",         "Stop0l_nbtags_METUnClustUp==0"},
        {"nb1",         "Stop0l_nbtags_METUnClustUp==1"},
        {"nbgeq1",      "Stop0l_nbtags_METUnClustUp>=1"},
        {"nb2",         "Stop0l_nbtags_METUnClustUp>=2"},
        {"nbeq2",       "Stop0l_nbtags_METUnClustUp==2"},
        {"nb3",         "Stop0l_nbtags_METUnClustUp>=3"},
        {"nivf0",       "Stop0l_nSoftb==0"},
        {"nivf1",       "Stop0l_nSoftb>=1"},
        {"lowptisr",    "Stop0l_ISRJetPt_METUnClustUp>=300 && Stop0l_ISRJetPt_METUnClustUp<500"},
        {"medptisr",    "Stop0l_ISRJetPt_METUnClustUp>=300"},
        {"highptisr",   "Stop0l_ISRJetPt_METUnClustUp>=500"},
        {"nj2to5",      "Stop0l_nJets_METUnClustUp>=2 && Stop0l_nJets_METUnClustUp<=5"},
        {"nj6",         "Stop0l_nJets_METUnClustUp>=6"},
        {"nj7",         "Stop0l_nJets_METUnClustUp>=7"},
        {"lowmtb",      "Stop0l_Mtb_METUnClustUp<175"},
        {"highmtb",     "Stop0l_Mtb_METUnClustUp>=175"},
        {"lowptb",      "Stop0l_Ptb_METUnClustUp<40"},
        {"medptb",      "Stop0l_Ptb_METUnClustUp>=40 && Stop0l_Ptb_METUnClustUp<70"},
        {"highptb",     "Stop0l_Ptb_METUnClustUp>=70"},
        {"lowptb12",    "Stop0l_Ptb_METUnClustUp<80"},
        {"medptb12",    "Stop0l_Ptb_METUnClustUp>=80 && Stop0l_Ptb_METUnClustUp<140"},
        {"highptb12",   "Stop0l_Ptb_METUnClustUp>=140"},
        {"nt0",         "Stop0l_nTop_METUnClustUp==0"},
        {"nt1",         "Stop0l_nTop_METUnClustUp==1"},
        {"nt2",         "Stop0l_nTop_METUnClustUp==2"},
        {"ntgeq1",      "Stop0l_nTop_METUnClustUp>=1"},
        {"nw0",         "Stop0l_nW_METUnClustUp==0"},
        {"nw1",         "Stop0l_nW_METUnClustUp==1"},
        {"nw2",         "Stop0l_nW_METUnClustUp==2"},
        {"nwgeq1",      "Stop0l_nW_METUnClustUp>=1"},
        {"nrt0",        "Stop0l_nResolved_METUnClustUp==0"},
        {"nrt1",        "Stop0l_nResolved_METUnClustUp==1"},
        {"nrt2",        "Stop0l_nResolved_METUnClustUp==2"},
        {"nrtgeq1",     "Stop0l_nResolved_METUnClustUp>=1"},
        {"nrtntnwgeq2", "(Stop0l_nTop_METUnClustUp+Stop0l_nResolved_METUnClustUp+Stop0l_nW_METUnClustUp) >= 2"},
        {"nrtntnwgeq3", "(Stop0l_nTop_METUnClustUp+Stop0l_nResolved_METUnClustUp+Stop0l_nW_METUnClustUp) >= 3"},
        {"htgt1000",    "Stop0l_HT_METUnClustUp>=1000"},
        {"htlt1000",    "Stop0l_HT_METUnClustUp<1000"},
        {"ht1000to1500","Stop0l_HT_METUnClustUp>=1000 && Stop0l_HT_METUnClustUp<1500"},
        {"htgt1500",    "Stop0l_HT_METUnClustUp>=1500"},
        {"htlt1300",    "Stop0l_HT_METUnClustUp<1300"},
        {"htgt1300",    "Stop0l_HT_METUnClustUp>=1300"},

    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();

std::map<TString, TString> cutMap_METUnClustDown = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt_METUnClustDown>=300 && Stop0l_Mtb_METUnClustDown < 175 && Stop0l_nTop_METUnClustDown==0 && Stop0l_nW_METUnClustDown==0 && Stop0l_nResolved_METUnClustDown==0 && Stop0l_METSig_METUnClustDown>=10"},
        {"dPhiLM",      "Pass_dPhiMETLowDM_METUnClustDown"},
        {"hmNoDPhi",    "Stop0l_nJets_METUnClustDown>=5 && Stop0l_nbtags_METUnClustDown>=1"},
        {"dPhiHM",      "Pass_dPhiMETHighDM_METUnClustDown"},
        {"invertDPhi",  "Pass_dPhiQCD_METUnClustDown"},
 
        {"nb0",         "Stop0l_nbtags_METUnClustDown==0"},
        {"nb1",         "Stop0l_nbtags_METUnClustDown==1"},
        {"nbgeq1",      "Stop0l_nbtags_METUnClustDown>=1"},
        {"nb2",         "Stop0l_nbtags_METUnClustDown>=2"},
        {"nbeq2",       "Stop0l_nbtags_METUnClustDown==2"},
        {"nb3",         "Stop0l_nbtags_METUnClustDown>=3"},
        {"nivf0",       "Stop0l_nSoftb==0"},
        {"nivf1",       "Stop0l_nSoftb>=1"},
        {"lowptisr",    "Stop0l_ISRJetPt_METUnClustDown>=300 && Stop0l_ISRJetPt_METUnClustDown<500"},
        {"medptisr",    "Stop0l_ISRJetPt_METUnClustDown>=300"},
        {"highptisr",   "Stop0l_ISRJetPt_METUnClustDown>=500"},
        {"nj2to5",      "Stop0l_nJets_METUnClustDown>=2 && Stop0l_nJets_METUnClustDown<=5"},
        {"nj6",         "Stop0l_nJets_METUnClustDown>=6"},
        {"nj7",         "Stop0l_nJets_METUnClustDown>=7"},
        {"lowmtb",      "Stop0l_Mtb_METUnClustDown<175"},
        {"highmtb",     "Stop0l_Mtb_METUnClustDown>=175"},
        {"lowptb",      "Stop0l_Ptb_METUnClustDown<40"},
        {"medptb",      "Stop0l_Ptb_METUnClustDown>=40 && Stop0l_Ptb_METUnClustDown<70"},
        {"highptb",     "Stop0l_Ptb_METUnClustDown>=70"},
        {"lowptb12",    "Stop0l_Ptb_METUnClustDown<80"},
        {"medptb12",    "Stop0l_Ptb_METUnClustDown>=80 && Stop0l_Ptb_METUnClustDown<140"},
        {"highptb12",   "Stop0l_Ptb_METUnClustDown>=140"},
        {"nt0",         "Stop0l_nTop_METUnClustDown==0"},
        {"nt1",         "Stop0l_nTop_METUnClustDown==1"},
        {"nt2",         "Stop0l_nTop_METUnClustDown==2"},
        {"ntgeq1",      "Stop0l_nTop_METUnClustDown>=1"},
        {"nw0",         "Stop0l_nW_METUnClustDown==0"},
        {"nw1",         "Stop0l_nW_METUnClustDown==1"},
        {"nw2",         "Stop0l_nW_METUnClustDown==2"},
        {"nwgeq1",      "Stop0l_nW_METUnClustDown>=1"},
        {"nrt0",        "Stop0l_nResolved_METUnClustDown==0"},
        {"nrt1",        "Stop0l_nResolved_METUnClustDown==1"},
        {"nrt2",        "Stop0l_nResolved_METUnClustDown==2"},
        {"nrtgeq1",     "Stop0l_nResolved_METUnClustDown>=1"},
        {"nrtntnwgeq2", "(Stop0l_nTop_METUnClustDown+Stop0l_nResolved_METUnClustDown+Stop0l_nW_METUnClustDown) >= 2"},
        {"nrtntnwgeq3", "(Stop0l_nTop_METUnClustDown+Stop0l_nResolved_METUnClustDown+Stop0l_nW_METUnClustDown) >= 3"},
        {"htgt1000",    "Stop0l_HT_METUnClustDown>=1000"},
        {"htlt1000",    "Stop0l_HT_METUnClustDown<1000"},
        {"ht1000to1500","Stop0l_HT_METUnClustDown>=1000 && Stop0l_HT_METUnClustDown<1500"},
        {"htgt1500",    "Stop0l_HT_METUnClustDown>=1500"},
        {"htlt1300",    "Stop0l_HT_METUnClustDown<1300"},
        {"htgt1300",    "Stop0l_HT_METUnClustDown>=1300"},

    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();

std::vector<TString> srbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  "lm_nb0_nivf0_highptisr_nj2to5",
  "lm_nb0_nivf0_highptisr_nj6",
  "lm_nb0_nivf1_highptisr_nj2to5",
  "lm_nb0_nivf1_highptisr_nj6",

  // 1b, 0 or >=1 ivf
  "lm_nb1_nivf0_lowmtb_lowptisr_lowptb",
  "lm_nb1_nivf0_lowmtb_lowptisr_medptb",
  "lm_nb1_nivf0_lowmtb_highptisr_lowptb",
  "lm_nb1_nivf0_lowmtb_highptisr_medptb",
  // ---
  "lm_nb1_nivf1_lowmtb_medptisr_lowptb",

  // 2b
  "lm_nb2_lowmtb_lowptisr_lowptb12",
  "lm_nb2_lowmtb_lowptisr_medptb12",
  "lm_nb2_lowmtb_lowptisr_highptb12_nj7",
  "lm_nb2_lowmtb_highptisr_lowptb12",
  "lm_nb2_lowmtb_highptisr_medptb12",
  "lm_nb2_lowmtb_highptisr_highptb12_nj7",
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  "hm_nb1_lowmtb_nj7_nrtgeq1",
  "hm_nb2_lowmtb_nj7_nrtgeq1",

  // high mtb
  // 0 taggged
  "hm_nb1_highmtb_nt0_nrt0_nw0_ht1000to1300",
  "hm_nb1_highmtb_nt0_nrt0_nw0_ht1300to1500",
  "hm_nb1_highmtb_nt0_nrt0_nw0_htgt1500",

  // nb1
  // 1 tagged
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1300",
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1300to1500",
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",
  "hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1000",
  "hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1000to1300",
  "hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1300to1500",
  "hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1500",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1300",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1300to1500",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",

  // 1+1
  "hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htlt1000",
  "hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1000to1300",
  "hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1300to1500",
  "hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htgt1500",
  "hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htlt1000",
  "hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1000to1300",
  "hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1300to1500",
  "hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htgt1500",
  "hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htlt1000",
  "hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1000to1300",
  "hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1300to1500",
  "hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htgt1500",

  // nb2
  "hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw0_htgt1500",
  // 1 tagged
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",

  // 1+1eq
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",

  // 2
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",

  // 3
  "hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",
  "hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",
  "hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",
  "hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",

  // nb3
  "hm_nb3_highmtb_nt0_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt0_nw0_htgt1500",
  //1 tagged
  "hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",
  "hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",
  "hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",
  "hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",

  //1+1
  "hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",
  "hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",
  "hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",
  "hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",
  "hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",

  //2
  "hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",
  "hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",
  "hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",
  "hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",
  "hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",

  // 3
  "hm_nb3_highmtb_nrtntnwgeq3_htlt1000",
  "hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",
  "hm_nb3_highmtb_nrtntnwgeq3_htgt1500",
  
  //---------- high deltaM ----------

};

std::map<TString, TString> srcuts = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap);
    return cuts;
}();

std::map<TString, TString> srcuts_JESUp = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap_JESUp);
    return cuts;
}();

std::map<TString, TString> srcuts_JESDown = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap_JESDown);
    return cuts;
}();

std::map<TString, TString> srcuts_METUnClustUp = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap_METUnClustUp);
    return cuts;
}();

std::map<TString, TString> srcuts_METUnClustDown = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap_METUnClustDown);
    return cuts;
}();

std::map<TString, TString> srlabels = []{
    std::map<TString, TString> cmap;
    for (auto s: srbins) cmap[s] = s;
    return cmap;
}();

std::map<TString, std::vector<int>> srMETbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              {     450, 550, 650, 750, 1000}},
  {"lm_nb0_nivf0_highptisr_nj6",                 {     450, 550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj2to5",              {     450, 550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj6",                 {     450, 550, 650, 750, 1000}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb",        {300, 400, 500, 600, 1000}},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb",        {300, 400, 500, 600, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",            {450, 550, 650, 750, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",            {450, 550, 650, 750, 1000}},

  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb",                 {300, 400, 500, 1000}},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12",            {300, 400, 500, 1000}},
  {"lm_nb2_lowmtb_lowptisr_medptb12",            {300, 400, 500, 1000}},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7",       {300, 400, 500, 1000}},
  {"lm_nb2_lowmtb_highptisr_lowptb12",                {450, 550, 650, 1000}},
  {"lm_nb2_lowmtb_highptisr_medptb12",                {450, 550, 650, 1000}},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7",           {450, 550, 650, 1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                    {250, 300, 400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                    {250, 300, 400, 500, 1000}},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1000to1300",     {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1300to1500",     {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 650, 1000}},

  // nb1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1300",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1300to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1000to1300",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1300to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1500",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1300",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1300to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htlt1000",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1000to1300",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1300to1500",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htgt1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htlt1000",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1000to1300",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1300to1500",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htgt1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htlt1000",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1000to1300",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1300to1500",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htgt1500",   {250, 350, 450, 550, 650, 1000}},

  // nb2
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  //1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  
  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",       {250, 350, 450, 550, 650, 1000}},

        // nb3
  {"hm_nb3_highmtb_nt0_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",         {250, 350, 450, 550, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",         {250, 350, 450, 550, 1000}},
  
  //---------- high deltaM ----------

};

// normalization cuts for Rz
std::map<TString, TString> normMap{
  {"lm_nb0_nivf0", createCutString("lmNoDPhi_nb0_nivf0", cutMap)},
  {"lm_nb0_nivf1", createCutString("lmNoDPhi_nb0_nivf1", cutMap)},
  {"lm_nb1_nivf0", createCutString("lmNoDPhi_nb1_nivf0", cutMap)},
  {"lm_nb1_nivf1", createCutString("lmNoDPhi_nb1_nivf1", cutMap)},
  {"lm_nb2",       createCutString("lmNoDPhi_nb2", cutMap)},

  {"hm_nb1",       createCutString("hmNoDPhi_nb1", cutMap)},
  {"hm_nb2",       createCutString("hmNoDPhi_nb2", cutMap)},
};

std::map<TString, TString> normMap_JESUp{
  {"lm_nb0_nivf0", createCutString("lmNoDPhi_nb0_nivf0", cutMap_JESUp)},
  {"lm_nb0_nivf1", createCutString("lmNoDPhi_nb0_nivf1", cutMap_JESUp)},
  {"lm_nb1_nivf0", createCutString("lmNoDPhi_nb1_nivf0", cutMap_JESUp)},
  {"lm_nb1_nivf1", createCutString("lmNoDPhi_nb1_nivf1", cutMap_JESUp)},
  {"lm_nb2",       createCutString("lmNoDPhi_nb2", cutMap_JESUp)},

  {"hm_nb1",       createCutString("hmNoDPhi_nb1", cutMap_JESUp)},
  {"hm_nb2",       createCutString("hmNoDPhi_nb2", cutMap_JESUp)},
};

std::map<TString, TString> normMap_JESDown{
  {"lm_nb0_nivf0", createCutString("lmNoDPhi_nb0_nivf0", cutMap_JESDown)},
  {"lm_nb0_nivf1", createCutString("lmNoDPhi_nb0_nivf1", cutMap_JESDown)},
  {"lm_nb1_nivf0", createCutString("lmNoDPhi_nb1_nivf0", cutMap_JESDown)},
  {"lm_nb1_nivf1", createCutString("lmNoDPhi_nb1_nivf1", cutMap_JESDown)},
  {"lm_nb2",       createCutString("lmNoDPhi_nb2", cutMap_JESDown)},

  {"hm_nb1",       createCutString("hmNoDPhi_nb1", cutMap_JESDown)},
  {"hm_nb2",       createCutString("hmNoDPhi_nb2", cutMap_JESDown)},
};

std::map<TString, TString> normMap_METUnClustUp{
  {"lm_nb0_nivf0", createCutString("lmNoDPhi_nb0_nivf0", cutMap_METUnClustUp)},
  {"lm_nb0_nivf1", createCutString("lmNoDPhi_nb0_nivf1", cutMap_METUnClustUp)},
  {"lm_nb1_nivf0", createCutString("lmNoDPhi_nb1_nivf0", cutMap_METUnClustUp)},
  {"lm_nb1_nivf1", createCutString("lmNoDPhi_nb1_nivf1", cutMap_METUnClustUp)},
  {"lm_nb2",       createCutString("lmNoDPhi_nb2", cutMap_METUnClustUp)},

  {"hm_nb1",       createCutString("hmNoDPhi_nb1", cutMap_METUnClustUp)},
  {"hm_nb2",       createCutString("hmNoDPhi_nb2", cutMap_METUnClustUp)},
};

std::map<TString, TString> normMap_METUnClustDown{
  {"lm_nb0_nivf0", createCutString("lmNoDPhi_nb0_nivf0", cutMap_METUnClustDown)},
  {"lm_nb0_nivf1", createCutString("lmNoDPhi_nb0_nivf1", cutMap_METUnClustDown)},
  {"lm_nb1_nivf0", createCutString("lmNoDPhi_nb1_nivf0", cutMap_METUnClustDown)},
  {"lm_nb1_nivf1", createCutString("lmNoDPhi_nb1_nivf1", cutMap_METUnClustDown)},
  {"lm_nb2",       createCutString("lmNoDPhi_nb2", cutMap_METUnClustDown)},

  {"hm_nb1",       createCutString("hmNoDPhi_nb1", cutMap_METUnClustDown)},
  {"hm_nb2",       createCutString("hmNoDPhi_nb2", cutMap_METUnClustDown)},
};

// normalize photon to Data after baseline+this cut to calc Sgamma
std::map<TString, TString> phoNormMap = []{
  if (ICHEPCR) return normMap;
  else return std::map<TString, TString>{
    {"lm_nb0", createCutString("lmNoDPhi_nb0", cutMap)},
    {"lm_nb1", createCutString("lmNoDPhi_nb1", cutMap)},
    {"lm_nb2", createCutString("lmNoDPhi_nb2", cutMap)},

    {"hm_nb1", createCutString("hmNoDPhi_nb1", cutMap)},
    {"hm_nb2", createCutString("hmNoDPhi_nb2", cutMap)},
  };
}();

std::map<TString, TString> phoNormMap_JESUp = []{
  if (ICHEPCR) return normMap_JESUp;
  else return std::map<TString, TString>{
    {"lm_nb0", createCutString("lmNoDPhi_nb0", cutMap_JESUp)},
    {"lm_nb1", createCutString("lmNoDPhi_nb1", cutMap_JESUp)},
    {"lm_nb2", createCutString("lmNoDPhi_nb2", cutMap_JESUp)},

    {"hm_nb1", createCutString("hmNoDPhi_nb1", cutMap_JESUp)},
    {"hm_nb2", createCutString("hmNoDPhi_nb2", cutMap_JESUp)},
  };
}();

std::map<TString, TString> phoNormMap_JESDown = []{
  if (ICHEPCR) return normMap_JESDown;
  else return std::map<TString, TString>{
    {"lm_nb0", createCutString("lmNoDPhi_nb0", cutMap_JESDown)},
    {"lm_nb1", createCutString("lmNoDPhi_nb1", cutMap_JESDown)},
    {"lm_nb2", createCutString("lmNoDPhi_nb2", cutMap_JESDown)},

    {"hm_nb1", createCutString("hmNoDPhi_nb1", cutMap_JESDown)},
    {"hm_nb2", createCutString("hmNoDPhi_nb2", cutMap_JESDown)},
  };
}();

std::map<TString, TString> phoNormMap_METUnClustUp = []{
  if (ICHEPCR) return normMap_METUnClustUp;
  else return std::map<TString, TString>{
    {"lm_nb0", createCutString("lmNoDPhi_nb0", cutMap_METUnClustUp)},
    {"lm_nb1", createCutString("lmNoDPhi_nb1", cutMap_METUnClustUp)},
    {"lm_nb2", createCutString("lmNoDPhi_nb2", cutMap_METUnClustUp)},

    {"hm_nb1", createCutString("hmNoDPhi_nb1", cutMap_METUnClustUp)},
    {"hm_nb2", createCutString("hmNoDPhi_nb2", cutMap_METUnClustUp)},
  };
}();

std::map<TString, TString> phoNormMap_METUnClustDown = []{
  if (ICHEPCR) return normMap_METUnClustDown;
  else return std::map<TString, TString>{
    {"lm_nb0", createCutString("lmNoDPhi_nb0", cutMap_METUnClustDown)},
    {"lm_nb1", createCutString("lmNoDPhi_nb1", cutMap_METUnClustDown)},
    {"lm_nb2", createCutString("lmNoDPhi_nb2", cutMap_METUnClustDown)},

    {"hm_nb1", createCutString("hmNoDPhi_nb1", cutMap_METUnClustDown)},
    {"hm_nb2", createCutString("hmNoDPhi_nb2", cutMap_METUnClustDown)},
  };
}();

//std::map<TString, TString> phoNormMap = normMap;

std::map<TString, TString> phocrMapping{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              "lm_nb0_nivf0_highptisr_nj2to5"},
  {"lm_nb0_nivf0_highptisr_nj6",                 "lm_nb0_nivf0_highptisr_nj6"},
  {"lm_nb0_nivf1_highptisr_nj2to5",              "lm_nb0_nivf1_highptisr_nj2to5"},
  {"lm_nb0_nivf1_highptisr_nj6",                 "lm_nb0_nivf1_highptisr_nj6"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb",        "lm_nb1_nivf0_lowmtb_lowptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb",        "lm_nb1_nivf0_lowmtb_lowptisr_medptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",       "lm_nb1_nivf0_lowmtb_highptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",       "lm_nb1_nivf0_lowmtb_highptisr_medptb"},
  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb",                 "lm_nb1_nivf1_lowmtb_medptisr_lowptb"},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12",            "lm_nb2_lowmtb_lowptisr_lowptb12"},
  {"lm_nb2_lowmtb_lowptisr_medptb12",            "lm_nb2_lowmtb_lowptisr_medptb12"},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7",       "lm_nb2_lowmtb_lowptisr_highptb12_nj7"},
  {"lm_nb2_lowmtb_highptisr_lowptb12",           "lm_nb2_lowmtb_highptisr_lowptb12"},
  {"lm_nb2_lowmtb_highptisr_medptb12",           "lm_nb2_lowmtb_highptisr_medptb12"},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7",      "lm_nb2_lowmtb_highptisr_highptb12_nj7"},
  //---------- low deltaM ----------

  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                         "hm_nb1_lowmtb_nj7_nrtgeq1"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                         "hm_nb2_lowmtb_nj7_nrtgeq1"},
  
  // high mtb                                          
  // 0 taggged                                         
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1000to1300",          "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1300to1500",          "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1500",              "hm_nb1_highmtb_htgt1500"},

  // nb1                                               
  // 1 tagged                                          
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",           "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1300",       "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1300to1500",       "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",           "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1000",           "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1000to1300",       "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1300to1500",       "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1500",           "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",           "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1300",       "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1300to1500",       "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",           "hm_nb1_highmtb_htgt1500"},

  // 1+1                                               
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htlt1000",        "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1000to1300",    "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1300to1500",    "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htgt1500",        "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htlt1000",        "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1000to1300",    "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1300to1500",    "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htgt1500",        "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htlt1000",        "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1000to1300",    "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1300to1500",    "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htgt1500",        "hm_nb1_highmtb_htgt1500"},

  // nb2                                               
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  // 1 tagged                                          
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 1+1eq                                             
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 2                                                 
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 3                                                 
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",             "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",         "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",         "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",             "hm_nbeq2_highmtb_htgt1500"},

  // nb3                                               
  {"hm_nb3_highmtb_nt0_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  //1 tagged                                           
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //1+1                                                
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //2                                                  
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  
  // 3                                                 
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",               "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",           "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",               "hm_nb3_highmtb_htgt1500"},
  
  //---------- high deltaM ----------

};


std::map<TString, TString> phocrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap);
    return cuts;
}();

std::map<TString, TString> phocrCuts_JESUp = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_JESUp);
    return cuts;
}();

std::map<TString, TString> phocrCuts_JESDown = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_JESDown);
    return cuts;
}();

std::map<TString, TString> phocrCuts_METUnClustUp = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_METUnClustUp);
    return cuts;
}();

std::map<TString, TString> phocrCuts_METUnClustDown = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_METUnClustDown);
    return cuts;
}();

std::map<TString, TString> phocrlabels = phocrMapping;

std::map<TString, std::vector<int>> phocrMETbins = srMETbins;


std::map<TString, TString> lepcrMapping {
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              "lm_nb0_nivf0_highptisr_nj2to5"},
  {"lm_nb0_nivf0_highptisr_nj6",                 "lm_nb0_nivf0_highptisr_nj6"},
  {"lm_nb0_nivf1_highptisr_nj2to5",              "lm_nb0_nivf1_highptisr_nj2to5"},
  {"lm_nb0_nivf1_highptisr_nj6",                 "lm_nb0_nivf1_highptisr_nj6"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb",        "lm_nb1_nivf0_lowmtb_lowptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb",        "lm_nb1_nivf0_lowmtb_lowptisr_medptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",       "lm_nb1_nivf0_lowmtb_highptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",       "lm_nb1_nivf0_lowmtb_highptisr_medptb"},
  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb",                 "lm_nb1_nivf1_lowmtb_medptisr_lowptb"},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12",            "lm_nb2_lowmtb_lowptisr_lowptb12"},
  {"lm_nb2_lowmtb_lowptisr_medptb12",            "lm_nb2_lowmtb_lowptisr_medptb12"},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7",       "lm_nb2_lowmtb_lowptisr_highptb12_nj7"},
  {"lm_nb2_lowmtb_highptisr_lowptb12",           "lm_nb2_lowmtb_highptisr_lowptb12"},
  {"lm_nb2_lowmtb_highptisr_medptb12",           "lm_nb2_lowmtb_highptisr_medptb12"},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7",      "lm_nb2_lowmtb_highptisr_highptb12_nj7"},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                         "hm_nb1_lowmtb_nj7_nrtgeq1"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                         "hm_nb2_lowmtb_nj7_nrtgeq1"},
  
  // high mtb                                          
  // 0 taggged                                         
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1000to1300",          "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1300to1500",          "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1500",              "hm_nb1_highmtb_htgt1500"},

  // nb1                                               
  // 1 tagged                                          
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",           "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1300",       "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1300to1500",       "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",           "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1000",           "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1000to1300",       "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1300to1500",       "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1500",           "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",           "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1300",       "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1300to1500",       "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",           "hm_nb1_highmtb_htgt1500"},

  // 1+1                                               
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htlt1000",        "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1000to1300",    "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1300to1500",    "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htgt1500",        "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htlt1000",        "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1000to1300",    "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1300to1500",    "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htgt1500",        "hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htlt1000",        "hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1000to1300",    "hm_nb1_highmtb_ht1000to1300"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1300to1500",    "hm_nb1_highmtb_ht1300to1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htgt1500",        "hm_nb1_highmtb_htgt1500"},

  // nb2                                               
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  // 1 tagged                                          
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 1+1eq                                             
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 2                                                 
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 3                                                 
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",             "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",         "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",         "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",             "hm_nbeq2_highmtb_htgt1500"},

  // nb3                                               
  {"hm_nb3_highmtb_nt0_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  //1 tagged                                           
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //1+1                                                
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //2                                                  
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  
  // 3                                                 
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",               "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",           "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",               "hm_nb3_highmtb_htgt1500"},
  
  //---------- high deltaM ----------

};


std::map<TString, TString> lepcrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap);
    return cuts;
}();

std::map<TString, TString> lepcrCuts_JESUp = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_JESUp);
    return cuts;
}();

std::map<TString, TString> lepcrCuts_JESDown = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_JESDown);
    return cuts;
}();

std::map<TString, TString> lepcrCuts_METUnClustUp = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_METUnClustUp);
    return cuts;
}();

std::map<TString, TString> lepcrCuts_METUnClustDown = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_METUnClustDown);
    return cuts;
}();

std::map<TString, TString> lepcrlabels = lepcrMapping;
std::map<TString, std::vector<int>> lepcrMETbins = srMETbins;

// qcd-cr: inverted dPhi cut applied on CR samples now
std::map<TString, TString> qcdcrMapping =[]{
  auto crmap = lepcrMapping;
  for (auto &s : crmap){
    s.second.ReplaceAll("lowmtb_nj7", "lowmtb_nj7_nrtgeq1");
    s.second.ReplaceAll("lm_", "lmNoDPhi_");
    s.second.ReplaceAll("hm_", "hmNoDPhi_");
  }
  return crmap;
}();
std::map<TString, TString> qcdcrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : qcdcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap);
    return cuts;
}();
std::map<TString, TString> qcdcrCuts_JESUp = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : qcdcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_JESUp);
    return cuts;
}();
std::map<TString, TString> qcdcrCuts_JESDown = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : qcdcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_JESDown);
    return cuts;
}();
std::map<TString, TString> qcdcrCuts_METUnClustUp = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : qcdcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_METUnClustUp);
    return cuts;
}();
std::map<TString, TString> qcdcrCuts_METUnClustDown = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : qcdcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap_METUnClustDown);
    return cuts;
}();
std::map<TString, TString> qcd1to1crCuts = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins){
      TString crname = name;
      crname.ReplaceAll("lm_", "lmNoDPhi_");
      crname.ReplaceAll("hm_", "hmNoDPhi_");
      cuts[name] = createCutString(crname, cutMap);
    }
    return cuts;
}();
std::map<TString, TString> qcd1to1crCuts_JESUp = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins){
      TString crname = name;
      crname.ReplaceAll("lm_", "lmNoDPhi_");
      crname.ReplaceAll("hm_", "hmNoDPhi_");
      cuts[name] = createCutString(crname, cutMap_JESUp);
    }
    return cuts;
}();
std::map<TString, TString> qcd1to1crCuts_JESDown = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins){
      TString crname = name;
      crname.ReplaceAll("lm_", "lmNoDPhi_");
      crname.ReplaceAll("hm_", "hmNoDPhi_");
      cuts[name] = createCutString(crname, cutMap_JESDown);
    }
    return cuts;
}();
std::map<TString, TString> qcd1to1crCuts_METUnClustUp = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins){
      TString crname = name;
      crname.ReplaceAll("lm_", "lmNoDPhi_");
      crname.ReplaceAll("hm_", "hmNoDPhi_");
      cuts[name] = createCutString(crname, cutMap_METUnClustUp);
    }
    return cuts;
}();
std::map<TString, TString> qcd1to1crCuts_METUnClustDown = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins){
      TString crname = name;
      crname.ReplaceAll("lm_", "lmNoDPhi_");
      crname.ReplaceAll("hm_", "hmNoDPhi_");
      cuts[name] = createCutString(crname, cutMap_METUnClustDown);
    }
    return cuts;
}();
std::map<TString, TString> qcdcrlabels = lepcrlabels;
std::map<TString, std::vector<int>> qcdcrMETbins {
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              {     450, 550, 650, 750, 1000}},
  {"lm_nb0_nivf0_highptisr_nj6",                 {     450, 550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj2to5",              {     450, 550, 650,      1000}}, // merge last 2 bins
  {"lm_nb0_nivf1_highptisr_nj6",                 {     450,                1000}}, // merge last 3 bins
  
  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb",        {300, 400,           1000}}, // merge last 3 bins
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb",        {300, 400,           1000}}, // merge last 3 bins
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",            {450, 550, 650,      1000}}, // merge last 2 bins
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",            {450, 550, 650,      1000}}, // merge last 2 bins
  
  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb",                 {300, 400,      1000}}, // merge last 2 bins
  
  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12",            {300,           1000}}, // merge all 3 bins
  {"lm_nb2_lowmtb_lowptisr_medptb12",            {300, 400,      1000}}, // merge last 2 bins
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7",       {300, 400,      1000}}, // merge last 2 bins
  {"lm_nb2_lowmtb_highptisr_lowptb12",                {450,           1000}}, // merge all 3 bins
  {"lm_nb2_lowmtb_highptisr_medptb12",                {450,           1000}}, // merge all 3 bins
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7",           {450, 550,      1000}}, // merge last 2 bins
  //---------- low deltaM ----------
  
  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                    {250, 300, 400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                    {250, 300, 400, 500, 1000}},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1000to1300",     {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_ht1300to1500",     {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 650, 1000}},

  // nb1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1300",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1300to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1000to1300",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_ht1300to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1500",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1300",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1300to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htlt1000",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1000to1300",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_ht1300to1500",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_htgt1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htlt1000",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1000to1300",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_ht1300to1500",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_htgt1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htlt1000",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1000to1300",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_ht1300to1500",{250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_htgt1500",   {250, 350, 450, 550, 650, 1000}},

  // nb2
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  //1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  
  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",       {250, 350, 450, 550, 650, 1000}},

        // nb3
  {"hm_nb3_highmtb_nt0_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",         {250, 350, 450, 550, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",         {250, 350, 450, 550, 1000}},
  
  //---------- high deltaM ----------

};

map<TString, Category> srCatMap(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts.at(name), srlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> srCatMap_JESUp(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts_JESUp.at(name), srlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> srCatMap_JESDown(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts_JESDown.at(name), srlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> srCatMap_METUnClustUp(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts_METUnClustUp.at(name), srlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> srCatMap_METUnClustDown(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts_METUnClustDown.at(name), srlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts: phocrCuts;
  const auto &labels = ICHEPCR ? srlabels: phocrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap_JESUp(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_JESUp: phocrCuts_JESUp;
  const auto &labels = ICHEPCR ? srlabels: phocrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap_JESDown(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_JESDown: phocrCuts_JESDown;
  const auto &labels = ICHEPCR ? srlabels: phocrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap_METUnClustUp(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_METUnClustUp: phocrCuts_METUnClustUp;
  const auto &labels = ICHEPCR ? srlabels: phocrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap_METUnClustDown(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_METUnClustDown: phocrCuts_METUnClustDown;
  const auto &labels = ICHEPCR ? srlabels: phocrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts: lepcrCuts;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap_JESUp(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_JESUp: lepcrCuts_JESUp;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap_JESDown(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_JESDown: lepcrCuts_JESDown;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap_METUnClustUp(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_METUnClustUp: lepcrCuts_METUnClustUp;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap_METUnClustDown(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts_METUnClustDown: lepcrCuts_METUnClustDown;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts: qcdcrCuts;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap_JESUp(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts_JESUp: qcdcrCuts_JESUp;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap_JESDown(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts_JESDown: qcdcrCuts_JESDown;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap_METUnClustUp(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts_METUnClustUp: qcdcrCuts_METUnClustUp;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap_METUnClustDown(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts_METUnClustDown: qcdcrCuts_METUnClustDown;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> zllCatMap{
  {"on-z",  Category("on-z",  "dilepmass > 80 && dilepmass < 100",                      "on Z",   BinInfo("MET_pt", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))},
  {"off-z", Category("off-z", "dilepmass > 50 && (dilepmass < 80 || dilepmass > 100)",  "off Z",  BinInfo("MET_pt", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))}
};


// ------------------------------------------------------------------------
// samples

BaseConfig phoConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/znunu";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("singlepho",   "Data",           datadir+"/photoncr/singlepho",  "1.0",  datasel() + trigPhoCR);

  config.addSample("photon",      "Photon",         "photoncr/photon",     phowgt(), datasel() + trigPhoCR + phoBadEventRemoval);
//  config.addSample("photon",      "Photon",         "photoncr/gjets",      phowgt, datasel() + trigPhoCR);
  config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt(), datasel() + trigSR() + vetoes());

  config.sel = baseline();
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = phoCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig zllConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/zllcr";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("dyll",      "Z#rightarrowll+jets",    "zllcr/z-soup",                    lepselwgt(), datasel() + trigDiLepCR);
  config.addSample("ttbar",     "t#bar{t}",               "zllcr/t-soup",                    lepselwgt(), datasel() + trigDiLepCR);
  config.addSample("doublelep", "Data",                   datadir+"/zllcr/doublelep",       "1.0",     datasel() + trigDiLepCR);

  config.sel = baseline();
  config.catMaps = zllCatMap;
  for (auto &c : zllCatMap) config.categories.push_back(c.first);

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig lepConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/LLB";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

    // samples for cr categories
  if (ADD_LEP_TO_MET){
    config.addSample("singlelep",        "Data",          datadir+"met", 		   "1.0",       datasel() + trigLepCR + lepcrsel);
    config.addSample("ttbar-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           onelepcrwgt()+"*"+isrwgtvar(), datasel() + trigLepCR + lepcrsel);
    config.addSample("wjets-2016",       "W+jets",        inputdir_2016+"wjets",           onelepcrwgt(), datasel() + trigLepCR + lepcrsel);
    config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              onelepcrwgt(), datasel() + trigLepCR + lepcrsel);
    config.addSample("ttW-2016",         "ttW",           inputdir_2016+"ttW",             onelepcrwgt(), datasel() + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "lepcr/qcd",             onelepcrwgt, datasel() + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",        "Data",          datadir+"met",                   "1.0",          datasel() + trigSR() + revert_vetoes());
    config.addSample("ttbar-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt()+"*"+isrwgtvar(),      datasel() + revert_vetoes());
    config.addSample("wjets-2016",       "W+jets",        inputdir_2016+"wjets",           lepselwgt(),      datasel() + revert_vetoes());
    config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              lepselwgt(),      datasel() + revert_vetoes());
    config.addSample("ttW-2016",         "ttW",           inputdir_2016+"ttW",             lepselwgt(),      datasel() + revert_vetoes());
    config.addSample("ttZ-2016",         "ttZ",           inputdir_2016+"ttZ",             lepselwgt(),      datasel() + revert_vetoes());
    config.addSample("diboson-2016",     "Diboson",       inputdir_2016+"diboson",         lepselwgt(),      datasel() + revert_vetoes());
    config.addSample("qcd-2016",         "QCD",           inputdir_2016+"qcd",             lepselwgt(),      datasel() + revert_vetoes());

    config.addSample("ttbar-2017RunBtoE",         "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017(),      datasel() + revert_vetoes());
    config.addSample("wjets-2017RunBtoE",         "W+jets",        inputdir_2017+"wjets",           lepselwgt_2017(),      datasel() + revert_vetoes());
    config.addSample("tW-2017RunBtoE",            "tW",            inputdir_2017+"tW",              lepselwgt_2017(),      datasel() + revert_vetoes());
    config.addSample("ttW-2017RunBtoE",           "ttW",           inputdir_2017+"ttW",             lepselwgt_2017(),      datasel() + revert_vetoes());
    config.addSample("ttZ-2017RunBtoE",           "ttZ",           inputdir_2017+"ttZ",             lepselwgt_2017(),      datasel() + revert_vetoes());
    config.addSample("diboson-2017RunBtoE",       "Diboson",       inputdir_2017+"diboson",         lepselwgt_2017(),      datasel() + revert_vetoes());
    config.addSample("qcd-2017RunBtoE",           "QCD",           inputdir_2017+"qcd",             lepselwgt_2017(),      datasel() + revert_vetoes());

    config.addSample("ttbar-2018preHEM",         "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018(),      datasel() + revert_vetoes());
    config.addSample("wjets-2018preHEM",         "W+jets",        inputdir_2018+"wjets",           lepselwgt_2018(),      datasel() + revert_vetoes());
    config.addSample("tW-2018preHEM",            "tW",            inputdir_2018+"tW",              lepselwgt_2018(),      datasel() + revert_vetoes());
    config.addSample("ttW-2018preHEM",           "ttW",           inputdir_2018+"ttW",             lepselwgt_2018(),      datasel() + revert_vetoes());
    config.addSample("ttZ-2018preHEM",           "ttZ",           inputdir_2018+"ttZ",             lepselwgt_2018(),      datasel() + revert_vetoes());
    config.addSample("diboson-2018preHEM",       "Diboson",       inputdir_2018+"diboson",         lepselwgt_2018(),      datasel() + revert_vetoes());
    config.addSample("qcd-2018preHEM",           "QCD",           inputdir_2018+"qcd",             lepselwgt_2018(),      datasel() + revert_vetoes());
  }

  // samples for sr categories
  config.addSample("ttbar-2016-sr",       "t#bar{t}",      inputdir_2016+"ttbar",                lepvetowgt()+"*"+isrwgtvar(), datasel() + vetoes());
  config.addSample("wjets-2016-sr",       "W+jets",        inputdir_2016+"wjets",                lepvetowgt(), datasel() + vetoes());
  config.addSample("tW-2016-sr",          "tW",            inputdir_2016+"tW",                   lepvetowgt(), datasel() + vetoes());
  config.addSample("ttW-2016-sr",         "ttW",           inputdir_2016+"ttW",                  lepvetowgt(), datasel() + vetoes());
  config.addSample("ttZ-2016-sr",         "ttZ",           inputdir_2016+"ttZ",                  lepvetowgt(), datasel() + vetoes());
  config.addSample("diboson-2016-sr",     "Diboson",       inputdir_2016+"diboson",              lepvetowgt(), datasel() + vetoes());

  config.addSample("ttbar-2017RunBtoE-sr",    "t#bar{t}",      inputdir_2017+"ttbar",            lepvetowgt_2017(), datasel() + vetoes());
  config.addSample("wjets-2017RunBtoE-sr",    "W+jets",        inputdir_2017+"wjets",            lepvetowgt_2017(), datasel() + vetoes());
  config.addSample("tW-2017RunBtoE-sr",       "tW",            inputdir_2017+"tW",               lepvetowgt_2017(), datasel() + vetoes());
  config.addSample("ttW-2017RunBtoE-sr",      "ttW",           inputdir_2017+"ttW",              lepvetowgt_2017(), datasel() + vetoes());
  config.addSample("ttZ-2017RunBtoE-sr",      "ttZ",           inputdir_2017+"ttZ",              lepvetowgt_2017(), datasel() + vetoes());
  config.addSample("diboson-2017RunBtoE-sr",  "Diboson",       inputdir_2017+"diboson",          lepvetowgt_2017(), datasel() + vetoes());

  config.addSample("ttbar-2018preHEM-sr",    "t#bar{t}",      inputdir_2018+"ttbar",             lepvetowgt_2018(), datasel() + vetoes());
  config.addSample("wjets-2018preHEM-sr",    "W+jets",        inputdir_2018+"wjets",             lepvetowgt_2018(), datasel() + vetoes());
  config.addSample("tW-2018preHEM-sr",       "tW",            inputdir_2018+"tW",                lepvetowgt_2018(), datasel() + vetoes());
  config.addSample("ttW-2018preHEM-sr",      "ttW",           inputdir_2018+"ttW",               lepvetowgt_2018(), datasel() + vetoes());
  config.addSample("ttZ-2018preHEM-sr",      "ttZ",           inputdir_2018+"ttZ",               lepvetowgt_2018(), datasel() + vetoes());
  config.addSample("diboson-2018preHEM-sr",  "Diboson",       inputdir_2018+"diboson",           lepvetowgt_2018(), datasel() + vetoes());

  if(doLepSyst){
    //yields for MC with specific lepton SF choosing smallest pt
    config.addSample("ttbar-2016-eventsf-sr",       "t#bar{t}",      inputdir_2016+"ttbar",                seplepvetowgt()+"*"+isrwgtvar(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2016-eventsf-sr",       "W+jets",        inputdir_2016+"wjets",                seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2016-eventsf-sr",          "tW",            inputdir_2016+"tW",                   seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2016-eventsf-sr",         "ttW",           inputdir_2016+"ttW",                  seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("ttZ-2016-eventsf-sr",         "ttZ",           inputdir_2016+"ttZ",                  seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("diboson-2016-eventsf-sr",     "Diboson",       inputdir_2016+"diboson",              seplepvetowgt(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2017RunBtoE-eventsf-sr",    "t#bar{t}",      inputdir_2017+"ttbar",            seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2017RunBtoE-eventsf-sr",    "W+jets",        inputdir_2017+"wjets",            seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2017RunBtoE-eventsf-sr",       "tW",            inputdir_2017+"tW",               seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2017RunBtoE-eventsf-sr",      "ttW",           inputdir_2017+"ttW",              seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("ttZ-2017RunBtoE-eventsf-sr",      "ttZ",           inputdir_2017+"ttZ",              seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("diboson-2017RunBtoE-eventsf-sr",  "Diboson",       inputdir_2017+"diboson",          seplepvetowgt_2017(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2018preHEM-eventsf-sr",    "t#bar{t}",      inputdir_2018+"ttbar",             seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2018preHEM-eventsf-sr",    "W+jets",        inputdir_2018+"wjets",             seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2018preHEM-eventsf-sr",       "tW",            inputdir_2018+"tW",                seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2018preHEM-eventsf-sr",      "ttW",           inputdir_2018+"ttW",               seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("ttZ-2018preHEM-eventsf-sr",      "ttZ",           inputdir_2018+"ttZ",               seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("diboson-2018preHEM-eventsf-sr",  "Diboson",       inputdir_2018+"diboson",           seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    
    //yields for MC without specific lepton SF
    config.addSample("ttbar-2016-event-sr",       "t#bar{t}",      inputdir_2016+"ttbar",                nolepvetowgt()+"*"+isrwgtvar(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2016-event-sr",       "W+jets",        inputdir_2016+"wjets",                nolepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2016-event-sr",          "tW",            inputdir_2016+"tW",                   nolepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2016-event-sr",         "ttW",           inputdir_2016+"ttW",                  nolepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("ttZ-2016-event-sr",         "ttZ",           inputdir_2016+"ttZ",                  nolepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("diboson-2016-event-sr",     "Diboson",       inputdir_2016+"diboson",              nolepvetowgt(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2017RunBtoE-event-sr",    "t#bar{t}",      inputdir_2017+"ttbar",            nolepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2017RunBtoE-event-sr",    "W+jets",        inputdir_2017+"wjets",            nolepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2017RunBtoE-event-sr",       "tW",            inputdir_2017+"tW",               nolepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2017RunBtoE-event-sr",      "ttW",           inputdir_2017+"ttW",              nolepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("ttZ-2017RunBtoE-event-sr",      "ttZ",           inputdir_2017+"ttZ",              nolepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("diboson-2017RunBtoE-event-sr",  "Diboson",       inputdir_2017+"diboson",          nolepvetowgt_2017(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2018preHEM-event-sr",    "t#bar{t}",      inputdir_2018+"ttbar",             nolepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2018preHEM-event-sr",    "W+jets",        inputdir_2018+"wjets",             nolepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2018preHEM-event-sr",       "tW",            inputdir_2018+"tW",                nolepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2018preHEM-event-sr",      "ttW",           inputdir_2018+"ttW",               nolepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("ttZ-2018preHEM-event-sr",      "ttZ",           inputdir_2018+"ttZ",               nolepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("diboson-2018preHEM-event-sr",  "Diboson",       inputdir_2018+"diboson",           nolepvetowgt_2018(), datasel() + revert_vetoes_sep());
  }

  config.sel = baseline();
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = lepCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig srConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/testSR";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        lepvetowgt(), datasel() + vetoes());
  config.addSample("wjets",       "W+jets",        "wjets",        lepvetowgt(), datasel() + vetoes());
  config.addSample("znunu",       "Z#rightarrow#nu#nu", "znunu",   lepvetowgt(), datasel() + vetoes());
  config.addSample("qcd",         "QCD",           "qcd-sr",       lepvetowgt(), datasel() + vetoes() + qcdSpikeRemovals);
  config.addSample("tW",          "tW",            "tW",           lepvetowgt(), datasel() + vetoes());
  config.addSample("ttW",         "ttW",           "ttW",          lepvetowgt(), datasel() + vetoes());
  config.addSample("ttZ",         "ttZ",           "ttZ",          lepvetowgt(), datasel() + vetoes());
  config.addSample("diboson",     "Diboson",       "diboson",      lepvetowgt(), datasel() + vetoes());

//  config.addSample("T2fbd_500_420", "T2fbd(500,420)", "T2fbd_500_420",  sigwgt, datasel() + vetoes());
//  config.addSample("T2fbd_500_450", "T2fbd(500,450)", "T2fbd_500_450",  sigwgt, datasel() + vetoes());
//  config.addSample("T2fbd_500_480", "T2fbd(500,480)", "T2fbd_500_480",  sigwgt, datasel() + vetoes());
//  config.addSample("T2cc_500_490",  "T2cc(500,490)",  "T2cc_500_490",   sigwgt, datasel() + vetoes());
//
//  config.addSample("T2tt_450_250",  "T2tt(450,250)",  "T2tt_450_250",   sigwgt, datasel() + vetoes());
//  config.addSample("T2tt_700_400",  "T2tt(700,400)",  "T2tt_700_400",   sigwgt, datasel() + vetoes());
//  config.addSample("T2tt_1100_1",   "T2tt(1100,1)",   "T2tt_1000_1",    sigwgt, datasel() + vetoes());
//  config.addSample("T2bW_850_1",    "T2bW(850,1)",    "T2bW_850_1",     sigwgt, datasel() + vetoes());
//  config.addSample("T2bW_550_350",  "T2bW(550,350)",  "T2bW_550_350",   sigwgt, datasel() + vetoes());


  COLOR_MAP["T2fbd_500_420"] = kRed;
  COLOR_MAP["T2fbd_500_450"] = kBlue;
  COLOR_MAP["T2fbd_500_480"] = kBlack;
  COLOR_MAP["T2cc_500_490"]  = kMagenta;

  COLOR_MAP["T2tt_450_250"]  = kOrange;
  COLOR_MAP["T2tt_700_400"]  = kCyan+2;
  COLOR_MAP["T2tt_1000_1"]   = kViolet+2;
  COLOR_MAP["T2bW_550_350"]  = kSpring-9;
  COLOR_MAP["T2bW_850_1"]    = kPink+2;

  config.sel = baseline();
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig qcdConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/QCD";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  // qcdcr
  config.addSample("data-cr",     "Data",             datadir+"met",  "1.0",      datasel() + trigSR() + vetoes() + dphi_invert());
  
  config.addSample("qcd-2016-cr",      "QCD",              inputdir_2016+"qcd",       qcdwgt(),      datasel() + dphi_invert());
  config.addSample("qcd-2016-withveto-cr",  "QCD",         inputdir_2016+"qcd",       qcdvetowgt(),  datasel() + vetoes() + dphi_invert());
  config.addSample("qcd-2016-withveto-sr",  "QCD",         inputdir_2016+"qcd",       qcdvetowgt(),  datasel() + vetoes());

  config.addSample("qcd-2017RunBtoE-cr",      "QCD",       inputdir_2017+"qcd",       qcdwgt_2017(),      datasel() + dphi_invert());
  config.addSample("qcd-2017RunBtoE-withveto-cr",  "QCD",  inputdir_2017+"qcd",       qcdvetowgt_2017(),  datasel() + vetoes() + dphi_invert());
  config.addSample("qcd-2017RunBtoE-withveto-sr",  "QCD",  inputdir_2017+"qcd",       qcdvetowgt_2017(),  datasel() + vetoes());

  config.addSample("qcd-2018preHEM-cr",      "QCD",        inputdir_2018+"qcd",       qcdwgt_2018(),       datasel() + dphi_invert());
  config.addSample("qcd-2018preHEM-withveto-cr",  "QCD",   inputdir_2018+"qcd",       qcdvetowgt_2018(),   datasel() + vetoes() + dphi_invert());
  config.addSample("qcd-2018preHEM-withveto-sr",  "QCD",   inputdir_2018+"qcd",       qcdvetowgt_2018(),   datasel() + vetoes());

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-2016-cr",       "t#bar{t}",      inputdir_2016+"ttbar",        lepvetowgt(),  datasel() + vetoes() + dphi_invert());
  config.addSample("wjets-2016-cr",       "W+jets",        inputdir_2016+"wjets",        lepvetowgt(),  datasel() + vetoes() + dphi_invert());
  config.addSample("tW-2016-cr",          "tW",            inputdir_2016+"tW",           lepvetowgt(),  datasel() + vetoes() + dphi_invert());
  config.addSample("ttW-2016-cr",         "ttW",           inputdir_2016+"ttW",          lepvetowgt(),  datasel() + vetoes() + dphi_invert());
  config.addSample("znunu-2016-cr",       "Znunu",         inputdir_2016+"znunu",        lepvetowgt(),  datasel() + vetoes() + dphi_invert());

  config.addSample("ttbar-2017RunBtoE-cr",       "t#bar{t}",      inputdir_2017+"ttbar",        lepvetowgt_2017(),  datasel() + vetoes() + dphi_invert());
  config.addSample("wjets-2017RunBtoE-cr",       "W+jets",        inputdir_2017+"wjets",        lepvetowgt_2017(),  datasel() + vetoes() + dphi_invert());
  config.addSample("tW-2017RunBtoE-cr",          "tW",            inputdir_2017+"tW",           lepvetowgt_2017(),  datasel() + vetoes() + dphi_invert());
  config.addSample("ttW-2017RunBtoE-cr",         "ttW",           inputdir_2017+"ttW",          lepvetowgt_2017(),  datasel() + vetoes() + dphi_invert());
  config.addSample("znunu-2017RunBtoE-cr",       "Znunu",         inputdir_2017+"znunu",        lepvetowgt_2017(),  datasel() + vetoes() + dphi_invert());

  config.addSample("ttbar-2018preHEM-cr",        "t#bar{t}",      inputdir_2018+"ttbar",        lepvetowgt_2018(),  datasel() + vetoes() + dphi_invert());
  config.addSample("wjets-2018preHEM-cr",        "W+jets",        inputdir_2018+"wjets",        lepvetowgt_2018(),  datasel() + vetoes() + dphi_invert());
  config.addSample("tW-2018preHEM-cr",           "tW",            inputdir_2018+"tW",           lepvetowgt_2018(),  datasel() + vetoes() + dphi_invert());
  config.addSample("ttW-2018preHEM-cr",          "ttW",           inputdir_2018+"ttW",          lepvetowgt_2018(),  datasel() + vetoes() + dphi_invert());
  config.addSample("znunu-2018preHEM-cr",        "Znunu",         inputdir_2018+"znunu",        lepvetowgt_2018(),  datasel() + vetoes() + dphi_invert());

  if(doLepSyst){
    //yields for MC with specific lepton SF choosing smallest pt
    config.addSample("qcd-2016-eventsf-withveto-cr",  "QCD",         inputdir_2016+"qcd",       sepqcdvetowgt(),  datasel() + revert_vetoes_sep() + dphi_invert());
    config.addSample("qcd-2016-eventsf-withveto-sr",  "QCD",         inputdir_2016+"qcd",       sepqcdvetowgt(),  datasel() + revert_vetoes_sep());
    config.addSample("qcd-2017RunBtoE-eventsf-withveto-cr",  "QCD",  inputdir_2017+"qcd",       sepqcdvetowgt_2017(),  datasel() + revert_vetoes_sep() + dphi_invert());
    config.addSample("qcd-2017RunBtoE-eventsf-withveto-sr",  "QCD",  inputdir_2017+"qcd",       sepqcdvetowgt_2017(),  datasel() + revert_vetoes_sep());
    config.addSample("qcd-2018preHEM-eventsf-withveto-cr",  "QCD",   inputdir_2018+"qcd",       sepqcdvetowgt_2018(),  datasel() + revert_vetoes_sep() + dphi_invert());
    config.addSample("qcd-2018preHEM-eventsf-withveto-sr",  "QCD",   inputdir_2018+"qcd",       sepqcdvetowgt_2018(),  datasel() + revert_vetoes_sep());
    
    config.addSample("ttbar-2016-eventsf-cr",       "t#bar{t}",      inputdir_2016+"ttbar",                seplepvetowgt()+"*"+isrwgtvar(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2016-eventsf-cr",       "W+jets",        inputdir_2016+"wjets",                seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2016-eventsf-cr",          "tW",            inputdir_2016+"tW",                   seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2016-eventsf-cr",         "ttW",           inputdir_2016+"ttW",                  seplepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("znunu-2016-eventsf-cr",     "znunu",       inputdir_2016+"znunu",              seplepvetowgt(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2017RunBtoE-eventsf-cr",    "t#bar{t}",      inputdir_2017+"ttbar",            seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2017RunBtoE-eventsf-cr",    "W+jets",        inputdir_2017+"wjets",            seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2017RunBtoE-eventsf-cr",       "tW",            inputdir_2017+"tW",               seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2017RunBtoE-eventsf-cr",      "ttW",           inputdir_2017+"ttW",              seplepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("znunu-2017RunBtoE-eventsf-cr",  "znunu",       inputdir_2017+"znunu",          seplepvetowgt_2017(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2018preHEM-eventsf-cr",    "t#bar{t}",      inputdir_2018+"ttbar",             seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2018preHEM-eventsf-cr",    "W+jets",        inputdir_2018+"wjets",             seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2018preHEM-eventsf-cr",       "tW",            inputdir_2018+"tW",                seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2018preHEM-eventsf-cr",      "ttW",           inputdir_2018+"ttW",               seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("znunu-2018preHEM-eventsf-cr",  "znunu",       inputdir_2018+"znunu",           seplepvetowgt_2018(), datasel() + revert_vetoes_sep());
    
    //yields for MC without specific lepton SF
    config.addSample("qcd-2016-event-withveto-cr",  "QCD",         inputdir_2016+"qcd",       	qcdvetowgt(),  datasel() + revert_vetoes_sep() + dphi_invert());
    config.addSample("qcd-2016-event-withveto-sr",  "QCD",         inputdir_2016+"qcd",       	qcdvetowgt(),  datasel() + revert_vetoes_sep());
    config.addSample("qcd-2017RunBtoE-event-withveto-cr",  "QCD",  inputdir_2017+"qcd",         qcdvetowgt_2017(),  datasel() + revert_vetoes_sep() + dphi_invert());
    config.addSample("qcd-2017RunBtoE-event-withveto-sr",  "QCD",  inputdir_2017+"qcd",         qcdvetowgt_2017(),  datasel() + revert_vetoes_sep());
    config.addSample("qcd-2018preHEM-event-withveto-cr",  "QCD",   inputdir_2018+"qcd",         qcdvetowgt_2018(),  datasel() + revert_vetoes_sep() + dphi_invert());
    config.addSample("qcd-2018preHEM-event-withveto-sr",  "QCD",   inputdir_2018+"qcd",         qcdvetowgt_2018(),  datasel() + revert_vetoes_sep());
    
    config.addSample("ttbar-2016-event-cr",       "t#bar{t}",      inputdir_2016+"ttbar",                lepvetowgt()+"*"+isrwgtvar(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2016-event-cr",       "W+jets",        inputdir_2016+"wjets",                lepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2016-event-cr",          "tW",            inputdir_2016+"tW",                   lepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2016-event-cr",         "ttW",           inputdir_2016+"ttW",                  lepvetowgt(), datasel() + revert_vetoes_sep());
    config.addSample("znunu-2016-event-cr",     "znunu",       inputdir_2016+"znunu",              lepvetowgt(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2017RunBtoE-event-cr",    "t#bar{t}",      inputdir_2017+"ttbar",            lepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2017RunBtoE-event-cr",    "W+jets",        inputdir_2017+"wjets",            lepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2017RunBtoE-event-cr",       "tW",            inputdir_2017+"tW",               lepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2017RunBtoE-event-cr",      "ttW",           inputdir_2017+"ttW",              lepvetowgt_2017(), datasel() + revert_vetoes_sep());
    config.addSample("znunu-2017RunBtoE-event-cr",  "znunu",       inputdir_2017+"znunu",          lepvetowgt_2017(), datasel() + revert_vetoes_sep());

    config.addSample("ttbar-2018preHEM-event-cr",    "t#bar{t}",      inputdir_2018+"ttbar",             lepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("wjets-2018preHEM-event-cr",    "W+jets",        inputdir_2018+"wjets",             lepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("tW-2018preHEM-event-cr",       "tW",            inputdir_2018+"tW",                lepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("ttW-2018preHEM-event-cr",      "ttW",           inputdir_2018+"ttW",               lepvetowgt_2018(), datasel() + revert_vetoes_sep());
    config.addSample("znunu-2018preHEM-event-cr",  "znunu",       inputdir_2018+"znunu",           lepvetowgt_2018(), datasel() + revert_vetoes_sep());
  }

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",           "Data",          datadir+"met", "1.0",      datasel() + trigSR() + revert_vetoes() + dphi_cut());
  config.addSample("ttbar-2016-norm",     "t#bar{t}",      inputdir_2016+"ttbar",     lepselwgt(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("wjets-2016-norm",     "W+jets",        inputdir_2016+"wjets",     lepselwgt(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("tW-2016-norm",        "tW",            inputdir_2016+"tW",        lepselwgt(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("ttW-2016-norm",       "ttW",           inputdir_2016+"ttW",       lepselwgt(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("qcd-2016-norm",       "QCD",           inputdir_2016+"qcd",       lepselwgt(),   datasel() + revert_vetoes() + dphi_cut());

  config.addSample("ttbar-2017RunBtoE-norm",     "t#bar{t}",      inputdir_2017+"ttbar",     lepselwgt_2017(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("wjets-2017RunBtoE-norm",     "W+jets",        inputdir_2017+"wjets",     lepselwgt_2017(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("tW-2017RunBtoE-norm",        "tW",            inputdir_2017+"tW",        lepselwgt_2017(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("ttW-2017RunBtoE-norm",       "ttW",           inputdir_2017+"ttW",       lepselwgt_2017(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("qcd-2017RunBtoE-norm",       "QCD",           inputdir_2017+"qcd",       lepselwgt_2017(),   datasel() + revert_vetoes() + dphi_cut());

  config.addSample("ttbar-2018preHEM-norm",     "t#bar{t}",      inputdir_2018+"ttbar",     lepselwgt_2018(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("wjets-2018preHEM-norm",     "W+jets",        inputdir_2018+"wjets",     lepselwgt_2018(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("tW-2018preHEM-norm",        "tW",            inputdir_2018+"tW",        lepselwgt_2018(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("ttW-2018preHEM-norm",       "ttW",           inputdir_2018+"ttW",       lepselwgt_2018(),   datasel() + revert_vetoes() + dphi_cut());
  config.addSample("qcd-2018preHEM-norm",       "QCD",           inputdir_2018+"qcd",       lepselwgt_2018(),   datasel() + revert_vetoes() + dphi_cut());

  // qcdsr
  config.addSample("qcd-2016-sr",         "QCD",           inputdir_2016+"qcd",       qcdwgt(),           datasel());
  config.addSample("qcd-2017RunBtoE-sr",  "QCD",           inputdir_2017+"qcd",       qcdwgt_2017(),   datasel());
  config.addSample("qcd-2018preHEM-sr",   "QCD",           inputdir_2018+"qcd",       qcdwgt_2018(),    datasel());

  config.sel = baseline();
  config.categories = srbins;
  config.catMaps = srCatMap();    // sr DPhi cut applied
  config.crCatMaps = qcdCatMap(); // no DPhi cut in category def

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig sigConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("data-sr",        "Data",             datadir+"/sr/met",                    "1.0",  datasel() + trigSR() + vetoes());

//  config.addSample("T2fbd_375_355",  "T2-4bd(375,355)",  "sig/T2fbd_375_355",  sigwgt, datasel() + vetoes());
//  config.addSample("T2fbd_375_325",  "T2-4bd(375,325)",  "sig/T2fbd_375_325",  sigwgt, datasel() + vetoes());
//  config.addSample("T2fbd_375_295",  "T2-4bd(375,295)",  "sig/T2fbd_375_295",  sigwgt, datasel() + vetoes());
//
  config.sel = baseline();
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

map<TString, BinInfo> varDict {
  {"norm",      BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{0, 1000}, "GeV")},
  {"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
  {"metgx",       BinInfo("MET_pt", "#slash{E}_{T}^{(#gamma)}", vector<int>{250, 350, 450, 550, 650, 850}, "GeV")},
  {"metzg",       BinInfo("MET_pt", "#slash{E}_{T}^{#gamma/ll}", vector<int>{250, 350, 450, 550, 650, 850}, "GeV")},
  {"origmet",   BinInfo("MET_pt", "Original #slash{E}_{T}", 20, 0, 500, "GeV")},
  {"njets",     BinInfo("Stop0l_nJets", "N_{j}", 8, -0.5, 7.5)},
  {"njl",       BinInfo("njl", "N_{j}^{ISR}", 4, 0.5, 4.5)},
  {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
  {"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
  {"dphij1met", BinInfo("Jet_dPhiMET[0]", "#Delta#phi(j_{1},#slash{E}_{T})", 30, 0, 3)},
  {"dphij2met", BinInfo("Jet_dPhiMET[1]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
  {"metovsqrtht",BinInfo("Stop0l_METSig", "#slash{E}_{T}/#sqrt{H_{T}}", 10, 0, 20)},
  {"dphiisrmet",BinInfo("dphiisrmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
  {"dphiisrmet_fine",BinInfo("dphiisrmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", 12, 0, 3)},
  {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
  {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 12, 0, 600)},
  {"leptonptovermet",  BinInfo("leptonpt/met", "p_{T}^{lep}/#slash{E}_{T}", 20, 0, 1.)},
  {"ak8isrpt",  BinInfo("ak8isrpt", "p_{T}(ISR) [GeV]",  6, 200, 800)},
  {"csvj1pt",   BinInfo("csvj1pt", "p_{T}(b_{1}) [GeV]", 8, 20, 100)},
  {"ptb12",     BinInfo("csvj1pt+csvj2pt", "p_{T}(b_{1})+p_{T}(b_{2}) [GeV]", 8, 40, 200)},
  {"dphilepisr",  BinInfo("dphilepisr", "#Delta#phi(lep, j_{1}^{ISR})", 30, 0, 3)},
  {"drlepisr",  BinInfo("drlepisr", "#DeltaR(lep, j_{1}^{ISR})", 25, 0, 5)},
};

}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
