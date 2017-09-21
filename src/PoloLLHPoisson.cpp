#include "PoloLLHPoisson.h"



PoloLLHPoisson::PoloLLHPoisson(PoloObsAbs& obs, double measYield) :
  PoloLLHAbs( obs.getName() + "_poisMeas" ),
  _obs( obs.clone() ),
  _measYield( measYield )
{

}

double PoloLLHPoisson::getProb(){
  return _obs->getPoissonProb(_measYield);
}

double PoloLLHPoisson::getNeg2LLH(){
  return _obs->getNeg2LogPoissonProb(_measYield);
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloLLHPoisson::getDependencies(){
  
  return _obs->getDependencies();

}

void   PoloLLHPoisson::genToyMeas(TRandom* random){
  _measYield = _obs->genPoisson(random);
}

PoloLLHAbs*  PoloLLHPoisson::clone(){
	return new PoloLLHPoisson(*this);
}

void PoloLLHPoisson::printOneliner(){

  std::cout << getName() << "   " 
            << _measYield << " ( exp: " << _obs->getVal() << " ) " << std::endl;

}


PoloLLHPoisson::~PoloLLHPoisson(){
  //delete _obs;
}






