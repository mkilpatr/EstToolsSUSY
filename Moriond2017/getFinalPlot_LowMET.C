#include "../utils/EstHelper.hh"
#include "LowMET_Parameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_LowMET(TString inputFile="std_pred_trad.root", TString outputName="/tmp/plots/validation", bool plotPulls=false){

  vector<TString> bkgs = {"diboson_pred", "ttZ_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"diboson_mc",   "ttZ_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  TString data = "data";
  TString ratiolabel = "N_{obs}/N_{exp}";

  vector<TString> bkglabels = {"Diboson", "ttZ", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> datalabel = {"Observed"};
  vector<TString> rawsimlabel = {"Simulation"};

  vector<TString> split = {"lm", "hm"};
  vector<TString> splitlabels = {
      "Low #DeltaM",
      "High #DeltaM",
  };
  TLatex tl;
  tl.SetTextSize(0.03);
  tl.SetTextAlign(11);
  vector<std::function<void()>> drawRegionLabels {
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
  };


  vector<TString> xlabels {
  };

  vector<TString> dummylabels(xlabels.size(), "");

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
  //  setBinLabels(hdata, dummylabels);
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

  TGraphAsymmErrors* gPulls = 0;
  if(plotPulls){
    TH1* hPulls = 0;
    TGraphAsymmErrors* gDataUnc = 0;

    // hbkgtotal is total corrected MC. verified central values & unc against plots.
    // ** necessary to use with ICHEP-cr roots, which lack "bkgtotal_unc_sr" (unc, with asymmetric errors)
    TH1* hbkgtotal = nullptr;
    for (auto *h : pred){
      auto *hmc = (TH1*)h->Clone();

      if (!hbkgtotal) { hbkgtotal = (TH1*)hmc->Clone("hbkgtotal"); }
      else { hbkgtotal->Add(hmc); }

      if (hmc->GetLineColor()!=kBlack){ hmc->SetFillColor(hmc->GetLineColor()); hmc->SetFillStyle(1001); hmc->SetLineColor(kBlack); }
    }

    // hPulls (no uncertainties) will replace hDataRawMC as yellow connected line in ratio plot
    // gPulls (no central values) will replace the shaded blue error bars in the ratio plot __only__
    hPulls = (TH1*)hdata->Clone("hDataRawMC");

    if(unc) {
      gPulls = (TGraphAsymmErrors*)unc->Clone(); // asymm errors from systematics, for Moriond17 samples
    }else{
      gPulls = new TGraphAsymmErrors(hbkgtotal); // from corrected bkg total histogram ... for ICHEP-cr samples
    }
    float nbins = (float)gPulls->GetN();
    std::cout << "Total bins: " << nbins << std::endl;

    hPulls->SetBinContent(hPulls->GetNbinsX()+1, 0.);//safety from overflow
    hPulls->SetBinContent(0, 0.);
    gDataUnc = getAsymmErrors(hdata);
    std::cout << "bin/data/dataunchigh/dataunclow/predi/prediunc/pull/pulllow/pullhigh: " << std::endl;
    int n1 = 0, n3 = 0, n5 = 0;
    for(unsigned i = 0; i < nbins; i++){
      float fdata        = hdata->GetBinContent(i+1); // histos are indexed (1...N)
      float fdataunchigh = gDataUnc->GetErrorYhigh(i);
      float fdataunclow  = gDataUnc->GetErrorYlow(i);
      float fpredi       = gPulls->GetY()[i];
      float fprediunc    = gPulls->GetErrorY(i); // avg of GetErrorYLow and GetErrorYHigh
      float pull         = (fdata - fpredi)/fprediunc;
      float pullhigh     = (fdata - (fpredi - fdataunchigh))/fprediunc;
      float pulllow      = (fdata - (fpredi + fdataunclow))/fprediunc;
      std::cout << i << " " <<fdata << " " << fdataunchigh << " " << fdataunclow << " " << fpredi<< " " <<fprediunc<< " " <<pull << " " << pulllow << " " << pullhigh << std::endl;
      if(abs(pull)>5) std::cout << "** Pull is over 5! " << i << " " << pull << std::endl;
      if(abs(pull)<1) n1++;
      if(abs(pull)<3) n3++;
      if(abs(pull)<5) n5++;
      hPulls->SetBinContent(i+1, pull);
      gPulls->SetPoint(i, gPulls->GetX()[i], pull);
      gPulls->SetPointEYhigh(i, pullhigh - pull);
      gPulls->SetPointEYlow(i, pull - pulllow);
    }
    std::cout << "Pulls within 1, 3, 5: " << n1 << " (" << n1/nbins << "%),  " << n3 << " (" << n3/nbins << "%),  " << n5 << " (" << n5/nbins << "%),  " << std::endl;
    hDataRawMC = hPulls; // switcharoo
    hDataRawMC->SetLineWidth(2);
    prepHists({hDataRawMC}, false, false, false, {kBlack});
    rawsimlabel.at(0) = "Pull";
    double maxpull = 5.;
    RATIO_YMIN = -maxpull + 0.001;
    RATIO_YMAX = +maxpull - 0.001;
    ratiolabel = "(D-P)/#sigma(P)";
  }


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

    LOG_YMIN = 0.1;
    PLOT_MAX_YSCALE = 1.2;
    PAD_SPLIT_Y = 0.33;
    PAD_BOTTOM_MARGIN = 0.38;

    auto leg = prepLegends({hdata}, datalabel, "LP");
    appendLegends(leg, pred, bkglabels, "F");
    appendLegends(leg, {hDataRawMC}, rawsimlabel, "L");
//  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    auto c = drawStackAndRatio(pred, hdata, leg, true, ratiolabel, RATIO_YMIN, RATIO_YMAX, xlow, xhigh, {}, unc, {hDataRawMC}, gPulls);

    c->SetCanvasSize(800, 600);
//    drawText(splitlabels.at(ireg), 0.18, 0.69);
//    drawRegionLabels.at(ireg)();
//    drawVerticalLines.at(ireg)(c);

//    double xpos = 0.19;
//    for (auto xl : xlabels){
//      drawTLatexNDC(xl, xpos, 0.12, 0.028, 13, 310, 42);
//      xpos += 0.0575;
//    }

    TString basename = outputName + "_" + region;
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");

  }

}
