#ifndef ESTTOOLS_STYLE_HH_
#define ESTTOOLS_STYLE_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TPad.h"
#include "TLine.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLatex.h"
#include "TASImage.h"
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TRandom3.h>
#include "TMath.h"
#include <Math/QuantFuncMathCore.h>

#define TDR_STYLE_

using namespace std;
#endif

namespace EstTools{

TString getLumi();

TString TDR_EXTRA_LABEL_ = "Preliminary";

std::map<TString, Color_t> COLOR_MAP = {
    {"data",      kBlack},
    {"single",    kBlack},
    {"double",    kBlack},
    {"jetht",     kBlack},
    {"gjets",     kOrange-3},
    {"wjets",     kYellow-9},
    {"fake",      kSpring-9},
    {"frag",      kGreen+3},
    {"ttg",       kYellow-9},
    {"photon",    kViolet+2},
    {"znunu",     kRed-9},
    {"dyll",      kRed-4},
    {"qcd",       kSpring-9},
    {"ttbar",     kAzure+6},
    {"ttw",       606},
    {"ttz",       797},
    {"rare",      797},
    {"diboson",   kGreen+3},
    {"ww",        kSpring-8},
    {"wz",        kGreen+3},
    {"zz",        kYellow-9},
    {"wmatch",    kGreen+3},
    {"topmatch",  kViolet+2}
};

const vector<Color_t> comp_colors {kBlue, kRed, kBlack, kViolet-1, kGreen+3, kOrange+2, kBlue+3, kRed+2, kMagenta, kBlue, kCyan+2, kAzure+2};

TCanvas *MakeCanvas(int dX = 600, int dY = 600)
{
  static int count = 0;
  TString name = "c" + std::to_string(count);
  ++count;

  // Start with a canvas
  TCanvas *canvas = new TCanvas(name,name,0,0,dX,dY);

  // General overall stuff
  canvas->SetFillColor      (0);
  canvas->SetBorderMode     (0);
  canvas->SetBorderSize     (10);

  // Set margins to reasonable defaults
  canvas->SetLeftMargin     (0.18);
  canvas->SetRightMargin    (0.05);
  canvas->SetTopMargin      (0.08);
  canvas->SetBottomMargin   (0.15);

  // Setup a frame which makes sense
  canvas->SetFrameFillStyle (0);
  canvas->SetFrameLineStyle (0);
  canvas->SetFrameLineWidth (3);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderSize(10);
  canvas->SetFrameFillStyle (0);
  canvas->SetFrameLineStyle (0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderSize(10);

  return canvas;
}

#ifdef TDR_STYLE_
void SetStyle(){
  // Copied from https://ghm.web.cern.ch/ghm/plots/MacroExample/tdrstyle.C

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  // tdrStyle->SetErrorX(0.);

  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(0); // FIXME: was 1
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

// For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:
  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);
  //
  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  tdrStyle->SetLineStyleString(11,"20 10");

  tdrStyle->cd();

  return;

}
#else
void SetStyle()
{
  TStyle *MyStyle = new TStyle("New Style","Better than the default style :-)");
  gStyle = MyStyle;

  // Canvas
  MyStyle->SetCanvasColor     (0);
  MyStyle->SetCanvasBorderSize(10);
  MyStyle->SetCanvasBorderMode(0);
  MyStyle->SetCanvasDefH      (700);
  MyStyle->SetCanvasDefW      (700);
  MyStyle->SetCanvasDefX      (100);
  MyStyle->SetCanvasDefY      (100);

  // color palette for 2D temperature plots
  MyStyle->SetPalette(1,0);

  // Pads
  MyStyle->SetPadColor       (0);
  MyStyle->SetPadBorderSize  (10);
  MyStyle->SetPadBorderMode  (0);
  MyStyle->SetPadBottomMargin(0.13);
  MyStyle->SetPadTopMargin   (0.08);
  MyStyle->SetPadLeftMargin  (0.15);
  MyStyle->SetPadRightMargin (0.05);
  MyStyle->SetPadGridX       (0);
  MyStyle->SetPadGridY       (0);
  MyStyle->SetPadTickX       (1);
  MyStyle->SetPadTickY       (1);

  // Frames
  MyStyle->SetLineWidth(3);
  MyStyle->SetFrameFillStyle ( 0);
  MyStyle->SetFrameFillColor ( 0);
  MyStyle->SetFrameLineColor ( 1);
  MyStyle->SetFrameLineStyle ( 0);
  MyStyle->SetFrameLineWidth ( 3);
  MyStyle->SetFrameBorderSize(10);
  MyStyle->SetFrameBorderMode( 0);

  // Histograms
  MyStyle->SetHistFillColor(2);
  MyStyle->SetHistFillStyle(0);
  MyStyle->SetHistLineColor(1);
  MyStyle->SetHistLineStyle(0);
  MyStyle->SetHistLineWidth(3);
  MyStyle->SetNdivisions(505, "X");

  // Functions
  MyStyle->SetFuncColor(1);
  MyStyle->SetFuncStyle(0);
  MyStyle->SetFuncWidth(2);

  // Various
  MyStyle->SetMarkerStyle(20);
  MyStyle->SetMarkerColor(kBlack);
  MyStyle->SetMarkerSize (1.2);

  MyStyle->SetTitleBorderSize(0);
  MyStyle->SetTitleFillColor (0);
  MyStyle->SetTitleX         (0.2);

  MyStyle->SetTitleSize  (0.055,"X");
  MyStyle->SetTitleOffset(1.200,"X");
  MyStyle->SetLabelOffset(0.014,"X");
  MyStyle->SetLabelSize  (0.040,"X");
  MyStyle->SetLabelFont  (62   ,"X");

  MyStyle->SetStripDecimals(kFALSE);
  MyStyle->SetLineStyleString(11,"20 10");

  MyStyle->SetTitleSize  (0.055,"Y");
  MyStyle->SetTitleOffset(1.600,"Y");
  MyStyle->SetLabelOffset(0.014,"Y");
  MyStyle->SetLabelSize  (0.040,"Y");
  MyStyle->SetLabelFont  (62   ,"Y");

  MyStyle->SetTextSize   (0.055);
  MyStyle->SetTextFont   (62);

  MyStyle->SetStatFont   (62);
  MyStyle->SetTitleFont  (62);
  MyStyle->SetTitleFont  (62,"X");
  MyStyle->SetTitleFont  (62,"Y");

  MyStyle->SetOptStat    (0);

  return;
}
#endif

void CMS_lumi(TPad* pad, int iPeriod, int iPosX, TString extraText=TDR_EXTRA_LABEL_)
{

  // Global variables

  TString cmsText     = "CMS";
  float cmsTextFont   = 62;  // default is helvetic-bold

  bool writeExtraText = true;
  float extraTextFont = 52;  // default is helvetica-italics

  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  float lumiTextSize     = 0.6;
  float lumiTextOffset   = 0.2;
  float cmsTextSize      = 0.75;
  float cmsTextOffset    = 0.11; //0.1;  // only used in outOfFrame version

  float relPosX    = 0.045;
  float relPosY    = 0.035;
  float relExtraDY = 1.2;

  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;

  TString lumi_13TeV = getLumi()+" fb^{-1}";
  TString lumi_8TeV  = "19.7 fb^{-1}";
  TString lumi_7TeV  = "5.1 fb^{-1}";
  TString lumi_sqrtS = "";

  bool drawLogo      = false;

  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  if( iPosX == 0  ) relPosX = cmsTextOffset;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  //  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 ) {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
  }
  else if ( iPeriod==2 ) {
    lumiText += lumi_8TeV;
    lumiText += " (8 TeV)";
  }
  else if( iPeriod==3 ) {
    lumiText = lumi_8TeV;
    lumiText += " (8 TeV)";
    lumiText += " + ";
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
  }
  else if ( iPeriod==4 ) {
    lumiText += lumi_13TeV;
    lumiText += " (13 TeV)";
  }
  else if ( iPeriod==7 ) {
    if( outOfFrame ) lumiText += "#scale[0.85]{";
    lumiText += lumi_13TeV;
    lumiText += " (13 TeV)";
    lumiText += " + ";
    lumiText += lumi_8TeV;
    lumiText += " (8 TeV)";
    lumiText += " + ";
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
    if( outOfFrame) lumiText += "}";
  }
  else if ( iPeriod==12 ) {
    lumiText += "8 TeV";
  }
  else if ( iPeriod==0 ) {
    lumiText += lumi_sqrtS;
  }

