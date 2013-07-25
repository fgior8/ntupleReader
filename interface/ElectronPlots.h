#ifndef ElectronPlots_h
#define ElectronPlots_h

#include "StdPlots.h"
#include "Data.h"

class ElectronPlots : public StdPlots{

 public:
  TH1F *h_charge, *h_HCalIso, *h_ECalIso, *h_TrkIso, *h_Detector_RelIso, *h_HCalIsoDeposit, *h_ECalIsoDeposit, *h_photonIso, *h_chargedHadronIso, *h_neutralHadronIso, *h_PF_RelIso;
  ElectronPlots(TString name);
  ~ElectronPlots();
  void Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &photonIso, Double_t &chargedHadronIso, Double_t &neutralHadronIso);
  void Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit);
  void Write();

};

#endif
