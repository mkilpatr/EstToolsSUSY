#ifndef ESTTOOLS_ESTIMATOR_HH_
#define ESTTOOLS_ESTIMATOR_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "EstHelper.hh"
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;
#endif

namespace EstTools{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class IEstimator {
public:
  IEstimator() : fout_(nullptr) {}
  IEstimator(TString outputdir, TString outputfile):
    outputdir_(outputdir),
    outputfile_(outputfile),
    fout_(nullptr)
  {
    gSystem->mkdir(outputdir, true);
    ROOT::EnableThreadSafety();
    SetStyle();
  }

  virtual ~IEstimator() {
//////    TH1::AddDirectory(kFALSE); // Detach the histograms from the file: problematic
    if (fout_) fout_->Close();
  }

  void setHeader(const TString& header) {
    header_ = header;
  }

  void setSaveHists(bool saveHists = true) {
    saveHists_ = saveHists;
  }

  void setPostfix(const TString& postfix) {
    postfix_ = postfix;
  }

  void setSelection(const TString& selection, const TString& postfix, const TString& header) {
    selection_ = selection;
    postfix_ = postfix;
    header_ = header;
  }

  void setSelection(const Category& cat){
    selection_ = cat.cut;
    postfix_ = cat.name;
    header_ = cat.label;
  }

  void resetSelection() {
    selection_ = "";
    postfix_ = "";
    header_ = "";
  }

  void setConfig(const BaseConfig& config) {
    this->config = config;
  }

public:
  void savePlot(TCanvas *c, TString fn){
    c->SaveAs(outputdir_+"/"+fn+"."+config.plotFormat);
  }

  void saveHist(const TH1 *h, TString name = ""){
    if (!fout_)
      fout_ = new TFile(outputdir_ + "/" + outputfile_, "RECREATE");
    fout_->cd();
    TH1* hnew = (TH1*) h->Clone();
    hnew->Write(name, TObject::kOverwrite);
  }

public:
  BaseConfig config;

  TString outputdir_;
  TString outputfile_;
  TFile   *fout_;
  TString header_;
  TString postfix_;
  TString selection_;
  bool    saveHists_ = false;

};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class BaseEstimator : public IEstimator {
public:
  BaseEstimator() {}
  BaseEstimator(TString outputdir, TString outputfile = "EstOutput.root") :
    IEstimator(outputdir, outputfile) {}
  BaseEstimator(const BaseConfig &config) :
    IEstimator(config.outputdir, "output.root") { setConfig(config); }

  virtual ~BaseEstimator() {}

  template<typename T>
  void printVec(const std::vector<T>& vec, const TString title="", bool printPercents = false) const{
    if (title!="")
      cout << title << endl;
    int ibin = 0;
    for (const auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);
      cout << setw(30) << cat.name << "\t ";
      for (const auto &b : cat.bin.cuts){
        const auto &quantity = vec.at(ibin++);
        cout << fixed << setprecision(2) << setw(10) << quantity << "\t ";
        if (printPercents && std::is_same<T, Quantity>::value)
          cout << " (" << toString(quantity.error/quantity.value*100, 0, true) << "%) ";
      }
      cout << endl;
    }
    cout << endl;
  }

  virtual void calcYields(){
    vector<TString> snames;
    for (const auto &s : config.samples) snames.push_back(s.first);
    doYieldsCalc(snames);
  }

  virtual void calcYieldsExcludes(const vector<TString> &excludes){
    vector<TString> snames;
    for (const auto &s : config.samples) {
      if ( std::find(excludes.begin(), excludes.end(), s.first) != excludes.end() ) continue;
      snames.push_back(s.first);
    }
    doYieldsCalc(snames);
  }

