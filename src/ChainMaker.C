#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"

TChain* ChainMaker(std::string filelist) {

  std::ifstream fin(filelist.c_str());
  std::string word;

  TChain* chain = new TChain("leptonAnalysis/allData");

  while ( fin >> word ) {
    chain->Add( word.c_str() );
    //std::cout << word << std::endl;
  }
  fin.close();

  //std::cout << "#events = " << chain->GetEntries() << std::endl;
  return chain;

}
