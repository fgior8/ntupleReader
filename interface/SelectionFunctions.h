#ifndef SelectionFunctions_h
#define SelectionFunctions_h

#include <iostream>
using namespace std;

#include "Lepton.h"
#include <vector>

static const Double_t Mass_Z = 91.1876;
static const Double_t Mass_W = 80.398;

Bool_t isGoodEvent(Int_t nVertex, Double_t *Vertex_Ndof, Double_t *Vertex_X, Double_t *Vertex_Y, Double_t *Vertex_Z, Double_t beamspot_x, Double_t beamspot_y, Bool_t *goodVerticies);

Bool_t ZandWveto(std::vector<Lepton>& leptonColl, Double_t MET, Double_t METx, Double_t METy);

Bool_t Zselection(std::vector<Lepton>& leptonColl, Double_t MET);
 
#endif

