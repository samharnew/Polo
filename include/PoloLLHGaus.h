/**
 * <B> PoloPoissonMeas </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  
 *  
 **/

 
#ifndef POLO_GAUS_LLH
#define POLO_GAUS_LLH

#include "TRandom.h"
#include "PoloObsAbs.h"
#include "PoloLLHAbs.h"


class PoloLLHGaus : public PoloLLHAbs  {
  
  MINT::counted_ptr<PoloObsAbs> _obs;
  double       _measVal;
  double       _measErr;

  public:

  PoloLLHGaus(PoloObsAbs& obs, double measVal, double measErr);
  /**< empty constructor */

  virtual double getNeg2LLH();
  /**<  */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();

  virtual PoloLLHAbs* clone();


  virtual void   genToyMeas(TRandom* random);
  /**< generate a measurement using the current value of the observable and
  the _measErr. Overwrite measVal given in constructor   */

  virtual void printOneliner();


  virtual ~PoloLLHGaus();
  /**< destructor */

};


#endif