#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <string.h>
#include <functional>

using namespace EstTools;

void getFinalPlot(TString inputDir="31Jul2020_Run2_dev_v7", TString outputName="getFinalPlot_allMethods_CWR_021721", bool otherSig = false){

  gROOT->SetBatch(1);
  gSystem->mkdir(outputName, true);

  TDR_EXTRA_LABEL_ = "";

  RATIOPLOT_XTITLE_OFFSET = 1.05;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.02;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;
  if(inputDir.Contains("2016")) lumistr = "35.815165";

  TString inputFile = "/eos/uscms/store/user/lpcsusyhad/Stop_production/LimitInputs/" + inputDir + "/SearchBinsPlot/";

  vector<TString> bkgs = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  vector<TString> bkgs_post = {"TTZ", "Rare", "qcd", "znunu", "ttbarplusw"};
  vector<TString> sigs = {"T2tt_1000_100", "T1tttt_2000_400"};
  if(otherSig)    sigs = {"T2fbd_500_460", "T2cc_500_460"};
  TString data = "hdata";
  TString data_post = "Graph";

  vector<TString> bkglabels = {"Lost lepton", "Z#rightarrow#nu#bar{#nu}", "QCD multijet", "Rare"};
  vector<TString> siglabels = {"T2tt(1000,100)", "T1tttt(2000, 400)"};
  if(otherSig)    siglabels = {"T2ttC(500, 460)", "T2cc(500, 460)"};
  vector<TString> datalabel = {"Data"};

  vector<TString> split = {"lm",
			   "hm_nb1_bins",
			   "hm_nbeq2",
			   "hm_nb3"
			   };
  vector<TString> splitlabels = {
      "Low #Deltam",
      "High #Deltam, N_{b}#geq1, (N_{t}, N_{W}, N_{res})",
      "High #Deltam, N_{b}=2, (N_{t}, N_{W}, N_{res})",
      "High #Deltam, N_{b}#geq3, (N_{t}, N_{W}, N_{res})"
  };

  TLatex tl, tv, ts;
  tl.SetTextSize(0.025);
  tl.SetTextAlign(31);
  tl.SetTextFont(42);
  tv.SetTextSize(0.025);
  tv.SetTextAlign(31);
  tv.SetTextAngle(90);
  tv.SetTextFont(42);
  ts.SetTextSize(0.020);
  ts.SetTextAlign(31);
  ts.SetTextFont(42);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){ tl.DrawLatexNDC(0.3525, 0.73, "N_{b}=0, p_{T}^{ISR}#geq500 GeV"); 
	     tl.DrawLatexNDC(0.2425, 0.69, "N_{SV}=0"); 
	     tl.DrawLatexNDC(0.35, 0.69, "N_{SV}#geq1"); 
	     tl.DrawLatexNDC(0.57, 0.73, "N_{b}=1"); 
	     tl.DrawLatexNDC(0.54, 0.69, "N_{SV}=0");
	     tl.DrawLatexNDC(0.68, 0.69, "N_{SV}#geq1"); 
	     tl.DrawLatexNDC(0.85, 0.73, "N_{b}=2");},
    [&tl](){ tl.DrawLatexNDC(0.26, 0.73, "m_{T}^{b} < 175"); 
	     tl.DrawLatexNDC(0.277, 0.68, "N_{b}=1    N_{b}#geq2"); 
	     tl.DrawLatexNDC(0.37, 0.73, "(0, 0, 0)"); 
	     tl.DrawLatexNDC(0.395, 0.68, "N_{b}=1    N_{b}#geq2"); 
	     tl.DrawLatexNDC(0.5, 0.68, "(#geq1, 0, 0)"); 
	     tl.DrawLatexNDC(0.63, 0.68, "(0, #geq1, 0)"); 
	     tl.DrawLatexNDC(0.78, 0.68, "(0, 0, #geq1)");},
    [&tl](){ tl.DrawLatexNDC(0.27, 0.70, "(1, 0, 0)"); 
	     tl.DrawLatexNDC(0.39, 0.70, "(0, 1, 0)"); 
	     tl.DrawLatexNDC(0.55, 0.70, "(0, 0, 1)");},
    [&tl](){ tl.DrawLatexNDC(0.32, 0.70, "(1, 0, 0)");
	     tl.DrawLatexNDC(0.47, 0.70, "(0, 1, 0)");
	     tl.DrawLatexNDC(0.63, 0.70, "(0, 0, 1)");},
  };

  vector<std::function<void()>> drawRegionLabelsSmall {
    [&ts](){ ts.DrawLatexNDC(0.6225, 0.66, "p_{T}^{ISR}[300, 500) GeV    p_{T}^{ISR}#geq500 GeV");
	     ts.DrawLatexNDC(0.92, 0.66,   "p_{T}^{ISR}[300, 500) GeV    p_{T}^{ISR}#geq500 GeV");},
    [&ts](){ },
    [&ts](){ },
    [&ts](){ },
  };

  vector<std::function<void()>> drawRegionLabelsVertical {
    [&tv](){},
    [&tv](){ tv.DrawLatexNDC(0.89, 0.73, "(#geq1, 0, #geq1)"); 
	     tv.DrawLatexNDC(0.92, 0.73, "(#geq1, #geq1, 0)"); 
	     tv.DrawLatexNDC(0.95, 0.73, "(0, #geq1, #geq1)");},
    [&tv](){ tv.DrawLatexNDC(0.68, 0.70, "(1, 1, 0)"); 
	     tv.DrawLatexNDC(0.75, 0.70, "(1, 0, 1)"); 
	     tv.DrawLatexNDC(0.815, 0.70, "(0, 1, 1)"); 
	     tv.DrawLatexNDC(0.845, 0.70, "(2, 0, 0)"); 
	     tv.DrawLatexNDC(0.875, 0.70, "(0, 2, 0)"); 
	     tv.DrawLatexNDC(0.92, 0.70, "(0, 0, 2)"); 
	     tv.DrawLatexNDC(0.985, 0.70, "(N_{t} + N_{res} + N_{W})#geq3");},
    [&tv](){ tv.DrawLatexNDC(0.74, 0.70, "(1, 1, 0)"); 
	     tv.DrawLatexNDC(0.78, 0.70, "(1, 0, 1)"); 
	     tv.DrawLatexNDC(0.82, 0.70, "(0, 1, 1)"); 
	     tv.DrawLatexNDC(0.845, 0.70, "(2, 0, 0)"); 
	     tv.DrawLatexNDC(0.875, 0.70, "(0, 2, 0)"); 
	     tv.DrawLatexNDC(0.91, 0.70, "(0, 0, 2)"); 
	     tv.DrawLatexNDC(0.985, 0.70, "(N_{t} + N_{res} + N_{W})#geq3");},
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(8.05,  LOG_YMIN, 8.05,   2000); 
								    drawLine(16.05, LOG_YMIN, 16.05,  200000); 
								    drawLine(24.05, LOG_YMIN, 24.05,  2000); 
								    drawLine(32.05, LOG_YMIN, 32.05,  2000); 
								    drawLine(35.05, LOG_YMIN, 35.05,  200000); 
								    drawLine(44.05, LOG_YMIN, 44.05,  2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(57.05, LOG_YMIN, 57.05, 2000); 
								    drawLine(61.05, LOG_YMIN, 61.05, 20000); 
								    drawLine(65.05, LOG_YMIN, 65.05, 2000); 
								    drawLine(69.05, LOG_YMIN, 69.05, 20000); 
								    drawLine(78.05, LOG_YMIN, 78.05, 20000); 
								    drawLine(84.05, LOG_YMIN, 84.05, 20000); 
								    drawLine(99.05, LOG_YMIN, 99.05, 20000); 
								    drawLine(101.05, LOG_YMIN, 101.05, 20000); 
								    drawLine(103.05, LOG_YMIN, 103.05, 20000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(114.05, LOG_YMIN, 114.05, 2000); 
								    drawLine(120.05, LOG_YMIN, 120.05, 2000); 
								    drawLine(135.05, LOG_YMIN, 135.05, 2000); 
								    drawLine(137.05, LOG_YMIN, 137.05, 2000); 
								    drawLine(143.05, LOG_YMIN, 143.05, 2000); 
								    drawLine(145.05, LOG_YMIN, 145.05, 2000); 
								    drawLine(147.05, LOG_YMIN, 147.05, 2000); 
								    drawLine(148.05, LOG_YMIN, 148.05, 2000); 
								    drawLine(152.05, LOG_YMIN, 152.05, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(162.05, LOG_YMIN, 162.05, 200); 
								    drawLine(165.05, LOG_YMIN, 165.05, 200); 
								    drawLine(174.05, LOG_YMIN, 174.05, 200); 
								    drawLine(175.05, LOG_YMIN, 175.05, 200); 
								    drawLine(177.05, LOG_YMIN, 177.05, 200); 
								    drawLine(178.05, LOG_YMIN, 178.05, 200); 
								    drawLine(179.05, LOG_YMIN, 179.05, 200); 
								    drawLine(180.05, LOG_YMIN, 180.05, 200); 
								    drawLine(182.05, LOG_YMIN, 182.05, 200); c->cd(); },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred, pred_leg, pred_post;
  vector<TH1*> pred_comp, pred_comp_post;
  vector<TH1*> hsigs;

  TString suffix = "";
  if(inputDir.Contains("2016")) suffix = "_2016";
  TFile *ttz = TFile::Open(inputFile + "TTZ_final_sb" + suffix + ".root");
  assert(ttz);
  TH1D* httZ = convertToHist({(TH1*)ttz->Get("Prediction")}, "ttZ_pred", ";Search bin number;Events", nullptr);
  TH1D* httZ_comp = convertToHist({(TH1*)ttz->Get("Prediction")}, "ttZ_comp", ";Search bin number;Events", nullptr);

  TFile *r = TFile::Open(inputFile + "Rare_final_sb" + suffix + ".root");
  assert(r);
  TH1D* hRare = convertToHist({(TH1*)r->Get("Prediction")}, "Rare_pred", ";Search bin number;Events", nullptr);
  TH1D* hRare_comp = convertToHist({(TH1*)r->Get("Prediction")}, "Rare_comp", ";Search bin number;Events", nullptr);

  TFile *q = TFile::Open(inputFile + "SearchBins_QCDResidMET.root");
  assert(q);
  TH1D* hqcd = convertToHist({(TH1*)q->Get("QCD")}, "qcd_pred", ";Search bin number;Events", nullptr);
  TH1D* hqcd_comp = convertToHist({(TH1*)q->Get("QCD")}, "qcd_comp", ";Search bin number;Events", nullptr);

  if(!inputDir.Contains("2016")) suffix = "_Run2";

  TFile *z = TFile::Open(inputFile + "searchBinsZinv_combined" + suffix + ".root");
  assert(z);
  TH1D* hznunu = convertToHist({(TH1*)z->Get("Prediction")}, "znunu_pred", ";Search bin number;Events", nullptr);
  TH1D* hznunu_comp = convertToHist({(TH1*)z->Get("Prediction")}, "znunu_comp", ";Search bin number;Events", nullptr);

  if(inputDir.Contains("2016")) suffix = "_2016";
  else suffix = "";
  TFile *f = TFile::Open("getFinalPlot" + suffix + "/SumOfBkg.root");
  assert(f);
  TH1D* httbar = convertToHist({(TH1*)f->Get("httbar")}, "httbar_pred", ";Search bin number;Events", nullptr);
  TH1D* httbar_comp = convertToHist({(TH1*)f->Get("httbar")}, "httbar_comp", ";Search bin number;Events", nullptr);
  TH1D* hznunu_aux = convertToHist({(TH1*)f->Get("hznunu")}, "hznunu_pred", ";Search bin number;Events", nullptr); // KH hack: this is a hack which we should be careful with

  TFile *p = TFile::Open("PostFit_v7.root");
  assert(p);
  TH1D* hist_buff = nullptr;
  for (auto &b : bkgs_post){
    TH1D* hist = convertToHist({(TH1*)p->Get(b)}, b + "_post", ";Search bin number;Events", nullptr);
    TH1D* hist_comp = convertToHist({(TH1*)p->Get(b)}, b + "_comp", ";Search bin number;Events", nullptr);
    if(b == "TTZ") hist_buff = (TH1D*)hist->Clone("httZ_add");
    if(b == "Rare") hist->Add(hist_buff);

    if(b != "TTZ") pred_post.push_back(hist);
    pred_comp_post.push_back(hist_comp);
  }

  pred_comp.push_back(httZ_comp);
  pred.push_back(hRare);
  pred_comp.push_back(hRare_comp);
  pred.push_back(hqcd);
  pred_comp.push_back(hqcd_comp);
  pred.push_back(hznunu);
  pred_comp.push_back(hznunu_comp);
  pred.push_back(httbar);
  pred_comp.push_back(httbar_comp);

  pred_leg.push_back(httbar);
  pred_leg.push_back(hznunu);
  pred_leg.push_back(hqcd);
  pred_leg.push_back(hRare);

  TH1* hdata = (TH1*)f->Get(data);
  TGraphAsymmErrors* gdata = (TGraphAsymmErrors*)p->Get(data_post);
  TH1D* hdata_post = new TH1D("data_post", "data_post", 183, 0, 183);
  for(int i=0; i < gdata->GetN(); ++i) {
    double x = 0., y = 0.;
    gdata->GetPoint(i, x, y);
    hdata_post->Fill(x+1,y);
    hdata_post->SetBinError(i, gdata->GetErrorY(i));
  }

  //get all of the uncertainties
  TH1D* ttbar_up_unc = (TH1D*)f->Get("ttbarplusw_syst_up");
  TH1D* ttbar_dn_unc = (TH1D*)f->Get("ttbarplusw_syst_dn");
  TH1D* znunu_up_unc = (TH1D*)f->Get("znunu_syst_up");
  TH1D* znunu_dn_unc = (TH1D*)f->Get("znunu_syst_dn");
  TH1D* ttZ_up_unc = (TH1D*)ttz->Get("Total_Up");
  TH1D* ttZ_dn_unc = (TH1D*)ttz->Get("Total_Down");
  TH1D* Rare_up_unc = (TH1D*)r->Get("Total_Up");
  TH1D* Rare_dn_unc = (TH1D*)r->Get("Total_Down");
  TH1D* qcd_up_unc = (TH1D*)q->Get("Tot_Up");
  TH1D* qcd_dn_unc = (TH1D*)q->Get("Tot_Down");
  //TH1D* znunu_up_unc = (TH1D*)z->Get("Total_Up");
  //TH1D* znunu_dn_unc = (TH1D*)z->Get("Total_Down");

  //Make unc for prefit
  TGraphAsymmErrors* unc = (TGraphAsymmErrors*)f->Get("ttbarplusw_unc_sr")->Clone("bkgtotal_unc_sr");
  TH1D* nominal = (TH1D*)httbar->Clone("Total_Prediction");
  for (int ibin = 0; ibin < unc->GetN(); ++ibin){
    int ibin_hist = ibin+1;
    //Systematics
    double unc_up = ((ttbar_up_unc->GetBinContent(ibin_hist)-1)*httbar->GetBinContent(ibin_hist))*((ttbar_up_unc->GetBinContent(ibin_hist)-1)*httbar->GetBinContent(ibin_hist));
    double unc_dn = ((1-ttbar_dn_unc->GetBinContent(ibin_hist))*httbar->GetBinContent(ibin_hist))*((1-ttbar_dn_unc->GetBinContent(ibin_hist))*httbar->GetBinContent(ibin_hist));
    unc_up += ((ttZ_up_unc->GetBinContent(ibin_hist)-1)*httZ->GetBinContent(ibin_hist))*((ttZ_up_unc->GetBinContent(ibin_hist)-1)*httZ->GetBinContent(ibin_hist));
    unc_dn += ((1-ttZ_dn_unc->GetBinContent(ibin_hist))*httZ->GetBinContent(ibin_hist))*((1-ttZ_dn_unc->GetBinContent(ibin_hist))*httZ->GetBinContent(ibin_hist));
    unc_up += ((Rare_up_unc->GetBinContent(ibin_hist)-1)*hRare->GetBinContent(ibin_hist))*((Rare_up_unc->GetBinContent(ibin_hist)-1)*hRare->GetBinContent(ibin_hist));
    unc_dn += ((1-Rare_dn_unc->GetBinContent(ibin_hist))*hRare->GetBinContent(ibin_hist))*((1-Rare_dn_unc->GetBinContent(ibin_hist))*hRare->GetBinContent(ibin_hist));
    unc_up += ((qcd_up_unc->GetBinContent(ibin_hist)-1)*hqcd->GetBinContent(ibin_hist))*((qcd_up_unc->GetBinContent(ibin_hist)-1)*hqcd->GetBinContent(ibin_hist));
    unc_dn += ((1-qcd_dn_unc->GetBinContent(ibin_hist))*hqcd->GetBinContent(ibin_hist))*((1-qcd_dn_unc->GetBinContent(ibin_hist))*hqcd->GetBinContent(ibin_hist));
    unc_up += ((znunu_up_unc->GetBinContent(ibin_hist)-1)*hznunu->GetBinContent(ibin_hist))*((znunu_up_unc->GetBinContent(ibin_hist)-1)*hznunu->GetBinContent(ibin_hist));
    unc_dn += ((1-znunu_dn_unc->GetBinContent(ibin_hist))*hznunu->GetBinContent(ibin_hist))*((1-znunu_dn_unc->GetBinContent(ibin_hist))*hznunu->GetBinContent(ibin_hist));

    //Statistical
    // ttbar:
    unc_up += httbar->GetBinError(ibin_hist)*httbar->GetBinError(ibin_hist);
    if(httbar->GetBinContent(ibin_hist) != 0)
      unc_dn += httbar->GetBinError(ibin_hist)*httbar->GetBinError(ibin_hist);
    else unc_dn += 0.; //
    // qcd:
    unc_up += hqcd->GetBinError(ibin_hist)*hqcd->GetBinError(ibin_hist);
    unc_dn += hqcd->GetBinError(ibin_hist)*hqcd->GetBinError(ibin_hist);
    // znunu:
    if(hznunu->GetBinContent(ibin_hist) != 0){
      unc_up += hznunu_aux->GetBinError(ibin_hist)*hznunu_aux->GetBinError(ibin_hist);
      unc_dn += hznunu_aux->GetBinError(ibin_hist)*hznunu_aux->GetBinError(ibin_hist);
    } else{
      unc_up += hznunu_aux->GetBinError(ibin_hist)*hznunu_aux->GetBinError(ibin_hist); //KH hack: when histograms from Caleb get this error correctly, use it.
      unc_dn += 0.;
    }
    unc_up += httZ->GetBinError(ibin_hist)*httZ->GetBinError(ibin_hist);
    unc_dn += httZ->GetBinError(ibin_hist)*httZ->GetBinError(ibin_hist);
    unc_up += hRare->GetBinError(ibin_hist)*hRare->GetBinError(ibin_hist);
    unc_dn += hRare->GetBinError(ibin_hist)*hRare->GetBinError(ibin_hist);

    //Data
    Quantity q_data = getHistBin(hdata, ibin_hist);

    //Nominal
    double pred = nominal->GetBinContent(ibin_hist);
    pred += hqcd->GetBinContent(ibin_hist);
    pred += hznunu->GetBinContent(ibin_hist);
    pred += hRare->GetBinContent(ibin_hist);
    pred += httZ->GetBinContent(ibin_hist);
    //if(q_data.error > (unc_up - pred) || q_data.error > (pred - unc_dn)){
    //  cout << "Bin: " << ibin_hist << endl;
    //  cout << "ttbar pred: " << nominal->GetBinContent(ibin_hist) << endl;
    //  cout << "qcd pred: " << hqcd->GetBinContent(ibin_hist) << endl;
    //  cout << "znunu pred: " << hznunu->GetBinContent(ibin_hist) << endl;
    //  cout << "Rare pred: " << hRare->GetBinContent(ibin_hist) << endl;
    //  cout << "httZ pred: " << httZ->GetBinContent(ibin_hist) << endl;
    //  cout << "bin: " << ibin << " pred: " << pred << " up: " << TMath::Sqrt(unc_up) << " dn: " << TMath::Sqrt(unc_dn) << endl;
    //  cout << "bin: " << ibin << " data: " << q_data.value << " +/- " << q_data.error << endl;
    //}

    unc->SetPoint(ibin, unc->GetX()[ibin], pred);
    unc->SetPointEYhigh(ibin, TMath::Sqrt(unc_up));
    unc->SetPointEYlow(ibin,  TMath::Sqrt(unc_dn));
  }

  //Make unc for postfit
  //Adding ttZ to Rare
  hRare->Add(httZ);
  TGraphAsymmErrors* unc_post = (TGraphAsymmErrors*)p->Get("Sumb");

  int style = 2;
  for (auto &s : sigs){
    TH1 *h = convertToHist({(TH1*)f->Get(s)}, s, ";Search bin number;Events", nullptr);
    h->SetLineStyle(style);
    h->SetLineWidth(3);
    hsigs.push_back(h);
    style++;
  }

  TH1* pull;
  TH1* pull_post;
  if(hdata) pull = getPullHist(hdata, unc, false, "Search Regions", 0, true);
  if(hdata_post) pull_post = getPullHist(hdata_post, unc_post);

  prepHists(pred,      false, false, true, {391, 811, 623, 866});
  prepHists(pred_post, false, false, true, {391, 811, 623, 866});
  prepHists(pred_comp,      false, false, false, {kRed, kRed, kRed, kRed, kRed});
  prepHists(pred_comp_post, false, false, false, {kBlue, kBlue, kBlue, kBlue, kBlue});
  prepHists(pred_leg, false, false, true, {866, 623, 811, 391});
  if(hdata) prepHists({hdata, hdata_post}, false, false, false, {kBlack, kBlack});
  cout << "Data Line width = " << hdata->GetLineWidth() << endl;
  if(hdata_post) prepHists({hdata_post}, false, false, false, {kBlack});
  if(hdata) prepHists({pull, pull_post}, false, false, false, {kRed, kRed});
  if(hdata_post) prepHists({pull_post}, false, false, false, {kRed});
  prepHists(hsigs, false, false, false, {kRed, kGreen + 3});
  if(otherSig) prepHists(hsigs, false, false, false, {kViolet+2, kGreen +3});
  unc->SetFillColor(kBlue);
  unc->SetFillStyle(3013);
  unc->SetLineStyle(0);
  unc->SetLineWidth(0);
  unc->SetMarkerSize(0);
  unc->Draw("E2same");



  vector<TH1*> ratio;
  for (unsigned bkg = 0; bkg != pred_comp.size(); bkg++){
    TH1* hr = (TH1*)pred_comp[bkg]->Clone(bkgs[bkg] + "_ratio");
    hr->Divide(pred_comp_post[bkg]);
    hr->SetLineWidth(2);
    prepHists({hr}, false, false, false, {kRed});
    ratio.push_back(hr);
  }

  auto catMap = srCatMap();
  for (unsigned ireg = 0; ireg < split.size(); ++ireg){
    auto &region = split.at(ireg);
    int xlow = 0, xhigh = 0;
    bool isfirst = true;
    int ibin = 0;
    for (auto &cat_name : srbins){
      auto nbins = catMap.at(cat_name).bin.nbins;
      if (cat_name.Contains(TRegexp(region)) || 
	 (TString(region).Contains("hm_nb1_bins") && (cat_name.Contains("hm_nb1") || cat_name.Contains("highmtb_nt0_nrt0_nw0") || cat_name.Contains("lowmtb_nj7_nrtgeq1"))) //hm_nb1_bins
         ){
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

    if (region.Contains("lm")) {LOG_YMIN = 0.1; PLOT_MAX_YSCALE = 1.0;}
    else if (region.Contains("hm_nbeq2")) {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 0.001;}
    else if (region.Contains("hm_nb3")) {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 0.0001;}
    else {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 1.0;}

    hdata->SetMarkerStyle(8);
    hdata_post->SetMarkerStyle(8);

    auto leg = prepLegends({hdata}, datalabel, "EP");
    appendLegends(leg, pred_leg, bkglabels, "F");
    addLegendEntry(leg, unc,"Bkg. uncertainty","F");
    appendLegends(leg, hsigs, siglabels, "L");
    setLegend(leg, 2, 0.49, 0.63, 0.97, 0.87);
    TCanvas* c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0, 1.999, xlow, xhigh, hsigs, unc, {}, nullptr, false, false, true);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    drawTLatexNDC(splitlabels.at(ireg), 0.195, 0.84, 0.030);
    drawRegionLabels.at(ireg)();
    drawRegionLabelsSmall.at(ireg)();
    drawRegionLabelsVertical.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "/pred_binnum__" + region;
    basename.ReplaceAll("nb[0-9]", "");
    c->Print(basename+".png");
    c->Print(basename+".pdf");
    c->Print(basename+".C");

    leg = prepLegends({hdata_post}, datalabel, "EP");
    appendLegends(leg, pred_leg, bkglabels, "F");
    addLegendEntry(leg, unc,"Bkg. uncertainty","F");
    appendLegends(leg, hsigs, siglabels, "L");
    setLegend(leg, 2, 0.49, 0.63, 0.97, 0.87);
    c = drawStackAndRatio(pred_post, hdata_post, leg, true, "N_{obs}/N_{exp}", 0, 1.999, xlow, xhigh, hsigs, unc_post, {}, nullptr, false, false, true);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    drawTLatexNDC(splitlabels.at(ireg), 0.195, 0.84, 0.030);
    drawRegionLabels.at(ireg)();
    drawRegionLabelsSmall.at(ireg)();
    drawRegionLabelsVertical.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    basename = outputName + "/pred_binnum__postfit_" + region;
    basename.ReplaceAll("nb[0-9]", "");
    c->Print(basename+".png");
    c->Print(basename+".pdf");
    c->Print(basename+".C");
  }

  for (unsigned bkg = 0; bkg != pred_comp.size(); bkg++){
    auto leg = prepLegends({}, {""}, "L");
    appendLegends(leg, {pred_comp[bkg]}, {bkgs[bkg]}, "L");
    appendLegends(leg, {pred_comp_post[bkg]}, {bkgs[bkg] + " Postfit"}, "L");
    setLegend(leg, 2, 0.49, 0.63, 0.97, 0.87);
 
    TCanvas* c = drawCompAndRatio({pred_comp[bkg], pred_comp_post[bkg]}, {ratio[bkg]}, leg, "N_{post}/N_{pre}", 0.749, 1.249, false, 0.001, -1., false);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    TString basename = outputName + "/pred_binnum__" + bkgs_post[bkg];
    c->Print(basename+".pdf");
  }

  if(hdata){
    double mean  = pull->GetMean();
    double StdDev = pull->GetStdDev();
    TString fitString = "#splitline{Mean = " + to_string(mean) + "}{StdDev = " + to_string(StdDev) + "}";
    std::function<void(TCanvas*)> plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC(fitString, 0.2, 0.72); };
    auto c_pull = drawCompMatt({pull}, 0, -1., &plotextra);
    c_pull->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    TString basename = outputName + "/pred_binnum__pull";
    c_pull->Print(basename+".pdf");

    mean  = pull_post->GetMean();
    StdDev = pull_post->GetStdDev();
    fitString = "#splitline{Mean = " + to_string(mean) + "}{StdDev = " + to_string(StdDev) + "}";
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC(fitString, 0.2, 0.72); };
    c_pull = drawCompMatt({pull_post}, 0, -1., &plotextra);
    c_pull->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    basename = outputName + "/pred_binnum__postfit_pull";
    c_pull->Print(basename+".pdf");
  }

  TFile *output = new TFile(outputName + "/pred_binnum_getFinalPlot_Nano.root", "RECREATE");
  for (auto *h : pred) h->Write();
  for (auto *h : pred_post) h->Write();
  for (auto *s : hsigs) s->Write();
  if(hdata) pull->Write();
  if(hdata_post) pull_post->Write();
  if(hdata) hdata->Write();
  if(hdata) hdata_post->Write();
  unc->Write();
  output->Close();

}
