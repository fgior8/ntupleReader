#include "OtherFunctions.h"

int nthdigit(int x, int n) {
  static int powersof10[] = {1, 10, 100, 1000, 10000, 100000};
  return ((x / powersof10[n]) % 10);
}

bool isPrompt(long pdgid) {
  pdgid = abs(pdgid);
  /*if (pdgid >= 1000001 && pdgid <= 1000006) return true; // SUSY squarks
  else if (pdgid >= 1000011 && pdgid <= 1000016) return true; // SUSY sleptons sneutrinos
  else if (pdgid >= 2000001 && pdgid <= 2000006) return true; // SUSY squarks
  else if (pdgid >= 2000011 && pdgid <= 2000015) return true; // SUSY sleptons
  else if (pdgid >= 1000021 && pdgid <= 1000025) return true; // SUSY gluino chargino neutralinos
  else if (pdgid >= 1000035 && pdgid <= 1000039) return true; // SUSY neutralinos charginos gravitino*/
  if (pdgid == 24) return true; // Z
  else if (pdgid == 23) return true; // W
  else if (pdgid == 15) return true; // taus
  else if (pdgid == 90) return true; // N
  else if (pdgid == 13) return true;
  else return false;
  //  return indexToPromptBool[ abs(pdgToIndex[pdgid]) ];
}


void getFakerate(TH2F* h1, TH2F* h2, TH2F* out, int nbinX, int nbinY) {
   double frate,ferr;
   for (int i=1; i<nbinX+1; i++)
      for (int j=1; j<nbinY+1; j++){
         double a = h1->GetBinContent(i,j);
         double b = h2->GetBinContent(i,j);
         if (b){
            frate = ((double) a)/((double) b);
            ferr = sqrt( frate*(1-frate)/(double) b); 
            out->SetBinContent(i,j,frate);
            out->SetBinError(i,j,ferr);
         }
         else {
            out->SetBinContent(i,j,0);
         }
   }
}

void FunzioProva(std::vector<Lepton>& leptonColli, UInt_t &ilep, std::vector<Lepton>& leptonCollj, UInt_t &jlep, Double_t ****fakeN) {
  double arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  double arraypT[] = {10,15,20,25,35};
  int n=5;

  int i0=1; int j0=1;
  int i1=1; int j1=1;
  double eta0= fabs(leptonColli[ilep].eta());
  double Pt0 = leptonColli[ilep].lorentzVec().Pt();
  double eta1= fabs(leptonCollj[jlep].eta());
  double Pt1 = leptonCollj[jlep].lorentzVec().Pt();
  if (eta0<0.0 || eta0>=2.5) {cout<<"CACCHIO eta!!!! "<<eta0<<endl; eta0<0.0 ? eta0=0.0 : eta0=2.49;} 
  if (Pt0<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt0<<endl; Pt0=10.0;}
  if (eta1<0.0 || eta1>=2.5) {cout<<"CACCHIO eta!!!! "<<eta1<<endl; eta1<0.0 ? eta1=0.0 : eta1=2.49;}
  if (Pt1<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt1<<endl; Pt1=10.0;}

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

  fakeN[i1-1][j1-1][i0-1][j0-1]+=1;
}

double DoublebackGround(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep, Double_t ****fakeN, Double_t weight) {
  double bkg=0;
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
  
  double A = fakerate->GetBinContent(i0,j0);
  double B = fakerate->GetBinContent(i1,j1);
  //double deltaA = fakerate->GetBinError(i0,j0);
  //double deltaB = fakerate->GetBinError(i1,j1);
  
  fakeN[i0-1][j0-1][i1-1][j1-1]+=weight;

  bkg = A*B / (( 1-A )*( 1-B ));
  //errbkg = sqrt ( ( B*(1-B)*deltaA+A*(1-A)*deltaB )/( pow(1-A,2)*pow(1-B,2) ) );

  return bkg;
}

