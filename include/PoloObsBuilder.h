/**
 * <B> PoloObsBuilder </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *
 *  This class just has a load of static functions that makes it very fast to build observables.
 *
 *  
 **/

 
#ifndef POLO_OBS_BUILDER
#define POLO_OBS_BUILDER

#include "PoloObsSet.h"
#include "PoloFPSetDtoFBinned.h"
#include "PoloFPSetDMixing.h"
#include "PoloFPSetBtoDh.h"
#include "PoloFPSetNorm.h"

#include "PoloObsSTYield.h"
#include "PoloObsDTYield.h"
#include "PoloObsBtoDhYield.h"
#include "PoloObsDstTaggedYield.h"


class PoloObsBuilder {
    
  public:

  PoloObsBuilder();
  
  static PoloObsSet buildSTObsSet     ( PoloFPSetDtoFBinned& dtof, PoloFPSetDMixing& dMix   , PoloFPSetNorm& nDDb );
  static PoloObsSet buildDTObsSet     ( PoloFPSetDtoFBinned& dtof, PoloFPSetDtoFBinned& dtog, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDDb );
  static PoloObsSet buildBptoDhpObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetBtoDh& bToDh, PoloFPSetNorm& norm );
  static PoloObsSet buildBmtoDhmObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetBtoDh& bToDh, PoloFPSetNorm& norm );

  static PoloObsSet buildDstpTaggedObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetDMixing& dMix, PoloFPSetNorm& norm, double tmin = 0.0, double tmax=50.0 );
  static PoloObsSet buildDstmTaggedObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetDMixing& dMix, PoloFPSetNorm& norm, double tmin = 0.0, double tmax=50.0 );

  static PoloObsSet buildDstpTaggedObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetDMixing& dMix, PoloFPSetNorm& norm, std::vector<double> binEdges );
  static PoloObsSet buildDstmTaggedObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetDMixing& dMix, PoloFPSetNorm& norm, std::vector<double> binEdges );


  ~PoloObsBuilder();

};


#endif