  virtual void doYieldsCalc(const vector<TString> &sample_names, int nBootstrapping = 0){
    // calculate yields for the samples in snames
    // use SR categories if no CR categories are defined OR sample name ends with "-sr"
    // otherwise use CR categories
    // IF sample name ends with "-sr-int", we want to integrate in tops/Ws like the CRs, so use CR categories
    for (auto &sname : sample_names){
      auto start = chrono::steady_clock::now();

      cout << "\nCalc yields for sample " << sname << endl;
      const auto &sample = config.samples.at(sname);
      auto catMaps = (config.crCatMaps.empty() || sname.EndsWith("-sr")) ? config.catMaps : config.crCatMaps;
      auto srCatMaps = config.catMaps;
      if(sname.EndsWith("-sr-int")) { catMaps = config.crCatMaps; }

      const int nMax = std::max(std::thread::hardware_concurrency()*0.8, std::thread::hardware_concurrency()-2.);
      std::atomic<int> nRunning(0);
      std::unordered_map<std::string, vector<Quantity>> results;
      std::mutex results_mutex;

      auto calcOne = [&] (TString cat_name) {
        ++nRunning;
        const auto & cat = catMaps.at(cat_name);
        auto cut = config.sel + " && " + cat.cut;
        auto v = getYieldVectorWrapper(sample, cut + sample.sel, cat.bin, nBootstrapping);
        if (v.size()<srCatMaps.at(cat_name).bin.nbins){
          // !! FIXME : if cr bin numbers < sr: repeat the last bin
          vector<Quantity> vv(v);
          for (unsigned ibin=v.size(); ibin<srCatMaps.at(cat_name).bin.nbins; ++ibin){
            vv.push_back(v.back());
          }
          v = vv;
        }
        std::lock_guard<std::mutex> guard(results_mutex);
        results[cat_name.Data()] = v;
        --nRunning;
      };

      std::vector<std::thread> pool;
      for (auto &cat_name : config.categories){
        while(nRunning>=nMax) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
        pool.emplace_back(calcOne, cat_name);
      }
      for (auto && t : pool) t.join();

      yields[sname] = vector<Quantity>();
      for (auto &cat_name : config.categories){
        yields[sname].insert(yields[sname].end(), results.at(cat_name.Data()).begin(), results.at(cat_name.Data()).end());
      }

      auto end = chrono::steady_clock::now();
      auto diff = end - start;
      cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    }
  }

  virtual vector<Quantity> getYieldVectorWrapper(const Sample& sample, TString sel, const BinInfo &bin, int nBootstrapping=0){
    if (nBootstrapping==0){
      std::unique_ptr<TFile> infile(new TFile(sample.filepath));
      std::unique_ptr<TTree> intree(dynamic_cast<TTree*>(infile->Get(sample.treename)));
      intree->SetTitle(sample.name);
      auto yields = getYieldVector(intree, sample.wgtvar, sel, bin);
      intree.reset();
      infile.reset();
      return yields;
    }else{
      throw std::invalid_argument("BaseEstimator::getYieldVectorWrapper: Bootstrapping not implemented!");
    }
  }

  void sumYields(vector<TString> list, TString sum_name){
    // sum yields from samples in the list, and store as "sum_name"
    assert(list.size() <= yields.size());
    yields[sum_name] = vector<Quantity>(config.nbins());
    for (const auto &s : list){
      yields[sum_name] = yields[sum_name] + yields.at(s);
    }
  }

  void printYields() const{
    cout << "Yields" << endl;
    for (const auto &p : yields){
      const auto &vec = p.second;
      cout << p.first << ": " << fixed << setprecision(2) << Quantity::sum(vec) << endl;
      printVec(vec);
    }
  }

  void printYieldsTable(vector<TString> columns) const{
    // print yields in tabular format (friendly for pasting into spreadsheets)

    unsigned ibin = 0;

    cout << "Yields" << "\t";
    for (const auto &c : columns){
      cout << c << "\t";
    }
    cout << endl;

    for (auto &cat_name : config.categories){
      const auto &cat = config.catMaps.at(cat_name);
      cout << cat.name << endl;
      for (auto &bin : cat.bin.plotnames){
        cout << bin << "\t";
        for (const auto &c : columns){
          cout << fixed << setprecision(2) << yields.at(c).at(ibin) << "\t ";
        }
        cout << endl;
        ++ibin;
      }
    }

  }

