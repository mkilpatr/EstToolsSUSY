#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../../utils/EstHelper.hh"

namespace EstTools{

TString sys_name = "nominal";
TString inputdir = "root://cmseos.fnal.gov//eos/uscms/store/user/mkilpatr/13TeV/";
TString inputdir_2016 = "nanoaod_all_skim_2016_100219/";
TString inputdir_2017 = "nanoaod_all_skim_2017_100219/";
TString inputdir_2018 = "nanoaod_all_skim_2018_100219/";
TString outputdir() {return "syst/"+sys_name;}

const TString datadir = "nanoaod_data_all_skim_100219/";

const TString lumistr = "137.728";
const TString lumistr_2016 = "35.922"; //Units are in pb
const TString lumistr_2017RunBtoE = "28.290";
const TString lumistr_2017RunF    = "13.527";
const TString lumistr_2018PreHEM  = "21.0684";
const TString lumistr_2018PostHEM = "38.8296";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// systematics weights
TString wtagwgt = "WtagSF";
TString sdmvawgt = "TopSF"; // top/W
TString restopwgt = "restopSF";
TString softbwgt = "SoftBSF";

TString puwgt = "puWeight"; // PU
TString BtoEpuwgt = "17BtoEpuWeight"; // PU
TString Fpuwgt = "17FpuWeight"; // PU

TString muonwgt = "MuonSF"; // tnp (el/mu)
TString elewgt = "ElectronSF";
TString tauwgt = "TauSF";

TString btagwgt = "BTagWeight"; // btag

TString prefirewgt = "PrefireWeight"; //prefire

TString trigger = "Stop0l_trigger_eff_MET_loose_baseline";

TString mcwgt = "1000*Stop0l_evtWeight"; // ttbarnorm / wjetsnorm

// lumi and base weight
TString wgtvar()        { return lumistr_2016+"*"+mcwgt+"*"+puwgt+"*"+btagwgt+"*"+trigger+"*"+prefirewgt+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt; }
TString wgtvar_RunBtoE(){ return lumistr_2017RunBtoE+"*"+mcwgt+"*"+BtoEpuwgt+"*"+btagwgt+"*"+trigger+"*"+prefirewgt+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt; }
TString wgtvar_RunF()   { return lumistr_2017RunF+"*"+mcwgt+"*"+Fpuwgt+"*"+btagwgt+"*"+trigger+"*"+prefirewgt+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt; }
TString wgtvar_preHEM() { return lumistr_2018PreHEM+"*"+mcwgt+"*"+puwgt+"*"+btagwgt+"*"+trigger+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt; }
TString wgtvar_postHEM(){ return lumistr_2018PostHEM+"*"+mcwgt+"*"+puwgt+"*"+btagwgt+"*"+trigger+"*"+wtagwgt+"*"+sdmvawgt+"*"+restopwgt+"*"+softbwgt; }

// photon trigger eff.
TString phowgt() { return wgtvar(); }
//TString phowgt = wgtvar + "*qcdRespTailWeight";

TString jes_postfix = "";

// No Lepton SF
//TString lepvetowgt() {return wgtvar();}
//TString lepselwgt()  {return wgtvar();}
//const TString vetoes = " && nvetolep==0 && nvetotau==0";

// Tag-and-Probe Lepton SF
TString lepvetowgt() 	     { return wgtvar() + "*"+muonwgt+"*"+elewgt+"*"+tauwgt; }
TString lepselwgt()  	     { return wgtvar() + "*"+muonwgt+"*"+elewgt; }
TString lepvetowgt_RunBtoE() { return wgtvar_RunBtoE() + "*"+muonwgt+"*"+elewgt+"*"+tauwgt; }
TString lepselwgt_RunBtoE()  { return wgtvar_RunBtoE() + "*"+muonwgt+"*"+elewgt; }
TString lepvetowgt_RunF()    { return wgtvar_RunF() + "*"+muonwgt+"*"+elewgt+"*"+tauwgt; }
TString lepselwgt_RunF()     { return wgtvar_RunF() + "*"+muonwgt+"*"+elewgt; }
TString lepvetowgt_preHEM()  { return wgtvar_preHEM() + "*"+muonwgt+"*"+elewgt+"*"+tauwgt; }
TString lepselwgt_preHEM()   { return wgtvar_preHEM() + "*"+muonwgt+"*"+elewgt; }
TString lepvetowgt_postHEM() { return wgtvar_postHEM() + "*"+muonwgt+"*"+elewgt+"*"+tauwgt; }
TString lepselwgt_postHEM()  { return wgtvar_postHEM() + "*"+muonwgt+"*"+elewgt; }
TString vetoes()	     { return  " && Pass_LeptonVeto"+jes_postfix; }

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// 1Lep LLB method
bool ADD_LEP_TO_MET = false;
bool ICHEPCR = false;
TString revert_vetoes() { return " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100"; }

// MET+LEP LL method
//bool ADD_LEP_TO_MET = true;
TString lepcrsel = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && MET_pt>100";

// lepton trigger eff.
//const TString trigLepCR = " && (passtrige || passtrigmu)";
//const TString onelepcrwgt  = lepselwgt + "*trigEleWeight*trigMuWeight";

const TString trigLepCR = " && passtriglepOR";
TString onelepcrwgt() {return lepselwgt();}

// qcd weights
//TString qcdwgt() {return wgtvar() + "*qcdRespTailWeight";}
TString qcdwgt() {return wgtvar();}
//TString qcdvetowgt() {return lepvetowgt() + "*qcdRespTailWeight";}
TString qcdvetowgt() {return lepvetowgt();}

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(1.0*(mtcsv12met<=175)+sdtopFastSimWeight*sdwFastSimWeight*(mtcsv12met>175))";
TString sigwgt() {return lepvetowgt();}

// triggers
TString trigSR = " && Pass_trigger_MET";
TString trigPhoCR = " && passtrigphoOR && origmet<200";
TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
TString datasel() { return " && Pass_EventFilter"+jes_postfix+" && Pass_HT"+jes_postfix+" && Pass_JetID"+jes_postfix+" && Pass_CaloMETRatio"+jes_postfix+" && (run < 319077 || (run >= 319077 && Pass_exHEMVeto20"+jes_postfix+"))"; }
TString dataselHEM() { return " && Pass_EventFilter"+jes_postfix+" && Pass_HT"+jes_postfix+" && Pass_JetID"+jes_postfix+" && Pass_CaloMETRatio"+jes_postfix+" && (run >= 319077 || run == 1) && Pass_exHEMVeto20"+jes_postfix+""; }
TString qcdSpikeRemovals = "";
TString dphi_invert = " && Pass_dPhiQCD";
TString dphi_cut() { return  " && ( ((Stop0l_Mtb"+jes_postfix+"<175 && Stop0l_nTop"+jes_postfix+"==0 && Stop0l_nW"+jes_postfix+"==0 && Stop0l_nResolved"+jes_postfix+"==0) && Pass_dPhiMETLowDM"+jes_postfix+") || (!(Stop0l_Mtb"+jes_postfix+"<175 && Stop0l_nTop"+jes_postfix+"==0 && Stop0l_nW"+jes_postfix+"==0 && Stop0l_nResolved"+jes_postfix+"==0) && Pass_dPhiMETHighDM"+jes_postfix+") )"; } // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

// ------------------------------------------------------------------------
// search regions and control regions

TString baseline() {return "Pass_MET"+jes_postfix+" && Pass_NJets20"+jes_postfix+""; }

std::map<TString, TString> cutMap = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt"+jes_postfix+">=300 && Stop0l_Mtb"+jes_postfix+" < 175 && Stop0l_nTop"+jes_postfix+"==0 && Stop0l_nW"+jes_postfix+"==0 && Stop0l_nResolved"+jes_postfix+"==0 && Stop0l_METSig"+jes_postfix+">=10"},
        {"dPhiLM",      "Pass_dPhiMETLowDM"+jes_postfix+""},
        {"hmNoDPhi",    "Stop0l_nJets"+jes_postfix+">=5 && Stop0l_nbtags"+jes_postfix+">=1"},
        {"dPhiHM",      "Pass_dPhiMETHighDM"+jes_postfix+""},
        {"invertDPhi",  "Pass_dPhiQCD"},
 
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
  "lm_nb1_nivf1_lowmtb_lowptb",

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
  "hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000",
  "hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000",

