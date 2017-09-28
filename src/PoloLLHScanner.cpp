#include "PoloLLHScanner.h"



PoloLLHScanner::PoloLLHScanner( PoloFPSnapshot& snapshot ) :
  _fitPars(snapshot)
{

}

PoloLLHScanner::PoloLLHScanner( TString filename ){
  load(filename);
}

void PoloLLHScanner::doQuietFit( MINT::Minimiser* minimiser ){

  TString redirectFile = "/FitOutput.txt";

  static std::ofstream out(redirectFile);
  std::streambuf *coutbuf = std::cout.rdbuf(); 
  std::cout.rdbuf(out.rdbuf()); 

  int oldErrorLevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = 5000;
  
  double arglist[10];
  int ierflg;
  arglist[0] = -1;
  minimiser->mnexcm("SET PRINT",arglist,1,ierflg);  
  arglist[0] = 0;
  minimiser->mnexcm("SET NOW",  arglist,0,ierflg);      


  minimiser->continueFit();
  
  gErrorIgnoreLevel = oldErrorLevel;

  std::cout.rdbuf(coutbuf);  


}

void PoloLLHScanner::doScan1D  (MINT::Minimiser* minimiser, int scanNum){
  
  PoloLLHScan1D& scan = _scans1D.at(scanNum);
  
  TH1D* scanHist = scan.addIndScan();
  int nbins = scanHist->GetXaxis()->GetNbins();

  TString parnamex = scan.getXParName();
  int parnumx  = _fitPars.findID( parnamex );
  double meanx = _fitPars.mean(parnumx);
  int closestBin = scanHist->GetXaxis()->FindFixBin( meanx );
  if (closestBin < 1    ) closestBin = 1;
  if (closestBin > nbins) closestBin = nbins; 

  MINT::FitParameter* fitparx = dynamic_cast<MINT::FitParameter*>(_fitPars.getParPtr(parnumx));
  
  if (fitparx->iFixInit() != 0){
    std::cout << "WARNING: Not performing a scan of parameter " << parnamex << " since it is fixed" << std::endl;
    return;
  }

  fitparx->fix();

  std::cout << "**********************************************" << std::endl;
  std::cout << "Doing scan of param : " << parnamex << std::endl;
  std::cout << "**********************************************" << std::endl;
  
  //we will already be close to the minima, so lower the required tollerance

  double usualTollerance= 0.01;
  double fastTollerance = 0.10;

  minimiser->setTollerance(fastTollerance);
  minimiser->setStrategy  (0.0);

  //this stops the cov-matrix being calculated at the end 
  minimiser->fItaur = 1;                            
       
  
  scanHist->SetBinContent(closestBin, minimiser->getFCNVal() );
  
  for (int j = closestBin + 1; j <= nbins; j++) {

    double binCenter = scanHist->GetBinCenter(j);
    fitparx->setCurrentFitVal(binCenter);

    doQuietFit(minimiser);

    scanHist->SetBinContent( j, minimiser->getFCNVal() );

  }  
  
  _fitPars.updateFPsFromSnapshot();

  for (int j = closestBin - 1; j >= 1; j--) {

    double binCenter = scanHist->GetBinCenter(j);
    fitparx->setCurrentFitVal(binCenter);

    doQuietFit(minimiser);

    scanHist->SetBinContent( j, minimiser->getFCNVal() );

  }  

  minimiser->setTollerance(usualTollerance);
  minimiser->setStrategy(1.0);
  minimiser->fItaur = 0;

  _fitPars.updateFPsFromSnapshot();

  fitparx->unFix();

  scan.popScanFromInds();

}

