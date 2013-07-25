#include "FakeRateCalculator.h"

FRCalculator::FRCalculator() {

  int nintpT = 4;
  double arraypT[] = {10,15,20,25,35};
  int ninteta = 4;
  double arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  h_nEvents = new TH2F ("h_nEvents", "Number of Events",ninteta,arrayeta,nintpT,arraypT);
  h_nEventsFO = new TH2F ("h_nEventsFO", "Number of Events FO",ninteta,arrayeta,nintpT,arraypT);
  h_FOrate = new TH2F ("h_FOrate", "FO rate",ninteta,arrayeta,nintpT,arraypT);

  h_TLnum = new MuonPlots("TL_numerator");
  h_TLden = new MuonPlots("TL_denominator");

}
FRCalculator::~FRCalculator() {

  outfile->cd();
  Dir = outfile->mkdir("Muons");
  outfile->cd( Dir->GetName() );
  h_muons->Write();
  h_MET->Write();
  h_TLnum->Write();
  h_TLden->Write();
  outfile->cd();

  Dir = outfile->mkdir("Electrons");
  outfile->cd( Dir->GetName() );
  h_electrons->Write();
  outfile->cd();
  
  Dir = outfile->mkdir("Jets");
  outfile->cd( Dir->GetName() );
  h_jets->Write();
  h_jets_veto->Write();
  outfile->cd();

  h_prova->Write();
  h_singlefake->Write();
  h_doublefake->Write();
  h_LeptvsVert->Write();
  h_nVertex->Write();

  h_FOrate->Write();
  h_nEventsFO->Write();
  h_nEvents->Write();
 
  outfile->Close();

}

