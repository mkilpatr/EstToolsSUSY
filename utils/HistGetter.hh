//--------------------------------------------------------------------------------------------------
//
//   Get TH1s from TTrees
//   This is for when you need lots of manual control
//
//--------------------------------------------------------------------------------------------------
// Copied from: AnalysisMethods/PlotUtils/interface/HistogramGetter.hh


#ifndef ESTTOOL_HISTGETTER_HH_
#define ESTTOOL_HISTGETTER_HH_

#include "TDirectory.h"
#include "TTree.h"
#include "TFile.h"
#include "TTreeFormula.h"
#include "TH1.h"

using namespace std;

namespace EstTools{

void toUnderflow(TH1 * h) {
    h->SetBinContent(1,h->GetBinContent(1) +h->GetBinContent(0) );
    h->SetBinContent(0,0);
    if(h->GetSumw2()->fN){
      (*h->GetSumw2())[1] += (*h->GetSumw2())[0];
      h->SetBinError(0,0);
    }
}
void toOverflow(TH1 * h) {
  int nBins = h->GetNbinsX();
    h->SetBinContent(nBins,h->GetBinContent(nBins) +h->GetBinContent(nBins+1) );
    h->SetBinContent(nBins+1,0);
    if(h->GetSumw2()->fN){
      (*h->GetSumw2())[nBins] += (*h->GetSumw2())[nBins +1];
      h->SetBinError(nBins+1,0);
    }

}
void toUnderflowX(TH2 * h) {
  for(int iBY = 0; iBY <= h->GetNbinsY()+1; ++iBY){
    int firstBin = h->GetBin(1,iBY);
    int underBin = h->GetBin(0,iBY);
    h->SetBinContent(firstBin,h->GetBinContent(firstBin)+h->GetBinContent(underBin));
    h->SetBinContent(underBin,0);
    if(h->GetSumw2()->fN){
      (*h->GetSumw2())[firstBin] += (*h->GetSumw2())[underBin];
      h->SetBinError(underBin,0);
    }
  }
}
void toOverflowX(TH2 * h) {
  int nBins = h->GetNbinsX();
  for(int iBY = 0; iBY <= h->GetNbinsY()+1; ++iBY){
    int lastBin = h->GetBin(nBins,iBY);
    int overBin = h->GetBin(nBins+1,iBY);
    h->SetBinContent(lastBin,h->GetBinContent(lastBin)+h->GetBinContent(overBin));
    h->SetBinContent(overBin,0);
    if(h->GetSumw2()->fN){
      (*h->GetSumw2())[lastBin] += (*h->GetSumw2())[overBin];
      h->SetBinError(overBin,0);
    }
  }
}


class HistogramGetter{
  //Helper classes
public:


  class BasicPlotInfo{
  public:
    TString var   ;
    TString xTitle;
    TString name  ;
    mutable unsigned int nH;
    unsigned int getN() const {return ++nH;}
    BasicPlotInfo(TString name,TString var,TString xTitle):
      var   (var   ),
      xTitle(xTitle),
      name  (name  ),
      nH(0)
    {};
    virtual ~BasicPlotInfo(){}
    virtual TH1F* getHistogram(TString histName) = 0;
    virtual TH2F* getHistogram2D(TString histName,int nYBins) = 0;
  };

  class MinMaxPlotInfo : public BasicPlotInfo{
  public:
    int     nBins ;
    double  minX  ;
    double  maxX  ;
    MinMaxPlotInfo(TString name,TString var,TString xTitle,int nBins,double minX,double maxX) :
      BasicPlotInfo(name,var,xTitle), nBins(nBins), minX(minX), maxX(maxX){}
    TH1F* getHistogram(TString histName){
      return new TH1F(histName,var.Data(),nBins,minX,maxX);
    }
    TH2F* getHistogram2D(TString histName,int nYBins){
      return new TH2F(histName,var.Data(),nBins,minX,maxX,nYBins, -.5, nYBins -.5);
    }
  };

