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

  // Hit Angle
  double hitAngle = 0.0;

  // Detected Photons Counter
  Int_t nPhotonDetected = -1;
  Int_t nSecPhotonDetected = -1;

  // Positions of Detected Photons
  std::vector<double> *nPhotonDetectedPosition = {};
  std::vector<double> *nPriPhotonDetectedPosition = {};
  std::vector<double> *nSecPhotonDetectedPosition = {};

  // Hit Angle
  tree->SetBranchAddress("hitAngle", &hitAngle);

  // Detected Photons Counter
  tree->SetBranchAddress("nPhotonDetected", &nPhotonDetected);
  tree->SetBranchAddress("nSecPhotonDetected", &nSecPhotonDetected);

  // Positions of Detected Photons
  tree->SetBranchAddress("nPhotonDetectedPosition", &nPhotonDetectedPosition);
  tree->SetBranchAddress("nPriPhotonDetectedPosition", &nPriPhotonDetectedPosition);
  tree->SetBranchAddress("nSecPhotonDetectedPosition", &nSecPhotonDetectedPosition);

  //--------------------------------------------------------------------//

  //---------------------------- Histograms ----------------------------//

  // Hit Angle

  TH1I *hist_hit_angle = new TH1I(
    "Hit Angle",
    "Hit Angle; Angle [°]; Events",
    100,
    0,
    65
  );

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
    100,
    0,
    1200
  );

  TH2F *hist_total_photon_detected_angle_counter = new TH2F(
    "Total Detected Photons and Hit Angle",
    "Total Detected Photons and  Hit Angle; n Photons; Angle [°]; Events",
    100,
    0,
    1000,
    100,
    0,
    65
  );

  TH2F *hist_primary_photon_detected_angle_counter = new TH2F(
    "Primary Detected Photons and Hit Angle",
    "Primary Detected Photons and  Hit Angle; n Photons; Angle [°]; Events",
    100,
    0,
    600,
    100,
    0,
    65
  );

  TH2F *hist_secondary_photon_detected_angle_counter = new TH2F(
    "Secondary Detected Photons and Hit Angle",
    "Secondary Detected Photons and  Hit Angle; n Photons; Angle [°]; Events",
    100,
    0,
    1200,
    100,
    0,
    65
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
    "Positions of Total Photons; radius; Events",
    100,
    0,
    5
  );

  TH1I *hist_primary_photon_detected_position = new TH1I(
    "Positions of Primary Detected Photons",
    "Positions of Primary Photons; radius; Events",
    100,
    0,
    5
  );

  TH1I *hist_secondary_photon_detected_position = new TH1I(
    "Positions of Secondary Detected Photons",
    "Positions of Secondary Photons; radius; Events",
    100,
    0,
    5
  );

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Hit Angle
    hist_hit_angle->Fill(hitAngle / M_PI * 180);

    // Detected Photons Counter
    hist_total_photon_detected_counter->Fill(nPhotonDetected);
    hist_primary_photon_detected_counter->Fill(
      nPhotonDetected - nSecPhotonDetected
    );
    hist_secondary_photon_detected_counter->Fill(nSecPhotonDetected);

    hist_total_photon_detected_angle_counter->Fill(
        nPhotonDetected, hitAngle / M_PI * 180
    );
    hist_primary_photon_detected_angle_counter->Fill(
        nPhotonDetected - nSecPhotonDetected, hitAngle / M_PI * 180
    );
    hist_secondary_photon_detected_angle_counter->Fill(
        nSecPhotonDetected, hitAngle / M_PI * 180
    );

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

// Hit Angle

hist_hit_angle->SetFillColor(kYellow);
hist_hit_angle->Draw();
canvas->Print("Totals/hit_angle.pdf");
canvas->Clear();

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

hist_total_photon_detected_angle_counter->Draw("COLZ");
hist_total_photon_detected_angle_counter->SetStats(kFALSE);
canvas->Print("total_photon_detected_angle_counter.pdf");
canvas->Clear();

hist_primary_photon_detected_angle_counter->Draw("COLZ");
hist_primary_photon_detected_angle_counter->SetStats(kFALSE);
canvas->Print("primary_photon_detected_angle_counter.pdf");
canvas->Clear();

hist_secondary_photon_detected_angle_counter->Draw("COLZ");
hist_secondary_photon_detected_angle_counter->SetStats(kFALSE);
canvas->Print("secondary_photon_detected_angle_counter.pdf");
canvas->Clear();

// Positions of Detected Photons

hist_total_photon_detected_position->SetStats(false);
hist_total_photon_detected_position->SetFillColor(kYellow);
hist_total_photon_detected_position->Draw();
canvas->Print("Totals/total_photon_detected_position.pdf");
canvas->Clear();

hist_primary_photon_detected_position->SetStats(false);
hist_primary_photon_detected_position->SetFillColor(kYellow);
hist_primary_photon_detected_position->Draw();
canvas->Print("Totals/primary_photon_detected_position.pdf");
canvas->Clear();

hist_secondary_photon_detected_position->SetStats(false);
hist_secondary_photon_detected_position->SetFillColor(kYellow);
hist_secondary_photon_detected_position->Draw();
canvas->Print("Totals/secondary_photon_detected_position.pdf");
canvas->Clear();

hist_total_photon_detected_counter->SetFillColorAlpha(kYellow, 1.0);
hist_secondary_photon_detected_counter_tail->SetFillColorAlpha(kRed, 0.5);
hist_total_photon_detected_counter->Draw();
hist_secondary_photon_detected_counter_tail->Draw("SAME");
canvas->Print("Totals/total_photons_detected_counter_tail.pdf");
canvas->Clear();

hist_primary_photon_detected_angle_counter->Draw("COLZ");
hist_primary_photon_detected_angle_counter->SetStats(kFALSE);

}
