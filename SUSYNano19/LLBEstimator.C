/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPred(){

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  //l.pred2016();
  l.pred();

  l.printYields();

  std::map<TString,int> digits;
  digits["singlelep"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap"] = -5;
  digits["_TF_SR_extrap"] = -5;
  digits["_pred"] = -5;

  l.printYieldsTableLatex({"singlelep", "ttbarplusw", "ttbarplusw-sr", "_TF", "_pred"}, labelMap, "LLB/yields_llb_all_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep", "ttbarplusw", "ttbarplusw-sr", "ttbarplusw-sr-int", "_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "LLB/yields_llb_all_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep", "ttbarplusw", "ttbarplusw-sr", "_TF", "_pred"}, labelMap, "LLB/yields_llb_all_hm.tex", "hm", digits);
  }

  return l.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPredSeparate(){

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  l.predSeparate();

  l.printYields();

  std::map<TString,int> digits;
  digits["singlelep"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap"] = -3;
  digits["_TF_SR_extrap"] = -3;
  digits["singlelep-2016"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2016"] = -3;
  digits["_TF_SR_extrap-2016"] = -3;
  digits["singlelep-2017RunBtoE"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2017RunBtoE"] = -3;
  digits["_TF_SR_extrap-2017RunBtoE"] = -3;
  digits["singlelep-2017RunF"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2017RunF"] = -3;
  digits["_TF_SR_extrap-2017RunF"] = -3;
  digits["singlelep-2018preHEM"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2018preHEM"] = -3;
  digits["_TF_SR_extrap-2018preHEM"] = -3;
  digits["singlelep-2018postHEM"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2018postHEM"] = -3;
  digits["_TF_SR_extrap-2018postHEM"] = -3;

  l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "LLB/yields_llb_all_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep", "_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "LLB/yields_llb_all_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep", "_TF", "_pred"}, labelMap, "LLB/yields_llb_all_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2016", "_TF-2016", "_pred-2016"}, labelMap, "LLB/yields_llb_2016_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2016", "_TF-2016", "_TF_CR_to_SR_noextrap-2016", "_TF_SR_extrap-2016", "_pred-2016"}, labelMap, "LLB/yields_llb_2016_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2016", "_TF-2016", "_pred-2016"}, labelMap, "LLB/yields_llb_2016_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2017RunBtoE", "_TF-2017RunBtoE", "_pred-2017RunBtoE"}, labelMap, "LLB/yields_llb_2017RunBtoE_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2017RunBtoE", "_TF-2017RunBtoE", "_TF_CR_to_SR_noextrap-2017RunBtoE", "_TF_SR_extrap-2017RunBtoE", "_pred-2017RunBtoE"}, labelMap, "LLB/yields_llb_2017RunBtoE_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2017RunBtoE", "_TF-2017RunBtoE", "_pred-2017RunBtoE"}, labelMap, "LLB/yields_llb_2017RunBtoE_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2017RunF", "_TF-2017RunF", "_pred-2017RunF"}, labelMap, "LLB/yields_llb_2017RunF_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2017RunF", "_TF-2017RunF", "_TF_CR_to_SR_noextrap-2017RunF", "_TF_SR_extrap-2017RunF", "_pred-2017RunF"}, labelMap, "LLB/yields_llb_2017RunF_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2017RunF", "_TF-2017RunF", "_pred-2017RunF"}, labelMap, "LLB/yields_llb_2017RunF_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2018preHEM", "_TF-2018preHEM", "_pred-2018preHEM"}, labelMap, "LLB/yields_llb_2018preHEM_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2018preHEM", "_TF-2018preHEM", "_TF_CR_to_SR_noextrap-2018preHEM", "_TF_SR_extrap-2018preHEM", "_pred-2018preHEM"}, labelMap, "LLB/yields_llb_2018preHEM_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2018preHEM", "_TF-2018preHEM", "_pred-2018preHEM"}, labelMap, "LLB/yields_llb_2018preHEM_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2018postHEM", "_TF-2018postHEM", "_pred-2018postHEM"}, labelMap, "LLB/yields_llb_2018postHEM_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2018postHEM", "_TF-2018postHEM", "_TF_CR_to_SR_noextrap-2018postHEM", "_TF_SR_extrap-2018postHEM", "_pred-2018postHEM"}, labelMap, "LLB/yields_llb_2018postHEM_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2018postHEM", "_TF-2018postHEM", "_pred-2018postHEM"}, labelMap, "LLB/yields_llb_2018postHEM_hm.tex", "hm", digits);
  }

  vector<TString> tf = {"_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap"};
  vector<TString> sep = {"", "_LM", "_HM_1", "_HM_2"};

  int start = 0, manualBins = 0;
  for(int j = 0; j <= 3; j++){
    if(j == 1){ 
      start = 0;
      manualBins = 53;
    } else if(j == 2){
      start = 53;
      manualBins = 65;
    } else if(j == 3){
      start = 117;
      manualBins = 65;
    }
    for(int i = 0; i != tf.size(); i++){
      auto hAll = convertToHist(l.yields.at(tf[i]),"TF All" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2016 = convertToHist(l.yields.at(tf[i]+"-2016"),"TF 2016" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2017RunBtoE = convertToHist(l.yields.at(tf[i]+"-2017RunBtoE"),"TF 2017RunBtoE" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2017RunF = convertToHist(l.yields.at(tf[i]+"-2017RunF"),"TF 2017RunF" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2018preHEM = convertToHist(l.yields.at(tf[i]+"-2018preHEM"),"TF 2018preHEM" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2018postHEM = convertToHist(l.yields.at(tf[i]+"-2018postHEM"),"TF 2018postHEM" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);

      prepHists({hAll, h2016, h2017RunBtoE, h2017RunF, h2018preHEM, h2018postHEM}, false, false, false, {kBlack, kRed, kBlue, kGreen, kAzure, kMagenta});

      TH1* h2016_div = (TH1*)h2016->Clone();
      h2016_div->Divide(hAll);
      h2016_div->SetLineWidth(2);
      prepHists({h2016_div}, false, false, false, {kRed});

      TH1* h2017RunBtoE_div = (TH1*)h2017RunBtoE->Clone();
      h2017RunBtoE_div->Divide(hAll);
      h2017RunBtoE_div->SetLineWidth(2);
      prepHists({h2017RunBtoE_div}, false, false, false, {kBlue});

      TH1* h2017RunF_div = (TH1*)h2017RunF->Clone();
      h2017RunF_div->Divide(hAll);
      h2017RunF_div->SetLineWidth(2);
      prepHists({h2017RunF_div}, false, false, false, {kGreen});

      TH1* h2018preHEM_div = (TH1*)h2018preHEM->Clone();
      h2018preHEM_div->Divide(hAll);
      h2018preHEM_div->SetLineWidth(2);
      prepHists({h2018preHEM_div}, false, false, false, {kAzure});

      TH1* h2018postHEM_div = (TH1*)h2018postHEM->Clone();
      h2018postHEM_div->Divide(hAll);
      h2018postHEM_div->SetLineWidth(2);
      prepHists({h2018postHEM_div}, false, false, false, {kMagenta});

      auto leg = prepLegends({}, {""}, "l");
      appendLegends(leg, {hAll}, {"TF All"}, "l");
      appendLegends(leg, {h2016}, {"TF 2016"}, "l");
      appendLegends(leg, {h2017RunBtoE}, {"TF 2017 RunBtoE"}, "l");
      appendLegends(leg, {h2017RunF}, {"TF 2017 RunF"}, "l");
      appendLegends(leg, {h2018preHEM}, {"TF 2018 preHEM"}, "l");
      appendLegends(leg, {h2018postHEM}, {"TF 2018 postHEM"}, "l");
      leg->SetTextSize(0.03);
//        leg->SetNColumns(2);
      leg->SetY1NDC(leg->GetY2NDC() - 0.2);
      TCanvas* c = nullptr;
      if(i != 1) c = drawCompAndRatio({hAll, h2016, h2017RunBtoE, h2017RunF, h2018preHEM, h2018postHEM}, {h2016_div, h2017RunBtoE_div, h2017RunF_div, h2018preHEM_div, h2018postHEM_div}, leg, "TF_{era}/TF_{All}", 0.001, 2.999, true, 0.00001, 110);
      else       c = drawCompAndRatio({hAll, h2016, h2017RunBtoE, h2017RunF, h2018preHEM, h2018postHEM}, {h2016_div, h2017RunBtoE_div, h2017RunF_div, h2018preHEM_div, h2018postHEM_div}, leg, "TF_{era}/TF_{All}", 0.001, 2.999, true, 0.1, 110);
      TString outputBase = "LostLepton"+tf[i]+"_Comparison" + sep[j];
      c->SetTitle(outputBase);
      c->Print(l.config.outputdir+"/TransferFactor/"+outputBase+".pdf");
      c->Print(l.config.outputdir+"/TransferFactor/"+outputBase+".C");

      TFile *output = new TFile(l.config.outputdir+"/"+outputBase+".root", "RECREATE");
      hAll->Write();
      h2016->Write();
      h2017RunBtoE->Write();
      h2017RunF->Write();
      h2018preHEM->Write();
      h2018postHEM->Write();
      output->Close();

      TCanvas* TFSumCanvas  = new TCanvas(outputBase+"_TF", "Transfer Factors", 200, 10, 700, 500);
      TH1F* h2016Sum        = new TH1F("hTF_0", "Transfer Factors", 41, -0.025, 2.025);
      TH1F* h2017RunBtoESum = new TH1F("hTF_1", "Transfer Factors", 41, -0.025, 2.025);
      TH1F* h2017RunFSum    = new TH1F("hTF_2", "Transfer Factors", 41, -0.025, 2.025);
      TH1F* h2018preHEMSum  = new TH1F("hTF_3", "Transfer Factors", 41, -0.025, 2.025);
      TH1F* h2018postHEMSum = new TH1F("hTF_4", "Transfer Factors", 41, -0.025, 2.025);
      for(unsigned int i = 1; i != h2016_div->GetNbinsX(); i++){
        h2016Sum->Fill(h2016_div->GetBinContent(i));
        h2017RunBtoESum->Fill(h2017RunBtoE_div->GetBinContent(i));
        h2017RunFSum->Fill(h2017RunF_div->GetBinContent(i));
        h2018preHEMSum->Fill(h2018preHEM_div->GetBinContent(i));
        h2018postHEMSum->Fill(h2018postHEM_div->GetBinContent(i));
        //cout << "2016: " << h2016_div->GetBinContent(i) << ", 2017 RunBtoE: " << h2017RunBtoE_div->GetBinContent(i) << ", 2017 RunF: " << h2017RunF_div->GetBinContent(i) << ", 2018 preHEM: " << h2018preHEM_div->GetBinContent(i) << ", 2018 postHEM: " << h2018postHEM_div->GetBinContent(i) << endl;
      }
      TFSumCanvas->cd();
      h2016Sum->SetLineWidth(2);
      h2016Sum->SetLineColor(kRed);
      h2017RunBtoESum->SetLineWidth(2);
      h2017RunBtoESum->SetLineColor(kBlue);
      h2017RunFSum->SetLineWidth(2);
      h2017RunFSum->SetLineColor(kGreen);
      h2018preHEMSum->SetLineWidth(2);
      h2018preHEMSum->SetLineColor(kAzure);
      h2018postHEMSum->SetLineWidth(2);
      h2018postHEMSum->SetLineColor(kMagenta);

      int max2016 = h2016Sum->GetMaximum();
      int max2017RunBtoE = h2017RunBtoESum->GetMaximum();
      int max2017RunF = h2017RunFSum->GetMaximum();
      int max2018preHEM = h2018preHEMSum->GetMaximum();
      int max2018PostHEM = h2018postHEMSum->GetMaximum();
      
      int max = std::max(max2016, std::max(std::max(max2017RunBtoE, max2017RunF), std::max(max2018preHEM, max2018PostHEM)));
      h2016Sum->SetMaximum(1.1*max);

      h2016Sum->GetYaxis()->SetTitleFont(62);
      h2016Sum->GetYaxis()->CenterTitle(kTRUE);
      h2016Sum->GetXaxis()->SetTitleFont(62);
      h2016Sum->GetYaxis()->SetNdivisions(305);
      h2016Sum->GetYaxis()->SetTitle("Search Regions");
      h2016Sum->GetXaxis()->SetTitle("(TF_{era})/(TF_{All})");
      
      float Mean2016 = h2016Sum->GetMean();
      float Mean2017RunBtoE = h2017RunBtoESum->GetMean();
      float Mean2017RunF = h2017RunFSum->GetMean();
      float Mean2018preHEM = h2018preHEMSum->GetMean();
      float Mean2018postHEM = h2018postHEMSum->GetMean();

      h2016Sum->Draw();
      h2017RunBtoESum->Draw("same");
      h2017RunFSum->Draw("same");
      h2018preHEMSum->Draw("same");
      h2018postHEMSum->Draw("same");
      auto legend = new TLegend(0.75,0.60,0.95,0.90);
      legend->AddEntry(h2016Sum, "TF 2016", "l");
      legend->AddEntry(h2017RunBtoESum, "TF 2017 RunBtoE", "l");
      legend->AddEntry(h2017RunFSum, "TF 2017 RunF", "l");
      legend->AddEntry(h2018preHEMSum, "TF 2018 preHEM", "l");
      legend->AddEntry(h2018postHEMSum, "TF 2018 postHEM", "l");
      legend->Draw();

      float ymax = h2016Sum->GetMaximum();
      TLine *line_m = new TLine(0.9, 0, 0.9, ymax);
      TLine *line_p = new TLine(1.1, 0, 1.1, ymax);
      line_m->SetLineColor(kBlack);
      line_p->SetLineColor(kBlack);
      line_m->SetLineStyle(2);
      line_p->SetLineStyle(2);
      line_m->Draw();
      line_p->Draw();

//  drawTLatexNDC(TString text, double xpos, double ypos, double size=0.03, double align=11, double angle = 0, int font = 62, int color = 1)
      drawTLatexNDC("TF 2016 Mean: " + to_string(Mean2016), 0.2, 0.80);
      drawTLatexNDC("TF 2017 RunBtoE Mean: " + to_string(Mean2017RunBtoE), 0.2, 0.75);
      drawTLatexNDC("TF 2017 RunF Mean: " + to_string(Mean2017RunF), 0.2, 0.70);
      drawTLatexNDC("TF 2018 preHEM Mean: " + to_string(Mean2018preHEM), 0.2, 0.65);
      drawTLatexNDC("TF 2018 postHEM Mean: " + to_string(Mean2018postHEM), 0.2, 0.60);
      cout << "TF 2016 Mean: " << Mean2016 << endl;
      cout << "TF 2017 RunBtoE Mean: " << Mean2017RunBtoE << endl;
      cout << "TF 2017 RunF Mean: " << Mean2017RunF << endl;
      cout << "TF 2018 preHEM Mean: " << Mean2018preHEM << endl;
      cout << "TF 2018 postHEM Mean: " << Mean2018postHEM << endl;
      CMS_lumi(TFSumCanvas, 4, 10);
      TFSumCanvas->Update();   
 
      TFSumCanvas->Print(l.config.outputdir+"/TransferFactor/" + outputBase +"_sum.pdf");
      TFSumCanvas->Print(l.config.outputdir+"/TransferFactor/" + outputBase +"_sum.C");
      TFSumCanvas->Print(l.config.outputdir+"/TransferFactor/" + outputBase +"_sum_canvas.root");

      delete gROOT->FindObject("hTF_0"); 
      delete gROOT->FindObject("hTF_1");  
      delete gROOT->FindObject("hTF_2"); 
      delete gROOT->FindObject("hTF_3"); 
      delete gROOT->FindObject("hTF_4");
    }
  }

  return l.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotLepCR(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_2017";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar", "wjets", "tW", "ttW"};
  TString data_sample = "singlelep";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.72); };
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plotLepCRAllEras(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_allEras";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017RunBtoE", "ttbar-2017RunF", "ttbar-2018preHEM", "ttbar-2018postHEM", "wjets-2016", "wjets-2017RunBtoE", "wjets-2017RunF", "wjets-2018preHEM", "wjets-2018postHEM", 
				"tW-2016", "tW-2017RunBtoE", "tW-2017RunF", "tW-2018preHEM", "tW-2018postHEM", "ttW-2016", "ttW-2017RunBtoE", "ttW-2017RunF", "ttW-2018preHEM", "ttW-2018postHEM"};
  TString data_sample = "singlelep";

  for (auto category : z.config.categories){
    const auto &cat = z.config.catMaps.at(category);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.72); };
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra);
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void compSLep2(){

  map<TString, vector<Quantity>> sLeps;
  map<TString, vector<Quantity>> pred;

  {
    ICHEPCR = true;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["ichepcr"] = z.yields.at("_SLep");
    pred["ichepcr"] = z.yields.at("_pred");
  }

  {
    ICHEPCR = false;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["newcr"] = z.yields.at("_SLep");
    pred["newcr"] = z.yields.at("_pred");

  }

  map<TString, TString> labelMap = {
      {"ichepcr", "ichep cr"},
      {"newcr", "new cr"}
      //{"addback", "#slash{E}_{T}+#vec{p}_{T}^{lep}"},
      //{"noaddback", "Traditional"}
  };

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : sLeps){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Correction");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "newcr") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);
    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio", 0., 2., true, -1., 2.);
    c->SaveAs(lepConfig().outputdir+"/llb_crs_sf_cmp.pdf");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_sf_cmp.root");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_sf_cmp.C");
  }

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : pred){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Events");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "newcr") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);

    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio", 0., 2., true, 0.01);
    c->SaveAs(lepConfig().outputdir+"/llb_crs_pred_cmp.pdf");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_pred_cmp.root");
    c->SaveAs(lepConfig().outputdir+"/llb_crs_pred_cmp.C");
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void compSLep(){

  map<TString, vector<Quantity>> sLeps;
  map<TString, vector<Quantity>> pred;

  {
    ADD_LEP_TO_MET = true;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["addback"] = z.yields.at("_SLep");
    pred["addback"] = z.yields.at("_pred");
  }

  {
    ADD_LEP_TO_MET = false;

    auto config = lepConfig();
    config.samples.erase("qcd-sr");
    LLBEstimator z(config.outputdir);
    z.setConfig(config);
    z.pred();
    sLeps["noaddback"] = z.yields.at("_SLep");
    pred["noaddback"] = z.yields.at("_pred");

  }

  map<TString, TString> labelMap = {
      {"addback", "#slash{E}_{T}+#vec{p}_{T}^{lep}"},
      {"noaddback", "Traditional"}
  };

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : sLeps){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Correction");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "noaddback") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);

    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio");
    c->SaveAs(lepConfig().outputdir+"/llb_sf_cmp.pdf");
  }

  {
    auto leg = initLegend();
    vector<TH1*> hists, hnum;
    TH1* href = nullptr;
    for (auto &p : pred){
      cout << p.first << p.second << endl;
      auto h = convertToHist(p.second, p.first, ";SR;Events");
      appendLegends(leg, {h}, {labelMap.at(p.first)});
      hists.push_back(h);
      if (p.first == "noaddback") href = h;
      else hnum.push_back(h);
    }
    prepHists(hists, false, false);
    href->SetLineColor(kRed); href->SetMarkerColor(kRed);

    auto c=drawCompAndRatio(hists, makeRatioHists(hnum, href), leg, "Ratio");
    c->SaveAs(lepConfig().outputdir+"/llb_pred_cmp.pdf");
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void srYields(){

  auto config = lepConfig();
  config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("ttbar-sr",       "t#bar{t}",      "ttbar",        lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "wjets",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "ttW",             lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("qcd-sr",         "QCD",           "qcd",    lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("znunu-sr",       "znunu",         "znunu",           lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("T1tttt-sr",	     "T1tttt(2000, 100)", "T1tttt_2000_100", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("T2tt_850_100-sr","T2tt(850, 100)","T2tt_850_100", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
  config.addSample("T2tt_500_325-sr","T2tt(500, 325)","T2tt_500_325", lepvetowgt+"*ISRWeight", datasel + trigSR + vetoes);
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);


  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["Total BKG"] = -3;
  digits["T1tttt-sr"] = -3;
  digits["T2tt_850_100-sr"] = -3;
  digits["T2tt_500_325-sr"] = -3;

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr"}, "Total BKG");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"});
  z.printYieldsTableLatex({"Total BKG", "T1tttt-sr", "T2tt_850_100-sr", "T2tt_500_325-sr"}, labelMap, "yields_llb_hm_raw.tex", "hm", digits);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SBv4Yields(){

  auto config = lepConfig();
  config.crCatMaps.clear();

  config.samples.clear();
  //config.addSample("ttbar-sr",       "t#bar{t}",      inputdir_2016+"ttbar",        "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight*ISRWeight", datasel + vetoes);
  //config.addSample("wjets-sr",       "W+jets",        inputdir_2016+"wjets",        "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("tW-sr",          "tW",            inputdir_2016+"tW",           "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("ttW-sr",         "ttW",           inputdir_2016+"ttW",          "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("ttZ-sr",         "ttZ",           inputdir_2016+"ttZ",          "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("qcd-sr",         "QCD",           inputdir_2016+"qcd",    	    "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("znunu-sr",       "znunu",         inputdir_2016+"znunu",        "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("ttbar-v2-sr",       "t#bar{t}",      inputdir_2016+"../nanoaod_all_skim_2016_082619/ttbar",        "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight*ISRWeight", datasel + vetoes);
  //config.addSample("wjets-v2-sr",       "W+jets",        inputdir_2016+"../nanoaod_all_skim_2016_082619/wjets",        "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("tW-v2-sr",          "tW",            inputdir_2016+"../nanoaod_all_skim_2016_082619/tW",           "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("ttW-v2-sr",         "ttW",           inputdir_2016+"../nanoaod_all_skim_2016_082619/ttW",          "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("ttZ-v2-sr",         "ttZ",           inputdir_2016+"../nanoaod_all_skim_2016_082619/ttZ",          "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("qcd-v2-sr",         "QCD",           inputdir_2016+"../nanoaod_all_skim_2016_082619/qcd",    	    "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);
  //config.addSample("znunu-v2-sr",       "znunu",         inputdir_2016+"../nanoaod_all_skim_2016_082619/znunu",        "137.728*1000*Stop0l_evtWeight*Stop0l_trigger_eff_MET_loose_baseline*puWeight*PrefireWeight", datasel + vetoes);

  config.addSample("ttbar-sr",       "t#bar{t}",      inputdir_2016+"ttbar",        "1.0", datasel + vetoes);
  config.addSample("wjets-sr",       "W+jets",        inputdir_2016+"wjets",        "1.0", datasel + vetoes);
  config.addSample("tW-sr",          "tW",            inputdir_2016+"tW",           "1.0", datasel + vetoes);
  config.addSample("ttW-sr",         "ttW",           inputdir_2016+"ttW",          "1.0", datasel + vetoes);
  config.addSample("ttZ-sr",         "ttZ",           inputdir_2016+"ttZ",          "1.0", datasel + vetoes);
  config.addSample("qcd-sr",         "QCD",           inputdir_2016+"qcd",    	    "1.0", datasel + vetoes);
  config.addSample("znunu-sr",       "znunu",         inputdir_2016+"znunu",        "1.0", datasel + vetoes);
  config.addSample("ttbar-v2-sr",       "t#bar{t}",      inputdir_2016+"../nanoaod_all_skim_2016_082619/ttbar",        "1.0", datasel + vetoes);
  config.addSample("wjets-v2-sr",       "W+jets",        inputdir_2016+"../nanoaod_all_skim_2016_082619/wjets",        "1.0", datasel + vetoes);
  config.addSample("tW-v2-sr",          "tW",            inputdir_2016+"../nanoaod_all_skim_2016_082619/tW",           "1.0", datasel + vetoes);
  config.addSample("ttW-v2-sr",         "ttW",           inputdir_2016+"../nanoaod_all_skim_2016_082619/ttW",          "1.0", datasel + vetoes);
  config.addSample("ttZ-v2-sr",         "ttZ",           inputdir_2016+"../nanoaod_all_skim_2016_082619/ttZ",          "1.0", datasel + vetoes);
  config.addSample("qcd-v2-sr",         "QCD",           inputdir_2016+"../nanoaod_all_skim_2016_082619/qcd",    	"1.0", datasel + vetoes);
  config.addSample("znunu-v2-sr",       "znunu",         inputdir_2016+"../nanoaod_all_skim_2016_082619/znunu",        "1.0", datasel + vetoes);
//  config.addSample("ww-sr",          "WW",            "sr/ww",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("wz-sr",          "WZ",            "sr/wz",              lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("zz-sr",          "ZZ",            "sr/zz",              lepvetowgt, datasel + trigSR + vetoes);


  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["LL"] = -5;
  digits["ttZ-sr"] = -5;
  digits["LL v2"] = -5;
  digits["ttZ-v2-sr"] = -5;

  z.calcYields();
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "LL");
  z.sumYields({"ttbar-v2-sr", "wjets-v2-sr", "tW-v2-sr", "ttW-v2-sr"}, "LL v2");
  z.printYieldsTable({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "qcd-sr", "znunu-sr", "ttZ-sr", "LL"});
  z.printYieldsTableLatex({"LL", "ttZ-sr", "LL v2", "ttZ-v2-sr"}, labelMap, "yields_llb_hm_raw.tex", "hm", digits);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lepcrYields(){

  auto config = lepConfig();

  config.samples.clear();
  config.addSample("singlelep",   "Data",          "met",       		"1.0",     datasel + trigLepCR + lepcrsel);
  config.addSample("ttbar",       "t#bar{t}",      "ttbar",        		lepselwgt+"*ISRWeight", datasel + trigLepCR + lepcrsel);
  config.addSample("wjets",       "W+jets",        "wjets",        		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("tW",          "tW",            "tW",              		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("ttW",         "ttW",           "ttW",             		lepselwgt, datasel + trigLepCR + lepcrsel);
  config.addSample("qcd",         "QCD",           "qcd",             		lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("ww",          "WW",            "sr/ww",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("wz",          "WZ",            "sr/wz",                 lepselwgt, datasel + trigLepCR + lepcrsel);
//  config.addSample("zz",          "ZZ",            "sr/zz",                 lepselwgt, datasel + trigLepCR + lepcrsel);

  BaseEstimator z(config);

  z.calcYields();
  z.printYields();
  z.sumYields({"ttbar", "wjets", "tW", "ttW", "qcd"}, "Total BKG");
  z.sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw-cr");
  z.printYieldsTable({"ttbar", "wjets", "tW", "ttW", "qcd", "Total BKG", "singlelep"});

  vector<TH1*> mc;
  mc.push_back(convertToHist(z.yields.at("ttbar"),"ttbar_cr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("wjets"),"wjets",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("tW"),"tW_cr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("ttW"),"ttWcr",";Search Region;Events"));
  mc.push_back(convertToHist(z.yields.at("ttbarplusw-cr"),"ttbarplusw_cr",";Search Region;Events"));
  
  auto hdata = convertToHist(z.yields.at("singlelep"),"data",";Search Region;Events");

  TFile *output = new TFile(z.config.outputdir+"/llcr_yields.root", "RECREATE");
  for (auto *h : mc)   h->Write();
  hdata->Write();
  output->Close();

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusive(){
  auto config = lepConfig();
  //config.sel = "MET_pt > 200";
  TString LLCR = "Pass_dPhiMETLowDM";
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_LMMed = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETMedDM";
  TString LLCR_LM_NoMed = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  config.sel = baseline + " && Stop0l_nJets >= 2";

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017RunBtoE", "ttbar-2017RunF", "ttbar-2018preHEM", "ttbar-2018postHEM", "wjets-2016", "wjets-2017RunBtoE", "wjets-2017RunF", "wjets-2018preHEM", "wjets-2018postHEM", 
				"tW-2016", "tW-2017RunBtoE", "tW-2017RunF", "tW-2018preHEM", "tW-2018postHEM", "ttW-2016", "ttW-2017RunBtoE", "ttW-2017RunF", "ttW-2018preHEM", "ttW-2018postHEM"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_samples_2017RunBtoE = {"ttbar-2017RunBtoE", "wjets-2017RunBtoE", "tW-2017RunBtoE", "ttW-2017RunBtoE"};
  vector<TString> mc_samples_2017RunF = {"ttbar-2017RunF", "wjets-2017RunF", "tW-2017RunF", "ttW-2017RunF"};
  vector<TString> mc_samples_2018preHEM = {"ttbar-2018preHEM", "wjets-2018preHEM", "tW-2018preHEM", "ttW-2018preHEM"};
  vector<TString> mc_samples_2018postHEM = {"ttbar-2018postHEM", "wjets-2018postHEM", "tW-2018postHEM", "ttW-2018postHEM"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017RunBtoE = "singlelep-2017RunBtoE";
  TString data_sample_2017RunF = "singlelep-2017RunF";
  TString data_sample_2018preHEM = "singlelep-2018preHEM";
  TString data_sample_2018postHEM = "singlelep-2018postHEM";

  map<TString, BinInfo> varDict {
	//{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"njets",     BinInfo("Stop0l_nJets", "N_{j}", 11, -0.5, 10.5)},
	//{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
	//{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
	{"dphij1met", BinInfo("Jet_dPhiMET[0]", "#Delta#phi(j_{1},#slash{E}_{T})", 30, 0, 3)},
	{"dphij2met", BinInfo("Jet_dPhiMET[1]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
	{"dphij3met", BinInfo("Jet_dPhiMET[2]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
  };
  vector< pair< TString, TString> > npv_bin = {
	make_pair(" && 1 == 1", 				"_allPU"),
	//make_pair(" && PV_npvsGood >= 0 && PV_npvsGood < 10", 	"_PU0to10"),
	//make_pair(" && PV_npvsGood >= 10 && PV_npvsGood < 20", 	"_PU10to20"),
	//make_pair(" && PV_npvsGood >= 20 && PV_npvsGood < 30", 	"_PU20to30"),
	//make_pair(" && PV_npvsGood >= 30 && PV_npvsGood < 40", 	"_PU30to40"),
	//make_pair(" && PV_npvsGood >= 40", 			"_PUgeq40"),
  };

  std::function<void(TCanvas*)> plotextra;
  std::function<void(TCanvas*)> plotextra30;
  for(int iPU = 0; iPU != npv_bin.size(); iPU++){
    for (auto &var : varDict){
      z.resetSelection();
      z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2016" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR LM Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", false, &plotextra);
      z.setSelection(LLCR_LM_NoMed + npv_bin[iPU].first, "llcr_lm_nomed_2016" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR LM No Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", false, &plotextra);
      z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2017RunBtoE" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017RunBtoE LLCR LM Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2017RunBtoE, data_sample_2017RunBtoE, Category::dummy_category(), false, "", false, &plotextra);
      z.setSelection(LLCR_LM_NoMed + npv_bin[iPU].first, "llcr_lm_nomed_2017RunBtoE" + npv_bin[iPU].second, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017RunBtoE LLCR LM No Med", 0.2, 0.72); };
      z.plotDataMC(var.second, mc_samples_2017RunBtoE, data_sample_2017RunBtoE, Category::dummy_category(), false, "", false, &plotextra);
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2017RunF" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017RunF LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples_2017RunF, data_sample_2017RunF, Category::dummy_category(), false, "", false, &plotextra);
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2018preHEM" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2018preHEM LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples_2018preHEM, data_sample_2018preHEM, Category::dummy_category(), false, "", false, &plotextra);
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_2018postHEM" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2018postHEM LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples_2018postHEM, data_sample_2018postHEM, Category::dummy_category(), false, "", false, &plotextra);
      //
      //z.setSelection(LLCR_LMMed + npv_bin[iPU].first, "llcr_lm_med_AllEras" + npv_bin[iPU].second, "");
      //plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("LLCR LM Med N_{j}(p_{T} #geq 20)", 0.2, 0.72); };
      //z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", false, &plotextra);
    }
  }
  
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusive2016(){
  auto config = lepConfig();
  //config.sel = "MET_pt > 200";
  TString LLCR = "Pass_dPhiMETLowDM";
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_LMMed = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETMedDM";
  TString LLCR_LM_NoMed = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  config.sel = baseline + " && Stop0l_nJets >= 2";

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  BaseEstimator z(config.outputdir);
  z.setConfig(config);

  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> sig_sample_fullsim = {"T2tt_175_1_full", "T2tt_250_50_full", "T2tt_250_75_full", "T2tt_250_100_full"};
  vector<TString> sig_sample_fastsim = {"T2tt_175_0_fast", "T2tt_250_50_fast", "T2tt_250_75_fast", "T2tt_250_100_fast"};
  TString data_sample = "singlelep-2016";

  map<TString, BinInfo> varDict {
	{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"njets",     BinInfo("Stop0l_nJets", "N_{j}", 11, -0.5, 10.5)},
	//{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
	//{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
	//{"dphij1met", BinInfo("Jet_dPhiMET[0]", "#Delta#phi(j_{1},#slash{E}_{T})", 30, 0, 3)},
	//{"dphij2met", BinInfo("Jet_dPhiMET[1]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
	//{"dphij3met", BinInfo("Jet_dPhiMET[2]", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
  };

  std::function<void(TCanvas*)> plotextra;
  std::function<void(TCanvas*)> plotextra30;
  for (auto &var : varDict){
    z.resetSelection();
    z.setSelection(LLCR_LM, "llcr_lm_2017_fullsim_v3", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017 LLCR LM fullsim_v3", 0.2, 0.72); };
    z.plotSigVsBkg(var.second, mc_samples_2016, sig_sample_fullsim, Category::dummy_category(), true, true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2017_fullsim_v3", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017 LLCR LM fullsim_v3", 0.2, 0.72); };
    z.plotSigVsBkg(var.second, mc_samples_2016, sig_sample_fullsim, Category::dummy_category(), true, true, &plotextra);

    z.setSelection(LLCR_LM, "llcr_lm_2017_fastsim_v3", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017 LLCR LM fastsim_v3", 0.2, 0.72); };
    z.plotSigVsBkg(var.second, mc_samples_2016, sig_sample_fastsim, Category::dummy_category(), true, true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2017_fastsim_v3", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017 LLCR LM fastsim_v3", 0.2, 0.72); };
    z.plotSigVsBkg(var.second, mc_samples_2016, sig_sample_fastsim, Category::dummy_category(), true, true, &plotextra);
  }
  
}

