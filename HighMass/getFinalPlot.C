#include "../utils/EstHelper.hh"
#include "HMParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot(TString inputFile="/tmp/plots/HighMass/sig/std_pred_trad.root", TString outputName="/tmp/plots/HighMass/HM_datavspred"){

  vector<TString> bkgs = {"rare_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  TString data = "data";

  vector<TString> bkglabels = {"Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"nb1_mtb0", "nb2_mtb0", "nb1_mtb175_nj[0-9]_nt0_nw0", "nb1_mtb175_nj5t", "nb2_mtb175_nj[0-9]_nt0_nw0", "nb2_mtb175_nj5t"};
  vector<TString> splitlabels = {
      "#splitline{N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) < 175 GeV}{}",
      "#splitline{N_{b}#geq2, M_{T}(b_{1,2},#slash{E}_{T}) < 175 GeV}{}",
      "#splitline{N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{N_{W} = 0, N_{T} = 0}",
      "#splitline{N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{#geq 5 jets}",
      "#splitline{N_{b}#geq2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{N_{W} = 0, N_{T} = 0}",
      "#splitline{N_{b}#geq2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{#geq 5 jets}"
  };

  TLatex tl;
  tl.SetTextSize(0.03);
  tl.SetTextAlign(31);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){ tl.DrawLatexNDC(0.4, 0.62, "5-6 jets"); tl.DrawLatexNDC(0.8, 0.62, "#geq 7 jets");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.62, "5-6 jets"); tl.DrawLatexNDC(0.8, 0.62, "#geq 7 jets");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.62, "5-6 jets"); tl.DrawLatexNDC(0.8, 0.62, "#geq 7 jets");},
    [&tl](){                              tl.DrawLatexNDC(0.36, 0.62, "N_{W} #geq 1, N_{T} = 0");
             tl.DrawLatexNDC(0.65, 0.62, "N_{W} = 0, N_{T} #geq 1");
             tl.DrawLatexNDC(0.93, 0.62, "N_{W} #geq 1, N_{T} #geq 1");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.62, "5-6 jets"); tl.DrawLatexNDC(0.8, 0.62, "#geq 7 jets");},
    [&tl](){                              tl.DrawLatexNDC(0.36, 0.62, "N_{W} #geq 1, N_{T} = 0");
             tl.DrawLatexNDC(0.65, 0.62, "N_{W} = 0, N_{T} #geq 1");
             tl.DrawLatexNDC(0.93, 0.62, "N_{W} #geq 1, N_{T} #geq 1");},
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(4,  0.01, 4,  2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(12, 0.01, 12, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, 0.01, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(29, 0.01, 29, 2000); drawLine(34, 0.01, 34, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(42, 0.01, 42, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(51, 0.01, 51, 2000); drawLine(56, 0.01, 56, 2000); c->cd(); },
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

    auto c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0.001, 2.999, xlow, xhigh, {}, unc, hDataRawMC);
    c->SetCanvasSize(800, 600);
    drawText(splitlabels.at(ireg), 0.18, 0.69);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    basename.ReplaceAll("_nj[0-9]", "");
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
