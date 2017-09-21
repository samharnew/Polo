/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Feb 2016
 *
 *  
 **/

 
#ifndef BINNED_D_TO_F_DECAY_FIT_PARAMS_HH
#define BINNED_D_TO_F_DECAY_FIT_PARAMS_HH

#include "Mint/FitParameter.h"
#include "PoloFPSetDtoF.h"
#include "Mint/MinuitParameterSet.h"

class PoloFPSetDtoFBinned{
  
  private:

  std::vector<PoloFPSetDtoF> _DtoFAmpFitParams;
  /**< one PoloFPSetDtoF for each phase space bin for this final state */

  public:
  
  PoloFPSetDtoFBinned( TString finalStateName, int nBins = 0, bool selfconj = false, MINT::MinuitParameterSet* parSet = 0, int paramType = 0);
  /**< Contructor to make a set of fit parameters that describe the hadronic parameters of a binned final state. 
  This requires a final state name, and the number of bins. Using nBins = 0 assumes a phase space integrated 
  final state. Can also use the selfconj flag if the final state is self conjugate e.g. KSpipi. In this case
  nBins bin PAIRS will be made e.g. nBins x 2 bins in total. The bin with bin number +i is paired with -i. These
  share the same fit parameters (although they result in different hadronic parameters i.e. 

    - K_+i    = Kbar_-i
    - Kbar_+i = K_-i
    - c_+i    =  c_-i
    - s_+i    = -s_-i

  If the final state is self conjugate AND phase space integrated e.g. nBins = 0. s_i is fixed to zero. */

  PoloFPSetDtoFBinned( std::vector<PoloFPSetDtoF> fpSetDtoF );
  /**< Alternative constructor that takes a vector of PoloFPSetDtoF */

  PoloFPSetDtoFBinned getCCFinalState(TString finalStateName = "");
  /**< Retrieve a new PoloFPSetDtoFBinned object that describes the charge conjugate final state.
  e.g. if the object describes K+pi-, this would return the hadronic parameters for K-pi+. By default
  "CC" will get added to the end of the final state name, but there is an option to pass a new name */

  PoloFPSetDtoF& getFPSetFromBinNum(int binNum);
  /**< retrieve a PoloFPSetDtoF from its phase space bin number.  */

  PoloFPSetDtoF& getFPSet          (int i);
  /**< retrieve a PoloFPSetDtoF from its index. */

  void makeKKbarPositive();
  /**< Loop over all K and Kbar fit parameters and make them positive. */

  void cpPlusES();
  /**< Make this final state a CP+ eigenstate by fixing ci to +1. Note that this only makes sense 
  for self-conjugate phase space integrated final states, so will show an error if this isn't the case */

  void cpMinusES();
  /**< Make this final state a CP- eigenstate by fixing ci to -1. Note that this only makes sense 
  for self-conjugate phase space integrated final states, so will show an error if this isn't the case */

  void dzES();
  /**< Make this final state a dz flavour eigenstate by fixing kb to zero and ci and si to zero. 
  Note that this only makes sense for a phase space integrated final states, 
  so will show an error if this isn't the case */

  void dzbES();
  /**< Make this final state a dz flavour eigenstate by fixing k to zero and ci and si to zero. 
  Note that this only makes sense for a phase space integrated final states, 
  so will show an error if this isn't the case */

  double calTotK();
  /**< Calculate K for the entire phase space (or all bins that have been added to the object) */

  double calTotKbar();  
  /**< Calculate Kbar for the entire phase space (or all bins that have been added to the object) */

  double calTotC();
  /**< Calculate c for the entire phase space (or all bins that have been added to the object) */

  double calTotS();
  /**< Calculate s for the entire phase space (or all bins that have been added to the object) */

  void fixAllS(double val = -99.9);
  /**< Fix the value of s for all phase space bins. If not value is provided, fix to current value */

  void fixAllC(double val = -99.9);
  /**< Fix the value of c for all phase space bins. If not value is provided, fix to current value */

  int size();
  /**< How many phase space bins are there */

  void print(std::ostream& os = std::cout);
  /**< Print some info about this object */

  void printSimple(std::ostream& os = std::cout);
  /**< Print some basic info about this object */

  ~PoloFPSetDtoFBinned();
  /**< Destructor */

};

#endif
