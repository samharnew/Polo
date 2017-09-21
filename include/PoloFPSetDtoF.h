/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 *  This class holds the fit parameters that describe the hadronic parameters
 *  of a D->f decay (a single phase space bin). 
 *  
 *  The object has two identifiers that are passed on construction:
 *    - finalStateName  (the name of the final state e.g. KSpipi )
 *    - binNumber       (lables the bin of phase space this object refers to)
 *
 *  There are some important conventions regarding the bin number:
 *    - A bin number of zero means 'phase space integrated' e.g. no binning.
 *    - Negative bin numbers are used for binned self-conjuate final states
 *      that are usually binned in 'pairs' such that +i and -i form a pair.
 *      
 *
 *  The standard parameteriation is to have the four fit parameters
 *    - K      (the branching fraction of the Dz ->f decay in given bin )
 *    - Kbar   (the branching fraction of the Dzb->f decay in given bin )
 *    - c      (bin averaged cosine between Dz ->f and Dzb->f amplitudes)
 *    - s      (bin averaged sine   between Dz ->f and Dzb->f amplitudes)
 *
 *
 *  Alternatively another parameterisation may be used:
 *    - K      ( as before )
 *    - r      = sqrt(Kbar/K) )
 *    - R      = sqrt(s*s + c*c)
 *    - delta  = arctan2(s,c)
 *
 **/

 
#ifndef POLO_FP_SET_D_TO_F_HH
#define POLO_FP_SET_D_TO_F_HH

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"
#include "Mint/MinuitParameterSet.h"

class PoloFPSetDtoF{
  
  private:
  
  TString    _finalStateName;    /**< name of the final state e.g. KpPim */
  int             _binNumber;    /**< phase space bin number  */

  bool _hasCPConjFitPars;           
  /**< Want to use the same fit parameters to describe the CC final state (or -i bins), so need this */

  //The standard parameterisation of hadronic parameters

  MINT::counted_ptr<MINT::FitParameter> _K    ; /**<  Decay rate in bin i of the flavour tagged Dz ->f DP */
  MINT::counted_ptr<MINT::FitParameter> _Kbar ; /**<  Decay rate in bin i of the flavour tagged Dzb->f DP */
  MINT::counted_ptr<MINT::FitParameter> _c    ; /**<  bin averaged cosine between Dz ->f and Dzb->f amplitudes */
  MINT::counted_ptr<MINT::FitParameter> _s    ; /**<  bin averaged   sine between Dz ->f and Dzb->f amplitudes */
  
  //The alternative parameterisation of hadronic parameters

  MINT::counted_ptr<MINT::FitParameter> _r    ; /**< r     = sqrt(_Kbar/_K)  */
  MINT::counted_ptr<MINT::FitParameter> _R    ; /**< R     = sqrt(s*s + c*c) */
  MINT::counted_ptr<MINT::FitParameter> _delta; /**< delta = arctan2(s,c)    */
  
  public:
  
  PoloFPSetDtoF(TString finalState, int binNumber = 0, MINT::MinuitParameterSet* parSet = 0, int paramType = 0); 
  /**< Build a new set of fit parameters for the given final state name and bin number (phase space bin). A bin
  number of zero should be used for phase space integrated measurements, or final states with a zero dimensional
  phase space (e.g. Kpi) */
  
  PoloFPSetDtoF();
  /**< Empty constructor */

  bool isAltParam() const;
  /**< Is the alternative parameterisation being used for the Had Pars */

  bool hasCPConjFPs() const;
  /**< Do the fit parameters represent the CP conjugate final state */
  
  bool warningForNoFPs() const;
  /**< Have any fit parameters been initialised. If not, print a warning and return 0 */

  PoloFPSetDtoF getCPConjFPSet        (TString finalStateName); 
  /**<  Make a new PoloFPSetDtoF for the CP conjugate final state. Can provide
  a new final state name (e.g. KmPip instead of KpPim). If no name is provided, the
  old final state name gets a CC added (e.g. KmPipCC). The functions getK() getKb() getc() gets()
  will be adjusted accordingly for the CP conjugate final state */

  PoloFPSetDtoF getSelfConjCPConjFPSet();
  /**<  This is identical to the getCPConjFPSet() function, but for self-conjugate final states. 
  In this case the final state remains the same i.e. KSpipi -> KSpipi but the bin number changes
  i.e. +3 -> -3 */

  TString getFinalStateName() const;
  /**<  Get the name of the final state */ 
   
  TString getName() const;
  /**<  Get the name of the final state, with the bin number included */  
  
  int binNum(){ return _binNumber; } 
  /**<  Get the bin number */  

  void setKbarToK();
  /**<  Make K and Kbar have the same fit parameter. This is useful for 
  self-conjugate decays that are phase space integrated */  

  double getK   () const;
  /**< return the val of K (BF of Dz->f in phase space bin)   
  If the alternative parameterisation of hadronic parameters is used, this is calculated */

  double getKbar() const;
  /**< return the val of Kbar (BF of Dzb->f in phase space bin)   
  If the alternative parameterisation of hadronic parameters is used, this is calculated */


  double getc   () const;
  /**< return the val of c (bin averaged cosine between Dz ->f and Dzb->f amplitudes). 
  If the alternative parameterisation of hadronic parameters is used, this is calculated */

  double gets   () const;
  /**< return the val of s (bin averaged sine between Dz ->f and Dzb->f amplitudes) 
  If the alternative parameterisation of hadronic parameters is used, this is calculated */

  void makeKandKbarPositive();
  /**< If the vales of the K and Kbar fit parameters are less than zero, change their 
  sign to make them positive. */

  MINT::counted_ptr<MINT::FitParameter> getFitParameterK    ();
  /**< get the fit parameter K */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterKbar ();
  /**< get the fit parameter Kbar */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterc    ();
  /**< get the fit parameter c */
  MINT::counted_ptr<MINT::FitParameter> getFitParameters    ();
  /**< get the fit parameter s */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterr    ();
  /**< get the fit parameter r */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterR    ();
  /**< get the fit parameter R */
  MINT::counted_ptr<MINT::FitParameter> getFitParameterdelta();
  /**< get the fit parameter delta */


  void setK   (double val);
  /**< set the fit parameter K - note that this will set Kbar if hasCPConjFPs() is true */

  void setKbar(double val);
  /**< set the fit parameter Kbar - note that this will set K if hasCPConjFPs() is true */

  void setc   (double val);
  /**< set the fit parameter c  */

  void sets   (double val);
  /**< set the fit parameter s - note that if hasCPConjFPs() is true the actual fit parameter
  (which describes the CP conjugate final state) will be set to -s  */

  void fixK   ();
  /**< fix the fit parameter K */
  void fixKbar();
  /**< fix the fit parameter Kbar */
  void fixc   ();
  /**< fix the fit parameter c */
  void fixs   ();
  /**< fix the fit parameter s */

  void unfixK   ();
  /**< unfix the fit parameter K */
  void unfixKbar();
  /**< unfix the fit parameter Kbar */
  void unfixc   ();
  /**< unfix the fit parameter c */
  void unfixs   ();
  /**< unfix the fit parameter s */

  void print(std::ostream& os = std::cout);
  /**< print some details about me */

  ~PoloFPSetDtoF();
  /**< destructor s */



};

#endif
