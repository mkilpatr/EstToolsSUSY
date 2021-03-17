#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"
#include "binDefinitions.hh"

namespace EstTools{

const TString inputdir = "root://cmseos.fnal.gov//eos/uscms/store/user/mkilpatr/13TeV/";
const TString inputdir_local = "/uscms/home/mkilpatr/nobackup/CMSSW_10_2_22/src/PhysicsTools/NanoSUSYTools/python/processors";
const TString inputdir_2018 = "nanoaod_2018_skim_diHiggs_030821_higgsSort/";
//const TString inputdir_2018 = "";

const TString outputdir = ".";

const TString datadir = "nanoaod_2018_skim_diHiggs_allVars_011921/";

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
const TString Lead_lepmuonChannel   = "(SVFit_channel[SVIndex[0]] == 0 && SVFit_PassTight[SVIndex[0]] && SVFit_tau1_muMT[SVIndex[0]] < 50)";
const TString Lead_elechadChannel   = "(SVFit_channel[SVIndex[0]] == 1 && SVFit_PassTight[SVIndex[0]] && SVFit_tau1_elecMT[SVIndex[0]] < 50)";
const TString Lead_hadhadChannel    = "(SVFit_channel[SVIndex[0]] == 2 && SVFit_PassTight[SVIndex[0]] && SVFit_ditauDR[SVIndex[0]] > 0.5 && SVFit_ditauPt[SVIndex[0]] > 50)";
const TString Lead_emuChannel       = "(SVFit_channel[SVIndex[0]] == 5 && SVFit_DZeta[SVIndex[0]] > -35 && SVFit_elecMuonMT[SVIndex[0]] < 60)";
const TString SubLead_lepmuonChannel= "(SVFit_channel[SVIndex[1]] == 0 && SVFit_PassTight[SVIndex[1]] && SVFit_tau1_muMT[SVIndex[1]] < 50)";
const TString SubLead_elechadChannel= "(SVFit_channel[SVIndex[1]] == 1 && SVFit_PassTight[SVIndex[1]] && SVFit_tau1_elecMT[SVIndex[1]] < 50)";
const TString SubLead_hadhadChannel = "(SVFit_channel[SVIndex[1]] == 2 && SVFit_PassTight[SVIndex[1]] && SVFit_ditauDR[SVIndex[1]] > 0.5 && SVFit_ditauPt[SVIndex[1]] > 50)";
const TString SubLead_emuChannel    = "(SVFit_channel[SVIndex[1]] == 5 && SVFit_DZeta[SVIndex[1]] > -35 && SVFit_elecMuonMT[SVIndex[1]] < 60)";

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
        {"lmNoDPhi",    "Stop0l_ISRJetPt>=200 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>=10"},
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
        {"ht1000to1300","Stop0l_HT>=1000 && Stop0l_HT<1300"},
        {"ht1300to1500","Stop0l_HT>=1300 && Stop0l_HT<1500"},
	{"htgt1500",    "Stop0l_HT>=1500"},	
	{"htlt1300",    "Stop0l_HT<1300"},	
	{"htgt1300",    "Stop0l_HT>=1300"},	
        {"noextrap",    "1 == 1"},
    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();


std::map<TString, TString> labelMap{
  {"lowptisr", R"($300\leq\ptisr<500$\,GeV)"},
  {"ntgeq1", R"($\nt\geq1$)"},
  {"nt2", R"($\nt=2$)"},
  {"nivf0", R"($\nsv=0$)"},
  {"nivf1", R"($\nsv\geq1$)"},
  {"nw2", R"($\nw=2$)"},
  {"nj2to5", R"($2\leq\nj\leq5$)"},
  {"nb2", R"($\nb\geq2$)"},
  {"nbeq2", R"($\nb=2$)"},
  {"nb3", R"($\nb\geq3$)"},
  {"nb1", R"($\nb=1$)"},
  {"nbgeq1", R"($\nb\geq1$)"},
  {"nb0", R"($\nb=0$)"},
  {"nrt2", R"($\nrt=2$)"},
  {"medptisr", R"($\ptisr\geq300$\,GeV)"},
  {"highptisr", R"($\ptisr\geq500$\,GeV)"},
  {"nj7", R"($\nj\geq7$)"},
  {"highptb", R"($\ptb\geq70$\,GeV)"},
  {"hm", R"(High \dm)"},
  {"nw0", R"($\nw=0$)"},
  {"nwgeq1", R"($\nw\geq1$)"},
  {"nw1", R"($\nw=1$)"},
  {"nrt0", R"($\nrt=0$)"},
  {"nrt1", R"($\nrt=1$)"},
  {"lowptb", R"($\ptb<40$\,GeV)"},
  {"medptb", R"($40<\ptb<70$\,GeV)"},
  {"nt0", R"($\nt=0$)"},
  {"lm", R"(Low \dm)"},
  {"lowptb12", R"($\ptbonetwo<80$\,GeV)"},
  {"highptb12", R"($\ptbonetwo\geq140$\,GeV)"},
  {"lowmtb", R"($\mtb<175$~\GeV)"},
  {"highmtb", R"($\mtb\geq175$~\GeV)"},
  {"nt1", R"($\nt=1$)"},
  {"medptb12", R"($80<\ptbonetwo<140$\,GeV)"},
  {"nrtgeq1", R"($\nrt\geq1$)"},
  {"nj6", R"($\nj\geq6$)"},
  {"nrtntnwgeq2", R"($(\nt+\nrt+\nw)\geq2$)"},
  {"nrtntnwgeq3", R"($(\nt+\nrt+\nw)\geq3$)"},
  {"htlt1000",    R"($\Ht<1000$)"},	
  {"htgt1000",    R"($\Ht\geq1000$)"},	
  {"ht1000to1500",R"($1000\leq\Ht<1500$)"},	
  {"ht1000to1300",R"($1000\leq\Ht<1300$)"},	
  {"ht1300to1500",R"($1300\leq\Ht<1500$)"},	
  {"htgt1500",    R"($\Ht\geq1500$)"},	
  {"htlt1300",    R"($\Ht<1300$)"},	
  {"htgt1300",    R"($\Ht\geq1300$)"},	
  {"lmNoDPhi",    R"(Low $\Delta m$)"},
  {"hmNoDPhi",    R"(High $\Delta m$)"},
  {"noextrap",    R"()"},
  
};

std::map<TString, TString> plotLabelMap{
  {"lowptisr", R"(300 #leq p_{T}(ISR) < 500)"},
  {"ntgeq1", R"(N_{t} #geq 1)"},
  {"nt2", R"(N_{t} = 2)"},
  {"nivf0", R"(N_{SV} = 0)"},
  {"nivf1", R"(N_{SV} #geq 1)"},
  {"nw2", R"(N_{W} = 2)"},
  {"nj2to5", R"(2 #leq N_{j} #leq 5)"},
  {"nb2", R"(N_{b} #geq 2)"},
  {"nbeq2", R"(N_{b} = 2)"},
  {"nb3", R"(N_{b} #geq 3)"},
  {"nb1", R"(N_{b} = 1)"},
  {"nbgeq1", R"(N_{b} #geq 1)"},
  {"nb0", R"(N_{b} = 0)"},
  {"nrt2", R"(N_{res} = 2)"},
  {"medptisr", R"(p_{T}(ISR) #geq 300)"},
  {"highptisr", R"(p_{T}(ISR) #geq 500)"},
  {"nj7", R"(N_{j} #geq 7)"},
  {"highptb", R"(p_{T}(b) #geq 70)"},
  {"hm", R"(High #Deltam)"},
  {"nw0", R"(N_{W} = 0)"},
  {"nwgeq1", R"(N_{W} #geq 1)"},
  {"nw1", R"(N_{W} = 1)"},
  {"nrt0", R"(N_{res} = 0)"},
  {"nrt1", R"(N_{res} = 1)"},
  {"lowptb", R"(p_{T}(b) < 40)"},
  {"medptb", R"(40 < p_{T}(b) < 70)"},
  {"nt0", R"(N_{t} = 0)"},
  {"lm", R"(Low #Deltam)"},
  {"lowptb12", R"(p_{T}(b_{12}) < 80)"},
  {"highptb12", R"(p_{T}(b_{12}) #geq 140)"},
  {"lowmtb", R"(M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175)"},
  {"highmtb", R"(M_{T}(b_{1,2},#vec{p}_{T}^{miss}) #geq 175)"},
  {"nt1", R"(N_{t} = 1)"},
  {"medptb12", R"(80 < p_{T}(b_{12}) < 140)"},
  {"nrtgeq1", R"(N_{res} #geq 1)"},
  {"nj6", R"(N_{j} #geq 6)"},
  {"nrtntnwgeq2", R"((N_{t}+N_{res}+N_{W}) #geq 2)"},
  {"nrtntnwgeq3", R"((N_{t}+N_{res}+N_{W}) #geq 3)"},
  {"htlt1000",    R"(H_{T}<1000)"},	
  {"htgt1000",    R"(H_{T} #geq 1000)"},	
  {"ht1000to1500",R"(1000#leqH_{T}<1500)"},	
  {"ht1000to1300",R"(1000#leqH_{T}<1300)"},	
  {"ht1300to1500",R"(1300#leqH_{T}<1500)"},	
  {"htgt1500",    R"(H_{T}#geq1500)"},	
  {"htlt1300",    R"(H_{T}<1300)"},	
  {"htgt1300",    R"(H_{T}#geq1300)"},	
  {"lmNoDPhi",    R"(Low #Delta m)"},
  {"hmNoDPhi",    R"(High #Delta m)"},
  {"noextrap",    R"()"},
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

BaseConfig lepConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/Tau";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  // samples for cr categories
  if (ADD_LEP_TO_MET){
    config.addSample("ttbar",       "t#bar{t}",      inputdir_2018+"ttbar",           onelepcrwgt+"*ISRWeight", datasel + trigLepCR + lepcrsel);
    config.addSample("wjets",       "W+jets",        inputdir_2018+"wjets",           onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("tW",          "tW",            inputdir_2018+"tW",              onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("ttW",         "t#bar{t}W",           inputdir_2018+"ttW",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
  }else{
    config.addSample("ttbar",       "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt+"*ISRWeight",      datasel + revert_vetoes);
    config.addSample("wjets",       "W+jets",        inputdir_2018+"wjets",           lepselwgt,      datasel + revert_vetoes);
    config.addSample("tW",          "Single t",      inputdir_2018+"tW",              lepselwgt,      datasel + revert_vetoes);
    config.addSample("ttW",         "t#bar{t}W",     inputdir_2018+"ttW",             lepselwgt,      datasel + revert_vetoes);
    config.addSample("ttZ",         "ttZ",           inputdir_2018+"ttZ",             lepselwgt+"*"+ttznorm, datasel + revert_vetoes + invert_genLep);
    config.addSample("diboson",     "Rare",            inputdir_2018+"diboson",         lepselwgt, datasel + revert_vetoes + invert_genLep + dibosonBadEventRemoval);
  }

  // samples for sr categories
  config.addSample("diboson-sr",     "diboson",      inputdir_2018+"diboson",              lepvetowgt, datasel + vetoes + invert_genLep);

  std::vector<TString> srbins_small;
  for (auto name : srbins){
    if(name != binMap() && binMap() != "allBins") continue;
    srbins_small.push_back(name);
  }
  
  config.sel = baseline;
  config.categories = (binMap() == "allBins") ? srbins : srbins_small;
  config.catMaps = srCatMap();
  config.crCatMaps = lepCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig sigConfig(){
  BaseConfig     config;

  config.inputdir = inputdir_local;
  //config.inputdir = inputdir;
  config.outputdir = outputdir+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("local",             "Local",          "nano_Skim", wgtvar,  datasel);
  //config.addSample("ggHHto2b2tau",     	"gg#rightarrowHH#rightarrowbb#tau#tau",      inputdir_2018+"ggHHto2b2tau", wgtvar,  datasel);
  //config.addSample("ggHto2tau",        "gg#rightarrowH#rightarrow#tau#tau",      inputdir_2018+"ggHto2tau", wgtvar,  datasel);
  //config.addSample("vbfHto2tau",           "VBF#rightarrowH#rightarrow#tau#tau",     inputdir_2018+"vbfHto2tau",    wgtvar,  datasel);
  ////config.addSample("vv",                "VV",                                     inputdir_2018+"vv",         wgtvar,  datasel);
  ////config.addSample("ww",                "WW",                                     inputdir_2018+"ww",         wgtvar,  datasel);
  ////config.addSample("wz",                "WZ",                                     inputdir_2018+"wz",         wgtvar,  datasel);
  //config.addSample("diboson",                "VV",                                     inputdir_2018+"diboson",         wgtvar,  datasel);
  //config.addSample("wjets",                  "W+jets",                                 inputdir_2018+"wjets",         wgtvar,  datasel);
  //config.addSample("dyll",                   "DY+jets",                                 inputdir_2018+"dyll",         wgtvar,  datasel);

  //config.addSample("T1tttt-v2p7-sr",  "T1tttt v2p7",  inputdir_sig+"T1tttt_2200_100_v2p7",  "1.0", datasel + vetoes);
  //config.addSample("T1tttt-v3-sr",  "T1tttt v3",  inputdir_sig+"T1tttt_2200_100_v3",  "1.0", datasel + vetoes);
//  config.addSample("T2fbd_375_325",  "T2-4bd(375,325)",  "sig/T2fbd_375_325",  sigwgt, datasel + vetoes);
//  config.addSample("T2fbd_375_295",  "T2-4bd(375,295)",  "sig/T2fbd_375_295",  sigwgt, datasel + vetoes);
//
  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

map<TString, BinInfo> varDict {
	{"Lead_tauChannel",	BinInfo("SVFit_channel[SVIndex[0]]",   "Tau channel", 6, -0.5, 5.5)},
	{"Lead_higgsPt",	BinInfo("SVFit_Pt[SVIndex[0]]",  	"p_{T}(H) [GeV]", 12, 100, 1000)},
	{"Lead_higgsEta",	BinInfo("SVFit_Eta[SVIndex[0]]", 	"#eta(H)", 16, -4, 4)},
	{"Lead_higgsPhi",	BinInfo("SVFit_Phi[SVIndex[0]]", 	"#phi(H)", 64, -3.2, 3.2)},
	{"Lead_higgsMass",	BinInfo("SVFit_Mass[SVIndex[0]]",	"M_{H}", 25, 0, 500)},
	{"Lead_higgsTransverseMass",	BinInfo("SVFit_TransverseMass[SVIndex[0]]",	"M_{T}^{H}", 25, 0, 500)},
	{"Lead_tau1Pt",	BinInfo("SVFit_tau1Pt[SVIndex[0]]",  	"p_{T}(#tau_{1}) [GeV]", 20, 0, 200)},
	{"Lead_tau1Eta",	BinInfo("SVFit_tau1Eta[SVIndex[0]]", 	"#eta(#tau_{1})", 16, -4, 4)},
	{"Lead_tau1Phi",	BinInfo("SVFit_tau1Phi[SVIndex[0]]", 	"#phi(#tau_{1})", 64, -3.2, 3.2)},
	{"Lead_tau1Mass",	BinInfo("SVFit_tau1Mass[SVIndex[0]]",	"M_{#tau_{1}}", 20, 0, 4)},
	{"Lead_tau1pdgid",	BinInfo("SVFit_tau1pdgId[SVIndex[0]]",	"pdgId #tau_{1}", 6, -0.5, 5.5)},
	{"Lead_tau1DM",	BinInfo("SVFit_tau1DM[SVIndex[0]]",	"Decay Mode #tau_{1}", 16, -0.5, 15.5)},
	{"Lead_tau2Pt",	BinInfo("SVFit_tau2Pt[SVIndex[0]]",  	"p_{T}(#tau_{2}) [GeV]", 20, 0, 200)},
	{"Lead_tau2Eta",	BinInfo("SVFit_tau2Eta[SVIndex[0]]", 	"#eta(#tau_{2})", 16, -4, 4)},
	{"Lead_tau2Phi",	BinInfo("SVFit_tau2Phi[SVIndex[0]]", 	"#phi(#tau_{2})", 64, -3.2, 3.2)},
	{"Lead_tau2Mass",	BinInfo("SVFit_tau2Mass[SVIndex[0]]",	"M_{#tau_{2}}", 20, 0, 4)},
	{"Lead_tau2pdgid",	BinInfo("SVFit_tau2pdgId[SVIndex[0]]",	"pdgId #tau_{2}", 6, -0.5, 5.5)},
	{"Lead_tau2DM",	BinInfo("SVFit_tau2DM[SVIndex[0]]",	"Decay Mode #tau_{2}", 16, -0.5, 15.5)},
	{"Lead_ht",		BinInfo("SVFit_HT",        "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000, 1500}, "GeV")},
	{"Lead_elecMuonMT",	BinInfo("SVFit_elecMuonMT[SVIndex[0]]","M_{T}^{e+#mu}", 20, 0, 200)},
	{"Lead_elecMT_tau1",	BinInfo("SVFit_tau1_elecMT[SVIndex[0]]","M_{T}^{e}", 20, 0, 200)},
	{"Lead_muonMT_tau1",	BinInfo("SVFit_tau1_muMT[SVIndex[0]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"Lead_tauMT_tau1",	BinInfo("SVFit_tau1_hadMT[SVIndex[0]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"Lead_muonMT_tau2",	BinInfo("SVFit_tau2_muMT[SVIndex[0]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"Lead_tauMT_tau2",	BinInfo("SVFit_tau2_hadMT[SVIndex[0]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"Lead_ditauMass",	BinInfo("SVFit_ditauMass[SVIndex[0]]",  "M_{#tau#tau}", 50, 0, 500)},
	{"Lead_ditauPt",	BinInfo("SVFit_ditauPt[SVIndex[0]]",    "p_{T}^{#tau#tau+miss} [GeV]", 25, 0, 600)},
	{"Lead_ditau_dR",	BinInfo("SVFit_ditauDR[SVIndex[0]]",    "#DeltaR(#tau_{1}, #tau_{2})", 30, 0, 6)},
	{"Lead_elecMuon_dR",	BinInfo("SVFit_deltaREMu[SVIndex[0]]",  "#DeltaR(e, #mu)", 30, 0, 6)},
	{"Lead_ditaudijetMass",BinInfo("SVFit_2tau2jetPt[SVIndex[0]]", 	"p_{T}^{#tau#taujj+miss}", 40, 0, 1000)},
	{"Lead_maxdR_bjettau",BinInfo("SVFit_MaxbjetTauDR[SVIndex[0]]",    "max(#DeltaR(b, #tau)", 30, 0, 6)},
	{"Lead_mindR_bjettau",BinInfo("SVFit_MinbjetTauDR[SVIndex[0]]",    "min(#DeltaR(b, #tau)", 30, 0, 6)},
	{"Lead_DZeta",	BinInfo("SVFit_DZeta[SVIndex[0]]",  "D_{#zeta}", 24, -40, 200)},
	{"SubLead_tauChannel",	BinInfo("SVFit_channel[SVIndex[1]]",   "Tau channel", 5, 0, 5)},
	{"SubLead_higgsPt",	BinInfo("SVFit_Pt[SVIndex[1]]",  	"p_{T}(H) [GeV]", 12, 100, 1000)},
	{"SubLead_higgsEta",	BinInfo("SVFit_Eta[SVIndex[1]]", 	"#eta(H)", 16, -4, 4)},
	{"SubLead_higgsPhi",	BinInfo("SVFit_Phi[SVIndex[1]]", 	"#phi(H)", 64, -3.2, 3.2)},
	{"SubLead_higgsMass",	BinInfo("SVFit_Mass[SVIndex[1]]",	"M_{H}", 25, 0, 500)},
	{"SubLead_higgsTransverseMass",	BinInfo("SVFit_TransverseMass[SVIndex[1]]",	"M_{T}^{H}", 25, 0, 500)},
	{"SubLead_tau1Pt",	BinInfo("SVFit_tau1Pt[SVIndex[1]]",  	"p_{T}(#tau_{1}) [GeV]", 20, 0, 200)},
	{"SubLead_tau1Eta",	BinInfo("SVFit_tau1Eta[SVIndex[1]]", 	"#eta(#tau_{1})", 16, -4, 4)},
	{"SubLead_tau1Phi",	BinInfo("SVFit_tau1Phi[SVIndex[1]]", 	"#phi(#tau_{1})", 64, -3.2, 3.2)},
	{"SubLead_tau1Mass",	BinInfo("SVFit_tau1Mass[SVIndex[1]]",	"M_{#tau_{1}}", 20, 0, 4)},
	{"SubLead_tau1pdgid",	BinInfo("SVFit_tau1pdgId[SVIndex[1]]",	"pdgId #tau_{1}", 6, -0.5, 5.5)},
	{"SubLead_tau1DM",	BinInfo("SVFit_tau1DM[SVIndex[1]]",	"Decay Mode #tau_{1}", 16, -0.5, 15.5)},
	{"SubLead_tau2Pt",	BinInfo("SVFit_tau2Pt[SVIndex[1]]",  	"p_{T}(#tau_{2}) [GeV]", 20, 0, 200)},
	{"SubLead_tau2Eta",	BinInfo("SVFit_tau2Eta[SVIndex[1]]", 	"#eta(#tau_{2})", 16, -4, 4)},
	{"SubLead_tau2Phi",	BinInfo("SVFit_tau2Phi[SVIndex[1]]", 	"#phi(#tau_{2})", 64, -3.2, 3.2)},
	{"SubLead_tau2Mass",	BinInfo("SVFit_tau2Mass[SVIndex[1]]",	"M_{#tau_{2}}", 20, 0, 4)},
	{"SubLead_tau2pdgid",	BinInfo("SVFit_tau2pdgId[SVIndex[1]]",	"pdgId #tau_{2}", 6, -0.5, 5.5)},
	{"SubLead_tau2DM",	BinInfo("SVFit_tau2DM[SVIndex[1]]",	"Decay Mode #tau_{2}", 16, -0.5, 15.5)},
	{"SubLead_ht",		BinInfo("SVFit_HT",        "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000, 1500}, "GeV")},
	{"SubLead_elecMuonMT",	BinInfo("SVFit_elecMuonMT[SVIndex[1]]","M_{T}^{e+#mu}", 20, 0, 200)},
	{"SubLead_elecMT_tau1",	BinInfo("SVFit_tau1_elecMT[SVIndex[1]]","M_{T}^{e}", 20, 0, 200)},
	{"SubLead_muonMT_tau1",	BinInfo("SVFit_tau1_muMT[SVIndex[1]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"SubLead_tauMT_tau1",	BinInfo("SVFit_tau1_hadMT[SVIndex[1]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"SubLead_muonMT_tau2",	BinInfo("SVFit_tau2_muMT[SVIndex[1]]",  "M_{T}^{#mu}", 20, 0, 200)},
	{"SubLead_tauMT_tau2",	BinInfo("SVFit_tau2_hadMT[SVIndex[1]]", "M_{T}^{#tau_{h}}", 20, 0, 200)},
	{"SubLead_ditauMass",	BinInfo("SVFit_ditauMass[SVIndex[1]]",  "M_{#tau#tau}", 50, 0, 500)},
	{"SubLead_ditauPt",	BinInfo("SVFit_ditauPt[SVIndex[1]]",    "p_{T}^{#tau#tau+miss} [GeV]", 25, 0, 600)},
	{"SubLead_ditau_dR",	BinInfo("SVFit_ditauDR[SVIndex[1]]",    "#DeltaR(#tau_{1}, #tau_{2})", 30, 0, 6)},
	{"SubLead_elecMuon_dR",	BinInfo("SVFit_deltaREMu[SVIndex[1]]",  "#DeltaR(e, #mu)", 30, 0, 6)},
	{"SubLead_ditaudijetMass",BinInfo("SVFit_2tau2jetPt[SVIndex[1]]", 	"p_{T}^{#tau#taujj+miss}", 40, 0, 1000)},
	{"SubLead_maxdR_bjettau",BinInfo("SVFit_MaxbjetTauDR[SVIndex[1]]",    "max(#DeltaR(b, #tau)", 30, 0, 6)},
	{"SubLead_mindR_bjettau",BinInfo("SVFit_MinbjetTauDR[SVIndex[1]]",    "min(#DeltaR(b, #tau)", 30, 0, 6)},
	{"SubLead_DZeta",	BinInfo("SVFit_DZeta[SVIndex[1]]",  "D_{#zeta}", 24, -40, 200)},
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
