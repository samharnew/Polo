/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * This class contains fit parameters for the DMixing parameters x and y
 *
 *
 **/

 
#ifndef POLO_FP_SET_D_MIXING
#define POLO_FP_SET_D_MIXING

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"
#include "Mint/MinuitParameterSet.h"

class PoloFPSetDMixing{
  
  private: 

  MINT::counted_ptr<MINT::FitParameter> _x; /**< Fit parameter for D-mixing parameter x */
  MINT::counted_ptr<MINT::FitParameter> _y; /**< Fit parameter for D-mixing parameter y */

  public:

  PoloFPSetDMixing(MINT::MinuitParameterSet* parSet = 0, TString suffix = "");
  /**< Constuctor to make two fit parameters for the D-mixing parameters x and y.
  Can add the fit parameters to a MinuitParameterSet if desired. Can also add
  a suffix if you need more than one set of these parameters. */

  double getX() const;
  /**< get the value of D-mixing parameter x */

  double getY() const;
  /**< get the value of D-mixing parameter y */

  MINT::counted_ptr<MINT::FitParameter> getFitParameterX();
  /**< get the fit parameter of D-mixing parameter x */

  MINT::counted_ptr<MINT::FitParameter> getFitParameterY();
  /**< get the fit parameter of D-mixing parameter y */

  void setX(double val);
  /**< get the value of the fit parameter for D-mixing parameter x */

  void setY(double val);
  /**< get the value of the fit parameter for D-mixing parameter y */

  void fixX();
  /**< Fix the fit paramter for D-mixing parameter x */

  void fixY();
  /**< Fix the fit paramter for D-mixing parameter y */

  void unfixX   ();
  /**< unfix the fit paramter for D-mixing parameter x */

  void unfixY();
  /**< unfix the fit paramter for D-mixing parameter y */

  void noMixing();
  /**< fix the mixing parameters to zero */


  ~PoloFPSetDMixing();
  /**< destructor */

};

#endif