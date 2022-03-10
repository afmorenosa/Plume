void TestBeamS () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *root_file = TFile::Open("testbeam.root");

  TTree *tree = (TTree *) root_file->Get("T");

  //------------------------ Branches variables ------------------------//

  double trigger_time1 = -1.0;
  double trigger_time2 = -1.0;

  Int_t nPhotonDetected1 = -1;
  Int_t nPhotonDetected2 = -1;

  tree->SetBranchAddress("trigger_time1", &trigger_time1);
  tree->SetBranchAddress("trigger_time2", &trigger_time2);

  tree->SetBranchAddress("nPhotonDetected1", &nPhotonDetected1);
  tree->SetBranchAddress("nPhotonDetected2", &nPhotonDetected2);

  //--------------------------------------------------------------------//

  //---------------------------- Histograms ----------------------------//

  TH1F *hist_trigger_time_1 = new TH1F(
    "Trigger time 1",
    "Trigger time 1; time; events",
    100,
    0.15,
    0.9
  );

  TH1F *hist_trigger_time_2 = new TH1F(
    "Trigger time 2",
    "Trigger time 2; time; events",
    100,
    0.9,
    1.8
  );

  TH1F *hist_trigger_time_diff = new TH1F(
    "Trigger time diff",
    "Trigger time diff; time; events",
    100,
    0.5,
    1
  );

  TH1F *hist_photons_detected_1 = new TH1F(
    "Photons Detected 1",
    "Photons Detected 1; n photons; events",
    100,
    0,
    15000
  );

  TH1F *hist_photons_detected_2 = new TH1F(
    "Photons Detected 2",
    "Photons Detected 2; n photons; events",
    100,
    0,
    16000
  );

  TH1F *hist_photons_detected_1_triggered = new TH1F(
    "Photons Detected 1 Triggered",
    "Photons Detected 1 Triggered; n photons; events",
    100,
    0,
    15000
  );

  TH1F *hist_photons_detected_2_triggered = new TH1F(
    "Photons Detected 2 Triggered",
    "Photons Detected 2 Triggered; n photons; events",
    100,
    0,
    16000
  );

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Fill histograms.
    hist_trigger_time_1->Fill(trigger_time1);
    hist_trigger_time_2->Fill(trigger_time2);

    double time_diff = trigger_time2 - trigger_time1;

    hist_trigger_time_diff->Fill(time_diff);

    hist_photons_detected_1->Fill(nPhotonDetected1);
    hist_photons_detected_2->Fill(nPhotonDetected2);

    if (time_diff < 0.75) {

      hist_photons_detected_1_triggered->Fill(nPhotonDetected1);
      hist_photons_detected_2_triggered->Fill(nPhotonDetected2);

    }

  }


  //-------------------------- Darw Histograms --------------------------//

  canvas->SetLogy(true);

  hist_trigger_time_1->SetFillColor(kYellow);
  hist_trigger_time_1->Draw();
  canvas->Print("simu/trigger_time_1.pdf");
  canvas->Clear();

  hist_trigger_time_2->SetFillColor(kYellow);
  hist_trigger_time_2->Draw();
  canvas->Print("simu/trigger_time_2.pdf");
  canvas->Clear();

  hist_trigger_time_diff->SetFillColor(kYellow);
  hist_trigger_time_diff->Draw();
  canvas->Print("simu/trigger_time_diff.pdf");
  canvas->Clear();

  hist_photons_detected_1->SetFillColor(kYellow);
  hist_photons_detected_1->Draw();
  canvas->Print("simu/photons_detected_1.pdf");
  canvas->Clear();

  hist_photons_detected_2->SetFillColor(kYellow);
  hist_photons_detected_2->Draw();
  canvas->Print("simu/photons_detected_2.pdf");
  canvas->Clear();

  hist_photons_detected_1_triggered->SetFillColor(kYellow);
  hist_photons_detected_1_triggered->Draw();
  canvas->Print("simu/photons_detected_1_triggered.pdf");
  canvas->Clear();

  hist_photons_detected_2_triggered->SetFillColor(kYellow);
  hist_photons_detected_2_triggered->Draw();
  canvas->Print("simu/photons_detected_2_triggered.pdf");
  canvas->Clear();

  //---------------------------------------------------------------------//

}
