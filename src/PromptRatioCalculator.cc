#include "PromptRatioCalculator.h"

PRCalculator::PRCalculator() {

  int nintpT = 4;
  double arraypT[] = {10,15,20,25,35};
  int ninteta = 4;
  double arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  h_nEvents = new TH2F ("h_nEvents", "Number of Events",ninteta,arrayeta,nintpT,arraypT);
  h_nEventsPR = new TH2F ("h_nEventsPR", "Number of Events PR",ninteta,arrayeta,nintpT,arraypT);
  h_PRrate = new TH2F ("h_PRrate", "Prompt ratio",ninteta,arrayeta,nintpT,arraypT);

}
PRCalculator::~PRCalculator() {

  outfile->cd();
  Dir = outfile->mkdir("Muons");
  outfile->cd( Dir->GetName() );
  h_muons->Write();
  h_MuonMET->Write();
  outfile->cd();

  Dir = outfile->mkdir("Electrons");
  outfile->cd( Dir->GetName() );
  h_electrons->Write();
  outfile->cd();
  
  Dir = outfile->mkdir("Jets with veto");
  outfile->cd( Dir->GetName() );
  h_jets->Write();
  outfile->cd();

  h_prova->Write();
  h_singlefake->Write();
  h_doublefake->Write();
  h_LeptvsVert->Write();
  h_nVertex->Write();

  h_PRrate->Write();
  h_nEventsPR->Write();
  h_nEvents->Write();
 
  outfile->Close();

}

