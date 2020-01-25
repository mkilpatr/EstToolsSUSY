#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_Nano(TString inputFile="/uscms/home/mkilpatr/nobackup/CMSSW_10_2_9/src/Limits/SumOfBkg.root", TString outputName="getFinalPlot/"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.04;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;


  vector<TString> bkgs = {"httz_stack_2", "hdiboson_stack_1", "hqcd_stack_3", "hznunu_stack_4", "httbar_stack_5"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  vector<TString> sigs = {"T2tt_850_50", "T2tt_600_300"};
  TString data = "data";

  vector<TString> bkglabels = {"ttZ", "Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2tt(850,50)", "T2tt(600,300)"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"lm_nb0",
			   "lm_nb1_nivf0_lowmtb_lowptisr",
			   "lm_nb1_otherptisr",
			   "lm_nb2",
			   "hm_nb[0-9]_lowmtb",
			   "hm_nb[0-9]_highmtb_nt0_nrt0_nw0",
			   "hm_nb1_highmtb",
			   "hm_nbeq2_highmtb",
			   "hm_nb3_highmtb"};
  vector<TString> splitlabels = {
      "#splitline{Low #Deltam, N_{b}=0, N_{SV} = 0,#geq1}{}",
      "#splitline{Low #Deltam, N_{b}=1, N_{SV} = 0,}{M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175, 300 #leq p_{T}(ISR) < 500}",
      "#splitline{Low #Deltam, N_{b}=1, N_{SV} = 0,#geq1,}{M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175}",
      "#splitline{Low #Deltam, N_{b}=2}{}",
      "#splitline{N_{b}#geq2, M_{T}(b_{1,2},#slash{E}_{T}) < 175 GeV}{}",
      "#splitline{N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{N_{W} = 0, N_{T} = 0}",
      "#splitline{N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{#geq 5 jets}",
      "#splitline{N_{b}#geq2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{N_{W} = 0, N_{T} = 0}",
      "#splitline{N_{b}#geq2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{#geq 5 jets}"
  };

  vector<double> ratioYmax = {2.999, 2.999, 2.999, 6.999, 2.999, 6.999};

  TLatex tl;
  tl.SetTextSize(0.025);
  tl.SetTextAlign(31);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){ tl.DrawLatexNDC(0.3, 0.66, "2-5 jets"); tl.DrawLatexNDC(0.5, 0.66, "#geq 6 jets"); tl.DrawLatexNDC(0.7, 0.66, "2-5 jets"); tl.DrawLatexNDC(0.9, 0.66, "#geq 6 jets");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.66, "p_{T}(b) < 40"); tl.DrawLatexNDC(0.8, 0.66, "40 < p_{T}(b) < 70");},
    [&tl](){ tl.DrawLatexNDC(0.7, 0.66, "#splitline{p_{T}(ISR) #geq 500,}{p_{T}(b) < 40}"); tl.DrawLatexNDC(0.9, 0.66, "#splitline{p_{T}(ISR) #geq 500,}{40 < p_{T}(b) < 70}");}, 


    [&tl](){ tl.DrawLatexNDC(0.4, 0.66, "5-6 jets"); tl.DrawLatexNDC(0.8, 0.66, "#geq 7 jets");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.64, "5-6 jets"); tl.DrawLatexNDC(0.8, 0.64, "#geq 7 jets");},
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
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(4,  LOG_YMIN, 4,  2000); c->cd(); ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(8,  LOG_YMIN, 8,  2000); c->cd(); ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(12,  LOG_YMIN, 12,  2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, LOG_YMIN, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, LOG_YMIN, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, LOG_YMIN, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, LOG_YMIN, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, LOG_YMIN, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(29, LOG_YMIN, 29, 2000); drawLine(34, LOG_YMIN, 34, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(42, LOG_YMIN, 42, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(51, LOG_YMIN, 51, 2000); drawLine(56, LOG_YMIN, 56, 2000); c->cd(); },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  cout << "Made it here 1" << endl;
  for (auto &b : bkgs){
    //TH1D* hist = convertToHist({(TH1*)f->Get(b)}, "hist", ";Search Region;Events", nullptr);
    pred.push_back((TH1*)f->Get(b));
  cout << "Made it here 2" << endl;
  }
  //TH1* hdata = (TH1*)f->Get(data);
  //TGraphAsymmErrors* unc   = (TGraphAsymmErrors*)f->Get("bkgtotal_unc_sr");
  TGraphAsymmErrors* unc   = nullptr;
  //for (auto &s : sigs){
  //  TH1 *h = (TH1*)f->Get(s);
  //  h->SetLineStyle(kDashed);
  //  hsigs.push_back(h);
  //}

  prepHists(pred, false, false, true, {797, 391, 811, 623, 866});
  cout << "Made it here 3" << endl;
  //prepHists({hdata}, false, false, false, {kBlack});
  //prepHists(hsigs, false, false, false, {kRed, kGreen+3});
  //setBinLabels(hdata, xlabels);
  //hdata->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");

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
	 (TString(region).Contains("otherptisr") && (cat_name.Contains("highptisr_lowptb") || cat_name.Contains("highptisr_medptb") || cat_name.Contains("medptisr"))) ){//lm_nb1_otherptisr
        if (isfirst){
          isfirst = false;
          xlow = ibin;
          xhigh = xlow + nbins;
        }else{
          xhigh += nbins;
        }
	cout << cat_name << ": " << ibin << ", " << xlow << ", " << xhigh << endl;
      }
      ibin += nbins;
    }
    //xhigh--;
    cout << "cat_name" << ": " << ibin << ", " << xlow << ", " << xhigh << endl;


    if (region.Contains("nj5t")) {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 1;}
    else {LOG_YMIN = 0.1; PLOT_MAX_YSCALE = 0.1;}

    //auto leg = prepLegends({hdata}, datalabel, "LP");
    auto leg = prepLegends(pred, bkglabels, "F");
    //appendLegends(leg, hsigs, siglabels, "L");
//    appendLegends(leg, {hDataRawMC}, {"Simulation", "L"});
  //  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    //auto c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, hsigs, unc);
    auto c = drawStackAndRatio(pred, nullptr, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, hsigs, unc);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    drawTLatexNDC(splitlabels.at(ireg), 0.2, 0.76, 0.025);
    drawRegionLabels.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    basename.ReplaceAll("_nj[0-9]", "");
    //c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
