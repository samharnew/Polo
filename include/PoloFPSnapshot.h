/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * Store a snapshot of a set of fit parameters and their uncertainties. 
 * This can be saved / loaded from a file.
 * 
 * 
 * 
 * 
 * 
 *
 *
 **/
 
#ifndef POLO_FP_SNAPSHOT_HH
#define POLO_FP_SNAPSHOT_HH

#include "Mint/FitParameter.h"
#include "Mint/MinuitParameterSet.h"
#include "Mint/counted_ptr.h"
#include "Mint/Minimiser.h"
#include "Mint/IMinuitParameter.h"
#include "TMatrixD.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TVectorD.h"
#include "TDecompChol.h"

#include "PoloConstraint.h"


class PoloFPSnapshot  {
  
  MINT::MinuitParameterSet* _parSet;
  std::vector< double  > _mean;
  std::vector< double  > _err;
  std::vector< double  > _errp;
  std::vector< double  > _errm;
  std::vector< TString > _name;
  TMatrixD _correlations;
  double   _neg2LLH;

  public:
  
  PoloFPSnapshot(MINT::MinuitParameterSet* parSet = 0);
  /**< add all parameters in the MinuitParameterSet to the snapshot.
  Also take the current central values and uncertainties */

  PoloFPSnapshot(std::vector<TString> names);
  /**< Make a snapshot with the given names. This snapshot will not have associated fit parameters
  so some functions will not work */

  PoloFPSnapshot(TString filename);
  /**< Load snapshot from a file. This snapshot will not have associated fit parameters
  so some functions will not work */

  void updateSnapshotFromFPs();
  /**< copy the current fit parameter values and uncertainties to the snapshot. */

  void updateFPsFromSnapshot();
  /**< Update the current values of the fit parameters from the snapshot */

  int size();
  /**< number of parameters in the snapshot */

  MINT::MinuitParameterSet* getParSet();
  /**< get the MinuitParameterSet associated with this snapshot */

  void updateCorrelations( MINT::Minimiser* mini );
  /**< update the correlation matrix from a minimiser */

  int findID(TString name);
  /**< find the ID of a parameter given its name. Returns -1 if cannot be found */
  
  void setNeg2LLH(double val);
  /**< set the neg2LLH associated to this set of parameters */

  void replaceAll(TString find, TString replace);
  /**< find any parameter names containing the 'find' string and replace that with the 
  'replace' string */

  double getNeg2LLH() const;
  /**< get the neg2LLH associated to this set of parameters */

  MINT::IMinuitParameter* getParPtr(int i);
  /**< get a pointer to one of the fit parameters */

  int getID(MINT::counted_ptr<MINT::FitParameter> fp);
  /**< get the ID of a fit parameter from a pointer to it */

  void copy(PoloFPSnapshot& snap);
  /**< copy everything from the given snapshot */

  void copyCommon(PoloFPSnapshot& snap);
  /**< copy any the values associated to any fit parameters that have a common name */

  void clearVals();
  /**< set all means, errors and correlations to zero */


  double mean(int i);
  /**< get the central value of the fit parameter with index i */
  double err (int i);
  /**< get the gaussian error of the fit parameter with index i */
  double errp (int i);
  /**< get the positive minos error of the fit parameter with index i */
  double errm (int i);
  /**< get the negative minos error of the fit parameter with index i */

  void setErr (int i, double val);
  /**< set the gaussian error of the fit parameter with index i */
  void setErrp(int i, double val);
  /**< set the positive minos error of the fit parameter with index i */
  void setErrm(int i, double val);    
  /**< set the negative minos error of the fit parameter with index i */
  void setMean(int i, double val);
  /**< set the central value of the fit parameter with index i */

  double covarience(int i, int j);
  /**< get the covarience the fit parameters with indices i and j */
  double correlation(int i, int j);
  /**< get the correlation coefficient the fit parameters with indices i and j */
  void setCorrelation(int i, int j, double val);
  /**< set the correlation coefficient the fit parameters with indices i and j */
  

  std::vector< double  > getMeanVect();
  /**< get a vector of the difference means */


  TMatrixD getCovarienceMatrix();
  /**< get the covarience matrix */
  TMatrixD getRedCovarienceMatrix( TVectorD& redMean,  std::vector<int>& parNums );
  /**< get a covarience matrix for all parameters with non-zero uncertainties. 
  A vecotr of the means is also provided, along with a vector that gives the parameter ID 
  of each row/column  */

  TString getName (int i);
  /**< get the name of the fit parameter with index i */


  PoloFPSnapshot getRandomisedSnapshot(TRandom* random = gRandom);
  /**< use the covarience matrix and central values to define a PDF. 
  Sample this PDF randomly and return the PoloFPSnapshot obtained */

  void updateFPsFromRandomisedSnapshot(TRandom* random = gRandom);
  /**< use the covarience matrix and central values to define a PDF. 
  Sample this PDF randomly and use the result to overwrite the current
  central values of the fit parameters. Note that the central values 
  stored in the snapshot are unaffected, only the fit parameters change */

  void randomise(TRandom* random = gRandom);
  /**< use the covarience matrix and central values to define a PDF. 
  Sample this PDF randomly and use the result to overwrite the current
  central values of this snapshot */

  double pull(PoloFPSnapshot& other, MINT::counted_ptr<MINT::FitParameter> fp);
  /**< get the pull between the this snapshot and the one given, for the given
  fit parameter */

  void compare(PoloFPSnapshot& other);
  /**< print a comparison between this snapshot and the one given */

  void print();
  /**< print this snapshot */

  void pulls(PoloFPSnapshot& other);
  /**< for all fit parameters common between the two snapshots, 
  print the pulls */

  void combineUncertainties(PoloFPSnapshot& other);
  /**< combine the uncertainties from this snapshot and the one provided 
  in quadrature. This includes correlations etc. */


  ~PoloFPSnapshot();
  /**< destructor */

  void load(TString filename);
  /**< load the snapshot in the given file and copy over anything that is associtated to
  fit paramters shared with this snapshot */

  void save(TString filename);
  /**< save this snapshot to a file */

  void normaliseParameters(std::vector<TString> paramnames);
  /**< this normalises the given parameters (so they sum to 1) and
  adjusts the uncertainties and correlations accordingly */
  
  PoloConstraint* getConstraint();
  /**< makes a PoloConstraint using the central values and covarience matrix from 
  this snapshot. This can then be used in a fit. 
  NOTE - NO NOT DELETE THE RETURNED CONSTRAINT */

  PoloConstraint* getConstraint(PoloFPSnapshot& other);
  /**< find any parameters that have common names between the
  snapshots, and make a PoloConstraint using and the central values 
  and covarience matrix the given snapshot (other). 
  NOTE - NO NOT DELETE THE RETURNED CONSTRAINT */

  PoloConstraint* getConstraint( MINT::MinuitParameterSet* parSet );
  /**< try and match the parameter names in this snapshot to fit 
  parameters in the MinuitParameterSet. Any parameters that
  can be matched, make a PoloConstraint.
  NOTE - NO NOT DELETE THE RETURNED CONSTRAINT */

  PoloConstraint* getConstraintFromFile(TString filename);
  /**< make a snapshot from the file containing any paramaters common with
  this snapshot. Use these common parameters, and the central values and covarience
  matrix from the file to make a PoloConstraint.
  NOTE - NO NOT DELETE THE RETURNED CONSTRAINT */


};


#endif


