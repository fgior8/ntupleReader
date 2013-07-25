#include "Analyzer.h"

Analyzer::Analyzer() {
cout<<"inizio"<<endl;
  h_MET = new TH1F("h_MET","Missing Et",50,0.0,500.0);
  h_METsign = new TH1F("h_METsign","Missing Et significance",50,0.0,50.0);
  h_MuonMissCharge = new TH1F("h_MuonMissCharge","Miss Charge for muons",6,0,6);
  h_EventFakeType = new TH1F("h_EventFakeType","Event fake type",3,0,3);
  h_LeptvsVert = new TH2I("h_LeptvsVert","Leptons per Vertex",50,0,50,5,0,5);

  h_nVertex= new TH1F("h_nVertex","number of verteces",30,0,30);
  h_nVertex0= new TH1F("h_nVertex0","number of verteces t0",30,0,30);
  h_nVertex1= new TH1F("h_nVertex1","number of verteces t1",30,0,30);
  h_nVertex2= new TH1F("h_nVertex2","number of verteces t2",30,0,30);
  
  h_nvtx_norw = new TH1F("h_nvtx_norw","Nvtx per bunch crossing at BX = 0 noreweight",50,0.0,50.0);
  h_nvtx_rw = new TH1F("h_nvtx_rw","Nvtx per bunch crossing at BX = 0 reweight",50,0.0,50.0);

  h_prova = new TH1F("h_prova","Di-Muon Mass (GeV)",200,0,200);
  h_RelIsoFR = new TH1F("h_RelIsoFR","RelIso FR weight",40,0,0.4);
  //  h_electrons = new TH1F("h_electrons","electrons number",4,-1,3);
  h_electrons = new ElectronPlots("electrons");
  h_muons = new MuonPlots("muons");
  h_muonsLoose = new MuonPlots("loose_muons");
  h_LnotT = new MuonPlots("loose_not_tight");
  //h_muonCharge = new MuonPlots("misscharge_muon");
  h_jets = new StdPlots("jets");
  h_jets_veto = new StdPlots("jets_w_veto");
  h_signal1 = new SignalPlots("s1");
  h_signal2 = new SignalPlots("s2");
  h_signal3 = new SignalPlots("s3");
  h_singlefakes = new SignalPlots("sf");
  h_doublefakes = new SignalPlots("df");
  h_single_doublefakes = new SignalPlots("tf");
  h_nsignal = new TH1F("h_signal","number of signal events ",4,-1,3);
  h_singlefake = new TH1F("h_singlefake","number of single fakes ",4,-1,3);
  h_doublefake = new TH1F("h_doublefake","number of double fakes ",4,-1,3);

  TFile *infile = new TFile("/uscms_data/d2/fgior8/Collisions11_428/CMSSW_4_2_8_patch7/src/UserCode/ntup/code/FR40_EWKcorr_14.20.root");  
//  TFile *infile = new TFile("/home/cms/fgior8/codeSummer11/Double_Single_Sept_totalFR_13.60.root");
  infile->cd();
  TDirectory *dir=gDirectory;             
  dir->GetObject("h_FOrate",FRhisto);
cout<<"fine"<<endl;
}