double SinglebackGround(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, Double_t **fakeN, Double_t weight) {
  double bkg=0;
  double arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  double arraypT[] = {10,15,20,25,35};
  int n=5;

  int i=1; int j=1;
  double eta= fabs(leptonColl[ilep].eta());
  double Pt = leptonColl[ilep].lorentzVec().Pt();
  if (eta<0.0 || eta>=2.5) {cout<<"CACCHIO eta!!!! "<<eta<<endl; eta<0.0 ? eta=0.0 : eta=2.49;}
  if (Pt<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt<<endl; Pt=10.0;}

  while(1) {
    if( arrayeta[(i-1)%n]<=eta && eta<arrayeta[i%n] )
      break;
    i++;
  }
  if (Pt>=35.0) j=4;
  else {
    while(1) {
      if( arraypT[(j-1)%n]<=Pt && Pt<arraypT[j%n] ) 
	break;
      j++;
    }
  }

  fakeN[i-1][j-1]+=weight;

  bkg = fakerate->GetBinContent(i,j) /( 1-fakerate->GetBinContent(i,j) );
  //errbkg = fakerate->GetBinError(i,j) / pow( 1-fakerate->GetBinContent(i,j),2 );
  
  return bkg; 
}

double Single_Doublebkg(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep) {
  double bkg=0;
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
  
  double A = fakerate->GetBinContent(i0,j0);
  double B = fakerate->GetBinContent(i1,j1);

  bkg = (-A/(1-A))* (A*(1-B)+B*(1-A)) / (( 1-A )*( 1-B ));

  return bkg;
}


