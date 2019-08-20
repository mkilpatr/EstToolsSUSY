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

vector<Quantity> getQCDPred(){
  auto qcdcfg = qcdConfig();
  QCDEstimator q(qcdcfg);
  q.runBootstrapping = false;
  q.pred();
  q.printYields();
  return q.yields.at("_TF");
}

map<TString, vector<Quantity>> getLLBPred(){
  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.predAllEras();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));

  return {
    {"ttbarplusw", l.yields.at("_TF")},
    {"ttZ",        l.yields.at("ttZ-sr")},
    {"diboson",    l.yields.at("diboson-sr")},
  };
}


void SystBTag(std::string outfile_path = "values_unc_btag.conf"){

  vector<TString> bkgnames  = {"diboson", "ttZ", "ttbarplusw"};
  map<TString, map<TString, vector<Quantity>>> proc_syst_pred; // {proc: {syst: yields}}
  for (auto &bkg : bkgnames){
    proc_syst_pred[bkg] = map<TString, vector<Quantity>>();
  }

  //inputdir = "/uscms_data/d3/hqu/trees/20170207_syst/others";
  // nominal
  {
    sys_name = "nominal";
    //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
    //proc_syst_pred["qcd"][sys_name]   = getQCDPred();
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // btag - heavy up
  {
    sys_name = "b_heavy_Up";
    btagwgt = "BTagWeight_Up";
    //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
    //proc_syst_pred["qcd"][sys_name]   = getQCDPred();
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // btag - heavy down
  {
    sys_name = "b_heavy_Down";
    btagwgt = "BTagWeight_Down";
    //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
    //proc_syst_pred["qcd"][sys_name]   = getQCDPred();
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  //// btag - light up
  //{
  //  sys_name = "b_light_Up";
  //  btagwgt = "BTagWeightLight_Up";
  //  //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
  //  //proc_syst_pred["qcd"][sys_name]   = getQCDPred();
  //  auto llb = getLLBPred();
  //  for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  //}

  //// btag - light down
  //{
  //  sys_name = "b_light_Down";
  //  btagwgt = "BTagWeightLight_Down";
  //  //proc_syst_pred["znunu"][sys_name] = getZnunuPred();
  //  //proc_syst_pred["qcd"][sys_name]   = getQCDPred();
  //  auto llb = getLLBPred();
  //  for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  //}

  cout << "\n\n Write unc to " << outfile_path << endl;
  ofstream outfile(outfile_path);
  auto config = lepConfig();

  for (auto &bkg : bkgnames){
    auto nominal_pred = proc_syst_pred[bkg]["nominal"];
    for (auto &sPair : proc_syst_pred[bkg]){
      if(sPair.first=="nominal") continue;
      if(sPair.first.EndsWith("_Down")) continue; // ignore down: processed at the same time as up
      vector<Quantity> uncs;

      if(sPair.first.EndsWith("_Up")){
        auto varup = sPair.second / nominal_pred;
        auto name_down = TString(sPair.first).ReplaceAll("_Up", "_Down");
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
          auto uncType = TString(sPair.first).ReplaceAll("_Up", ""); // get rid of "up"
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
