#include "PoloObsSTYield.h"


PoloObsSTYield::PoloObsSTYield(PoloFPSetDtoF& dToF, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDDb) :
  _dToF(dToF),
  _dMix(dMix),
  _nDDb(nDDb)
{

  TString name = "singleTag___";
  name += _dToF.getName();
  setName(name);
  setObsID( _dToF.binNum(), 0 );

}  
  
double PoloObsSTYield::getBF(){
  
  double K  = _dToF.getK()   ; 
  double Kb = _dToF.getKbar();
  double c  = _dToF.getc();
  double y  = _dMix.getY();
  double val = ( K + Kb - 2.0*c*y*sqrt(K*Kb) )*(1.0 + y*y);

  return val; 

}

double PoloObsSTYield::getVal(){
  
  return getBF()*_nDDb.getVal();

}
 
std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsSTYield::getDependencies(){

  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;
  dependencies.push_back( _dToF.getFitParameterK    () );
  dependencies.push_back( _dToF.getFitParameterKbar () );
  dependencies.push_back( _dToF.getFitParameterc    () );
  dependencies.push_back( _dToF.getFitParameterr    () );
  dependencies.push_back( _dToF.getFitParameterR    () );  
  dependencies.push_back( _dToF.getFitParameterdelta() );    
  dependencies.push_back( _dMix.getFitParameterY    () );
  dependencies.push_back( _nDDb.getFitParameter     () );  
  return     dependencies; 

}


PoloObsAbs* PoloObsSTYield::clone(){

  return new PoloObsSTYield(*this);

}


PoloObsSTYield::~PoloObsSTYield(){



}




