#include "PoloObsBtoDhYield.h"

PoloObsBtoDhYield::PoloObsBtoDhYield(PoloFPSetDtoF& dToF, PoloFPSetBtoDh& bToDh, PoloFPSetNorm& norm, bool chargeConj) :
  _dToF (dToF ),
  _bToDh(bToDh),
  _norm (norm ),
  _chargeConj(chargeConj)
{

  TString name = "BToDHTag___";
  name += _bToDh.getFinalStateName();
  if (_chargeConj) name += "CC"; 
  name += "___";
  name += _dToF.getName();

  setName(name); 
  setObsID( _dToF.binNum(), 0 );

}

double PoloObsBtoDhYield::getVal(){
  
  double Kf  = _dToF.getK()   ; 
  double Kfb = _dToF.getKbar();
  double cf  = _dToF.getc();
  double sf  = _dToF.gets();

  double x   = _bToDh.getxp();
  double y   = _bToDh.getyp();
  
  double norm = _norm.getVal();  

  if (_chargeConj){
    x   = _bToDh.getxm();
    y   = _bToDh.getym();
  }
  
  double rBsq = x*x + y*y;

  double val  = 0.0;
  
  if (_chargeConj == false){
    //Bp->DKp, D->f
    val = (Kf*rBsq) + (Kfb) + 2.0*sqrt(Kf*Kfb)*( (cf*x) - (sf*y) );
  }
  else{
    //Bm->DKm, D->f
    val = (Kfb*rBsq) + (Kf) + 2.0*sqrt(Kf*Kfb)*( (cf*x) + (sf*y) );    
  }
  
  val *= norm;

  if (val != val){
    std::cout << "PoloObsBtoDhYield is returning NaN, how?" << std::endl;
    std::cout << "Kf    = " <<  Kf   << std::endl;
    std::cout << "Kfb   = " <<  Kfb  << std::endl;
    std::cout << "cf    = " <<  cf   << std::endl;
    std::cout << "sf    = " <<  sf   << std::endl;
    std::cout << "x     = " <<  x    << std::endl;
    std::cout << "y     = " <<  y    << std::endl;
  }

  return val;

}

PoloObsAbs* PoloObsBtoDhYield::clone(){
  return new PoloObsBtoDhYield(*this);
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloObsBtoDhYield::getDependencies(){

  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;
  dependencies.push_back( _dToF.getFitParameterK       () );
  dependencies.push_back( _dToF.getFitParameterKbar    () );
  dependencies.push_back( _dToF.getFitParameterc       () );
  dependencies.push_back( _dToF.getFitParameters       () );  
  dependencies.push_back( _dToF.getFitParameterr       () );
  dependencies.push_back( _dToF.getFitParameterR       () );  
  dependencies.push_back( _dToF.getFitParameterdelta   () );     
  if (_chargeConj){
    dependencies.push_back( _bToDh.getFitParameterxm   () );     
    dependencies.push_back( _bToDh.getFitParameterym   () );     
  }
  else {
    dependencies.push_back( _bToDh.getFitParameterxp   () );     
    dependencies.push_back( _bToDh.getFitParameteryp   () );     
  }
  dependencies.push_back( _bToDh.getFitParametergamma   () );     
  dependencies.push_back( _bToDh.getFitParameterrB      () );       
  dependencies.push_back( _bToDh.getFitParameterdeltaB  () );      

  dependencies.push_back( _norm.getFitParameter() );  

  return     dependencies; 

} 

void PoloObsBtoDhYield::print(TString prefix){

  std::cout << prefix << getName() << "   expected yield = " << getVal() << std::endl;

}

PoloObsBtoDhYield::~PoloObsBtoDhYield(){

}



