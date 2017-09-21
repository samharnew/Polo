/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Feb 2016
 *
 *  
 *  This takes an array of PoloLLH terms and minises the total expression to 
 *
 *
 **/

 
#ifndef POLO_FITTER_HH
#define POLO_FITTER_HH

#include "TRandom.h"
#include "Mint/Minimisable.h"
#include "Mint/Minimiser.h"
#include "Mint/FitParameter.h"

#include "PoloLLHAbs.h"
#include "PoloConstraint.h"
#include "PoloFPSnapshot.h"
#include "PoloFPSnapshotEnsemble.h"
#include "PoloMeas.h"
#include "PoloMeasSet.h"
#include "PoloObsSet.h"

#include "PoloLLHGaus.h"
#include "PoloLLHPoisson.h"


#include <fstream>
#include <utility>
#include <string>
#include <complex>
#include <iostream>
#include <tuple>


class PoloFitter : public MINT::Minimisable {

  MINT::MinuitParameterSet*     _parSet;

  std::vector<PoloLLHAbs*     > _llhTerms;
  std::vector<PoloConstraint* > _constraints;
  std::vector<PoloConstraint* > _randomisers;

  MINT::Minimiser* _minimiser;
  
  bool _minos;

  public:

  PoloFitter(MINT::MinuitParameterSet* parSet = 0);
  /**< Create a fitter. If a MinuitParameterSet is passed, only
  parameters that are within that set are considered in the 
  minimisation */
    
  void addLLH       (PoloLLHAbs   & llh       );
  /**< Add a LLH term to the fitter */

  void addObs       (PoloObsAbs   & obs, PoloMeas meas );
  /**< Add a LLH term to the fitter using the observable and 
  the measurement given. If the measurement has an error, a 
  Gaussian type LLH is added. If there is no error, a Poisson
  type LLH is added. */
  
  void addObs       (PoloObsSet   & obsSet, PoloMeasSet& measSet );
  /**< Add a LLH term to the fitter using the observable set and 
  the measurement set given. If the measurement has an error, a 
  Gaussian type LLH is added. If there is no error, a Poisson
  type LLH is added. If there are correlations, a multi-variate
  Gaussian type LLH is added. */

  void addObs       (PoloObsAbs   & obs );
  /**< Add a LLH term to the fitter using the observable given. 
  No measurement is given in this case, so this is useless for fitting
  your data. When generating toys, these measurements get overwritten
  anyway, so this function is perfect for generating toys. All LLHs 
  that are created are of the Poisson type. */
  
  void addObs       (PoloObsSet   & obsSet );
  /**< Add a LLH term to the fitter using each of the observables given. 
  No measurement is given in this case, so this is useless for fitting
  your data. When generating toys, these measurements get overwritten
  anyway, so this function is perfect for generating toys. All LLHs 
  that are created are of the Poisson type. */

  void addConstraint(PoloConstraint& constraint);
  /**< Add a parameter constraint to the fitter */

  void addRandomiser(PoloConstraint& randomiser);
  /**< Add parameter randomiser to the fitter. This is useful
  when you want to do multiple fits with different starting values. */

  MINT::Minimiser* getMinimiser();
  /**< Get the minimiser associated with this fitter. 
  If it doesn't exist, create one */

  void fixNonDependencies();
  /**< Fix any fit parameters that do not depend on the observables or
  the constraints provided */

  void setFPsFromConstraints(TRandom* random);
  /**< Use the constraints to set new values for the fit parameters. This should
  be called before generating any toy datasets */

  void randFPs               (TRandom* random);
  /**< Use the constraints and the randomisers to set new values for the fit parameters.
  This should be called after generating a toy datset, but before fitting it */

  void fixConstrainedFPs      ();
  /**< Fix any fit parameters that have a constraint associated to them */

  void fixConstrainedFPsToMean();
  /**< Fix any parameters that have a constraint associated with it, and
  set their values to the central value of the constraint */

  void unfixConstrainedFPs();
  /**< unfix any fit parameters that have a constraint associated to them */

  void clearLLHs();
  /**< remove all LLH terms from the fitter */

  double calcNeg2LLHSum();
  /**< calcualte the sum of all the LLH terms (doesn't include constraints) */

  double calcConstraintNeg2LLHSum();
  /**< calcualte the sum of all the constraint LLH terms */

  virtual double getVal();
  /**< the total LLH that we want to maximise */

  int fit(PoloFPSnapshot* snap = 0, MINT::Minimiser* mini = 0);
  /**< maximise the LLH wrt all fit parameter dependencies */

  int fitWFixedCon(int nfits=100, PoloFPSnapshot* statresults=0, PoloFPSnapshot* sysresults=0, TRandom* random=0, MINT::Minimiser* mini=0);
  /**< maximise the LLH wrt all fit parameter dependencies */



  void generateToy(TRandom* random, PoloFPSnapshot* snap = 0, bool sampleConstraints = true);
  /**< generate a toy dataset (this is saved within the LLH terms). A snapshot of the fit parameters
  used to generate the dataset is saved in the PoloFPSnapshot provided. If the sampleConstraints
  flag is set to true, any fit parameters that are constrained in the fit are first sampled from those
  constraints before the toy dataset is generated. This sampling is stored in the PoloFPSnapshot */

  PoloFPSnapshot getShapshot();
  /**< get a snapshot of the current fit parameters */

  std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< get a list of all fit parameters that can are dependencies of the LLH terms and the
  constraints */

  void print();
  /**< print some info */

  ~PoloFitter();
  /**< destructor */

};







#endif


