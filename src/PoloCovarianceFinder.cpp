#include "PoloCovarianceFinder.h"

PoloCovarianceFinder::PoloCovarianceFinder(int dim) :
  _dim     (dim),
  _expij   (dim, dim),
  _expi    (dim     ),
  _nEntries(0       )
{

}

void PoloCovarianceFinder::addEntry( std::vector<double> vals ){
  
  if (_dim != (int)vals.size()){
  	std::cout << "ERROR! PoloCovarianceFinder. You have provided a vector of the wrong dimension" << std::endl;
  	return;
  }
  
  for (int i = 0; i < _dim; i++){
    _expi (i  ) += vals.at(i);
    for (int j = 0; j < _dim; j++){
      _expij (i,j) += vals.at(i)*vals.at(j);
    }
  }
  
  _nEntries++;
}

TMatrixD PoloCovarianceFinder::getCovarianceMatrix(){
  TMatrixD cov(_dim,_dim);
  for (int i = 0; i < _dim; i++){
    for (int j = 0; j < _dim; j++){
      cov(i,j) = getCovariance(i,j);
    }
  }
  return cov;
}

TMatrixD PoloCovarianceFinder::getCorrelationMatrix(){
  TMatrixD cor(_dim,_dim);
  for (int i = 0; i < _dim; i++){
    for (int j = 0; j < _dim; j++){
      cor(i,j) = getCorrelation(i,j);
    }
  }
  return cor;
}

double PoloCovarianceFinder::getMean   (int i){
  return _expi (i  )/double(_nEntries);
}


double PoloCovarianceFinder::getCovariance (int i, int j){
  double expij = _expij(i,j)/double(_nEntries);
  double expi  = _expi (i  )/double(_nEntries);
  double expj  = _expi (j  )/double(_nEntries);
  return expij - expi*expj;
}

double PoloCovarianceFinder::getVariance   (int i){
  return getCovariance(i,i);
}

double PoloCovarianceFinder::getCorrelation(int i, int j){
  return getCovariance(i,j)/sqrt(getVariance(i)*getVariance(j));
}


PoloCovarianceFinder::~PoloCovarianceFinder(){

}

