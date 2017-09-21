/**
 * <B> PoloObsDTYield </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 * A constraint is a bit like a PoloLLHAbs term, except that it is applied directly to
 * fit parameters rather than observables. When generating toy MC, they also behave 
 * differently. For PoloLLHAbs terms, you generate a toy measurement e.g. there is an
 * expected yeild of 5.4 for D->f decays, and in a toy experiment 7 are generated. 
 * For PoloConstraint terms, the FitParameters are first sampled from the 
 * constraint before the toy MC is generated e.g. I may constrain the c_i parameter
 * of D->f to be 0.6±0.2. Before generating the toy MC you first sample from this.
 *
 *
 **/

 
#ifndef POLO_CONSTRAINT
#define POLO_CONSTRAINT

#include "TVectorD.h"
#include "TMatrixD.h"
#include "TRandom.h"
#include "TDecompChol.h"

#include "Mint/FitParameter.h"
#include "Mint/counted_ptr.h"


class PoloConstraint {
  
  protected:

  std::vector< MINT::counted_ptr<MINT::FitParameter> > _dependencies;
  TVectorD _value;
  
  //These are going to be used so often that may as well give them
  //to the base class. Might even set some default behaviour using
  //them.

  TVectorD _mean;
  TMatrixD _covarience;

  TMatrixD _invcovarience;
  
  TString _name;

  virtual void popValsFromFPs();
  /**< populate the _values vector from the fit parameters */

  public:

  PoloConstraint(std::vector< MINT::counted_ptr<MINT::FitParameter> > dependencies, TVectorD mean, TMatrixD covarience);
  PoloConstraint();
  
  virtual double getNeg2LLH();  
  /**< Get the LLH of the constraint */ 

  virtual void fixFPsToMean();
  /**< Fix the fit parameters to the mean of the constraint */ 

  virtual void setFPsToMean();
  /**< Set the fit parameters to the mean of the constraint */ 

  virtual void fixFPs();
  /**< fix the fit parameters */ 

  virtual void unfixFPs();
  /**< unfix the fit parameters */ 

  virtual void genToyFPs (TRandom* random); 
  /**< sample the PDF defined by the constraint to pick new values for the fit parameters.
  This is important to get the correct pull distribution in a fit */ 

  virtual void randFPs   (TRandom* random);
  /**< randomise the fit parameters. */ 

  virtual std::vector< MINT::counted_ptr<MINT::FitParameter> > getDependencies();
  /**< Get a list of fit parameter dependencies */ 

  virtual PoloConstraint* clone();
  /**< clone the constraint */ 

  void setName(TString val);
  /**< name the constraint */ 

  TString getName();
  /**< get the name of the constraint */ 

  void print();
  /**< print some info */ 

  virtual ~PoloConstraint();
  /**< destructor */ 

};


#endif 


