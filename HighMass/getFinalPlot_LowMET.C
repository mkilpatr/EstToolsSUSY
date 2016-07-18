#include "../utils/EstHelper.hh"
#include "HMParameters_LowMET.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_LowMET(TString inputFile="/tmp/LowMET/HighMass/sig/std_pred_trad.root", TString outputName="/tmp/LowMET/HighMass/HM_validation"){

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
  tl.SetTextSize(0.03);
  tl.SetTextAlign(11);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){
      tl.DrawLatexNDC(0.18, 0.70, "M_{T}(b_{1,2},#slash{E}_{T}) < 175 GeV");
      tl.DrawLatexNDC(0.2, 0.64, "N_{b}=1");
      tl.DrawLatexNDC(0.32, 0.64, "N_{b}#geq2");
      tl.DrawLatexNDC(0.58, 0.70, "M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV");
      tl.DrawLatexNDC(0.52, 0.64, "N_{b}=1");
      tl.DrawLatexNDC(0.80, 0.64, "N_{b}#geq2");
    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){
      ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
      drawLine(2,  0.01, 2,  2000);
      drawLine(4,  0.01, 4,  50000);
      drawLine(9,  0.01, 9,  2000);
      c->cd();
    },
  };


  vector<TString> xlabels {
    "5-6j", "#geq7j",
    "5-6j", "#geq7j",
    "0W, 0T, 5-6j", "0W, 0T, #geq7j",
    "#geq1W, 0T", "0W, #geq1T", "#geq1W, #geq1T",
    "0W, 0T, 5-6j", "0W, 0T, #geq7j",
    "#geq1W, 0T", "0W, #geq1T", "#geq1W, #geq1T",
  };

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
  hdata->GetXaxis()->SetTitle("");

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
    c->SetCanvasSize(800, 600);
    drawText(splitlabels.at(ireg), 0.18, 0.69);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
