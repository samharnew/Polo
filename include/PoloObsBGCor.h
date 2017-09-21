/**
 * <B> PoloObsBGCor </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *   Add background correction to an observable i.e. obs -> obs + bkg
 *  
 *  
 **/

 
#ifndef POLO_OBS_BG_COR
#define POLO_OBS_BG_COR

#include "PoloObsAbs.h"
#include "PoloMeas.h"

class PoloObsBGCor : public PoloObsAbs {
  
  PoloObsAbs*    _obs;
  PoloMeas       _bkg;

  public:

  PoloObsBGCor(PoloObsAbs& obs, PoloMeas& bgMeas );

  virtual double getVal();
  /**< Get the expected number of single tagged DDb->fX decays. This is just getBF() mulitpled by 
  the normalistion parameter */

  virtual PoloObsAbs* clone();
  /**< Return a pointer with a cloned copy of the observable */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< Get a list of all the MINT::FitParameter that this observable depends on */

  virtual void print(TString prefix = "");
  /**< print the name and getVal() of the observable with a prefix */

  virtual ~PoloObsBGCor();
  /**< destructor */

};


#endif
