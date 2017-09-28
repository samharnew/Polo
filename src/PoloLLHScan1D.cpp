#include "PoloLLHScan1D.h"


PoloLLHScan1D::PoloLLHScan1D(TString name, TString xparname, int nbinsx, double xmin, double xmax) :
  _scanname(name),
  _xparname(xparname),
  _scan(_scanname, _scanname, nbinsx, xmin, xmax)
{
  
  _scan.GetXaxis()->SetTitle(_xparname);

}
  
PoloLLHScan1D::PoloLLHScan1D(TDirectory* dir){

  load(dir);

}

void PoloLLHScan1D::save(TDirectory* dir){
  
  TNamed scanname("scanname", _scanname.Data());
  TNamed xparname("xparname", _xparname.Data());
  
  dir->cd();
  scanname.Write();
  xparname.Write();
  _scan.Write();
  for (unsigned i = 0; i < _indscans.size(); i++){
    _indscans.at(i)->Write();
  }

}

void PoloLLHScan1D::save(TString filename){
  TFile* file = new TFile(filename, "RECREATE");
  if (file == 0){
    std::cout << "ERROR: PoloLLHScan1D could not create file" << std::endl;
    return;
  }
  save(file);
  file->Close();
}


TH1D* PoloLLHScan1D::addIndScan(){
  int nbins  = _scan.GetXaxis()->GetNbins();
  double min = _scan.GetXaxis()->GetBinLowEdge(1    );
  double max = _scan.GetXaxis()->GetBinUpEdge (nbins);
  TString name = _scanname + "_ind";
  name += _indscans.size();
  _indscans.push_back( new TH1D(name,name,nbins,min,max) );
  _indscans.back()->GetXaxis()->SetTitle(_xparname);

  return _indscans.back();
}

TH1D* PoloLLHScan1D::getScan(){
  return &_scan;
}


void PoloLLHScan1D::load(TString filename){
  TFile* file = new TFile(filename, "READ");
  if (file == 0){
    std::cout << "ERROR: PoloLLHScan1D could not load file" << std::endl;
    return;
  }
  load(file);
  file->Close();
}

void PoloLLHScan1D::load(TDirectory* dir){
  
  _scanname = dir->Get("scanname")->GetTitle();
  _xparname = dir->Get("xparname")->GetTitle();
  _scan     = *((TH1D*)dir->Get(_scanname)->Clone());
  
  gROOT->cd();
  for (int i = 0; i < 10000; i++){
    TString name = _scanname + "_ind";
    name += i;
    if ( dir->Get(name) != 0 ){
      TH1D* hist = (TH1D*)dir->Get(name)->Clone(name);
      _indscans.push_back( hist );
    }
    else{
      break;
    }
  }

}

void PoloLLHScan1D::popScanFromInds(){

  int nbins  = _scan.GetXaxis()->GetNbins();

  for (int i = 1; i <= nbins; i++){
    PoloMinMaxFinder minmax;
    for (unsigned h = 0; h < _indscans.size(); h++){
      minmax.add( _indscans.at(h)->GetBinContent(i) );
    }
    _scan.SetBinContent( i, minmax.getMin() );
  }

}

TString PoloLLHScan1D::getXParName(){
  return _xparname;
}

TString PoloLLHScan1D::getName(){
  return _scanname;
}




int PoloLLHScan1D::nIndScans(){
  
  return _indscans.size();

}

TH1D* PoloLLHScan1D::getIndScan(int i){
 
  return _indscans.at(i);

}


void PoloLLHScan1D::print(){

  std::cout << "scanname = " << _scanname << std::endl;
  std::cout << "xparname = " << _xparname << std::endl;
  std::cout << "nbins    = " << _scan.GetXaxis()->GetNbins() << std::endl;

}

void PoloLLHScan1D::plot(TString output, double delLLH){
  
  TCanvas canvas("PoloLLHScan1DPlot", "PoloLLHScan1DPlot");
  _scan.Draw();
  
  PoloMinMaxFinder stats;
  for (int i = 1; i <= _scan.GetXaxis()->GetNbins(); i++){
    stats.add( _scan.GetBinContent(i) );
  }

  _scan.SetMinimum( stats.getMin()-0.1    );
  _scan.SetMaximum( stats.getMax()+delLLH );
  canvas.Print(output);
}


PoloLLHScan1D::~PoloLLHScan1D(){

}
