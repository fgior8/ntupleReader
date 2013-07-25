#ifndef MuonPlots_h
#define MuonPlots_h

#include "StdPlots.h"

class MuonPlots : public StdPlots{
 public:
  TH1F *h_charge, *h_HCalIso, *h_ECalIso, *h_TrkIso, *h_Detector_RelIso, *h_Detector_RelIsorho, *h_HCalIsoDeposit, *h_ECalIsoDeposit, *h_photonIso, *h_chargedHadronIso, *h_neutralHadronIso, *h_PF_RelIso, *h_GlbChi2, *h_GlbNdof, *h_GlbNormChi2, *h_dxy, *h_dz;
  MuonPlots(TString name);
  ~MuonPlots();
  void Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &photonIso, Double_t &chargedHadronIso, Double_t &neutralHadronIso, Double_t &Muon_GlobalChi2, Double_t &Muon_GlobalNdof, Double_t dxy, Double_t dz, Double_t &rho);
  void Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &Muon_GlobalChi2, Double_t &Muon_GlobalNdof);
  void Write();

};

#endif
