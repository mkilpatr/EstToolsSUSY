#include "../EstMethods/LLBEstimator.hh"
#include "HMParameters.hh"
#include "../utils/JsonHelper.h"

using namespace EstTools;

// Procedure: Entries 9-108 in the systweights vector correspond to pdf variations at fixed alpha_S, 109 and 110 correspond to variations of alpha_S. For the pdf variations, we take the standard deviation of the 100 variations, then add in quadrature the maximum alpha_S variation. In order to factor out the effects on the cross section, yields should be normalized to the inclusive yield. To be done properly, input trees should have no pre-selection
// Entry 0 is the nominal
const unsigned SYSWGT_BEGIN = 0, SYSWGT_END = 111; // [BEGIN, END)


class VarCalculator{
public:

  VarCalculator(unsigned low, unsigned high) : low_(low), high_(high){
    outputName_ = "output_"+to_string(low_)+"to"+to_string(high_)+"_yields.json";
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void runVariations(){
    readNormalization();

    varYields.clear();
    for (unsigned isys = low_; isys < high_; ++isys){
      auto tf = getYields(isys);
      varYields[to_string(isys)] = tf;
    }
    JsonHelper::dumpJson(outputName_, json(varYields));
  }

  // varYields["isys"]: tf for the isys'th variation
  map<string, vector<double>> varYields;

private:
  unsigned low_, high_; // range [low, high)
  string outputName_;

  map<std::string, vector<double>> reNormMap;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void readNormalization(){
    reNormMap.clear();

    BaseConfig config;
    config.inputdir = "/tmp/syst_trees";
    config.addSample("ttZ",       "ttZ",      "sr/ttZ",        "weight", "");

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

    auto config = lepConfig();
    config.inputdir = "/tmp/syst_trees";
    config.samples.clear();
    config.crCatMaps.clear();

    config.addSample("ttZ",         "ttZ",           "sr/ttZ",             lumistr+"*weight*"+varWgt,            datasel + trigSR + " && nvetolep==0 && nvetotau==0");

    return config;
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::vector<double> getYields(int idx){
    cerr << "\n--->" << __func__  << "-- idx = " << idx << endl;

    TString syswgtvar = TString::Format("systweights[%d]",idx);

    vector<Quantity> yields;

    auto config = varConfig(syswgtvar);
    BaseEstimator z(config);
    z.calcYields();
    z.printYields();
    for (const auto &samp : config.samples){
      double norm = reNormMap.at(samp.first.Data()).at(idx);
      cout << "--> norm: " << norm << endl;
      if (yields.empty())
        yields = z.yields.at(samp.first) * norm;
      else
        yields = yields + z.yields.at(samp.first) * norm;
    }

    for (auto &s : config.samples){
      delete s.second.tree;
    }

    vector<double> rlt;
    for (auto q:yields) rlt.push_back(q.value);
    cout << rlt << endl;

    return rlt;
  }

};

void PDFCalcTTZ(unsigned low, unsigned high){
  VarCalculator v(low, high);
  v.runVariations();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class VarReader{

public:

  void read(std::string input = "yields.json"){
    json j;
    ifstream infile;
    infile.open(input);
    infile >> j;
    infile.close();
//    cerr << "here" << endl;
//    auto tfMap = j.get< map<std::string, vector<double>> >();
    varYields.clear();
    for (unsigned isys=SYSWGT_BEGIN; isys<SYSWGT_END; ++isys){
//      cout << j.at(to_string(isys)) << endl;
      varYields.push_back(j.at(to_string(isys)).get<vector<double>>());
    }
  }

  vector<vector<double>> varYields;

};


class UncCalculator{

public:

  enum PdfUncType {MC, RMS, HESSIAN};

  UncCalculator(std::string input = "yields.json"){
    VarReader r;
    r.read(input);
    varYields = r.varYields;
  }

  vector<double> calcPDFUnc(PdfUncType pdfuncType, unsigned i_begin=9, unsigned i_end=108){

    auto nominal_yields = varYields.at(0);
    vector<double> relUncs;

    auto config = lepConfig();
    auto nbins = config.nbins();

    for (unsigned ibin=0; ibin<nbins; ++ibin){
      vector<double> ensemble;
      double nominal = nominal_yields.at(ibin);
      for (unsigned isys=i_begin; isys<i_end; ++isys){
        const auto &yld = varYields.at(isys);
        ensemble.push_back(yld.at(ibin));
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
    auto nominal_yields = varYields.at(0);
    vector<double> relUncs;

    auto config = lepConfig();
    auto nbins = config.nbins();

    for (unsigned ibin=0; ibin<nbins; ++ibin){
      vector<double> ensemble;
      double nominal = nominal_yields.at(ibin);
      for (auto idx : indices){
        const auto &tfs = varYields.at(idx);
        ensemble.push_back(tfs.at(ibin));
//        cerr << "~~~" << ibin << "~~~" << tfs.at(ibin) << endl;
      }
      double unc = getScaleUnc(ensemble);
      relUncs.push_back(1+unc/nominal);
    }
    return relUncs;

  }

  vector<double> calcAlphaSUnc(vector<unsigned> indices = {109, 110}){
    auto nominal_yields = varYields.at(0);
    vector<double> relUncs;

    auto config = lepConfig();
    auto nbins = config.nbins();

    for (unsigned ibin=0; ibin<nbins; ++ibin){
      vector<double> ensemble;
      double nominal = nominal_yields.at(ibin);
      for (auto idx : indices){
        const auto &tfs = varYields.at(idx);
        ensemble.push_back(tfs.at(ibin));
        cerr << "~~~" << ibin << "~~~" << tfs.at(ibin) << endl;
      }
      double unc = getAlphaSUnc(nominal, ensemble);
      relUncs.push_back(1+unc/nominal);
    }
    return relUncs;

  }


  void writeUncFiles(vector<double> uncs, string uncType = "pdfscale", string base_filename = "values_unc_", string sample = "rare"){
    string fn = base_filename + uncType + ".conf";
    ofstream outfile;
    outfile.open(fn);

    unsigned ibin = 0;
    auto config = lepConfig();
    for (auto &cat_name : config.categories){
      auto &cat = config.crCatMaps.at(cat_name);
      for (unsigned ix = 0; ix < cat.bin.nbins; ++ix){
        auto xlow = cat.bin.plotbins.at(ix);
        auto binname = "bin_" + toString(xlow,0) + "_" + cat_name;
        outfile << binname << "\t" << sample+"_"+uncType << "\t" << sample << "\t" << (uncs.at(ibin)>2 ? 2 : uncs.at(ibin)) << endl;
        ++ibin;
      }

    }

    outfile.close();

  }

  vector<vector<double>> varYields;

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

  double getAlphaSUnc(double nominal, const vector<double> &vec){
    double maxunc = -1;
    for (auto v : vec){
      double df = fabs(v-nominal);
      if (df>maxunc) maxunc = df;
    }
    return maxunc;
  }

};



void PDFUncertainties(){
  UncCalculator *unc = new UncCalculator();

  auto pdfunc = unc->calcPDFUnc(UncCalculator::MC);
  unc->writeUncFiles(pdfunc, "pdfunc");

  auto pdfunc_rms = unc->calcPDFUnc(UncCalculator::RMS);
  unc->writeUncFiles(pdfunc_rms, "pdfunc_rms");

  auto scaleunc = unc->calcScaleUnc();
  unc->writeUncFiles(scaleunc, "scaleunc");

  auto asunc = unc->calcAlphaSUnc();
  unc->writeUncFiles(asunc, "alphasunc");

  auto sqr = [](double v){return (v-1)*(v-1);};

  vector<double> combineduncs;
  for (unsigned i=0; i<pdfunc.size(); ++i){
    double u = std::sqrt(sqr(pdfunc.at(i)) + sqr(scaleunc.at(i)) + sqr(asunc.at(i))) + 1;
    combineduncs.push_back(u);
  }
  unc->writeUncFiles(combineduncs, "pdfscale");

}

