/**
 * <B> PoloObsSum </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * 
 *  Just just adds a list of observables i.e. obs=obs1+obs2+...
 *  
 **/

 
#ifndef POLO_OBS_SUM
#define POLO_OBS_SUM

#include "PoloObsAbs.h"


class PoloObsSum : public PoloObsAbs {
  
  std::vector<PoloObsAbs*>    _obs;

  public:
  
  PoloObsSum(PoloObsAbs& obs1);

  PoloObsSum(PoloObsAbs& obs1, PoloObsAbs& obs2);

  PoloObsSum(PoloObsAbs& obs1, PoloObsAbs& obs2, PoloObsAbs& obs3);


  void addObs(PoloObsAbs& obs);


  virtual double getVal();
  /**< Get the expected number of single tagged DDb->fX decays. This is just getBF() mulitpled by 
  the normalistion parameter */

  virtual PoloObsAbs* clone();
  /**< Return a pointer with a cloned copy of the observable */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< Get a list of all the MINT::FitParameter that this observable depends on */

  virtual void print(TString prefix = "");
  /**< print the name and getVal() of the observable with a prefix */

  virtual ~PoloObsSum();
  /**< destructor */

};


#endif
