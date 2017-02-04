#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"

namespace EstTools{

TString sys_name = "nominal";
TString inputdir = "/tmp/hqu/syst_trees";
TString outputdir() {return "/tmp/hqu/syst/"+sys_name;}

const TString datadir = ".";
const TString lumistr = "36.8";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

TString sdmvawgt = "sdMVAWeight";
TString restopwgt = "resTopWeight";

// lumi and base weight
TString wgtvar(){
  return lumistr+"*weight*truePUWeight*btagWeight*topptWeight*"+sdmvawgt+"*"+restopwgt;
}
//TString wgtvar = lumistr+"*weight*topptWeight*truePUWeight*btagWeight";

// photon trigger eff.
TString phowgt() { return wgtvar(); }
//TString phowgt = wgtvar + "*qcdRespTailWeight";

// No Lepton SF
TString lepvetowgt() {return wgtvar();}
TString lepselwgt()  {return wgtvar();}
const TString vetoes = " && nvetolep==0 && nvetotau==0";

// Tag-and-Probe Lepton SF
//const TString lepvetowgt = wgtvar + "*leptnpweightHM*lepvetoweightHM";
//const TString lepselwgt  = wgtvar + "*leptnpweightHM";
//const TString vetoes = " && nvetolep==0 && (nvetotau==0 || (ismc && npromptgentau>0))";

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// 1Lep LLB method
bool ADD_LEP_TO_MET = false;
bool ICHEPCR = false;
const TString revert_vetoes = " && nvetolep>0 && mtlepmet<100";

// MET+LEP LL method
//bool ADD_LEP_TO_MET = true;
const TString lepcrsel = " && nvetolep==1 && mtlepmet<100 && origmet>100";
//const TString lepcrsel = " && nprimlep==1 && mtlepmet<100 && origmet>100";

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
const TString trigSR = " && (passmetmht || ismc)";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && passjson && (passmetfilters || process==10) && j1chEnFrac>0.1 && j1chEnFrac<0.99";
//const TString qcdSpikeRemovals = " && (!(run==1 && lumi==46160 && event==331634716)) && (!(run==1 && lumi==91626 && event==208129617))";
const TString dphi_invert = " && (dphij1met<0.1 || dphij2met<0.1 || dphij3met<0.1)";

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "met>250 && njets>=2";

std::map<TString, TString> cutMap = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
        {"lmNoDPhi",  "ak8isrpt>200 && dphiisrmet>2 && nsdtop==0 && nsdw==0 && nrestop==0 && metovsqrtht>10"},
        {"dPhiLM",    "dphij1met>0.5 && dphij2met>0.15 && dphij3met>0.15"},
        {"hmNoDPhi",  "njets>=5 && nbjets>=1"},
        {"dPhiHM",    "dphij1met>0.5 && dphij2met>0.5 && dphij3met>0.5 && dphij4met>0.5"},
        {"invertDPhi","(dphij1met<0.1 || dphij2met<0.1 || dphij3met<0.1)"},

        {"nb0",       "nbjets==0"},
        {"nb1",       "nbjets==1"},
        {"nb2",       "nbjets>=2"},
        {"nivf0",     "nivf==0"},
        {"nivf1",     "nivf>=1"},
        {"lowptisr",  "ak8isrpt>300 && ak8isrpt<500"},
        {"highptisr", "ak8isrpt>500"},
        {"nj2to5",    "njets>=2 && njets<=5"},
        {"nj6",       "njets>=6"},
        {"nj7",       "njets>=7"},
        {"lowmtb",    "mtcsv12met<175"},
        {"highmtb",   "mtcsv12met>175"},
        {"lowptb",    "csvj1pt<40"},
        {"medptb",    "csvj1pt>40 && csvj1pt<70"},
        {"highptb",   "csvj1pt>70"},
        {"lowptb12",  "(csvj1pt+csvj2pt)<80"},
        {"medptb12",  "(csvj1pt+csvj2pt)>80 && (csvj1pt+csvj2pt)<140"},
        {"highptb12", "(csvj1pt+csvj2pt)>140"},
        {"nt0",       "nsdtop==0"},
        {"nt1",       "nsdtop==1"},
        {"nt2",       "nsdtop>=2"},
        {"ntgeq1",    "nsdtop>=1"},
        {"nw0",       "nsdw==0"},
        {"nw1",       "nsdw==1"},
        {"nw2",       "nsdw>=2"},
        {"nwgeq1",    "nsdw>=1"},
        {"nrt0",      "nrestop==0"},
        {"nrt1",      "nrestop==1"},
        {"nrt2",      "nrestop>=2"},
        {"nrtgeq1",   "nrestop>=1"},
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
  "hm_nb1_highmtb_nj7_nt0_nrt0_nw0",
  "hm_nb2_highmtb_nj7_nt0_nrt0_nw0",