void PoloLLHScanner::doScan2D  (MINT::Minimiser* minimiser, int scanNum){

  PoloLLHScan2D& scan = _scans2D.at(scanNum);
  
  TH2D* scanHist = scan.addIndScan();
  int nbinsx = scanHist->GetXaxis()->GetNbins();
  int nbinsy = scanHist->GetYaxis()->GetNbins();

  TString parnamex = scan.getXParName();
  TString parnamey = scan.getYParName();

  int parnumx  = _fitPars.findID( parnamex );
  double meanx = _fitPars.mean(parnumx);

  int parnumy  = _fitPars.findID( parnamey );
  double meany = _fitPars.mean(parnumy);

  int closestBinX = scanHist->GetXaxis()->FindFixBin( meanx );
  int closestBinY = scanHist->GetYaxis()->FindFixBin( meany );
  
  if (closestBinX < 1     ) closestBinX = 1;
  if (closestBinX > nbinsx) closestBinX = nbinsx; 

  if (closestBinY < 1     ) closestBinY = 1;
  if (closestBinY > nbinsy) closestBinY = nbinsy;   


  MINT::FitParameter* fitparx = dynamic_cast<MINT::FitParameter*>(_fitPars.getParPtr(parnumx));
  MINT::FitParameter* fitpary = dynamic_cast<MINT::FitParameter*>(_fitPars.getParPtr(parnumy));
  
  if (fitparx->iFixInit() != 0 || fitpary->iFixInit() != 0){
    std::cout << "WARNING: Not performing a scan of parameters " 
              << parnamex << " and " << parnamey << " since one is fixed" << std::endl;
    return;
  }

  fitparx->fix();
  fitpary->fix();

  std::cout << "**********************************************" << std::endl;
  std::cout << "Doing scan of param : " << parnamex << " vs. " << parnamey << std::endl;
  std::cout << "**********************************************" << std::endl;
  
  //we will already be close to the minima, so lower the required tollerance

  double usualTollerance= 0.01;
  double fastTollerance = 0.10;

  minimiser->setTollerance(fastTollerance);
  minimiser->setStrategy  (0.0);

  //this stops the cov-matrix being calculated at the end 
  minimiser->fItaur = 1;                            
       
  _fitPars.updateFPsFromSnapshot();

  scanHist->SetBinContent(closestBinX, closestBinY, minimiser->getFCNVal() );
  
  PoloFPSnapshot snap(_fitPars);
  
  for (int i = closestBinX; i <= nbinsx; i++) {
    
    double valX = scanHist->GetXaxis()->GetBinCenter(i          );
    double valY = scanHist->GetYaxis()->GetBinCenter(closestBinY);    

    snap.updateFPsFromSnapshot();

    fitparx->setCurrentFitVal(valX);   
    fitpary->setCurrentFitVal(valY);     
    doQuietFit(minimiser);
    if (i != closestBinX){
      scanHist->SetBinContent( i, closestBinY, minimiser->getFCNVal() );
    }

    snap.updateSnapshotFromFPs();

    for (int j = closestBinY+1; j <= nbinsy; j++) {

      valY = scanHist->GetYaxis()->GetBinCenter(j);

      fitparx->setCurrentFitVal(valX);   
      fitpary->setCurrentFitVal(valY);     
      doQuietFit(minimiser);
      scanHist->SetBinContent( i, j, minimiser->getFCNVal() ); 

    }  

    snap.updateFPsFromSnapshot();

    for (int j = closestBinY-1; j >=1; j--) {
  
      valY = scanHist->GetYaxis()->GetBinCenter(j);

      fitparx->setCurrentFitVal(valX);   
      fitpary->setCurrentFitVal(valY);     
      doQuietFit(minimiser);
      scanHist->SetBinContent( i, j, minimiser->getFCNVal() ); 


    }      

  }
  
  snap = _fitPars;

  for (int i = closestBinX-1; i >=1; i--) {

    double valX = scanHist->GetXaxis()->GetBinCenter(i          );
    double valY = scanHist->GetYaxis()->GetBinCenter(closestBinY);    

    snap.updateFPsFromSnapshot();

    fitparx->setCurrentFitVal(valX);   
    fitpary->setCurrentFitVal(valY);     
    doQuietFit(minimiser);
    scanHist->SetBinContent( i, closestBinY, minimiser->getFCNVal() );
    
    snap.updateSnapshotFromFPs();

    for (int j = closestBinY+1; j <= nbinsy; j++) {

      valY = scanHist->GetYaxis()->GetBinCenter(j);

      fitparx->setCurrentFitVal(valX);   
      fitpary->setCurrentFitVal(valY);     
      doQuietFit(minimiser);
      scanHist->SetBinContent( i, j, minimiser->getFCNVal() ); 

    }  

    snap.updateFPsFromSnapshot();

    for (int j = closestBinY-1; j >= 1; j--) {
  
      valY = scanHist->GetYaxis()->GetBinCenter(j);

      fitparx->setCurrentFitVal(valX);   
      fitpary->setCurrentFitVal(valY);     
      doQuietFit(minimiser);
      scanHist->SetBinContent( i, j, minimiser->getFCNVal() ); 


    }      

  }

  minimiser->setTollerance(usualTollerance);
  minimiser->setStrategy(1.0);
  minimiser->fItaur = 0;

  _fitPars.updateFPsFromSnapshot();

  fitparx->unFix();  
  fitpary->unFix();  
  scan.popScanFromInds();


}


