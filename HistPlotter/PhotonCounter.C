void PhotonCounter() {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );


  TFile *plume_file = TFile::Open("conf_1_e-_1GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_e-_5GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_e-_10GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_e-_15GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_e-_20GeV.root");
  //
  // TFile *plume_file = TFile::Open("conf_1_p_1GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_p_5GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_p_10GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_p_15GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_p_20GeV.root");
  //
  // TFile *plume_file = TFile::Open("conf_1_pi+_1GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_pi+_5GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_pi+_10GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_pi+_15GeV.root");
  // TFile *plume_file = TFile::Open("conf_1_pi+_20GeV.root");


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

  // Photons Inside and Outside
  // Int_t nPhotonInside = -1;
  // Int_t nPhotonOutside = -1;

  // Photon Counter
  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nSecondaryPhotCreated", &nSecondaryPhotCreated);

  // Reflections
  tree->SetBranchAddress("nPhotReflection", &nPhotReflection);

  // Detected Photons
  tree->SetBranchAddress("nPhotonDetected", &nPhotonDetected);
  tree->SetBranchAddress("nSecPhotonDetected", &nSecPhotonDetected);

  // Photons Inside and Outside
  // tree->SetBranchAddress("nPhotonInside", &nPhotonInside);
  // tree->SetBranchAddress("nPhotonOutside", &nPhotonOutside);

  // Photon Counter

  TH1I *hist_primary_photon_counter = new TH1I(
    "Primary Created Photons",
    "Primary Created Photons; Number of Photons; Number of Events",
    180,
    400,
    1200
  );

  TH1I *hist_photon_counter_totals = new TH1I(
    "Total Created Photons",
    "Total Created Photons; Number of Photons; Number of Events",
    100,
    400,
    2000
  );

  TH1I *hist_secondary_photon_counter = new TH1I(
    "Secondary Created Photons",
    "Secondary Created Photons; Number of Photons; Number of Events",
    140,
    0,
    4000
  );

  TH1I *hist_secondary_photon_counter_tail = new TH1I(
    "Total Created Photons Tail",
    "Total Created Photons Tail; Number of Photons; Number of Events",
    100,
    400,
    2000
  );

  // Reflections

  TH1I *hist_photon_reflection = new TH1I(
    "Reflected Photons",
    "Reflected Photons; Number of Photons; Number of Events",
    100,
    0,
    5000
  );

  // Detected Photons

  TH1I *hist_primary_detected_photons = new TH1I(
    "Primary Detected Photons",
    "Primary Detected Photons; Number of Photons; Number of Events",
    100,
    100,
    600
  );

  TH1I *hist_secondary_detected_photons = new TH1I(
    "Secondary Detected Photons",
    "Secondary Detected Photons; Number of Photons; Number of Events",
    100,
    0,
    4000
  );

  TH1I *hist_total_detected_photons = new TH1I(
    "Total Detected Photons",
    "Total Detected Photons; Number of Photons; Number of Events",
    100,
    100,
    1700
  );

  TH1I *hist_total_detected_photons_tail = new TH1I(
    "Total Detected Photons Tail",
    "Total Detected Photons Tail; Number of Photons; Number of Events",
    100,
    100,
    1700
  );

  // TH1I *hist_inside_photons = new TH1I(
  //   "Inside Photons",
  //   "Inside Photons; Number of Photons; Number of Events",
  //   100,
  //   0,
  //   3000
  // );
  //
  // TH1I *hist_outside_photons = new TH1I(
  //   "Outside Photons",
  //   "Outside Photons; Number of Photons; Number of Events",
  //   100,
  //   0,
  //   3000
  // );

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

    // hist_inside_photons->Fill(nPhotonInside);
    // hist_outside_photons->Fill(nPhotonOutside);

  }

  //>>>>>>>>>>>>>>>>> Set Canvas

  // Photon Counter
  canvas->SetLogy(true);

  hist_primary_photon_counter->SetFillColor(kYellow);
  hist_primary_photon_counter->SetMaximum(8000);
  hist_primary_photon_counter->SetMinimum(1e-1);
  hist_primary_photon_counter->Draw();
  canvas->Print("Configuration_1/Electron/1_GeV/PrimaryCreatedPhotons.pdf");
  canvas->Clear();

  hist_secondary_photon_counter->SetFillColor(kYellow);
  hist_secondary_photon_counter->SetMaximum(2e5);
  hist_secondary_photon_counter->SetMinimum(1e-1);
  hist_secondary_photon_counter->Draw();
  canvas->Print("Configuration_1/Electron/1_GeV/SecondaryCreatedPhotons.pdf");
  canvas->Clear();

  //hist_primary_photon_counter->SetFillColorAlpha(kYellow, 1.0);
  hist_photon_counter_totals->SetFillColorAlpha(kYellow, 1.0);
  hist_secondary_photon_counter_tail->SetFillColorAlpha(kRed, 0.5);
  //hist_primary_photon_counter->Draw();
  hist_photon_counter_totals->SetMaximum(2e5);
  hist_photon_counter_totals->SetMinimum(1e-1);
  hist_photon_counter_totals->Draw();
  hist_secondary_photon_counter_tail->Draw("SAME");
  canvas->Print("Configuration_1/Electron/1_GeV/TotalCreatedPhotons.pdf");
  canvas->Clear();

  // Detected Photons

  hist_primary_detected_photons->SetFillColor(kYellow);
  hist_primary_detected_photons->SetMaximum(2e5);
  hist_primary_detected_photons->SetMinimum(1e-1);
  hist_primary_detected_photons->Draw();
  canvas->Print("Configuration_1/Electron/1_GeV/PrimaryDetectedPhotons.pdf");
  canvas->Clear();

  hist_secondary_detected_photons->SetFillColor(kYellow);
  hist_secondary_detected_photons->SetMaximum(2e5);
  hist_secondary_detected_photons->SetMinimum(1e-1);
  hist_secondary_detected_photons->Draw();
  canvas->Print("Configuration_1/Electron/1_GeV/SecondaryDetectedPhotons.pdf");
  canvas->Clear();

  //hist_primary_photon_counter->SetFillColorAlpha(kYellow, 1.0);
  hist_total_detected_photons->SetFillColorAlpha(kYellow, 1.0);
  hist_total_detected_photons_tail->SetFillColorAlpha(kRed, 0.5);
  //hist_primary_photon_counter->Draw();
  hist_total_detected_photons->SetMaximum(2e5);
  hist_total_detected_photons->SetMinimum(1e-1);
  hist_total_detected_photons->Draw();
  hist_total_detected_photons_tail->Draw("SAME");
  canvas->Print("Configuration_1/Electron/1_GeV/TotalDetectedPhotons.pdf");
  canvas->Clear();


  // Reflections
  hist_photon_reflection->SetFillColor(kYellow);
  hist_photon_reflection->Draw();
  canvas->Print("Configuration_1/Electron/1_GeV/ReflectedPhotons.pdf");
  canvas->Clear();

  // hist_inside_photons->SetFillColor(kYellow);
  // hist_inside_photons->Draw();
  // canvas->Print("Configuration_1/Electron/1_GeV/InsidePhotons.pdf");
  // canvas->Clear();
  //
  // hist_outside_photons->SetFillColor(kYellow);
  // hist_outside_photons->Draw();
  // canvas->Print("Configuration_1/Electron/1_GeV/OutsidePhotons.pdf");
  // canvas->Clear();

}
