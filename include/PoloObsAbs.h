/**
 * <B> PoloObsAbs </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  This is an abstact class that forms all observables i.e. things that
 *  you will measure in your experiment. Each observable will depend on a set
 *  of Mint::FitParameters. 
 *  
 *  
 **/

 
#ifndef ABS_POLO_OBS
#define ABS_POLO_OBS

#include "TRandom.h"
#include "PoloObsID.h"
#include "Mint/counted_ptr.h"
#include "Mint/FitParameter.h"

class PoloObsAbs : public PoloObsID {
  
  TString _name;          
  /**< Observable name */

  double _safeThreshold;  
  /**< Sometimes things can go bad if an observable is less than or equal to
  zero (e.g. log 0 = -inf in a likelihood fit). In cases such as this, we can 
  set the _safeThreshold. Above this value getVal(x) = getValSafe(x). Below 
  this value, getValSafe(x) will force getVal(x) to go smoothly towards zero. 
  The idea is that this stops the fit wandering into unphysical regions and 
  crashing, although it should be checked that it doesn't bias the result */
  
  public:

  PoloObsAbs();
  /**< empty constructor */

  virtual double getVal() = 0;
  /**< Virtual function that returns the expected value of the 
  observable given the FitParameter dependencies */
  
  virtual double getValSafe();
  /**< Same as getVal() while getVal() > _safeThreshold. getValSafe() will
  always be larger than zero. */

  virtual double getLogValSafe();
  /**< The log of getValSafe() */

  virtual PoloObsAbs* clone() = 0;
  /**< Return a pointer with a cloned copy of the observable */

  virtual int    genPoisson (TRandom* random);
  /**< Randomly draw from a Poisson dristribution using the expected value 
  of the observable. Returns an integer */

  virtual double genPoissonD(TRandom* random);
  /**< Randomly draw from a Poisson dristribution using the expected value 
  of the observable. Returns an double (TRandom stops working eventually) */

  virtual double    genGaus (double err, TRandom* random);
  /**< Randomly draw from a Gaussian dristribution using the expected value 
  of the observable and the uncertainty given.  */

  void setName(TString val);
  /**< set the name of the observable */

  TString getName();
  /**< get the name of the observable */

  virtual double getPoissonProb       (double nObs);
  /**< Calculate the Poisson probability P(k, lambda) with lambda = getVal(), and
  k = nObs */

  virtual double getGausProb       (double nObs, double err);
  /**< Calculate the Gaussian probability G(k, mu, sig) with k = nObs, mu = getVal()
  and sig = err */

  virtual double getNeg2LogPoissonProb       (double nObs);
  /**< get -2log(  getPoissonProb(nObs)  ) */

  virtual double getNeg2LogGausProb       (double nObs, double err);
  /**< get -2log(  getGausProb(nObs, err)  ) */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies() = 0;
  /**< Get a list of all the MINT::FitParameter that this observable depends on */

  virtual void print(TString prefix = "");
  /**< print the name and getVal() of the observable with a prefix */

  virtual ~PoloObsAbs();
  /**< destructor */

};


#endif
