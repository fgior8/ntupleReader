#ifndef MuonSelection_h
#define MuonSelection_h

#include "LeptonSelection.h"

class MuonSel : public Lep {
  Int_t numVer, leptoni, ifid;
  Double_t Vxy, Vz;
  Double_t dz_cut;
  Double_t MuTkIso, MuEcalIso, MuHcalIso;
  static const Double_t AreaTrackerMu[5];
  static const Double_t AreaEcalMu[5];
  static const Double_t AreaHcalMu[5];

 public:
  MuonSel();
  ~MuonSel();

  void MuonSelection(Int_t Nlepton, Bool_t *Lepton_IsTracker, Double_t *Lepton_Eta, Double_t *Lepton_Pt, Double_t *Lepton_PtErr, Double_t *Lepton_Px, Double_t *Lepton_Py, Double_t *Lepton_Pz, Double_t *Lepton_E, Double_t *Lepton_TrkIso, Double_t *Lepton_ECalIso, Double_t *Lepton_HCalIso, Double_t *Lepton_Charge, Double_t *Lepton_ECalIsoDeposit, Double_t *Lepton_HCalIsoDeposit, Int_t *Lepton_Gen_Mother, Int_t *Lepton_TrkValidHits, std::vector<Lepton>& leptonColl, bool *Lepton_IsGlobal, Double_t *Lepton_StandValidHits, Double_t *Lepton_GlobalChi2, Double_t *Lepton_GlobalNdof, Double_t *Lepton_Trkdx, Double_t *Lepton_Trkdy, Double_t *Lepton_Trkdz, Double_t *Lepton_TrkIPToolsIP, Double_t *Lepton_TrkIPToolsIPError, Double_t *Lepton_TrkIPToolsIPSignificance, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, Double_t rho);

};

const Double_t MuonSel::AreaTrackerMu[5] = {0., 0., 0., 0., 0.};         	  //   barrel/endcap
const Double_t MuonSel::AreaEcalMu[5]    = {0.091, 0.077, 0.055, 0.034, 0.045};   //   barrel/endcap
const Double_t MuonSel::AreaHcalMu[5]    = {0.029, 0.027, 0.036, 0.040, 0.054};   //   barrel/endcap

#endif
