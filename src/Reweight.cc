#ifndef Reweight_h
#define Reweight_h

#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"

class ReweightPU {

  public:

    ReweightPU(TString filenameMC, TString filenameData) {

      fileMC_ = 0;
      fileData_ = 0;

      fileMC_   = new TFile(filenameMC, "READ");
      fileData_ = new TFile(filenameData, "READ");

      if (!fileMC_ || !fileData_) {
        cout << "\n\nAt least one of the Nvtx reweighting files could not be opened!\n\n";
      }

      h_MC_ = 0;
      h_Data_ = 0;

      h_MC_ = (TH1F*)fileMC_->Get("pu_MC");
      h_Data_ = (TH1D*)fileData_->Get("pileup");

      if (!h_MC_) cout << "Can't open PU mc reweight histo";
      if (!h_Data_) cout << "Can't open PU data reweight histo";
/*
      Double_t probdistFlat10[25] = {
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0698146584,
          0.0630151648,
          0.0526654164,
          0.0402754482,
          0.0292988928,
          0.0194384503,
          0.0122016783,
          0.007207042,
          0.004003637,
          0.0020278322,
          0.0010739954,
          0.0004595759,
          0.0002229748,
          0.0001028162,
          4.58337152809607E-05
      };
*/
/*
  Double_t PoissonOneXDist[35] = {
    1.45346E-01,
    6.42802E-02,
    6.95255E-02,
    6.96747E-02,
    6.92955E-02,
    6.84997E-02,
    6.69528E-02,
    6.45515E-02,
    6.09865E-02,
    5.63323E-02,
    5.07322E-02,
    4.44681E-02,
    3.79205E-02,
    3.15131E-02,
    2.54220E-02,
    2.00184E-02,
    1.53776E-02,
    1.15387E-02,
    8.47608E-03,
    6.08715E-03,
    4.28255E-03,
    2.97185E-03,
    2.01918E-03,
    1.34490E-03,
    8.81587E-04,
    5.69954E-04,
    3.61493E-04,
    2.28692E-04,
    1.40791E-04,
    8.44606E-05,
    5.10204E-05,
    3.07802E-05,
    1.81401E-05,
    1.00201E-05,
    5.80004E-06
  };
*/

 // Summer11 PU_S4, distribution obtained by averaging the number of interactions
 // in each beam crossing to estimate the true mean.  

  Double_t PoissonIntDist[25] = {
    0.104109,
    0.0703573,
    0.0698445,
    0.0698254,
    0.0697054,
    0.0697907,
    0.0696751,
    0.0694486,
    0.0680332,
    0.0651044,
    0.0598036,
    0.0527395,
    0.0439513,
    0.0352202,
    0.0266714,
    0.019411,
    0.0133974,
    0.00898536,
    0.0057516,
    0.00351493,
    0.00212087,
    0.00122891,
    0.00070592,
    0.000384744,
    0.000219377
  };


/*
  Double_t Fall2011[50] = {
    0.003388501,
    0.010357558,
    0.024724258,
    0.042348605,
    0.058279812,
    0.068851751,
    0.072914824,
    0.071579609,
    0.066811668,
    0.060672356,
    0.054528356,
    0.04919354,
    0.044886042,
    0.041341896,
    0.0384679,
    0.035871463,
    0.03341952,
    0.030915649,
    0.028395374,
    0.025798107,
    0.023237445,
    0.020602754,
    0.0180688,
    0.015559693,
    0.013211063,
    0.010964293,
    0.008920993,
    0.007080504,
    0.005499239,
    0.004187022,
    0.003096474,
    0.002237361,
    0.001566428,
    0.001074149,
    0.000721755,
    0.000470838,
    0.00030268,
    0.000184665,
    0.000112883,
    6.74043E-05,
    3.82178E-05,
    2.22847E-05,
    1.20933E-05,
    6.96173E-06,
    3.4689E-06,
    1.96172E-06,
    8.49283E-07,
    5.02393E-07,
    2.15311E-07,
    9.56938E-08
  };
*/
      h_MCmod_ = (TH1D*)h_Data_->Clone("h_MCmod_");
      for (Int_t i = 1; i < 26; i++) {
        h_MCmod_->SetBinContent(i, PoissonIntDist[i-1]);
        //h_MCmod_->SetBinContent(i, Fall2011[i-1]);
        //h_MCmod_->SetBinContent(i, h_MC_->GetBinContent(i));
        cout << h_MCmod_->GetBinContent(i) <<endl;
      }

      double int_MC_ = h_MCmod_->Integral();
      double int_Data_ = h_Data_->Integral();

      h_Data_->Divide(h_MCmod_);
      h_Data_->Scale(int_MC_ / int_Data_);

      cout << endl;
      for (Int_t i = 1; i < 26; i++)
        cout << h_Data_->GetBinContent(i) <<endl;

    }

    ~ReweightPU() {
      delete fileMC_;
      delete fileData_;
      delete h_MC_;
      delete h_MCmod_;
      delete h_Data_;
    }

    double GetWeight(int nvtx) {

      return h_Data_->GetBinContent( nvtx + 1 );

    }

  private:

    TFile* fileMC_;
    TFile* fileData_;

    TH1F* h_MC_;
    TH1D* h_MCmod_;
    TH1D* h_Data_;

};

