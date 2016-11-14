#include "../utils/EstHelper.hh"
#include "LMParameters_SSR.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_SSR(TString inputFile="/tmp/SSR/LowMass/sig/fbd_pred_lepplusmet.root", TString outputName="/tmp/SSR/LowMass/LM_SSR"){

  LOG_YMIN = 0.1;

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.13;
  RATIOPLOT_XLABEL_OFFSET = 0.04;
  PAD_SPLIT_Y = 0.31;
  PAD_BOTTOM_MARGIN = 0.38;


  vector<TString> bkgs = {"rare_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  vector<TString> sigs = {"T2fbd_375_295", "T2fbd_375_325", "T2fbd_375_355"};
  TString data = "data";

  vector<TString> bkglabels = {"Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2fbd(375,295)", "T2fbd(375,325)", "T2fbd(375,355)"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"_"};
  vector<TString> splitlabels = {
      "",
  };

  TLatex tl;
  tl.SetTextSize(0.03);
  tl.SetTextAlign(21);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){
      tl.DrawLatexNDC(0.37, 0.69, "N_{b} #geq 1, N_{b}^{L} = 1");
      tl.DrawLatexNDC(0.37, 0.65, "p_{T}(j_{ISR}) > 250");
      drawTLatexNDC("p_{T}(b) < 40", 0.23, 0.60, 0.025); drawTLatexNDC("40 #leq p_{T}(b) < 70", 0.4, 0.60, 0.025);

      tl.DrawLatexNDC(0.77, 0.69, "N_{b} #geq 1, N_{b}^{L} #geq 2");
      tl.DrawLatexNDC(0.77, 0.65, "p_{T}(j_{ISR}) > 250");
      drawTLatexNDC("p_{T}(b_{12}) < 100", 0.62, 0.60, 0.025); drawTLatexNDC("100 #leq p_{T}(b_{12}) < 160", 0.79, 0.60, 0.025);

    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){
      ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
      drawLine(3,  LOG_YMIN, 3,  1000);
      drawLine(6,  LOG_YMIN, 6,  40000);
      drawLine(9,  LOG_YMIN, 9,  1000);
      c->cd();
    },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    pred.push_back((TH1*)f->Get(b));
  }
  TH1* hdata = (TH1*)f->Get(data);
  TGraphAsymmErrors* unc   = (TGraphAsymmErrors*)f->Get("bkgtotal_unc_sr");
  for (auto &s : sigs){
    TH1 *h = (TH1*)f->Get(s);
    h->SetLineStyle(kDashed);
    hsigs.push_back(h);
  }

  prepHists(pred, false, false, true);
  prepHists({hdata}, false, false, false, {kBlack});
  prepHists(hsigs, false, false, false, {kGreen+3, kViolet-1, kRed});
  setBinLabels(hdata, xlabels);
  hdata->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");

  // plot raw MC
//  TH1 *hmctotal = nullptr;
//  for(auto &mc : mcs){
//    if (!hmctotal) hmctotal = (TH1*)f->Get(mc)->Clone();
//    else hmctotal->Add((TH1*)f->Get(mc));
//  }

//  TH1* hDataRawMC = (TH1*)hdata->Clone("hDataRawMC");
//  hDataRawMC->Divide(hmctotal);
//  hDataRawMC->SetLineWidth(2);
//  prepHists({hDataRawMC}, false, false, false, {kOrange});

  auto catMap = srCatMap();
  for (unsigned ireg = 0; ireg < split.size(); ++ireg){
    auto &region = split.at(ireg);
    int xlow = 0, xhigh = 0;
    bool isfirst = true;
    int ibin = 0;
    for (auto &cat_name : srbins){
      auto nbins = catMap.at(cat_name).bin.nbins;
      if (cat_name.Contains(TRegexp(region))){
        if (isfirst){
          isfirst = false;
          xlow = ibin;
          xhigh = xlow + nbins;
        }else{
          xhigh += nbins;
        }
      }
      ibin += nbins;
    }

    auto leg = prepLegends({hdata}, datalabel, "LP");
    appendLegends(leg, pred, bkglabels, "F");
    appendLegends(leg, hsigs, siglabels, "L");
//    appendLegends(leg, {hDataRawMC}, {"Simulation", "L"});
  //  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.51, 0.69, 0.94, 0.87);

    auto c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, xlow, xhigh, hsigs, unc);
    c->SetCanvasSize(900, 600);
//    drawText(splitlabels.at(ireg), 0.18, 0.69);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
