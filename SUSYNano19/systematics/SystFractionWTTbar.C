/*
 * Znunu.C
 *
 *  Created on: Oct 23, 2019
 *      Author: mkilpatr
 */

#include <fstream>

//#include "Syst_SR_Parameters.hh"
#include "Syst_LowMET_Parameters.hh"

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
  z.pred2018();
  z.printYields();
  return z.yields.at("_TF");
}

vector<Quantity> getQCDPred(){
  auto qcdcfg = qcdConfig2018();
  QCDEstimator q(qcdcfg);
  q.runBootstrapping = false;
  q.pred2018();
  q.printYields();
  return q.yields.at("_TF");
}

map<TString, vector<Quantity>> getLLBPred(){
  auto llbcfg = lepConfig2018();
  LLBEstimator l(llbcfg);
  l.pred2018();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));

  return {
    {"ttbarplusw", l.yields.at("_TF")},
    {"ttZ",        l.yields.at("ttZ-sr")},
    {"diboson",    l.yields.at("diboson-sr")},
  };
}


void SystFractionWTTbar(std::string outfile_path = "values_unc_val_wtopfrac.conf"){

  vector<TString> bkgnames  = {"ttbarplusw"};
  map<TString, map<TString, vector<Quantity>>> proc_syst_pred; // {proc: {syst: yields}}
  for (auto &bkg : bkgnames){
    proc_syst_pred[bkg] = map<TString, vector<Quantity>>();
  }

  inputdir = "/uscms/home/hqu/nobackup/trees/20180206_lepSF";

  // nominal
  {
    sys_name = "nominal";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // ttbarNorm +20%
  {
    sys_name = "ttbarNorm";
    mcwgt = "weight*((process==2)*1.2+(process!=2)*1.0)";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // wjetsNorm +20%
  {
    sys_name = "wjetsNorm";
    mcwgt = "weight*((process==3)*1.2+(process!=3)*1.0)";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  cout << "\n\n Write unc to " << outfile_path << endl;
  ofstream outfile(outfile_path);
  auto config = lepConfig2018();

  for (auto &bkg : bkgnames){
    auto nominal_pred = proc_syst_pred[bkg]["nominal"];
    for (auto &sPair : proc_syst_pred[bkg]){
      if(sPair.first=="nominal") continue;
      if(sPair.first.EndsWith("_DOWN")) continue; // ignore down: processed at the same time as up
      vector<Quantity> uncs;

      if(sPair.first.EndsWith("_UP")){
        auto varup = sPair.second / nominal_pred;
        auto name_down = TString(sPair.first).ReplaceAll("_UP", "_DOWN");
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
          auto uncType = TString(sPair.first).ReplaceAll("_UP", ""); // get rid of "up"
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
