#include "PoloContourMaker.h"


PoloContourMaker* PoloContourMaker::s_singleton = 0; 

TH2D* PoloContourMaker::s_originalHist = 0; 

TH2D* PoloContourMaker::s_wideHist = 0;     
  
double PoloContourMaker::s_minReturn = 0;
double PoloContourMaker::s_maxReturn = 0;

PoloContourMaker::PoloContourMaker() {




}


void PoloContourMaker::setHistogram(TH2D* hist){

  s_originalHist = hist;
  makeWideHist();

}

void PoloContourMaker::makeWideHist(){
  
  //create a histogram that is 2 bins wider in each direction

  Double_t x_axis_min = s_originalHist->GetXaxis()->GetXmin();
  Double_t x_axis_max = s_originalHist->GetXaxis()->GetXmax();
  Double_t y_axis_min = s_originalHist->GetYaxis()->GetXmin();
  Double_t y_axis_max = s_originalHist->GetYaxis()->GetXmax();
  
  int nBinsX = s_originalHist->GetXaxis()->GetNbins();
  int nBinsY = s_originalHist->GetYaxis()->GetNbins();

  double xwidth = x_axis_max - x_axis_min;
  double ywidth = y_axis_max - y_axis_min;
  
  double xbinwidth = xwidth/double(nBinsX);
  double ybinwidth = ywidth/double(nBinsY);

  x_axis_min -= 2*xbinwidth;
  x_axis_max += 2*xbinwidth;
  y_axis_min -= 2*ybinwidth;
  y_axis_max += 2*ybinwidth;
  

  delete s_wideHist;
  s_wideHist = new TH2D("tempHist", "tempHist", nBinsX + 4, x_axis_min, x_axis_max, nBinsY + 4, y_axis_min, y_axis_max);
  
  PoloMinMaxFinder stats;
  for (int i = 1 ; i <= nBinsX; i++){
    for (int j = 1 ; j <= nBinsY; j++){
      stats.add( s_originalHist->GetBinContent(i, j) );
    }
  }

  //First set all the bins to a really big value
  s_minReturn = stats.getMin();
  s_maxReturn = stats.getMin() + 20000.0;

  for (int i = 1 ; i <= nBinsX + 4; i++){
    for (int j = 1 ; j <= nBinsY + 4; j++){
      s_wideHist->SetBinContent(i, j, s_maxReturn);
    }
  }
  
  //Leave the outer row as it is, as well as the bins that overlap with the original histogram
  for (int i = 2; i <= nBinsX + 3; i++){
    for (int j = 2; j <= nBinsY + 3; j++){
      
      //map back to the orginal histogram bin numbers
      double tempi = i - 2;
      double tempj = j - 2;

      //if it's outside the bin number range, push it back in.
      if (tempi == 0          ) tempi++;
      if (tempj == 0          ) tempj++;
      if (tempi == nBinsX + 3 ) tempi--;
      if (tempj == nBinsY + 3 ) tempj--;
      
      double cont = s_originalHist->GetBinContent(tempi, tempj);

      s_wideHist->SetBinContent(i, j, cont);
    }
  } 

}

double PoloContourMaker::smoothedHistogram( Double_t * abscissa, Double_t * parameter ){

    Double_t x = abscissa[0];
    Double_t y = abscissa[1];

    Double_t x_axis_min = s_wideHist->GetXaxis()->GetXmin();
    Double_t x_axis_max = s_wideHist->GetXaxis()->GetXmax();
    Double_t y_axis_min = s_wideHist->GetYaxis()->GetXmin();
    Double_t y_axis_max = s_wideHist->GetYaxis()->GetXmax();
    
    if (x <= x_axis_min) return s_maxReturn;
    if (x >= x_axis_max) return s_maxReturn;
    if (y <= y_axis_min) return s_maxReturn;
    if (y >= y_axis_max) return s_maxReturn;

    return -s_wideHist->Interpolate(x, y);
} 


