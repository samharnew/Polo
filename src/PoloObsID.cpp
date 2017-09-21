#include "PoloObsID.h"


PoloObsID::PoloObsID(){
  
}

PoloObsID::PoloObsID(int id1){
  _obsIDs.push_back(id1);
}

PoloObsID::PoloObsID(int id1, int id2){
  _obsIDs.push_back(id1);
  _obsIDs.push_back(id2);
}

PoloObsID::PoloObsID(int id1, int id2, int id3){
  _obsIDs.push_back(id1);
  _obsIDs.push_back(id2);
  _obsIDs.push_back(id3);
}


int PoloObsID::numObsIDs(){
  
  return _obsIDs.size();

}

void PoloObsID::setObsID(int val, int i){
  
  if (i >= numObsIDs()){
    _obsIDs.push_back(0);
    setObsID(val, i);
  }
  else{
    _obsIDs.at(i) = val;
  }
  
}

TString PoloObsID::getObsIDStr(){
  
  TString str = "(";
  for (int i = 0; i < numObsIDs(); i++){
    int val = getObsID(i);
    if (val >= 0) {
      str += "+";
      str += val;
    }
    else{
      str += val;
    }
    if (i != numObsIDs() - 1) {
      str += ",";
    }
  }  
  str += ")";
  return str;

}

bool PoloObsID::hasObsID(){
  
  return _obsIDs.size() != 0;

}

int PoloObsID::getObsID(int i){
  
  return _obsIDs.at(i);

}

bool PoloObsID::lessThan(const PoloObsID& other) const {
  if (_obsIDs.size() < other._obsIDs.size()) return true;
  if (_obsIDs.size() > other._obsIDs.size()) return false;

  for (unsigned i = 0; i < _obsIDs.size(); i++){
    if (_obsIDs.at(i) < other._obsIDs.at(i)) return true;
    if (_obsIDs.at(i) > other._obsIDs.at(i)) return false;
  }
  return false;
}

bool PoloObsID::greaterThan(const PoloObsID& other) const{
  if (_obsIDs.size() < other._obsIDs.size()) return false;
  if (_obsIDs.size() > other._obsIDs.size()) return true;

  for (unsigned i = 0; i < _obsIDs.size(); i++){
    if (_obsIDs.at(i) < other._obsIDs.at(i)) return false;
    if (_obsIDs.at(i) > other._obsIDs.at(i)) return true;
  }
  return false;

}

bool PoloObsID::equalTo(const PoloObsID& other) const{
  if (_obsIDs.size() != other._obsIDs.size()) return false;

  for (unsigned i = 0; i < _obsIDs.size(); i++){
    if (_obsIDs.at(i) != other._obsIDs.at(i)) return false;
  }
  return true;
}

bool PoloObsID::operator <  (const PoloObsID& other) const{
  return lessThan(other);
}
bool PoloObsID::operator >  (const PoloObsID& other) const{
  return greaterThan(other);
}
bool PoloObsID::operator == (const PoloObsID& other) const{
  return equalTo(other);
}

void PoloObsID::addObsID(int val){
  _obsIDs.push_back(val);
}

PoloObsID PoloObsID::getPoloObsID(){
  return PoloObsID(*this);
}

void PoloObsID::setPoloObsID(PoloObsID& obsID){
  _obsIDs = obsID._obsIDs;
}



TString PoloObsID::getStr() const{
  
  TString str = "";
  for (unsigned i = 0; i < _obsIDs.size(); i++){
    if (_obsIDs.at(i) >= 0) str += "+";
    str += _obsIDs.at(i);
    if (i != (_obsIDs.size() -1) ) str += "_";
  }
  return str;
}


PoloObsID::~PoloObsID(){

}




