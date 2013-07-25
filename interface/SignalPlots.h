#ifndef SignalPlots_h
#define SignalPlots_h

#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "Lepton.h"
#include "Jet.h"

class SignalPlots {

 public:
  TH1F *h_jjmass, *h_llmass, *h_l1jjmass, *h_l2jjmass, *h_lljjmass, *h_MET;
  TH2F *h_WandNmass;
  TH1F *h_leadingMuonPt, *h_secondMuonPt, *h_leadingJetPt, *h_secondJetPt;
  TH1F *h_leadingMuonIso, *h_secondMuonIso;
 
  SignalPlots(TString name);
  ~SignalPlots();
  void Fill(Double_t MET, std::vector<Lepton>& muons, std::vector<Jet>& jets, Double_t weight, Bool_t ptok, Bool_t ssok);
  void Fill(Double_t MET, std::vector<Lepton>& muons, std::vector<Lepton>& muonsloose, std::vector<Jet>& jets, Double_t weight, Bool_t ptok, Bool_t ssok);
  void Write();

};


#endif
