/*
 *
 *  Created on: Oct 23, 2019
 *      Author: mkilpatr
 */

#include <fstream>

#include "Syst_SR_Parameters.hh"
//#include "Syst_LowMET_Parameters.hh"

#include "../../EstMethods/LLBEstimator.hh"
#include "../../EstMethods/QCDEstimator.hh"

using namespace EstTools;

vector<Quantity> getQCDPred(TString sys_name = ""){
  auto qcdcfg = qcdConfig();
  if(sys_name == "JESUp"){
    qcdcfg.catMaps = srCatMap_JESUp();
    qcdcfg.crCatMaps = qcdCatMap_JESUp();
  } else if(sys_name == "JESDown"){
    qcdcfg.catMaps = srCatMap_JESDown();
    qcdcfg.crCatMaps = qcdCatMap_JESDown();
  } else if(sys_name == "metresUp"){
    qcdcfg.catMaps = srCatMap_METUnClustUp();
    qcdcfg.crCatMaps = qcdCatMap_METUnClustUp();
  } else if(sys_name == "metresDown"){
    qcdcfg.catMaps = srCatMap_METUnClustDown();
    qcdcfg.crCatMaps = qcdCatMap_METUnClustDown();
  } else{
    qcdcfg.catMaps = srCatMap();
    qcdcfg.crCatMaps = qcdCatMap();
  }
  QCDEstimator q(qcdcfg);
  q.runBootstrapping = false;
  q.pred();
  q.printYields();
  vector<Quantity> yields = q.yields.at("_TF");
  qcdcfg.reset();
  return yields;
}

map<TString, vector<Quantity>> getLLBPred(TString sys_name = ""){
  auto llbcfg = lepConfig();
  if(sys_name == "JESUp"){
    llbcfg.catMaps = srCatMap_JESUp();
    llbcfg.crCatMaps = lepCatMap_JESUp();
  } else if(sys_name == "JESDown"){
    llbcfg.catMaps = srCatMap_JESDown();
    llbcfg.crCatMaps = lepCatMap_JESDown();
  } else if(sys_name == "metresUp"){
    llbcfg.catMaps = srCatMap_METUnClustUp();
    llbcfg.crCatMaps = lepCatMap_METUnClustUp();
  } else if(sys_name == "metresDown"){
    llbcfg.catMaps = srCatMap_METUnClustDown();
    llbcfg.crCatMaps = lepCatMap_METUnClustDown();
  } else{
    llbcfg.catMaps = srCatMap();
    llbcfg.crCatMaps = lepCatMap();
  }
  LLBEstimator l(llbcfg);
  l.pred();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));
  vector<Quantity> yields = l.yields.at("_TF");
  llbcfg.reset();
  
  return {
    {"ttbarplusw", yields},
    //{"ttZ",        l.yields.at("ttZ-sr")},
    //{"diboson",    l.yields.at("diboson-sr")},
  };
}

void SystJES(std::string outfile_path = "values_unc_jes.conf"){

  vector<TString> bkgnames  = {"qcd", "ttbarplusw"};
  map<TString, map<TString, vector<Quantity>>> proc_syst_pred; // {proc: {syst: yields}}
  for (auto &bkg : bkgnames){
    proc_syst_pred[bkg] = map<TString, vector<Quantity>>();
  }

  // nominal
  {
    //inputdir = ".";
    sys_name = "nominal";
    EstTools::jes_postfix = "";
    //proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // jes - up
  {
    sys_name = "JES_up";
    EstTools::jes_postfix = "_JESUp";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  {
    sys_name = "JES_down";
    EstTools::jes_postfix = "_JESDown";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // metres - up
  {
    sys_name = "metres_up";
    EstTools::jes_postfix = "_METUnClustUp";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  {
    sys_name = "metres_down";
    EstTools::jes_postfix = "_METUnClustDown";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // trigger - up
  {
    sys_name = "trigger_eff_up";
    triggerwgt = "Stop0l_trigger_eff_MET_loose_baseline_up";
    triggerwgtqcd = "Stop0l_trigger_eff_MET_loose_baseline_QCD_up";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  {
    sys_name = "trigger_eff_down";
    triggerwgt = "Stop0l_trigger_eff_MET_loose_baseline_down";
    triggerwgtqcd = "Stop0l_trigger_eff_MET_loose_baseline_QCD_down";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  cout << "\n\n Write unc to " << outfile_path << endl;
  ofstream outfile(outfile_path);
  auto config = lepConfig();

  for (auto &bkg : bkgnames){
    auto nominal_pred = proc_syst_pred[bkg]["nominal"];
    for (auto &sPair : proc_syst_pred[bkg]){
      if(sPair.first=="nominal") continue;
      if(sPair.first.EndsWith("_down")) continue; // ignore down: processed at the same time as up
      std::pair<vector<Quantity>, vector<Quantity>> uncs;
      vector<Quantity> uncs_up, uncs_down;

      if(sPair.first.EndsWith("_up")){
        auto varup = sPair.second / nominal_pred;
        auto name_down = TString(sPair.first).ReplaceAll("_up", "_down");
        auto vardown = proc_syst_pred[bkg].at(name_down) / nominal_pred;
        uncs = Quantity::combineUpDownSepUncs(varup, vardown);
	uncs_up = uncs.first;
	uncs_down = uncs.second;
      } else{
        uncs_down = sPair.second / nominal_pred;
      }

      unsigned ibin = 0;
      for (auto &cat_name : config.categories){
        auto &cat = config.catMaps.at(cat_name);
        for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
          auto xlow = toString(cat.bin.plotbins.at(ix), 0);
          auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
          auto binname = "bin_" + cat_name + "_" + cat.bin.var + xlow + "to" + xhigh;
          auto uncType_up   = TString(sPair.first); 
          auto uncType_down = TString(sPair.first).ReplaceAll("_up", "_down"); 
          outfile << binname << "\t" << uncType_up << "\t" << bkg << "\t" << uncs_up.at(ibin).value << endl;
          outfile << binname << "\t" << uncType_down << "\t" << bkg << "\t" << uncs_down.at(ibin).value << endl;
          ++ibin;
        }
      }
    }
  }

  outfile.close();

  cout << "Done!" << endl;

}
