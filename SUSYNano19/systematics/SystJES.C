/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>

#include "Syst_SR_Parameters.hh"
//#include "Syst_LowMET_Parameters.hh"

#include "../../EstMethods/LLBEstimator.hh"
#include "../../EstMethods/ZnunuEstimator.hh"
#include "../../EstMethods/QCDEstimator.hh"

using namespace EstTools;

vector<Quantity> getZnunuPred(){
  auto phocfg = phoConfig();
  ZnunuEstimator z(phocfg);
  z.zllcr_cfg = zllConfig();
  z.zll_normMap = normMap;
  z.phocr_normMap = phoNormMap;
  z.pred();
  z.printYields();
  return z.yields.at("_TF");
}

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
  }
  QCDEstimator q(qcdcfg);
  q.runBootstrapping = false;
  q.pred();
  q.printYields();
  return q.yields.at("_TF");
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
  }
  LLBEstimator l(llbcfg);
  l.pred();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));

  return {
    {"ttbarplusw", l.yields.at("_TF")},
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

  //// nominal
  //{
  //  //inputdir = ".";
  //  sys_name = "nominal";
  //  EstTools::jes_postfix = "";
  //  //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
  //  proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
  //  auto llb = getLLBPred();
  //  for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  //}

  //// jes - up
  //{
  //  sys_name = "JESUp";
  //  EstTools::jes_postfix = "_JESUp";
  //  //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
  //  proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
  //  auto llb = getLLBPred(sys_name);
  //  for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  //}

  //{
  //  sys_name = "JESDown";
  //  EstTools::jes_postfix = "_JESDown";
  //  //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
  //  proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
  //  auto llb = getLLBPred(sys_name);
  //  for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  //}

  // metres - up
  {
    sys_name = "metresUp";
    EstTools::jes_postfix = "_METUnClustUp";
    //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
    proc_syst_pred["qcd"][sys_name]   = getQCDPred(sys_name);
    auto llb = getLLBPred(sys_name);
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  {
    sys_name = "metresDown";
    EstTools::jes_postfix = "_METUnClustDown";
    //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
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
      if(sPair.first.EndsWith("Down")) continue; // ignore down: processed at the same time as up
      vector<Quantity> uncs;

      if(sPair.first.EndsWith("Up")){
        auto varup = sPair.second / nominal_pred;
        auto name_down = TString(sPair.first).ReplaceAll("Up", "Down");
        auto vardown = proc_syst_pred[bkg].at(name_down) / nominal_pred;
        uncs = Quantity::combineUpDownUncs(varup, vardown);
      }else{
        uncs = sPair.second / nominal_pred;
      }

      unsigned ibin = 0;
      for (auto &cat_name : config.categories){
        auto &cat = config.catMaps.at(cat_name);
        for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
          auto xlow = toString(cat.bin.plotbins.at(ix), 0);
          auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
          auto binname = "bin_" + cat_name + "_" + cat.bin.var + xlow + "to" + xhigh;
          auto uncType = TString(sPair.first).ReplaceAll("Up", ""); // get rid of "up"
//          outfile << binname << "\t" << uncType << "\t" << bkg << "\t" << uncs.at(ibin).value << endl;
          double val = uncs.at(ibin).value;
          if (val>2 || std::isnan(val)) {
            cout << "Invalid unc, set to 100%: " << binname << "\t" << uncType << "\t" << bkg << "\t" << uncs.at(ibin).value << endl;
            val = 2;
          }else if (val<0.5){
            cout << "Invalid unc, set to -100%: " << binname << "\t" << uncType << "\t" << bkg << "\t" << uncs.at(ibin).value << endl;
            val = 0.001;
          }
          outfile << binname << "\t" << uncType << "\t" << bkg << "\t" << val << endl;
          ++ibin;
        }
      }
    }
  }

  outfile.close();

  cout << "Done!" << endl;

}
