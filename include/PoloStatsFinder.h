/**
 * <B>Polo</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Dec 2015
 *
 * Used to find statistics for a dataset. Note that this code
 * is largely copied from HyperPlot. 
 **/

#ifndef POLO_STATISTICS_FINDER_HH
#define POLO_STATISTICS_FINDER_HH

#include <vector>
#include <iostream>
#include <math.h>

class PoloStatsFinder {

  double _min;     /**< The smallest member added to the PoloStatsFinder */
  double _max;     /**< The largest  member added to the PoloStatsFinder */
  
  double _nEvents; /**< The number of events added to the PoloStatsFinder */
  double _wSum;    /**< The weighted sum of values   added to the PoloStatsFinder */
  double _wSum2;   /**< The weighted sum of values^2 added to the PoloStatsFinder */
  double _wSum3;   /**< The weighted sum of values^3 added to the PoloStatsFinder */
  double _wSum4;   /**< The weighted sum of values^4 added to the PoloStatsFinder */
  double _sumW;    /**< The sum of weights */

  //Can specify to keep track of the ordered events
  //allowing things like the median to be calculated

  int _keepOrderedEvents; /**<  Keep a list of the values added (so the median can be found) */
  mutable std::vector<double> _orderedEvents; /**<  list of the values added  */

  bool needOrderedEvents() const;
  void warnIfWeightedEvents() const;
  bool notEnoughInformation(const double& val) const;

  public:

  PoloStatsFinder(bool mean = 1, bool width = 1, bool widthError = 1, bool keepOrderedEvents = 0);

  double median() const;
  
  double numEvents() const{return _nEvents;}  /**<  numer of events added to the PoloStatsFinder  */

  void add(const double& x, const double& weight = 1.0);

  double mean() const;
  double meanError() const;
  double varience() const;
  double width() const;
  double widthError() const;
 
  double expX() const; 
  double expX2() const;
  double expX3() const;
  double expX4() const;
  
  double secondCentralMom() const;
  double fourthCentralMom() const;

  const double& getMin() const{return _min;}  /**<  min value added to the PoloStatsFinder  */
  const double& getMax() const{return _max;}  /**<  max value added to the PoloStatsFinder  */
  
  double range() const{return _max - _min;} /**<  max - min value added to the PoloStatsFinder  */

  virtual ~PoloStatsFinder();

};

/**
 * <B>HyperPlot</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Dec 2015
 *
 * Make a PoloStatsFinder, but tell it to only store 
 * enough information to calcuate the minimum and maximum
 * 
 **/
class PoloMinMaxFinder : public PoloStatsFinder{
  public:
  PoloMinMaxFinder() : PoloStatsFinder(0,0,0,0){} /**< Constructor */
  ~PoloMinMaxFinder(){} /**< Destructor */

};

/**
 * <B>HyperPlot</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Dec 2015
 *
 * Make a PoloStatsFinder, but tell it to only store 
 * enough information to calcuate the mean
 * 
 **/
class PoloMeanFinder : public PoloStatsFinder{
  public:
  PoloMeanFinder() : PoloStatsFinder(1,0,0,0){} /**< Constructor */
  ~PoloMeanFinder(){} /**< Destructor */

};

/**
 * <B>HyperPlot</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Dec 2015
 *
 * Make a PoloStatsFinder, but tell it to only store 
 * enough information to calcuate the mean and width
 * (error on the mean also comes for free)
 **/
class PoloWidthFinder : public PoloStatsFinder{
  public:
  PoloWidthFinder() : PoloStatsFinder(1,1,0,0){} /**< Constructor */
  ~PoloWidthFinder(){} /**< Destructor */

};

/**
 * <B>HyperPlot</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Dec 2015
 *
 * Make a PoloStatsFinder, but tell it to only store 
 * enough information to calcuate the mean, width, 
 * and error on the width 
 **/
class PoloWidthErrorFinder : public PoloStatsFinder{
  public:
  PoloWidthErrorFinder() : PoloStatsFinder(1,1,1,0){} /**< Constructor */
  ~PoloWidthErrorFinder(){} /**< Destructor */

};

/**
 * <B>HyperPlot</B>,
 * Author: Sam Harnew, sam.harnew@gmail.com ,
 * Date: Dec 2015
 *
 * Make a PoloStatsFinder, and let it store enough info
 * to calculate the median 
 **/
class PoloMedianFinder : public PoloStatsFinder{
  public:
  PoloMedianFinder() : PoloStatsFinder(1,1,1,1){} /**< Constructor */
  ~PoloMedianFinder(){} /**< Destructor */

};

#endif
