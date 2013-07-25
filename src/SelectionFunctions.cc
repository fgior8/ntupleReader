#include "SelectionFunctions.h"

Bool_t isGoodEvent(Int_t nVertex, Double_t *Vertex_Ndof, Double_t *Vertex_X, Double_t *Vertex_Y, Double_t *Vertex_Z, Double_t beamspot_x, Double_t beamspot_y, Bool_t *goodVerticies) {
  if (nVertex>0) { 
    if (nVertex>50) {
      //cout<<"nVertex "<<nVertex<<endl;
      nVertex=50;
    }
    for (Int_t i=0; i<nVertex; i++) {
      if ( Vertex_Ndof[i]>4 && fabs(Vertex_Z[i])<=24 && fabs(sqrt(pow(Vertex_X[i],2)+pow(Vertex_Y[i],2))-sqrt(pow(beamspot_x,2)+pow(beamspot_y,2)))<=2 ) {
	goodVerticies[i] = true;
	return true;
      }
      else {
	goodVerticies[i] = false;
      }
    }
    return false;
  }
  else
    return false;
}

Bool_t Zselection(std::vector<Lepton>& leptonColl, Double_t MET) {
  Double_t mass=0;
  Double_t temp_mass=0;
  if (leptonColl.size()==2) {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
      for(UInt_t j=i+1; j<leptonColl.size(); j++) {
        if ( leptonColl[i].charge() != leptonColl[j].charge() ) {
          temp_mass = (leptonColl[i].lorentzVec() + leptonColl[j].lorentzVec()).M();
          if ( fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z) )
            mass=temp_mass;
        }
      }
    if ( MET < 20 && mass > (Mass_Z-20) && mass < (Mass_Z+20) )
      return true;
    else
      return false;
  }
  else
    return false;
}


Bool_t ZandWveto(std::vector<Lepton>& leptonColl, Double_t MET, Double_t METx, Double_t METy) {
  Double_t mass=0;
  Double_t temp_mass=0;
  Double_t MT=0;
  if (leptonColl.size()>0) { 
    MT = sqrt(2.*(leptonColl[0].lorentzVec().Pt()*MET - leptonColl[0].lorentzVec().Px()*METx - leptonColl[0].lorentzVec().Py()*METy));
    if (leptonColl.size()>=2) {
      for (UInt_t i=0; i<leptonColl.size()-1; i++)
	for(UInt_t j=i+1; j<leptonColl.size(); j++) {
	  if ( leptonColl[i].charge() != leptonColl[j].charge() && leptonColl[i].lorentzVec().Pt()>20 && leptonColl[j].lorentzVec().Pt()>20) {
	    temp_mass = (leptonColl[i].lorentzVec() + leptonColl[j].lorentzVec()).M();
	    if ( fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z) ) 
	      mass=temp_mass;
	  }
	}
    } 
    if ( MET < 20 && MT < 20 && (mass < (Mass_Z-20) || mass > (Mass_Z+20) ) )
      return false;
    else
      return true;
  }
  else
    return true;
}