void FRCalculator::LoopFR() {
 
  if(!weight) weight=1;

  if (fChain == 0) 
    cout << "Ciao!" << endl;
//  cout << "Do you want limited events?" <<endl;
//  cin >>entrieslimit;
//  if (entrieslimit != -1)
//    nentries=entrieslimit;
//  nentries=30000;
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
        !trig("HLT_Mu8_v1") && !trig("HLT_Mu8_v2") && !trig("HLT_Mu8_v3") && !trig("HLT_Mu8_v4") && !trig("HLT_Mu8_v5") && !trig("HLT_Mu8_v6") && !trig("HLT_Mu8_v7") && !trig("HLT_Mu8_v8") && !trig("HLT_Mu8_v9") && !trig("HLT_Mu8_v10") && !trig("HLT_Mu8_v11") && !trig("HLT_Mu8_v12") &&
        !trig("HLT_Mu8_Jet40_v3") && !trig("HLT_Mu8_Jet40_v4") && !trig("HLT_Mu8_Jet40_v5") && !trig("HLT_Mu8_Jet40_v6") && !trig("HLT_Mu8_Jet40_v7") && !trig("HLT_Mu8_Jet40_v8") && !trig("HLT_Mu8_Jet40_v9") && !trig("HLT_Mu8_Jet40_v10") && !trig("HLT_Mu8_Jet40_v11") && !trig("HLT_Mu8_Jet40_v12") && !trig("HLT_Mu8_Jet40_v13") && !trig("HLT_Mu8_Jet40_v14") && !trig("HLT_Mu8_Jet40_v15") &&
//        !trig("HLT_Mu12_v1") && !trig("HLT_Mu12_v2") && !trig("HLT_Mu12_v3") && !trig("HLT_Mu12_v4") && !trig("HLT_Mu12_v5") && !trig("HLT_Mu12_v6") && !trig("HLT_Mu12_v7") && !trig("HLT_Mu12_v8") && !trig("HLT_Mu12_v9") && !trig("HLT_Mu12_v10") && !trig("HLT_Mu12_v11") &&
        !trig("HLT_Mu15_v2") && !trig("HLT_Mu15_v3") && !trig("HLT_Mu15_v4") && !trig("HLT_Mu15_v5") && !trig("HLT_Mu15_v6") && !trig("HLT_Mu15_v7") && !trig("HLT_Mu15_v8") && !trig("HLT_Mu15_v9") && !trig("HLT_Mu15_v10") && !trig("HLT_Mu15_v11") && !trig("HLT_Mu15_v12") && !trig("HLT_Mu15_v13")
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
    MuonLoose.SetPt(10); MuonLoose.SetEta(2.4); MuonLoose.SetRelIso(0.80); MuonLoose.SetChiNdof(10); MuonLoose.SetBSdxy(0.01);
    MuonLoose.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonLooseColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    if ( ZandWveto(muonLooseColl, MET, METx, METy) ) continue;

    ///// SOME STANDARD PLOTS/////
    if (muonLooseColl.size() > 0) {
      for (UInt_t i=0; i<muonLooseColl.size(); i++) {
        UInt_t index=muonLooseColl[i].ilepton();
        h_muons->Fill(Nmuon, Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], fabs(muonLooseColl[i].dxy_BS()-sqrt(pow(Vertex_X[VertexN],2)+pow(Vertex_Y[VertexN],2))), fabs(muonLooseColl[i].dz_BS()-Vertex_Z[VertexN]), rho);
        h_MET->Fill(MET);
      }
    }
 
    ///// STARTING WITH COLLECTIONS NEEDED FOR THE FAKERATE /////

    //cout << "Event number " <<jentry<< endl;
    std::vector<Lepton> muonTightColl;
    MuonTight.SetPt(10); MuonTight.SetEta(2.4); MuonTight.SetRelIso(0.10); MuonTight.SetChiNdof(10); MuonTight.SetBSdxy(0.01);
    MuonTight.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonTightColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    std::vector<Lepton> electronColl;
    Electron.SetPt(10); Electron.SetEta(2.4); Electron.SetRelIso(0.10);
    Electron.LeptonSelection(Nelec, Elec_HasTrack, Elec_Eta, Elec_Pt, Elec_Px, Elec_Py, Elec_Pz, Elec_E, Elec_TrkIso, Elec_ECalIso, Elec_HCalIso, Elec_Charge, Elec_ECalIsoDeposit, Elec_HCalIsoDeposit, Elec_Gen_Mother, Elec_ValidHits, electronColl, rho);
    if (electronColl.size() >0)
      for (UInt_t i=0; i<electronColl.size(); i++) {
        index=electronColl[i].ilepton();
        h_electrons->Fill(Nelec, Elec_Pt[index], Elec_Eta[index], Elec_Phi[index], Elec_Charge[index], Elec_TrkIso[index], Elec_ECalIso[index], Elec_HCalIso[index], Elec_ECalIsoDeposit[index], Elec_HCalIsoDeposit[index],Elec_photonIso[index], Elec_chargedHadronIso[index], Elec_neutralHadronIso[index]);
      }

    std::vector<Jet> jetColl;
    Jets.SetPt(5); Jets.SetEta(2.5);
    Jets.JetSelection(Njet, Jet_Id_loose, Jet_Pt, Jet_Px, Jet_Py, Jet_Pz, Jet_E, Jet_Eta, Jet_neutralHadronEnergyFraction, Jet_neutralEmEnergyFraction, Jet_chargedHadronEnergyFraction, Jet_chargedMultiplicity, Jet_chargedEmEnergyFraction, Jet_BTag_TCHE, jetColl);
    if (jetColl.size() >0 && muonLooseColl.size()==1) {
      for (UInt_t i=0; i<jetColl.size(); i++)
        for (UInt_t j=0; j<muonLooseColl.size(); j++) {
          if (jetColl[i].lorentzVec().DeltaR( muonLooseColl[j].lorentzVec() ) > 1.0 && jetColl[i].lorentzVec().Pt()>60)
            for (UInt_t m=0; m<jetColl.size(); m++) {
              if (jetColl[m].lorentzVec().DeltaR( muonLooseColl[j].lorentzVec() ) < 0.3) {
                index=jetColl[m].ijet();
                h_jets->Fill(1.0, (Int_t) jetColl.size(), Jet_Pt[index], Jet_Eta[index], Jet_Phi[index]);
                goto end;
              }
            }
        }
    }
    end:

    std::vector<Jet> jetCollVeto;
    JetsVeto.SetPt(40); JetsVeto.SetEta(2.5);
    JetsVeto.JetSelectionLeptonVeto(Njet, Jet_Id_loose, Jet_Pt, Jet_Px, Jet_Py, Jet_Pz, Jet_E, Jet_Eta, Jet_neutralHadronEnergyFraction, Jet_neutralEmEnergyFraction, Jet_chargedHadronEnergyFraction, Jet_chargedMultiplicity, Jet_chargedEmEnergyFraction, Jet_BTag_TCHE, muonTightColl, electronColl, jetCollVeto);
    if (jetCollVeto.size() >0) 
      for (UInt_t i=0; i<jetCollVeto.size(); i++) {
        index=jetCollVeto[i].ijet();
        h_jets_veto->Fill(1.0, Njet, Jet_Pt[index], Jet_Eta[index], Jet_Phi[index]);
      }   
 
    ///// FAKE RATES /////
    
    if (muonLooseColl.size() == 1 && muonTightColl.size() == 1  && jetCollVeto.size() >= 1) {
      for (UInt_t iii=0; iii<muonTightColl.size(); iii++) {
	for (UInt_t yyy=0; yyy<jetCollVeto.size(); yyy++) {
	//if (jetCollVeto.size() == 1)
	  dr = muonTightColl[iii].lorentzVec().DeltaR( jetCollVeto[yyy].lorentzVec() );
	//else
	  //dr = 10;
	  if (dr > 1.0) {
	    h_nEvents->Fill(fabs(muonTightColl[iii].eta()),muonTightColl[iii].lorentzVec().Pt(), weight);

            if (muonTightColl[iii].lorentzVec().Pt()<=35) {
              UInt_t index=muonLooseColl[iii].ilepton();
              h_TLnum->Fill( (Int_t) muonTightColl.size(), Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], muonTightColl[iii].dxy_BS(), muonTightColl[iii].dz_BS(), rho);
            }

	    goto fine;
	  }
        }
      }
    }
    fine:
    if (muonLooseColl.size() == 1 && jetCollVeto.size() >= 1) {
      for (UInt_t iii=0; iii<muonLooseColl.size(); iii++) {
	for (UInt_t yyy=0; yyy<jetCollVeto.size(); yyy++) {
	//if (jetCollVeto.size() == 1)
	  dr = muonLooseColl[iii].lorentzVec().DeltaR( jetCollVeto[yyy].lorentzVec() );
	//else
	  //dr = 10;
	  if (dr > 1.0) {
	    h_nEventsFO->Fill(fabs(muonLooseColl[iii].eta()),muonLooseColl[iii].lorentzVec().Pt(), weight);
	    h_nVertex->Fill(nVertex);

            if (muonLooseColl[iii].lorentzVec().Pt()<=35) {
              UInt_t index=muonLooseColl[iii].ilepton();
              h_TLden->Fill( (Int_t) muonLooseColl.size(), Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], muonLooseColl[iii].dxy_BS(), muonLooseColl[iii].dz_BS(), rho);
            }

	    goto fineFO;
	  }
	}
      }
    }
    fineFO:
    ; 
  } //loop on the entries
  

  getFakerate(h_nEvents,h_nEventsFO,h_FOrate,4,4);
  
}
