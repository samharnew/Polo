#include "PoloFPSnapshotEnsemble.h"


PoloFPSnapshotEnsemble::PoloFPSnapshotEnsemble() {

 
}

void PoloFPSnapshotEnsemble::add( PoloFPSnapshot shapshot ){

  _shapshots .push_back( shapshot   );

} 

double PoloFPSnapshotEnsemble::getMinNeg2LLH(){

  PoloMinMaxFinder stats;

  for (unsigned i = 0; i < _shapshots.size(); i++){
    stats.add( _shapshots.at(i).getNeg2LLH() );
  }   
  
  return stats.getMin();

}


double PoloFPSnapshotEnsemble::getMedianError(int pari){

  std::vector<double> errors; 
  
  int nSnaps = _shapshots.size();

  for (int i = 0; i < nSnaps; i++){
    errors.push_back( _shapshots.at(i).err(pari) );
  }

  std::sort(errors.begin(),errors.end());
  
  if ( nSnaps%2 != 0){
    return errors.at( (nSnaps - 1)/2 );
  }
  
  return 0.5*(errors.at( (nSnaps/2) ) + errors.at( (nSnaps/2) - 1 ));

}



PoloFPSnapshot PoloFPSnapshotEnsemble::getBestFit(){
  
  int nSnaps = _shapshots.size();

  double minNeg2LLH = _shapshots.at(0).getNeg2LLH();
  int bestSol = 0;

  for (int i = 1; i < nSnaps; i++){
    double thisNeg2LLH = _shapshots.at(i).getNeg2LLH();
    if (thisNeg2LLH < minNeg2LLH){
      bestSol = i;
      minNeg2LLH = thisNeg2LLH;
    }
  }
  
  return _shapshots.at(bestSol);

} 



PoloFPSnapshot PoloFPSnapshotEnsemble::getSysSnapshot(){

  int nParams = _shapshots.at(0).size();
  int nSnaps  = _shapshots.size();
  
  PoloCovarianceFinder covFinder( nParams );
  
  for (int i = 0; i < nSnaps; i++){
    covFinder.addEntry( _shapshots.at(i).getMeanVect() ); 
  }

  PoloFPSnapshot snappy = _shapshots.at(0);
  
  for (int i = 0; i < nParams; i++){
    
    double widthi = sqrt( covFinder.getVariance(i) );
    if (widthi != widthi) widthi = 0.0;

    snappy.setErr (i, widthi               );
    snappy.setErrp(i, widthi               );
    snappy.setErrm(i, widthi               );
    snappy.setMean(i, covFinder.getMean(i) );
  
    for (int j = 0; j < nParams; j++){
       
      double correlation = covFinder.getCorrelation(i,j);
      if (correlation != correlation){
        if (i == j) snappy.setCorrelation(i,j,1.0);
        else        snappy.setCorrelation(i,j,0.0);          
      }
      else{
        snappy.setCorrelation ( i, j, correlation );
      }

    }
  
  }
  
  return snappy;
  
}

bool PoloFPSnapshotEnsemble::containsEqual( PoloFPSnapshot& shapshot, double tollerance ){

  int nSnaps = _shapshots.size();

  for (int i = 0; i < nSnaps; i++){
    if ( _shapshots.at(i).equal(shapshot, tollerance) == true ) return true;
  }

  return false;

}

void PoloFPSnapshotEnsemble::save(TString filename){
  
  TFile* file = new TFile( filename, "RECREATE");
  
  save(file);

  file->Close();

}

void PoloFPSnapshotEnsemble::save(TDirectory* dir){
  
  dir->cd();

  int nSnaps = _shapshots.size();

  for (int i = 0; i < nSnaps; i++){
    TString dirname = "snapshot";
    dirname += i;
    TDirectory* diri = dir->mkdir(dirname);
    _shapshots.at(i).save(diri);
  }

}

void PoloFPSnapshotEnsemble::load(TString filename){
  
  TFile* file = new TFile( filename, "READ");
  
  load(file);
  
  file->Close();

}

void PoloFPSnapshotEnsemble::load(TDirectory* dir){
  
  
  for (int i = 0; i < 10000; i++){
    TString dirname = "snapshot";
    dirname += i;
    if ( dir->GetDirectory(dirname) != 0){
      PoloFPSnapshot snap( dir->GetDirectory(dirname) );
      add(snap);
    }
    else{
      break;
    }
  }
  

}

PoloFPSnapshotEnsemble::~PoloFPSnapshotEnsemble() {
    

}




