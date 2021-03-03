#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <string.h>
#include <functional>

using namespace EstTools;

void compPredMethods(TString bkg = "ttbarplusw"){


  SetStyle();
  TDR_EXTRA_LABEL_ = "Supplementary";
  TDR_EXTRA_LABEL_2 = "arXiv:2103.01290";
  PAD_SPLIT_Y = 0.35;

  TString outDir = "LLB/SupplementaryPlots/";

  double xlow=69, xhigh = 153;

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
  auto getRatioGraphError = [&](const TGraphAsymmErrors *num, const TGraphAsymmErrors *denom){
    auto ratio = convertToHist(toQuantities(num), "tmp", "");
    auto den   = convertToHist(toQuantities(denom), "tmp_denom", "");
    for(int ibin=0; ibin < num->GetN(); ++ibin){
      int ibin_hist = ibin+1;
      double num_err = std::max(num->GetEYhigh()[ibin], num->GetEYlow()[ibin]);
      double denom_err = std::max(denom->GetEYhigh()[ibin], denom->GetEYlow()[ibin]);
      Quantity r = getHistBin(ratio, ibin_hist), d = getHistBin(den, ibin_hist);
      r.value = num_err;
      r.error = 0;
      d.value = denom_err;
      d.error = 0;
      if(num_err/denom_err > 1.) cout << "bin: " << ibin << " num: " << num_err << " denom: " << denom_err << " ratio: " << num_err/denom_err << endl;;
      setHistBin(ratio, ibin_hist, r);
      setHistBin(den, ibin_hist, d);
    }
    ratio->Divide(den);
    auto gr = new TGraphAsymmErrors(ratio);
    for (int i=0; i<gr->GetN(); ++i){
      gr->GetEXlow()[i] = 0;
      gr->GetEXhigh()[i] = 0;
    }
    return gr;
  };

  vector<TString> split = {
			   "hm_nb1_bins",
			   };
  vector<TString> splitlabels = {
      "High #Deltam, N_{b}=1,2",
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);


  TString predFile = "sig/std_pred_trad_withExtrap_081620.root";
  TString predFile_noextrap = "sig/std_pred_trad_withoutExtrap_081620.root";
//  TString output  = "";

  TFile *fpred = TFile::Open(predFile);
  TFile *fpred_noextrap = TFile::Open(predFile_noextrap);
  assert(fpred); assert(fpred_noextrap);

  TGraphAsymmErrors* pred = (TGraphAsymmErrors*)fpred->Get(bkg+"_unc_sr");
  TGraphAsymmErrors* pred_statOnly = (TGraphAsymmErrors*)fpred->Get(TString::Format("Graph_from_%s_pred_gr", bkg.Data()));
  TGraphAsymmErrors* pred_noextrap = (TGraphAsymmErrors*)fpred_noextrap->Get(TString::Format("Graph_from_%s_pred_gr", bkg.Data()));
  TGraphAsymmErrors* unc = (TGraphAsymmErrors*)pred_statOnly->Clone("pred_statOnly_unc");
  TGraphAsymmErrors* unc_all = (TGraphAsymmErrors*)pred->Clone("pred_unc");

  for (int i=0; i<pred_noextrap->GetN(); ++i){
    if(i < 153) continue;
    cout << "bin " << i << ": Pred: " << pred->GetY()[i] << "(+" << pred->GetErrorYhigh(i) << ")(-" << pred->GetErrorYlow(i) << ")" << endl;
    cout << "bin " << i << ": pred_statOnly: " << pred_statOnly->GetY()[i] << "(+" << pred_statOnly->GetErrorYhigh(i) << ")(-" << pred_statOnly->GetErrorYlow(i) << ")" << endl;
    cout << "bin " << i << ": pred_noextrap: " << pred_noextrap->GetY()[i] << "(+" << pred_noextrap->GetErrorYhigh(i) << ")(-" << pred_noextrap->GetErrorYlow(i) << ")" << endl;
    pred->GetX()[i] += 1.5;
    pred_statOnly->GetX()[i] += 1.5;
    pred_noextrap->GetX()[i] += 1.5;
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
  //for (int i=0; i<ratio_pred_noextrap->GetN(); ++i){
  //  ratio_pred->GetX()[i] += 0.1;
  //  ratio_pred_statOnly->GetX()[i] += 0.2;
  //  ratio_pred_noextrap->GetX()[i] += 0.3;
  //}

  //TH1* extrap = convertToHist(toQuantities(pred_noextrap), "tmp", "");
  auto ratio_new_noextrap = getRatioGraphError(pred_statOnly, pred_noextrap);
  auto ratio_all_noextrap = getRatioGraphError(pred, pred_noextrap);
  for (int i=0; i<ratio_new_noextrap->GetN(); ++i){
    if(i < 153) continue;
    ratio_new_noextrap->GetX()[i] += 1.5;
  }

  //Check Pull
  TH1* pull = getPullHist(convertToHist(toQuantities(pred_noextrap), "tmp", ""), pred, false, "High #Deltam Search Regions", 53);
  prepHists({pull}, false, false, false, {kRed});
  double mean  = pull->GetMean();
  double StdDev = pull->GetStdDev();
  TString fitString = "#splitline{Mean = " + to_string(mean) + "}{StdDev = " + to_string(StdDev) + "}";
  std::function<void(TCanvas*)> plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC(fitString, 0.2, 0.68); };
  auto c_pull = drawCompMatt({pull}, 0, -1., &plotextra);
  c_pull->SetCanvasSize(800, 600);
  gStyle->SetOptStat(0);
  TString basename = "bkgpred_comp_small__pull";
  c_pull->Print(basename+".pdf");

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
  pred->GetYaxis()->SetRangeUser(0.01, 1e7);
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

  ratio_pred->GetXaxis()->SetTitle("Search bin number");
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
  c->SaveAs(outDir + "bkgpred_comp_small_"+bkg+".pdf");
  c->SaveAs(outDir + "bkgpred_comp_small_"+bkg+".png");


  TH1* pred_noextrap_hist = convertToHist(toQuantities(pred_noextrap), "tmp", ";Search bin number;Events");
  TH1* pred_hist          = convertToHist(toQuantities(pred), "tmp", ";Search bin number;Events");
  TH1* pred_statOnly_hist = convertToHist(toQuantities(pred_statOnly), "tmp", ";Search bin number;Events");
  TH1* ratio_new_noextrap_hist = convertToHist(toQuantities(ratio_new_noextrap), "tmp", ";Search bin number;Events");
  TH1* ratio_all_noextrap_hist= convertToHist(toQuantities(ratio_all_noextrap), "tmp", ";Search bin number;Events");
  prepHists({pred_statOnly_hist, pred_hist}, false, false, true, {866, 866});

  auto leg_new = prepLegends({}, {""}, "L");
  appendLegends(leg_new, {pred_statOnly_hist}, {"extrapolation"}, "F");
  appendLegends(leg_new, {pred_noextrap_hist}, {"w/o extrapolation (Stat. unc.)"}, "LP");
  addLegendEntry(leg_new, unc,"Stat. unc.","F");
  auto leg_all = prepLegends({}, {""}, "L");
  appendLegends(leg_all, {pred_hist}, {"extrapolation"}, "F");
  appendLegends(leg_all, {pred_noextrap_hist}, {"w/o extrapolation (Stat. unc.)"}, "LP");
  addLegendEntry(leg_all, unc_all,"Syst. + Stat. unc.","F");
  //c = drawStackAndRatio({pred_statOnly_hist}, pred_noextrap_hist, leg_new, true, "#frac{Unc.(extrap)}{Unc.(w/o extrap)}", 0, 1.499, xlow, xhigh, {}, unc, {ratio_new_noextrap_hist}, nullptr, false, false, true, true, false, true);
  //c->SetCanvasSize(800, 600);
  //gStyle->SetOptStat(0);
  //drawTLatexNDC(splitlabels.at(0), 0.605, 0.76, 0.032);
  //c->Print("bkgpred_comp_small_newratio_"+bkg+".png");
  //c->Print("bkgpred_comp_small_newratio_"+bkg+".pdf");


  //Add new version with diff ratio
  auto cnew = MakeCanvas(1000, 600);
  TPad *p1new = new TPad("p1new","p1new",0,PAD_SPLIT_Y,1,1);
  p1new->SetLeftMargin  (0.16);
  p1new->SetTopMargin   (0.10);
  p1new->SetRightMargin (0.04);
  p1new->SetBottomMargin(0.03);
  p1new->Draw();
  p1new->cd();


  pred_statOnly_hist->GetXaxis()->SetRangeUser(xlow, xhigh);
  pred_statOnly_hist->GetYaxis()->SetRangeUser(0.01, 1e7);
  p1new->SetLogy();

  pred_statOnly_hist->GetYaxis()->SetTitle("Prediction");
  pred_statOnly_hist->GetYaxis()->SetTitleSize(0.07);
  pred_statOnly_hist->GetYaxis()->SetTitleOffset(0.8);
  pred_statOnly_hist->GetXaxis()->SetLabelOffset(0.6);
  pred_statOnly_hist->GetXaxis()->SetNdivisions(520);
  pred_statOnly_hist->Draw("hist");
  unc->SetFillColor(kBlue);
  unc->SetFillStyle(3013);
  unc->SetLineStyle(0);
  unc->SetLineWidth(0);
  unc->SetMarkerSize(0);
  unc->Draw("E2same");
  pred_noextrap->Draw("P0same");

  setLegend(leg_new, 1, 0.5, 0.70, 0.92, 0.87);
  leg_new->Draw();
  CMS_lumi(p1new, 4, 10);
  
  cnew->cd();
  drawTLatexNDC(splitlabels.at(0), 0.605, 0.76, 0.032);

  TPad *p2new = new TPad("p2new","p2new",0,0,1,PAD_SPLIT_Y);
  p2new->SetLeftMargin  (0.16);
  p2new->SetTopMargin   (0.00);
  p2new->SetRightMargin (0.04);
  p2new->SetBottomMargin(PAD_BOTTOM_MARGIN);
  p2new->SetGridy(1);
  p2new->Draw();
  p2new->cd();

  ratio_new_noextrap_hist->GetXaxis()->SetTitle("Search bin number");
  ratio_new_noextrap_hist->GetYaxis()->SetTitle("#frac{Unc.(extrap)}{Unc.(w/o extrap)}");
  ratio_new_noextrap_hist->GetXaxis()->SetRangeUser(xlow, xhigh);
  ratio_new_noextrap_hist->GetXaxis()->SetNdivisions(520);
  ratio_new_noextrap_hist->GetYaxis()->SetRangeUser(0, 1.001);
  ratio_new_noextrap_hist->GetYaxis()->ChangeLabel(6, -1, 0.);
  ratio_new_noextrap_hist->GetXaxis()->SetTitleSize(0.12);
  ratio_new_noextrap_hist->GetYaxis()->SetTitleSize(0.09);
  ratio_new_noextrap_hist->GetYaxis()->SetTitleOffset(0.6);
  ratio_new_noextrap_hist->GetXaxis()->SetLabelSize(0.1);
  ratio_new_noextrap_hist->GetXaxis()->SetLabelOffset(0.01);
  ratio_new_noextrap_hist->GetYaxis()->SetLabelSize(0.1);
  ratio_new_noextrap_hist->GetYaxis()->CenterTitle(kTRUE);
  ratio_new_noextrap_hist->GetYaxis()->SetNdivisions(309);
  ratio_new_noextrap_hist->SetMarkerSize(0);

  ratio_new_noextrap_hist->Draw("E");

  p2new->SetTicks(1, 1);
  p2new->RedrawAxis("G");
  
  cnew->cd();
  cnew->SaveAs(outDir + "bkgpred_comp_small_newratio_"+bkg+".pdf");
  cnew->SaveAs(outDir + "bkgpred_comp_small_newratio_"+bkg+".png");

  //Add new version with diff ratio
  auto call = MakeCanvas(1000, 600);
  TPad *p1all = new TPad("p1all","p1all",0,PAD_SPLIT_Y,1,1);
  p1all->SetLeftMargin  (0.16);
  p1all->SetTopMargin   (0.10);
  p1all->SetRightMargin (0.04);
  p1all->SetBottomMargin(0.03);
  p1all->Draw();
  p1all->cd();


  pred_hist->GetXaxis()->SetRangeUser(xlow, xhigh);
  pred_hist->GetYaxis()->SetRangeUser(0.01, 1e7);
  p1all->SetLogy();

  pred_hist->GetYaxis()->SetTitle("Prediction");
  pred_hist->GetYaxis()->SetTitleSize(0.07);
  pred_hist->GetYaxis()->SetTitleOffset(0.8);
  pred_hist->GetXaxis()->SetLabelOffset(0.6);
  pred_hist->GetXaxis()->SetNdivisions(520);
  pred_hist->Draw("hist");
  unc_all->SetFillColor(kBlue);
  unc_all->SetFillStyle(3013);
  unc_all->SetLineStyle(0);
  unc_all->SetLineWidth(0);
  unc_all->SetMarkerSize(0);
  unc_all->Draw("E2same");
  pred_noextrap->Draw("P0same");

  setLegend(leg_all, 1, 0.5, 0.70, 0.92, 0.87);
  leg_all->Draw();
  CMS_lumi(p1all, 4, 10);
  
  call->cd();
  drawTLatexNDC(splitlabels.at(0), 0.605, 0.76, 0.032);

  TPad *p2all = new TPad("p2all","p2all",0,0,1,PAD_SPLIT_Y);
  p2all->SetLeftMargin  (0.16);
  p2all->SetTopMargin   (0.00);
  p2all->SetRightMargin (0.04);
  p2all->SetBottomMargin(PAD_BOTTOM_MARGIN);
  p2all->SetGridy(1);
  p2all->Draw();
  p2all->cd();

  ratio_all_noextrap_hist->GetXaxis()->SetTitle("Search bin number");
  ratio_all_noextrap_hist->GetYaxis()->SetTitle("#frac{Unc.(extrap)}{Unc.(w/o extrap)}");
  ratio_all_noextrap_hist->GetXaxis()->SetRangeUser(xlow, xhigh);
  ratio_all_noextrap_hist->GetXaxis()->SetNdivisions(520);
  ratio_all_noextrap_hist->GetYaxis()->SetRangeUser(0, 1.501);
  ratio_all_noextrap_hist->GetXaxis()->SetTitleSize(0.12);
  ratio_all_noextrap_hist->GetYaxis()->SetTitleSize(0.09);
  ratio_all_noextrap_hist->GetYaxis()->SetTitleOffset(0.8);
  ratio_all_noextrap_hist->GetXaxis()->SetLabelSize(0.1);
  ratio_all_noextrap_hist->GetXaxis()->SetLabelOffset(0.01);
  ratio_all_noextrap_hist->GetYaxis()->SetLabelSize(0.1);
  ratio_all_noextrap_hist->GetYaxis()->CenterTitle(kTRUE);
  ratio_all_noextrap_hist->GetYaxis()->SetNdivisions(309);
  ratio_all_noextrap_hist->SetMarkerSize(0);

  ratio_all_noextrap_hist->Draw("E");

  p2all->SetTicks(1, 1);
  p2all->RedrawAxis("G");
  
  call->cd();
  call->SaveAs(outDir + "bkgpred_comp_small_allratio_"+bkg+".pdf");
  call->SaveAs(outDir + "bkgpred_comp_small_allratio_"+bkg+".png");

}
