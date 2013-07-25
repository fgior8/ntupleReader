#include "LeptonSelection.h"

Lep::Lep() {}

Lep::~Lep() {}

void Lep::LeptonSelection(Int_t Nlepton, Bool_t *Lepton_IsTracker, Double_t *Lepton_Eta, Double_t *Lepton_Pt, Double_t *Lepton_Px, Double_t *Lepton_Py, Double_t *Lepton_Pz, Double_t *Lepton_E, Double_t *Lepton_TrkIso, Double_t *Lepton_ECalIso, Double_t *Lepton_HCalIso, Double_t *Lepton_Charge, Double_t *Lepton_ECalIsoDeposit, Double_t *Lepton_HCalIsoDeposit, Int_t *Lepton_Gen_Mother, Double_t *Lepton_TrkValidHits, std::vector<Lepton>& leptonColl, Double_t rho, Bool_t *Lepton_IsGlobal, Double_t *Lepton_StandValidHits, Double_t *Lepton_GlobalChi2, Double_t *Lepton_GlobalNdof, Double_t *Lepton_Trkdx, Double_t *Lepton_Trkdy, Double_t *Lepton_Trkdz, Double_t *Lepton_TrkIPToolsIP, Double_t *Lepton_TrkIPToolsIPError, Double_t *Lepton_TrkIPToolsIPSignificance) {
  casediscriminator = 999;
  Lepton_IsGlobal==NULL ? casediscriminator=0 : casediscriminator=1;
  //ilepton = leptonColl.size();

  Nlepton>20 ? numlep=20 : numlep=Nlepton;
  for (Int_t ilep=0; ilep<numlep; ilep++) {

    vLepton.SetPxPyPzE(Lepton_Px[ilep], Lepton_Py[ilep], Lepton_Pz[ilep], Lepton_E[ilep]);

    fakeType = Lepton::unknown;
    looseTight = Lepton::Other;
    if ( isPrompt((long)Lepton_Gen_Mother[ilep]) ) {
      if ( Lepton_Charge[ilep]*Lepton_Gen_Mother[ilep] == -24 || Lepton_Charge[ilep]*Lepton_Gen_Mother[ilep] == 15 ) 
	fakeType = Lepton::chargemisid;
      else
	fakeType = Lepton::notfake;
    }
    else {
      if ( nthdigit( abs((long)Lepton_Gen_Mother[ilep]),0 ) == 5 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),1 ) == 5 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),2 ) == 5)
        fakeType = Lepton::bjet;
	
      else if ( nthdigit( abs((long)Lepton_Gen_Mother[ilep]),0 ) == 4 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),1 ) == 4 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),2 ) == 4)
        fakeType = Lepton::cjet;
      
      else if (nthdigit( abs((long)Lepton_Gen_Mother[ilep]),0 ) == 1 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),1 ) == 1 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),2 ) == 1
            || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),0 ) == 2 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),1 ) == 2 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),2 ) == 2
            || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),0 ) == 3 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),1 ) == 3 || nthdigit( abs((long)Lepton_Gen_Mother[ilep]),2 ) == 3 )
        fakeType = Lepton::jet;
    }

    switch (casediscriminator) {
    case 0:
      leptonType = Lepton::Electron;
      individual = true;

      ifid = (fabs(Lepton_Eta[ilep]) < 1.479) ? 0 : 1;
      ElTkIso   = Lepton_TrkIso[ilep] - AreaTrackerEl[ifid] * rho;
      ElEcalIso = Lepton_ECalIso[ilep] - AreaEcalEl[ifid]  * rho;
      ElHcalIso = Lepton_HCalIso[ilep] - AreaHcalEl[ifid] * rho;

      if (Lepton_Pt[ilep] > 0.01)
	//LeptonRelIso =  (Lepton_HCalIso[ilep] + Lepton_ECalIso[ilep] + Lepton_TrkIso[ilep]) / max(Lepton_Pt[ilep], 20.);
        LeptonRelIso  = (ElTkIso+ElEcalIso+ElHcalIso)/Lepton_Pt[ilep];
      else LeptonRelIso = 9999.;

      LeptonchiNdof = 9999.;
      /*
      D0 = - ( - (Elec_Vx[ielec]-beamspot_x0) * Elec_Py[ielec] + (Elec_Vy[ielec]-beamspot_y0) * Elec_Px[ielec] ) / Elec_Pt[ielec];
      D0Error = sqrt( Elec_D0Error[ielec] * Elec_D0Error[ielec] + beamspot_BeamWidth * beamspot_BeamWidth );
      D0Significance = D0/D0Error;
      */

      if (D0Error < 1E-6) D0Error = 1E-6;

      (fabs(Lepton_Eta[ilep]) < eta_cut && Lepton_Pt[ilep] >= pt_cut_min && Lepton_Pt[ilep] < pt_cut_max) ? etaPt=true : etaPt =false;

      /// ***** TO BE FIXED ****** ///
      //(fabs(Lepton_Trkdxy_BS[ilep]) < BSdxy_cut && LeptonRelIso < relIso_cut && ( LeptonRelIso >= relIsoMIN_cut || fabs(Lepton_Trkdxy_BS[ilep]) >= BSdxyMIN_cut )) ? RelIsod0=true : RelIsod0=false;
      /// ***** TO BE FIXED ****** ///

      (LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0=true : RelIsod0=false;

      if (etaPt && RelIsod0) {
	leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Lepton_Eta[ilep], LeptonchiNdof, D0, D0Error, D0Significance, dxy, dz, Lepton_Charge[ilep], fakeType, looseTight, Lepton_TrkIso[ilep], LeptonRelIso) );

      };

      break;
    case 1:
      leptonType = Lepton::Muon;
      if (Lepton_Pt[ilep] > 0.01)
	LeptonRelIso = (Lepton_HCalIso[ilep] + Lepton_ECalIso[ilep] + Lepton_TrkIso[ilep]) / std::max(Lepton_Pt[ilep], 20.);
      else LeptonRelIso = 9999.;

      LeptonchiNdof = Lepton_GlobalChi2[ilep]/Lepton_GlobalNdof[ilep];
      
      dz = Lepton_Trkdz[ilep];
      dxy = sqrt(pow(Lepton_Trkdx[ilep],2)+pow(Lepton_Trkdy[ilep],2));
      D0 = fabs( Lepton_TrkIPToolsIP[ilep] );
      D0Error = Lepton_TrkIPToolsIPError[ilep];
      D0Significance = Lepton_TrkIPToolsIPSignificance[ilep];

      if (D0Error < 1E-6) D0Error = 1E-6;

      /*
	isIso = false;
	if (Lepton_Pt[ilep] > 30.) isIso = LeptonRelIso < 0.1;
	else isIso = Lepton_TrkIso[ilep] < 5.;
      */
      (Lepton_IsTracker[ilep]==1 && Lepton_IsGlobal[ilep]==1 && Lepton_TrkValidHits[ilep]>= 11 && Lepton_StandValidHits[ilep]>=1) ? individual = true :individual = false;

      (Lepton_HCalIsoDeposit[ilep]<=6 && Lepton_ECalIsoDeposit[ilep]<=4) ? DepositVeto=true : DepositVeto=false;

      (fabs(Lepton_Eta[ilep]) < eta_cut && Lepton_Pt[ilep] >= pt_cut_min && Lepton_Pt[ilep] < pt_cut_max) ? etaPt=true : etaPt =false;

      (LeptonchiNdof<chiNdof_cut && dxy < dxy_cut && LeptonRelIso < relIso_cut && ( LeptonRelIso >= relIsoMIN_cut || LeptonchiNdof>=chiNdofMIN_cut || dxy >= dxyMIN_cut )) ? RelIsod0Chi2=true : RelIsod0Chi2=false;


      if (etaPt && RelIsod0Chi2 && DepositVeto && individual) {
	leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Lepton_Eta[ilep], LeptonchiNdof, D0, D0Error, D0Significance, dxy, dz, Lepton_Charge[ilep], fakeType, looseTight, Lepton_TrkIso[ilep], LeptonRelIso) );
   
      }

      break;
      
    default:
      cout<<"Qualcosa non va, CAZZAROLA!!!"<<endl;
      break;
    }
    
  }
  
  std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );
}

