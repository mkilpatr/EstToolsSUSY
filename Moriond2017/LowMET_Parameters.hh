#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"

namespace EstTools{

const TString datadir = ".";
const TString lumistr = "35.6";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// lumi and base weight
const TString wgtvar = lumistr+"*weight*topptWeight*sdMVAWeight*resTopWeight";
//const TString wgtvar = lumistr+"*weight*topptWeight*truePUWeight*btagWeight";

// photon trigger eff.
const TString phowgt = wgtvar;
//const TString phowgt = wgtvar + "*qcdRespTailWeight";

// No Lepton SF
const TString lepvetowgt = wgtvar;
const TString lepselwgt  = wgtvar;
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
const TString onelepcrwgt  = lepselwgt;

// qcd weights
//const TString qcdwgt = wgtvar + "*qcdRespTailWeight";
const TString qcdwgt = wgtvar;
//const TString qcdvetowgt = lepvetowgt + "*qcdRespTailWeight";
const TString qcdvetowgt = lepvetowgt;

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(1.0*(mtcsv12met<=175)+sdtopFastSimWeight*sdwFastSimWeight*(mtcsv12met>175))";
const TString sigwgt = lepvetowgt;

// triggers
const TString trigSR = " && (passmetmht || ismc)";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && passjson && (passmetfilters || process==10) && j1chEnFrac>0.1 && j1chEnFrac<0.99";
//const TString qcdSpikeRemovals = " && (!(run==1 && lumi==46160 && event==331634716)) && (!(run==1 && lumi==91626 && event==208129617))";
const TString dphi_invert = " && (dphij1met<0.1 || dphij2met<0.1 || dphij3met<0.1)";

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "met>200 && njets>=2";

std::map<TString, TString> cutMap = []{
    // Underscore "_" not allowed in the names!!!
    std::map<TString, TString> cmap = {
        {"lmNoDPhi",  "j1lpt>200 && dphij1lmet>2 && nsdtop==0 && nsdw==0 && nrestop==0 && metovsqrtht>10"},
        {"dPhiLM",    "dphij1met>0.5 && dphij2met>0.15 && dphij3met>0.15"},
        {"hmNoDPhi",  "njets>=5 && nbjets>=1"},
        {"dPhiHM",    "dphij1met>0.5 && dphij2met>0.5 && dphij3met>0.5 && dphij4met>0.5"},
        {"invertDPhi","(dphij1met<0.1 || dphij2met<0.1 || dphij3met<0.1)"},

        {"nb0",       "nbjets==0"},
        {"nb1",       "nbjets==1"},
        {"nb2",       "nbjets>=2"},
        {"nivf0",     "nivf==0"},
        {"nivf1",     "nivf>=1"},
        {"lowptisr",  "j1lpt>300 && j1lpt<500"},
        {"highptisr", "j1lpt>500"},
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
        {"nw0",       "nsdw==0"},
        {"nw1",       "nsdw==1"},
        {"nw2",       "nsdw>=2"},
        {"nrt0",      "nrestop==0"},
        {"nrt1",      "nrestop==1"},
        {"nrt2",      "nrestop>=2"},
        {"nrtge1",    "nrestop>=1"},
        {"met250",    "met<250"},
        {"met350",    "met<350"},
        {"met400",    "met<400"},
        {"met450",    "met<450"},
    };

    cmap["lm"] = createCutString("lmNoDPhi_dPhiLM", cmap);
    cmap["hm"] = createCutString("hmNoDPhi_dPhiHM", cmap);
    return cmap;
}();


std::vector<TString> srbins{
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  "lm_nb0_nivf0_highptisr_nj2to5_met400",
  "lm_nb0_nivf0_highptisr_nj6_met400",
  "lm_nb0_nivf1_highptisr_nj2to5_met400",
  "lm_nb0_nivf1_highptisr_nj6_met400",

  // 1b, 0 or >=1 ivf
  "lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met250",
  "lm_nb1_nivf0_lowmtb_lowptisr_medptb_met250",
  "lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400",
  "lm_nb1_nivf0_lowmtb_highptisr_medptb_met400",
  // ---
  "lm_nb1_nivf1_lowmtb_lowptisr_lowptb_met250",
  "lm_nb1_nivf1_lowmtb_highptisr_lowptb_met400",

  // 2b
  "lm_nb2_lowmtb_lowptisr_lowptb12_met250",
  "lm_nb2_lowmtb_lowptisr_medptb12_met250",
  "lm_nb2_lowmtb_lowptisr_highptb12_nj7_met250",
  "lm_nb2_lowmtb_highptisr_lowptb12_met400",
  "lm_nb2_lowmtb_highptisr_medptb12_met400",
  "lm_nb2_lowmtb_highptisr_highptb12_nj7_met400",
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  "hm_nb1_lowmtb_nj7_nrtge1_met250",
  "hm_nb2_lowmtb_nj7_nrtge1_met250",

  // high mtb
  // 0 taggged
  "hm_nb1_highmtb_nj7_nt0_nrt0_nw0_met250",
  "hm_nb2_highmtb_nj7_nt0_nrt0_nw0_met250",

  // 1
  "hm_nb1_highmtb_nt1_nrt0_nw0_met450",
  "hm_nb2_highmtb_nt1_nrt0_nw0_met450",
  "hm_nb1_highmtb_nt0_nrt1_nw0_met250",
  "hm_nb2_highmtb_nt0_nrt1_nw0_met250",
  "hm_nb2_highmtb_nt0_nrt0_nw1_met250",

  // 1+1
  "hm_nb1_highmtb_nt1_nrt0_nw1_met450",
  "hm_nb2_highmtb_nt1_nrt0_nw1_met450",
  "hm_nb1_highmtb_nt0_nrt1_nw1_met250",
  "hm_nb2_highmtb_nt0_nrt1_nw1_met250",

  "hm_nb2_highmtb_nt1_nrt1_nw0_met250",

  // 2
  "hm_nb2_highmtb_nt2_nrt0_nw0_met250",
  "hm_nb2_highmtb_nt0_nrt2_nw0_met250",
  "hm_nb2_highmtb_nt0_nrt0_nw2_met250",
  //---------- high deltaM ----------

};

std::map<TString, TString> srcuts = []{
    std::map<TString, TString> cuts;
    for (auto name : srbins)
      cuts[name] = createCutString(name, cutMap);
    return cuts;
}();

std::map<TString, TString> srlabels=srcuts;// FIXME

std::map<TString, std::vector<int>> srMETbins{
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5_met400",              {200, 1000}},
  {"lm_nb0_nivf0_highptisr_nj6_met400",                 {200, 1000}},
  {"lm_nb0_nivf1_highptisr_nj2to5_met400",              {200, 1000}},
  {"lm_nb0_nivf1_highptisr_nj6_met400",                 {200, 1000}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met250",        {200, 1000}},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb_met250",        {200, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400",       {200, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb_met400",       {200, 1000}},

  {"lm_nb1_nivf1_lowmtb_lowptisr_lowptb_met250",        {200, 1000}},
  {"lm_nb1_nivf1_lowmtb_highptisr_lowptb_met400",       {200, 1000}},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12_met250",            {200, 1000}},
  {"lm_nb2_lowmtb_lowptisr_medptb12_met250",            {200, 1000}},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7_met250",       {200, 1000}},
  {"lm_nb2_lowmtb_highptisr_lowptb12_met400",           {200, 1000}},
  {"lm_nb2_lowmtb_highptisr_medptb12_met400",           {200, 1000}},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7_met400",      {200, 1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtge1_met250",       {200, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtge1_met250",       {200, 1000}},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0_met250",  {200, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0_met250",  {200, 1000}},

  // 1
  {"hm_nb1_highmtb_nt1_nrt0_nw0_met450",      {200, 1000}},
  {"hm_nb2_highmtb_nt1_nrt0_nw0_met450",      {200, 1000}},
  {"hm_nb1_highmtb_nt0_nrt1_nw0_met250",  {200, 1000}},
  {"hm_nb2_highmtb_nt0_nrt1_nw0_met250",  {200, 1000}},

  {"hm_nb2_highmtb_nt0_nrt0_nw1_met250",  {200, 1000}},

  // 1+1
  {"hm_nb1_highmtb_nt1_nrt0_nw1_met450",  {200, 1000}},
  {"hm_nb2_highmtb_nt1_nrt0_nw1_met450",  {200, 1000}},

  {"hm_nb1_highmtb_nt0_nrt1_nw1_met250",  {200, 1000}},
  {"hm_nb2_highmtb_nt0_nrt1_nw1_met250",  {200, 1000}},

  {"hm_nb2_highmtb_nt1_nrt1_nw0_met250",  {200, 1000}},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0_met250",  {200, 1000}},
  {"hm_nb2_highmtb_nt0_nrt2_nw0_met250",  {200, 1000}},
  {"hm_nb2_highmtb_nt0_nrt0_nw2_met250",  {200, 1000}},
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
std::map<TString, TString> phoNormMap = {
  {"lm_nb0", createCutString("lmNoDPhi_nb0", cutMap)},
  {"lm_nb1", createCutString("lmNoDPhi_nb1", cutMap)},
  {"lm_nb2", createCutString("lmNoDPhi_nb2", cutMap)},

  {"hm_nb1", createCutString("hmNoDPhi_nb1", cutMap)},
  {"hm_nb2", createCutString("hmNoDPhi_nb2", cutMap)},
};

//std::map<TString, TString> phoNormMap = normMap;

std::map<TString, TString> phocrMapping{
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5_met400",              "lm_nb0_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf0_highptisr_nj6_met400",                 "lm_nb0_highptisr_nj6_met400"},
  {"lm_nb0_nivf1_highptisr_nj2to5_met400",              "lm_nb0_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf1_highptisr_nj6_met400",                 "lm_nb0_highptisr_nj6_met400"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met250",        "lm_nb1_lowmtb_lowptisr_lowptb_met250"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb_met250",        "lm_nb1_lowmtb_lowptisr_medptb_met250"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400",       "lm_nb1_lowmtb_highptisr_lowptb_met400"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb_met400",       "lm_nb1_lowmtb_highptisr_medptb_met400"},
  {"lm_nb1_nivf1_lowmtb_lowptisr_lowptb_met250",        "lm_nb1_lowmtb_lowptisr_lowptb_met250"},
  {"lm_nb1_nivf1_lowmtb_highptisr_lowptb_met400",       "lm_nb1_lowmtb_highptisr_lowptb_met400"},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12_met250",            "lm_nb2_lowmtb_lowptisr_lowptb12_met250"},
  {"lm_nb2_lowmtb_lowptisr_medptb12_met250",            "lm_nb2_lowmtb_lowptisr_medptb12_met250"},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7_met250",       "lm_nb2_lowmtb_lowptisr_highptb12_nj7_met250"},
  {"lm_nb2_lowmtb_highptisr_lowptb12_met400",           "lm_nb2_lowmtb_highptisr_lowptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_medptb12_met400",           "lm_nb2_lowmtb_highptisr_medptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7_met400",      "lm_nb2_lowmtb_highptisr_highptb12_nj7_met400"},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtge1_met250",       "hm_nb1_lowmtb_nj7_met250"},
  {"hm_nb2_lowmtb_nj7_nrtge1_met250",       "hm_nb2_lowmtb_nj7_met250"},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0_met250",  "hm_nb1_highmtb_nj7_met250"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0_met250",  "hm_nb2_highmtb_nj7_met250"},

  // 1
  {"hm_nb1_highmtb_nt1_nrt0_nw0_met450",  "hm_nb1_highmtb_met450"},
  {"hm_nb2_highmtb_nt1_nrt0_nw0_met450",  "hm_nb2_highmtb_met450"},
  {"hm_nb1_highmtb_nt0_nrt1_nw0_met250",  "hm_nb1_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt1_nw0_met250",  "hm_nb2_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt0_nw1_met250",  "hm_nb2_highmtb_met250"},

  // 1+1
  {"hm_nb1_highmtb_nt1_nrt0_nw1_met450",  "hm_nb1_highmtb_met450"},
  {"hm_nb2_highmtb_nt1_nrt0_nw1_met450",  "hm_nb2_highmtb_met450"},

  {"hm_nb1_highmtb_nt0_nrt1_nw1_met250",  "hm_nb1_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt1_nw1_met250",  "hm_nb2_highmtb_met250"},

  {"hm_nb2_highmtb_nt1_nrt1_nw0_met250",  "hm_nb2_highmtb_met250"},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0_met250",  "hm_nb2_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt2_nw0_met250",  "hm_nb2_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt0_nw2_met250",  "hm_nb2_highmtb_met250"},
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
  {"lm_nb0_nivf0_highptisr_nj2to5_met400",              "lm_nb0_nivf0_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf0_highptisr_nj6_met400",                 "lm_nb0_nivf0_highptisr_nj6_met400"},
  {"lm_nb0_nivf1_highptisr_nj2to5_met400",              "lm_nb0_nivf1_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf1_highptisr_nj6_met400",                 "lm_nb0_nivf1_highptisr_nj6_met400"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met250",        "lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met250"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb_met250",        "lm_nb1_nivf0_lowmtb_lowptisr_medptb_met250"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400",       "lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb_met400",       "lm_nb1_nivf0_lowmtb_highptisr_medptb_met400"},
  {"lm_nb1_nivf1_lowmtb_lowptisr_lowptb_met250",        "lm_nb1_nivf1_lowmtb_lowptisr_lowptb_met250"},
  {"lm_nb1_nivf1_lowmtb_highptisr_lowptb_met400",       "lm_nb1_nivf1_lowmtb_highptisr_lowptb_met400"},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12_met250",            "lm_nb2_lowmtb_lowptisr_lowptb12_met250"},
  {"lm_nb2_lowmtb_lowptisr_medptb12_met250",            "lm_nb2_lowmtb_lowptisr_medptb12_met250"},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7_met250",       "lm_nb2_lowmtb_lowptisr_highptb12_nj7_met250"},
  {"lm_nb2_lowmtb_highptisr_lowptb12_met400",           "lm_nb2_lowmtb_highptisr_lowptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_medptb12_met400",           "lm_nb2_lowmtb_highptisr_medptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7_met400",      "lm_nb2_lowmtb_highptisr_highptb12_nj7_met400"},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtge1_met250",       "hm_nb1_lowmtb_nj7_met250"},
  {"hm_nb2_lowmtb_nj7_nrtge1_met250",       "hm_nb2_lowmtb_nj7_met250"},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0_met250",  "hm_nb1_highmtb_nj7_met250"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0_met250",  "hm_nb2_highmtb_nj7_met250"},

  // 1
  {"hm_nb1_highmtb_nt1_nrt0_nw0_met450",  "hm_nb1_highmtb_met450"},
  {"hm_nb2_highmtb_nt1_nrt0_nw0_met450",  "hm_nb2_highmtb_met450"},
  {"hm_nb1_highmtb_nt0_nrt1_nw0_met250",  "hm_nb1_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt1_nw0_met250",  "hm_nb2_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt0_nw1_met250",  "hm_nb2_highmtb_met250"},

  // 1+1
  {"hm_nb1_highmtb_nt1_nrt0_nw1_met450",  "hm_nb1_highmtb_met450"},
  {"hm_nb2_highmtb_nt1_nrt0_nw1_met450",  "hm_nb2_highmtb_met450"},

  {"hm_nb1_highmtb_nt0_nrt1_nw1_met250",  "hm_nb1_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt1_nw1_met250",  "hm_nb2_highmtb_met250"},

  {"hm_nb2_highmtb_nt1_nrt1_nw0_met250",  "hm_nb2_highmtb_met250"},

  // 2
  {"hm_nb2_highmtb_nt2_nrt0_nw0_met250",  "hm_nb2_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt2_nw0_met250",  "hm_nb2_highmtb_met250"},
  {"hm_nb2_highmtb_nt0_nrt0_nw2_met250",  "hm_nb2_highmtb_met250"},
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
  auto crmap = phocrMapping;
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
std::map<TString, TString> qcdcrlabels = phocrlabels;
std::map<TString, std::vector<int>> qcdcrMETbins = srMETbins;


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
  const auto &cuts = ICHEPCR ? srcuts: qcdcrCuts;
  const auto &labels = ICHEPCR ? srlabels: qcdcrlabels;
  for (auto &name : srbins){
    cmap[name] = Category(name, cuts.at(name), labels.at(name), BinInfo("met", "#slash{E}_{T}", qcdcrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> zllCatMap{
  {"on-z",  Category("on-z",  "dilepmass > 80 && dilepmass < 100",                      "on Z",   BinInfo("met", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))},
  {"off-z", Category("off-z", "dilepmass > 20 && (dilepmass < 80 || dilepmass > 100)",  "off Z",  BinInfo("met", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))}
};


// ------------------------------------------------------------------------
// samples

BaseConfig phoConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/plots/LowMET_ak4isr/znunu";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("singlepho",   "Data",           datadir+"/photoncr/singlepho",  "1.0",  datasel + trigPhoCR);

  config.addSample("photon",      "Photon",         "photoncr/photon",     phowgt, datasel + trigPhoCR);
//  config.addSample("photon",      "Photon",         "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt, datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = phoCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig zllConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/plots/LowMET_ak4isr/zllcr";
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

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/plots/LowMET_ak4isr/LLB";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  if (ADD_LEP_TO_MET){
    config.addSample("singlelep",   "Data",          datadir+"/lepcr/singlelep",       "1.0",     datasel + trigLepCR + lepcrsel);
    config.addSample("ttbar",       "t#bar{t}",      "lepcr/ttbar",           onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("wjets",       "W+jets",        "lepcr/wjets",           onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("tW",          "tW",            "lepcr/tW",              onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("ttW",         "ttW",           "lepcr/ttW",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "lepcr/qcd",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",   "Data",          datadir+"/sr/met",    "1.0",     datasel + trigSR + revert_vetoes);
    config.addSample("ttbar",       "t#bar{t}",      "sr/ttbar",           lepselwgt, datasel + trigSR + revert_vetoes);
    config.addSample("wjets",       "W+jets",        "sr/wjets",           lepselwgt, datasel + trigSR + revert_vetoes);
    config.addSample("tW",          "tW",            "sr/tW",              lepselwgt, datasel + trigSR + revert_vetoes);
    config.addSample("ttW",         "ttW",           "sr/ttW",             lepselwgt, datasel + trigSR + revert_vetoes);
//    config.addSample("qcd",         "QCD",           "sr/qcd",             lepselwgt, datasel + trigSR + revert_vetoes);
  }

  config.addSample("ttbar-sr",       "t#bar{t}",      "sr/ttbar",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "sr/wjets",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "sr/tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "sr/ttW",             lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("qcd-sr",         "QCD",           "sr/qcd",             qcdwgt, datasel + trigSR + vetoes);
//  config.addSample("rare-sr",        "Rare",          "sr/rare",            lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttZ-sr",         "ttZ",           "sr/ttZ",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("diboson-sr",     "Diboson",       "sr/diboson",         lepvetowgt, datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = lepCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig srConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/plots/testSR";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("wjets",       "W+jets",        "wjets",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu",       "Z#rightarrow#nu#nu", "znunu",   lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("qcd",         "QCD",           "qcd",          lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW",          "tW",            "tW",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW",         "ttW",           "ttW",          lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttZ",         "ttZ",           "ttZ",          lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("diboson",     "Diboson",       "diboson",      lepvetowgt, datasel + trigSR + vetoes);

  config.addSample("T2fbd_500_420", "T2fbd(500,420)", "T2fbd_500_420",  sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2fbd_500_450", "T2fbd(500,450)", "T2fbd_500_450",  sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2fbd_500_480", "T2fbd(500,480)", "T2fbd_500_480",  sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2cc_500_490",  "T2cc(500,490)",  "T2cc_500_490",   sigwgt, datasel + trigSR + vetoes);

  config.addSample("T2tt_450_250",  "T2tt(450,250)",  "T2tt_450_250",   sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2tt_700_400",  "T2tt(700,400)",  "T2tt_700_400",   sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2tt_1100_1",   "T2tt(1100,1)",   "T2tt_1000_1",    sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2bW_850_1",    "T2bW(850,1)",    "T2bW_850_1",     sigwgt, datasel + trigSR + vetoes);
  config.addSample("T2bW_550_350",  "T2bW(550,350)",  "T2bW_550_350",   sigwgt, datasel + trigSR + vetoes);


  COLOR_MAP["T2fbd_500_420"] = kRed;
  COLOR_MAP["T2fbd_500_450"] = kBlue;
  COLOR_MAP["T2fbd_500_480"] = kBlack;
  COLOR_MAP["T2cc_500_490"]  = kMagenta;

  COLOR_MAP["T2tt_450_250"]  = kOrange;
  COLOR_MAP["T2tt_700_400"]  = kCyan+2;
  COLOR_MAP["T2tt_1100_1"]   = kViolet+2;
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

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/plots/LowMET_ak4isr/QCD";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  // qcdcr
  config.addSample("data-cr",     "Data",             datadir+"/sr/met",  "1.0",      datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-cr",      "QCD",              "sr/qcd",          qcdwgt,      datasel + trigSR + dphi_invert);

  config.addSample("qcd-withveto-cr",  "QCD",         "sr/qcd",          qcdvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-withveto-sr",  "QCD",         "sr/qcd",          qcdvetowgt,  datasel + trigSR + vetoes);

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-cr",       "t#bar{t}",      "sr/ttbar",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("wjets-cr",       "W+jets",        "sr/wjets",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("tW-cr",          "tW",            "sr/tW",           lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("ttW-cr",         "ttW",           "sr/ttW",          lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("znunu-cr",       "Znunu",         "sr/znunu",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",      "Data",          datadir+"/sr/met", "1.0",       datasel + trigSR + revert_vetoes);
  config.addSample("ttbar-norm",     "t#bar{t}",      "sr/ttbar",        lepselwgt,   datasel + trigSR + revert_vetoes);
  config.addSample("wjets-norm",     "W+jets",        "sr/wjets",        lepselwgt,   datasel + trigSR + revert_vetoes);
  config.addSample("tW-norm",        "tW",            "sr/tW",           lepselwgt,   datasel + trigSR + revert_vetoes);
  config.addSample("ttW-norm",       "ttW",           "sr/ttW",          lepselwgt,   datasel + trigSR + revert_vetoes);
  config.addSample("qcd-norm",       "QCD",           "sr/qcd",          lepselwgt,   datasel + trigSR + revert_vetoes);

  // qcdsr
  config.addSample("qcd-sr",         "QCD",           "sr/qcd",          qcdwgt,      datasel + trigSR);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = qcdCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig sigConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/plots/LowMET_ak4isr/sig";
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
  {"dphij1lmet",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
  {"dphij1lmet_fine",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", 12, 0, 3)},
  {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
  {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 12, 0, 600)},
  {"leptonptovermet",  BinInfo("leptonpt/met", "p_{T}^{lep}/#slash{E}_{T}", 20, 0, 1.)},
  {"j1lpt",     BinInfo("j1lpt", "p_{T}(j_{1}^{ISR}) [GeV]", 10, 250, 750)},
  {"csvj1pt",   BinInfo("csvj1pt/1", "p_{T}(b_{1}) [GeV]", 8, 20, 100)},
  {"ptb12",     BinInfo("csvj1pt+csvj2pt", "p_{T}(b_{1})+p_{T}(b_{2}) [GeV]", 8, 40, 200)},
  {"dphilepisr",  BinInfo("dphilepisr", "#Delta#phi(lep, j_{1}^{ISR})", 30, 0, 3)},
  {"drlepisr",  BinInfo("drlepisr", "#DeltaR(lep, j_{1}^{ISR})", 25, 0, 5)},
};

}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
