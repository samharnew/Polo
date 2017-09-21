#include "PoloFPSetDMixing.h"


PoloFPSetDMixing::PoloFPSetDMixing( MINT::MinuitParameterSet* parSet, TString suffix ) :
  _x(0),
  _y(0)
{
  _x = new MINT::FitParameter( ("xD"+suffix).Data() , 0, 0.01 , 0.01  , 0.0 , 0.0, parSet);
  _y = new MINT::FitParameter( ("yD"+suffix).Data() , 0, 0.01 , 0.01  , 0.0 , 0.0, parSet);
}
  
  
double PoloFPSetDMixing::getX() const{
  return (double)*_x;
}

double PoloFPSetDMixing::getY() const{
  return (double)*_y;
}

void PoloFPSetDMixing::setX(double val){
  *_x = val;
  _x->setCurrentFitVal(val);
}

void PoloFPSetDMixing::setY(double val){
  *_y = val;
  _y->setCurrentFitVal(val);
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetDMixing::getFitParameterX(){
  return _x;
}


MINT::counted_ptr<MINT::FitParameter> PoloFPSetDMixing::getFitParameterY(){
  return _y;
}

void PoloFPSetDMixing::fixX   (){
  _x->fix();
}

void PoloFPSetDMixing::fixY   (){
  _y->fix();
}

void PoloFPSetDMixing::unfixX   (){
  _x->unFix();
}

void PoloFPSetDMixing::unfixY(){
  _y->unFix();
}


void PoloFPSetDMixing::noMixing(){
  setX(0.0);
  setY(0.0);
  fixX();
  fixY();  
}

PoloFPSetDMixing::~PoloFPSetDMixing(){

}