  class SetBinsPlotInfo : public BasicPlotInfo{
  public:
    int     nBins ;
    double* bins  ;
    SetBinsPlotInfo(TString name,TString var,TString xTitle,int nBins,const double* inbins) :
      BasicPlotInfo(name,var,xTitle), nBins(nBins){
      bins = new double[nBins+1];
      for(int iB = 0; iB < nBins+1; ++iB) bins[iB] = inbins[iB];
    }
    ~SetBinsPlotInfo() {delete [] bins;}
    TH1F* getHistogram(TString histName){
      return new TH1F(histName,var.Data(),nBins,bins);
    }
    TH2F* getHistogram2D(TString histName,int nYBins){
      return new TH2F(histName,var.Data(),nBins,bins,nYBins, -.5, nYBins -.5);
    }
  };

  public:
  BasicPlotInfo * plotInfo;
  HistogramGetter(BasicPlotInfo * plotInfo) : plotInfo(plotInfo), nBootStraps(0), underflow(false), overflow(true) {}
  HistogramGetter(TString name,TString var,TString xTitle,int nBins,const double* bins) :
    plotInfo(new SetBinsPlotInfo(name,var,xTitle,nBins, bins)), nBootStraps(0), underflow(false), overflow(true) {}
  HistogramGetter(TString name,TString var,TString xTitle,int nBins,double minX,double maxX) :
    plotInfo(new MinMaxPlotInfo(name,var,xTitle,nBins, minX,maxX)), nBootStraps(0), underflow(false), overflow(true) {}

  //Get a histogram with the loaded plotInfo, but set your own weight and selection string
  TH1F * getHistogram(TTree* tree,TString histSelection,TString histWeight, TString histSampleName = "");

  //Get a histogram with the loaded plotInfo, but set your own weight and selection string
  //But do it inefficienty by iterating over the tree manually....use it for bootstrapping when it is
  //MUCH MORE EFFICIENT
  TH1F * getHistogramManual(TTree* tree,TString histSelection,TString histWeight, TString histSampleName = "");

  //Get a correlated TF: numerator/denominator. Only really usefull if you are doing bootstrapping
  //Will also print out the covariance matrix from the bootstrapping
  TH1F*  getTFAndCov(TTree* tree,TString numSelection,TString numWeight, TString denSelection,TString denWeight, TString histSampleName = "");

  //For when you want to flip between bootstrapping for the same getter
  void setNBS(int newBS) {nBootStraps = newBS;}

  // Set underflow and overflow
  void setUnderOverflow(bool addUnderflow, bool addOverflow) { underflow = addUnderflow; overflow = addOverflow; }

  private:
  TH1F * getHistogram(TTree* tree);
  TH1F*  getHistogramManual(TTree * tree);
  TString getFullName();
  TString getSelString();