void Lep::SetPt(Double_t minPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;
}

void Lep::SetPt(Double_t minPt, Double_t maxPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void Lep::SetEta(Double_t Eta) {
  Eta ? eta_cut=Eta : eta_cut=3.0;
}

void Lep::SetRelIso(Double_t RelIso) {
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
  relIsoMIN_cut=0.0;
}

void Lep::SetRelIso(Double_t RelIsoMIN, Double_t RelIso) {
  RelIsoMIN ? relIsoMIN_cut=RelIsoMIN : relIsoMIN_cut=0.0;
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
}

void Lep::SetChiNdof(Double_t ChiNdof) {
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
  chiNdofMIN_cut=0.0;
}

void Lep::SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof) {
  ChiNdofMIN ? chiNdofMIN_cut=ChiNdofMIN : chiNdofMIN_cut=0.0;
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
}

void Lep::SetBSdxy(Double_t dxy) {
   dxy ? dxy_cut=dxy : dxy_cut=2.0;
   dxyMIN_cut=0.0;
}

void Lep::SetBSdxy(Double_t dxyMIN, Double_t dxy) {
   dxyMIN ? dxyMIN_cut=dxyMIN : dxyMIN_cut=0.0;
   dxy ? dxy_cut=dxy : dxy_cut=2.0;
}
