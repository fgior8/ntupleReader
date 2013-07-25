#ifndef LeptonSelection_h
#define LeptonSelection_h

#include <iostream>
using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "Lepton.h"
#include "OtherFunctions.h"

class Lep {

  Int_t ifid;
  Double_t ElTkIso, ElEcalIso, ElHcalIso;
  static const Double_t AreaTrackerEl[2];
  static const Double_t AreaEcalEl[2];
  static const Double_t AreaHcalEl[2];

 public:
  Lepton::FakeType fakeType;
  Lepton::LooseTight looseTight;
  Lepton::LeptonType leptonType;
  TLorentzVector vLepton;
  Bool_t etaPt,RelIsod0Chi2,DepositVeto,individual,RelIsod0;//fiducial;//muonid,pTcut,isIso;
  Double_t LeptonRelIso,dxy,dz,D0,D0Error,D0Significance;
  Int_t numlep;
  Double_t pt_cut_min, pt_cut_max, eta_cut, relIso_cut, relIsoMIN_cut, chiNdof_cut, chiNdofMIN_cut, dxy_cut, dxyMIN_cut;
  Int_t casediscriminator,simpleselection;

  Double_t LeptonchiNdof;
  Lep();
  ~Lep();


  void LeptonSelection(Int_t Nlepton, Bool_t *Lepton_IsTracker, Double_t *Lepton_Eta, Double_t *Lepton_Pt, Double_t *Lepton_Px, Double_t *Lepton_Py, Double_t *Lepton_Pz, Double_t *Lepton_E, Double_t *Lepton_TrkIso, Double_t *Lepton_ECalIso, Double_t *Lepton_HCalIso, Double_t *Lepton_Charge, Double_t *Lepton_ECalIsoDeposit, Double_t *Lepton_HCalIsoDeposit, Int_t *Lepton_Gen_Mother, Double_t *Lepton_TrkValidHits, std::vector<Lepton>& leptonColl, Double_t rho, Bool_t *Lepton_IsGlobal=NULL, Double_t *Lepton_StandValidHits=NULL, Double_t *Lepton_GlobalChi2=NULL, Double_t *Lepton_GlobalNdof=NULL, Double_t *Lepton_Trkdx=NULL, Double_t *Lepton_Trkdy=NULL, Double_t *Lepton_Trkdz=NULL, Double_t *Lepton_TrkIPToolsIP=NULL, Double_t *Lepton_TrkIPToolsIPError=NULL, Double_t *Lepton_TrkIPToolsIPSignificance=NULL); 

  //void LeptonSelection(int Nlepton, bool *Lepton_IsTracker, Double_t *Lepton_Eta, Double_t *Lepton_Pt, Double_t *Lepton_Px, Double_t *Lepton_Py, Double_t *Lepton_Pz, Double_t *Lepton_E, Double_t *Lepton_TrkIso, Double_t *Lepton_ECalIso, Double_t *Lepton_HCalIso, Double_t *Lepton_Charge, Double_t *Lepton_ECalIsoDeposit, Double_t *Lepton_HCalIsoDeposit, Double_t *Lepton_Gen_Mother, Double_t *Lepton_TrkValidHits, std::vector<Lepton>& leptonColl, bool *Lepton_IsGlobal, Double_t *Lepton_StandValidHits, Double_t *Lepton_GlobalChi2, Double_t *Lepton_GlobalNdof, Double_t *Lepton_Trkdz_BS, Double_t *Lepton_Trkdxy_BS, Double_t *Lepton_TrkIPToolsIP, Double_t *Lepton_TrkIPToolsIPError, Double_t *Lepton_TrkIPToolsIPSignificance);

  void SetPt(Double_t minPt, Double_t maxPt);
  void SetPt(Double_t minPt);
  void SetEta(Double_t Eta);
  void SetRelIso(Double_t RelIso);
  void SetRelIso(Double_t RelIsoMIN, Double_t RelIso);
  void SetChiNdof(Double_t ChiNdof);
  void SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof);
  void SetBSdxy(Double_t dxy);
  void SetBSdxy(Double_t dxyMIN, Double_t dxy);
};

const Double_t Lep::AreaTrackerEl[2] = {0., 0.};         //   barrel/endcap
const Double_t Lep::AreaEcalEl[2]    = {0.101, 0.046};   //   barrel/endcap
const Double_t Lep::AreaHcalEl[2]    = {0.021 , 0.040}; //   barrel/endcap

#endif
