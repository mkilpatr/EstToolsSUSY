#ifndef ESTTOOLS_MINITOOLS_HH_
#define ESTTOOLS_MINITOOLS_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <vector>
#include <map>
#include <set>
#include "TTreeFormula.h"
#include "TRegexp.h"

#include "Style.hh"
#include "QuantityAsymmErrors.h"
#include "Config.h"

using namespace std;
#endif

namespace EstTools{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename Number>
std::string toString(Number value, int precision = 2, bool setFixed = true){
  std::stringstream ss;
  if (setFixed) ss << fixed;
  ss << setprecision(precision) << value;
  return ss.str();
}

TString filterString(TString instr){
  return instr.ReplaceAll(" ", "").ReplaceAll(",", "_").ReplaceAll("/", "_over_").ReplaceAll("*", "_times_").ReplaceAll("(", "_").ReplaceAll(")", "_");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TString joinString(const vector<TString>& vec, TString delimiter){
  TString rlt = "";
  for (unsigned i=0; i<vec.size(); ++i){
    if (i==0){
      rlt = vec.at(i);
    }else{
      rlt = rlt + delimiter + vec.at(i);
    }
  }
  return rlt;
}

TString joinStringSplit(const vector<TString>& vec_1, const vector<TString>& vec_2, const vector<TString>& vec_3, const vector<TString>& vec_4, TString delimiter){
  TString rlt = "", rlt_1 = "", rlt_2 = "", rlt_3 = "", rlt_4 = "";
  for (unsigned i=0; i<vec_1.size(); ++i){
    if (i==0){
      rlt_1 = vec_1.at(i);
    }else{
      rlt_1 = rlt_1 + delimiter + vec_1.at(i);
    }
  }
  for (unsigned i=0; i<vec_2.size(); ++i){
    if (i==0){
      rlt_2 = vec_2.at(i);
    }else{
      rlt_2 = rlt_2 + delimiter + vec_2.at(i);
    }
  }
  for (unsigned i=0; i<vec_3.size(); ++i){
    if (i==0){
      rlt_3 = vec_3.at(i);
    }else{
      rlt_3 = rlt_3 + delimiter + vec_3.at(i);
    }
  }
  for (unsigned i=0; i<vec_4.size(); ++i){
    if (i==0){
      rlt_4 = vec_4.at(i);
    }else{
      rlt_4 = rlt_4 + delimiter + vec_4.at(i);
    }
  }

  rlt = "#splitline{" + rlt_1 + "}{#splitline{" + rlt_2 + "}{#splitline{" + rlt_3 + "}{" + rlt_4 + "}}}";
  return rlt;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TString addCuts(const vector<TString>& cuts, TString prefix=""){
  vector<TString> cCuts;
  for (const auto &c : cuts) {
    if (c.IsWhitespace()) continue; // ignore empty string
    cCuts.push_back(c);
  }
  return prefix + joinString(cCuts, " && ");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<TString> splitString(const TString &instr, const TString &delimiter){
  vector<TString> v;
  TObjArray *tx = instr.Tokenize(delimiter);
  for (Int_t i = 0; i < tx->GetEntries(); i++)
    v.push_back(((TObjString *)(tx->At(i)))->String());
  return v;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TString translateString(TString name, const std::map<TString, TString>& strMap, TString splitBy, TString concatBy, bool splitline = false){
  auto keys = splitString(name, splitBy);
  vector<TString> substrs, substrs_1, substrs_2, substrs_3, substrs_4;
  int size = keys.size();
  bool isOdd = ((size % 2) != 0) ? false : true;
  int i = 0;
  for (auto k : keys){
    //cout << "i: " << i << ", k: " << k << endl;
    try{
      if(splitline){
	if(k.Contains("ptisr") || k.Contains("ht") || k.Contains("nrtntnw")){
	  substrs_3.push_back(strMap.at(k));
	} else if(k.Contains("ptb")){
	  substrs_4.push_back(strMap.at(k));
        } else if(substrs_1.size() < 2 || k.Contains("nivf") || k.Contains("nj7")){
	  substrs_1.push_back(strMap.at(k));
        } else if(substrs_2.size() < 2){
	  substrs_2.push_back(strMap.at(k));
        } else {
	  substrs_3.push_back(strMap.at(k));
        }
      } else {
        substrs.push_back(strMap.at(k));
      }
    }catch (const std::out_of_range &e) {
      cerr << "No string mapping for " << k << endl;
      throw e;
    }
    i++;
  }
  if(splitline) return joinStringSplit(substrs_1, substrs_2, substrs_3, substrs_4, concatBy);
  else          return joinString(substrs, concatBy);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TString createCutString(TString name, const std::map<TString, TString>& cutMap, TString delimiter="_"){
  return translateString(name, cutMap, delimiter, " && ");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TString createCutString(TString name, std::map<TString, TString>& cutMap, TString delimiter="_"){
  return translateString(name, cutMap, delimiter, " && ");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* normalize(TH1 *h, double norm = 1){
  h->Scale(norm/h->Integral(0, h->GetNbinsX()+1));
  return h;
}

vector<TH1*> normalize(vector<TH1*> hist, double norm = 1){
  for(auto *h : hist){
    h->Scale(norm/h->Integral(0, h->GetNbinsX()+1));
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* addOverflow(TH1 *h){
  int nbins = h->GetNbinsX()+1;
  double e1 = h->GetBinError(nbins-1);
  double e2 = h->GetBinError(nbins);
  h->AddBinContent(nbins-1, h->GetBinContent(nbins));
  h->SetBinError(nbins-1, sqrt(e1*e1 + e2*e2));
  h->SetBinContent(nbins, 0);
  h->SetBinError(nbins, 0);
  return h;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* addUnderflow(TH1 *h){
  double e1 = h->GetBinError(1);
  double e0 = h->GetBinError(0);
  h->AddBinContent(1, h->GetBinContent(0));
  h->SetBinError(1, sqrt(e1*e1 + e0*e0));
  h->SetBinContent(0, 0);
  h->SetBinError(0, 0);
  return h;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Quantity getHistBin(const TH1* h, int ibin){
  double value = h->GetBinContent(ibin);
  double error = h->GetBinError(ibin);
  if (std::isnan(value)) value = 0;
  if (std::isnan(error)) error = 0;

  return Quantity(value, error);
  //return Quantity(h->GetBinContent(ibin), h->GetBinError(ibin));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setHistBin(TH1* h, int ibin, const Quantity& q){
  h->SetBinContent(ibin, q.value);
  h->SetBinError(ibin, q.error);
}

TH1* getIntegratedHist(const TH1* h, bool useGreaterThan = true, bool useUnderflow = false, bool useOverflow = true){

  TH1 *htmp = (TH1 *)h->Clone("htmp");
  if (useUnderflow) addUnderflow(htmp);
  if (useOverflow) addOverflow(htmp);

  TH1 *hist = (TH1 *)htmp->Clone(TString(h->GetName())+"_intg");
  double integral, error;

  int nbins = hist->GetNbinsX();
  for(int ibin = 1; ibin <= nbins; ibin++) {
    if(useGreaterThan) {
      integral = htmp->IntegralAndError(ibin, nbins, error);
    } else {
      integral = htmp->IntegralAndError(1, ibin, error);
    }
    hist->SetBinContent(ibin, integral);
    hist->SetBinError(ibin, error);
  }
  delete htmp;
  return hist;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* convertToHist(const vector<Quantity> &vec, TString hname, TString title, const BinInfo *bin=nullptr, int start = 0, int manualBins = 0){
  auto nbins = vec.size();
  if(manualBins > 0) nbins = manualBins;
  TH1D *hist;

  if (bin && bin->nbins==nbins){
    hist = new TH1D(hname, title, nbins, bin->plotbins.data());
    hist->SetXTitle(bin->label + (bin->unit=="" ? "" : "["+bin->unit+"]"));
  }else{
    hist = new TH1D(hname, title, nbins, start, start + nbins);
  }
  hist->Sumw2();
  for (unsigned i=0; i<nbins; ++i){
    hist->SetBinContent(i+1, vec.at(i+start).value);
    hist->SetBinError(i+1, vec.at(i+start).error);
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* convertToHist(const vector<double> &vec, TString hname, TString title, const BinInfo *bin=nullptr, int start = 0, int manualBins = 0){
  auto nbins = vec.size();
  if(manualBins > 0) nbins = manualBins;
  TH1D *hist;

  if (bin && bin->nbins==nbins){
    hist = new TH1D(hname, title, nbins, bin->plotbins.data());
    hist->SetXTitle(bin->label + (bin->unit=="" ? "" : "["+bin->unit+"]"));
  }else{
    hist = new TH1D(hname, title, nbins, start, start + nbins);
  }
  hist->Sumw2();
  for (unsigned i=0; i<nbins; ++i){
    hist->SetBinContent(i+1, vec.at(i+start));
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* convertToHist(const vector<TH1*> &vec, TString hname, TString title, const BinInfo *bin=nullptr, bool noError = false){
  auto nbins = (unsigned)vec[0]->GetNbinsX();
  TH1D *hist;

  if (bin && bin->nbins==nbins){
    hist = new TH1D(hname, title, nbins, bin->plotbins.data());
    hist->SetXTitle(bin->label + (bin->unit=="" ? "" : "["+bin->unit+"]"));
  }else{
    hist = new TH1D(hname, title, nbins, 0, nbins);
  }
  hist->Sumw2();
  for (unsigned j=0; j!=vec.size();j++){
    for (unsigned i=1; i<nbins+1; ++i){
      hist->SetBinContent(i, vec[j]->GetBinContent(i));
      if (!noError) hist->SetBinError(i, vec[j]->GetBinError(i));
    }
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* convertToHist(const vector<QuantityAsymmErrors> &vec, TString hname, TString title, const BinInfo *bin=nullptr, int start = 0, int manualBins = 0){
  vector<Quantity> qv;
  for (auto &q : vec){
    qv.push_back(q.getQuantity(true));
  }
  return convertToHist(qv, hname, title, bin, start, manualBins);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TGraphAsymmErrors* convertToGraphAsymmErrors(const vector<QuantityAsymmErrors> &vec, TString hname, TString title, const BinInfo *bin=nullptr){
  auto h = convertToHist(vec, hname, title, bin);
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(h);
  for(int ibin = 0; ibin < gr->GetN(); ++ibin) {
    gr->SetPointEYhigh(ibin, vec.at(ibin).errHigh);
    gr->SetPointEYlow(ibin, vec.at(ibin).errLow);
  }
  return gr;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TGraphAsymmErrors* convertToGraphAsymmErrors(TGraphAsymmErrors* vec, TString hname, TString title, const BinInfo *bin=nullptr){
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(*vec);
  for(int ibin = 0; ibin < gr->GetN(); ++ibin) {
    gr->SetPointEYhigh(ibin, vec->GetErrorYhigh(ibin));
    gr->SetPointEYlow(ibin, vec->GetErrorYlow(ibin));
  }
  return gr;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double getHistMaximumPlusError(const TH1* h){
  double max = -1e99;
  for (int i=1; i<h->GetNbinsX()+1; ++i){
    if (h->GetBinContent(i)+h->GetBinError(i)>max)
      max = h->GetBinContent(i)+h->GetBinError(i);
  }
  return max;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double getHistXCenter(TH1* hist, double min=1, double max=-1){
  assert(hist);
  double sum_evt = 0;
  double sum_pos = 0;
  int lowBin, highBin;
  if (min<=max){
    lowBin = hist->FindBin(min);
    lowBin = lowBin>0 ? lowBin : 1;
    highBin = hist->FindBin(max);
    if (max==hist->GetBinLowEdge(highBin)) --highBin;
    highBin = highBin<=hist->GetNbinsX() ? highBin : hist->GetNbinsX();
  }else{
    lowBin = 1;
    highBin = hist->GetNbinsX();
  }
  for (int ibin=lowBin; ibin<=highBin; ++ibin){
    double value = hist->GetBinContent(ibin);
    double pos   = hist->GetXaxis()->GetBinCenter(ibin);
    sum_evt += value;
    sum_pos += value * pos;
  }
  return sum_pos/sum_evt;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* sumHists(const std::vector<TH1*>& hists, const std::vector<double>& weights, TString name = ""){
  assert(!hists.empty());
  assert(hists.size() == weights.size());
  auto hist = (TH1*)hists.front()->Clone(name!="" ? name : (hists.front()->GetName()+TString("_sum")));
  hist->Reset();
  hist->Sumw2();
#ifdef DEBUG_
  cout << (name!="" ? name : (hists.front()->GetName()+TString("_sum"))) << endl;
#endif
  for (unsigned i=0; i<hists.size(); ++i){
    hist->Add(hists.at(i), weights.at(i));
#ifdef DEBUG_
    cout << "---, " << hists.at(i)->GetName() << ", ... x " << weights.at(i) << endl;
#endif
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* sumHists(const std::vector<TH1*>& hists, TString name = ""){
  assert(!hists.empty());
  auto hist = (TH1*)hists.front()->Clone(name!="" ? name : (hists.front()->GetName()+TString("_sum")));
  hist->Reset();
  hist->Sumw2();
#ifdef DEBUG_
  cout << (name!="" ? name : (hists.front()->GetName()+TString("_sum"))) << endl;
#endif
  for (unsigned i=0; i<hists.size(); ++i){
    hist->Add(hists.at(i));
#ifdef DEBUG_
    cout << "    --- " << hists.at(i)->GetName() << endl;
#endif
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* getSummedHist(std::vector<TTree*> intrees, std::vector<double> weights, TString plotvar, TString wgtvar, TString sel, TString hname, TString title, int nbinsx, double xmin, double xmax){
  assert(intrees.size()==weights.size());
  TH1D* hist = new TH1D(hname, title, nbinsx, xmin, xmax);
  hist->Sumw2();
  TH1D* htmp = new TH1D("htmp", title, nbinsx, xmin, xmax);
  hist->Sumw2();
  TString cutstr = wgtvar + "*(" + sel + ")";
  for (unsigned i=0; i<intrees.size(); ++i){
#ifdef DEBUG_
    cout << hname << endl << intrees.at(i)->GetTitle() << ": " << cutstr << endl;
#endif
    intrees.at(i)->Project("htmp", plotvar, cutstr, "e");
    hist->Add(htmp, weights.at(i));
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D* getSummedHist(std::vector<TTree*> intrees, std::vector<double> weights, TString plotvar, TString wgtvar, TString sel, TString hname, TString title, std::vector<double> xbins){
  assert(intrees.size()==weights.size());
  TH1D* hist = new TH1D(hname, title, xbins.size()-1, xbins.data());
  hist->Sumw2();
  TH1D* htmp = new TH1D("htmp", title, xbins.size()-1, xbins.data());
  hist->Sumw2();
  TString cutstr = wgtvar + "*(" + sel + ")";
  for (unsigned i=0; i<intrees.size(); ++i){
#ifdef DEBUG_
    cout << hname << endl << intrees.at(i)->GetTitle() << ": " << cutstr << endl;
#endif
    intrees.at(i)->Project("htmp", plotvar, cutstr, "e");
    hist->Add(htmp, weights.at(i));
  }
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* getReweightedHist(TTree *intree, TString plotvar, TString wgtvar, TString sel, const TH1 *hWeights, TString rewgtvar, TString hname, TString title, std::vector<double> xbins){
  TH1D* hist = new TH1D(hname, title, xbins.size()-1, xbins.data());
  TString rewgtstr;
  for (int ibin=0; ibin<=hWeights->GetNbinsX()+1; ++ibin){
    TString cond;
    if (ibin==0){
      cond = "(" + rewgtvar + "<" + std::to_string(hWeights->GetBinLowEdge(1)) + ")";
    }else if (ibin==hWeights->GetNbinsX()+1){
      cond = "(" + rewgtvar + ">=" + std::to_string(hWeights->GetBinLowEdge(hWeights->GetNbinsX()+1)) + ")";
    }else{
      cond = "(" + rewgtvar + ">=" + std::to_string(hWeights->GetBinLowEdge(ibin)) + "&&" + rewgtvar + "<" + std::to_string(hWeights->GetBinLowEdge(ibin)+hWeights->GetBinWidth(ibin)) + ")";
    }
    rewgtstr = rewgtstr + "*(" + cond + "*" + std::to_string(hWeights->GetBinContent(ibin)) + " + (!" + cond + ")*1.0" + ")";
  }
  TString cutstr = wgtvar + "*(" + sel + ")" + rewgtstr;
#ifdef DEBUG_
  cout << hname << endl << intree->GetTitle() << ": " << cutstr << endl;
#endif
  intree->Project(hname, plotvar, cutstr, "e");
  return hist;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1* getReweightedHist(TTree *intree, TString plotvar, TString wgtvar, TString sel, const TH1 *hWeights, TString rewgtvar, TString hname, TString title, int nbinsx, double xmin, double xmax){
  TH1D* hist = new TH1D(hname, title, nbinsx, xmin, xmax);
  TString rewgtstr;
  for (int ibin=0; ibin<=hWeights->GetNbinsX()+1; ++ibin){
    TString cond;
    if (ibin==0){
      cond = "(" + rewgtvar + "<" + std::to_string(hWeights->GetBinLowEdge(1)) + ")";
    }else if (ibin==hWeights->GetNbinsX()+1){
      cond = "(" + rewgtvar + ">=" + std::to_string(hWeights->GetBinLowEdge(hWeights->GetNbinsX()+1)) + ")";
    }else{
      cond = "(" + rewgtvar + ">=" + std::to_string(hWeights->GetBinLowEdge(ibin)) + "&&" + rewgtvar + "<" + std::to_string(hWeights->GetBinLowEdge(ibin)+hWeights->GetBinWidth(ibin)) + ")";
    }
    rewgtstr = rewgtstr + "*(" + cond + "*" + std::to_string(hWeights->GetBinContent(ibin)) + " + (!" + cond + ")*1.0" + ")";
  }
  TString cutstr = wgtvar + "*(" + sel + ")" + rewgtstr;
#ifdef DEBUG_
  cout << hname << endl << intree->GetTitle() << ": " << cutstr << endl;
#endif
  intree->Project(hname, plotvar, cutstr, "e");
  return hist;
}

TH1* getPullHist(TH1 *h_data, TGraphAsymmErrors* hs, bool Ratio = false){
  auto pull_h=new TH1F("pull_h",";Pull;Search Regions",40,-4,4);
  TH1D *ratio = (TH1D*)h_data->Clone("hratio");
  cout << "pull = (a-b)/sqrt(b+(db)^2)" << endl;
  for(int ibin = 0; ibin < hs->GetN(); ++ibin){
    int ibin_data = ibin + 1;
    ratio->SetBinError(ibin,0);
    float a = h_data->GetBinContent(ibin_data);
    float b = hs->GetY()[ibin];
    //if data >= BG
    float da = h_data->GetBinErrorLow(ibin_data) * h_data->GetBinErrorLow(ibin_data);
    float db = hs->GetErrorYhigh(ibin) * hs->GetErrorYhigh(ibin);
    if (a < b){//if data < BG
      da = h_data->GetBinErrorUp(ibin_data) * h_data->GetBinErrorUp(ibin_data);
      db = hs->GetErrorYlow(ibin) * hs->GetErrorYlow(ibin);
    }
    float pull = (a-b)/sqrt(b+db);	//ken's formular: pull = data-pred/sqrt(pred + d_pred^2)
    ratio->SetBinContent(ibin,pull);
    pull_h->Fill(pull);
    if(TMath::Abs(pull) > 2.0)cout << "bin " << ibin << ": " << pull << " = " << "(" << a << " - " << b << ")/sqrt(" << b << " + (" << sqrt(db) << ")^2)" << endl;  
  }
  if (Ratio) return ratio;
  return pull_h;
}

TH1* getQHist(TH1 *h_data, TGraphAsymmErrors* hs){
  TH1 *q_h = (TH1 *)h_data->Clone("hq");
  cout << "q = 2(sqrt(S+B) - sqrt(B))" << endl;
  for(int ibin = 0; ibin < hs->GetN(); ++ibin){
    int ibin_data = ibin + 1;
    float a = h_data->GetBinContent(ibin_data);
    float b = hs->GetY()[ibin];
    //if data >= BG
    float da = h_data->GetBinErrorLow(ibin_data) * h_data->GetBinErrorLow(ibin_data);
    float db = hs->GetErrorYhigh(ibin) * hs->GetErrorYhigh(ibin);
    if (a < b){//if data < BG
      da = h_data->GetBinErrorUp(ibin_data) * h_data->GetBinErrorUp(ibin_data);
      db = hs->GetErrorYlow(ibin) * hs->GetErrorYlow(ibin);
    }
    float q = 2*(sqrt(a+b) - sqrt(b));
    q_h->SetBinContent(ibin, q);
    q_h->SetBinError(ibin, 0);
    cout << "bin " << ibin << ": " << q << " = " << "2*(sqrt(" << a << " + " << b << ") - sqrt(" << b << "))" << endl;  
  }
  return q_h;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void prepHists(vector<TH1*> hists, bool isNormalized = false, bool isOverflowAdded = true, bool isFilled = false, vector<Color_t> colors = {}){
  int count = 0;
  for (unsigned ih = 0; ih < hists.size(); ++ih){
    auto *h = hists.at(ih);
    if (isNormalized) normalize(h);
    if (isOverflowAdded) addOverflow(h);

    bool isColored = false;
    if (ih < colors.size()){
      h->SetLineColor(colors.at(ih));
      isColored = true;
    }else {
      TString hname = h->GetName();
      for (const auto &c : COLOR_MAP){
        if (hname.Contains(c.first, TString::kIgnoreCase)){
          h->SetLineColor(c.second);
          isColored = true;
          break;
        }
      }
    }
    if (!isColored) {
      h->SetLineColor(comp_colors.at(count % comp_colors.size()));
      ++count;
    }
    h->SetMarkerColor(h->GetLineColor());
  }

  std::set<Color_t> colorset;
  for (auto *h : hists){
    auto color = h->GetLineColor();
    if (colorset.find(color)!=colorset.end()){
      h->SetLineColor(color+2);
      h->SetMarkerColor(color+2);
    }
    colorset.insert(color);
  }

  if (isFilled){
    for (auto h:hists){
      if (h->GetLineColor()!=kBlack)
        h->SetFillColor(h->GetLineColor()); h->SetFillStyle(1001); h->SetLineColor(kBlack);
    }
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TLegend* initLegend(){
  double fLegX1 = 0.58, fLegY1 = 0.87, fLegX2 = 0.92, fLegY2 = 0.87;
  TLegend *leg = new TLegend(fLegX1, fLegY1, fLegX2, fLegY2);
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.048);
  leg->SetTextFont(42);
  return leg;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void addLegendEntry(TLegend *leg, TObject* obj, TString label, TString legType = "EP", double height = 0.06){
  double fLegY1 = leg->GetY1()-height;
  leg->SetY1(fLegY1);
  leg->AddEntry(obj, label, legType);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class T>
TLegend* appendLegends(TLegend *leg, vector<T*> hists, vector<TString> labels, TString legType = "EP"){
  assert(hists.size() == labels.size());
  double fLegY1 = leg->GetY1()-0.06*hists.size();
  leg->SetY1(fLegY1);
  for (unsigned i=0; i<hists.size(); ++i){
    leg->AddEntry(hists.at(i), labels.at(i), legType);
  }
  return leg;
}

TLegend* appendLegends(TLegend *leg, vector<TH1*> hists, vector<TString> labels, TString legType = "EP"){
  return appendLegends<TH1>(leg, hists, labels, legType);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class T>
TLegend* prepLegends(vector<T*> hists, vector<TString> labels, TString legType = "EP"){
  assert(hists.size() == labels.size());
  auto leg = initLegend();
  appendLegends<T>(leg, hists, labels, legType);
  return leg;
}

TLegend* prepLegends(vector<TH1*> hists, vector<TString> labels, TString legType = "EP"){
  return prepLegends<TH1>(hists, labels, legType);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setLegend(TLegend *leg, int ncols, double x1, double y1, double x2, double y2){
  leg->SetNColumns(ncols);
  leg->SetX1(x1);
  leg->SetY1(y1);
  leg->SetX2(x2);
  leg->SetY2(y2);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void drawHeader(TString text, TPad *p=0, double lowX = 0.7, double lowY = 0.93)
{
#ifdef TDR_STYLE_
  if (text.Contains("TeV")) {
    if (p) CMS_lumi(p, 4, 10);
    return;
  }
#endif
  TPaveText* lumi  = new TPaveText(lowX, lowY, lowX+0.25, lowY+0.04, "NDC");
  lumi->SetBorderSize(   0 );
  lumi->SetFillStyle(    0 );
  lumi->SetTextAlign(   31 );
  lumi->SetTextSize ( 0.045);
  lumi->SetTextColor(    1 );
  lumi->SetTextFont (   42 );
  lumi->AddText(text);
  lumi->Draw();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void drawTextBox(TString text, double x1, double y1, double x2, double y2, int align = 21, int bordersize=0, int textcolor=1, int fillcolor=0){

  TPaveText *tb = new TPaveText(x1,y1,x2,y2,"NDC");
  tb->SetTextColor(textcolor);
  tb->SetTextAlign(align);

  if(fillcolor==-1)
    tb->SetFillStyle(0);
  else
    tb->SetFillColor(fillcolor);

  tb->SetBorderSize(bordersize);
  tb->AddText(text);
  tb->Draw();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void drawText(TString text, double lowX = 0.7, double lowY = 0.93)
{
  TPaveText* lumi  = new TPaveText(lowX, lowY, lowX+0.25, lowY+0.04, "NDC");
  lumi->SetBorderSize(   0 );
  lumi->SetFillStyle(    0 );
  lumi->SetTextAlign(   11 );
  lumi->SetTextSize ( 0.03);
  lumi->SetTextColor(    1 );
  lumi->SetTextFont (   42 );
  lumi->AddText(text);
  lumi->Draw();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void drawTLatexNDC(TString text, double xpos, double ypos, double size=0.03, double align=11, double angle = 0, int font = 42, int color = 1)
{
  TLatex tl;
  tl.SetTextSize(size);
  tl.SetTextAlign(align);
  tl.SetTextAngle(angle);
  tl.SetTextFont(font);
  tl.SetTextColor(color);
  tl.DrawLatexNDC(xpos, ypos, text);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void drawLine(double x1, double y1, double x2, double y2, int color=kGray+2, int style=kDashed, int width=3)
{
  TLine *line = new TLine(x1,y1,x2,y2);
  line->SetLineColor(color);
  line->SetLineStyle(style);
  line->SetLineWidth(width);
  line->Draw();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void getRatioUpDownErrors(int dN, double mN, double mE, double& eL, double& eH){
  if(mN <= 0) return;
  if(dN < 0)  return;
  eL = 0;
  eH = 0;

  if (dN > 10){
    // if data counts > 10, use Gaussian error
    auto q = Quantity(dN, std::sqrt(1.*dN)) / Quantity(mN, mE);
    eL = q.error;
    eH = eL;
    return;
  }

  const double alpha = 1 - 0.6827;
  static TRandom3 * rand = new TRandom3(1234);

  const int nEntries = 10000;
  vector<float> h;
  h.reserve(nEntries);
  vector<float> hL;
  hL.reserve(nEntries);

  for(unsigned int i = 0; i < nEntries; ++i){
    double ndL = 0;
    for(int iD = 0; iD < dN; ++iD){
      ndL -= TMath::Log(rand->Uniform());
    }
    double nd = ndL -  TMath::Log(rand->Uniform());
    double nm = rand->Gaus(mN,mE);
    if(nm < 0) nm = fabs(nm);
    h.push_back(nd/nm);
    hL.push_back(ndL/nm);
  }

  if(dN){
      std::sort(hL.begin(), hL.end());
      eL = hL[int( double(nEntries)*alpha/2  )];
      eL = double(dN)/mN - eL;
   }

  std::sort(h.begin(), h.end());
  eH = h[int( double(nEntries)* (1 - alpha/2)  )];
  eH = eH - double(dN)/mN;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TGraphAsymmErrors* getAsymmErrors(TH1* h){
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(h);
  const double alpha = 1 - 0.6827;
  for(int ibin = 0; ibin < gr->GetN(); ++ibin) {
    int dN = gr->GetY()[ibin];
    double L =  (dN == 0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,dN,1.));
    double U =  ROOT::Math::gamma_quantile_c(alpha/2,dN+1,1) ;
    gr->SetPointEYhigh(ibin, U - double(dN));
    gr->SetPointEYlow(ibin, double(dN)- L);
    if(dN == 0) {
      gr->SetPointEXlow(ibin, 0);
      gr->SetPointEXhigh(ibin, 0);
    }
  }
  return gr;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TGraphAsymmErrors* getRatioAsymmErrors(TH1* hD, TH1* hM) {
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(hD);
  for(int ibin = 0; ibin < gr->GetN(); ++ibin) {
    int dN = gr->GetY()[ibin];
    double mN = hM->GetBinContent(ibin+1);
    double mE = hM->GetBinError(ibin+1);
    double eL = 0, eH = 0;
    gr->SetPoint(ibin, gr->GetX()[ibin], double(dN)/mN);
    getRatioUpDownErrors(dN, mN, mE, eL, eH);
    gr->SetPointEYhigh(ibin, eH);
    gr->SetPointEYlow(ibin, eL);
  }
  return gr;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TGraphAsymmErrors* getRatioAsymmErrors(TH1* hD, TH1* hnonttbar, TH1* httbar) {
  //(Data - nonttbar)/ttbar
  cout << "____Ratio: (Data - nonttbar)/ttbar" << endl;
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(hD);
  for(int ibin = 0; ibin < gr->GetN(); ++ibin) {
    int dN = gr->GetY()[ibin];
    double mN = httbar->GetBinContent(ibin+1);
    double mE = httbar->GetBinError(ibin+1);
    double nonmN = hnonttbar->GetBinContent(ibin+1);
    double nonmE = hnonttbar->GetBinError(ibin+1);
    double eL = 0, eH = 0;
    gr->SetPoint(ibin, gr->GetX()[ibin], (double(dN)-nonmN)/mN);
    getRatioUpDownErrors(dN, mN, mE, eL, eH);
    gr->SetPointEYhigh(ibin, eH);
    gr->SetPointEYlow(ibin, eL);
  }
  return gr;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Quantity dileptonZtoLLScaleFactorHelper(Quantity data_peak, Quantity dy_peak, Quantity tt_peak, Quantity data_off, Quantity dy_off, Quantity tt_off){
  double num = (data_off*tt_peak - data_peak*tt_off).value;
  double den = (  dy_off*tt_peak -   dy_peak*tt_off).value;
  double val = num/den;
  double err = (tt_peak.value*data_off - tt_off.value*data_peak - val*tt_peak.value*dy_off + val*tt_off.value*dy_peak
      + (data_off.value-val*dy_off.value)*tt_peak + (-data_peak.value+val*dy_peak.value)*tt_off).error / std::abs(den);
  return Quantity(val, err);
}

Quantity dileptonTTbarScaleFactorHelper(Quantity data_peak, Quantity dy_peak, Quantity tt_peak, Quantity data_off, Quantity dy_off, Quantity tt_off){
  return dileptonZtoLLScaleFactorHelper(data_peak, tt_peak, dy_peak, data_off, tt_off, dy_off);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename Number>
vector<TString> convertBinRangesToLabels(const vector<Number>& binedges, bool tableStyle = false){
  vector<TString> labels;
  for (unsigned idx=0; idx<binedges.size()-1; ++idx){
    if (idx == binedges.size() - 2){
      TString tmpl = tableStyle ? "$\\geq%d$" : "#geq %d";
      labels.push_back(TString::Format(tmpl, int(binedges.at(idx))));
    }
    else{
      TString tmpl = tableStyle ? "%d$-$%d" : "[%d, %d)";
      labels.push_back(TString::Format(tmpl, int(binedges.at(idx)), int(binedges.at(idx+1))));
    }
  }
  return labels;
}

template<typename Number>
vector<TString> convertBinRangesToLabels(const vector<TString>& binnames, const map<TString, vector<Number>>& binedges, bool tableStyle = false){
  vector<TString> labels;
  for (const auto &name : binnames){
    auto bins = binedges.at(name);
    auto l = convertBinRangesToLabels<Number>(bins, tableStyle);
    labels.insert(labels.end(), l.begin(), l.end());
  }
  return labels;
}

void setBinLabels(TH1 *h, const vector<TString>& labels){
  for (unsigned i=0; i<labels.size() && i<unsigned(h->GetNbinsX()); ++i){
    h->GetXaxis()->SetBinLabel(i+1, labels.at(i));
  }
}

void SetEx(TGraphAsymmErrors* gae, Double_t Ex)
{
  Int_t np = gae->GetN();
  for (Int_t i=0; i<np; i++) {
    gae->SetPointEXhigh(i,Ex);
    gae->SetPointEXlow(i,Ex);
  }
}

std::pair<double, double> doLogNorm(vector<double> p_down, vector<double> p_up){
  double log_syst_up_sum = 0., log_syst_down_sum = 0.;
  double log_syst_up_total = 0., log_syst_down_total = 0.;
  double log_final_up = 0., log_final_down = 0.;
  for(unsigned p = 0; p != p_down.size(); p++){
    double log_syst_up     = p_up[p];
    double log_syst_down   = p_down[p];
    if ((log_syst_up > 1 && log_syst_down > 1) || (log_syst_up < 1 && log_syst_down < 1)){
      double geometric_mean = TMath::Sqrt(log_syst_up * log_syst_down);
      log_syst_up   /= geometric_mean;
      log_syst_down /= geometric_mean;
    }
    if (log_syst_up > 1 || log_syst_down < 1){
        log_syst_up_sum     += pow(TMath::Log(log_syst_up), 2);
        log_syst_down_sum   += pow(TMath::Log(log_syst_down), 2);
    } else{
        log_syst_up_sum     += pow(TMath::Log(log_syst_down), 2);
        log_syst_down_sum   += pow(TMath::Log(log_syst_up), 2);
    }
    log_syst_up_total   = TMath::Exp( TMath::Sqrt(log_syst_up_sum));
    log_syst_down_total = TMath::Exp(-TMath::Sqrt(log_syst_down_sum)); // Minus sign is needed because this is the *down* ratio
    log_final_up   = log_syst_up_total;
    log_final_down = log_syst_down_total;
  }

  return make_pair(log_final_down, log_final_up);
}

}
#endif /*ESTTOOLS_MINITOOLS_HH_*/
