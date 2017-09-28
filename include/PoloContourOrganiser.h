/**
 * <B> PoloContourOrgainiser </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  This hold a single contour, and can link to contours it contains 
 *  
 **/


#ifndef POLO_CONTOUR_ORGANISER_HH
#define POLO_CONTOUR_ORGANISER_HH

#include "TGraph.h"
#include <vector>
#include "TH2D.h"
#include "PoloStatsFinder.h"
#include "TF2.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "PoloContour.h"
#include "PoloContourPlotter.h"

class PoloContourOrganiser {
  
  std::vector<PoloContour*> _unorganisedContours;
  std::vector<PoloContour*> _organisedContours;

  public:
    
  PoloContourOrganiser();
  
  void addContour(PoloContour* contour);
  void orgainise();
  
  void findMotherContours(std::vector<PoloContour*> unsortedContours, std::vector<PoloContour*>& motherContours, std::vector<PoloContour*>& daughterContours);
  /**< Find all the contours that are not inside any other conour */

  void plotFilledContours (PoloContourPlotter* plotter);
  void plotContourOutlines(PoloContourPlotter* plotter, int style = 1);

  ~PoloContourOrganiser();
  
};


#endif


