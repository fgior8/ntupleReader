#ifndef OtherFunctions_h
#define OtherFunctions_h

#include <iostream>
using namespace std;
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "Lepton.h"
#include "Data.h"

int nthdigit(int x, int n);

bool isPrompt(long pdgid);

void getFakerate(TH2F* h1, TH2F* h2, TH2F* out, int nbinX, int nbinY);

double DoublebackGround(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep, Double_t ****fakeN, Double_t weight);

double SinglebackGround(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, Double_t **fakeN, Double_t weight);

double Single_Doublebkg(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep);

void FunzioProva(std::vector<Lepton>& leptonColli, UInt_t &ilep, std::vector<Lepton>& leptonCollj, UInt_t &jlep, Double_t ****fakeN);

void BackGroundEstimate(TH2F* fakerate, Double_t **fakeN1, Double_t ****prova, Double_t ****fakeN2, Double_t &singolo, Double_t &errsingolo, Double_t &doppio, Double_t &errdoppio, Double_t &singoloreale, Double_t &errsingoloreale, Double_t &doppioreale, Double_t &totale, Double_t &doubletosingle, Double_t &errdoubletosingle);

void WeigthedMean(std::vector<double>& value, std::vector<double>& error, double &mean, double &stddev);

Double_t TriggerWeight(stringtobool* HLT_triggered);
 
#endif
