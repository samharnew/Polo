
#include "PoloContourPlotter.h"
#include "PoloContourOrganiser.h"

#include "PoloContour.h"


PoloContourPlotter::PoloContourPlotter(TString name, double minx, double maxx, double miny, double maxy) :
  _canvas(name + "_can" , name + "_can" ),
  _hist  (name + "_his" , name + "_his", 10, minx, maxx, 10, miny, maxy )
{

  _hist.Draw("AXIS");

  useRegularColourScheme();

}

PoloContourPlotter::PoloContourPlotter(TH2D* limits) :
  _canvas(TString(limits->GetName()) + "_can" , TString(limits->GetName()) + "_can" ),
  _hist(*(TH2D*)limits->Clone())
{


  _hist.Draw("AXIS");

  useRegularColourScheme();


}


int PoloContourPlotter::getFillColor(int i){

  return _fillColors.at(i);

}
int PoloContourPlotter::getLineColor(int i){

  return _lineColors.at(i);

}
int PoloContourPlotter::getFillStyle(int i){

  return _fillStyles.at(i);  

}


void PoloContourPlotter::useRegularColourScheme(){
  
  _fillColors = std::vector<int>(5, 0);
  _lineColors = std::vector<int>(5, 0);
  _fillStyles = std::vector<int>(5, 0);

  _fillColors[0] = kBlue  -  10;
  _fillColors[1] = kGreen -  10;
  _fillColors[2] = kRed   -  10;
  _fillColors[3] = kRed   -  10;
  _fillColors[4] = kRed   -  10;

  _lineColors[0] = kBlue  - 6;
  _lineColors[1] = kGreen - 5;
  _lineColors[2] = kRed   - 6;
  _lineColors[3] = kRed   - 6;
  _lineColors[4] = kRed   - 6;

  _fillStyles[0] = 3002;
  _fillStyles[1] = 3244;
  _fillStyles[2] = 1001;
  _fillStyles[3] = 1001;
  _fillStyles[4] = 1001;

}

void PoloContourPlotter::useAlternateColourScheme(){

  _fillColors = std::vector<int>(5, 0);
  _lineColors = std::vector<int>(5, 0);
  _fillStyles = std::vector<int>(5, 0);

  _fillColors[0] = kCyan    - 10;
  _fillColors[1] = kYellow  - 10;
  _fillColors[2] = kMagenta - 10;
  _fillColors[3] = kRed     - 10;
  _fillColors[4] = kRed     - 10;

  _lineColors[0] = kCyan    - 6;
  _lineColors[1] = kYellow  - 5;
  _lineColors[2] = kMagenta - 6;
  _lineColors[3] = kRed     - 6;
  _lineColors[4] = kRed     - 6;

  _fillStyles[0] = 3002;
  _fillStyles[1] = 3244;
  _fillStyles[2] = 1001;
  _fillStyles[3] = 1001;
  _fillStyles[4] = 1001;

}

