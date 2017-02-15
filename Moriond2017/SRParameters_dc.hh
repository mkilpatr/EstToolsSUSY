#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"

namespace EstTools{

const TString inputdir = "/data/hqu/trees/20170206_lepSF";
const TString outputdir = "/tmp/hqu/plots/20170206_lepSF/unblind_36p8ifb";

const TString datadir = ".";
const TString lumistr = "36.8";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// lumi and base weight
const TString wgtvar = lumistr+"*weight*truePUWeight*btagWeight*topptWeight*sdMVAWeight*resTopWeight";
//const TString wgtvar = lumistr+"*weight*topptWeight*truePUWeight*btagWeight";

// photon trigger eff.
const TString phowgt = wgtvar;
//const TString phowgt = wgtvar + "*qcdRespTailWeight";

// No Lepton SF
//const TString lepvetowgt = wgtvar;
//const TString lepselwgt  = wgtvar;
//const TString vetoes = " && nvetolep==0 && nvetotau==0";

// Tag-and-Probe Lepton SF
const TString lepvetowgt = wgtvar + "*(leptnpweightLM*lepvetoweightLM*(njets<5 || nbjets<1) + leptnpweightHM*lepvetoweightHM*(njets>=5 && nbjets>=1))";
const TString lepselwgt  = wgtvar + "*(leptnpweightLM*(njets<5 || nbjets<1) + leptnpweightHM*(njets>=5 && nbjets>=1))";
const TString vetoes = " && nvetolep==0 && (nvetotau==0 || (ismc && npromptgentau>0))";

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// sr weight w/o top/W SF
const TString lepvetowgt_no_wtopsf = lumistr+"*weight*truePUWeight*btagWeight*topptWeight*(leptnpweightLM*lepvetoweightLM*(njets<5 || nbjets<1) + leptnpweightHM*lepvetoweightHM*(njets>=5 && nbjets>=1))";

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
const TString qcdwgt = wgtvar + "*qcdRespTailWeight";
//const TString qcdwgt = wgtvar;
const TString qcdvetowgt = lepvetowgt + "*qcdRespTailWeight";
//const TString qcdvetowgt = lepvetowgt;

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight*isrWeightTight*(1.0*(mtcsv12met<=175)+sdtopFastSimWeight*sdwFastSimWeight*(mtcsv12met>175))";
const TString sigwgt = lepvetowgt;
const TString siglepselwgt = lepselwgt;

// triggers
const TString trigSR = " && (passmetmht || ismc)";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString phoBadEventRemoval = " && (!(lumi==189375 && event==430170481) && !(lumi==163479 && event==319690728) && !(lumi==24214 && event==55002562) && !(lumi==12510 && event==28415512) && !(lumi==16662 && event==32583938) && !(lumi==115657 && event==226172626) && !(lumi==149227 && event==431689582) && !(lumi==203626 && event==398201606))";
const TString trigDiLepCR = " && passtrigdilepOR && dileppt>200";
const TString datasel = " && passjson && (passmetfilters || process==10) && j1chEnFrac>0.1 && j1chEnFrac<0.99 && (origmet/calomet<5)";
//const TString datasel = " && passjetid && passjson && (passmetfilters || process==10) && j1chEnFrac>0.1 && j1chEnFrac<0.99";
const TString qcdSpikeRemovals = " && (!(lumi==40062 && event==91000735))";
const TString dphi_invert = " && (dphij1met<0.1 || dphij2met<0.1 || dphij3met<0.1)";
const TString dphi_cut = " && ( ((mtcsv12met<175 && nsdtop==0 && nsdw==0 && nrestop==0) && (dphij1met>0.5 && dphij2met>0.15 && dphij3met>0.15)) || (!(mtcsv12met<175 && nsdtop==0 && nsdw==0 && nrestop==0) && (dphij1met>0.5 && dphij2met>0.5 && dphij3met>0.5 && dphij4met>0.5)) )"; // ( ((passLM) && dPhiLM) || ((!passLM) && dPhiHM) )

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
        {"nj5to6",    "njets>=5 && njets<=6"},
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

vector<TString> signals {
  "T2fbd_500_450",
  "T2tt_1000_1",
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
  "hm_nb1_highmtb_nj7_nt0_nrt0_nw0",
  "hm_nb2_highmtb_nj7_nt0_nrt0_nw0",

  // 5-6j
  // nb1
  // 1 tagged
  "hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nw0",
  "hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nw0",
  // 1+1
  "hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nwgeq1",
  "hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nwgeq1",

  // nb2
  // 1 tagged
  "hm_nb2_highmtb_nj5to6_nt1_nrt0_nw0",
  "hm_nb2_highmtb_nj5to6_nt0_nrt1_nw0",
  "hm_nb2_highmtb_nj5to6_nt0_nrt0_nw1",

  // 1+1
  "hm_nb2_highmtb_nj5to6_nt1_nrt0_nw1",
  "hm_nb2_highmtb_nj5to6_nt0_nrt1_nw1",
  "hm_nb2_highmtb_nj5to6_nt1_nrt1_nw0",

  // 2
  "hm_nb2_highmtb_nj5to6_nt2_nrt0_nw0",
  "hm_nb2_highmtb_nj5to6_nt0_nrt2_nw0",
  "hm_nb2_highmtb_nj5to6_nt0_nrt0_nw2",

  // >=7j
	// nb1
  // 1 tagged
  "hm_nb1_highmtb_nj7_ntgeq1_nrt0_nw0",
  "hm_nb1_highmtb_nj7_nt0_nrtgeq1_nw0",
  // 1+1
  "hm_nb1_highmtb_nj7_ntgeq1_nrt0_nwgeq1",
  "hm_nb1_highmtb_nj7_nt0_nrtgeq1_nwgeq1",

	// nb2
  // 1 tagged
  "hm_nb2_highmtb_nj7_nt1_nrt0_nw0",
  "hm_nb2_highmtb_nj7_nt0_nrt1_nw0",
  "hm_nb2_highmtb_nj7_nt0_nrt0_nw1",

  // 1+1
  "hm_nb2_highmtb_nj7_nt1_nrt0_nw1",
  "hm_nb2_highmtb_nj7_nt0_nrt1_nw1",
  "hm_nb2_highmtb_nj7_nt1_nrt1_nw0",

  // 2
  "hm_nb2_highmtb_nj7_nt2_nrt0_nw0",
  "hm_nb2_highmtb_nj7_nt0_nrt2_nw0",
  "hm_nb2_highmtb_nj7_nt0_nrt0_nw2",
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
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0",         {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0",         {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},

  // 5-6j
  // nb1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nw0",                  {550, 650, 1000}},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nw0",   {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nwgeq1",               {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nwgeq1",{250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},

  // nb2
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw0",                     {550, 650, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw1",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw1",                     {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw1",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt1_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 1000}},

  // 2
  {"hm_nb2_highmtb_nj5to6_nt2_nrt0_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt2_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw2",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},

  // >=7j
  // nb1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nw0",                  {550, 650, 1000}},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nw0",   {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nwgeq1",               {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nwgeq1",{250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},

  // nb2
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw0",                     {550, 650, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw1",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw1",                     {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw1",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj7_nt1_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 1000}},

  // 2
  {"hm_nb2_highmtb_nj7_nt2_nrt0_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt2_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw2",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
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

  // 5-6j
  // nb1
  // 1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nw0",   "hm_nb1_highmtb_nj5to6"},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nw0",   "hm_nb1_highmtb_nj5to6"},
  // 1+1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nwgeq1",  "hm_nb1_highmtb_nj5to6"},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nwgeq1",  "hm_nb1_highmtb_nj5to6"},

  // nb2
  //1
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw0",      "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw0",      "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw1",      "hm_nb2_highmtb_nj5to6"},

  // 1+1
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw1",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw1",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt1_nrt1_nw0",        "hm_nb2_highmtb_nj5to6"},

  // 2
  {"hm_nb2_highmtb_nj5to6_nt2_nrt0_nw0",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt2_nw0",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw2",        "hm_nb2_highmtb_nj5to6"},


  // >=7j
  // nb1
  // 1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nw0",   "hm_nb1_highmtb_nj7"},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nw0",   "hm_nb1_highmtb_nj7"},
  // 1+1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nwgeq1",  "hm_nb1_highmtb_nj7"},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nwgeq1",  "hm_nb1_highmtb_nj7"},

  // nb2
  //1
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw0",      "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw0",      "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw1",      "hm_nb2_highmtb_nj7"},

  // 1+1
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw1",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw1",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt1_nrt1_nw0",        "hm_nb2_highmtb_nj7"},

  // 2
  {"hm_nb2_highmtb_nj7_nt2_nrt0_nw0",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt2_nw0",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw2",        "hm_nb2_highmtb_nj7"},
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

  // 5-6j
  // nb1
  // 1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nw0",     "hm_nb1_highmtb_nj5to6"},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nw0",     "hm_nb1_highmtb_nj5to6"},
  // 1+1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nwgeq1",  "hm_nb1_highmtb_nj5to6"},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nwgeq1",  "hm_nb1_highmtb_nj5to6"},

  // nb2
  // 1
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw0",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw0",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw1",        "hm_nb2_highmtb_nj5to6"},
  // 1+1
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw1",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw1",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt1_nrt1_nw0",        "hm_nb2_highmtb_nj5to6"},

  // 2
  {"hm_nb2_highmtb_nj5to6_nt2_nrt0_nw0",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt2_nw0",        "hm_nb2_highmtb_nj5to6"},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw2",        "hm_nb2_highmtb_nj5to6"},

  // >=7j
  // nb1
  // 1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nw0",     "hm_nb1_highmtb_nj7"},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nw0",     "hm_nb1_highmtb_nj7"},
  // 1+1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nwgeq1",  "hm_nb1_highmtb_nj7"},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nwgeq1",  "hm_nb1_highmtb_nj7"},

  // nb2
  // 1
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw0",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw0",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw1",        "hm_nb2_highmtb_nj7"},
  // 1+1
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw1",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw1",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt1_nrt1_nw0",        "hm_nb2_highmtb_nj7"},

  // 2
  {"hm_nb2_highmtb_nj7_nt2_nrt0_nw0",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt2_nw0",        "hm_nb2_highmtb_nj7"},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw2",        "hm_nb2_highmtb_nj7"},
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
  {"hm_nb1_lowmtb_nj7_nrtgeq1",        {250, 300, 400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",        {250, 300, 400, 500, 1000}},

  // high mtb
  // 0 taggged
  {"hm_nb1_highmtb_nj7_nt0_nrt0_nw0",         {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw0",         {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},

  // 5-6j
  // nb1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nw0",                  {550, 650, 1000}},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nw0",   {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_nj5to6_ntgeq1_nrt0_nwgeq1",               {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb1_highmtb_nj5to6_nt0_nrtgeq1_nwgeq1",{250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},

  // nb2
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw0",                     {550, 650, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw1",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb2_highmtb_nj5to6_nt1_nrt0_nw1",                     {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt1_nw1",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt1_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 1000}},

  // 2
  {"hm_nb2_highmtb_nj5to6_nt2_nrt0_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt2_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj5to6_nt0_nrt0_nw2",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},

  // >=7j
  // nb1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nw0",                  {550, 650, 1000}},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nw0",   {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb1_highmtb_nj7_ntgeq1_nrt0_nwgeq1",               {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb1_highmtb_nj7_nt0_nrtgeq1_nwgeq1",{250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},

  // nb2
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw0",                     {550, 650, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw1",      {250, 350, 450, 550, 650, 1000}},

  // 1+1
  {"hm_nb2_highmtb_nj7_nt1_nrt0_nw1",                     {550, 650, 1000}}, // {550, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt1_nw1",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 550, 1000}},
  {"hm_nb2_highmtb_nj7_nt1_nrt1_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 350, 450, 1000}},

  // 2
  {"hm_nb2_highmtb_nj7_nt2_nrt0_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt2_nw0",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
  {"hm_nb2_highmtb_nj7_nt0_nrt0_nw2",      {250, 350, 450, 550, 650, 1000}}, // {250, 1000}},
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

    // add signals in lepcr
    for (const auto &sig : signals){
      config.addSample("lepcr_"+sig,   sig,          "signals/"+sig,    siglepselwgt, datasel + trigSR + revert_vetoes);
    }
  }

  config.addSample("ttbar-sr",       "t#bar{t}",      "sr/ttbar",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "sr/wjets",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "sr/tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "sr/ttW",             lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("qcd-sr",         "QCD",           "qcd",                lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("rare-sr",        "Rare",          "sr/rare",            lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttZ-sr",         "ttZ",           "sr/ttZ",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("diboson-sr",     "Diboson",       "sr/diboson",         lepvetowgt, datasel + trigSR + vetoes);

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
  config.addSample("data-cr",     "Data",             datadir+"/sr/met",  "1.0",      datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-cr",      "QCD",              "sr/qcd-cr",       qcdwgt,      datasel + trigSR + dphi_invert + qcdSpikeRemovals);

  config.addSample("qcd-withveto-cr",  "QCD",         "sr/qcd-cr",       qcdvetowgt,  datasel + trigSR + vetoes + dphi_invert + qcdSpikeRemovals);
  config.addSample("qcd-withveto-sr",  "QCD",         "sr/qcd-sr",       qcdvetowgt,  datasel + trigSR + vetoes + qcdSpikeRemovals);

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-cr",       "t#bar{t}",      "sr/ttbar",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("wjets-cr",       "W+jets",        "sr/wjets",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("tW-cr",          "tW",            "sr/tW",           lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("ttW-cr",         "ttW",           "sr/ttW",          lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("znunu-cr",       "Znunu",         "sr/znunu",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",      "Data",          datadir+"/sr/met", "1.0",       datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("ttbar-norm",     "t#bar{t}",      "sr/ttbar",        lepselwgt,   datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("wjets-norm",     "W+jets",        "sr/wjets",        lepselwgt,   datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("tW-norm",        "tW",            "sr/tW",           lepselwgt,   datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("ttW-norm",       "ttW",           "sr/ttW",          lepselwgt,   datasel + trigSR + revert_vetoes + dphi_cut);
  config.addSample("qcd-norm",       "QCD",           "sr/qcd-sr",       lepselwgt,   datasel + trigSR + revert_vetoes + dphi_cut + qcdSpikeRemovals);

  // qcdsr
  config.addSample("qcd-sr",         "QCD",           "sr/qcd-sr",       qcdwgt,      datasel + trigSR + qcdSpikeRemovals);

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

map<TString, Category> mergedSRCatMap(){
  map<TString, Category> cmap;
  for (auto &name : mergedSRbins){
    cmap[name] = Category(name, mergedSRcuts.at(name), mergedSRlabels.at(name), BinInfo("met", "#slash{E}_{T}", mergedSRMETbins.at(name), "GeV"));
  }
  return cmap;
}

BaseConfig sigConfig(){
  BaseConfig     config;

  config.inputdir = inputdir;
  config.outputdir = outputdir+"/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("data",        "Data",          datadir+"/sr/met",    "1.0",      datasel + trigSR + vetoes);
  config.addSample("ttZ",         "ttZ",           "sr/ttZ",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("diboson",     "Diboson",       "sr/diboson",         lepvetowgt, datasel + trigSR + vetoes);

  // signals in sr
  for (const auto &sig : signals){
    config.addSample(sig,         sig,             "signals/"+sig,       sigwgt,     datasel + trigSR + vetoes);
  }

  config.sel = baseline;
  config.categories = mergedSRbins;
  config.catMaps = mergedSRCatMap();

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
    if (merged_cat_name.Contains("nt0_nrt0_nw0")) categories_to_process.push_back(merged_cat_name);
    else {
      categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("highmtb", "highmtb_nj7"));
      categories_to_process.push_back(TString(merged_cat_name).ReplaceAll("highmtb", "highmtb_nj5to6"));
    }

    // create the sr-to-cr map
    const auto& merged_bin = merged_srCatMap.at(merged_cat_name);
    for (const auto &split_cat_name : categories_to_process){
      // loop over all categories to consider, e.g., 5-6j, >=7j
      const auto &split_bin = split_srCatMap.at(split_cat_name);
      for (unsigned ibin=0; ibin<merged_bin.bin.nbins; ++ibin){
        std::string mergedsr_binname = ("bin_"+merged_cat_name+"_"+merged_bin.bin.binnames.at(ibin)).Data();
        if (merged_bin.bin.plotbins.at(ibin+1) == split_bin.bin.plotbins.at(ibin+1)) {
          if (merged_cat_name.Contains("nt0_nrt0_nw0")) continue;
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
            auto splitsrbinname = "bin_"+split_cat_name+"_"+split_bin.bin.binnames.at(icr);
            auto crbinname = "bin_"+control_region+"_"+TString(crMapping.at(split_cat_name)).ReplaceAll("NoDPhi_","_")+"_"+split_bin.bin.binnames.at(icr);
            results[mergedsr_binname]; // touch it: initialize it if not, otherwise should append (5-6j, and >=7j)
            results[mergedsr_binname].push_back("<"+splitsrbinname+">*("+crbinname+")");
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

map<std::string, std::string> lepcrBinMap = makeBinMap("lepcr");
map<std::string, std::string> phocrBinMap = makeBinMap("phocr");
map<std::string, std::string> qcdcrBinMap = makeBinMap("qcdcr");
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
