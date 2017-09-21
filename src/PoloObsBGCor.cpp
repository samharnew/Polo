#include "PoloObsBGCor.h"

PoloObsBGCor::PoloObsBGCor(PoloObsAbs& obs, PoloMeas& bgMeas ) :
  _obs( obs.clone() ),
  _bkg( bgMeas      )
{
  
  setPoloObsID( obs );

  TString prefix = "bgCor___";  
  TString name   = obs.getName();
  setName(prefix + name);  

}

double PoloObsBGCor::getVal(){
  return _obs->getVal() + _bkg.getVal();
}


PoloObsAbs* PoloObsBGCor::clone(){
  return new PoloObsBGCor(*this);
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsBGCor::getDependencies(){
  return _obs->getDependencies();
}

void PoloObsBGCor::print(TString prefix){

  PoloObsAbs::print(prefix);
  _obs->print(prefix + "    ");


}


PoloObsBGCor::~PoloObsBGCor(){

}
