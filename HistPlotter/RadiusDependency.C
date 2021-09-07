void RadiusDependency () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *root_file = TFile::Open("quartz.root");

  TTree *tree = (TTree *) root_file->Get("T");

  //------------------------ Branches variables ------------------------//

  // Detected Photons Counter
  Int_t nPhotonDetected = -1;
  Int_t nSecPhotonDetected = -1;

  // Positions of Detected Photons
  std::vector<double> *nPhotonDetectedPosition = {};
  std::vector<double> *nPriPhotonDetectedPosition = {};
  std::vector<double> *nSecPhotonDetectedPosition = {};

  // Detected Photons Counter
  tree->SetBranchAddress("nPhotonDetected", &nPhotonDetected);
  tree->SetBranchAddress("nSecPhotonDetected", &nSecPhotonDetected);

  // Positions of Detected Photons
  tree->SetBranchAddress("nPhotonDetectedPosition", &nPhotonDetectedPosition);
  tree->SetBranchAddress("nPriPhotonDetectedPosition", &nPriPhotonDetectedPosition);
  tree->SetBranchAddress("nSecPhotonDetectedPosition", &nSecPhotonDetectedPosition);

  //--------------------------------------------------------------------//

  //---------------------------- Histograms ----------------------------//

  // Detected Photons Counter

  TH1I *hist_total_photon_detected_counter = new TH1I(
    "Total Detected Photons",
    "Total Detected Photons; n Photons; Events",
    100,
    0,
    1000
  );

  TH1I *hist_primary_photon_detected_counter = new TH1I(
    "Primary Detected Photons",
    "Primary Detected Photons; n Photons; Events",
    100,
    0,
    600
  );

  TH1I *hist_secondary_photon_detected_counter = new TH1I(
    "Secondary Detected Photons",
    "Secondary Detected Photons; n Photons; Events",
    120,
    0,
    1200
  );

  TH1I *hist_secondary_photon_detected_counter_tail = new TH1I(
    "Secondary Detected Photons Counter tail",
    "Secondary Photons Detected Counter tail; n Photons; Events",
    100,
    0,
    1000
  );

  // Counter of Positions of Detected Photons

  TH1I *hist_total_photon_detected_position = new TH1I(
    "Positions of Total Detected Photons",
    "Positions of Total Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1I *hist_primary_photon_detected_position = new TH1I(
    "Positions of Primary Detected Photons",
    "Positions of Primary Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1I *hist_secondary_photon_detected_position = new TH1I(
    "Positions of Secondary Detected Photons",
    "Positions of Secondary Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Detected Photons Counter
    hist_total_photon_detected_counter->Fill(nPhotonDetected);
    hist_primary_photon_detected_counter->Fill(
      nPhotonDetected - nSecPhotonDetected
    );
    hist_secondary_photon_detected_counter->Fill(nSecPhotonDetected);

    if (nSecPhotonDetected > 0) {
      hist_secondary_photon_detected_counter_tail->Fill(
        nPhotonDetected
      );
    }

    // Positions of Detected Photons
    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {
      hist_total_photon_detected_position->Fill(
        nPhotonDetectedPosition->at(j)
      );

    }

    for (size_t j = 0; j < nPriPhotonDetectedPosition->size(); j++) {
      hist_primary_photon_detected_position->Fill(
        nPriPhotonDetectedPosition->at(j)
      );
    }

    for (size_t j = 0; j < nSecPhotonDetectedPosition->size(); j++) {
      hist_secondary_photon_detected_position->Fill(
        nSecPhotonDetectedPosition->at(j)
      );
    }

}

//-------------------------- Darw Histograms --------------------------//

// Detected Photons Counter

hist_total_photon_detected_counter->SetFillColor(kYellow);
hist_total_photon_detected_counter->Draw();
canvas->Print("Totals/total_photon_detected_counter.pdf");
canvas->Clear();

hist_primary_photon_detected_counter->SetFillColor(kYellow);
hist_primary_photon_detected_counter->Draw();
canvas->Print("Totals/primary_photon_detected_counter.pdf");
canvas->Clear();

canvas->SetLogy(true);

hist_secondary_photon_detected_counter->SetFillColor(kYellow);
hist_secondary_photon_detected_counter->Draw();
canvas->Print("Totals/secondary_photon_detected_counter.pdf");
canvas->Clear();

canvas->SetLogy(false);

// Positions of Detected Photons

hist_total_photon_detected_position->SetStats(false);
hist_total_photon_detected_position->SetFillColor(kYellow);
hist_total_photon_detected_position->Draw();
canvas->Print("Totals/total_photon__detected_position.pdf");
canvas->Clear();

hist_primary_photon_detected_position->SetStats(false);
hist_primary_photon_detected_position->SetFillColor(kYellow);
hist_primary_photon_detected_position->Draw();
canvas->Print("Totals/primary_photon_detected_position.pdf");
canvas->Clear();

//canvas->SetLogy(true);

hist_secondary_photon_detected_position->SetStats(false);
hist_secondary_photon_detected_position->SetFillColor(kYellow);
hist_secondary_photon_detected_position->Draw();
canvas->Print("Totals/secondary_photon_detected_position.pdf");
canvas->Clear();

//canvas->SetLogy(false);

hist_total_photon_detected_counter->SetFillColorAlpha(kYellow, 1.0);
hist_secondary_photon_detected_counter_tail->SetFillColorAlpha(kRed, 0.5);
hist_total_photon_detected_counter->Draw();
hist_secondary_photon_detected_counter_tail->Draw("SAME");
canvas->Print("Totals/total_photons_detected_counter_tail.pdf");
canvas->Clear();

}
