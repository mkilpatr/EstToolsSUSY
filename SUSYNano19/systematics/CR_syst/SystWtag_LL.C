/*
 *
 *  Created on: Oct 23, 2019
 *      Author: mkilpatr
 */

#include <fstream>

#include "../Syst_CR_Parameters.hh"

#include "../../../EstMethods/LLBEstimator.hh"

using namespace EstTools;

map<TString, vector<Quantity>> getLLBPred(){
  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.pred();
  l.printYields();
  Quantity::removeNegatives(l.yields.at("ttZ-sr"));
  Quantity::removeNegatives(l.yields.at("diboson-sr"));
  vector<Quantity> yields = l.yields.at("ttbarplusw");
  llbcfg.reset();
  
  return {
    {"ttbarplusw", yields},
    //{"ttZ",        l.yields.at("ttZ-sr")},
    //    //{"diboson",    l.yields.at("diboson-sr")},
    };
}


void SystWtag_LL(std::string outfile_path = "values_unc_cb_ll_wtag.conf"){

  vector<TString> bkgnames  = {"ttbarplusw"};
  map<TString, map<TString, vector<Quantity>>> proc_syst_pred; // {proc: {syst: yields}}
  for (auto &bkg : bkgnames){
    proc_syst_pred[bkg] = map<TString, vector<Quantity>>();
  }

  //inputdir = "/data/hqu/trees/0221_wtopSyst";

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
      if(sPair.first.EndsWith("_Down")) continue; // ignore down: processed at the same time as up
      std::pair<vector<Quantity>, vector<Quantity>> uncs;
      vector<Quantity> uncs_Up, uncs_Down;

      if(sPair.first.EndsWith("_Up")){
        auto varup = sPair.second / nominal_pred;
        auto name_Down = TString(sPair.first).ReplaceAll("_Up", "_Down");
        auto vardown = proc_syst_pred[bkg].at(name_Down) / nominal_pred;
        uncs = Quantity::combineUpDownSepUncs(varup, vardown);
	uncs_Up = uncs.first;
	uncs_Down = uncs.second;
      } else{
        uncs_Down = sPair.second / nominal_pred;
      }

      unsigned ibin = 0;
      for (auto &cat_name : config.categories){
        auto &cat = config.crCatMaps.at(cat_name);
        for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
          auto xlow = toString(cat.bin.plotbins.at(ix), 0);
          auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
	  auto binname = "bin_lepcr_" + TString(lepcrMapping.at(cat_name)) + "_" + cat.bin.var + xlow + "to" + xhigh;
          auto uncType_Up   = TString(sPair.first); 
          auto uncType_Down = TString(sPair.first).ReplaceAll("_Up", "_Down"); 
	  if (std::isnan(uncs_Up.at(ibin).value)) {
            cout << "Invalid unc, set to 100%: " << binname << "\t" << uncType_Up << "\t" << bkg << "\t" << uncs_Up.at(ibin).value << endl;
            uncs_Up.at(ibin).value = 2;
          }
	  if (std::isnan(uncs_Down.at(ibin).value)) {
            cout << "Invalid unc, set to 100%: " << binname << "\t" << uncType_Down << "\t" << bkg << "\t" << uncs_Down.at(ibin).value << endl;
            uncs_Down.at(ibin).value = 0.001;
          }
	  outfile << binname << "\t" << uncType_Up << "\t" << bkg << "\t" << uncs_Up.at(ibin).value << endl;
          outfile << binname << "\t" << uncType_Down << "\t" << bkg << "\t" << uncs_Down.at(ibin).value << endl;
          ++ibin;
        }
      }
    }
  }

  outfile.close();

  cout << "Done!" << endl;

}
