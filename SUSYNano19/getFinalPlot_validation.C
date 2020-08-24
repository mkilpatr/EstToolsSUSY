#include "../utils/EstHelper.hh"
#include "LowMET_Parameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <string.h>
#include <functional>

using namespace EstTools;

void getFinalPlot_validation(TString inputDir="31Jul2020_Run2_dev_v7", TString outputName="getFinalPlot_validation"){

  gSystem->mkdir(outputName, true);

  RATIOPLOT_XTITLE_OFFSET = 1.25;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;
  if(inputDir.Contains("2016")) lumistr = "35.815165";

  TString inputFile = "/eos/uscms/store/user/lpcsusyhad/Stop_production/ValidationInputs/" + inputDir + "/";

  vector<TString> bkgs = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  TString data = "data";

  vector<TString> bkglabels = {"Lost lepton", "Z#rightarrow#nu#bar{#nu}", "QCD multijet", "t#bar{t}Z/Rare"};
  vector<TString> siglabels = {"T2tt(1000, 0)"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"lm",
			   "hm",
			   };
  vector<TString> splitlabels = {
      "Low #Deltam",
      "High #Deltam",
  };

  vector<double> ratioYmax = {2.999, 2.999};

  TLatex tl;
  tl.SetTextSize(0.025);
  tl.SetTextAlign(31);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){},
    [&tl](){},
    [&tl](){},
    [&tl](){},
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred, pred_leg;

  TFile *q = TFile::Open(inputFile + "QCD/Ex_Validation_QCDResidMET.root");
  assert(q);
  TH1D* hqcd = convertToHist({(TH1*)q->Get("QCD")}, "qcd_pred", ";Validation bin number;Events", nullptr);

  TFile *f = TFile::Open(inputFile+ "LostLepton/std_pred_trad_Run2_withttZRare.root");
  TFile *f_syst = TFile::Open(inputFile+ "LostLepton/Total.root");
  assert(f);
  TH1D* httbar = convertToHist({(TH1*)f->Get("ttbarplusw_pred")}, "httbar_pred", ";Validation bin number;Events", nullptr);

  TFile *ttz = TFile::Open(inputFile + "TTZRare/TTZ_final_vb.root");
  assert(ttz);
  TH1D* httz_low = convertToHist({(TH1*)ttz->Get("TTZ_vb_low")}, "ttz_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* httz_high = convertToHist({(TH1*)ttz->Get("TTZ_vb_high")}, "ttz_high_pred", ";Validation bin number;Events", nullptr);
  TH1D* httz_syst_up_low = convertToHist({(TH1*)ttz->Get("TTZ_vb_low_up")}, "ttz_syst_up_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* httz_syst_up_high = convertToHist({(TH1*)ttz->Get("TTZ_vb_high_up")}, "ttz_syst_up_high_pred", ";Validation bin number;Events", nullptr);
  TH1D* httz_syst_dn_low = convertToHist({(TH1*)ttz->Get("TTZ_vb_low_down")}, "ttz_syst_dn_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* httz_syst_dn_high = convertToHist({(TH1*)ttz->Get("TTZ_vb_high_down")}, "ttz_syst_dn_high_pred", ";Validation bin number;Events", nullptr);
  TH1* httz = (TH1*)httbar->Clone("ttz_pred");
  TH1* ttz_up_unc = (TH1*)httbar->Clone("ttz_syst_up");
  TH1* ttz_dn_unc = (TH1*)httbar->Clone("ttz_syst_dn");
  for (int ibin = 1; ibin < httz->GetNbinsX()+1; ++ibin){
    if(ibin < 20){ 
      httz->SetBinContent(ibin, httz_low->GetBinContent(ibin));
      httz->SetBinError(ibin, httz_low->GetBinError(ibin));
      ttz_up_unc->SetBinContent(ibin, httz_syst_up_low->GetBinContent(ibin));
      ttz_up_unc->SetBinError(ibin, 0);
      ttz_dn_unc->SetBinContent(ibin, httz_syst_dn_low->GetBinContent(ibin));
      ttz_dn_unc->SetBinError(ibin, 0);
    } else {
      httz->SetBinContent(ibin, httz_high->GetBinContent(ibin - 19));
      httz->SetBinError(ibin, httz_high->GetBinError(ibin - 19));
      ttz_up_unc->SetBinContent(ibin, httz_syst_up_low->GetBinContent(ibin - 19));
      ttz_up_unc->SetBinError(ibin, 0);
      ttz_dn_unc->SetBinContent(ibin, httz_syst_dn_low->GetBinContent(ibin - 19));
      ttz_dn_unc->SetBinError(ibin, 0);
    }
  }

  TFile *r = TFile::Open(inputFile + "TTZRare/Rare_final_vb.root");
  assert(r);
  TH1D* hRare_low = convertToHist({(TH1*)r->Get("Rare_vb_low")}, "Rare_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* hRare_high = convertToHist({(TH1*)r->Get("Rare_vb_high")}, "Rare_high_pred", ";Validation bin number;Events", nullptr);
  TH1D* hRare_syst_up_low = convertToHist({(TH1*)r->Get("Rare_vb_low_up")}, "Rare_syst_up_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* hRare_syst_up_high = convertToHist({(TH1*)r->Get("Rare_vb_high_up")}, "Rare_syst_up_high_pred", ";Validation bin number;Events", nullptr);
  TH1D* hRare_syst_dn_low = convertToHist({(TH1*)r->Get("Rare_vb_low_down")}, "Rare_syst_dn_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* hRare_syst_dn_high = convertToHist({(TH1*)r->Get("Rare_vb_high_down")}, "Rare_syst_dn_high_pred", ";Validation bin number;Events", nullptr);
  TH1* hRare = (TH1*)httbar->Clone("Rare_pred");
  TH1* Rare_up_unc = (TH1*)httbar->Clone("Rare_syst_up");
  TH1* Rare_dn_unc = (TH1*)httbar->Clone("Rare_syst_dn");
  for (int ibin = 1; ibin < hRare->GetNbinsX()+1; ++ibin){
    if(ibin < 20){ 
      hRare->SetBinContent(ibin, hRare_low->GetBinContent(ibin));
      hRare->SetBinError(ibin, hRare_low->GetBinError(ibin));
      Rare_up_unc->SetBinContent(ibin, hRare_syst_up_low->GetBinContent(ibin));
      Rare_up_unc->SetBinError(ibin, 0);
      Rare_dn_unc->SetBinContent(ibin, hRare_syst_dn_low->GetBinContent(ibin));
      Rare_dn_unc->SetBinError(ibin, 0);
    } else {
      hRare->SetBinContent(ibin, hRare_high->GetBinContent(ibin - 19));
      hRare->SetBinError(ibin, hRare_high->GetBinError(ibin - 19));
      Rare_up_unc->SetBinContent(ibin, hRare_syst_up_low->GetBinContent(ibin - 19));
      Rare_up_unc->SetBinError(ibin, 0);
      Rare_dn_unc->SetBinContent(ibin, hRare_syst_dn_low->GetBinContent(ibin - 19));
      Rare_dn_unc->SetBinError(ibin, 0);
    }
  }


  TFile *z = TFile::Open(inputFile + "Zinvisible/validationBinsZinv_Run2.root");
  TFile *z_syst = TFile::Open(inputFile + "Zinvisible/validationBinsZinv_syst_Run2.root");
  assert(z);
  TH1D* hznunu_low = convertToHist({(TH1*)z->Get("pred_lowdm")}, "znunu_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* hznunu_high = convertToHist({(TH1*)z->Get("pred_highdm")}, "znunu_high_pred", ";Validation bin number;Events", nullptr);
  TH1D* hznunu_syst_up_low = convertToHist({(TH1*)z_syst->Get("syst_up_lowdm")}, "znunu_syst_up_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* hznunu_syst_up_high = convertToHist({(TH1*)z_syst->Get("syst_up_highdm")}, "znunu_syst_up_high_pred", ";Validation bin number;Events", nullptr);
  TH1D* hznunu_syst_dn_low = convertToHist({(TH1*)z_syst->Get("syst_down_lowdm")}, "znunu_syst_dn_low_pred", ";Validation bin number;Events", nullptr);
  TH1D* hznunu_syst_dn_high = convertToHist({(TH1*)z_syst->Get("syst_down_highdm")}, "znunu_syst_dn_high_pred", ";Validation bin number;Events", nullptr);
  TH1* hznunu = (TH1*)httbar->Clone("znunu_pred");
  TH1* znunu_up_unc = (TH1*)httbar->Clone("znunu_syst_up");
  TH1* znunu_dn_unc = (TH1*)httbar->Clone("znunu_syst_dn");
  for (int ibin = 1; ibin < hznunu->GetNbinsX()+1; ++ibin){
    //cout << "ibin: " << ibin
    if(ibin < 20){ 
      hznunu->SetBinContent(ibin, hznunu_low->GetBinContent(ibin));
      hznunu->SetBinError(ibin, hznunu_low->GetBinError(ibin));
      znunu_up_unc->SetBinContent(ibin, hznunu_syst_up_low->GetBinContent(ibin));
      znunu_up_unc->SetBinError(ibin, 0);
      znunu_dn_unc->SetBinContent(ibin, hznunu_syst_dn_low->GetBinContent(ibin));
      znunu_dn_unc->SetBinError(ibin, 0);
    } else {
      hznunu->SetBinContent(ibin, hznunu_high->GetBinContent(ibin - 19));
      hznunu->SetBinError(ibin, hznunu_high->GetBinError(ibin - 19));
      znunu_up_unc->SetBinContent(ibin, hznunu_syst_up_low->GetBinContent(ibin - 19));
      znunu_up_unc->SetBinError(ibin, 0);
      znunu_dn_unc->SetBinContent(ibin, hznunu_syst_dn_low->GetBinContent(ibin - 19));
      znunu_dn_unc->SetBinError(ibin, 0);
    }
  }

  //Adding ttZ to Rare
  hRare->Add(httz);

  pred.push_back(hRare);
  pred.push_back(hqcd);
  pred.push_back(hznunu);
  pred.push_back(httbar);

  pred_leg.push_back(httbar);
  pred_leg.push_back(hznunu);
  pred_leg.push_back(hqcd);
  pred_leg.push_back(hRare);
  
  TH1* hdata = (TH1*)f->Get(data);

  //get all of the uncertainties
  TH1D* ttbar_up_unc = (TH1D*)f_syst->Get("Up");
  TH1D* ttbar_dn_unc = (TH1D*)f_syst->Get("Down");
  TH1D* qcd_up_unc = (TH1D*)q->Get("Tot_Up");
  TH1D* qcd_dn_unc = (TH1D*)q->Get("Tot_Down");

  TGraphAsymmErrors *unc = new TGraphAsymmErrors(httbar);
  //TGraphAsymmErrors* unc = (TGraphAsymmErrors*)f->Get("ttbarplusw_unc_sr")->Clone("bkgtotal_unc_sr");
  TH1D* nominal = (TH1D*)httbar->Clone("Total_Prediction");
  for (int ibin = 0; ibin < unc->GetN(); ++ibin){
    int ibin_hist = ibin+1;
    //Systematics
    double unc_up = ((ttbar_up_unc->GetBinContent(ibin_hist)-1)*httbar->GetBinContent(ibin_hist))*((ttbar_up_unc->GetBinContent(ibin_hist)-1)*httbar->GetBinContent(ibin_hist));
    double unc_dn = ((1-ttbar_dn_unc->GetBinContent(ibin_hist))*httbar->GetBinContent(ibin_hist))*((1-ttbar_dn_unc->GetBinContent(ibin_hist))*httbar->GetBinContent(ibin_hist));
    unc_up += ((ttz_up_unc->GetBinContent(ibin_hist)-1)*httz->GetBinContent(ibin_hist))*((ttz_up_unc->GetBinContent(ibin_hist)-1)*httz->GetBinContent(ibin_hist));
    unc_dn += ((1-ttz_dn_unc->GetBinContent(ibin_hist))*httz->GetBinContent(ibin_hist))*((1-ttz_dn_unc->GetBinContent(ibin_hist))*httz->GetBinContent(ibin_hist));
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
      unc_up += hznunu->GetBinError(ibin_hist)*hznunu->GetBinError(ibin_hist);
      unc_dn += hznunu->GetBinError(ibin_hist)*hznunu->GetBinError(ibin_hist);
    } else{
      unc_up += hznunu->GetBinError(ibin_hist)*hznunu->GetBinError(ibin_hist); //KH hack: when histograms from Caleb get this error correctly, use it.
      unc_dn += 0.;
    }
    unc_up += httz->GetBinError(ibin_hist)*httz->GetBinError(ibin_hist);
    unc_dn += httz->GetBinError(ibin_hist)*httz->GetBinError(ibin_hist);
    unc_up += hRare->GetBinError(ibin_hist)*hRare->GetBinError(ibin_hist);
    unc_dn += hRare->GetBinError(ibin_hist)*hRare->GetBinError(ibin_hist);

    //Nominal
    double pred = nominal->GetBinContent(ibin_hist);
    pred += hqcd->GetBinContent(ibin_hist);
    pred += hznunu->GetBinContent(ibin_hist);
    pred += hRare->GetBinContent(ibin_hist);
    pred += httz->GetBinContent(ibin_hist);

    cout << "bin: " << ibin << " pred: " << pred << " up: " << TMath::Sqrt(unc_up) << " dn: " << TMath::Sqrt(unc_dn) << endl;

    unc->SetPoint(ibin, unc->GetX()[ibin], pred);
    unc->SetPointEYhigh(ibin, TMath::Sqrt(unc_up));
    unc->SetPointEYlow(ibin,  TMath::Sqrt(unc_dn));
  }

  TH1* pull;
  if(hdata){
    pull = getPullHist(hdata, unc);
  }

  prepHists(pred, false, false, true, {797, 391, 811, 623, 866});
  prepHists(pred_leg, false, false, true, {866, 623, 811, 391, 797});
  if(hdata) prepHists({hdata}, false, false, false, {kBlack});
  if(hdata) prepHists({pull}, false, false, false, {kRed});

  hdata->SetMarkerStyle(7);

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


    if (region.Contains("lm")) {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 10.0;}
    else {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 1.0;}

    hdata->SetMarkerStyle(7);

    auto leg = prepLegends({hdata}, datalabel, "EP");
    appendLegends(leg, pred_leg, bkglabels, "F");
//    appendLegends(leg, {hDataRawMC}, {"Simulation", "L"});
  //  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    TCanvas* c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, {}, unc, {}, nullptr, false, false, true);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    drawTLatexNDC(splitlabels.at(ireg), 0.195, 0.78, 0.025);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "/pred_binnum__" + region;
    basename.ReplaceAll("nb[0-9]", "");
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
  }

  TFile *output = new TFile(outputName + "/pred_binnum_getFinalPlot_Nano.root", "RECREATE");
  for (auto *h : pred) h->Write();
  if(hdata) pull->Write();
  if(hdata) hdata->Write();
  output->Close();

}
