/**
 * <B> PoloLLHPoisson </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  
 *  
 **/

 
#ifndef POLO_POISSION_LLH
#define POLO_POISSION_LLH

#include "TRandom.h"
#include "PoloObsAbs.h"
#include "PoloLLHAbs.h"


class PoloLLHPoisson : public PoloLLHAbs  {
  
  MINT::counted_ptr<PoloObsAbs>  _obs;
  double       _measYield;

  public:

  PoloLLHPoisson(PoloObsAbs& obs, double measYield = 0);
  /**< empty constructor */

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();

  virtual PoloLLHAbs* clone();

  virtual double getProb();
  virtual double getNeg2LLH();
  virtual void   genToyMeas(TRandom* random);

  virtual void printOneliner();


  virtual ~PoloLLHPoisson();
  /**< destructor */

};


#endif