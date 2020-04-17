#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../../utils/EstHelper.hh"
#include "../binDefinitions_dc.hh"

namespace EstTools{

const TString inputdir = "root://cmseos.fnal.gov//eos/uscms/store/user/mkilpatr/13TeV/";
const TString inputdir_2016 = "nanoaod_all_skim_2016_041620_devv6_limits/";
const TString inputdir_sig  = "nanoaod_T2tt_corridor_2017_100119/";

const TString outputdir = ".";

const TString datadir = "nanoaod_data_all_skim_041620_devv6_limits/";

const TString lumistr = "35.815165";
const TString lumistr_2016 = "35.815165"; //Units are in pb

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

const TString HEMVeto     = "(" + lumistr_2018PostHEM + "*(Pass_exHEMVeto30) + " + lumistr_2018PreHEM + "*(!Pass_exHEMVeto30))";
const TString HEMVetoElec = "(" + lumistr_2018PostHEM + "*(Pass_exHEMVeto30 && Pass_exHEMVetoElec30) + " + lumistr_2018PreHEM + "*(!(Pass_exHEMVeto30 && Pass_exHEMVetoElec30)))";

// lumi and base weight
const TString basic_wgt = "*Stop0l_evtWeight*puWeight*BTagWeight*Stop0l_DeepAK8_SFWeight*SoftBSF*Stop0l_ResTopWeight*Stop0l_topptWeight";
const TString wgtvar = lumistr_2016+"*1000*PrefireWeight"+basic_wgt;// //2016

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
const TString lepvetowgt_no_wtopsf = lumistr_2016+"*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*BTagWeight*ISRWeight*PrefireWeight";

// 1Lep LLB method
bool ADD_LEP_TO_MET = false;
bool ICHEPCR = false;

bool SPLITTF = false; // split TF to CR-SR and SR-extrapolation
const TString revert_vetoes = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && (run < 319077 || (run >= 319077 && Pass_exHEMVetoElec30))";

// MET+LEP LL method
//bool ADD_LEP_TO_MET = true;
const TString lepcrsel = " && Stop0l_nVetoElecMuon == 1 && Stop0l_MtLepMET < 100 && MET_pt>100";


// lepton trigger eff.
//const TString trigLepCR = " && (passtrige || passtrigmu)";
//const TString onelepcrwgt  = lepselwgt + "*trigEleWeight*trigMuWeight";

const TString trigLepCR = "";
const TString onelepcrwgt  = lepselwgt;

// qcd weights
const TString qcdwgt         = wgtvar + "*qcdRespTailWeight*Stop0l_trigger_eff_MET_loose_baseline_QCD";
const TString qcdvetowgt       = lepvetowgt + "*qcdRespTailWeight";

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(0.85*(Stop0l_nSoftb>=1) + 1.0*(Stop0l_nSoftb==0))";
const TString sigwgt = lumistr+"/"+lumistr_2016+"*"+lepvetowgt+"*ISRWeight";
const TString siglepselwgt = lumistr+"/"+lumistr_2016+"*"+lepselwgt+"*ISRWeight";

// triggers
const TString trigSR = " && Pass_trigger_MET";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && Pass_EventFilter && Pass_HT && Pass_JetID && Pass_CaloMETRatio && (run < 319077 || (run >= 319077 && Pass_exHEMVeto30)) && Pass_LHETTbar";
//const TString dataselHEM = " && Pass_EventFilter && Pass_HT && Pass_JetID && Pass_CaloMETRatio && (run >= 319077 || run == 1) && Pass_exHEMVeto30 && Pass_LHETTbar";
const TString qcdSpikeRemovals = "";
const TString dphi_invert = " && Pass_dPhiQCD";
const TString dphi_cut = " && ( ((Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETLowDM) || (!(Stop0l_Mtb<175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0) && Pass_dPhiMETHighDM) )"; // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "Pass_MET && Pass_NJets30";

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

std::map<TString, TString> phocrCuts = []{
    std::map<TString, TString> cuts;
    for (auto sr2cr : phocrMapping)
      cuts[sr2cr.first] = createCutString(sr2cr.second, cutMap);
    return cuts;
}();

std::map<TString, TString> phocrlabels = phocrMapping;

std::map<TString, std::vector<int>> phocrMETbins = srMETbins;

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

