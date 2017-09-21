/**
 * <B>D4piCleoAnalysis</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Feb 2016
 *
 *  This class just contains a load of hadronic parameter measurements for 
 *  KSpipi and KLpipi
 *
 *  
 **/

 
#ifndef POLO_INPUTS_K0PIPI
#define POLO_INPUTS_K0PIPI

#include "TRandom.h"
#include "TMatrixDSym.h"
#include "TVectorD.h"

class PoloInputsK0PiPi {
  
  /* The ci si central values, stat/sys uncertainties, and correlations
  for the four K0pipi binning schemes.  */

  TMatrixDSym stat_cor_optimal;
  TMatrixDSym syst_cor_optimal;

  TMatrixDSym stat_cor_modoptimal;
  TMatrixDSym syst_cor_modoptimal;

  TMatrixDSym stat_cor_babar;
  TMatrixDSym syst_cor_babar;

  TMatrixDSym stat_cor_belle;
  TMatrixDSym syst_cor_belle;  

  TVectorD mean_optimal;
  TVectorD stat_optimal;
  TVectorD syst_optimal;

  TVectorD mean_modoptimal;
  TVectorD stat_modoptimal;
  TVectorD syst_modoptimal;

  TVectorD mean_babar;
  TVectorD stat_babar;
  TVectorD syst_babar;

  TVectorD mean_belle;
  TVectorD stat_belle;
  TVectorD syst_belle;
  
  /* The ki and kibar central values and uncertainties for KSPiPi.
  There are three sources. The first is model independent from CLEO.
  The second is from a combination of KSPiPi amplitude models, with 
  a DMixing correction applied.  */  

  TVectorD ki_cleo_mean;
  TVectorD ki_cleo_stat;
  TVectorD kibar_cleo_mean;
  TVectorD kibar_cleo_stat;

  TVectorD ki_model_mean;
  TVectorD ki_model_stat;
  TVectorD kibar_model_mean;
  TVectorD kibar_model_stat;

  /* The ki and kibar central values and uncertainties for KLPiPi.*/  

  TVectorD kiprime_cleo_mean;
  TVectorD kiprime_cleo_stat;
  TVectorD kibarprime_cleo_mean;
  TVectorD kibarprime_cleo_stat;

  /* There are many choices of what constraints to use. The chosen constrains
  are referenced to by the below */  

  TMatrixDSym& stat_cor;
  TMatrixDSym& syst_cor;  
  TVectorD&    mean;
  TVectorD&    stat;
  TVectorD&    syst;

  TVectorD&    ki_mean        ;
  TVectorD&    kibar_mean     ;
  TVectorD&    ki_stat        ;
  TVectorD&    kibar_stat     ;

  TVectorD&    kiprime_mean   ;
  TVectorD&    kibarprime_mean;
  TVectorD&    kiprime_stat   ;
  TVectorD&    kibarprime_stat;

  public:

  PoloInputsK0PiPi();
    
  double getci(int i);
  double getsi(int i);
  double getciprime(int i);
  double getsiprime(int i);

  double getciStat(int i);
  double getsiStat(int i);
  double getciprimeStat(int i);
  double getsiprimeStat(int i);

  double getciSyst(int i);
  double getsiSyst(int i);
  double getciprimeSyst(int i);
  double getsiprimeSyst(int i);

  double getciError(int i);
  double getsiError(int i);
  double getciprimeError(int i);
  double getsiprimeError(int i);


  int getciID(int i);
  int getsiID(int i);
  int getciprimeID(int i);
  int getsiprimeID(int i);
  
  double getStatCorrelation(int i, int j);
  double getSystCorrelation(int i, int j);
  double getMean(int i);
  double getStat(int i);
  double getSyst(int i);
  double getError(int i);
  
  double getFi(int i);
  double getFibar(int i);
  double getFiprime(int i);
  double getFibarprime(int i);

  double getFiError(int i);
  double getFibarError(int i);
  double getFiprimeError(int i);
  double getFibarprimeError(int i);

  virtual ~PoloInputsK0PiPi();

};


#endif
