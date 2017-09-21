/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * Store a snapshot of a set of fit parameters and their uncertainties. 
 * This can be saved / loaded from a file.
 * 
 * 
 * 
 * 
 * 
 *
 *
 **/
 

#ifndef POLO_PULLS_HH
#define POLO_PULLS_HH

#include "Mint/FitParameter.h"
#include "Mint/MinuitParameterSet.h"
#include "Mint/counted_ptr.h"
#include "Mint/Minimiser.h"
#include "Mint/IMinuitParameter.h"
#include "TMatrixD.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TF1.h"
#include "TCanvas.h"

#include "TRandom.h"
#include "TVectorD.h"
#include "TDecompChol.h"

#include "PoloStatsFinder.h"
#include "PoloCovarianceFinder.h"
#include "PoloFPSnapshot.h"

 
class PoloPulls {
  
  private:
  
  TString _name;
  TString _axisName;
  bool    _drawMeanWidth;

  std::vector<double>   _measurement;
  std::vector<double>   _error;
  std::vector<double>   _value;
  
  public:
    
  PoloPulls(TString name = "");
  
  void drawMeanAndWidth(bool i){_drawMeanWidth = i;}
  void setAxisName(TString name){_axisName = name;}

  void add(double measurement, double error, double value, int print = 0, std::ostream& os=std::cout);
  void add(double measurement, double negError, double posError, double value, int print = 0, std::ostream& os=std::cout);
  void addPull(double measurement, double pull, double value, int print = 0, std::ostream& os=std::cout);
  
  int getNToys();

  double getMeas (int itoy);
  double getGen  (int itoy);
  double getErr  (int itoy);
  double getPull (int itoy);
  double getResid(int itoy);
  
  void fillMeasStat (PoloStatsFinder& stats);
  void fillGenStat  (PoloStatsFinder& stats);
  void fillErrStat  (PoloStatsFinder& stats);
  void fillPullStat (PoloStatsFinder& stats);
  void fillResidStat(PoloStatsFinder& stats);




  void print();


  void plotPulls(TString location = "", int nBins = 30, double minmax = -1.0, bool drawMeanWidth = true);
  //void plotResiduals(TString location = "", int nBins = 30, double minmax = -1.0);
  //void plotErrors(TString location = "", int nBins = 30);
  //void plotValues(TString location = "", int nBins = 30);
  //void plotErrorPullCorrelation(TString location, int nBins);

  //void plotAll(TString location = "", int nBins = 30, double minmax = -1.0);

  //void save();

  ~PoloPulls();
};


#endif



