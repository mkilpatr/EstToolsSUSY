#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void srYields(){

  auto config = srConfig();
  BaseEstimator z(config);
  z.calcYields();
  z.printYields();

//  z.sumYields({"ttbar","ttW", "tW", "wjets"}, "LLB");
//  z.sumYields({"qcd", "diboson", "ttZ", "ttW", "tW", "znunu", "wjets", "ttbar"}, "Total BKG");
//  z.printYieldsTable({"LLB", "znunu", "qcd", "ttZ", "diboson", "Total BKG", "T2fbd_500_420", "T2fbd_500_450", "T2fbd_500_480", "T2tt_450_250", "T2tt_700_400", "T2tt_1100_1", "T2bW_550_350", "T2bW_850_1"});
//  z.printYieldsTable({"LLB", "znunu", "qcd", "ttZ", "diboson", "Total BKG"});

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotSigVsBkg(){
  auto config = srConfig();
  BaseEstimator z(config);

  LOG_YMIN = 0.1;

  vector<TString> mc_samples = {"qcd", "diboson", "ttZ", "ttW", "tW", "znunu", "wjets", "ttbar"};
  vector<TString> signal_samples_lm = {"T2fbd_500_420", "T2fbd_500_450", "T2fbd_500_480", "T2tt_450_250", "T2tt_450_350"};
  vector<TString> signal_samples_hm = {"T2tt_450_250", "T2tt_700_400", "T2tt_1100_1", "T2bW_550_350", "T2bW_850_1"};

//  vector<TString> signal_samples = {"T2fbd_500_420", "T2fbd_500_450", "T2fbd_500_480", "T2tt_450_250", "T2tt_700_400", "T2tt_1100_1", "T2bW_550_350", "T2bW_850_1"};

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
//    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.72); };
    z.plotSigVsBkg(cat.bin, mc_samples, category.Contains("hm_") ? signal_samples_hm : signal_samples_lm, cat, true, true);
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void dumpDC(){
  BaseConfig     config;
  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();

  BaseEstimator z(config);
  z.dumpDatacardConfig("/tmp/dc.conf");
}

void testOrthogonality(){
  auto config = srConfig();
  BaseEstimator z(config);
  z.testSROrthogonality();
}

