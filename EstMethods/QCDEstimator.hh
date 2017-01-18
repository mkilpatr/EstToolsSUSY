#ifndef ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_
#define ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "../utils/Estimator.hh"
#include "../utils/HistGetter.hh"

using namespace std;
#endif

namespace EstTools{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<Quantity> getYieldVectorManual(const std::unique_ptr<TTree>& intree, TString wgtvar, TString sel, const BinInfo &bin, int nBootstrapping){
  assert(intree);

#ifdef DEBUG_
  auto start = chrono::steady_clock::now();
#endif

  auto metGetter = HistogramGetter(bin.var, bin.var, bin.label, bin.nbins, bin.plotbins.data());
  metGetter.setUnderOverflow(false, true);
  metGetter.setNBS(nBootstrapping);
  auto htmp = metGetter.getHistogramManual(intree.get(), sel, wgtvar, "htmp");

  vector<Quantity> yields;
  for (unsigned i=0; i<bin.nbins; ++i)
  yields.push_back(getHistBin(htmp, i+1));

#ifdef DEBUG_
  stringstream ss;
  ss << intree->GetTitle() << ": " << wgtvar + "*(" + sel + ")" << ", " << bin.var << ", entries=" << htmp->GetEntries() << endl
       << "  --> " << yields << endl;

  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  ss << chrono::duration <double, milli> (diff).count() << " ms" << endl;

  cerr << ss.str();
#endif

  return yields;
}


class QCDEstimator : public BaseEstimator {
public:
  QCDEstimator() {}
  QCDEstimator(TString outputdir, TString outputfile = "QCD_output.root") :
    BaseEstimator(outputdir, outputfile) {}
  QCDEstimator(const BaseConfig &config) :
    BaseEstimator(config) {}

  virtual ~QCDEstimator() {}

  virtual vector<Quantity> getYieldVectorWrapper(const Sample& sample, TString sel, const BinInfo &bin, int nBootstrapping=0) override{
    std::unique_ptr<TFile> infile(new TFile(sample.filepath));
    std::unique_ptr<TTree> intree(dynamic_cast<TTree*>(infile->Get(sample.treename)));
    intree->SetTitle(sample.name);
    vector<Quantity> yields;
    if (nBootstrapping==0){
      yields = getYieldVector(intree, sample.wgtvar, sel, bin);
    }else{
      yields = getYieldVectorManual(intree, sample.wgtvar, sel, bin, 50);
    }
    intree.reset();
    infile.reset();
    return yields;
  }

  void naiveTF(){
    yields["_NaiveTF"] = yields.at("qcd-withveto-sr") / yields.at("qcd-withveto-cr");
  }

  void calcTF(){
    // calculate transfer factors

    cerr << "\n--->" << __func__ << endl;

    doYieldsCalc({"qcd-sr", "qcd-cr"}, runBootstrapping ? 50 : 0);

    // FIXME
    for (auto &q : yields.at("qcd-cr")){
      if (q.value<0.0001){
        cerr << "MC yields <0.0001!" << endl;
        q.value = 0.0001;
        q.error = 0.0001;
      }
    }

    yields["_QCDTF"] = yields.at("qcd-sr")/yields.at("qcd-cr");

  }

  void calcDataCorr(){

    cerr << "\n--->" << __func__ << endl;

    vector<TString> calc_samples = {"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr", "znunu-cr", "data-cr"};
    doYieldsCalc(calc_samples);
    doYieldsCalc({"qcd-withveto-sr", "qcd-withveto-cr"}, runBootstrapping ? 50 : 0);

    vector<TString> otherbkg_samples = {"ttbar-cr", "wjets-cr", "tW-cr", "ttW-cr"};
    vector<TString> norm_samples = {"ttbar-norm", "wjets-norm", "tW-norm", "ttW-norm", "qcd-norm"};
    sumYields(otherbkg_samples, "non-qcd");
    yields["otherbkgs-noznunu"] = yields.at("non-qcd");

    yields["_SubNormCorr"] = std::vector<Quantity>();
    unsigned ibin = 0;
    for (auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);

      auto samp = config.samples.at("data-norm");
      auto norm_sel = config.sel + " && " + cat.cut + " && " + cat.bin.var + ">" + toString(cat.bin.plotbins.front()) + samp.sel;
      auto norm_datayield = getYields(samp.tree, samp.wgtvar, norm_sel);
      Quantity norm_bkgtotal(0, 0);
      for (auto &s : norm_samples){
        samp = config.samples.at(s);
        norm_bkgtotal = norm_bkgtotal + getYields(samp.tree, samp.wgtvar, norm_sel);
      }
      Quantity norm_factor = norm_datayield / norm_bkgtotal;
      cerr << endl << "~~~" << cat_name << ": data(norm) = " << norm_datayield << ", total bkg (norm) = " << norm_bkgtotal << endl << endl;

      for (auto &c : cat.bin.cuts){
        yields.at("_SubNormCorr").push_back(norm_factor);
        yields.at("otherbkgs-noznunu").at(ibin) = yields.at("otherbkgs-noznunu").at(ibin) * norm_factor;
        ++ibin;
      }
    }

