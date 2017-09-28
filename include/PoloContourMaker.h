/**
 * <B> PoloContourMaker </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  This make LLH contours from a LLH scan 
 *  
 **/


#ifndef POLO_CONTOUR_MAKER_HH
#define POLO_CONTOUR_MAKER_HH

#include "TGraph.h"
#include <vector>
#include "TH2D.h"
#include "PoloStatsFinder.h"
#include "TF2.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "PoloContourOrganiser.h"

class PoloContourMaker {
  
  PoloContourMaker();
  
  static PoloContourMaker* s_singleton; 

  //The original histogram you are finding the contours of
  static TH2D* s_originalHist; 
  //A new histogram with one bin extra around the edges with a large bin content. 
  //This forces all contours to be complete.
  static TH2D* s_wideHist;     
  
  static double s_maxReturn;
  static double s_minReturn;
  
  static void makeWideHist();

  bool mapContourIntoRange(TGraph*& graph, double xmin, double xmax, double ymin, double ymax);

  static double smoothedHistogram( Double_t * abscissa, Double_t * parameter );

  public:
  
  static PoloContourMaker* getPoloContourMaker();

  void setHistogram(TH2D* hist);
  
  std::vector<TGraph*> makeContours(double contourLevel);
  
  PoloContourOrganiser getContourOrgainiser(TH2D* hist, std::vector<double> levels);

  PoloContourOrganiser getContourOrgainiser(TString filename, TString histname, std::vector<double> levels);

  ~PoloContourMaker();
  
};


#endif




