#include "PoloLLHScan2D.h"





PoloLLHScan2D::PoloLLHScan2D(TString name, TString xparname, TString yparname, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax) :
  _scanname(name),
  _xparname(xparname),
  _yparname(yparname),
  _scan(_scanname, _scanname, nbinsx, xmin, xmax, nbinsy, ymin, ymax)
{
  
  _scan.GetXaxis()->SetTitle(_xparname);
  _scan.GetYaxis()->SetTitle(_yparname);

}
  
PoloLLHScan2D::PoloLLHScan2D(TDirectory* dir){

  load(dir);

}

void PoloLLHScan2D::save(TDirectory* dir){
  
  TNamed scanname("scanname", _scanname.Data());
  TNamed xparname("xparname", _xparname.Data());
  TNamed yparname("yparname", _yparname.Data());

  dir->cd();
  scanname.Write();
  xparname.Write();
  yparname.Write();
  _scan.Write();
  for (unsigned i = 0; i < _indscans.size(); i++){
    _indscans.at(i)->Write();
  }

}

void PoloLLHScan2D::save(TString filename){
  TFile* file = new TFile(filename, "RECREATE");
  if (file == 0){
    std::cout << "ERROR: PoloLLHScan2D could not create file" << std::endl;
    return;
  }
  save(file);
  file->Close();
}


TH2D* PoloLLHScan2D::addIndScan(){

  int nbinsx  = _scan.GetXaxis()->GetNbins();
  int nbinsy  = _scan.GetYaxis()->GetNbins();

  double xmin = _scan.GetXaxis()->GetBinLowEdge(1     );
  double xmax = _scan.GetXaxis()->GetBinUpEdge (nbinsx);

  double ymin = _scan.GetYaxis()->GetBinLowEdge(1     );
  double ymax = _scan.GetYaxis()->GetBinUpEdge (nbinsy);

  TString name = _scanname + "_ind";
  name += _indscans.size();
  _indscans.push_back( new TH2D(name,name,nbinsx,xmin,xmax,nbinsy,ymin,ymax) );
  _indscans.back()->GetXaxis()->SetTitle(_xparname);
  _indscans.back()->GetYaxis()->SetTitle(_yparname);
  return _indscans.back();

}

TH2D* PoloLLHScan2D::getScan(){
  return &_scan;
}


void PoloLLHScan2D::load(TString filename){
  TFile* file = new TFile(filename, "READ");
  if (file == 0){
    std::cout << "ERROR: PoloLLHScan2D could not load file" << std::endl;
    return;
  }
  load(file);
  file->Close();
}

void PoloLLHScan2D::load(TDirectory* dir){
  
  _scanname = dir->Get("scanname")->GetTitle();
  _xparname = dir->Get("xparname")->GetTitle();
  _yparname = dir->Get("yparname")->GetTitle();
  _scan     = *((TH2D*)dir->Get(_scanname)->Clone());
  
  gROOT->cd();
  for (int i = 0; i < 10000; i++){
    TString name = _scanname + "_ind";
    name += i;
    if ( dir->Get(name) != 0 ){
      TH2D* hist = (TH2D*)dir->Get(name)->Clone(name);
      _indscans.push_back( hist );
    }
    else{
      break;
    }
  }

}

void PoloLLHScan2D::popScanFromInds(){

  int nbinsx  = _scan.GetXaxis()->GetNbins();
  int nbinsy  = _scan.GetYaxis()->GetNbins();

  for (int i = 1; i <= nbinsx; i++){
    for (int j = 1; j <= nbinsy; j++){

      PoloMinMaxFinder minmax;
      for (unsigned h = 0; h < _indscans.size(); h++){
        minmax.add( _indscans.at(h)->GetBinContent(i,j) );
      }
      _scan.SetBinContent( i, j, minmax.getMin() );

    }
  }

}

int PoloLLHScan2D::nIndScans(){
  
  return _indscans.size();

}

TString PoloLLHScan2D::getXParName(){
  return _xparname;
}
TString PoloLLHScan2D::getYParName(){
  return _yparname;

}

TH2D* PoloLLHScan2D::getIndScan(int i){
 
  return _indscans.at(i);

}

void PoloLLHScan2D::plot(TString output){

  TCanvas canvas("PoloLLHScan1DPlot", "PoloLLHScan1DPlot");
  _scan.Draw("COLZ");
  canvas.Print(output);
}

TString PoloLLHScan2D::getName(){
  return _scanname;
}

void PoloLLHScan2D::print(){

  std::cout << "scanname = " << _scanname << std::endl;
  std::cout << "xparname = " << _xparname << std::endl;
  std::cout << "nbins    = " << _scan.GetXaxis()->GetNbins() << std::endl;

}


PoloLLHScan2D::~PoloLLHScan2D(){

}




