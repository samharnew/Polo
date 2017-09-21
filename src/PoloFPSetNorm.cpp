#include "PoloFPSetNorm.h"



PoloFPSetNorm::PoloFPSetNorm(MINT::MinuitParameterSet* parSet, TString name) :
  _norm(0)
{
  _norm    = new MINT::FitParameter( ("norm_" + name).Data() , 0, 10000.0 , 1000.0  , 0.0 , 0.0, parSet);
}


  
double PoloFPSetNorm::getVal() const{
  return fabs((double)*_norm);
}
 


void PoloFPSetNorm::setVal(double val){
  *_norm = val;
  _norm->setCurrentFitVal(val);

}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetNorm::getFitParameter(){

  return _norm;

}


void PoloFPSetNorm::fix  (){
  _norm->fix();
}

void PoloFPSetNorm::unfix  (){
  _norm->unFix();
}



