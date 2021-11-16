
void AngleAnalysis () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *root_files = TFile::Open("random_angle_shield.root");

  TTree *tree = (TTree *) root_files->Get("T");

  //------------------------ Branches variables ------------------------//

  // Hit Angle
  double hitAngle = 0.0;
  // Zones
  Int_t Zone = -1;

  // Counter of Photons in Zone Detector
  Int_t nPhotonZone0 = -1;
  Int_t nPhotonZone1 = -1;
  Int_t nPhotonZone2 = -1;
  Int_t nPhotonZone3 = -1;
  Int_t nPhotonZone4 = -1;

  // Detected Photons Counter
  Int_t nPhotonDetected = -1;
  Int_t nSecPhotonDetected = -1;

  // Positions of Detected Photons
  std::vector<double> *nPhotonDetectedPosition = {};
  std::vector<double> *nPriPhotonDetectedPosition = {};
  std::vector<double> *nSecPhotonDetectedPosition = {};

  // Positions of Primary Electron
  Double_t nPostPVxPosition = -1.0;
  Double_t nPostPVyPosition = -1.0;

  // Hit Angle
  tree->SetBranchAddress("hitAngle", &hitAngle);

  // Zones
  tree->SetBranchAddress("Zone", &Zone);

  // Counter of Photons in Zone Detector
  tree->SetBranchAddress("nPhotonZone0", &nPhotonZone0);
  tree->SetBranchAddress("nPhotonZone1", &nPhotonZone1);
  tree->SetBranchAddress("nPhotonZone2", &nPhotonZone2);
  tree->SetBranchAddress("nPhotonZone3", &nPhotonZone3);
  tree->SetBranchAddress("nPhotonZone4", &nPhotonZone4);

  // Detected Photons Counter
  tree->SetBranchAddress("nPhotonDetected", &nPhotonDetected);
  tree->SetBranchAddress("nSecPhotonDetected", &nSecPhotonDetected);

  // Positions of Detected Photons
  tree->SetBranchAddress("nPhotonDetectedPosition", &nPhotonDetectedPosition);
  tree->SetBranchAddress("nPriPhotonDetectedPosition", &nPriPhotonDetectedPosition);
  tree->SetBranchAddress("nSecPhotonDetectedPosition", &nSecPhotonDetectedPosition);

  // Positions of Primary Electron
  tree->SetBranchAddress("nPostPVxPosition", &nPostPVxPosition);
  tree->SetBranchAddress("nPostPVyPosition", &nPostPVyPosition);

  //--------------------------------------------------------------------//

  //---------------------------- Histograms ----------------------------//

  // Hit Angle

  TH1I *hist_hit_angle = new TH1I(
    "Hit Angle",
    "Hit Angle; Angle [°]; Number of Events",
    100,
    0,
    65
  );

  // Detected Photons Counter

  TH1I *hist_total_photon_detected_counter = new TH1I(
    "Total Detected Photons",
    "Total Detected Photons; Number of Photons; Number of Events",
    100,
    0,
    1000
  );

  TH1I *hist_primary_photon_detected_counter = new TH1I(
    "Primary Detected Photons",
    "Primary Detected Photons; Number of Photons; Number of Events",
    100,
    0,
    800
  );

  TH1I *hist_secondary_photon_detected_counter = new TH1I(
    "Secondary Detected Photons",
    "Secondary Detected Photons; Number of Photons; Number of Events",
    100,
    0,
    1200
  );

  // Counter of Positions of Detected Photons

  TH1F *hist_total_photon_detected_position = new TH1F(
    "Positions of Total Detected Photons",
    "Positions of Total Detected Photons; Radius [mm]; Number of Events",
    100,
    0,
    5
  );

  TH1F *hist_primary_photon_detected_position = new TH1F(
    "Positions of Primary Detected Photons",
    "Positions of Primary Detected Photons; Radius [mm]; Number of Events",
    100,
    0,
    5
  );

  TH1F *hist_secondary_photon_detected_position = new TH1F(
    "Positions of Secondary Detected Photons",
    "Positions of Secondary Detected Photons; Radius [mm]; Number of Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_normalized = new TH1F(
    "Positions of Total Detected Photons Normalized",
    "Positions of Total Detected Photons Normalized; Radius [mm]; Number of Events",
    100,
    0,
    5
  );

  // Position of Detected Photons Normalized by Radius
  TH1F *hist_total_photon_detected_position_radius = new TH1F(
    "Positions of Total Detected Photons Test Normalized",
    "Positions of Total Detected Photons Test; Radius [mm]; Number of Events",
    50,
    0,
    5
  );

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int k = 0; k < nentries; k++) {
    nbytes = tree->GetEntry(k);

    // Fill histograms.

    // Hit Angle
    hist_hit_angle->Fill(hitAngle / M_PI * 180);

    // Detected Photons Counter
    hist_total_photon_detected_counter->Fill(nPhotonDetected);

    hist_primary_photon_detected_counter->Fill(
      nPhotonDetected - nSecPhotonDetected
    );

    hist_secondary_photon_detected_counter->Fill(nSecPhotonDetected);

    // Positions of Detected Photons (Primary and secondary)

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

    std::map<Int_t, Int_t> zones_counter;

    zones_counter[0] = nPhotonZone0;
    zones_counter[1] = nPhotonZone1;
    zones_counter[2] = nPhotonZone2;
    zones_counter[3] = nPhotonZone3;
    zones_counter[4] = nPhotonZone4;

    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {
      Int_t phtoton_zone = 0;

      if (nPhotonDetectedPosition->at(j) < std::sqrt(5.0)) {
        phtoton_zone = 0;
      } else if (nPhotonDetectedPosition->at(j)< std::sqrt(10.0)) {
        phtoton_zone = 1;
      } else if (nPhotonDetectedPosition->at(j)< std::sqrt(15.0)) {
        phtoton_zone = 2;
      } else if (nPhotonDetectedPosition->at(j)< std::sqrt(20.0)) {
        phtoton_zone = 3;
      } else {
        phtoton_zone = 4;
      }

      hist_total_photon_detected_position_normalized->Fill(
        nPhotonDetectedPosition->at(j), 1.0/(zones_counter[phtoton_zone]*1.0)
      );

    }

    ////////////// ------ TEST ------ //////////////
    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {

      // Positions of Detected Photons

      hist_total_photon_detected_position->Fill(
        nPhotonDetectedPosition->at(j)
      );

      // Position of Detected Photons Normalized by Radius

      Int_t bin = hist_total_photon_detected_position_radius->FindBin(
        nPhotonDetectedPosition->at(j)
      );

      float inv_weight = hist_total_photon_detected_position_radius->GetBinCenter(
        bin
      );

      hist_total_photon_detected_position_radius->Fill(
        nPhotonDetectedPosition->at(j), 1.0 / inv_weight
      );

    }

  }

  //-------------------------- Draw Histograms --------------------------//

  // Hit Angle

  hist_hit_angle->SetFillColor(kYellow);
  hist_hit_angle->Draw();
  canvas->Print("Angles_Coating/hit_angle.pdf");
  canvas->Clear();

  // Detected Photons Counter

  hist_total_photon_detected_counter->SetFillColor(kYellow);
  hist_total_photon_detected_counter->Draw();
  canvas->Print("Angles_Coating/total_photon_detected_counter.pdf");
  canvas->Clear();

  hist_primary_photon_detected_counter->SetFillColor(kYellow);
  hist_primary_photon_detected_counter->Draw();
  canvas->Print("Angles_Coating/primary_photon_detected_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_photon_detected_counter->SetFillColor(kYellow);
  hist_secondary_photon_detected_counter->Draw();
  canvas->Print("Angles_Coating/secondary_photon_detected_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  // Positions of Detected Photons

  hist_total_photon_detected_position->SetFillColor(kYellow);
  hist_total_photon_detected_position->Draw();
  canvas->Print("Angles_Coating/total_photon_detected_position.pdf");
  canvas->Clear();

  hist_primary_photon_detected_position->SetFillColor(kYellow);
  hist_primary_photon_detected_position->Draw();
  canvas->Print("Angles_Coating/primary_photon_detected_position.pdf");
  canvas->Clear();

  hist_secondary_photon_detected_position->SetFillColor(kYellow);
  hist_secondary_photon_detected_position->Draw();
  canvas->Print("Angles_Coating/secondary_photon_detected_position.pdf");
  canvas->Clear();

  // -------------------------------------------------------------- //

  // Test

  hist_total_photon_detected_position_normalized->SetFillColor(kYellow);
  hist_total_photon_detected_position_normalized->Draw("HIST");
  canvas->Print("Angles_Coating/total_photon_detected_position_normalized.pdf");
  canvas->Clear();

  //// Test 3 ////

  canvas->SetLogy(true);

  // Position of Detected Photons Normalized by Radius
  hist_total_photon_detected_position_radius->GetYaxis()->SetRangeUser(1, 4e6);
  hist_total_photon_detected_position_radius->SetFillColor(kYellow);
  hist_total_photon_detected_position_radius->Draw("HIST");
  canvas->Print("Angles_Coating/total_photon_detected_position_radius_norm_TEST.pdf");
  canvas->Clear();

  //---------------------------------------------------------------------//

}
