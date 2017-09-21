#include "PoloPulls.h"


PoloPulls::PoloPulls(TString name ) :
  _name(name),
  _axisName(name)
{

}

void PoloPulls::add(double measurement, double error, double value, int print, std::ostream& os){

  _measurement.push_back(measurement);
  _error      .push_back(error      );
  _value      .push_back(value      );

  if (print == 1) os << _name << " :  True Value = " << value << "    Measured = " << measurement << "    Error = " << error << "    Pull = " << (measurement - value)/error << std::endl;
 
}

void PoloPulls::add(double measurement, double negError, double posError, double value, int print, std::ostream& os){
  
  double error = fabs(negError);

  if (measurement < value) error = fabs(posError);

  _measurement.push_back(measurement);
  _error      .push_back(error      );
  _value      .push_back(value      );

  if (print == 1) os << _name << " :  True Value = " << value << "    Measured = " << measurement << "    Error = " << error << "    Pull = " << (measurement - value)/error << std::endl;

}

void PoloPulls::addPull(double measurement, double pull, double value, int print, std::ostream& os){

  double error = (measurement - value)/pull;
  
  error = fabs(error);

  _measurement.push_back(measurement);
  _error      .push_back(error      );
  _value      .push_back(value      );

  if (print == 1) os << _name << " :  True Value = " << value << "    Measured = " << measurement << "    Error = " << error << "    Pull = " << (measurement - value)/error << std::endl;

}


int PoloPulls::getNToys(){
  return _measurement.size();
}

double PoloPulls::getMeas (int itoy){
  return _measurement.at(itoy);
}

double PoloPulls::getGen  (int itoy){
  return _value.at(itoy);
}

double PoloPulls::getErr  (int itoy){
  return _error.at(itoy);
}

double PoloPulls::getResid(int itoy){
  return getMeas(itoy)-getGen(itoy);
}


double PoloPulls::getPull (int itoy){
  return getResid(itoy)/getErr(itoy);
}



void PoloPulls::fillMeasStat (PoloStatsFinder& stats){
  for (int i = 0; i < getNToys(); i++){
    stats.add( getMeas(i) );
  }
}

void PoloPulls::fillGenStat  (PoloStatsFinder& stats){
  for (int i = 0; i < getNToys(); i++){
    stats.add( getGen(i) );
  }
}

void PoloPulls::fillErrStat  (PoloStatsFinder& stats){
  for (int i = 0; i < getNToys(); i++){
    stats.add( getErr(i) );
  }
}

void PoloPulls::fillPullStat (PoloStatsFinder& stats){
  for (int i = 0; i < getNToys(); i++){
    stats.add( getPull(i) );
  }
}

void PoloPulls::fillResidStat(PoloStatsFinder& stats){
  for (int i = 0; i < getNToys(); i++){
    stats.add( getResid(i) );
  }
}


void PoloPulls::print(){

  PoloWidthErrorFinder stats;
  fillPullStat(stats);

  std::cout << _name << " :  Pull = " << stats.mean() << " ± " << stats.meanError() << "    Width = " << stats.width() << " ± " << stats.widthError() << std::endl;

}



void PoloPulls::plotPulls(TString location, int nBins, double minmax, bool drawMeanWidth){
  
  PoloWidthErrorFinder stats;
  fillPullStat(stats);

  if (minmax == -1){
    double min = stats.getMin();
    double max = stats.getMax();

    min = fabs(min);
    max = fabs(max);
    if (max < min) minmax = min;
    else           minmax = max;
  }
  
  int intminmax = floor(minmax+1.0);
  TH1D pulls("pulls", "pulls", nBins, -intminmax, intminmax);
  pulls.GetXaxis()->SetTitle(_axisName + " pull");
  pulls.GetYaxis()->SetTitle("Number of Toys");

  for (unsigned i = 0; i < _measurement.size(); i++){
    pulls.Fill( getPull(i) );
  }
  
  double mean       = stats.mean();
  double meanError  = stats.meanError();
  double width      = stats.width();
  double widthError = stats.widthError();

  double normalisation = (_measurement.size()*intminmax*2.0)/(nBins*width*sqrt(2.0*TMath::Pi()));

  TF1* gaussian = new TF1("gaussian","gaus(0)",-intminmax,intminmax);
  gaussian->SetParameter(0, normalisation );
  gaussian->SetParameter(1, mean        );
  gaussian->SetParameter(2, width       );
 
  TString meanS       = ""; meanS      += mean      ;
  TString meanErrorS  = ""; meanErrorS += meanError ;
  TString widthS      = ""; widthS     += width     ;
  TString widthErrorS = ""; widthErrorS+= widthError;

  int meanChop = 4; if ( mean < 0.0 ) meanChop = 5;




  TCanvas canvas("canvas" + _name, "canvas" + _name);

  pulls.Draw("E");

  if ( drawMeanWidth == 1 ){

    TLatex* meanL  = new TLatex(0.53, 0.8, "#mu = " + meanS(0,meanChop) + " #pm " + meanErrorS(0,4));
    TLatex* widthL = new TLatex(0.53, 0.67, "#sigma = " + widthS(0,4) + " #pm " + widthErrorS(0,4));
    
    meanL->SetNDC();
    meanL->SetTextAlign(12);
    meanL->SetTextSize(0.06);
    widthL->SetNDC();
    widthL->SetTextAlign(12);
    widthL->SetTextSize(0.06);
  
    meanL ->Draw();
    widthL->Draw();

  }
  
  gaussian->SetLineColor(kRed);
  gaussian->Draw("SAME");
  pulls.Draw("SAME E");

  canvas.Print(location + _name + "_pulls.pdf");
  

}



PoloPulls::~PoloPulls(){

}