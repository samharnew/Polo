#include "PoloObsAbs.h"

#define NOT_STORED_VAL -999999.9

PoloObsAbs::PoloObsAbs() :
  _safeThreshold(0.05)
{

}


int PoloObsAbs::genPoisson(TRandom* random){
  
  return random->Poisson( getVal() );  

}


double PoloObsAbs::genPoissonD(TRandom* random){

  return random->PoissonD( getVal() );

}

double PoloObsAbs::genGaus (double err, TRandom* random){
  return random->Gaus( getVal(), err );
}


double PoloObsAbs::getPoissonProb       (double nObs){
  return exp( -0.5*getNeg2LogPoissonProb(nObs));
}

double PoloObsAbs::getGausProb       (double nObs, double err){
  return exp( -0.5*getNeg2LogGausProb(nObs, err));
}

double PoloObsAbs::getNeg2LogPoissonProb       (double nObs){

  double expectedVal    = getValSafe   ();
  double logExpectedVal = getLogValSafe();
  
  double val = 2.0*(expectedVal - nObs*logExpectedVal);
  
  return val;
}

double PoloObsAbs::getNeg2LogGausProb       (double nObs, double err){

  double expectedValNotSafe = getVal();
  double pull = (expectedValNotSafe - nObs)/err;  
  return pull*pull;

}



double PoloObsAbs::getValSafe(){
  
  double val = getVal();
  if (val < _safeThreshold){
    return _safeThreshold*exp( (val - _safeThreshold) / _safeThreshold );
  }
  return val;

}

void PoloObsAbs::print(TString prefix){

  std::cout << prefix << _name << "   expected yield = " << getVal() << std::endl;

}

double PoloObsAbs::getLogValSafe(){
  
  double val = getVal();
  double logval = 0.0;
  if (val < _safeThreshold){
    logval = log(_safeThreshold) + ((val - _safeThreshold) / _safeThreshold );
  }
  else{
    logval = log(val);
  }

  if (logval != logval){
    std::cout << "logval is NaN. How?" << std::endl;
    std::cout << "log(_safeThreshold)" << log(_safeThreshold) << std::endl;
    std::cout << "val" << val << std::endl;
    std::cout << "_safeThreshold" << _safeThreshold << std::endl;
  }

  return logval;
}



void PoloObsAbs::setName(TString val){
  
  _name = val;

}





TString PoloObsAbs::getName(){

  return _name;

}

 
PoloObsAbs::~PoloObsAbs(){
  
}


#undef NOT_STORED_VAL 








