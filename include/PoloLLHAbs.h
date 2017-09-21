/**
 * <B> PoloLLHAbs </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  
 *  
 **/

 
#ifndef POLO_LLH_ABS
#define POLO_LLH_ABS

#include "TRandom.h"
#include "Mint/counted_ptr.h"
#include "Mint/FitParameter.h"

#include <iostream>


class PoloLLHAbs {
  
  TString _name;

  public:

  PoloLLHAbs();
  /**< empty constructor */

  PoloLLHAbs(TString name);
  /**< constructor with name */

  virtual double getNeg2LLH() = 0;
  virtual void   genToyMeas(TRandom* random) = 0;

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies() = 0;
  /**< Get a list of all the MINT::FitParameter that this llh depends on */

  virtual PoloLLHAbs* clone() = 0;

  TString getName();
  void    setName(TString name);
  
  virtual void printOneliner();

  virtual ~PoloLLHAbs(){;}
  /**< destructor */

};


#endif
