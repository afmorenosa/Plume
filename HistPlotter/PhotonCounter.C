void PhotonCounter() {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *plume_file = TFile::Open("con_coating.root");

  TTree *tree = (TTree *) plume_file->Get("T");

  // Zones
  Int_t Zones = -1;

  // Photon Counter
  Int_t nPhotCreated = -1;
  Int_t nSecondaryPhotCreated = -1;

  // Reflections
  Int_t nPhotReflection = -1;

  // Detected Photons
  Int_t nPhotonDetected = -1;
  Int_t nSecPhotonDetected = -1;

  // Photon Counter
  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nSecondaryPhotCreated", &nSecondaryPhotCreated);

  // Reflections
  tree->SetBranchAddress("nPhotReflection", &nPhotReflection);

  // Detected Photons
  tree->SetBranchAddress("nPhotonDetected", &nPhotonDetected);
  tree->SetBranchAddress("nSecPhotonDetected", &nSecPhotonDetected);

  // Photon Counter

  TH1I *hist_primary_photon_counter = new TH1I(
    "Primary Created Photons",
    "Primary Created Photons; Number of Photon; Number of Events",
    180,
    0,
    2000
  );

  TH1I *hist_photon_counter_totals = new TH1I(
    "Total Created Photons",
    "Total Created Photons; Number of Photon; Number of Events",
    100,
    0,
    2000
  );

  TH1I *hist_secondary_photon_counter = new TH1I(
        "Secondary Created Photons",
    "Secondary Created Photons; Number of Photon; Number of Events",
    140,
    0,
    1400
  );

  TH1I *hist_secondary_photon_counter_tail = new TH1I(
        "Total Created Photons",
    "Total Created Photons; Number of Photon; Number of Events",
    100,
    0,
    2000
  );

  // Reflections

  TH1I *hist_photon_reflection = new TH1I(
    "Reflected Photons",
    "Reflected Photons; Number of Photon; Number of Events",
    100,
    0,
    5000
  );

  // Detected Photons

  TH1I *hist_primary_detected_photons = new TH1I(
    "Primary Detected Photons",
    "Primary Detected Photons; Number of Photon; Number of Events",
    100,
    0,
    1000
  );

  TH1I *hist_secondary_detected_photons = new TH1I(
    "Secondary Detected Photons",
    "Secondary Detected Photons; Number of Photon; Number of Events",
    100,
    0,
    1000
  );

  TH1I *hist_total_detected_photons = new TH1I(
    "Total Detected Photons",
    "Total Detected Photons; Number of Photon; Number of Events",
    100,
    0,
    1000
  );

  TH1I *hist_total_detected_photons_tail = new TH1I(
    "Total Detected Photons",
    "Total Detected Photons; Number of Photon; Number of Events",
    100,
    0,
    1000
  );

  //>>>>>>>>>>>>>> Fill Histograms

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Photon Counter
    hist_photon_counter_totals->Fill(nSecondaryPhotCreated + nPhotCreated);
    hist_primary_photon_counter->Fill(nPhotCreated);
    hist_secondary_photon_counter->Fill(nSecondaryPhotCreated);

    if (nSecondaryPhotCreated > 0) {
      hist_secondary_photon_counter_tail->Fill(
        nSecondaryPhotCreated + nPhotCreated
      );
    }

    // Reflections
    hist_photon_reflection->Fill(nPhotReflection);

    // Detected Photons
    hist_primary_detected_photons->Fill(nPhotonDetected - nSecPhotonDetected);
    hist_secondary_detected_photons->Fill(nSecPhotonDetected);
    hist_total_detected_photons->Fill(nPhotonDetected);

    if (nSecPhotonDetected > 0) {
      hist_total_detected_photons_tail->Fill(
        nPhotonDetected
      );
    }

  }

  //>>>>>>>>>>>>>>>>> Set Canvas

  // Photon Counter

  hist_primary_photon_counter->SetFillColor(kYellow);
  hist_primary_photon_counter->Draw();
  canvas->Print("PrimaryCreatedPhotons_CON.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_photon_counter->SetFillColor(kYellow);
  hist_secondary_photon_counter->Draw();
  canvas->Print("SecondaryCreatedPhotons_CON.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  //hist_primary_photon_counter->SetFillColorAlpha(kYellow, 1.0);
  hist_photon_counter_totals->SetFillColorAlpha(kYellow, 1.0);
  hist_secondary_photon_counter_tail->SetFillColorAlpha(kRed, 0.5);
  //hist_primary_photon_counter->Draw();
  hist_photon_counter_totals->Draw();
  hist_secondary_photon_counter_tail->Draw("SAME");
  canvas->Print("TotalCreatedPhotons_CON.pdf");
  canvas->Clear();

  // Detected Photons

  hist_primary_detected_photons->SetFillColor(kYellow);
  hist_primary_detected_photons->Draw();
  canvas->Print("PrimaryDetectedPhotons_CON.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_detected_photons->SetFillColor(kYellow);
  hist_secondary_detected_photons->Draw();
  canvas->Print("SecondaryDetectedPhotons_CON.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  //hist_primary_photon_counter->SetFillColorAlpha(kYellow, 1.0);
  hist_total_detected_photons->SetFillColorAlpha(kYellow, 1.0);
  hist_total_detected_photons_tail->SetFillColorAlpha(kRed, 0.5);
  //hist_primary_photon_counter->Draw();
  hist_total_detected_photons->Draw();
  hist_total_detected_photons_tail->Draw("SAME");
  canvas->Print("TotalDetectedPhotons_CON.pdf");
  canvas->Clear();


  // Reflections
  canvas->SetLogy(true);

  hist_photon_reflection->SetFillColor(kYellow);
  hist_photon_reflection->Draw();
  canvas->Print("ReflectedPhotons_CON.pdf");
  canvas->Clear();

}
