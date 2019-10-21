#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"

namespace EstTools{

const TString inputdir = "root://cmseos.fnal.gov//eos/uscms/store/user/mkilpatr/13TeV/";
const TString inputdir_2016 = "nanoaod_all_skim_2016_100219/";
const TString inputdir_2017 = "nanoaod_all_skim_2017_100219/";
const TString inputdir_2018 = "nanoaod_all_skim_2018_100219/";
const TString inputdir_sig  = "nanoaod_T2tt_corridor_2017_101119/";

const TString outputdir = ".";

const TString datadir = "nanoaod_data_all_skim_100219/";

const TString lumistr = "137.728";
const TString lumistr_2016 = "35.922"; //Units are in pb
const TString lumistr_2017RunBtoE = "28.290";
const TString lumistr_2017RunF    = "13.527";
const TString lumistr_2018PreHEM  = "21.0684";
const TString lumistr_2018PostHEM = "38.8296";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// lumi and base weight
const TString wgtvar = lumistr_2016+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight*PrefireWeight*WtagSF*TopSF*SoftBSF"; //2016
const TString wgtvar_RunBtoE = lumistr_2017RunBtoE+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*17BtoEpuWeight*BTagWeight*PrefireWeight*WtagSF*TopSF*SoftBSF"; //2017
const TString wgtvar_RunF = lumistr_2017RunF+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*17FpuWeight*BTagWeight*PrefireWeight*WtagSF*TopSF*SoftBSF"; //2017
const TString wgtvar_preHEM = lumistr_2018PreHEM+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight*WtagSF*TopSF*SoftBSF"; //2018
const TString wgtvar_postHEM = lumistr_2018PostHEM+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight*WtagSF*TopSF*SoftBSF"; //2018

// photon trigger eff.
const TString phowgt = wgtvar;
//const TString phowgt = wgtvar + "*qcdRespTailWeight";

// No Lepton SF
//const TString lepvetowgt = wgtvar;
//const TString lepselwgt  = wgtvar;
//const TString vetoes = " && nvetolep==0 && nvetotau==0";

// Tag-and-Probe Lepton SF
const TString lepvetowgt =              wgtvar          + "*MuonLooseSF*ElectronVetoSF*TauSF";
const TString lepselwgt  =              wgtvar          + "*MuonLooseSF*ElectronVetoSF";
const TString lepvetowgt_RunBtoE =      wgtvar_RunBtoE  + "*MuonLooseSF*ElectronVetoSF*TauSF";
const TString lepselwgt_RunBtoE  =      wgtvar_RunBtoE  + "*MuonLooseSF*ElectronVetoSF";
const TString lepvetowgt_RunF =         wgtvar_RunF     + "*MuonLooseSF*ElectronVetoSF*TauSF";
const TString lepselwgt_RunF  =         wgtvar_RunF     + "*MuonLooseSF*ElectronVetoSF";
const TString lepvetowgt_preHEM =       wgtvar_preHEM   + "*MuonLooseSF*ElectronVetoSF*TauSF";
const TString lepselwgt_preHEM  =       wgtvar_preHEM   + "*MuonLooseSF*ElectronVetoSF";
const TString lepvetowgt_postHEM =      wgtvar_postHEM  + "*MuonLooseSF*ElectronVetoSF*TauSF";
const TString lepselwgt_postHEM  =      wgtvar_postHEM  + "*MuonLooseSF*ElectronVetoSF";
const TString vetoes = " && Pass_LeptonVeto";

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// sr weight w/o top/W SF
const TString lepvetowgt_no_wtopsf = lumistr_2016+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight*ISRWeight*PrefireWeight";
const TString lepvetowgt_no_wtopsf_RunBtoE = lumistr_2017RunBtoE+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*17BtoEpuWeight*BTagWeight*PrefireWeight";
const TString lepvetowgt_no_wtopsf_RunF = lumistr_2017RunF+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*17FpuWeight*BTagWeight*PrefireWeight";
const TString lepvetowgt_no_wtopsf_preHEM = lumistr_2018PreHEM+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight";
const TString lepvetowgt_no_wtopsf_postHEM = lumistr_2018PostHEM+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight";

// 1Lep LLB method
bool ADD_LEP_TO_MET = false;
bool ICHEPCR = false;

bool SPLITTF = true; // split TF to CR-SR and SR-extrapolation
const TString revert_vetoes = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100";

// MET+LEP LL method
//bool ADD_LEP_TO_MET = true;
const TString lepcrsel = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && MET_pt>100";


// lepton trigger eff.
//const TString trigLepCR = " && (passtrige || passtrigmu)";
//const TString onelepcrwgt  = lepselwgt + "*trigEleWeight*trigMuWeight";

const TString trigLepCR = "";
const TString onelepcrwgt  = lepselwgt;

// qcd weights
//const TString qcdwgt = wgtvar + "*qcdRespTailWeight";
const TString qcdwgt         = wgtvar;
const TString qcdwgt_RunBtoE = wgtvar_RunBtoE;
const TString qcdwgt_RunF    = wgtvar_RunF;
const TString qcdwgt_preHEM  = wgtvar_preHEM;
const TString qcdwgt_postHEM = wgtvar_postHEM;
//const TString qcdvetowgt = lepvetowgt + "*qcdRespTailWeight";
const TString qcdvetowgt         = lepvetowgt;
const TString qcdvetowgt_RunBtoE = lepvetowgt_RunBtoE;
const TString qcdvetowgt_RunF    = lepvetowgt_RunF;
const TString qcdvetowgt_preHEM  = lepvetowgt_preHEM;
const TString qcdvetowgt_postHEM = lepvetowgt_postHEM;

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(0.85*(Stop0l_nSoftb>=1) + 1.0*(Stop0l_nSoftb==0))";
const TString sigwgt = lumistr+"/"+lumistr_2016+"*"+lepvetowgt+"*ISRWeight";
const TString siglepselwgt = lumistr+"/"+lumistr_2016+"*"+lepselwgt+"*ISRWeight";

// triggers
const TString trigSR = " && Pass_trigger_MET";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(     lumi==203626 && event==398201606))";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && Pass_EventFilter && Pass_HT && Pass_JetID && Pass_CaloMETRatio && (run < 319077 || (run >= 319077 && Pass_exHEMVeto20))";
const TString dataselHEM = " && Pass_EventFilter && Pass_HT && Pass_JetID && Pass_CaloMETRatio && (run >= 319077 || run == 1) && Pass_exHEMVeto20";
const TString qcdSpikeRemovals = "";
const TString dphi_invert = " && Pass_dPhiQCD";
const TString dphi_cut = " && ( ((Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETLowDM) || (!(Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETHighDM) )"; // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "Pass_MET && Pass_NJets20";

