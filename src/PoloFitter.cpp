#include "PoloFitter.h"

PoloFitter::PoloFitter(MINT::MinuitParameterSet* parSet) :
  _parSet(parSet),
  _minimiser(0),
  _minos(0)
{
  //MINT::Minimisable needs this...
  setPset(_parSet);
}
    
  
void PoloFitter::addObs       (PoloObsAbs   & obs, PoloMeas meas ){
  if (meas.hasErr()){
    _llhTerms.push_back( new PoloLLHGaus(obs, meas.getVal(), meas.getErr()) );
  }
  else{
    _llhTerms.push_back( new PoloLLHPoisson(obs, meas.getVal()) );    
  }
}

void PoloFitter::addObs       (PoloObsSet   & obsSet, PoloMeasSet& measSet ){
  _llhTerms.push_back( obsSet.getLLH(measSet).clone() );
}


void PoloFitter::addObs       (PoloObsAbs   & obs ){
  _llhTerms.push_back( new PoloLLHPoisson(obs, 0.0) );    
}

void PoloFitter::addObs       (PoloObsSet   & obsSet ){
  _llhTerms.push_back( obsSet.getLLHForToys().clone() );
}

void PoloFitter::addLLH       (PoloLLHAbs   & llh       ){
  _llhTerms.push_back( llh.clone() );
}

void PoloFitter::addConstraint(PoloConstraint& constraint){
  _constraints.push_back( constraint.clone() );
}

void PoloFitter::addRandomiser(PoloConstraint& randomiser){
  _randomisers.push_back( randomiser.clone() );
}

MINT::Minimiser* PoloFitter::getMinimiser(){
  
  if (_minimiser == 0){
    _minimiser = new MINT::Minimiser(this);
  }
  return _minimiser;

}


void PoloFitter::fixNonDependencies(){

  for (unsigned fp = 0; fp < _parSet->size(); fp++){
    TString parname = _parSet->getParPtr(fp)->name();
    
    bool isDependencyOfObervable = false;

    for (unsigned llhi = 0; llhi < _llhTerms.size(); llhi++){
      std::vector< MINT::counted_ptr<MINT::FitParameter> > depends = _llhTerms.at(llhi)->getDependencies();
      
      for (unsigned dep = 0; dep < depends.size(); dep++){
        if (depends.at(dep) == 0) continue;
        if (parname == depends.at(dep)->name()) isDependencyOfObervable = true;
      }

    }
    
    bool isDependencyOfConstraint = false;

    for (unsigned coni = 0; coni < _constraints.size(); coni++){
      std::vector< MINT::counted_ptr<MINT::FitParameter> > depends = _constraints.at(coni)->getDependencies();
      
      for (unsigned dep = 0; dep < depends.size(); dep++){
        if (depends.at(dep) == 0) continue;
        if (parname == depends.at(dep)->name()) isDependencyOfConstraint = true;
      }

    }

    if (isDependencyOfObervable == false && isDependencyOfConstraint == false) ((MINT::FitParameter*)_parSet->getParPtr(fp))->fix();

  }

}


void PoloFitter::setFPsFromConstraints(TRandom* random){

  for (unsigned i = 0; i < _constraints.size(); i++){
    _constraints.at(i)->genToyFPs(random);
  }

}


void PoloFitter::randFPs        (TRandom* random){

  for (unsigned i = 0; i < _constraints.size(); i++){
    _constraints.at(i)->randFPs(random);
  }
  for (unsigned i = 0; i < _constraints.size(); i++){
    _randomisers.at(i)->randFPs(random);
  }

}


void PoloFitter::fixConstrainedFPs      (){

  for (unsigned i = 0; i < _constraints.size(); i++){
    _constraints.at(i)->fixFPs();
  }

}

void PoloFitter::fixConstrainedFPsToMean(){


  for (unsigned i = 0; i < _constraints.size(); i++){
    _constraints.at(i)->fixFPsToMean();
  }

}

void PoloFitter::unfixConstrainedFPs(){

  for (unsigned i = 0; i < _constraints.size(); i++){
    _constraints.at(i)->unfixFPs();
  }

}

void PoloFitter::clearLLHs(){

  _llhTerms.clear();

}

double PoloFitter::calcNeg2LLHSum(){
  
  double val = 0.0; 
  for (unsigned int i = 0; i < _llhTerms.size(); i++){
    val += _llhTerms.at(i)->getNeg2LLH();
  }
  return val;
}

double PoloFitter::calcConstraintNeg2LLHSum(){

  double val = 0.0; 
  for (unsigned int i = 0; i < _constraints.size(); i++){
    val += _constraints.at(i)->getNeg2LLH();
  }
  return val;
}

double PoloFitter::getVal(){

  return calcNeg2LLHSum() + calcConstraintNeg2LLHSum(); 

}

