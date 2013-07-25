#ifndef JetSelection_h
#define JetSelection_h

#include <iostream>
using namespace std;

#include "TLorentzVector.h"
#include <vector>
#include "Jet.h"
#include "Lepton.h"

class JJ {

  TLorentzVector vJet;
  Bool_t jetIsOK;
  Double_t pt_cut_min, pt_cut_max, eta_cut;
  
 public:
  JJ();
  ~JJ();
 
  void JetSelection(Int_t Njet, Bool_t *Jet_Id_loose, Double_t *Jet_Pt, Double_t *Jet_Px, Double_t *Jet_Py, Double_t *Jet_Pz, Double_t *Jet_E, Double_t *Jet_Eta, Double_t *Jet_neutralHadronEnergyFraction, Double_t *Jet_neutralEmEnergyFraction, Double_t *Jet_chargedHadronEnergyFraction, Int_t *Jet_chargedMultiplicity, Double_t *Jet_chargedEmEnergyFraction, Double_t *Jet_BTag_TkCountHighEff, std::vector<Jet>& jetColl);
  
  void JetSelectionLeptonVeto(Int_t Njet, Bool_t *Jet_Id_loose, Double_t *Jet_Pt, Double_t *Jet_Px, Double_t *Jet_Py, Double_t *Jet_Pz, Double_t *Jet_E, Double_t *Jet_Eta, Double_t *Jet_neutralHadronEnergyFraction, Double_t *Jet_neutralEmEnergyFraction, Double_t *Jet_chargedHadronEnergyFraction, Int_t *Jet_chargedMultiplicity, Double_t *Jet_chargedEmEnergyFraction, Double_t *Jet_BTag_TkCountHighEff, std::vector<Lepton>& leptonColl1, std::vector<Lepton>& leptonColl2, std::vector<Jet>& jetColl);

  void SetPt(Double_t minPt, Double_t maxPt);
  void SetPt(Double_t minPt);
  void SetEta(Double_t Eta);
 
};

#endif
