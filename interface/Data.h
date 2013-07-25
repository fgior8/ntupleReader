#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <TROOT.h>
#include "TTree.h"
#include <TChain.h>
#include <TFile.h>
//#include "TLorentzVector.h"
//#include "TH1F.h"
//#include "TH2F.h"
//#include "TH3F.h"

//#include "Lepton.h"
//#include "Permutation.h"
//#include "Jet.h"
#include "/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/LeptonAnalysis/interface/MuonData.h"
#include "/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/LeptonAnalysis/interface/ElectronData.h"
#include "/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/LeptonAnalysis/interface/JetData.h"
#include "/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/LeptonAnalysis/interface/METData.h"
#include "/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/LeptonAnalysis/interface/OtherData.h"

typedef std::map<std::string, bool> stringtobool;

class Data : public MuonData, public ElectronData, public JetData, public OtherData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   Data();
   ~Data();

   Int_t    GetEntry(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void Init(TTree *tree);
   Bool_t   Notify(); //remove if possible
   void     Show(Long64_t entry = -1); //remove if possible

   void setBranchStatus(void);

    bool trig(std::string triggername)
      { return HLT_triggered->find(triggername) != HLT_triggered->end()
               && (*HLT_triggered)[triggername]; }

    ////////////////////////////////////
    //   Declaration of leaf types    //
    ////////////////////////////////////

    stringtobool* HLT_triggered;

    // MET
    Int_t MET_Nalgo;
    std::vector<std::string>* MET_algoStringVector;
    Double_t MET_fullcorr_nocc[5][3];
    Double_t MET_fullcorr_nocc_significance[5];
    Double_t MET_uncorrALL_nocc[5][2];
    Double_t MET_uncorrJES_nocc[5][2];
    Double_t MET_uncorrMUON_nocc[5][2];
    Double_t MET_gen[5][3];

    Long64_t nentries;

};

#endif


