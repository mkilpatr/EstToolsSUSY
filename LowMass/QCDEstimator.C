#include "../EstMethods/QCDEstimator.hh"

#include "LMParameters.hh"

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

  z.plotDataMC({"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr", "znunu-cr", "qcd-cr-withveto"}, "data-cr", false);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void Yields(){

  auto config = qcdConfig();

//  config.samples.clear();

//  config.addSample("data-cr",     "Data",          "sr/met",             "1.0",       datasel + trigSR + vetoes + dphi_invert);
//  config.addSample("data-cr-old",     "Data",          "sr/met-old-trig",             "1.0",       datasel + trigSR + vetoes + dphi_invert);

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  z.calcYields();
  z.printYields();

}

