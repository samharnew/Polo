/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *
 **/

 
#ifndef POLO_CON_CP_EVEN_FRAC
#define POLO_CON_CP_EVEN_FRAC

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
#include "PoloMeas.h"


class PoloConCPEvenFrac : public PoloConstraint {
  
  protected:
  
  void init(PoloFPSetDtoF      & dToF, PoloMeas meas);

  public:

  PoloConCPEvenFrac( PoloFPSetDtoFBinned& dToF, PoloMeas meas );
  PoloConCPEvenFrac( PoloFPSetDtoF      & dToF, PoloMeas meas );
  
  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  virtual ~PoloConCPEvenFrac();
  /**< destructor */ 

};


#endif 