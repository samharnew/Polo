/**
 * <B> PoloLLHMultVarGaus </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  
 *  
 **/

 
#ifndef POLO_MULTI_VAR_GAUS_LLH
#define POLO_MULTI_VAR_GAUS_LLH

#include "TRandom.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TDecompChol.h"

#include "PoloObsAbs.h"
#include "PoloLLHAbs.h"


class PoloLLHMultVarGaus : public PoloLLHAbs {
  
  std::vector<PoloObsAbs*> _obs;
  TVectorD                 _measVals;
  TMatrixD                 _covMatrix;
  TMatrixD                 _invCovMatrix;

  public:

  PoloLLHMultVarGaus(std::vector<PoloObsAbs*> obs, TVectorD measVals, TMatrixD covMatrix);
  /**< empty constructor */

  PoloLLHMultVarGaus(std::vector<PoloObsAbs*> obs, TVectorD measVals, TVectorD errs, TMatrixD corMatrix);

  TVectorD getExpVals();


  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();

  virtual PoloLLHAbs* clone();

  virtual double getProb();
  virtual double getNeg2LLH();
  virtual void   genToyMeas(TRandom* random);

  virtual void   printOneliner();


  virtual ~PoloLLHMultVarGaus();
  /**< destructor */


};


#endif

