#include "PoloConQuaziFlav.h"


PoloConQuaziFlav::PoloConQuaziFlav( PoloFPSetDtoFBinned& dToKmPi, PoloFPSetDtoFBinned& dToKmPiPi0, PoloFPSetDtoFBinned& dToKmPiPiPi ){
  init(dToKmPi.getFPSetFromBinNum(0), dToKmPiPi0.getFPSetFromBinNum(0), dToKmPiPiPi.getFPSetFromBinNum(0));
}



PoloConQuaziFlav::PoloConQuaziFlav( PoloFPSetDtoF      & dToKmPi, PoloFPSetDtoF      & dToKmPiPi0, PoloFPSetDtoF      & dToKmPiPiPi ){
  init(dToKmPi, dToKmPiPi0, dToKmPiPiPi);
}


void PoloConQuaziFlav::init(PoloFPSetDtoF      & dToKmPi, PoloFPSetDtoF      & dToKmPiPi0, PoloFPSetDtoF      & dToKmPiPiPi){

  _value        .ResizeTo(9);
  _mean         .ResizeTo(9);
  _covarience   .ResizeTo(9,9);
  _invcovarience.ResizeTo(9,9);
  
  TVectorD error(9);
  TMatrixD cor  (9,9);

  _dependencies.push_back( dToKmPi    .getFitParameterr()     );
  _dependencies.push_back( dToKmPi    .getFitParameterR()     );
  _dependencies.push_back( dToKmPi    .getFitParameterdelta() );
  _dependencies.push_back( dToKmPiPi0 .getFitParameterr()     );
  _dependencies.push_back( dToKmPiPi0 .getFitParameterR()     );
  _dependencies.push_back( dToKmPiPi0 .getFitParameterdelta() );
  _dependencies.push_back( dToKmPiPiPi.getFitParameterr()     );
  _dependencies.push_back( dToKmPiPiPi.getFitParameterR()     );
  _dependencies.push_back( dToKmPiPiPi.getFitParameterdelta() );

  _mean[0] = sqrt(0.003485); // = 0.05903 //http://www.slac.stanford.edu/xorg/hfag/charm/CKM16/results_mix_cpv.html
  _mean[1] = 1.0 ;  //http://www.slac.stanford.edu/xorg/hfag/charm/CKM16/results_mix_cpv.html
  _mean[2] = 3.407; //http://www.slac.stanford.edu/xorg/hfag/charm/CKM16/results_mix_cpv.html (add pi for convention)
  _mean[3] = 0.0447;
  _mean[4] = 0.81;
  _mean[5] = 198.0*(3.141/180.0); //=3.141
  _mean[6] = 0.0549;
  _mean[7] = 0.43;
  _mean[8] = 128.0*(3.141/180.0); //=2.967

  error[0] = 0.0000353/(2.0*_mean[0]); // = 0.000299
  error[1] = 0.000001; //This should really be zero
  error[2] = 0.139; 
  error[3] = 0.0012;
  error[4] = 0.06;
  error[5] = 14.5*(3.141/180.0); //=0.30
  error[6] = 0.0006;
  error[7] = 0.15;
  error[8] = 22.5*(3.141/180.0); //=0.66

  cor[0][0] = 1.00; cor[0][1] = 0.34; cor[0][2] = 0.00; cor[0][3] = 0.00; cor[0][4] = 0.00; cor[0][5] = 0.00; cor[0][6] = 0.00; cor[0][7] = 0.00; cor[0][8] = 0.00; 
  cor[1][0] = 0   ; cor[1][1] = 1.00; cor[1][2] = 0.00; cor[1][3] = 0.00; cor[1][4] = 0.00; cor[1][5] = 0.00; cor[1][6] = 0.00; cor[1][7] = 0.00; cor[1][8] = 0.00; 
  cor[2][0] = 0   ; cor[2][1] = 0   ; cor[2][2] = 1.00; cor[2][3] = 0.00; cor[2][4] = 0.00; cor[2][5] = 0.00; cor[2][6] = 0.00; cor[2][7] = 0.00; cor[2][8] = 0.00; 
  cor[3][0] = 0   ; cor[3][1] = 0   ; cor[3][2] = 0   ; cor[3][3] = 1.00; cor[3][4] =-0.04; cor[3][5] =-0.03; cor[3][6] =-0.03; cor[3][7] =-0.04; cor[3][8] = 0.08; 
  cor[4][0] = 0   ; cor[4][1] = 0   ; cor[4][2] = 0   ; cor[4][3] = 0   ; cor[4][4] = 1.00; cor[4][5] = 0.23; cor[4][6] =-0.04; cor[4][7] = 0.03; cor[4][8] = 0.02; 
  cor[5][0] = 0   ; cor[5][1] = 0   ; cor[5][2] = 0   ; cor[5][3] = 0   ; cor[5][4] = 0   ; cor[5][5] = 1.00; cor[5][6] =-0.02; cor[5][7] =-0.05; cor[5][8] = 0.15; 
  cor[6][0] = 0   ; cor[6][1] = 0   ; cor[6][2] = 0   ; cor[6][3] = 0   ; cor[6][4] = 0   ; cor[6][5] = 0   ; cor[6][6] = 1.00; cor[6][7] =-0.48; cor[6][8] = 0.12; 
  cor[7][0] = 0   ; cor[7][1] = 0   ; cor[7][2] = 0   ; cor[7][3] = 0   ; cor[7][4] = 0   ; cor[7][5] = 0   ; cor[7][6] = 0   ; cor[7][7] = 1.00; cor[7][8] =-0.67; 
  cor[8][0] = 0   ; cor[8][1] = 0   ; cor[8][2] = 0   ; cor[8][3] = 0   ; cor[8][4] = 0   ; cor[8][5] = 0   ; cor[8][6] = 0   ; cor[8][7] = 0   ; cor[8][8] = 1.00; 

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (i > j) {
        _covarience[i][j] = cor[j][i]*error[i]*error[j];
      }
      else{
        _covarience[i][j] = cor[i][j]*error[i]*error[j];
      }
    }
  }

  _invcovarience = _covarience;
  _invcovarience.Invert();  
   
}




PoloConstraint* PoloConQuaziFlav::clone(){

  return new PoloConQuaziFlav(*this);

}

PoloConQuaziFlav::~PoloConQuaziFlav(){



}