  // printYieldsTableLatex
  //
  // Purpose 
  //   spits out latex-formatted table for Moriond17 results. designed so that llb/znunu/qcd/bkgs/results tables are similar.
  // Arguments
  //   vector<strings> of yields which have already been computed elsewhere, eg yields["TF_"] for LLB.
  //   optionally a filename to save the tex (default /tmp/yields.tex)
  //   optionally a TString, default "all", indicating whether to do only "lm" or "hm" table, case-insensitive
  //   optionally a map<String,int> from particular samples (no size requirement) overriding the # of digits displayed in table for those samples
  // Digits (case-sensitive)
  //   default is 2, eg 123.12+/-1.11
  //   if sample string contains "TF" (our usual transfer factor naming) then 3 digits, eg 0.002 +/- 0.001 is encountered in LLB
  //   if sample string contains "data" or optional argument digits.at(sample string) is zero, give zero digits and no uncertainties, eg 17
  // Usage for LLB
  //   std::map<TString,int> dig; // OPTIONAL: to override some samples' digits
  //   dig["singlelep"] = 0; // indicate "singlelep" yields are data for proper formatting
  //   // l.yields should already contain all of these yields, typically from a call to l.pred()
  //   l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "/tmp/alex_yields_llb_lm.tex", true, dig); // LM table
  //   l.printYieldsTableLatex({"singlelep", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "/tmp/alex_yields_llb_hm.tex", false, dig); // HM table
  //
  // current format of output .tex, to be copy-pasted into AN/PAS/Paper tables:
  // \hline
  // \multicolumn{5}{c}{low \dm, $\nb=0$, $\nsv=0$, $\ptisr>500$\,GeV, $2\leq\nj<5$} \\
  // \hline
  // %  lm_nb0_nivf0_highptisr_nj2to5
  // 0 & 450$-$550 & 1681 &      0.448$\pm$0.012 &     753.12$\pm$27.10 \\
  // ...etc

  void printYieldsTableLatex(const vector<TString> &samples, const map<TString, TString> &labelMap, std::string outputfile="/tmp/yields.tex", TString whichCats="all", const map<TString,int>& digits = map<TString,int>()) const{
    ofstream outfile(outputfile);
    Quantity::printStyle = Quantity::LATEX;
    whichCats.ToLower();

    // linearly traverse all bins (lm then hm, currently)
    unsigned ibin = 0;

    // latex comment to label columns for user. user makes their own pretty column header.
    outfile << "% Search region" << " & \t" << R"($\met$)" << " & \t";
    for (const auto &c : samples){
      outfile << c << " & \t";
    }
    outfile << endl;

    int ncols = samples.size()+2; // bin # + MET range + samples
    for (auto &cat_name : config.categories){
      // skip it? must be careful and use bool b/c # of met bins varies... can't just 'continue' past category
      bool skip = false;
      if(whichCats == "lm" && !cat_name.Contains("lm_")) skip=true; // wanted LM, not LM
      if(whichCats == "hm" && !cat_name.Contains("hm_")) skip=true; // wanted HM, not HM
      const auto &cat = config.catMaps.at(cat_name);

      // latex format for each category header: hline, multicolumn thing with pretty cat label, hline
      auto cat_label = translateString(cat_name, labelMap, "_", ", ");
      if(!skip) outfile << R"(\hline)" << endl << R"(\multicolumn{)"+to_string(ncols)+R"(}{c}{)" + cat_label + R"(} \\)" << endl << R"(\hline)" << endl;

      // a latex comment with raw cat label for clarity
      if(!skip) outfile << " % " << setw(30) << cat.label << endl;

      // latex format for each met bin row: search region #, met, each sample's yields
      auto metlabels = convertBinRangesToLabels(cat.bin.plotbins, true);
      for (const auto &p : metlabels){
        // search region #, met
        if(!skip) outfile << ibin << " & " << p;
 
        // each sample's yields
        int isamp = 0;
        for (const auto &c : samples){
          // what precision to use for this sample's yields?
          bool isData = c.Contains("data"); // just a guess - see later
          int dig = 2; // default 2 digits
          if(c.Contains("TF")) dig = 3; // transfer factors get 3 digits
          if(digits.count(c)>0) dig = digits.at(c); // user overrides # of digits for this sample

          // send it!
          if(!skip) {
            outfile << " & \t" << fixed << setprecision(dig);
            if(isData || dig==0) outfile << setprecision(0)    << yields.at(c).at(ibin).value; // no digits, no uncertainties
            else                 outfile << setprecision(dig)  << yields.at(c).at(ibin);       // 'dig' digits + uncertainties
          }
          ++isamp;
        }
        if(!skip) outfile << R"( \\)" << endl;
        ++ibin;
      }//for met
    }//for cats
    outfile.close();
  }//for country!


