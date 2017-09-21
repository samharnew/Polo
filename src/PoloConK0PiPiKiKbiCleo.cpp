#include "PoloConK0PiPiKiKbiCleo.h"


PoloConK0PiPiKiKbiCleo::PoloConK0PiPiKiKbiCleo( PoloFPSetDtoFBinned& dToKSpipi, PoloFPSetDtoFBinned& dToKLpipi, double KSpipiBF, double KLpipiBF){
  
  PoloInputsK0PiPi cleoInputs;

  int nKSbins = dToKSpipi.size()/2;
  int nKLbins = dToKLpipi.size()/2;

  int dim = nKSbins*2 + nKLbins*2; //each decay has a constraint for both Ki and Kibar

  _value        .ResizeTo(dim);
  _mean         .ResizeTo(dim);
  _covarience   .ResizeTo(dim, dim);
  _invcovarience.ResizeTo(dim, dim);


  if (nKSbins != 8 || nKLbins != 8){
    std::cout << "ERROR: This ci si constraint assumes 8 bins pairs for both dToKSpipi and dToKLpipi" << std::endl;
  }

  //numering goes like this... (for 8 bins)

  //KS Ki
  //KS Kibar
  //KL Ki 
  //KL Kibar
  
  for (int i = 1; i <= nKSbins; i++){
    _dependencies.push_back( dToKSpipi.getFPSetFromBinNum(i).getFitParameterK() );
  }
  for (int i = 1; i <= nKSbins; i++){
    _dependencies.push_back( dToKSpipi.getFPSetFromBinNum(i).getFitParameterKbar()    );
  }
  for (int i = 1; i <= nKLbins; i++){
    _dependencies.push_back( dToKLpipi.getFPSetFromBinNum(i).getFitParameterK() );
  }
  for (int i = 1; i <= nKLbins; i++){
    _dependencies.push_back( dToKLpipi.getFPSetFromBinNum(i).getFitParameterKbar()    );
  }

  for (int i = 1; i <= nKSbins; i++){ 
    int id = i-1;
    _mean[id]           = cleoInputs.getFi(i)*KSpipiBF ;  
    _covarience[id][id] = cleoInputs.getFiError(i)*cleoInputs.getFiError(i)*KSpipiBF*KSpipiBF;  
  }
  for (int i = 1; i <= nKSbins; i++){
    int id = i+7;
    _mean[id]           = cleoInputs.getFibar(i)*KSpipiBF;  
    _covarience[id][id] = cleoInputs.getFibarError(i)*cleoInputs.getFibarError(i)*KSpipiBF*KSpipiBF;   
  }
  for (int i = 1; i <= nKLbins; i++){
    int id = i+15;
    _mean[id]           = cleoInputs.getFiprime(i)*KLpipiBF;  
    _covarience[id][id] = cleoInputs.getFiprimeError(i)*cleoInputs.getFiprimeError(i)*KLpipiBF*KLpipiBF;    
  }
  for (int i = 1; i <= nKLbins; i++){
    int id = i+23;
    _mean[id]           = cleoInputs.getFibarprime(i)*KLpipiBF;  
    _covarience[id][id] = cleoInputs.getFibarprimeError(i)*cleoInputs.getFibarprimeError(i)*KLpipiBF*KLpipiBF;    
  }

  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      if (i == j) continue;
      _covarience[i][j] = 0.0;  
    }
  }
 
  _invcovarience = _covarience;
  _invcovarience.Invert(); 

}
  

PoloConstraint* PoloConK0PiPiKiKbiCleo::clone(){

  return new PoloConK0PiPiKiKbiCleo(*this);

}

PoloConK0PiPiKiKbiCleo::~PoloConK0PiPiKiKbiCleo(){



}