std::map<TString, TString> cutMap = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
	{"lmNoDPhi",    "Stop0l_ISRJetPt>=300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>=10"},
	{"dPhiLM",      "Pass_dPhiMETLowDM"},
	{"hmNoDPhi",    "Stop0l_nJets>=5 && Stop0l_nbtags>=1"},
	{"dPhiHM",      "Pass_dPhiMETHighDM"},
	{"invertDPhi",  "Pass_dPhiQCD"},
	
	{"nb0",         "Stop0l_nbtags==0"},
	{"nb1",         "Stop0l_nbtags==1"},
	{"nbgeq1",      "Stop0l_nbtags>=1"},
	{"nb2",         "Stop0l_nbtags>=2"},
	{"nbeq2",       "Stop0l_nbtags==2"},
	{"nb3",         "Stop0l_nbtags>=3"},
	{"nivf0",       "Stop0l_nSoftb==0"},
	{"nivf1",       "Stop0l_nSoftb>=1"},
	{"lowptisr",    "Stop0l_ISRJetPt>=300 && Stop0l_ISRJetPt<500"},
	{"medptisr",    "Stop0l_ISRJetPt>=300"},
	{"highptisr",   "Stop0l_ISRJetPt>=500"},
	{"nj2to5",      "Stop0l_nJets>=2 && Stop0l_nJets<=5"},
	{"nj6",         "Stop0l_nJets>=6"},
	{"nj7",         "Stop0l_nJets>=7"},
	{"lowmtb",      "Stop0l_Mtb<175"},
	{"highmtb",     "Stop0l_Mtb>=175"},
	{"lowptb",      "Stop0l_Ptb<40"},
	{"medptb",      "Stop0l_Ptb>=40 && Stop0l_Ptb<70"},
	{"highptb",     "Stop0l_Ptb>=70"},
	{"lowptb12",    "Stop0l_Ptb<80"},
	{"medptb12",    "Stop0l_Ptb>=80 && Stop0l_Ptb<140"},
	{"highptb12",   "Stop0l_Ptb>=140"},
	{"nt0",         "Stop0l_nTop==0"},
	{"nt1",         "Stop0l_nTop==1"},
	{"nt2",         "Stop0l_nTop==2"},
	{"ntgeq1",      "Stop0l_nTop>=1"},
	{"nw0",         "Stop0l_nW==0"},
	{"nw1",         "Stop0l_nW==1"},
	{"nw2",         "Stop0l_nW==2"},
	{"nwgeq1",      "Stop0l_nW>=1"},
	{"nrt0",        "Stop0l_nResolved==0"},
	{"nrt1",        "Stop0l_nResolved==1"},
	{"nrt2",        "Stop0l_nResolved==2"},
	{"nrtgeq1",     "Stop0l_nResolved>=1"},
	{"nrtntnwgeq2", "(Stop0l_nTop+Stop0l_nResolved+Stop0l_nW) >= 2"},
	{"nrtntnwgeq3", "(Stop0l_nTop+Stop0l_nResolved+Stop0l_nW) >= 3"},
	{"htlt1000",    "Stop0l_HT<1000"},
	{"htgt1000",    "Stop0l_HT>=1000"},
	{"ht1000to1500","Stop0l_HT>=1000 && Stop0l_HT<1500"},
	{"htgt1500",    "Stop0l_HT>=1500"},
	{"htlt1300",    "Stop0l_HT<1300"},
	{"htgt1300",    "Stop0l_HT>=1300"},
	{"ht1000to1300","Stop0l_HT>=1000 && Stop0l_HT<1300"},
	{"ht1300to1500","Stop0l_HT>=1300 && Stop0l_HT<1500"},
    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();

vector<TString> signals_small {
  "T2tt_175_1",
  "T2tt_250_50",
  "T2tt_250_75",
  "T2tt_250_100",
};

