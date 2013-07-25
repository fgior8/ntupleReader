#include "SignalPlots.h"

SignalPlots::SignalPlots(TString name) {
  h_jjmass =         new TH1F("h_dijetsmass_"    + name,"Invariant mass of the two leading jets",100,0,1000);
  h_llmass =         new TH1F("h_llmass_"        + name,"Invariant mass of the two leading muons",100,0,1000);
  h_l1jjmass =       new TH1F("h_l1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  h_l2jjmass =       new TH1F("h_l2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  h_lljjmass =       new TH1F("h_lljjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
  h_WandNmass =      new TH2F("h_WandNmass_"     + name,"Invariant mass of the W and the N",200,0,2000,200,0,2000);
  h_leadingMuonPt =  new TH1F("h_leadingMuonPt_" + name,"leading muon pt",60,0,300);
  h_secondMuonPt =   new TH1F("h_secondMuonPt_"  + name,"secondary muon pt",60,0,300);
  h_leadingJetPt =   new TH1F("h_leadingJetPt_"  + name,"leading jet pt",60,0,300);
  h_secondJetPt =    new TH1F("h_secondJetPt_"   + name,"secondary jet pt",60,0,300);
  h_leadingMuonIso = new TH1F("h_leadingMuonIso_"+ name,"leading muon relIso",40,0,0.4);
  h_secondMuonIso =  new TH1F("h_secondMuonIso_" + name,"secondary muon relIso",40,0,0.4);
  h_MET =            new TH1F("h_MET_"           + name,"Missing Et",50,0.0,500.0);
}

SignalPlots::~SignalPlots() {
  delete h_jjmass;
  delete h_llmass;
  delete h_l1jjmass;
  delete h_l2jjmass;
  delete h_lljjmass;
  delete h_WandNmass;
  delete h_leadingMuonPt;
  delete h_secondMuonPt;
  delete h_leadingJetPt;
  delete h_secondJetPt;
  delete h_leadingMuonIso;
  delete h_secondMuonIso;
  delete h_MET;
}

void SignalPlots::Fill(Double_t MET, std::vector<Lepton>& muons, std::vector<Jet>& jets, Double_t weight, Bool_t ptok, Bool_t ssok) {
  // Double_t jets2mass;
  for(UInt_t i=0; i<muons.size()-1; i++)
    for(UInt_t j=i+1; j<muons.size(); j++) {
      if (muons[i].charge()*muons[j].charge()>0 || ssok)
	if (muons[i].lorentzVec().Pt()>=20 || ptok) {
	  /*
	  for(UInt_t m=0; m<jets.size()-1; m++)
	   for(UInt_t n=1; n<jets.size(); n++) {
	     jets2mass=(jets[m].lorentzVec()+jets[n].lorentzVec()).M();
	     if (jets2mass<300) goto duejetsmass;
	   }
	duejetsmass:
	  */
          h_MET->Fill(MET, weight);
	  Int_t m=0; Int_t n=1;
	  h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_llmass->Fill( (muons[i].lorentzVec()+muons[j].lorentzVec()).M(),weight);
	  h_l1jjmass->Fill( (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_l2jjmass->Fill( (muons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_lljjmass->Fill( (muons[i].lorentzVec()+muons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_WandNmass->Fill( (muons[i].lorentzVec()+muons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M() , (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_leadingMuonPt->Fill( muons[i].lorentzVec().Pt(),weight);
	  h_secondMuonPt->Fill( muons[j].lorentzVec().Pt(),weight);
	  h_leadingJetPt->Fill( jets[m].lorentzVec().Pt(),weight);
	  h_secondJetPt->Fill( jets[n].lorentzVec().Pt(),weight);
	  h_leadingMuonIso->Fill( muons[i].relIso(),weight);
	  h_secondMuonIso->Fill( muons[j].relIso(),weight);
	}
   }
}

void SignalPlots::Fill(Double_t MET, std::vector<Lepton>& muons, std::vector<Lepton>& muonsloose, std::vector<Jet>& jets, Double_t weight, Bool_t ptok, Bool_t ssok) {
  //Double_t jets2mass;
  for(UInt_t i=0; i<muons.size(); i++)
    for(UInt_t j=0; j<muonsloose.size(); j++) {
      if (muons[i].charge()*muonsloose[j].charge()>0 || ssok)
	if (muons[i].lorentzVec().Pt()>=20 || muonsloose[j].lorentzVec().Pt()>=20 || ptok) {
	  if (muons[i].lorentzVec().Pt()>=muonsloose[j].lorentzVec().Pt()) {
          /*
          for(UInt_t m=0; m<jets.size()-1; m++)
           for(UInt_t n=1; n<jets.size(); n++) {
             jets2mass=(jets[m].lorentzVec()+jets[n].lorentzVec()).M();
             if (jets2mass<300) goto duejetsmass;
           }
        duejetsmass:
          */
          h_MET->Fill(MET, weight);
          Int_t m=0; Int_t n=1;
          h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_llmass->Fill( (muons[i].lorentzVec()+muonsloose[j].lorentzVec()).M(),weight);
          h_l1jjmass->Fill( (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_l2jjmass->Fill( (muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_lljjmass->Fill( (muons[i].lorentzVec()+muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_WandNmass->Fill( (muons[i].lorentzVec()+muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M() , (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_leadingMuonPt->Fill( muons[i].lorentzVec().Pt(),weight);
          h_secondMuonPt->Fill( muonsloose[j].lorentzVec().Pt(),weight);
          h_leadingJetPt->Fill( jets[m].lorentzVec().Pt(),weight);
          h_secondJetPt->Fill( jets[n].lorentzVec().Pt(),weight);
          h_leadingMuonIso->Fill( muons[i].relIso(),weight);
          h_secondMuonIso->Fill( muonsloose[j].relIso(),weight);
          goto fine;
          }
	  else {
	  /*
	  for(UInt_t m=0; m<jets.size()-1; m++)
	   for(UInt_t n=1; n<jets.size(); n++) {
	     jets2mass=(jets[m].lorentzVec()+jets[n].lorentzVec()).M();
	     if (jets2mass<300) goto duejetsmass;
	   }
	duejetsmass:
	  */
          h_MET->Fill(MET, weight);
	  Int_t m=0; Int_t n=1;
	  h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_llmass->Fill( (muonsloose[j].lorentzVec()+muons[i].lorentzVec()).M(),weight);
          h_l1jjmass->Fill( (muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_l2jjmass->Fill( (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_lljjmass->Fill( (muonsloose[j].lorentzVec()+muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_WandNmass->Fill( (muonsloose[j].lorentzVec()+muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M() , (muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_leadingMuonPt->Fill( muonsloose[j].lorentzVec().Pt(),weight);
          h_secondMuonPt->Fill( muons[i].lorentzVec().Pt(),weight);
          h_leadingJetPt->Fill( jets[m].lorentzVec().Pt(),weight);
          h_secondJetPt->Fill( jets[n].lorentzVec().Pt(),weight);
          h_leadingMuonIso->Fill( muonsloose[j].relIso(),weight);
          h_secondMuonIso->Fill( muons[i].relIso(),weight);
	  goto fine;
          }
       }
   }
 fine:
;
}

void SignalPlots::Write() {
  h_jjmass->Write();
  h_llmass->Write();
  h_l1jjmass->Write();
  h_l2jjmass->Write();
  h_lljjmass->Write();
  h_WandNmass->Write();
  h_leadingMuonPt->Write();
  h_secondMuonPt->Write();
  h_leadingJetPt->Write();
  h_secondJetPt->Write();
  h_leadingMuonIso->Write();
  h_secondMuonIso->Write();
  h_MET->Write();
}

