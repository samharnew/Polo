/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * An observable to describe the yield of double tagged DDb->fg decays. 
 * The hadronic parameters of the D->f decay must be given, along with the D-mixing parameters and
 * a normalisation parameter that represents the total number of DDb pairs
 *  
 *  
 **/

 
#ifndef POLO_OBS_DT_YIELD
#define POLO_OBS_DT_YIELD

#include "PoloObsAbs.h"
#include "PoloFPSetDtoF.h"
#include "PoloFPSetDMixing.h"
#include "PoloFPSetNorm.h"

class PoloObsDTYield : public PoloObsAbs {
  
  PoloFPSetDtoF    _dToF;
  PoloFPSetDtoF    _dToG;
  PoloFPSetDMixing _dMix;
  PoloFPSetNorm    _nDDb;

  public:

  PoloObsDTYield(PoloFPSetDtoF& dToF, PoloFPSetDtoF& dToG, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDDb);
  /**< Create a new observable to describe the yield of double tagged DDb->fg decays. 
  The hadronic parameters of the D->f and D->g decays must be given, along with the D-mixing parameters and
  a normalisation parameter that represents the total number of DDb pairs  */

  virtual double getVal();
  /**< Get the expected number of double tagged DDb->fg decays. This is just getBF() mulitpled by 
  the normalistion parameter */

  double getBF();
  /**< Get the expected branching fraction for DDb->fg decays, where the DDb come from a psi(3770) decay */

  virtual PoloObsAbs* clone();
  /**< Return a pointer with a cloned copy of the observable */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< Get a list of all the MINT::FitParameter that this observable depends on */

  virtual ~PoloObsDTYield();
  /**< destructor */

};


#endif
