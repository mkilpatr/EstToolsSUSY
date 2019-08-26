/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>
#include <string>  

//#include "SRParameters_Tau_HM.hh"
//#include "SRParameters_Tau_HM_1.hh"
//#include "SRParameters_Tau_HM_2.hh"
//#include "SRParameters_Tau_HM_3.hh"
#include "SRParameters.hh"
//#include "LowMET_HM_Parameters.hh"

#include "../EstMethods/LLBEstimator.hh"

using namespace EstTools;

void BkgPredHM_LowMET_Tau(){
  auto start = chrono::steady_clock::now();

  vector<std::string> bkgnames  = {"ttbarplusw_pred", "ttbarplusw_pred-iso"};
  vector<TString> bkglabels = {""};
  vector<TString> datalabel = {"Data"};

  auto convert = [&bkgnames](const ToyCombination &c, vector<TH1*> &hists, vector<TGraphAsymmErrors*> &graphs){
    for(const auto &s : bkgnames){
      hists.push_back(convertToHist(c.getPrediction(s), s, ";Search Region;Events"));
      graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(s), s+"_gr", ";Search Region;Events"));
    }
    graphs.push_back(convertToGraphAsymmErrors(c.getPrediction(), "pred_total_gr", ";Search Region;Events"));
  };

  auto sigcfg = sigConfig();
  BaseEstimator s(sigcfg);
  s.calcYields();

  auto hT1tttt = convertToHist(s.yields.at("T1tttt-sr"),"T1tttt_2000_100",";Search Region;Events");
  auto hT2tt_500_325 = convertToHist(s.yields.at("T2tt_500_325-sr"),"T2tt_500_325",";Search Region;Events");
  auto hT2tt_850_100 = convertToHist(s.yields.at("T2tt_850_100-sr"),"T2tt_850_100",";Search Region;Events");
  auto hT1tttt_iso = convertToHist(s.yields.at("T1tttt-sr-iso"),"T1tttt_2000_100-iso",";Search Region;Events");
  auto hT2tt_500_325_iso = convertToHist(s.yields.at("T2tt_500_325-sr-iso"),"T2tt_500_325-iso",";Search Region;Events");
  auto hT2tt_850_100_iso = convertToHist(s.yields.at("T2tt_850_100-sr-iso"),"T2tt_850_100-iso",";Search Region;Events");

  auto plot = [&](TString outputBase) {
    prepHists({hT1tttt, hT2tt_500_325, hT2tt_850_100, hT1tttt_iso, hT2tt_500_325_iso, hT2tt_850_100_iso}, false, false, false, {kRed-7, kMagenta-10, kBlue, kRed-5, kMagenta-8, kAzure-4});

    // plot raw MC - w/o top/W SF
    TH1 *hmcnosf = nullptr;
    vector<TString> mcnosf = {"znunu-raw-sr","ttbar-raw-sr","wjets-raw-sr","tW-raw-sr","ttW-raw-sr","qcd-raw-sr","ttZ-raw-sr","diboson-raw-sr"};
    for (auto &sname : mcnosf){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf) hmcnosf = (TH1*)hmc->Clone();
      else hmcnosf->Add(hmc);
    }
    TH1 *hmcnosf_iso = nullptr;
    vector<TString> mcnosf_iso = {"znunu-raw-sr-iso","ttbar-raw-sr-iso","wjets-raw-sr-iso","tW-raw-sr-iso","ttW-raw-sr-iso","qcd-raw-sr-iso","ttZ-raw-sr-iso","diboson-raw-sr-iso"};
    for (auto &sname : mcnosf_iso){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf_iso) hmcnosf_iso = (TH1*)hmc->Clone();
      else hmcnosf_iso->Add(hmc);
    }

    prepHists({hmcnosf}, false, false, false, {kAzure+6});
    prepHists({hmcnosf_iso}, false, false, false, {kSpring-9});

    TH1* hmcnosf_div = (TH1*)hmcnosf->Clone();
    hmcnosf_div->Divide(hmcnosf_iso);
    hmcnosf_div->SetLineWidth(2);
    prepHists({hmcnosf_div}, false, false, false, {kAzure+6});

    TH1* hT1tttt_div = (TH1*)hT1tttt->Clone();
    hT1tttt_div->Divide(hT1tttt_iso);
    hT1tttt_div->SetLineWidth(2);
    prepHists({hT1tttt_div}, false, false, false, {kRed-7});

    TH1* hT2tt_850_100_div = (TH1*)hT2tt_850_100->Clone();
    hT2tt_850_100_div->Divide(hT2tt_850_100_iso);
    hT2tt_850_100_div->SetLineWidth(2);
    prepHists({hT2tt_850_100_div}, false, false, false, {kBlue});

    TH1* hT2tt_500_325_div = (TH1*)hT2tt_500_325->Clone();
    hT2tt_500_325_div->Divide(hT2tt_500_325_iso);
    hT2tt_500_325_div->SetLineWidth(2);
    prepHists({hT2tt_500_325_div}, false, false, false, {kMagenta-10});

    auto leg = prepLegends({}, bkglabels, "F");
    appendLegends(leg, {hT1tttt}, {"T1tttt(2000, 100) MVA"}, "L");
    appendLegends(leg, {hT1tttt_iso}, {"T1tttt(2000, 100) IsoTrack + TauPOG"}, "L");
    appendLegends(leg, {hT2tt_500_325}, {"T2tt(500, 325) MVA"}, "L");
    appendLegends(leg, {hT2tt_500_325_iso}, {"T2tt(500, 325) IsoTrack + TauPOG"}, "L");
    appendLegends(leg, {hT2tt_850_100}, {"T2tt(850, 100) MVA"}, "L");
    appendLegends(leg, {hT2tt_850_100_iso}, {"T2tt(850, 100) IsoTrack + TauPOG"}, "L");
    appendLegends(leg, {hmcnosf}, {"MC MVA"}, "L");
    appendLegends(leg, {hmcnosf_iso}, {"MC Iso"}, "L");
    leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    auto c = drawCompAndRatio({hT1tttt, hT2tt_500_325, hT2tt_850_100, hT1tttt_iso, hT2tt_500_325_iso, hT2tt_850_100_iso, hmcnosf, hmcnosf_iso}, {hmcnosf_div, hT1tttt_div, hT2tt_500_325_div, hT2tt_850_100_div}, leg, "N_{mva}/N_{iso+taupog}", 0.501, 1.499, false, 0.001);
    c->SetTitle(outputBase);
    c->SetCanvasSize(800, 600);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");
    c->Print(s.config.outputdir+"/" + outputBase +"_canvas.root");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    hmcnosf->Write();
    hmcnosf_iso->Write();
    hmcnosf_div->Write();
    hT1tttt->Write();
    hT2tt_500_325->Write();
    hT2tt_850_100->Write();
    hT1tttt_iso->Write();
    hT2tt_500_325_iso->Write();
    hT2tt_850_100_iso->Write();
    hT1tttt_div->Write();
    hT2tt_500_325_div->Write();
    hT2tt_850_100_div->Write();
    output->Close();
  };

  auto plotSig = [&](TString outputBase) {
    prepHists({hT1tttt, hT2tt_500_325, hT2tt_850_100, hT1tttt_iso, hT2tt_500_325_iso, hT2tt_850_100_iso}, false, false, false, {kRed-7, kMagenta-10, kBlue, kRed-5, kMagenta-8, kAzure-4});

    // plot raw MC - w/o top/W SF
    TH1 *hmcnosf = nullptr;
    vector<TString> mcnosf = {"znunu-raw-sr","ttbar-raw-sr","wjets-raw-sr","tW-raw-sr","ttW-raw-sr","qcd-raw-sr","ttZ-raw-sr","diboson-raw-sr"};
    for (auto &sname : mcnosf){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf) hmcnosf = (TH1*)hmc->Clone();
      else hmcnosf->Add(hmc);
    }
    TH1 *hmcnosf_iso = nullptr;
    vector<TString> mcnosf_iso = {"znunu-raw-sr-iso","ttbar-raw-sr-iso","wjets-raw-sr-iso","tW-raw-sr-iso","ttW-raw-sr-iso","qcd-raw-sr-iso","ttZ-raw-sr-iso","diboson-raw-sr-iso"};
    for (auto &sname : mcnosf_iso){
      auto hmc = convertToHist(s.yields.at(sname), sname, ";Search Region;Events");
      if (!hmcnosf_iso) hmcnosf_iso = (TH1*)hmc->Clone();
      else hmcnosf_iso->Add(hmc);
    }

    prepHists({hmcnosf}, false, false, false, {kAzure+6});
    prepHists({hmcnosf_iso}, false, false, false, {kSpring-9});

    TH1 *hmcnosf_root = (TH1*)hmcnosf->Clone("hmcroot");
    TH1 *hmcnosf_root_iso = (TH1*)hmcnosf_iso->Clone("hmcroot_iso");
    for(unsigned int i = 0; i != hmcnosf_root->GetNbinsX() + 1; i++){
	if(hmcnosf_root->GetBinContent(i) > 0) 		hmcnosf_root->SetBinContent(i, TMath::Sqrt(hmcnosf_root->GetBinContent(i)));
	else						hmcnosf_root->SetBinContent(i, TMath::Sqrt(0.00001));
	if(hmcnosf_root_iso->GetBinContent(i) > 0)  	hmcnosf_root_iso->SetBinContent(i, TMath::Sqrt(hmcnosf_root_iso->GetBinContent(i)));
	else						hmcnosf_root_iso->SetBinContent(i, TMath::Sqrt(0.00001));
    }

    for(unsigned int i = 0; i != hT1tttt->GetNbinsX() + 1; i++){
	if(hT1tttt->GetBinContent(i) <= 0.) hT1tttt->SetBinContent(i, 0.00001);
	if(hT1tttt_iso->GetBinContent(i) <= 0.) hT1tttt_iso->SetBinContent(i, 0.00001);
	if(hT2tt_500_325->GetBinContent(i) <= 0.) hT2tt_500_325->SetBinContent(i, 0.00001);
	if(hT2tt_500_325_iso->GetBinContent(i) <= 0.) hT2tt_500_325_iso->SetBinContent(i, 0.00001);
	if(hT2tt_850_100->GetBinContent(i) <= 0.) hT2tt_850_100->SetBinContent(i, 0.00001);
	if(hT2tt_850_100_iso->GetBinContent(i) <= 0.) hT2tt_850_100_iso->SetBinContent(i, 0.00001);
    }

    TH1* hT1tttt_sig = (TH1*)hT1tttt->Clone();
    hT1tttt_sig->Divide(hmcnosf_root);
    hT1tttt_sig->SetLineWidth(2);
    TH1* hT1tttt_sig_iso = (TH1*)hT1tttt_iso->Clone();
    hT1tttt_sig_iso->Divide(hmcnosf_root_iso);
    hT1tttt_sig_iso->SetLineWidth(2);
    TH1* hT1tttt_sig_div = (TH1*)hT1tttt_sig->Clone();
    hT1tttt_sig_div->Divide(hT1tttt_sig_iso);
    hT1tttt_sig_div->SetLineWidth(2);
    prepHists({hT1tttt_sig_div}, false, false, false, {kRed-7});

    TH1* hT2tt_850_100_sig = (TH1*)hT2tt_850_100->Clone();
    hT2tt_850_100_sig->Divide(hmcnosf_root);
    hT2tt_850_100_sig->SetLineWidth(2);
    TH1* hT2tt_850_100_sig_iso = (TH1*)hT2tt_850_100_iso->Clone();
    hT2tt_850_100_sig_iso->Divide(hmcnosf_root_iso);
    hT2tt_850_100_sig_iso->SetLineWidth(2);
    TH1* hT2tt_850_100_sig_div = (TH1*)hT2tt_850_100_sig->Clone();
    hT2tt_850_100_sig_div->Divide(hT2tt_850_100_sig_iso);
    hT2tt_850_100_sig_div->SetLineWidth(2);
    prepHists({hT2tt_850_100_sig_div}, false, false, false, {kBlue});

    TH1* hT2tt_500_325_sig = (TH1*)hT2tt_500_325->Clone();
    hT2tt_500_325_sig->Divide(hmcnosf_root);
    hT2tt_500_325_sig->SetLineWidth(2);
    TH1* hT2tt_500_325_sig_iso = (TH1*)hT2tt_500_325_iso->Clone();
    hT2tt_500_325_sig_iso->Divide(hmcnosf_root_iso);
    hT2tt_500_325_sig_iso->SetLineWidth(2);
    TH1* hT2tt_500_325_sig_div = (TH1*)hT2tt_500_325_sig->Clone();
    hT2tt_500_325_sig_div->Divide(hT2tt_500_325_sig_iso);
    hT2tt_500_325_sig_div->SetLineWidth(2);
    prepHists({hT2tt_500_325_sig_div}, false, false, false, {kMagenta-10});

    auto leg = prepLegends({}, bkglabels, "F");
    appendLegends(leg, {hT1tttt_sig}, {"T1tttt(2000, 100) MVA"}, "L");
    appendLegends(leg, {hT1tttt_sig_iso}, {"T1tttt(2000, 100) IsoTrack + TauPOG"}, "L");
    appendLegends(leg, {hT2tt_500_325_sig}, {"T2tt(500, 325) MVA"}, "L");
    appendLegends(leg, {hT2tt_500_325_sig_iso}, {"T2tt(500, 325) IsoTrack + TauPOG"}, "L");
    appendLegends(leg, {hT2tt_850_100_sig}, {"T2tt(850, 100) MVA"}, "L");
    appendLegends(leg, {hT2tt_850_100_sig_iso}, {"T2tt(850, 100) IsoTrack + TauPOG"}, "L");
    leg->SetTextSize(0.03);
