#include "../utils/EstHelper.hh"
#include "LMParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot(TString inputFile="/tmp/plots/LowMass/sig/fbd_pred_lepplusmet.root", TString outputName="/tmp/plots/LowMass/LM_datavspred"){

  vector<TString> bkgs = {"rare_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  TString data = "data";

  vector<TString> bkglabels = {"Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"nb0", "nb1", "nb2"};
  vector<TString> splitlabels = {
      "N_{b}=0, p_{T}(j_{ISR}) #geq 500 GeV",
      "N_{b}#geq1, N_{b}^{L}=1",
      "N_{b}#geq1, N_{b}^{L}#geq2"
  };

  TLatex tl;
  tl.SetTextSize(0.03);
  tl.SetTextAlign(21);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){ tl.DrawLatexNDC(0.36, 0.64, "2-5 jets"); tl.DrawLatexNDC(0.76, 0.64, "#geq 6 jets");},
    [&tl](){ tl.DrawLatexNDC(0.38, 0.65, "250 #leq p_{T}(j_{ISR}) < 500 GeV");
             drawTLatexNDC("p_{T}(b) < 40 GeV", 0.2, 0.60, 0.026); drawTLatexNDC("40 #leq p_{T}(b) < 70 GeV", 0.38, 0.60, 0.026);
             tl.DrawLatexNDC(0.76, 0.65, "p_{T}(j_{ISR}) > 500 GeV");
             drawTLatexNDC("p_{T}(b) < 40 GeV", 0.6, 0.60, 0.026); drawTLatexNDC("40 #leq p_{T}(b) < 70 GeV", 0.78, 0.60, 0.026);
    },
    [&tl](){ tl.DrawLatexNDC(0.38, 0.65, "250 #leq p_{T}(j_{ISR}) < 500 GeV");
             drawTLatexNDC("p_{T}(b_{12}) < 100 GeV", 0.19, 0.60, 0.023); drawTLatexNDC("100 #leq p_{T}(b_{12}) < 160 GeV", 0.365, 0.60, 0.023);
             tl.DrawLatexNDC(0.76, 0.65, "p_{T}(j_{ISR}) > 500 GeV");
             drawTLatexNDC("p_{T}(b_{12}) < 100 GeV", 0.59, 0.60, 0.023); drawTLatexNDC("100 #leq p_{T}(b_{12}) < 160 GeV", 0.765, 0.60, 0.023);
    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(4,  0.1, 4,  10000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(12, 0.01, 12, 1000); drawLine(16, 0.01, 16, 5000); drawLine(20, 0.01, 20, 1000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(28, 0.01, 28, 1000); drawLine(32, 0.01, 32, 5000); drawLine(36, 0.01, 36, 1000); c->cd(); },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    pred.push_back((TH1*)f->Get(b));
  }
  TH1* hdata = (TH1*)f->Get(data);
  TH1* unc   = (TH1*)f->Get("bkgtotal_unc_sr");

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

    if (ireg==0) LOG_YMIN = 0.1;
    else LOG_YMIN = 0.01;

    auto c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, xlow, xhigh, {}, unc, hDataRawMC);
    c->SetCanvasSize(800, 600);
    drawText(splitlabels.at(ireg), 0.18, 0.72);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
