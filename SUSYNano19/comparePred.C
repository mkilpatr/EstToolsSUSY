#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TLatex.h"
#include <functional>
#include <regex>
#include <TGraph.h>

using namespace EstTools;

void comparePred(TString bkg = "ttbarplusw"){

  //lumistr = "35.815165";  //2016
  lumistr = "41.486136";  //2017
  //lumistr = "59.699489";  //2018

  SetStyle();
  PAD_SPLIT_Y = 0.35;

  double xlow=0.1, xhigh = 44;

  auto toQuantities = [](const TGraphAsymmErrors *gr){
    vector<Quantity> vec;
    for (int i=0; i<gr->GetN(); ++i){
      vec.emplace_back(gr->GetY()[i], (gr->GetEYlow()[i]+gr->GetEYhigh()[i])/2);
      if (vec.back().value==0) vec.back().value = 1e-3;
    }
    return vec;
  };
  auto getRatioGraph = [&](const TGraphAsymmErrors *num, const TH1 *denom){
    auto ratio = convertToHist(toQuantities(num), "tmp", "");
    ratio->Divide(denom);
    auto gr = new TGraphAsymmErrors(ratio);
    for (int i=0; i<gr->GetN(); ++i){
      gr->GetEXlow()[i] = 0;
      gr->GetEXhigh()[i] = 0;
    }
    return gr;
  };

  TString predFile = "2017/LowMET/sig/std_pred_trad_HM_2017.root";
  TString predFile_noextrap = "2017/LowMET/sig/std_pred_trad_HM_2017_noextrap.root";
  TString systFile = "uncertainties_LowMET_031320/Total.root";

  TFile *fpred = TFile::Open(predFile);
  TFile *fpred_noextrap = TFile::Open(predFile_noextrap);
  TFile *fsystFile = TFile::Open(systFile);
  assert(fpred); assert(fpred_noextrap); assert(fsystFile);

  TH1* pred_ = (TH1*)fpred->Get(bkg+"_pred");
  TH1* pred = (TH1*)pred_->Clone("hPrediction");
  TH1* pred_noextrap = (TH1*)fpred_noextrap->Get(bkg+"_pred");
  TH1* syst_up = (TH1*)fsystFile->Get("Up");
  TH1* syst_dn = (TH1*)fsystFile->Get("Down");
  pred->SetLineColor(kBlue); pred->SetMarkerColor(kBlue);
  pred_noextrap->SetLineColor(kRed); pred_noextrap->SetMarkerColor(kRed);
  prepHists({pred, pred_noextrap}, false, false, false, {kBlue, kRed});
  pred->SetFillStyle(0); pred_noextrap->SetFillStyle(0);

  double x[pred->GetNbinsX()], y[pred->GetNbinsX()], exl[pred->GetNbinsX()], eyl[pred->GetNbinsX()], exh[pred->GetNbinsX()], eyh[pred->GetNbinsX()];
  for (int i=1; i< pred->GetNbinsX(); i++){
    x[i-1] = i + 18.5;
    y[i-1] = pred->GetBinContent(i);
    exl[i-1] = 0.5;
    exh[i-1] = 0.5;
    eyl[i-1] = (1-syst_dn->GetBinContent(i+18))*pred->GetBinContent(i);
    eyh[i-1] = (syst_up->GetBinContent(i+18)-1)*pred->GetBinContent(i);
  }
  TGraphAsymmErrors* unc = new TGraphAsymmErrors(pred->GetNbinsX(), x, y, exl, exh, eyl, eyh);

  TH1* hratio_pred = (TH1*)pred->Clone("hratio_pred");
  hratio_pred->Divide(pred_noextrap);
  hratio_pred->SetLineWidth(2);
  prepHists({hratio_pred}, false, false, false, {kBlue});

  cout << pred->GetBinContent(16) << endl;
  cout << pred_noextrap->GetBinContent(16) << endl;
  cout << hratio_pred->GetBinContent(16) << endl;

  auto leg = prepLegends({pred, pred_noextrap}, {"Prediction", "Prediction w/o extrapolation"}, "L");
  leg->SetTextSize(0.03);
  leg->SetY1NDC(leg->GetY2NDC() - 0.2);
  TCanvas* c = drawCompAndRatio({pred, pred_noextrap}, {hratio_pred}, leg, "N_{pred}/N_{pred}^{noextrap}", RATIO_YMIN, RATIO_YMAX, true, -1., -1., false, unc);
  TString outputBase = "ExtrapolationComparison_2017";
  c->SetTitle(outputBase);
  c->SetCanvasSize(800, 600);
  c->Print("LLB/" + outputBase +".pdf");
}
