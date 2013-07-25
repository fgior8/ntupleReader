#include "JetSelection.h"

JJ::JJ() { }
JJ::~JJ() { }

void JJ::JetSelection (Int_t Njet, Bool_t *Jet_Id_loose, Double_t *Jet_Pt, Double_t *Jet_Px, Double_t *Jet_Py, Double_t *Jet_Pz, Double_t *Jet_E, Double_t *Jet_Eta, Double_t *Jet_neutralHadronEnergyFraction, Double_t *Jet_neutralEmEnergyFraction, Double_t *Jet_chargedHadronEnergyFraction, Int_t *Jet_chargedMultiplicity, Double_t *Jet_chargedEmEnergyFraction, Double_t *Jet_BTag_TkCountHighEff, std::vector<Jet>& jetColl) {
  if (Njet > 30) Njet = 30;
  for (Int_t ijet = 0; ijet < Njet; ++ijet) {


    if (Jet_Pt[ijet] >= pt_cut_min && Jet_Pt[ijet] < pt_cut_max && 
	fabs(Jet_Eta[ijet]) < eta_cut
        && Jet_Id_loose[ijet]
        && Jet_neutralHadronEnergyFraction[ijet] < 0.99
        && Jet_neutralEmEnergyFraction[ijet] < 0.99
        //&& Jet_hitsInN90[ijet] > 1
      && ( fabs( Jet_Eta[ijet] ) > 2.4 || ( Jet_chargedHadronEnergyFraction[ijet] > 0. && Jet_chargedMultiplicity[ijet] > 0. && Jet_chargedEmEnergyFraction[ijet] < 0.99 ) ) ) {
      //std::cout << "                             PASS\n";
      TLorentzVector vJet11(Jet_Px[ijet], Jet_Py[ijet], Jet_Pz[ijet], Jet_E[ijet]);
      jetColl.push_back( Jet(vJet11, (Double_t)Jet_BTag_TkCountHighEff[ijet], (unsigned int) ijet) );
    }
  }
}

void JJ::JetSelectionLeptonVeto(Int_t Njet, Bool_t *Jet_Id_loose, Double_t *Jet_Pt, Double_t *Jet_Px, Double_t *Jet_Py, Double_t *Jet_Pz, Double_t *Jet_E, Double_t *Jet_Eta, Double_t *Jet_neutralHadronEnergyFraction, Double_t *Jet_neutralEmEnergyFraction, Double_t *Jet_chargedHadronEnergyFraction, Int_t *Jet_chargedMultiplicity, Double_t *Jet_chargedEmEnergyFraction, Double_t *Jet_BTag_TkCountHighEff, std::vector<Lepton>& leptonColl1, std::vector<Lepton>& leptonColl2, std::vector<Jet>& jetColl) {
  std::vector<Jet> pre_jetColl;
  if (Njet > 30) Njet = 30; 

  for (Int_t ijet = 0; ijet < Njet; ijet++) {

    if (Jet_Pt[ijet] >= pt_cut_min && Jet_Pt[ijet] < pt_cut_max && 
	fabs(Jet_Eta[ijet]) < eta_cut
	&& Jet_Id_loose[ijet]
	&& Jet_neutralHadronEnergyFraction[ijet] < 0.99
	&& Jet_neutralEmEnergyFraction[ijet] < 0.99
	//&& Jet_hitsInN90[ijet] > 1
	&& ( fabs( Jet_Eta[ijet] ) > 2.4 || ( Jet_chargedHadronEnergyFraction[ijet] > 0. && Jet_chargedMultiplicity[ijet] > 0. && Jet_chargedEmEnergyFraction[ijet] < 0.99 ) ) ) {
      
      TLorentzVector vJet11(Jet_Px[ijet], Jet_Py[ijet], Jet_Pz[ijet], Jet_E[ijet]);
      pre_jetColl.push_back( Jet(vJet11, (Double_t)Jet_BTag_TkCountHighEff[ijet], (unsigned int) ijet) );
    }
  }

  for (unsigned int ijet = 0; ijet < pre_jetColl.size(); ijet++) {
    jetIsOK = true;
    for (unsigned int ilep = 0; ilep < leptonColl1.size(); ilep++) {
      if (leptonColl1[ilep].leptonType()==Lepton::Muon)
	if (leptonColl1[ilep].lorentzVec().DeltaR( pre_jetColl[ijet].lorentzVec() ) < 0.4) {
	  jetIsOK = false;
	  ilep = leptonColl1.size();
	}
    }
    for (unsigned int ilep = 0; ilep < leptonColl2.size(); ilep++) {
      if (leptonColl2[ilep].leptonType()==Lepton::Electron)
	if (leptonColl2[ilep].lorentzVec().DeltaR( pre_jetColl[ijet].lorentzVec() ) < 0.4 
	    //&& Elec_IdRobTight[ leptonColl[ilep].ilepton() ] && leptonColl[ilep].relIso() < 0.15 
	    ) {
	  jetIsOK = false;
	  ilep = leptonColl2.size();
	}
    }
    
    if (jetIsOK)
      jetColl.push_back( pre_jetColl[ijet] );
  }
}

void JJ::SetPt(Double_t minPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;
}

void JJ::SetPt(Double_t minPt, Double_t maxPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void JJ::SetEta(Double_t Eta) {
  Eta ? eta_cut=Eta : eta_cut=3.0;
}
