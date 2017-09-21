#include "PoloFPPulls.h"


PoloFPPulls::PoloFPPulls(PoloFPSnapshot* genSnapshot, PoloFPSnapshot* fitSnapshot) :
  _genSnapshotPtr(genSnapshot),
  _fitSnapshotPtr(fitSnapshot)
{ 

  createPullContainers(_genSnapshotPtr);
  
}

void PoloFPPulls::createPullContainers(PoloFPSnapshot* snapshot){
  for (int i = 0; i < snapshot->size(); i++){
  	_pullstats.push_back( PoloPulls( snapshot->getName(i)) );
  }
}

void PoloFPPulls::addPull(PoloFPSnapshot* genSnapshot, PoloFPSnapshot* fitSnapshot){
  
  if (genSnapshot == 0) genSnapshot = _genSnapshotPtr;
  if (fitSnapshot == 0) fitSnapshot = _fitSnapshotPtr;

  _genSnapshots.push_back(*genSnapshot);
  _fitSnapshots.push_back(*fitSnapshot);

  for (unsigned i = 0; i < _pullstats.size(); i++){
    _pullstats.at(i).add( fitSnapshot->mean(i), 
    	                      fitSnapshot->errm(i), 
    	                      fitSnapshot->errp(i), 
    	                      genSnapshot->mean(i) 
    	                    );
  }

}


void PoloFPPulls::drawPulls(TString dir, int nbins){
  for (unsigned i = 0; i < _pullstats.size(); i++){
    _pullstats.at(i).plotPulls(dir, nbins);
  }
}


void PoloFPPulls::printPulls(){

  for (unsigned i = 0; i < _pullstats.size(); i++){
    
    PoloWidthErrorFinder stats;
    _pullstats.at(i).fillPullStat(stats);

  	double mean     = stats.mean();
  	double meanerr  = stats.meanError();
  	double width    = stats.width();
  	double widtherr = stats.widthError();
    if (mean != mean) continue;
  	std::cout << _genSnapshotPtr->getName(i) << " : mean = " << mean << " ± " << meanerr << "     width = " << width << " ± " << widtherr << std::endl;
  }

}

void PoloFPPulls::printPullsTex(TString filename, std::map<TString, TString> niceNames){
  
  std::ofstream os;
  os.open (filename.Data());  
  
  os << "\\begin{tabular}{ l | l | l }";
  os << "Name & Pull Mean & Pull Width \\\\";
  os << "\\hline" << std::endl;

  for (auto i = niceNames.begin(); i != niceNames.end(); ++i){

    int id = _genSnapshotPtr->findID( i->first );

    PoloWidthErrorFinder stats;
    _pullstats.at(id).fillPullStat(stats);

    double mean     = stats.mean();
    double meanerr  = stats.meanError();
    double width    = stats.width();
    double widtherr = stats.widthError();
    if (mean != mean) continue;
    os << std::setprecision(2) << std::fixed << i->second << " & $" << mean << " \\pm " << meanerr << "$ & $" << width << " \\pm " << widtherr << "$ \\\\" << std::endl;
  }

  os << "\\end{tabular}" << std::endl;
  os.close();  

}




PoloFPPulls::~PoloFPPulls(){

}






