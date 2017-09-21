/**
 * <B> PoloObsEffCor </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  Add efficiency correction to an observable i.e. obs -> obs * eff
 *  
 **/

 
#ifndef POLO_OBS_EFF_COR
#define POLO_OBS_EFF_COR

#include "PoloObsAbs.h"
#include "PoloMeas.h"


class PoloObsEffCor : public PoloObsAbs {
  
  std::vector<PoloObsAbs*>    _obs;
  std::vector<PoloMeas   >    _eff;

  public:

  PoloObsEffCor(PoloObsAbs& obs, PoloMeas& effMeas );

  virtual double getVal();
  /**< Get the expected number of single tagged DDb->fX decays. This is just getBF() mulitpled by 
  the normalistion parameter */

  virtual PoloObsAbs* clone();
  /**< Return a pointer with a cloned copy of the observable */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< Get a list of all the MINT::FitParameter that this observable depends on */

  virtual void print(TString prefix = "");
  /**< print the name and getVal() of the observable with a prefix */

  virtual ~PoloObsEffCor();
  /**< destructor */

};


#endif
