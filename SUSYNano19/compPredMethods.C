#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TLatex.h"
#include <functional>
#include <regex>

using namespace EstTools;

void compPredMethods(TString bkg = "ttbarplusw"){

  SetStyle();
  PAD_SPLIT_Y = 0.35;

  double xlow=54, xhigh = 183.9;

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

  TString predFile = "sig/std_pred_trad_withExtrap_052820.root";
  TString predFile_noextrap = "sig/std_pred_trad_withoutExtrap_052820.root";
//  TString output  = "";

  TFile *fpred = TFile::Open(predFile);
  TFile *fpred_noextrap = TFile::Open(predFile_noextrap);
  assert(fpred); assert(fpred_noextrap);

  TGraphAsymmErrors* pred = (TGraphAsymmErrors*)fpred->Get(bkg+"_unc_sr");
  TGraphAsymmErrors* pred_statOnly = (TGraphAsymmErrors*)fpred->Get(TString::Format("Graph_from_%s_pred_gr", bkg.Data()));
  TGraphAsymmErrors* pred_noextrap = (TGraphAsymmErrors*)fpred_noextrap->Get(TString::Format("Graph_from_%s_pred_gr", bkg.Data()));

  //TH1* mc_ = (TH1*)fpred->Get(bkg+"_mc");
  //double x[mc_->GetNbinsX()], y[mc_->GetNbinsX()], exl[mc_->GetNbinsX()], eyl[mc_->GetNbinsX()], exh[mc_->GetNbinsX()], eyh[mc_->GetNbinsX()];
  //double x_noextrap[mc_->GetNbinsX()], y_noextrap[mc_->GetNbinsX()], exl_noextrap[mc_->GetNbinsX()], eyl_noextrap[mc_->GetNbinsX()], exh_noextrap[mc_->GetNbinsX()], eyh_noextrap[mc_->GetNbinsX()];
  //double x_statOnly[mc_->GetNbinsX()], y_statOnly[mc_->GetNbinsX()], exl_statOnly[mc_->GetNbinsX()], eyl_statOnly[mc_->GetNbinsX()], exh_statOnly[mc_->GetNbinsX()], eyh_statOnly[mc_->GetNbinsX()];
  //for (int i=0; i != mc_->GetNbinsX(); i++){
  //  int j = i + 19;
  //  x[i] = j;
  //  exl[i] = 0;
  //  exh[i] = 1;
  //  y[i] = pred_->GetErrorY(j);
  //  eyl[i] = pred_->GetErrorYlow(j);
  //  eyh[i] = pred_->GetErrorYhigh(j);
  //  x_noextrap[i] = j;
  //  exl_noextrap[i] = 0;
  //  exh_noextrap[i] = 1;
  //  y_noextrap[i] = pred_noextrap_->GetErrorY(j);
  //  eyl_noextrap[i] = pred_noextrap_->GetErrorYlow(j);
  //  eyh_noextrap[i] = pred_noextrap_->GetErrorYhigh(j);
  //  x_statOnly[i] = j;
  //  exl_statOnly[i] = 0;
  //  exh_statOnly[i] = 1;
  //  y_statOnly[i] = pred_statOnly_->GetErrorY(j);
  //  eyl_statOnly[i] = pred_statOnly_->GetErrorYlow(j);
  //  eyh_statOnly[i] = pred_statOnly_->GetErrorYhigh(j);
  //}
  //TGraphAsymmErrors* pred = new TGraphAsymmErrors(mc_->GetNbinsX(), x, y, exl, exh, eyl, eyh);
  //TGraphAsymmErrors* pred_noextrap = new TGraphAsymmErrors(mc_->GetNbinsX(), x_noextrap, y_noextrap, exl_noextrap, exh_noextrap, eyl_noextrap, eyh_noextrap);
  //TGraphAsymmErrors* pred_statOnly = new TGraphAsymmErrors(mc_->GetNbinsX(), x_statOnly, y_statOnly, exl_statOnly, exh_statOnly, eyl_statOnly, eyh_statOnly);


  for (int i=0; i<pred_noextrap->GetN(); ++i){
    pred->GetX()[i] += 0.1;
    pred_statOnly->GetX()[i] += 0.2;
    pred_noextrap->GetX()[i] += 0.3;
  }
  pred->SetLineColor(kBlue); pred->SetMarkerColor(kBlue);
  pred_statOnly->SetLineColor(kRed); pred_statOnly->SetMarkerColor(kRed);
  for (auto *gr : {pred, pred_statOnly, pred_noextrap}){
    for (int i=0; i<gr->GetN(); ++i){
      gr->GetEXlow()[i] = 0;
      gr->GetEXhigh()[i] = 0;
    }
  }


  TH1* mc = (TH1*)fpred->Get(bkg+"_mc");
  auto ratio_pred = getRatioGraph(pred, mc);
  auto ratio_pred_statOnly = getRatioGraph(pred_statOnly, mc);
  auto ratio_pred_noextrap = getRatioGraph(pred_noextrap, mc);
  for (int i=0; i<ratio_pred_noextrap->GetN(); ++i){
    ratio_pred->GetX()[i] += 0.1;
    ratio_pred_statOnly->GetX()[i] += 0.2;
    ratio_pred_noextrap->GetX()[i] += 0.3;
  }

  auto leg = prepLegends<TGraphAsymmErrors>({pred_statOnly, pred, pred_noextrap}, {"Stats. unc. only", "Stats. + Syst. unc.", "w/o extrapolation"}, "LP");

  auto c = MakeCanvas(1000, 600);
  TPad *p1 = new TPad("p1","p1",0,PAD_SPLIT_Y,1,1);
  p1->SetLeftMargin  (0.16);
  p1->SetTopMargin   (0.10);
  p1->SetRightMargin (0.04);
  p1->SetBottomMargin(0.03);
  p1->Draw();
  p1->cd();


  pred->GetXaxis()->SetRangeUser(xlow, xhigh);
  pred->GetYaxis()->SetRangeUser(0.01, 1e6);
  p1->SetLogy();

  pred->GetYaxis()->SetTitle("Prediction");
  pred->GetYaxis()->SetTitleSize(0.07);
  pred->GetYaxis()->SetTitleOffset(0.8);
  pred->GetXaxis()->SetLabelOffset(0.6);
  pred->Draw("PA0");
  pred_statOnly->Draw("P0same[]");
  pred_noextrap->Draw("P0same");
  leg->Draw();
  CMS_lumi(p1, 4, 10);

  c->cd();

  TPad *p2 = new TPad("p2","p2",0,0,1,PAD_SPLIT_Y);
  p2->SetLeftMargin  (0.16);
  p2->SetTopMargin   (0.00);
  p2->SetRightMargin (0.04);
  p2->SetBottomMargin(PAD_BOTTOM_MARGIN);
  p2->SetGridy(1);
  p2->Draw();
  p2->cd();

  ratio_pred->GetXaxis()->SetTitle("Search region");
  ratio_pred->GetYaxis()->SetTitle("#frac{Prediction}{Simulation}");
  ratio_pred->GetXaxis()->SetRangeUser(xlow, xhigh);
  ratio_pred->GetXaxis()->SetNdivisions(520);
  ratio_pred->GetYaxis()->SetRangeUser(0, 1.999);
  ratio_pred->GetXaxis()->SetTitleSize(0.12);
  ratio_pred->GetYaxis()->SetTitleSize(0.12);
  ratio_pred->GetYaxis()->SetTitleOffset(0.41);
  ratio_pred->GetXaxis()->SetLabelSize(0.1);
  ratio_pred->GetXaxis()->SetLabelOffset(0.01);
  ratio_pred->GetYaxis()->SetLabelSize(0.1);
  ratio_pred->GetYaxis()->CenterTitle(kTRUE);
  ratio_pred->GetYaxis()->SetNdivisions(305);


  ratio_pred->SetLineColor(kBlue); ratio_pred->SetMarkerColor(kBlue);
  ratio_pred_statOnly->SetLineColor(kRed); ratio_pred_statOnly->SetMarkerColor(kRed);

  ratio_pred->Draw("PA0");
  ratio_pred_statOnly->Draw("P0same[]");
  ratio_pred_noextrap->Draw("P0same");

  c->cd();
  c->SaveAs("bkgpred_comp_"+bkg+".png");
}
