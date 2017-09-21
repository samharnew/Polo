
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "PoloFPSetBtoDh.h"
#include "PoloFPSetDtoFBinned.h"
#include "PoloFPSetDMixing.h"
#include "PoloFPSetNorm.h"

#include "PoloObsSTYield.h"
#include "PoloObsDTYield.h"
#include "PoloObsBtoDhYield.h"

#include "PoloObsBuilder.h"

#include "PoloLLHGaus.h"
#include "PoloLLHPoisson.h"
#include "PoloPulls.h"
#include "PoloFPPulls.h"
#include "PoloFitter.h"
#include "PoloMeasSet.h"

#include "PoloConDzDecBF.h"
#include "PoloConQuaziFlav.h"
#include "PoloConCPEvenFrac.h"
#include "PoloConDMixing.h"

#include "PoloConK0PiPiCiSiCleo.h"
#include "PoloConK0PiPiKiKbiCleo.h"


namespace PDG{
  
  //KS BFs

  const double BF_KS_PiPi         = 0.6920;
  const double BF_KS_PiPi_Err     = 0.0005;

  //Pi0 BFs

  const double BF_Pi0_GG         = 0.98823;
  const double BF_Pi0_GG_Err     = 0.00034;

  //Omega BFs

  double BF_Omega_PiPiPi0      = 0.892; 
  double BF_Omega_PiPiPi0_Err  = 0.007; 

  //Eta BFs

  double BF_Eta_PiPiPi0      = 0.2292; 
  double BF_Eta_PiPiPi0_Err  = 0.0028;

  double BF_Eta_GG       = 0.3941; 
  double BF_Eta_GG_Err   = 0.002;
  
  //EtaP BFs

  double BF_EtaP_EtaPiPi     = 0.429; 
  double BF_EtaP_EtaPiPi_Err = 0.007;


  //D BFs

  const double BF_D_PiPiPiPi         = 0.00745;  
  const double BF_D_PiPiPiPi_Err     = 0.00022;

  const double BF_D_PiPiPi0         = 0.0147;  
  const double BF_D_PiPiPi0_Err     = 0.0009;

  const double BF_D_KPi         = 0.0393;
  const double BF_D_KPi_Err     = 0.0004;

  const double BF_D_KPiPi0         = 0.143;
  const double BF_D_KPiPi0_Err     = 0.008;

  const double BF_D_KPiPiPi         = 0.0806;
  const double BF_D_KPiPiPi_Err     = 0.0023;  

  const double BF_D_KLPi0       = 0.0100; //1
  const double BF_D_KLPi0_Err   = 0.0007;

  const double BF_D_KSPiPi      = 0.0285;    
  const double BF_D_KSPiPi_Err  = 0.0020;    

  const double BF_D_KLPiPi      = BF_D_KSPiPi    ;    // TAKEN FROM KS MODE!!!
  const double BF_D_KLPiPi_Err  = BF_D_KSPiPi_Err;    // TAKEN FROM KS MODE!!!

  const double BF_D_KK         =  0.00401; //2
  const double BF_D_KK_Err     =  0.00007;   
  
  const double BF_D_PiPi       =  0.00142; //3
  const double BF_D_PiPi_Err   =  0.00003;   
  
  const double BF_D_KSPi0Pi0      =  0.0091 ; //4 
  const double BF_D_KSPi0Pi0_Err  =  0.0011;   
  
  const double BF_D_KSPi0            =  0.012  ;  //5
  const double BF_D_KSPi0_Err        =  0.0004;
   
  const double BF_D_KSOmega          =  0.0111 ;  
  const double BF_D_KSOmega_Err      =  0.0006;           
   
  const double BF_D_KSEta            =  0.00485;  
  const double BF_D_KSEta_Err        =  0.0003;
   
  const double BF_D_KSEtaP           =  0.0095;  
  const double BF_D_KSEtaP_Err       =  0.0005;
  
  //Product BFs

  const double BF_D_KLOmega3Pi     = 0.0099;  //6
  const double BF_D_KLOmega3Pi_Err = 0.0005;  

  const double BF_D_KLEta3Pi     = 0.00102; //7
  const double BF_D_KLEta3Pi_Err = 0.00009;  

  const double BF_D_KSEta3Pi     =  BF_D_KSEta * BF_Eta_PiPiPi0;  //8
  const double BF_D_KSEta3Pi_Err =  BF_D_KSEta_Err * BF_Eta_PiPiPi0; //INCOMPLETE

  const double BF_D_KSEtaGG     =  BF_D_KSEta     * BF_Eta_GG;  //9
  const double BF_D_KSEtaGG_Err =  BF_D_KSEta_Err * BF_Eta_GG; //INCOMPLETE

