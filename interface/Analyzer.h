#ifndef Analyzer_h
#define Analyzer_h

#include <set>
#include "Data.h"
#include "MuonSelection.h"
#include "JetSelection.h"
#include "SelectionFunctions.h"
#include "OtherFunctions.h"
#include "ElectronPlots.h"
#include "MuonPlots.h"
#include "SignalPlots.h"
#include "Reweight.cc"

class Analyzer : public Data {

  Double_t ****doubleFake; Double_t **singleFake; Double_t ****prova;
  Double_t finalbkg1, finalbkgerror1, finalbkg2, finalbkgerror2, jets2mass, triggerweight, realsingle, realsingleerror, realdouble, realtotal, doubletosingle, errdoubletosingle;
  Int_t tempCharge, index;
  Char_t *completename;
  static const Bool_t debug = false; 
  Bool_t VETO, SINGLEFAKE, DOUBLEFAKE;
  static const Double_t integratedlumi = 4681.8;
  static const Double_t Mass_Z = 91.1876;
  static const Double_t Mass_W = 80.398;
  static const Double_t trigeff = 0.94;
  static const Double_t mu1scale = 0.927;
  static const Double_t mu2scale = 0.992;

  ReweightPU *reweightPU;
  TH1F *h_nvtx_norw, *h_nvtx_rw;
 
 public:
  Bool_t *goodVerticies;
  TDirectory *Dir;
  TH1F *h_prova, *h_RelIsoFR;
  TH1F *h_nVertex, *h_nVertex0, *h_nVertex1, *h_nVertex2;
  TH1F *h_nsignal, *h_singlefake, *h_doublefake;
  TH1F *h_MET, *h_METsign, *h_MuonMissCharge, *h_EventFakeType;
  TH2F *FRhisto;
  TH2I *h_LeptvsVert;

  TFile *outfile;

  Long64_t entrieslimit, nb;
  Double_t METx,METy,MET, dr, MCweight, weight;
  UInt_t VertexN;

  MuonSel MuonTight, MuonLooseButNotTight, MuonLoose;
  Lep Electron;
  JJ  JetsVeto, Jets; 
  //  std::vector<Lepton> lepton;
  ElectronPlots *h_electrons;
  MuonPlots *h_muons, *h_muonsLoose, *h_LnotT;// *h_muonCharge;
  StdPlots *h_jets, *h_jets_veto;
  //SignalPlots *h_signal3;
  SignalPlots *h_signal1, *h_signal2, *h_signal3;
  SignalPlots *h_singlefakes, *h_doublefakes, *h_single_doublefakes;

  Analyzer();
  ~Analyzer();
  void Loop();
  void SetWeight(Double_t CrossSection, Double_t nevents);
  void SetName(string name, Float_t version);
  void SetEvtN(Long64_t events);

};
#endif
