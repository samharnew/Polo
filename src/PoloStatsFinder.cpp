#include "PoloStatsFinder.h"

#include <algorithm>

#define NOT_STORED_VAL -999999.9

/**

In the constuctor you decide what things you want to be stored once you start
adding values. This will determine what statistics you are able to calcuate later

*/
PoloStatsFinder::PoloStatsFinder(bool mean, bool width, bool widthError, bool keepOrderedEvents) :
  _min    (0.0),
  _max    (0.0),
  _nEvents(0  ),
  _wSum   (0.0),
  _wSum2  (0.0),
  _wSum3  (0.0),
  _wSum4  (0.0),
  _sumW   (0.0),
  _keepOrderedEvents(keepOrderedEvents)
{
  if( widthError == 0 ) { _wSum3 = NOT_STORED_VAL; _wSum4 = NOT_STORED_VAL;} 
  if( width      == 0 ) { _wSum2 = NOT_STORED_VAL;                         }
  if( mean       == 0 ) { _wSum  = NOT_STORED_VAL; _sumW  = NOT_STORED_VAL;}
}

/**
  A warning that is shown if ordered events are needed (but haven't been stored)
*/
bool PoloStatsFinder::needOrderedEvents() const{
  if (_keepOrderedEvents == 0){
    std::cout << "You need to keep ordered events to calculate this value";
    return 0;
  }
  return 1;
}

/**
  A warning that is shown if the value being returned is meaningless because 
  weights have been used
*/
void PoloStatsFinder::warnIfWeightedEvents() const{
  if ((int)_sumW != _nEvents){
    std::cout << "You have used weighted events. This may make this function meaningless";
  }
}

/**
  The median
*/
double PoloStatsFinder::median() const{
  if ( needOrderedEvents() == 0) return 0.0;
  warnIfWeightedEvents();
  
  std::sort(_orderedEvents.begin(),_orderedEvents.end());
  
  int nEntries = _orderedEvents.size();

  if (nEntries % 2 == 0){
    int lowi  = (nEntries/2) - 1;
    int highi = (nEntries/2);
    return 0.5*(_orderedEvents.at(lowi) + _orderedEvents.at(highi));
  }
  
  return _orderedEvents.at( (nEntries - 1)/2 );

}

/**
  A warning that is shown if not enough information has been provided to 
  calculate what you want
*/
bool PoloStatsFinder::notEnoughInformation(const double& val) const{
  if (val == NOT_STORED_VAL) {
    std::cout << "You are not storing the correct information to calculate this value. Consider changing the constuctor";
    return 0;
  }
  return 1;
}

/**
  Add a value (with optional weight) to the PoloStatsFinder
*/
void PoloStatsFinder::add(const double& x, const double& weight){
  if (_nEvents == 0){
    _min = x;
    _max = x;
  }
  else{
    if (x < _min) _min = x;
    if (x > _max) _max = x;
  }
  if (_sumW  != NOT_STORED_VAL) _sumW  += weight;
  if (_wSum  != NOT_STORED_VAL) _wSum  += x*weight;
  if (_wSum2 != NOT_STORED_VAL) _wSum2 += x*x*weight;
  if (_wSum3 != NOT_STORED_VAL) _wSum3 += x*x*x*weight;
  if (_wSum4 != NOT_STORED_VAL) _wSum4 += x*x*x*x*weight;

  if ( _keepOrderedEvents == 1) _orderedEvents.push_back(x);
  
  _nEvents += 1.0;
}
 
/**
  calculate and return the mean
*/
double PoloStatsFinder::mean() const{
  return expX();
}

/**
  calculate and return the error on the mean
*/
double PoloStatsFinder::meanError() const{
  return  width() /sqrt(_nEvents);
}

/**
  calculate and return the varience
*/
double PoloStatsFinder::varience() const{
  return secondCentralMom();
}

/**
  calculate and return the width
*/
double PoloStatsFinder::width() const{
  return sqrt(secondCentralMom());  
}

/**
  calculate and return the error on the width
*/
double PoloStatsFinder::widthError() const{
  return sqrt( sqrt( ( fourthCentralMom() - varience()*varience() )*(1.0/(8.0*_nEvents*_nEvents)) ) );
}

/**
  calculate and return the expectation value of X
*/
double PoloStatsFinder::expX() const{
  if ( notEnoughInformation(_wSum) == 0 ) return 0.0;
  return _wSum/_sumW;
}

/**
  calculate and return the expectation value of X^2
*/
double PoloStatsFinder::expX2() const{
  if ( notEnoughInformation(_wSum2) == 0 ) return 0.0;
  return _wSum2/_sumW;
}

/**
  calculate and return the expectation value of X^3
*/
double PoloStatsFinder::expX3() const{
  if ( notEnoughInformation(_wSum3) == 0 ) return 0.0;
  return _wSum3/_sumW; 
}

/**
  calculate and return the expectation value of X^4
*/
double PoloStatsFinder::expX4() const{
  if ( notEnoughInformation(_wSum4) == 0 ) return 0.0;
  return _wSum4/_sumW;  
}

/**
  calculate and return the second central moment

  E[(X - E(X))^2] = E[X^2] - E[X]^2
*/
double PoloStatsFinder::secondCentralMom() const{
  return expX2() - expX()*expX();
}

/**
  calculate and return the second central moment

  E[(X - E(X))^4] = E[X^4] - 4E[X]E[X^3] + 6E[X]^2 E[X^2] - 3 E[X]^4
*/
double PoloStatsFinder::fourthCentralMom() const{
  return expX4() - 4.0*expX()*expX3() + 6.0*expX()*expX()*expX2() - 3.0*expX()*expX()*expX()*expX();
}

/**
  Destructor
*/
PoloStatsFinder::~PoloStatsFinder(){

}

#undef NOT_STORED_VAL 
