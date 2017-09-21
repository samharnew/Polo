/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *
 **/

 
#ifndef POLO_CON_QUAZI_FLAV
#define POLO_CON_QUAZI_FLAV

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


class PoloConQuaziFlav : public PoloConstraint {
  
  protected:
  
  void init(PoloFPSetDtoF      & dToKmPi, PoloFPSetDtoF      & dToKmPiPi0, PoloFPSetDtoF      & dToKmPiPiPi);

  public:

  PoloConQuaziFlav( PoloFPSetDtoFBinned& dToKmPi, PoloFPSetDtoFBinned& dToKmPiPi0, PoloFPSetDtoFBinned& dToKmPiPiPi );
  PoloConQuaziFlav( PoloFPSetDtoF      & dToKmPi, PoloFPSetDtoF      & dToKmPiPi0, PoloFPSetDtoF      & dToKmPiPiPi );
  
  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  virtual ~PoloConQuaziFlav();
  /**< destructor */ 

};


#endif 


