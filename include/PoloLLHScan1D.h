/**
 * <B> PoloLLHScanner </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  This holds a 1D LLH scan. This can sometimes be formed from lots of individual scans,
 *  and the enveope of these scans gives the total scan. This is useful in a couple of 
 *  situations:
 *
 *    - There are multiple minima in the LLH (either local or global). To get a 
 *      full LLH scan, one wants to scan around each minimima, and take the envelope.
 *
 *    - If one is dealing with parmeter constraints, one method is to repeat the fit
 *      lots of times, where each time the parameters are varied within their constraints.
 *      To get a LLH scan, you want to take the envolope of these scans, where each gets
 *      a LLH penalty based on the constraint.
 **/

 
#ifndef POLO_LLH_SCAN_1D
#define POLO_LLH_SCAN_1D

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

#include "Mint/Minimiser.h"


class PoloLLHScan1D{

  TString             _scanname;
  TString             _xparname;
  TH1D                _scan;
  std::vector<TH1D*>  _indscans;
  
  public:

  PoloLLHScan1D(TString name, TString xparname, int nbinsx, double xmin, double xmax); 
  PoloLLHScan1D(TDirectory* dir); 
  
  void save(TDirectory* dir);
  void save(TString filename);

  void load(TDirectory* dir);
  void load(TString filename);

  void print();

  TH1D* addIndScan();
  TH1D* getScan();
  
  TString getXParName();

  TString getName();


  void popScanFromInds();

  int nIndScans();
  TH1D* getIndScan(int i);
  
  void plot(TString output, double delLLH = 9.0);

  ~PoloLLHScan1D();

};

#endif




