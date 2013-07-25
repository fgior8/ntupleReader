#ifndef DATA_CC
#define DATA_CC

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

#include "Data.h"

////////////////////////////////////////////////////
//             Member functions                   //
////////////////////////////////////////////////////

Data::Data()
{

   //Init(tree);

}

Data::~Data()
{
//   if (!fChain) return;
//   delete fChain->GetCurrentFile();
}

Int_t Data::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t Data::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Data::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) {std::cout << "tree pointer null\n"; return; }
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(0);

   //fChain->SetBranchAddress("Q", &Q, &b_Q);
   //fChain->SetBranchAddress("Q", Q, &b_Q);

   fChain->SetBranchAddress("NInteraction", &NInteraction);

   fChain->SetBranchAddress("EventAux_bx", &EventAux_bx);
   fChain->SetBranchAddress("EventAux_orbitNumber", &EventAux_orbitNumber);
   fChain->SetBranchAddress("EventAux_storeNumber", &EventAux_storeNumber);
   fChain->SetBranchAddress("EventAux_event", &EventAux_event);
   fChain->SetBranchAddress("EventAux_run", &EventAux_run);
   fChain->SetBranchAddress("EventAux_lumi", &EventAux_lumi);

   // HLT
   HLT_triggered = 0;
   fChain->SetBranchAddress("HLT_triggered",       &HLT_triggered);

   // Vertices
   fChain->SetBranchAddress("nVertex", &nVertex);
   fChain->SetBranchAddress("Vertex_sum_track_pt", Vertex_sum_track_pt);
   fChain->SetBranchAddress("Vertex_Chi2", Vertex_Chi2);
   fChain->SetBranchAddress("Vertex_Ndof", Vertex_Ndof);
   fChain->SetBranchAddress("Vertex_NormalizedChi2", Vertex_NormalizedChi2);
   fChain->SetBranchAddress("Vertex_X", Vertex_X);
   fChain->SetBranchAddress("Vertex_Y", Vertex_Y);
   fChain->SetBranchAddress("Vertex_Z", Vertex_Z);
   fChain->SetBranchAddress("Vertex_dX", Vertex_dX);
   fChain->SetBranchAddress("Vertex_dY", Vertex_dY);
   fChain->SetBranchAddress("Vertex_dZ", Vertex_dZ);
   fChain->SetBranchAddress("Vertex_isFake", Vertex_isFake);

   fChain->SetBranchAddress("HcalNoise_filterResult",&HcalNoise_filterResult);
   fChain->SetBranchAddress("HcalNoise_status",&HcalNoise_status);
   fChain->SetBranchAddress("HcalNoise_noiseType",&HcalNoise_noiseType);
   fChain->SetBranchAddress("HcalNoise_eventEMFraction",&HcalNoise_eventEMFraction);

   // Beamspot
   fChain->SetBranchAddress("beamspot_x0", &beamspot_x0);
   fChain->SetBranchAddress("beamspot_y0", &beamspot_y0);
   fChain->SetBranchAddress("beamspot_z0", &beamspot_z0);
   fChain->SetBranchAddress("beamspot_BeamWidth", &beamspot_BeamWidth);

   // Tracks
   fChain->SetBranchAddress("Ntrack", &Ntrack);
   fChain->SetBranchAddress("Track_Charge", Track_Charge);
   //for(unsigned int i = 0; i<50; i++) Track_Charge[i]=1;
   fChain->SetBranchAddress("Track_Pt", Track_Pt);
   fChain->SetBranchAddress("Track_Px", Track_Px);
   fChain->SetBranchAddress("Track_Py", Track_Py);
   fChain->SetBranchAddress("Track_Pz", Track_Pz);
   fChain->SetBranchAddress("Track_Phi", Track_Phi);
   fChain->SetBranchAddress("Track_Eta", Track_Eta);

   fChain->SetBranchAddress("Track_dxy_BS", Track_dxy_BS);
   fChain->SetBranchAddress("Track_dz_BS", Track_dz_BS);
   fChain->SetBranchAddress("Track_nValid", Track_nValid);

   fChain->SetBranchAddress("Track_trackIso", Track_trackIso);
   fChain->SetBranchAddress("Track_ecalIso", Track_ecalIso);
   fChain->SetBranchAddress("Track_hcalIso", Track_hcalIso);

   // Electrons
   fChain->SetBranchAddress("Nelec", &Nelec);
   fChain->SetBranchAddress("Elec_E", Elec_E);
   fChain->SetBranchAddress("Elec_Et", Elec_Et);
   fChain->SetBranchAddress("Elec_Pt", Elec_Pt);
   fChain->SetBranchAddress("Elec_Px", Elec_Px);
   fChain->SetBranchAddress("Elec_Py", Elec_Py);
   fChain->SetBranchAddress("Elec_Pz", Elec_Pz);
   fChain->SetBranchAddress("Elec_Eta", Elec_Eta);
   fChain->SetBranchAddress("Elec_supercluster_Eta", Elec_supercluster_Eta);
   fChain->SetBranchAddress("Elec_Phi", Elec_Phi);
   fChain->SetBranchAddress("Elec_Charge", Elec_Charge);

   fChain->SetBranchAddress("Elec_TrkIso", Elec_TrkIso);
   fChain->SetBranchAddress("Elec_ECalIso", Elec_ECalIso);
   fChain->SetBranchAddress("Elec_HCalIso", Elec_HCalIso);
   fChain->SetBranchAddress("Elec_chargedHadronIso", Elec_chargedHadronIso);
   fChain->SetBranchAddress("Elec_neutralHadronIso", Elec_neutralHadronIso);
   fChain->SetBranchAddress("Elec_photonIso", Elec_photonIso);
   fChain->SetBranchAddress("Elec_ECalIsoDeposit", Elec_ECalIsoDeposit);
   fChain->SetBranchAddress("Elec_HCalIsoDeposit", Elec_HCalIsoDeposit);
   //fChain->SetBranchAddress("Elec_AllIso", Elec_AllIso, &b_Elec_AllIso);

   fChain->SetBranchAddress("Elec_TrkChiNorm", Elec_TrkChiNorm);
   fChain->SetBranchAddress("Elec_HasTrack", Elec_HasTrack);
   fChain->SetBranchAddress("Elec_TrackPt", Elec_TrackPt);
   fChain->SetBranchAddress("Elec_TrackPx", Elec_TrackPx);
   fChain->SetBranchAddress("Elec_TrackPy", Elec_TrackPy);
   fChain->SetBranchAddress("Elec_TrackPz", Elec_TrackPz);
   fChain->SetBranchAddress("Elec_TrackCharge", Elec_TrackCharge);

   fChain->SetBranchAddress("Elec_dr03TkSumPt", Elec_dr03TkSumPt);
   fChain->SetBranchAddress("Elec_dr03EcalRecHitSumEt", Elec_dr03EcalRecHitSumEt);
   fChain->SetBranchAddress("Elec_dr03HcalTowerSumEt", Elec_dr03HcalTowerSumEt);

   fChain->SetBranchAddress("Elec_eidVeryLoose", Elec_eidVeryLoose);
   fChain->SetBranchAddress("Elec_eidLoose", Elec_eidLoose);
   fChain->SetBranchAddress("Elec_eidMedium", Elec_eidMedium);
   fChain->SetBranchAddress("Elec_eidTight", Elec_eidTight);
   fChain->SetBranchAddress("Elec_eidSuperTight", Elec_eidSuperTight);
   fChain->SetBranchAddress("Elec_eidHyperTight1", Elec_eidHyperTight1);
   fChain->SetBranchAddress("Elec_eidHyperTight2", Elec_eidHyperTight2);
   fChain->SetBranchAddress("Elec_eidHyperTight3", Elec_eidHyperTight3);
   fChain->SetBranchAddress("Elec_eidHyperTight4", Elec_eidHyperTight4);

   //fChain->SetBranchAddress("Elec_IdLoose", Elec_IdLoose);
   fChain->SetBranchAddress("Elec_IdTight", Elec_IdTight);
   fChain->SetBranchAddress("Elec_IdRobLoose", Elec_IdRobLoose);
   fChain->SetBranchAddress("Elec_IdRobTight", Elec_IdRobTight);
   fChain->SetBranchAddress("Elec_simpleEleId95cIso", Elec_simpleEleId95cIso);
   fChain->SetBranchAddress("Elec_simpleEleId90cIso", Elec_simpleEleId90cIso);
   fChain->SetBranchAddress("Elec_simpleEleId85cIso", Elec_simpleEleId85cIso);
   fChain->SetBranchAddress("Elec_simpleEleId80cIso", Elec_simpleEleId80cIso);
   fChain->SetBranchAddress("Elec_simpleEleId70cIso", Elec_simpleEleId70cIso);
   fChain->SetBranchAddress("Elec_simpleEleId60cIso", Elec_simpleEleId60cIso);
   fChain->SetBranchAddress("Elec_ChargeMode", Elec_ChargeMode);
   fChain->SetBranchAddress("Elec_PtMode", Elec_PtTrkMode);
   fChain->SetBranchAddress("Elec_QOverPErrTrkMode", Elec_QOverPErrTrkMode); // FIXME??? is anything actually broken here? - Arun 2010-05-18

   fChain->SetBranchAddress("Elec_CaloEnergy", Elec_CaloEnergy);
   fChain->SetBranchAddress("Elec_HOverE", Elec_HOverE);
   fChain->SetBranchAddress("Elec_Vx", Elec_Vx);
   fChain->SetBranchAddress("Elec_Vy", Elec_Vy);
   fChain->SetBranchAddress("Elec_Vz", Elec_Vz);
   fChain->SetBranchAddress("Elec_D0", Elec_D0);
   fChain->SetBranchAddress("Elec_dxy_bs", Elec_dxy_bs);
   //fChain->SetBranchAddress("Elec_D0Error", Elec_D0Error); // Version G
   fChain->SetBranchAddress("Elec_Dz", Elec_Dz);
   fChain->SetBranchAddress("Elec_PtTrk", Elec_PtTrk);
   fChain->SetBranchAddress("Elec_QOverPErrTrk", Elec_QOverPErrTrk);
   fChain->SetBranchAddress("Elec_LostHits", Elec_LostHits);
   fChain->SetBranchAddress("Elec_ValidHits", Elec_ValidHits);
   fChain->SetBranchAddress("Elec_NCluster", Elec_NCluster);
   fChain->SetBranchAddress("Elec_EtaTrk", Elec_EtaTrk);
   fChain->SetBranchAddress("Elec_PhiTrk", Elec_PhiTrk);
   fChain->SetBranchAddress("Elec_WidthClusterEta", Elec_WidthClusterEta);
   fChain->SetBranchAddress("Elec_WidthClusterPhi", Elec_WidthClusterPhi);
   fChain->SetBranchAddress("Elec_PinTrk", Elec_PinTrk);
   fChain->SetBranchAddress("Elec_PoutTrk", Elec_PoutTrk);
   // add Elec_NormChi2 if in LeptonAnalysis tree maker

   fChain->SetBranchAddress("Elec_Gen_PdgId", Elec_Gen_PdgId);
   fChain->SetBranchAddress("Elec_Gen_Mother", Elec_Gen_Mother);
   fChain->SetBranchAddress("Elec_Gen_Px", Elec_Gen_Px);
   fChain->SetBranchAddress("Elec_Gen_Py", Elec_Gen_Py);
   fChain->SetBranchAddress("Elec_Gen_Pz", Elec_Gen_Pz);
   //fChain->SetBranchAddress("Elec_isccElecAssoc", Elec_isccElecAssoc, &b_Elec_isccElecAssoc);

   //fChain->SetBranchAddress("Q", &Q, &b_Q);
   fChain->SetBranchAddress("rho", &rho);
   fChain->SetBranchAddress("Nmuon", &Nmuon);
   fChain->SetBranchAddress("Muon_E", Muon_E);
   fChain->SetBranchAddress("Muon_Et", Muon_Et);
   fChain->SetBranchAddress("Muon_Pt", Muon_Pt);