Analyzer::~Analyzer() { 
  outfile->cd();
  
  Dir = outfile->mkdir("Muons");
  outfile->cd( Dir->GetName() );
  h_muons->Write();
  h_muonsLoose->Write();
  h_LnotT->Write();
  //h_muonCharge->Write();
  h_MET->Write();
  h_METsign->Write();
  h_MuonMissCharge->Write();
  h_RelIsoFR->Write();
  outfile->cd();
 
  Dir = outfile->mkdir("Electrons");
  outfile->cd( Dir->GetName() );
  h_electrons->Write();
  outfile->cd();  
  
  Dir = outfile->mkdir("Jets");
  outfile->cd( Dir->GetName() );
  h_jets->Write();
  outfile->cd();

  Dir = outfile->mkdir("Jets_with_veto");
  outfile->cd( Dir->GetName() );
  h_jets_veto->Write();
  outfile->cd();

  Dir = outfile->mkdir("Heavy_Neutrino");
  outfile->cd( Dir->GetName() );
  h_signal3->Write();
  outfile->cd();

  Dir = outfile->mkdir("First_selection");
  outfile->cd( Dir->GetName() );
  h_signal1->Write(); 
  outfile->cd();
  Dir = outfile->mkdir("Second_selection");
  outfile->cd( Dir->GetName() );
  h_signal2->Write(); 
  outfile->cd();

  Dir = outfile->mkdir("SingleFakes");
  outfile->cd( Dir->GetName() );
  h_singlefakes->Write();
  outfile->cd();
  Dir = outfile->mkdir("DoubleFakes");
  outfile->cd( Dir->GetName() );
  h_doublefakes->Write();
  outfile->cd();
  Dir = outfile->mkdir("TotalFakes");
  outfile->cd( Dir->GetName() );
  h_single_doublefakes->Write();
  outfile->cd();

  h_EventFakeType->Write();
  h_prova->Write();
  h_nsignal->Write();
  h_singlefake->Write();
  h_doublefake->Write();
  h_LeptvsVert->Write();
  h_nVertex->Write();
  h_nVertex0->Write();
  h_nVertex1->Write();
  h_nVertex2->Write();
  h_nvtx_norw->Write();
  h_nvtx_rw->Write();
  outfile->Close();
  /*
  h_electrons->~ElectronPlots();
  h_muons->~MuonPlots();
  h_jets->~StdPlots();
  h_signal1->~SignalPlots(); h_signal2->~SignalPlots(); h_signal3->~SignalPlots();
  h_singlefakes->~SignalPlots(); h_doublefakes->~SignalPlots();
  */
}

void Analyzer::SetName(string name, Float_t version) {
  UInt_t size = name.length();
  completename = new Char_t [size+22];
  strcpy(completename,name.c_str());
  sprintf (completename,"%s_%.2f.root",completename,version);
  outfile = new TFile(completename,"RECREATE");
}

void Analyzer::SetWeight(Double_t CrossSection, Double_t nevents) {

  MCweight = integratedlumi * CrossSection / nevents;
// lumi *  cs(pb) * gen filter efficiency / MCevents
  cout<<"MCweight = "<<MCweight<<endl;
 
}

void Analyzer::SetEvtN(Long64_t events) {
  events ? entrieslimit=events :  entrieslimit=-1;
  cout<<"events "<<events<<endl<<"entrieslimit "<<entrieslimit<<endl;
}

