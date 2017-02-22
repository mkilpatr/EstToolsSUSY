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

    vector<TString> qcdsamp = {"qcd-sr", "qcd-cr"};
    if(splitTF) qcdsamp.push_back("qcd-sr-int");
    doYieldsCalc(qcdsamp, runBootstrapping ? 50 : 0);

    // FIXME
    for (auto &q : yields.at("qcd-cr")){
      if (q.value<0.0001){
        cerr << "MC yields <0.0001!" << endl;
        q.value = 0.0001;
        q.error = 0.0001;
      }
    }

    if(splitTF){
      yields["_QCDTF_CR_to_SR_noextrap_nocorr"] = yields.at("qcd-sr-int")/yields.at("qcd-cr"); // split _QCDTF into CR-SR and tags extrapolation
      yields["_QCDTF_SR_extrap"]                = yields.at("qcd-sr")/yields.at("qcd-sr-int");
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

      // use CR map, because we want to correct ttbarplusw in CR (i.e., w/o top/W cut)
      // dphi cut specified in sample definition
      const auto & crCat = config.crCatMaps.at(cat_name);
      const auto & srCat = config.catMaps.at(cat_name);

      auto samp = config.samples.at("data-norm");
      auto norm_sel = config.sel + " && " + crCat.cut + " && " + crCat.bin.var + ">" + toString(crCat.bin.plotbins.front());
      auto norm_datayield = getYields(samp.tree, samp.wgtvar, norm_sel + samp.sel);
      Quantity norm_bkgtotal(0, 0);
      for (auto &s : norm_samples){
        samp = config.samples.at(s);
        norm_bkgtotal = norm_bkgtotal + getYields(samp.tree, samp.wgtvar, norm_sel + samp.sel);
      }
      Quantity norm_factor = norm_datayield / norm_bkgtotal;
      cerr << endl << "~~~" << cat_name << ": data(norm) = " << norm_datayield << ", total bkg (norm) = " << norm_bkgtotal << endl << endl;

      for (auto &c : srCat.bin.cuts){
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
    if (splitTF){
      yields["_QCDTF_CR_to_SR_noextrap"] = std::vector<Quantity>(); // corrected cr-to-sr half of the TF
    }
    for (unsigned i=0; i<vdata.size(); ++i){
      double otherVal = yields.at("otherbkgs").at(i).value;
      double dataVal = vdata.at(i).value;
      if (dataVal<10) dataVal = yields.at("qcd-withveto-cr").at(i).value + otherVal;
      dataVal = std::max(0.0001, dataVal); // FIXME
      double sub = otherVal/dataVal;
//      Quantity corr(1-sub, sub*(1-sub)); // 100% unc on the subtraction: FIXME?
      Quantity corr(1-sub, 0); // subtraction unc taken externally (in addition to jetresptail & met integration)
      yields.at("_SubCorr").push_back(corr);
      yields.at("_TF").push_back(yields.at("_QCDTF").at(i) * corr);
      if (splitTF){
        std::cout << "Correcting the split QCD TF" << std::endl;
        yields["_QCDTF_CR_to_SR_noextrap"].push_back(yields.at("_QCDTF_CR_to_SR_noextrap_nocorr").at(i) * corr);
      }
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

  void prepDatacard(){
    convertYields("qcd-withveto-sr",  "",       "qcd");
    convertYields("qcd-withveto-cr",  "qcdcr",  "qcdcr_qcd");
    convertYields("otherbkgs",        "qcdcr",  "qcdcr_otherbkgs");
    convertYields("data-cr",          "qcdcr",  "qcdcr_data");
  }


  // whether run bootstrapping for QCD uncertainty or not
  bool runBootstrapping = true;

  // whether to split TF when making prediction tables
  bool splitTF = false;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


}

#endif /*ESTTOOLS_ESTMETHODS_QCDESTIMATOR_HH_*/