int PoloFitter::fit(PoloFPSnapshot* results, MINT::Minimiser* mini){
  

  bool migradHesseSuccess = 1;
  bool minosSuccess       = 1;

  if (mini  == 0) mini = getMinimiser();
  if (_minos == 1) migradHesseSuccess = mini->continueMinosFit();
  else            migradHesseSuccess = mini->continueFit();  
  
  MINT::FitParameter::printResultFormat();

  //If _minosErrorsFlag is true, loop over the parameters that we want to have
  //minos errors for.

  if (results) {
    results->updateSnapshotFromFPs();
    results->updateCorrelations(mini);
    results->setNeg2LLH( getVal() );
  }

  int errCode = 0;
  TString errMsg = "FIT SUCCESSFUL";
   
  double neg2llh = 0.0;
  double edm     = 0.0;
  double errdef  = 0.0;
  int nparfloat  = 0;
  int npar       = 0;
  int istat      = 0;  
  //0 - not calculated
  //1 - only approximate
  //2 - not pos def
  //3 - full accurate

  mini->mnstat(neg2llh, edm, errdef, nparfloat, npar, istat);
 
  if      ( migradHesseSuccess == false   ) { errCode = 1; errMsg = "MIGRAD / HESSE FAILED";         }
  else if ( minosSuccess       == false   ) { errCode = 2; errMsg = "MINOS FAILED";                  }
  else if ( edm                > 0.01     ) { errCode = 4; errMsg = "BAD EDM";                       }
  else if ( neg2llh            != neg2llh ) { errCode = 5; errMsg = "NEG2LLH IS NaN";                }
  else if ( istat              == 0       ) { errCode = 6; errMsg = "COVARIENCE MATRIX NOT CALC";    }
  else if ( istat              == 1       ) { errCode = 7; errMsg = "COVARIENCE MATRIX ONLY APPROX"; }
  else if ( istat              == 2       ) { errCode = 8; errMsg = "COVARIENCE MATRIX NOT POS DEF"; }
  

  std::cout << "********************** ObservableFitter::fit() **********************" << std::endl;
  std::cout << "*********************************************************************" << std::endl;
  std::cout << "                         " << errMsg << std::endl;
  std::cout << "*********************************************************************" << std::endl;
  
  return errCode;

}

int PoloFitter::fitWFixedCon(int nfits, PoloFPSnapshot* statresults, PoloFPSnapshot* sysresults, TRandom* random, MINT::Minimiser* mini){

  bool migradHesseSuccess = 1;
  bool minosSuccess       = 1;
  
  fixConstrainedFPsToMean();

  if (mini   == 0) mini = getMinimiser();

  int errorCode = fit(statresults, mini);
  
  PoloFPSnapshotEnsemble fpEnsemble;

  for (int i = 0; i < nfits; i++){
    setFPsFromConstraints(random);
    fit(sysresults, mini);
    fpEnsemble.add(*sysresults);
  }
  
  if (sysresults != 0){
    *sysresults = fpEnsemble.getSysSnapshot();
  }

  return errorCode;
  
}

void PoloFitter::generateToy(TRandom* random, PoloFPSnapshot* snap, bool sampleConstraints){
  
  if (snap!=0) snap->updateFPsFromSnapshot();

  //This is important to get the correct pulls. The true values need to
  //be sampled from the constraints

  if (sampleConstraints) setFPsFromConstraints(random);
 
  if (snap!=0) snap->updateSnapshotFromFPs();

  for (unsigned i = 0; i < _llhTerms.size(); i++){
    _llhTerms.at(i)->genToyMeas(random);     
  }

}


PoloFPSnapshot PoloFitter::getShapshot(){
  PoloFPSnapshot snap(_parSet); 
  return snap;
}

std::vector< MINT::counted_ptr<MINT::FitParameter> > PoloFitter::getDependencies(){

  std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies;

  for (unsigned obs = 0; obs < _llhTerms.size(); obs++){
    std::vector< MINT::counted_ptr<MINT::FitParameter> > depends = _llhTerms.at(obs)->getDependencies();
    
    for (unsigned dep = 0; dep < depends.size(); dep++){

      MINT::counted_ptr<MINT::FitParameter> newDependency = depends.at(dep);
      bool isItAlreadyInList = false;

      for (unsigned exdep = 0; exdep < dependencies.size(); exdep++){
        if (depends.at(dep) == dependencies.at(exdep)) {
          isItAlreadyInList = true;
          break;
        }
      }

      if (isItAlreadyInList == false) dependencies.push_back(newDependency);

    }

  }
  
  for (unsigned obs = 0; obs < _constraints.size(); obs++){
    std::vector< MINT::counted_ptr<MINT::FitParameter> > depends = _constraints.at(obs)->getDependencies();
    
    for (unsigned dep = 0; dep < depends.size(); dep++){

      MINT::counted_ptr<MINT::FitParameter> newDependency = depends.at(dep);
      bool isItAlreadyInList = false;

      for (unsigned exdep = 0; exdep < dependencies.size(); exdep++){
        if (depends.at(dep) == dependencies.at(exdep)) {
          isItAlreadyInList = true;
          break;
        }
      }

      if (isItAlreadyInList == false) dependencies.push_back(newDependency);

    }

  }


  return dependencies;


}

void PoloFitter::print(){
  
  std::cout << "-----------------------------------------------------" << std::endl;
  std::cout << "---------------- PoloFitter::print() ----------------" << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;
  std::cout << " printing all contributions to the total -neg2LLH    " << std::endl;
  std::cout << " that is being minimised " << std::endl << std::endl;

  for (unsigned llhi = 0; llhi < _llhTerms.size(); llhi++){
    _llhTerms.at(llhi)->printOneliner();
  }

}

PoloFitter::~PoloFitter(){

}