  //config.addSample("singlepho",   "Data",           datadir+"/photoncr/singlepho",  "1.0",  datasel + trigPhoCR);

  //config.addSample("photon",      "Photon",         "photoncr/photon",     phowgt, datasel + trigPhoCR + phoBadEventRemoval);
////  config.addSample("photon",      "Photon",         "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  //config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt, datasel + trigSR + vetoes);

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

  //config.addSample("dyll",      "Z#rightarrowll+jets",    "zllcr/z-soup",                    lepselwgt, datasel + trigDiLepCR);
  //config.addSample("ttbar",     "t#bar{t}",               "zllcr/t-soup",                    lepselwgt, datasel + trigDiLepCR);
  //config.addSample("doublelep", "Data",                   datadir+"/zllcr/doublelep",       "1.0",     datasel + trigDiLepCR);

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

  // samples for cr categories
  if (ADD_LEP_TO_MET){
    config.addSample("singlelep",        "Data",          inputdir_2016+"met", 		   "1.0",       datasel + trigLepCR + lepcrsel);
    config.addSample("ttbar",       "t#bar{t}",      inputdir_2016+"ttbar",           onelepcrwgt+"*ISRWeight", datasel + trigLepCR + lepcrsel);
    config.addSample("wjets",       "W+jets",        inputdir_2016+"wjets",           onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("tW",          "tW",            inputdir_2016+"tW",              onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("ttW",         "ttW",           inputdir_2016+"ttW",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "lepcr/qcd",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",        "Data",         inputdir_2016+"met",                   "1.0",          datasel + trigSR + revert_vetoes);
    config.addSample("ttbar",       "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",      datasel + revert_vetoes);
    config.addSample("wjets",       "W+jets",        inputdir_2016+"wjets",           lepselwgt,      datasel + revert_vetoes);
    config.addSample("tW",          "tW",            inputdir_2016+"tW",              lepselwgt,      datasel + revert_vetoes);
    config.addSample("ttW",         "ttW",           inputdir_2016+"ttW",             lepselwgt,      datasel + revert_vetoes);
    //config.addSample("ttZ",         "ttZ",           inputdir_2016+"ttZ",           lepselwgt,      datasel + revert_vetoes);
    //config.addSample("diboson",     "Diboson",       inputdir_2016+"diboson",       lepselwgt,      datasel + revert_vetoes);
    //config.addSample("qcd",         "QCD",           inputdir_2016+"qcd_smear",     lepselwgt,      datasel + revert_vetoes);
  }

  // samples for sr categories
  config.addSample("ttbar-sr",       "t#bar{t}",      inputdir_2016+"ttbar",                lepvetowgt+"*ISRWeight", datasel + vetoes);
  config.addSample("wjets-sr",       "W+jets",        inputdir_2016+"wjets",                lepvetowgt, datasel + vetoes);
  config.addSample("tW-sr",          "tW",            inputdir_2016+"tW",                   lepvetowgt, datasel + vetoes);
  config.addSample("ttW-sr",         "ttW",           inputdir_2016+"ttW",                  lepvetowgt, datasel + vetoes);
  config.addSample("ttZ-sr",         "ttZ",           inputdir_2016+"ttZ",                  lepvetowgt, datasel + vetoes);
  config.addSample("diboson-sr",     "Diboson",       inputdir_2016+"diboson",              lepvetowgt, datasel + vetoes);

  // samples for splitting the TF (optional, see l.splitTF)
  if (SPLITTF){
    config.addSample("ttbar-sr-int",       "t#bar{t}",      inputdir_2016+"ttbar",                lepvetowgt+"*ISRWeight", datasel + vetoes);
    config.addSample("wjets-sr-int",       "W+jets",        inputdir_2016+"wjets",                lepvetowgt, datasel + vetoes);
    config.addSample("tW-sr-int",          "tW",            inputdir_2016+"tW",                   lepvetowgt, datasel + vetoes);
    config.addSample("ttW-sr-int",         "ttW",           inputdir_2016+"ttW",                  lepvetowgt, datasel + vetoes);
    config.addSample("ttZ-sr-int",         "ttZ",           inputdir_2016+"ttZ",                  lepvetowgt, datasel + vetoes);
    config.addSample("diboson-sr-int",     "Diboson",       inputdir_2016+"diboson",              lepvetowgt, datasel + vetoes);
  }

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
  config.addSample("data-cr",     "Data",             inputdir_2016+"met",  "1.0",      datasel + trigSR + vetoes + dphi_invert);
  
  config.addSample("qcd-cr",      "QCD",              inputdir_2016+"qcd_smear",       qcdwgt,      datasel + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-withveto-cr",  "QCD",         inputdir_2016+"qcd_smear",       qcdvetowgt,  datasel + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-withveto-sr",  "QCD",         inputdir_2016+"qcd_smear",       qcdvetowgt,  datasel + vetoes + qcdSpikeRemovals);
  // qcdcr: other bkg subtraction
  config.addSample("ttbar-cr",       "t#bar{t}",      inputdir_2016+"ttbar",        lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("wjets-cr",       "W+jets",        inputdir_2016+"wjets",        lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("tW-cr",          "tW",            inputdir_2016+"tW",           lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("ttW-cr",         "ttW",           inputdir_2016+"ttW",          lepvetowgt,  datasel + vetoes + dphi_invert);
  config.addSample("znunu-cr",       "Znunu",         inputdir_2016+"znunu",        lepvetowgt,  datasel + vetoes + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",           "Data",          inputdir_2016+"met", "1.0",      datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("ttbar-norm",     "t#bar{t}",      inputdir_2016+"ttbar",     lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("wjets-norm",     "W+jets",        inputdir_2016+"wjets",     lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("tW-norm",        "tW",            inputdir_2016+"tW",        lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("ttW-norm",       "ttW",           inputdir_2016+"ttW",       lepselwgt,   datasel + revert_vetoes + dphi_cut);
  config.addSample("qcd-norm",       "QCD",           inputdir_2016+"qcd_smear",       lepselwgt,   datasel + revert_vetoes + dphi_cut + qcdSpikeRemovals);

  // qcdsr
  config.addSample("qcd-sr",         "QCD",           inputdir_2016+"qcd_smear",       qcdwgt,           datasel + qcdSpikeRemovals);

  // samples for splitting the TF, optional (see z.splitTF)
  if (SPLITTF){
    config.addSample("qcd-sr-int",         "QCD",           inputdir_2016+"qcd_smear",       qcdwgt,           datasel + dphi_cut + qcdSpikeRemovals);
  }

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();    // sr DPhi cut applied
  config.crCatMaps = qcdCatMap(); // no DPhi cut in category def
  config.crMapping = qcdcrMapping;

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

  config.addSample("data",        	     "Data",          inputdir_2016+"met",    		 "1.0",      datasel + trigSR + vetoes);
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
      //cout << "SB binname: " << mergedsr_binname << ": " << mergedsr_binnum << endl;
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
  const auto &split_srCatMap = control_region == "qcdcr" ? qcdCatMap() : srCatMap();

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
      //cout << "unit srbinname: " << splitsr_binname << ": " << splitsr_binnum << endl;
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
map<std::string, std::string> phocrUnitCRNumMap = makeNumUnitCRMap("phocr");
map<std::string, std::string> qcdcrUnitCRNumMap = makeNumUnitCRMap("qcdcr");
map<std::string, std::string> phocrBinMap = makeBinMap("phocr");
map<std::string, std::string> qcdcrBinMap = makeBinMap("qcdcr");
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
