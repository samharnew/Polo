#include "PoloConK0PiPiCiSiCleo.h"


PoloConK0PiPiCiSiCleo::PoloConK0PiPiCiSiCleo( PoloFPSetDtoFBinned& dToKSpipi, PoloFPSetDtoFBinned& dToKLpipi, TString opt){
  
  PoloInputsK0PiPi cleoInputs;

  int nKSbins = dToKSpipi.size()/2;
  int nKLbins = dToKLpipi.size()/2;
 
  int dim = nKSbins*2 + nKLbins*2; //each decay has a constraint for both ci and si

  _value        .ResizeTo(dim);
  _mean         .ResizeTo(dim);
  _covarience   .ResizeTo(dim, dim);
  _invcovarience.ResizeTo(dim, dim);
  
  if (nKSbins != 8 || nKLbins != 8){
    std::cout << "ERROR: This ci si constraint assumes 8 bins pairs for both KSpipi and KLpipi" << std::endl;
  }

  //numering goes like this... (for 8 bins)

  //dToKSpipi ci [0 ,7 ] 
  //dToKSpipi si [8 ,15] 
  //dToKLpipi ci [16,23]
  //dToKLpipi si [24,31]
  
  for (int i = 1; i <= nKSbins; i++){
  	_dependencies.push_back( dToKSpipi.getFPSetFromBinNum(i).getFitParameterc() );
  }
  for (int i = 1; i <= nKSbins; i++){
  	_dependencies.push_back( dToKSpipi.getFPSetFromBinNum(i).getFitParameters() );
  }
  for (int i = 1; i <= nKLbins; i++){
  	_dependencies.push_back( dToKLpipi.getFPSetFromBinNum(i).getFitParameterc() );
  } 
  for (int i = 1; i <= nKLbins; i++){
  	_dependencies.push_back( dToKLpipi.getFPSetFromBinNum(i).getFitParameters() );
  }

  for (int i = 0; i < dim; i++){

    bool KSci = false;
    bool KSsi = false;
    bool KLci = false;
    bool KLsi = false;

  	if      (i >= 0         && i < 1*nKSbins          ) KSci = true;
    else if (i >= nKSbins   && i < 2*nKSbins          ) KSsi = true;
    else if (i >= 2*nKSbins && i < 2*nKSbins + nKLbins) KLci = true;
    else                                                KLsi = true;
    
    int signi = 1;
    
    // Note that the CLEO paper uses different conventions for
    // KLpipi and KSpipi so an alteration must be made
    // - KL uses a different convention -> c = -c and s = -s
    if (KLci || KLsi) signi = -1;

  	_mean[i] = signi*cleoInputs.getMean(i);

    for (int j = 0; j < dim; j++){

      bool KScj = false;
      bool KSsj = false;
      bool KLcj = false;
      bool KLsj = false;

      if      (j >= 0         && j < 1*nKSbins          ) KScj = true;
      else if (j >= nKSbins   && j < 2*nKSbins          ) KSsj = true;
      else if (j >= 2*nKSbins && j < 2*nKSbins + nKLbins) KLcj = true;
      else                                                KLsj = true;
    
      int signj = 1;
      if (KLcj || KLsj) signj = -1;

  	  double rhoStat  = signi*signj*cleoInputs.getStatCorrelation(i,j);
  	  double rhoSyst  = signi*signj*cleoInputs.getSystCorrelation(i,j);
  	  double errSysti = cleoInputs.getSyst(i);
  	  double errStati = cleoInputs.getStat(i);
  	  double errSystj = cleoInputs.getSyst(j);
  	  double errStatj = cleoInputs.getStat(j);
  	  double covStat = rhoStat*errStati*errStatj;
  	  double covSyst = rhoSyst*errSysti*errSystj;
  	  double cov = covStat + covSyst;
      
      if (opt == "Stat") cov = covStat;
      if (opt == "Syst") cov = covSyst;

      _covarience[i][j] = cov;
    }  	
  }

  _invcovarience = _covarience;
  _invcovarience.Invert();  

}
  

bool PoloConK0PiPiCiSiCleo::coherenceFactorsLessThanOne(){
  
  int nbins = _dependencies.size() / 4; 

  for (int i = 0; i < nbins; i++){
    double ci = _dependencies.at(i      )->mean();
    double si = _dependencies.at(i+nbins)->mean();
    if ( (ci*ci + si*si) > 1.0 ) return false;
  }

  for (int i = 0; i < nbins; i++){
    double ci = _dependencies.at(i+nbins*2)->mean();
    double si = _dependencies.at(i+nbins*3)->mean();
    if ( (ci*ci + si*si) > 1.0 ) return false;
  }

  return true;

}

void PoloConK0PiPiCiSiCleo::genToyFPs (TRandom* random){

  PoloConstraint::genToyFPs(random);

  while ( coherenceFactorsLessThanOne() == false ){
    PoloConstraint::genToyFPs(random);
  }

}
  

PoloConstraint* PoloConK0PiPiCiSiCleo::clone(){

  return new PoloConK0PiPiCiSiCleo(*this);

}

PoloConK0PiPiCiSiCleo::~PoloConK0PiPiCiSiCleo(){



}






