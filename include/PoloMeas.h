/**
 * <B> PoloMeas </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 **/

 
#ifndef POLO_MEAS
#define POLO_MEAS

#include "TRandom.h"
#include "Mint/counted_ptr.h"
#include "Mint/FitParameter.h"

class PoloMeas {
    
  double _val;
  double _err;

  public:

  PoloMeas();
  /**< empty constructor */

  PoloMeas(double val);
  /**< constructor with a central value but no uncertainty */

  PoloMeas(double val, double err);
  /**< constructor with a central value and uncertainty */

  double getVal();
  /**< get the central value */

  double getErr();
  /**< get the error */

  bool hasErr();
  /**< has an uncertainty been set? */


  void setVal(double val);
  /**< set the central value */

  void setErr(double err);
  /**< set the error */

  virtual ~PoloMeas();
  /**< destructor */

};


#endif
