 #include "PoloObsBuilder.h"


PoloObsSet PoloObsBuilder::buildSTObsSet     ( PoloFPSetDtoFBinned& dtof, PoloFPSetDMixing& dMix   , PoloFPSetNorm& nDDb ){
  
  PoloObsSet obsSet;
  for (int i = 0; i < dtof.size(); i++){
  	PoloObsSTYield obs( dtof.getFPSet(i), dMix, nDDb);
  	obsSet.addObs(obs);
  }
  return obsSet;

}

PoloObsSet PoloObsBuilder::buildDTObsSet     ( PoloFPSetDtoFBinned& dtof, PoloFPSetDtoFBinned& dtog, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDDb ){

  PoloObsSet obsSet;
  for (int i = 0; i < dtof.size(); i++){
    for (int j = 0; j < dtog.size(); j++){
  	  PoloObsDTYield obs( dtof.getFPSet(i), dtog.getFPSet(j), dMix, nDDb);
  	  obsSet.addObs(obs);
  	}
  }
  return obsSet;

}

PoloObsSet PoloObsBuilder::buildBptoDhpObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetBtoDh& bToDh, PoloFPSetNorm& norm ){

  PoloObsSet obsSet;
  for (int i = 0; i < dtof.size(); i++){
  	PoloObsBtoDhYield obs( dtof.getFPSet(i), bToDh, norm, 0);
  	obsSet.addObs(obs);
  }
  return obsSet;

}

PoloObsSet PoloObsBuilder::buildBmtoDhmObsSet( PoloFPSetDtoFBinned& dtof, PoloFPSetBtoDh& bToDh, PoloFPSetNorm& norm ){

  PoloObsSet obsSet;
  for (int i = 0; i < dtof.size(); i++){
  	PoloObsBtoDhYield obs( dtof.getFPSet(i), bToDh, norm, 1);
  	obsSet.addObs(obs);
  }
  return obsSet;

}



