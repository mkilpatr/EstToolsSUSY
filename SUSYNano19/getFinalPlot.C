#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <string.h>
#include <functional>

using namespace EstTools;

void getFinalPlot(TString inputFile="getFinalPlot_2016/SumOfBkg.root", TString outputName="getFinalPlot_2016/pred_binnum_"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;
  if(inputFile.Contains("2016")) lumistr = "35.815165";

  vector<TString> bkgs = {"httz_stack_2", "hdiboson_stack_1", "hqcd_stack_3", "hznunu_stack_4", "httbar_stack_5"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  vector<TString> sigs = {"T2tt_1000_0"};
  TString data = "hdata";

  vector<TString> bkglabels = {"ttZ", "Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2tt(1000,0)"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"lm",
			   "hm_nb1_bins",
			   "hm_nbeq2",
			   "hm_nb3"
			   };
  vector<TString> splitlabels = {
      "#splitline{Low #Deltam}{}",
      "#splitline{High #Deltam, N_{b}=1, #geq 2}{}",
      "#splitline{High #Deltam, N_{b}=2}{}",
      "#splitline{High #Deltam, N_{b} #geq 3}{}"
  };

  vector<double> ratioYmax = {2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999};

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

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    TH1D* hist = convertToHist({(TH1*)f->Get(b)}, b, ";Search Region;Events", nullptr);
    pred.push_back(hist);
  }
  TH1* hdata = (TH1*)f->Get(data);
  TGraphAsymmErrors* unc = (TGraphAsymmErrors*)f->Get("bkgtotal_unc_sr");
  for (auto &s : sigs){
    TH1 *h = convertToHist({(TH1*)f->Get(s)}, s, ";Search Region;Events", nullptr);
    h->SetLineStyle(kDashed);
    hsigs.push_back(h);
  }
  TH1* pull;
  if(hdata){
    pull = getPullHist(hdata, unc);
  }

  prepHists(pred, false, false, true, {797, 391, 811, 623, 866});
  if(hdata) prepHists({hdata}, false, false, false, {kBlack});
  if(hdata) prepHists({pull}, false, false, false, {kRed});
  prepHists(hsigs, false, false, false, {kRed});

  // plot raw MC
//  TH1 *hmctotal = nullptr;
//  for(auto &mc : mcs){
//    if (!hmctotal) hmctotal = (TH1*)f->Get(mc)->Clone();
//    else hmctotal->Add((TH1*)f->Get(mc));
//  }

//  TH1* hDataRawMC = (TH1*)hdata->Clone("hDataRawMC");
//  hDataRawMC->Divide(hmctotal);
//  hDataRawMC->SetLineWidth(2);
//  prepHists({hDataRawMC}, false, false, false, {kOrange});

  auto catMap = srCatMap();
  for (unsigned ireg = 0; ireg < split.size(); ++ireg){
    auto &region = split.at(ireg);
    int xlow = 0, xhigh = 0;
    bool isfirst = true;
    int ibin = 0;
    for (auto &cat_name : srbins){
      auto nbins = catMap.at(cat_name).bin.nbins;
      if (cat_name.Contains(TRegexp(region)) || 
	 (TString(region).Contains("hm_nb1_bins") && (cat_name.Contains("hm_nb1") || cat_name.Contains("highmtb_nt0_nrt0_nw0") || cat_name.Contains("lowmtb_nj7_nrtgeq1"))) || //hm_nb1_bins
	 (TString(region).Contains("otherptisr") && (cat_name.Contains("nb1_nivf0_lowmtb_highptisr_lowptb") || cat_name.Contains("nb1_nivf0_lowmtb_highptisr_medptb") || cat_name.Contains("medptisr"))) || //lm_nb1_otherptisr
	 (TString(region).Contains("nb1_highmtb_1tag") && (cat_name.Contains("ntgeq1_nrt0_nw0") || cat_name.Contains("nt0_nrt0_nwgeq1"))) || //hm_nb1_highmtb_1tag  
	 (TString(region).Contains("hm_nb1_highmtb_nrt_2tags") && (cat_name.Contains("hm_nb1_highmtb_nt0_nrtgeq1_nw0") || cat_name.Contains("ntgeq1_nrt0_nwgeq1") || cat_name.Contains("nt0_nrtgeq1_nwgeq1") || cat_name.Contains("ntgeq1_nrtgeq1_nw0"))) || //hm_nb1_highmtb_nrt_2tags
	 (TString(region).Contains("nbeq2_highmtb_1tag") && (cat_name.Contains("nbeq2_highmtb_nt1_nrt0_nw0") || cat_name.Contains("nbeq2_highmtb_nt0_nrt0_nw1"))) || //hm_nb2_highmtb_1tag  
	 (TString(region).Contains("nbeq2_highmtb_2tag") && (cat_name.Contains("nbeq2_highmtb_nt1_nrt0_nw1") || cat_name.Contains("nbeq2_highmtb_nt1_nrt1_nw0") || cat_name.Contains("nbeq2_highmtb_nt0_nrt1_nw1"))) || //hm_nb2_highmtb_2tag
	 (TString(region).Contains("nbeq2_highmtb_taggt2") && (cat_name.Contains("nbeq2_highmtb_nt2_nrt0_nw0") || cat_name.Contains("nbeq2_highmtb_nt0_nrt0_nw2") || cat_name.Contains("nbeq2_highmtb_nt0_nrt2_nw0") || cat_name.Contains("nbeq2_highmtb_nrtntnwgeq3"))) || //hm_nb2_highmtb_taggt2
	 (TString(region).Contains("nb3_highmtb_1tag") && (cat_name.Contains("nb3_highmtb_nt1_nrt0_nw0") || cat_name.Contains("nb3_highmtb_nt0_nrt0_nw1") || cat_name.Contains("nb3_highmtb_nt0_nrt1_nw0"))) || //hm_nb3_highmtb_1tag
	 (TString(region).Contains("nb3_highmtb_taggeq2") && (cat_name.Contains("nb3_highmtb_nt1_nrt0_nw1") || cat_name.Contains("nb3_highmtb_nt1_nrt1_nw0") || cat_name.Contains("nb3_highmtb_nt0_nrt1_nw1") || cat_name.Contains("nb3_highmtb_nt2_nrt0_nw0") || cat_name.Contains("nb3_highmtb_nt0_nrt0_nw2") || cat_name.Contains("nb3_highmtb_nt0_nrt2_nw0") || cat_name.Contains("nb3_highmtb_nrtntnwgeq3"))) //hm_nb3_highmtb_taggeq2
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


    if (region.Contains("nj5t")) {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 1;}
    else {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 0.01;}

    auto leg = prepLegends({hdata}, datalabel, "LP");
    appendLegends(leg, pred, bkglabels, "F");
    appendLegends(leg, hsigs, siglabels, "L");
//    appendLegends(leg, {hDataRawMC}, {"Simulation", "L"});
  //  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    TCanvas* c;
    if(hdata) c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, hsigs, unc);
    else      c = drawStackAndRatio(pred, nullptr, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, hsigs, unc);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    drawTLatexNDC(splitlabels.at(ireg), 0.2, 0.76, 0.025);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    basename.ReplaceAll("nb[0-9]", "");
    c->Print(basename+".png");
    c->Print(basename +".C");
  }

  if(hdata){
    double mean  = pull->GetMean();
    double StdDev = pull->GetStdDev();
    //cout << "Made it here" << endl;
    TString fitString = "#splitline{Mean = " + to_string(mean) + "}{StdDev = " + to_string(StdDev) + "}";
    std::function<void(TCanvas*)> plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC(fitString, 0.2, 0.72); };
    //cout << "Made it here" << endl;
    auto c_pull = drawCompMatt({pull}, 0, -1., &plotextra);
    cout << "Made it here" << endl;
    c_pull->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    TString basename = outputName + "_pull";
    c_pull->Print(basename+".png");
    c_pull->Print(basename +".C");
  }

  TFile *output = new TFile(outputName + "getFinalPlot_Nano.root", "RECREATE");
  for (auto *h : pred) h->Write();
  for (auto *s : hsigs) s->Write();
  if(hdata) pull->Write();
  if(hdata) hdata->Write();
  output->Close();

}
