#include "../utils/EstHelper.hh"
#include "HMParameters_SSR.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_SSR(TString inputFile="/tmp/SSR/HighMass/sig/std_pred_trad.root", TString outputName="/tmp/SSR/HighMass/HM_SSR"){

  LOG_YMIN = 0.1;

  vector<TString> bkgs = {"rare_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  TString data = "data";

  vector<TString> bkglabels = {"Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"_"};
  vector<TString> splitlabels = {
      "",
  };
  vector<std::function<void()>> drawRegionLabels {
    [](){
      drawTLatexNDC("M_{T}(b_{1,2},#slash{E}_{T}) < 175 GeV", 0.19, 0.70);
      drawTLatexNDC("#geq 7 jets", 0.26, 0.65);
      drawTLatexNDC("N_{b}=1", 0.21, 0.60, 0.025);
      drawTLatexNDC("N_{b}#geq2", 0.32, 0.60, 0.025);

      drawTLatexNDC("M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV, N_{b}#geq2", 0.54, 0.70);
      drawTLatexNDC("N_{W} = 0, N_{T} = 0", 0.48, 0.64, 0.025); drawTLatexNDC("#geq 7 jets", 0.5, 0.6, 0.025);
      drawTLatexNDC("N_{W} #geq 1", 0.69, 0.64, 0.025); drawTLatexNDC("N_{T} = 0",    0.69, 0.6, 0.025);
      drawTLatexNDC("N_{W} = 0",    0.81, 0.64, 0.025); drawTLatexNDC("N_{T} #geq 1", 0.81, 0.6, 0.025);
      drawTLatexNDC("N_{W} #geq 1, N_{T} #geq 1", 0.94, 0.5, 0.025, 11, 90);
    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){
      ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
      drawLine(2,  LOG_YMIN, 2,  2000);
      drawLine(4,  LOG_YMIN, 4,  50000);
      drawLine(8,  LOG_YMIN, 8,  2000);
      drawLine(10,  LOG_YMIN, 10,  2000);
      drawLine(12,  LOG_YMIN, 12,  2000);
      drawLine(14,  LOG_YMIN, 14,  2000);
      c->cd();
    },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);
  xlabels[1] = "[300, 400)";
  xlabels[3] = "[300, 400)";

  vector<TH1*> pred;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    pred.push_back((TH1*)f->Get(b));
  }
  TH1* hdata = (TH1*)f->Get(data);
  TGraphAsymmErrors* unc   = (TGraphAsymmErrors*)f->Get("bkgtotal_unc_sr");

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
    c->SetCanvasSize(800, 600);
//    drawText(splitlabels.at(ireg), 0.18, 0.69);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
