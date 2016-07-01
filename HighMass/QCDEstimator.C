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

  z.plotDataMC({"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr", "znunu-cr", "qcd-cr-withveto"}, "data-cr", false);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

