/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * This class contains a generic normalisation parameter to be used in fits
 *
 *
 **/

 
#ifndef POLO_FP_SET_NORM
#define POLO_FP_SET_NORM

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"
#include "Mint/MinuitParameterSet.h"

class PoloFPSetNorm{
  
  private:
  
  MINT::counted_ptr<MINT::FitParameter> _norm;
  /**< The FitParameter used as the normalisation parameter */

  public:

  PoloFPSetNorm(MINT::MinuitParameterSet* parSet = 0, TString name = "");
  /**< create a normalisation fit parmaeter, with a given name */

  double getVal() const;
  /**< get the current value of the normalisation parameter */

  void fix   ();
  /**< fix the normalisation parameter to its current value */

  void unfix ();
  /**< unfix the normalisation parameter */

  MINT::counted_ptr<MINT::FitParameter> getFitParameter();
  /**< get the fit parameter */

  void setVal(double val);
  /**< set the current value of the normalisation parameter */
  
  ~PoloFPSetNorm(){;}
};

#endif