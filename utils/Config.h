#ifndef ESTTOOLS_CONFIG_H_
#define ESTTOOLS_CONFIG_H_

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "THStack.h"
#include <TRandom3.h>
#include "TMath.h"

#include "Quantity.h"

using namespace std;
#endif

namespace EstTools{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct BinInfo{
  // struct to store binning information for plotting or getting yields

  TString var;    // the variable
  TString label;  // label of the variable for plotting
  TString unit;   // unit of the variable (if exist)

  vector<TString> cuts;         // cut strings for getting yields
  vector<TString> plotnames;    // name for each bin (filename compatible), e.g., met250to300
  vector<TString> plotlabels;   // label for each bin (for plot legends), e.g., N_{j}#geq5
  vector<double>  plotbins;     // vector of bin edges for making histograms
  unsigned nbins = 0;           // number of bins (i.e., size of cust, plotnames, plotlabels, and *plotbins.size()-1*)

  BinInfo() {}
  BinInfo(TString var, TString label, TString unit = "") : var(var), label(label), unit(unit) {}
  BinInfo(TString var, TString label, vector<int> bins, TString unit = "") : var(var), label(label), unit(unit) {
    setBinning<int>(bins);
  }
  BinInfo(TString var, TString label, vector<double> bins, TString unit = "") : var(var), label(label), unit(unit) {
    setBinning<double>(bins);
  }
//  BinInfo(TString var, TString label, int nbins, int xmin, int xmax, TString unit = "") : var(var), label(label), unit(unit) {
//    setBinning<int>(nbins, xmin, xmax);
//  }
  BinInfo(TString var, TString label, int nbins, double xmin, double xmax, TString unit = "") : var(var), label(label), unit(unit) {
    setBinning<double>(nbins, xmin, xmax);
  }

  // set the binning by a vector
  // bin edges convention: similar to TH1, i.e., [A, b). Always include *overflow* in the highest bin.
  // e.g., {2, 5, 10} -> 2<=x<5, x>=5
  template<typename Number>
  void setBinning(vector<Number> bins){
    reset();
    nbins = bins.size() - 1;

    for (auto &n : bins) plotbins.push_back(n);

    for (unsigned i=0; i<bins.size()-1; ++i){
      Number lower = bins.at(i), upper = bins.at(i+1);
      if (i==bins.size()-2){
        cuts.push_back(var + ">=" + to_string(lower));
        plotnames.push_back(var + "geq" + to_string(lower));
        plotlabels.push_back(label + "#geq" + to_string(lower));
      }else{
        if (std::is_integral<Number>::value && upper==(lower+1)){
          cuts.push_back(var + "==" + to_string(lower));
          plotnames.push_back(var + to_string(lower));
          plotlabels.push_back(label + "=" + to_string(lower));
        }else {
          cuts.push_back(var + ">=" + to_string(lower) + " && " + var + "<" + to_string(upper));
          plotnames.push_back(var + to_string(lower) + "to" + to_string(upper));
          plotlabels.push_back(to_string(lower) + "#leq" + label + "<" + to_string(upper));
        }
      }
    }
//#ifdef DEBUG_
//    cout << *this << endl;
//#endif
  }

  // set the binning by nbins and lower and upper edges
  template<typename Number>
  void setBinning(unsigned nbin, Number xmin, Number xmax){
    auto step = (xmax-xmin)/nbin;
    vector<Number> bins;
    for (unsigned i=0; i<=nbin; ++i){
      bins.push_back(xmin);
      xmin+=step;
    }
    setBinning<Number>(bins);
  }

  void reset(){
    cuts.clear();
    plotnames.clear();
    plotlabels.clear();
    plotbins.clear();
  }

  friend std::ostream &operator<<(std::ostream &os, const BinInfo &b){
    os << setw(20) << "Name" << setw(40) << "Cut" << setw(40) << "Label" << endl;
    for(unsigned i=0; i<b.plotnames.size(); ++i){
      os << setw(20) << b.plotnames.at(i) << setw(40) << b.cuts.at(i) << setw(40) << b.plotlabels.at(i) << endl;
    }
    return os;
  }

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct Category{
  // struct to store information of a selection category

  TString name;   // name of the category
  TString cut;    // cut string for this category
  TString label;  // label: TO_BE_IMPLEMENTED

  BinInfo bin;    // binning infomation

  Category() {}
  Category(TString name, TString cut, TString label = "") : name(name), cut(cut), label(label!=""?label:name) {}
  Category(TString name, TString cut, TString label, BinInfo bin) : name(name), cut(cut), label(label), bin(bin) {}

  // dummy category with no selection
  static Category dummy_category(){
    return Category("", "(1==1)", "");
  }
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct Sample{
  // struct to store information of a sample (ROOT trees)

  TString label;  // plotting label for the sample, e.g., t#bar{t}
  TString fname;  // filename
  TString wgtvar; // weight variable for getting yields/plotting
  TString sel;    // sample-specific selection string

  TFile*  infile; // the root file
  TTree*  tree;   // the tree

  Sample() : infile(nullptr), tree(nullptr) {}
  Sample(TString label, TString fname, TString wgtvar, TString sel = "") :
    label(label), fname(fname), wgtvar(wgtvar), sel(sel), infile(nullptr), tree(nullptr) {}

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct BaseConfig {
  // base class to store configurations (samples, selection, categories, etc...)

  BaseConfig():
    inputdir("/tmp/trees"),
    outputdir("/tmp/plots"),
    plotFormat("pdf"),
    header(""),
    nbins_(0)
  {}

  void addSample(TString name, TString label, TString file, TString wgtvar, TString extraCut){
    // add data/MC sample to the *sample* map, e.g.
    // addSample("ttbar",     "t#bar{t}",    "lepcr/ttbar-mg",                                   "2.3*weight",      "nvetolep>0");
    //     *key of the map*   *plot label*   *filepath (postfix "_tree.root" added by default)*  *weight variable*  *extra selection*

    Sample sample(label, file, wgtvar, extraCut);
    TString filepath = inputdir+"/"+sample.fname+"_tree.root";
    sample.infile = TFile::Open(filepath);
    assert(sample.infile);
    sample.tree = (TTree*)sample.infile->Get("Events");
    assert(sample.tree);
    sample.tree->SetTitle(name);
    samples[name] = sample;

    cerr << "### Open file " << filepath << " as *" << name << "*" << endl;
  }

  unsigned nbins(){
    // return the total number of bins
    if (nbins_==0){
      for (auto &cat : catMaps)
        nbins_ += cat.second.bin.nbins;
    }
    return nbins_;
  }

  void reset(){
    sbin = BinInfo();
    samples.clear();
    categories.clear();
    catMaps.clear();
    nbins_ = 0;
  }

public:

  TString sel;    // baseline selection

  BinInfo sbin;   // TO_BE_IMPLEMENTED?

  map<TString, Sample> samples;     // map of samples

  vector<TString> categories;       // category names (use vector to *keep the order*)
  map<TString, Category> catMaps;   // map from category names to the Category struct
  map<TString, Category> crCatMaps; // map from category names to the Category struct for the control region

  TString inputdir;                 // location of ROOT trees
  TString outputdir;                // location of output plots
  TString plotFormat;               // format of plots

  TString header;                   // header to draw on the plots

private:
  unsigned nbins_;

};

}
#endif /*ESTTOOLS_CONFIG_H_*/
