/**
 * <B> PoloObsSet </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 **/

 
#ifndef POLO_OBS_SET
#define POLO_OBS_SET

#include "PoloMeas.h"
#include "PoloObsAbs.h"
#include "TMatrixD.h"

#include "PoloMeasSet.h"
#include "PoloObsBGCor.h"
#include "PoloObsEffCor.h"
#include "PoloLLHAbs.h"
#include "PoloLLHSum.h"
#include "PoloLLHPoisson.h"
#include "PoloLLHGaus.h"
#include "PoloLLHMultVarGaus.h"

#include <map>
#include <iostream>
#include <fstream>


class PoloObsSet {
  
  std::vector<PoloObsAbs*> _obs;

  public:

  PoloObsSet();
  /**< empty constructor */

  void addObs ( PoloObsAbs& obs );
  /**< add another observable to the observable set */

  PoloObsAbs* getObs ( PoloObsID& id );
  /**< return the observable with a given ID */

  int getObsNum( PoloObsID& id );
  /**< return the observable number of a given ID. Return -1 if doesn't exist */

  void addBackground  ( PoloMeasSet& bg  );
  /**< add background to all observables in the observable set.
  The entires in the PoloMeasSet and the PoloObsSet are linked 
  through their PoloObsID numbers, so the order that observables/
  measurements are added to either does not matter. */

  void addEfficiencies( PoloMeasSet& eff );
  /**< add effencies to all observables in the observable set.
  The entires in the PoloMeasSet and the PoloObsSet are linked 
  through their PoloObsID numbers, so the order that observables/
  measurements are added to either does not matter. */  

  void addBackground  ( PoloMeas bg  );
  /**< add the same expected background yield to all observables in the observable set. */

  void addEfficiencies( PoloMeas eff );
  /**< add the same efficiency correction to all observables in the observable set. */
 
  void addBackground  ( PoloObsID id, PoloMeas bg  );
  /**< add background yield to observable with specific ID */

  void addEfficiencies( PoloObsID id, PoloMeas eff );
  /**< add efficiency correction to observable with specific ID */

  void print();
  /**< print the list of observables in this set. */


  PoloLLHSum getLLH( PoloMeasSet& meas );
  /**< calculate the llh sum of the observables given the measurements provided. 
  The entires in the PoloMeasSet and the PoloObsSet are linked 
  through their PoloObsID numbers, so the order that observables/
  measurements are added to either does not matter. 
  This function creates one of three different liklihood terms, dependent
  on the measurement given:

    -If the measurements have no uncertainties it is assumed they are raw yields.
     Therefore a LLH term is created for each observable based on a Poisson distibution.

    -If the measurements have uncertainties a LLH term is created for each 
     observable based on a Gaussian distibution, with a width equal to the uncertainty.

    -If correlations are given, a single LLH term is given which is based in a 
     mulitvariate Gaussian

  */  

  PoloLLHSum getLLHForToys();
  /**< calculate the llh sum using the observables. Since no measurements are given,
  all measured values are set to 0 with no uncertainties or correlations. For each
  observable it uses a log likelihood term based on a Poisson distibution. 

  This is perfect for generating toys, where no measurements are needed. */

  std::vector<PoloObsID> getIDList();
  /**< get a list of all the PoloObsID values */

  virtual ~PoloObsSet();
  /**< destructor */

};


#endif
