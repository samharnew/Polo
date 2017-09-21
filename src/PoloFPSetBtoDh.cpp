#include "PoloFPSetBtoDh.h"


PoloFPSetBtoDh::PoloFPSetBtoDh(TString finalStateName, MINT::MinuitParameterSet* parSet, int paramType) :
  _finalStateName       (finalStateName),
  _xp                   (0         ),
  _xm                   (0         ),
  _yp                   (0         ),
  _ym                   (0         ),
  _rB                   (0         ),
  _deltaB               (0         ),
  _gamma                (0         ),
  _paramType            (paramType )  
{
  if (_paramType == 0){ 
    _xp  = new MINT::FitParameter( (getFinalStateName() + "_xp" ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _xm  = new MINT::FitParameter( (getFinalStateName() + "_xm" ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _yp  = new MINT::FitParameter( (getFinalStateName() + "_yp" ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _ym  = new MINT::FitParameter( (getFinalStateName() + "_ym" ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
  }
  if (_paramType == 1){ 
    _rB     = new MINT::FitParameter( (getFinalStateName() + "_rB"    ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _deltaB = new MINT::FitParameter( (getFinalStateName() + "_deltaB").Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
    _gamma  = new MINT::FitParameter( (getFinalStateName() + "_gamma" ).Data() , 0, 0.1 , 0.01  ,  0.0 , 0.0, parSet);
  }

}

TString PoloFPSetBtoDh::getFinalStateName() const{
  return _finalStateName;
}


void PoloFPSetBtoDh::removeCPV(){
  if (_paramType == 0){
    _xm = _xp;
    _ym = _yp;
  }
  if (_paramType == 1){
    setgamma(0.0);
    fixgamma();    
  }
}


void PoloFPSetBtoDh::copyGammaFitPatameter(PoloFPSetBtoDh& other){
  _gamma = other._gamma;
}


void PoloFPSetBtoDh::randomise( TRandom* random ){
  if (_paramType == 0){
    if ( getFitParameterxp()->iFixInit() == 0 ) setxp( random->Uniform(-0.3, 0.3) );
    if ( getFitParameterxm()->iFixInit() == 0 ) setxm( random->Uniform(-0.3, 0.3) );
    if ( getFitParameteryp()->iFixInit() == 0 ) setyp( random->Uniform(-0.3, 0.3) );
    if ( getFitParameterym()->iFixInit() == 0 ) setym( random->Uniform(-0.3, 0.3) );
  }
  if (_paramType == 1){
    if ( getFitParametergamma ()->iFixInit() == 0 ) setgamma ( random->Uniform(-TMath::Pi(), TMath::Pi())  );
    if ( getFitParameterrB    ()->iFixInit() == 0 ) setrB    ( random->Uniform(0.0, 0.3)   );
    if ( getFitParameterdeltaB()->iFixInit() == 0 ) setdeltaB( random->Uniform(-TMath::Pi(), TMath::Pi())  );
  }
}


double PoloFPSetBtoDh::getxp  () const{
  if (_paramType == 0){
    return *_xp;
  }
  if (_paramType == 1){
    return (*_rB)*cos( (*_deltaB) + (*_gamma) );   
  }
  std::cout <<"Error: this parameterisation doesn't exisit. Must use 0 or 1" << std::endl;
  return 0;
}

double PoloFPSetBtoDh::getxm  () const{
  if (_paramType == 0){
    return *_xm;
  }
  if (_paramType == 1){
    return (*_rB)*cos( (*_deltaB) - (*_gamma) );   
  }
  std::cout <<"Error: this parameterisation doesn't exisit. Must use 0 or 1" << std::endl;
  return 0;
}

double PoloFPSetBtoDh::getyp  () const{
  if (_paramType == 0){
    return *_yp;
  }
  if (_paramType == 1){
    return (*_rB)*sin( (*_deltaB) + (*_gamma) );   
  }
  std::cout <<"Error: this parameterisation doesn't exisit. Must use 0 or 1" << std::endl;
  return 0;
}

double PoloFPSetBtoDh::getym  () const{
  if (_paramType == 0){
    return *_ym;
  }
  if (_paramType == 1){
    return (*_rB)*sin( (*_deltaB) - (*_gamma) );   
  }
  std::cout <<"Error: this parameterisation doesn't exisit. Must use 0 or 1" << std::endl;
  return 0;
}



MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParameterxp    (){
  return _xp;
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParameterxm    (){
  return _xm;
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParameteryp    (){
  return _yp;
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParameterym    (){
  return _ym;
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParameterrB    (){
  return _rB;
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParameterdeltaB(){
  return _deltaB;
}

MINT::counted_ptr<MINT::FitParameter> PoloFPSetBtoDh::getFitParametergamma (){
  return _gamma;
}


void PoloFPSetBtoDh::setxp  (double val){
  if (_xp == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " xp " << std::endl;
    return;
  }
  *_xp = val; 
  _xp->setCurrentFitVal(val);
}

void PoloFPSetBtoDh::setxm  (double val){
  if (_xm == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " xm " << std::endl;
    return;
  }
  *_xm = val; 
  _xm->setCurrentFitVal(val);
}

void PoloFPSetBtoDh::setyp  (double val){
  if (_yp == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " yp " << std::endl;
    return;
  }
  *_yp = val; 
  _yp->setCurrentFitVal(val);
}

void PoloFPSetBtoDh::setym  (double val){
  if (_ym == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " ym " << std::endl;
    return;
  }
  *_ym = val; 
  _ym->setCurrentFitVal(val);
}


void PoloFPSetBtoDh::setrB      (double val){
  if (_rB == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " rB " << std::endl;
    return;
  }
  *_rB = val; 
  _rB->setCurrentFitVal(val);
}

void PoloFPSetBtoDh::setdeltaB  (double val){
  if (_deltaB == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " deltaB " << std::endl;
    return;
  }
  *_deltaB = val; 
  _deltaB->setCurrentFitVal(val);
}

void PoloFPSetBtoDh::setgamma   (double val){
  if (_gamma == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " gamma " << std::endl;
    return;
  }
  *_gamma = val; 
  _gamma->setCurrentFitVal(val);
}


void PoloFPSetBtoDh::setAll  (double rB, double deltaB, double gamma, bool degrees){
  double multiplier = 1.0; 
  if (degrees) multiplier = TMath::Pi()/180.0;
  deltaB *= multiplier;
  gamma  *= multiplier;


  if (_paramType == 0){
    setxp( rB*cos( deltaB + gamma ) );
    setxm( rB*cos( deltaB - gamma ) );
    setyp( rB*sin( deltaB + gamma ) );
    setym( rB*sin( deltaB - gamma ) );
  }
  if (_paramType == 1){
    setgamma ( gamma  );
    setrB    ( rB     );
    setdeltaB( deltaB );
  }
}


void PoloFPSetBtoDh::mapgammaToWithinPi (double val, bool degrees){
  if (_gamma == 0) return;
 
  if (degrees) val *= (TMath::Pi()/180.0);
  
  double gam = (*_gamma);
  while ( gam - val < -TMath::Pi() ){
    gam += 2.0*TMath::Pi();
  }
  while ( gam - val > TMath::Pi() ){
    gam -= 2.0*TMath::Pi();
  }
  setgamma(gam);
}

void PoloFPSetBtoDh::mapdeltaBToWithinPi(double val, bool degrees){
  if (_deltaB == 0) return;
 
  if (degrees) val *= (TMath::Pi()/180.0);
  
  double delB = (*_deltaB);
  while ( delB - val < -TMath::Pi() ){
    delB += 2.0*TMath::Pi();
  }
  while ( delB - val > TMath::Pi() ){
    delB -= 2.0*TMath::Pi();
  }
  setdeltaB(delB);
}

void PoloFPSetBtoDh::mapGammaAndDelta(double gammaInput, double deltaInput, bool degrees){
  if (degrees) {
    gammaInput *= (TMath::Pi()/180.0);
    deltaInput *= (TMath::Pi()/180.0);
  }

  double gam = (*_gamma );
  double del = (*_deltaB);
  
  bool divBy2Pi = true;

  while ( gam - gammaInput < -TMath::Pi()*0.5 ){
    gam += TMath::Pi();
    divBy2Pi = !divBy2Pi;
  }
  while ( gam - gammaInput > TMath::Pi()*0.5 ){
    gam -= TMath::Pi();
    divBy2Pi = !divBy2Pi;
  }  
  
  if (divBy2Pi == false) del += TMath::Pi();
  
  setgamma (gam);
  setdeltaB(del);

  //mapgammaToWithinPi(gammaInput, false);
  mapdeltaBToWithinPi(deltaInput, false);
}




void PoloFPSetBtoDh::fixxp(){
  if (_xp == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _xp " << std::endl;
    return;
  }
  _xp->fix();
}

void PoloFPSetBtoDh::fixxm(){
  if (_xm == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _xm " << std::endl;
    return;
  }
  _xm->fix();
}

void PoloFPSetBtoDh::fixyp(){
  if (_yp == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _yp " << std::endl;
    return;
  }
  _yp->fix();
}

void PoloFPSetBtoDh::fixym(){
  if (_ym == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _ym " << std::endl;
    return;
  }
  _ym->fix();
}


void PoloFPSetBtoDh::fixrB      (){
  if (_rB == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _rB " << std::endl;
    return;
  }
  _rB->fix();
}

void PoloFPSetBtoDh::fixdeltaB  (){
  if (_deltaB == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _deltaB " << std::endl;
    return;
  }
  _deltaB->fix();
}

void PoloFPSetBtoDh::fixgamma   (){
  if (_gamma == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _gamma " << std::endl;
    return;
  }
  _gamma->fix();
}



void PoloFPSetBtoDh::unfixxp(){
  if (_xp == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _xp " << std::endl;
    return;
  }
  _xp->unFix();
}

void PoloFPSetBtoDh::unfixxm(){
  if (_xm == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _xm " << std::endl;
    return;
  }
  _xm->unFix();
}

void PoloFPSetBtoDh::unfixyp(){
  if (_yp == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _yp " << std::endl;
    return;
  }
  _yp->unFix();
}

void PoloFPSetBtoDh::unfixym(){
  if (_ym == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _ym " << std::endl;
    return;
  }
  _ym->unFix();
}


void PoloFPSetBtoDh::unfixrB      (){
  if (_rB == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _rB " << std::endl;
    return;
  }
  _rB->unFix();
}

void PoloFPSetBtoDh::unfixdeltaB  (){
  if (_deltaB == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _deltaB " << std::endl;
    return;
  }
  _deltaB->unFix();
}

void PoloFPSetBtoDh::unfixgamma   (){
  if (_gamma == 0){
    std::cout << "No fit paramaters have been created for " << _finalStateName << " _gamma " << std::endl;
    return;
  }
  _gamma->unFix();
}



PoloFPSetBtoDh::~PoloFPSetBtoDh(){

}








