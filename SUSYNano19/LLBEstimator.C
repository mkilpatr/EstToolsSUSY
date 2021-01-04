#include "../EstMethods/LLBEstimator.hh"

#include "SRParameters.hh"

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
  TString region = "TransferFactor_devv7_081620";
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

      TH1* h2017_div = (TH1*)h2017->Clone();
      h2017_div->Divide(hAll);
      h2017_div->SetLineWidth(2);

      TH1* h2018_div = (TH1*)h2018->Clone();
      h2018_div->Divide(hAll);
      h2018_div->SetLineWidth(2);
      prepHists({h2016_div, h2017_div, h2018_div}, false, false, false, {kRed, kAzure+6, 876});

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

      TH1F* h2016Sum = new TH1F("hTF_0", ";TF_{era}/TF_{All};Search Regions", 41, -0.025, 2.025);
      TH1F* h2017Sum = new TH1F("hTF_1", ";TF_{era}/TF_{All};Search Regions", 41, -0.025, 2.025);
      TH1F* h2018Sum = new TH1F("hTF_3", ";TF_{era}/TF_{All};Search Regions", 41, -0.025, 2.025);
      for(int i = 1; i != h2016_div->GetNbinsX(); i++){
        h2016Sum->Fill(h2016_div->GetBinContent(i));
        h2017Sum->Fill(h2017_div->GetBinContent(i));
        h2018Sum->Fill(h2018_div->GetBinContent(i));
      }
      for(int i = 1; i < h2016Sum->GetNbinsX() + 1; i++){
        h2016Sum->SetBinError(i, 0.);;
        h2017Sum->SetBinError(i, 0.);;
        h2018Sum->SetBinError(i, 0.);;
      }

      prepHists({h2016Sum, h2017Sum, h2018Sum}, false, false, false, {kRed, kAzure+6, 876});

      TString Mean2016 = TString(to_string(h2016Sum->GetMean()));
      TString Mean2017 = TString(to_string(h2017Sum->GetMean()));
      TString Mean2018 = TString(to_string(h2018Sum->GetMean()));
      std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{TF 2016 Mean: " + Mean2016 + "}{#splitline{TF 2017 Mean: " + Mean2017 + "}{TF 2018 Mean: " + Mean2018 + "}}", 0.20, 0.74); };

      auto legend = prepLegends({}, {""}, "l");
      appendLegends(legend, {h2016Sum}, {"TF 2016"}, "l");
      appendLegends(legend, {h2017Sum}, {"TF 2017"}, "l");
      appendLegends(legend, {h2018Sum}, {"TF 2018"}, "l");
      setLegend(legend, 1, 0.75, 0.75, 0.92,0.87);
      legend->SetTextSize(0.03);
      legend->SetY1NDC(legend->GetY2NDC() - 0.2);
      TCanvas* sum_c = drawCompMatt({h2016Sum, h2017Sum, h2018Sum}, legend, -1., &plotextra);
      gStyle->SetOptStat(0);
      float ymax = 1.25*std::max(h2016Sum->GetMaximum(), std::max(h2017Sum->GetMaximum(), h2018Sum->GetMaximum()));
      TLine *line_m = new TLine(0.9, 0, 0.9, ymax);
      TLine *line_p = new TLine(1.1, 0, 1.1, ymax);
      line_m->SetLineColor(kBlack);
      line_p->SetLineColor(kBlack);
      line_m->SetLineStyle(2);
      line_p->SetLineStyle(2);
      line_m->Draw();
      line_p->Draw();
      sum_c->Update();
      sum_c->SetTitle(outputBase);
      sum_c->Print(l.config.outputdir+"/"+outputBase+"_sum.pdf");
      sum_c->Print(l.config.outputdir+"/"+outputBase+"_sum.root");

      delete gROOT->FindObject("hTF_0");
      delete gROOT->FindObject("hTF_1");
      delete gROOT->FindObject("hTF_3");
    }
  }

  return l.yields.at("_pred");
}

void LLBPredSeparateRePlot(){

  TString region = "LLB/TransferFactor_devv7_081620";
  vector<TString> tf = {"_TF", "_TF_CR_to_SR_noextrap", "_TF_SR_extrap"};
  vector<TString> sep = {"", "_LM", "_HM_1", "_HM_2"};

  int start = 0, manualBins = 0;
  int max_graph = 3;
  int max_tf = 2;
  for(int j = 0; j <= max_graph; j++){
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
    for(int i = 0; i <= max_tf; i++){
      TFile *tfFile = TFile::Open(region+"/LostLepton"+tf[i]+"_Comparison"+sep[j]+".root");

      vector<TString> hNames = {"TF All00", "TF 201600", "TF 201700", "TF 201800"};
      if(i == 1 && j == 0) hNames = {"TF All10", "TF 201610", "TF 201710", "TF 201810"};
      if(i == 2 && j == 0) hNames = {"TF All20", "TF 201620", "TF 201720", "TF 201820"};
      if(i == 0 && j == 1) hNames = {"TF All01", "TF 201601", "TF 201701", "TF 201801"};
      if(i == 1 && j == 1) hNames = {"TF All11", "TF 201611", "TF 201711", "TF 201811"};
      if(i == 2 && j == 1) hNames = {"TF All21", "TF 201621", "TF 201721", "TF 201821"};
      if(i == 0 && j == 2) hNames = {"TF All02", "TF 201602", "TF 201702", "TF 201802"};
      if(i == 1 && j == 2) hNames = {"TF All12", "TF 201612", "TF 201712", "TF 201812"};
      if(i == 2 && j == 2) hNames = {"TF All22", "TF 201622", "TF 201722", "TF 201822"};
      if(i == 0 && j == 3) hNames = {"TF All03", "TF 201603", "TF 201703", "TF 201803"};
      if(i == 1 && j == 3) hNames = {"TF All13", "TF 201613", "TF 201713", "TF 201813"};
      if(i == 2 && j == 3) hNames = {"TF All23", "TF 201623", "TF 201723", "TF 201823"};

      TH1D* hAll  = convertToHist({(TH1*)tfFile->Get(hNames[0])},hNames[0], ";Search Region;Transfer Factor", nullptr, start, manualBins);
      TH1D* h2016 = convertToHist({(TH1*)tfFile->Get(hNames[1])},hNames[1],";Search Region;Transfer Factor", nullptr, start, manualBins);
      TH1D* h2017 = convertToHist({(TH1*)tfFile->Get(hNames[2])},hNames[2],";Search Region;Transfer Factor", nullptr, start, manualBins);
      TH1D* h2018 = convertToHist({(TH1*)tfFile->Get(hNames[3])},hNames[3],";Search Region;Transfer Factor", nullptr, start, manualBins);

      prepHists({hAll, h2016, h2017, h2018}, false, false, false, {kBlack, kRed, kAzure+6, 876});

      TH1* h2016_div = (TH1*)h2016->Clone();
      h2016_div->Divide(hAll);
      h2016_div->SetLineWidth(2);

      TH1* h2017_div = (TH1*)h2017->Clone();
      h2017_div->Divide(hAll);
      h2017_div->SetLineWidth(2);

      TH1* h2018_div = (TH1*)h2018->Clone();
      h2018_div->Divide(hAll);
      h2018_div->SetLineWidth(2);
      prepHists({h2016_div, h2017_div, h2018_div}, false, false, false, {kRed, kAzure+6, 876});

      auto leg = prepLegends({}, {""}, "l");
      appendLegends(leg, {hAll}, {"TF Run2"}, "l");
      appendLegends(leg, {h2016}, {"TF 2016"}, "l");
      appendLegends(leg, {h2017}, {"TF 2017"}, "l");
      appendLegends(leg, {h2018}, {"TF 2018"}, "l");
      leg->SetTextSize(0.03);
//        leg->SetNColumns(2);
      leg->SetY1NDC(leg->GetY2NDC() - 0.2);
      TCanvas* c = nullptr;
      if(i != 1) c = drawCompAndRatio({hAll, h2016, h2017, h2018}, {h2016_div, h2017_div, h2018_div}, leg, "TF_{era}/TF_{Run2}", 0.001, 2.999, true, 0.00001, 110);
      else       c = drawCompAndRatio({hAll, h2016, h2017, h2018}, {h2016_div, h2017_div, h2018_div}, leg, "TF_{era}/TF_{Run2}", 0.001, 2.999, true, 0.1, 110);
      TString outputBase = "LostLepton"+tf[i]+"_Comparison" + sep[j];
      c->SetTitle(outputBase);
      c->Print(region+"/"+outputBase+".pdf");
      c->Print(region+"/"+outputBase+".png");
      c->Print(region+"/"+outputBase+".C");

      TH1F* h2016Sum = new TH1F("hTF_0", ";TF_{era}/TF_{Run2};Search Regions", 41, -0.025, 2.025);
      TH1F* h2017Sum = new TH1F("hTF_1", ";TF_{era}/TF_{Run2};Search Regions", 41, -0.025, 2.025);
      TH1F* h2018Sum = new TH1F("hTF_3", ";TF_{era}/TF_{Run2};Search Regions", 41, -0.025, 2.025);
      for(int i = 1; i != h2016_div->GetNbinsX(); i++){
        h2016Sum->Fill(h2016_div->GetBinContent(i));
        h2017Sum->Fill(h2017_div->GetBinContent(i));
        h2018Sum->Fill(h2018_div->GetBinContent(i));
      }
      for(int i = 1; i < h2016Sum->GetNbinsX() + 1; i++){
        h2016Sum->SetBinError(i, 0.);;
        h2017Sum->SetBinError(i, 0.);;
        h2018Sum->SetBinError(i, 0.);;
      }

      prepHists({h2016Sum, h2017Sum, h2018Sum}, false, false, false, {kRed, kAzure+6, 876});

      h2016Sum->SetLineWidth(3);
      h2017Sum->SetLineWidth(3);
      h2018Sum->SetLineWidth(3);

      TString Mean2016 = TString(to_string(h2016Sum->GetMean()));
      TString Mean2017 = TString(to_string(h2017Sum->GetMean()));
      TString Mean2018 = TString(to_string(h2018Sum->GetMean()));
      std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{TF 2016 Mean: " + Mean2016 + "}{#splitline{TF 2017 Mean: " + Mean2017 + "}{TF 2018 Mean: " + Mean2018 + "}}", 0.215, 0.67, 0.028); };

      double stdDev = (h2016Sum->GetStdDev() + h2017Sum->GetStdDev() + h2018Sum->GetStdDev())/3;

      auto legend = prepLegends({}, {""}, "l");
      appendLegends(legend, {h2016Sum}, {"TF 2016"}, "l");
      appendLegends(legend, {h2017Sum}, {"TF 2017"}, "l");
      appendLegends(legend, {h2018Sum}, {"TF 2018"}, "l");
      setLegend(legend, 1, 0.75, 0.75, 0.92,0.87);
      legend->SetTextSize(0.03);
      legend->SetY1NDC(legend->GetY2NDC() - 0.2);
      TCanvas* sum_c = drawCompMatt({h2016Sum, h2017Sum, h2018Sum}, legend, -1., &plotextra);
      gStyle->SetOptStat(0);
      float ymax = 1.25*std::max(h2016Sum->GetMaximum(), std::max(h2017Sum->GetMaximum(), h2018Sum->GetMaximum()));
      TLine *line_m = new TLine(1. - stdDev, 0, 1. - stdDev, ymax);
      TLine *line_p = new TLine(1. + stdDev, 0, 1. + stdDev, ymax);
      line_m->SetLineColor(kBlack);
      line_p->SetLineColor(kBlack);
      line_m->SetLineStyle(2);
      line_p->SetLineStyle(2);
      line_m->Draw();
      line_p->Draw();
      sum_c->Update();
      sum_c->SetTitle(outputBase);
      sum_c->Print(region+"/"+outputBase+"_sum.pdf");
      sum_c->Print(region+"/"+outputBase+"_sum.png");
      sum_c->Print(region+"/"+outputBase+"_sum.root");

      delete gROOT->FindObject("hTF_0");
      delete gROOT->FindObject("hTF_1");
      delete gROOT->FindObject("hTF_3");
    }
  }
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

  TString region = ICHEPCR ? "lepcr_ichepcr" : "lepcr_devv7_081620";
  BaseEstimator z(config.outputdir+"/"+region);
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttx-2016", "ttx-2017", "ttx-2018",
				"polyboson-2016", "polyboson-2017", "polyboson-2018"};
  TString data_sample = "singlelep";

  vector<TString> systs = {"ISR_Weight_background", "JES", "PDF_Weight", "PU_Weight", "PowhegOverMG", "Prefire_Weight", "b", "eff_densetoptag", "eff_e", "eff_fatjet_veto", "eff_restoptag", "eff_tau", "eff_toptag", "eff_wtag", "err_mu", "ivfunc", "metres", "toppt", "trigger_err", "xsecNorm_ttbar", "xsecNorm_wjets"};

  int binNum = 0;
  int ix = 0;
  for (auto category : z.config.categories){
    TString location = "uncertainties_CR_Run2_071520";
    vector<TH1*> unc_up, unc_dn;
    unc_up.clear();
    unc_dn.clear();
    const auto &cat = z.config.crCatMaps.at(category);
    cout << cat.bin.plotbins.size() << endl;
    TString suffix = "";
    //for (auto s : systs){
    //  TString filename = location + "/" + s + ".root";
    //  TFile *p = TFile::Open(filename);
    //  assert(p);
    //  cout << filename << endl;
    //  unc_up.push_back(convertToHist({(TH1*)p->Get("ttbarplusw_Up")}, s + "up", ";MET_pt;Events", nullptr, true, binNum, binNum + cat.bin.plotbins.size()));
    //  unc_dn.push_back(convertToHist({(TH1*)p->Get("ttbarplusw_Down")}, s + "down", ";MET_pt;Events", nullptr, true, binNum, binNum + cat.bin.plotbins.size()));
    //}
    //const auto &cat = z.config.crCatMaps.at(category);
    auto cat_label = translateString(cat.label, plotLabelMap, "_", ", ", true);
    std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat_label, 0.2, 0.75); };
    //z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra, false, unc_up, unc_dn);
    z.plotDataMC(cat.bin, mc_samples, data_sample, cat, false, "", false, &plotextra);
    binNum += cat.bin.plotbins.size();
    ix++;
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
  config.addSample("ttW-sr",         "t#bar{t}W",           "ttW",             lepvetowgt, datasel + trigSR + vetoes);
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