  TString selection;
  TString weight;
  TString sampleName;
  unsigned int nBootStraps;
  bool underflow;
  bool overflow;

};


TH1F * HistogramGetter::getHistogramManual(TTree* tree,TString histSelection,TString histWeight, TString histSampleName){
  selection = histSelection;
  weight = histWeight;
  sampleName = histSampleName;
  return getHistogramManual(tree);
}

TH1F * HistogramGetter::getHistogram(TTree* tree,TString histSelection,TString histWeight, TString histSampleName){
  selection = histSelection;
  weight = histWeight;
  sampleName = histSampleName;
  return getHistogram(tree);
}


TH1F*  HistogramGetter::getTFAndCov(TTree* tree,TString numSelection,TString numWeight, TString denSelection,TString denWeight, TString histSampleName){

  sampleName = histSampleName;
  TTreeFormula *varFormula = new TTreeFormula("form2",plotInfo->var, tree);

  selection = numSelection;
  weight = numWeight;
  TString nameN = getFullName();
  TString selN = getSelString();
  TH1F * hN = plotInfo->getHistogram(nameN);
  hN->Sumw2();

  TTreeFormula *selNFormula = new TTreeFormula("form1",selN, tree);

  selection = denSelection;
  weight = denWeight;
  TString nameD = getFullName();
  TString selD = getSelString();
  TH1F * hD = plotInfo->getHistogram(nameD);
  hD->Sumw2();

  TTreeFormula *selDFormula = new TTreeFormula("form2",selD, tree);


  vector<TTreeFormula *> bootFormulas(nBootStraps);

  TH2F *hbN = 0;
  TH2F *hbD = 0;

  if(nBootStraps){
    TString nameS = plotInfo->name += "_bN";
    hbN  = plotInfo->getHistogram2D(nameS,nBootStraps);
    nameS = plotInfo->name += "_bD";
    hbD  = plotInfo->getHistogram2D(nameS,nBootStraps);

    for(unsigned int iB = 0; iB < nBootStraps; ++iB){
      bootFormulas[iB] = new TTreeFormula(TString::Format("boostForm_%u",iB),TString::Format("bootstrapWeight[%u]",iB), tree);
    }
  }


  int nEntries = tree->GetEntries();
  for (int i= 0;i<nEntries;i++) {
    tree->GetEntry(i);
    double var      = varFormula->EvalInstance();
    double weightN   = selNFormula->EvalInstance();
    double weightD   = selDFormula->EvalInstance();
    if(weightD == 0 && weightN == 0) continue;

    if(weightN) hN->Fill(var,weightN);
    if(weightD) hD->Fill(var,weightD);

    for(unsigned int iB = 0; iB < nBootStraps; ++iB){
      bootFormulas[iB]->GetNdata();
      double bootWeight = bootFormulas[iB]->EvalInstance();
      if(bootWeight && weightN)
        hbN->Fill(var,iB,weightN*bootWeight);
      if(bootWeight && weightD)
        hbD->Fill(var,iB,weightD*bootWeight);
    }
  }

  delete selNFormula;
  delete selDFormula;
  delete varFormula;
  for(unsigned int iB = 0; iB < nBootStraps; ++iB)
    delete bootFormulas[iB];

  if(underflow){
    toUnderflow(hN);
    toUnderflow(hD);
    if(nBootStraps){
      toUnderflowX(hbN);
      toUnderflowX(hbD);
    }
  }
  if(overflow){
    toOverflow(hN);
    toOverflow(hD);
    if(nBootStraps){
      toOverflowX(hbN);
      toOverflowX(hbD);
    }
  }

  hN->Divide(hD);

  if(nBootStraps){
    hbN->Divide(hbD);
    const unsigned int nBinsX = hbN->GetNbinsX();

    vector<double> means(nBinsX +2,0);
    vector<vector<double> > meanSqs(nBinsX +2, vector<double>(nBinsX +2,0)      );

    for(unsigned int iBS = 0; iBS < nBootStraps; ++iBS){
      for(unsigned int iB = 0; iB <= nBinsX +1; ++iB){
        means[iB] += hbN->GetBinContent(iB,iBS+1);
        for(unsigned int iB2 = 0; iB2 <= nBinsX +1; ++iB2){
          meanSqs[iB][iB2] += hbN->GetBinContent(iB,iBS+1)*hbN->GetBinContent(iB2,iBS+1);
        }
      }
    }

    vector<vector<double> > covMatrix(nBinsX +2, vector<double>(nBinsX +2,0)      );
    for(unsigned int iB = 0; iB <= nBinsX +1; ++iB){
      for(unsigned int iB2 = 0; iB2 <= nBinsX +1; ++iB2){
        covMatrix[iB][iB2] = meanSqs[iB][iB2]/double(nBootStraps) - (means[iB]/double(nBootStraps) )*(means[iB2]/double(nBootStraps)) ;
        cout << covMatrix[iB][iB2] <<" ";
      }
      cout << endl;
    }
    cout << endl <<"Norm!"<<endl;
    for(unsigned int iB = 0; iB <= nBinsX +1; ++iB){
      for(unsigned int iB2 = 0; iB2 <= nBinsX +1; ++iB2){
        cout << TString::Format("%.2f",(covMatrix[iB][iB] == 0 ? 0 : covMatrix[iB][iB2]/covMatrix[iB][iB])) << " ";
      }
      cout << endl;
    }

    cout << endl;



    for(unsigned int iB = 0; iB <= nBinsX +1; ++iB){
      hN->SetBinError(iB,TMath::Sqrt(covMatrix[iB][iB]) );
    }
    delete hbN;
    delete hbD;
  }

  return hN;
}


TH1F * HistogramGetter::getHistogram(TTree* tree){
  if(nBootStraps > 0){
    return getHistogramManual(tree);
  }

  TString name = getFullName();
  TString sel = getSelString();
  TH1F * h = plotInfo->getHistogram(name);
  h->Sumw2();

  tree->Draw(TString::Format("%s>>+%s",plotInfo->var.Data(),name.Data()),sel,"goff");

  if(underflow)
    toUnderflow(h);
  if(overflow)
    toOverflow(h);

  return h;
}

TH1F*  HistogramGetter::getHistogramManual(TTree * tree){

  TString name = getFullName();
  TString sel = getSelString();
  TH1F * h = plotInfo->getHistogram(name);
  h->Sumw2();

  TTreeFormula *selFormula = new TTreeFormula("form1",sel, tree);
  TTreeFormula *varFormula = new TTreeFormula("form2",plotInfo->var, tree);

  vector<TTreeFormula *> bootFormulas(nBootStraps);

  TH2F *hb = 0;

  if(nBootStraps){
    TString nameS = plotInfo->name += "_b";
    hb  = plotInfo->getHistogram2D(nameS,nBootStraps);

    for(unsigned int iB = 0; iB < nBootStraps; ++iB){
      bootFormulas[iB] = new TTreeFormula(TString::Format("boostForm_%u",iB),TString::Format("bootstrapWeight[%u]",iB), tree);
    }
  }


  int nEntries = tree->GetEntries();
  for (int i= 0;i<nEntries;i++) {
    tree->GetEntry(i);
    double var      = varFormula->EvalInstance();
    double weight   = selFormula->EvalInstance();
    if(weight == 0) continue;

    h->Fill(var,weight);

    for(unsigned int iB = 0; iB < nBootStraps; ++iB){
      bootFormulas[iB]->GetNdata();
      double bootWeight = bootFormulas[iB]->EvalInstance();
      if(bootWeight)
        hb->Fill(var,iB,weight*bootWeight);
    }
  }

  delete selFormula;
  delete varFormula;
  for(unsigned int iB = 0; iB < nBootStraps; ++iB)
    delete bootFormulas[iB];

  if(underflow){
    toUnderflow(h);
    if(nBootStraps){
      toUnderflowX(hb);
    }
  }
  if(overflow){
    toOverflow(h);
    if(nBootStraps){
      toOverflowX(hb);
    }
  }

  if(nBootStraps){
    const unsigned int nBinsX = h->GetNbinsX() ;
    for(unsigned int iB = 0; iB <= nBinsX +1; ++iB){
      double s = 0;
      double ss = 0;
      double stest = 0;
      double sstest = 0;

      for(unsigned int iBS = 0; iBS < nBootStraps; ++iBS){
	cout << "hb->GetBinContent(iB,iBS+1): " << hb->GetBinContent(iB,iBS+1) << endl;
        s += hb->GetBinContent(iB,iBS+1);
        ss += hb->GetBinContent(iB,iBS+1)*hb->GetBinContent(iB,iBS+1);
      }
      std::cout << "sum s: "<< s << std::endl;
      std::cout << "sum SS: "<< ss << std::endl;
      std::cout << "nBootstraps: "<< nBootStraps << std::endl;
      double stdDev = TMath::Sqrt(nBootStraps*ss - s*s)/nBootStraps;
      cout << "stdDev: " << stdDev << endl;
      h->SetBinError(iB,stdDev);
    }
    delete hb;
  }

  return h;
}

TString HistogramGetter::getFullName(){
  if(sampleName != "")
    return TString::Format("%s_%s_%i",sampleName.Data(), plotInfo->name.Data(), plotInfo->getN());
  else
    return TString::Format("%s_%i",plotInfo->name.Data(), plotInfo->getN());
}

TString HistogramGetter::getSelString() {
  TString selString("");
  if(weight != ""){
    selString = weight;
    if(selection != "")
      selString += TString::Format("*(%s)",selection.Data());
  } else if (selection != ""){
    selString = selection;
  }

  return selString;

}


}


#endif /*ESTTOOL_HISTGETTER_HH_*/