  // nb1
  // 1 tagged
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500",
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",
  "hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300",
  "hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",

  // 1+1
  "hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",
  "hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0",
  "hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",

  // nb2
  // 1 tagged
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",

  // 1+1eq
  "hm_nbeq2_highmtb_nt1_nrt0_nw1",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1",

  // 2
  "hm_nbeq2_highmtb_nt2_nrt0_nw0",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",

  // 3
  "hm_nbeq2_highmtb_nrtntnwgeq3",

  // nb3
  //1 tagged
  "hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",
  "hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt0_nw1",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",
  "hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",

  //1+1
  "hm_nb3_highmtb_nt1_nrt0_nw1",
  "hm_nb3_highmtb_nt1_nrt1_nw0",
  "hm_nb3_highmtb_nt0_nrt1_nw1",

  //2
  "hm_nb3_highmtb_nt2_nrt0_nw0",
  "hm_nb3_highmtb_nt0_nrt0_nw2",
  "hm_nb3_highmtb_nt0_nrt2_nw0",

  // 3
  "hm_nb3_highmtb_nrtntnwgeq3",
  
  //---------- high deltaM ----------
};

std::map<TString, TString> srcuts = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap);
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

  {"lm_nb1_nivf1_lowmtb_lowptb",                 {300, 400, 500, 1000}},

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
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000",         {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000",         {250, 350, 450, 550, 1000}},

  // nb1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",      {250, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500",  {250, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",      {250, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300",      {250, 350, 450, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300",      {250, 350, 450, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",            {250, 550, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0",            {250, 550, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",            {250, 550, 1000}},

  // nb2
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",       {250, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",   {250, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {250, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1",                {250, 550, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1",                {250, 550, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0",       	   {250, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2",                {250, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",       {250, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",       {250, 450, 1000}},

  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3",        	   {250, 1000}},

        // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1",                  {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {250, 350, 550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1",                  {250, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0",         	   {250, 350, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1",                  {250, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0",         	   {250, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2",                  {250, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0",         	   {250, 350, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3",                   {250, 1000}},
  
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
  {"lm_nb1_nivf1_lowmtb_lowptb",                 "lm_nb1_nivf1_lowmtb_lowptb"},

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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                  	"hm_nb1_lowmtb_nj7"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",			 	"hm_nb2_lowmtb_nj7"},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000",		"hm_nb1_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000",		"hm_nb2_highmtb"},

        // nb1
  // 1 tagged
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",		"hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500",	"hm_nb1_highmtb_ht1000to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",		"hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300",		"hm_nb1_highmtb_htlt1300"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300",		"hm_nb1_highmtb_htgt1300"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",		"hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500",	"hm_nb1_highmtb_ht1000to1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",		"hm_nb1_highmtb_htgt1500"},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",		 	"hm_nb1_highmtb"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0",		 	"hm_nb1_highmtb"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",		 	"hm_nb1_highmtb"},

        // nb2
  // 1 tagged
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",		"hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",	"hm_nbeq2_highmtb_ht1000to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",		"hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300",		"hm_nbeq2_highmtb_htlt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",		"hm_nbeq2_highmtb_htgt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",		"hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",	"hm_nbeq2_highmtb_ht1000to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",		"hm_nbeq2_highmtb_htgt1500"},

  // 1+1eq
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1",		 	"hm_nbeq2_highmtb"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",		"hm_nbeq2_highmtb_htlt1300"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",		"hm_nbeq2_highmtb_htgt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1",		 	"hm_nbeq2_highmtb"},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0",			"hm_nbeq2_highmtb"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2",		 	"hm_nbeq2_highmtb"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",		"hm_nbeq2_highmtb_htlt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",		"hm_nbeq2_highmtb_htgt1300"},

  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3",			"hm_nbeq2_highmtb"},

        // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",		"hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",		"hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",		"hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1",		 	"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",		"hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",		"hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",		"hm_nb3_highmtb_htgt1500"},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1",		 	"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0",			"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1",		 	"hm_nb3_highmtb"},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0",			"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2",		 	"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0",			"hm_nb3_highmtb"},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3",		 	"hm_nb3_highmtb"},
  
  //---------- high deltaM ----------
};


