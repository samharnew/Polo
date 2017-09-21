#include "PoloConCPEvenFrac.h"


PoloConCPEvenFrac::PoloConCPEvenFrac( PoloFPSetDtoFBinned& dToF, PoloMeas meas ){
  init( dToF.getFPSetFromBinNum(0), meas );
}



PoloConCPEvenFrac::PoloConCPEvenFrac( PoloFPSetDtoF& dToF, PoloMeas meas ){
  init( dToF , meas);
}


void PoloConCPEvenFrac::init( PoloFPSetDtoF      & dToF, PoloMeas meas ){

  _value        .ResizeTo(1);
  _mean         .ResizeTo(1);
  _covarience   .ResizeTo(1,1);
  _invcovarience.ResizeTo(1,1);
  
  _dependencies.push_back( dToF    .getFitParameterc()     );
  
  if (_dependencies.at(0) == 0){
    std::cout << "ERROR: The fit parameter you are trying to constrain doesn't exist." << std::endl;
  }

  _mean[0] = (2.0*meas.getVal()) - 1.0; //need to get ci from F+ i.e. ci = (2F+ - 1) 
  _covarience(0,0) = meas.getErr()*meas.getErr()*4.0; 

  _invcovarience = _covarience;
  _invcovarience.Invert();  
   
}




PoloConstraint* PoloConCPEvenFrac::clone(){

  return new PoloConCPEvenFrac(*this);

}

PoloConCPEvenFrac::~PoloConCPEvenFrac(){



}



