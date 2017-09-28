/**
 * <B> PoloContourPlotter </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  
 *  
 **/


#ifndef POLO_CONTOUR_PLOTTER_HH
#define POLO_CONTOUR_PLOTTER_HH

#include "TGraph.h"
#include <vector>
#include "TH2D.h"
#include "PoloStatsFinder.h"
#include "TF2.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TColor.h"
#include "PoloContour.h"

class PoloContour;
class PoloContourOrganiser;

class PoloContourPlotter {
  
  TCanvas _canvas;
  TH2D    _hist;

  std::vector<int> _fillColors;
  std::vector<int> _lineColors;
  std::vector<int> _fillStyles;

  public: 

  PoloContourPlotter(TString name, double minx, double maxx, double miny, double maxy);
  PoloContourPlotter(TH2D* limits);

  int getFillColor(int i);
  int getLineColor(int i);
  int getFillStyle(int i);


  void useRegularColourScheme();
  void useAlternateColourScheme();
  void useAlternateColourScheme2();
  void addFilledContour(PoloContour* contour, int mothernsig);
  void addContourOutline(PoloContour* contour, int mothernsig, int lineStyle = 1);

  void addContourOutlines(PoloContourOrganiser* contours, int lineStyle = 1);
  void addFilledContours (PoloContourOrganiser* contours);


  void plot(TString filename);


  ~PoloContourPlotter();


};

#endif