  const double BF_D_KSEtaP3H     =  BF_D_KSEtaP     * BF_EtaP_EtaPiPi * BF_Eta_GG;  //10
  const double BF_D_KSEtaP3H_Err =  BF_D_KSEtaP_Err * BF_EtaP_EtaPiPi * BF_Eta_GG; //INCOMPLETE

  const double BF_D_KSOmega3Pi          =  BF_D_KSOmega     * BF_Omega_PiPiPi0;  
  const double BF_D_KSOmega3Pi_Err      =  BF_D_KSOmega_Err * BF_Omega_PiPiPi0;         
   
  const double BF_D_KSPiPi_PiPi      = BF_D_KSPiPi    *BF_KS_PiPi;    
  const double BF_D_KSPiPi_PiPi_Err  = BF_D_KSPiPi_Err*BF_KS_PiPi;    

  const double BF_D_Kenu      = 0.03538;    
  const double BF_D_Kenu_Err  = 0.00033;   

}

void cisiFitExample(){

  MINT::MinuitParameterSet parSet;

  int nFourPiBinPairs = 5;
  int nK0PiPiBinPairs = 8;
  int psInt           = 0;

  const bool selfconj = true;
  
  const int cartesian = 0; //ci si ki kbi
  const int polar     = 1; //del_D, RD, rD, ki


  /*************************************************************
     
     First step is to define all the D decay final states.
     Here I'm just using final states from the D->4pi ci si analysis 

  *************************************************************/

  //Make the final state we are interested in PiPiPiPi. This 
  //is a self conjugate final state so bins will be made in pairs
  // i.e. +i and -i with c_i = c_-i s
  PoloFPSetDtoFBinned fpsPiPiPiPi("PiPiPiPi", nFourPiBinPairs, selfconj, &parSet, cartesian);
  
  //Make the CP+ eigenstates - using self-conjugate = true forces the
  //relations k=kbar and si = 0.
  PoloFPSetDtoFBinned fpsKK      ("KK"       , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsPiPi    ("PiPi"     , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKSPi0Pi0("KSPi0Pi0" , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKLPi0   ("KLPi0"    , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKLOmega ("KLOmega"  , psInt, selfconj, &parSet, cartesian);
  
  //Specify that these are CP even - this fixes ci = +1 
  fpsKK      .cpPlusES ();
  fpsPiPi    .cpPlusES ();
  fpsKSPi0Pi0.cpPlusES ();
  fpsKLPi0   .cpPlusES ();
  fpsKLOmega .cpPlusES ();

  //Make the CP- eigenstates 
  PoloFPSetDtoFBinned fpsKSPi0    ("KSPi0"    , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKSOmega  ("KSOmega"  , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKSEtaGG  ("KSEtaGG"  , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKSEtaHad ("KSEtaHad" , psInt, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKSEtaP   ("KSEtaP"   , psInt, selfconj, &parSet, cartesian);

  //Specify that these are CP odd - this fixes ci = -1 
  fpsKSPi0   .cpMinusES ();
  fpsKSOmega .cpMinusES ();
  fpsKSEtaGG .cpMinusES ();
  fpsKSEtaHad.cpMinusES ();
  fpsKSEtaP  .cpMinusES ();

  //Make the flavour eigenstates - the hadronic paramters are 'shared' between
  //the final state and its charge conjugate final state i.e. k<->kb si -> -si

  PoloFPSetDtoFBinned fpsKmenu    ("Kmenu"    , psInt, !selfconj, &parSet, cartesian);
  fpsKmenu.dzES();
  PoloFPSetDtoFBinned fpsKpenu    = fpsKmenu.getCCFinalState("Kpenu");
  
  //Make the quazi-flavour eigenstates. Note that, since these use the 
  //polar parameterisation i.e. K, rD, deltaD, RD. it only makes sense
  //to create these with the K-Pi+ final state, since rD is usally defined
  //to be << 1
  PoloFPSetDtoFBinned fpsKmPi     ("KmPi"     , psInt, !selfconj, &parSet, polar);
  PoloFPSetDtoFBinned fpsKmPiPi0  ("KmPiPi0"  , psInt, !selfconj, &parSet, polar);
  PoloFPSetDtoFBinned fpsKmPiPiPi ("KmPiPiPi" , psInt, !selfconj, &parSet, polar);

  PoloFPSetDtoFBinned fpsKpPi     = fpsKmPi    .getCCFinalState("KpPi"    );
  PoloFPSetDtoFBinned fpsKpPiPi0  = fpsKmPiPi0 .getCCFinalState("KpPiPi0" );
  PoloFPSetDtoFBinned fpsKpPiPiPi = fpsKmPiPiPi.getCCFinalState("KpPiPiPi");

  //Make the self-conjugate states 

  PoloFPSetDtoFBinned fpsPiPiPi0("PiPiPi0"  , psInt          , selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKSPiPi ("KSPiPi"   , nK0PiPiBinPairs, selfconj, &parSet, cartesian);
  PoloFPSetDtoFBinned fpsKLPiPi ("KLPiPi"   , nK0PiPiBinPairs, selfconj, &parSet, cartesian);
  
  /*************************************************************
     
     Now we have made the fit parameters, we set some realistic 
     branching fractions. There are still some parameters that
     need to be set (cisi for KSpipi for instance). These will
     later be set using parameter constraints.

  *************************************************************/
    
  fpsKK      .getFPSetFromBinNum(0).setK(PDG::BF_D_KK                  );
  fpsPiPi    .getFPSetFromBinNum(0).setK(PDG::BF_D_PiPi                );
  fpsKSPi0Pi0.getFPSetFromBinNum(0).setK(PDG::BF_D_KSPi0Pi0*PDG::BF_KS_PiPi );
  fpsKLPi0   .getFPSetFromBinNum(0).setK(PDG::BF_D_KLPi0               );
  fpsKLOmega .getFPSetFromBinNum(0).setK(PDG::BF_D_KLOmega3Pi          ); 

  fpsKSPi0   .getFPSetFromBinNum(0).setK(PDG::BF_D_KSPi0*PDG::BF_KS_PiPi      );
  fpsKSOmega .getFPSetFromBinNum(0).setK(PDG::BF_D_KSOmega3Pi*PDG::BF_KS_PiPi );
  fpsKSEtaGG .getFPSetFromBinNum(0).setK(PDG::BF_D_KSEtaGG*PDG::BF_KS_PiPi    );
  fpsKSEtaHad.getFPSetFromBinNum(0).setK(PDG::BF_D_KSEta3Pi*PDG::BF_KS_PiPi   );
  fpsKSEtaP  .getFPSetFromBinNum(0).setK(PDG::BF_D_KSEtaP3H*PDG::BF_KS_PiPi   ); 
  
  fpsPiPiPi0 .getFPSetFromBinNum(0).setK(PDG::BF_D_PiPiPi0    );

  fpsKmenu   .getFPSetFromBinNum(0).setK(PDG::BF_D_Kenu      );

  fpsKmPi    .getFPSetFromBinNum(0).setK(PDG::BF_D_KPi     );
  fpsKmPiPi0 .getFPSetFromBinNum(0).setK(PDG::BF_D_KPiPi0  );
  fpsKmPiPiPi.getFPSetFromBinNum(0).setK(PDG::BF_D_KPiPiPi );

  /*************************************************************
     
     Next step is to define the d-mixing parameters and a
     normalisation parameter

  *************************************************************/

  PoloFPSetNorm    fpsNDDb( &parSet, "nDDbar" );
  fpsNDDb.setVal(10000.0);

  PoloFPSetDMixing fpsDMix( &parSet );
  //fpsDMix.noMixing();
  
  /*************************************************************
     
     Next we make sets of single-tagged and double-tagged
     observables using the parameters defined above

  *************************************************************/

  //Make single tagged observables for some of the final states (can't do
  // single tags for final states with a KL or neutrino   )

  PoloObsSet ST_KK          = PoloObsBuilder::buildSTObsSet( fpsKK       , fpsDMix , fpsNDDb );
  PoloObsSet ST_PiPi        = PoloObsBuilder::buildSTObsSet( fpsPiPi     , fpsDMix , fpsNDDb );
  PoloObsSet ST_KSPi0Pi0    = PoloObsBuilder::buildSTObsSet( fpsKSPi0Pi0 , fpsDMix , fpsNDDb );
 
  PoloObsSet ST_KSPi0       = PoloObsBuilder::buildSTObsSet( fpsKSPi0    , fpsDMix , fpsNDDb );
  PoloObsSet ST_KSOmega     = PoloObsBuilder::buildSTObsSet( fpsKSOmega  , fpsDMix , fpsNDDb );
  PoloObsSet ST_KSEtaGG     = PoloObsBuilder::buildSTObsSet( fpsKSEtaGG  , fpsDMix , fpsNDDb );
  PoloObsSet ST_KSEtaHad    = PoloObsBuilder::buildSTObsSet( fpsKSEtaHad , fpsDMix , fpsNDDb );
  PoloObsSet ST_KSEtaP      = PoloObsBuilder::buildSTObsSet( fpsKSEtaP   , fpsDMix , fpsNDDb );

  PoloObsSet ST_KmPi        = PoloObsBuilder::buildSTObsSet( fpsKmPi     , fpsDMix , fpsNDDb );
  PoloObsSet ST_KpPi        = PoloObsBuilder::buildSTObsSet( fpsKpPi     , fpsDMix , fpsNDDb );

  PoloObsSet ST_PiPiPi0     = PoloObsBuilder::buildSTObsSet( fpsPiPiPi0  , fpsDMix , fpsNDDb );


  //Make double tagged observables all some of the final states (vs 4pi).
  //Note that this will make every combination of phase space bins between the 
  //two final states, and return them all in a PoloObsSet

  PoloObsSet DT_KK          = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKK       , fpsDMix , fpsNDDb );
  PoloObsSet DT_PiPi        = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsPiPi     , fpsDMix , fpsNDDb );
  PoloObsSet DT_KSPi0Pi0    = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSPi0Pi0 , fpsDMix , fpsNDDb );
  PoloObsSet DT_KLPi0       = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKLPi0    , fpsDMix , fpsNDDb );
  PoloObsSet DT_KLOmega     = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKLOmega  , fpsDMix , fpsNDDb );

  PoloObsSet DT_KSPi0       = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSPi0    , fpsDMix , fpsNDDb );
  PoloObsSet DT_KSOmega     = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSOmega  , fpsDMix , fpsNDDb );
  PoloObsSet DT_KSEtaGG     = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSEtaGG  , fpsDMix , fpsNDDb );
  PoloObsSet DT_KSEtaHad    = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSEtaHad , fpsDMix , fpsNDDb );
  PoloObsSet DT_KSEtaP      = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSEtaP   , fpsDMix , fpsNDDb );



  PoloObsSet DT_Kmenu       = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKmPi     , fpsDMix , fpsNDDb );
  PoloObsSet DT_Kpenu       = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKpPi     , fpsDMix , fpsNDDb );

  PoloObsSet DT_KmPi        = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKmPi     , fpsDMix , fpsNDDb );
  PoloObsSet DT_KpPi        = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKpPi     , fpsDMix , fpsNDDb );
  PoloObsSet DT_KmPiPi0     = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKmPiPi0  , fpsDMix , fpsNDDb );
  PoloObsSet DT_KpPiPi0     = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKpPiPi0  , fpsDMix , fpsNDDb );
  PoloObsSet DT_KmPiPiPi    = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKmPiPiPi , fpsDMix , fpsNDDb );
  PoloObsSet DT_KpPiPiPi    = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKpPiPiPi , fpsDMix , fpsNDDb );

  PoloObsSet DT_PiPiPi0     = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsPiPiPi0  , fpsDMix , fpsNDDb );
  PoloObsSet DT_KSPiPi      = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKSPiPi   , fpsDMix , fpsNDDb );
  PoloObsSet DT_KLPiPi      = PoloObsBuilder::buildDTObsSet( fpsPiPiPiPi, fpsKLPiPi   , fpsDMix , fpsNDDb );

  /*************************************************************
     
     It is now possible to add background and efficiencies.

     Within each PoloObsSet, each individual observable can 
     be assessed by its PoloObsID e.g. suppose we want 4pi bin 3
     and KLpipi bin -5 from the DT_KLPiPi PoloObsSet. We would 
     access this using PoloID(3, -5). Lots of examples below

  *************************************************************/
  

  //I am just show a few examples here to give an idea of how it works...

  //This will multiply all KSPi0 vs. 4pi observables 
  //by an efficiency of 80%

  DT_KSPi0.addEfficiencies( PoloMeas(0.80) ); 

  //This will add an expected background yield of 2 to all 
  // KSPi0 vs. 4pi observables 

  DT_KSPi0.addBackground  ( PoloMeas(2.0) ); 

  //Print the list of observables in this PoloObsSet.
  //This also gives a breakdown of efficiencies + backgrounds
  //added, so is useful to check

  DT_KSPi0.print();

  //Make a PoloMeasSet to describe the bin-by-bin backgrounds.
  //   NOTE: The PoloMeasSet can be very easily saved and loaded
  //   to/from a text file. So for your analysis you can determine
  //   and save these elsewhere, then quickly load them using:
  //
  //   PoloMeasSet DT_KSOmega_eff( filename );
  //

  PoloMeasSet DT_KSOmega_eff;
  for (int i = 1; i <= nFourPiBinPairs; i++ ){
    double eff = 0.2 + double(i)*0.02;
    DT_KSOmega_eff.setMeas( PoloObsID(+i), PoloMeas(eff) );
    DT_KSOmega_eff.setMeas( PoloObsID(-i), PoloMeas(eff) );
  }
  
  //Include the bin-by-bin efficiencies in the observable
  DT_KSOmega.addBackground  ( DT_KSOmega_eff ); 
  DT_KSOmega.print();
  
  //Include background in a single phase space bin. Also
  //demonstrates how to deal with cases where both final 
  //states are binned.
  DT_KSPiPi.addBackground( PoloObsID(+4, +6), PoloMeas(0.4) );
  DT_KSPiPi.print();

  /*************************************************************
     
     We also want to add some constraints to the fitter.

  *************************************************************/
  
  //Branching fraction constraints for the CP tags that do
  //not have ST decays
  PoloConDzDecBF con_KLPi0_BF  ( fpsKLPi0  , PoloMeas( PDG::BF_D_KLPi0     , PDG::BF_D_KLPi0_Err      ) );
  PoloConDzDecBF con_KLOmega_BF( fpsKLOmega, PoloMeas( PDG::BF_D_KLOmega3Pi, PDG::BF_D_KLOmega3Pi_Err ) );
  
  //Constrain the hadronic parameters of the quazi flavour final states
  PoloConQuaziFlav con_quaziFlav( fpsKmPi, fpsKmPiPi0, fpsKmPiPiPi );
  
  //Constrain the cp even fraction of the pipipi0 decay
  PoloConCPEvenFrac con_PiPiPi0_CPEven( fpsPiPiPi0, PoloMeas( 0.90, 0.03 )  );
  
  //Constrain the d mixing parameters
  PoloConDMixing con_DMixing( fpsDMix, PoloMeas( 0.00322, 0.00140 ), PoloMeas( 0.00688, 0.00060 ), -0.058 );

  //Constrain the hadronic parameters of the KSpipi and KLpipi final states
  PoloConK0PiPiCiSiCleo  con_K0PiPi_cisi ( fpsKSPiPi, fpsKLPiPi );
  PoloConK0PiPiKiKbiCleo con_K0PiPi_kikbi( fpsKSPiPi, fpsKLPiPi, PDG::BF_D_KSPiPi*PDG::BF_KS_PiPi, PDG::BF_D_KLPiPi );


  //We want to set sensible values for the 4pi hadronic parameters, so we use
  // their previously measured values from (https://arxiv.org/abs/1709.03467). 
  //The supplementary material gives
  //the reslts in root format, that can be loaded with the PoloFPSnapshot class. 
  //The results were saved using a different final state name ("pi+pi-pi+pi-" 
  // rather than "PiPiPiPi", so we change this to make them consistent)
  PoloFPSnapshot fourpiHadPars("../data/hadPars4pi/OptAlt5_statsyst.root");
  fourpiHadPars.print();
  fourpiHadPars.replaceAll("pi+pi-pi+pi-", "PiPiPiPi");
  
  // We now make a constraint using the results in fourpiHadPars. (this matches
  // the fitparameter names in the given MinuitParameterSet, with the names in 
  // the snapshot )
  PoloConstraint* fourpiCon = fourpiHadPars.getConstraint(&parSet);
  fourpiCon->print();
  fourpiCon->setFPsToMean();

  //Note that we are not actually going to use this constraint in the fit! 
  //We have made it purely to set some sensible stating values (that will)
  //be used to generate the toy MC

  /*************************************************************
     
     Finally we use the obserables to create LLH terms and 
     add them to the fitter.

  *************************************************************/
  
  //Create a fitter that can only vary the fit parameters
  //in the given MinuitParameterSet
  PoloFitter fitter(&parSet);
  
  //Add an observable and its measurement to the fitter. 
  //As an example will look at the 4pi vs. KK obserables
  //and the 4pi vs. PiPi obserables
  
  //first need to make a PoloMeasSet with the measured yields
  PoloMeasSet DT_KK_meas;
  PoloMeasSet DT_PiPi_meas;

  for (int i = -nFourPiBinPairs; i <= nFourPiBinPairs; i++){
    if (i == 0) continue;

    /*****  4pi vs. KK *****/

    //get the expected yield
    double expectedYield = DT_KK.getObs( PoloObsID(+i) )->getVal();
    //sample from a Poisson distribution
    double yield = gRandom->Poisson(expectedYield);
    //set the measurement
    DT_KK_meas.setMeas( PoloObsID(+i), PoloMeas(yield) );

    /*****  4pi vs. PiPi *****/

    //get the expected yield
    expectedYield = DT_PiPi.getObs( PoloObsID(+i) )->getVal();

    //For PiPi we are instead going to use Gaussian stats.
    yield = gRandom->Gaus( expectedYield, sqrt(expectedYield) );
    
    //Note that this time we also give an uncertainty!
    DT_PiPi_meas.setMeas( PoloObsID(+i), PoloMeas(yield, sqrt(expectedYield) ) );


  }

  //Add the obervable and its measurement to the fitter
  fitter.addObs( DT_KK   , DT_KK_meas    );
  fitter.addObs( DT_PiPi , DT_PiPi_meas  );
  
  /**** IMPORTANT ****/
  /**
    Since for 4pi vs. KK only yields (and no errors) were given, a Poisson type
    LLH term is added to the fitter. For 4pi vs. PiPi, errors were given, so 
    a Guassian type LLH term is added to the fitter.

    It is ALSO possible to add correlations to a   PoloMeasSet by doing something like:

    DT_KK.setCor( PoloObsID(+2), PoloObsID(-4), 0.34 )

    When creating a LLH term using this measurement, a Mulitvariate Gaussian type
    constraint will be used.

    NOTE: For DT where both final states are binned you can do things like
    
      setMeas( PoloObsID(+2, -5), PoloMeas(yield, sqrt(yield)) );

  **/
  
  //Since we are not actually inputting experimental measurements for this 
  //example (we are just generating toys). There is no need to actually give
  //measurements. When generating toys, it will internally do what was
  //done for 4pi vs. KK above.

  fitter.addObs( DT_KSPi0Pi0  );
  fitter.addObs( DT_KLPi0     );
  fitter.addObs( DT_KLOmega   );
  fitter.addObs( DT_KSPi0     );
  fitter.addObs( DT_KSOmega   );
  fitter.addObs( DT_KSEtaGG   );
  fitter.addObs( DT_KSEtaHad  );
  fitter.addObs( DT_KSEtaP    );
  fitter.addObs( DT_Kmenu     );
  fitter.addObs( DT_Kpenu     );
  fitter.addObs( DT_KmPi      );
  fitter.addObs( DT_KpPi      );
  fitter.addObs( DT_KmPiPi0   );
  fitter.addObs( DT_KpPiPi0   );
  fitter.addObs( DT_KmPiPiPi  );
  fitter.addObs( DT_KpPiPiPi  );
  fitter.addObs( DT_PiPiPi0   );
  fitter.addObs( DT_KSPiPi    );
  fitter.addObs( DT_KLPiPi    );

  fitter.addObs( ST_KK        );
  fitter.addObs( ST_PiPi      );
  fitter.addObs( ST_KSPi0Pi0  );
  fitter.addObs( ST_KSPi0     );
  fitter.addObs( ST_KSOmega   );
  fitter.addObs( ST_KSEtaGG   );
  fitter.addObs( ST_KSEtaHad  );
  fitter.addObs( ST_KSEtaP    );
  fitter.addObs( ST_KmPi      );
  fitter.addObs( ST_KpPi      );
  fitter.addObs( ST_PiPiPi0   );

  //Also want to add the constraints...

  fitter.addConstraint( con_KLPi0_BF       );
  fitter.addConstraint( con_KLOmega_BF     );
  fitter.addConstraint( con_quaziFlav      );
  fitter.addConstraint( con_PiPiPi0_CPEven );
  fitter.addConstraint( con_DMixing        );
  fitter.addConstraint( con_K0PiPi_cisi    );
  fitter.addConstraint( con_K0PiPi_kikbi   );
  
  //Create a fit parameter shapshot that contains the
  //values of the fit parameters that will be used to 
  //generate the toy datasets. 
  PoloFPSnapshot genSnapshot(&parSet);

  //Create another fit parameter shapshot that will 
  //later be used to hold the fitted values of the fit paramters
  PoloFPSnapshot fitSnapshot(&parSet);

  //This class makes pull distributions easy. Give it pointers to the generated
  //and fitted snapshot. Whenever addPull() gets called, the current values in 
  //these snapshots are used to add another entry to the pull distribution
  PoloFPPulls pulls(&genSnapshot, &fitSnapshot);
  
  //Look at all the LLH terms and constraints added to the fitter, and see if
  //there are any fit parameters that do not effect their values. If there are,
  //fix them. This makes it easy to remove a particualr final state, for example,
  //and not have stray fit parameters that cause bad convergence.
  fitter.fixNonDependencies();
  

  for (int i = 0; i < 200; i++){

    //generate a toy dataset and save the parameters used to generate
    //it in genSnapshot. Note that any constrained parameters  (i.e. the 4pi 
    //hadronic parameters) will be randomly sampled from their associated 
    //constraint before the toy is generated. Any parameters that are NOT
    //constrained will be taken from genSnapshot

    fitter.generateToy(gRandom, &genSnapshot);
    
    //maximise the LLH and save the resulting central values,
    //uncertainties and correlations in fitSnapshot
    fitter.fit(&fitSnapshot);

    //print some info about the current state of the fitter. 
    fitter.print();

    //add an instance to the pull thingy
    pulls.addPull();
  }
  
  //print the pull means and widths
  pulls.printPulls();

}

