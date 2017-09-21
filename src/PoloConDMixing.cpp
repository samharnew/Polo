#include "PoloConDMixing.h"


PoloConDMixing::PoloConDMixing( PoloFPSetDMixing      & fpsMix, PoloMeas x, PoloMeas y, double correlation  ){

  _value        .ResizeTo(2);
  _mean         .ResizeTo(2);
  _covarience   .ResizeTo(2,2);
  _invcovarience.ResizeTo(2,2);
  
  _dependencies.push_back( fpsMix    .getFitParameterX()     );
  _dependencies.push_back( fpsMix    .getFitParameterY()     );

  _mean[0] = x.getVal();
  _mean[1] = y.getVal();           

  _covarience(0,0) = x.getErr()*x.getErr();
  _covarience(1,1) = y.getErr()*y.getErr();
  _covarience(0,1) = x.getErr()*y.getErr()*correlation;
  _covarience(1,0) = x.getErr()*y.getErr()*correlation;

  _invcovarience = _covarience;
  _invcovarience.Invert();  
   
}




PoloConstraint* PoloConDMixing::clone(){

  return new PoloConDMixing(*this);

}

PoloConDMixing::~PoloConDMixing(){



}



