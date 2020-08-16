#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void formatFinalPlots(TString inputFile="/uscms/home/mkilpatr/nobackup/CMSSW_10_2_9/src/Limits/SumOfBkg.root", TString outputName="getFinalPlot/"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;


  vector<TString> bkgs = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  vector<TString> bkgs_name = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  vector<TString> sigs = {"T2tt_1000_0", "T1tttt_2200_400"};
  //vector<TString> sigs = {"T2tt_1000_0"};
  TString data = "hdata";

  vector<TString> bkglabels = {"ttZ", "Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2tt(1000,0)", "T1tttt(2200, 400)"};
  vector<TString> datalabel = {"Observed"};
  vector<double> ratioYmax = {2.999, 2.999, 2.999, 6.999, 2.999, 6.999};

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

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


  TFile *output = new TFile(outputName+"SumOfBkg.root", "RECREATE");
  for (auto *h : pred) h->Write();
  for (auto *s : hsigs) s->Write();
  if(hdata) hdata->Write();
  total->Write();
  output->Close();



}