void yieldsForAnna(){

  auto config = lepConfig();
  //config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              lepselwgt,      datasel + revert_vetoes);
  config.addSample("tW-2017",          "tW",            inputdir_2017+"tW",              lepselwgt_2017,      datasel + revert_vetoes);
  config.addSample("tW-2018",          "tW",            inputdir_2018+"tW",              lepselwgt_2018,      datasel + revert_vetoes);

  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["Total ttW"] = -3;

  z.calcYields();
  z.sumYields({"tW-2016", "tW-2017", "tW-2018"}, "Total ttW");
  auto htW_2016 = convertToHist(z.yields.at("tW-2016"),"tW 2016" ,";Control Region;Raw Yields for tW", nullptr);
  auto htW_2017 = convertToHist(z.yields.at("tW-2017"),"tW 2017" ,";Control Region;Raw Yields for tW", nullptr);
  auto htW_2018 = convertToHist(z.yields.at("tW-2018"),"tW 2018" ,";Control Region;Raw Yields for tW", nullptr);
  TFile *output = new TFile(config.outputdir+"/tW_yield_withWeight_forAnna.root", "RECREATE");
  htW_2016->Write();
  htW_2017->Write();
  htW_2018->Write();
  output->Close();

  //z.printYieldsTable({"tW-2016", "tW-2017", "tW-2018", "Total ttW"});
  //z.printYieldsTableLatex({"tW-2016", "tW-2017", "tW-2018", "Total ttW"}, labelMap, "yields_llb_hm_raw.tex", "hm", digits);

}

