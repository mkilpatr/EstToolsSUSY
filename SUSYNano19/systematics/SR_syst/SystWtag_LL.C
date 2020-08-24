/*
 *
 *  Created on: Oct 23, 2019
 *      Author: mkilpatr
 */

#include <fstream>

#include "../Syst_SR_Parameters.hh"

#include "../../../EstMethods/LLBEstimator.hh"

using namespace EstTools;

void SystWtag_LL(){

  std::string bins = "sb";
  std::string mc = "";
       if(EstTools::region.Contains("CR"))     bins = "cb";
  else if(EstTools::region.Contains("LowMET")) bins = "LowMET";
       if(EstTools::region.Contains("2016"))   mc = "_2016";
  else if(EstTools::region.Contains("2017"))   mc = "_2017";
  else if(EstTools::region.Contains("2018"))   mc = "_2018";

  std::string outfile_path = "values_unc_" + bins + mc + (string)binMap_+ "_ll_wtag.conf";

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
    sys_name = "eff_wtag_Up";
    sdmvawgt = "(Stop0l_DeepAK8_SFWeight_w_up)"; 
    cout << "\n\n ====== Using weights " << sdmvawgt << " and " << sdmvawgt << " and " << restopwgt << "======\n\n";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  // wtag down
  {
    sys_name = "eff_wtag_Down";
    sdmvawgt = "(Stop0l_DeepAK8_SFWeight_w_dn)"; 
    cout << "\n\n ====== Using weights " << sdmvawgt << " and " << sdmvawgt << " and " << restopwgt << "======\n\n";
    auto llb = getLLBPred();
    for (auto &p : llb) proc_syst_pred[p.first][sys_name] = p.second;
  }

  cout << "\n\n Write unc to " << outfile_path << endl;
  ofstream outfile(outfile_path);
  auto config = lepConfig();
         if(EstTools::region.Contains("2016and2017")) config = lepConfig2016and2017();
  else if(EstTools::region.Contains("2016")) config = lepConfig2016();
  else if(EstTools::region.Contains("2017")) config = lepConfig2017();
  else if(EstTools::region.Contains("2018")) config = lepConfig2018();

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
        auto &cat = EstTools::region.Contains("CR") ? config.crCatMaps.at(cat_name) : config.catMaps.at(cat_name);
        for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
          auto xlow = toString(cat.bin.plotbins.at(ix), 0);
          auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
          auto binname = EstTools::region.Contains("CR") ? "bin_lepcr_" + TString(lepcrMapping.at(cat_name)) + "_" + cat.bin.var + xlow + "to" + xhigh : "bin_" + cat_name + "_" + cat.bin.var + xlow + "to" + xhigh;
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
