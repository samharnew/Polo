/**
 * <B> PoloMeas </B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Sept 2017
 *
 *  
 **/

 
#ifndef POLO_MEAS_SET
#define POLO_MEAS_SET

#include "PoloMeas.h"
#include "PoloObsID.h"
#include "TMatrixD.h"
#include "TVectorD.h"

#include <map>
#include <iostream>
#include <fstream>


class PoloMeasSet {
  
  std::map<PoloObsID    , PoloMeas> _meas;
  std::map<PoloObsID, std::map<PoloObsID, PoloMeas> > _cor;

  public:

  PoloMeasSet();
  /**< empty constructor */

  PoloMeasSet(TString filename);
  /**< empty constructor */

  void setMeas( PoloObsID id, PoloMeas meas );
  void setCor ( PoloObsID id1, PoloObsID id2, PoloMeas meas );
 
  PoloMeas getMeas( PoloObsID id );
  PoloMeas getCor ( PoloObsID id1, PoloObsID id2 );

  bool measExists( PoloObsID id );
  bool corExists ( PoloObsID id1, PoloObsID id2 );
  
  void setMig ( PoloObsID true_id, PoloObsID reco_id, PoloMeas meas );
  /**< can also use this to deal with bin migration. Does 
  exactly the same as the setCor function. */

  PoloMeas getMig ( PoloObsID true_id, PoloObsID reco_id );

  bool migExists ( PoloObsID true_id, PoloObsID reco_id );


  std::vector<PoloObsID> getIDList();

  std::vector<PoloMeas> getMeasList( std::vector<PoloObsID> idList );
  TMatrixD              getCorMatix( std::vector<PoloObsID> idList );
  TVectorD              getVals    ( std::vector<PoloObsID> idList );
  TVectorD              getErrs    ( std::vector<PoloObsID> idList );


  void save( TString filename, bool append = false );
  void load( TString filename );
  
  bool allMeasHaveErrs();
  bool someMeasHaveErrs();

  bool allMeasHaveCor();
  bool someMeasHaveCor();

  virtual ~PoloMeasSet();
  /**< destructor */

};


#endif