void BackGroundEstimate(TH2F* fakerate,  Double_t **fakeN1, Double_t ****prova, Double_t ****fakeN2, Double_t &singolo, Double_t &errsingolo, Double_t &doppio, Double_t &errdoppio, Double_t &singoloreale, Double_t &errsingoloreale, Double_t &doppioreale, Double_t &totale, Double_t &doubletosingle, Double_t &errdoubletosingle) {
  UInt_t nbinX=fakerate->GetNbinsX(); UInt_t nbinY=fakerate->GetNbinsY();
  Double_t tmperrsingolo, tmperrdoppio, tmperrsingoloreale, tmpdoubletosinglerr;
  tmperrsingolo=tmperrdoppio=tmperrsingoloreale=tmpdoubletosinglerr=0;
  for (UInt_t i=1; i<nbinX+1; i++)
    for (UInt_t j=1; j<nbinY+1; j++) {
      if (fakeN1[i-1][j-1]) {
	Double_t FR = fakerate->GetBinContent(i,j);
	Double_t deltaFR = fakerate->GetBinError(i,j);
	singolo+=fakeN1[i-1][j-1]*FR/(1-FR);
	tmperrsingolo+=pow(fakeN1[i-1][j-1],2)*pow( (deltaFR/pow( (1-FR) ,2)) ,2) + fakeN1[i-1][j-1]*pow(FR/(1-FR),2);
      }
      for (UInt_t m=1; m<nbinX+1; m++)
	for (UInt_t n=1; n<nbinY+1; n++) {
	  if (fakeN2[i-1][j-1][m-1][n-1]) {
	    Double_t FRi = fakerate->GetBinContent(i,j);
	    Double_t deltaFRi = fakerate->GetBinError(i,j);
	    Double_t FRm = fakerate->GetBinContent(m,n);
	    Double_t deltaFRm = fakerate->GetBinError(m,n);
	    Double_t W = FRi*FRm / ((1-FRi)*(1-FRm));
	    Double_t deltaW = sqrt( ( pow(FRi*(1-FRi), 2)*pow(deltaFRm,2) + pow(FRm*(1-FRm), 2)*pow(deltaFRi,2 ) ) / ( pow( (1-FRi) ,4)*pow( (1-FRm) ,4) ) );
	    doppio+=fakeN2[i-1][j-1][m-1][n-1]*W;
	    tmperrdoppio+=pow(fakeN2[i-1][j-1][m-1][n-1],2)*pow(deltaW,2) + fakeN2[i-1][j-1][m-1][n-1]*pow(W,2);
          }  
          if (fakeN2[i-1][j-1][m-1][n-1] || prova[i-1][j-1][m-1][n-1]) {
            Double_t FRi = fakerate->GetBinContent(i,j);
            Double_t FRm = fakerate->GetBinContent(m,n);
            Double_t deltaFRi = fakerate->GetBinError(i,j);
            Double_t deltaFRm = fakerate->GetBinError(m,n);
	    Double_t singolorealetmp= FRi/(1-FRi) * ( prova[i-1][j-1][m-1][n-1] - ( fakeN2[i-1][j-1][m-1][n-1] * ( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)) ) );
            singoloreale+= FRi/(1-FRi) * ( prova[i-1][j-1][m-1][n-1] - ( fakeN2[i-1][j-1][m-1][n-1] * ( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)) ) );
            tmperrsingoloreale+=pow(prova[i-1][j-1][m-1][n-1], 2)*pow(deltaFRi/pow(1-FRi,2), 2) + prova[i-1][j-1][m-1][n-1]*pow(FRi/(1-FRi), 2) + pow(fakeN2[i-1][j-1][m-1][n-1], 2)*(pow(FRm-1, 2)*pow(FRm+FRi*(2-3*FRm), 2)*pow(deltaFRi,2) + pow(FRi-1, 4)*pow(FRi, 2)*pow(deltaFRm,2)) / (pow( (FRi-1) ,6)*pow( (FRm-1) ,4)) + fakeN2[i-1][j-1][m-1][n-1]*pow( (( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)))*FRi/(1-FRi) ,2);
            Double_t doppiorealetmp= FRi*FRm*fakeN2[i-1][j-1][m-1][n-1] / ((1-FRi)*(1-FRm));
            doppioreale+= FRi*FRm*fakeN2[i-1][j-1][m-1][n-1] / ((1-FRi)*(1-FRm));
            totale+=singolorealetmp + doppiorealetmp;

	    doubletosingle += fakeN2[i-1][j-1][m-1][n-1] * ( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm));
	    tmpdoubletosinglerr += fakeN2[i-1][j-1][m-1][n-1]*pow(( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)),2) + pow(fakeN2[i-1][j-1][m-1][n-1]*deltaFRi/pow(1-FRi,2),2) + pow(fakeN2[i-1][j-1][m-1][n-1]*deltaFRm/pow(1-FRm,2),2);
	  }
	  
	}
    }
  errsingoloreale=sqrt(tmperrsingoloreale);
  errsingolo=sqrt(tmperrsingolo);
  errdoppio=sqrt(tmperrdoppio);
  errdoubletosingle=sqrt(tmpdoubletosinglerr);
}

void WeigthedMean(std::vector<double>& value, std::vector<double>& error, double &mean, double &stddev) {
if (value.size()>0) {
  double DEN=0; double NUM=0; double weight;
  for(UInt_t iii=0; iii<value.size(); iii++) {
    weight=1/pow(error[iii],2);
    DEN+=weight;
    NUM+=value[iii]*weight;
  }
    mean=NUM/DEN;
    stddev=sqrt(1/DEN);
 }   
}