void PoloLLHScanner::add1Dscan(TString scanName, TString name1, int nbinsx, double xmin, double xmax){

  PoloLLHScan1D scan(scanName, name1, nbinsx, xmin, xmax); 
  _scans1D.push_back(scan);

}

void PoloLLHScanner::add2Dscan(TString scanName, TString name1, TString name2, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax){

  PoloLLHScan2D scan(scanName, name1, name2, nbinsx, xmin, xmax, nbinsy, ymin, ymax); 
  _scans2D.push_back(scan);

}


void PoloLLHScanner::addMinimiser(MINT::Minimiser* minimiser){

  _fitPars.updateSnapshotFromFPs();
  _fitPars.updateCorrelations(minimiser);  
  
  bool isUnique = !_uniqueSolutions.containsEqual( _fitPars, 0.02 );
  
  if (isUnique){
    _uniqueSolutions.add(_fitPars);
    for (unsigned i = 0; i < _scans1D.size(); i++){
      doScan1D(minimiser, i);
    }
    for (unsigned i = 0; i < _scans2D.size(); i++){
      doScan2D(minimiser, i);
    }
  }

}

void PoloLLHScanner::plot(TString directory){

  for (unsigned i = 0; i < _scans1D.size(); i++){
    _scans1D.at(i).plot(directory + _scans1D.at(i).getName() + ".pdf");
  }
  for (unsigned i = 0; i < _scans2D.size(); i++){
    _scans2D.at(i).plot(directory + _scans2D.at(i).getName() + ".pdf");    
  }

}

int PoloLLHScanner::get2DScanNum(TString scanName){
  for (unsigned i = 0; i < _scans2D.size(); i++){
    if (scanName == _scans2D.at(i).getName()) return i;
  }
  return -1;
}

int PoloLLHScanner::get1DScanNum(TString scanName){
  for (unsigned i = 0; i < _scans1D.size(); i++){
    if (scanName == _scans1D.at(i).getName()) return i;
  }
  return -1;
}

TH2D* PoloLLHScanner::get2DScan(TString scanName){
  int scanNum = get2DScanNum(scanName);
  if (scanNum == -1){
    std::cout << "ERROR: A scan with this name does not exist. Sorry!" << std::endl;
    return 0;
  }  
  return _scans2D.at(scanNum).getScan();
}

TH1D* PoloLLHScanner::get1DScan(TString scanName){
  int scanNum = get1DScanNum(scanName);
  if (scanNum == -1){
    std::cout << "ERROR: A scan with this name does not exist. Sorry!" << std::endl;
    return 0;
  }
  return _scans1D.at(scanNum).getScan();
}

PoloContourOrganiser PoloLLHScanner::get2DContourSet(TString scanName, std::vector<double> levels){
  
  int scanNum = get2DScanNum(scanName);
  if (scanNum == -1){
    std::cout << "ERROR: A scan with this name does not exist. Sorry!" << std::endl;
    return PoloContourOrganiser();
  }

  return get2DContourSet( scanNum, levels );

}

