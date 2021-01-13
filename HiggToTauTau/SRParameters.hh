#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"
#include "binDefinitions.hh"

namespace EstTools{

const TString inputdir = "root://cmseos.fnal.gov//eos/uscms/store/user/mkilpatr/13TeV/";
//const TString inputdir_local = "/uscms/home/mkilpatr/nobackup/CMSSW_10_2_22/src/PhysicsTools/NanoSUSYTools/python/processors";
const TString inputdir_2018 = "nanoaod_2018_skim_diHiggs_011121/";
//const TString inputdir_2018 = "";

const TString outputdir = ".";

const TString datadir = "nanoaod_2018_skim_diHiggs_111620/";

TString lumistr = "59.699489";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// lumi and base weight
const TString basic_wgt = "*Stop0l_evtWeight";
const TString wgtvar = lumistr+"*1000*"+basic_wgt;// //2016

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

// triggers
const TString dibosonBadEventRemoval = " && event != 237972";
const TString trigSR = " && Pass_trigger_MET";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && Pass_EventFilter && Pass_HT && Pass_JetID";
const TString qcdSpikeRemovals = "";
const TString dphi_invert = " && Pass_dPhiQCD";
const TString dphi_cut = " && ( ((Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETLowDM) || (!(Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETHighDM) )"; // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "Pass_NJets30 && SVFitMET_isValid";

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

  //config.inputdir = inputdir;
  config.inputdir = inputdir;
  config.outputdir = outputdir+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("GluGluToHHTo2B2Tau",     "gg#rightarrowHH#rightarrowbb#tau#tau",      inputdir_2018+"GluGluToHHTo2B2Tau", wgtvar,  datasel);
  config.addSample("GluGluHToTauTau",        "gg#rightarrowH#rightarrow#tau#tau",      inputdir_2018+"GluGluHToTauTau", wgtvar,  datasel);
  config.addSample("VBFHToTauTau",           "VBF#rightarrowH#rightarrow#tau#tau",     inputdir_2018+"VBFHToTauTau",    wgtvar,  datasel);
  //config.addSample("vv",                "VV",                                     inputdir_2018+"vv",         wgtvar,  datasel);
  //config.addSample("ww",                "WW",                                     inputdir_2018+"ww",         wgtvar,  datasel);
  //config.addSample("wz",                "WZ",                                     inputdir_2018+"wz",         wgtvar,  datasel);
  config.addSample("diboson",                "VV",                                     inputdir_2018+"diboson",         wgtvar,  datasel);
  config.addSample("wjets",                  "W+jets",                                 inputdir_2018+"wjets",         wgtvar,  datasel);
  config.addSample("dyll",                   "DY+jets",                                 inputdir_2018+"dyll",         wgtvar,  datasel);

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
  {"norm",      BinInfo("MET_pt", "p^{miss}_{T}", vector<int>{0, 1000}, "GeV")},
  {"met",       BinInfo("MET_pt", "p^{miss}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
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
