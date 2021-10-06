
void AngleAnalysis () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  std::vector<TFile *> root_files;
  root_files.push_back(TFile::Open("angle0.root"));
  root_files.push_back(TFile::Open("angleA.root"));
  root_files.push_back(TFile::Open("angleB.root"));
  root_files.push_back(TFile::Open("angleC.root"));
  root_files.push_back(TFile::Open("angleD.root"));
  root_files.push_back(TFile::Open("angleE.root"));

  std::vector<TTree *> trees;
  for (size_t i = 0; i < root_files.size(); i++) {
    trees.push_back((TTree *) root_files[i]->Get("T"));
  }

  //------------------------ Branches variables ------------------------//

  // Hit Angle
  std::vector<double> hitAngle(trees.size(), 0.0);
  // Zones
  std::vector<Int_t> Zone(trees.size(), -1);

  // Counter of Photons in Zone Detector
  std::vector<Int_t> nPhotonZone0(trees.size(), -1);
  std::vector<Int_t> nPhotonZone1(trees.size(), -1);
  std::vector<Int_t> nPhotonZone2(trees.size(), -1);
  std::vector<Int_t> nPhotonZone3(trees.size(), -1);
  std::vector<Int_t> nPhotonZone4(trees.size(), -1);

  // Detected Photons Counter
  std::vector<Int_t> nPhotonDetected(trees.size(), -1);
  std::vector<Int_t> nSecPhotonDetected(trees.size(), -1);

  // Positions of Detected Photons
  std::vector<std::vector<double> *> nPhotonDetectedPosition(trees.size(), {});
  std::vector<std::vector<double> *> nPriPhotonDetectedPosition(trees.size(), {});
  std::vector<std::vector<double> *> nSecPhotonDetectedPosition(trees.size(), {});

  // Positions of Primary Electron
  std::vector<Double_t> nPostPVxPosition(trees.size(), -1.0);
  std::vector<Double_t> nPostPVyPosition(trees.size(), -1.0);

  for (size_t i = 0; i < trees.size(); i++) {

    // Hit Angle
    trees[i]->SetBranchAddress("hitAngle", &hitAngle[i]);

    // Zones
    trees[i]->SetBranchAddress("Zone", &Zone[i]);

    // Counter of Photons in Zone Detector
    trees[i]->SetBranchAddress("nPhotonZone0", &nPhotonZone0[i]);
    trees[i]->SetBranchAddress("nPhotonZone1", &nPhotonZone1[i]);
    trees[i]->SetBranchAddress("nPhotonZone2", &nPhotonZone2[i]);
    trees[i]->SetBranchAddress("nPhotonZone3", &nPhotonZone3[i]);
    trees[i]->SetBranchAddress("nPhotonZone4", &nPhotonZone4[i]);

    // Detected Photons Counter
    trees[i]->SetBranchAddress("nPhotonDetected", &nPhotonDetected[i]);
    trees[i]->SetBranchAddress("nSecPhotonDetected", &nSecPhotonDetected[i]);

    // Positions of Detected Photons
    trees[i]->SetBranchAddress("nPhotonDetectedPosition", &nPhotonDetectedPosition[i]);
    trees[i]->SetBranchAddress("nPriPhotonDetectedPosition", &nPriPhotonDetectedPosition[i]);
    trees[i]->SetBranchAddress("nSecPhotonDetectedPosition", &nSecPhotonDetectedPosition[i]);

    // Positions of Primary Electron
    trees[i]->SetBranchAddress("nPostPVxPosition", &nPostPVxPosition[i]);
    trees[i]->SetBranchAddress("nPostPVyPosition", &nPostPVyPosition[i]);

  }

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
    800
  );

  TH1I *hist_secondary_photon_detected_counter = new TH1I(
    "Secondary Detected Photons",
    "Secondary Detected Photons; n Photons; Events",
    100,
    0,
    1200
  );

  // Counter of Positions of Detected Photons

  TH1F *hist_total_photon_detected_position = new TH1F(
    "Positions of Total Detected Photons",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_primary_photon_detected_position = new TH1F(
    "Positions of Primary Detected Photons",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_secondary_photon_detected_position = new TH1F(
    "Positions of Secondary Detected Photons",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_normalized = new TH1F(
    "Positions of Total Detected Photons Normalized",
    "Positions of Total Detected Photons Normalized; Radius [mm]; Events",
    100,
    0,
    5
  );

  // Position of Detected Photons Normalized by Radius
  TH1F *hist_total_photon_detected_position_radius = new TH1F(
    "Positions of Total Detected Photons Test Normalized",
    "Positions of Total Detected Photons Test; Radius [mm]; Events",
    50,
    0,
    5
  );

  //--------------------------------------------------------------------//

  std::map<int, TH1I *> hist_hit_angle_angle;
  std::map<int, TH1I *> hist_total_photon_detected_counter_angle;
  std::map<int, TH1I *> hist_primary_photon_detected_counter_angle;
  std::map<int, TH1I *> hist_secondary_photon_detected_counter_angle;
  std::map<int, TH1F *> hist_total_photon_detected_position_angle;
  std::map<int, TH1F *> hist_primary_photon_detected_position_angle;
  std::map<int, TH1F *> hist_secondary_photon_detected_position_angle;
  std::map<int, TH1F *> hist_total_photon_detected_position_normalized_angle;
  std::map<int, TH1F *> hist_total_photon_detected_position_radius_angle;

  for (size_t i = 0; i < trees.size(); i++) {

    hist_hit_angle_angle[i] = new TH1I(
      "Hit Angle, Index: I" +
      TString(std::to_string(i).c_str()),
      "Hit Angle; Angle [°]; Events",
      100,
      0,
      65
    );

    hist_total_photon_detected_counter_angle[i] = new TH1I(
      "Total Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Total Detected Photons; n Photons; Events",
      100,
      0,
      1000
    );

    hist_primary_photon_detected_counter_angle[i] = new TH1I(
      "Primary Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Primary Detected Photons; n Photons; Events",
      100,
      0,
      800
    );

    hist_secondary_photon_detected_counter_angle[i] = new TH1I(
      "Secondary Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Secondary Detected Photons; n Photons; Events",
      100,
      0,
      1200
    );

    hist_total_photon_detected_position_angle[i] = new TH1F(
      "Positions of Total Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Positions of Total Detected Photons; Radius [mm]; Events",
      100,
      0,
      5
    );

    hist_primary_photon_detected_position_angle[i] = new TH1F(
      "Positions of Primary Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Positions of Primary Detected Photons; Radius [mm]; Events",
      100,
      0,
      5
    );

    hist_secondary_photon_detected_position_angle[i] = new TH1F(
      "Positions of Secondary Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Positions of Secondary Detected Photons; Radius [mm]; Events",
      100,
      0,
      5
    );

    hist_total_photon_detected_position_normalized_angle[i] = new TH1F(
      "Positions of Total Detected Photons Normalized, Index: " +
      TString(std::to_string(i).c_str()),
      "Positions of Total Detected Photons Normalized; Radius [mm]; Events",
      100,
      0,
      5
    );

    hist_total_photon_detected_position_radius_angle[i] = new TH1F(
      "Positions of Total Detected Photons Test Normalized, Index: " +
      TString(std::to_string(i).c_str()),
      "Positions of Total Detected Photons Test; Radius [mm]; Events",
      50,
      0,
      5
    );

  }

  //--------------------------------------------------------------------//

  for (size_t i = 0; i < trees.size(); i++) {

    int nentries, nbytes;
    nentries = (Int_t)trees[i]->GetEntries();

    for (int k = 0; k < nentries; k++) {
      nbytes = trees[i]->GetEntry(k);

      // Fill histograms.

      // Hit Angle
      hist_hit_angle->Fill(hitAngle[i] / M_PI * 180);
      hist_hit_angle_angle[i]->Fill(hitAngle[i] / M_PI * 180);

      // Detected Photons Counter
      hist_total_photon_detected_counter->Fill(nPhotonDetected[i]);
      hist_total_photon_detected_counter_angle[i]->Fill(nPhotonDetected[i]);

      hist_primary_photon_detected_counter->Fill(
        nPhotonDetected[i] - nSecPhotonDetected[i]
      );
      hist_primary_photon_detected_counter_angle[i]->Fill(
        nPhotonDetected[i] - nSecPhotonDetected[i]
      );

      hist_secondary_photon_detected_counter->Fill(nSecPhotonDetected[i]);
      hist_secondary_photon_detected_counter_angle[i]->Fill(nSecPhotonDetected[i]);

      // Positions of Detected Photons (Primary and secondary)

      for (size_t j = 0; j < nPriPhotonDetectedPosition[i]->size(); j++) {
        hist_primary_photon_detected_position->Fill(
          nPriPhotonDetectedPosition[i]->at(j)
        );
        hist_primary_photon_detected_position_angle[i]->Fill(
          nPriPhotonDetectedPosition[i]->at(j)
        );
      }

      for (size_t j = 0; j < nSecPhotonDetectedPosition[i]->size(); j++) {
        hist_secondary_photon_detected_position->Fill(
          nSecPhotonDetectedPosition[i]->at(j)
        );
        hist_secondary_photon_detected_position_angle[i]->Fill(
          nSecPhotonDetectedPosition[i]->at(j)
        );
      }

      std::map<Int_t, Int_t> zones_counter;

      zones_counter[0] = nPhotonZone0[i];
      zones_counter[1] = nPhotonZone1[i];
      zones_counter[2] = nPhotonZone2[i];
      zones_counter[3] = nPhotonZone3[i];
      zones_counter[4] = nPhotonZone4[i];

      for (size_t j = 0; j < nPhotonDetectedPosition[i]->size(); j++) {
        Int_t phtoton_zone = 0;

        if (nPhotonDetectedPosition[i]->at(j) < std::sqrt(5.0)) {
          phtoton_zone = 0;
        } else if (nPhotonDetectedPosition[i]->at(j)< std::sqrt(10.0)) {
          phtoton_zone = 1;
        } else if (nPhotonDetectedPosition[i]->at(j)< std::sqrt(15.0)) {
          phtoton_zone = 2;
        } else if (nPhotonDetectedPosition[i]->at(j)< std::sqrt(20.0)) {
          phtoton_zone = 3;
        } else {
          phtoton_zone = 4;
        }

        hist_total_photon_detected_position_normalized->Fill(
          nPhotonDetectedPosition[i]->at(j), 1.0/(zones_counter[phtoton_zone]*1.0)
        );

        hist_total_photon_detected_position_normalized_angle[i]->Fill(
          nPhotonDetectedPosition[i]->at(j), 1.0/(zones_counter[phtoton_zone]*1.0)
        );
      }

      // //////////// ------ TEST ------
      for (size_t j = 0; j < nPhotonDetectedPosition[i]->size(); j++) {

        // Positions of Detected Photons

        hist_total_photon_detected_position->Fill(
          nPhotonDetectedPosition[i]->at(j)
        );
        hist_total_photon_detected_position_angle[i]->Fill(
          nPhotonDetectedPosition[i]->at(j)
        );

        // Position of Detected Photons Normalized by Radius

        Int_t bin = hist_total_photon_detected_position_radius->FindBin(
          nPhotonDetectedPosition[i]->at(j)
        );

        float inv_weight = hist_total_photon_detected_position_radius->GetBinCenter(
          bin
        );

        hist_total_photon_detected_position_radius->Fill(
          nPhotonDetectedPosition[i]->at(j), 1.0 / inv_weight
        );

        Int_t bin_i = hist_total_photon_detected_position_radius_angle[i]->FindBin(
          nPhotonDetectedPosition[i]->at(j)
        );

        float inv_weight_i = hist_total_photon_detected_position_radius_angle[i]->GetBinCenter(
          bin_i
        );

        hist_total_photon_detected_position_radius_angle[i]->Fill(
          nPhotonDetectedPosition[i]->at(j), 1.0 / inv_weight_i
        );

      }

    }

  }

  //-------------------------- Draw Histograms --------------------------//

  // Hit Angle

  TLegend* legend_hit_angle = new TLegend(0.55, 0.68, 0.7, 0.85);
  legend_hit_angle->SetBorderSize(0);
  legend_hit_angle->SetFillColorAlpha(0, 0.0);

  // legend_hit_angle->AddEntry(hist_hit_angle, "Total", "F");
  legend_hit_angle->AddEntry(hist_hit_angle_angle[0], "Baseline", "F");
  legend_hit_angle->AddEntry(hist_hit_angle_angle[1], "[0 - 12]", "F");
  legend_hit_angle->AddEntry(hist_hit_angle_angle[2], "[12 - 24]", "F");
  legend_hit_angle->AddEntry(hist_hit_angle_angle[3], "[24 - 36]", "F");
  legend_hit_angle->AddEntry(hist_hit_angle_angle[4], "[36 - 48]", "F");
  legend_hit_angle->AddEntry(hist_hit_angle_angle[5], "[48 - 60]", "F");

  hist_hit_angle_angle[0]->SetStats(false);

  hist_hit_angle->SetMaximum(8000);

  hist_hit_angle_angle[0]->GetYaxis()->SetRangeUser(0, 8000);
  hist_hit_angle->SetFillColorAlpha(kYellow, 0.0);
  hist_hit_angle_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_hit_angle_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_hit_angle_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_hit_angle_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_hit_angle_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_hit_angle_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_hit_angle->Draw();
  hist_hit_angle_angle[0]->Draw();
  hist_hit_angle_angle[1]->Draw("SAME");
  hist_hit_angle_angle[2]->Draw("SAME");
  hist_hit_angle_angle[3]->Draw("SAME");
  hist_hit_angle_angle[4]->Draw("SAME");
  hist_hit_angle_angle[5]->Draw("SAME");
  legend_hit_angle->Draw("SAME");
  canvas->Print("Angles/hit_angle.pdf");
  canvas->Clear();

  // Detected Photons Counter

  TLegend* legend_total_photon_detected_counter = new TLegend(0.55, 0.65, 0.7, 0.82);
  legend_total_photon_detected_counter->SetBorderSize(0);
  legend_total_photon_detected_counter->SetFillColorAlpha(0, 0.0);

  // legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter, "Total", "F");
  legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter_angle[0], "Baseline", "F");
  legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter_angle[1], "[0 - 12]", "F");
  legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter_angle[2], "[12 - 24]", "F");
  legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter_angle[3], "[24 - 36]", "F");
  legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter_angle[4], "[36 - 48]", "F");
  legend_total_photon_detected_counter->AddEntry(hist_total_photon_detected_counter_angle[5], "[48 - 60]", "F");

  hist_total_photon_detected_counter_angle[0]->SetStats(false);

  hist_total_photon_detected_counter_angle[0]->GetYaxis()->SetRangeUser(0, 18000);
  hist_total_photon_detected_counter->SetFillColorAlpha(kYellow, 0.0);
  hist_total_photon_detected_counter_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_total_photon_detected_counter_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_total_photon_detected_counter_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_total_photon_detected_counter_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_total_photon_detected_counter_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_total_photon_detected_counter_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_total_photon_detected_counter->Draw();
  hist_total_photon_detected_counter_angle[0]->Draw();
  hist_total_photon_detected_counter_angle[1]->Draw("SAME");
  hist_total_photon_detected_counter_angle[2]->Draw("SAME");
  hist_total_photon_detected_counter_angle[3]->Draw("SAME");
  hist_total_photon_detected_counter_angle[4]->Draw("SAME");
  hist_total_photon_detected_counter_angle[5]->Draw("SAME");
  legend_total_photon_detected_counter->Draw("SAME");
  canvas->Print("Angles/total_photon_detected_counter.pdf");
  canvas->Clear();


  TLegend* legend_primary_photon_detected_counter = new TLegend(0.25, 0.65, 0.4, 0.82);
  legend_primary_photon_detected_counter->SetBorderSize(0);
  legend_primary_photon_detected_counter->SetFillColorAlpha(0, 0.0);

  // legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter, "Total", "F");
  legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter_angle[0], "Baseline", "F");
  legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter_angle[1], "[0 - 12]", "F");
  legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter_angle[2], "[12 - 24]", "F");
  legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter_angle[3], "[24 - 36]", "F");
  legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter_angle[4], "[36 - 48]", "F");
  legend_primary_photon_detected_counter->AddEntry(hist_primary_photon_detected_counter_angle[5], "[48 - 60]", "F");

  hist_primary_photon_detected_counter_angle[0]->SetStats(false);

  hist_primary_photon_detected_counter_angle[0]->GetYaxis()->SetRangeUser(0, 18000);
  hist_primary_photon_detected_counter->SetFillColorAlpha(kYellow, 0.0);
  hist_primary_photon_detected_counter_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_primary_photon_detected_counter_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_primary_photon_detected_counter_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_primary_photon_detected_counter_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_primary_photon_detected_counter_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_primary_photon_detected_counter_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_primary_photon_detected_counter->Draw();
  hist_primary_photon_detected_counter_angle[0]->Draw();
  hist_primary_photon_detected_counter_angle[1]->Draw("SAME");
  hist_primary_photon_detected_counter_angle[2]->Draw("SAME");
  hist_primary_photon_detected_counter_angle[3]->Draw("SAME");
  hist_primary_photon_detected_counter_angle[4]->Draw("SAME");
  hist_primary_photon_detected_counter_angle[5]->Draw("SAME");
  legend_primary_photon_detected_counter->Draw("SAME");
  canvas->Print("Angles/primary_photon_detected_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(true);


  TLegend* legend_secondary_photon_detected_counter = new TLegend(0.55, 0.65, 0.7, 0.82);
  legend_secondary_photon_detected_counter->SetBorderSize(0);
  legend_secondary_photon_detected_counter->SetFillColorAlpha(0, 0.0);

  // legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter, "Total", "F");
  legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter_angle[0], "Baseline", "F");
  legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter_angle[1], "[0 - 12]", "F");
  legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter_angle[2], "[12 - 24]", "F");
  legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter_angle[3], "[24 - 36]", "F");
  legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter_angle[4], "[36 - 48]", "F");
  legend_secondary_photon_detected_counter->AddEntry(hist_secondary_photon_detected_counter_angle[5], "[48 - 60]", "F");

  hist_secondary_photon_detected_counter_angle[0]->SetStats(false);

  // hist_secondary_photon_detected_counter_angle[0]->GetYaxis()->SetRangeUser(1, 4e6);
  hist_secondary_photon_detected_counter->SetFillColorAlpha(kYellow, 0.0);
  hist_secondary_photon_detected_counter_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_secondary_photon_detected_counter_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_secondary_photon_detected_counter_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_secondary_photon_detected_counter_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_secondary_photon_detected_counter_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_secondary_photon_detected_counter_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_secondary_photon_detected_counter->Draw();
  hist_secondary_photon_detected_counter_angle[0]->Draw();
  hist_secondary_photon_detected_counter_angle[1]->Draw("SAME");
  hist_secondary_photon_detected_counter_angle[2]->Draw("SAME");
  hist_secondary_photon_detected_counter_angle[3]->Draw("SAME");
  hist_secondary_photon_detected_counter_angle[4]->Draw("SAME");
  hist_secondary_photon_detected_counter_angle[5]->Draw("SAME");
  legend_secondary_photon_detected_counter->Draw("SAME");
  canvas->Print("Angles/secondary_photon_detected_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  // Positions of Detected Photons

  TLegend* legend_total_photon_detected_position = new TLegend(0.25, 0.65, 0.4, 0.82);
  legend_total_photon_detected_position->SetBorderSize(0);
  legend_total_photon_detected_position->SetFillColorAlpha(0, 0.0);

  // legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position, "Total", "F");
  legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position_angle[0], "Baseline", "F");
  legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position_angle[1], "[0 - 12]", "F");
  legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position_angle[2], "[12 - 24]", "F");
  legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position_angle[3], "[24 - 36]", "F");
  legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position_angle[4], "[36 - 48]", "F");
  legend_total_photon_detected_position->AddEntry(hist_total_photon_detected_position_angle[5], "[48 - 60]", "F");

  hist_total_photon_detected_position_angle[0]->SetStats(false);

  hist_total_photon_detected_position_angle[0]->GetYaxis()->SetRangeUser(0, 100e4);
  hist_total_photon_detected_position->SetFillColorAlpha(kYellow, 0.0);
  hist_total_photon_detected_position_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_total_photon_detected_position_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_total_photon_detected_position_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_total_photon_detected_position_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_total_photon_detected_position_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_total_photon_detected_position_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_total_photon_detected_position->Draw();
  hist_total_photon_detected_position_angle[0]->Draw();
  hist_total_photon_detected_position_angle[1]->Draw("SAME");
  hist_total_photon_detected_position_angle[2]->Draw("SAME");
  hist_total_photon_detected_position_angle[3]->Draw("SAME");
  hist_total_photon_detected_position_angle[4]->Draw("SAME");
  hist_total_photon_detected_position_angle[5]->Draw("SAME");
  legend_total_photon_detected_position->Draw("SAME");
  canvas->Print("Angles/total_photon_detected_position.pdf");
  canvas->Clear();



  TLegend* legend_primary_photon_detected_position = new TLegend(0.25, 0.65, 0.4, 0.82);
  legend_primary_photon_detected_position->SetBorderSize(0);
  legend_primary_photon_detected_position->SetFillColorAlpha(0, 0.0);

  // legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position, "Total", "F");
  legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position_angle[0], "Baseline", "F");
  legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position_angle[1], "[0 - 12]", "F");
  legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position_angle[2], "[12 - 24]", "F");
  legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position_angle[3], "[24 - 36]", "F");
  legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position_angle[4], "[36 - 48]", "F");
  legend_primary_photon_detected_position->AddEntry(hist_primary_photon_detected_position_angle[5], "[48 - 60]", "F");

  hist_primary_photon_detected_position_angle[0]->SetStats(false);

  hist_primary_photon_detected_position_angle[0]->GetYaxis()->SetRangeUser(0, 100e4);
  hist_primary_photon_detected_position->SetFillColorAlpha(kYellow, 0.0);
  hist_primary_photon_detected_position_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_primary_photon_detected_position_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_primary_photon_detected_position_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_primary_photon_detected_position_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_primary_photon_detected_position_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_primary_photon_detected_position_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_primary_photon_detected_position->Draw();
  hist_primary_photon_detected_position_angle[0]->Draw();
  hist_primary_photon_detected_position_angle[1]->Draw("SAME");
  hist_primary_photon_detected_position_angle[2]->Draw("SAME");
  hist_primary_photon_detected_position_angle[3]->Draw("SAME");
  hist_primary_photon_detected_position_angle[4]->Draw("SAME");
  hist_primary_photon_detected_position_angle[5]->Draw("SAME");
  legend_primary_photon_detected_position->Draw("SAME");
  canvas->Print("Angles/primary_photon_detected_position.pdf");
  canvas->Clear();



  TLegend* legend_secondary_photon_detected_position = new TLegend(0.25, 0.65, 0.4, 0.82);
  legend_secondary_photon_detected_position->SetBorderSize(0);
  legend_secondary_photon_detected_position->SetFillColorAlpha(0, 0.0);

  // legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position, "Total", "F");
  legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position_angle[0], "Baseline", "F");
  legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position_angle[1], "[0 - 12]", "F");
  legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position_angle[2], "[12 - 24]", "F");
  legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position_angle[3], "[24 - 36]", "F");
  legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position_angle[4], "[36 - 48]", "F");
  legend_secondary_photon_detected_position->AddEntry(hist_secondary_photon_detected_position_angle[5], "[48 - 60]", "F");

  hist_secondary_photon_detected_position_angle[0]->SetStats(false);

  hist_secondary_photon_detected_position_angle[0]->GetYaxis()->SetRangeUser(0, 100000);
  hist_secondary_photon_detected_position->SetFillColorAlpha(kYellow, 0.0);
  hist_secondary_photon_detected_position_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_secondary_photon_detected_position_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_secondary_photon_detected_position_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_secondary_photon_detected_position_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_secondary_photon_detected_position_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_secondary_photon_detected_position_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_secondary_photon_detected_position->Draw();
  hist_secondary_photon_detected_position_angle[0]->Draw();
  hist_secondary_photon_detected_position_angle[1]->Draw("SAME");
  hist_secondary_photon_detected_position_angle[2]->Draw("SAME");
  hist_secondary_photon_detected_position_angle[3]->Draw("SAME");
  hist_secondary_photon_detected_position_angle[4]->Draw("SAME");
  hist_secondary_photon_detected_position_angle[5]->Draw("SAME");
  legend_secondary_photon_detected_position->Draw("SAME");
  canvas->Print("Angles/secondary_photon_detected_position.pdf");
  canvas->Clear();

  // -------------------------------------------------------------- //

  // Test

  TLegend* legend_total_photon_detected_position_normalized = new TLegend(0.25, 0.65, 0.4, 0.82);
  legend_total_photon_detected_position_normalized->SetBorderSize(0);
  legend_total_photon_detected_position_normalized->SetFillColorAlpha(0, 0.0);

  // legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized, "Total", "F");
  legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized_angle[0], "Baseline", "F");
  legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized_angle[1], "[0 - 12]", "F");
  legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized_angle[2], "[12 - 24]", "F");
  legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized_angle[3], "[24 - 36]", "F");
  legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized_angle[4], "[36 - 48]", "F");
  legend_total_photon_detected_position_normalized->AddEntry(hist_total_photon_detected_position_normalized_angle[5], "[48 - 60]", "F");

  hist_total_photon_detected_position_normalized_angle[0]->SetStats(false);

  hist_total_photon_detected_position_normalized_angle[0]->GetYaxis()->SetRangeUser(0, 10000);
  hist_total_photon_detected_position_normalized->SetFillColorAlpha(kYellow, 0.0);
  hist_total_photon_detected_position_normalized_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_total_photon_detected_position_normalized_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_total_photon_detected_position_normalized_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_total_photon_detected_position_normalized_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_total_photon_detected_position_normalized_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_total_photon_detected_position_normalized_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_total_photon_detected_position_normalized->Draw("HIST");
  hist_total_photon_detected_position_normalized_angle[0]->Draw("HIST");
  hist_total_photon_detected_position_normalized_angle[1]->Draw("HIST SAME");
  hist_total_photon_detected_position_normalized_angle[2]->Draw("HIST SAME");
  hist_total_photon_detected_position_normalized_angle[3]->Draw("HIST SAME");
  hist_total_photon_detected_position_normalized_angle[4]->Draw("HIST SAME");
  hist_total_photon_detected_position_normalized_angle[5]->Draw("HIST SAME");
  legend_total_photon_detected_position_normalized->Draw("SAME");
  canvas->Print("Angles/total_photon_detected_position_normalized.pdf");
  canvas->Clear();

  //// Test 3 ////

  canvas->SetLogy(true);

  TLegend* legend_total_photon_detected_position_radius = new TLegend(0.55, 0.65, 0.7, 0.82);
  legend_total_photon_detected_position_radius->SetBorderSize(0);
  legend_total_photon_detected_position_radius->SetFillColorAlpha(0, 0.0);

  // legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius, "Total", "F");
  legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius_angle[0], "Baseline", "F");
  legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius_angle[1], "[0 - 12]", "F");
  legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius_angle[2], "[12 - 24]", "F");
  legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius_angle[3], "[24 - 36]", "F");
  legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius_angle[4], "[36 - 48]", "F");
  legend_total_photon_detected_position_radius->AddEntry(hist_total_photon_detected_position_radius_angle[5], "[48 - 60]", "F");

  hist_total_photon_detected_position_radius_angle[0]->SetStats(false);

  // Position of Detected Photons Normalized by Radius
  hist_total_photon_detected_position_radius->GetYaxis()->SetRangeUser(1, 4e6);
  hist_total_photon_detected_position_radius_angle[0]->GetYaxis()->SetRangeUser(1, 5e9);
  hist_total_photon_detected_position_radius->SetFillColorAlpha(kYellow, 0.0);
  hist_total_photon_detected_position_radius_angle[0]->SetFillColorAlpha(kYellow, 1);
  hist_total_photon_detected_position_radius_angle[1]->SetFillColorAlpha(kRed, 0.3);
  hist_total_photon_detected_position_radius_angle[2]->SetFillColorAlpha(kBlue, 0.3);
  hist_total_photon_detected_position_radius_angle[3]->SetFillColorAlpha(kMagenta, 0.3);
  hist_total_photon_detected_position_radius_angle[4]->SetFillColorAlpha(kGreen, 0.3);
  hist_total_photon_detected_position_radius_angle[5]->SetFillColorAlpha(kCyan, 0.3);
  // hist_total_photon_detected_position_radius->Draw("HIST");
  hist_total_photon_detected_position_radius_angle[0]->Draw("HIST");
  hist_total_photon_detected_position_radius_angle[1]->Draw("HIST SAME");
  hist_total_photon_detected_position_radius_angle[2]->Draw("HIST SAME");
  hist_total_photon_detected_position_radius_angle[3]->Draw("HIST SAME");
  hist_total_photon_detected_position_radius_angle[4]->Draw("HIST SAME");
  hist_total_photon_detected_position_radius_angle[5]->Draw("HIST SAME");
  legend_total_photon_detected_position_radius->Draw("SAME");
  canvas->Print("Angles/total_photon_detected_position_radius_norm_TEST.pdf");
  canvas->Clear();

  //---------------------------------------------------------------------//

}
