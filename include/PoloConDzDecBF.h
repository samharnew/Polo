/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *
 **/

 
#ifndef POLO_CON_D_TO_F_BF
#define POLO_CON_D_TO_F_BF

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


class PoloConDzDecBF : public PoloConstraint {
  
  protected:
  
  void init(PoloFPSetDtoF      & dToF, PoloMeas meas);

  public:

  PoloConDzDecBF( PoloFPSetDtoFBinned& dToF, PoloMeas meas );
  PoloConDzDecBF( PoloFPSetDtoF      & dToF, PoloMeas meas );
  
  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  virtual ~PoloConDzDecBF();
  /**< destructor */ 

};


#endif 