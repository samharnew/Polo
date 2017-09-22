/**
 * <B> PoloObsSTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * An observable to describe the yield of B->Dh, D->f decays. Should probably update this
 * to include D-mixing at some point.
 *  
 **/

 
#ifndef POLO_OBS_B_TO_DH_YIELD
#define POLO_OBS_B_TO_DH_YIELD

#include "PoloObsAbs.h"
#include "PoloFPSetDtoF.h"
#include "PoloFPSetBtoDh.h"
#include "PoloFPSetDMixing.h"
#include "PoloFPSetNorm.h"

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"


class PoloObsBtoDhYield : public PoloObsAbs {
  
  PoloFPSetDtoF   _dToF;
  PoloFPSetBtoDh  _bToDh;
  PoloFPSetNorm   _norm;
  
  bool _chargeConj;

  public:
  
  PoloObsBtoDhYield(PoloFPSetDtoF& dToF, PoloFPSetBtoDh& bToDh, PoloFPSetNorm& norm, bool chargeConj = 0);
  
  virtual double getVal();

  virtual PoloObsAbs* clone();

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();

  void print(TString prefix);

  virtual ~PoloObsBtoDhYield();

};


#endif
