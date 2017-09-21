/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  Contrains the ki and kbi parameters using various amplitude models. 
 *  This is for the Equal Delta delta D binning.
 *
 **/

 
#ifndef POLO_CON_K0PIPI_KI_CLEO
#define POLO_CON_K0PIPI_KI_CLEO


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


class PoloConK0PiPiKiKbiCleo : public PoloConstraint {
  
  protected:
  

  public:

  PoloConK0PiPiKiKbiCleo( PoloFPSetDtoFBinned& dToKSpipi, PoloFPSetDtoFBinned& dToKLpipi, double KSpipiBF, double KLpipiBF );
  
  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  virtual ~PoloConK0PiPiKiKbiCleo();
  /**< destructor */ 

};


#endif 