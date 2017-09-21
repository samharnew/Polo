#include "PoloFPSetDtoF.h"

#define FABS(a) fabs(a)
//#define FABS(a) a

PoloFPSetDtoF::PoloFPSetDtoF(TString finalStateName, int binNumber, MINT::MinuitParameterSet* parSet, int paramType) :
  _finalStateName       (finalStateName),
  _binNumber            (binNumber     ),
  _hasCPConjFitPars          (false         ),
  _K                    (0             ),
  _Kbar                 (0             ),
  _c                    (0             ),
  _s                    (0             ),
  _r                    (0             ),
  _R                    (0             ),
  _delta                (0             )  
{
  
  if (paramType == 0){ 
    _K    = new MINT::FitParameter( (getName() + "_K"   ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _Kbar = new MINT::FitParameter( (getName() + "_Kbar").Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _c    = new MINT::FitParameter( (getName() + "_C"   ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _s    = new MINT::FitParameter( (getName() + "_S"   ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
  }
  if (paramType == 1){ 
    _K     = new MINT::FitParameter( (getName() + "_K"    ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _r     = new MINT::FitParameter( (getName() + "_r"    ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _R     = new MINT::FitParameter( (getName() + "_R"    ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _delta = new MINT::FitParameter( (getName() + "_delta").Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
  }

} 

PoloFPSetDtoF::PoloFPSetDtoF() :
  _finalStateName       ( ""       ),
  _binNumber            (-9999     ),
  _hasCPConjFitPars          (false     ),
  _K                    (0         ),
  _Kbar                 (0         ),
  _c                    (0         ),
  _s                    (0         ),
  _r                    (0         ),
  _R                    (0         ),
  _delta                (0         )    
{
  


}


bool PoloFPSetDtoF::isAltParam() const{
  if (_r == 0) return 0;
  return 1;
}

bool PoloFPSetDtoF::hasCPConjFPs() const{
  return _hasCPConjFitPars;
}

bool PoloFPSetDtoF::warningForNoFPs() const{

  if (_K == 0){
    std::cout << "ERROR!! No fit paramaters have been created for " << getName() << std::endl;
    return 0;
  }
  return 1;

}


void PoloFPSetDtoF::makeKandKbarPositive(){
  if (_K != 0) {
    double val = *_K;
    if (val < 0.0){
      *_K = -val;
      _K->setCurrentFitVal(-val);
    }
  }

  if (_Kbar != 0) {
    double val = *_Kbar;
    if (val < 0.0){
      *_Kbar = -val;
      _Kbar->setCurrentFitVal(-val);
    }
  }

  if (_r != 0) {
    double val = *_r;
    if (val < 0.0){
      *_r = -val;
      _r->setCurrentFitVal(-val);
    }
  }

}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameterK   (){
  return _K;
} 
MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameterKbar(){
  return _Kbar;
}
MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameterc   (){
  return _c;
}
MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameters   (){
  return _s;
}
MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameterR   (){
  return _R;
}
MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameterr   (){
  return _r;
}
MINT::counted_ptr<MINT::FitParameter> PoloFPSetDtoF::getFitParameterdelta(){
  return _delta;
}




void PoloFPSetDtoF::setKbarToK(){
  _Kbar = _K;
}



TString PoloFPSetDtoF::getFinalStateName() const{
  
  return _finalStateName;

}


TString PoloFPSetDtoF::getName() const{
  
  TString name = getFinalStateName();
   
  name += "_"; 
  if (_binNumber < 0.0) {
    name += _binNumber;
  }
  else{
    name += "+"; 
    name += _binNumber; 
  }
  return name;

}

  
PoloFPSetDtoF PoloFPSetDtoF::getCPConjFPSet(TString finalStateName){
  
  //If no final state name is provided, then just use the 
  //old one with CC (charge conjugate) after.

  if (finalStateName == ""){
    finalStateName = _finalStateName + "CC";
    finalStateName.ReplaceAll("CCCC", ""); 
  }

  PoloFPSetDtoF fBarParams;
   
  //Flip _K<->_Kbar and flip the sign of _s

  fBarParams._finalStateName   = finalStateName;
  fBarParams._binNumber        = _binNumber;
  fBarParams._K                = _K   ;
  fBarParams._Kbar             = _Kbar;
  fBarParams._c                = _c   ;
  fBarParams._s                = _s   ; 
  fBarParams._r                = _r   ;
  fBarParams._R                = _R   ;
  fBarParams._delta            = _delta; 
  fBarParams._hasCPConjFitPars = !_hasCPConjFitPars;
  
  return fBarParams;

}
  

PoloFPSetDtoF PoloFPSetDtoF::getSelfConjCPConjFPSet(){

  PoloFPSetDtoF fBarParams;
   
  //Flip _K<->_Kbar and flip the sign of _s
  
  fBarParams._finalStateName   = _finalStateName;
  fBarParams._binNumber        = -_binNumber;
  fBarParams._K                = _K   ;
  fBarParams._Kbar             = _Kbar;
  fBarParams._c                = _c   ;
  fBarParams._s                = _s   ;
  fBarParams._r                = _r   ;
  fBarParams._R                = _R   ;
  fBarParams._delta            = _delta;   
  fBarParams._hasCPConjFitPars = !_hasCPConjFitPars;
  
  return fBarParams;


}



double PoloFPSetDtoF::getK   () const{
  
  warningForNoFPs();

  if ( !isAltParam() && !hasCPConjFPs() ){
    return FABS((double)*_K);
  }
  else if ( !isAltParam() &&  hasCPConjFPs() ){
    return FABS((double)*_Kbar);
  }
  else if ( isAltParam() && !hasCPConjFPs() ){
    return FABS((double)*_K);
  }
  else if ( isAltParam() &&  hasCPConjFPs() ){
    return FABS(((double)*_K)*((double)*_r)*((double)*_r));
  }

  return 0.0; //this should never happen

}

double PoloFPSetDtoF::getKbar   () const{
  
  warningForNoFPs();

  if ( !isAltParam() && !hasCPConjFPs() ){
    return FABS((double)*_Kbar);
  }
  else if ( !isAltParam() &&  hasCPConjFPs() ){
    return FABS((double)*_K);
  }
  else if ( isAltParam() && !hasCPConjFPs() ){
    return FABS(((double)*_K)*((double)*_r)*((double)*_r));
  }
  else if ( isAltParam() &&  hasCPConjFPs() ){
    return FABS((double)*_K);
  }

  return 0.0; //this should never happen

}

double PoloFPSetDtoF::getc   () const{

  warningForNoFPs();

  if ( !isAltParam() ){
    return (double)*_c;
  }
  else if ( isAltParam() ){
    return ((double)*_R)*cos((double)*_delta);
  }

  return 0.0; //this should never happen

}

double PoloFPSetDtoF::gets   () const{

  warningForNoFPs();

  if ( !isAltParam() && !hasCPConjFPs() ){
    return (double)*_s;
  }
  if ( !isAltParam() &&  hasCPConjFPs() ){
    return -1.0*((double)*_s);
  }
  if ( isAltParam() && !hasCPConjFPs() ){
    return ((double)*_R)*sin((double)*_delta);
  }
  if ( isAltParam() &&  hasCPConjFPs() ){
    return -((double)*_R)*sin((double)*_delta);
  }

  return 0.0; //this should never happen

}


void PoloFPSetDtoF::setK   (double val){

  warningForNoFPs();
  
  if      ( !isAltParam() && !hasCPConjFPs() ){
    *_K = val;  
    _K->setCurrentFitVal(val);    
  }
  else if ( !isAltParam() &&  hasCPConjFPs() ){
    *_Kbar = val;  
    _Kbar->setCurrentFitVal(val);    
  }
  else if (  isAltParam() && !hasCPConjFPs() ){
    *_K = val;  
    _K->setCurrentFitVal(val);
  }
  else if (  isAltParam() &&  hasCPConjFPs() ){
    std::cout << "Error!! Since I'm using the CP conjugate fit parameters to describe this";
    std::cout << "final state, a fit parameter for K does not exist. It is calculated using";
    std::cout << " K = Kbar*r_D^2 when needed" << std::endl;
  }

}

void PoloFPSetDtoF::setKbar(double val){

  warningForNoFPs();
  
  if      ( !isAltParam() && !hasCPConjFPs() ){
    *_Kbar = val;  
    _Kbar->setCurrentFitVal(val);    
  }
  else if ( !isAltParam() &&  hasCPConjFPs() ){
    *_K = val;  
    _K->setCurrentFitVal(val);    
  }
  else if (  isAltParam() && !hasCPConjFPs() ){
    std::cout << "Error!! In this parameterisation, a Kbar fit parameter does not exist" << std::endl;
  }
  else if (  isAltParam() &&  hasCPConjFPs() ){
    *_Kbar = val;  
    _Kbar->setCurrentFitVal(val);  
  }

}

void PoloFPSetDtoF::setc   (double val){

  if      ( !isAltParam() && !hasCPConjFPs() ){
    *_c = val;  
    _c->setCurrentFitVal(val);    
  }
  else if ( !isAltParam() &&  hasCPConjFPs() ){
    *_c = val;  
    _c->setCurrentFitVal(val);    
  }
  else if (  isAltParam()  ){
    std::cout << "Error!! In this parameterisation, a c fit parameter does not exist" << std::endl;
  }

}

void PoloFPSetDtoF::sets   (double val){

  if      ( !isAltParam() && !hasCPConjFPs() ){
    *_s = val;  
    _s->setCurrentFitVal(val);    
  }
  else if ( !isAltParam() &&  hasCPConjFPs() ){
    *_s = -val;  
    _s->setCurrentFitVal(-val);    
  }
  else if (  isAltParam()  ){
    std::cout << "Error!! In this parameterisation, a s fit parameter does not exist" << std::endl;
  }


}


void PoloFPSetDtoF::fixK   (){
  _K->fix();
}

void PoloFPSetDtoF::fixKbar(){
  _Kbar->fix();
}

void PoloFPSetDtoF::fixc   (){
  _c->fix();
}

void PoloFPSetDtoF::fixs   (){
  _s->fix();
}

void PoloFPSetDtoF::unfixK   (){
  _K->unFix();
}

void PoloFPSetDtoF::unfixKbar(){
  _Kbar->unFix();
}

void PoloFPSetDtoF::unfixc   (){
  _c->unFix();
}

void PoloFPSetDtoF::unfixs   (){
  _s->unFix();
}


void PoloFPSetDtoF::print(std::ostream& os){
  
  TString finalStateName = getName();
  os << finalStateName; 
  os << std::endl;

}



PoloFPSetDtoF::~PoloFPSetDtoF(){

}


















