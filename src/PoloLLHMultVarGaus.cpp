#include "PoloLLHMultVarGaus.h"



PoloLLHMultVarGaus::PoloLLHMultVarGaus(std::vector<PoloObsAbs*> obs, TVectorD measVals, TMatrixD covMatrix) :
  PoloLLHAbs   ( obs.at(0)->getName() + "_MVGausMeas" ),
  _obs         ( obs       ),
  _measVals    ( measVals  ),
  _covMatrix   ( covMatrix ),
  _invCovMatrix( covMatrix )
{

  _invCovMatrix.Invert();

}

PoloLLHMultVarGaus::PoloLLHMultVarGaus( std::vector<PoloObsAbs*> obs, TVectorD measVals, TVectorD measErrs, TMatrixD corMatrix) :
  PoloLLHAbs   ( obs.at(0)->getName() + "_MVGausMeas" ),
  _obs         ( obs       ),
  _measVals    ( measVals  ),
  _covMatrix   ( corMatrix ),
  _invCovMatrix( corMatrix )
{
  
  int nobs = _obs.size();

  for (int i = 0; i < nobs; i++){
    for (int j = 0; j < nobs; j++){
      _covMatrix(i,j) = measErrs(i)*measErrs(j)*corMatrix(i,j);
    }    
  }

  _invCovMatrix = _covMatrix;
  _invCovMatrix.Invert();

}



double PoloLLHMultVarGaus::getProb(){
  return getNeg2LLH();

}

TVectorD PoloLLHMultVarGaus::getExpVals(){
  TVectorD vals(_obs.size());
  for (unsigned i = 0; i < _obs.size(); i++){
    vals(i) = _obs.at(i)->getVal();
  }  
  return vals;
}

double PoloLLHMultVarGaus::getNeg2LLH(){

  TVectorD expVal = getExpVals();
  
  TVectorD res = expVal - _measVals;

  return _invCovMatrix.Similarity(res);

}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloLLHMultVarGaus::getDependencies(){
  
  std::vector< MINT::counted_ptr<MINT::FitParameter> > allDeps;

  for (unsigned i = 0; i < _obs.size(); i++){
    std::vector< MINT::counted_ptr<MINT::FitParameter> > deps;
    for (unsigned j = 0; j < deps.size(); j++){
      allDeps.push_back( deps.at(j) );
    }
  }

  return allDeps;

}

void   PoloLLHMultVarGaus::genToyMeas(TRandom* random){

  //Stealing some code from RooFit and method from https://en.wikipedia.org/wiki/Multivariate_normal_distribution#Drawing_values_from_the_distribution)
  // - find a matrix A such that AA^T = Sigma (the covarience matrix)
  // - generate a vector, v, of random values, each distiuted to a Gaussian of width 1 mean 0
  // - x = mu + Av 

  TDecompChol tdc(_covMatrix) ;
  tdc.Decompose() ;
  TMatrixD U = tdc.GetU() ;
  TMatrixD TU(TMatrixD::kTransposed,U) ;    
  
  // Fill cache data
  //cacheData.UT.ResizeTo(TU) ;
  //cacheData.UT = TU ;
  
  TVectorD expVal = getExpVals();

  TVectorD x  = expVal;
  TVectorD v  = expVal;

  for (int i = 0; i < v.GetNrows(); i++){
    v[i] = random->Gaus();
  }

  x = expVal + TU*v;

  for (int i = 0; i < v.GetNrows(); i++){
    _measVals(i) = x[i];
  }

}

void PoloLLHMultVarGaus::printOneliner(){
  
  for (int i = 0; i < _measVals.GetNrows(); i++){
    std::cout << _obs.at(i)->getName() << "   " 
              << _measVals(i) << " ± " << sqrt(_covMatrix(i,i)) << " ( exp: " << _obs.at(i)->getVal() << " ) " << std::endl;
  }

}

PoloLLHAbs*  PoloLLHMultVarGaus::clone(){
  return new PoloLLHMultVarGaus(*this);
}

PoloLLHMultVarGaus::~PoloLLHMultVarGaus(){
  //delete _obs;
}






