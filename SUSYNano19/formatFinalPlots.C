#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void formatFinalPlots(TString inputFile="$CMSSW_BASE/src/Limits/SumOfBkg.root", TString outputName="getFinalPlot"){

  gSystem->mkdir(outputName, true);

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;


  vector<TString> bkgs = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  vector<TString> bkgs_name = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  vector<TString> sigs = {"T2tt_1000_100", "T1tttt_2000_400", "T2fbd_500_460", "T2cc_500_460"};
  TString data = "hdata";

  vector<TString> bkglabels = {"ttZ", "Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2tt(1000,100)", "T1tttt(2000, 400)", "T2ttC(500, 460)", "T2cc(500, 460)"};
  vector<TString> datalabel = {"Observed"};
  vector<double> ratioYmax = {2.999, 2.999, 2.999, 6.999, 2.999, 6.999};

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (unsigned b = 0; b != bkgs.size(); b++){
    TH1D* hist = convertToHist({(TH1*)f->Get(bkgs[b])}, bkgs_name[b], ";Search Region;Events", nullptr);
    pred.push_back(hist);
  }
  TH1D* total = convertToHist({(TH1*)f->Get("hpred")}, "hpred", ";Search Region;Events", nullptr);
  TH1* hdata = (TH1*)f->Get(data);
  for (auto &s : sigs){
    TH1 *h = convertToHist({(TH1*)f->Get(s)}, s, ";Search Region;Events", nullptr);
    h->SetLineStyle(kDashed);
    hsigs.push_back(h);
  }

  prepHists(pred, false, false, true, {797, 391, 811, 623, 866});
  prepHists({total}, false, false, true, {kRed});
  if(hdata) prepHists({hdata}, false, false, false, {kBlack});
  prepHists(hsigs, false, false, false, {kRed});
  //hdata->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");


  TFile *output = new TFile(outputName+"/SumOfBkg.root", "RECREATE");
  for (auto *h : pred) h->Write();
  for (auto *s : hsigs) s->Write();
  if(hdata) hdata->Write();
  total->Write();
  output->Close();



}
