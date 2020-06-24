#ifndef ESTTOOLS_ESTHELPER_HH_
#define ESTTOOLS_ESTHELPER_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <memory>
#include <chrono>
#include <functional>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <TTreeFormula.h>

#include "json.hpp"
#include "MiniTools.hh"

#define DEBUG_

// show overall data/MC SF on plot
//#define SHOW_DATA_MC_RATIO

using namespace std;
#endif

namespace EstTools{

double PLOT_MAX_YSCALE = 1.25;

double PAD_SPLIT_Y = 0.3;
double PAD_BOTTOM_MARGIN = 0.30;

double RATIOPLOT_XLABEL_FONTSIZE = 0.10;
double RATIOPLOT_XLABEL_OFFSET = 0.01;
double RATIOPLOT_XTITLE_OFFSET = 0.85;
double RATIO_YMIN = 0;
double RATIO_YMAX = 1.999;

double LOG_YMIN = 0.01;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Quantity getYields(TTree *intree, TString wgtvar, TString sel){
  assert(intree);

  TH1D htmp("htmp", "htmp", 1, 0, 1e9);
  htmp.Sumw2();

  TString cutstr = wgtvar + "*(" + sel + ")";
  intree->Project("htmp", wgtvar, cutstr, "e");
  double err = 0.0;
  double val = htmp.IntegralAndError(0, htmp.GetNbinsX()+1, err);
#ifdef DEBUG_
  cout << intree->GetTitle() << ": " << cutstr << " --> " << Quantity(val, err) << endl;
#endif
  return Quantity(val, err);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<Quantity> getYieldVector(const std::unique_ptr<TTree>& intree, TString wgtvar, TString sel, const BinInfo &bin){
  assert(intree);

  TH1D htmp("htmp", "htmp", bin.nbins, bin.plotbins.data());
  htmp.Sumw2();
  TString cutstr = wgtvar + "*(" + sel + ")";
  auto nentries = intree->Project("htmp", bin.var, cutstr, "e");

  addOverflow(&htmp);

  vector<Quantity> yields;
  for (unsigned i=0; i<bin.nbins; ++i)
    yields.push_back(getHistBin(&htmp, i+1));
#ifdef DEBUG_
  stringstream ss;
  ss << intree->GetTitle() << ": " << cutstr << ", " << bin.var << ", entries=" << nentries << endl
       << "  --> " << yields << endl;
  cerr << ss.str();
#endif

  return yields;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//vector<Quantity> getYieldVector(TTree *intree, TString wgtvar, TString sel, const BinInfo &bin){
//  assert(intree);
//
//  auto start = chrono::steady_clock::now();
//
//  vector<double> weights(bin.nbins, 0);
//  vector<double> sumsqrs(bin.nbins, 0);
//
//  TTreeFormula fwgt("wgt", wgtvar, intree);
//  fwgt.GetNdata();
//  vector<std::shared_ptr<TTreeFormula>> formulas;
//  for (unsigned ibin=0; ibin<bin.nbins; ++ibin){
//    formulas.emplace_back(new TTreeFormula(bin.plotnames.at(ibin), sel + " && " + bin.cuts.at(ibin), intree));
//    formulas.back()->GetNdata();
//  }
//
//  for (Long64_t i=0; i<intree->GetEntries(); ++i){
//    intree->GetEntry(i);
//    double weight = fwgt.EvalInstance();
//    for (unsigned ibin=0; ibin<bin.nbins; ++ibin){
//      auto &f = formulas.at(ibin);
//      if (f->EvalInstance()){
//        weights.at(ibin) += weight;
//        sumsqrs.at(ibin) += weight*weight;
//      }
//    }
//  }
//
//  vector<Quantity> yields;
//  for (unsigned ibin=0; ibin<bin.nbins; ++ibin){
//    yields.emplace_back(weights.at(ibin), std::sqrt(sumsqrs.at(ibin)));
//  }
//
//#ifdef DEBUG_
//  cout << intree->GetTitle() << ": " << sel << ", " << bin.var << endl
//       << "  --> " << yields << endl;
//#endif
//  auto end = chrono::steady_clock::now();
//  auto diff = end - start;
//  cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
//
//  return yields;
//}
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Quantity getEfficiency(TTree *t, TString wgtvar, TString basesel, TString extrasel){
  return getYields(t, wgtvar, basesel+" && "+extrasel) / getYields(t, wgtvar, basesel);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* getHist(TTree *intree, TString plotvar, TString wgtvar, TString sel, TString hname, TString title, int nbinsx, double xmin, double xmax){
  TH1D* hist = new TH1D(hname, title, nbinsx, xmin, xmax);
  TString cutstr = wgtvar + "*(" + sel + ")";
#ifdef DEBUG_
  cout << hname << endl << intree->GetTitle() << ": " << cutstr << endl;
#endif
  intree->Project(hname, plotvar, cutstr, "e");
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* getHist(TTree *intree, TString plotvar, TString wgtvar, TString sel, TString hname, TString title, std::vector<double> xbins){
  TH1D* hist = new TH1D(hname, title, xbins.size()-1, xbins.data());
  TString cutstr = wgtvar + "*(" + sel + ")";
#ifdef DEBUG_
  cout << hname << endl << intree->GetTitle() << ": " << cutstr << endl;
#endif
  intree->Project(hname, plotvar, cutstr, "e");
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH2D* getHist2D(TTree *intree, TString plotvar, TString wgtvar, TString sel, TString hname, TString title, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax){
  TH2D* hist = new TH2D(hname, title, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
  TString cutstr = wgtvar + "*(" + sel + ")";
#ifdef DEBUG_
  cout << hname << endl << intree->GetTitle() << ": " << cutstr << endl;
#endif
  intree->Project(hname, plotvar, cutstr, "e");
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH2D* getHist2D(TTree *intree, TString plotvar, TString wgtvar, TString sel, TString hname, TString title, std::vector<double> xbins, std::vector<double> ybins){
  TH2D* hist = new TH2D(hname, title, xbins.size()-1, xbins.data(), ybins.size()-1, ybins.data());
  TString cutstr = wgtvar + "*(" + sel + ")";
#ifdef DEBUG_
  cout << hname << endl << intree->GetTitle() << ": " << cutstr << endl;
#endif
  intree->Project(hname, plotvar, cutstr, "e");
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<TH1*> makeRatioHists(vector<TH1*> num, vector<TH1*> denom, TString option = ""){
  assert(num.size() == denom.size());
  vector<TH1*> ratios;
  for (unsigned i=0; i<num.size(); ++i){
    auto hnew = (TH1*)num.at(i)->Clone(num.at(i)->GetName() + TString("__over__") + denom.at(i)->GetName());
    hnew->Divide(hnew, denom.at(i), 1, 1, option);
    ratios.push_back(hnew);
  }
  return ratios;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<TH1*> makeRatioHists(vector<TH1*> num, TH1* denom, TString option = ""){
  assert(denom);
  vector<TH1*> ratios;
  for (unsigned i=0; i<num.size(); ++i){
    auto hnew = (TH1*)num.at(i)->Clone(num.at(i)->GetName() + TString("__over__") + denom->GetName());
    hnew->Divide(hnew, denom, 1, 1, option);
    ratios.push_back(hnew);
  }
  return ratios;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* makeRatioHists(TH1* num, TH1* denom, TString option = ""){
  assert(num && denom);
  auto hnew = (TH1*)num->Clone(num->GetName() + TString("__over__") + denom->GetName());
  hnew->Divide(hnew, denom, 1, 1, option);
  return hnew;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* makeRatioHists(TH1* nonTTbar, TH1* TTbar, TH1* data, TString option = ""){
  //(data - non-ttbar MC)/ttbar
  cout << "____Ratio: (data - non-ttbar MC)/ttbar " << endl;
  assert(nonTTbar && data && TTbar);
  auto hnum = (TH1*)data->Clone(data->GetName() + TString("__num__"));
  hnum->Add(nonTTbar, -1);
  hnum->Divide(hnum, TTbar, 1, 1, option);
  return hnum;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawComp(vector<TH1*> inhists, TLegend *leg = 0)
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;

  vector<TH1*> hists;
  for (auto *h : inhists) hists.push_back((TH1*)h->Clone());

  auto c = MakeCanvas();
  c->cd();
  double ymax = 0;
  for (auto *h : hists){
    if (getHistMaximumPlusError(h)>ymax) ymax = getHistMaximumPlusError(h);
  }
  cout << "plotMax: " << plotMax << ", ymax: " << ymax << endl;
  bool isFirst = true;
  for (auto *h : hists){
    h->SetLineWidth(3);
    h->GetXaxis()->SetTitleFont(42);
    h->GetYaxis()->SetTitleFont(42);
    h->GetXaxis()->SetLabelFont(42);
    h->GetYaxis()->SetLabelFont(42);
    if (isFirst){
      isFirst = false;
      h->GetYaxis()->SetRangeUser(0,plotMax*ymax);
      h->Draw("histe");
    }
    h->Draw("histesame");
#ifdef DEBUG_
    cout << "-->drawing drawComp: "<< h->GetName() << endl;
#endif
  }
  if (leg) leg->Draw();
#ifdef TDR_STYLE_
  CMS_lumi(c, 4, 10);
#endif
  return c;
}

TCanvas* drawCompMatt(vector<TH1*> inhists, TLegend *leg = 0, float logymin = -1., std::function<void(TCanvas*)> *plotextra = nullptr, TString drawType = "hist")
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;

  vector<TH1*> hists;
  for (auto *h : inhists) hists.push_back((TH1*)h->Clone());

  auto c = MakeCanvas();
  c->cd();
  double ymax = 0;
  for (auto *h : hists){
    if (getHistMaximumPlusError(h)>ymax) ymax = getHistMaximumPlusError(h);
  }
  bool isFirst = true;
  for (auto *h : hists){
    h->SetLineWidth(3);
    h->GetXaxis()->SetTitleFont(42);
    h->GetYaxis()->SetTitleFont(42);
    h->GetXaxis()->SetLabelFont(42);
    h->GetYaxis()->SetLabelFont(42);
    if (isFirst){
      isFirst = false;
      h->GetYaxis()->SetRangeUser(0,1.25*ymax);
      if(logymin>0) {
        float gap = 0.20;
        h->GetYaxis()->SetRangeUser(0., (logymin > 0 ? pow(ymax,1./(1.-gap))*pow(logymin,-gap/(1.-gap)) : 1.5*ymax));
        h->SetMinimum(logymin);
        gPad->SetLogy(1);
      }
      h->Draw(drawType);
    }
    h->Draw(drawType + "same");
#ifdef DEBUG_
    cout << "-->drawing drawComp: "<< h->GetName() << endl;
#endif
  }
  if (leg) leg->Draw();
#ifdef TDR_STYLE_
  CMS_lumi(c, 4, 10);
#endif
  if (plotextra) (*plotextra)(c);
  c->Update();

  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawComp(vector<TGraph*> inhists, TLegend *leg = 0)
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;

  vector<TGraph*> hists;
  for (auto *h : inhists) hists.push_back((TGraph*)h->Clone());

  auto c = MakeCanvas();
  c->cd();
  double ymax = 0;
  for (auto *h : hists){
    if (h->GetMaximum()>ymax) ymax = h->GetMaximum();
  }
  bool isFirst = true;
  for (auto *h : hists){
    h->SetLineWidth(2);
    if (isFirst){
      isFirst = false;
      h->GetYaxis()->SetRangeUser(0,plotMax*ymax);
      h->Draw();
    }
    h->Draw("same");
#ifdef DEBUG_
    cout << "-->drawing: "<< h->GetName() << endl;
#endif
  }
  if (leg) leg->Draw();
#ifdef TDR_STYLE_
  CMS_lumi(c, 4, 10);
#endif

  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawCompAndRatio(vector<TH1*> inhists, vector<TH1*> inratiohists, TLegend *leg = 0, TString ratioYTitle = "Ratio", double lowY = RATIO_YMIN, double highY=RATIO_YMAX, bool showErrorBarInRatio=true, float logymin = -1., float forceymax = -1., bool isVal = false, TGraphAsymmErrors* inUnc=nullptr, bool ratiolog = false)
{

  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;

  vector<TH1*> hists, ratiohists;
  for (auto *h : inhists) hists.push_back((TH1*)h->Clone());
  for (auto *h : inratiohists) ratiohists.push_back((TH1*)h->Clone());

  auto c = MakeCanvas();
  c->cd();
  TPad *p1 = new TPad("p1","p1",0,PAD_SPLIT_Y,1,1);
  p1->SetLeftMargin  (0.16);
  p1->SetTopMargin   (0.10);
  p1->SetRightMargin (0.04);
  p1->SetBottomMargin(0.03);
  p1->Draw();
  p1->cd();
  //  c->SetLogx(fLogx);
  // c->SetLogy(fLogy);
  double ymax = 0;
  for (auto *h : hists){
    if (getHistMaximumPlusError(h)>ymax) ymax = getHistMaximumPlusError(h);
  }
  bool isFirst = true;
  double val = 0.;
  for (auto *h : hists){
    double m = h->GetMaximum();
    val = m > val ? m : val;
  }

  int nbin = 0;
  for (auto *h : hists){
    nbin = h->GetNbinsX();
    h->SetLineWidth(2);
    h->GetXaxis()->SetLabelOffset(0.20);
    if (isFirst){
      isFirst = false;
      if(isVal){
	double m = 1 + std::max(h->GetMaximum() - 1, 1 - h->GetMinimum());
        val = m > val ? m : val;
	double max = val > 1 ? val : 1 + (1 - val);
	double min = val > 1 ? 1 - (val - 1) : 1 - (1 - val);
	h->GetYaxis()->SetRangeUser(0.85*min, 1.15*max);
	h->SetMinimum(0.85*min);
      }
      if(!isVal) h->GetYaxis()->SetRangeUser(0,plotMax*ymax);
      if(forceymax>0) h->GetYaxis()->SetRangeUser(0,plotMax*forceymax);
      if(logymin>0) {
        float gap = 0.40;
        h->GetYaxis()->SetRangeUser(0., (logymin > 0 ? pow(ymax,1./(1.-gap))*pow(logymin,-gap/(1.-gap)) : 1.5*ymax));
        h->SetMinimum(logymin);
        gPad->SetLogy(1);
      }
      h->Draw("histe");
    }
    h->Draw("histesame");
#ifdef DEBUG_
    cout << "-->drawing drawCompAndRatio: "<< h->GetName() << endl;
#endif
  }

  if(inUnc){
    TGraphAsymmErrors *unc = inUnc;
    unc->SetFillColor(kBlue);
    unc->SetFillStyle(3013);
    unc->SetLineStyle(0);
    unc->SetLineWidth(0);
    unc->SetMarkerSize(0);
    unc->Draw("E2same");
    if(leg) addLegendEntry(leg, unc,"Bkg. uncertainty","F");
  }

  if (leg) leg->Draw();

#ifdef TDR_STYLE_
  if(!isVal) CMS_lumi(p1, 4, 10);
#endif

  c->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,PAD_SPLIT_Y);
  p2->SetLeftMargin  (0.16);
  p2->SetTopMargin   (0.00);
  p2->SetRightMargin (0.04);
  p2->SetBottomMargin(PAD_BOTTOM_MARGIN);
  p2->SetGridy(1);
  p2->Draw();
  p2->cd();
  isFirst = true;
  TString drawOpt = showErrorBarInRatio?"E":"hist";
  if(isVal) gStyle->SetOptStat(0);
  for (auto *h : ratiohists){
    if (isFirst) {
      isFirst = false;
      h->SetTitleSize  (0.10,"Y");
      h->SetTitleOffset(0.70,"Y");
      h->SetTitleSize  (0.14,"X");
      h->SetTitleOffset(0.85,"X");
      h->SetLabelSize  (0.10,"X");
      h->SetLabelSize  (0.12,"Y");
      h->GetYaxis()->SetTitleFont(42);
      h->GetYaxis()->CenterTitle(kTRUE);
      h->GetXaxis()->SetTitleFont(42);
      h->GetYaxis()->SetNdivisions(305);
      h->GetYaxis()->SetTitle(ratioYTitle);
      h->GetYaxis()->SetRangeUser(lowY, highY);
      if(ratiolog) {
        float gap = 0.10;
        h->GetYaxis()->SetRangeUser(0., (lowY > 0 ? pow(highY,1./(1.-gap))*pow(lowY,-gap/(1.-gap)) : 1.5*highY));
        h->SetMinimum(lowY);
        gPad->SetLogy(1);
        h->GetYaxis()->SetMoreLogLabels();
      }

#ifdef TDR_STYLE_
      h->GetXaxis()->SetTitleFont(42);
      h->GetYaxis()->SetTitleFont(42);
      h->GetXaxis()->SetLabelFont(42);
      h->GetYaxis()->SetLabelFont(42);
#endif

      h->Draw(drawOpt);

      double xmin = h->GetXaxis()->GetXmin();
      double xmax = h->GetXaxis()->GetXmax();
      TLine *l = new TLine(xmin,1,xmax,1);
      l->SetLineWidth(3);
      l->Draw("same");
    }
    h->Draw(drawOpt+"same");
#ifdef DEBUG_
    cout << "-->drawing RATIO drawCompAndRatio: "<< h->GetName() << endl;
#endif
  }

  if(inUnc){
    TGraphAsymmErrors* hRelUnc = (TGraphAsymmErrors*)inUnc->Clone();
    for (int i=0; i < hRelUnc->GetN(); ++i){
      auto val = hRelUnc->GetY()[i];
      auto errUp = hRelUnc->GetErrorYhigh(i);
      auto errLow = hRelUnc->GetErrorYlow(i);
      if (val==0) continue;
      hRelUnc->SetPointEYhigh(i, errUp/val);
      hRelUnc->SetPointEYlow(i, errLow/val);
      hRelUnc->SetPoint(i, hRelUnc->GetX()[i], (1) );
    }
    hRelUnc->SetFillColor(kBlue);
    hRelUnc->SetFillStyle(3013);
    hRelUnc->SetLineStyle(0);
    hRelUnc->SetLineWidth(0);
    hRelUnc->SetMarkerSize(0);
    hRelUnc->Draw("E2same");
  }

  c->Update();
  c->cd();
  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawStack(vector<TH1*> bkghists, vector<TH1*> sighists, bool plotlog = false, TLegend *leg = 0)
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;
  TH1* hbkgtotal = nullptr;
  THStack* hstack = new THStack(bkghists.front()->GetName()+TString("_stack"), bkghists.front()->GetTitle());
  for (auto *h : bkghists){
    auto *hmc = (TH1*)h->Clone();
    if (!hbkgtotal)
      hbkgtotal = (TH1*)hmc->Clone("hbkgtotal");
    else
      hbkgtotal->Add(hmc);
//    if (hmc->GetLineColor()!=kBlack){
//      hmc->SetFillColor(hmc->GetLineColor()); hmc->SetFillStyle(1001); hmc->SetLineColor(kBlack);
//    }
    hstack->Add(hmc);
  }

  auto c = MakeCanvas();
  c->cd();
  c->SetLogy(plotlog);
  double ymax = hbkgtotal->GetMaximum();
  for (auto *h : sighists){
    if (h->GetMaximum()>ymax) ymax = h->GetMaximum();
  }
  hbkgtotal->SetLineColorAlpha(kWhite,0);
  hbkgtotal->SetMarkerColorAlpha(kWhite,0);
  hbkgtotal->SetMaximum(ymax*(plotlog ? plotMax*100000: plotMax));
  hbkgtotal->SetMinimum(plotlog ? LOG_YMIN : 0);
  hbkgtotal->Draw("hist");
  hstack->Draw("histsame");
#ifdef DEBUG_
  cout << "-->drawing drawStack: "<< hstack->GetName() << endl;
#endif

  for (auto *sig : sighists){
    auto h = (TH1*)sig->Clone();
    h->SetLineWidth(3);
    h->Draw("histsame");
#ifdef DEBUG_
  cout << "-->drawing drawStack: "<< h->GetName() << endl;
#endif
  }

#ifdef TDR_STYLE_
  hbkgtotal->SetFillColor(kBlue);
  hbkgtotal->SetFillStyle(3013);
  hbkgtotal->SetLineStyle(0);
  hbkgtotal->SetLineWidth(0);
  hbkgtotal->SetMarkerSize(0);
  hbkgtotal->Draw("E2same");
  if(leg) addLegendEntry(leg, hbkgtotal,"Bkg. uncertainty","F");

  CMS_lumi(c, 4, 10);
#endif
  if (leg) leg->Draw();

  c->RedrawAxis();
  c->Update();
  c->cd();

  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawStackAndRatio(vector<TH1*> inhists, TH1* inData, TLegend *leg = 0, bool plotlog = false, TString ratioYTitle = "N_{obs}/N_{exp}", double lowY = RATIO_YMIN, double highY = RATIO_YMAX, double lowX = 0, double highX = -1, vector<TH1*> sighists={}, TGraphAsymmErrors* inUnc=nullptr, vector<TH1*> inRatios = {}, TGraphAsymmErrors* inRelUnc=nullptr, bool diffRatio = false, bool ttbarRatio = false, bool finalPlot = false, bool manualLabelChange = false)
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;
  TH1* hData = inData ? (TH1*)inData->Clone() : nullptr;
  TH1* hbkgtotal = nullptr;
  TH1* hnonttbar = nullptr;
  TH1* httbar = nullptr;
  TString name = "";
  THStack* hstack = new THStack(inhists.front()->GetName()+TString("_stack"), inhists.front()->GetTitle());
  for (auto *h : inhists){
    auto *hmc = (TH1*)h->Clone();
    name = hmc->GetName();
    if (!hbkgtotal)
      hbkgtotal = (TH1*)hmc->Clone("hbkgtotal");
    else
      hbkgtotal->Add(hmc);

    if(ttbarRatio && TString(hmc->GetName()).Contains("ttbar"))
      httbar = (TH1*)hmc->Clone("httbar");
    else if (!hnonttbar)
      hnonttbar = (TH1*)hmc->Clone("hnonttbar");
    else
      hnonttbar->Add(hmc);
    if (hmc->GetLineColor()!=kBlack){
      hmc->SetFillColor(hmc->GetLineColor()); hmc->SetFillStyle(1001); hmc->SetLineColor(kBlack);
    }
    hstack->Add(hmc);
  }

  auto c = MakeCanvas();
  c->cd();
  TPad *p1 = new TPad("p1","p1",0,PAD_SPLIT_Y,1,1);
  p1->SetLeftMargin  (0.16);
  p1->SetTopMargin   (0.10);
  p1->SetRightMargin (0.04);
  p1->SetBottomMargin(0.03);
  p1->Draw();
  p1->SetLogy(plotlog);
  p1->cd();
  double ymax = hData ? getHistMaximumPlusError(hData) : 0;
  if(hbkgtotal->GetMaximum()>ymax) ymax=hbkgtotal->GetMaximum();
  for (auto *h : sighists){
    if (h->GetMaximum()>ymax) ymax = h->GetMaximum();
  }
  hbkgtotal->SetMaximum(ymax*(plotlog ? plotMax*10000 : plotMax));
  hbkgtotal->SetMinimum(plotlog? LOG_YMIN : 0);
  if(lowX<highX) hbkgtotal->GetXaxis()->SetRangeUser(lowX, highX);
  hbkgtotal->GetXaxis()->SetLabelOffset(0.20);
  hbkgtotal->GetYaxis()->SetTitleSize(0.08);
  hbkgtotal->GetYaxis()->SetTitleOffset(0.85);
  hbkgtotal->GetYaxis()->SetLabelSize  (0.06);
  TGaxis::SetMaxDigits(4);
  hbkgtotal->Draw("hist");

  hstack->Draw("histsame");

  for (auto *sig : sighists){
    auto h = (TH1*)sig->Clone();
    h->SetLineWidth(3);
    h->Draw("histsame");
#ifdef DEBUG_
  cout << "-->drawing drawStacKAndRatio sighist: "<< h->GetName() << endl;
#endif
  }

#ifdef TDR_STYLE_
  TGraphAsymmErrors *unc = inUnc ? inUnc : new TGraphAsymmErrors(hbkgtotal);
  unc->SetFillColor(kBlue);
  unc->SetFillStyle(3013);
  unc->SetLineStyle(0);
  unc->SetLineWidth(0);
  unc->SetMarkerSize(0);
  unc->Draw("E2same");
  if(leg) addLegendEntry(leg, unc,"Bkg. uncertainty","F");

  if (hData){
    TH1F *h00 = (TH1F*)hData->Clone("data0");
    TGraphAsymmErrors* gr = getAsymmErrors(h00);
    gr->SetMarkerStyle(20);
    if(finalPlot) gr->SetMarkerStyle(7);
    gr->SetLineWidth(hData->GetLineWidth());
    gr->SetFillStyle(0);
    SetEx(gr, 0.);
    gr->Draw("PZ0same");
  }
  CMS_lumi(p1, 4, 10);
#else
  if(hData) hData->Draw("Esame");
#endif
  if (leg) leg->Draw();

  p1->SetTicks(1, 1);
  if(finalPlot){ 
    p1->SetTicks(1, 0);
    hbkgtotal->Draw("AXISsame");
  }
  p1->RedrawAxis();
  p1->RedrawAxis("G");

#ifdef DEBUG_
  cout << "-->drawing drawStackAndRatio stack: "<< hstack->GetName() << endl;
#endif

  c->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,PAD_SPLIT_Y);
  p2->SetLeftMargin  (0.16);
  p2->SetTopMargin   (0.00);
  p2->SetRightMargin (0.04);
  p2->SetBottomMargin(PAD_BOTTOM_MARGIN);
  p2->SetGridy(1);
  p2->Draw();
  p2->cd();

#ifdef TDR_STYLE_
  TH1 *haxis = (TH1*)hbkgtotal->Clone("htmpaxis");
  if (ttbarRatio){
    haxis->SetTitleSize  (0.08,"Y");
    haxis->SetTitleOffset(0.60,"Y");
  } else{ 
    haxis->SetTitleSize  (0.14,"Y");
    haxis->SetTitleOffset(0.41,"Y");
  }
  haxis->SetTitleSize  (0.14,"X");
  haxis->SetTitleOffset(RATIOPLOT_XTITLE_OFFSET,"X");
  haxis->SetLabelSize  (RATIOPLOT_XLABEL_FONTSIZE,"X");
  haxis->SetLabelOffset(RATIOPLOT_XLABEL_OFFSET, "X");
  haxis->SetLabelSize  (0.12,"Y");
  haxis->GetYaxis()->CenterTitle(kTRUE);
  haxis->GetYaxis()->SetNdivisions(304);
  haxis->GetYaxis()->SetTitle(ratioYTitle);
  haxis->GetXaxis()->SetTitleFont(42);
  haxis->GetYaxis()->SetTitleFont(42);
  haxis->GetXaxis()->SetLabelFont(42);
  haxis->GetYaxis()->SetLabelFont(42);
  haxis->GetYaxis()->SetRangeUser(lowY,highY);
  if(lowX<highX) haxis->GetXaxis()->SetRangeUser(lowX, highX);
  if(manualLabelChange){
    if(name.Contains("nTop") || name.Contains("nW") || name.Contains("nResolved")){
      haxis->GetXaxis()->ChangeLabel(1, -1, 0.);
      haxis->GetXaxis()->ChangeLabel(3, -1, 0.);
      haxis->GetXaxis()->ChangeLabel(5, -1, 0.);
      haxis->GetXaxis()->ChangeLabel(7, -1, 0.);
      haxis->GetXaxis()->ChangeLabel(6, -1, -1, -1, 1, -1, "2+");
    } else if(name.Contains("MET")){
      haxis->GetXaxis()->ChangeLabel(8, -1, -1, -1, 1, -1, "#infty");
    }
    if((lowX == 0 && highX == 53) || (lowX == 105 && highX == 153)){
      haxis->GetXaxis()->ChangeLabel(1, -1, 0.);  
    }

  }
  haxis->Draw("AXIS");

  if (inData){
    TH1 *h3 = (TH1*)inData->Clone("data3");

    TGraphAsymmErrors* ratio;
    if (ttbarRatio){
      TH1* hnonttbarNoError = (TH1*)hnonttbar->Clone("hnonttbarNoError");
      TH1* httbarNoError = (TH1*)httbar->Clone("httbarNoError");
      for (int i=1; i < hnonttbarNoError->GetNbinsX()+1; ++i) hnonttbarNoError->SetBinError(i, 0);
      for (int i=1; i < httbarNoError->GetNbinsX()+1; ++i) httbarNoError->SetBinError(i, 0);
      ratio = getRatioAsymmErrors(h3, hnonttbarNoError, httbarNoError);
    } else {   
      TH1* hMCNoError = (TH1*)hbkgtotal->Clone("hMCNoError");
      for (int i=1; i < hMCNoError->GetNbinsX()+1; ++i) hMCNoError->SetBinError(i, 0);
      ratio = getRatioAsymmErrors(h3, hMCNoError);
    }
    ratio->SetLineWidth(h3->GetLineWidth());
    SetEx(ratio, 0.);
    if(finalPlot) ratio->SetMarkerStyle(7);
    if(!inRelUnc) ratio->Draw("PZ0same");
  }

  TGraphAsymmErrors* hRelUnc = inRelUnc ? (TGraphAsymmErrors*)inRelUnc->Clone() : (TGraphAsymmErrors*)unc->Clone();
  for (int i=0; i < hRelUnc->GetN(); ++i){
    auto val = hRelUnc->GetY()[i];
    auto errUp = hRelUnc->GetErrorYhigh(i);
    auto errLow = hRelUnc->GetErrorYlow(i);
    if (val==0) continue;
    hRelUnc->SetPointEYhigh(i, errUp/val);
    hRelUnc->SetPointEYlow(i, errLow/val);
    hRelUnc->SetPoint(i, hRelUnc->GetX()[i], (inRelUnc ? 0 : 1) );
  }
  hRelUnc->SetFillColor(kBlue);
  hRelUnc->SetFillStyle(3013);
  hRelUnc->SetLineStyle(0);
  hRelUnc->SetLineWidth(0);
  hRelUnc->SetMarkerSize(0);
  hRelUnc->Draw("E2same");

  p2->SetTicks(1, 1);
  p2->RedrawAxis("G");

#else
  if (inData){
    TH1F* hRatio = nullptr;
    if (diffRatio)       hRatio = new TRatioPlot(inData, hbkgtotal);
    else if (ttbarRatio) hRatio = makeRatioHists(hnonttbar, httbar, inData);
    else 	         hRatio = makeRatioHists(inData, hbkgtotal);
    if (ttbarRatio) hRatio->SetTitleSize  (0.08,"Y");
    else hRatio->SetTitleSize  (0.14,"Y");
    hRatio->SetTitleOffset(0.41,"Y");
    hRatio->SetTitleSize  (0.14,"X");
    hRatio->SetTitleOffset(0.85,"X");
    hRatio->SetLabelSize  (0.10,"X");
    hRatio->SetLabelSize  (0.12,"Y");
    hRatio->GetYaxis()->SetTitleFont(42);
    hRatio->GetYaxis()->CenterTitle(kTRUE);
    hRatio->GetXaxis()->SetTitleFont(42);
    hRatio->GetYaxis()->SetNdivisions(304);
    hRatio->GetYaxis()->SetTitle(ratioYTitle);
    hRatio->GetYaxis()->SetRangeUser(lowY, highY);
    if(lowX<highX) hRatio->GetXaxis()->SetRangeUser(lowX, highX);
    removeBinLabels(hRatio, ".5");
    hRatio->Draw("E");

#ifdef DEBUG_
    cout << "-->drawing RATIO drawStackAndRatio: "<< hRatio->GetName() << endl;
#endif
  }
#endif

  for (const auto& inRatio : inRatios) inRatio->Draw("histsame");

  double xmin = inhists.front()->GetXaxis()->GetXmin();
  double xmax = inhists.front()->GetXaxis()->GetXmax();
  if (lowX<highX) { xmin = lowX; xmax = highX; }
  if (!inRelUnc){
    TLine *l = new TLine(xmin,1,xmax,1);
    l->SetLineWidth(2);
    l->SetLineColor(kBlack);
    l->Draw("same");
  }

  if (hData){
    Quantity q_data, q_mc;
    q_data.value = hData->IntegralAndError(1, hData->GetNbinsX()+1, q_data.error);
    q_mc.value = hbkgtotal->IntegralAndError(1, hbkgtotal->GetNbinsX()+1, q_mc.error);
    auto sf = q_data/q_mc;
    cout << " :: Data/MC = " << sf << endl;
#ifdef SHOW_DATA_MC_RATIO
    drawTLatexNDC(TString::Format("Data/MC=%.2f#pm%.2f", sf.value, sf.error), 0.75, 0.88, 0.08, 11, 0, 42, kRed);
#endif
  }

  c->cd();
  c->Update();
  c->RedrawAxis();
  c->RedrawAxis("G");
  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawStackAndRatio(map<TString, vector<Quantity>> invec, vector<TString> labels, vector<Quantity> vecData, TString ratioYTitle = "N_{obs}/N_{exp}", const BinInfo *bin = nullptr, TString title = ";Search Regions;Events")
{
  vector<TH1*> inhists;
  for (const auto &vec : invec){
    inhists.push_back(convertToHist(vec.second, vec.first + "_tohist", title, bin));
  }
  TH1 *hData = convertToHist(vecData, "data_tohist", title, bin);
  prepHists(inhists, false, false);
  prepHists({hData}, false, false);

  for_each(inhists.begin(), inhists.end(), [](TH1 *h){ h->SetFillColor(h->GetLineColor()); h->SetFillStyle(1001); h->SetLineColor(kBlack);});
  auto leg = prepLegends({hData}, {"Data"}, "EP");
  appendLegends(leg, inhists, labels, "F");
  return drawStackAndRatio(inhists, hData, leg, ratioYTitle);

}

}
#endif /*ESTTOOLS_ESTHELPER_HH_*/
