#include "PoloObsSum.h"


PoloObsSum::PoloObsSum(PoloObsAbs& obs1){
  
  setPoloObsID( obs1 );

  TString prefix = "obsSum___";  
  TString name   = obs1.getName();
  setName(prefix + name);

  addObs(obs1);

}

PoloObsSum::PoloObsSum(PoloObsAbs& obs1, PoloObsAbs& obs2){

  setPoloObsID( obs1 );

  TString prefix = "obsSum___";  
  TString name   = obs1.getName();
  setName(prefix + name);

  addObs(obs1);
  addObs(obs2);
  
}

PoloObsSum::PoloObsSum(PoloObsAbs& obs1, PoloObsAbs& obs2, PoloObsAbs& obs3){

  setPoloObsID( obs1 );

  TString prefix = "obsSum___";  
  TString name   = obs1.getName();
  setName(prefix + name);

  addObs(obs1);
  addObs(obs2);
  addObs(obs3);
  
}


void PoloObsSum::addObs(PoloObsAbs& obs){
  _obs.push_back(obs.clone());
}


double PoloObsSum::getVal(){
  double sum = 0.0;
  for (unsigned i = 0; i < _obs.size(); i++){
    sum += _obs.at(i)->getVal();
  }
  return sum;
}


PoloObsAbs* PoloObsSum::clone(){
  return new PoloObsSum(*this);
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsSum::getDependencies(){
  
  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;

  for (unsigned i = 0; i < _obs.size(); i++){
    
    std::vector< MINT::counted_ptr<MINT::FitParameter> > temp = _obs.at(i)->getDependencies();
     
    for (unsigned j = 0; j < temp.size(); j++){
      dependencies.push_back(temp.at(j));
    }

  }

  return dependencies; 

}

void PoloObsSum::print(TString prefix){

  PoloObsAbs::print(prefix);
  for (unsigned i = 0; i < _obs.size(); i++){
    TString prefixi = prefix + "    ";
    _obs.at(i)->print(prefixi);
  }

}

PoloObsSum::~PoloObsSum(){
  
}
