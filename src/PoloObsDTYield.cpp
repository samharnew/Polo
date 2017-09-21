#include "PoloObsDTYield.h"


PoloObsDTYield::PoloObsDTYield(PoloFPSetDtoF& dToF, PoloFPSetDtoF& dToG, PoloFPSetDMixing& dMix, PoloFPSetNorm& nDDb) :
  _dToF(dToF),
  _dToG(dToG),
  _dMix(dMix),
  _nDDb(nDDb)
{

  TString name = "doubleTag___";
  name += _dToF.getName();
  name += "___";
  name += _dToG.getName();
  setName(name);
  
  if (_dToF.binNum() == 0){
    setObsID( _dToG.binNum(), 0 );
  }
  else if (_dToG.binNum() == 0){
    setObsID( _dToF.binNum(), 0 );
  }
  else{
    setObsID( _dToF.binNum(), 0 );
    setObsID( _dToG.binNum(), 1 );
  }
   
}  
  
double PoloObsDTYield::getBF(){
  
  double Kf  = _dToF.getK()   ; 
  double Kfb = _dToF.getKbar();
  double Kg  = _dToG.getK()   ;
  double Kgb = _dToG.getKbar();
  double cf  = _dToF.getc();
  double sf  = _dToF.gets();
  double cg  = _dToG.getc();
  double sg  = _dToG.gets();
  double x   = _dMix.getX();
  double y   = _dMix.getY();

  double TwoAplus  = (Kf*Kgb) + (Kfb*Kg ) - 2.0*sqrt(Kf*Kgb*Kfb*Kg)*( (cf*cg) + (sf*sg) );
  double TwoAminus = (Kf*Kg ) + (Kfb*Kgb) - 2.0*sqrt(Kf*Kgb*Kfb*Kg)*( (cf*cg) - (sf*sg) );

  double val = TwoAplus*(1.0 + ((y*y - x*x)/2.0) ) + TwoAminus*((y*y + x*x)/2.0);
  
  if (val != val){
    std::cout << "DoubleTaggedDecayYield is returning NaN, how?" << std::endl;
    std::cout << "Kf    = " <<  Kf   << std::endl;
    std::cout << "Kfb   = " <<  Kfb  << std::endl;
    std::cout << "Kg    = " <<  Kg   << std::endl;
    std::cout << "Kgb   = " <<  Kgb  << std::endl;
    std::cout << "cf    = " <<  cf   << std::endl;
    std::cout << "sf    = " <<  sf   << std::endl;
    std::cout << "cg    = " <<  cg   << std::endl;
    std::cout << "sg    = " <<  sg   << std::endl;
    std::cout << "x     = " <<  x    << std::endl;
    std::cout << "y     = " <<  y    << std::endl;
  }

  if (val < 0.0) {
    //std::cout << "negative BF" << std::endl;
  }
  return val;

}

double PoloObsDTYield::getVal(){
  
  return getBF()*_nDDb.getVal();

}
 
std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsDTYield::getDependencies(){

  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;
  dependencies.push_back( _dToF.getFitParameterK       () );
  dependencies.push_back( _dToF.getFitParameterKbar    () );
  dependencies.push_back( _dToF.getFitParameterc       () );
  dependencies.push_back( _dToF.getFitParameters       () );  
  dependencies.push_back( _dToF.getFitParameterr       () );
  dependencies.push_back( _dToF.getFitParameterR       () );  
  dependencies.push_back( _dToF.getFitParameterdelta   () );     
  dependencies.push_back( _dToG.getFitParameterK       () );
  dependencies.push_back( _dToG.getFitParameterKbar    () );
  dependencies.push_back( _dToG.getFitParameterc       () );
  dependencies.push_back( _dToG.getFitParameters       () );  
  dependencies.push_back( _dToG.getFitParameterr       () );
  dependencies.push_back( _dToG.getFitParameterR       () );  
  dependencies.push_back( _dToG.getFitParameterdelta   () );     
  dependencies.push_back( _dMix.getFitParameterX       () );
  dependencies.push_back( _dMix.getFitParameterY       () );
  dependencies.push_back( _nDDb.getFitParameter        () );  
  return     dependencies; 

}


PoloObsAbs* PoloObsDTYield::clone(){

  return new PoloObsDTYield(*this);

}


PoloObsDTYield::~PoloObsDTYield(){



}