bool PoloContourMaker::mapContourIntoRange(TGraph*& graph, double xmin, double xmax, double ymin, double ymax){
  
  double xrange = xmax - xmin;
  double yrange = ymax - ymin;
  
  xmin += xrange*0.002;
  xmax -= xrange*0.002;
  ymin += yrange*0.002;
  ymax -= yrange*0.002;

  int nPoints = graph->GetN();
  
  bool inRange = 0;
  
  double prevx = 0.0;
  double prevy = 0.0;
  int samex =0;
  int samey =0;

  Double_t* xcoords = new Double_t [graph->GetN()];
  Double_t* ycoords = new Double_t [graph->GetN()];

  int count = 0;
  
  for(int i = 0; i < nPoints; i++){
   
    double x = 0.0;
    double y = 0.0;
    graph->GetPoint(i, x, y);
    if (x == 0.0 && y == 0.0) continue;
    
    //Just need one point to be in range
    if (x > xmin && x < xmax && y > ymin && y < ymax) inRange = 1;
    
    if (x < xmin) x = xmin;
    if (x > xmax) x = xmax;
    if (y < ymin) y = ymin;
    if (y > ymax) y = ymax;
    
    xcoords[count] = x;
    ycoords[count] = y;

    if (prevx == x && prevy == y) {
      //do nothing
    }
    else{
      count++;
    }

    prevx = x; 
    prevy = y;

  }
   
  graph = new TGraph(count, xcoords, ycoords);

  delete [] xcoords;
  delete [] ycoords;

  return inRange;

}


PoloContourMaker* PoloContourMaker::getPoloContourMaker(){
  
  if (s_singleton == 0){
    s_singleton = new PoloContourMaker();
  }
  return s_singleton;

}


std::vector<TGraph*> PoloContourMaker::makeContours(double contourLevel){

  Double_t x_axis_min = s_wideHist->GetXaxis()->GetXmin();
  Double_t x_axis_max = s_wideHist->GetXaxis()->GetXmax();
  Double_t y_axis_min = s_wideHist->GetYaxis()->GetXmin();
  Double_t y_axis_max = s_wideHist->GetYaxis()->GetXmax();
  
  
  TF2* myFunc = new TF2( "myFunc", PoloContourMaker::smoothedHistogram, x_axis_min, x_axis_max, y_axis_min, y_axis_max, 0 );
  
  //find the minimum of the histogram, and set contours at 1,2 and 3 sigma

  Double_t contoursthing[1] = { - s_minReturn - contourLevel };

  myFunc->SetContour(1,contoursthing);   
  myFunc->SetNpx(500);
  myFunc->SetNpy(500);
  
  //draw contours onto canvas with list option, to save the contours as TGraphs somewhere random
  
  TCanvas *c1_m = new TCanvas("c1_m","Contours",10,10,800,600);
  myFunc->Draw("contz,list");
  c1_m->Update();

  TObjArray *contours_m = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
  
  //get a TList containing the contours for 1, 2 and 3 sigma 

  TList *lcontour1_m = (TList*)contours_m->At(0);
  
  std::vector<TGraph*> contourList;

  x_axis_min = s_originalHist->GetXaxis()->GetXmin();
  x_axis_max = s_originalHist->GetXaxis()->GetXmax();
  y_axis_min = s_originalHist->GetYaxis()->GetXmin();
  y_axis_max = s_originalHist->GetYaxis()->GetXmax();

  for (int i = 0; i < lcontour1_m->GetEntries(); i++){
    TGraph* temp = new TGraph( *((TGraph*)lcontour1_m->At(i)) );
    bool isIn = mapContourIntoRange( temp, x_axis_min, x_axis_max, y_axis_min, y_axis_max );
    if (isIn) contourList.push_back(temp);
  }
  
  delete c1_m  ;
  delete myFunc;

  return contourList;

}

PoloContourOrganiser PoloContourMaker::getContourOrgainiser(TH2D* hist, std::vector<double> levels){

  PoloContourOrganiser contoursOrg;

  setHistogram(hist);

  for (unsigned i = 0; i < levels.size(); i++){
  
    double level = levels.at(i);
    std::vector<TGraph*> contours = makeContours(level);

    for (unsigned j = 0; j < contours.size(); j++){
      contoursOrg.addContour( new PoloContour(contours.at(j), i) );
    }
  }
  
  contoursOrg.orgainise();

  return contoursOrg;

}

PoloContourOrganiser PoloContourMaker::getContourOrgainiser(TString filename, TString histname, std::vector<double> levels){

  TFile file(filename, "READ");

  if ( file.IsZombie() ) {
    std::cout << "File is a Zombie... going to crash" << std::endl;
    //return;
  }
  if (file.TestBit(TFile::kRecovered) ) {
    std::cout << "File had recovered bits... might crash" << std::endl;
  }

  //Open histograms
  
  gROOT->cd();

  TH2D* hist = new TH2D( *(TH2D*)file.Get( histname ) );
  
  PoloContourOrganiser contOrg = getContourOrgainiser(hist, levels);
  
  delete hist;

  return contOrg;

}