std::map<TString, TString> phocrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap);
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
  {"lm_nb1_nivf1_lowmtb_lowptb",                 "lm_nb1_nivf1_lowmtb_lowptb"},

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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                  	"hm_nb1_lowmtb_nj7"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",			 	"hm_nb2_lowmtb_nj7"},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000",		"hm_nb1_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000",		"hm_nb2_highmtb"},

        // nb1
  // 1 tagged
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",		"hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500",	"hm_nb1_highmtb_ht1000to1500"},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",		"hm_nb1_highmtb_htgt1500"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300",		"hm_nb1_highmtb_htlt1300"},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300",		"hm_nb1_highmtb_htgt1300"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",		"hm_nb1_highmtb_htlt1000"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500",	"hm_nb1_highmtb_ht1000to1500"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",		"hm_nb1_highmtb_htgt1500"},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",		 	"hm_nb1_highmtb"},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0",		 	"hm_nb1_highmtb"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",		 	"hm_nb1_highmtb"},

        // nb2
  // 1 tagged
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",		"hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",	"hm_nbeq2_highmtb_ht1000to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",		"hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300",		"hm_nbeq2_highmtb_htlt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",		"hm_nbeq2_highmtb_htgt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",		"hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",	"hm_nbeq2_highmtb_ht1000to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",		"hm_nbeq2_highmtb_htgt1500"},

  // 1+1eq
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1",		 	"hm_nbeq2_highmtb"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",		"hm_nbeq2_highmtb_htlt1300"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",		"hm_nbeq2_highmtb_htgt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1",		 	"hm_nbeq2_highmtb"},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0",			"hm_nbeq2_highmtb"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2",		 	"hm_nbeq2_highmtb"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",		"hm_nbeq2_highmtb_htlt1300"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",		"hm_nbeq2_highmtb_htgt1300"},

  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3",			"hm_nbeq2_highmtb"},

        // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",		"hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",		"hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",		"hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1",		 	"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",		"hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",		"hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",		"hm_nb3_highmtb_htgt1500"},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1",		 	"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0",			"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1",		 	"hm_nb3_highmtb"},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0",			"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2",		 	"hm_nb3_highmtb"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0",			"hm_nb3_highmtb"},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3",		 	"hm_nb3_highmtb"},

  //---------- high deltaM ----------
};


