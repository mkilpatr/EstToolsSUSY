/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "SRParameters.hh"
#include "../utils/Estimator.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// bkg: qcd, znunu, diboson, ttZ, ttbarplusw
// whichCats: "all", "lm", "hm"
//
void makeUncTables(TString inputDir="./confs20170208/", TString outputDir="./tables/", TString whichCats="all"){
  BaseConfig config;
  config.categories = srbins;
  config.catMaps = srCatMap();
  BaseEstimator z(config);

  // load the uncertainty types
  // top tag header: AnalysisBase/TreeAnalyzer/interface/TopWCorrectionSet.h
  map<TString, vector<TString>> unc_to_file;
  unc_to_file["ttbarplusw_pdfunc"]          = {"values_unc_pdfunc_LLB.conf"};
  unc_to_file["ttZ_pdfasunc"]               = {"values_unc_pdfasunc_ttZ.conf"};
  unc_to_file["diboson_pdfasunc"]           = {"values_unc_pdfasunc_diboson.conf"};
  unc_to_file["eff_e"]                      = {"values_unc_lepton.conf"};
  unc_to_file["eff_mu"]                     = {"values_unc_lepton.conf"};
  unc_to_file["eff_tau"]                    = {"values_unc_lepton.conf"};
  unc_to_file["sdMVAWeight_STATS_W"]        = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_STATS_T"]        = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_PS"]             = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_GEN"]            = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_MISTAG_UP_W"]    = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_MISTAG_UP_T"]    = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_MISTAG_STATS_W"] = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_MISTAG_STATS_T"] = {"values_unc_wtoptag.conf"};
  unc_to_file["sdMVAWeight_MISTAG_NB"]      = {"values_unc_wtoptag.conf"};
  unc_to_file["resTopWeight_STATS"]         = {"values_unc_wtoptag.conf"};
  unc_to_file["resTopWeight_PS"]            = {"values_unc_wtoptag.conf"};
  unc_to_file["resTopWeight_GEN"]           = {"values_unc_wtoptag.conf"};
  unc_to_file["resTopWeight_MISTAG_UP"]     = {"values_unc_wtoptag.conf"};
  unc_to_file["resTopWeight_MISTAG_STATS"]  = {"values_unc_wtoptag.conf"};
  unc_to_file["resTopWeight_MISTAG_NB"]     = {"values_unc_wtoptag.conf"};
  unc_to_file["jes"]                        = {"values_unc_jes.conf"};
  unc_to_file["toppt"]                      = {"values_unc_toppt.conf"};
  unc_to_file["ttbarplusw_scaleunc"]        = {"values_unc_scaleunc_LLB.conf"};
  unc_to_file["ttZ_scaleunc"]               = {"values_unc_scaleunc_ttZ.conf"};
  unc_to_file["diboson_scaleunc"]           = {"values_unc_scaleunc_diboson.conf"};
  unc_to_file["b_heavy"]                    = {"values_unc_btag.conf"};
  unc_to_file["b_light"]                    = {"values_unc_btag.conf"};
  unc_to_file["pu"]                         = {"values_unc_pu.conf"};
  unc_to_file["wjetsNorm"]                  = {"values_unc_wtopfrac.conf"};
  unc_to_file["ttbarNorm"]                  = {"values_unc_wtopfrac.conf"};
  unc_to_file["qcd_num_tfstatunc"]          = {"values_0l_unc_qcd_lm.conf","values_0l_unc_qcd_hm.conf"};
  unc_to_file["qcd_den_tfstatunc"]          = {"values_0l_unc_qcd_lm.conf","values_0l_unc_qcd_hm.conf"};
  unc_to_file["qcd_jetresptailunc"]         = {"values_0l_unc_qcd_lm.conf","values_0l_unc_qcd_hm.conf"};
  unc_to_file["qcd_bkgsubunc"]              = {"values_0l_unc_qcd_lm.conf","values_0l_unc_qcd_hm.conf"};
  unc_to_file["qcd_met_integration_systematic"] = {"values_0l_unc_qcd_lm.conf"};
  unc_to_file["lumi"]                       = {"values_0l_unc_all.conf"};
  unc_to_file["dibosonNorm"]                = {"values_0l_unc_all.conf"};
  unc_to_file["ttZNorm"]                    = {"values_0l_unc_all.conf"};
  unc_to_file["qcdSmearNorm"]               = {"values_0l_unc_all.conf"};
  unc_to_file["znunu_zgammadiff"]           = {"values_unc_zgammadiff.conf"};
  unc_to_file["znunu_rzunc"]                = {"values_0l_unc_znunu.conf"};

  // specify any to be combined in quadrature
  vector<pair<TString, TString>> combinedNames = // uncType / combinedName
    {
        {"sdMVAWeight_STATS_W",       "merged_other"},
        {"sdMVAWeight_STATS_T",       "merged_other"},
        {"sdMVAWeight_MISTAG_UP_W",   "merged_other"},
        {"sdMVAWeight_MISTAG_UP_T",   "merged_other"},
        {"sdMVAWeight_MISTAG_STATS_W","merged_other"},
        {"sdMVAWeight_MISTAG_STATS_T","merged_other"},
        {"sdMVAWeight_MISTAG_NB",     "merged_other"},
        {"resTopWeight_STATS",        "resolved_other"},
        {"resTopWeight_MISTAG_UP",    "resolved_other"},
        {"resTopWeight_MISTAG_STATS", "resolved_other"},
        {"resTopWeight_MISTAG_NB",    "resolved_other"},
        {"resTopWeight_MISTAG_STATS", "resolved_qcdznunu"},
        {"resTopWeight_MISTAG_NB",    "resolved_qcdznunu"},
    };

  // llb uncs
  { 
   vector<TString> order = 
      {"eff_e", "eff_mu", "eff_tau", "b_heavy", "b_light", "sdMVAWeight_GEN", "sdMVAWeight_PS", "merged_other", 
       "resTopWeight_PS", "resTopWeight_GEN", "resolved_other","jes", "ttbarNorm", "wjetsNorm", "toppt","pu","ttbarplusw_pdfunc","ttbarplusw_scaleunc"};

    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "ttbarplusw", inputDir, outputDir+"llbunc_lm.tex",  "lm");
    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "ttbarplusw", inputDir, outputDir+"llbunc_hm.tex",  "hm");
  }

  // qcd uncs
  {
   vector<TString> order = 
     {"eff_e", "eff_mu", "eff_tau", "b_heavy", "b_light", "sdMVAWeight_MISTAG_STATS_W","sdMVAWeight_MISTAG_STATS_T","sdMVAWeight_MISTAG_NB","resolved_qcdznunu",
      "jes","qcd_bkgsubunc","qcd_jetresptailunc","qcd_met_integration_systematic","qcd_num_tfstatunc","qcd_den_tfstatunc","qcdSmearNorm"};
    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "qcd", inputDir, outputDir+"qcdunc_lm.tex",  "lm");

   // for HM no met integration systematics.
   order =
     {"eff_e", "eff_mu", "eff_tau", "b_heavy", "b_light", "sdMVAWeight_MISTAG_STATS_W","sdMVAWeight_MISTAG_STATS_T","sdMVAWeight_MISTAG_NB","resolved_qcdznunu",
      "jes","qcd_bkgsubunc","qcd_jetresptailunc","qcd_num_tfstatunc","qcd_den_tfstatunc","qcdSmearNorm"};
    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "qcd", inputDir, outputDir+"qcdunc_hm.tex",  "hm");
  }

  // znunu uncs
  {
   vector<TString> order =
     {"eff_e", "eff_mu", "eff_tau", "b_heavy", "b_light", "sdMVAWeight_MISTAG_STATS_W","sdMVAWeight_MISTAG_STATS_T","sdMVAWeight_MISTAG_NB","resolved_qcdznunu", 
     "jes","znunu_rzunc", "znunu_zgammadiff"};

    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "znunu", inputDir, outputDir+"znunuunc_lm.tex",  "lm");
    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "znunu", inputDir, outputDir+"znunuunc_hm.tex",  "hm");
  }

  // ttZ uncs - hm only
  {
    vector<TString> order =
     {"eff_e", "eff_mu", "eff_tau", "b_heavy", "b_light", "sdMVAWeight_GEN", "sdMVAWeight_PS", "merged_other", "resTopWeight_PS", "resTopWeight_GEN", "resolved_other", 
      "ttZ_pdfasunc","jes","ttZ_scaleunc","ttZNorm"};
    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "ttZ", inputDir, outputDir+"rareunc_hm.tex",  "hm");
  }

  // diboson uncs - lm only
  {
    vector<TString> order = 
     {"eff_e", "eff_mu", "eff_tau", "b_heavy", "b_light", "sdMVAWeight_GEN", "sdMVAWeight_PS", "merged_other", "resTopWeight_PS", "resTopWeight_GEN", "resolved_other", 
      "diboson_pdfasunc","diboson_scaleunc","lumi","dibosonNorm"};
    z.printUncsTableLatex(order, combinedNames, unc_to_file, labelMap, "diboson", inputDir, outputDir+"rareunc_lm.tex",  "lm");
  }

}
