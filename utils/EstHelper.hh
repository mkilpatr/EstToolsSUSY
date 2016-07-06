#ifndef ESTTOOLS_ESTHELPER_HH_
#define ESTTOOLS_ESTHELPER_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <chrono>
#include <vector>
#include <map>
#include <set>
#include <TTreeFormula.h>

#include "MiniTools.hh"

#define DEBUG_

#define PLOT_MAX_YSCALE 1.25
#define LOG_YMIN 0.01

#define RATIO_YMIN 0
#define RATIO_YMAX 1.999

using namespace std;
#endif

namespace EstTools{

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
vector<Quantity> getYieldVector(TTree *intree, TString wgtvar, TString sel, const BinInfo &bin){
  assert(intree);

  auto start = chrono::steady_clock::now();

  TH1D htmp("htmp", "htmp", bin.nbins, bin.plotbins.data());
  htmp.Sumw2();
  TString cutstr = wgtvar + "*(" + sel + ")";
  auto nentries = intree->Project("htmp", bin.var, cutstr, "e");

  addOverflow(&htmp);

  vector<Quantity> yields;
  for (unsigned i=0; i<bin.nbins; ++i)
  yields.push_back(getHistBin(&htmp, i+1));
#ifdef DEBUG_
  cout << intree->GetTitle() << "(" << intree << ")" << ": " << cutstr << ", " << bin.var << ", entries=" << nentries << endl
       << "  --> " << yields << endl;
#endif

  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;

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
TCanvas* drawComp(vector<TH1*> inhists, TLegend *leg = 0)
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;

  vector<TH1*> hists;
  for (auto *h : inhists) hists.push_back((TH1*)h->Clone());

  auto c = MakeCanvas();
  c->cd();
  double ymax = 0;
  for (auto *h : hists){
    if (h->GetMaximum()>ymax) ymax = h->GetMaximum();
  }
  bool isFirst = true;
  for (auto *h : hists){
    h->SetLineWidth(3);
    if (isFirst){
      isFirst = false;
      h->GetYaxis()->SetRangeUser(0,plotMax*ymax);
      h->Draw("histe");
    }
    h->Draw("histesame");
#ifdef DEBUG_
    cout << "-->drawing: "<< h->GetName() << endl;
#endif
  }
  if (leg) leg->Draw();
  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawCompAndRatio(vector<TH1*> inhists, vector<TH1*> inratiohists, TLegend *leg = 0, TString ratioYTitle = "Ratio", double lowY = RATIO_YMIN, double highY=RATIO_YMAX, bool showErrorBarInRatio=true)
{

  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;

  vector<TH1*> hists, ratiohists;
  for (auto *h : inhists) hists.push_back((TH1*)h->Clone());
  for (auto *h : inratiohists) ratiohists.push_back((TH1*)h->Clone());

  auto c = MakeCanvas();
  c->cd();
  TPad *p1 = new TPad("p1","p1",0,0.3,1,1);
  p1->SetLeftMargin  (0.16);
  p1->SetTopMargin   (0.10);
  p1->SetRightMargin (0.04);
  p1->SetBottomMargin(0.03);
  p1->Draw();
  p1->cd();
  //  c->SetLogx(fLogx);
  //  c->SetLogy(fLogy);
  double ymax = 0;
  for (auto *h : hists){
    if (h->GetMaximum()>ymax) ymax = h->GetMaximum();
  }
  bool isFirst = true;
  for (auto *h : hists){
    h->SetLineWidth(3);
    h->GetXaxis()->SetLabelOffset(0.20);
    if (isFirst){
      isFirst = false;
      h->GetYaxis()->SetRangeUser(0,plotMax*ymax);
      h->Draw("histe");
    }
    h->Draw("histesame");
#ifdef DEBUG_
    cout << "-->drawing: "<< h->GetName() << endl;
#endif
  }
  if (leg) leg->Draw();

#ifdef TDR_STYLE_
  CMS_lumi(p1, 4, 10);
#endif

  c->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,0.3);
  p2->SetLeftMargin  (0.16);
  p2->SetTopMargin   (0.00);
  p2->SetRightMargin (0.04);
  p2->SetBottomMargin(0.30);
  p2->SetGridy(1);
  p2->Draw();
  p2->cd();
  isFirst = true;
  TString drawOpt = showErrorBarInRatio?"E":"hist";
  for (auto *h : ratiohists){
    if (isFirst) {
      isFirst = false;
      h->SetTitleSize  (0.10,"Y");
      h->SetTitleOffset(0.70,"Y");
      h->SetTitleSize  (0.14,"X");
      h->SetTitleOffset(0.85,"X");
      h->SetLabelSize  (0.10,"X");
      h->SetLabelSize  (0.12,"Y");
      h->GetYaxis()->SetTitleFont(62);
      h->GetYaxis()->CenterTitle(kTRUE);
      h->GetXaxis()->SetTitleFont(62);
      h->GetYaxis()->SetNdivisions(305);
      h->GetYaxis()->SetTitle(ratioYTitle);
      h->GetYaxis()->SetRangeUser(lowY, highY);

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
    cout << "-->drawing RATIO: "<< h->GetName() << endl;
#endif
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
  hbkgtotal->SetMaximum(ymax*(plotlog ? plotMax*10000: plotMax));
  hbkgtotal->SetMinimum(plotlog ? LOG_YMIN : 0);
  hbkgtotal->Draw("hist");
  hstack->Draw("histsame");
#ifdef DEBUG_
  cout << "-->drawing: "<< hstack->GetName() << endl;
#endif

  for (auto *sig : sighists){
    auto h = (TH1*)sig->Clone();
    h->SetLineWidth(3);
    h->Draw("histsame");
#ifdef DEBUG_
  cout << "-->drawing: "<< h->GetName() << endl;
#endif
  }

#ifdef TDR_STYLE_
  hbkgtotal->SetFillColor(kBlue);
  hbkgtotal->SetFillStyle(3013);
  hbkgtotal->SetLineStyle(0);
  hbkgtotal->SetLineWidth(0);
  hbkgtotal->SetMarkerSize(0);
  hbkgtotal->Draw("E2same");
  if(leg) addLegendEntry(leg, hbkgtotal,"Bkg. Uncertainty","F");

  CMS_lumi(c, 4, 10);
#endif

  if (leg) leg->Draw();

  c->RedrawAxis();
  c->Update();
  c->cd();

  return c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TCanvas* drawStackAndRatio(vector<TH1*> inhists, TH1* inData, TLegend *leg = 0, bool plotlog = false, TString ratioYTitle = "N_{obs}/N_{exp}", double lowY = RATIO_YMIN, double highY = RATIO_YMAX, double lowX = 0, double highX = -1, vector<TH1*> sighists={}, TH1* inUnc=nullptr, TH1* inRatio = nullptr)
{
  double plotMax = leg?PLOT_MAX_YSCALE/leg->GetY1():PLOT_MAX_YSCALE;
  TH1* hData = (TH1*)inData->Clone();
  TH1* hbkgtotal = nullptr;
  THStack* hstack = new THStack(hData->GetName()+TString("_stack"), hData->GetTitle());
  for (auto *h : inhists){
    auto *hmc = (TH1*)h->Clone();
    if (!hbkgtotal)
      hbkgtotal = (TH1*)hmc->Clone("hbkgtotal");
    else
      hbkgtotal->Add(hmc);
    if (hmc->GetLineColor()!=kBlack){
      hmc->SetFillColor(hmc->GetLineColor()); hmc->SetFillStyle(1001); hmc->SetLineColor(kBlack);
    }
    hstack->Add(hmc);
  }
  auto hMC = (TH1*)hstack->GetStack()->Last();

  auto c = MakeCanvas();
  c->cd();
  TPad *p1 = new TPad("p1","p1",0,0.3,1,1);
  p1->SetLeftMargin  (0.16);
  p1->SetTopMargin   (0.10);
  p1->SetRightMargin (0.04);
  p1->SetBottomMargin(0.03);
  p1->Draw();
  p1->SetLogy(plotlog);
  p1->cd();
  //  c->SetLogx(fLogx);
  //  c->SetLogy(fLogy);
  double ymax = hData->GetMaximum();
  if(hMC->GetMaximum()>ymax) ymax=hMC->GetMaximum();
  for (auto *h : sighists){
    if (h->GetMaximum()>ymax) ymax = h->GetMaximum();
  }
  hData->SetMaximum(ymax*(plotlog ? plotMax*10000 : plotMax));
  hData->SetMinimum(plotlog? LOG_YMIN : 0);
  if(lowX<highX) hData->GetXaxis()->SetRangeUser(lowX, highX);
  hData->GetXaxis()->SetLabelOffset(0.20);
  hData->Draw("E");
  hstack->Draw("histsame");

  for (auto *sig : sighists){
    auto h = (TH1*)sig->Clone();
    h->SetLineWidth(2);
    h->Draw("histsame");
#ifdef DEBUG_
  cout << "-->drawing: "<< h->GetName() << endl;
#endif
  }

#ifdef TDR_STYLE_
  TH1 *unc = inUnc ? inUnc : hbkgtotal;
  unc->SetFillColor(kBlue);
  unc->SetFillStyle(3013);
  unc->SetLineStyle(0);
  unc->SetLineWidth(0);
  unc->SetMarkerSize(0);
  unc->Draw("E2same");
  if(leg) addLegendEntry(leg, unc,"Bkg. Uncertainty","F");

  TH1F *h00 = (TH1F*)hData->Clone("data0");
  TGraphAsymmErrors* gr = getAsymmErrors(h00);
  gr->SetMarkerStyle(20);
  gr->SetLineWidth(hData->GetLineWidth());
  gr->SetFillStyle(0);
  gr->Draw("PZ0same");

  CMS_lumi(p1, 4, 10);
#else
  hData->Draw("same");
#endif
  if (leg) leg->Draw();

#ifdef DEBUG_
  cout << "-->drawing: "<< hstack->GetName() << endl;
#endif

  c->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,0.3);
  p2->SetLeftMargin  (0.16);
  p2->SetTopMargin   (0.00);
  p2->SetRightMargin (0.04);
  p2->SetBottomMargin(0.30);
  p2->SetGridy(1);
  p2->Draw();
  p2->cd();

#ifdef TDR_STYLE_
  TH1 *h3 = (TH1*)inData->Clone("data3");
  h3->SetTitleSize  (0.14,"Y");
  h3->SetTitleOffset(0.41,"Y");
  h3->SetTitleSize  (0.14,"X");
  h3->SetTitleOffset(0.85,"X");
  h3->SetLabelSize  (0.10,"X");
  h3->SetLabelSize  (0.12,"Y");
  h3->GetYaxis()->CenterTitle(kTRUE);
  h3->GetYaxis()->SetNdivisions(305);
  h3->GetYaxis()->SetTitle(ratioYTitle);
  h3->GetXaxis()->SetTitleFont(42);
  h3->GetYaxis()->SetTitleFont(42);
  h3->GetXaxis()->SetLabelFont(42);
  h3->GetYaxis()->SetLabelFont(42);

  TGraphAsymmErrors* ratio;
  TH1* hMCNoError = (TH1*)hbkgtotal->Clone("hMCNoError");
  for (int i=1; i < hMCNoError->GetNbinsX()+1; ++i) hMCNoError->SetBinError(i, 0);
  ratio = getRatioAsymmErrors(h3, hMCNoError);
  ratio->SetLineWidth(h3->GetLineWidth());
  h3->GetYaxis()->SetRangeUser(lowY,highY);
  if(lowX<highX) h3->GetXaxis()->SetRangeUser(lowX, highX);
  h3->Draw("AXIS");
  ratio->Draw("PZ0same");

  TH1* hRelUnc = (TH1*)hbkgtotal->Clone();
  for (int i=0; i < hRelUnc->GetNbinsX()+1; ++i){
    auto val = hRelUnc->GetBinContent(i);
    auto err = hRelUnc->GetBinError(i);
    if (val==0) continue;
    hRelUnc->SetBinError(i, err/val);
    hRelUnc->SetBinContent(i, 1);
  }
  hRelUnc->SetFillColor(kBlue);
  hRelUnc->SetFillStyle(3013);
  hRelUnc->SetLineStyle(0);
  hRelUnc->SetLineWidth(0);
  hRelUnc->SetMarkerSize(0);
  hRelUnc->Draw("E2same");

  p2->RedrawAxis("G");
#else
    auto hRatio = makeRatioHists(inData, hbkgtotal);
    hRatio->SetTitleSize  (0.14,"Y");
    hRatio->SetTitleOffset(0.41,"Y");
    hRatio->SetTitleSize  (0.14,"X");
    hRatio->SetTitleOffset(0.85,"X");
    hRatio->SetLabelSize  (0.10,"X");
    hRatio->SetLabelSize  (0.12,"Y");
    hRatio->GetYaxis()->SetTitleFont(62);
    hRatio->GetYaxis()->CenterTitle(kTRUE);
    hRatio->GetXaxis()->SetTitleFont(62);
    hRatio->GetYaxis()->SetNdivisions(305);
    hRatio->GetYaxis()->SetTitle(ratioYTitle);
    hRatio->GetYaxis()->SetRangeUser(lowY, highY);
    if(lowX<highX) hRatio->GetXaxis()->SetRangeUser(lowX, highX);
    hRatio->Draw("E");
#ifdef DEBUG_
  cout << "-->drawing RATIO: "<< hRatio->GetName() << endl;
#endif
#endif

  if (inRatio) inRatio->Draw("histsame");

  double xmin = inData->GetXaxis()->GetXmin();
  double xmax = inData->GetXaxis()->GetXmax();
  if (lowX<highX) { xmin = lowX; xmax = highX; }
  TLine *l = new TLine(xmin,1,xmax,1);
  l->SetLineWidth(2);
  l->SetLineColor(kBlack);
  l->Draw("same");

  c->cd();
  c->Update();
  c->RedrawAxis();
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
  auto leg = prepLegends({hData}, {"Data"}, "PL");
  appendLegends(leg, inhists, labels, "F");
  return drawStackAndRatio(inhists, hData, leg, ratioYTitle);

}

}
#endif /*ESTTOOLS_ESTHELPER_HH_*/
