void TestBeamA () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *root_file = TFile::Open("testbeam.root");

  TTree *tree = (TTree *) root_file->Get("T");

  //------------------------ Branches variables ------------------------//

  const int n_channels = 8;

  Float_t timeCFD[n_channels];
  Float_t sigChargeInWindowVT[n_channels];

  tree->SetBranchAddress("timeCFD", &timeCFD);
  tree->SetBranchAddress("sigChargeInWindowVT", &sigChargeInWindowVT);

  //--------------------------------------------------------------------//

  //---------------------------- Histograms ----------------------------//

  TH1F *hist_timeCFD_module_1 = new TH1F(
    "timeCFD Module 1",
    "timeCFD Module 1; Time; Events",
    100,
    0,
    330
  );

  TH1F *hist_timeCFD_module_2 = new TH1F(
    "timeCFD Module 2",
    "timeCFD Module 2; Time; Events",
    100,
    0,
    330
  );

  TH1F *hist_timeCFD_diff = new TH1F(
    "timeCFD Diff",
    "timeCFD Diff; Time; Events",
    100,
    0,
    50
  );

  TH1F *hist_sigChargeInWindowVT_module_1 = new TH1F(
    "sigChargeInWindowVT Module 1",
    "sigChargeInWindowVT Module 1; Charge; Events",
    100,
    -3,
    10
  );

  TH1F *hist_sigChargeInWindowVT_module_2 = new TH1F(
    "sigChargeInWindowVT Module 2",
    "sigChargeInWindowVT Module 2; Charge; Events",
    100,
    -3,
    10
  );

  std::vector<int> trigger_keys = {
    5, 6, 7, 8, 9, 10
  };

  std::map<int, TH1F*> hists_sigChargeInWindowVT_trigger2;
  std::map<int, TH1F*> hists_sigChargeInWindowVT_trigger1;

  for (size_t i = 0; i < trigger_keys.size(); i++) {

    hists_sigChargeInWindowVT_trigger1[trigger_keys[i]] = new TH1F(
      "sigChargeInWindowVT module 1 timetrigger " +
      TString(std::to_string(trigger_keys[i]).c_str()),
      "sigChargeInWindowVT module 1 timetrigger " +
      TString(std::to_string(trigger_keys[i]).c_str()) +
      TString("; Charge; Events"),
      100,
      -0.25,
      4.5
    );

    hists_sigChargeInWindowVT_trigger2[trigger_keys[i]] = new TH1F(
      "sigChargeInWindowVT module 2 timetrigger " +
      TString(std::to_string(trigger_keys[i]).c_str()),
      "sigChargeInWindowVT module 2 timetrigger " +
      TString(std::to_string(trigger_keys[i]).c_str()) +
      TString("; Charge; Events"),
      100,
      -0.25,
      6
    );

  }

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Fill histograms.

    hist_timeCFD_module_1->Fill(timeCFD[1]);
    hist_timeCFD_module_2->Fill(timeCFD[2]);

    hist_sigChargeInWindowVT_module_1->Fill(sigChargeInWindowVT[1]);
    hist_sigChargeInWindowVT_module_2->Fill(sigChargeInWindowVT[2]);

    double time_diff = std::abs(timeCFD[2] - timeCFD[1]);

    hist_timeCFD_diff->Fill(time_diff);

    for (size_t i = 0; i < trigger_keys.size(); i++) {

      if (time_diff <= trigger_keys[i]) {
        hists_sigChargeInWindowVT_trigger1[trigger_keys[i]]->Fill(
          sigChargeInWindowVT[1]
        );
        hists_sigChargeInWindowVT_trigger2[trigger_keys[i]]->Fill(
          sigChargeInWindowVT[2]
        );
      }

    }

  }

  //-------------------------- Darw Histograms --------------------------//

  canvas->SetLogy();

  hist_timeCFD_module_1->SetFillColor(kYellow);
  hist_timeCFD_module_1->Draw();
  canvas->Print("timeCFD_module_1.pdf");
  canvas->Clear();

  hist_timeCFD_module_2->SetFillColor(kYellow);
  hist_timeCFD_module_2->Draw();
  canvas->Print("timeCFD_module_2.pdf");
  canvas->Clear();

  hist_timeCFD_diff->SetFillColor(kYellow);
  hist_timeCFD_diff->Draw();
  canvas->Print("timeCFD_diff.pdf");
  canvas->Clear();

  hist_sigChargeInWindowVT_module_1->SetFillColor(kYellow);
  hist_sigChargeInWindowVT_module_1->Draw();
  canvas->Print("sigChargeInWindowVT_module_1.pdf");
  canvas->Clear();

  hist_sigChargeInWindowVT_module_2->SetFillColor(kYellow);
  hist_sigChargeInWindowVT_module_2->Draw();
  canvas->Print("sigChargeInWindowVT_module_2.pdf");
  canvas->Clear();

  for (size_t i = 0; i < trigger_keys.size(); i++) {

    hists_sigChargeInWindowVT_trigger1[trigger_keys[i]]->SetFillColor(kYellow);
    hists_sigChargeInWindowVT_trigger1[trigger_keys[i]]->Draw();
    canvas->Print(
      "sigChargeInWindowVT_" +
      TString(std::to_string(trigger_keys[i]).c_str()) +
      "_trigger1.pdf"
    );
    canvas->Clear();

    hists_sigChargeInWindowVT_trigger2[trigger_keys[i]]->SetFillColor(kYellow);
    hists_sigChargeInWindowVT_trigger2[trigger_keys[i]]->Draw();
    canvas->Print(
      "sigChargeInWindowVT_" +
      TString(std::to_string(trigger_keys[i]).c_str()) +
      "_trigger2.pdf"
    );
    canvas->Clear();

  }

  //---------------------------------------------------------------------//

}