void Analyzer::Loop() {

  nb=0;
  Double_t SingleFake=0; Double_t DoubleFake=0; Double_t Single_Double=0;
  Int_t nSingleFake=0; Int_t nDoubleFake=0;

  reweightPU = new ReweightPU("pileup_NR_m130_Warren_14.19.root", "Data_pileup_14.06.root");

  UInt_t nbinX=FRhisto->GetNbinsX(); UInt_t nbinY=FRhisto->GetNbinsY();

  singleFake=new Double_t*[nbinX];
  for (UInt_t i=0; i<nbinX; i++)
    singleFake[i]=new Double_t[nbinY];
  for (UInt_t i=0; i<nbinX; i++)
    for (UInt_t j=0; j<nbinY; j++)
      singleFake[i][j]=0;
  doubleFake=new Double_t***[nbinX];
  prova=new Double_t***[nbinX];
  for (UInt_t i=0; i<nbinX; i++) {
    doubleFake[i]=new Double_t**[nbinY];
    prova[i]=new Double_t**[nbinY];
  }
  for (UInt_t i=0; i<nbinX; i++)
    for (UInt_t j=0; j<nbinY; j++) {
      doubleFake[i][j]=new Double_t*[nbinX];
      prova[i][j]=new Double_t*[nbinX];
  }
  for (UInt_t i=0; i<nbinX; i++)
    for (UInt_t j=0; j<nbinY; j++)
      for (UInt_t m=0; m<nbinX; m++) {
	doubleFake[i][j][m]=new Double_t[nbinY];
        prova[i][j][m]=new Double_t[nbinY];
  }
  for (UInt_t i=0; i<nbinX; i++)
    for (UInt_t j=0; j<nbinY; j++)
      for (UInt_t m=0; m<nbinX; m++)
	for (UInt_t n=0; n<nbinY; n++) {
	  doubleFake[i][j][m][n]=0;
          prova[i][j][m][n]=0;
  }

  if(!MCweight) MCweight=1; 

  weight=MCweight;

  if (fChain == 0) 
    cout << "Ciao!" << endl;

//  cout << "Do you want limited events?" <<endl;
//  cin >> entrieslimit;
//  if (entrieslimit != -1)
//    nentries=entrieslimit;
  //entrieslimit = 3000;


  std::set<int> runs;
  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {

    //    watch_getentry.Start(false);

    if (!(jentry % 1000))
      cout << jentry << endl;

    if ( runs.find(EventAux_run) == runs.end() ) {
      cout << "run " << EventAux_run <<endl;
      runs.insert(EventAux_run);
    }
    
//    start = watch.CpuTime();

    //if (ientry < 0) {
      //cout<<"CAZZAROLA!"<<endl;
      //break;
    //}

    if (!fChain) cout<<"porcaccia"<<endl;
    fChain->GetEntry(jentry);  // nbytes += nb; // nb = number of bytes read
    // Print HLT info on zeroth event
    if (jentry == 0 && HLT_triggered && debug) {
      cout<< "HLT map:\n";
      cout << "map size = " << HLT_triggered->size() <<endl;
      for (stringtobool::iterator trigtry = HLT_triggered->begin(); trigtry != HLT_triggered->end(); trigtry++)
        cout << trigtry->first << " = " << trigtry->second <<endl;
    }

    // event skips fo di-muons
    //if (jentry < 7400000) continue;
    //if (jentry == 160300) jentry += 10000;    
/*
    if ( !( trig("HLT_DoubleMu7_v1")) && !( trig("HLT_DoubleMu7_v2")) && 
         !( trig("HLT_Mu13_Mu8_v1")) && !( trig("HLT_Mu13_Mu8_v2")) && !( trig("HLT_Mu13_Mu8_v3")) && !( trig("HLT_Mu13_Mu8_v4")) && !( trig("HLT_Mu13_Mu8_v5")) && !( trig("HLT_Mu13_Mu8_v6")) && 
         !( trig("HLT_Mu13_Mu8_v7")) && !( trig("HLT_Mu13_Mu8_v8")) && !( trig("HLT_Mu13_Mu8_v9")) &&
         !( trig("HLT_Mu17_Mu8_v10")) && !( trig("HLT_Mu17_Mu8_v11"))
       ) continue;

    if (
        !trig("HLT_Mu8_v1") && !trig("HLT_Mu8_v2") && !trig("HLT_Mu8_v3") && !trig("HLT_Mu8_v4") && !trig("HLT_Mu8_v5") && !trig("HLT_Mu8_v6") && !trig("HLT_Mu8_v7") && !trig("HLT_Mu8_v8") && !trig("HLT_Mu8_v9") && !trig("HLT_Mu8_v10") && !trig("HLT_Mu8_v11") && !trig("HLT_Mu8_v12") &&
        !trig("HLT_Mu8_Jet40_v3") && !trig("HLT_Mu8_Jet40_v4") && !trig("HLT_Mu8_Jet40_v5") && !trig("HLT_Mu8_Jet40_v6") && !trig("HLT_Mu8_Jet40_v7") && !trig("HLT_Mu8_Jet40_v8") && !trig("HLT_Mu8_Jet40_v9") && !trig("HLT_Mu8_Jet40_v10") && !trig("HLT_Mu8_Jet40_v11") && !trig("HLT_Mu8_Jet40_v12") && !trig("HLT_Mu8_Jet40_v13") && !trig("HLT_Mu8_Jet40_v14") && !trig("HLT_Mu8_Jet40_v15") &&
        !trig("HLT_Mu15_v2") && !trig("HLT_Mu15_v3") && !trig("HLT_Mu15_v4") && !trig("HLT_Mu15_v5") && !trig("HLT_Mu15_v6") && !trig("HLT_Mu15_v7") && !trig("HLT_Mu15_v8") && !trig("HLT_Mu15_v9") && !trig("HLT_Mu15_v10") && !trig("HLT_Mu15_v11") && !trig("HLT_Mu15_v12") && !trig("HLT_Mu15_v13")
    ) continue;
*/
  //  triggerweight=TriggerWeight(HLT_triggered);
    triggerweight=1.0;
    if(triggerweight==-1) {
      cout<< "HLT map:\n\n\n";
      cout << "map size = " << HLT_triggered->size() <<endl;
      for (stringtobool::iterator trigtry = HLT_triggered->begin(); trigtry != HLT_triggered->end(); trigtry++)
        cout << trigtry->first << " = " << trigtry->second <<endl;
    }

    /// ***PU reweghting*** ///
    //weight_ = noreweight_;// mc weight;
    h_nvtx_norw->Fill(NInteraction, MCweight);
    weight = reweightPU->GetWeight(NInteraction)*MCweight;
    h_nvtx_rw->Fill(NInteraction, weight);
    

    goodVerticies = new Bool_t [nVertex];
    if ( !isGoodEvent(nVertex, Vertex_Ndof, Vertex_X, Vertex_Y, Vertex_Z, beamspot_x0, beamspot_y0, goodVerticies) ) continue;

    for(Int_t vv=0; vv<nVertex; vv++) {
      if(goodVerticies[vv]) {
        VertexN=vv;
        break;
      }
    }

    //       MET         //
    METx = MET_fullcorr_nocc[0][0];
    METy = MET_fullcorr_nocc[0][1];
    MET = sqrt( METx*METx + METy*METy );

    ///// STARTING WITH COLLECTIONS NEEDED FOR THE FAKERATE /////

    //cout << "Event number " <<jentry<< endl;
    std::vector<Lepton> muonTightColl;
    MuonTight.SetPt(10); MuonTight.SetEta(2.4); MuonTight.SetRelIso(0.1); MuonTight.SetChiNdof(10); MuonTight.SetBSdxy(0.01); 
    MuonTight.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonTightColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    ///// SOME STANDARD PLOTS/////
    if (muonTightColl.size() > 0) {
      for (UInt_t i=0; i<muonTightColl.size(); i++) {
	index=muonTightColl[i].ilepton();
	h_muons->Fill( (Int_t) muonTightColl.size(), Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], muonTightColl[i].dxy_BS(), muonTightColl[i].dz_BS(), rho);     
	if (muonTightColl[i].fakeType() == Lepton::unknown && Muon_Gen_Mother[index]!=999) cout<<"SCONOSCIUTO!!!!!"<<" pdgID "<<Muon_Gen_Mother[index]<<endl;
      }	 
    }
    h_MET->Fill(MET);
    h_METsign->Fill(MET_fullcorr_nocc_significance[0]);

    if(MET>50) continue;

    /// ***simple check for double muon invariant mass and 3rd lepton Z veto*** ///
    Double_t masslow=999.9;
    if (muonTightColl.size() >= 2) {
      masslow = (muonTightColl[0].lorentzVec() + muonTightColl[1].lorentzVec()).M();
      h_prova->Fill(masslow);
    }
    if (masslow < 5.0) continue;
    Double_t mass3rd=999.9;
    Double_t temp_mass3rd=999.9;
    if (muonTightColl.size() > 2) {
      for(UInt_t i=0; i<muonTightColl.size()-1; i++)
	for(UInt_t j=i+1; j<muonTightColl.size(); j++) {
	  if ( muonTightColl[i].charge() != muonTightColl[j].charge() ) {
	    temp_mass3rd = (muonTightColl[i].lorentzVec() + muonTightColl[j].lorentzVec()).M();
	    if ( fabs(temp_mass3rd-Mass_Z) < fabs(mass3rd-Mass_Z) ) 
	      mass3rd=temp_mass3rd;
	  }
	}
    }    
    if (mass3rd > (Mass_Z-15) && mass3rd < (Mass_Z+15) ) continue;

    std::vector<Lepton> muonLooseColl;
    MuonLoose.SetPt(10); MuonLoose.SetEta(2.4); MuonLoose.SetRelIso(0.80); MuonLoose.SetChiNdof(10); MuonLoose.SetBSdxy(0.01);
    MuonLoose.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonLooseColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);

    ///// SOME STANDARD PLOTS/////
    if (muonLooseColl.size() > 0) {
      for (UInt_t i=0; i<muonLooseColl.size(); i++) {
        index=muonLooseColl[i].ilepton();
        h_muonsLoose->Fill( (Int_t) muonLooseColl.size(), Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], muonLooseColl[i].dxy_BS(), muonLooseColl[i].dz_BS(), rho);
      }
    }

    std::vector<Lepton> muonLooseButTightColl;
    MuonLooseButNotTight.SetPt(10); MuonLooseButNotTight.SetEta(2.4); MuonLooseButNotTight.SetRelIso(0.10,0.80); MuonLooseButNotTight.SetChiNdof(10); MuonLooseButNotTight.SetBSdxy(0.01);
    MuonLooseButNotTight.MuonSelection(Nmuon, Muon_IsTracker, Muon_Eta, Muon_Pt, Muon_PtErr, Muon_Px, Muon_Py, Muon_Pz, Muon_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Muon_Charge, Muon_ECalIsoDeposit, Muon_HCalIsoDeposit, Muon_Gen_Mother, Muon_TrkValidHits, muonLooseButTightColl, Muon_IsGlobal, Muon_StandValidHits, Muon_GlobalChi2, Muon_GlobalNdof, Muon_TrkVx, Muon_TrkVy, Muon_TrkVz, Muon_TrkIPToolsIP, Muon_TrkIPToolsIPError, Muon_TrkIPToolsIPSignificance, Vertex_X[VertexN], Vertex_Y[VertexN], Vertex_Z[VertexN], rho);
    if (muonLooseButTightColl.size() > 0) {
      for (UInt_t i=0; i<muonLooseButTightColl.size(); i++) {
        index=muonLooseButTightColl[i].ilepton();
        h_LnotT->Fill( (Int_t) muonLooseButTightColl.size(), Muon_Pt[index], Muon_Eta[index], Muon_Phi[index], Muon_Charge[index], Muon_TrkIso[index], Muon_ECalIso[index], Muon_HCalIso[index], Muon_ECalIsoDeposit[index], Muon_HCalIsoDeposit[index], Muon_photonIso[index], Muon_chargedHadronIso[index], Muon_neutralHadronIso[index], Muon_GlobalChi2[index], Muon_GlobalNdof[index], muonLooseButTightColl[i].dxy_BS(), muonLooseButTightColl[i].dz_BS(), rho);
      }
    }

    //if (muonLooseColl.size() == 0) continue;

    std::vector<Lepton> electronColl;
    Electron.SetPt(10); Electron.SetEta(2.4); Electron.SetRelIso(0.10);
    Electron.LeptonSelection(Nelec, Elec_HasTrack, Elec_Eta, Elec_Pt, Elec_Px, Elec_Py, Elec_Pz, Elec_E, Muon_TrkIso, Muon_ECalIso, Muon_HCalIso, Elec_Charge, Elec_ECalIsoDeposit, Elec_HCalIsoDeposit, Elec_Gen_Mother, Elec_ValidHits, electronColl, rho);
    if (electronColl.size() >0) {
      for (UInt_t i=0; i<electronColl.size(); i++) {
        index=electronColl[i].ilepton();
	h_electrons->Fill( (Int_t) electronColl.size(), Elec_Pt[index], Elec_Eta[index], Elec_Phi[index], Elec_Charge[index], Elec_TrkIso[index], Elec_ECalIso[index], Elec_HCalIso[index], Elec_ECalIsoDeposit[index], Elec_HCalIsoDeposit[index],Elec_photonIso[index], Elec_chargedHadronIso[index], Elec_neutralHadronIso[index]);
      }
    }
    
    std::vector<Jet> jetColl;
    Jets.SetPt(5); Jets.SetEta(2.5);
    Jets.JetSelection(Njet, Jet_Id_loose, Jet_Pt, Jet_Px, Jet_Py, Jet_Pz, Jet_E, Jet_Eta, Jet_neutralHadronEnergyFraction, Jet_neutralEmEnergyFraction, Jet_chargedHadronEnergyFraction, Jet_chargedMultiplicity, Jet_chargedEmEnergyFraction, Jet_BTag_TCHE, jetColl);
    if (jetColl.size() >0 && muonLooseColl.size()==1) {
      for (UInt_t i=0; i<jetColl.size(); i++)
        for (UInt_t j=0; j<muonLooseColl.size(); j++) {
          if (jetColl[i].lorentzVec().DeltaR( muonLooseColl[j].lorentzVec() ) > 1.0 && jetColl[i].lorentzVec().Pt()>50)
            for (UInt_t m=0; m<jetColl.size(); m++) {
              if (jetColl[m].lorentzVec().DeltaR( muonLooseColl[j].lorentzVec() ) < 0.3) {
                index=jetColl[m].ijet();
                h_jets->Fill(triggerweight, (Int_t) jetColl.size(), Jet_Pt[index], Jet_Eta[index], Jet_Phi[index]);
                goto end;
              }
            }
        }
    }
    end:
    
    std::vector<Jet> jetCollVeto;
    JetsVeto.SetPt(20); JetsVeto.SetEta(2.5);
    JetsVeto.JetSelectionLeptonVeto(Njet, Jet_Id_loose, Jet_Pt, Jet_Px, Jet_Py, Jet_Pz, Jet_E, Jet_Eta, Jet_neutralHadronEnergyFraction, Jet_neutralEmEnergyFraction, Jet_chargedHadronEnergyFraction, Jet_chargedMultiplicity, Jet_chargedEmEnergyFraction, Jet_BTag_TCHE, muonTightColl, electronColl, jetCollVeto);
    if (jetCollVeto.size() >0)
      for (UInt_t i=0; i<jetCollVeto.size(); i++) {
        index=jetCollVeto[i].ijet();
        h_jets_veto->Fill(1, (Int_t) jetCollVeto.size(), Jet_Pt[index], Jet_Eta[index], Jet_Phi[index]);
      }

