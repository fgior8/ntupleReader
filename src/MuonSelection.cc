#include "MuonSelection.h"

MuonSel::MuonSel() {};


MuonSel::~MuonSel() {};

void MuonSel::MuonSelection(Int_t Nlepton, Bool_t *Lepton_IsTracker, Double_t *Lepton_Eta, Double_t *Lepton_Pt, Double_t *Lepton_PtErr, Double_t *Lepton_Px, Double_t *Lepton_Py, Double_t *Lepton_Pz, Double_t *Lepton_E, Double_t *Lepton_TrkIso, Double_t *Lepton_ECalIso, Double_t *Lepton_HCalIso, Double_t *Lepton_Charge, Double_t *Lepton_ECalIsoDeposit, Double_t *Lepton_HCalIsoDeposit, Int_t *Lepton_Gen_Mother, Int_t *Lepton_TrkValidHits, std::vector<Lepton>& leptonColl, bool *Lepton_IsGlobal, Double_t *Lepton_StandValidHits, Double_t *Lepton_GlobalChi2, Double_t *Lepton_GlobalNdof, Double_t *Lepton_Trkdx, Double_t *Lepton_Trkdy, Double_t *Lepton_Trkdz, Double_t *Lepton_TrkIPToolsIP, Double_t *Lepton_TrkIPToolsIPError, Double_t *Lepton_TrkIPToolsIPSignificance, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, Double_t rho) {
  //ilepton = leptonColl.size();
  dz_cut=0.1;
  Nlepton>20 ? numlep=20 : numlep=Nlepton;

  for (Int_t ilep=0; ilep<numlep; ilep++) {

    LeptonchiNdof = Lepton_GlobalChi2[ilep]/Lepton_GlobalNdof[ilep];  
    dz = Lepton_Trkdz[ilep];
    dxy = sqrt(pow(Lepton_Trkdx[ilep],2)+pow(Lepton_Trkdy[ilep],2));
    D0 = fabs( Lepton_TrkIPToolsIP[ilep] );
    D0Error = Lepton_TrkIPToolsIPError[ilep];
    D0Significance = Lepton_TrkIPToolsIPSignificance[ilep];

   
    // RHO
    // = (fabs(Muon_Eta[imuon]) < 1.479) ? 0 : 1;    //we distinguish beetwen EB and EE and HB and HE

    if (fabs(Lepton_Eta[ilep]) < 0.5) ifid=0;
    else if (fabs(Lepton_Eta[ilep]) >= 0.5 && fabs(Lepton_Eta[ilep]) < 1.0) ifid=1;
    else if (fabs(Lepton_Eta[ilep]) >= 1.0 && fabs(Lepton_Eta[ilep]) < 1.5) ifid=2;
    else if (fabs(Lepton_Eta[ilep]) >= 1.5 && fabs(Lepton_Eta[ilep]) < 2.0) ifid=3;
    else if (fabs(Lepton_Eta[ilep]) >= 2.0 && fabs(Lepton_Eta[ilep]) < 2.5) ifid=4;
    else ifid=-1;

    MuTkIso   = Lepton_TrkIso[ilep] - AreaTrackerMu[ifid] * rho;
    MuEcalIso = Lepton_ECalIso[ilep] - AreaEcalMu[ifid]  * rho;
    MuHcalIso = Lepton_HCalIso[ilep] - AreaHcalMu[ifid] * rho;
    
    vLepton.SetPxPyPzE(Lepton_Px[ilep], Lepton_Py[ilep], Lepton_Pz[ilep], Lepton_E[ilep]);

    fakeType = Lepton::unknown;
    looseTight = Lepton::Other;
    leptonType = Lepton::Muon;

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
 
    if (Lepton_Pt[ilep] > 0.01)
      //LeptonRelIso = (Lepton_HCalIso[ilep] + Lepton_ECalIso[ilep] + Lepton_TrkIso[ilep]) / std::max(Lepton_Pt[ilep], 20.);
      LeptonRelIso  = (MuTkIso+MuEcalIso+MuHcalIso)/Lepton_Pt[ilep];
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;
    
    if (D0Error < 1E-6) D0Error = 1E-6;


    (Lepton_IsTracker[ilep]==1 && Lepton_IsGlobal[ilep]==1 && Lepton_TrkValidHits[ilep]>= 11 && Lepton_StandValidHits[ilep]>=1) ? individual = true :individual = false;

    (Lepton_HCalIsoDeposit[ilep]<=6 && Lepton_ECalIsoDeposit[ilep]<=4) ? DepositVeto=true : DepositVeto=false;

    (fabs(Lepton_Eta[ilep]) < eta_cut && Lepton_Pt[ilep] >= pt_cut_min && Lepton_Pt[ilep] < pt_cut_max && Lepton_PtErr[ilep]/Lepton_Pt[ilep]<=0.10) ? etaPt=true : etaPt =false;
    
    Vz = Vertex_Z;
    Vxy = sqrt(pow(Vertex_X,2)+pow(Vertex_Y,2));

    //(LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || LeptonchiNdof>=chiNdofMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    //(LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    (LeptonchiNdof<chiNdof_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0Chi2=true : RelIsod0Chi2=false; 

    if (etaPt && RelIsod0Chi2 && DepositVeto && individual)
      leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Lepton_Eta[ilep], LeptonchiNdof, D0, D0Error, D0Significance, dxy, dz, Lepton_Charge[ilep], fakeType, looseTight, Lepton_TrkIso[ilep], LeptonRelIso) );
    
  }
  
  std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );
  
}