void yieldsForDataCheck(){

  auto config = srConfig();

  TString region = "DataCheck_devv7_081620";
  config.outputdir += "/" +region;
  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["data"] = -3;
  digits["data-v6p5"] = -3;

  z.calcYields();
  z.yields["v6p5Overv7"] = z.yields.at("data-v6p5")/z.yields.at("data");
  auto hLL = convertToHist(z.yields.at("data"),"Data" ,";Search Region;Yields", nullptr);
  auto httZ = convertToHist(z.yields.at("data-v6p5"),"Data v6p5" ,";Search Region;Yields", nullptr);
  auto httZOverLL = convertToHist(z.yields.at("v6p5Overv7"),"v6p5Overv7" ,";Search Region;Ratio", nullptr);
  prepHists({hLL, httZ, httZOverLL}, false, false, false, {kRed, kBlue, kBlue});

  auto leg = prepLegends({hLL, httZ}, {"Data v7", "Data v6p5"}, "L");
  TCanvas* c = drawCompAndRatio({hLL, httZ}, {httZOverLL}, leg, "N_{v6p5}/N_{v7}", 0.899, 1.101, true, 0.001);  
  TString outputBase = "DataCheck_080720";
  c->SetTitle(outputBase);
  c->Print(z.config.outputdir+"/"+outputBase+".pdf");
  c->Print(z.config.outputdir+"/"+outputBase+".C");

  TFile *output = new TFile(z.config.outputdir+"/"+outputBase+".root", "RECREATE");
  hLL->Write();
  httZ->Write();
  httZOverLL->Write();
  output->Close();
}
void yieldsForZhenbin(){

  auto config = lepConfig();
  //config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("ttbar-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",      datasel + revert_vetoes);
  config.addSample("wjets-2016",       "W+jets",        inputdir_2016+"wjets",           lepselwgt,      datasel + revert_vetoes);
  config.addSample("tW-2016",          "tW",            inputdir_2016+"tW",              lepselwgt,      datasel + revert_vetoes);
  config.addSample("ttW-2016",          "ttW",            inputdir_2016+"ttW",              lepselwgt,      datasel + revert_vetoes);
  config.addSample("ttbar-2017",         "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017,      datasel + revert_vetoes);
  config.addSample("wjets-2017",         "W+jets",        inputdir_2017+"wjets",           lepselwgt_2017,      datasel + revert_vetoes);
  config.addSample("tW-2017",            "tW",            inputdir_2017+"tW",              lepselwgt_2017,      datasel + revert_vetoes);
  config.addSample("ttW-2017",            "ttW",            inputdir_2017+"ttW",              lepselwgt_2017,      datasel + revert_vetoes);
  config.addSample("ttbar-2018",         "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018,      datasel + revert_vetoes);
  config.addSample("wjets-2018",         "W+jets",        inputdir_2018+"wjets",           lepselwgt_2018,      datasel + revert_vetoes);
  config.addSample("tW-2018",            "tW",            inputdir_2018+"tW",              lepselwgt_2018,      datasel + revert_vetoes);
  config.addSample("ttW-2018",            "ttW",            inputdir_2018+"ttW",              lepselwgt_2018,      datasel + revert_vetoes);

  //Rare processes
  config.addSample("ww-2016",    	"WW",               inputdir_2016+"ww",             lepselwgt,      datasel + revert_vetoes + invert_genLep);
  config.addSample("ww-2017",    	"WW",               inputdir_2017+"ww",             lepselwgt_2017, datasel + revert_vetoes + invert_genLep);
  config.addSample("ww-2018",    	"WW",               inputdir_2018+"ww",             lepselwgt_2018, datasel + revert_vetoes + invert_genLep);
  config.addSample("wz-2016",    	"wz",               inputdir_2016+"wz",             lepselwgt,      datasel + revert_vetoes + invert_genLep);
  config.addSample("wz-2017",    	"wz",               inputdir_2017+"wz",             lepselwgt_2017, datasel + revert_vetoes + invert_genLep);
  config.addSample("wz-2018",    	"wz",               inputdir_2018+"wz",             lepselwgt_2018, datasel + revert_vetoes + invert_genLep);
  config.addSample("zz-2016",    	"zz",               inputdir_2016+"zz",             lepselwgt,      datasel + revert_vetoes + invert_genLep);
  config.addSample("zz-2017",    	"zz",               inputdir_2017+"zz",             lepselwgt_2017, datasel + revert_vetoes + invert_genLep);
  config.addSample("zz-2018",    	"zz",               inputdir_2018+"zz",             lepselwgt_2018, datasel + revert_vetoes + invert_genLep);
  config.addSample("triboson-2016",     "VVV",              inputdir_2016+"vvv",            lepselwgt,      datasel + revert_vetoes + invert_genLep);
  config.addSample("triboson-2017",     "VVV",              inputdir_2017+"vvv",            lepselwgt_2017, datasel + revert_vetoes + invert_genLep);
  config.addSample("triboson-2018",     "VVV",              inputdir_2018+"vvv",            lepselwgt_2018, datasel + revert_vetoes + invert_genLep);
  config.addSample("ttX-2016",    	"ttX",              inputdir_2016+"ttX",            lepselwgt,      datasel + revert_vetoes + invert_genLep);
  config.addSample("ttX-2017",    	"ttX",              inputdir_2017+"ttX",            lepselwgt_2017, datasel + revert_vetoes + invert_genLep);
  config.addSample("ttX-2018",    	"ttX",              inputdir_2018+"ttX",            lepselwgt_2018, datasel + revert_vetoes + invert_genLep);

  TString region = "RareContamination_devv7_081620_newbin";
  config.outputdir += "/" +region;
  BaseEstimator z(config);

  std::map<TString,int> digits;
  digits["ttbarplusw"] = -3;
  digits["ttz"] = -3;
  digits["diboson"] = -3;

  z.calcYields();
  z.sumYields({"ttbar-2016", "ttbar-2017", "ttbar-2018"}, "ttbar");
  z.sumYields({"wjets-2016", "wjets-2017", "wjets-2018"}, "wjets");
  z.sumYields({"tW-2016", "tW-2017", "tW-2018"}, "tW");
  z.sumYields({"ww-2016", "ww-2017", "ww-2018"}, "ww");
  z.sumYields({"wz-2016", "wz-2017", "wz-2018"}, "wz");
  z.sumYields({"zz-2016", "zz-2017", "zz-2018"}, "zz");
  z.sumYields({"triboson-2016", "triboson-2017", "triboson-2018"}, "triboson");
  z.sumYields({"ttX-2016", "ttX-2017", "ttX-2018"}, "ttX");
  z.sumYields({"ttbar", "wjets", "tW", "ww", "wz", "zz", "triboson", "ttX"}, "ttbarplusw"); 
 
  z.yields["wwOverLL"] = z.yields.at("ww")/z.yields.at("ttbarplusw");
  z.yields["wzOverLL"] = z.yields.at("wz")/z.yields.at("ttbarplusw");
  z.yields["zzOverLL"] = z.yields.at("zz")/z.yields.at("ttbarplusw");
  z.yields["tribosonOverLL"] = z.yields.at("triboson")/z.yields.at("ttbarplusw");
  z.yields["ttXOverLL"] = z.yields.at("ttX")/z.yields.at("ttbarplusw");
  auto hLL = convertToHist(z.yields.at("ttbarplusw"),"Lost Lepton" ,";Control Region;Events", nullptr);
  auto hww = convertToHist(z.yields.at("ww"),"WW" ,";Control Region;Events", nullptr);
  auto hwz = convertToHist(z.yields.at("wz"),"WZ" ,";Control Region;Events", nullptr);
  auto hzz = convertToHist(z.yields.at("zz"),"ZZ" ,";Control Region;Events", nullptr);
  auto htriboson = convertToHist(z.yields.at("triboson"),"VVV" ,";Control Region;Events", nullptr);
  auto httX = convertToHist(z.yields.at("ttX"),"ttX" ,";Control Region;Events", nullptr);
  auto hwwOverLL = convertToHist(z.yields.at("wwOverLL"),"wwOverLL" ,";Control Region;Ratio", nullptr);
  auto hwzOverLL = convertToHist(z.yields.at("wzOverLL"),"wzOverLL" ,";Control Region;Ratio", nullptr);
  auto hzzOverLL = convertToHist(z.yields.at("zzOverLL"),"zzOverLL" ,";Control Region;Ratio", nullptr);
  auto htribosonOverLL = convertToHist(z.yields.at("tribosonOverLL"),"tribosonOverLL" ,";Control Region;Ratio", nullptr);
  auto httXOverLL = convertToHist(z.yields.at("ttXOverLL"),"ttXOverLL" ,";Control Region;Ratio", nullptr);
  prepHists({hLL, hww, hwz, hzz, htriboson, httX}, false, false, false);
  prepHists({hLL, hwwOverLL, hwzOverLL, hzzOverLL, htribosonOverLL, httXOverLL}, false, false, false);

  auto leg = prepLegends({hLL, hww, hwz, hzz, htriboson, httX}, {"ttbarplusw", "WW", "WZ", "ZZ", "VVV", "ttX"}, "L");
  TCanvas* c = drawCompAndRatio({hLL, hww, hwz, hzz, htriboson, httX}, {hwwOverLL, hwzOverLL, hzzOverLL, htribosonOverLL, httXOverLL}, leg, "N_{other}/N_{LL}", 0.000, 0.200, true, 0.001);  
  TString outputBase = "LostLepton_Rare_contribution";
  c->SetTitle(outputBase);
  c->Print(z.config.outputdir+"/"+outputBase+".pdf");
  c->Print(z.config.outputdir+"/"+outputBase+".C");

  TFile *output = new TFile(z.config.outputdir+"/"+outputBase+".root", "RECREATE");
  hLL->Write();
  hww->Write();
  hwz->Write();
  hzz->Write();
  htriboson->Write();
  httX->Write();
  hwwOverLL->Write();
  hwzOverLL->Write();
  hzzOverLL->Write();
  htribosonOverLL->Write();
  httXOverLL->Write();
  output->Close();
  
  //z.printYieldsTable({"ttZOverLL", "dibosonOverLL"});

}

void predYieldCheck(){

  auto config = lepConfig();

  TString region = "predictionYieldCheck_devv7_082020";
  config.outputdir += "/" +region;
  BaseEstimator z(config);
  vector<TString> TTZRare = {
				"polyboson-2016", "polyboson-2017", "polyboson-2018", "ttx-2016", "ttx-2017", "ttx-2018",
			    };

  z.calcYieldsExcludes(TTZRare);
  z.sumYields({"ttbar-2016", "ttbar-2017", "ttbar-2018"}, "ttbar");
  z.sumYields({"wjets-2016", "wjets-2017", "wjets-2018"}, "wjets");
  z.sumYields({"tW-2016", "tW-2017", "tW-2018"}, "tW");
  z.sumYields({"ttW-2016", "ttW-2017", "ttW-2018"}, "ttW");
  z.sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw-v6p5");
  z.sumYields({"ttZ-2016", "ttZ-2017", "ttZ-2018"}, "ttZ");
  z.sumYields({"diboson-2016", "diboson-2017", "diboson-2018"}, "diboson");
  Quantity::removeNegatives(z.yields.at("ttZ"));
  Quantity::removeNegatives(z.yields.at("diboson"));
  z.sumYields({"ttbar", "wjets", "tW", "ttW", "ttZ", "diboson"}, "ttbarplusw-v7");

  z.sumYields({"ttbar-2016-sr", "ttbar-2017-sr", "ttbar-2018-sr"}, "ttbar-sr");
  z.sumYields({"wjets-2016-sr", "wjets-2017-sr", "wjets-2018-sr"}, "wjets-sr");
  z.sumYields({"tW-2016-sr", "tW-2017-sr", "tW-2018-sr"}, "tW-sr");
  z.sumYields({"ttW-2016-sr", "ttW-2017-sr", "ttW-2018-sr"}, "ttW-sr");
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr-v6p5");
  z.sumYields({"ttZ-2016-sr", "ttZ-2017-sr", "ttZ-2018-sr"}, "ttZ-sr");
  z.sumYields({"diboson-2016-sr", "diboson-2017-sr", "diboson-2018-sr"}, "diboson-sr");
  Quantity::removeNegatives(z.yields.at("ttZ-sr"));
  Quantity::removeNegatives(z.yields.at("diboson-sr"));
  z.sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr", "diboson-sr", "ttZ-sr"}, "ttbarplusw-sr-v7");

  // _TF   = N(MC,SR)/N(MC,CR)
  // _pred = _TF * N(Data,CR)
  // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
  // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
  z.yields["_TF-v6p5"]     		    = z.yields.at("ttbarplusw-sr-v6p5")/z.yields.at("ttbarplusw-v6p5");
  z.yields["_pred-v6p5"]                 = z.yields.at("singlelep") * z.yields.at("_TF-v6p5");
  z.yields["_TF-v7"]     		    = z.yields.at("ttbarplusw-sr-v7")/z.yields.at("ttbarplusw-v7");
  z.yields["_pred-v7"]                 = z.yields.at("singlelep") * z.yields.at("_TF-v7");

  z.sumYields({"ttbar-2016-sr-int", "ttbar-2017-sr-int", "ttbar-2018-sr-int"}, "ttbar-sr-int");
  z.sumYields({"wjets-2016-sr-int", "wjets-2017-sr-int", "wjets-2018-sr-int"}, "wjets-sr-int");
  z.sumYields({"tW-2016-sr-int", "tW-2017-sr-int", "tW-2018-sr-int"}, "tW-sr-int");
  z.sumYields({"ttW-2016-sr-int", "ttW-2017-sr-int", "ttW-2018-sr-int"}, "ttW-sr-int");
  z.sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int-v6p5");
  z.sumYields({"ttZ-2016-sr-int", "ttZ-2017-sr-int", "ttZ-2018-sr-int"}, "ttZ-sr-int");
  z.sumYields({"diboson-2016-sr-int", "diboson-2017-sr-int", "diboson-2018-sr-int"}, "diboson-sr-int");
  Quantity::removeNegatives(z.yields.at("ttZ-sr-int"));
  Quantity::removeNegatives(z.yields.at("diboson-sr-int"));
  z.sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int", "ttZ-sr-int", "diboson-sr-int"}, "ttbarplusw-sr-int-v7");
  z.yields["_TF_CR_to_SR_noextrap-v6p5"] = z.yields.at("ttbarplusw-sr-int-v6p5")/z.yields.at("ttbarplusw-v6p5");
  z.yields["_TF_SR_extrap-v6p5"]         = z.yields.at("ttbarplusw-sr-v6p5")/z.yields.at("ttbarplusw-sr-int-v6p5");
  z.yields["_TF_CR_to_SR_noextrap-v7"] = z.yields.at("ttbarplusw-sr-int-v7")/z.yields.at("ttbarplusw-v7");
  z.yields["_TF_SR_extrap-v7"]         = z.yields.at("ttbarplusw-sr-v7")/z.yields.at("ttbarplusw-sr-int-v7");
 
  z.yields["ttbarplusw-ratio"] = z.yields.at("ttbarplusw-v7")/z.yields.at("ttbarplusw-v6p5");
  z.yields["ttbarplusw-sr-ratio"] = z.yields.at("ttbarplusw-sr-v7")/z.yields.at("ttbarplusw-sr-v6p5");
  z.yields["ttbarplusw-sr-int-ratio"] = z.yields.at("ttbarplusw-sr-int-v7")/z.yields.at("ttbarplusw-sr-int-v6p5");
  z.yields["_TF-ratio"] = z.yields.at("_TF-v7")/z.yields.at("_TF-v6p5");
  z.yields["_TF_CR_to_SR_noextrap-ratio"] = z.yields.at("_TF_CR_to_SR_noextrap-v7")/z.yields.at("_TF_CR_to_SR_noextrap-v6p5");
  z.yields["_TF_SR_extrap-ratio"] = z.yields.at("_TF_SR_extrap-v7")/z.yields.at("_TF_SR_extrap-v6p5");
  z.yields["_pred-ratio"] = z.yields.at("_pred-v7")/z.yields.at("_pred-v6p5");
  //v6p5
  auto httbarplusw_v6p5 = convertToHist(z.yields.at("ttbarplusw-v6p5"),"ttbarplusw-v6p5" ,";Search Region;Events", nullptr);
  auto httbarplusw_sr_v6p5 = convertToHist(z.yields.at("ttbarplusw-sr-v6p5"),"ttbarplusw-sr-v6p5" ,";Search Region;Events", nullptr);
  auto httbarplusw_sr_int_v6p5 = convertToHist(z.yields.at("ttbarplusw-sr-int-v6p5"),"ttbarplusw-sr-int-v6p5" ,";Search Region;Events", nullptr);
  auto h_TF_v6p5 = convertToHist(z.yields.at("_TF-v6p5"),"_TF-v6p5" ,";Search Region;Events", nullptr);
  auto h_TF_CR_to_SR_noextrap_v6p5 = convertToHist(z.yields.at("_TF_CR_to_SR_noextrap-v6p5"),"_TF_CR_to_SR_noextrap-v6p5" ,";Search Region;Events", nullptr);
  auto h_TF_SR_extrap_v6p5 = convertToHist(z.yields.at("_TF_SR_extrap-v6p5"),"_TF_SR_extrap-v6p5" ,";Search Region;Events", nullptr);
  auto h_pred_v6p5 = convertToHist(z.yields.at("_pred-v6p5"),"_pred-v6p5" ,";Search Region;Events", nullptr);
  //v7
  auto httbarplusw_v7 = convertToHist(z.yields.at("ttbarplusw-v7"),"ttbarplusw-v7" ,";Search Region;Events", nullptr);
  auto httbarplusw_sr_v7 = convertToHist(z.yields.at("ttbarplusw-sr-v7"),"ttbarplusw-sr-v7" ,";Search Region;Events", nullptr);
  auto httbarplusw_sr_int_v7 = convertToHist(z.yields.at("ttbarplusw-sr-int-v7"),"ttbarplusw-sr-int-v7" ,";Search Region;Events", nullptr);
  auto h_TF_v7 = convertToHist(z.yields.at("_TF-v7"),"_TF-v7" ,";Search Region;Events", nullptr);
  auto h_TF_CR_to_SR_noextrap_v7 = convertToHist(z.yields.at("_TF_CR_to_SR_noextrap-v7"),"_TF_CR_to_SR_noextrap-v7" ,";Search Region;Events", nullptr);
  auto h_TF_SR_extrap_v7 = convertToHist(z.yields.at("_TF_SR_extrap-v7"),"_TF_SR_extrap-v7" ,";Search Region;Events", nullptr);
  auto h_pred_v7 = convertToHist(z.yields.at("_pred-v7"),"_pred-v7" ,";Search Region;Events", nullptr);
  //ratio
  auto httbarplusw_ratio = convertToHist(z.yields.at("ttbarplusw-ratio"),"ttbarplusw-ratio" ,";Search Region;Events", nullptr);
  auto httbarplusw_sr_ratio = convertToHist(z.yields.at("ttbarplusw-sr-ratio"),"ttbarplusw-sr-ratio" ,";Search Region;Events", nullptr);
  auto httbarplusw_sr_int_ratio = convertToHist(z.yields.at("ttbarplusw-sr-int-ratio"),"ttbarplusw-sr-int-ratio" ,";Search Region;Events", nullptr);
  auto h_TF_ratio = convertToHist(z.yields.at("_TF-ratio"),"_TF-ratio" ,";Search Region;Events", nullptr);
  auto h_TF_CR_to_SR_noextrap_ratio = convertToHist(z.yields.at("_TF_CR_to_SR_noextrap-ratio"),"_TF_CR_to_SR_noextrap-ratio" ,";Search Region;Events", nullptr);
  auto h_TF_SR_extrap_ratio = convertToHist(z.yields.at("_TF_SR_extrap-ratio"),"_TF_SR_extrap-ratio" ,";Search Region;Events", nullptr);
  auto h_pred_ratio = convertToHist(z.yields.at("_pred-ratio"),"_pred-ratio" ,";Search Region;Events", nullptr);
  prepHists({httbarplusw_v6p5, httbarplusw_v7, httbarplusw_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({httbarplusw_sr_v6p5, httbarplusw_sr_v7, httbarplusw_sr_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({httbarplusw_sr_int_v6p5, httbarplusw_sr_int_v7, httbarplusw_sr_int_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_TF_v6p5, h_TF_v7, h_TF_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_TF_CR_to_SR_noextrap_v6p5, h_TF_CR_to_SR_noextrap_v7, h_TF_CR_to_SR_noextrap_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_TF_SR_extrap_v6p5, h_TF_SR_extrap_v7, h_TF_SR_extrap_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_pred_v6p5, h_pred_v7, h_pred_ratio}, false, false, false, {kBlue, kRed, kBlue});

  vector<TH1D*> v6p5  = {httbarplusw_v6p5, httbarplusw_sr_v6p5, httbarplusw_sr_int_v6p5, h_TF_v6p5, h_TF_CR_to_SR_noextrap_v6p5, h_TF_SR_extrap_v6p5, h_pred_v6p5};
  vector<TH1D*> v7    = {httbarplusw_v7, httbarplusw_sr_v7, httbarplusw_sr_int_v7, h_TF_v7, h_TF_CR_to_SR_noextrap_v7, h_TF_SR_extrap_v7, h_pred_v7};
  vector<TH1D*> ratio = {httbarplusw_ratio, httbarplusw_sr_ratio, httbarplusw_sr_int_ratio, h_TF_ratio, h_TF_CR_to_SR_noextrap_ratio, h_TF_SR_extrap_ratio, h_pred_ratio};
  vector<TString> label={"CR", "SR", "SR_noextrap", "TF", "TF_CR_to_SR_noextrap", "TF_SR_extrap", "Prediction"};
  vector<double> yMin = {1.,   0.01, 0.1,           0.001, 0.1,                   0.001,          0.001};
  vector<double> rMin = {0.8,  0.8,  0.8,         0.249, 0.499,                 0.499,          0.499};
  vector<double> rMax = {1.2,  1.8,  1.8,           1.3,   1.1,                   1.251,          1.251};

  for(unsigned iS = 0; iS != ratio.size(); iS++){
    auto leg = prepLegends({v6p5[iS], v7[iS]}, {label[iS] + " v6p5", label[iS] + " v7"}, "L");
    TCanvas* c = drawCompAndRatio({v6p5[iS], v7[iS]}, {ratio[iS]}, leg, "v6p5/v7", rMin[iS], rMax[iS], true, yMin[iS]);  
    TString outputBase = label[iS] + "_comparison";
    c->SetTitle(outputBase);
    c->Print(z.config.outputdir+"/"+outputBase+".pdf");
  }

  TFile *output = new TFile(z.config.outputdir+"/PredComp_v6p5_v7.root", "RECREATE");
  for(auto h : v6p5)  h->Write();
  for(auto h : v7)    h->Write();
  for(auto h : ratio) h->Write();
  output->Close();
  
  //z.printYieldsTable({"ttZOverLL", "dibosonOverLL"});

}

void formatPredYieldCheck(){

  TString outputdir = "LLB/predictionYieldCheck_devv7_082020";

  TFile *yield = TFile::Open("LLB/predictionYieldCheck_devv7_082020/PredComp_v6p5_v7.root");

  //v6p5
  TH1D* httbarplusw_v6p5 		= convertToHist({(TH1D*)yield->Get("ttbarplusw-v6p5")},"ttbarplusw-v6p5" ,";Search Region;Events", nullptr);
  TH1D* httbarplusw_sr_v6p5 		= convertToHist({(TH1D*)yield->Get("ttbarplusw-sr-v6p5")},"ttbarplusw-sr-v6p5" ,";Search Region;Events", nullptr);
  TH1D* httbarplusw_sr_int_v6p5 	= convertToHist({(TH1D*)yield->Get("ttbarplusw-sr-int-v6p5")},"ttbarplusw-sr-int-v6p5" ,";Search Region;Events", nullptr);
  TH1D* h_TF_v6p5 			= convertToHist({(TH1D*)yield->Get("_TF-v6p5")},"_TF-v6p5" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_TF_CR_to_SR_noextrap_v6p5 	= convertToHist({(TH1D*)yield->Get("_TF_CR_to_SR_noextrap-v6p5")},"_TF_CR_to_SR_noextrap-v6p5" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_TF_SR_extrap_v6p5 		= convertToHist({(TH1D*)yield->Get("_TF_SR_extrap-v6p5")},"_TF_SR_extrap-v6p5" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_pred_v6p5 			= convertToHist({(TH1D*)yield->Get("_pred-v6p5")},"_pred-v6p5" ,";Search Region;Events", nullptr);
  //v7
  TH1D* httbarplusw_v7 			= convertToHist({(TH1D*)yield->Get("ttbarplusw-v7")},"ttbarplusw-v7" ,";Search Region;Events", nullptr);
  TH1D* httbarplusw_sr_v7 		= convertToHist({(TH1D*)yield->Get("ttbarplusw-sr-v7")},"ttbarplusw-sr-v7" ,";Search Region;Events", nullptr);
  TH1D* httbarplusw_sr_int_v7 		= convertToHist({(TH1D*)yield->Get("ttbarplusw-sr-int-v7")},"ttbarplusw-sr-int-v7" ,";Search Region;Events", nullptr);
  TH1D* h_TF_v7 			= convertToHist({(TH1D*)yield->Get("_TF-v7")},"_TF-v7" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_TF_CR_to_SR_noextrap_v7 	= convertToHist({(TH1D*)yield->Get("_TF_CR_to_SR_noextrap-v7")},"_TF_CR_to_SR_noextrap-v7" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_TF_SR_extrap_v7 		= convertToHist({(TH1D*)yield->Get("_TF_SR_extrap-v7")},"_TF_SR_extrap-v7" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_pred_v7 			= convertToHist({(TH1D*)yield->Get("_pred-v7")},"_pred-v7" ,";Search Region;Events", nullptr);
  //ratio
  TH1D* httbarplusw_ratio 		= convertToHist({(TH1D*)yield->Get("ttbarplusw-ratio")},"ttbarplusw-ratio" ,";Search Region;Events", nullptr);
  TH1D* httbarplusw_sr_ratio 		= convertToHist({(TH1D*)yield->Get("ttbarplusw-sr-ratio")},"ttbarplusw-sr-ratio" ,";Search Region;Events", nullptr);
  TH1D* httbarplusw_sr_int_ratio 	= convertToHist({(TH1D*)yield->Get("ttbarplusw-sr-int-ratio")},"ttbarplusw-sr-int-ratio" ,";Search Region;Events", nullptr);
  TH1D* h_TF_ratio 			= convertToHist({(TH1D*)yield->Get("_TF-ratio")},"_TF-ratio" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_TF_CR_to_SR_noextrap_ratio 	= convertToHist({(TH1D*)yield->Get("_TF_CR_to_SR_noextrap-ratio")},"_TF_CR_to_SR_noextrap-ratio" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_TF_SR_extrap_ratio 		= convertToHist({(TH1D*)yield->Get("_TF_SR_extrap-ratio")},"_TF_SR_extrap-ratio" ,";Search Region;Transfer Factor", nullptr);
  TH1D* h_pred_ratio 			= convertToHist({(TH1D*)yield->Get("_pred-ratio")},"_pred-ratio" ,";Search Region;Events", nullptr);
  prepHists({httbarplusw_v6p5, httbarplusw_v7, httbarplusw_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({httbarplusw_sr_v6p5, httbarplusw_sr_v7, httbarplusw_sr_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({httbarplusw_sr_int_v6p5, httbarplusw_sr_int_v7, httbarplusw_sr_int_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_TF_v6p5, h_TF_v7, h_TF_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_TF_CR_to_SR_noextrap_v6p5, h_TF_CR_to_SR_noextrap_v7, h_TF_CR_to_SR_noextrap_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_TF_SR_extrap_v6p5, h_TF_SR_extrap_v7, h_TF_SR_extrap_ratio}, false, false, false, {kBlue, kRed, kBlue});
  prepHists({h_pred_v6p5, h_pred_v7, h_pred_ratio}, false, false, false, {kBlue, kRed, kBlue});

  vector<TH1D*> v6p5  = {httbarplusw_v6p5, httbarplusw_sr_v6p5, httbarplusw_sr_int_v6p5, h_TF_v6p5, h_TF_CR_to_SR_noextrap_v6p5, h_TF_SR_extrap_v6p5, h_pred_v6p5};
  vector<TH1D*> v7    = {httbarplusw_v7, httbarplusw_sr_v7, httbarplusw_sr_int_v7, h_TF_v7, h_TF_CR_to_SR_noextrap_v7, h_TF_SR_extrap_v7, h_pred_v7};
  vector<TH1D*> ratio = {httbarplusw_ratio, httbarplusw_sr_ratio, httbarplusw_sr_int_ratio, h_TF_ratio, h_TF_CR_to_SR_noextrap_ratio, h_TF_SR_extrap_ratio, h_pred_ratio};
  vector<TString> label={"CR", "SR", "SR noExtrap", "TF", "TF(CR-noextrap)", "TF(SR-extrap)", "Prediction"};
  vector<double> yMin = {1.,   0.01, 0.1,           0.0001, 0.100,                   0.001,          0.001};
  vector<double> rMin = {0.9,  0.8,  0.8,           0.799, 0.799,                   0.799,          0.799};
  vector<double> rMax = {1.2,  1.8,  1.3,           1.501, 1.201,                   1.251,          1.501};

  for(unsigned iS = 0; iS != ratio.size(); iS++){
    auto leg = prepLegends({v6p5[iS], v7[iS]}, {label[iS] + " Orig.", label[iS] + " Rare"}, "L");
    TCanvas* c = drawCompAndRatio({v6p5[iS], v7[iS]}, {ratio[iS]}, leg, "Rare/Original", rMin[iS], rMax[iS], true, yMin[iS]);  
    TString outputBase = label[iS] + "_comparison";
    c->SetTitle(outputBase);
    c->Print(outputdir+"/"+outputBase+".pdf");
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SBv4Yields(){

  auto config = lepConfig();
  config.crCatMaps.clear();

  config.samples.clear();
  config.addSample("ttbar-sr",       "t#bar{t}",      inputdir_2016+"ttbar",        "1.0", datasel + vetoes);
  config.addSample("wjets-sr",       "W+jets",        inputdir_2016+"wjets",        "1.0", datasel + vetoes);
  config.addSample("tW-sr",          "tW",            inputdir_2016+"tW",           "1.0", datasel + vetoes);
  config.addSample("ttW-sr",         "t#bar{t}W",           inputdir_2016+"ttW",          "1.0", datasel + vetoes);
  config.addSample("ttZ-sr",         "ttZ",           inputdir_2016+"ttZ",          "1.0", datasel + vetoes);
  config.addSample("qcd-sr",         "QCD",           inputdir_2016+"qcd",    	    "1.0", datasel + vetoes);
  config.addSample("znunu-sr",       "znunu",         inputdir_2016+"znunu",        "1.0", datasel + vetoes);
  config.addSample("ttbar-v2-sr",       "t#bar{t}",      inputdir_2016+"../nanoaod_all_skim_2016_082619/ttbar",        "1.0", datasel + vetoes);
  config.addSample("wjets-v2-sr",       "W+jets",        inputdir_2016+"../nanoaod_all_skim_2016_082619/wjets",        "1.0", datasel + vetoes);
  config.addSample("tW-v2-sr",          "tW",            inputdir_2016+"../nanoaod_all_skim_2016_082619/tW",           "1.0", datasel + vetoes);
  config.addSample("ttW-v2-sr",         "t#bar{t}W",           inputdir_2016+"../nanoaod_all_skim_2016_082619/ttW",          "1.0", datasel + vetoes);
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
  config.addSample("ttW",         "t#bar{t}W",           "ttW",             		lepselwgt, datasel + trigLepCR + lepcrsel);
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
void plotAK8SFSyst(){
  auto config = lepConfig();
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  config.sel = baseline;
  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString ak8_veto_up = "*Stop0l_DeepAK8_SFWeight_veto_up/Stop0l_DeepAK8_SFWeight";
  TString ak8_veto_dn = "*Stop0l_DeepAK8_SFWeight_veto_dn/Stop0l_DeepAK8_SFWeight";
  TString ak8_top_up = "*Stop0l_DeepAK8_SFWeight_top_up/Stop0l_DeepAK8_SFWeight";
  TString ak8_top_dn = "*Stop0l_DeepAK8_SFWeight_top_dn/Stop0l_DeepAK8_SFWeight";
  TString ak8_w_up = "*Stop0l_DeepAK8_SFWeight_w_up/Stop0l_DeepAK8_SFWeight";
  TString ak8_w_dn = "*Stop0l_DeepAK8_SFWeight_w_dn/Stop0l_DeepAK8_SFWeight";

  TString region = "lepcr_AK8SF_051520";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  config.addSample("ttbar-nominal-2016", "t#bar{t}",    inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-veto-Up-2016", "t#bar{t}",    inputdir_2016+"ttbar",           lepselwgt+ak8_veto_up+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-veto-Down-2016", "t#bar{t}",  inputdir_2016+"ttbar",           lepselwgt+ak8_veto_dn+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-top-Up-2016", "t#bar{t}",     inputdir_2016+"ttbar",           lepselwgt+ak8_top_up+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-top-Down-2016", "t#bar{t}",   inputdir_2016+"ttbar",           lepselwgt+ak8_top_dn+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-w-Up-2016", "t#bar{t}",       inputdir_2016+"ttbar",           lepselwgt+ak8_w_up+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-w-Down-2016", "t#bar{t}",     inputdir_2016+"ttbar",           lepselwgt+ak8_w_dn+"*ISRWeight",       datasel + revert_vetoes);

  vector< TString > mc_samples_veto = {"ttbar-nominal-2016", "ttbar-veto-Up-2016", "ttbar-veto-Down-2016"};
  vector< TString > mc_samples_top  = {"ttbar-nominal-2016", "ttbar-top-Up-2016", "ttbar-top-Down-2016"};
  vector< TString > mc_samples_w    = {"ttbar-nominal-2016", "ttbar-w-Up-2016", "ttbar-w-Down-2016"};

  map<TString, BinInfo> varDict {
	{"ak8_genpart",      BinInfo("FatJet_nGenPart", "N(AK8 GenPart)",  11, -0.5, 10.5)},
  };

  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    z.resetSelection();
    lumistr = lumistr_2016;
    z.setSelection(LLCR_LM, "llcr_lm_2016_veto", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2016 Low #Deltam LLCR}{veto Up/Down}", 0.2, 0.75); };
    cout << "Made it here 1" << endl;
    //z.plotComp(var.second, mc_samples_veto, Category::dummy_category(), true, false, 0.001, plotextra)
    z.plotDataMC(var.second, mc_samples_veto, "", Category::dummy_category(), false, "", true, &plotextra);
    cout << "Made it here 2" << endl;
    z.setSelection(LLCR_HM, "llcr_hm_2016_veto", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_veto, "", Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2016;
    z.setSelection(LLCR_LM, "llcr_lm_2016_top", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2016 Low #Deltam LLCR}{top Up/Down}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_top, "", Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2016_top", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_top, "", Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2016;
    z.setSelection(LLCR_LM, "llcr_lm_2016_w", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2016 Low #Deltam LLCR}{w Up/Down}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_w, "", Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2016_w", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("2016 LLCR HM", 0.2, 0.72); };
    z.plotDataMC(var.second, mc_samples_w, "", Category::dummy_category(), false, "", true, &plotextra);
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ExtrapStudies(){
  auto config = lepConfig();
  config.catMaps = lepCatMap();
  TString topAK8Full = "*Stop0l_topAK8Weight";
  TString toppt_mgpow = "*Stop0l_topptWeight";

  LOG_YMIN = 0.1;

  config.addSample("ttbar-topptmgpow-2016", "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+toppt_mgpow+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-topptmgpow-2017", "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+toppt_mgpow,      	        datasel + revert_vetoes);
  config.addSample("ttbar-topptmgpow-2018", "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+toppt_mgpow,               datasel + revert_vetoes);
  config.addSample("ttbar-topAK8Full-2016", "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topAK8Full+"*ISRWeight",        datasel + revert_vetoes);
  config.addSample("ttbar-topAK8Full-2017", "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topAK8Full,      	        datasel + revert_vetoes);
  config.addSample("ttbar-topAK8Full-2018", "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topAK8Full,                datasel + revert_vetoes);

  TString region = "ExtrapolationStudy_toppt_050520";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_samples_2017 = {"ttbar-2017", "wjets-2017", "tW-2017", "ttW-2017"};
  vector<TString> mc_samples_2018 = {"ttbar-2018", "wjets-2018", "tW-2018", "ttW-2018"};
  vector<TString> mc_toppt_mgpow_samples = {"ttbar-topptmgpow-2016", "ttbar-topptmgpow-2017", "ttbar-topptmgpow-2018", "wjets-2016", "wjets-2017", "wjets-2018",
		     			    "tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_toppt_mgpow_samples_2016 = {"ttbar-topptmgpow-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_toppt_mgpow_samples_2017 = {"ttbar-topptmgpow-2017", "wjets-2017", "tW-2017", "ttW-2017"};
  vector<TString> mc_toppt_mgpow_samples_2018 = {"ttbar-topptmgpow-2018", "wjets-2018", "tW-2018", "ttW-2018"};
  vector<TString> mc_topAK8Full_samples = {"ttbar-topAK8Full-2016", "ttbar-topAK8Full-2017", "ttbar-topAK8Full-2018", "wjets-2016", "wjets-2017", "wjets-2018",
		      			   "tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_topAK8Full_samples_2016 = {"ttbar-topAK8Full-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_topAK8Full_samples_2017 = {"ttbar-topAK8Full-2017", "wjets-2017", "tW-2017", "ttW-2017"};
  vector<TString> mc_topAK8Full_samples_2018 = {"ttbar-topAK8Full-2018", "wjets-2018", "tW-2018", "ttW-2018"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017 = "singlelep-2017";
  TString data_sample_2018 = "singlelep-2018";

  map<TString, BinInfo> varDict {
	{"ntop",        BinInfo("Stop0l_nTop", "N_{t}", 4, -0.5, 3.5)},
	//{"nrestop",     BinInfo("Stop0l_nResolved", "N_{rest}", 4, -0.5, 3.5)},
	{"nw",          BinInfo("Stop0l_nW", "N_{W}", 4, -0.5, 3.5)},
	{"met",         BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"ak8jet",      BinInfo("FatJet_pt[0]", "p_{T}(ak8) [GeV]",  12, 200, 800)},
  };

  vector<pair<TString, pair<double, double>>> ratioFitValues;
  std::function<void(TCanvas*)> plotextra;
  vector<TH1*> ratiohist;
  TString suffix = "";
  for (auto &var : varDict){
    for (auto category : z.config.categories){
      ratiohist.clear();
      z.resetSelection();
      const auto &cat = z.config.crCatMaps.at(category);
      auto cat_label = translateString(cat.label, plotLabelMap, "_", ", ", true);
      std::function<void(TCanvas*)> plotextra = [&](TCanvas *c){ c->cd(); drawTLatexNDC(cat_label, 0.2, 0.75); };
      lumistr = "137.00079";
      z.setSelection(cat.cut, "_Run2"+suffix, "_Run2"+suffix);
      ratiohist.push_back(z.plotDataMC(var.second, mc_samples, data_sample, cat, false, "", true, &plotextra));

      lumistr = "137.00079";
      z.setSelection(cat.cut, "_Run2_topAK8Full"+suffix, "_Run2_topAK8Full"+suffix);
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 Top AK8 Full}{" + cat_label + "}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_topAK8Full_samples, data_sample, cat, false, "", true, &plotextra));

      lumistr = "137.00079";
      z.setSelection(cat.cut, "_Run2_toppt_mgpow"+suffix, "_Run2_toppt_mgpow"+suffix);
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 Top p_{T} + Pow/MG}{" + cat_label + "}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_toppt_mgpow_samples, data_sample, cat, false, "", true, &plotextra));

      prepHists(ratiohist, false, false, false, {kBlack, kRed, kAzure+6});

      for(auto *hr : ratiohist){
        hr->Fit("pol1");
        TF1 *ratioFit = (TF1*)hr->GetFunction("pol1");
        cout << hr->GetName() << ": " << ratioFit->GetParameter(1) << endl;
        ratioFitValues.push_back(make_pair(hr->GetName(), make_pair(ratioFit->GetParameter(1), ratioFit->GetParameter(0))));
        hr->GetYaxis()->SetTitle("Data/MC");
      }

      auto leg = prepLegends(ratiohist, {"No Top Weight", "Top AK8 Full", "Top p_{T}+Pow/MG"}, "L");
      auto c = drawComp(ratiohist, leg);
      c->SetCanvasSize(800, 600);
      gStyle->SetOptStat(0);
      TString basename = z.config.outputdir+"/"+region+"/"+ var.first + "_" + cat.name + suffix;
      c->Print(basename+".pdf");
      c->Print(basename +".C");

      TFile *output = new TFile(basename + ".root", "RECREATE");
      for (auto *h : ratiohist) h->Write();
      output->Close();
    }
  }

  for(unsigned iR = 0; iR < ratioFitValues.size(); iR++){
    cout << ratioFitValues[iR].first << ": " << ratioFitValues[iR].second.first << "*x + " << ratioFitValues[iR].second.second << endl;
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusive(){
  auto config = lepConfig();
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  TString LLCR    = "Pass_LLCR";
  TString noTopPt = "/Stop0l_topptWeight";
  config.sel = baseline;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  // qcdsr
  config.addSample("qcd-2016",         "QCD",           inputdir_2016+"qcd",       qcdwgt,         datasel + revert_vetoes);
  config.addSample("qcd-2017",  "QCD",           inputdir_2017+"qcd",              qcdwgt_2017,    datasel + revert_vetoes);
  config.addSample("qcd-2018",   "QCD",           inputdir_2018+"qcd",             qcdwgt_2018,    datasel + revert_vetoes);
  // Znunu
  config.addSample("znunu-2016",       "Z#rightarrow#nu#bar{#nu}",         inputdir_2016+"znunu",        lepselwgt,       datasel + revert_vetoes);
  config.addSample("znunu-2017",       "Z#rightarrow#nu#bar{#nu}",         inputdir_2017+"znunu",        lepselwgt_2017,  datasel + revert_vetoes);
  config.addSample("znunu-2018",       "Z#rightarrow#nu#bar{#nu}",         inputdir_2018+"znunu",        lepselwgt_2018,  datasel + revert_vetoes);
  //// diboson
  //config.addSample("diboson-2016",       "Diboson",         inputdir_2016+"diboson",        lepselwgt,       datasel + revert_vetoes);
  //config.addSample("diboson-2017",       "Diboson",         inputdir_2017+"diboson",        lepselwgt_2017,  datasel + revert_vetoes);
  //config.addSample("diboson-2018",       "Diboson",         inputdir_2018+"diboson",        lepselwgt_2018,  datasel + revert_vetoes);
  //// ttZ
  //config.addSample("ttZ-2016",       "ttZ",         inputdir_2016+"ttZ",        lepselwgt,       datasel + revert_vetoes);
  //config.addSample("ttZ-2017",       "ttZ",         inputdir_2017+"ttZ",        lepselwgt_2017,  datasel + revert_vetoes);
  //config.addSample("ttZ-2018",       "ttZ",         inputdir_2018+"ttZ",        lepselwgt_2018,  datasel + revert_vetoes);

  config.addSample("ttbar-notoppt-2016",      "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+noTopPt+"*ISRWeight",         datasel + revert_vetoes);
  config.addSample("ttbar-notoppt-2017",      "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+noTopPt,        	        datasel + revert_vetoes);
  config.addSample("ttbar-notoppt-2018",      "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+noTopPt,                 datasel + revert_vetoes);

  TString region = "lepcr_inclusive_devv7_081620";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> mc_samples_ISR = {
				"ttbar-notoppt-2016", "ttbar-notoppt-2017", "ttbar-notoppt-2018",
				"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018",
				};
  vector<TString> mc_samples_ttbar_ISR = {
				"ttbar-notoppt-2016", "ttbar-notoppt-2017", "ttbar-notoppt-2018",
				"ttbar-2016", "ttbar-2017", "ttbar-2018",
				};
  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttx-2016", "ttx-2017", "ttx-2018",
				"polyboson-2016", "polyboson-2017", "polyboson-2018"};
  vector<TString> mc_samples_purity = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				       "tW-2016", "tW-2017", "tW-2018", "ttx-2016", "ttx-2017", "ttx-2018",
				       "polyboson-2016", "polyboson-2017", "polyboson-2018",
				       "qcd-2016", "qcd-2017", "qcd-2018", "znunu-2016", "znunu-2017", "znunu-2018"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttx-2016", "polyboson-2016"};
  vector<TString> mc_samples_2017 = {"ttbar-2017", "wjets-2017", "tW-2017", "ttx-2017", "polyboson-2017"};
  vector<TString> mc_samples_2018 = {"ttbar-2018", "wjets-2018", "tW-2018", "ttx-2018", "polyboson-2018"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017 = "singlelep-2017";
  TString data_sample_2018 = "singlelep-2018";

  map<TString, BinInfo> varDict {
	{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"met_phi",       BinInfo("MET_phi", "#slash{E}_{T} #phi", 64, -3.2, 3.2)},
	//{"ht",       BinInfo("Stop0l_HT", "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"toppt",      BinInfo("FatJet_TopPt", "p_{T}(top) [GeV]", 12, 400, 1000)},
	//{"ak8jet",      BinInfo("FatJet_pt[0]", "p_{T}(ak8) [GeV]", 16, 0, 800)},
        //{"ptb12",       BinInfo("Stop0l_Ptb", "p_{T}(b_{1})+p_{T}(b_{2}) [GeV]", 8, 40, 200)},
        //{"ptlepbmet",     BinInfo("Stop0l_PtLepMetB", "p_{T}(l,b,#slash{E}_{T}) [GeV]", 32, 0, 800)},
	//{"nivf",         BinInfo("Stop0l_nSoftb", "N_{SV}", 5, -0.5, 4.5)},
	//{"ntop",        BinInfo("Stop0l_nTop", "N_{t}", 4, -0.5, 3.5)},
	//{"nrestop",     BinInfo("Stop0l_nResolved", "N_{t}", 4, -0.5, 3.5)},
	//{"nw",          BinInfo("Stop0l_nW", "N_{W}", 4, -0.5, 3.5)},
	//{"softbsf",     BinInfo("SoftBSF", "SoftBSF", 100, 0.5, 1.5)},
	//{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
	//{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
	//{"nisr",        BinInfo("nISRJets",  "N_{ISR}", 8, 2.5, 10.5)},
  };

  std::function<void(TCanvas*)> plotextra;
  bool norm = true;
  TString suffix = norm ? "_norm" : "";
  TString extra = norm ? "Normalized" : "";
  for (auto &var : varDict){
    z.resetSelection();
    if (var.first.Contains("nisr")){
      z.setSelection(LLCR_LM, "llcr_lm_syst" + suffix, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{#splitline{Run 2 Low #Deltam}{LL control region}}{" + extra + "}", 0.2, 0.73); };
      z.plotDataMC(var.second, mc_samples_ISR, "", Category::dummy_category(), norm, "", true, &plotextra, false, {}, {}, true);
      z.setSelection(LLCR_LM, "llcr_lm_syst_ttbar" + suffix, "");
      z.plotDataMC(var.second, mc_samples_ttbar_ISR, "", Category::dummy_category(), norm, "", true, &plotextra, false, {}, {}, true);
      z.setSelection(LLCR_HM, "llcr_hm_syst" + suffix, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{#splitline{Run 2 High #Deltam}{LL control region}}{" + extra + "}", 0.2, 0.73); };
      z.plotDataMC(var.second, mc_samples_ISR, "", Category::dummy_category(), norm, "", true, &plotextra, false, {}, {}, true);
      z.setSelection(LLCR_HM, "llcr_hm_syst_ttbar" + suffix, "");
      z.plotDataMC(var.second, mc_samples_ttbar_ISR, "", Category::dummy_category(), norm, "", true, &plotextra, false, {}, {}, true);
    } else{
      z.setSelection(LLCR , "llcr", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run 2}{LL control region}", 0.2, 0.75); };
      z.plotDataMC(var.second, mc_samples_purity, data_sample, Category::dummy_category(), false, "", true, &plotextra);
      z.setSelection(LLCR_LM , "llcr_lm", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run 2 Low #Deltam}{LL control region}", 0.2, 0.75); };
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);
      z.setSelection(LLCR_HM, "llcr_hm", "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run 2 High #Deltam}{LL control region}", 0.2, 0.75); };
      z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);
    }

    lumistr = lumistr_2016;
    z.setSelection(LLCR_LM , "llcr_lm_2016", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2016 Low #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2016", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2016 High #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_2016, data_sample_2016, Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2017;
    z.setSelection(LLCR_LM , "llcr_lm_2017", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2017 Low #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_2017, data_sample_2017, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2017", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2017 High #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_2017, data_sample_2017, Category::dummy_category(), false, "", true, &plotextra);

    lumistr = lumistr_2018PostHEM;
    z.setSelection(LLCR_LM , "llcr_lm_2018", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 Low #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_2018, data_sample_2018, Category::dummy_category(), false, "", true, &plotextra);
    z.setSelection(LLCR_HM, "llcr_hm_2018", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{2018 High #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples_2018, data_sample_2018, Category::dummy_category(), false, "", true, &plotextra);
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void plot1LepInclusiveLepton(){
  auto config = lepConfig();
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  //config.samples.clear();
  config.sel = baseline;
  //ttbar electron
  config.addSample("ttbarplusw-ttbar-electron-2016",   "electron",       inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-ttbar-electron-2017",   "electron",       inputdir_2017+"ttbar",           lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-ttbar-electron-2018",   "electron",       inputdir_2018+"ttbar",           lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-wjets-electron-2016",   "electron",       inputdir_2016+"wjets",           lepselwgt,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-wjets-electron-2017",   "electron",       inputdir_2017+"wjets",           lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-wjets-electron-2018",   "electron",       inputdir_2018+"wjets",           lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-tW-electron-2016",      "electron",       inputdir_2016+"tW",              lepselwgt,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-tW-electron-2017",      "electron",       inputdir_2017+"tW",              lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-tW-electron-2018",      "electron",       inputdir_2018+"tW",              lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-ttW-electron-2016",     "electron",       inputdir_2016+"ttW",             lepselwgt,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-ttW-electron-2017",     "electron",       inputdir_2017+"ttW",             lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  config.addSample("ttbarplusw-ttW-electron-2018",     "electron",       inputdir_2018+"ttW",             lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoElectron == 1");
  //ttbar muon
  config.addSample("ttbarplusw-ttbar-muon-2016",       "muon",           inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-ttbar-muon-2017",       "muon",           inputdir_2017+"ttbar",           lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-ttbar-muon-2018",       "muon",           inputdir_2018+"ttbar",           lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-wjets-muon-2016",       "muon",           inputdir_2016+"wjets",           lepselwgt,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-wjets-muon-2017",       "muon",           inputdir_2017+"wjets",           lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-wjets-muon-2018",       "muon",           inputdir_2018+"wjets",           lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-tW-muon-2016",          "muon",           inputdir_2016+"tW",              lepselwgt,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-tW-muon-2017",          "muon",           inputdir_2017+"tW",              lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-tW-muon-2018",          "muon",           inputdir_2018+"tW",              lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-ttW-muon-2016",         "muon",           inputdir_2016+"ttW",             lepselwgt,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-ttW-muon-2017",         "muon",           inputdir_2017+"ttW",             lepselwgt_2017,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");
  config.addSample("ttbarplusw-ttW-muon-2018",         "muon",           inputdir_2018+"ttW",             lepselwgt_2018,      datasel + revert_vetoes + " && Stop0l_nVetoMuon == 1");

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  TString region = "lepcr_inclusive_sepLeptons_v6_070720";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbarplusw-ttbar-electron-2016", "ttbarplusw-ttbar-electron-2017", "ttbarplusw-ttbar-electron-2018", "ttbarplusw-wjets-electron-2016", "ttbarplusw-wjets-electron-2017", "ttbarplusw-wjets-electron-2018",
				"ttbarplusw-tW-electron-2016", "ttbarplusw-tW-electron-2017", "ttbarplusw-tW-electron-2018", "ttbarplusw-ttW-electron-2016", "ttbarplusw-ttW-electron-2017", "ttbarplusw-ttW-electron-2018",
				"ttbarplusw-ttbar-muon-2016", "ttbarplusw-ttbar-muon-2017", "ttbarplusw-ttbar-muon-2018", "ttbarplusw-wjets-muon-2016", "ttbarplusw-wjets-muon-2017", "ttbarplusw-wjets-muon-2018",
				"ttbarplusw-tW-muon-2016", "ttbarplusw-tW-muon-2017", "ttbarplusw-tW-muon-2018", "ttbarplusw-ttW-muon-2016", "ttbarplusw-ttW-muon-2017", "ttbarplusw-ttW-muon-2018"};
  TString data_sample = "singlelep";

  map<TString, BinInfo> varDict {
	{"met",       BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	{"ht",       BinInfo("Stop0l_HT", "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	{"toppt",      BinInfo("FatJet_TopPt", "p_{T}(top) [GeV]", 12, 400, 1000)},
	{"ak8jet",      BinInfo("FatJet_pt[0]", "p_{T}(ak8) [GeV]", 16, 0, 800)},
        {"ptb12",       BinInfo("Stop0l_Ptb", "p_{T}(b_{1})+p_{T}(b_{2}) [GeV]", 8, 40, 200)},
        //{"ptlepbmet",     BinInfo("Stop0l_PtLepMetB", "p_{T}(l,b,#slash{E}_{T}) [GeV]", 32, 0, 800)},
	{"nivf",         BinInfo("Stop0l_nSoftb", "N_{SV}", 5, -0.5, 4.5)},
	{"ntop",        BinInfo("Stop0l_nTop", "N_{t}", 4, -0.5, 3.5)},
	{"nrestop",     BinInfo("Stop0l_nResolved", "N_{t}", 4, -0.5, 3.5)},
	{"nw",          BinInfo("Stop0l_nW", "N_{W}", 4, -0.5, 3.5)},
	//{"softbsf",     BinInfo("SoftBSF", "SoftBSF", 100, 0.5, 1.5)},
	//{"j1pt",      BinInfo("Jet_pt[0]", "p_{T}(j1)", vector<int>{30, 50, 100, 200, 400, 1000}, "GeV")},
	{"nbjets",    BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 5, -0.5, 4.5)},
  };

  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    z.resetSelection();
    z.setSelection(LLCR_LM , "llcr_lm", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run 2 Low #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra, false, {}, {}, true);
    z.setSelection(LLCR_HM, "llcr_hm", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run 2 High #Deltam}{LL control region}", 0.2, 0.75); };
    z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra, false, {}, {}, true);
  }
}

void plotMtb(){
  TDR_EXTRA_LABEL_ = "Simulation";
  TDR_EXTRA_LABEL_2 = "Supplementary";
  TDR_EXTRA_LABEL_3 = "arXiv: XXXX.XXXXX";
  auto config = lepConfig();
  TString mtb = "Pass_Baseline && Pass_dPhiMETHighDM && Stop0l_Mtb > 0 && Stop0l_Mtb < 350";
  config.sel = baseline;

  LOG_YMIN = 100.;
  PLOT_MAX_YSCALE = 1.2;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  config.samples.clear();
  config.addSample("ttbarplusw-ttbar-2016",         "t#bar{t} + single t",      inputdir_2016+"ttbar",           lepselwgt+"*ISRWeight",      datasel);
  config.addSample("ttbarplusw-ttbar-2017",         "t#bar{t} + single t",      inputdir_2017+"ttbar",           lepselwgt_2017,      datasel);
  config.addSample("ttbarplusw-ttbar-2018",         "t#bar{t} + single t",      inputdir_2018+"ttbar",           lepselwgt_2018,      datasel);
  config.addSample("ttbarplusw-tW-2016",            "t#bar{t} + single t",            inputdir_2016+"tW",              lepselwgt,      datasel);
  config.addSample("ttbarplusw-tW-2017",            "t#bar{t} + single t",            inputdir_2017+"tW",              lepselwgt_2017,      datasel);
  config.addSample("ttbarplusw-tW-2018",            "t#bar{t} + single t",            inputdir_2018+"tW",              lepselwgt_2018,      datasel);
  config.addSample("ttbarplusw-ttW-2016",           "t#bar{t} + single t",           inputdir_2016+"ttW",             lepselwgt,      datasel);
  config.addSample("ttbarplusw-ttW-2017",           "t#bar{t} + single t",           inputdir_2017+"ttW",             lepselwgt_2017,      datasel);
  config.addSample("ttbarplusw-ttW-2018",           "t#bar{t} + single t",           inputdir_2018+"ttW",             lepselwgt_2018,      datasel);
  config.addSample("ttbarplusw-ttZ-2016",           "t#bar{t} + single t",           inputdir_2016+"ttZ",             lepselwgt,      datasel);
  config.addSample("ttbarplusw-ttZ-2017",           "t#bar{t} + single t",           inputdir_2017+"ttZ",             lepselwgt_2017,      datasel);
  config.addSample("ttbarplusw-ttZ-2018",           "t#bar{t} + single t",           inputdir_2018+"ttZ",             lepselwgt_2018,      datasel);
  // W+jets
  config.addSample("wjets-2016",         "W+jets",        inputdir_2016+"wjets",           lepselwgt,      datasel);
  config.addSample("wjets-2017",         "W+jets",        inputdir_2017+"wjets",           lepselwgt_2017,      datasel);
  config.addSample("wjets-2018",         "W+jets",        inputdir_2018+"wjets",           lepselwgt_2018,      datasel);
  // qcdsr
  config.addSample("qcd-2016",         "QCD",           inputdir_2016+"qcd",       qcdwgt,         datasel);
  config.addSample("qcd-2017",  "QCD",           inputdir_2017+"qcd",              qcdwgt_2017,    datasel);
  config.addSample("qcd-2018",   "QCD",           inputdir_2018+"qcd",             qcdwgt_2018,    datasel);
  // Znunu
  config.addSample("znunu-2016",       "Z#rightarrow#nu#bar{#nu}",         inputdir_2016+"znunu",        lepselwgt,  datasel);
  config.addSample("znunu-2017",       "Z#rightarrow#nu#bar{#nu}",         inputdir_2017+"znunu",        lepselwgt_2017,  datasel);
  config.addSample("znunu-2018",       "Z#rightarrow#nu#bar{#nu}",         inputdir_2018+"znunu",        lepselwgt_2018,  datasel);
  //signal
  config.addSample("T1tttt-1200-800",  "T1tttt(1200, 800)",  inputdir_sig_2017+"SMS_T1tttt_mGluino1200_mLSP800",  "1.0", datasel);
  config.addSample("T1tttt-2000-100",  "T1tttt(2000, 100)",  inputdir_sig_2017+"SMS_T1tttt_mGluino2000_mLSP100",  "1.0", datasel);
  config.addSample("T2tt-500-325",     "T2tt(500, 325)",     inputdir_sig_2016+"SMS_T2tt_mStop_500_mLSP_325",  "1.0", datasel);
  config.addSample("T2tt-850-100",     "T2tt(850, 100)",     inputdir_sig_2017+"SMS_T2tt_mStop_850_mLSP_100",  "1.0", datasel);
  config.addSample("T2ttC-650-600",    "T2ttC(650, 600)",     inputdir_sig_2017+"SMS_T2fbd_mStop650_mLSP600",  "1.0", datasel);

  TString region = "lepcr_inclusive_devv7_083120_suplementary";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

//  vector<TString> mc_samples = {
//				"ttbarplusw-ttbar-2016", "ttbarplusw-ttbar-2017", "ttbarplusw-ttbar-2018",
//				"ttbarplusw-tW-2016", "ttbarplusw-tW-2017", "ttbarplusw-tW-2018",
//				"ttbarplusw-ttW-2016", "ttbarplusw-ttW-2017", "ttbarplusw-ttW-2018",
//				"ttbarplusw-ttZ-2016", "ttbarplusw-ttZ-2017", "ttbarplusw-ttZ-2018",
//				"wjets-2016", "wjets-2017", "wjets-2018",
//				"znunu-2016", "znunu-2017", "znunu-2018",
//				"qcd-2016", "qcd-2017", "qcd-2018",
//				};
  vector<TString> mc_samples = {
				"qcd-2016", "qcd-2017", "qcd-2018",
				"znunu-2016", "znunu-2017", "znunu-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"ttbarplusw-ttbar-2016", "ttbarplusw-ttbar-2017", "ttbarplusw-ttbar-2018",
				"ttbarplusw-tW-2016", "ttbarplusw-tW-2017", "ttbarplusw-tW-2018",
				"ttbarplusw-ttW-2016", "ttbarplusw-ttW-2017", "ttbarplusw-ttW-2018",
				"ttbarplusw-ttZ-2016", "ttbarplusw-ttZ-2017", "ttbarplusw-ttZ-2018",
				};
  vector<TString> sig_samples = {"T2ttC-650-600", "T1tttt-2000-100", "T2tt-500-325", "T2tt-850-100"};

  map<TString, BinInfo> varDict {
	{"mtb",      BinInfo("Stop0l_Mtb", "m_{T}^{b} [GeV]", 35, 0, 350)},
	//{"met",         	BinInfo("MET_pt", "p^{miss}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
  };

  vector<TH1*> ratiohist;
  std::function<void(TCanvas*)> plotextra;
  for (auto &var : varDict){
    //z.resetSelection();
    z.setSelection(mtb, "baseline", "");
    plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Signal scaled}{to bkg sum}", 0.715, 0.65); };
    z.plotSigVsBkg(var.second, mc_samples, sig_samples, Category::dummy_category(), true, false, true, &plotextra, false);
    //z.plotSigVsBkg(var.second, mc_samples, sig_samples, Category::dummy_category(), true, true, true, &plotextra, false);
  }
}

void plot1LepInclusiveWithSyst(){
  auto config = lepConfig();
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  TString LLCR_LM = "Stop0l_ISRJetPt>300 && Stop0l_Mtb < 175 && Stop0l_nTop==0 && Stop0l_nW==0 && Stop0l_nResolved==0 && Stop0l_METSig>10 && Pass_dPhiMETLowDM";
  TString noTopPt = "/Stop0l_topptWeight";
  config.sel = baseline;
  lumistr = "137.00079";

  TDR_EXTRA_LABEL_ = "";
  TDR_EXTRA_LABEL_2 = "";

  LOG_YMIN = 1.;
  //RATIO_YMIN = 0.499;
  //RATIO_YMAX = 1.501;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  //Adding separated Rare/ttZ contribution

  config.addSample("ttbar-notoppt-2016",      "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+noTopPt+"*ISRWeight",         datasel + revert_vetoes);
  config.addSample("ttbar-notoppt-2017",      "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+noTopPt,        	        datasel + revert_vetoes);
  config.addSample("ttbar-notoppt-2018",      "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+noTopPt,                 datasel + revert_vetoes);

  TString region = "lepcr_inclusive_withSyst_devv7_122120";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> mc_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttx-2016", "ttx-2017", "ttx-2018",
				"polyboson-2016", "polyboson-2017", "polyboson-2018"};
  vector<TString> mc_samples_notoppt = {"ttbar-notoppt-2016", "ttbar-notoppt-2017", "ttbar-notoppt-2018", "wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018",
				"polyboson-2016", "polyboson-2017", "polyboson-2018", "ttZ-2016", "ttZ-2017", "ttZ-2018"};
  TString data_sample = "singlelep";

  map<TString, BinInfo> varDict {
	//{"toppt_nowgt", 	BinInfo("FatJet_TopPt", "p_{T}(top) [GeV]", 12, 400, 1000)},
	//{"toppt",       	BinInfo("FatJet_TopPt", "p_{T}(top) [GeV]", 12, 400, 1000)},
	//{"ntop",        	BinInfo("Stop0l_nTop", "N_{t}", 3, -0.5, 2.5)},
	//{"ntop_nowgt",  	BinInfo("Stop0l_nTop", "N_{t}", 3, -0.5, 2.5)},
	//{"nrestop",     	BinInfo("Stop0l_nResolved", "N_{res}", 3, -0.5, 2.5)},
	//{"nrestop_nowgt",     	BinInfo("Stop0l_nResolved", "N_{res}", 3, -0.5, 2.5)},
	{"nw",          	BinInfo("Stop0l_nW", "N_{W}", 3, -0.5, 2.5)},
	//{"nw_nowgt",    	BinInfo("Stop0l_nW", "N_{W}", 3, -0.5, 2.5)},
	//{"met",         	BinInfo("MET_pt", "p^{miss}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"met_nowgt",         	BinInfo("MET_pt", "p^{miss}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"ht",       		BinInfo("Stop0l_HT", "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"ht_nowgt",       	BinInfo("Stop0l_HT", "H_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"nb",        		BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 4, 0.5, 4.5)},
	//{"nb_nowgt",  		BinInfo("Stop0l_nbtags",  "N_{B}^{medium}", 4, 0.5, 4.5)},

  };
  vector<pair<TString, TString>> systFile = {
				make_pair("met",   "uncertainties_CRInclusive_Run2_080520_MET"),
				make_pair("ntop",  "uncertainties_CRInclusive_Run2_080520_top"),
				make_pair("nw",    "uncertainties_CRInclusive_Run2_080520_w"),
				make_pair("nrestop","uncertainties_CRInclusive_Run2_080520_res"),
				//make_pair("toppt", "uncertainties_CRInclusive_Run2_080520_toppt"),
				//make_pair("ht",    "uncertainties_CRInclusive_Run2_080520_ht"),
				//make_pair("nb",    "uncertainties_CRInclusive_Run2_080520_btag"),
				};

  vector<TString> systs = {"ISR_Weight_background", "JES", "PDF_Weight", "PU_Weight", "PowhegOverMG", "Prefire_Weight", "b_light", "b_heavy", "eff_densetoptag", "eff_e", "eff_fatjet_veto", "eff_restoptag", "eff_tau", "eff_toptag", "eff_wtag", "err_mu", "ivfunc", "metres", "toppt", "trigger_err", "xsecNorm_ttbar", "xsecNorm_wjets"};
  systs = {"eff_wtag"};

  std::function<void(TCanvas*)> plotextra;
  TString location = "";
  vector<TH1*> ratiohist;
  for (unsigned i = 0; i < 1; i++){
    for (auto &var : varDict){
      vector<TH1*> unc_up, unc_dn;
      unc_up.clear();
      unc_dn.clear();
      TString suffix = "";
      for (auto s : systs){
        TString whichVar = var.first;
        //whichVar.ReplaceAll("_nowgt", "");
        for ( vector < pair<TString, TString> >::const_iterator it = systFile.begin() ; it != systFile.end(); it++)
          if (whichVar == it->first) location = it->second;

        if (i == 0 && !var.first.Contains("toppt")) suffix = "_norm";
        else if (var.first == "toppt") suffix = "_withtoppt";
        if (var.first.Contains("nowgt") && (s.Contains("PowhegOverMG") || s.Contains("toppt"))) continue;
        if (suffix.Contains("norm") && s.Contains("xsecNorm")) continue;

        TString filename = location + "/" + s + ".root";
        TFile *p = TFile::Open(filename);
        assert(p);
        cout << filename << endl;
        unc_up.push_back(convertToHist({(TH1*)p->Get(s + "_Up")}, s + "up", ";"+var.first+";Events", nullptr));
        unc_dn.push_back(convertToHist({(TH1*)p->Get(s + "_Down")}, s + "down", ";"+var.first+";Events", nullptr));
        //p->Close();
      }
      if (var.first.Contains("nowgt")) suffix += "_notoppt";
      z.resetSelection();
      //Make final plot with stat + syst
      z.setSelection(LLCR_HM, "llcr_hm_syst_onlyWtag" + suffix, "");
      if (var.first.Contains("_nowgt") && suffix.Contains("norm")){
        plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{#splitline{High #Deltam}{LL control region}}{No Top p_{T} Weight}", 0.2, 0.77, 0.035); };
        ratiohist.push_back(z.plotDataMC(var.second, mc_samples_notoppt, data_sample, Category::dummy_category(), true, "", true, &plotextra, false, unc_up, unc_dn));
      } else if (!var.first.Contains("toppt") && suffix.Contains("norm")){
        plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{High #Deltam}{LL control region}", 0.2, 0.79, 0.035); };
        z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), true, "", true, &plotextra, false, unc_up, unc_dn);
      } else if (var.first.Contains("_nowgt")){
        plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{#splitline{High #Deltam}{LL control region}}{No Top p_{T} Weight}", 0.2, 0.77, 0.035); };
        ratiohist.push_back(z.plotDataMC(var.second, mc_samples_notoppt, data_sample, Category::dummy_category(), false, "", true, &plotextra, false, unc_up, unc_dn));
      } else {
        plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{High #Deltam}{LL control region}", 0.2, 0.79, 0.035); };
        ratiohist.push_back(z.plotDataMC(var.second, mc_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra, false, unc_up, unc_dn));
      }
    }
  }

  TFile *output = new TFile(config.outputdir+"/"+region + "/DataOverMC_inclusive.root", "RECREATE");
  for (auto *h : ratiohist) h->Write();
  output->Close();

}

void topPtSyst(){
  vector<float> up = {1.077, 1.05, 1.02, 0.982, 0.959, 0.942, 0.925, 0.891, 0.846};
  vector<float> dn = {1.016,   1, 0.976, 0.936, 0.914, 0.884, 0.857, 0.801, 0.712};
  vector<float> nom= {1.05022035, 1.02429032, 0.9990005, 0.9622317, 0.93847412, 0.91530311, 0.8927042, 0.8491665, 0.78780869};
  Float_t bins[] = {25, 75, 125, 200, 250, 300, 350, 450, 600, 800};

  TH1F* hup = new TH1F("topPt_up", "topPt_up", 9, bins);
  TH1F* hdn = new TH1F("topPt_dn", "topPt_dn", 9, bins);

  for(unsigned i = 0; i != up.size(); i++){
    hup->SetBinContent(i+1, up[i]/nom[i]);
    hdn->SetBinContent(i+1, dn[i]/nom[i]);
  }

  TFile *output = new TFile("LostLepton_topPt_systematics.root", "RECREATE");
  hup->Write();
  hdn->Write();
  output->Close();
}

void plot1LepTTbarMatch(){
  auto config = lepConfig();
  TString LLCR_HM = "Stop0l_nJets>=5 && Stop0l_nbtags>=1 && Pass_dPhiMETHighDM";
  TString LLCR_TopPT = "Stop0l_nJets>=4 && Stop0l_nbtags>=2 && Pass_dPhiMETHighDM";
  // new weights
  TString ttbartopPTwgt = "*(Stop0l_topAK8Weight*(FatJet_GenMatch[0] == 1) + 1*(FatJet_GenMatch[0] != 1))";
  TString topAK8 = ttbartopPTwgt;
  TString topAK8Full = "*Stop0l_topAK8Weight";
  TString toppt  = "*Stop0l_topptOnly";
  TString topmgpow = "*Stop0l_topMGPowWeight";
  TString toppt_mgpow = "*Stop0l_topptWeight";
  TString topptlepmetb = "*Stop0l_topPtLepBMetWeight";

  config.sel = baseline;
  LOG_YMIN = 1.;

  config.categories.push_back("dummy");
  config.catMaps["dummy"] = Category::dummy_category();

  config.addSample("ttbar-toppt-2016",      "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+toppt+"*ISRWeight",             datasel + revert_vetoes);
  config.addSample("ttbar-toppt-2017",      "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+toppt,      	        datasel + revert_vetoes);
  config.addSample("ttbar-toppt-2018",      "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+toppt,                     datasel + revert_vetoes);
  config.addSample("ttbar-topptmgpow-2016", "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+toppt_mgpow+"*ISRWeight",       datasel + revert_vetoes);
  config.addSample("ttbar-topptmgpow-2017", "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+toppt_mgpow,      	        datasel + revert_vetoes);
  config.addSample("ttbar-topptmgpow-2018", "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+toppt_mgpow,               datasel + revert_vetoes);
  config.addSample("ttbar-topAK8-2016",     "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topAK8+"*ISRWeight",            datasel + revert_vetoes);
  config.addSample("ttbar-topAK8-2017",     "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topAK8,      	        datasel + revert_vetoes);
  config.addSample("ttbar-topAK8-2018",     "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topAK8,                    datasel + revert_vetoes);
  config.addSample("ttbar-topAK8Full-2016", "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topAK8Full+"*ISRWeight",        datasel + revert_vetoes);
  config.addSample("ttbar-topAK8Full-2017", "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topAK8Full,      	        datasel + revert_vetoes);
  config.addSample("ttbar-topAK8Full-2018", "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topAK8Full,                datasel + revert_vetoes);
  config.addSample("ttbar-mgpow-2016",      "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topmgpow+"*ISRWeight",          datasel + revert_vetoes);
  config.addSample("ttbar-mgpow-2017",      "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topmgpow,      	        datasel + revert_vetoes);
  config.addSample("ttbar-mgpow-2018",      "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topmgpow,                  datasel + revert_vetoes);
  config.addSample("ttbar-ptlepmetb-2016",  "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topptlepmetb+"*ISRWeight",      datasel + revert_vetoes);
  config.addSample("ttbar-ptlepmetb-2017",  "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topptlepmetb,      	datasel + revert_vetoes);
  config.addSample("ttbar-ptlepmetb-2018",  "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topptlepmetb,              datasel + revert_vetoes);
  // Adding samples with different gentop matched to FatJet
  config.addSample("ttbar-topmatch-2016",       "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topAK8+"*ISRWeight",      datasel + revert_vetoes + " && FatJet_GenMatch[0] == 1");
  config.addSample("ttbar-topmatch-2017",       "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topAK8,      	datasel + revert_vetoes + " && FatJet_GenMatch[0] == 1");
  config.addSample("ttbar-topmatch-2018",       "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topAK8,              datasel + revert_vetoes + " && FatJet_GenMatch[0] == 1");
  config.addSample("ttbar-wmatch-2016",         "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topAK8+"*ISRWeight",      datasel + revert_vetoes + " && FatJet_GenMatch[0] == 2");
  config.addSample("ttbar-wmatch-2017",         "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topAK8,      	datasel + revert_vetoes + " && FatJet_GenMatch[0] == 2");
  config.addSample("ttbar-wmatch-2018",         "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topAK8,              datasel + revert_vetoes + " && FatJet_GenMatch[0] == 2");
  config.addSample("ttbar-fake-2016",           "t#bar{t}",      inputdir_2016+"ttbar",           lepselwgt+topAK8+"*ISRWeight",      datasel + revert_vetoes + " && FatJet_GenMatch[0] == 0");
  config.addSample("ttbar-fake-2017",           "t#bar{t}",      inputdir_2017+"ttbar",           lepselwgt_2017+topAK8,      	datasel + revert_vetoes + " && FatJet_GenMatch[0] == 0");
  config.addSample("ttbar-fake-2018",           "t#bar{t}",      inputdir_2018+"ttbar",           lepselwgt_2018+topAK8,              datasel + revert_vetoes + " && FatJet_GenMatch[0] == 0");

  TString region = "lepcr_inclusive_v6_toppt_matching_043020";
  BaseEstimator z(config.outputdir+"/"+region);
  config.plotFormat = "pdf";
  z.setConfig(config);

  vector<TString> mc_toppt_mgpow_samples = {"ttbar-topptmgpow-2016", "ttbar-topptmgpow-2017", "ttbar-topptmgpow-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_toppt_samples = {"ttbar-toppt-2016", "ttbar-toppt-2017", "ttbar-toppt-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_topAK8_samples = {"ttbar-topAK8-2016", "ttbar-topAK8-2017", "ttbar-topAK8-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_topAK8Full_samples = {"ttbar-topAK8Full-2016", "ttbar-topAK8Full-2017", "ttbar-topAK8Full-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_orig_samples = {"ttbar-2016", "ttbar-2017", "ttbar-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_mgpow_samples = {"ttbar-mgpow-2016", "ttbar-mgpow-2017", "ttbar-mgpow-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_ptlepmetb_samples = {"ttbar-ptlepmetb-2016", "ttbar-ptlepmetb-2017", "ttbar-ptlepmetb-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018",
				"ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_match_samples = {"ttbar-topmatch-2016", "ttbar-topmatch-2017", "ttbar-topmatch-2018",
                                "ttbar-wmatch-2016", "ttbar-wmatch-2017", "ttbar-wmatch-2018",
				"ttbar-fake-2016", "ttbar-fake-2017", "ttbar-fake-2018",
				"wjets-2016", "wjets-2017", "wjets-2018",
				"tW-2016", "tW-2017", "tW-2018", "ttW-2016", "ttW-2017", "ttW-2018"};
  vector<TString> mc_samples_2016 = {"ttbar-2016", "wjets-2016", "tW-2016", "ttW-2016"};
  vector<TString> mc_samples_2017 = {"ttbar-2017", "wjets-2017", "tW-2017", "ttW-2017"};
  vector<TString> mc_samples_2018 = {"ttbar-2018", "wjets-2018", "tW-2018", "ttW-2018"};
  TString data_sample = "singlelep";
  TString data_sample_2016 = "singlelep-2016";
  TString data_sample_2017 = "singlelep-2017";
  TString data_sample_2018 = "singlelep-2018";

  map<TString, BinInfo> varDict {
	//{"met",         BinInfo("MET_pt", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
	//{"ak8jet",      BinInfo("FatJet_pt[0]", "p_{T}(ak8) [GeV]",  20, 0, 1000)},
	{"ak8jet2",      BinInfo("FatJet_pt[1]", "p_{T}(ak8) [GeV]",  20, 0, 1000)},
	//{"ntop",        BinInfo("Stop0l_nTop", "N_{t}", 4, -0.5, 3.5)},
	//{"nrestop",     BinInfo("Stop0l_nResolved", "N_{rest}", 4, -0.5, 3.5)},
	//{"nw",          BinInfo("Stop0l_nW", "N_{W}", 4, -0.5, 3.5)},
        //{"ptlepmetb",   BinInfo("Stop0l_PtLepMetB", "p_{T}(l,b,#slash{E}_{T}) [GeV]", 40, 0, 1000)},
        //{"njets",       BinInfo("Stop0l_nJets", "N_{j}", 8, 2.5, 10.5)},
  };

  vector <pair <TString, pair <TString, TString> > >   mtb_bins = {
                                                                            make_pair("",           make_pair("1 == 1",                  "")),
      //                                                                      make_pair("_lowmtb",           make_pair("Stop0l_Mtb < 175",                  "M_{T}(b_{1,2},#vec{p}_{T}^{miss}) < 175")),
      //                                                                      make_pair("_highmtb",          make_pair("Stop0l_Mtb => 175",                 "M_{T}(b_{1,2},#vec{p}_{T}^{miss}) #geq 175"))
                                                                          };

  vector<pair<TString, pair<double, double>>> ratioFitValues;
  std::function<void(TCanvas*)> plotextra;
  for(unsigned iB = 0; iB < mtb_bins.size(); iB++){
    vector<TH1*> ratiohist;
    for (auto &var : varDict){
      ratiohist.clear();
      z.resetSelection();
      //orig
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_orig" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{No Top Weight}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_orig_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //mgpow
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_mgpow" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top Pow/MG}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_mgpow_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //toppt
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_toppt" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top p_{T}}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_toppt_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //toppt and mgpow
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_toppt_mgpow" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top p_{T} + Pow/MG}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_toppt_mgpow_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //topAK8
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_topAK8" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top AK8 Matching}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_topAK8_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //topAK8Full
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_topAK8Full" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top AK8 Full}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_topAK8Full_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //ptlepmetb
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_ptlepmetb" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top p_{T}(l,b,#slash{E}_{T}) Weight}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      ratiohist.push_back(z.plotDataMC(var.second, mc_ptlepmetb_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra));
      //top GenMatching
      z.setSelection(LLCR_HM + " && " + mtb_bins[iB].second.first, "llcr_hm_top_matching" + mtb_bins[iB].first, "");
      plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC("#splitline{Run2 LLCR HM}{#splitline{Top AK8 Gen Matching}{" + mtb_bins[iB].second.second + "}}", 0.2, 0.75); };
      z.plotDataMC(var.second, mc_match_samples, data_sample, Category::dummy_category(), false, "", true, &plotextra);

      prepHists(ratiohist, false, false, false, {kBlack, kRed, kAzure+6, 876, kOrange-3, kGreen+3, kBlue});

      for(auto *hr : ratiohist){
        hr->Fit("pol1");
        TF1 *ratioFit = (TF1*)hr->GetFunction("pol1");
        cout << hr->GetName() << ": " << ratioFit->GetParameter(1) << endl;
        ratioFitValues.push_back(make_pair(hr->GetName(), make_pair(ratioFit->GetParameter(1), ratioFit->GetParameter(0))));
        hr->GetYaxis()->SetTitle("Data/MC");
      }

      auto leg = prepLegends(ratiohist, {"No Top Weight", "Top Pow/MG", "Top p_{T}", "Top p_{T}+Pow/MG", "Top AK8 Match", "Top AK8 Full", "Top p_{T}(l,b,#slash{E}_{T})"}, "L");
      auto c = drawComp(ratiohist, leg);
      c->SetCanvasSize(800, 600);
      gStyle->SetOptStat(0);
      TString basename = z.config.outputdir+"/"+region+"/LostLepton_HM_weight_" + var.first + mtb_bins[iB].first;
      c->Print(basename+".pdf");
      c->Print(basename +".C");

      TFile *output = new TFile(basename + ".root", "RECREATE");
      for (auto *h : ratiohist) h->Write();
      output->Close();
    }
  }

  for(unsigned iR = 0; iR < ratioFitValues.size(); iR++){
    cout << ratioFitValues[iR].first << ": " << ratioFitValues[iR].second.first << "*x + " << ratioFitValues[iR].second.second << endl;
  }
}