  std::cout << lumiText << std::endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame ) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11);
    latex.SetTextSize(cmsTextSize*t);
    latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
  }

  pad->cd();

  float posX_=0;
  if( iPosX%10<=1 ) {
    posX_ =   l + relPosX*(1-l-r);
  }
  else if( iPosX%10==2 ) {
    posX_ =  l + 0.5*(1-l-r);
  }
  else if( iPosX%10==3 ) {
    posX_ =  1-r - relPosX*(1-l-r);
  }
  float posY_ = 1-t - relPosY*(1-t-b);

  if( !outOfFrame ) {
    if( drawLogo ) {
      posX_ =   l + 0.045*(1-l-r)*W/H;
      posY_ = 1-t - 0.045*(1-t-b);
      float xl_0 = posX_;
      float yl_0 = posY_ - 0.15;
      float xl_1 = posX_ + 0.15*H/W;
      float yl_1 = posY_;
      TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
      TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
      pad_logo->Draw();
      pad_logo->cd();
      CMS_logo->Draw("X");
      pad_logo->Modified();
      pad->cd();
    } else {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextSize(cmsTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, cmsText);
      if( writeExtraText ) {
        latex.SetTextFont(extraTextFont);
        latex.SetTextAlign(align_);
        latex.SetTextSize(extraTextSize*t);
        latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
      }
    }
  }
  else if( writeExtraText ) {
    if( iPosX==0) {
      posX_ =   l +  relPosX*(1-l-r);
      posY_ =   1-t+lumiTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, extraText);
  }

  return;

}

}

#endif /* ESTTOOLS_STYLE_HH_ */
