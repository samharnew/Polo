/**
 * <B> PoloPoissonMeas </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  
 *  
 **/

 
#ifndef POLO_LLH_SUM
#define POLO_LLH_SUM

#include "TRandom.h"
#include "PoloLLHAbs.h"


class PoloLLHSum : public PoloLLHAbs  {
  
  std::vector<PoloLLHAbs*> _llh;

  public:

  PoloLLHSum();
  PoloLLHSum(PoloLLHAbs* llh1);
  PoloLLHSum(PoloLLHAbs* llh1, PoloLLHAbs* llh2);
  PoloLLHSum(PoloLLHAbs* llh1, PoloLLHAbs* llh2, PoloLLHAbs* llh3);
  
  void addLLH(PoloLLHAbs* llh);

  virtual double getNeg2LLH();

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();

  virtual PoloLLHAbs* clone();

  virtual void printOneliner();


  virtual void   genToyMeas(TRandom* random);
  /**< generate a measurement using the current value of the observable and
  the _measErr. Overwrite measVal given in constructor   */

  virtual ~PoloLLHSum();
  /**< destructor */

};


#endif