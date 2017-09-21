#include "PoloLLHAbs.h"



PoloLLHAbs::PoloLLHAbs() :
  _name("")
{

}

PoloLLHAbs::PoloLLHAbs(TString name) :
  _name(name)
{

}


TString PoloLLHAbs::getName(){
  return _name;
}

void PoloLLHAbs::printOneliner(){
  std::cout << _name << "  no printOneliner made :( " << std::endl;
}


void    PoloLLHAbs::setName(TString name){
  _name = name;
}

