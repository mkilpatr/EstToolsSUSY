#include "../EstMethods/LLBEstimator.hh"
#include "SRParameters.hh"
#include "../utils/JsonHelper.h"

#include <algorithm>

using namespace EstTools;

/* Procedure:
 * Entry 0 is the norminal
 * Scale Uncertainty: take the envelop of entries {1, 2, 3, 4, 6, 8}
 * For NNPDF set:
 * Entries [10, 109] are the pdf variations (9 is nominal)
 * Take the RMS or [(84th) - (16th)]/2
 */

const unsigned SYSWGT_BEGIN = 0, SYSWGT_END = 110; // [BEGIN, END)

BaseConfig baseConfig(){
  BaseConfig config;
  config.inputdir = "/data/hqu/trees/20170205_pdfSyst/sr";
  config.outputdir = outputdir;

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}

class VarCalculator{
public:

  VarCalculator(unsigned low, unsigned high) : low_(low), high_(high){
    outputName_ = "pdf_var_LLB.json";
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void runVariations(){
    readNormalization();

    varTFs.clear();
    for (unsigned isys = low_; isys < high_; ++isys){
      auto tf = getTF(isys);
      varTFs[to_string(isys)] = tf;
    }
    JsonHelper::dumpJson(outputName_, json(varTFs));
  }

  // varTFs["isys"]: tf for the isys'th variation
  map<string, vector<double>> varTFs;

private:
  unsigned low_, high_; // range [low, high)
  string outputName_;

  map<std::string, vector<double>> reNormMap;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void readNormalization(){
    reNormMap.clear();

    BaseConfig config;
    config.inputdir = "/data/hqu/trees/20170205_pdfSyst";
    config.addSample("ttbar",       "t#bar{t}",      "sr/ttbar",        "weight", "");
    config.addSample("wjets",       "W+jets",        "sr/wjets",        "weight", "");

    for (const auto &s : config.samples){
      TH1* hsys = (TH1*)s.second.infile->Get("hsys");
      double nominal = hsys->GetBinContent(0);
      vector<double> norm;
      for (unsigned isys = SYSWGT_BEGIN; isys < SYSWGT_END; ++isys){
        norm.push_back(nominal/hsys->GetBinContent(isys));
      }
      reNormMap[s.first.Data()] = norm;
    }

  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  BaseConfig varConfig(TString varWgt){

    BaseConfig config;
    config.inputdir = "/data/hqu/trees/20170205_pdfSyst";
    config.outputdir = outputdir+"/LLB";

    config.sel = baseline;
    config.categories = srbins;
    config.catMaps = srCatMap();
    config.crCatMaps = lepCatMap();

    config.addSample("ttbar",          "t#bar{t}",      "sr/ttbar",        lepselwgt+"*"+varWgt,  datasel + trigSR + revert_vetoes);
    config.addSample("wjets",          "W+jets",        "sr/wjets",        lepselwgt+"*"+varWgt,  datasel + trigSR + revert_vetoes);
    config.addSample("tW",             "tW",            "sr/tW",           lepselwgt,             datasel + trigSR + revert_vetoes);
    config.addSample("ttW",            "ttW",           "sr/ttW",          lepselwgt,             datasel + trigSR + revert_vetoes);

    config.addSample("ttbar-sr",       "t#bar{t}",      "sr/ttbar",        lepvetowgt+"*"+varWgt, datasel + trigSR + vetoes);
    config.addSample("wjets-sr",       "W+jets",        "sr/wjets",        lepvetowgt+"*"+varWgt, datasel + trigSR + vetoes);
    config.addSample("tW-sr",          "tW",            "sr/tW",           lepvetowgt,            datasel + trigSR + vetoes);
    config.addSample("ttW-sr",         "ttW",           "sr/ttW",          lepvetowgt,            datasel + trigSR + vetoes);

    return config;
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::vector<double> getTF(int idx){
    cerr << "\n--->" << __func__  << "-- idx = " << idx << endl;

    TString syswgtvar = TString::Format("systweights[%d]",idx);
    double ttbarNorm = reNormMap.at("ttbar").at(idx);
    double wjetsNorm = reNormMap.at("wjets").at(idx);

    auto config = varConfig(syswgtvar);
    BaseEstimator z(config);
    z.calcYields();
    auto sr = z.yields.at("ttbar-sr")*ttbarNorm + z.yields.at("wjets-sr")*wjetsNorm + z.yields.at("tW-sr") + z.yields.at("ttW-sr");
    auto cr = z.yields.at("ttbar")*ttbarNorm + z.yields.at("wjets")*wjetsNorm + z.yields.at("tW") + z.yields.at("ttW");
    auto tf = sr/cr;
    cout << tf << endl;

    for (auto &s : config.samples){
      delete s.second.tree;
    }

    vector<double> tfval;
    for (auto &q : tf) tfval.push_back(std::max(q.value, 0.));
    return tfval;
  }
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};

// ---------------------
class VarReader{

public:

  void read(std::string input = "pdf_var_LLB.json"){
    json j;
    ifstream infile;
    infile.open(input);
    infile >> j;
    infile.close();
    cerr << "here" << endl;
//    auto tfMap = j.get< map<std::string, vector<double>> >();
    varTFs.clear();
    for (unsigned isys=SYSWGT_BEGIN; isys<SYSWGT_END; ++isys){
      cout << j.at(to_string(isys)) << endl;
      varTFs.push_back(j.at(to_string(isys)).get<vector<double>>());
    }
  }

  vector<vector<double>> varTFs;

};


class UncCalculator{

public:

  enum PdfUncType {MC, RMS, HESSIAN};

  UncCalculator(std::string input = "pdf_var_LLB.json"){
    VarReader r;
    r.read(input);
    varTFs = r.varTFs;
  }

  vector<double> calcPDFUnc(PdfUncType pdfuncType, unsigned i_begin=10, unsigned i_end=110){

    auto nominal_tf = varTFs.at(0);
    vector<double> relUncs;

    auto config = baseConfig();
    auto nbins = config.nbins();

    for (unsigned ibin=0; ibin<nbins; ++ibin){
      vector<double> ensemble;
      double nominal = nominal_tf.at(ibin);
      for (unsigned isys=i_begin; isys<i_end; ++isys){
        const auto &tfs = varTFs.at(isys);
        ensemble.push_back(tfs.at(ibin));
      }
      double unc = 0;
      switch (pdfuncType) {
        case MC:
          unc = getPDFUncMC(ensemble);
          break;
        case RMS:
          unc = getPDFUncRMS(ensemble);
          break;
        case HESSIAN:
          unc = getPDFUncHessian(ensemble, nominal);
          break;
        default:
          break;
      }
      relUncs.push_back(1+unc/nominal);
    }
    return relUncs;
  }

  vector<double> calcScaleUnc(vector<unsigned> indices = {1, 2, 3, 4, 6, 8}){
    auto nominal_tf = varTFs.at(0);
    vector<double> relUncs;

    auto config = baseConfig();
    auto nbins = config.nbins();

    for (unsigned ibin=0; ibin<nbins; ++ibin){
      vector<double> ensemble;
      double nominal = nominal_tf.at(ibin);
      for (auto idx : indices){
        const auto &tfs = varTFs.at(idx);
        ensemble.push_back(tfs.at(ibin));
        cerr << "~~~" << ibin << "~~~" << tfs.at(ibin) << endl;
      }
      double unc = getScaleUnc(ensemble);
      relUncs.push_back(1+unc/nominal);
    }
    return relUncs;

  }

  void writeUncFiles(vector<double> uncs, string uncType, string base_filename = "values_unc_", string sample = "ttbarplusw"){
    string fn = base_filename + uncType + "_LLB.conf";
    ofstream outfile;
    outfile.open(fn);

    unsigned ibin = 0;
    auto config = baseConfig();
    for (auto &cat_name : config.categories){
      auto &cat = config.catMaps.at(cat_name);
      for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
        auto xlow = toString(cat.bin.plotbins.at(ix), 0);
        auto xhigh = (ix==cat.bin.nbins-1) ? "inf" : toString(cat.bin.plotbins.at(ix+1), 0);
        auto binname = "bin_" + cat_name + "_" + cat.bin.var + xlow + "to" + xhigh;
        outfile << binname << "\t" << sample+"_"+uncType << "\t" << sample << "\t" << (uncs.at(ibin)>2 || std::isnan(uncs.at(ibin)) ? 2 : uncs.at(ibin)) << endl;
        ++ibin;
      }

    }

    outfile.close();

  }

  vector<vector<double>> varTFs;

private:
  double getPDFUncMC(vector<double> vec){
    std::sort(vec.begin(), vec.end());
    unsigned lower = vec.size()*.16-1;
    unsigned upper = vec.size()*.84-1;
    double unc = (vec.at(upper) - vec.at(lower))/2;
    return unc;
  }

  double getPDFUncRMS(const vector<double> &vec){
    double avg = 0;
    for (const auto &v : vec) avg += v;
    avg /= vec.size();

    double sumsq = 0;
    for (const auto &v : vec) sumsq += (v-avg)*(v-avg);
    double unc = sqrt(sumsq/(vec.size()-1));
    return unc;
  }

  double getPDFUncHessian(const vector<double> &vec, double nominal){
    double sumsq = 0;
    for (const auto &v : vec) sumsq += (v-nominal)*(v-nominal);
    double unc = sqrt(sumsq);
    return unc;
  }

  double getScaleUnc(const vector<double> &vec){
    auto mm = std::minmax_element(vec.begin(), vec.end());
    auto unc = (*mm.second-*mm.first)/2;
    return unc;
  }

};


void PDFUncertainties(){
  UncCalculator *unc = new UncCalculator();

  auto pdfunc = unc->calcPDFUnc(UncCalculator::MC);
  unc->writeUncFiles(pdfunc, "pdfunc");

  auto pdfunc_rms = unc->calcPDFUnc(UncCalculator::RMS);
  unc->writeUncFiles(pdfunc_rms, "pdfunc_rms");

//  auto pdfunc_hessian = unc->calcPDFUnc(UncCalculator::HESSIAN);
//  unc->writeUncFiles(pdfunc_hessian, "pdfunc_hessian");

  auto scaleunc = unc->calcScaleUnc();
  unc->writeUncFiles(scaleunc, "scaleunc");
}


void PDFCalcLLB(){
  VarCalculator v(SYSWGT_BEGIN, SYSWGT_END);
  v.runVariations();
  PDFUncertainties();
}

