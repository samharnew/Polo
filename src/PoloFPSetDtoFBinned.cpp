  #include "PoloFPSetDtoFBinned.h"


PoloFPSetDtoFBinned::PoloFPSetDtoFBinned(TString finalStateName, int nBins, bool selfconj, MINT::MinuitParameterSet* parSet, int paramType ){


  if (nBins == 0){
    _DtoFAmpFitParams.push_back( PoloFPSetDtoF(finalStateName, 0, parSet, paramType) );
    if (selfconj) {
      _DtoFAmpFitParams.back().setKbarToK();
      _DtoFAmpFitParams.back().sets(0.0);
      _DtoFAmpFitParams.back().fixs();
    }
  }

  for (int i = 0; i < nBins; i++){
    _DtoFAmpFitParams.push_back( PoloFPSetDtoF(finalStateName, i+1, parSet, paramType) );
    if (selfconj) _DtoFAmpFitParams.push_back( _DtoFAmpFitParams.back().getSelfConjCPConjFPSet() );
  }

}

PoloFPSetDtoFBinned::PoloFPSetDtoFBinned( std::vector<PoloFPSetDtoF> fpSetDtoF ) :
  _DtoFAmpFitParams( fpSetDtoF )
{


}



PoloFPSetDtoF& PoloFPSetDtoFBinned::getFPSetFromBinNum(int binNum){

  for (int i = 0; i < size(); i++){
    if (_DtoFAmpFitParams.at(i).binNum() == binNum) return _DtoFAmpFitParams.at(i);
  }
  
  std::cout << "ERROR: Could not find a DToFDecayFitParams with the bin number " << binNum << std::endl;
  return _DtoFAmpFitParams.at(0);
}

PoloFPSetDtoF& PoloFPSetDtoFBinned::getFPSet(int i){
  return _DtoFAmpFitParams.at(i);
}

PoloFPSetDtoFBinned PoloFPSetDtoFBinned::getCCFinalState(TString finalStateName){

  std::vector<PoloFPSetDtoF> dToFbarDecayFitParams;

  for (int i = 0; i < size(); i++){
    dToFbarDecayFitParams.push_back( _DtoFAmpFitParams.at(i).getCPConjFPSet(finalStateName) );
  }

  return PoloFPSetDtoFBinned(dToFbarDecayFitParams);

}

void PoloFPSetDtoFBinned::cpPlusES(){

  if (size() != 1){
    std::cout << "ERROR!! You cannot make a binned final state a CP eigenstate - must only have a single bin" << std::endl;
    return;
  }

  PoloFPSetDtoF& fps = getFPSet(0);

  if (fps.binNum() != 0){
    std::cout << "ERROR!! I expect a CP eigenstate to have bin number 0 " << std::endl;
  }

  fps.sets(0.0);
  fps.fixs();
  fps.setc(1.0);
  fps.fixc();
  fps.setKbarToK();

}

void PoloFPSetDtoFBinned::cpMinusES(){
  
  if (size() != 1){
    std::cout << "ERROR!! You cannot make a binned final state a CP eigenstate - must only have a single bin" << std::endl;
    return;
  }

  PoloFPSetDtoF& fps = getFPSet(0);

  if (fps.binNum() != 0){
    std::cout << "ERROR!! I expect a CP eigenstate to have bin number 0 " << std::endl;
  }

  fps.sets(0.0);
  fps.fixs();
  fps.setc(-1.0);
  fps.fixc();
  fps.setKbarToK();

}

void PoloFPSetDtoFBinned::dzES(){

   
  if (size() != 1){
    std::cout << "ERROR!! You cannot make a binned final state a flavour eigenstate - must only have a single bin" << std::endl;
    return;
  }

  PoloFPSetDtoF& fps = getFPSet(0);

  if (fps.binNum() != 0){
    std::cout << "ERROR!! I expect a CP eigenstate to have bin number 0 " << std::endl;
  }

  fps.sets(0.0);
  fps.fixs();
  fps.setc(0.0);
  fps.fixc();
  fps.setKbar(0.0);
  fps.fixKbar();


}

void PoloFPSetDtoFBinned::dzbES(){

   
  if (size() != 1){
    std::cout << "ERROR!! You cannot make a binned final state a flavour eigenstate - must only have a single bin" << std::endl;
    return;
  }

  PoloFPSetDtoF& fps = getFPSet(0);

  if (fps.binNum() != 0){
    std::cout << "ERROR!! I expect a CP eigenstate to have bin number 0 " << std::endl;
  }

  fps.sets(0.0);
  fps.fixs();
  fps.setc(0.0);
  fps.fixc();
  fps.setK(0.0);
  fps.fixK();


}

void PoloFPSetDtoFBinned::makeKKbarPositive(){

  for (int i = 0; i < size(); i++){
    getFPSet(i).makeKandKbarPositive();
  }

}


double PoloFPSetDtoFBinned::calTotK(){
  double sum = 0.0;
  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF& params = getFPSet(i);
    sum += params.getK();
  }
  return sum;
}


double PoloFPSetDtoFBinned::calTotKbar(){
  double sum = 0.0;
  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF& params = getFPSet(i);
    sum += params.getKbar();
  }
  return sum;
}

double PoloFPSetDtoFBinned::calTotC(){

  double sum = 0.0;
  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF& params = getFPSet(i);
    double kb = params.getKbar();
    double k  = params.getK();
    double c  = params.getc();
    sum += c*sqrt(kb*k);
  }

  double totK  = calTotK   ();
  double totKb = calTotKbar();

  return sum/sqrt(totK*totKb);

}

double PoloFPSetDtoFBinned::calTotS(){

  double sum = 0.0;
  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF& params = getFPSet(i);
    double kb = params.getKbar();
    double k  = params.getK();
    double s  = params.gets();
    sum += s*sqrt(kb*k);
  }

  double totK  = calTotK   ();
  double totKb = calTotKbar();

  return sum/sqrt(totK*totKb);
}


void PoloFPSetDtoFBinned::print(std::ostream& os){
  for (int i = 0; i < size(); i++){
    _DtoFAmpFitParams.at( i ).print(os);
  }
}

void PoloFPSetDtoFBinned::printSimple(std::ostream& os){

  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF pars = _DtoFAmpFitParams.at(i);
    os << pars.binNum() << ": " 
       << "  K  = " << pars.getK()
       << "  Kb = " << pars.getKbar()
       << "  c  = " << pars.getc()
       << "  s  = " << pars.gets()
       << std::endl;
  }

}


void PoloFPSetDtoFBinned::fixAllC(double val){
  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF& params = getFPSet(i);
    if (val != -99.9) params.setc(val);
    params.fixc();
  }
}

void PoloFPSetDtoFBinned::fixAllS(double val){
  for (int i = 0; i < size(); i++){
    PoloFPSetDtoF& params = getFPSet(i);
    if (val != -99.9) params.sets(val);
    params.fixs();
  }
}

int PoloFPSetDtoFBinned::size(){

  return _DtoFAmpFitParams.size();

}
 

PoloFPSetDtoFBinned::~PoloFPSetDtoFBinned(){



}



