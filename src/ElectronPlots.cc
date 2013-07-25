#include "ElectronPlots.h"

ElectronPlots::ElectronPlots(TString name) : StdPlots(name) {

  h_charge             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  h_HCalIso            = new TH1F("h_"+name+"_HCalIso",name+" HCal Iso",100,0.,10.);
  h_ECalIso            = new TH1F("h_"+name+"_ECalIso",name+" ECal Iso",100,0.,10.);
  h_TrkIso             = new TH1F("h_"+name+"_TrkIso",name+" Tracker Iso",100,0.,10.);
  h_Detector_RelIso    = new TH1F("h_"+name+"_Detector_RelIso",name+" Detector_RelIso",100,0.,1.);
  h_photonIso          = new TH1F("h_"+name+"_photonIso",name+" photon Iso",100,0.,10.);
  h_chargedHadronIso   = new TH1F("h_"+name+"_chargedHadronIso",name+" charged Hadron Iso",100,0.,10.);
  h_neutralHadronIso   = new TH1F("h_"+name+"_neutralHadronIso",name+" neutral Hadron Iso",100,0.,10.);
  h_PF_RelIso          = new TH1F("h_"+name+"_PF_RelIso",name+" Particle Flow RelIso",100,0.,1.);
  h_HCalIsoDeposit     = new TH1F("h_"+name+"_HCalIsoDeposit",name+" HCal Iso Deposit",100,0.,10.);
  h_ECalIsoDeposit     = new TH1F("h_"+name+"_ECalIsoDeposit",name+" ECal Iso Deposit",100,0.,10.);
  
}

ElectronPlots::~ElectronPlots() {
  //StdPlots::~StdPlots();
  delete h_charge;
  delete h_HCalIso;
  delete h_ECalIso;
  delete h_TrkIso;
  delete h_Detector_RelIso;
  delete h_HCalIsoDeposit;
  delete h_ECalIsoDeposit;  
  delete h_photonIso;
  delete h_chargedHadronIso;
  delete h_neutralHadronIso;
  delete h_PF_RelIso;
}

void ElectronPlots::Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &photonIso, Double_t &chargedHadronIso, Double_t &neutralHadronIso) { 
  StdPlots::Fill(1.0, N, pt, eta, phi);
  h_charge->Fill(charge);
  h_HCalIso->Fill(hCalIso);
  h_ECalIso->Fill(eCalIso);
  h_TrkIso->Fill(trkIso);
  h_photonIso->Fill(photonIso);
  h_chargedHadronIso->Fill(chargedHadronIso);
  h_neutralHadronIso->Fill(neutralHadronIso);
  h_PF_RelIso->Fill( (photonIso+chargedHadronIso+neutralHadronIso)/ pt );
  if (pt>0.01)
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) );
  else
    h_Detector_RelIso->Fill(999.9);
  h_HCalIsoDeposit->Fill(hCalIsoDeposit);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit);
}

void ElectronPlots::Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit) {
  StdPlots::Fill(1.0, N, pt, eta, phi);
  h_charge->Fill(charge);
  h_HCalIso->Fill(hCalIso);
  h_ECalIso->Fill(eCalIso);
  h_TrkIso->Fill(trkIso);
  if (pt>0.01)
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) );
  else
    h_Detector_RelIso->Fill(999.9);
  h_HCalIsoDeposit->Fill(hCalIsoDeposit);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit);
}


void ElectronPlots::Write() {
  StdPlots::Write();
  h_charge->Write();
  h_HCalIso->Write();
  h_ECalIso->Write();
  h_TrkIso->Write();
  h_Detector_RelIso->Write();
  h_HCalIsoDeposit->Write();
  h_ECalIsoDeposit->Write();
//  h_photonIso->Write();
//  h_chargedHadronIso->Write();
//  h_neutralHadronIso->Write();
//  h_PF_RelIso->Write();
}
