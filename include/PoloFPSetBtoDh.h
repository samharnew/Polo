/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  This class holds the fit parameters that describe BtoDK decays. There are two parameterisations 
 *  avalible:  
 *
 *  r_B    -   ratio of magnitudes of B+ -> Dz h+ to B+ -> Dzb h+ ampliudes 
 *  del_B  -   strong phase difference between B+ -> Dz h+ to B+ -> Dzb h+ ampliudes 
 *  gamma  -   weak   phase difference between B+ -> Dz h+ to B+ -> Dzb h+ ampliudes 
 *
 *
 *  The alternative is to use:
 *
 *  x+     - r_B cos (del_B + gamma)
 *  x-     - r_B cos (del_B - gamma)
 *  y+     - r_B sin (del_B + gamma)
 *  y-     - r_B sin (del_B - gamma)
 *
 **/

 
#ifndef POLO_FP_SET_B_TO_DH_HH
#define POLO_FP_SET_B_TO_DH_HH

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"
#include "Mint/MinuitParameterSet.h"

#include "TRandom.h"


class PoloFPSetBtoDh{
  
  private:
  
  TString _finalStateName;   

  MINT::counted_ptr<MINT::FitParameter> _xp;
  MINT::counted_ptr<MINT::FitParameter> _xm;
  MINT::counted_ptr<MINT::FitParameter> _yp;
  MINT::counted_ptr<MINT::FitParameter> _ym;
  
  MINT::counted_ptr<MINT::FitParameter> _rB    ; 
  MINT::counted_ptr<MINT::FitParameter> _deltaB; 
  MINT::counted_ptr<MINT::FitParameter> _gamma ; 
  
  int _paramType;

  public:
  
  PoloFPSetBtoDh(TString finalStateName, MINT::MinuitParameterSet* parSet = 0, int paramType = 0); 
  /**< make a new set of B->Dh parameters using the specified parameterisation. Can assign a 
  name in case you are using muliple B->Dh decays (e.g. B->Dpi and B->DK)  */

  TString getFinalStateName() const;
  /**< get the name of the final state */

  void removeCPV();
  /**< remove CP violation from the system. This either means that x+ = x- and y+ = y- or gamma = 0 */

  void copyGammaFitPatameter(PoloFPSetBtoDh& other);
  /**< copy the gamma fit parameter from another PoloFPSetBtoDh. This is useful if you wanted the
  same CPV in B->Dpi and B->DK decays, for example */

  void randomise( TRandom* random );
  /**< randomise the parameters - angles from [-pi, pi], rB from [-0.3, 0.3], and x±/y± from [-0.3, 0.3] */  

  double getxp  () const; 
  /**< get the value of x+ (this works whatever the parameterisation) */
  double getxm  () const;
  /**< get the value of x- (this works whatever the parameterisation) */
  double getyp  () const;
  /**< get the value of y+ (this works whatever the parameterisation) */
  double getym  () const;
  /**< get the value of y- (this works whatever the parameterisation) */


  MINT::counted_ptr<MINT::FitParameter> getFitParameterxp    ();
  /**< get the fit parameter for x+  */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterxm    ();
  /**< get the fit parameter for x-  */
  MINT::counted_ptr<MINT::FitParameter> getFitParameteryp    ();
  /**< get the fit parameter for y+  */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterym    ();
  /**< get the fit parameter for y-  */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterrB    ();
  /**< get the fit parameter for rb  */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterdeltaB();
  /**< get the fit parameter for delB  */
  MINT::counted_ptr<MINT::FitParameter> getFitParametergamma ();
  /**< get the fit parameter for gamma  */
  
  void setxp  (double val);
  /**< set the value of the xp fit parameter  */
  void setxm  (double val);
  /**< set the value of the xm fit parameter  */
  void setyp  (double val);
  /**< set the value of the yp fit parameter  */
  void setym  (double val);
  /**< set the value of the ym fit parameter  */
  
  void setrB      (double val);
  /**< set the value of the ym fit parameter  */
  void setdeltaB  (double val);
  /**< set the value of the deltaB fit parameter  */
  void setgamma   (double val);
  /**< set the value of the gamma fit parameter  */

  void setAll  (double rB, double deltaB, double gamma, bool degrees = false);
  /**< set values for all the fit parameters. This works whatever the parameterisation  */

  void mapgammaToWithinPi (double val, bool degrees);
  /**< map the gamma parameter to within pi of the value given by adding/subtracting 
  muliples of 2pi */
  void mapdeltaBToWithinPi(double val, bool degrees);
  /**< map the delta parameter to within pi of the value given by adding/subtracting 
  muliples of 2pi */
  void mapGammaAndDelta(double gamma, double delta, bool degrees);
  /**< there often two solutions where gamma+pi and delta+pi. This 
  function will map gamma to within pi/2 degrees of the given value,
  then map delta to withing pi degrees of the given value */  


  void fixxp();
  /** fix the xp fit parameter */
  void fixxm();
  /** fix the xm fit parameter */
  void fixyp();
  /** fix the yp fit parameter */
  void fixym();
  /** fix the ym fit parameter */

  void fixrB      ();
  /** fix the rb fit parameter */
  void fixdeltaB  ();
  /** fix the deltaB fit parameter */
  void fixgamma   ();
  /** fix the gamma fit parameter */


  void unfixxp();
  /** unfix the xp fit parameter */
  void unfixxm();
  /** unfix the xm fit parameter */
  void unfixyp();
  /** unfix the yp fit parameter */
  void unfixym();
  /** unfix the ym fit parameter */

  void unfixrB      ();
  /** unfix the rb fit parameter */
  void unfixdeltaB  ();
  /** unfix the deltaB fit parameter */
  void unfixgamma   ();
  /** unfix the gamma fit parameter */


  ~PoloFPSetBtoDh();
  /** destructor */

};

#endif
