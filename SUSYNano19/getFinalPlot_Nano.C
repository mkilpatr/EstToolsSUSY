#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void getFinalPlot_Nano(TString inputFile="/uscms/home/mkilpatr/nobackup/CMSSW_10_2_9/src/Limits/SumOfBkg.root", TString outputName="getFinalPlot/pred"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
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
			   "hm_nb1_highmtb_1tag",
			   "hm_nb1_highmtb_2tag",
			   "hm_nbeq2_highmtb_1tag",
			   "hm_nbeq2_highmtb_2tag",
			   "hm_nbeq2_highmtb_taggt2",
			   "hm_nb3_highmtb_1tag",
			   "hm_nb3_highmtb_taggeq2"};
  vector<TString> splitlabels = {
      "#splitline{Low #Deltam, N_{b}=0, N_{SV} = 0,#geq1}{}",
      "#splitline{Low #Deltam, N_{b}=1, N_{SV} = 0}{M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175, 300 #leq p_{T}(ISR) < 500}",
      "#splitline{Low #Deltam, N_{b}=1, N_{SV} = 0,#geq1}{M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175}",
      "#splitline{Low #Deltam, N_{b}=2, M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175}{300 #leq p_{T}(ISR) < 500, #geq 500}",
      "#splitline{High #Deltam, M_{T}(b_{1,2},#slash{E}_{T}) < 175 GeV}{N_{j} #geq 7, N_{res} #geq 1}",
      "#splitline{High #Deltam, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{H_{T} #geq 1000, N_{W} = 0, N_{T} = 0, N_{res} = 0}",
      "#splitline{High #Deltam, N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}",
      "#splitline{High #Deltam, N_{b}=1, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}",
      "#splitline{High #Deltam, N_{b}=2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}",
      "#splitline{High #Deltam, N_{b}=2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}",
      "#splitline{High #Deltam, N_{b}=2, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}",
      "#splitline{High #Deltam, N_{b}#geq3, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}",
      "#splitline{High #Deltam, N_{b}#geq3, M_{T}(b_{1,2},#slash{E}_{T}) > 175 GeV}{}"
  };

  vector<double> ratioYmax = {2.999, 2.999, 2.999, 6.999, 2.999, 6.999};

  TLatex tl;
  tl.SetTextSize(0.025);
  tl.SetTextAlign(31);
  vector<std::function<void()>> drawRegionLabels {
    [&tl](){ tl.DrawLatexNDC(0.3, 0.70, "2-5 jets"); tl.DrawLatexNDC(0.5, 0.70, "#geq 6 jets"); tl.DrawLatexNDC(0.7, 0.70, "2-5 jets"); tl.DrawLatexNDC(0.9, 0.70, "#geq 6 jets");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.66, "p_{T}(b) < 40"); tl.DrawLatexNDC(0.8, 0.66, "40 < p_{T}(b) < 70");},
    [&tl](){ tl.DrawLatexNDC(0.35, 0.66, "#splitline{p_{T}(ISR) #geq 500}{p_{T}(b) < 40}"); tl.DrawLatexNDC(0.65, 0.66, "#splitline{p_{T}(ISR) #geq 500}{40 < p_{T}(b) < 70}"); tl.DrawLatexNDC(0.9, 0.66, "#splitline{p_{T}(ISR) #geq 300}{p_{T}(b) < 40}");}, 
    [&tl](){ tl.DrawLatexNDC(0.27, 0.66, "#splitline{p_{T}(b_{12}) < 80}{}"); tl.DrawLatexNDC(0.43, 0.66, "#splitline{80 < p_{T}(b_{12}) < 140}{}"); tl.DrawLatexNDC(0.55, 0.66, "#splitline{p_{T}(b_{12}) #geq 140}{N_{j} #geq 7}"); tl.DrawLatexNDC(0.67, 0.66, "#splitline{p_{T}(b_{12}) < 80}{}"); tl.DrawLatexNDC(0.83, 0.66, "#splitline{80 < p_{T}(b_{12}) < 140}{}"); tl.DrawLatexNDC(0.95, 0.66, "#splitline{p_{T}(b_{12}) #geq 140}{N_{j} #geq 7}");}, 

    [&tl](){ tl.DrawLatexNDC(0.4, 0.66, "N_{b}=1"); tl.DrawLatexNDC(0.8, 0.66, "N_{b} #geq 2");},
    [&tl](){ tl.DrawLatexNDC(0.4, 0.66, "N_{b}=1"); tl.DrawLatexNDC(0.8, 0.66, "N_{b} #geq 2");},
    [&tl](){ tl.DrawLatexNDC(0.35, 0.73, "#splitline{N_{T} #geq 1}{#splitline{H_{T} #leq 1000}{#splitline{1000 < H_{T} #leq 1500}{H_{T} > 1500}}}"); 
	     tl.DrawLatexNDC(0.53, 0.73, "#splitline{N_{W} #geq 1}{#splitline{H_{T} #leq 1300}{H_{T} > 1300}}"); 
	     tl.DrawLatexNDC(0.8, 0.73, "#splitline{N_{res} #geq 1}{#splitline{H_{T} #leq 1000}{#splitline{1000 < H_{T} #leq 1500}{H_{T} > 1500}}}");},
    [&tl](){ tl.DrawLatexNDC(0.3, 0.66, "#splitline{N_{T} #geq 1}{N_{W} #geq 1}"); 
	     tl.DrawLatexNDC(0.57, 0.66, "#splitline{N_{T} #geq 1}{N_{res} #geq 1}"); 
	     tl.DrawLatexNDC(0.8, 0.66, "#splitline{N_{res} #geq 1}{N_{W} #geq 1}");},
    [&tl](){ tl.DrawLatexNDC(0.35, 0.73, "#splitline{N_{T} = 1}{#splitline{H_{T} #leq 1000}{#splitline{1000 < H_{T} #leq 1500}{H_{T} > 1500}}}"); 
	     tl.DrawLatexNDC(0.53, 0.73, "#splitline{N_{W} = 1}{#splitline{H_{T} #leq 1300}{H_{T} > 1300}}"); 
	     tl.DrawLatexNDC(0.8, 0.73, "#splitline{N_{res} = 1}{#splitline{H_{T} #leq 1000}{#splitline{1000 < H_{T} #leq 1500}{H_{T} > 1500}}}");},
    [&tl](){ tl.DrawLatexNDC(0.27, 0.66, "#splitline{N_{T} = 1}{N_{W} = 1}"); 
	     tl.DrawLatexNDC(0.67, 0.66, "#splitline{N_{T} = 1, N_{res} = 1}{H_{T} #leq 1300, H_{T} > 1300}"); 
	     tl.DrawLatexNDC(0.9, 0.66, "#splitline{N_{res} = 1}{N_{W} = 1}");},
    [&tl](){ tl.DrawLatexNDC(0.3, 0.66, "#splitline{N_{T} = 2}{}"); 
	     tl.DrawLatexNDC(0.43, 0.66, "#splitline{N_{W} = 2}{}"); 
	     tl.DrawLatexNDC(0.77, 0.66, "#splitline{N_{res} = 2}{H_{T} #leq 1300, H_{T} > 1300}");
	     tl.DrawLatexNDC(0.93, 0.66, "#splitline{N_{T}+N_{W}+N_{res} #geq 3}{}");},
    [&tl](){ tl.DrawLatexNDC(0.45, 0.66, "#splitline{N_{T} = 1, H_{T} #leq 1000}{1000 < H_{T} #leq 1500, H_{T} > 1500}");
             tl.DrawLatexNDC(0.57, 0.66, "N_{W} = 1");
             tl.DrawLatexNDC(0.90, 0.66, "#splitline{N_{res} = 1, H_{T} #leq 1000}{1000 < H_{T} #leq 1500, H_{T} > 1500}");},
    [&tl](){ tl.DrawLatexNDC(0.23, 0.66, "#splitline{N_{T} = 1}{N_{W} = 1}");
             tl.DrawLatexNDC(0.37, 0.66, "#splitline{N_{T} = 1}{N_{res} = 1}");
             tl.DrawLatexNDC(0.5, 0.66, "#splitline{N_{res} = 1}{N_{W} = 1}");
             tl.DrawLatexNDC(0.57, 0.66, "#splitline{N_{T} = 2}{}");
             tl.DrawLatexNDC(0.67, 0.66, "#splitline{N_{W} = 2}{}");
             tl.DrawLatexNDC(0.8, 0.66, "#splitline{N_{res} = 2}{}");
             tl.DrawLatexNDC(0.93, 0.66, "#splitline{N_{T}+N_{W}+N_{res} #geq 3}{}");},
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(4,  LOG_YMIN, 4,  2000); drawLine(8,  LOG_YMIN, 8,  2000); drawLine(12,  LOG_YMIN, 12,  2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(20, LOG_YMIN, 20, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(28, LOG_YMIN, 28, 2000); drawLine(32, LOG_YMIN, 32, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(38, LOG_YMIN, 38, 2000); drawLine(41, LOG_YMIN, 41, 2000); drawLine(44, LOG_YMIN, 44, 2000); drawLine(47, LOG_YMIN, 47, 2000); drawLine(50, LOG_YMIN, 50, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(57, LOG_YMIN, 57, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(65, LOG_YMIN, 65, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(72, LOG_YMIN, 72, 2000); drawLine(75, LOG_YMIN, 75, 2000); drawLine(78, LOG_YMIN, 78, 2000); drawLine(81, LOG_YMIN, 81, 2000); drawLine(84, LOG_YMIN, 84, 2000); drawLine(89, LOG_YMIN, 89, 2000); c->cd(); drawLine(94, LOG_YMIN, 94, 2000); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(101, LOG_YMIN, 101, 2000); drawLine(103, LOG_YMIN, 103, 2000);c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(108, LOG_YMIN, 108, 2000); drawLine(111, LOG_YMIN, 111, 2000); drawLine(114, LOG_YMIN, 114, 2000); drawLine(117, LOG_YMIN, 117, 2000); drawLine(120, LOG_YMIN, 120, 2000); drawLine(125, LOG_YMIN, 125, 2000); drawLine(130, LOG_YMIN, 130, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(137, LOG_YMIN, 137, 2000); drawLine(140, LOG_YMIN, 140, 2000); drawLine(143, LOG_YMIN, 143, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(147, LOG_YMIN, 147, 2000); drawLine(148, LOG_YMIN, 148, 2000); drawLine(150, LOG_YMIN, 150, 2000); drawLine(152, LOG_YMIN, 152, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(156, LOG_YMIN, 156, 2000); drawLine(159, LOG_YMIN, 159, 2000); drawLine(162, LOG_YMIN, 162, 2000); drawLine(165, LOG_YMIN, 165, 2000); drawLine(168, LOG_YMIN, 168, 2000); drawLine(171, LOG_YMIN, 171, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(175, LOG_YMIN, 175, 2000); drawLine(177, LOG_YMIN, 177, 2000); drawLine(178, LOG_YMIN, 178, 2000); drawLine(179, LOG_YMIN, 179, 2000); drawLine(180, LOG_YMIN, 180, 2000); drawLine(182, LOG_YMIN, 182, 2000); c->cd(); },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    TH1D* hist = convertToHist({(TH1*)f->Get(b)}, "hist", ";Search Region;Events", nullptr);
    pred.push_back(hist);
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
	 (TString(region).Contains("otherptisr") && (cat_name.Contains("nb1_nivf0_lowmtb_highptisr_lowptb") || cat_name.Contains("nb1_nivf0_lowmtb_highptisr_medptb") || cat_name.Contains("medptisr"))) || //lm_nb1_otherptisr
	 (TString(region).Contains("nb1_highmtb_1tag") && (cat_name.Contains("ntgeq1_nrt0_nw0") || cat_name.Contains("nt0_nrt0_nwgeq1") || cat_name.Contains("nt0_nrtgeq1_nw0"))) || //hm_nb1_highmtb_1tag  
	 (TString(region).Contains("nb1_highmtb_2tag") && (cat_name.Contains("ntgeq1_nrt0_nwgeq1") || cat_name.Contains("nt0_nrtgeq1_nwgeq1") || cat_name.Contains("ntgeq1_nrtgeq1_nw0"))) || //hm_nb1_highmtb_2tag  
	 (TString(region).Contains("nbeq2_highmtb_1tag") && (cat_name.Contains("nbeq2_highmtb_nt1_nrt0_nw0") || cat_name.Contains("nbeq2_highmtb_nt0_nrt0_nw1") || cat_name.Contains("nbeq2_highmtb_nt0_nrt1_nw0"))) || //hm_nb2_highmtb_1tag  
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
    basename.ReplaceAll("nb[0-9]", "");
    //c->SetTitle(basename);
    c->Print(basename+".pdf");
    c->Print(basename +".C");


  }




}