PoloContourOrganiser PoloLLHScanner::get2DContourSet(int scanNum, std::vector<double> levels){
  
  if (levels.size() == 0){
    levels.push_back(1.0);
    levels.push_back(4.0);
    levels.push_back(9.0);
  }

  TH2D* scan = _scans2D.at(scanNum).getScan();
  PoloContourMaker* contourMaker = PoloContourMaker::getPoloContourMaker();
  PoloContourOrganiser org = contourMaker->getContourOrgainiser(_scans2D.at(scanNum).getScan(), levels);  
  return org;

}

void PoloLLHScanner::plotContours(TString directory, std::vector<double> levels){
  
  for (int i = 0; i < _scans2D.size(); i++){
    TString name = _scans2D.at(i).getName();
    PoloContourOrganiser org = get2DContourSet(i, levels);
    
    PoloContourPlotter plotter(_scans2D.at(i).getScan());
    plotter.addFilledContours  (&org);
    plotter.addContourOutlines (&org);
    plotter.plot(directory + name + ".pdf");
  }
}

void PoloLLHScanner::plotOverlappingContours(TString scanName1, TString scanName2, TString filename, std::vector<double> levels){

  PoloContourOrganiser org1 = get2DContourSet(scanName1, levels);
  PoloContourOrganiser org2 = get2DContourSet(scanName2, levels);
  
  PoloContourPlotter plotter( get2DScan(scanName1) );
  
  plotter.useRegularColourScheme();
  plotter.addFilledContours (&org1);
  plotter.addContourOutlines(&org1);

  plotter.useAlternateColourScheme();
  plotter.addFilledContours (&org2);
  plotter.addContourOutlines(&org2);

  plotter.useRegularColourScheme();
  plotter.addContourOutlines(&org1, 2);
  
  plotter.plot(filename);  

}


void PoloLLHScanner::save(TString filename){
 
  TFile* file = new TFile(filename, "RECREATE");
  
  TDirectory* dirFP = file->mkdir("fitPars");
  TDirectory* dirUS = file->mkdir("uniqueSolutions");
  TDirectory* dir1D = file->mkdir("scans1D");
  TDirectory* dir2D = file->mkdir("scans2D");

  _fitPars        .save(dirFP);
  _uniqueSolutions.save(dirUS);

  for (unsigned i = 0; i < _scans1D.size(); i++){
    TDirectory* diri = dir1D->mkdir( _scans1D.at(i).getName() );
    _scans1D.at(i).save( diri );    
  }
  for (unsigned i = 0; i < _scans2D.size(); i++){
    TDirectory* diri = dir2D->mkdir( _scans2D.at(i).getName() );
    _scans2D.at(i).save( diri );    
  }
  
  file->Close();
}

void PoloLLHScanner::load(TString filename){

  TFile* file = new TFile(filename, "READ");
  
  TDirectory* dirFP = file->GetDirectory("fitPars");
  TDirectory* dirUS = file->GetDirectory("uniqueSolutions");
  TDirectory* dir1D = file->GetDirectory("scans1D");
  TDirectory* dir2D = file->GetDirectory("scans2D");

  _fitPars        .loadOverwrite(dirFP);
  _uniqueSolutions.load(dirUS);
  
  TIter iter1D(dir1D->GetListOfKeys());
  TKey* key = 0;
  while ((key = (TKey*)iter1D())) {
    TDirectory* diri = dir1D->GetDirectory( key->ReadObj()->GetName() );
    PoloLLHScan1D scan(diri);
    _scans1D.push_back( scan );    
  }

  TIter iter2D(dir2D->GetListOfKeys());
  while ((key = (TKey*)iter2D())) {
    TDirectory* diri = dir2D->GetDirectory( key->ReadObj()->GetName() );
    PoloLLHScan2D scan(diri);
    _scans2D.push_back( scan );    
  }

  file->Close();

}


void PoloLLHScanner::print(std::ostream& os){

}

PoloLLHScanner::~PoloLLHScanner(){

}