void gammaFitExample(){
  
  //See below to understand the different fit methods.
  int fitMethod = 0;

  //Make a minuit parameter set that will contain all the fit
  //parameters used in this example.
  MINT::MinuitParameterSet parSet;
  
  //Create the fit parameters for the 4pi final state. We tell the constructor
  //the number of phase space bins, and that this is a self-conjugate final state -
  //this automatically gives the final state nbins*2 bin pairs, where bins +i and
  //-i will share the same fit parameters (with s_i = -s_-i, k_i = kb_-i etc.)
  int nFourPiBinPairs = 5;
  const bool selfconj = true;
  PoloFPSetDtoFBinned fpsPiPiPiPi("PiPiPiPi", nFourPiBinPairs, selfconj, &parSet);
  
  //Create a set of fit parameters that describes the B->DK decay. This can be done 
  //in either catesian or polar coordinates (x^± y± or rb delta gamma). Have also
  //set some realistic values for the toy studies.
  double gamma = 80.0;
  double delB  = 230.0;
  double rB    = 0.1;
  const bool degrees = true;
  const int  cartesian = 0;
  const int  polar     = 1;

  PoloFPSetBtoDh      fpsBtoDK   ("DtoDK"   , &parSet, cartesian);
  fpsBtoDK.setAll(rB, delB, gamma, degrees);
  
  //Make two normalisation fit parameters, one that will be used for B+->DK decays
  //and the other for B- -> DK decays.
  PoloFPSetNorm    fpsNDDbBp( &parSet, "nDDbarBp" );
  PoloFPSetNorm    fpsNDDbBm( &parSet, "nDDbarBm" );

  fpsNDDbBp.setVal(750.0);
  fpsNDDbBm.setVal(750.0);
  
  //We want to constrain the 4pi hadronic parameters to their previously measured
  //values (https://arxiv.org/abs/1709.03467). The supplementary material gives
  //the reslts in root format, that can be loaded with the PoloFPSnapshot class. 
  //The results were saved using a different final state name ("pi+pi-pi+pi-" 
  // rather than "PiPiPiPi", so we change this to make them consistent)
  PoloFPSnapshot fourpiHadPars("../data/hadPars4pi/OptAlt5_statsyst.root");
  fourpiHadPars.print();
  fourpiHadPars.replaceAll("pi+pi-pi+pi-", "PiPiPiPi");
  
  //We now make a constraint using the results in fourpiHadPars. (this matches
  // the fitparameter names in the given MinuitParameterSet, with the names in 
  // the snapshot )
  PoloConstraint* fourpiCon = fourpiHadPars.getConstraint(&parSet);
  fourpiCon->print();
  
  
  //Use the PoloObsBuilder class to quicly make B+->DK+, D->4pi and B-->DK-, D->4pi 
  //observables. These are saved in a PoloObsSet
  PoloObsSet BpToDKp = PoloObsBuilder::buildBptoDhpObsSet(fpsPiPiPiPi, fpsBtoDK, fpsNDDbBp );
  PoloObsSet BmToDKm = PoloObsBuilder::buildBmtoDhmObsSet(fpsPiPiPiPi, fpsBtoDK, fpsNDDbBm );

  //For each phase spave bin add an efficiency of 80%
  BmToDKm.addEfficiencies( PoloMeas(0.80) ); 

  //Might also want to add relative efficiencies one-by-one...
  BpToDKp.addEfficiencies( PoloObsID(+1), PoloMeas(0.80) ); 
  BpToDKp.addEfficiencies( PoloObsID(+3), PoloMeas(0.62) ); 
  BpToDKp.addEfficiencies( PoloObsID(-2), PoloMeas(0.65) ); 
  //... 
  
  //Or you can do them all together using a PoloMeasSet...
  PoloMeasSet BpToDKp_eff;
  for (int i = -nFourPiBinPairs; i <= nFourPiBinPairs; i++){
    if (i==0) continue;
    BpToDKp_eff.setMeas( PoloObsID(i), PoloMeas(0.80) );
  }
  BpToDKp.addEfficiencies( BpToDKp_eff );
  
  //NOTE: A PoloMeasSet can be easily saved and loaded to a text file,
  //so you could save them in another piece of code, and quicky load them
  //using:
  // PoloMeasSet BpToDKp_eff(filename);


  //For each phase spave bin add an expected background yield of 4.0
  //Can also do all the tricks shown above for the efficiency for bin-
  //by-bin backgrounds.
  BmToDKm.addBackground  ( PoloMeas(4.0 ) ); 
  BpToDKp.addBackground  ( PoloMeas(3.0 ) ); 
  
  //Make a fitter
  PoloFitter fitter(&parSet);
  
  //Add observables to the fitter. When fitting experimental 
  //data, one would also provide measured yields here. Since
  //we are generating and fitting toys, they are not needed
  //in this instance.
  fitter.addObs(BpToDKp);
  fitter.addObs(BmToDKm);

  // NOTE**** Below, I just show how it would 
  //     **** be done for an experimental measurement

  if (false){

    // If you're just counting B->DK yields...

    PoloMeasSet Meas_BpToDKp_case1;
    Meas_BpToDKp_case1.setMeas( PoloObsID(+1), PoloMeas(5) );
    Meas_BpToDKp_case1.setMeas( PoloObsID(+2), PoloMeas(4) );
    //...
    fitter.addObs(BmToDKm, Meas_BpToDKp_case1);
    


    //If you're fitting B->DK yields and they have an uncertainty...

    PoloMeasSet Meas_BpToDKp_case2;
    Meas_BpToDKp_case2.setMeas( PoloObsID(+1), PoloMeas(5.2, 2.3) );
    Meas_BpToDKp_case2.setMeas( PoloObsID(+2), PoloMeas(4.3, 1.2) );
    //...
    fitter.addObs(BmToDKm, Meas_BpToDKp_case2);



    //If you're fitted B->DK yields are correlated...

    PoloMeasSet Meas_BpToDKp_case3;
    Meas_BpToDKp_case3.setMeas( PoloObsID(+1), PoloMeas(5.2, 2.3) );
    Meas_BpToDKp_case3.setMeas( PoloObsID(+2), PoloMeas(4.3, 1.2) );
    Meas_BpToDKp_case3.setCor ( PoloObsID(+1), PoloObsID(+2), 0.4 ); //set correlation

    //...
    fitter.addObs(BmToDKm, Meas_BpToDKp_case3);
    

    //Remember, the PoloMeasSet can easily be saved elsewhere / loaded, so you 
    //would not have to clutter your fitting script with all of the above.  
  }
  
  //A PoloFPSnapshot holds a snapshot of all the fit parameters, uncertainties
  //and correlations. We want three of these. One to hold the generated parameters,
  //one to hold the fitted parameters and uncertainties, and another to hold
  //the systematic uncertainties

  PoloFPSnapshot genSnapshot(&parSet);
  PoloFPSnapshot fitSnapshot(&parSet);
  PoloFPSnapshot fitSnapshotSys(&parSet);
  
  //This class makes pull distributions easy. Give it pointers to the generated
  //and fitted snapshot. Whenever addPull() gets called, the current values in 
  //these snapshots are used to add another entry to the pull distribution
  PoloFPPulls pulls(&genSnapshot, &fitSnapshot);
  
  //Add a gaussian constraint for the 4pi hadronic parameters
  fitter.addConstraint( *fourpiCon   );
  
  //Look at all the LLH terms and constraints added to the fitter, and see if
  //there are any fit parameters that do not effect their values. If there are,
  //fix them
  fitter.fixNonDependencies();

  //Do 200 peusdo experiments
  for (int i = 0; i < 2000; i++){

    //generate a toy dataset and save the parameters used to generate
    //it in genSnapshot. Note that any constrained parameters  (i.e. the 4pi 
    //hadronic parameters) will be randomly sampled from their associated 
    //constraint before the toy is generated.
    
    fitter.generateToy(gRandom, &genSnapshot);
    
    //The first method is to float all parameters and apply all constraints
    //to the total LLH to be maximised. This method was found to give large 
    //biases in the pull distribtuions   
    if (fitMethod == 0){
      fitter.fit(&fitSnapshot);
    }

    int nFits = 100;

    //The second fit method is to float only unconstrained fit parameters. 
    //In this case, this means the hadronic parameters will be fixed,
    //and gamma, delta, rb, and the overall normalisation will be floated.
    //This fit is performed nFits times, where for each, the 'constrained'
    //parameters are randomly varied according the their associated constraint. 
    //This function returns TWO PoloFPSnapshot instances. The first contains the
    //results of a single fit where the constrained parameters are fixed to 
    //their central values. 
    //The second contains central values which are taken from the mean of the
    //individual nFits. The uncertainties + correlations are taken from the
    //covarience of the individual nFits. 
    if (fitMethod == 1){
      fitter.fitWFixedCon(nFits, &fitSnapshot, &fitSnapshotSys, gRandom);
      //For the pulls we want the total uncertainty, so have combined the 
      //two sets of uncertainties in quadrature. The cenral values are
      //taken from 'fitSnapshot'
      fitSnapshot.combineUncertainties(fitSnapshotSys);
    }
    
    //Add a new instance to the pull distributions
    pulls.addPull();
  }
  
  //draw and print the pull distributions.
  pulls.drawPulls("");
  pulls.printPulls();
  
  //print the status of the fitter. This should list the 
  //measured yields for each observable, and the expected yields
  //as determined from the current state of the fit parameters.
  fitter.print();

}




int main(int argc, char** argv) {
  
  bool cisiExample  = 0;
  bool gammaExample = 0;
  bool help         = 0;

  for(int i = 1; i<argc; i=i+2){
  
    //Options to do with offline selection
    if       (std::string(argv[i])=="--cisi-example"   ) { cisiExample  =  1; i--; }
    else if  (std::string(argv[i])=="--gamma-example"  ) { gammaExample =  1; i--; }
    else if  (std::string(argv[i])=="--help"           ) { help         =  1; i--; }    
    else { 
      std::cout << "User entered invalid argument:" << argv[i] << std::endl;
      return 0;  
    }
  }

  if (cisiExample  ) cisiFitExample ();
  if (gammaExample ) gammaFitExample();
  
  if (help || (cisiExample == 0 && gammaExample == 0) ){
    std::cout << "--cisi-example    Run example fit to determine 4pi hadronic parameters"   << std::endl;
    std::cout << "--gamma-example   Run example fit to determine gamma using B->DK, D->4pi" << std::endl;
  }

  return 0;

}
