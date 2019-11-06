/*
 *
 *  Created on: Oct 23, 2019
 *      Author: mkilpatr
 */

#include <fstream>

#include "Syst_SR_Parameters.hh"
//#include "Syst_LowMET_Parameters.hh"

#include "../../EstMethods/LLBEstimator.hh"

using namespace EstTools;

map<TString, vector<Quantity>> getLLBPred(){
  auto llbcfg = lepConfig();
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
    //    //{"diboson",    l.yields.at("diboson-sr")},
    //      };
}


void SystW_LL(std::string outfile_path = "values_unc_ll_wtag.conf"){

  vector<TString> bkgnames  = {"ttbarplusw"};
  map<TString, map<TString, vector<Quantity>>> proc_syst_pred; // {proc: {syst: yields}}
  for (auto &bkg : bkgnames){
    proc_syst_pred[bkg] = map<TString, vector<Quantity>>();
  }

  //inputdir = "/data/hqu/trees/20170221_wtopSyst";

  // nominal
  {
    sys_name = "nominal";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // wtag up
  {
    sys_name = "eff_wtag_err_Up";
    wtagwgt = "(WtagSF + WtagSFErr)"; 
    cout << "\n\n ====== Using weights " << wtagwgt << " and " << sdmvawgt << " and " << restopwgt << "======\n\n";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // wtag down
  {
    sys_name = "eff_wtag_err_Down";
    wtagwgt = "(WtagSF - WtagSFErr)"; 
    cout << "\n\n ====== Using weights " << wtagwgt << " and " << sdmvawgt << " and " << restopwgt << "======\n\n";
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
      if(sPair.first.EndsWith("_DOWN")) continue; // ignore down: processed at the same time as up
      vector<Quantity> uncs;
      
      if(sPair.first.EndsWith("_UP")){
        auto varup = sPair.second / nominal_pred;
        auto name_down = TString(sPair.first).ReplaceAll("_UP", "_DOWN");
        auto vardown = proc_syst_pred[bkg].at(name_down) / nominal_pred;
        uncs = Quantity::combineUpDownUncs(varup, vardown);
      } else if(sPair.first.EndsWith("err")){
        auto varerr = sPair.second / nominal_pred;
        uncs = Quantity::CombineErrUncs(varerr);
      } else{
        uncs = sPair.second / nominal_pred;
      }

	cout << "Uncertainty: " << uncs << endl;
      unsigned ibin = 0;
      for (auto &cat_name : config.categories){
        auto &cat = config.catMaps.at(cat_name);
        for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
          auto xlow = toString(cat.bin.plotbins.at(ix), 0);
          auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
          auto binname = "bin_" + cat_name + "_" + cat.bin.var + xlow + "to" + xhigh;
	  auto uncType = TString(sPair.first).ReplaceAll("_Up", ""); // get rid of "up"
	  uncType = TString(sPair.first).ReplaceAll("_err", ""); // get rid of "err"
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
