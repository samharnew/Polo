#include "PoloFPSnapshot.h"

PoloFPSnapshot::PoloFPSnapshot(MINT::MinuitParameterSet* parSet) :
  _parSet(parSet), 
  _neg2LLH(0.0)
{
  
  if (parSet != 0){
    for (unsigned i = 0; i < _parSet->size(); i++){
      _mean.push_back( _parSet->getParPtr(i)->mean() );
      _err .push_back( _parSet->getParPtr(i)->err () );
      _errp.push_back( ((MINT::FitParameter*)_parSet->getParPtr(i))->errPos () );
      _errm.push_back( ((MINT::FitParameter*)_parSet->getParPtr(i))->errNeg () );
      _name.push_back( _parSet->getParPtr(i)->name() );
    }
  }
  _correlations.ResizeTo(size(), size());

}

PoloFPSnapshot::PoloFPSnapshot( std::vector<TString> names ) :
  _parSet(0), 
  _neg2LLH(0.0)
{

  for (unsigned i = 0; i < names.size(); i++){
    _mean.push_back( 0.0 );
    _err .push_back( 0.0 );
    _errp.push_back( 0.0 );
    _errm.push_back( 0.0 );
    _name.push_back( names.at   (i) );
  }
  
  _correlations.ResizeTo(size(), size());
  
  for (int i = 0; i < size(); i++){
    for (int j = 0; j < size(); j++){
      _correlations(i,j) = 0.0;
      if (i == j) _correlations(i,j) = 1.0;
    }
  }

}




PoloFPSnapshot::PoloFPSnapshot(TString filename, TString dirname) :
  _parSet(0), 
  _neg2LLH(0.0)
{

  TFile* file = new TFile(filename, "READ");
  TDirectory* dir = file;

  if (dirname != ""){
    dir = file->GetDirectory(dirname);
  }

  if (dir == 0){
    std::cout << "File does not exist!" << std::endl;
  }
  
  loadOverwrite(dir);

  file->Close();

}

PoloFPSnapshot::PoloFPSnapshot(TDirectory* dir){

  loadOverwrite(dir);

}


void PoloFPSnapshot::loadOverwrite(TDirectory* dir){

  TMatrixD* correlations = (TMatrixD*)dir->Get("correlationMatrix"   );
  TTree*    tree         = (TTree   *)dir->Get("FitParameterSnapshot");
  TMatrixD* neg2LLH      = (TMatrixD*)dir->Get("neg2LLH");

  if (correlations == 0){
    std::cout << "correlations does not exist!" << std::endl;
  }
  if (tree == 0){
    std::cout << "tree does not exist!" << std::endl;
  }  
  if (neg2LLH == 0){
    std::cout << "neg2LLH does not exist!" << std::endl;
    _neg2LLH = 0;
  }  
  else{
    _neg2LLH = (*neg2LLH)(0,0);
  }
  //Set all the branch addresses 

  _correlations.ResizeTo(*correlations);
  _correlations = *correlations;
  
  TString* parameterName = new TString(0);
  double  mean         = 0.0;
  double  err          = 0.0;
  double  errp         = 0.0;
  double  errm         = 0.0;

  tree->SetBranchAddress( "parameterName", &parameterName );
  tree->SetBranchAddress( "mean"         , &mean          );
  tree->SetBranchAddress( "err"          , &err           );   
  tree->SetBranchAddress( "errp"         , &errp          );
  tree->SetBranchAddress( "errm"         , &errm          );  
  
  _name .clear();
  _mean .clear();
  _err  .clear();
  _errp .clear();
  _errm .clear();

  for (int i = 0; i < tree->GetEntries(); i++){
    tree->GetEntry(i);
    _name .push_back(*parameterName);
    _mean .push_back(mean         );
    _err  .push_back(err          );
    _errp .push_back(errp         );
    _errm .push_back(errm         );
  }
  
}