  TH1* getHistogram(const BinInfo& var_info, TString sample, const Category& category){
    // get a histogram of the given sample in the given category

    TString plotvar = var_info.var;
    TString title = ";"
        + var_info.label + (var_info.unit=="" ? "" : " ["+var_info.unit + "]") +";"
        + "Events";

    auto cut = config.sel + " && " + category.cut + TString(selection_=="" ? "" : " && "+selection_);

    auto samp = config.samples.at(sample);
    auto hname = filterString(plotvar) + "_" + sample + "_" + category.name + "_" + postfix_;
    auto hist = getHist(samp.tree, plotvar, samp.wgtvar, cut + samp.sel, hname, title, var_info.plotbins);
    prepHists({hist});
    if (saveHists_) saveHist(hist);

    return hist;
  }

  void plotComp(const BinInfo& var_info, const vector<TString> comp_samples, const vector<TString> comp_categories, bool comp_in_samples = true, bool isNormalized = true, float logymin = -1, std::function<void(TCanvas*)> *plotextra = nullptr){
    // plot distribution in *var_info.var* for all given samples and categories
    // and compare them between either *samples* or *categories* (in the ratio plot)

    vector<TH1*> hists;
    vector<TH1*> ratioHists;
    auto leg = initLegend();

    TString plotvar = var_info.var;
    TString title = ";"
        + var_info.label + (var_info.unit=="" ? "" : " ["+var_info.unit + "]") +";"
        + (isNormalized ? "Normalized (to 1.) Events" : "Events");

    for (unsigned isamp=0; isamp<comp_samples.size(); ++isamp){
      TH1* hRef = nullptr;
      auto sname = comp_samples.at(isamp);
      auto sample = config.samples.at(sname);
      for (unsigned icat=0; icat<comp_categories.size(); ++icat){
        auto cat = config.catMaps.at(comp_categories.at(icat));
        auto hname = filterString(plotvar) + "_" + sname + "_" + cat.name + "_" + postfix_;
        auto cut = config.sel + sample.sel + " && " + cat.cut + TString(selection_=="" ? "" : " && "+selection_);
        auto htmp = getHist(sample.tree, plotvar, sample.wgtvar, cut, hname, title, var_info.plotbins);
        htmp->SetLineStyle(icat+1);
        prepHists({htmp}, isNormalized);
        if (saveHists_) saveHist(htmp);
        hists.push_back(htmp);

        // add legend
        addLegendEntry(leg, htmp, sample.label + " " + cat.label);

        // make ratio histograms : compare between categories
        if (!comp_in_samples){
          if (icat==0)
            hRef = htmp;
          else{
            auto rhist = makeRatioHists(htmp, hRef);
            ratioHists.push_back(rhist);
            if (saveHists_) saveHist(rhist);
          }
        }

      }
    }

    // make ratio histograms : compare between samples
    if (comp_in_samples){
      for (unsigned icat=0; icat<comp_categories.size(); ++icat){
        TH1* hRef = nullptr;
        for (unsigned isamp=0; isamp<comp_samples.size(); ++isamp){
          if (isamp==0)
            hRef = hists.at(icat);
          else{
            auto htmp = hists.at(isamp*comp_categories.size()+icat);
            auto rhist = makeRatioHists(htmp, hRef);
            ratioHists.push_back(rhist);
            if (saveHists_) saveHist(rhist);
          }
        }
      }
    }

    TString RYtitle = comp_in_samples ?
        "#frac{dN(" + (comp_samples.size()==2 ? config.samples.at(comp_samples.back()).label : "...") + ")}{dN(" + config.samples.at(comp_samples.front()).label +")}" :
        "#frac{dN(" + (comp_categories.size()==2 ? config.catMaps.at(comp_categories.back()).label : "...") + ")}{dN(" + config.catMaps.at(comp_categories.front()).label +")}";
    auto c = drawCompAndRatio(hists, ratioHists, leg, RYtitle, RATIO_YMIN, RATIO_YMAX, true, logymin);
    if (plotextra) (*plotextra)(c);
//    drawHeader(header_);
    TString plotname = "comp_"+filterString(plotvar)+"_btw_"+(comp_in_samples?"samples":"categories")+"__"+postfix_;
    c->SetTitle(plotname);
    savePlot(c, plotname);

  }

