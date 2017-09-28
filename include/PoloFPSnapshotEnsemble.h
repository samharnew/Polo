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
 

#ifndef POLO_FP_SNAPSHOT_ENSEMBLE_HH
#define POLO_FP_SNAPSHOT_ENSEMBLE_HH

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

 
class PoloFPSnapshotEnsemble {
  
  std::vector<PoloFPSnapshot> _shapshots;

  public:

  PoloFPSnapshotEnsemble();
  /**< create a new ensemble of PoloFPSnapshots */

  void add( PoloFPSnapshot shapshot );
  /**< add a new snapshot to the ensemble */

  double getMinNeg2LLH();
  /**< get the smallest neg2llh from any of the snapshots in the ensemble  */

  PoloFPSnapshot getBestFit();
  /**< get the snapshot with the smallest neg2LLH  */

  double getMedianError( int pari );
  /**< get the median uncertainty for a given parameter number   */

  PoloFPSnapshot getSysSnapshot();
  /**< get a new snapshot, with central values that are the mean of the values
  in the ensemble, and uncertainties / correlations taken from the covarienvce 
  of the snapshots in the ensemble */

  bool containsEqual( PoloFPSnapshot& shapshot, double tollerance );
  /**< compare the given snapshot to all in the Ensemble, and see if any are the 
  same (within tollerance). See PoloFPSnapshot::equal() for more details.  */
  
  void save(TString filename);
  void save(TDirectory* dir);


  void load(TString filename);
  void load(TDirectory* dir);


  virtual ~PoloFPSnapshotEnsemble();
  /**< desctructor */

};


#endif