void PoloFPSnapshot::updateSnapshotFromFPs(){

  for (int i = 0; i < size(); i++){
    _mean.at(i) = _parSet->getParPtr(i)->mean();
    _err .at(i) = _parSet->getParPtr(i)->err ();
    _errp.at(i) = ((MINT::FitParameter*)_parSet->getParPtr(i))->errPos();
    _errm.at(i) = ((MINT::FitParameter*)_parSet->getParPtr(i))->errNeg();    
  }

}

void PoloFPSnapshot::updateFPsFromSnapshot(){

  for (int i = 0; i < size(); i++){
  	_parSet->getParPtr(i)->setCurrentFitVal( _mean.at(i) );
  }

}

int PoloFPSnapshot::size(){
  return _name .size();
}

MINT::MinuitParameterSet* PoloFPSnapshot::getParSet(){
  return _parSet;
}

void PoloFPSnapshot::updateCorrelations( MINT::Minimiser* mini ){

  TMatrixTSym<double> covMatrixFull = mini->covMatrixFull();
  
  int npars     = size();
  int nparsMini = mini->nPars();
  
  std::vector<int> parNumbers;

  
  for (int i = 0; i < npars; i++){
    MINT::IMinuitParameter* par =  _parSet->getParPtr(i);    
    for (int j = 0; j < nparsMini; j++){
      if ( mini->getParPtr(j) == par ){
        parNumbers.push_back(j);
        break;
      } 
    }
  }


  for (int i = 0; i < npars; i++){
    for (int j = 0; j < npars; j++){
      int pari = parNumbers.at(i);  
      int parj = parNumbers.at(j);
      double vari = covMatrixFull(pari, pari);
      double varj = covMatrixFull(parj, parj); 
      if (vari == 0.0 || varj == 0.0) { _correlations(i,j) = 0.0; }  
      else{
        _correlations(i,j) = covMatrixFull(pari, parj)/sqrt(vari*varj);
      }
    }
  }
  
}

int PoloFPSnapshot::findID(TString name){
  for (int i = 0; i < size(); i++){
    if ( getName(i) == name) return i;
  }
  return -1;
}

void PoloFPSnapshot::setNeg2LLH(double val){
  _neg2LLH = val;
}

double PoloFPSnapshot::getNeg2LLH() const{
  return _neg2LLH;
}

MINT::IMinuitParameter* PoloFPSnapshot::getParPtr(int i){
  return _parSet->getParPtr(i);   
}

int PoloFPSnapshot::getID(MINT::counted_ptr<MINT::FitParameter> fp){
  for (int i = 0; i < size(); i++){
    if ( getName(i) == fp->name()) return i;
  }
  return -1;
}

void PoloFPSnapshot::copy(PoloFPSnapshot& snap){

  _parSet = snap._parSet;
  _mean = snap._mean;
  _err  = snap._err ;
  _errp = snap._errp;
  _errm = snap._errm;
  _name = snap._name;
  _correlations.ResizeTo(snap._correlations);
  _correlations = snap._correlations;
  _neg2LLH = snap._neg2LLH;

}

void PoloFPSnapshot::clearVals(){

  for (int i = 0; i < size(); i++){
    _mean.at(i) = 0.0;
    _err .at(i) = 0.0;
    _errp.at(i) = 0.0;
    _errm.at(i) = 0.0;
  }
  for (int i = 0; i < size(); i++){
    for (int j = 0; j < size(); j++){
      _correlations(i,j) = 0.0;
      if (i == j) _correlations(i,j) = 1.0;
    }
  }

}

void PoloFPSnapshot::copyCommon(PoloFPSnapshot& snap){

  _neg2LLH = snap._neg2LLH;

  for (int i = 0; i < size(); i++){
    int idi = snap.findID(getName(i));
    if (idi == -1) continue;

    _mean.at(i) = snap._mean.at(idi);
    _err .at(i) = snap._err .at(idi);
    _errp.at(i) = snap._errp.at(idi);
    _errm.at(i) = snap._errm.at(idi); 

    for (int j = 0; j < size(); j++){
      int idj = snap.findID(getName(j));
      if (idj == -1) continue;
      _correlations(i,j) = snap._correlations(idi,idj);
    }
  }

}

