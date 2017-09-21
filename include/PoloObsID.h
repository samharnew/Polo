/**
 * <B> PoloObsID </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 **/

 
#ifndef POLO_OBS_ID
#define POLO_OBS_ID

#include "TRandom.h"
#include "Mint/counted_ptr.h"
#include "Mint/FitParameter.h"

class PoloObsID {
    
  std::vector<int> _obsIDs;
  /**< A lot of the time, you will have a group of similar observables that
  you want to distinguish e.g. B->DK, D->4pi where there are N phase space bins.
  Or DDbar-> 4pi,KSpipi where there are N and M phase space bins for 4pi and
  KSpipi respectively. This identifier will be very useful for book keeping.  */

  public:

  PoloObsID();
  /**< empty constructor */

  PoloObsID(int id1);
  /**< make an PoloObsID with a single ID of given value */

  PoloObsID(int id1, int id2);
  /**< make an PoloObsID with two ids given values */

  PoloObsID(int id1, int id2, int id3);
  /**< make an PoloObsID with three ids given values */

  void setObsID(int val, int i = 0);
  /**< set the observable number */

  bool hasObsID();
  /**< have an observable numbers been set */

  int numObsIDs();
  /**< have an observable numbers been set */

  int getObsID(int i = 0);
  /**< get the observable number */

  TString getObsIDStr();
  /**< get a string that describes the ObsID */

  void addObsID(int val);
  /**< add a new observable ID to the end of the list */

  PoloObsID getPoloObsID();
  /**< get a copy of the PoloObsID */

  void setPoloObsID(PoloObsID& obsID);

  TString getStr() const;

  bool greaterThan(const PoloObsID& other) const;
  bool lessThan   (const PoloObsID& other) const;
  bool equalTo    (const PoloObsID& other) const;

  bool operator <  (const PoloObsID& other) const;
  bool operator >  (const PoloObsID& other) const;
  bool operator == (const PoloObsID& other) const;

  virtual ~PoloObsID();
  /**< destructor */

};


#endif