//   fChain->SetBranchAddress("Muon_PtErr", Muon_PtErr);
//   fChain->SetBranchAddress("Muon_PtPF", Muon_PtPF);
   fChain->SetBranchAddress("Muon_Px", Muon_Px);
   fChain->SetBranchAddress("Muon_Py", Muon_Py);
   fChain->SetBranchAddress("Muon_Pz", Muon_Pz);
   fChain->SetBranchAddress("Muon_Eta", Muon_Eta);
   fChain->SetBranchAddress("Muon_Phi", Muon_Phi);
   fChain->SetBranchAddress("Muon_Charge", Muon_Charge);

   fChain->SetBranchAddress("Muon_TrkIso", Muon_TrkIso);
   fChain->SetBranchAddress("Muon_ECalIso", Muon_ECalIso);
   fChain->SetBranchAddress("Muon_HCalIso", Muon_HCalIso);
   fChain->SetBranchAddress("Muon_chargedHadronIso", Muon_chargedHadronIso);
   fChain->SetBranchAddress("Muon_neutralHadronIso", Muon_neutralHadronIso);
   fChain->SetBranchAddress("Muon_photonIso", Muon_photonIso);
   fChain->SetBranchAddress("Muon_ECalIsoDeposit", Muon_ECalIsoDeposit);
   fChain->SetBranchAddress("Muon_HCalIsoDeposit", Muon_HCalIsoDeposit);
   //fChain->SetBranchAddress("Muon_AllIso", Muon_AllIso);

   fChain->SetBranchAddress("Muon_TrkChiNorm", Muon_TrkChiNorm);

   fChain->SetBranchAddress("Muon_IsGlobal", Muon_IsGlobal);
   fChain->SetBranchAddress("Muon_IsStandAlone", Muon_IsStandAlone);
   fChain->SetBranchAddress("Muon_IsTracker", Muon_IsTracker);

   fChain->SetBranchAddress("Muon_TrackerMuonArbitrated", Muon_TrackerMuonArbitrated);
   fChain->SetBranchAddress("Muon_AllArbitrated", Muon_AllArbitrated);
   fChain->SetBranchAddress("Muon_GlobalMuonPromptTight", Muon_GlobalMuonPromptTight);
   fChain->SetBranchAddress("Muon_TMLastStationLoose", Muon_TMLastStationLoose);
   fChain->SetBranchAddress("Muon_TMLastStationTight", Muon_TMLastStationTight);
   fChain->SetBranchAddress("Muon_TM2DCompatibilityLoose", Muon_TM2DCompatibilityLoose);
   fChain->SetBranchAddress("Muon_TM2DCompatibilityTight", Muon_TM2DCompatibilityTight);
   fChain->SetBranchAddress("Muon_TMOneStationLoose", Muon_TMOneStationLoose);
   fChain->SetBranchAddress("Muon_TMOneStationTight", Muon_TMOneStationTight);
   fChain->SetBranchAddress("Muon_TMLastStationOptimizedLowPtLoose", Muon_TMLastStationOptimizedLowPtLoose);
   fChain->SetBranchAddress("Muon_TMLastStationOptimizedLowPtTight", Muon_TMLastStationOptimizedLowPtTight);
   fChain->SetBranchAddress("Muon_GMTkChiCompatibility", Muon_GMTkChiCompatibility);
   fChain->SetBranchAddress("Muon_GMStaChiCompatibility", Muon_GMStaChiCompatibility);
   fChain->SetBranchAddress("Muon_GMTkKinkTight", Muon_GMTkKinkTight);
   fChain->SetBranchAddress("Muon_TMLastStationAngLoose", Muon_TMLastStationAngLoose);
   fChain->SetBranchAddress("Muon_TMLastStationAngTight", Muon_TMLastStationAngTight);
   //fChain->SetBranchAddress("Muon_TMOneStationAngLoose", Muon_TMOneStationAngLoose);
   //fChain->SetBranchAddress("Muon_TMOneStationAngTight", Muon_TMOneStationAngTight);
   fChain->SetBranchAddress("Muon_TMLastStationOptimizedBarrelLowPtLoose", Muon_TMLastStationOptimizedBarrelLowPtLoose);
   fChain->SetBranchAddress("Muon_TMLastStationOptimizedBarrelLowPtTight", Muon_TMLastStationOptimizedBarrelLowPtTight);

   fChain->SetBranchAddress("Muon_GlobalVx", Muon_GlobalVx);
   fChain->SetBranchAddress("Muon_GlobalVy", Muon_GlobalVy);
   fChain->SetBranchAddress("Muon_GlobalVz", Muon_GlobalVz);
   fChain->SetBranchAddress("Muon_GlobalD0", Muon_GlobalD0);
   fChain->SetBranchAddress("Muon_GlobalDz", Muon_GlobalDz);
   fChain->SetBranchAddress("Muon_GlobalChi2", Muon_GlobalChi2);
   fChain->SetBranchAddress("Muon_GlobalNdof", Muon_GlobalNdof);
   fChain->SetBranchAddress("Muon_Global_muonHits", Muon_Global_muonHits);

   fChain->SetBranchAddress("Muon_StandValidHits", Muon_StandValidHits);
   fChain->SetBranchAddress("Muon_StandLostHits", Muon_StandLostHits);
   fChain->SetBranchAddress("Muon_StandPt", Muon_StandPt);
   fChain->SetBranchAddress("Muon_StandPz", Muon_StandPz);
   fChain->SetBranchAddress("Muon_StandP", Muon_StandP);
   fChain->SetBranchAddress("Muon_StandEta", Muon_StandEta);
   fChain->SetBranchAddress("Muon_StandPhi", Muon_StandPhi);
   fChain->SetBranchAddress("Muon_StandCharge", Muon_StandCharge);
   fChain->SetBranchAddress("Muon_StandChi", Muon_StandChi);
   fChain->SetBranchAddress("Muon_StandQOverPError", Muon_StandQOverPError);

   fChain->SetBranchAddress("Muon_GlbValidTrkHits", Muon_GlbValidTrkHits); //FIXME
   fChain->SetBranchAddress("Muon_TrkValidHits", Muon_TrkValidHits);
   fChain->SetBranchAddress("Muon_TrkLostHits", Muon_TrkLostHits);
   fChain->SetBranchAddress("Muon_TrkPt", Muon_TrkPt);
   fChain->SetBranchAddress("Muon_TrkPz", Muon_TrkPz);
   fChain->SetBranchAddress("Muon_TrkP", Muon_TrkP);
   fChain->SetBranchAddress("Muon_Trkdxy_BS", Muon_Trkdxy_BS);
   fChain->SetBranchAddress("Muon_Trkdz_BS", Muon_Trkdz_BS);
   fChain->SetBranchAddress("Muon_TrkVx", Muon_TrkVx);
   fChain->SetBranchAddress("Muon_TrkVy", Muon_TrkVy);
   fChain->SetBranchAddress("Muon_TrkVz", Muon_TrkVz);
   fChain->SetBranchAddress("Muon_TrkEta", Muon_TrkEta);
   fChain->SetBranchAddress("Muon_TrkPhi", Muon_TrkPhi);
   fChain->SetBranchAddress("Muon_TrkChi", Muon_TrkChi);
   fChain->SetBranchAddress("Muon_TrkCharge", Muon_TrkCharge);
   fChain->SetBranchAddress("Muon_TrkQOverPError", Muon_TrkQOverPError);
   fChain->SetBranchAddress("Muon_TrkOuterZ", Muon_TrkOuterZ);
   fChain->SetBranchAddress("Muon_TrkOuterR", Muon_TrkOuterR);
   fChain->SetBranchAddress("Muon_TrkD0", Muon_TrkD0);
   fChain->SetBranchAddress("Muon_TrkD0Error", Muon_TrkD0Error);

   fChain->SetBranchAddress("Muon_pixelLayersWithMeas", Muon_pixelLayersWithMeas); //FIXME
   fChain->SetBranchAddress("Muon_pixelHits", Muon_pixelHits);
   fChain->SetBranchAddress("Muon_nMatches", Muon_nMatches);

   fChain->SetBranchAddress("Muon_TrkIPToolsIP", Muon_TrkIPToolsIP);
   fChain->SetBranchAddress("Muon_TrkIPToolsIPError", Muon_TrkIPToolsIPError);
   fChain->SetBranchAddress("Muon_TrkIPToolsIPSignificance", Muon_TrkIPToolsIPSignificance);

   fChain->SetBranchAddress("Muon_Gen_PdgId", Muon_Gen_PdgId);
   fChain->SetBranchAddress("Muon_Gen_Mother", Muon_Gen_Mother);
   fChain->SetBranchAddress("Muon_Gen_Px", Muon_Gen_Px);
   fChain->SetBranchAddress("Muon_Gen_Py", Muon_Gen_Py);
   fChain->SetBranchAddress("Muon_Gen_Pz", Muon_Gen_Pz);
   //fChain->SetBranchAddress("Muon__isccMuon_Assoc", Muon__isccMuon_Assoc);

   fChain->SetBranchAddress("Njet", &Njet);
   fChain->SetBranchAddress("Jet_E", Jet_E);
   fChain->SetBranchAddress("Jet_Et", Jet_Et);
   fChain->SetBranchAddress("Jet_Pt", Jet_Pt);
   fChain->SetBranchAddress("Jet_Px", Jet_Px);
   fChain->SetBranchAddress("Jet_Py", Jet_Py);
   fChain->SetBranchAddress("Jet_Pz", Jet_Pz);
   fChain->SetBranchAddress("Jet_Eta", Jet_Eta);
   fChain->SetBranchAddress("Jet_Phi", Jet_Phi);
   fChain->SetBranchAddress("Jet_vx", Jet_vx);
   fChain->SetBranchAddress("Jet_vy", Jet_vy);
   fChain->SetBranchAddress("Jet_vz", Jet_vz);
   fChain->SetBranchAddress("Jet_Id_minimal", Jet_Id_minimal);
   fChain->SetBranchAddress("Jet_Id_loose_aod", Jet_Id_loose_aod);
   fChain->SetBranchAddress("Jet_Id_loose", Jet_Id_loose);
   fChain->SetBranchAddress("Jet_Id_tight", Jet_Id_tight);
   fChain->SetBranchAddress("Jet_Fem", Jet_Fem);
   fChain->SetBranchAddress("Jet_fHPD", Jet_fHPD);
   fChain->SetBranchAddress("Jet_fRBX", Jet_fRBX);
   fChain->SetBranchAddress("Jet_hitsInN90", Jet_hitsInN90);
   fChain->SetBranchAddress("Jet_neutralEmEnergyFraction",    Jet_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jet_neutralHadronEnergyFraction",Jet_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("Jet_chargedMultiplicity",        Jet_chargedMultiplicity);
   fChain->SetBranchAddress("Jet_chargedEmEnergyFraction",    Jet_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jet_chargedHadronEnergyFraction",Jet_chargedHadronEnergyFraction);

   //fChain->SetBranchAddress("Jet_Hemi", Jet_Hemi, &b_Jet_Hemi);
   fChain->SetBranchAddress("Jet_MCcorrFactor", Jet_MCcorrFactor);
   fChain->SetBranchAddress("Jet_JPTcorrFactor", Jet_JPTcorrFactor);

   fChain->SetBranchAddress("Jet_BTag_TCHE", Jet_BTag_TCHE);
   fChain->SetBranchAddress("Jet_BTag_TCHP", Jet_BTag_TCHP);
   fChain->SetBranchAddress("Jet_BTag_jetProb", Jet_BTag_jetProb);
   fChain->SetBranchAddress("Jet_BTag_jetBProb", Jet_BTag_jetBProb);
   fChain->SetBranchAddress("Jet_BTag_SSVHE", Jet_BTag_SSVHE);
   fChain->SetBranchAddress("Jet_BTag_SSVHP", Jet_BTag_SSVHP);
   fChain->SetBranchAddress("Jet_BTag_CSV", Jet_BTag_CSV);
   fChain->SetBranchAddress("Jet_BTag_CSVMVA", Jet_BTag_CSVMVA);
   fChain->SetBranchAddress("Jet_BTag_SoftLepton", Jet_BTag_SoftLepton);
   fChain->SetBranchAddress("Jet_BTag_SoftLeptonByIP", Jet_BTag_SoftLeptonByIP);
   fChain->SetBranchAddress("Jet_BTag_SoftLeptonByPt", Jet_BTag_SoftLeptonByPt);

/*   fChain->SetBranchAddress("Jet_uncplus", Jet_uncplus); //FIXME
   fChain->SetBranchAddress("Jet_uncminus", Jet_uncminus); //FIXME
   fChain->SetBranchAddress("Jet_uncorr_E", Jet_uncorr_E); //FIXME
   fChain->SetBranchAddress("Jet_uncorr_Pt", Jet_uncorr_Pt); //FIXME
   fChain->SetBranchAddress("Jet_uncorr_Px", Jet_uncorr_Px); //FIXME
   fChain->SetBranchAddress("Jet_uncorr_Py", Jet_uncorr_Py); //FIXME
   fChain->SetBranchAddress("Jet_uncorr_Pz", Jet_uncorr_Pz); //FIXME
*/
   fChain->SetBranchAddress("Jet_Gen_E", Jet_Gen_E);
   fChain->SetBranchAddress("Jet_Gen_Et", Jet_Gen_Et);
   fChain->SetBranchAddress("Jet_Gen_Pt", Jet_Gen_Pt);
   fChain->SetBranchAddress("Jet_Gen_Px", Jet_Gen_Px);
   fChain->SetBranchAddress("Jet_Gen_Py", Jet_Gen_Py);
   fChain->SetBranchAddress("Jet_Gen_Pz", Jet_Gen_Pz);
   fChain->SetBranchAddress("Jet_Gen_Eta", Jet_Gen_Eta);
   fChain->SetBranchAddress("Jet_Gen_Phi", Jet_Gen_Phi);

   fChain->SetBranchAddress("Jet_PartonFlavour", Jet_PartonFlavour);
   fChain->SetBranchAddress("Jet_Parton_Id", Jet_Parton_Id);
   fChain->SetBranchAddress("Jet_Parton_Mother", Jet_Parton_Mother);
   fChain->SetBranchAddress("Jet_Parton_Px", Jet_Parton_Px);
   fChain->SetBranchAddress("Jet_Parton_Py", Jet_Parton_Py);
   fChain->SetBranchAddress("Jet_Parton_Pz", Jet_Parton_Pz);
   fChain->SetBranchAddress("Jet_Parton_Et", Jet_Parton_Et);
   fChain->SetBranchAddress("Jet_Parton_E", Jet_Parton_E);
   fChain->SetBranchAddress("Jet_Parton_Phi", Jet_Parton_Phi);
   fChain->SetBranchAddress("Jet_Parton_Eta", Jet_Parton_Eta);

   fChain->SetBranchAddress("Jet_TrackPt", Jet_TrackPt);
   fChain->SetBranchAddress("Jet_TrackPhi", Jet_TrackPhi);
   fChain->SetBranchAddress("Jet_TrackPhiWeighted", Jet_TrackPhiWeighted);
   fChain->SetBranchAddress("Jet_TrackNo", Jet_TrackNo);

   MET_algoStringVector = 0;
   fChain->SetBranchAddress("MET_Nalgo",            &MET_Nalgo);
   fChain->SetBranchAddress("MET_algoStringVector", &MET_algoStringVector);
   fChain->SetBranchAddress("MET_fullcorr_nocc",     MET_fullcorr_nocc);
   fChain->SetBranchAddress("MET_fullcorr_nocc_significance", MET_fullcorr_nocc_significance);
   fChain->SetBranchAddress("MET_uncorrALL_nocc",    MET_uncorrALL_nocc);
   fChain->SetBranchAddress("MET_uncorrJES_nocc",    MET_uncorrJES_nocc);
   fChain->SetBranchAddress("MET_uncorrMUON_nocc",   MET_uncorrMUON_nocc);
   fChain->SetBranchAddress("MET_gen", MET_gen);

   fChain->SetBranchAddress("genN", &genN);
   fChain->SetBranchAddress("genId", genId);
   fChain->SetBranchAddress("genMotherRef", genMotherRef);
   fChain->SetBranchAddress("genE", genE);
   fChain->SetBranchAddress("genPx", genPx);
   fChain->SetBranchAddress("genPy", genPy);
   fChain->SetBranchAddress("genPz", genPz);
   fChain->SetBranchAddress("genStatus", genStatus);

   fChain->SetBranchAddress("genLepN", &genLepN);
   fChain->SetBranchAddress("genLepId", genLepId);
   fChain->SetBranchAddress("genLepMotherRef", genLepMotherRef);
   fChain->SetBranchAddress("genLepE", genLepE);
   fChain->SetBranchAddress("genLepPx", genLepPx);
   fChain->SetBranchAddress("genLepPy", genLepPy);
   fChain->SetBranchAddress("genLepPz", genLepPz);
   fChain->SetBranchAddress("genLepStatus", genLepStatus);
 
   nentries = fChain->GetEntries();
   cout << "Entries " <<nentries<< endl;

   Notify();
}

void Data::setBranchStatus(void) {

  fChain->SetBranchStatus("*",1);

}

Bool_t Data::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Data::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

/*
void Data::initPdgIdIndices(void) {
  int pdgToIndex[1000];
  std::map<long, bool> pdgToIndex;
  typedef std:pair<long, bool> longboolpair;
  if (    int nthdigit(int x, int n);
)
  pdgToIndex.insert(logboolpair(23,true));
  pdgToIndex.insert(logboolpair(24,true));
  pdgToIndex.insert(logboolpair(25,true));
  pdgToIndex.insert(logboolpair(35,true));
  pdgToIndex.insert(logboolpair(36,true));
  pdgToIndex.insert(logboolpair(37,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
  pdgToIndex.insert(logboolpair(,true));
}
*/




#endif