  void plotEfficiencyComp(const BinInfo& num, const BinInfo& denom, const vector<TString> comp_samples = {"mc", "data"}, TString ytitle="Efficiency", TString ratioYtitle = "Data/MC"){
    // plot the ratio histogram of num.var/denom.var
    // compare the differences between different samples listed in comp_samples

    vector<TH1*> hists;
    vector<TH1*> ratioHists;
    auto leg = initLegend();

    TString num_var = num.var;
    TString denom_var = denom.var;
    TString title = ";"
        + num.label + (num.unit=="" ? "" : " ["+num.unit + "]") +";"
        + ytitle;

    TH1D* hRef = nullptr;
    for (unsigned isamp=0; isamp<comp_samples.size(); ++isamp){
      auto sname = comp_samples.at(isamp);
      auto sample = config.samples.at(sname);
      auto hname = num_var + "_over_" + denom_var + "_" + sname + "_" + postfix_;
      auto cut = config.sel + TString(selection_=="" ? "" : " && "+selection_);
      auto hnum = getHist(sample.tree, num_var, sample.wgtvar, cut + sample.sel, hname, title, num.plotbins);
      auto hdenom = getHist(sample.tree, denom_var, sample.wgtvar, cut + sample.sel, hname+"_denom", title, num.plotbins);
      prepHists({hnum, hdenom});
      hnum->Divide(hnum, hdenom, 1, 1, "B");
      if (comp_samples.size()==2){
        if(isamp==0) { hnum->SetLineColor(kOrange); hnum->SetMarkerColor(kOrange);}
        else if (isamp==1) { hnum->SetLineColor(kBlack); hnum->SetMarkerColor(kBlack);}
      }
      if (saveHists_) saveHist(hnum);
      hists.push_back(hnum);

      // add legend
      addLegendEntry(leg, hnum, sample.label);

      // make ratio histograms
      if (isamp==0)
        hRef = hnum;
      else{
        auto rhist = makeRatioHists(hnum, hRef);
        ratioHists.push_back(rhist);
        if (saveHists_) saveHist(rhist);
      }
    }

    auto c = drawCompAndRatio(hists, ratioHists, leg, ratioYtitle);
//    drawHeader(header_);
    TString plotname = "comp_"+num_var+"_over_"+denom_var+"_btw_"+"samples"+"__"+postfix_;
    c->SetTitle(plotname);
    savePlot(c, plotname);

  }

