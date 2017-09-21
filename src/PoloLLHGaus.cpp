#include "PoloLLHGaus.h"



PoloLLHGaus::PoloLLHGaus(PoloObsAbs& obs, double measVal, double measErr) :
  PoloLLHAbs( obs.getName() + "_meas" ),
  _obs( obs.clone() ),
  _measVal( measVal ),
  _measErr( measErr )
{

}


double PoloLLHGaus::getNeg2LLH(){
  return _obs->getNeg2LogGausProb(_measVal, _measErr);
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloLLHGaus::getDependencies(){
  
  return _obs->getDependencies();

}


void   PoloLLHGaus::genToyMeas(TRandom* random){
  _measVal = _obs->genGaus(_measErr, random);
}

PoloLLHAbs*  PoloLLHGaus::clone(){
  return new PoloLLHGaus(*this);
}


void PoloLLHGaus::printOneliner(){

  std::cout << getName() << "   " 
            << _measVal << " ± " << _measErr << " ( exp: " << _obs->getVal() << " ) " << std::endl;

}


PoloLLHGaus::~PoloLLHGaus(){
  //delete _obs;
}






