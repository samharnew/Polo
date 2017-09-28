#include "PoloContour.h"

#include "PoloContourPlotter.h"

/***********************************************************************************

**********************************************************************************/

PoloContourPoint::PoloContourPoint(double x, double y) :
  _x(x),
  _y(y)
{


}
  
double PoloContourPoint::getX() const{
  return _x;
}

double PoloContourPoint::getY() const{
  return _y;
}

void PoloContourPoint::setX(const double& x){
  _x = x;
}

void PoloContourPoint::setY(const double& y){
  _y = y;
}

PoloContourPoint::~PoloContourPoint(){


}


/***********************************************************************************

**********************************************************************************/



PoloContourLine::PoloContourLine( const PoloContourPoint& a, const PoloContourPoint& b ):
  _a(a),
  _b(b)
{


}

const PoloContourPoint& PoloContourLine::getPointA() const{
  return _a;
}

const PoloContourPoint& PoloContourLine::getPointB() const{
  return _b;
}



PoloContourLine::~PoloContourLine(){


}


/***********************************************************************************

**********************************************************************************/


PoloContour::PoloContour(TGraph* graph, int level) :
  _graph(graph),
  _level(level)
{


}

int PoloContour::getNumPoints(){

  return _graph->GetN();
	
}



int PoloContour::numDaughters(){

  return (int)_daughters.size();

}

PoloContour* PoloContour::getDaughter(int i){

  return _daughters.at(i);

}

bool PoloContour::addDaughter(PoloContour* contour){

  if ( isInside( *contour ) == false) return false;

  int ndaughters = numDaughters();

  for (int i = 0; i < ndaughters; i++){
    if ( getDaughter(i)->addDaughter( contour ) == true ) return true;
  }

  _daughters.push_back( contour );
  return true;

}

PoloContourPoint PoloContour::getPoint(int i){

  double x = 0.0;
  double y = 0.0;
  _graph->GetPoint(i, x,y);
  return PoloContourPoint(x,y);
	
}

PoloContourLine  PoloContour::getLine (int i){
  
  if ( i == getNumPoints() - 1 ){
    //std::cout << "should only happen at the end" << std::endl;
    return PoloContourLine( getPoint(getNumPoints() - 1), getPoint(0) );
  }

  return PoloContourLine( getPoint(i), getPoint(i+1) );
	
}

int PoloContour::isInside   ( PoloContourPoint& point ){
  
  bool oddNodes = false;
  int nlines = getNumPoints();
  //std::cout << nlines <<std::endl;
  double x = point.getX();
  double y = point.getY();
  
  //std::cout << "PoloContour::isInside( ContourPoint& point )" << std::endl; 

  for (int i = 0 ; i < nlines; i++){
  	PoloContourLine line = getLine(i);
    double y1 = line.getPointA().getY();
    double y2 = line.getPointB().getY();
    double x1 = line.getPointA().getX();
    double x2 = line.getPointB().getX();
    
    if (x1 == x2 && x1 == x && ((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) ) return -1;
    if (y1 == y2 && y1 == y && ((y >= y1 && y <= y2) || (y >= y2 && y <= y1)) ) return -1;

    if ( (y > y1 && y <= y2) || (y >= y2 && y < y1) ) {
      
      double m = (y1-y2)/(x1-x2);
      double c = y1 - m*x1;

      if ((y - c)/m < x ) {
        oddNodes=!oddNodes;
      }
      if (x1 == x2){
      	if (x1 < x) oddNodes=!oddNodes;
      }


    }
  }

  return oddNodes;
	
}


bool PoloContour::isInside ( PoloContour& other, double* frac ){
  
  int inside  = 0;
  int outside = 0;

  int npoints = other.getNumPoints();
  for (int i = 0; i < npoints; i++){
  	PoloContourPoint point = other.getPoint(i);
  	//std::cout << "is point inside?" << std::endl;
    if ( isInside( point ) == 1 ) inside++;
    if ( isInside( point ) == 0 ) outside++;   
  }
	
  double insidefrac = double(inside)/double(inside+outside);
  //std::cout << insidefrac << std::endl;
  
  if (frac != 0) *frac = insidefrac;

  if (insidefrac > 0.80) return true;
  return false;

} 



TGraph* PoloContour::getTGraph(){

  return _graph;

}

int PoloContour::getNSigma(){

  return _level;

}


void PoloContour::plotFilledContours (PoloContourPlotter* plotter, int mothernsig){
  
  plotter->addFilledContour(this, mothernsig);

  int nDaughters = numDaughters();
  for (int i = 0; i < nDaughters; i++){    
    getDaughter(i)->plotFilledContours(plotter, _level);
  }
    
}


void PoloContour::plotContourOutlines(PoloContourPlotter* plotter, int mothernsig, int lineStyle){

  plotter->addContourOutline(this, mothernsig, lineStyle);

  int nDaughters = numDaughters();
  for (int i = 0; i < nDaughters; i++){    
    getDaughter(i)->plotContourOutlines(plotter, _level, lineStyle);
  }
    
    
}


PoloContour::~PoloContour(){

	
}
  