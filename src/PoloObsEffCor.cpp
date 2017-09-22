#include "PoloObsEffCor.h"

PoloObsEffCor::PoloObsEffCor(PoloObsAbs& obs, PoloMeas effMeas ) {

  setPoloObsID( obs );

  TString prefix = "effCor___";  
  TString name   = obs.getName();
  setName(prefix + name);

  addObs(obs, effMeas);
  
}


PoloObsEffCor::PoloObsEffCor( PoloObsAbs& obs ) {

  setPoloObsID( obs );

  TString prefix = "migCor___";  
  TString name   = obs.getName();
  setName(prefix + name);


}

void PoloObsEffCor::addObs(PoloObsAbs& obs, PoloMeas effMeas){

  _obs.push_back(obs.clone());
  _eff.push_back(effMeas    );

}


double PoloObsEffCor::getVal(){
  double val = 0.0;
  for (unsigned i = 0; i < _obs.size(); i++){
    val += (_obs.at(i)->getVal() * _eff.at(i).getVal());
  }
  return val;
}


PoloObsAbs* PoloObsEffCor::clone(){
  return new PoloObsEffCor(*this);
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsEffCor::getDependencies(){

  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;

  for (unsigned i = 0; i < _obs.size(); i++){
    
    std::vector< MINT::counted_ptr<MINT::FitParameter> > temp = _obs.at(i)->getDependencies();
     
    for (unsigned j = 0; j < temp.size(); j++){
      dependencies.push_back(temp.at(j));
    }

  }

  return dependencies; 

}

void PoloObsEffCor::print(TString prefix){

  PoloObsAbs::print(prefix);
  for (unsigned i = 0; i < _obs.size(); i++){
    std::cout << prefix << _eff.at(i).getVal() << " x " << std::endl;
    TString prefixi = prefix + "    ";
    _obs.at(i)->print(prefixi);
  }

}

PoloObsEffCor::~PoloObsEffCor(){
  
}