double PoloFPSnapshot::mean(int i){
  return _mean .at(i);
}

double PoloFPSnapshot::err (int i){
  return _err .at(i);
}

double PoloFPSnapshot::errp (int i){
  if (_errp .at(i) == 0.0) return err(i);
  return _errp .at(i);
}

double PoloFPSnapshot::errm (int i){
  if (_errm .at(i) == 0.0) return err(i);
  return _errm .at(i);
}

void PoloFPSnapshot::setErr (int i, double val){
  _err.at(i) = val;
}

void PoloFPSnapshot::setErrp(int i, double val){
  _errp.at(i) = val;
}

void PoloFPSnapshot::setErrm(int i, double val){
  _errm.at(i) = val;
}    

void PoloFPSnapshot::setMean(int i, double val){
  _mean.at(i) = val;
}

double PoloFPSnapshot::covarience(int i, int j){
  double erri = err(i);
  double errj = err(j);
  double cor  = correlation(i,j);
  return erri*errj*cor;
}

double PoloFPSnapshot::correlation(int i, int j){
  return _correlations(i,j);
}

void PoloFPSnapshot::setCorrelation(int i, int j, double val){
  _correlations(i,j) = val;
}

TMatrixD PoloFPSnapshot::getCovarienceMatrix(){
  int npars = size();
  
  TMatrixD covMatrix(npars, npars);

  for (int i = 0; i < npars; i++){
    for (int j = 0; j < npars; j++){
      double cor  = _correlations(i,j);
      double erri = _err.at(i);
      double errj = _err.at(j);
      
      covMatrix(i,j) = cor*erri*errj;

    }
  }
 
  return covMatrix;
}

std::vector< double  > PoloFPSnapshot::getMeanVect(){
  
  return _mean;

}



TMatrixD PoloFPSnapshot::getRedCovarienceMatrix( TVectorD& redMean, std::vector<int>& parNums ){

  int npars = size();
  
  parNums.clear();

  for (int i = 0; i < npars; i++){

    double erri = _err.at(i);
    if (erri == 0.0) continue;
    parNums.push_back(i);

  }  
  
  int nRedPars = parNums.size();

  TMatrixD redCovMatrix(nRedPars, nRedPars);
  redMean.ResizeTo(nRedPars);

  for (int i = 0; i < nRedPars; i++){

    int parNumi = parNums.at(i);
    redMean(i) = _mean.at(parNumi);

    for (int j = 0; j < nRedPars; j++){
      int parNumj = parNums.at(j);

      double cor  = _correlations(parNumi,parNumj);
      double erri = _err.at(parNumi);
      double errj = _err.at(parNumj);
      
      redCovMatrix(i,j) = cor*erri*errj;

    }
  }
  
  return redCovMatrix;
}

TString PoloFPSnapshot::getName (int i){
  return _name.at(i);
}

void PoloFPSnapshot::replaceAll(TString find, TString replace){
  for (unsigned i = 0; i < _name.size(); i++){
    _name.at(i).ReplaceAll(find, replace);
  }
}




PoloFPSnapshot PoloFPSnapshot::getRandomisedSnapshot(TRandom* random){
  PoloFPSnapshot copySnap(*this);
  copySnap.randomise(random);
  return copySnap;
}


void PoloFPSnapshot::updateFPsFromRandomisedSnapshot(TRandom* random){
  PoloFPSnapshot randSnap = getRandomisedSnapshot(random);
  randSnap.updateFPsFromSnapshot();
}

