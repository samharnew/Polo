/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *
 **/

 
#ifndef POLO_CON_DMIXING
#define POLO_CON_DMIXING

#include "TVectorD.h"
#include "TMatrixD.h"
#include "TRandom.h"
#include "TDecompChol.h"

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"

#include "TDecompChol.h"

#include "PoloConstraint.h"
#include "PoloFPSetDMixing.h"
#include "PoloMeas.h"


class PoloConDMixing : public PoloConstraint {
  
  protected:
  
  public:

  PoloConDMixing( PoloFPSetDMixing      & fpsMix, PoloMeas x, PoloMeas y, double correlation );
  
  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  virtual ~PoloConDMixing();
  /**< destructor */ 

};


#endif 