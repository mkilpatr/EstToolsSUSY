#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TLatex.h"
#include <functional>
#include <regex>

using namespace EstTools;

void compPredMethods(TString bkg = "ttbarplusw"){

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

  TString predFile = "2016/LowMET/sig/std_pred_trad_HM_2016.root";
  TString predFile_noextrap = "2016/LowMET/sig/std_pred_trad_HM_2016_noextrap.root";
//  TString output  = "";

  TFile *fpred = TFile::Open(predFile);
  TFile *fpred_noextrap = TFile::Open(predFile_noextrap);
  assert(fpred); assert(fpred_noextrap);

  TH1* pred_ = (TH1*)fpred->Get(bkg+"_pred");
  TH1* pred = (TH1*)pred_->Clone("hPrediction");
  TH1* pred_noextrap = (TH1*)fpred_noextrap->Get(bkg+"_pred");
  pred->SetLineColor(kBlue); pred->SetMarkerColor(kBlue);
  pred_noextrap->SetLineColor(kRed); pred_noextrap->SetMarkerColor(kRed);

  TH1* hratio_pred = (TH1*)pred->Clone("hratio_pred");
  hratio_pred->Divide(pred_noextrap);
  hratio_pred->SetLineWidth(2);
  prepHists({hratio_pred}, false, false, false, {kBlue});

  auto leg = prepLegends({pred, pred_noextrap}, {"Prediction", "Prediction w/o extrapolation"}, "L");
  leg->SetTextSize(0.03);
  leg->SetY1NDC(leg->GetY2NDC() - 0.2);
  TCanvas* c = drawCompAndRatio({pred, pred_noextrap}, {hratio_pred}, leg);
  TString outputBase = "ExtrapolationComparison";
  c->SetTitle(outputBase);
  c->SetCanvasSize(800, 600);
  c->Print("LLB/" + outputBase +".pdf");
  c->Print("LLB/" + outputBase +".C");
  c->Print("LLB/" + outputBase +"_canvas.root");
}
