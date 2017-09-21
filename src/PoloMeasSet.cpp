#include "PoloMeasSet.h"


PoloMeasSet::PoloMeasSet(){

}


void PoloMeasSet::setMeas( PoloObsID id, PoloMeas meas ){

  _meas[id] = meas;
}

void PoloMeasSet::setCor ( PoloObsID id1, PoloObsID id2, PoloMeas meas ){
  
  _cor[id1][id2] = meas;

}
  
std::vector<PoloObsID> PoloMeasSet::getIDList(){

  std::vector<PoloObsID> list;

  for (auto iter = _meas.begin(); iter != _meas.end(); ++iter){
    list.push_back( iter->first );
  }
  
  return list;

}

bool PoloMeasSet::measExists( PoloObsID id ){
  return _meas.count(id) == 1;
}

bool PoloMeasSet::corExists ( PoloObsID id1, PoloObsID id2 ){

  if ( _cor.count(id1)      == 0 ) return false;
  if ( _cor[id1].count(id2) == 0 ) return false;
  return true;

}

PoloMeas PoloMeasSet::getMeas( PoloObsID id ){
  
  return _meas[id];

}


PoloMeas PoloMeasSet::getCor ( PoloObsID id1, PoloObsID id2 ){

  return _cor[id1][id2];

}

bool PoloMeasSet::allMeasHaveErrs(){
  std::vector<PoloObsID> idlist = getIDList();
  for (unsigned i = 0; i < idlist.size(); i++){
    if ( getMeas(idlist.at(i)).hasErr() == false) {
      return false;
    }
  }
  return true;
}

bool PoloMeasSet::allMeasHaveCor(){
  std::vector<PoloObsID> idlist = getIDList();
  for (unsigned i = 0; i < idlist.size(); i++){
    for (unsigned j = 0; j < idlist.size(); j++){
      if ( corExists( idlist.at(i), idlist.at(j) ) == false) {
        return false;
      }
    }
  }
  return true;
}

bool PoloMeasSet::someMeasHaveErrs(){
  std::vector<PoloObsID> idlist = getIDList();
  for (unsigned i = 0; i < idlist.size(); i++){
    if ( getMeas(idlist.at(i)).hasErr() == true) {
      return true;
    }
  }
  return false;
}

bool PoloMeasSet::someMeasHaveCor(){
  std::vector<PoloObsID> idlist = getIDList();
  for (unsigned i = 0; i < idlist.size(); i++){
    for (unsigned j = 0; j < idlist.size(); j++){
      if ( corExists( idlist.at(i), idlist.at(j) ) == true) {
        return true;
      }
    }
  }
  return false;
}

std::vector<PoloMeas> PoloMeasSet::getMeasList( std::vector<PoloObsID> idList ){
  
  std::vector<PoloMeas> measList;

  for (unsigned i = 0; i < idList.size(); i++){
    if ( measExists(idList.at(i)) == true ){
      measList.push_back( getMeas( idList.at(i) ) );
    }
    else{
      std::cout << "ERROR: The observable ID you have requested is not avalible in this PoloMeasSet" << std::endl;
    }
  }
  
  return measList;

}

TMatrixD              PoloMeasSet::getCorMatix( std::vector<PoloObsID> idList ){
  
  TMatrixD matrix( idList.size(), idList.size() );

  for (unsigned i = 0; i < idList.size(); i++){
    for (unsigned j = 0; j < idList.size(); j++){
      
      if ( corExists(idList.at(i), idList.at(j)) == true ){
        matrix(i,j) = getCor( idList.at(i), idList.at(j) ).getVal();
      }
      else{
        std::cout << "ERROR: The observable ID you have requested is not avalible in this PoloMeasSet" << std::endl;
      }
    }
  }
  
  return matrix;

}

TVectorD    PoloMeasSet::getVals    ( std::vector<PoloObsID> idList ){
  TVectorD vect(idList.size());
  
  for (unsigned i = 0; i < idList.size(); i++){

      if ( measExists(idList.at(i)) == true ){
        vect(i) = getMeas( idList.at(i) ).getVal();
      }
      else{
        std::cout << "ERROR: The observable ID you have requested is not avalible in this PoloMeasSet" << std::endl;
      }

  }
  return vect;

}

TVectorD    PoloMeasSet::getErrs    ( std::vector<PoloObsID> idList ){
  TVectorD vect(idList.size());
  
  for (unsigned i = 0; i < idList.size(); i++){

      if ( measExists(idList.at(i)) == true ){
        vect(i) = getMeas( idList.at(i) ).getErr();
      }
      else{
        std::cout << "ERROR: The observable ID you have requested is not avalible in this PoloMeasSet" << std::endl;
      }

  }
  return vect;

}




void PoloMeasSet::save( TString filename, bool append ){

  std::ofstream file;
  
  if (append == false){
    file.open (filename.Data());   
  }
  if (append == true){
    file.open (filename.Data(), std::ios_base::app);   
  }
  
  //Save all the central values
  for (auto iter = _meas.begin(); iter != _meas.end(); ++iter) {

    TString idStr = iter->first .getStr();
    double  val   = iter->second.getVal();
    double  err   = iter->second.getErr();
    bool hasErr   = iter->second.hasErr();
    
    file << "meas_" << idStr << "   " << val;
    if (hasErr) file << "   " << err;
    file << std::endl;

  }    


  //Save all the correlations  
  for (auto iteri = _cor.begin(); iteri != _cor.end(); ++iteri) {
    for (auto iterj = iteri->second.begin(); iterj != iteri->second.end(); ++iterj) {

      TString idStri = iteri->first .getStr();
      TString idStrj = iterj->first .getStr();

      double  val   = iterj->second.getVal();
      double  err   = iterj->second.getErr();
      bool hasErr   = iterj->second.hasErr();
      
      file << "cor_" << idStri << "_x_" << idStrj << "   " << val;
      if (hasErr) file << "   " << err;
      file << std::endl;
    }
  }  


  file.close();

}

void PoloMeasSet::load( TString filename ){

  std::ifstream inputFile(filename.Data());
  std::string line;
  
  while( getline(inputFile, line) ) {
  
    std::istringstream iss(line);
    std::string name  = "" ;
    double      val = 0.0;
    double      err = -1.0;

    iss >> name >> val >> err;

    PoloMeas meas(val);
    if (err != -1) meas.setErr(err);

    std::istringstream namess(name);
    std::string str  = "" ;
    
    bool passedX = false;
    PoloObsID poloID1;
    PoloObsID poloID2;

    while( getline(namess, str, '_') ){
      if (str == "meas") continue;
      if (str == "cor" ) continue;
      if (str == "x" ) {
        passedX = true;
        continue;
      }
      if (passedX == false) {
        int id = 0;
        std::istringstream idss(str);
        idss >> id;
        poloID1.addObsID(id);
      }
      if (passedX == true) {
        int id = 0;
        std::istringstream idss(str);
        idss >> id;
        poloID2.addObsID(id);
      }  

    }
    
    if ( poloID2.numObsIDs() == 0 ){
      setMeas(poloID1, meas);
    }
    else {
      setCor(poloID1, poloID2, meas);
    }


  }

}




PoloMeasSet::~PoloMeasSet(){

}


