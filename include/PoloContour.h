/**
 * <B> PPoloContour </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  This hold a single contour, and can link to contours it contains 
 *  
 **/


#ifndef POLO_CONTOUR_HH
#define POLO_CONTOUR_HH

#include "TGraph.h"
#include <vector>
#include "TH2D.h"
#include "PoloStatsFinder.h"
#include "TF2.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "PoloContourPlotter.h"

class PoloContourPoint{
  
  private:
  
  double _x;
  double _y;

  public:

  PoloContourPoint(double x, double y);
  
  double getX() const;
  double getY() const;

  void setX(const double& x);
  void setY(const double& y);

  ~PoloContourPoint();

};

class PoloContourLine{
  
  private:
  
  PoloContourPoint _a;
  PoloContourPoint _b;

  public:  

  PoloContourLine( const PoloContourPoint& a, const PoloContourPoint& b );
    
  const PoloContourPoint& getPointA() const;
  const PoloContourPoint& getPointB() const;

  ~PoloContourLine();

};

class PoloContourPlotter;

class PoloContour{


  TGraph* _graph;
  int     _level;
  std::vector<PoloContour*> _daughters;

  public:

  PoloContour(TGraph* graph, int level);
  
  int getNumPoints();

  PoloContourLine  getLine (int i);
  PoloContourPoint getPoint(int i);
  
  int numDaughters();

  PoloContour* getDaughter(int i);
  
  TGraph* getTGraph();
  int getNSigma();

  bool addDaughter( PoloContour* contour );

  int isInside   ( PoloContourPoint& point );

  bool isInside ( PoloContour& other, double* frac = 0 ); //check if this Polocontour is inside the other

  void plotFilledContours (PoloContourPlotter* plotter, int mothernsig);
  void plotContourOutlines(PoloContourPlotter* plotter, int mothernsig, int lineStyle = 1);

  ~PoloContour();
    

};


#endif

