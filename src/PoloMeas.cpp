#include "PoloMeas.h"

PoloMeas::PoloMeas() :
  _val( 0.0),
  _err(-1.0)
{

}

PoloMeas::PoloMeas(double val) :
  _val( val),
  _err(-1.0)  
{

}

PoloMeas::PoloMeas(double val, double err) :
  _val( val),
  _err( err)
{

}

bool PoloMeas::hasErr(){
  return _err != -1;
}

double PoloMeas::getVal(){
  return _val;
}

double PoloMeas::getErr(){
  return _err;
}

void PoloMeas::setVal(double val){
  _val = val;
}

void PoloMeas::setErr(double err){
  _err = err;
}

PoloMeas::~PoloMeas(){

}