vector<TString> signals {
  "T2tt_150_1",
  "T2tt_150_25",
  "T2tt_150_50",
  "T2tt_150_63",
  "T2tt_167_1",
  "T2tt_175_1",
  "T2tt_175_25",
  "T2tt_175_50",
  "T2tt_175_75",
  "T2tt_175_88",
  "T2tt_183_1",
  "T2tt_192_25",
  "T2tt_200_1",
  "T2tt_200_25",
  "T2tt_200_50",
  "T2tt_200_75",
  "T2tt_200_100",
  "T2tt_200_113",
  "T2tt_208_25",
  "T2tt_217_50",
  "T2tt_225_1",
  "T2tt_225_25",
  "T2tt_225_50",
  "T2tt_225_75",
  "T2tt_225_100",
  "T2tt_225_125",
  "T2tt_225_138",
  "T2tt_233_50",
  "T2tt_242_75",
  "T2tt_250_25",
  "T2tt_250_50",
  "T2tt_250_75",
  "T2tt_250_100",
  "T2tt_250_125",
  "T2tt_250_150",
  "T2tt_250_163",
  "T2tt_258_75",
  "T2tt_267_100",
  "T2tt_275_1",
  "T2tt_275_25",
  "T2tt_275_50",
  "T2tt_275_75",
  "T2tt_275_100",
  "T2tt_275_125",
  "T2tt_275_150",
  "T2tt_275_175",
  "T2tt_275_188",
  "T2tt_283_100",
  "T2tt_292_125",
  "T2tt_300_1",
  "T2tt_300_25",
  "T2tt_300_50",
  "T2tt_300_75",
  "T2tt_300_100",
  "T2tt_300_125",
  "T2tt_300_150",
  "T2tt_300_175",
  "T2tt_300_200",
  "T2tt_300_213",
  "T2tt_308_125",
  "T2tt_317_150",
  "T2tt_325_75",
  "T2tt_325_100",
  "T2tt_325_125",
  "T2tt_325_150",
  "T2tt_325_200",
  "T2tt_333_150",
  "T2tt_342_175",
  "T2tt_350_125",
  "T2tt_350_150",
  "T2tt_350_175",
  "T2tt_350_200",
  "T2tt_350_225",
  "T2tt_350_250",
  "T2tt_350_263",
  "T2tt_358_175",
  "T2tt_367_200",
  "T2tt_375_75",
  "T2tt_375_125",
  "T2tt_375_175",
  "T2tt_375_225",
  "T2tt_392_225",
  "T2tt_400_175",
  "T2tt_400_275",
  "T2tt_408_225",
  "T2tt_425_125",
  "T2tt_425_150",
  "T2tt_425_175",
  "T2tt_425_200",
  "T2tt_425_225",
  "T2tt_425_250",
  "T2tt_425_275",
  "T2tt_425_300",
  "T2tt_433_250",
  "T2tt_442_275",
  "T2tt_450_1",
  "T2tt_450_50",
  "T2tt_450_100",
  "T2tt_450_150",
  "T2tt_450_175",
  "T2tt_450_200",
  "T2tt_450_225",
  "T2tt_450_250",
  "T2tt_450_275",
  "T2tt_450_300",
  "T2tt_450_325",
  "T2tt_450_363",
  "T2tt_458_275",
  "T2tt_475_175",
  "T2tt_475_200",
  "T2tt_475_225",
  "T2tt_475_250",
  "T2tt_475_275",
  "T2tt_475_300",
  "T2tt_475_325",
  "T2tt_475_350",
  "T2tt_475_375",
  "T2tt_492_325",
  "T2tt_500_1",
  "T2tt_500_50",
  "T2tt_500_100",
  "T2tt_500_150",
  "T2tt_500_200",
  "T2tt_500_225",
  "T2tt_500_250",
  "T2tt_500_275",
  "T2tt_500_300",
  "T2tt_500_325",
  "T2tt_500_350",
  "T2tt_500_375",
  "T2tt_500_400",
  "T2tt_500_413",
  "T2tt_517_350",
  "T2tt_525_225",
  "T2tt_525_250",
  "T2tt_525_275",
  "T2tt_525_300",
  "T2tt_525_325",
  "T2tt_525_350",
  "T2tt_525_375",
  "T2tt_525_400",
  "T2tt_525_425",
  "T2tt_525_438",
  "T2tt_533_350",
  "T2tt_542_375",
  "T2tt_550_1",
  "T2tt_550_50",
  "T2tt_550_100",
  "T2tt_550_150",
  "T2tt_550_200",
  "T2tt_550_250",
  "T2tt_550_275",
  "T2tt_550_300",
  "T2tt_550_325",
  "T2tt_550_350",
  "T2tt_550_375",
  "T2tt_550_400",
  "T2tt_550_425",
  "T2tt_550_450",
  "T2tt_558_375",
  "T2tt_567_400",
  "T2tt_575_275",
  "T2tt_575_300",
  "T2tt_575_325",
  "T2tt_575_350",
  "T2tt_575_375",
  "T2tt_575_400",
  "T2tt_575_425",
  "T2tt_575_450",
  "T2tt_575_475",
  "T2tt_575_488",
  "T2tt_583_400",
  "T2tt_592_425",
  "T2tt_600_1",
  "T2tt_600_50",
  "T2tt_600_100",
  "T2tt_600_150",
  "T2tt_600_200",
  "T2tt_600_250",
  "T2tt_600_300",
  "T2tt_600_325",
  "T2tt_600_350",
  "T2tt_600_375",
  "T2tt_600_400",
  "T2tt_600_425",
  "T2tt_600_450",
  "T2tt_600_475",
  "T2tt_600_500",
  "T2tt_600_513",
  "T2tt_608_425",
  "T2tt_617_450",
  "T2tt_625_325",
  "T2tt_625_350",
  "T2tt_625_375",
  "T2tt_625_400",
  "T2tt_625_425",
  "T2tt_625_450",
  "T2tt_625_475",
  "T2tt_625_500",
  "T2tt_625_525",
  "T2tt_625_538",
  "T2tt_633_450",
  "T2tt_642_475",
  "T2tt_650_1",
  "T2tt_650_50",
  "T2tt_650_100",
  "T2tt_650_150",
  "T2tt_650_200",
  "T2tt_650_250",
  "T2tt_650_300",
  "T2tt_650_350",
  "T2tt_650_375",
  "T2tt_650_400",
  "T2tt_650_425",
  "T2tt_650_450",
  "T2tt_650_475",
  "T2tt_650_500",
  "T2tt_650_525",
  "T2tt_650_550",
  "T2tt_650_563",
  "T2tt_658_475",
  "T2tt_667_500",
  "T2tt_675_375",
  "T2tt_675_400",
  "T2tt_675_425",
  "T2tt_675_450",
  "T2tt_675_475",
  "T2tt_675_500",
  "T2tt_675_525",
  "T2tt_675_550",
  "T2tt_675_575",
  "T2tt_675_588",
  "T2tt_683_500",
  "T2tt_692_525",
  "T2tt_700_1",
  "T2tt_700_50",
  "T2tt_700_100",
  "T2tt_700_150",
  "T2tt_700_200",
  "T2tt_700_250",
  "T2tt_700_300",
  "T2tt_700_350",
  "T2tt_700_400",
  "T2tt_700_425",
  "T2tt_700_450",
  "T2tt_700_475",
  "T2tt_700_500",
  "T2tt_700_525",
  "T2tt_700_550",
  "T2tt_700_575",
  "T2tt_700_600",
  "T2tt_700_613",
  "T2tt_708_525",
  "T2tt_717_550",
  "T2tt_725_425",
  "T2tt_725_450",
  "T2tt_725_475",
  "T2tt_725_500",
  "T2tt_725_525",
  "T2tt_725_550",
  "T2tt_725_575",
  "T2tt_725_600",
  "T2tt_725_625",
  "T2tt_725_638",
  "T2tt_733_550",
  "T2tt_742_575",
  "T2tt_750_1",
  "T2tt_750_50",
  "T2tt_750_100",
  "T2tt_750_150",
  "T2tt_750_200",
  "T2tt_750_250",
  "T2tt_750_300",
  "T2tt_750_350",
  "T2tt_750_400",
  "T2tt_750_450",
  "T2tt_750_475",
  "T2tt_750_500",
  "T2tt_750_525",
  "T2tt_750_550",
  "T2tt_750_575",
  "T2tt_750_600",
  "T2tt_750_625",
  "T2tt_750_650",
  "T2tt_758_575",
  "T2tt_767_600",
  "T2tt_775_475",
  "T2tt_775_500",
  "T2tt_775_525",
  "T2tt_775_550",
  "T2tt_775_575",
  "T2tt_775_600",
  "T2tt_775_625",
  "T2tt_775_650",
  "T2tt_783_600",
  "T2tt_792_625",
  "T2tt_800_1",
  "T2tt_800_50",
  "T2tt_800_100",
  "T2tt_800_150",
  "T2tt_800_200",
  "T2tt_800_250",
  "T2tt_800_300",
  "T2tt_800_350",
  "T2tt_800_400",
  "T2tt_800_450",
  "T2tt_800_500",
  "T2tt_800_525",
  "T2tt_800_550",
  "T2tt_800_575",
  "T2tt_800_600",
  "T2tt_800_625",
  "T2tt_800_650",
  "T2tt_808_625",
  "T2tt_817_650",
  "T2tt_825_525",
  "T2tt_825_550",
  "T2tt_825_575",
  "T2tt_825_600",
  "T2tt_825_625",
  "T2tt_825_650",
  "T2tt_833_650",
  "T2tt_850_1",
  "T2tt_850_50",
  "T2tt_850_100",
  "T2tt_850_150",
  "T2tt_850_200",
  "T2tt_850_250",
  "T2tt_850_300",
  "T2tt_850_350",
  "T2tt_850_400",
  "T2tt_850_450",
  "T2tt_850_500",
  "T2tt_850_550",
  "T2tt_850_575",
  "T2tt_850_600",
  "T2tt_850_625",
  "T2tt_850_650",
  "T2tt_875_575",
  "T2tt_875_600",
  "T2tt_875_625",
  "T2tt_875_650",
  "T2tt_900_1",
  "T2tt_900_50",
  "T2tt_900_100",
  "T2tt_900_150",
  "T2tt_900_200",
  "T2tt_900_250",
  "T2tt_900_300",
  "T2tt_900_350",
  "T2tt_900_400",
  "T2tt_900_450",
  "T2tt_900_500",
  "T2tt_900_550",
  "T2tt_900_600",
  "T2tt_900_625",
  "T2tt_900_650",
  "T2tt_925_625",
  "T2tt_925_650",
  "T2tt_950_1",
  "T2tt_950_50",
  "T2tt_950_100",
  "T2tt_950_150",
  "T2tt_950_200",
  "T2tt_950_250",
  "T2tt_950_300",
  "T2tt_950_350",
  "T2tt_950_400",
  "T2tt_950_450",
  "T2tt_950_500",
  "T2tt_950_550",
  "T2tt_950_600",
  "T2tt_950_650",
  "T2tt_1000_1",
  "T2tt_1000_50",
  "T2tt_1000_100",
  "T2tt_1000_150",
  "T2tt_1000_200",
  "T2tt_1000_250",
  "T2tt_1000_300",
  "T2tt_1000_350",
  "T2tt_1000_400",
  "T2tt_1000_450",
  "T2tt_1000_500",
  "T2tt_1000_550",
  "T2tt_1000_600",
  "T2tt_1000_650",
  "T2tt_1050_1",
  "T2tt_1050_50",
  "T2tt_1050_100",
  "T2tt_1050_150",
  "T2tt_1050_200",
  "T2tt_1050_250",
  "T2tt_1050_300",
  "T2tt_1050_350",
  "T2tt_1050_400",
  "T2tt_1050_450",
  "T2tt_1050_500",
  "T2tt_1050_550",
  "T2tt_1050_600",
  "T2tt_1050_650",
  "T2tt_1100_1",
  "T2tt_1100_50",
  "T2tt_1100_100",
  "T2tt_1100_150",
  "T2tt_1100_200",
  "T2tt_1100_250",
  "T2tt_1100_300",
  "T2tt_1100_350",
  "T2tt_1100_400",
  "T2tt_1100_450",
  "T2tt_1100_500",
  "T2tt_1100_550",
  "T2tt_1100_600",
  "T2tt_1100_650",
  "T2tt_1150_1",
  "T2tt_1150_50",
  "T2tt_1150_100",
  "T2tt_1150_150",
  "T2tt_1150_200",
  "T2tt_1150_250",
  "T2tt_1150_300",
  "T2tt_1150_350",
  "T2tt_1150_400",
  "T2tt_1150_450",
  "T2tt_1150_500",
  "T2tt_1150_550",
  "T2tt_1150_600",
  "T2tt_1150_650",
  "T2tt_1200_1",
  "T2tt_1200_50",
  "T2tt_1200_100",
  "T2tt_1200_150",
  "T2tt_1200_200",
  "T2tt_1200_250",
  "T2tt_1200_300",
  "T2tt_1200_350",
  "T2tt_1200_400",
  "T2tt_1200_450",
  "T2tt_1200_500",
  "T2tt_1200_550",
  "T2tt_1200_600",
  "T2tt_1200_650",
  "T2fbd_250_170",
  "T2fbd_250_180",
  "T2fbd_250_190",
  "T2fbd_250_200",
  "T2fbd_250_210",
  "T2fbd_250_220",
  "T2fbd_250_230",
  "T2fbd_250_240",
  "T2fbd_275_195",
  "T2fbd_275_205",
  "T2fbd_275_215",
  "T2fbd_275_225",
  "T2fbd_275_235",
  "T2fbd_275_245",
  "T2fbd_275_255",
  "T2fbd_275_265",
  "T2fbd_300_220",
  "T2fbd_300_230",
  "T2fbd_300_240",
  "T2fbd_300_250",
  "T2fbd_300_260",
  "T2fbd_300_270",
  "T2fbd_300_280",
  "T2fbd_300_290",
  "T2fbd_325_245",
  "T2fbd_325_255",
  "T2fbd_325_265",
  "T2fbd_325_275",
  "T2fbd_325_285",
  "T2fbd_325_295",
  "T2fbd_325_305",
  "T2fbd_325_315",
  "T2fbd_350_270",
  "T2fbd_350_280",
  "T2fbd_350_290",
  "T2fbd_350_300",
  "T2fbd_350_310",
  "T2fbd_350_320",
  "T2fbd_350_330",
  "T2fbd_350_340",
  "T2fbd_375_295",
  "T2fbd_375_305",
  "T2fbd_375_315",
  "T2fbd_375_325",
  "T2fbd_375_335",
  "T2fbd_375_345",
  "T2fbd_375_355",
  "T2fbd_375_365",
  "T2fbd_400_320",
  "T2fbd_400_330",
  "T2fbd_400_340",
  "T2fbd_400_350",
  "T2fbd_400_360",
  "T2fbd_400_370",
  "T2fbd_400_380",
  "T2fbd_400_390",
  "T2fbd_425_345",
  "T2fbd_425_355",
  "T2fbd_425_365",
  "T2fbd_425_375",
  "T2fbd_425_385",
  "T2fbd_425_395",
  "T2fbd_425_405",
  "T2fbd_425_415",
  "T2fbd_450_370",
  "T2fbd_450_380",
  "T2fbd_450_390",
  "T2fbd_450_400",
  "T2fbd_450_410",
  "T2fbd_450_420",
  "T2fbd_450_430",
  "T2fbd_450_440",
  "T2fbd_475_395",
  "T2fbd_475_405",
  "T2fbd_475_415",
  "T2fbd_475_425",
  "T2fbd_475_435",
  "T2fbd_475_445",
  "T2fbd_475_455",
  "T2fbd_475_465",
  "T2fbd_500_420",
  "T2fbd_500_430",
  "T2fbd_500_440",
  "T2fbd_500_450",
  "T2fbd_500_460",
  "T2fbd_500_470",
  "T2fbd_500_480",
  "T2fbd_500_490",
  "T2fbd_525_445",
  "T2fbd_525_455",
  "T2fbd_525_465",
  "T2fbd_525_475",
  "T2fbd_525_485",
  "T2fbd_525_495",
  "T2fbd_525_505",
  "T2fbd_525_515",
  "T2fbd_550_470",
  "T2fbd_550_480",
  "T2fbd_550_490",
  "T2fbd_550_500",
  "T2fbd_550_510",
  "T2fbd_550_520",
  "T2fbd_550_530",
  "T2fbd_550_540",
  "T2fbd_575_495",
  "T2fbd_575_505",
  "T2fbd_575_515",
  "T2fbd_575_525",
  "T2fbd_575_535",
  "T2fbd_575_545",
  "T2fbd_575_555",
  "T2fbd_575_565",
  "T2fbd_600_520",
  "T2fbd_600_530",
  "T2fbd_600_540",
  "T2fbd_600_550",
  "T2fbd_600_560",
  "T2fbd_600_570",
  "T2fbd_600_580",
  "T2fbd_600_590",
  "T2fbd_625_545",
  "T2fbd_625_555",
  "T2fbd_625_565",
  "T2fbd_625_575",
  "T2fbd_625_585",
  "T2fbd_625_595",
  "T2fbd_625_605",
  "T2fbd_625_615",
  "T2fbd_650_570",
  "T2fbd_650_580",
  "T2fbd_650_590",
  "T2fbd_650_600",
  "T2fbd_650_610",
  "T2fbd_650_620",
  "T2fbd_650_630",
  "T2fbd_650_640",
  "T2fbd_675_595",
  "T2fbd_675_605",
  "T2fbd_675_615",
  "T2fbd_675_625",
  "T2fbd_675_635",
  "T2fbd_675_645",
  "T2fbd_675_655",
  "T2fbd_675_665",
  "T2fbd_700_620",
  "T2fbd_700_630",
  "T2fbd_700_640",
  "T2fbd_700_650",
  "T2fbd_700_660",
  "T2fbd_700_670",
  "T2fbd_700_680",
  "T2fbd_700_690",
  "T2fbd_725_645",
  "T2fbd_725_655",
  "T2fbd_725_665",
  "T2fbd_725_675",
  "T2fbd_725_685",
  "T2fbd_725_695",
  "T2fbd_725_705",
  "T2fbd_725_715",
  "T2fbd_750_670",
  "T2fbd_750_680",
  "T2fbd_750_690",
  "T2fbd_750_700",
  "T2fbd_750_710",
  "T2fbd_750_720",
  "T2fbd_750_730",
  "T2fbd_750_740",
  "T2fbd_775_695",
  "T2fbd_775_705",
  "T2fbd_775_715",
  "T2fbd_775_725",
  "T2fbd_775_735",
  "T2fbd_775_745",
  "T2fbd_775_755",
  "T2fbd_775_765",
  "T2fbd_800_720",
  "T2fbd_800_730",
  "T2fbd_800_740",
  "T2fbd_800_750",
  "T2fbd_800_760",
  "T2fbd_800_770",
  "T2fbd_800_780",
  "T2fbd_800_790"
};

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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                         "hm_nb1_lowmtb_nj7"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                         "hm_nb2_lowmtb_nj7"},
  
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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                         "hm_nb1_lowmtb_nj7"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                         "hm_nb2_lowmtb_nj7"},
  
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
  config.outputdir = outputdir+"/znunu";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("singlepho",   "Data",           datadir+"/photoncr/singlepho",  "1.0",  datasel + trigPhoCR);

  config.addSample("photon",      "Photon",         "photoncr/photon",     phowgt, datasel + trigPhoCR + phoBadEventRemoval);