//    if ( ZandWveto(muonTightColl, MET, METx, METy) ) continue;
     
    ///// SIGNAL /////

    VETO=false; 
    if (muonTightColl.size() >= 2  && jetCollVeto.size() >= 2) {
      for(UInt_t i=0; i<muonTightColl.size()-1; i++)
	for(UInt_t j=i+1; j<muonTightColl.size(); j++) {
	  if (muonTightColl[i].charge()*muonTightColl[j].charge()>0) 
	    if (muonTightColl[i].lorentzVec().Pt() >=20) {
	      /*
	      for(UInt_t mmm=0; mmmm<jetCollVeto.size()-1; mmm++)
		for(UInt_t nnn=1; nnn<jetCollVeto.size(); nnn++) {
		  jets2mass=(jetCollVeto[mmm].lorentzVec()+jetCollVeto[nnn].lorentzVec()).M();
		  if (jets2mass<300) goto duejetsmass;
		  if (mmm==jetCollVeto.size()-1 && nnn==jetCollVeto.size()) goto duejetsmassLARGE;
		}
	    duejetsmass:
	      */
              if (muonTightColl[j].lorentzVec().Pt()>=20)
                weight *= trigeff*mu2scale*mu2scale;
              else
                weight *= trigeff*mu1scale*mu2scale;
	      h_MuonMissCharge->Fill(muonTightColl[i].fakeType());
	      h_MuonMissCharge->Fill(muonTightColl[j].fakeType());
	      cout<<"First muon is "<<muonTightColl[i].fakeType()<<endl;
	      cout<<"Second muon is "<<muonTightColl[j].fakeType()<<endl;
              cout<<"             Event number "<<jentry<<endl;
	      //VETO=true;
	      if (muonTightColl[i].fakeType()==Lepton::notfake && muonTightColl[j].fakeType()==Lepton::notfake) {
		h_EventFakeType->Fill(0);
 		//VETO=true; goto cacca;
   	      }
	      else if ( (muonTightColl[i].fakeType()==Lepton::notfake && muonTightColl[j].fakeType()!=Lepton::notfake) || (muonTightColl[i].fakeType()!=Lepton::notfake && muonTightColl[j].fakeType()==Lepton::notfake) )
		h_EventFakeType->Fill(1);
	      else if (muonTightColl[i].fakeType()!=Lepton::notfake && muonTightColl[j].fakeType()!=Lepton::notfake)
		h_EventFakeType->Fill(2);
 	      VETO=true; goto cacca;
	    }
	}
    }
    cacca:
    //duejetsmassLARGE:
    if(VETO) {
      h_nVertex->Fill(nVertex);
      h_nVertex2->Fill(nVertex);
      h_nsignal->Fill(1,weight);
      h_signal3->Fill(MET, muonTightColl, jetCollVeto, weight, false, false);
    }

    ///// BACKGROUND /////

    DOUBLEFAKE=false;
    if (muonLooseButTightColl.size() == 2 && muonTightColl.size() == 0 && jetCollVeto.size() >= 2) {
      for(UInt_t i=0; i<muonLooseButTightColl.size()-1; i++)
	for(UInt_t j=i+1; j<muonLooseButTightColl.size(); j++) {
	  if (muonLooseButTightColl[i].charge()*muonLooseButTightColl[j].charge()>0)
	    if (muonLooseButTightColl[i].lorentzVec().Pt() >=20) {
	      DOUBLEFAKE=true;
              DoubleFake=DoublebackGround(FRhisto, muonLooseButTightColl, i, j, doubleFake, 1);
              Single_Double=Single_Doublebkg(FRhisto, muonLooseButTightColl, i, j);
            }
	}
    }
    if (DOUBLEFAKE) {
//      DoubleFake=DoublebackGround(FRhisto, muonLooseButTightColl, doubleFake, 1);
      nDoubleFake++;
      h_doublefakes->Fill(MET, muonLooseButTightColl, jetCollVeto, DoubleFake*weight, false, false);
      h_single_doublefakes->Fill(MET, muonLooseButTightColl, jetCollVeto, (DoubleFake+Single_Double)*weight, false, false);
      Int_t iFG, jFG;
      if (muonLooseButTightColl[0].lorentzVec().Pt() <= 15) iFG=1;
      else if (muonLooseButTightColl[0].lorentzVec().Pt() <= 20) iFG=2;
      else if (muonLooseButTightColl[0].lorentzVec().Pt() <= 25) iFG=3;
      else iFG=4;
      if (fabs(muonLooseButTightColl[0].eta()) <= 1.0) jFG=1;
      else if (fabs(muonLooseButTightColl[0].eta()) <= 1.479) jFG=2;
      else if (fabs(muonLooseButTightColl[0].eta()) <= 2.0) jFG=3;
      else jFG=4;
      h_RelIsoFR->Fill(muonLooseButTightColl[0].relIso()*FRhisto->GetBinContent(jFG,iFG),(DoubleFake+Single_Double)*weight);
      if (muonLooseButTightColl[1].lorentzVec().Pt() <= 15) iFG=1;
      else if (muonLooseButTightColl[1].lorentzVec().Pt() <= 20) iFG=2;
      else if (muonLooseButTightColl[1].lorentzVec().Pt() <= 25) iFG=3;
      else iFG=4;
      if (fabs(muonLooseButTightColl[1].eta()) <= 1.0) jFG=1;
      else if (fabs(muonLooseButTightColl[1].eta()) <= 1.479) jFG=2;
      else if (fabs(muonLooseButTightColl[1].eta()) <= 2.0) jFG=3;
      else jFG=4;

      h_RelIsoFR->Fill(muonLooseButTightColl[1].relIso()*FRhisto->GetBinContent(jFG,iFG),(DoubleFake+Single_Double)*weight);
      h_nVertex->Fill(nVertex);
      h_nVertex0->Fill(nVertex);
    }
  
    SINGLEFAKE=false;
    if (!VETO) {
      if (muonLooseButTightColl.size() == 1 && muonTightColl.size() == 1 && jetCollVeto.size() >= 2) {
	for(UInt_t i=0; i<muonTightColl.size(); i++) 
	  for(UInt_t j=0; j<muonLooseButTightColl.size(); j++) {
	    if (muonLooseButTightColl[j].charge()*muonTightColl[i].charge()>0)
	      if (muonLooseButTightColl[j].lorentzVec().Pt() >=20 || muonTightColl[i].lorentzVec().Pt() >=20) {
		SINGLEFAKE=true;
                SingleFake=SinglebackGround(FRhisto, muonLooseButTightColl, j, singleFake, 1);
                FunzioProva(muonTightColl, i, muonLooseButTightColl, j, prova);
	 	goto endSingle;
              }
	  }
      }
    }
    endSingle:
    if (SINGLEFAKE) {
//      SingleFake=SinglebackGround(FRhisto, muonLooseButTightColl, singleFake, 1);
//      FunzioProva(muonLooseButTightColl, muonTightColl, prova);
      nSingleFake++;
      h_singlefakes->Fill(MET, muonTightColl, muonLooseButTightColl, jetCollVeto, SingleFake*weight, false, false);
      h_single_doublefakes->Fill(MET, muonTightColl, muonLooseButTightColl, jetCollVeto, SingleFake*weight, false, false);
      Int_t iFG, jFG;
      if (muonLooseButTightColl[0].lorentzVec().Pt() <= 15) iFG=1;
      else if (muonLooseButTightColl[0].lorentzVec().Pt() <= 20) iFG=2;
      else if (muonLooseButTightColl[0].lorentzVec().Pt() <= 25) iFG=3;
      else iFG=4;
      if (fabs(muonLooseButTightColl[0].eta()) <= 1.0) jFG=1;
      else if (fabs(muonLooseButTightColl[0].eta()) <= 1.479) jFG=2;
      else if (fabs(muonLooseButTightColl[0].eta()) <= 2.0) jFG=3;
      else jFG=4;
      h_RelIsoFR->Fill(muonLooseButTightColl[0].relIso()*FRhisto->GetBinContent(jFG,iFG),SingleFake*weight);
      if (muonTightColl[0].lorentzVec().Pt() <= 15) iFG=1;
      else if (muonTightColl[0].lorentzVec().Pt() <= 20) iFG=2;
      else if (muonTightColl[0].lorentzVec().Pt() <= 25) iFG=3;
      else iFG=4;
      if (fabs(muonTightColl[0].eta()) <= 1.0) jFG=1;
      else if (fabs(muonTightColl[0].eta()) <= 1.479) jFG=2;
      else if (fabs(muonTightColl[0].eta()) <= 2.0) jFG=3;
      else jFG=4;
      h_RelIsoFR->Fill(muonTightColl[0].relIso()*FRhisto->GetBinContent(jFG,iFG),SingleFake*weight);
      h_nVertex->Fill(nVertex);
      h_nVertex1->Fill(nVertex);
    }

    /// BACKGROUND END ///

    if (muonLooseColl.size() >= 2  && jetCollVeto.size() >= 2)
      if (jetCollVeto[0].lorentzVec().Pt() >=20)
        h_signal1->Fill(MET, muonLooseColl, jetCollVeto, weight, true, true);

    VETO=false;
    if (muonTightColl.size() >= 2  && jetCollVeto.size() >= 2) {
      for(UInt_t i=0; i<muonTightColl.size()-1; i++) {
	if (muonTightColl[i].lorentzVec().Pt() >=20 && jetCollVeto[0].lorentzVec().Pt() >=20)
	  VETO=true;
      }
    }
    if(VETO) 
      h_signal2->Fill(MET, muonTightColl, jetCollVeto, weight, false, true);


    muonTightColl.clear(); muonLooseButTightColl.clear(); muonLooseColl.clear();
    electronColl.clear(); jetCollVeto.clear();

  }

  finalbkg1=finalbkgerror1=finalbkg2=finalbkgerror2=realsingle=realdouble=realtotal=doubletosingle=errdoubletosingle=0;
  BackGroundEstimate(FRhisto, singleFake, prova, doubleFake, finalbkg1, finalbkgerror1, finalbkg2, finalbkgerror2, realsingle, realsingleerror, realdouble, realtotal, doubletosingle, errdoubletosingle);

  cout<<"Single Fake n "<<nSingleFake<<" value "<<SingleFake<<endl;
  h_singlefake->SetBinContent(3,finalbkg1);
  h_singlefake->SetBinError(3,finalbkgerror1);
  h_singlefake->SetBinContent(1,realsingle);
  h_singlefake->SetBinError(1,realsingleerror);
  h_doublefake->SetBinContent(3,finalbkg2);
  h_doublefake->SetBinError(3,finalbkgerror2);
  h_doublefake->SetBinContent(1,realdouble);
  h_doublefake->SetBinContent(2,doubletosingle);
  h_doublefake->SetBinError(2,errdoubletosingle);
  cout<<"Double Fake n "<<nDoubleFake<<" value "<<DoubleFake<<endl;
  cout<<"Single_Double "<<Single_Double<<endl;
  cout<<"totale "<<realtotal<<endl;
}