class Reweight {

  public:
    Reweight(TString filename) {
      file_ = new TFile(filename, "READ");
      if (!file_) {
        cout << "\n\nweight file not found!"<<endl<<endl;
      }

      h_weightBC_ = (TH1F*)file_->Get("hm_met_v_mt_BC_costheta0");
      if (!h_weightBC_) {
        cout << "\n\ncostheta weightBC histogram not found!"<<endl<<endl;
      }
      else {
        h_weightBC_->Rebin(5);
        Double_t integral = h_weightBC_->Integral();
        if (integral > 0.000001)
          h_weightBC_->Scale(1./integral);
      }

      h_weightAD_ = (TH1F*)file_->Get("hm_met_v_mt_AD_costheta0");
      if (!h_weightAD_) {
        cout << "\n\ncostheta weightAD histogram not found!"<<endl<<endl;
      } else {
        h_weightAD_->Rebin(5);
        Double_t integral = h_weightAD_->Integral();
        if (integral > 0.000001)
          h_weightAD_->Scale(1./integral);
      }

      h_weightBCboost_ = (TH1F*)file_->Get("hm_BC_boost0");
      //h_weightBCboost2_ = (TH1F*)file2_->Get("hm_BC_boost0");
      if (!h_weightBCboost_){// || !h_weightBCboost2_) {
        cout << "\n\nweightBCboost histogram not found!"<<endl<<endl;
      }
      else {
        h_weightBCboost_->Rebin(2);
        //h_weightBCboost2_->Rebin(2);
        Double_t integral = h_weightBCboost_->Integral();
        //Double_t integral2 = h_weightBCboost2_->Integral();
        if (integral > 0.000001) {
          h_weightBCboost_->Scale(1./integral);
          //h_weightBCboost2_->Scale(1./integral2);
        }
      }

      h_weightADboost_ = (TH1F*)file_->Get("hm_AD_boost0");
      if (!h_weightADboost_) {
        cout << "\n\nweightADboost histogram not found!"<<endl<<endl;
      } else {
        h_weightADboost_->Rebin(2);
        Double_t integral = h_weightADboost_->Integral();
        if (integral > 0.000001)
          h_weightADboost_->Scale(1./integral);
      }

      h_weightBCeta_ = (TH1F*)file_->Get("hm_BC_eta0");
      if (!h_weightBCeta_) {
        cout << "\n\nweightBCeta histogram not found!"<<endl<<endl;
      }
      else {
        h_weightBCeta_->Rebin(2);
        Double_t integral = h_weightBCeta_->Integral();
        if (integral > 0.000001)
          h_weightBCeta_->Scale(1./integral);
      }

      h_weightADeta_ = (TH1F*)file_->Get("hm_AD_eta0");
      if (!h_weightADeta_) {
        cout << "\n\nweightADeta histogram not found!"<<endl<<endl;
      } else {
        h_weightADeta_->Rebin(2);
        Double_t integral = h_weightADeta_->Integral();
        if (integral > 0.000001)
          h_weightADeta_->Scale(1./integral);
      }
    }
    ~Reweight(void) {
      //file_->Close();
      delete file_;
    }
/*    double GetWeight(double costheta) {
      Int_t bin = 10 * (costheta + 1.)/2.;
      if (!file_) {
        std::cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weight_) {
        std::cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weight_->GetBinContent(bin);
    }
*/
    double GetWeightBC(double costheta) {
      Int_t bin = 10 * (costheta + 1.)/2. + 1;
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n"<<endl<<endl;
        return -1.;
      }
      if (!h_weightBC_) {
        cout << "\n\ncostheta weight histogram not found!"<<endl<<endl;
        return -1.;
      }
      return h_weightBC_->GetBinContent(bin);
    }

    double GetWeightAD(double costheta) {
      Int_t bin = 10 * (costheta + 1.)/2. + 1;
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n"<<endl<<endl;
        return -1.;
      }
      if (!h_weightAD_) {
        cout << "\n\ncostheta weight histogram not found!"<<endl<<endl;
        return -1.;
      }
      return h_weightAD_->GetBinContent(bin);
    }

    double GetWeightBCboost(double boost) {
      Int_t bin = 50. * (boost)/1.2 + 1;
      if (!file_) {
        std::cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightBCboost_) {
        std::cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightBCboost_->GetBinContent(bin);
    }

    double GetWeightADboost(double boost) {
      Int_t bin = 50. * (boost)/1.2 + 1;
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightADboost_) {
        cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightADboost_->GetBinContent(bin);
    }


    double GetWeightBCeta(double eta) {
      Int_t bin = 20. * (eta)/4. + 1; // 40 bins rebinned down to 20 bins;
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightBCeta_) {
        cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightBCeta_->GetBinContent(bin);
    }

    double GetWeightADeta(double eta) {
      Int_t bin = 20. * (eta)/4. + 1; // 40 bins rebinned down to 20 bins
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightADeta_) {
        cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightADeta_->GetBinContent(bin);
    }

  private:
    TFile* file_;
    TH1F* h_weightBC_;
    TH1F* h_weightAD_;
    TH1F* h_weightBCboost_;
    TH1F* h_weightADboost_;
    TH1F* h_weightBCeta_;
    TH1F* h_weightADeta_;
};

#endif
