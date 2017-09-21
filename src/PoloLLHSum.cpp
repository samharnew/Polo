#include "PoloLLHSum.h"

PoloLLHSum::PoloLLHSum(){

}


PoloLLHSum::PoloLLHSum(PoloLLHAbs* llh1){
  _llh.push_back(llh1->clone());
}

PoloLLHSum::PoloLLHSum(PoloLLHAbs* llh1, PoloLLHAbs* llh2){
  _llh.push_back(llh1->clone());
  _llh.push_back(llh2->clone());
}

PoloLLHSum::PoloLLHSum(PoloLLHAbs* llh1, PoloLLHAbs* llh2, PoloLLHAbs* llh3){
  _llh.push_back(llh1->clone());
  _llh.push_back(llh2->clone());
  _llh.push_back(llh3->clone());
}

double PoloLLHSum::getNeg2LLH(){
  double n2llh = 0.0;
  for (unsigned i = 0; i < _llh.size(); i++){
    n2llh += _llh.at(i)->getNeg2LLH();
  }
  return n2llh;
}

void PoloLLHSum::addLLH(PoloLLHAbs* llh){
  _llh.push_back(llh->clone());
}


std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloLLHSum::getDependencies(){
  
  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;

  for (unsigned i = 0; i < _llh.size(); i++){
    
    std::vector< MINT::counted_ptr<MINT::FitParameter> > temp = _llh.at(i)->getDependencies();
     
    for (unsigned j = 0; j < temp.size(); j++){
      dependencies.push_back(temp.at(j));
    }

  }

  return dependencies;

}

PoloLLHAbs* PoloLLHSum::clone(){
  return new PoloLLHSum(*this);
}

void PoloLLHSum::printOneliner(){
  for (unsigned i = 0; i < _llh.size(); i++){
    _llh.at(i)->printOneliner();
  }
}

void   PoloLLHSum::genToyMeas(TRandom* random){
  for (unsigned i = 0; i < _llh.size(); i++){
    _llh.at(i)->genToyMeas(random);
  }
}

PoloLLHSum::~PoloLLHSum(){

}