Double_t TriggerWeight(stringtobool* HLT_triggered) {

  Char_t name[20];
  Int_t pt[]={5,8,12,15,30};
 
  Int_t mu5[]={0,0,40,100,100,150,0,320,320,640,320,320,320};
  Int_t mu8[]={4,20,20,0,60,120,120,40,80,80,80,0,0};
  Int_t mu12[]={10,420,420,0,630,450,450,70,70,70,70,0,0};
  Int_t mu15[]={0,1,160,160,0,240,720,720,65,25,25,25,0};
  Int_t mu30[]={1,1,1,0,25,80,80,10,4,4,4,0,0};
  Int_t L1_Mu3[]={60,90,120,180,240,600};
  Int_t L1_Mu7[]={1,1,40,60,80,100};
  Int_t L1_Mu10[]={1,1,1,20,30,80};
  Int_t L1_Mu12[]={1,1,1,15,20,60};

  Int_t all[5][13];
  for(Int_t i=0;i<5;i++)
    for(Int_t j=0;j<13;j++) {
      switch (i) {
	case 0:
	  if(j<4)
	    all[i][j]=mu5[j]*L1_Mu3[0];
	  else if(j<7)
	    all[i][j]=mu5[j]*L1_Mu3[1];
	  else if (j<8)
	    all[i][j]=mu5[j]*L1_Mu3[2];
	  else if (j<9)
	    all[i][j]=mu5[j]*L1_Mu3[3];
	  else if (j<10)
	    all[i][j]=mu5[j]*L1_Mu3[4];
	  else if (j<13)
	    all[i][j]=mu5[j]*L1_Mu3[5];
	  else 
	    all[i][j]=0;
	  break;
	case 1:
	  if(j<2)
	    all[i][j]=mu8[j]*L1_Mu3[0];
	  else if(j<5)
	    all[i][j]=mu8[j]*L1_Mu3[1];
	  else if (j<6)
	    all[i][j]=mu8[j]*L1_Mu3[2];
	  else if (j<7)
	    all[i][j]=mu8[j]*L1_Mu3[3];
	  else if (j<8)
	    all[i][j]=mu8[j]*L1_Mu3[4];
	  else if (j<11)
	    all[i][j]=mu8[j]*L1_Mu3[5];
	  else
	    all[i][j]=0;
	  break;
	case 2:
	  if(j<2)
	    all[i][j]=mu12[j]*L1_Mu7[0];
	  else if(j<5)
	    all[i][j]=mu12[j]*L1_Mu7[1];
	  else if (j<6)
	    all[i][j]=mu12[j]*L1_Mu7[2];
	  else if (j<7)
	    all[i][j]=mu12[j]*L1_Mu7[3];
	  else if (j<8)
	    all[i][j]=mu12[j]*L1_Mu7[4];
	  else if (j<11)
	    all[i][j]=mu12[j]*L1_Mu7[5];
	  else
	    all[i][j]=0;
	  break;
	case 3:
	  if(j<3)
	    all[i][j]=mu15[j]*L1_Mu10[0];
	  else if(j<6)
	    all[i][j]=mu15[j]*L1_Mu10[1];
	  else if (j<7)
	    all[i][j]=mu15[j]*L1_Mu10[2];
	  else if (j<8)
	    all[i][j]=mu15[j]*L1_Mu10[3];
	  else if (j<9)
	    all[i][j]=mu15[j]*L1_Mu10[4];
	  else if (j<12)
	    all[i][j]=mu15[j]*L1_Mu10[5];
	  else
	    all[i][j]=0;
	  break;
	case 4:
	  if(j<2)
	    all[i][j]=mu30[j]*L1_Mu12[0];
	  else if(j<5)
	    all[i][j]=mu30[j]*L1_Mu12[1];
	  else if (j<6)
	    all[i][j]=mu30[j]*L1_Mu12[2];
	  else if (j<7)
	    all[i][j]=mu30[j]*L1_Mu12[3];
	  else if (j<8)
	    all[i][j]=mu30[j]*L1_Mu12[4];
	  else if (j<11)
	    all[i][j]=mu30[j]*L1_Mu12[5];
	  else
	    all[i][j]=0;
	  break;
	}
    }

  for(Int_t i=4;i>=0;i--)
    for(Int_t ver=0;ver<13;ver++) {
      strcpy(name,"");strcpy(name,"");
      sprintf(name,"HLT_Mu%i_v%i",pt[i],ver+1);
      
      if ( HLT_triggered->find(name) != HLT_triggered->end() && (*HLT_triggered)[name] )
	return all[i][ver];
   
    }
  return -1;
 
}