void PoloFPSnapshot::randomise(TRandom* random){

  std::vector<int> indexToParNum; 
  TVectorD redMean;
  TMatrixD redCov = getRedCovarienceMatrix(redMean, indexToParNum);

  //Stealing some code from RooFit and method from https://en.wikipedia.org/wiki/Multivariate_normal_distribution#Drawing_values_from_the_distribution)
  // - find a matrix A such that AA^T = Sigma (the covarience matrix)
  // - generate a vector, v, of random values, each distiuted to a Gaussian of width 1 mean 0
  // - x = mu + Av 
  
  TDecompChol tdc(redCov) ;
  tdc.Decompose() ;
  TMatrixD U = tdc.GetU() ;
  TMatrixD TU(TMatrixD::kTransposed,U) ;    
  

  TVectorD x  = redMean;
  TVectorD v  = redMean;

  for (int i = 0; i < v.GetNrows(); i++){
    v[i] = random->Gaus();
  }

  x = redMean + TU*v;

  int nRedParams = redMean.GetNrows();

  for (int i = 0; i < nRedParams; i++){
    int parNum = indexToParNum.at(i);
    _mean.at(parNum) = x(i);
  }

}



double PoloFPSnapshot::pull(PoloFPSnapshot& other, MINT::counted_ptr<MINT::FitParameter> fp){

  int i = getID(fp);

  double gen = mean(i);
  double fit = other.mean(i);
  double err = other.err(i);

  return (gen-fit)/err;

}

bool PoloFPSnapshot::equal(PoloFPSnapshot& other, double tollerance){

  for (int i = 0; i < size(); i++){
    
    double mean1 =       mean(i);
    double mean2 = other.mean(i);
    double err1  =       err (i);
    double err2  = other.err (i);
    
    if (err1 == 0.0 && err2 == 0.0){
      if (mean1 != mean2) return false;
    }
    else{
      double resid = mean1 - mean2;
      double err   = sqrt(err1*err1 + err2*err2);
      if ( fabs(resid/err) > tollerance ) return false;
    }
  }

  return true; 
}  




void PoloFPSnapshot::compare(PoloFPSnapshot& other){

  for (int i = 0; i < size(); i++){
    std::cout << "---------------------  " << i << "  ---------------------" << std::endl;
    std::cout << getName(i) << std::endl;
    std::cout << "mean  : " << _mean.at(i) << "      " << other._mean.at(i) << std::endl;
    std::cout << "error : " << _err .at(i) << "      " << other._err .at(i) << std::endl;
    std::cout << "correlations : " << std::endl;
    for (int j = 0; j < size(); j++){
      if ( (_correlations(i,j) - other._correlations(i,j)) < 0.01) continue;
      std::cout << "( " << _correlations(i,j) << ", " << other._correlations(i,j) << " )   ";
      if (j%6 == 5) std::cout << std::endl;
    }
    std::cout << std::endl;
  }  

}

void PoloFPSnapshot::print(){

  std::cout << "PoloFPSnapshot::print()" << std::endl;
  
  std::cout << std::left << std::setw(25) << "Par Name" 
            << std::left << std::setw(14) << "mean" 
            << std::left << std::setw(14) << "err "
            << std::left << std::setw(14) << "errp"
            << std::left << std::setw(14) << "errm" << std::endl;

  for (int i = 0; i < size(); i++){
    
    if ( errp(i) != 0.0 ){
      std::cout << std::left << std::setw(25) << getName(i) 
                << std::left << std::setw(14) << mean(i)
                << std::left << std::setw(14) << err(i)
                << std::left << std::setw(14) << errp(i)
                << std::left << std::setw(14) << errm(i) << std::endl;
    }
    else{
      std::cout << std::left << std::setw(20) << getName(i) 
                << std::left << std::setw(14) << mean(i)
                << std::left << std::setw(14) << err(i) << std::endl;    
    }

  }  

  std::cout << "-----------------------------" << std::endl;

}

void PoloFPSnapshot::pulls(PoloFPSnapshot& other){

  for (int i = 0; i < size(); i++){
  	double pull = (_mean.at(i) - other._mean.at(i)) / other._err.at(i);
  	std::cout << getName(i) << " : " << pull << std::endl;
  }  

}

