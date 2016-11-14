#include "../utils/EstHelper.hh"
#include "LMParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot(TString inputFile="/tmp/plots/LowMass/sig/fbd_pred_lepplusmet.root", TString outputName="/tmp/plots/LowMass/LM_datavspred"){

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

  vector<TString> split = {"nb0", "nb1", "nb2"};
  vector<TString> splitlabels = {
      "N_{b}=0, p_{T}(j_{ISR}) #geq 500 GeV",
      "N_{b}#geq1, N_{b}^{L}=1",
      "N_{b}#geq1, N_{b}^{L}#geq2"
  };

  vector<double> ratioYmax = {2.999, 5.999, 2.999};

  TLatex tl;
  tl.SetTextSize(0.033);
  tl.SetTextAlign(21);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){ tl.DrawLatexNDC(0.36, 0.66, "2-5 jets"); tl.DrawLatexNDC(0.76, 0.66, "#geq 6 jets");},
    [&tl](){ tl.DrawLatexNDC(0.38, 0.67, "250 #leq p_{T}(j_{ISR}) < 500 GeV");
             drawTLatexNDC("p_{T}(b) < 40 GeV", 0.2, 0.62, 0.029); drawTLatexNDC("40 #leq p_{T}(b) < 70 GeV", 0.38, 0.62, 0.029);
             tl.DrawLatexNDC(0.76, 0.67, "p_{T}(j_{ISR}) > 500 GeV");
             drawTLatexNDC("p_{T}(b) < 40 GeV", 0.6, 0.62, 0.029); drawTLatexNDC("40 #leq p_{T}(b) < 70 GeV", 0.77, 0.62, 0.029);
    },
    [&tl](){ tl.DrawLatexNDC(0.38, 0.67, "250 #leq p_{T}(j_{ISR}) < 500 GeV");
             drawTLatexNDC("p_{T}(b_{12}) < 100 GeV", 0.19, 0.62, 0.026); drawTLatexNDC("100 #leq p_{T}(b_{12}) < 160 GeV", 0.365, 0.62, 0.026);
             tl.DrawLatexNDC(0.76, 0.67, "p_{T}(j_{ISR}) > 500 GeV");
             drawTLatexNDC("p_{T}(b_{12}) < 100 GeV", 0.59, 0.62, 0.026); drawTLatexNDC("100 #leq p_{T}(b_{12}) < 160 GeV", 0.761, 0.62, 0.026);
    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(4,  LOG_YMIN, 4,  5000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(12, LOG_YMIN, 12, 1000); drawLine(16, LOG_YMIN, 16, 20000); drawLine(20, LOG_YMIN, 20, 1000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(28, LOG_YMIN, 28, 1000); drawLine(32, LOG_YMIN, 32, 50000); drawLine(36, LOG_YMIN, 36, 1000); c->cd(); },
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
    setLegend(leg, 2, 0.45, 0.68, 0.95, 0.87);

    if (ireg==0) {LOG_YMIN = 1; PLOT_MAX_YSCALE=0.01;}
    else if(ireg==1) {LOG_YMIN = 0.001; PLOT_MAX_YSCALE = 10;}
    else {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 10;}

    auto c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, hsigs, unc);
    c->SetCanvasSize(900, 600);
    drawTLatexNDC(splitlabels.at(ireg), 0.2, 0.74, 0.032);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