    yields["otherbkgs"] = yields.at("otherbkgs-noznunu") + yields.at("znunu-cr");

    auto vdata = yields.at("data-cr");
    Quantity::removeZeroes(vdata);
    yields["_DATA"] = vdata;

    yields["_SubCorr"] = std::vector<Quantity>();
    yields["_TF"] = std::vector<Quantity>();
    for (unsigned i=0; i<vdata.size(); ++i){
      double otherVal = yields.at("otherbkgs").at(i).value;
      double dataVal = vdata.at(i).value;
      if (dataVal<10) dataVal = yields.at("qcd-withveto-cr").at(i).value + otherVal;
      double sub = otherVal/dataVal;
//      Quantity corr(1-sub, sub*(1-sub)); // 100% unc on the subtraction: FIXME?
      Quantity corr(1-sub, 0); // subtraction unc taken externally (in addition to jetresptail & met integration)
      yields.at("_SubCorr").push_back(corr);
      yields.at("_TF").push_back(yields.at("_QCDTF").at(i) * corr);
    }

  }

  void pred(){
    cerr << "\n--->" << "Running QCD prediction..." << endl << endl;

    if (!runBootstrapping){
      cerr << "... Do NOT run bootstrapping ..." << endl;
    }

    // calc TF first: needed in calcDataCorr
    calcTF();
    calcDataCorr();

    yields["_pred"] = yields.at("_DATA") * yields.at("_TF");
    printVec(yields["_pred"], "QCD prediction", true);

  }

  // whether run bootstrapping for QCD uncertainty or not
  bool runBootstrapping = true;

  // spits out latex-formatted table for Moriond17 results
  // design to be consistent with 'results' tables
  // req's category names starting with either lm_ or hm_
  // bool parameter can output the tables to two (LM/HM) text files
  // categories are traversed linearly with no special cases other than starting with 'lm_' or 'hm_'
  void printMoriond17Table(const map<TString, TString> &labelMap, std::string outFilePrefix = "/tmp/Moriond17_"){
    Quantity::printStyle = Quantity::LATEX;
    fstream outStreamLM, outStreamHM; ostringstream outString; // form string in outString, then conditionally write outString to cout or file
    bool saveToFile = true;
    if(saveToFile){
      outStreamLM.open(outFilePrefix+"qcd_lm.txt",ios::out);
      outStreamHM.open(outFilePrefix+"qcd_hm.txt",ios::out);
    }

    // linearly traverse all bins (hm and lm)
    int ibin = 0;
    for (const auto &cat_name : config.categories){
      bool isLM = false;
      // simple check for any changes in category names which would cause unexpected behavior
      if(cat_name.Contains("lm_")) { isLM = true; }
      else if(cat_name.Contains("hm_")) { isLM = false; }
      else { throw std::runtime_error(TString::Format("QCDEstimator.hh/printMoriond17Table: category name, %s, must start with lm_ or hm_. New categories? Update this function!\n",cat_name.Data())); }
      const auto & cat = config.catMaps.at(cat_name);

      // latex format for each category header: hline, multicolumn with cat label, hline
      auto cat_label = translateString(cat_name, labelMap, "_", ", ");
      int ncols = 5;
      outString << R"(\hline)" << endl << R"(\multicolumn{)"+to_string(ncols)+R"(}{c}{)" + cat_label + R"(} \\)" << endl << R"(\hline)" << endl;

      // latex format for each met bin in the category: search region, met, ----numbers
      auto metlabels = convertBinRangesToLabels(cat.bin.plotbins, true);
      for (const auto &p : metlabels){
        const auto &ndata    = yields["_DATA"].at(ibin);
        const auto &tf       = yields["_TF"].at(ibin);
        const auto &pred     = yields["_pred"].at(ibin);
        outString << ibin << " & " << p << " & " << fixed << setprecision(0) << setw(10) << ndata << " & " << fixed << setprecision(4) << setw(10) << tf << " & " << fixed << setprecision(2) << setw(10) << pred << " \\\\" << endl;

        // send it
        cout << outString.str();
        if(saveToFile){
          if(isLM) { outStreamLM << outString.str(); }
          else { outStreamHM << outString.str(); }
        }
        outString.str(""); // reset
        ibin++;
      }//for met
    }//for cat
  }//for country

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


}

#endif /*ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_*/
