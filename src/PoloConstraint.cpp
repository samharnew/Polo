#include "PoloConstraint.h"


PoloConstraint::PoloConstraint(std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies, TVectorD mean, TMatrixD covarience) :
  _dependencies(dependencies),
  _value(mean),
  _mean (mean),
  _covarience(covarience),
  _invcovarience(covarience),
  _name("")
{
  _invcovarience.Invert();  
}
  
PoloConstraint::PoloConstraint() :
  _value(0),
  _mean (0),
  _covarience(0,0),
  _invcovarience(0,0),
  _name("")
{


}


void PoloConstraint::popValsFromFPs(){

  for (int i = 0; i < _value.GetNrows(); i++){
    _value[i] = *_dependencies.at(i);
  }

}


double PoloConstraint::getNeg2LLH(){

  popValsFromFPs();

  //Default behaviour is just a gaussian constraint using the 
  //inverse of the covarience matrix.
  TVectorD residual = _mean - _value;
  double penalty = _invcovarience.Similarity(residual);

  return penalty;
}  

void PoloConstraint::fixFPsToMean(){
  for (unsigned i = 0; i < _dependencies.size(); i++){
    _dependencies.at(i)->setCurrentFitVal(_mean[i]);
    _dependencies.at(i)->fix();
  }
}

void PoloConstraint::setFPsToMean(){
  for (unsigned i = 0; i < _dependencies.size(); i++){
    _dependencies.at(i)->setCurrentFitVal(_mean[i]);
  }  
}

void PoloConstraint::fixFPs(){
  for (unsigned i = 0; i < _dependencies.size(); i++){
    _dependencies.at(i)->fix();
  }  
}

void PoloConstraint::unfixFPs(){
  for (unsigned i = 0; i < _dependencies.size(); i++){
    _dependencies.at(i)->unFix();
  }  
}

void PoloConstraint::genToyFPs (TRandom* random){

  //Stealing some code from RooFit and method from https://en.wikipedia.org/wiki/Multivariate_normal_distribution#Drawing_values_from_the_distribution)
  // - find a matrix A such that AA^T = Sigma (the covarience matrix)
  // - generate a vector, v, of random values, each distiuted to a Gaussian of width 1 mean 0
  // - x = mu + Av 

  TDecompChol tdc(_covarience) ;
  tdc.Decompose() ;
  TMatrixD U = tdc.GetU() ;
  TMatrixD TU(TMatrixD::kTransposed,U) ;    
  
  // Fill cache data
  //cacheData.UT.ResizeTo(TU) ;
  //cacheData.UT = TU ;

  TVectorD x  = _mean;
  TVectorD v  = _mean;

  for (int i = 0; i < v.GetNrows(); i++){
    v[i] = random->Gaus();
  }

  x = _mean + TU*v;

  for (int i = 0; i < v.GetNrows(); i++){
    _dependencies.at(i)->setCurrentFitVal(x[i]);
  }

}


void PoloConstraint::randFPs   (TRandom* random){

  genToyFPs(random);

}

void PoloConstraint::print(){


  std::cout << "PoloConstraint::print()" << std::endl;
  
  std::cout << std::left << std::setw(25) << "Par Name" 
            << std::left << std::setw(14) << "mean" 
            << std::left << std::setw(14) << "err " << std::endl;

  for (unsigned i = 0; i < _dependencies.size(); i++){
    
    std::cout << std::left << std::setw(20) << _dependencies.at(i)->name() 
              << std::left << std::setw(14) << _mean(i)
              << std::left << std::setw(14) << sqrt(_covarience(i,i)) << std::endl;    

  }  

  std::cout << "-----------------------------" << std::endl;  

}


std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloConstraint::getDependencies(){
  return _dependencies;
}

PoloConstraint* PoloConstraint::clone(){
  return new PoloConstraint(*this);
}

void PoloConstraint::setName(TString val){
  _name = val;
}

TString PoloConstraint::getName(){
  return _name;
}

PoloConstraint::~PoloConstraint(){

}
