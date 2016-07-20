#include "../EstMethods/QCDEstimator.hh"

#include "HMParameters.hh"

using namespace EstTools;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> QCDPred(){
  auto config = qcdConfig();

  QCDEstimator z(config);

  z.runBootstrapping = false;

  z.pred();
  z.naiveTF();
  z.printYields();

  return z.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotQCDCR(){
  auto config = qcdConfig();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  z.plotDataMC({"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr", "znunu-cr", "qcd-withveto-cr"}, "data-cr", false);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotQCDInclusive(){
  auto config = qcdConfig();

  config.sel = "njets>=2 && met>250 && metovsqrtht>10";
//  config.addSample("qcd",  "QCD",      "qcd-4bd/qcd",          qcdvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd",  "QCD",      "qcd-old",          wgtvar,  datasel + trigSR + vetoes + dphi_invert);

//  config.addSample("qcd",  "QCD",      "qcd-std/qcd",          qcdvetowgt,  datasel + trigSR + vetoes + dphi_invert);


  BaseEstimator z(config);

  vector<TString> mc_samples = {"qcd", "ttbar-cr", "wjets-cr", "tW-cr"};
  TString data_sample = "data-cr";

  map<TString, BinInfo> varDict {
//    {"met",       BinInfo("met", "#slash{E}_{T}", 16, 0, 800, "GeV")},
    {"ht",        BinInfo("ht",  "H_{T}", 100, 0, 2000, "GeV")}
//    {"j1chef",    BinInfo("j1chEnFrac",  "j1chEnFrac", 20, 0, 1, "GeV")},
//    {"njets",     BinInfo("njets", "N_{j}", 12, -0.5, 11.5)},
//    {"nt",        BinInfo("nsdtoploose", "N_{t}", 2, -0.5, 1.5)},
//    {"nw",        BinInfo("nsdwloose", "N_{W}", 2, -0.5, 1.5)},
//    {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
//    {"nbjets",    BinInfo("nbjets",  "N_{B}^{medium}", 5, -0.5, 4.5)},
//    {"dphij1met", BinInfo("dphij1met", "#Delta#phi(j_{1},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij2met", BinInfo("dphij2met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"dphij3met", BinInfo("dphij3met", "#Delta#phi(j_{2},#slash{E}_{T})", 32, 0, 3.2)},
//    {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
//    {"metovsqrtht",BinInfo("metovsqrtht", "#slash{E}_{T}/#sqrt{H_{T}}", 10, 0, 20)},
//    {"dphij1lmet",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
//    {"njl",       BinInfo("njl", "N_{j}^{ISR}", 5, -0.5, 4.5)},
//    {"j1lpt",     BinInfo("j1lpt", "p_{T}(j_{1}^{ISR}) [GeV]", 20, 0, 1000)},
//    {"csvj1pt",   BinInfo("csvj1pt", "p_{T}(b_{1}) [GeV]", 8, 20, 100)}
  };



  for (auto &var : varDict){
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
