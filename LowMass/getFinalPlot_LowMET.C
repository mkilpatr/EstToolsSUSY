#include "../utils/EstHelper.hh"
#include "LMParameters_LowMET.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_LowMET(TString inputFile="/tmp/LowMET/LowMass/sig/fbd_pred_lepplusmet.root", TString outputName="/tmp/LowMET/LowMass/LM_validation"){

  LOG_YMIN = 0.01;

  vector<TString> bkgs = {"rare_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  TString data = "data";

  vector<TString> bkglabels = {"Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"_"};
  vector<TString> splitlabels = {
      "",
  };

  TLatex tl;
  tl.SetTextSize(0.025);
  tl.SetTextAlign(11);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){
      tl.DrawLatexNDC(0.22, 0.74, "N_{b} = 0"); tl.DrawLatexNDC(0.18, 0.70, "p_{T}(j_{ISR}) > 500");
      tl.DrawLatexNDC(0.18, 0.66, "5-6 jets");  tl.DrawLatexNDC(0.26, 0.66, "#geq 7 jets");

      tl.DrawLatexNDC(0.42, 0.74, "N_{b} #geq 1, N_{b_{l}} = 1");
      tl.DrawLatexNDC(0.34, 0.70, "250 #leq p_{T}(j_{ISR}) < 500"); tl.DrawLatexNDC(0.52, 0.70, "p_{T}(j_{ISR}) > 500");

      tl.DrawLatexNDC(0.76, 0.74, "N_{b} #geq 1, N_{b_{l}} #geq 2");
      tl.DrawLatexNDC(0.66, 0.70, "250 #leq p_{T}(j_{ISR}) < 500"); tl.DrawLatexNDC(0.83, 0.70, "p_{T}(j_{ISR}) > 500");
      drawTLatexNDC("p_{T}(b) < 40", 0.65, 0.64, 0.018); drawTLatexNDC("40 #leq p_{T}(b) < 70", 0.72, 0.64, 0.018);
      drawTLatexNDC("p_{T}(b_{12}) < 100", 0.84, 0.52, 0.018, 11, 90); drawTLatexNDC("100 #leq p_{T}(b_{12}) < 160", 0.91, 0.52, 0.018, 11, 90);

    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){
      ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
      drawLine(2,  LOG_YMIN, 2,  2000);
      drawLine(4,  LOG_YMIN, 4,  20000);
      drawLine(6,  LOG_YMIN, 6,  1000);
      drawLine(8,  LOG_YMIN, 8,  4000);
      drawLine(10,  LOG_YMIN, 10,  1000);
      drawLine(12,  LOG_YMIN, 12,  20000);
      drawLine(14,  LOG_YMIN, 14,  1000);
      drawLine(16,  LOG_YMIN, 16,  4000);
      drawLine(18,  LOG_YMIN, 18,  1000);
      c->cd();
    },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    pred.push_back((TH1*)f->Get(b));
  }
  TH1* hdata = (TH1*)f->Get(data);
  TGraphAsymmErrors* unc   = (TGraphAsymmErrors*)f->Get("pred_total_gr");

  prepHists(pred, false, false, true);
  prepHists({hdata}, false, false, false, {kBlack});
  setBinLabels(hdata, xlabels);
  hdata->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");

  // plot raw MC
  TH1 *hmctotal = nullptr;
  for(auto &mc : mcs){
    if (!hmctotal) hmctotal = (TH1*)f->Get(mc)->Clone();
    else hmctotal->Add((TH1*)f->Get(mc));
  }

  TH1* hDataRawMC = (TH1*)hdata->Clone("hDataRawMC");
  hDataRawMC->Divide(hmctotal);
  hDataRawMC->SetLineWidth(2);
  prepHists({hDataRawMC}, false, false, false, {kOrange});

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
    appendLegends(leg, {hDataRawMC}, {"Simulation", "L"});
  //  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.54, 0.72, 0.96, 0.88);

    auto c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, xlow, xhigh, {}, unc, hDataRawMC);
    c->SetCanvasSize(900, 600);
    drawText(splitlabels.at(ireg), 0.18, 0.69);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
