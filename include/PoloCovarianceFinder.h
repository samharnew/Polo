/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *
 *
 **/

 
#ifndef POLO_COV_FINDER
#define POLO_COV_FINDER

#include "TVectorD.h"
#include "TMatrixD.h"
#include "TRandom.h"
#include "TDecompChol.h"

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"


class PoloCovarianceFinder {
  
  protected:

  int      _dim;
  TMatrixD _expij;
  TVectorD _expi;
  int      _nEntries;

  public:

  PoloCovarianceFinder(int dim);
  /**< finding a Covariance matrix of dimension 'dim' */ 

  void addEntry(std::vector<double> vals);  
  /**< add a vector of values */ 

  TMatrixD getCovarianceMatrix();
  /**< get Covariance matrix */ 

  TMatrixD getCorrelationMatrix();
  /**< get Covariance matrix */ 

  double getCovariance (int i, int j);
  /**< get Covariance matrix element ij */ 

  double getVariance   (int i);
  /**< get varience of element i */ 

  double getMean   (int i);
  /**< get mean of element i */ 

  double getCorrelation(int i, int j);
  /**< get correlation coefficient between elements i and j */ 

  ~PoloCovarianceFinder();
  /**< destructor */ 

};


#endif 