  void plotStack(const BinInfo& var_info, const vector<TString> mc_samples, const vector<TString> signal_samples, const Category& category, bool norm_to_bkg = false, double sigScale = 1){
    // make stack plots with the given cateogory selection
    // possible to scale signals to total bkg, or scale signal by a const ratio

    vector<TH1*> mchists;
    vector<TH1*> sighists;
    auto leg = initLegend();

    TString plotvar = var_info.var;
    TString title = ";"
        + var_info.label + (var_info.unit=="" ? "" : " ["+var_info.unit + "]") +";"
        + "Events";
    TString RYTitle = "N_{obs}/N_{exp}";

    auto cut = config.sel + " && " + category.cut + TString(selection_=="" ? "" : " && "+selection_);

    TH1 *hbkgtotal = nullptr;
    for (const auto &sname : mc_samples){
      auto sample = config.samples.at(sname);
      auto hname = filterString(plotvar) + "_" + sname + "_" + category.name + "_" + postfix_;
      auto hist = getHist(sample.tree, plotvar, sample.wgtvar, cut + sample.sel, hname, title, var_info.plotbins);
      prepHists({hist}, false, true, true);
      if (saveHists_) saveHist(hist);
      mchists.push_back(hist);

      addLegendEntry(leg, hist, sample.label, "F", 0.04);

      if(!hbkgtotal)
        hbkgtotal = (TH1*)hist->Clone("bkgtotal");
      else
        hbkgtotal->Add(hist);
    }

    double totalbkg = hbkgtotal->Integral(1, hbkgtotal->GetNbinsX()+1);

    for (const auto &sname : signal_samples){
      auto sample = config.samples.at(sname);
      auto hname = filterString(plotvar) + "_" + sname + "_" + category.name + "_" + postfix_;
      auto hist = getHist(sample.tree, plotvar, sample.wgtvar, cut + sample.sel, hname, title, var_info.plotbins);
      prepHists({hist});
      if (saveHists_) saveHist(hist);
      sighists.push_back(hist);

      addLegendEntry(leg, hist, sample.label, "L", 0.04);

      if (norm_to_bkg)
        hist->Scale(totalbkg/hist->Integral(1, hist->GetNbinsX()+1));
      else
        hist->Scale(sigScale);
    }

    leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.45, 0.6, 0.92, 0.87);

