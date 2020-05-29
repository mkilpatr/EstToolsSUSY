#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <string.h>
#include <functional>

using namespace EstTools;

void getFinalPlot_compare(TString inputFile="/eos/uscms/store/user/lpcsusyhad/Stop_production/LimitInputs/19May2020_Run2Unblind_dev_v6/SearchBinsPlot/", TString outputName="getFinalPlot_compare/pred_binnum_"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;
  if(inputFile.Contains("2016")) lumistr = "35.815165";

  vector<TString> bkgs_matt_up = {"qcd_syst_up", "znunu_syst_up", "TTZ_syst_up", "Rare_syst_up", "ttbarplusw_syst_up"};
  vector<TString> bkgs_matt_dn = {"qcd_syst_dn", "znunu_syst_dn", "TTZ_syst_dn", "Rare_syst_dn", "ttbarplusw_syst_dn"};
  vector<TString> bkglabels = {"QCD Matt", "Z#rightarrow#nu#nu Matt", "ttZ Matt", "Rare Matt", "t#bar{t}/W"};
  vector<TString> bkglabels_other = {"QCD Jon", "Z#rightarrow#nu#nu Caleb", "ttZ Anna", "Rare Anna"};

  vector<TH1*> pred_unc_up, pred_unc_dn;
  vector<TH1*> pred_other_up, pred_other_dn;

  TFile *q = TFile::Open(inputFile + "SearchBins_QCDResidMET.root");
  assert(q);
  TFile *z = TFile::Open(inputFile + "searchBinsZinv_combined_Run2.root");
  assert(z);
  TFile *ttz = TFile::Open(inputFile + "TTZ_final_sb.root");
  assert(ttz);
  TFile *r = TFile::Open(inputFile + "Rare_final_sb.root");
  assert(r);
  TFile *f = TFile::Open("getFinalPlot/SumOfBkg.root");
  assert(f);

  //get all of the uncertainties
  for (auto &b : bkgs_matt_up){
    pred_unc_up.push_back(convertToHist({(TH1*)f->Get(b)}, b + "_", ";Search Region;Events", nullptr));
  }
  for (auto &b : bkgs_matt_dn){
    pred_unc_dn.push_back(convertToHist({(TH1*)f->Get(b)}, b + "_", ";Search Region;Events", nullptr));
  }

  pred_other_up.push_back(convertToHist({(TH1*)  q->Get("Tot_Up")    }, "Tot_Up_qcd",     ";Search Region;Events", nullptr, true));
  pred_other_up.push_back(convertToHist({(TH1*)  z->Get("Total_Up")  }, "Total_Up_z",   ";Search Region;Events", nullptr, true));
  pred_other_up.push_back(convertToHist({(TH1*)ttz->Get("Total_Up")  }, "Total_Up_ttz",   ";Search Region;Events", nullptr, true));
  pred_other_up.push_back(convertToHist({(TH1*)  r->Get("Total_Up")  }, "Total_Up_rare",   ";Search Region;Events", nullptr, true));
  pred_other_dn.push_back(convertToHist({(TH1*)  q->Get("Tot_Down")  }, "Tot_Down_qcd",   ";Search Region;Events", nullptr, true));
  pred_other_dn.push_back(convertToHist({(TH1*)  z->Get("Total_Down")}, "Total_Down_z", ";Search Region;Events", nullptr, true));
  pred_other_dn.push_back(convertToHist({(TH1*)ttz->Get("Total_Down")}, "Total_Down_ttz", ";Search Region;Events", nullptr, true));
  pred_other_dn.push_back(convertToHist({(TH1*)  r->Get("Total_Down")}, "Total_Down_rare", ";Search Region;Events", nullptr, true));

  prepHists(pred_unc_up, false, false, false, {kRed, kRed, kRed, kRed, kRed});
  prepHists(pred_unc_dn, false, false, false, {kRed, kRed, kRed, kRed, kBlue});
  prepHists(pred_other_up, false, false, false, {kBlue, kBlue, kBlue, kBlue});
  prepHists(pred_other_dn, false, false, false, {kBlue, kBlue, kBlue, kBlue});
 
  vector<TH1*> ratio_up, ratio_dn;
  for (unsigned bkg = 0; bkg != pred_unc_up.size(); bkg++){
    if (bkgs_matt_up[bkg].Contains("ttbarplusw")){
      TH1* hr_up = (TH1*)pred_unc_up[bkg]->Clone(bkgs_matt_up[bkg] + "_ratio_up");
      hr_up->Divide(pred_unc_dn[bkg]);
      hr_up->SetLineWidth(2);
      cout << "made it here" << endl;
      ratio_up.push_back(hr_up);
    } else {
      TH1* hr_up = (TH1*)pred_unc_up[bkg]->Clone(bkgs_matt_up[bkg] + "_ratio_up");
      hr_up->Divide(pred_other_up[bkg]);
      hr_up->SetLineWidth(2);
      ratio_up.push_back(hr_up);
      TH1* hr_dn = (TH1*)pred_unc_dn[bkg]->Clone(bkgs_matt_up[bkg] + "_ratio_dn");
      hr_dn->Divide(pred_other_dn[bkg]);
      hr_dn->SetLineWidth(2);
      ratio_dn.push_back(hr_dn);
    }
  }
  prepHists(ratio_up, false, false, false, {kRed, kRed, kRed, kRed});
  prepHists(ratio_dn, false, false, false, {kRed, kRed, kRed, kRed});
 
  for (unsigned bkg = 0; bkg != pred_unc_up.size(); bkg++){
    auto leg = prepLegends({}, {""}, "L");
    if (bkgs_matt_up[bkg].Contains("ttbarplusw")){
      appendLegends(leg, {pred_unc_up[bkg]}, {bkglabels[bkg] + " Up"}, "L");
      appendLegends(leg, {pred_unc_dn[bkg]}, {bkglabels[bkg] + " Down"}, "L");
    } else{
      appendLegends(leg, {pred_unc_up[bkg]}, {bkglabels[bkg]}, "L");
      appendLegends(leg, {pred_other_up[bkg]}, {bkglabels_other[bkg]}, "L");
    }
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    TCanvas* c;
    if(bkgs_matt_up[bkg].Contains("nu"))
      c = drawCompAndRatio({pred_unc_up[bkg], pred_other_up[bkg], pred_unc_dn[bkg], pred_other_dn[bkg]}, {ratio_up[bkg], ratio_dn[bkg]}, leg, "N_{syst}^{Matt}/N_{syst}^{other}", 0.749, 1.249, false, -1., 5., true);
    else if(bkgs_matt_up[bkg].Contains("ttbarplusw"))
      c = drawCompAndRatio({pred_unc_up[bkg], pred_unc_dn[bkg]}, {ratio_up[bkg]}, leg, "N_{Up}/N_{Down}", 0.749, 1.249, false, -1., 2., false);
    else
      c = drawCompAndRatio({pred_unc_up[bkg], pred_other_up[bkg], pred_unc_dn[bkg], pred_other_dn[bkg]}, {ratio_up[bkg], ratio_dn[bkg]}, leg, "N_{syst}^{Matt}/N_{syst}^{other}", 0.749, 1.249, false, -1., -1., false);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    TString basename = outputName + "_" + bkgs_matt_up[bkg];
    c->Print(basename+".png");
  }
}