	// nb1
  // 1 tagged
  "hm_nb1_highmtb_ntgeq1_nrt0_nw0",
  "hm_nb1_highmtb_nt0_nrtgeq1_nw0",
  // 1+1
  "hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",
  "hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",

	// nb2
  // 1 tagged
  "hm_nb2_highmtb_nt1_nrt0_nw0",
  "hm_nb2_highmtb_nt0_nrt1_nw0",
  "hm_nb2_highmtb_nt0_nrt0_nw1",

  // 1+1
  "hm_nb2_highmtb_nt1_nrt0_nw1",
  "hm_nb2_highmtb_nt0_nrt1_nw1",
  "hm_nb2_highmtb_nt1_nrt1_nw0",

  // 2
  "hm_nb2_highmtb_nt2_nrt0_nw0",
  "hm_nb2_highmtb_nt0_nrt2_nw0",
  "hm_nb2_highmtb_nt0_nrt0_nw2",
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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",        {250, 300, 400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",        {250, 300, 400, 500, 1000}},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0",  {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0",  {250, 350, 450, 550, 1000}},

  // nb1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0",                  {550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0",   {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",               {550, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",{250, 350, 450, 550, 1000}},

  // nb2
  {"hm_nb2_highmtb_nt1_nrt0_nw0",                     {550, 650, 1000}},
  {"hm_nb2_highmtb_nt0_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw1",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb2_highmtb_nt1_nrt0_nw1",                     {550, 1000}},
  {"hm_nb2_highmtb_nt0_nrt1_nw1",      {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nt1_nrt1_nw0",      {250, 350, 450, 1000}},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0",      {250, 1000}},
  {"hm_nb2_highmtb_nt0_nrt2_nw0",      {250, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw2",      {250, 1000}},
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
  {"lm_nb0_nivf0_highptisr_nj2to5",              "lm_nb0_highptisr_nj2to5"},
  {"lm_nb0_nivf0_highptisr_nj6",                 "lm_nb0_highptisr_nj6"},
  {"lm_nb0_nivf1_highptisr_nj2to5",              "lm_nb0_highptisr_nj2to5"},
  {"lm_nb0_nivf1_highptisr_nj6",                 "lm_nb0_highptisr_nj6"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb",        "lm_nb1_lowmtb_lowptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb",        "lm_nb1_lowmtb_lowptisr_medptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",       "lm_nb1_lowmtb_highptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",       "lm_nb1_lowmtb_highptisr_medptb"},
  {"lm_nb1_nivf1_lowmtb_lowptb",                 "lm_nb1_lowmtb_lowptb"},

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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",        "hm_nb1_lowmtb_nj7"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",        "hm_nb2_lowmtb_nj7"},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0",  "hm_nb1_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0",  "hm_nb2_highmtb_nj7"},

  // nb1
  // 1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0",   "hm_nb1_highmtb"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0",   "hm_nb1_highmtb"},
  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",  "hm_nb1_highmtb"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",  "hm_nb1_highmtb"},

  // nb2
  //1
  {"hm_nb2_highmtb_nt1_nrt0_nw0",      "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt1_nw0",      "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt0_nw1",      "hm_nb2_highmtb"},

  // 1+1
  {"hm_nb2_highmtb_nt1_nrt0_nw1",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt1_nw1",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt1_nrt1_nw0",        "hm_nb2_highmtb"},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt2_nw0",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt0_nw2",        "hm_nb2_highmtb"},
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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",          "hm_nb1_lowmtb_nj7"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",          "hm_nb2_lowmtb_nj7"},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0",    "hm_nb1_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0",    "hm_nb2_highmtb_nj7"},

  // nb1
  // 1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0",     "hm_nb1_highmtb"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0",     "hm_nb1_highmtb"},
  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",  "hm_nb1_highmtb"},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",  "hm_nb1_highmtb"},

  // nb2
  // 1
  {"hm_nb2_highmtb_nt1_nrt0_nw0",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt1_nw0",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt0_nw1",        "hm_nb2_highmtb"},
  // 1+1
  {"hm_nb2_highmtb_nt1_nrt0_nw1",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt1_nw1",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt1_nrt1_nw0",        "hm_nb2_highmtb"},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt2_nw0",        "hm_nb2_highmtb"},
  {"hm_nb2_highmtb_nt0_nrt0_nw2",        "hm_nb2_highmtb"},
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
  {"lm_nb0_nivf1_highptisr_nj2to5",              {     450, 550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj6",                 {     450, 550, 650, 750, 1000}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb",        {300,                1000}},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb",        {300,                1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",            {450,                1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",            {450,                1000}},

  {"lm_nb1_nivf1_lowmtb_lowptb",                 {300,                1000}},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12",            {300,                1000}},
  {"lm_nb2_lowmtb_lowptisr_medptb12",            {300,                1000}},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7",       {300,                1000}},
  {"lm_nb2_lowmtb_highptisr_lowptb12",                {450,                1000}},
  {"lm_nb2_lowmtb_highptisr_medptb12",                {450,                1000}},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7",           {450,                1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",        {250, 300, 400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",        {250, 300, 400, 500, 1000}},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0",  {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0",  {250, 350, 450, 550, 1000}},

  // nb1
  // 1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nw0",                  {550, 650, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nw0",   {250, 350, 450, 550, 650, 1000}},
  // 1+1
  {"hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1",               {550, 1000}},
  {"hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1",{250, 350, 450, 550, 1000}},

  // nb2
  // 1
  {"hm_nb2_highmtb_nt1_nrt0_nw0",                     {550, 650, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw1",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb2_highmtb_nt0_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb2_highmtb_nt1_nrt0_nw1",                     {550, 1000}},
  {"hm_nb2_highmtb_nt0_nrt1_nw1",      {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nt1_nrt1_nw0",      {250, 350, 450, 1000}},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0",      {250, 1000}},
  {"hm_nb2_highmtb_nt0_nrt2_nw0",      {250, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw2",      {250, 1000}},
  //---------- high deltaM ----------
};


map<TString, Category> srCatMap(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts.at(name), srlabels.at(name), BinInfo("met", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts: phocrCuts;
  const auto &labels = ICHEPCR ? srlabels: phocrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("met", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? srcuts: lepcrCuts;
  const auto &labels = ICHEPCR ? srlabels: lepcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("met", varlabel, lepcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap(){
  map<TString, Category> cmap;
  const auto &cuts = ICHEPCR ? qcd1to1crCuts: qcdcrCuts;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("met", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> zllCatMap{
  {"on-z",  Category("on-z",  "dilepmass > 80 && dilepmass < 100",                      "on Z",   BinInfo("met", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))},
  {"off-z", Category("off-z", "dilepmass > 50 && (dilepmass < 80 || dilepmass > 100)",  "off Z",  BinInfo("met", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))}
};


// ------------------------------------------------------------------------
// samples

BaseConfig phoConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/znunu";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("singlepho",   "Data",           datadir+"/photoncr/singlepho",  "1.0",  datasel + trigPhoCR);

  config.addSample("photon",      "Photon",         "photoncr/photon",     phowgt(), datasel + trigPhoCR + phoBadEventRemoval);
//  config.addSample("photon",      "Photon",         "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt(), datasel + trigSR + vetoes);

  config.sel = baseline;
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

  config.addSample("dyll",      "Z#rightarrowll+jets",    "zllcr/z-soup",                    lepselwgt(), datasel + trigDiLepCR);
  config.addSample("ttbar",     "t#bar{t}",               "zllcr/t-soup",                    lepselwgt(), datasel + trigDiLepCR);
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
  config.outputdir = outputdir()+"/LLB";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  if (ADD_LEP_TO_MET){
    config.addSample("singlelep",   "Data",          datadir+"/lepcr/singlelep",       "1.0",     datasel + trigLepCR + lepcrsel);
    config.addSample("ttbar",       "t#bar{t}",      "lepcr/ttbar",           onelepcrwgt(), datasel + trigLepCR + lepcrsel);
    config.addSample("wjets",       "W+jets",        "lepcr/wjets",           onelepcrwgt(), datasel + trigLepCR + lepcrsel);
    config.addSample("tW",          "tW",            "lepcr/tW",              onelepcrwgt(), datasel + trigLepCR + lepcrsel);
    config.addSample("ttW",         "ttW",           "lepcr/ttW",             onelepcrwgt(), datasel + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "lepcr/qcd",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",   "Data",          datadir+"/sr/met",    "1.0",     datasel + trigSR + revert_vetoes);
    config.addSample("ttbar",       "t#bar{t}",      "sr/ttbar",           lepselwgt(), datasel + trigSR + revert_vetoes);
    config.addSample("wjets",       "W+jets",        "sr/wjets",           lepselwgt(), datasel + trigSR + revert_vetoes);
    config.addSample("tW",          "tW",            "sr/tW",              lepselwgt(), datasel + trigSR + revert_vetoes);
    config.addSample("ttW",         "ttW",           "sr/ttW",             lepselwgt(), datasel + trigSR + revert_vetoes);
//    config.addSample("qcd",         "QCD",           "sr/qcd",             lepselwgt, datasel + trigSR + revert_vetoes);
  }

  config.addSample("ttbar-sr",       "t#bar{t}",      "sr/ttbar",           lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "sr/wjets",           lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "sr/tW",              lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "sr/ttW",             lepvetowgt(), datasel + trigSR + vetoes);
//  config.addSample("qcd-sr",         "QCD",           "qcd",                lepvetowgt(), datasel + trigSR + vetoes);
//  config.addSample("rare-sr",        "Rare",          "sr/rare",            lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("ttZ-sr",         "ttZ",           "sr/ttZ",             lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("diboson-sr",     "Diboson",       "sr/diboson",         lepvetowgt(), datasel + trigSR + vetoes);

  config.sel = baseline;
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

  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("wjets",       "W+jets",        "wjets",        lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("znunu",       "Z#rightarrow#nu#nu", "znunu",   lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("qcd",         "QCD",           "qcd-sr",       lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("tW",          "tW",            "tW",           lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("ttW",         "ttW",           "ttW",          lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("ttZ",         "ttZ",           "ttZ",          lepvetowgt(), datasel + trigSR + vetoes);
  config.addSample("diboson",     "Diboson",       "diboson",      lepvetowgt(), datasel + trigSR + vetoes);

//  config.addSample("T2fbd_500_420", "T2fbd(500,420)", "T2fbd_500_420",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2fbd_500_450", "T2fbd(500,450)", "T2fbd_500_450",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2fbd_500_480", "T2fbd(500,480)", "T2fbd_500_480",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2cc_500_490",  "T2cc(500,490)",  "T2cc_500_490",   sigwgt, datasel + trigSR + vetoes);
//
//  config.addSample("T2tt_450_250",  "T2tt(450,250)",  "T2tt_450_250",   sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2tt_700_400",  "T2tt(700,400)",  "T2tt_700_400",   sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2tt_1100_1",   "T2tt(1100,1)",   "T2tt_1000_1",    sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2bW_850_1",    "T2bW(850,1)",    "T2bW_850_1",     sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2bW_550_350",  "T2bW(550,350)",  "T2bW_550_350",   sigwgt, datasel + trigSR + vetoes);


  COLOR_MAP["T2fbd_500_420"] = kRed;
  COLOR_MAP["T2fbd_500_450"] = kBlue;
  COLOR_MAP["T2fbd_500_480"] = kBlack;
  COLOR_MAP["T2cc_500_490"]  = kMagenta;

  COLOR_MAP["T2tt_450_250"]  = kOrange;
  COLOR_MAP["T2tt_700_400"]  = kCyan+2;
  COLOR_MAP["T2tt_1000_1"]   = kViolet+2;
  COLOR_MAP["T2bW_550_350"]  = kSpring-9;
  COLOR_MAP["T2bW_850_1"]    = kPink+2;

  config.sel = baseline;
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
  config.addSample("data-cr",     "Data",             datadir+"/sr/met",  "1.0",      datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-cr",      "QCD",              "sr/qcd-cr",       qcdwgt(),      datasel + trigSR + dphi_invert);

  config.addSample("qcd-withveto-cr",  "QCD",         "sr/qcd-cr",       qcdvetowgt(),  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-withveto-sr",  "QCD",         "sr/qcd-sr",       qcdvetowgt(),  datasel + trigSR + vetoes);

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-cr",       "t#bar{t}",      "sr/ttbar",        lepvetowgt(),  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("wjets-cr",       "W+jets",        "sr/wjets",        lepvetowgt(),  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("tW-cr",          "tW",            "sr/tW",           lepvetowgt(),  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("ttW-cr",         "ttW",           "sr/ttW",          lepvetowgt(),  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("znunu-cr",       "Znunu",         "sr/znunu",        lepvetowgt(),  datasel + trigSR + vetoes + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",      "Data",          datadir+"/sr/met", "1.0",       datasel + trigSR + revert_vetoes);
  config.addSample("ttbar-norm",     "t#bar{t}",      "sr/ttbar",        lepselwgt(),   datasel + trigSR + revert_vetoes);
  config.addSample("wjets-norm",     "W+jets",        "sr/wjets",        lepselwgt(),   datasel + trigSR + revert_vetoes);
  config.addSample("tW-norm",        "tW",            "sr/tW",           lepselwgt(),   datasel + trigSR + revert_vetoes);
  config.addSample("ttW-norm",       "ttW",           "sr/ttW",          lepselwgt(),   datasel + trigSR + revert_vetoes);
  config.addSample("qcd-norm",       "QCD",           "sr/qcd-sr",       lepselwgt(),   datasel + trigSR + revert_vetoes);

  // qcdsr
  config.addSample("qcd-sr",         "QCD",           "sr/qcd-sr",       qcdwgt(),      datasel + trigSR);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = qcdCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig sigConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir()+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("data-sr",        "Data",             datadir+"/sr/met",                    "1.0",  datasel + trigSR + vetoes);

//  config.addSample("T2fbd_375_355",  "T2-4bd(375,355)",  "sig/T2fbd_375_355",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2fbd_375_325",  "T2-4bd(375,325)",  "sig/T2fbd_375_325",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2fbd_375_295",  "T2-4bd(375,295)",  "sig/T2fbd_375_295",  sigwgt, datasel + trigSR + vetoes);
//
  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

map<TString, BinInfo> varDict {
  {"norm",      BinInfo("met", "#slash{E}_{T}", vector<int>{0, 1000}, "GeV")},
  {"met",       BinInfo("met", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
  {"metgx",       BinInfo("met", "#slash{E}_{T}^{(#gamma)}", vector<int>{250, 350, 450, 550, 650, 850}, "GeV")},
  {"metzg",       BinInfo("met", "#slash{E}_{T}^{#gamma/ll}", vector<int>{250, 350, 450, 550, 650, 850}, "GeV")},
  {"origmet",   BinInfo("origmet", "Original #slash{E}_{T}", 16, 0, 800, "GeV")},
  {"njets",     BinInfo("njets", "N_{j}", 8, -0.5, 7.5)},
  {"njl",       BinInfo("njl", "N_{j}^{ISR}", 4, 0.5, 4.5)},
  {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
  {"nbjets",    BinInfo("nbjets",  "N_{B}^{medium}", 5, -0.5, 4.5)},
  {"dphij1met", BinInfo("dphij1met", "#Delta#phi(j_{1},#slash{E}_{T})", 30, 0, 3)},
  {"dphij2met", BinInfo("dphij2met", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
  {"metovsqrtht",BinInfo("metovsqrtht", "#slash{E}_{T}/#sqrt{H_{T}}", 10, 0, 20)},
  {"dphiisrmet",BinInfo("dphiisrmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
  {"dphiisrmet_fine",BinInfo("dphiisrmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", 12, 0, 3)},
  {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
  {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 12, 0, 600)},
  {"leptonptovermet",  BinInfo("leptonpt/met", "p_{T}^{lep}/#slash{E}_{T}", 20, 0, 1.)},
  {"ak8isrpt",  BinInfo("ak8isrpt", "p_{T}(ISR) [GeV]",  5, 300, 800)},
  {"csvj1pt",   BinInfo("csvj1pt", "p_{T}(b_{1}) [GeV]", 8, 20, 100)},
  {"ptb12",     BinInfo("csvj1pt+csvj2pt", "p_{T}(b_{1})+p_{T}(b_{2}) [GeV]", 8, 40, 200)},
  {"dphilepisr",  BinInfo("dphilepisr", "#Delta#phi(lep, j_{1}^{ISR})", 30, 0, 3)},
  {"drlepisr",  BinInfo("drlepisr", "#DeltaR(lep, j_{1}^{ISR})", 25, 0, 5)},
};

}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
