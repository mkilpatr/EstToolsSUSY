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


void SystElectron(std::string outfile_path = "values_unc_electron.conf"){

  vector<TString> bkgnames  = {"qcd", "ttbarplusw"};
  map<TString, map<TString, vector<Quantity>>> proc_syst_pred; // {proc: {syst: yields}}
  for (auto &bkg : bkgnames){
    proc_syst_pred[bkg] = map<TString, vector<Quantity>>();
  }

  //inputdir = "/data/hqu/ramdisk/20170207_syst/others";
  // nominal
  {
    sys_name = "nominal";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred();
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // ele - up
  {
    sys_name = "eff_e_err_Up";
    elewgt = "(ElectronVetoSF + ElectronVetoSFErr)";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred();
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // ele - down
  {
    sys_name = "eff_e_err_Down";
    elewgt = "(ElectronVetoSF - ElectronVetoSFErr)";
    proc_syst_pred["qcd"][sys_name]   = getQCDPred();
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  cout << "\n\n Write unc to " << outfile_path << endl;
  ofstream outfile(outfile_path);
  auto config = lepConfig();

  for (auto &bkg : bkgnames){
    auto nominal_pred = proc_syst_pred[bkg]["nominal"];
    for (auto &sPair : proc_syst_pred[bkg]){
      if(sPair.first=="nominal") continue;
      if(sPair.first.EndsWith("_Down")) continue; // ignore down: processed at the same time as up
      vector<Quantity> uncs_up, uncs_down;
      vector<Quantity> varup, vardown;

      if(sPair.first.EndsWith("_Up")){
        if(bkg == "ttbarplusw") varup = nominal_pred / sPair.second;
	else 			varup = sPair.second / nominal_pred;
        auto name_down = TString(sPair.first).ReplaceAll("_Up", "_Down");
        if(bkg == "ttbarplusw") vardown = nominal_pred / proc_syst_pred[bkg].at(name_down);
	else 			vardown = proc_syst_pred[bkg].at(name_down) / nominal_pred;
        uncs_up = Quantity::combineUpUncs(varup);
        uncs_down = Quantity::combineDownUncs(vardown);
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
          auto uncType_up   = TString(sPair.first); // get rid of "up"
          auto uncType_down = TString(sPair.first).ReplaceAll("_Up", "_Down"); // get rid of "up"
          //double val = uncs.at(ibin).value;
          //if (val>2 || std::isnan(val)) {
          //  cout << "Invalid unc, set to 100%: " << binname << "\t" << uncType << "\t" << bkg << "\t" << uncs.at(ibin).value << endl;
          //  val = 2;
          //}else if (val<0.5){
          //  cout << "Invalid unc, set to -100%: " << binname << "\t" << uncType << "\t" << bkg << "\t" << uncs.at(ibin).value << endl;
          //  val = 0.001;
          //}
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