//  config.addSample("photon",      "Photon",         "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt, datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = phoCatMap();
  config.crMapping = phocrMapping;

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig zllConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/zllcr";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("dyll",      "Z#rightarrowll+jets",    "zllcr/z-soup",                    lepselwgt, datasel + trigDiLepCR);
  config.addSample("ttbar",     "t#bar{t}",               "zllcr/t-soup",                    lepselwgt, datasel + trigDiLepCR);
  config.addSample("doublelep", "Data",                   datadir+"/zllcr/doublelep",       "1.0",     datasel + trigDiLepCR);

  config.sel = baseline;
  config.catMaps = zllCatMap;
  for (auto &c : zllCatMap) config.categories.push_back(c.first);

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig lepConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/LLB";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  if (ADD_LEP_TO_MET){
    config.addSample("singlelep",   "Data",          datadir+"/singlelep",       "1.0",     datasel + trigLepCR + lepcrsel);
    config.addSample("ttbar",       "t#bar{t}",      "ttbar",           onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("wjets",       "W+jets",        "wjets",           onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("tW",          "tW",            "tW",              onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("ttW",         "ttW",           "ttW",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "qcd",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",        "Data",          datadir+"met",                   "1.0",          datasel + trigSR + revert_vetoes);
    //config.addSample("singlelep-2016",   "Data 2016",     datadir+"met_2016",              "1.0",          datasel + trigSR + revert_vetoes);
    config.addSample("ttbar-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",      datasel + revert_vetoes);
    config.addSample("wjets-2016",       "W+jets",        inputdir_2016+"wjets",           lepselwgt,      datasel + revert_vetoes);
    config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              lepselwgt,      datasel + revert_vetoes);
    config.addSample("ttW-2016",         "ttW",           inputdir_2016+"ttW",             lepselwgt,      datasel + revert_vetoes);
    //config.addSample("ttZ-2016",         "ttZ",           inputdir_2016+"ttZ",             lepselwgt,      datasel + revert_vetoes);
    //config.addSample("diboson-2016",     "Diboson",       inputdir_2016+"diboson",         lepselwgt,      datasel + revert_vetoes);
    //config.addSample("qcd-2016",         "QCD",           inputdir_2016+"qcd",             lepselwgt,      datasel + revert_vetoes);

    //config.addSample("singlelep-2017RunBtoE",   "Data 2017RunBtoE",     datadir+"met_RunBtoE",              "1.0",          datasel + trigSR + revert_vetoes);
    config.addSample("ttbar-2017RunBtoE",         "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_RunBtoE,      datasel + revert_vetoes);
    config.addSample("wjets-2017RunBtoE",         "W+jets",        inputdir_2017+"wjets",           lepselwgt_RunBtoE,      datasel + revert_vetoes);
    config.addSample("tW-2017RunBtoE",            "tW",            inputdir_2017+"tW",              lepselwgt_RunBtoE,      datasel + revert_vetoes);
    config.addSample("ttW-2017RunBtoE",           "ttW",           inputdir_2017+"ttW",             lepselwgt_RunBtoE,      datasel + revert_vetoes);
    //config.addSample("ttZ-2017RunBtoE",           "ttZ",           inputdir_2017+"ttZ",             lepselwgt_RunBtoE,      datasel + revert_vetoes);
    //config.addSample("diboson-2017RunBtoE",       "Diboson",       inputdir_2017+"diboson",         lepselwgt_RunBtoE,      datasel + revert_vetoes);
    //config.addSample("qcd-2017RunBtoE",           "QCD",           inputdir_2017+"qcd",             lepselwgt_RunBtoE,      datasel + revert_vetoes);
    //config.addSample("singlelep-2017RunF",   "Data 2017RunF",     datadir+"met_RunF",              "1.0",          datasel + trigSR + revert_vetoes);
    config.addSample("ttbar-2017RunF",       	  "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_RunF,      datasel + revert_vetoes);
    config.addSample("wjets-2017RunF",       	  "W+jets",        inputdir_2017+"wjets",           lepselwgt_RunF,      datasel + revert_vetoes);
    config.addSample("tW-2017RunF",          	  "tW",            inputdir_2017+"tW",              lepselwgt_RunF,      datasel + revert_vetoes);
    config.addSample("ttW-2017RunF",         	  "ttW",           inputdir_2017+"ttW",             lepselwgt_RunF,      datasel + revert_vetoes);
    //config.addSample("ttZ-2017RunF",         	  "ttZ",           inputdir_2017+"ttZ",             lepselwgt_RunF,      datasel + revert_vetoes);
    //config.addSample("diboson-2017RunF",     	  "Diboson",       inputdir_2017+"diboson",         lepselwgt_RunF,      datasel + revert_vetoes);
    //config.addSample("qcd-2017RunF",         	  "QCD",           inputdir_2017+"qcd",             lepselwgt_RunF,      datasel + revert_vetoes);

    //config.addSample("singlelep-2018preHEM",   "Data 2018preHEM",     datadir+"met_2018",              "1.0",          datasel + trigSR + revert_vetoes);
    config.addSample("ttbar-2018preHEM",         "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_preHEM,      datasel + revert_vetoes);
    config.addSample("wjets-2018preHEM",         "W+jets",        inputdir_2018+"wjets",           lepselwgt_preHEM,      datasel + revert_vetoes);
    config.addSample("tW-2018preHEM",            "tW",            inputdir_2018+"tW",              lepselwgt_preHEM,      datasel + revert_vetoes);
    config.addSample("ttW-2018preHEM",           "ttW",           inputdir_2018+"ttW",             lepselwgt_preHEM,      datasel + revert_vetoes);
    //config.addSample("ttZ-2018preHEM",           "ttZ",           inputdir_2018+"ttZ",             lepselwgt_preHEM,      datasel + revert_vetoes);
    //config.addSample("diboson-2018preHEM",       "Diboson",       inputdir_2018+"diboson",         lepselwgt_preHEM,      datasel + revert_vetoes);
    //config.addSample("qcd-2018preHEM",           "QCD",           inputdir_2018+"qcd",             lepselwgt_preHEM,      datasel + revert_vetoes);
    //config.addSample("singlelep-2018postHEM",   "Data 2018postHEM",     datadir+"met_2018",              "1.0",    dataselHEM + trigSR + revert_vetoes);
    config.addSample("ttbar-2018postHEM",        "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_postHEM,      dataselHEM + revert_vetoes);
    config.addSample("wjets-2018postHEM",        "W+jets",        inputdir_2018+"wjets",           lepselwgt_postHEM,      dataselHEM + revert_vetoes);
    config.addSample("tW-2018postHEM",           "tW",            inputdir_2018+"tW",              lepselwgt_postHEM,      dataselHEM + revert_vetoes);
    config.addSample("ttW-2018postHEM",          "ttW",           inputdir_2018+"ttW",             lepselwgt_postHEM,      dataselHEM + revert_vetoes);
    //config.addSample("ttZ-2018postHEM",          "ttZ",           inputdir_2018+"ttZ",             lepselwgt_postHEM,      dataselHEM + revert_vetoes);
    //config.addSample("diboson-2018postHEM",      "Diboson",       inputdir_2018+"diboson",         lepselwgt_postHEM,      dataselHEM + revert_vetoes);
    //config.addSample("qcd-2018postHEM",          "QCD",           inputdir_2018+"qcd",             lepselwgt_postHEM,      dataselHEM + revert_vetoes);

    // add signals in lepcr
    for (const auto &sig : signals_small){
      config.addSample("lepcr_"+sig,   sig,          inputdir_sig+sig,    siglepselwgt, datasel + trigSR + revert_vetoes);
    }
  }

  config.addSample("ttbar-2016-sr",       "t#bar{t}",      inputdir_2016+"ttbar",                lepvetowgt+"*ISRWeight", datasel + vetoes);
  config.addSample("wjets-2016-sr",       "W+jets",        inputdir_2016+"wjets",                lepvetowgt, datasel + vetoes);
  config.addSample("tW-2016-sr",          "tW",            inputdir_2016+"tW",                   lepvetowgt, datasel + vetoes);
  config.addSample("ttW-2016-sr",         "ttW",           inputdir_2016+"ttW",                  lepvetowgt, datasel + vetoes);
  config.addSample("ttZ-2016-sr",         "ttZ",           inputdir_2016+"ttZ",                  lepvetowgt, datasel + vetoes);
  config.addSample("diboson-2016-sr",     "Diboson",       inputdir_2016+"diboson",              lepvetowgt, datasel + vetoes);

  config.addSample("ttbar-2017RunBtoE-sr",    "t#bar{t}",      inputdir_2017+"ttbar",            lepvetowgt_RunBtoE, datasel + vetoes);
  config.addSample("wjets-2017RunBtoE-sr",    "W+jets",        inputdir_2017+"wjets",            lepvetowgt_RunBtoE, datasel + vetoes);
  config.addSample("tW-2017RunBtoE-sr",       "tW",            inputdir_2017+"tW",               lepvetowgt_RunBtoE, datasel + vetoes);
  config.addSample("ttW-2017RunBtoE-sr",      "ttW",           inputdir_2017+"ttW",              lepvetowgt_RunBtoE, datasel + vetoes);
  config.addSample("ttZ-2017RunBtoE-sr",      "ttZ",           inputdir_2017+"ttZ",              lepvetowgt_RunBtoE, datasel + vetoes);
  config.addSample("diboson-2017RunBtoE-sr",  "Diboson",       inputdir_2017+"diboson",          lepvetowgt_RunBtoE, datasel + vetoes);
  config.addSample("ttbar-2017RunF-sr",       "t#bar{t}",      inputdir_2017+"ttbar",            lepvetowgt_RunF, datasel + vetoes);
  config.addSample("wjets-2017RunF-sr",       "W+jets",        inputdir_2017+"wjets",            lepvetowgt_RunF, datasel + vetoes);
  config.addSample("tW-2017RunF-sr",          "tW",            inputdir_2017+"tW",               lepvetowgt_RunF, datasel + vetoes);
  config.addSample("ttW-2017RunF-sr",         "ttW",           inputdir_2017+"ttW",              lepvetowgt_RunF, datasel + vetoes);
  config.addSample("ttZ-2017RunF-sr",         "ttZ",           inputdir_2017+"ttZ",              lepvetowgt_RunF, datasel + vetoes);
  config.addSample("diboson-2017RunF-sr",     "Diboson",       inputdir_2017+"diboson",          lepvetowgt_RunF, datasel + vetoes);

  config.addSample("ttbar-2018preHEM-sr",    "t#bar{t}",      inputdir_2018+"ttbar",             lepvetowgt_preHEM, datasel + vetoes);
  config.addSample("wjets-2018preHEM-sr",    "W+jets",        inputdir_2018+"wjets",             lepvetowgt_preHEM, datasel + vetoes);
  config.addSample("tW-2018preHEM-sr",       "tW",            inputdir_2018+"tW",                lepvetowgt_preHEM, datasel + vetoes);
  config.addSample("ttW-2018preHEM-sr",      "ttW",           inputdir_2018+"ttW",               lepvetowgt_preHEM, datasel + vetoes);
  config.addSample("ttZ-2018preHEM-sr",      "ttZ",           inputdir_2018+"ttZ",               lepvetowgt_preHEM, datasel + vetoes);
  config.addSample("diboson-2018preHEM-sr",  "Diboson",       inputdir_2018+"diboson",           lepvetowgt_preHEM, datasel + vetoes);
  config.addSample("ttbar-2018postHEM-sr",   "t#bar{t}",      inputdir_2018+"ttbar",             lepvetowgt_postHEM, dataselHEM + vetoes);
  config.addSample("wjets-2018postHEM-sr",   "W+jets",        inputdir_2018+"wjets",             lepvetowgt_postHEM, dataselHEM + vetoes);
  config.addSample("tW-2018postHEM-sr",      "tW",            inputdir_2018+"tW",                lepvetowgt_postHEM, dataselHEM + vetoes);
  config.addSample("ttW-2018postHEM-sr",     "ttW",           inputdir_2018+"ttW",               lepvetowgt_postHEM, dataselHEM + vetoes);
  config.addSample("ttZ-2018postHEM-sr",     "ttZ",           inputdir_2018+"ttZ",               lepvetowgt_postHEM, dataselHEM + vetoes);
  config.addSample("diboson-2018postHEM-sr", "Diboson",       inputdir_2018+"diboson",           lepvetowgt_postHEM, dataselHEM + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = lepCatMap();
  config.crMapping = lepcrMapping;

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig qcdConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/QCD";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  // qcdcr
  config.addSample("data-cr",     "Data",             datadir+"met",  "1.0",      datasel + trigSR + vetoes + dphi_invert);
  
  config.addSample("qcd-2016-cr",      "QCD",              inputdir_2016+"qcd",       qcdwgt,      datasel + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2016-withveto-cr",  "QCD",         inputdir_2016+"qcd",       qcdvetowgt,  datasel + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2016-withveto-sr",  "QCD",         inputdir_2016+"qcd",       qcdvetowgt,  datasel + vetoes + qcdSpikeRemovals);

  config.addSample("qcd-2017RunBtoE-cr",      "QCD",       inputdir_2017+"qcd",       qcdwgt_RunBtoE,      datasel + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2017RunBtoE-withveto-cr",  "QCD",  inputdir_2017+"qcd",       qcdvetowgt_RunBtoE,  datasel + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2017RunBtoE-withveto-sr",  "QCD",  inputdir_2017+"qcd",       qcdvetowgt_RunBtoE,  datasel + vetoes + qcdSpikeRemovals);
  config.addSample("qcd-2017RunF-cr",      "QCD",          inputdir_2017+"qcd",       qcdwgt_RunF,         datasel + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2017RunF-withveto-cr",  "QCD",     inputdir_2017+"qcd",       qcdvetowgt_RunF,     datasel + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2017RunF-withveto-sr",  "QCD",     inputdir_2017+"qcd",       qcdvetowgt_RunF,     datasel + vetoes + qcdSpikeRemovals);

  config.addSample("qcd-2018preHEM-cr",      "QCD",        inputdir_2018+"qcd",       qcdwgt_preHEM,       datasel + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2018preHEM-withveto-cr",  "QCD",   inputdir_2018+"qcd",       qcdvetowgt_preHEM,   datasel + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2018preHEM-withveto-sr",  "QCD",   inputdir_2018+"qcd",       qcdvetowgt_preHEM,   datasel + vetoes + qcdSpikeRemovals);
  config.addSample("qcd-2018postHEM-cr",      "QCD",       inputdir_2018+"qcd",       qcdwgt_postHEM,      dataselHEM + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2018postHEM-withveto-cr",  "QCD",  inputdir_2018+"qcd",       qcdvetowgt_postHEM,  dataselHEM + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-2018postHEM-withveto-sr",  "QCD",  inputdir_2018+"qcd",       qcdvetowgt_postHEM,  dataselHEM + vetoes + qcdSpikeRemovals);

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-2016-cr",       "t#bar{t}",      inputdir_2016+"ttbar",        lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("wjets-2016-cr",       "W+jets",        inputdir_2016+"wjets",        lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("tW-2016-cr",          "tW",            inputdir_2016+"tW",           lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("ttW-2016-cr",         "ttW",           inputdir_2016+"ttW",          lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("znunu-2016-cr",       "Znunu",         inputdir_2016+"znunu",        lepvetowgt,  datasel + vetoes + dphi_invert);

  config.addSample("ttbar-2017RunBtoE-cr",       "t#bar{t}",      inputdir_2017+"ttbar",        lepvetowgt_RunBtoE,  datasel + vetoes + dphi_invert);
  config.addSample("wjets-2017RunBtoE-cr",       "W+jets",        inputdir_2017+"wjets",        lepvetowgt_RunBtoE,  datasel + vetoes + dphi_invert);
  config.addSample("tW-2017RunBtoE-cr",          "tW",            inputdir_2017+"tW",           lepvetowgt_RunBtoE,  datasel + vetoes + dphi_invert);
  config.addSample("ttW-2017RunBtoE-cr",         "ttW",           inputdir_2017+"ttW",          lepvetowgt_RunBtoE,  datasel + vetoes + dphi_invert);
  config.addSample("znunu-2017RunBtoE-cr",       "Znunu",         inputdir_2017+"znunu",        lepvetowgt_RunBtoE,  datasel + vetoes + dphi_invert);
  config.addSample("ttbar-2017RunF-cr",          "t#bar{t}",      inputdir_2017+"ttbar",           lepvetowgt_RunF,     datasel + vetoes + dphi_invert);
  config.addSample("wjets-2017RunF-cr",          "W+jets",        inputdir_2017+"wjets",           lepvetowgt_RunF,     datasel + vetoes + dphi_invert);
  config.addSample("tW-2017RunF-cr",             "tW",            inputdir_2017+"tW",              lepvetowgt_RunF,     datasel + vetoes + dphi_invert);
  config.addSample("ttW-2017RunF-cr",            "ttW",           inputdir_2017+"ttW",             lepvetowgt_RunF,     datasel + vetoes + dphi_invert);
  config.addSample("znunu-2017RunF-cr",          "Znunu",         inputdir_2017+"znunu",           lepvetowgt_RunF,     datasel + vetoes + dphi_invert);

  config.addSample("ttbar-2018preHEM-cr",        "t#bar{t}",      inputdir_2018+"ttbar",        lepvetowgt_preHEM,  datasel + vetoes + dphi_invert);
  config.addSample("wjets-2018preHEM-cr",        "W+jets",        inputdir_2018+"wjets",        lepvetowgt_preHEM,  datasel + vetoes + dphi_invert);
  config.addSample("tW-2018preHEM-cr",           "tW",            inputdir_2018+"tW",           lepvetowgt_preHEM,  datasel + vetoes + dphi_invert);
  config.addSample("ttW-2018preHEM-cr",          "ttW",           inputdir_2018+"ttW",          lepvetowgt_preHEM,  datasel + vetoes + dphi_invert);
  config.addSample("znunu-2018preHEM-cr",        "Znunu",         inputdir_2018+"znunu",        lepvetowgt_preHEM,  datasel + vetoes + dphi_invert);
  config.addSample("ttbar-2018postHEM-cr",       "t#bar{t}",      inputdir_2018+"ttbar",       lepvetowgt_postHEM, dataselHEM + vetoes + dphi_invert);
  config.addSample("wjets-2018postHEM-cr",       "W+jets",        inputdir_2018+"wjets",       lepvetowgt_postHEM, dataselHEM + vetoes + dphi_invert);
  config.addSample("tW-2018postHEM-cr",          "tW",            inputdir_2018+"tW",          lepvetowgt_postHEM, dataselHEM + vetoes + dphi_invert);
  config.addSample("ttW-2018postHEM-cr",         "ttW",           inputdir_2018+"ttW",         lepvetowgt_postHEM, dataselHEM + vetoes + dphi_invert);
  config.addSample("znunu-2018postHEM-cr",       "Znunu",         inputdir_2018+"znunu",       lepvetowgt_postHEM, dataselHEM + vetoes + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",           "Data",          datadir+"met", "1.0",      datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("ttbar-2016-norm",     "t#bar{t}",      inputdir_2016+"ttbar",     lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("wjets-2016-norm",     "W+jets",        inputdir_2016+"wjets",     lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("tW-2016-norm",        "tW",            inputdir_2016+"tW",        lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("ttW-2016-norm",       "ttW",           inputdir_2016+"ttW",       lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("qcd-2016-norm",       "QCD",           inputdir_2016+"qcd",       lepselwgt,   datasel + revert_vetoes + dphi_cut + qcdSpikeRemovals);

  config.addSample("ttbar-2017RunBtoE-norm",     "t#bar{t}",      inputdir_2017+"ttbar",     lepselwgt_RunBtoE,   datasel + revert_vetoes + dphi_cut);
  config.addSample("wjets-2017RunBtoE-norm",     "W+jets",        inputdir_2017+"wjets",     lepselwgt_RunBtoE,   datasel + revert_vetoes + dphi_cut);
  config.addSample("tW-2017RunBtoE-norm",        "tW",            inputdir_2017+"tW",        lepselwgt_RunBtoE,   datasel + revert_vetoes + dphi_cut);
  config.addSample("ttW-2017RunBtoE-norm",       "ttW",           inputdir_2017+"ttW",       lepselwgt_RunBtoE,   datasel + revert_vetoes + dphi_cut);
  config.addSample("qcd-2017RunBtoE-norm",       "QCD",           inputdir_2017+"qcd",       lepselwgt_RunBtoE,   datasel + revert_vetoes + dphi_cut + qcdSpikeRemovals);
  config.addSample("ttbar-2017RunF-norm",        "t#bar{t}",      inputdir_2017+"ttbar",     lepselwgt_RunF,      datasel + revert_vetoes + dphi_cut);
  config.addSample("wjets-2017RunF-norm",        "W+jets",        inputdir_2017+"wjets",     lepselwgt_RunF,      datasel + revert_vetoes + dphi_cut);
  config.addSample("tW-2017RunF-norm",           "tW",            inputdir_2017+"tW",        lepselwgt_RunF,      datasel + revert_vetoes + dphi_cut);
  config.addSample("ttW-2017RunF-norm",          "ttW",           inputdir_2017+"ttW",       lepselwgt_RunF,      datasel + revert_vetoes + dphi_cut);
  config.addSample("qcd-2017RunF-norm",          "QCD",           inputdir_2017+"qcd",       lepselwgt_RunF,      datasel + revert_vetoes + dphi_cut + qcdSpikeRemovals);

  config.addSample("ttbar-2018preHEM-norm",     "t#bar{t}",      inputdir_2018+"ttbar",     lepselwgt_preHEM,   datasel + revert_vetoes + dphi_cut);
  config.addSample("wjets-2018preHEM-norm",     "W+jets",        inputdir_2018+"wjets",     lepselwgt_preHEM,   datasel + revert_vetoes + dphi_cut);
  config.addSample("tW-2018preHEM-norm",        "tW",            inputdir_2018+"tW",        lepselwgt_preHEM,   datasel + revert_vetoes + dphi_cut);
  config.addSample("ttW-2018preHEM-norm",       "ttW",           inputdir_2018+"ttW",       lepselwgt_preHEM,   datasel + revert_vetoes + dphi_cut);
  config.addSample("qcd-2018preHEM-norm",       "QCD",           inputdir_2018+"qcd",       lepselwgt_preHEM,   datasel + revert_vetoes + dphi_cut + qcdSpikeRemovals);
  config.addSample("ttbar-2018postHEM-norm",    "t#bar{t}",      inputdir_2018+"ttbar",     lepselwgt_postHEM,  dataselHEM + revert_vetoes + dphi_cut);
  config.addSample("wjets-2018postHEM-norm",    "W+jets",        inputdir_2018+"wjets",     lepselwgt_postHEM,  dataselHEM + revert_vetoes + dphi_cut);
  config.addSample("tW-2018postHEM-norm",       "tW",            inputdir_2018+"tW",        lepselwgt_postHEM,  dataselHEM + revert_vetoes + dphi_cut);
  config.addSample("ttW-2018postHEM-norm",      "ttW",           inputdir_2018+"ttW",       lepselwgt_postHEM,  dataselHEM + revert_vetoes + dphi_cut);
  config.addSample("qcd-2018postHEM-norm",      "QCD",           inputdir_2018+"qcd",       lepselwgt_postHEM,  dataselHEM + revert_vetoes + dphi_cut + qcdSpikeRemovals);

  // qcdsr
  config.addSample("qcd-2016-sr",         "QCD",           inputdir_2016+"qcd",       qcdwgt,           datasel + qcdSpikeRemovals);
  config.addSample("qcd-2017RunBtoE-sr",  "QCD",           inputdir_2017+"qcd",       qcdwgt_RunBtoE,   datasel + qcdSpikeRemovals);
  config.addSample("qcd-2017RunF-sr",     "QCD",           inputdir_2017+"qcd",       qcdwgt_RunF,      datasel + qcdSpikeRemovals);
  config.addSample("qcd-2018preHEM-sr",   "QCD",           inputdir_2018+"qcd",       qcdwgt_preHEM,    datasel + qcdSpikeRemovals);
  config.addSample("qcd-2018postHEM-sr",  "QCD",           inputdir_2018+"qcd",       qcdwgt_postHEM,   dataselHEM + qcdSpikeRemovals);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();    // sr DPhi cut applied
  config.crCatMaps = qcdCatMap(); // no DPhi cut in category def
  config.crMapping = qcdcrMapping;

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// --------------
std::vector<TString> mergedSRbins{
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

std::map<TString, TString> mergedSRcuts = []{
    std::map<TString, TString> cuts;
    for (auto name : mergedSRbins)
      cuts[name] = createCutString(name, cutMap);
    return cuts;
}();

std::map<TString, TString> mergedSRlabels = []{
    std::map<TString, TString> cmap;
    for (auto s: mergedSRbins) cmap[s] = s;
    return cmap;
}();

std::map<TString, std::vector<int>> mergedSRMETbins{
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

map<TString, Category> mergedSRCatMap(){
  map<TString, Category> cmap;
  for (auto &name : mergedSRbins){
    cmap[name] = Category(name, mergedSRcuts.at(name), mergedSRlabels.at(name), BinInfo("MET_pt", "#slash{E}_{T}", mergedSRMETbins.at(name), "GeV"));
  }
  return cmap;
}

BaseConfig srConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("data",        	     "Data",          datadir+"met",    		 "1.0",      datasel + trigSR + vetoes);
  //config.addSample("ttZ",            "ttZ",           inputdir_2016+"ttZ",               lepvetowgt, datasel + vetoes);
  //config.addSample("diboson",        "Diboson",       inputdir_2016+"diboson",           lepvetowgt, datasel + vetoes);


  config.sel = baseline;
  config.categories = mergedSRbins;
  config.catMaps = mergedSRCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig signalConfig(TString signal){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/sig";

  // signals in sr
  config.addSample(signal,          signal,           inputdir_sig+signal,    sigwgt,      datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = mergedSRbins;
  config.catMaps = mergedSRCatMap();

  return config;
}

BaseConfig lepcrSignalConfig(TString signal){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/LLB";

  // add signals in lepcr
  config.addSample("lepcr_"+signal,   signal,          inputdir_sig+signal,   siglepselwgt, datasel + trigSR + revert_vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = lepCatMap();
  config.crMapping = lepcrMapping;

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
map<std::string, std::string> makeBinMap(TString control_region){
  map<std::string, vector<TString>> results; // srbinname_met -> [(sr_sub1, cr_sub1), ...]

  const auto &crMapping = control_region=="phocr" ? phocrMapping : (control_region=="lepcr" ? lepcrMapping : qcdcrMapping);

  const auto &merged_srCatMap = mergedSRCatMap();
  const auto &split_srCatMap = srCatMap();

  for (const auto &merged_cat_name : mergedSRbins){
    cout << "merged bin: " << merged_cat_name << endl;
    vector<TString> categories_to_process; // get the categories to consider
    if (merged_cat_name.BeginsWith("lm") || merged_cat_name.Contains("lowmtb")) continue;
    if(merged_cat_name.Contains("nb2")){
      TString nb2_bin = TString(merged_cat_name).ReplaceAll("nb2", "nbeq2");
      categories_to_process.push_back(TString(nb2_bin).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_ht1000to1300"));
      categories_to_process.push_back(TString(nb2_bin).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_ht1300to1500"));
      categories_to_process.push_back(TString(nb2_bin).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_htgt1500"));
      TString nb3_bin = TString(merged_cat_name).ReplaceAll("nb2", "nb3");
      categories_to_process.push_back(TString(nb3_bin).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_ht1000to1500"));
      categories_to_process.push_back(TString(nb3_bin).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_htgt1500"));
    } else if (merged_cat_name.Contains("nt0_nrt0_nw0")) {
      categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_ht1000to1300"));
      categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_ht1300to1500"));
      categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("nt0_nrt0_nw0_htgt1000", "nt0_nrt0_nw0_htgt1500"));
    }
    else {
      if (merged_cat_name.Contains("ht1000to1500")) {
	if (!merged_cat_name.Contains("nb3")){
          categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("ht1000to1500", "ht1000to1300"));
          categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("ht1000to1500", "ht1300to1500"));
	} else {
	  categories_to_process.push_back(TString(merged_cat_name));
	}
      } else if (merged_cat_name.Contains("htlt1000")) {
          categories_to_process.push_back(TString(merged_cat_name));
      } else if (merged_cat_name.Contains("htlt1300")) {
          categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("htlt1300", "htlt1000"));
          categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("htlt1300", "ht1000to1300"));
      } else if (merged_cat_name.Contains("htgt1300")) {
          categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("htgt1300", "ht1300to1500"));
          categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("htgt1300", "htgt1500"));
      } else if (merged_cat_name.Contains("htgt1500")) {
          categories_to_process.push_back(TString(merged_cat_name));
      } else if (!merged_cat_name.Contains("ht")) {
	if(!merged_cat_name.Contains("nb3")){
          categories_to_process.push_back(TString(merged_cat_name) + "_htlt1000");
          categories_to_process.push_back(TString(merged_cat_name) + "_ht1000to1300");
          categories_to_process.push_back(TString(merged_cat_name) + "_ht1300to1500");
          categories_to_process.push_back(TString(merged_cat_name) + "_htgt1500");
	} else {
          categories_to_process.push_back(TString(merged_cat_name) + "_htlt1000");
          categories_to_process.push_back(TString(merged_cat_name) + "_ht1000to1500");
          categories_to_process.push_back(TString(merged_cat_name) + "_htgt1500");
	}
      }
    }

    // create the sr-to-cr map
    const auto& merged_bin = merged_srCatMap.at(merged_cat_name);
    for (const auto &split_cat_name : categories_to_process){
      // loop over all categories to consider, e.g., ht bins
      
      const auto &split_bin = split_srCatMap.at(split_cat_name);
      for (unsigned ibin=0; ibin<merged_bin.bin.nbins; ++ibin){
        std::string mergedsr_binname = ("bin_"+merged_cat_name+"_"+merged_bin.bin.binnames.at(ibin)).Data();
        if (merged_bin.bin.plotbins.at(ibin+1) == split_bin.bin.plotbins.at(ibin+1)) {
          if (merged_cat_name.Contains("lowmtb")) continue;
          else{
            // no splitting in MET: merged in nj
            auto splitsrbinname = "bin_"+split_cat_name+"_"+split_bin.bin.binnames.at(ibin);
            auto crbinname = "bin_"+control_region+"_"+TString(crMapping.at(split_cat_name)).ReplaceAll("NoDPhi_","_")+"_"+split_bin.bin.binnames.at(ibin);
            results[mergedsr_binname]; // touch it: initialize it if not, otherwise should append (5-6j, and >=7j)
            results[mergedsr_binname].push_back("<"+splitsrbinname+">*("+crbinname+")");
          }
        }else{
          // also merge in MET
          for (unsigned icr = ibin; icr < split_bin.bin.nbins; ++icr){
	    if(split_bin.bin.plotbins.at(icr+1) <= merged_bin.bin.plotbins.at(ibin+1) && split_bin.bin.plotbins.at(icr) >= merged_bin.bin.plotbins.at(ibin)){
              auto splitsrbinname = "bin_"+split_cat_name+"_"+split_bin.bin.binnames.at(icr);
              auto crbinname = "bin_"+control_region+"_"+TString(crMapping.at(split_cat_name)).ReplaceAll("NoDPhi_","_")+"_"+split_bin.bin.binnames.at(icr);
              results[mergedsr_binname]; // touch it: initialize it if not, otherwise should append (5-6j, and >=7j)
              results[mergedsr_binname].push_back("<"+splitsrbinname+">*("+crbinname+")");
            }
          }
        }
      }
    }
  }

  map<std::string, std::string> rltstr;
  for (const auto &s : results){
    rltstr[s.first] = joinString(s.second, " + ").Data();
    cout << s.first << endl << rltstr[s.first] << endl << endl;
  }
  return rltstr;
}

map<std::string, std::string> makeNumBinMap(){
  map<std::string, vector<TString>> results; // srbinname_met -> [(sr_sub1, cr_sub1), ...]

  const auto &merged_srCatMap = mergedSRCatMap();

  int binNum = 0;
  for (const auto &merged_cat_name : mergedSRbins){
    const auto& merged_bin = merged_srCatMap.at(merged_cat_name);
      
    for (unsigned ibin=0; ibin<merged_bin.bin.nbins; ++ibin){
      std::string mergedsr_binname = ("bin_"+merged_cat_name+"_"+merged_bin.bin.binnames.at(ibin)).Data();
      std::string mergedsr_binnum = to_string(binNum);
      results[mergedsr_binname]; // touch it: initialize it if not, otherwise should append (5-6j, and >=7j)
      results[mergedsr_binname].push_back(mergedsr_binnum); 
      cout << "SB binname: " << mergedsr_binname << ": " << mergedsr_binnum << endl;
      binNum++;
    }
  }

  map<std::string, std::string> rltstr;
  for (const auto &s : results){
    rltstr[s.first] = joinString(s.second, " + ").Data();
    //cout << s.first << endl << rltstr[s.first] << endl << endl;
  }
  return rltstr;
}

map<std::string, std::string> makeNumUnitCRMap(TString control_region){
  map<std::string, vector<TString>> results; // srbinname_met -> [(sr_sub1, cr_sub1), ...]

  const auto &crMapping = control_region=="phocr" ? phocrMapping : (control_region=="lepcr" ? lepcrMapping : qcdcrMapping);
  const auto &split_srCatMap = srCatMap();

  int UnitNum = 0;
  for (const auto &split_cat_name : srbins){
    const auto& split_bin = split_srCatMap.at(split_cat_name);
      
    for (unsigned ibin=0; ibin<split_bin.bin.nbins; ++ibin){
      std::string splitsr_binnum = to_string(UnitNum);
      std::string crbinname = ("bin_"+control_region+"_"+TString(crMapping.at(split_cat_name)).ReplaceAll("NoDPhi_","_")+"_"+split_bin.bin.binnames.at(ibin)).Data();
      if(!results.count(crbinname)){
        results[crbinname]; // touch it: initialize it if not, otherwise should append (5-6j, and >=7j)
        results[crbinname].push_back(splitsr_binnum); 
	cout << "unit crbinname: " << crbinname << ": " << splitsr_binnum << endl;
        UnitNum++;
      }
    }
  }

  map<std::string, std::string> rltstr;
  for (const auto &s : results){
    rltstr[s.first] = joinString(s.second, " + ").Data();
    //cout << s.first << endl << rltstr[s.first] << endl << endl;
  }
  return rltstr;
}

map<std::string, std::string> makeNumUnitMap(){
  map<std::string, vector<TString>> results; // srbinname_met -> [(sr_sub1, cr_sub1), ...]

  const auto &split_srCatMap = srCatMap();

  int UnitNum = 0;
  for (const auto &split_cat_name : srbins){
    const auto& split_bin = split_srCatMap.at(split_cat_name);
      
    for (unsigned ibin=0; ibin<split_bin.bin.nbins; ++ibin){
      std::string splitsr_binname = ("bin_"+split_cat_name+"_"+split_bin.bin.binnames.at(ibin)).Data();
      std::string splitsr_binnum = to_string(UnitNum);
      results[splitsr_binname]; // touch it: initialize it if not, otherwise should append (5-6j, and >=7j)
      results[splitsr_binname].push_back(splitsr_binnum); 
      cout << "unit srbinname: " << splitsr_binname << ": " << splitsr_binnum << endl;
      UnitNum++;
    }
  }

  map<std::string, std::string> rltstr;
  for (const auto &s : results){
    rltstr[s.first] = joinString(s.second, " + ").Data();
    //cout << s.first << endl << rltstr[s.first] << endl << endl;
  }
  return rltstr;
}

map<std::string, std::string> lepcrBinMap = makeBinMap("lepcr");
map<std::string, std::string> lepcrBinNumMap = makeNumBinMap();
map<std::string, std::string> lepcrUnitNumMap = makeNumUnitMap();
map<std::string, std::string> lepcrUnitCRNumMap = makeNumUnitCRMap("lepcr");
map<std::string, std::string> phocrBinMap = makeBinMap("phocr");
map<std::string, std::string> qcdcrBinMap = makeBinMap("qcdcr");
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