std::map<TString, TString> lepcrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : lepcrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap);
    return cuts;
}();

std::map<TString, TString> lepcrlabels = lepcrMapping;
std::map<TString, std::vector<int>> lepcrMETbins = srMETbins;

// qcd-cr: inverted dPhi cut applied on CR samples now
std::map<TString, TString> qcdcrMapping =[]{
  auto crmap = lepcrMapping;
  for (auto &s : crmap){
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
  
  {"lm_nb1_nivf1_lowmtb_lowptb",                 {300, 400,      1000}}, // merge last 2 bins
  
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
  {"hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000",         {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000",         {250, 350, 450, 550, 1000}},

  // nb1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000",      {250, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500",  {250, 550, 650, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500",      {250, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300",      {250, 350, 450, 1000}},
  {"hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300",      {250, 350, 450, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500",  {250, 350, 450, 550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",            {250, 550, 1000}},
  {"hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0",            {250, 550, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",            {250, 550, 1000}},

  // nb2
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000",       {250, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",   {250, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {250, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1",                {250, 550, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",       {250, 350, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1",                {250, 550, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0",       	   {250, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2",                {250, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",       {250, 450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",       {250, 450, 1000}},

  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3",        	   {250, 1000}},

        // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1",                  {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {250, 350, 550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1",                  {250, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0",         	   {250, 350, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1",                  {250, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0",         	   {250, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2",                  {250, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0",         	   {250, 350, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3",                   {250, 1000}},
  
  //---------- high deltaM ----------
};


map<TString, Category> srCatMap(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts.at(name), srlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
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

map<TString, Category> qcdCatMap(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts: qcdcrCuts;
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
  config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt(), datasel() + trigSR + vetoes());

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
    config.addSample("ttbar-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           onelepcrwgt()+"*ISRWeight", datasel() + trigLepCR + lepcrsel);
    config.addSample("wjets-2016",       "W+jets",        inputdir_2016+"wjets",           onelepcrwgt(), datasel() + trigLepCR + lepcrsel);
    config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              onelepcrwgt(), datasel() + trigLepCR + lepcrsel);
    config.addSample("ttW-2016",         "ttW",           inputdir_2016+"ttW",             onelepcrwgt(), datasel() + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "lepcr/qcd",             onelepcrwgt, datasel() + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",        "Data",          datadir+"met",                   "1.0",          datasel() + trigSR + revert_vetoes());
    config.addSample("ttbar-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt()+"*ISRWeight",      datasel() + trigSR + revert_vetoes());
    config.addSample("wjets-2016",       "W+jets",        inputdir_2016+"wjets",           lepselwgt(),      datasel() + trigSR + revert_vetoes());
    config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              lepselwgt(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttW-2016",         "ttW",           inputdir_2016+"ttW",             lepselwgt(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttZ-2016",         "ttZ",           inputdir_2016+"ttZ",             lepselwgt(),      datasel() + trigSR + revert_vetoes());
    config.addSample("diboson-2016",     "Diboson",       inputdir_2016+"diboson",         lepselwgt(),      datasel() + trigSR + revert_vetoes());
    config.addSample("qcd-2016",         "QCD",           inputdir_2016+"qcd",             lepselwgt(),      datasel() + trigSR + revert_vetoes());

    //config.addSample("singlelep-2017RunBtoE",     "Data",          inputdir_2017+"met_RunBtoE",         "1.0",      datasel() + trigSR + revert_vetoes());
    config.addSample("ttbar-2017RunBtoE",         "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    config.addSample("wjets-2017RunBtoE",         "W+jets",        inputdir_2017+"wjets",           lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    config.addSample("tW-2017RunBtoE",            "tW",            inputdir_2017+"tW",              lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttW-2017RunBtoE",           "ttW",           inputdir_2017+"ttW",             lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttZ-2017RunBtoE",           "ttZ",           inputdir_2017+"ttZ",             lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    config.addSample("diboson-2017RunBtoE",       "Diboson",       inputdir_2017+"diboson",         lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    config.addSample("qcd-2017RunBtoE",           "QCD",           inputdir_2017+"qcd",             lepselwgt_RunBtoE(),      datasel() + trigSR + revert_vetoes());
    //config.addSample("singlelep-2017RunF",        "Data",          inputdir_2017+"met_RunF",            "1.0",      datasel() + trigSR + revert_vetoes());
    config.addSample("ttbar-2017RunF",       	  "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());
    config.addSample("wjets-2017RunF",       	  "W+jets",        inputdir_2017+"wjets",           lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());
    config.addSample("tW-2017RunF",          	  "tW",            inputdir_2017+"tW",              lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttW-2017RunF",         	  "ttW",           inputdir_2017+"ttW",             lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttZ-2017RunF",         	  "ttZ",           inputdir_2017+"ttZ",             lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());
    config.addSample("diboson-2017RunF",     	  "Diboson",       inputdir_2017+"diboson",         lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());
    config.addSample("qcd-2017RunF",         	  "QCD",           inputdir_2017+"qcd",             lepselwgt_RunF(),      datasel() + trigSR + revert_vetoes());

    //config.addSample("singlelep-2018preHEM",     "Data",          inputdir_2018+"met_PreHEM",                 "1.0",      datasel() + trigSR + revert_vetoes());
    config.addSample("ttbar-2018preHEM",         "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    config.addSample("wjets-2018preHEM",         "W+jets",        inputdir_2018+"wjets",           lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    config.addSample("tW-2018preHEM",            "tW",            inputdir_2018+"tW",              lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttW-2018preHEM",           "ttW",           inputdir_2018+"ttW",             lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    config.addSample("ttZ-2018preHEM",           "ttZ",           inputdir_2018+"ttZ",             lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    config.addSample("diboson-2018preHEM",       "Diboson",       inputdir_2018+"diboson",         lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    config.addSample("qcd-2018preHEM",           "QCD",           inputdir_2018+"qcd",             lepselwgt_preHEM(),      datasel() + trigSR + revert_vetoes());
    //config.addSample("singlelep-2018postHEM",    "Data",          inputdir_2018+"met_PostHEM",                 "1.0",     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("ttbar-2018postHEM",        "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("wjets-2018postHEM",        "W+jets",        inputdir_2018+"wjets",           lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("tW-2018postHEM",           "tW",            inputdir_2018+"tW",              lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("ttW-2018postHEM",          "ttW",           inputdir_2018+"ttW",             lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("ttZ-2018postHEM",          "ttZ",           inputdir_2018+"ttZ",             lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("diboson-2018postHEM",      "Diboson",       inputdir_2018+"diboson",         lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
    config.addSample("qcd-2018postHEM",          "QCD",           inputdir_2018+"qcd",             lepselwgt_postHEM(),     dataselHEM() + trigSR + revert_vetoes());
  }

  // samples for sr categories
  config.addSample("ttbar-2016-sr",       "t#bar{t}",      inputdir_2016+"ttbar",                lepvetowgt()+"*ISRWeight", datasel() + trigSR + vetoes());
  config.addSample("wjets-2016-sr",       "W+jets",        inputdir_2016+"wjets",                lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("tW-2016-sr",          "tW",            inputdir_2016+"tW",                   lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("ttW-2016-sr",         "ttW",           inputdir_2016+"ttW",                  lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("ttZ-2016-sr",         "ttZ",           inputdir_2016+"ttZ",                  lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("diboson-2016-sr",     "Diboson",       inputdir_2016+"diboson",              lepvetowgt(), datasel() + trigSR + vetoes());

  config.addSample("ttbar-2017RunBtoE-sr",    "t#bar{t}",      inputdir_2017+"ttbar",            lepvetowgt_RunBtoE(), datasel() + trigSR + vetoes());
  config.addSample("wjets-2017RunBtoE-sr",    "W+jets",        inputdir_2017+"wjets",            lepvetowgt_RunBtoE(), datasel() + trigSR + vetoes());
  config.addSample("tW-2017RunBtoE-sr",       "tW",            inputdir_2017+"tW",               lepvetowgt_RunBtoE(), datasel() + trigSR + vetoes());
  config.addSample("ttW-2017RunBtoE-sr",      "ttW",           inputdir_2017+"ttW",              lepvetowgt_RunBtoE(), datasel() + trigSR + vetoes());
  config.addSample("ttZ-2017RunBtoE-sr",      "ttZ",           inputdir_2017+"ttZ",              lepvetowgt_RunBtoE(), datasel() + trigSR + vetoes());
  config.addSample("diboson-2017RunBtoE-sr",  "Diboson",       inputdir_2017+"diboson",          lepvetowgt_RunBtoE(), datasel() + trigSR + vetoes());
  config.addSample("ttbar-2017RunF-sr",       "t#bar{t}",      inputdir_2017+"ttbar",            lepvetowgt_RunF(), datasel() + trigSR + vetoes());
  config.addSample("wjets-2017RunF-sr",       "W+jets",        inputdir_2017+"wjets",            lepvetowgt_RunF(), datasel() + trigSR + vetoes());
  config.addSample("tW-2017RunF-sr",          "tW",            inputdir_2017+"tW",               lepvetowgt_RunF(), datasel() + trigSR + vetoes());
  config.addSample("ttW-2017RunF-sr",         "ttW",           inputdir_2017+"ttW",              lepvetowgt_RunF(), datasel() + trigSR + vetoes());
  config.addSample("ttZ-2017RunF-sr",         "ttZ",           inputdir_2017+"ttZ",              lepvetowgt_RunF(), datasel() + trigSR + vetoes());
  config.addSample("diboson-2017RunF-sr",     "Diboson",       inputdir_2017+"diboson",          lepvetowgt_RunF(), datasel() + trigSR + vetoes());

  config.addSample("ttbar-2018preHEM-sr",    "t#bar{t}",      inputdir_2018+"ttbar",             lepvetowgt_preHEM(), datasel() + trigSR + vetoes());
  config.addSample("wjets-2018preHEM-sr",    "W+jets",        inputdir_2018+"wjets",             lepvetowgt_preHEM(), datasel() + trigSR + vetoes());
  config.addSample("tW-2018preHEM-sr",       "tW",            inputdir_2018+"tW",                lepvetowgt_preHEM(), datasel() + trigSR + vetoes());
  config.addSample("ttW-2018preHEM-sr",      "ttW",           inputdir_2018+"ttW",               lepvetowgt_preHEM(), datasel() + trigSR + vetoes());
  config.addSample("ttZ-2018preHEM-sr",      "ttZ",           inputdir_2018+"ttZ",               lepvetowgt_preHEM(), datasel() + trigSR + vetoes());
  config.addSample("diboson-2018preHEM-sr",  "Diboson",       inputdir_2018+"diboson",           lepvetowgt_preHEM(), datasel() + trigSR + vetoes());
  config.addSample("ttbar-2018postHEM-sr",   "t#bar{t}",      inputdir_2018+"ttbar",             lepvetowgt_postHEM(), dataselHEM() + trigSR + vetoes());
  config.addSample("wjets-2018postHEM-sr",   "W+jets",        inputdir_2018+"wjets",             lepvetowgt_postHEM(), dataselHEM() + trigSR + vetoes());
  config.addSample("tW-2018postHEM-sr",      "tW",            inputdir_2018+"tW",                lepvetowgt_postHEM(), dataselHEM() + trigSR + vetoes());
  config.addSample("ttW-2018postHEM-sr",     "ttW",           inputdir_2018+"ttW",               lepvetowgt_postHEM(), dataselHEM() + trigSR + vetoes());
  config.addSample("ttZ-2018postHEM-sr",     "ttZ",           inputdir_2018+"ttZ",               lepvetowgt_postHEM(), dataselHEM() + trigSR + vetoes());
  config.addSample("diboson-2018postHEM-sr", "Diboson",       inputdir_2018+"diboson",           lepvetowgt_postHEM(), dataselHEM() + trigSR + vetoes());


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

  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("wjets",       "W+jets",        "wjets",        lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("znunu",       "Z#rightarrow#nu#nu", "znunu",   lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("qcd",         "QCD",           "qcd-sr",       lepvetowgt(), datasel() + trigSR + vetoes() + qcdSpikeRemovals);
  config.addSample("tW",          "tW",            "tW",           lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("ttW",         "ttW",           "ttW",          lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("ttZ",         "ttZ",           "ttZ",          lepvetowgt(), datasel() + trigSR + vetoes());
  config.addSample("diboson",     "Diboson",       "diboson",      lepvetowgt(), datasel() + trigSR + vetoes());

//  config.addSample("T2fbd_500_420", "T2fbd(500,420)", "T2fbd_500_420",  sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2fbd_500_450", "T2fbd(500,450)", "T2fbd_500_450",  sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2fbd_500_480", "T2fbd(500,480)", "T2fbd_500_480",  sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2cc_500_490",  "T2cc(500,490)",  "T2cc_500_490",   sigwgt, datasel() + trigSR + vetoes());
//
//  config.addSample("T2tt_450_250",  "T2tt(450,250)",  "T2tt_450_250",   sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2tt_700_400",  "T2tt(700,400)",  "T2tt_700_400",   sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2tt_1100_1",   "T2tt(1100,1)",   "T2tt_1000_1",    sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2bW_850_1",    "T2bW(850,1)",    "T2bW_850_1",     sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2bW_550_350",  "T2bW(550,350)",  "T2bW_550_350",   sigwgt, datasel() + trigSR + vetoes());


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
  config.addSample("data-cr",     "Data",             datadir+"/sr/met",  "1.0",      datasel() + trigSR + vetoes() + dphi_invert);
  config.addSample("qcd-cr",      "QCD",              "sr/qcd-cr",       qcdwgt(),      datasel() + trigSR + dphi_invert + qcdSpikeRemovals);

  config.addSample("qcd-withveto-cr",  "QCD",         "sr/qcd-cr",       qcdvetowgt(),  datasel() + trigSR + vetoes() + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-withveto-sr",  "QCD",         "sr/qcd-sr",       qcdvetowgt(),  datasel() + trigSR + vetoes() + qcdSpikeRemovals);

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-cr",       "t#bar{t}",      "sr/ttbar",        lepvetowgt(),  datasel() + trigSR + vetoes() + dphi_invert);
  config.addSample("wjets-cr",       "W+jets",        "sr/wjets",        lepvetowgt(),  datasel() + trigSR + vetoes() + dphi_invert);
  config.addSample("tW-cr",          "tW",            "sr/tW",           lepvetowgt(),  datasel() + trigSR + vetoes() + dphi_invert);
  config.addSample("ttW-cr",         "ttW",           "sr/ttW",          lepvetowgt(),  datasel() + trigSR + vetoes() + dphi_invert);
  config.addSample("znunu-cr",       "Znunu",         "sr/znunu",        lepvetowgt(),  datasel() + trigSR + vetoes() + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",      "Data",          datadir+"/sr/met", "1.0",       datasel() + trigSR + revert_vetoes() + dphi_cut());
  config.addSample("ttbar-norm",     "t#bar{t}",      "sr/ttbar",        lepselwgt(),   datasel() + trigSR + revert_vetoes() + dphi_cut());
  config.addSample("wjets-norm",     "W+jets",        "sr/wjets",        lepselwgt(),   datasel() + trigSR + revert_vetoes() + dphi_cut());
  config.addSample("tW-norm",        "tW",            "sr/tW",           lepselwgt(),   datasel() + trigSR + revert_vetoes() + dphi_cut());
  config.addSample("ttW-norm",       "ttW",           "sr/ttW",          lepselwgt(),   datasel() + trigSR + revert_vetoes() + dphi_cut());
  config.addSample("qcd-norm",       "QCD",           "sr/qcd-sr",       lepselwgt(),   datasel() + trigSR + revert_vetoes() + dphi_cut() + qcdSpikeRemovals);

  // qcdsr
  config.addSample("qcd-sr",         "QCD",           "sr/qcd-sr",       qcdwgt(),      datasel() + trigSR + qcdSpikeRemovals);

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

  config.addSample("data-sr",        "Data",             datadir+"/sr/met",                    "1.0",  datasel() + trigSR + vetoes());

//  config.addSample("T2fbd_375_355",  "T2-4bd(375,355)",  "sig/T2fbd_375_355",  sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2fbd_375_325",  "T2-4bd(375,325)",  "sig/T2fbd_375_325",  sigwgt, datasel() + trigSR + vetoes());
//  config.addSample("T2fbd_375_295",  "T2-4bd(375,295)",  "sig/T2fbd_375_295",  sigwgt, datasel() + trigSR + vetoes());
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
