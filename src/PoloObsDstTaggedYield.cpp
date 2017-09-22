#include "PoloObsDstTaggedYield.h"


PoloObsDstTaggedYield::PoloObsDstTaggedYield(PoloFPSetDtoF& dToF, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDst, int dstQ, double mint, double maxt, int decTimeBin) :
  _dToF      (dToF),
  _dMix      (dMix),
  _nDst      (nDst),
  _dstQ      (dstQ),
  _minDecTime(mint),
  _maxDecTime(maxt)
{

  TString name = "DstTag___";

  
  setObsID( _dToF.binNum(), 0 );
  if (decTimeBin != -1){
    setObsID( decTimeBin, 1 );
    name += "DTBin";
    name += decTimeBin;
    name += "___";
  }

  name += _dToF.getName();
  setName(name);

}  
  
double PoloObsDstTaggedYield::getDecayTimeIntVal(){
  
  double K  = _dToF.getK()   ; 
  double Kb = _dToF.getKbar();
  double c  = _dToF.getc();
  double s  = _dToF.gets();
  double x  = _dMix.getX();
  double y  = _dMix.getY();
  
  double norm  = _nDst.getVal();


  double val = 0.0;
  if (_dstQ == +1){
    val = K - sqrt( Kb*K )*( y*c + x*s ) + Kb*(x*x + y*y)*0.5;
  }
  else{
    val = Kb - sqrt( Kb*K )*( y*c - x*s ) + K*(x*x + y*y)*0.5;
  }
  return val*norm; 

}

double PoloObsDstTaggedYield::integrand(double t){

  double K  = _dToF.getK()   ; 
  double Kb = _dToF.getKbar();
  double c  = _dToF.getc();
  double s  = _dToF.gets();
  double x  = _dMix.getX();
  double y  = _dMix.getY();
  
  double norm  = _nDst.getVal();


  double val = 0.0;
  if (_dstQ == +1){
    val = K*exp(-t) 
        - sqrt( Kb*K )*( y*c + x*s )*exp(-t)*(1.0+t) 
        + Kb*(x*x + y*y)*0.25*exp(-t)*(2.0 + 2.0*t + t*t);
  }
  else{
    val = Kb*exp(-t) 
        - sqrt( Kb*K )*( y*c - x*s )*exp(-t)*(1.0+t) 
        + K*(x*x + y*y)*0.25*exp(-t)*(2.0 + 2.0*t + t*t);
  }
  return -val*norm;   

}

double PoloObsDstTaggedYield::getVal(){
  
  //I confirmed that the two methods give indentical results for t=[0,50]
  if (_maxDecTime >= 50.0 && _minDecTime == 0.0){
    return getDecayTimeIntVal();
  }

  return integrand(_maxDecTime) - integrand(_minDecTime);

}
 
std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsDstTaggedYield::getDependencies(){

  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;
  dependencies.push_back( _dToF.getFitParameterK    () );
  dependencies.push_back( _dToF.getFitParameterKbar () );
  dependencies.push_back( _dToF.getFitParameterc    () );
  dependencies.push_back( _dToF.getFitParameters    () );
  dependencies.push_back( _dToF.getFitParameterr    () );
  dependencies.push_back( _dToF.getFitParameterR    () );  
  dependencies.push_back( _dToF.getFitParameterdelta() );    
  dependencies.push_back( _dMix.getFitParameterX    () );
  dependencies.push_back( _dMix.getFitParameterY    () );
  dependencies.push_back( _nDst.getFitParameter     () );  
  return     dependencies; 

}


PoloObsAbs* PoloObsDstTaggedYield::clone(){

  return new PoloObsDstTaggedYield(*this);

}


PoloObsDstTaggedYield::~PoloObsDstTaggedYield(){



}