void PoloContourPlotter::useAlternateColourScheme2(){
  
  TColor *color5 = new TColor(2205, 201.0/256.0, 217.0/256.0, 255.0/256.0);
  TColor *color4 = new TColor(2204, 181.0/256.0, 195.0/256.0, 229.0/256.0);
  TColor *color3 = new TColor(2203, 151.0/256.0, 163.0/256.0, 191.0/256.0);
  TColor *color2 = new TColor(2202, 101.0/256.0, 109.0/256.0, 127.0/256.0);
  TColor *color1 = new TColor(2201,  (50.0/256.0)*1.65,  (54.0/256.0)*1.65,  (64.0/256.0)*1.65);

  TColor *color5x = new TColor(2215,  59.0/256.0, 126.0/256.0, 255.0/256.0);
  TColor *color4x = new TColor(2214,  53.0/256.0, 113.0/256.0, 229.0/256.0);
  TColor *color3x = new TColor(2213,  44.0/256.0,  94.0/256.0, 191.0/256.0);
  TColor *color2x = new TColor(2212,  29.0/256.0,  63.0/256.0, 127.0/256.0);
  TColor *color1x = new TColor(2211,  (15.0/256.0)*1.65,  (31.0/256.0)*1.65,  (64.0/256.0)*1.65);

  _fillColors = std::vector<int>(5, 0);
  _lineColors = std::vector<int>(5, 0);
  _fillStyles = std::vector<int>(5, 0);

  _fillColors[0] = 2201;
  _fillColors[1] = 2202;
  _fillColors[2] = 2203;
  _fillColors[3] = 2204;
  _fillColors[4] = 2205;

  _lineColors[0] = 2201;
  _lineColors[1] = 2202;
  _lineColors[2] = 2203;
  _lineColors[3] = 2204;
  _lineColors[4] = 2205;

  _fillStyles[0] = 2201;
  _fillStyles[1] = 2202;
  _fillStyles[2] = 2203;
  _fillStyles[3] = 2204;
  _fillStyles[4] = 2205;

}

void PoloContourPlotter::addFilledContour(PoloContour* contour, int mothernsig){
  
  TGraph* tempBG = new TGraph( *contour->getTGraph() );
  TGraph* tempTX = new TGraph( *contour->getTGraph() );

  int nsigma = contour->getNSigma();
  
  //std::cout << "Plotting " << nsigma << " sigma contour" << std::endl;

  if (mothernsig <= nsigma) nsigma++;

  tempTX->SetLineStyle (0);
  tempTX->SetLineWidth (0);
  tempTX->SetMarkerSize(0);

  tempBG->SetLineStyle (0);
  tempBG->SetLineWidth (0);
  tempBG->SetMarkerSize(0);

  
  if (nsigma < _fillColors.size()){ 
    if ( getFillStyle(nsigma) == 1001 ) {
      tempTX->SetFillColor( getFillColor(nsigma) );
      tempTX->SetLineColor( getFillColor(nsigma) );
    }
    else{ 
      tempTX->SetFillColor( getLineColor(nsigma) );
      tempTX->SetLineColor( getLineColor(nsigma) );
    }
    tempTX->SetFillStyle( getFillStyle(nsigma) );
  
    tempBG->SetFillColor( getFillColor(nsigma) );
    tempBG->SetLineColor( getFillColor(nsigma) );
  }
  else{
    
    tempTX->SetFillColor(0);
    tempTX->SetLineColor(0);
   
    tempBG->SetFillColor(0);
    tempBG->SetLineColor(0);  

  }   
  
  _canvas.cd();
  tempBG->Draw("cfpl");
  tempTX->Draw("cfpl");

}




void PoloContourPlotter::addContourOutline(PoloContour* contour, int mothernsig, int lineStyle){

  TGraph* tempTX = new TGraph( *contour->getTGraph() );

  int nsigma = contour->getNSigma();
  
  tempTX->SetLineStyle (lineStyle);
  tempTX->SetLineWidth (3);
  tempTX->SetMarkerSize(0);
  tempTX->SetFillStyle (0);
  tempTX->SetFillColor (0);

  if (nsigma < _fillColors.size()){ 
    tempTX->SetLineColor(getLineColor(nsigma));
    tempTX->SetFillColor(getLineColor(nsigma));
  }
  else{
    tempTX->SetLineColor(0);
    tempTX->SetFillColor(0);
  }    

  tempTX->Draw("c");

}

void PoloContourPlotter::addContourOutlines(PoloContourOrganiser* contours, int lineStyle){
  contours->plotContourOutlines(this, lineStyle);
}
void PoloContourPlotter::addFilledContours (PoloContourOrganiser* contours){
  contours->plotFilledContours(this);
}

void PoloContourPlotter::plot(TString filename){
  _canvas.Print(filename);
}

PoloContourPlotter::~PoloContourPlotter(){


}


