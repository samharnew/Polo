/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  Contrains the ci and si parameters using the constrains from the
 *  CLEO measurement. This includes correlations. This is for the 
 *  Equal Delta delta D binning.
 *
 **/

 
#ifndef POLO_CON_K0PIPI_CISI_CLEO
#define POLO_CON_K0PIPI_CISI_CLEO

#include "TVectorD.h"
#include "TMatrixD.h"
#include "TRandom.h"
#include "TDecompChol.h"

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"

#include "TDecompChol.h"

#include "PoloConstraint.h"
#include "PoloFPSetDtoF.h"
#include "PoloFPSetDtoFBinned.h"
#include "PoloInputsK0PiPi.h"


class PoloConK0PiPiCiSiCleo : public PoloConstraint {
  
  protected:
  

  public:

  PoloConK0PiPiCiSiCleo( PoloFPSetDtoFBinned& dToKSpipi, PoloFPSetDtoFBinned& dToKLpipi, TString opt = "" );
  
  bool coherenceFactorsLessThanOne();

  virtual void genToyFPs (TRandom* random);
  /**< this is like the default generation technique in PoloConstraint (draw
  instances from a multivariate gaussian) but rejects unphysical cases with 
  ci^2 + si^2 > 1 */ 


  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  virtual ~PoloConK0PiPiCiSiCleo();
  /**< destructor */ 

};


#endif 