#include "MuonPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



MuonPlots::MuonPlots(TString name) : StdPlots(name) {

  h_charge             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  h_HCalIso            = new TH1F("h_"+name+"_HCalIso",name+" HCal Iso",100,0.,10.);
  h_ECalIso            = new TH1F("h_"+name+"_ECalIso",name+" ECal Iso",100,0.,10.);
  h_TrkIso             = new TH1F("h_"+name+"_TrkIso",name+" Tracker Iso",100,0.,10.);
  h_Detector_RelIso    = new TH1F("h_"+name+"_Detector_RelIso",name+" Detector_RelIso",100,0.,1.);
  h_Detector_RelIsorho = new TH1F("h_"+name+"_Detector_RelIso_rho",name+" Detector_RelIso #rho corrected",100,0.,1.);
  h_photonIso          = new TH1F("h_"+name+"_photonIso",name+" photon Iso",100,0.,10.);
  h_chargedHadronIso   = new TH1F("h_"+name+"_chargedHadronIso",name+" charged Hadron Iso",100,0.,10.);
  h_neutralHadronIso   = new TH1F("h_"+name+"_neutralHadronIso",name+" neutral Hadron Iso",100,0.,10.);
  h_PF_RelIso          = new TH1F("h_"+name+"_PF_RelIso",name+" Particle Flow RelIso",100,0.,1.);
  h_HCalIsoDeposit     = new TH1F("h_"+name+"_HCalIsoDeposit",name+" HCal Iso Deposit",100,0.,10.);
  h_ECalIsoDeposit     = new TH1F("h_"+name+"_ECalIsoDeposit",name+" ECal Iso Deposit",100,0.,10.);
  h_GlbChi2            = new TH1F("h_"+name+"_GlbChi2",name+" Global #chi^{2}",1000,0.,1000.);
  h_GlbNdof            = new TH1F("h_"+name+"_GlbNdof",name+" Degrees of Freedom",150,0.,150.);
  h_GlbNormChi2        = new TH1F("h_"+name+"_GlbNormChi2",name+" Global #chi^{2}/Ndof",200,0.,100.);
  h_dxy                = new TH1F("h_"+name+"_dxy",name+" transverse IP",100,0.0,0.5);
  h_dz                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",200,0.0,2.0);
}

MuonPlots::~MuonPlots() {
  // ~StdPlots();
  delete h_charge;
  delete h_HCalIso;
  delete h_ECalIso;
  delete h_TrkIso;
  delete h_Detector_RelIso;
  delete h_Detector_RelIsorho;
  delete h_HCalIsoDeposit;
  delete h_ECalIsoDeposit;  
  delete h_photonIso;
  delete h_chargedHadronIso;
  delete h_neutralHadronIso;
  delete h_PF_RelIso;
  delete h_GlbChi2;
  delete h_GlbNdof;
  delete h_GlbNormChi2;
  delete h_dxy;
  delete h_dz;
}

void MuonPlots::Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &photonIso, Double_t &chargedHadronIso, Double_t &neutralHadronIso, Double_t &Muon_GlobalChi2, Double_t &Muon_GlobalNdof, Double_t dxy, Double_t dz, Double_t &rho) { 

  Double_t AreaTrackerMu[5] = {0., 0., 0., 0., 0.};                  //   barrel/endcap
  Double_t AreaEcalMu[5]    = {0.091, 0.077, 0.055, 0.034, 0.045};   //   barrel/endcap
  Double_t AreaHcalMu[5]    = {0.029, 0.027, 0.036, 0.040, 0.054};   //   barrel/endcap
  Int_t ifid;
  if (fabs(eta) < 0.5) ifid=0;
  else if (fabs(eta) >= 0.5 && fabs(eta) < 1.0) ifid=1;
  else if (fabs(eta) >= 1.0 && fabs(eta) < 1.5) ifid=2;
  else if (fabs(eta) >= 1.5 && fabs(eta) < 2.0) ifid=3;
  else if (fabs(eta) >= 2.0 && fabs(eta) < 2.5) ifid=4;
  else ifid=-1;
  Double_t MuTkIso   = trkIso  - AreaTrackerMu[ifid] * rho;
  Double_t MuEcalIso = eCalIso  - AreaEcalMu[ifid]  * rho;
  Double_t MuHcalIso = hCalIso - AreaHcalMu[ifid] * rho;

  StdPlots::Fill(1.0, N, pt, eta, phi);
  h_charge->Fill(charge);
  h_HCalIso->Fill(hCalIso);
  h_ECalIso->Fill(eCalIso);
  h_TrkIso->Fill(trkIso);
  h_photonIso->Fill(photonIso);
  h_chargedHadronIso->Fill(chargedHadronIso);
  h_neutralHadronIso->Fill(neutralHadronIso);
  if (pt>0.01) {
    h_PF_RelIso->Fill( (photonIso+chargedHadronIso+neutralHadronIso)/ pt );
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) );
    h_Detector_RelIsorho->Fill( (MuTkIso+MuEcalIso+MuHcalIso) / pt );
  }
  h_HCalIsoDeposit->Fill(hCalIsoDeposit);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit);
  h_GlbChi2->Fill(Muon_GlobalChi2);
  h_GlbNdof->Fill(Muon_GlobalNdof);
  if (Muon_GlobalNdof>0)
    h_GlbNormChi2->Fill( (Muon_GlobalChi2/Muon_GlobalNdof) );
  else
    h_GlbNormChi2->Fill(-999.9);
  h_dxy->Fill(dxy);
  h_dz->Fill(dz);
}

void MuonPlots::Fill(Int_t N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &Muon_GlobalChi2, Double_t &Muon_GlobalNdof) {
  StdPlots::Fill(1.0, N, pt, eta, phi);
  h_charge->Fill(charge);
  h_HCalIso->Fill(hCalIso);
  h_ECalIso->Fill(eCalIso);
  h_TrkIso->Fill(trkIso);
  if (pt>0.01)
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) );
  h_HCalIsoDeposit->Fill(hCalIsoDeposit);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit);
  h_GlbChi2->Fill(Muon_GlobalChi2);
  h_GlbNdof->Fill(Muon_GlobalNdof);
  if (Muon_GlobalNdof>0)
    h_GlbNormChi2->Fill( (Muon_GlobalChi2/Muon_GlobalNdof) );
  else
    h_GlbNormChi2->Fill(-999.9);
}

void MuonPlots::Write() {
  StdPlots::Write();
  h_charge->Write();
  h_HCalIso->Write();
  h_ECalIso->Write();
  h_TrkIso->Write();
  h_Detector_RelIso->Write();
  h_Detector_RelIsorho->Write();
  h_HCalIsoDeposit->Write();
  h_ECalIsoDeposit->Write();
  h_photonIso->Write();
  h_chargedHadronIso->Write();
  h_neutralHadronIso->Write();
  h_PF_RelIso->Write();
  h_GlbChi2->Write();
  h_GlbNdof->Write();
  h_GlbNormChi2->Write();
  h_dxy->Write();
  h_dz->Write();
}
