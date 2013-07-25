#include "OtherFunctionsPR.h"

void SinglebackGroundPR(std::vector<Lepton>& leptonColli, UInt_t &ilep, std::vector<Lepton>& leptonCollj, UInt_t &jlep, Double_t ****fakeN, Double_t weight) {
  double arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  double arraypT[] = {10,15,20,25,35};
  int n=5;

  int i0=1; int j0=1;
  int i1=1; int j1=1;
  double eta0= fabs(leptonColli[ilep].eta());
  double Pt0 = leptonColli[ilep].lorentzVec().Pt();
  double eta1= fabs(leptonCollj[jlep].eta());
  double Pt1 = leptonCollj[jlep].lorentzVec().Pt();

  while(1) {
    if( arrayeta[(i0-1)%n]<=eta0 && arrayeta[i0%n]>eta0 )
      break;
    i0++;
  }
  if (Pt0>=35.0) j0=4;
  else {
    while(1) {
      if( arraypT[(j0-1)%n]<=Pt0 && arraypT[j0%n]>Pt0 )
        break;
      j0++;
    }
  }

  while(1) {
    if( arrayeta[(i1-1)%n]<=eta1 && arrayeta[i1%n]>eta1 )
      break;
    i1++;
  }
  if (Pt1>=35.0) j1=4;
  else {
    while(1) {
      if( arraypT[(j1-1)%n]<=Pt1 && arraypT[j1%n]>Pt1 )
        break;
      j1++;
    }
  }

  fakeN[i0-1][j0-1][i1-1][j1-1]+=weight;
}

void DoublebackGroundPR(std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep, Double_t ****fakeN, Double_t weight) {
  double arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  double arraypT[] = {10,15,20,25,35};
  int n=5;

  int i0=1; int j0=1;
  int i1=1; int j1=1;
  double eta0= fabs(leptonColl[ilep].eta());
  double Pt0 = leptonColl[ilep].lorentzVec().Pt();
  double eta1= fabs(leptonColl[jlep].eta());
  double Pt1 = leptonColl[jlep].lorentzVec().Pt();
  if (eta0<0.0 || eta0>=2.5) {cout<<"CACCHIO eta!!!! "<<eta0<<endl; eta0<0.0 ? eta0=0.0 : eta0=2.49;}
  if (Pt0<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt0<<endl; Pt0=10.0;}
  if (eta1<0.0 || eta1>=2.5) {cout<<"CACCHIO eta!!!! "<<eta1<<endl; eta1<0.0 ? eta1=0.0 : eta1=2.49;}
  if (Pt1<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt1<<endl; Pt1=10.0;}

  while(1) {
    if( arrayeta[(i0-1)%n]<=eta0 && eta0<arrayeta[i0%n] ) 
      break;
    i0++;
  }
  if (Pt0>=35.0) j0=4;
  else {
    while(1) {
      if( arraypT[(j0-1)%n]<=Pt0 && Pt0<arraypT[j0%n] )
	break;
      j0++;
    }
  }

  while(1) {
    if( arrayeta[(i1-1)%n]<=eta1 && eta1<arrayeta[i1%n] )
      break;
    i1++;
  }
  if (Pt1>=35.0) j1=4;
  else {
    while(1) {
      if( arraypT[(j1-1)%n]<=Pt1 && Pt1<arraypT[j1%n] )
	break;
      j1++;
    }
  }
   
  fakeN[i0-1][j0-1][i1-1][j1-1]+=weight;
}

void BackGroundEstimatePR(TH2F* fakerate, TH2F* promptratio, Double_t ****Nt0, Double_t ****Nt1, Double_t ****Nt2, Double_t &singolo, Double_t &errsingolo, Double_t &doppio, Double_t &errdoppio, Double_t &totale) {
  UInt_t nbinX=fakerate->GetNbinsX(); UInt_t nbinY=fakerate->GetNbinsY();
  Double_t tmperrsingolo, tmperrdoppio;
  tmperrsingolo=tmperrdoppio=0;
  for (UInt_t i=0; i<nbinX; i++)
    for (UInt_t j=0; j<nbinY; j++)
      for (UInt_t m=0; m<nbinX; m++)
	for (UInt_t n=0; n<nbinY; n++) {
          if (Nt0[i][j][m][n] || Nt1[i][j][m][n] || Nt2[i][j][m][n]) {
            Double_t FRi = fakerate->GetBinContent(i+1,j+1);
            Double_t FRm = fakerate->GetBinContent(m+1,n+1);
            Double_t deltaFRi = fakerate->GetBinError(i+1,j+1);
            Double_t deltaFRm = fakerate->GetBinError(m+1,n+1);
            Double_t PRi = promptratio->GetBinContent(i+1,j+1);
	    Double_t PRm = promptratio->GetBinContent(m+1,n+1);
	    Double_t deltaPRi = promptratio->GetBinError(i+1,j+1);
            Double_t deltaPRm = promptratio->GetBinError(m+1,n+1);

	    totale+= PRm*PRi/((PRi-FRm)*(PRm-FRm)) * (FRm*FRm*Nt0[i][j][m][n] + (-1+FRm)*FRm*Nt1[i][j][m][n] + (-1+FRm)*(-1+FRm)*Nt2[i][j][m][n]);
    
	    singolo+= PRi*FRm/(PRi-FRm)* 1/((PRi-FRi)*(PRm-FRm)) * (
                      Nt0[i][j][m][n]* (-(1-FRi)*FRm*PRi*PRm - FRi*(1-FRm)*PRi*PRm + FRi*FRm*(1-PRi)*PRm + FRi*FRm*PRi*(1-PRm)) +
                      Nt1[i][j][m][n]* ((1-FRi)*(1-FRm)*PRi*PRm - FRi*FRm*(1-PRi)*(1-PRm)) +
                      Nt2[i][j][m][n]* (-(1-FRi)*(1-FRm)*(1-PRi)*PRm - (1-FRi)*(1-FRm)*PRi*(1-PRm) + (1-FRi)*FRm*(1-PRi)*(1-PRm) + FRi*(1-FRm)*(1-PRi)*(1-PRm)) );

            tmperrsingolo+=1;

            doppio+= FRm*FRi/((PRi-FRi)*(PRi-FRm)) * (Nt0[i][j][m][n]*PRi*PRi + Nt1[i][j][m][n]*(-1+PRi)*PRi + Nt2[i][j][m][n]*(-1+PRi)*(-1+PRi));

	    tmperrdoppio+=1;

	  }
	}
  errsingolo=sqrt(tmperrsingolo);
  errdoppio=sqrt(tmperrdoppio);
}
