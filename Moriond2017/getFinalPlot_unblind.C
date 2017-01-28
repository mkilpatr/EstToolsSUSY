#include "../utils/EstHelper.hh"
#include "SRParameters_unblind.hh"
#include "TLatex.h"
#include <functional>
#include <regex>

using namespace EstTools;

void getFinalPlot_unblind(TString inputFile="std_pred_trad_unblind.root", TString outputName="/tmp/plots/unblind_18p2ifb/pred", bool plotPulls=false){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.04;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;

  vector<TString> bkgs = {"diboson_pred", "ttZ_pred", "qcd_pred", "znunu_pred", "ttbarplusw_pred"};
  vector<TString> mcs =  {"diboson_mc",   "ttZ_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  TString data = "data";
  TString ratiolabel = "N_{obs}/N_{exp}";

  vector<TString> bkglabels = {"Diboson", "ttZ", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> datalabel = {"Observed"};
  vector<TString> rawsimlabel = {"Simulation"};

  vector<TString> split = {"lm_nb0", "lm_nb1", "lm_nb2",
      "hm_nb(1|2)_(high|low)mtb_nj7", "hm_nb1_highmtb_nt",
      "hm_nb2_highmtb_(nt1_nrt0_nw0|nt0_nrt1_nw0|nt0_nrt0_nw1)",
      "hm_nb2_highmtb_(nt1_nrt0_nw1|nt0_nrt1_nw1|nt1_nrt1_nw0|nt2_nrt0_nw0|nt0_nrt2_nw0|nt0_nrt0_nw2)"};
  vector<TString> splitlabels = {
      "#splitline{Low #DeltaM}{N_{b}=0}",
      "#splitline{Low #DeltaM}{N_{b}=1}",
      "#splitline{Low #DeltaM}{N_{b}#geq2}",
      "#splitline{High #DeltaM}{#geq 7 jets}",
      "#splitline{High #DeltaM}{M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV, N_{b}=1}",
      "#splitline{High #DeltaM}{M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV, N_{b}#geq2, 1 top- or W-tag}",
      "#splitline{High #DeltaM}{M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV, N_{b}#geq2, #geq 2 top- or W-tags}",
  };

  vector<double> ratioYmax = {2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999};

  TLatex tl;
  tl.SetTextSize(0.033);
  tl.SetTextAlign(31);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){
      tl.SetTextSize(0.033);
      tl.DrawLatexNDC(0.4, 0.7, "N_{SV}=0"); tl.DrawLatexNDC(0.8, 0.7, "N_{SV}#geq1");
      tl.DrawLatexNDC(0.29, 0.66, "2-5 jets"); tl.DrawLatexNDC(0.48, 0.66, "#geq 6 jets");
      tl.DrawLatexNDC(0.7, 0.66, "2-5 jets"); tl.DrawLatexNDC(0.9, 0.66, "#geq 6 jets");
    },
    [&tl](){
      tl.SetTextSize(0.027);
      tl.DrawLatexNDC(0.44, 0.7, "N_{SV} = 0, 300 < p_{T}(ISR) < 500"); tl.DrawLatexNDC(0.75, 0.7, "N_{SV} = 0, p_{T}(ISR) > 500"); tl.DrawLatexNDC(0.93, 0.7, "N_{SV} #geq 1");
      tl.DrawLatexNDC(0.29, 0.66, "p_{T}(b) < 40"); tl.DrawLatexNDC(0.48, 0.66, "40 #leq p_{T}(b) < 70");
      tl.DrawLatexNDC(0.62, 0.66, "p_{T}(b) < 40"); tl.DrawLatexNDC(0.82, 0.66, "40 #leq p_{T}(b) < 70");
      tl.DrawLatexNDC(0.94, 0.66, "p_{T}(b) < 40");
    },
    [&tl](){
      tl.SetTextSize(0.027);
      tl.DrawLatexNDC(0.48, 0.7, "300 < p_{T}(ISR) < 500"); tl.DrawLatexNDC(0.8, 0.7, "p_{T}(ISR) > 500");
      tl.SetTextSize(0.024);
      tl.DrawLatexNDC(0.28, 0.66, "p_{T}(b_{12}) < 80"); tl.DrawLatexNDC(0.43, 0.66, "80 #leq p_{T}(b_{12}) < 140");
      tl.DrawLatexNDC(0.55, 0.64, "#splitline{p_{T}(b_{12}) > 140}{#geq 7 jets}");
      tl.DrawLatexNDC(0.68, 0.66, "p_{T}(b_{12}) < 80"); tl.DrawLatexNDC(0.84, 0.66, "80 #leq p_{T}(b_{12}) < 140");
      tl.DrawLatexNDC(0.95, 0.64, "#splitline{p_{T}(b_{12}) > 140}{#geq 7 jets}");
    },

    [&tl](){
      tl.SetTextSize(0.029);
      tl.DrawLatexNDC(0.48, 0.68, "M_{T}(b_{1,2},#slash{E}_{T}) < 175, N_{res} #geq 1"); tl.DrawLatexNDC(0.86, 0.66, "#splitline{M_{T}(b_{1,2},#slash{E}_{T}) > 175,}{N_{t} = 0, N_{W} = 0, N_{res} = 0}");
      tl.DrawLatexNDC(0.29, 0.6, "N_{b} = 1"); tl.DrawLatexNDC(0.48, 0.6, "N_{b} #geq 2");
      tl.DrawLatexNDC(0.7, 0.6, "N_{b} = 1"); tl.DrawLatexNDC(0.9, 0.6, "N_{b} #geq 2");
    },
    [&tl](){
      tl.SetTextSize(0.027);
      tl.DrawLatexNDC(0.29, 0.65, "N_{t} #geq 1, N_{W} = 0"); tl.DrawLatexNDC(0.27, 0.62, "N_{res} = 0");
      tl.DrawLatexNDC(0.54, 0.65, "N_{t} = 0, N_{W} = 0, N_{res} #geq 1");
      tl.DrawLatexNDC(0.679, 0.65, "N_{t} #geq 1"); tl.DrawLatexNDC(0.686, 0.62, "N_{W} #geq 1"); tl.DrawLatexNDC(0.693, 0.59, "N_{res} = 0");
      tl.DrawLatexNDC(0.92, 0.65, "N_{t} = 0, N_{W} #geq 1, N_{res} #geq 1");
    },
    [&tl](){
      tl.SetTextSize(0.027);
      tl.DrawLatexNDC(0.29, 0.65, "N_{t} = 1, N_{W} = 0"); tl.DrawLatexNDC(0.27, 0.62, "N_{res} = 0");
      tl.DrawLatexNDC(0.54, 0.65, "N_{t} = 0, N_{W} = 0, N_{res} = 1");
      tl.DrawLatexNDC(0.87, 0.65, "N_{t} = 0, N_{W} = 1, N_{res} = 0");
    },
    [&tl](){
      tl.SetTextSize(0.027);
      tl.DrawLatexNDC(0.219, 0.65, "N_{t} = 1"); tl.DrawLatexNDC(0.226, 0.62, "N_{W} = 1"); tl.DrawLatexNDC(0.233, 0.59, "N_{res} = 0");
      tl.DrawLatexNDC(0.47, 0.65, "N_{t} = 0, N_{W} = 1, N_{res} = 1");
      tl.DrawLatexNDC(0.73, 0.65, "N_{t} = 1, N_{W} = 0, N_{res} = 1");
      tl.DrawLatexNDC(0.799, 0.65, "N_{t} #geq 2"); tl.DrawLatexNDC(0.806, 0.62, "N_{W} = 0"); tl.DrawLatexNDC(0.811, 0.59, "N_{res} = 0");
      tl.DrawLatexNDC(0.876, 0.65, "N_{t} = 0"); tl.DrawLatexNDC(0.886, 0.62, "N_{W} #geq 2"); tl.DrawLatexNDC(0.888, 0.59, "N_{res} = 0");
      tl.DrawLatexNDC(0.946, 0.65, "N_{t} = 0"); tl.DrawLatexNDC(0.953, 0.62, "N_{W} = 0"); tl.DrawLatexNDC(0.956, 0.59, "N_{res} #geq 2");

    },
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(4,  LOG_YMIN, 4,  2000);
    drawLine(8,  LOG_YMIN, 8,  20000);
    drawLine(12, LOG_YMIN, 12, 2000);
    c->cd();
    },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(20, LOG_YMIN, 20, 2000);
    drawLine(24, LOG_YMIN, 24, 20000);
    drawLine(28, LOG_YMIN, 28, 2000);
    drawLine(32, LOG_YMIN, 32, 20000);
    c->cd();
    },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(38, LOG_YMIN, 38, 600);
    drawLine(41, LOG_YMIN, 41, 600);
    drawLine(44, LOG_YMIN, 44, 6000);
    drawLine(47, LOG_YMIN, 47, 600);
    drawLine(50, LOG_YMIN, 50, 600);
    c->cd(); },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(57, LOG_YMIN, 57, 2000);
    drawLine(61, LOG_YMIN, 61, 20000);
    drawLine(65, LOG_YMIN, 65, 2000);
    c->cd(); },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(71, LOG_YMIN, 71, 2000);
    drawLine(76, LOG_YMIN, 76, 2000);
    drawLine(77, LOG_YMIN, 77, 2000);
    c->cd(); },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(83, LOG_YMIN, 83, 2000);
    drawLine(88, LOG_YMIN, 88, 2000);
    drawLine(93, LOG_YMIN, 93, 2000);
    c->cd(); },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd();
    drawLine(94, LOG_YMIN, 94, 200);
    drawLine(98, LOG_YMIN, 98, 200);
    drawLine(101, LOG_YMIN, 101, 200);
    drawLine(102, LOG_YMIN, 102, 200);
    drawLine(103, LOG_YMIN, 103, 200);
    c->cd(); },
  };

  vector<double> plot_ymax_scales = { 1,    1,    0.1,  0.1, 1,    0.1,  0.01 };
  vector<double> plot_log_ymin    = { 0.01, 0.01, 0.01, 0.1, 0.01, 0.01, 0.01 };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    pred.push_back((TH1*)f->Get(b));
  }
  TH1* hdata = (TH1*)f->Get(data);
  TGraphAsymmErrors* unc   = (TGraphAsymmErrors*)f->Get("bkgtotal_unc_sr");

  prepHists(pred, false, false, true);
  prepHists({hdata}, false, false, false, {kBlack});
  for (auto *h : pred){
    setBinLabels(h, xlabels);
    h->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  }

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
    auto region = split.at(ireg);
    int xlow = 0, xhigh = 0;
    bool isfirst = true;
    int ibin = 0;
    for (auto &cat_name : srbins){
      auto nbins = catMap.at(cat_name).bin.nbins;
      if (std::regex_search(cat_name.Data(), std::regex(region.Data()))){
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

    PLOT_MAX_YSCALE = plot_ymax_scales.at(ireg);
    LOG_YMIN = plot_log_ymin.at(ireg);

    auto leg = prepLegends({hdata}, datalabel, "LP");
    appendLegends(leg, pred, bkglabels, "F");
    appendLegends(leg, {hDataRawMC}, rawsimlabel, "L");
//  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    auto c = drawStackAndRatio(pred, hdata, leg, true, ratiolabel, RATIO_YMIN, RATIO_YMAX, xlow, xhigh, hsigs, unc, {hDataRawMC}, gPulls);
    c->SetCanvasSize(800, 600);
    drawTLatexNDC(splitlabels.at(ireg), 0.2, 0.76, 0.03);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    basename.ReplaceAll("(", "");
    basename.ReplaceAll(")", "");
    basename.ReplaceAll("|", "_");
    c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
