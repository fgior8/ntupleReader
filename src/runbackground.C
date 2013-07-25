{
  gROOT->ProcessLine(".L Data.cc+");
  gROOT->ProcessLine(".L OtherFunctions.cc+");
  gROOT->ProcessLine(".L SelectionFunctions.cc+");
  gROOT->ProcessLine(".L LeptonSelection.cc+");
  gROOT->ProcessLine(".L MuonSelection.cc+");
  gROOT->ProcessLine(".L JetSelection.cc+");
  gROOT->ProcessLine(".L StdPlots.cc+");
  gROOT->ProcessLine(".L ElectronPlots.cc+");
  gROOT->ProcessLine(".L MuonPlots.cc+");
  gROOT->ProcessLine(".L SignalPlots.cc+");
  gROOT->ProcessLine(".L Analyzer.cc+");
  gROOT->ProcessLine(".L FakeRateCalculator.cc+");
  gROOT->ProcessLine(".L ChainMaker.C+");

  TString extralabel = "";

  //////////////////////////////////////////////////////////
  //                          MC                          //
  //////////////////////////////////////////////////////////

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/QCD_mu10.txt");
    FRCalculator Pippo; Pippo.Init(chain); Pippo.SetName("QCD_mu_FR",12.00); //Pippo.SetWeight(10.04, 2194752);
    std::cout << "QCD_mu\n";  Pippo.LoopFR();
    Pippo.~FRCalculator();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/QCD_mu.txt");
    FRCalculator Pippo; Pippo.Init(chain); Pippo.SetName("QCD_mu_FR",12.00); //Pippo.SetWeight(10.04, 2194752);
    std::cout << "QCD_mu\n";  Pippo.LoopFR();
    Pippo.~FRCalculator();
  }


  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/ttbar.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("ttbar",12.20); Pippo.SetWeight(94.76, 3701947);
    std::cout << "ttbar\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/singletop_tW.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("singletop_tW",12.20); Pippo.SetWeight(7.466, 814390);
    std::cout << "singletop_tW\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/singletopbar_tW.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("singletopbar_tW",12.20); Pippo.SetWeight(7.46, 809984);
    std::cout << "singletopbar_tW\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/singletop_s-channel.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("singletop_s-channel",12.20); Pippo.SetWeight(2.341, 259971);
    std::cout << "singletop_s-channel\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/singletopbar_s-channel.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("singletopbar_s-channel",12.20); Pippo.SetWeight(1.265, 137980);
    std::cout << "singletopbar_s-channel\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/singletop_t-channel.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("singletop_t-channel",12.20); Pippo.SetWeight(3.572, 3900171);
    std::cout << "singletop_t-channel\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/singletopbar_t-channel.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("singletopbar_t-channel",12.20); Pippo.SetWeight(1.843, 1944826);
    std::cout << "singletopbar_t-channel\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/ZZ_inclusive.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("ZZ_inclusive",12.20); Pippo.SetWeight(4.287, 4187885);
    std::cout << "ZZ\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/WZ_inclusive.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("WZ_inclusive",12.20); Pippo.SetWeight(10.47, 4265243);
    std::cout << "WZ\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/WW_inclusive.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("WW_inclusive",12.20); Pippo.SetWeight(27.83, 4225916);
    std::cout << "WW\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (0) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/DY_m10-20.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("DY_m10-20",12.20); Pippo.SetWeight(2659.0, 2192421);
    std::cout << "DY_m10-20\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  if (1) {
    TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/DY_m20.txt");
    Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("DY_m20",12.20); Pippo.SetWeight(1300.0, 2148325);
    std::cout << "DY_m20\n";  Pippo.Loop();
    Pippo.~Analyzer();
  }

  //////////////////////////////////////////////////////////
  //                        Data                          //
  //////////////////////////////////////////////////////////

  if (0) {
     TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/SingleMu_2011A.txt");
     // 864682443.141 (mb)^-1 
     FRCalculator Pippo; Pippo.Init(chain); Pippo.SetName("SingleMu_2011AFR",12.05); //Pippo.SetWeight(.02);
     std::cout << "mu\n";  Pippo.LoopFR();
     Pippo.~FRCalculator(); //cout<<"palle"<<endl;
  }

  if (0) {
     TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/DoubleMu_2011A_May10ReReco-v1.txt");
     // 191438641.118 (mb)^-1 
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("DoubleMu_2011A_May10ReReco-v1",12.00); //Pippo.SetWeight(.02);
     std::cout << "mu\n";  Pippo.Loop();
     Pippo.~Analyzer();
  }
 
  if (0) {
     TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/DoubleMu_2011A_PromptReco-v4.txt");
     // 884872472.556 (mb)^-1
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("DoubleMu_2011A_PromptReco-v4",12.00); //Pippo.SetWeight(.02);
     std::cout << "mu\n";  Pippo.Loop();
     Pippo.~Analyzer();
  }

  if (0) {
     TChain* chain = ChainMaker("/uscms_data/d2/fgior8/Summer2011_425/CMSSW_4_2_5/src/UserCode/ntup/code/DataSetList/DoubleMu_2011A.txt");
     // 1076311113.674 (mb)^-1 
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("DoubleMu_2011A",12.11); //Pippo.SetWeight(.02);
     std::cout << "mu\n";  Pippo.Loop();
     Pippo.~Analyzer();
  }


}

