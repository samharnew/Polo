#include "PoloContourOrganiser.h"
    
PoloContourOrganiser::PoloContourOrganiser(){

}

void PoloContourOrganiser::addContour(PoloContour* contour){
  _unorganisedContours.push_back(contour);
}

void PoloContourOrganiser::orgainise(){
  
  std::vector<PoloContour*> motherContours;
  std::vector<PoloContour*> daughtContours;
  
  //Look through the unorganised contours and find any that are not contained 
  //by the others
  findMotherContours( _unorganisedContours, motherContours, daughtContours);
  
  //These form the top of the organised contour tree.
  _organisedContours = motherContours;
  std::vector<PoloContour*> prevDaught = daughtContours;
  
  int nTopMothers = _organisedContours.size();
  
  while ( prevDaught.size() != 0 ){
    
    //Look at the contours that have not yet been added to the orgainised 
    //contours. Find which of these are not contained by any other.
    //Add these to each of the TopMothers.

    findMotherContours(prevDaught, motherContours, daughtContours);
    int nMothers = motherContours.size();

    for (int j = 0; j < nMothers; j++){
      for (int i = 0; i < nTopMothers; i++){
        bool added = _organisedContours.at(i)->addDaughter( motherContours.at(j) );
        if (added == true) break;
      }    
    }

    prevDaught = daughtContours;

  }

}


void PoloContourOrganiser::findMotherContours(std::vector<PoloContour*> unsortedContours, std::vector<PoloContour*>& motherContours, std::vector<PoloContour*>& daughterContours){

  
  motherContours   .clear();
  daughterContours .clear();

  int nContours = unsortedContours.size();

  for (int icont = 0; icont < nContours; icont++){
    
    bool insideAny = false;

    for (int jcont = 0; jcont < nContours; jcont++){

      if (icont == jcont) continue;
      
      double fracA = 0.0;
      double fracB = 0.0;

      unsortedContours.at(jcont)->isInside( *unsortedContours.at(icont), &fracA );
      unsortedContours.at(icont)->isInside( *unsortedContours.at(jcont), &fracB );

      if ( fracA > 0.80 ) insideAny = true;

    }    
    
    if (insideAny == false) motherContours    .push_back( unsortedContours.at(icont) );
    else                    daughterContours  .push_back( unsortedContours.at(icont) );
  }

}

void PoloContourOrganiser::plotFilledContours (PoloContourPlotter* plotter){

  int nMothers = _organisedContours.size();
  for (int i = 0; i < nMothers; i++){
    _organisedContours.at(i)->plotFilledContours(plotter, 10);

  }  

}

void PoloContourOrganiser::plotContourOutlines(PoloContourPlotter* plotter, int style){

  int nMothers = _organisedContours.size();
  for (int i = 0; i < nMothers; i++){
  
    _organisedContours.at(i)->plotContourOutlines(plotter, 10, style);

  }  

}


PoloContourOrganiser::~PoloContourOrganiser(){
  
}
  