    TCanvas *c = drawStack(mchists, sighists, false, leg);
    TString plotname = filterString(plotvar)+"_stack_"+category.name+"__"+postfix_;
    c->SetTitle(plotname);
    savePlot(c, plotname);

  }

  void plotSigVsBkg(const BinInfo& var_info, const vector<TString>& mc_samples, const vector<TString>& sig_sample, const Category& category, bool showSigma = true,  bool plotlog = false, std::function<void(TCanvas*)> *plotextra = nullptr){
    // make BKG vs Signal plots with the given cateogory selection
    // plot S/sqrt(B) in the lower pad

    vector<TH1*> mchists, sighists, sigmahists;
    TH1 *bkgtotal = nullptr;
    auto leg = initLegend();

    TString plotvar = var_info.var;
    TString title = ";"
        + var_info.label + (var_info.unit=="" ? "" : " ["+var_info.unit + "]") +";"
        + "Events";
    TString RYTitle = "S/#sqrt{B}";

    auto cut = config.sel + " && " + category.cut + TString(selection_=="" ? "" : " && "+selection_);

    for (auto &sname : mc_samples){
      auto sample = config.samples.at(sname);
      auto hname = filterString(plotvar) + "_" + sname + "_" + category.name + "_" + postfix_;
      auto hist = getHist(sample.tree, plotvar, sample.wgtvar, cut + sample.sel, hname, title, var_info.plotbins);
      prepHists({hist});
      if (saveHists_) saveHist(hist);
      mchists.push_back(hist);
      hist->SetFillColor(hist->GetLineColor()); hist->SetFillStyle(1001); hist->SetLineColor(kBlack);
      addLegendEntry(leg, hist, sample.label, "F");
      if (!bkgtotal){ bkgtotal = (TH1*)hist->Clone("bkgtotal"); }
      else{ bkgtotal->Add(hist); }
    }

    for (int i=0; i<=bkgtotal->GetNbinsX(); ++i){
      auto q =getHistBin(bkgtotal, i).power(0.5);
      if (q.value == 0) q=Quantity(0.0001, 0.0001);
      setHistBin(bkgtotal, i, q);
    }

    for (auto &sname : sig_sample){
      auto sample = config.samples.at(sname);
      auto hname = filterString(plotvar) + "_" + sname + "_" + category.name + "_" + postfix_;
      auto hist = getHist(sample.tree, plotvar, sample.wgtvar, cut + sample.sel, hname, title, var_info.plotbins);
      prepHists({hist});
      hist->SetLineStyle(kDashed);
      hist->SetLineWidth(3);
      if (saveHists_) saveHist(hist);
      sighists.push_back(hist);
      addLegendEntry(leg, hist, sample.label, "L");
      auto hs = (TH1*)hist->Clone(hname+"_signalOvSqrtBkg");
      hs->Divide(bkgtotal);
      sigmahists.push_back(hs);
      if (saveHists_) saveHist(hs);
    }

    leg->SetTextSize(0.04);
    setLegend(leg, 2, 0.45, 0.6, 0.92, 0.87);

    TCanvas *c = nullptr;
    if (showSigma){
      c = drawStackAndRatio(mchists, nullptr, leg, plotlog, RYTitle, 0, 2.999, 0, -1, sighists, nullptr, sigmahists);
    }else{
      c = drawStack(mchists, sighists, plotlog, leg);
    }

    if (plotextra) (*plotextra)(c);

    TString plotname = filterString(plotvar)+"_SigVsBkg_"+category.name+"__"+postfix_;
    c->SetTitle(plotname);
    savePlot(c, plotname);

  }


  TH1* plotDataMC(const BinInfo& var_info, const vector<TString> mc_samples, TString data_sample, const Category& category, bool norm_to_data = false, TString norm_cut = "", bool plotlog = false, std::function<void(TCanvas*)> *plotextra = nullptr){
    // make DataMC plots with the given cateogory selection
    // possible to normalize MC to Data with a different selection (set by *norm_cut*)

    vector<TH1*> mchists;
    auto leg = initLegend();

    TString plotvar = var_info.var;
    TString title = ";"
        + var_info.label + (var_info.unit=="" ? "" : " ["+var_info.unit + "]") +";"
        + "Events";
    TString RYTitle = "N_{obs}/N_{exp}";

    auto cut = config.sel + " && " + category.cut + TString(selection_=="" ? "" : " && "+selection_);

    TH1 *hdata = nullptr;
    Sample d_sample;
    if (data_sample!=""){
      d_sample = config.samples.at(data_sample);
      auto hname = filterString(plotvar) + "_" + data_sample + "_" + category.name + "_" + postfix_;
      hdata = getHist(d_sample.tree, plotvar, d_sample.wgtvar, cut + d_sample.sel, hname, title, var_info.plotbins);
      prepHists({hdata});
      if (saveHists_) saveHist(hdata);
      addLegendEntry(leg, hdata, d_sample.label, "LP");
    }

    for (auto &sname : mc_samples){
      auto sample = config.samples.at(sname);
      auto hname = filterString(plotvar) + "_" + sname + "_" + category.name + "_" + postfix_;
      auto hist = getHist(sample.tree, plotvar, sample.wgtvar, cut + sample.sel, hname, title, var_info.plotbins);
      prepHists({hist});
      if (saveHists_) saveHist(hist);
      mchists.push_back(hist);
      hist->SetFillColor(hist->GetLineColor()); hist->SetFillStyle(1001); hist->SetLineColor(kBlack);

      addLegendEntry(leg, hist, sample.label, "F");
    }

    if (hdata){
      if (norm_to_data){
        double sf = 1;
        // calc sf
        if (norm_cut==""){
          auto hsum = (TH1*)mchists.front()->Clone("hsum");
          for (unsigned i=1; i<mchists.size(); ++i){
            hsum->Add(mchists.at(i));
          }
          sf = hdata->Integral(1, hsum->GetNbinsX()+1) / hsum->Integral(1, hsum->GetNbinsX()+1);
        }else {
          cout << " ... using normMap " << norm_cut << endl;
          auto data_inc = getYields(d_sample.tree, d_sample.wgtvar, norm_cut + d_sample.sel);
          vector<Quantity> mc_quantities;
          for (auto &sname : mc_samples){
            auto sample = config.samples.at(sname);
            mc_quantities.push_back(getYields(sample.tree, sample.wgtvar, norm_cut + sample.sel));
          }
          auto mc_inc = Quantity::sum(mc_quantities);
          sf = (data_inc/mc_inc).value;
          cout << "... normScaleFactor = " << sf << endl;
        }
        // scale the mc hists
        for (auto *hist : mchists) hist->Scale(sf);
      }
    }

    TCanvas *c = nullptr;
    if (hdata){
      c = drawStackAndRatio(mchists, hdata, leg, plotlog);
    }else{
      c = drawStack(mchists, {}, plotlog, leg);
    }

    if (plotextra) (*plotextra)(c);

    TString plotname = filterString(plotvar)+"_DataMC_"+category.name+"__"+postfix_;
    c->SetTitle(plotname);
    savePlot(c, plotname);

    if (hdata)
      return makeRatioHists(hdata, sumHists(mchists, "bkgtotal"));
    else
      return nullptr;
  }

  void plotDataMC(const vector<TString> mc_samples, TString data_sample, bool norm_to_data = false, TString norm_cut = "", bool plotlog = false, std::function<void(TCanvas*)> *plotextra = nullptr){
    // make Data/MC plots for all categories
    for (auto category : config.categories){
      const auto &cat = config.catMaps.at(category);
      plotDataMC(cat.bin, mc_samples, data_sample, cat, norm_to_data, norm_cut, plotlog, plotextra);
    }
  }

  void printSummary(const vector<vector<Quantity>> &bkgs, const vector<Quantity> &data){
    auto totalbkg = bkgs.front();
    for (unsigned ibkg=1; ibkg<bkgs.size(); ++ibkg) totalbkg = totalbkg + bkgs.at(ibkg);

    cout << setw(30) << "category" << "\t " << setw(30) << "pred." << setw(30) << "obs." << endl;
    unsigned ibin=0;
    for (const auto &cat_name : config.categories){
      Quantity pred(0, 0);
      Quantity obs(0, 0);
      const auto & cat = config.catMaps.at(cat_name);
      for (const auto &b : cat.bin.cuts){
        pred = pred + totalbkg.at(ibin);
        obs  = obs  + data.at(ibin);
        ++ibin;
      }
      cout << setw(30) << cat.name << "\t "
          << setw(30) << setprecision(2) << pred
          << setw(30) << setprecision(0) << obs.value << endl;
    }

  }

  void dumpDatacardConfig(std::string filename, std::string wrapping = ""){
    cerr << "Writing binning definition to file: " << filename << endl;

    std::ofstream fout(filename);

    std::string tab = "  ";

    auto vec2str = [](const vector<double>& vec){
      TString s="";
      for (auto v : vec) {
        if (s=="") s = toString(v, 0);
        else s = s+", "+toString(v, 0);
      }
      return s;
    };

    for (const auto &category : config.categories){
      const auto &cat = config.catMaps.at(category);
      fout << wrapping << cat.name << wrapping << ": {" << endl
           << tab << "'cut': '" + cat.cut + "'," << endl
           << tab << "'var': '" + cat.bin.var + "'," << endl
           << tab << "'bin': [" + vec2str(cat.bin.plotbins) + "]" << endl
           << tab << "}" << endl;
    }

    fout.close();
  }

  void testSROrthogonality(TString samp = "ttbar"){
    // test if SRs are orthogonal
    for (unsigned ia=0; ia<config.categories.size(); ++ia){
      for (unsigned ib=ia+1; ib<config.categories.size(); ++ib){
        auto sra = config.categories.at(ia);
        auto srb = config.categories.at(ib);
        cout << "------\nTesting " << sra << " && " << srb << endl;
        auto cut = addCuts({config.catMaps.at(sra).cut, config.catMaps.at(srb).cut});
        cout << "---\n" << cut << "\n---\n";
        if (config.samples.at(samp).tree->GetEntries(cut)){
          throw std::logic_error("Found overlap: " + sra + ", " + srb);
        }
      }
    }
  }

public:
  map<TString, vector<Quantity>> yields;  // stores yields of all bins in all categories for each sample

};



}

#endif /*ESTTOOLS_ESTIMATOR_HH_*/
