/**
 * <B> PoloLLHScanner </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  This allows LLH scans to be made for chosen observables. 
 *  
 **/

 
#ifndef POLO_LLH_SCANNER
#define POLO_LLH_SCANNER

#include "PoloStatsFinder.h"
#include "PoloObsAbs.h"
#include "PoloFPSnapshot.h"
#include "PoloFPSnapshotEnsemble.h"


#include <vector>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TKey.h"
#include "Mint/Minimiser.h"
#include "PoloLLHScan1D.h"
#include "PoloLLHScan2D.h"
#include "PoloContourMaker.h"
#include "PoloContourPlotter.h"
#include "PoloContourOrganiser.h"

class PoloLLHScanner{
  
  PoloFPSnapshot                _fitPars;

  PoloFPSnapshotEnsemble        _uniqueSolutions;
  std::vector<PoloLLHScan1D>    _scans1D;
  std::vector<PoloLLHScan2D>    _scans2D;


  void doQuietFit( MINT::Minimiser* minimiser );
  
  void  doScan1D(MINT::Minimiser* minimiser, int param);
  void  doScan2D(MINT::Minimiser* minimiser, int param);

  public: 

  PoloLLHScanner( PoloFPSnapshot& snapshot );
  PoloLLHScanner( TString filename );

  void add1Dscan(TString scanname, TString name1, int nbinsx, double xmin, double xmax);
  void add2Dscan(TString scanname, TString name1, TString name2, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax);
  

  //add a minimiser that is in a local minima
  void addMinimiser(MINT::Minimiser* minimiser);
  
  //plot the resulting scans
  void plot(TString directory);

  PoloContourOrganiser get2DContourSet(int scanNum, std::vector<double> levels);
  PoloContourOrganiser get2DContourSet(TString scanName, std::vector<double> levels);

  TH2D* get2DScan(TString scanName);
  TH1D* get1DScan(TString scanName);

  int get2DScanNum(TString scanName);
  int get1DScanNum(TString scanName);

  void plotContours(TString directory, std::vector<double> levels);

  void plotOverlappingContours(TString scanName1, TString scanName2, TString directory, std::vector<double> levels);


  void save(TString filename);
  void load(TString filename);

  void print(std::ostream& os=std::cout);

  ~PoloLLHScanner();

};


#endif