void PRCalculator::LoopPR() {
 
  if(!weight) weight=1;

  if (fChain == 0) 
    cout << "Ciao!" << endl;
//  cout << "Do you want limited events?" <<endl;
//  cin >>entrieslimit;
//  if (entrieslimit != -1)
//    nentries=entrieslimit;
//  nentries=5000000;
  std::set<int> runs;
  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {

    // event skips fo di-muons
    //if (jentry == 25462350) jentry += 20;

    if (!(jentry % 1000))
      cout << jentry <<endl;
    if ( runs.find(EventAux_run) == runs.end() ) {
      cout << EventAux_run <<endl;
      runs.insert(EventAux_run);
    }

    fChain->GetEntry(jentry);

    if (
//      !trig("HLT_Mu5_v3") && !trig("HLT_Mu5_v4") && !trig("HLT_Mu5_v5") && !trig("HLT_Mu5_v6") && !trig("HLT_Mu5_v7") && !trig("HLT_Mu5_v8") && !trig("HLT_Mu5_v9") && !trig("HLT_Mu5_v10") && !trig("HLT_Mu5_v11") && !trig("HLT_Mu5_v12") && !trig("HLT_Mu5_v13") &&
        !trig("HLT_Mu8_v1") && !trig("HLT_Mu8_v2") && !trig("HLT_Mu8_v3") && !trig("HLT_Mu8_v4") && !trig("HLT_Mu8_v5") && !trig("HLT_Mu8_v6") && !trig("HLT_Mu8_v7") && !trig("HLT_Mu8_v8") && !trig("HLT_Mu8_v9") && !trig("HLT_Mu8_v10") && !trig("HLT_Mu8_v11") &&
        !trig("HLT_Mu8_Jet40_v3") && !trig("HLT_Mu8_Jet40_v4") && !trig("HLT_Mu8_Jet40_v5") && !trig("HLT_Mu8_Jet40_v6") && !trig("HLT_Mu8_Jet40_v7") && !trig("HLT_Mu8_Jet40_v8") && !trig("HLT_Mu8_Jet40_v9") && !trig("HLT_Mu8_Jet40_v10") && !trig("HLT_Mu8_Jet40_v11") && !trig("HLT_Mu8_Jet40_v12") && !trig("HLT_Mu8_Jet40_v13") && !trig("HLT_Mu8_Jet40_v14") &&
//        !trig("HLT_Mu12_v1") && !trig("HLT_Mu12_v2") && !trig("HLT_Mu12_v3") && !trig("HLT_Mu12_v4") && !trig("HLT_Mu12_v5") && !trig("HLT_Mu12_v6") && !trig("HLT_Mu12_v7") && !trig("HLT_Mu12_v8") && !trig("HLT_Mu12_v9") && !trig("HLT_Mu12_v10") && !trig("HLT_Mu12_v11") &&
        !trig("HLT_Mu15_v2") && !trig("HLT_Mu15_v3") && !trig("HLT_Mu15_v4") && !trig("HLT_Mu15_v5") && !trig("HLT_Mu15_v6") && !trig("HLT_Mu15_v7") && !trig("HLT_Mu15_v8") && !trig("HLT_Mu15_v9") && !trig("HLT_Mu15_v10") && !trig("HLT_Mu15_v11") && !trig("HLT_Mu15_v12")
//        !trig("HLT_Mu30_v1") && !trig("HLT_Mu30_v2") && !trig("HLT_Mu30_v3") && !trig("HLT_Mu30_v4") && !trig("HLT_Mu30_v5") && !trig("HLT_Mu30_v6") && !trig("HLT_Mu30_v7") && !trig("HLT_Mu30_v8") && !trig("HLT_Mu30_v9") && !trig("HLT_Mu30_v10") && !trig("HLT_Mu30_v11")
    ) continue;

    goodVerticies = new Bool_t [nVertex];
    if ( !isGoodEvent(nVertex, Vertex_Ndof, Vertex_X, Vertex_Y, Vertex_Z, beamspot_x0, beamspot_y0, goodVerticies) ) continue;

    for(Int_t vv=0; vv<nVertex; vv++) {
      if(goodVerticies[vv]) {
        VertexN=vv;
        break;
      }
    }

    ///////////////////////
    //       MET         //
    ///////////////////////

    for (Int_t yy = 0; yy < MET_Nalgo; yy++)
    {
      //cout<<(*MET_algoStringVector)[yy]<<endl;
      if ((*MET_algoStringVector)[yy] == "patMETsPF")
      {
        METx = MET_fullcorr_nocc[yy][0];
        METy = MET_fullcorr_nocc[yy][1];
        //pfmetsig = MET_fullcorr_nocc_significance[yy];
        //genMETx = MET_gen[yy][0];
        //genMETy = MET_gen[yy][1];
      }
    }

    MET = sqrt( METx*METx + METy*METy );
    ///// MUON COLLECTON FOR Z/W VETO /////    

    std::vector<Lepton> muonLooseColl;
    MuonLoose.SetPt(10); MuonLoose.SetEta(2.4); MuonLoose.SetRelIso(0.40); MuonLoose.SetChiNdof(10); MuonLoose.SetBSdxy(0.01);
    MuonLoose.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonLooseColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    if (!Zselection(muonLooseColl, MET)) continue;

    ///// SOME STANDARD PLOTS/////
    if (muonLooseColl.size() > 0) {
      for (UInt_t i=0; i<muonLooseColl.size(); i++) {
        UInt_t index=muonLooseColl[i].ilepton();
        h_muons->Fill(Nmuon, Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], muonLooseColl[i].dxy_BS(), rho);
        h_MuonMET->Fill(MET);
      }
    }
 
    ///// STARTING WITH COLLECTIONS NEEDED FOR THE FAKERATE /////

    //cout << "Event number " <<jentry<< endl;
    std::vector<Lepton> muonTightColl;
    MuonTight.SetPt(10); MuonTight.SetEta(2.4); MuonTight.SetRelIso(0.10); MuonTight.SetChiNdof(10); MuonTight.SetBSdxy(0.01);
    MuonTight.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonTightColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    std::vector<Lepton> muonTagColl;
    MuonTag.SetPt(10); MuonTag.SetEta(2.4); MuonTag.SetRelIso(0.10); MuonTag.SetChiNdof(10); MuonTag.SetBSdxy(0.01);
    MuonTag.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonTagColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    std::vector<Lepton> muonLooseButNotTightColl;
    MuonLooseButNotTight.SetPt(10); MuonLooseButNotTight.SetEta(2.4); MuonLooseButNotTight.SetRelIso(0.10,0.4); MuonLooseButNotTight.SetChiNdof(10); MuonLooseButNotTight.SetBSdxy(0.01);
    MuonLooseButNotTight.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonLooseButNotTightColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    std::vector<Lepton> electronColl;
    Electron.SetPt(10); Electron.SetEta(2.4); Electron.SetRelIso(0.15);
    Electron.LeptonSelection(Nelec, Elec_HasTrack, Elec_Eta, Elec_Pt, Elec_Px, Elec_Py, Elec_Pz, Elec_E, Elec_TrkIso, Elec_ECalIso, Elec_HCalIso, Elec_Charge, Elec_ECalIsoDeposit, Elec_HCalIsoDeposit, Elec_Gen_Mother, Elec_ValidHits, electronColl, rho);
    if (electronColl.size() >0)
      for (UInt_t i=0; i<electronColl.size(); i++) {
        index=electronColl[i].ilepton();
        h_electrons->Fill(Nelec, Elec_Pt[index], Elec_Eta[index], Elec_Phi[index], Elec_Charge[index], Elec_TrkIso[index], Elec_ECalIso[index], Elec_HCalIso[index], Elec_ECalIsoDeposit[index], Elec_HCalIsoDeposit[index],Elec_photonIso[index], Elec_chargedHadronIso[index], Elec_neutralHadronIso[index]);
      }

    std::vector<Jet> jetCollVeto;
    JetsVeto.SetPt(40); JetsVeto.SetEta(2.5);
    JetsVeto.JetSelectionLeptonVeto(Njet, Jet_Id_loose, Jet_Pt, Jet_Px, Jet_Py, Jet_Pz, Jet_E, Jet_Eta, Jet_neutralHadronEnergyFraction, Jet_neutralEmEnergyFraction, Jet_chargedHadronEnergyFraction, Jet_chargedMultiplicity, Jet_chargedEmEnergyFraction, Jet_BTag_TCHE, muonTightColl, electronColl, jetCollVeto);
    if (jetCollVeto.size() >0) 
      for (UInt_t i=0; i<jetCollVeto.size(); i++) {
        index=jetCollVeto[i].ijet();
        h_jets->Fill(1.0, Njet, Jet_Pt[index], Jet_Eta[index], Jet_Phi[index]);
      }   
 
    ///// PROMPT RATIO /////
    if ( muonLooseColl.size() == 2 && jetCollVeto.size() >= 1 ) {
      if ( muonTagColl.size() == 2 &&
           (muonTagColl[0].lorentzVec()+muonTagColl[1].lorentzVec()).M()<(Mass_Z+15) && (muonTagColl[0].lorentzVec()+muonTagColl[1].lorentzVec()).M()>(Mass_Z-15) && muonTagColl[0].charge()!=muonTagColl[1].charge() )  {
        h_nEvents->Fill(fabs(muonTightColl[0].eta()),muonTightColl[0].lorentzVec().Pt(), weight);
        h_nEvents->Fill(fabs(muonTightColl[1].eta()),muonTightColl[1].lorentzVec().Pt(), weight);
        h_nEventsPR->Fill(fabs(muonTightColl[0].eta()),muonTightColl[0].lorentzVec().Pt(), weight);
        h_nEventsPR->Fill(fabs(muonTightColl[1].eta()),muonTightColl[1].lorentzVec().Pt(), weight);   
      }
      if ( muonTagColl.size() == 1 && muonLooseButNotTightColl.size() == 1 && 
           (muonTagColl[0].lorentzVec()+muonLooseButNotTightColl[0].lorentzVec()).M()<(Mass_Z+15) && (muonTagColl[0].lorentzVec()+muonLooseButNotTightColl[0].lorentzVec()).M()>(Mass_Z-15) &&
           muonTagColl[0].charge()!=muonLooseButNotTightColl[0].charge() )
        h_nEventsPR->Fill(fabs(muonLooseButNotTightColl[0].eta()),muonLooseButNotTightColl[0].lorentzVec().Pt(), weight);
      
      h_nVertex->Fill(nVertex);
    }

  }
  

  getFakerate(h_nEvents,h_nEventsPR,h_PRrate,4,4);
  
}
