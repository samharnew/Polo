/**
 * <B> PoloObsDstTaggedYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  
 *  
 **/

 
#ifndef POLO_OBS_DST_TAGGED_YIELD
#define POLO_OBS_DST_TAGGED_YIELD

#include "PoloObsAbs.h"
#include "PoloFPSetDtoF.h"
#include "PoloFPSetDMixing.h"
#include "PoloFPSetNorm.h"

class PoloObsDstTaggedYield : public PoloObsAbs {
  
  PoloFPSetDtoF    _dToF;
  PoloFPSetDMixing _dMix;
  PoloFPSetNorm    _nDst;
  int              _dstQ;  //charge of the dstar
  double           _minDecTime; 
  double           _maxDecTime;

  public:

  PoloObsDstTaggedYield(PoloFPSetDtoF& dToF, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDst, int dstQ = +1, double mint=0.0, double maxt=50.0, int decTimeBin = -1);
  /**< Create a new observable to describe the yield of D*+ -> D, D->f. 
  The hadronic parameters of the D->f decay must be given, along with the D-mixing parameters and
  a normalisation parameter that represents the total number of D*±  */

  double getDecayTimeIntVal();
  /**< Get the expected number in the decay time range [0-inf]tau. If t_max > 50 and tmin = 0 this is used */

  double integrand(double t);
  /**< get the integrand of the time dependent decay rate */


  virtual double getVal();
  /**< Get the expected number D*+ -> D, D->f decays with decay-time > t_min and < t_max */

  virtual PoloObsAbs* clone();
  /**< Return a pointer with a cloned copy of the observable */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< Get a list of all the MINT::FitParameter that this observable depends on */

  virtual ~PoloObsDstTaggedYield();
  /**< destructor */

};


#endif