//    leg->SetNColumns(2);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    auto c = drawCompAndRatio({hT1tttt_sig, hT2tt_500_325_sig, hT2tt_850_100_sig, hT1tttt_sig_iso, hT2tt_500_325_sig_iso, hT2tt_850_100_sig_iso}, {hT1tttt_sig_div, hT2tt_500_325_sig_div, hT2tt_850_100_sig_div}, leg, "(S/#sqrt{B})_{mva}/(S/#sqrt{B}_{iso+taupog}", 0.501, 1.499, false, 0.001);
    c->SetTitle(outputBase);
    c->SetCanvasSize(800, 600);
    c->Print(s.config.outputdir+"/" + outputBase +".pdf");
    c->Print(s.config.outputdir+"/" + outputBase +".C");
    c->Print(s.config.outputdir+"/" + outputBase +"_canvas.root");

    TFile *output = new TFile(s.config.outputdir+"/" + outputBase +".root", "RECREATE");
    hmcnosf->Write();
    hmcnosf_iso->Write();
    hT1tttt->Write();
    hT2tt_500_325->Write();
    hT2tt_850_100->Write();
    hT1tttt_iso->Write();
    hT2tt_500_325_iso->Write();
    hT2tt_850_100_iso->Write();
    hT1tttt_sig->Write();
    hT2tt_500_325_sig->Write();
    hT2tt_850_100_sig->Write();
    output->Close();

    TCanvas* SigSumCanvas = new TCanvas(outputBase+"_sum", "Significances", 200, 10, 700, 500);
    TH1F* hT1ttttSum       = new TH1F("hSum_0", "Significances", 41, -0.025, 2.025);
    TH1F* hT2tt_850_100Sum = new TH1F("hSum_1", "Significances", 41, -0.025, 2.025);
    TH1F* hT2tt_500_325Sum = new TH1F("hSum_2", "Significances", 41, -0.025, 2.025);
    for(unsigned int i = 0; i != hT1tttt_sig_div->GetNbinsX() + 1; i++){
      hT1ttttSum->Fill(hT1tttt_sig_div->GetBinContent(i));
      hT2tt_850_100Sum->Fill(hT2tt_850_100_sig_div->GetBinContent(i));
      hT2tt_500_325Sum->Fill(hT2tt_500_325_sig_div->GetBinContent(i));
    }  
    SigSumCanvas->cd();
    hT1ttttSum->SetLineWidth(2);
    hT1ttttSum->SetLineColor(kRed-7);
    hT2tt_850_100Sum->SetLineWidth(2);
    hT2tt_850_100Sum->SetLineColor(kBlue);
    hT2tt_500_325Sum->SetLineWidth(2);
    hT2tt_500_325Sum->SetLineColor(kMagenta-10);

    hT1ttttSum->GetYaxis()->SetTitleFont(62);
    hT1ttttSum->GetYaxis()->CenterTitle(kTRUE);
    hT1ttttSum->GetXaxis()->SetTitleFont(62);
    hT1ttttSum->GetYaxis()->SetNdivisions(305);
    hT1ttttSum->GetYaxis()->SetTitle("Search Regions");
    hT1ttttSum->GetXaxis()->SetTitle("(S/#sqrt{B})_{mva}/(S/#sqrt{B}_{iso+taupog}");

    float T1tttMean = hT1ttttSum->GetMean();
    float T2tt850Mean = hT2tt_850_100Sum->GetMean();
    float T2tt500Mean = hT2tt_500_325Sum->GetMean();

    hT1ttttSum->Draw();
    hT2tt_850_100Sum->Draw("same");
    hT2tt_500_325Sum->Draw("same");
    auto legend = new TLegend(0.75,0.60,0.95,0.90);
    legend->AddEntry(hT1ttttSum, "T1tttt(2000, 100)", "l");
    legend->AddEntry(hT2tt_850_100Sum, "T2tt(850, 100)", "l");
    legend->AddEntry(hT2tt_500_325Sum, "T2tt(500, 325)", "l");
    legend->Draw();

    cout << "T1tttt(2000, 100) Mean: " << T1tttMean << endl;
    cout << "T2tt(850, 100) Mean: " << T2tt850Mean << endl;
    cout << "T2tt(500, 325) Mean: " << T2tt500Mean << endl;

    SigSumCanvas->Print(s.config.outputdir+"/" + outputBase +"_sum.pdf");
    SigSumCanvas->Print(s.config.outputdir+"/" + outputBase +"_sum.C");
    SigSumCanvas->Print(s.config.outputdir+"/" + outputBase +"_sum_canvas.root");
 
  };

  //plot("std_pred_trad_allHM");
  //plotSig("std_pred_trad_sig_allHM");
  plot("std_pred_trad_allHM_4");
  plotSig("std_pred_trad_sig_allHM_4");


  cout << "\n\n Traditional \n";
  //for (const auto &b : lc.bkgs){
  //  s.printVec(lc.getPrediction(b.first),b.first);
  //}
  //s.printVec(lc.getPrediction(),"total_bkg");
  cout << "\n Summary Traditional \n";
  //s.printSummary({s.yields.at("_pred"), l.yields.at("ttZ-sr"), l.yields.at("diboson-sr")}, s.yields.at("data-sr"));


  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double> (diff).count() << " s" << endl;

}
