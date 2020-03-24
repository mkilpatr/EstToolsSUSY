#include "../EstMethods/LLBEstimator.hh"

//#include "SRParameters.hh"
#include "LowMET_Parameters.hh"

using namespace EstTools;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPred(){

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  l.pred();

  l.printYields();

  std::map<TString,int> digits;
  digits["singlelep"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap"] = -5;
  digits["_TF_SR_extrap"] = -5;
  digits["_pred"] = -5;

  l.printYieldsTableLatex({"singlelep", "ttbarplusw", "ttbarplusw-sr", "_TF", "_pred"}, labelMap, "LLB/yields_llb_2016_njets30_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep", "ttbarplusw", "ttbarplusw-sr", "ttbarplusw-sr-int", "_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap", "_pred"}, labelMap, "LLB/yields_llb_2016_njets30_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep", "ttbarplusw", "ttbarplusw-sr", "_TF", "_pred"}, labelMap, "LLB/yields_llb_2016_njets30_hm.tex", "hm", digits);
  }

  return l.yields.at("_pred");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

vector<Quantity> LLBPredSeparate(){

  auto llbcfg = lepConfig();
  TString region = "TransferFactor_new";
  llbcfg.outputdir += "/" +region;
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  l.predSeparate();

  l.printYields();

  std::map<TString,int> digits;
  digits["singlelep"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap"] = -5;
  digits["_TF_SR_extrap"] = -5;
  digits["singlelep-2016"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2016"] = -5;
  digits["_TF_SR_extrap-2016"] = -5;
  digits["singlelep-2017"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2017"] = -5;
  digits["_TF_SR_extrap-2017"] = -5;
  digits["singlelep-2018"] = 0; // indicate it's data for proper formatting
  digits["_TF_CR_to_SR_noextrap-2018"] = -5;
  digits["_TF_SR_extrap-2018"] = -5;

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

  l.printYieldsTableLatex({"singlelep-2017", "_TF-2017", "_pred-2017"}, labelMap, "LLB/yields_llb_2017_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2017", "_TF-2017", "_TF_CR_to_SR_noextrap-2017", "_TF_SR_extrap-2017", "_pred-2017"}, labelMap, "LLB/yields_llb_2017_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2017", "_TF-2017", "_pred-2017"}, labelMap, "LLB/yields_llb_2017_hm.tex", "hm", digits);
  }

  l.printYieldsTableLatex({"singlelep-2018", "_TF-2018", "_pred-2018"}, labelMap, "LLB/yields_llb_2018_lm.tex", "lm", digits); // LM
  if(l.splitTF){
    l.printYieldsTableLatex({"singlelep-2018", "_TF-2018", "_TF_CR_to_SR_noextrap-2018", "_TF_SR_extrap-2018", "_pred-2018"}, labelMap, "LLB/yields_llb_2018_hm.tex", "hm", digits);
  }else{
    l.printYieldsTableLatex({"singlelep-2018", "_TF-2018", "_pred-2018"}, labelMap, "LLB/yields_llb_2018_hm.tex", "hm", digits);
  }

  vector<TString> tf = {"_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap"};
  vector<TString> sep = {"", "_LM", "_HM_1", "_HM_2"};

  int start = 0, manualBins = 0;
  int max_graph = l.yields.at(tf[0]).size() > 100 ? 3 : 2;
  int max_tf = 2;
  for(int j = 0; j <= max_graph; j++){
    if(l.splitTF){
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
    }else{
      if(j == 1){ 
        start = 0;
        manualBins = 19;
      } else if(j == 2){
        start = 19;
        manualBins = 24;
      }
    }
    for(int i = 0; i <= max_tf; i++){
      auto hAll = convertToHist(l.yields.at(tf[i]),"TF All" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2016 = convertToHist(l.yields.at(tf[i]+"-2016"),"TF 2016" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2017 = convertToHist(l.yields.at(tf[i]+"-2017"),"TF 2017" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);
      auto h2018 = convertToHist(l.yields.at(tf[i]+"-2018"),"TF 2018" + to_string(i) + to_string(j),";Search Region;Transfer Factor", nullptr, start, manualBins);

      prepHists({hAll, h2016, h2017, h2018}, false, false, false, {kBlack, kRed, kAzure+6, 876});

      TH1* h2016_div = (TH1*)h2016->Clone();
      h2016_div->Divide(hAll);
      h2016_div->SetLineWidth(2);
      prepHists({h2016_div}, false, false, false, {kRed});

      TH1* h2017_div = (TH1*)h2017->Clone();
      h2017_div->Divide(hAll);
      h2017_div->SetLineWidth(2);
      prepHists({h2017_div}, false, false, false, {kAzure+6});

      TH1* h2018_div = (TH1*)h2018->Clone();
      h2018_div->Divide(hAll);
      h2018_div->SetLineWidth(2);
      prepHists({h2018_div}, false, false, false, {876});

      auto leg = prepLegends({}, {""}, "l");
      appendLegends(leg, {hAll}, {"TF All"}, "l");
      appendLegends(leg, {h2016}, {"TF 2016"}, "l");
      appendLegends(leg, {h2017}, {"TF 2017"}, "l");
      appendLegends(leg, {h2018}, {"TF 2018"}, "l");
      leg->SetTextSize(0.03);
//        leg->SetNColumns(2);
      leg->SetY1NDC(leg->GetY2NDC() - 0.2);
      TCanvas* c = nullptr;
      if(i != 1) c = drawCompAndRatio({hAll, h2016, h2017, h2018}, {h2016_div, h2017_div, h2018_div}, leg, "TF_{era}/TF_{All}", 0.001, 2.999, true, 0.00001, 110);
      else       c = drawCompAndRatio({hAll, h2016, h2017, h2018}, {h2016_div, h2017_div, h2018_div}, leg, "TF_{era}/TF_{All}", 0.001, 2.999, true, 0.1, 110);
      TString outputBase = "LostLepton"+tf[i]+"_Comparison" + sep[j];
      c->SetTitle(outputBase);
      c->Print(l.config.outputdir+"/"+outputBase+".pdf");
      c->Print(l.config.outputdir+"/"+outputBase+".C");

      TFile *output = new TFile(l.config.outputdir+"/"+outputBase+".root", "RECREATE");
      hAll->Write();
      h2016->Write();
      h2017->Write();
      h2018->Write();
      output->Close();

      TCanvas* TFSumCanvas  = new TCanvas(outputBase+"_TF", "Transfer Factors", 200, 10, 700, 500);
      TH1F* h2016Sum        = new TH1F("hTF_0", "Transfer Factors", 41, -0.025, 2.025);
      TH1F* h2017Sum = new TH1F("hTF_1", "Transfer Factors", 41, -0.025, 2.025);
      TH1F* h2018Sum  = new TH1F("hTF_3", "Transfer Factors", 41, -0.025, 2.025);
      for(int i = 1; i != h2016_div->GetNbinsX(); i++){
        h2016Sum->Fill(h2016_div->GetBinContent(i));
        h2017Sum->Fill(h2017_div->GetBinContent(i));
        h2018Sum->Fill(h2018_div->GetBinContent(i));
      }

      TFSumCanvas->cd();
      h2016Sum->SetLineWidth(2);
      h2016Sum->SetLineColor(kRed);
      h2017Sum->SetLineWidth(2);
      h2017Sum->SetLineColor(kAzure+6);
      h2018Sum->SetLineWidth(2);
      h2018Sum->SetLineColor(876);

      int max2016 = h2016Sum->GetMaximum();
      int max2017 = h2017Sum->GetMaximum();
      int max2018 = h2018Sum->GetMaximum();
      
      int max = std::max(max2016, std::max(max2017, max2018));
      h2016Sum->SetMaximum(1.1*max);

      h2016Sum->GetYaxis()->SetTitleFont(62);
      h2016Sum->GetYaxis()->CenterTitle(kTRUE);
      h2016Sum->GetXaxis()->SetTitleFont(62);
      h2016Sum->GetYaxis()->SetNdivisions(305);
      h2016Sum->GetYaxis()->SetTitle("Search Regions");
      h2016Sum->GetXaxis()->SetTitle("(TF_{era})/(TF_{All})");
      
      float Mean2016 = h2016Sum->GetMean();
      float Mean2017 = h2017Sum->GetMean();
      float Mean2018 = h2018Sum->GetMean();

      h2016Sum->Draw();
      h2017Sum->Draw("same");
      h2018Sum->Draw("same");
      auto legend = new TLegend(0.75,0.60,0.95,0.90);
      legend->AddEntry(h2016Sum, "TF 2016", "l");
      legend->AddEntry(h2017Sum, "TF 2017", "l");
      legend->AddEntry(h2018Sum, "TF 2018", "l");
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
      drawTLatexNDC("TF 2017 Mean: " + to_string(Mean2017), 0.2, 0.75);
      drawTLatexNDC("TF 2018 Mean: " + to_string(Mean2018), 0.2, 0.70);
      cout << "TF 2016 Mean: " << Mean2016 << endl;
      cout << "TF 2017 Mean: " << Mean2017 << endl;
      cout << "TF 2018 Mean: " << Mean2018 << endl;
      CMS_lumi(TFSumCanvas, 4, 10);
      TFSumCanvas->Update();   
 
      TFSumCanvas->Print(l.config.outputdir+"/" + outputBase +"_sum.pdf");
      TFSumCanvas->Print(l.config.outputdir+"/" + outputBase +"_sum.C");
      TFSumCanvas->Print(l.config.outputdir+"/" + outputBase +"_sum_canvas.root");

      delete gROOT->FindObject("hTF_0"); 
      delete gROOT->FindObject("hTF_1");  
      delete gROOT->FindObject("hTF_3"); 
    }
  }

  return l.yields.at("_pred");
}

//--------------------------------------------------
vector<Quantity> ANQuestion(){

  auto llbcfg = lepConfig();
  TString outputBase = "";
  TString region = "ANQuestion";
  llbcfg.outputdir += "/" +region;
  LLBEstimator l(llbcfg);
  l.splitTF = SPLITTF;
  l.predSeparate();

  l.printYields();

  vector<TString> mc_name = {"ttbar", "wjets", "tW", "ttW", "ttbarplusw"};

  for(unsigned i = 0; i != mc_name.size(); i++){
    TH1* mc_2016_cr = convertToHist(l.yields.at(mc_name[i]+"-2016"),mc_name[i]+"_cr_2016",";AN Region;Events", nullptr);
    TH1* mc_2017_cr = convertToHist(l.yields.at(mc_name[i]+"-2017"),mc_name[i]+"_cr_2017",";AN Region;Events", nullptr);
    TH1* mc_2018_cr = convertToHist(l.yields.at(mc_name[i]+"-2018"),mc_name[i]+"_cr_2018",";AN Region;Events", nullptr);
    TH1* mc_Run2_cr = convertToHist(l.yields.at(mc_name[i]),mc_name[i]+"_cr",";AN Region;Events", nullptr);
    TH1* mc_2016_sr = convertToHist(l.yields.at(mc_name[i]+"-2016-sr-int"),mc_name[i]+"_sr_2016",";AN Region;Events", nullptr);
    TH1* mc_2017_sr = convertToHist(l.yields.at(mc_name[i]+"-2017-sr-int"),mc_name[i]+"_sr_2017",";AN Region;Events", nullptr);
    TH1* mc_2018_sr = convertToHist(l.yields.at(mc_name[i]+"-2018-sr-int"),mc_name[i]+"_sr_2018",";AN Region;Events", nullptr);
    TH1* mc_Run2_sr = convertToHist(l.yields.at(mc_name[i]+"-sr-int"),mc_name[i]+"_sr",";AN Region;Events", nullptr);

    prepHists({mc_2016_cr}, false, false, false, {kRed});
    prepHists({mc_2016_sr}, false, false, false, {kRed+2});
    prepHists({mc_2017_cr}, false, false, false, {kBlue});
    prepHists({mc_2017_sr}, false, false, false, {kBlue+2});
    prepHists({mc_2018_cr}, false, false, false, {kMagenta});
    prepHists({mc_2018_sr}, false, false, false, {kMagenta+2});
    prepHists({mc_Run2_cr}, false, false, false, {kGreen});
    prepHists({mc_Run2_sr}, false, false, false, {kGreen+2});

    TH1* mc_2016_cr_ratio = (TH1*)mc_2016_sr->Clone(TString(mc_name[i]) + "2016_cr_ratio");
    mc_2016_cr_ratio->Divide(mc_Run2_cr);
    mc_2016_cr_ratio->SetLineWidth(2);
    prepHists({mc_2016_cr_ratio}, false, false, false, {kRed});
    TH1* mc_2017_cr_ratio = (TH1*)mc_2017_sr->Clone(TString(mc_name[i]) + "2017_cr_ratio");
    mc_2017_cr_ratio->Divide(mc_Run2_cr);
    mc_2017_cr_ratio->SetLineWidth(2);
    prepHists({mc_2017_cr_ratio}, false, false, false, {kBlue});
    TH1* mc_2018_cr_ratio = (TH1*)mc_2018_sr->Clone(TString(mc_name[i]) + "2018_cr_ratio");
    mc_2018_cr_ratio->Divide(mc_Run2_cr);
    mc_2018_cr_ratio->SetLineWidth(2);
    prepHists({mc_2018_cr_ratio}, false, false, false, {kMagenta});

    TH1* mc_2016_sr_ratio = (TH1*)mc_2016_sr->Clone(TString(mc_name[i]) + "2016_sr_ratio");
    mc_2016_sr_ratio->Divide(mc_Run2_sr);
    mc_2016_sr_ratio->SetLineWidth(2);
    prepHists({mc_2016_sr_ratio}, false, false, false, {kRed+2});
    TH1* mc_2017_sr_ratio = (TH1*)mc_2017_sr->Clone(TString(mc_name[i]) + "2017_sr_ratio");
    mc_2017_sr_ratio->Divide(mc_Run2_sr);
    mc_2017_sr_ratio->SetLineWidth(2);
    prepHists({mc_2017_sr_ratio}, false, false, false, {kBlue+2});
    TH1* mc_2018_sr_ratio = (TH1*)mc_2018_sr->Clone(TString(mc_name[i]) + "2018_sr_ratio");
    mc_2018_sr_ratio->Divide(mc_Run2_sr);
    mc_2018_sr_ratio->SetLineWidth(2);
    prepHists({mc_2018_sr_ratio}, false, false, false, {kMagenta+2});
    
    auto leg = prepLegends({}, {""}, "l");
    appendLegends(leg, {mc_2016_cr}, {mc_name[i] + " CR 2016"}, "L");
    appendLegends(leg, {mc_2017_cr}, {mc_name[i] + " CR 2017"}, "L");
    appendLegends(leg, {mc_2018_cr}, {mc_name[i] + " CR 2018"}, "L");
    appendLegends(leg, {mc_Run2_cr}, {mc_name[i] + " CR Run2"}, "L");
    appendLegends(leg, {mc_2016_sr}, {mc_name[i] + " SR 2016"}, "L");
    appendLegends(leg, {mc_2017_sr}, {mc_name[i] + " SR 2017"}, "L");
    appendLegends(leg, {mc_2018_sr}, {mc_name[i] + " SR 2018"}, "L");
    appendLegends(leg, {mc_Run2_sr}, {mc_name[i] + " SR Run2"}, "L");
    leg->SetTextSize(0.03);
    leg->SetY1NDC(leg->GetY2NDC() - 0.2);
    TCanvas* c = drawCompAndRatio({mc_2016_cr, mc_2017_cr, mc_2018_cr, mc_Run2_cr, mc_2016_sr, mc_2017_sr, mc_2018_sr, mc_Run2_sr}, {mc_2016_cr_ratio, mc_2017_cr_ratio, mc_2018_cr_ratio, mc_2016_sr_ratio, mc_2017_sr_ratio, mc_2018_sr_ratio}, leg, "N_{year}/N_{Run2}", 0.001, 0.999);
    c->SetTitle(outputBase + "_" + mc_name[i]);
    c->SetCanvasSize(800, 600);
    c->Print(l.config.outputdir+"/" + mc_name[i] + ".pdf");
    c->Print(l.config.outputdir+"/" + mc_name[i] + ".C");
    c->Print(l.config.outputdir+"/" + mc_name[i] + "_canvas.root");
  } 
 
  return l.yields.at("_pred");
}

//--------------------------------------------------

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

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_restop";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018", 
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  TString data_sample = "singlelep";

  for (auto category : z.config.categories){
    const auto &cat = z.config.crCatMaps.at(category);
    auto cat_label = translateString(cat.label, plotLabelMap, "_", ", ", true);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat_label, 0.2, 0.75); };
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
void ExtrapStudies(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();

  //config.samples.clear();
  //config.addSample("ttbar-2016",         "t#bar{t}",      inputdir_2016+"ttbar",           "1.0",      datasel + revert_vetoes);
  //config.addSample("wjets-2016",         "W+jets",        inputdir_2016+"wjets",           "1.0",      datasel + revert_vetoes);
  //config.addSample("tW-2016",            "tW",            inputdir_2016+"tW",              "1.0",      datasel + revert_vetoes);
  //config.addSample("ttW-2016",           "ttW",           inputdir_2016+"ttW",             "1.0",      datasel + revert_vetoes);
  //config.addSample("ttbar-2017",         "t#bar{t}",      inputdir_2017+"ttbar",           "1.0",      datasel + revert_vetoes);
  //config.addSample("wjets-2017",         "W+jets",        inputdir_2017+"wjets",           "1.0",      datasel + revert_vetoes);
  //config.addSample("tW-2017",            "tW",            inputdir_2017+"tW",              "1.0",      datasel + revert_vetoes);
  //config.addSample("ttW-2017",           "ttW",           inputdir_2017+"ttW",             "1.0",      datasel + revert_vetoes);
  //config.addSample("ttbar-2018",         "t#bar{t}",      inputdir_2018+"ttbar",           "1.0",      datasel + revert_vetoes);
  //config.addSample("wjets-2018",         "W+jets",        inputdir_2018+"wjets",           "1.0",      datasel + revert_vetoes);
  //config.addSample("tW-2018",            "tW",            inputdir_2018+"tW",              "1.0",      datasel + revert_vetoes);
  //config.addSample("ttW-2018",           "ttW",           inputdir_2018+"ttW",             "1.0",      datasel + revert_vetoes);

  TString region = "ExtrapolationStudy_withoutExtrap_toppt";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018", 
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_samples_2017 = {"ttbar-2017", "wjets-2017", "tW-2017", "ttW-2017"};
  vector<TString> mc_samples_2018 = {"ttbar-2018", "wjets-2018", "tW-2018", "ttW-2018"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017 = "singlelep-2017";
  TString data_sample_2018 = "singlelep-2018";

  map<TString, BinInfo> varDict {
	//{"restopsf",    BinInfo("Stop0l_ResTopWeight", "Stop0l_ResTopWeight", 100, 0.5, 1.5)},
	//{"deepak8",     BinInfo("Stop0l_DeepAK8_SFWeight", "Stop0l_DeepAK8_SFWeight", 100, 0.5, 1.5)},
	//{"ntop",        BinInfo("Stop0l_nTop", "N_{t}", 4, -0.5, 3.5)},
	//{"nrestop",     BinInfo("Stop0l_nResolved", "N_{rest}", 4, -0.5, 3.5)},
	//{"nw",          BinInfo("Stop0l_nW", "N_{W}", 4, -0.5, 3.5)},
	{"ak8jet",      BinInfo("FatJet_pt[0]", "p_{T}(ak8) [GeV]",  12, 200, 800)},
	{"ak4jet",      BinInfo("Jet_pt[0]", "p_{T}(ak4) [GeV]",  12, 200, 800)},
	//{"ak8jet_isr",      BinInfo("Stop0l_ISRJetPt[0]", "p_{T}(ISR) [GeV]",  12, 200, 800)},
  };

  std::function<void(TCanvas*)> plotextra;
  for (auto category : z.config.categories){
    for (auto &var : varDict){
      z.resetSelection();
      const auto &cat = z.config.crCatMaps.at(category);
      auto cat_label = translateString(cat.label, plotLabelMap, "_", ", ", true);
      //std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat_label, 0.2, 0.75); };
      std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat.label, 0.2, 0.75); };
      cout << cat_label << endl;
      //lumistr = "137.00079";
      //z.setSelection(cat.cut, "_Run2", "_Run2");
      //z.plotDataMC(var.second, mc_samples, "", cat, false, "", true, &plotextra);

      //lumistr = lumistr_2016;
      //z.setSelection(cat.cut, "_2016", "_2016");
      //z.plotDataMC(var.second, mc_samples_2016, "", cat, false, "", true, &plotextra);

      //lumistr = lumistr_2017;
      //z.setSelection(cat.cut, "_2017", "_2017");
      //z.plotDataMC(var.second, mc_samples_2017, data_sample_2017, cat, false, "", true, &plotextra);

      lumistr = lumistr_2018PostHEM;
      z.setSelection(cat.cut, "_2018", "_2018");
      z.plotDataMC(var.second, mc_samples_2018, data_sample_2018, cat, false, "", true, &plotextra);

    }
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusive(){
  auto config = lepConfig();
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  config.sel = baseline;

  config.categories.clear();
  config.catMaps.clear();
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString region = "lepcr_inclusive_v6";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018", 
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_samples_2017 = {"ttbar-2017", "wjets-2017", "tW-2017", "ttW-2017"};
  vector<TString> mc_samples_2018 = {"ttbar-2018", "wjets-2018", "tW-2018", "ttW-2018"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017 = "singlelep-2017";
  TString data_sample_2018 = "singlelep-2018";

  map<TString, BinInfo> varDict {
	//{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	{"ntop",        BinInfo("Stop0l_nTop", "N_{t}", 4, -0.5, 3.5)},
	{"nrestop",     BinInfo("Stop0l_nResolved", "N_{t}", 4, -0.5, 3.5)},
	{"nw",          BinInfo("Stop0l_nW", "N_{t}", 4, -0.5, 3.5)},
	//{"softbsf",     BinInfo("SoftBSF", "SoftBSF", 100, 0.5, 1.5)},
	//{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
	//{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
  };

  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    z.resetSelection();
    z.setSelection(LLCR_LM, "llcr_lm", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("Run2 LLCR LM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("Run2 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2016;
    z.setSelection(LLCR_LM, "llcr_lm_2016", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR LM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2016", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2017;
    z.setSelection(LLCR_LM, "llcr_lm_2017", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017 LLCR LM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_2017, data_sample_2017, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2017", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2017 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_2017, data_sample_2017, Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2018PostHEM;
    z.setSelection(LLCR_LM, "llcr_lm_2018", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2018 LLCR LM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_2018, data_sample_2018, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2018", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2018 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_2018, data_sample_2018, Category::dummy_category(), false, "", true, &plotextra);

  }
  
}
