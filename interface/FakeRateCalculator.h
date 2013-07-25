#ifndef FakeRateCalculator_h
#define FakeRateCalculator_h

#include "Analyzer.h"

class FRCalculator : public Analyzer {

  TH2F *h_nEvents, *h_nEventsFO, *h_FOrate;
  MuonSel MuonLoose;
  UInt_t index;
  MuonPlots *h_TLnum, *h_TLden;

 public:

  FRCalculator();
  ~FRCalculator();

  void LoopFR();

};
#endif