void PoloFPSnapshot::combineUncertainties(PoloFPSnapshot& other){

  TMatrixD covarienceMatrix(size(), size());

  for (int i = 0; i < size(); i++){

    int idotheri = other.findID( getName(i) );
    

    for (int j = 0; j < size(); j++){
      int idotherj = other.findID( getName(j) );
      
      covarienceMatrix(i,j) = covarience(i,j);
      
      if (idotheri != -1 && idotherj != -1){
        covarienceMatrix(i,j) += other.covarience(idotheri, idotherj);
      }
      
    }  

  }  
  
  for (int i = 0; i < size(); i++){
    
    double erri = sqrt(covarienceMatrix(i,i));

    setErr (i, erri);
    setErrp(i, erri);
    setErrm(i, erri);

    for (int j = 0; j < size(); j++){
      
      double errj = sqrt(covarienceMatrix(j,j));
      double corr = covarienceMatrix(i,j)/(erri*errj);

      setCorrelation(i,j,corr);
    }  

  }      

}

void PoloFPSnapshot::load(TString filename){
  PoloFPSnapshot snap(filename);
  copyCommon(snap);
}

void PoloFPSnapshot::save(TString filename){

  TFile* file = new TFile(filename, "RECREATE");
  
  save(file);

  file->Close();

}

void PoloFPSnapshot::save(TDirectory* dir){

  dir->cd();

  _correlations.Write("correlationMatrix");
  
  TMatrixD neg2LLH(1, 1); 
  neg2LLH(0,0) = _neg2LLH;
  neg2LLH.Write("neg2LLH");


  TTree* tree = new TTree("FitParameterSnapshot", "FitParameterSnapshot");

  TString parameterName = "" ;
  double  mean          = 0.0;
  double  err           = 0.0;
  double  errp          = 0.0;
  double  errm          = 0.0;

  tree->Branch( "parameterName", &parameterName);
  tree->Branch( "mean"         , &mean         );
  tree->Branch( "err"          , &err          );
  tree->Branch( "errp"         , &errp         );
  tree->Branch( "errm"         , &errm         );
  
  for (int i = 0; i < size(); i++){
    parameterName = _name.at(i);
    mean          = _mean.at(i);
    err           = _err .at(i);
    errp          = _errp.at(i);
    errm          = _errm.at(i);
    tree->Fill();
  }
  
  tree->Write();

}

PoloConstraint* PoloFPSnapshot::getConstraint(){
  

  std::vector<int> indexToParNum; 
  TVectorD redMean;
  TMatrixD redCov = getRedCovarienceMatrix(redMean, indexToParNum);
  
  std::vector< MINT::counted_ptr<MINT::FitParameter> > redDependencies;  
  for (unsigned i = 0; i < indexToParNum.size(); i++){
    redDependencies.push_back( (MINT::FitParameter*)getParPtr( indexToParNum.at(i) ) );
  }

  //Have to return this as a pointer. The MinuitParameterSet holds pointers,
  //not counted pointers. Therefore if we make  
  PoloConstraint* constraint = new PoloConstraint(redDependencies,redMean,redCov);
  return constraint;

}


PoloConstraint* PoloFPSnapshot::getConstraint(PoloFPSnapshot& other){
  
  PoloFPSnapshot snap(*this);
  snap.clearVals();
  snap.copyCommon(other);
  return snap.getConstraint();

}


PoloConstraint* PoloFPSnapshot::getConstraintFromFile(TString filename){

  PoloFPSnapshot snap( *this );
  snap.clearVals();
  snap.load(filename);
  return snap.getConstraint();

}

PoloConstraint* PoloFPSnapshot::getConstraint( MINT::MinuitParameterSet* parSet ){
  
  PoloFPSnapshot snap(parSet);
  return snap.getConstraint(*this);

}


PoloFPSnapshot::~PoloFPSnapshot(){

}





