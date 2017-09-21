#include "PoloObsSet.h"

PoloObsSet::PoloObsSet(){

}

void PoloObsSet::addObs ( PoloObsAbs& obs ){
  _obs.push_back( obs.clone() );
}


void PoloObsSet::addBackground  ( PoloMeas bg  ){
  
  std::vector<PoloObsAbs*> _updatedObsList;

  for (unsigned i = 0; i < _obs.size(); i++){
    _updatedObsList.push_back( new PoloObsBGCor( *_obs.at(i), bg ) );
  }

  _obs = _updatedObsList;

}

void PoloObsSet::addEfficiencies( PoloMeas eff ){
  
  std::vector<PoloObsAbs*> _updatedObsList;

  for (unsigned i = 0; i < _obs.size(); i++){
    _updatedObsList.push_back( new PoloObsEffCor( *_obs.at(i), eff ) );
  }

  _obs = _updatedObsList;

}

void PoloObsSet::addBackground  ( PoloObsID id, PoloMeas bg  ){
  int i = getObsNum(id);
  if (i == -1){
    std::cout << "ERROR: Cannot addBackground to this PoloObsID as" << std::endl;
    std::cout << "it does not exist in this PoloObsSet" << std::endl;
    return;
  }
  PoloObsAbs* current = _obs.at(i);
  _obs.at(i) = new PoloObsBGCor( *current, bg );


}

void PoloObsSet::addEfficiencies( PoloObsID id, PoloMeas eff ){
  int i = getObsNum(id);
  if (i == -1){
    std::cout << "ERROR: Cannot addBackground to this PoloObsID as" << std::endl;
    std::cout << "it does not exist in this PoloObsSet" << std::endl;
    return;
  }
  PoloObsAbs* current = _obs.at(i);
  _obs.at(i) = new PoloObsEffCor( *current, eff );

}

void PoloObsSet::addBackground  ( PoloMeasSet& bg  ){
  
  std::vector<PoloObsAbs*> _updatedObsList;

  std::vector<PoloMeas> bglist = bg.getMeasList( getIDList() );
  for (unsigned i = 0; i < _obs.size(); i++){
    _updatedObsList.push_back( new PoloObsBGCor( *_obs.at(i), bglist.at(i) ) );
  }

  _obs = _updatedObsList;

}


void PoloObsSet::addEfficiencies( PoloMeasSet& eff ){

  std::vector<PoloObsAbs*> _updatedObsList;

  std::vector<PoloMeas> efflist = eff.getMeasList( getIDList() );
  for (unsigned i = 0; i < _obs.size(); i++){
    _updatedObsList.push_back( new PoloObsEffCor( *_obs.at(i), efflist.at(i) ) );
  }

  _obs = _updatedObsList;

}

PoloLLHSum PoloObsSet::getLLH( PoloMeasSet& meas ){
  
  bool allErrs = meas.allMeasHaveErrs();
  bool allCor  = meas.allMeasHaveCor ();
  
  bool someErrs = meas.someMeasHaveErrs();
  bool someCor  = meas.someMeasHaveCor ();

  bool poisFit = false;
  bool gausFit = false;
  bool mvgFit  = false;

  if (!allErrs && someErrs){
  	std::cout << "ERROR: Errors have only been provided for some of these measurements."           << std::endl;
  	std::cout << "       it's therefore not clear if you want me to do a chi2 or a likelihood fit" << std::endl;
  }
  if (!allCor  && someCor){
  	std::cout << "ERROR: Correlations have only been provided for some of these measurements." << std::endl;
  	std::cout << "       it's therefore not clear if you want me to use these correlations"    << std::endl;
  }

  if (allCor){
  	mvgFit = true;
  }
  else if (allErrs){
  	gausFit = true;
  }
  else{
  	poisFit = true;
  }

  PoloLLHSum llhsum;
  
  if (poisFit){
    std::vector<PoloMeas> ordMeas = meas.getMeasList( getIDList() );
    for (unsigned i = 0; i < _obs.size(); i++){
      PoloLLHPoisson llh(*_obs.at(i), ordMeas.at(i).getVal());
      llhsum.addLLH(&llh);
    }
  }

  if (gausFit){
    std::vector<PoloMeas> ordMeas = meas.getMeasList( getIDList() );
    for (unsigned i = 0; i < _obs.size(); i++){
      PoloLLHGaus llh(*_obs.at(i), ordMeas.at(i).getVal(), ordMeas.at(i).getErr());
      llhsum.addLLH(&llh);
    }
  }

  if (mvgFit){

    TVectorD vals = meas.getVals    ( getIDList() );
    TVectorD errs = meas.getErrs    ( getIDList() );
    TMatrixD cors = meas.getCorMatix( getIDList() );

    PoloLLHMultVarGaus llh(_obs, vals, errs, cors);
    llhsum.addLLH(&llh);

  }

  return llhsum;
}


PoloLLHSum PoloObsSet::getLLHForToys( ){
  
  PoloLLHSum llhsum;
  for (unsigned i = 0; i < _obs.size(); i++){
    PoloLLHPoisson llh(*_obs.at(i));
    llhsum.addLLH(&llh);
  }

  return llhsum;
}

std::vector<PoloObsID> PoloObsSet::getIDList(){
  std::vector<PoloObsID> obsIDList;
  for (unsigned i = 0; i < _obs.size(); i++){
  	obsIDList.push_back( _obs.at(i)->getPoloObsID() );
  }
  return obsIDList;
}


int PoloObsSet::getObsNum ( PoloObsID& id ){
  
  for (unsigned i = 0; i < _obs.size(); i++){
    if (_obs.at(i)->getPoloObsID() == id) return i;
  }  
  return -1;
}

PoloObsAbs* PoloObsSet::getObs ( PoloObsID& id ){
  
  for (unsigned i = 0; i < _obs.size(); i++){
    if (_obs.at(i)->getPoloObsID() == id) return _obs.at(i);
  }  
  return 0;
}

void PoloObsSet::print(){

  std::cout << "-----------------------------------------------------" << std::endl;
  std::cout << "---------------- PoloObsSet::print() ----------------" << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;

  for (unsigned i = 0; i < _obs.size(); i++){
    std::cout << "PoloObsID = " <<_obs.at(i)->getObsIDStr() << std::endl;
    std::cout << std::endl;
    _obs.at(i)->print();
    std::cout << "-----------------------------------------------------" << std::endl;
  }



}


PoloObsSet::~PoloObsSet(){

}



