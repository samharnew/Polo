/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * A class that makes it very fast to do pull studies. Give it PoloFPSnapshot of
 * the generated and fitted parameters, then it automatically makes a pull distribtuion
 * for every parameter in the PoloFPSnapshot
 * 
 * 
 * 
 *
 *
 **/
 

#ifndef POLO_FP_PULLS_HH
#define POLO_FP_PULLS_HH

#include "Mint/FitParameter.h"
#include "Mint/MinuitParameterSet.h"
#include "Mint/counted_ptr.h"
#include "Mint/Minimiser.h"
#include "Mint/IMinuitParameter.h"
#include "TMatrixD.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TVectorD.h"
#include "TDecompChol.h"

#include "PoloStatsFinder.h"
#include "PoloCovarianceFinder.h"
#include "PoloFPSnapshot.h"
#include "PoloPulls.h"
 
#include <fstream>

class PoloFPPulls {
  
  PoloFPSnapshot* _genSnapshotPtr;
  PoloFPSnapshot* _fitSnapshotPtr;
  
  std::vector<PoloFPSnapshot> _genSnapshots;
  std::vector<PoloFPSnapshot> _fitSnapshots;

  std::vector<PoloPulls> _pullstats;

  void createPullContainers(PoloFPSnapshot* snapshot);


  public:

  PoloFPPulls(PoloFPSnapshot* genSnapshot, PoloFPSnapshot* fitSnapshot);
  /**< Constructor for PoloFPPulls. You pass a pointer to two PoloFPSnapshot
  objects, one that contains the values of the fit parameters used to generate
  a simulated sample, and another that was found from fitting the simulated sample.
  Every time addPull() is called, a new entry is added to this object using these pointers */

  void addPull(PoloFPSnapshot* genSnapshot=0, PoloFPSnapshot* fitSnapshot=0);
  /**< see constructor description for details. Can additionally provide
  snapshots here that overwrite the defult ones that were passed in the constructor  */

  void drawPulls(TString dir, int nbins = 40);

  //double getMedianError(int i);
  //ddouble getWidthPulls (int i);

  void printPulls();
  void printPullsTex(TString filename, std::map<TString, TString> niceNames);
  
  //dvoid save(TString dir);

  virtual ~PoloFPPulls();
};


#endif



