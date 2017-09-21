#include "PoloConDzDecBF.h"


PoloConDzDecBF::PoloConDzDecBF( PoloFPSetDtoFBinned& dToF, PoloMeas meas ){
  init( dToF.getFPSetFromBinNum(0), meas );
}



PoloConDzDecBF::PoloConDzDecBF( PoloFPSetDtoF& dToF, PoloMeas meas ){
  init( dToF , meas);
}


void PoloConDzDecBF::init( PoloFPSetDtoF      & dToF, PoloMeas meas ){

  _value        .ResizeTo(1);
  _mean         .ResizeTo(1);
  _covarience   .ResizeTo(1,1);
  _invcovarience.ResizeTo(1,1);
  
  if ( dToF.hasCPConjFPs() ){
    _dependencies.push_back( dToF    .getFitParameterKbar()     );
  }
  else{
    _dependencies.push_back( dToF    .getFitParameterK()     );
  }

  if (_dependencies.at(0) == 0){
    std::cout << "ERROR: The fit parameter you are trying to constrain doesn't exist." << std::endl;
  }

  _mean[0] = meas.getVal(); 
  _covarience(0,0) = meas.getErr()*meas.getErr(); 

  _invcovarience = _covarience;
  _invcovarience.Invert();  
   
}




PoloConstraint* PoloConDzDecBF::clone(){

  return new PoloConDzDecBF(*this);

}

PoloConDzDecBF::~PoloConDzDecBF(){



}



