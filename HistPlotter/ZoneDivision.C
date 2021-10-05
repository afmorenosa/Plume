
void ZoneDivision() {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *root_file = TFile::Open("quartz.root");

  TTree *tree = (TTree *) root_file->Get("T");

  //------------------------ Branches variables ------------------------//

  // Zones
  Int_t Zone = -1;

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

  // Zones
  tree->SetBranchAddress("Zone", &Zone);

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

  // Position of TOTAL Detected Photons Divided by Zone


  TH1F *hist_total_photon_detected_position_zone_1 = new TH1F(
    "Positions of Total Detected Photons Zone 1",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_zone_2 = new TH1F(
    "Positions of Total Detected Photons Zone 2",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_zone_3 = new TH1F(
    "Positions of Total Detected Photons Zone 3",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_zone_4 = new TH1F(
    "Positions of Total Detected Photons Zone 4",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_zone_5 = new TH1F(
    "Positions of Total Detected Photons Zone 5",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );



  // Position of PRIMARY Detected Photons Divided by Zone

  TH1F *hist_primary_photon_detected_position_zone_1 = new TH1F(
    "Positions of Primary Detected Photons Zone 1",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_primary_photon_detected_position_zone_2 = new TH1F(
    "Positions of Primary Detected Photons Zone 2",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_primary_photon_detected_position_zone_3 = new TH1F(
    "Positions of Primary Detected Photons Zone 3",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_primary_photon_detected_position_zone_4 = new TH1F(
    "Positions of Primary Detected Photons Zone 4",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_primary_photon_detected_position_zone_5 = new TH1F(
    "Positions of Primary Detected Photons Zone 5",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );


  // Position of SECONDARY Detected Photons Divided by Zone

  TH1F *hist_secondary_photon_detected_position_zone_1 = new TH1F(
    "Positions of Secondary Detected Photons Zone 1",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_secondary_photon_detected_position_zone_2 = new TH1F(
    "Positions of Secondary Detected Photons Zone 2",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_secondary_photon_detected_position_zone_3 = new TH1F(
    "Positions of Secondary Detected Photons Zone 3",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_secondary_photon_detected_position_zone_4 = new TH1F(
    "Positions of Secondary Detected Photons Zone 4",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_secondary_photon_detected_position_zone_5 = new TH1F(
    "Positions of Secondary Detected Photons Zone 5",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  // Position of TOTAL Detected Photons Normalized by Radius
  TH1F *hist_total_photon_detected_position_radius = new TH1F(
    "Positions of Total Detected Photons Normalized",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    50,
    0,
    5
  );

  // Position of PRIMARY Detected Photons Normalized by Radius
  TH1F *hist_primary_photon_detected_position_radius = new TH1F(
    "Positions of Primary Detected Photons Normalized",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    50,
    0,
    5
  );

  // Position of SECONDARY Detected Photons Normalized by Radius
  TH1F *hist_secondary_photon_detected_position_radius = new TH1F(
    "Positions of Secondary Detected Photons Normalized",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
    50,
    0,
    5
  );

  /////////////-------------------------------------------->>>>>>>>>>>>>>>>

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {

      // Positions of TOTAL Detected Photons Divided by Zones

      if (Zone == 0) {
          Int_t bin = hist_total_photon_detected_position_zone_1->FindBin(
            nPhotonDetectedPosition->at(j)
          );

          float inv_weight = hist_total_photon_detected_position_zone_1->GetBinCenter(
            bin
          );

          hist_total_photon_detected_position_zone_1->Fill(
            nPhotonDetectedPosition->at(j), 1.0 / inv_weight
          );
      } else if (Zone == 1) {
          Int_t bin = hist_total_photon_detected_position_zone_2->FindBin(
            nPhotonDetectedPosition->at(j)
          );

          float inv_weight = hist_total_photon_detected_position_zone_2->GetBinCenter(
            bin
          );

          hist_total_photon_detected_position_zone_2->Fill(
            nPhotonDetectedPosition->at(j), 1.0 / inv_weight
          );
      } else if (Zone == 2) {
          Int_t bin = hist_total_photon_detected_position_zone_3->FindBin(
            nPhotonDetectedPosition->at(j)
          );

          float inv_weight = hist_total_photon_detected_position_zone_3->GetBinCenter(
            bin
          );

          hist_total_photon_detected_position_zone_3->Fill(
            nPhotonDetectedPosition->at(j), 1.0 / inv_weight
          );
      } else if (Zone == 3) {
          Int_t bin = hist_total_photon_detected_position_zone_4->FindBin(
            nPhotonDetectedPosition->at(j)
          );

          float inv_weight = hist_total_photon_detected_position_zone_4->GetBinCenter(
            bin
          );

          hist_total_photon_detected_position_zone_4->Fill(
            nPhotonDetectedPosition->at(j), 1.0 / inv_weight
          );
      } else {
          Int_t bin = hist_total_photon_detected_position_zone_5->FindBin(
            nPhotonDetectedPosition->at(j)
          );

          float inv_weight = hist_total_photon_detected_position_zone_5->GetBinCenter(
            bin
          );

          hist_total_photon_detected_position_zone_5->Fill(
            nPhotonDetectedPosition->at(j), 1.0 / inv_weight
          );
      }

      // Position of TOTAL Detected Photons Normalized by Radius

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


    for (size_t j = 0; j < nPriPhotonDetectedPosition->size(); j++) {

      // Positions of PRIMARY Detected Photons Divided by Zones

      if (Zone == 0) {
        hist_primary_photon_detected_position_zone_1->Fill(
          nPriPhotonDetectedPosition->at(j)
        );
      } else if (Zone == 1) {
        hist_primary_photon_detected_position_zone_2->Fill(
          nPriPhotonDetectedPosition->at(j)
        );
      } else if (Zone == 2) {
        hist_primary_photon_detected_position_zone_3->Fill(
          nPriPhotonDetectedPosition->at(j)
        );
      } else if (Zone == 3) {
        hist_primary_photon_detected_position_zone_4->Fill(
          nPriPhotonDetectedPosition->at(j)
        );
      } else {
        hist_primary_photon_detected_position_zone_5->Fill(
          nPriPhotonDetectedPosition->at(j)
        );
      }

      // Position of PRIMARY Detected Photons Normalized by Radius

      Int_t bin = hist_primary_photon_detected_position_radius->FindBin(
        nPriPhotonDetectedPosition->at(j)
      );

      float inv_weight = hist_primary_photon_detected_position_radius->GetBinCenter(
        bin
      );

      hist_primary_photon_detected_position_radius->Fill(
        nPriPhotonDetectedPosition->at(j), 1.0 / inv_weight
      );

    }


    for (size_t j = 0; j < nSecPhotonDetectedPosition->size(); j++) {

      // Positions of SECONDARY Detected Photons Divided by Zones

      if (Zone == 0) {
        hist_secondary_photon_detected_position_zone_1->Fill(
          nSecPhotonDetectedPosition->at(j)
        );
      } else if (Zone == 1) {
        hist_secondary_photon_detected_position_zone_2->Fill(
          nSecPhotonDetectedPosition->at(j)
        );
      } else if (Zone == 2) {
        hist_secondary_photon_detected_position_zone_3->Fill(
          nSecPhotonDetectedPosition->at(j)
        );
      } else if (Zone == 3) {
        hist_secondary_photon_detected_position_zone_4->Fill(
          nSecPhotonDetectedPosition->at(j)
        );
      } else {
        hist_secondary_photon_detected_position_zone_5->Fill(
          nSecPhotonDetectedPosition->at(j)
        );
      }

      // Position of SECONDARY Detected Photons Normalized by Radius

      Int_t bin = hist_secondary_photon_detected_position_radius->FindBin(
        nSecPhotonDetectedPosition->at(j)
      );

      float inv_weight = hist_secondary_photon_detected_position_radius->GetBinCenter(
        bin
      );

      hist_secondary_photon_detected_position_radius->Fill(
        nSecPhotonDetectedPosition->at(j), 1.0 / inv_weight
      );

    }

  }

  //-------------------------- Darw Histograms --------------------------//


  // Position of TOTAL Detected Photons Divided by Zones
  TLegend* legend_total_photon_detected_position_zones = new TLegend(0.75, 0.73, 0.9, 0.9);
  legend_total_photon_detected_position_zones->SetBorderSize(1);
  legend_total_photon_detected_position_zones->SetFillColor(0);

  legend_total_photon_detected_position_zones->AddEntry(
    hist_total_photon_detected_position_zone_1, "Zone 1", "F"
  );
  legend_total_photon_detected_position_zones->AddEntry(
    hist_total_photon_detected_position_zone_2, "Zone 2", "F"
  );
  legend_total_photon_detected_position_zones->AddEntry(
    hist_total_photon_detected_position_zone_3, "Zone 3", "F"
  );
  legend_total_photon_detected_position_zones->AddEntry(
    hist_total_photon_detected_position_zone_4, "Zone 4", "F"
  );
  legend_total_photon_detected_position_zones->AddEntry(
    hist_total_photon_detected_position_zone_5, "Zone 5", "F"
  );

  hist_total_photon_detected_position_zone_1->GetYaxis()->SetRangeUser(0,100e3);
  hist_total_photon_detected_position_zone_1->SetStats(false);
  hist_total_photon_detected_position_zone_1->SetFillColorAlpha(kRed, 0.5);

  hist_total_photon_detected_position_zone_2->SetStats(false);
  hist_total_photon_detected_position_zone_2->SetFillColorAlpha(kBlue, 0.5);

  hist_total_photon_detected_position_zone_3->SetStats(false);
  hist_total_photon_detected_position_zone_3->SetFillColorAlpha(kMagenta, 0.5);

  hist_total_photon_detected_position_zone_4->SetStats(false);
  hist_total_photon_detected_position_zone_4->SetFillColorAlpha(kGreen, 0.5);

  hist_total_photon_detected_position_zone_5->SetStats(false);
  hist_total_photon_detected_position_zone_5->SetFillColorAlpha(kCyan, 0.5);

  hist_total_photon_detected_position_zone_1->Draw("HIST");
  hist_total_photon_detected_position_zone_2->Draw("HIST SAME");
  hist_total_photon_detected_position_zone_3->Draw("HIST SAME");
  hist_total_photon_detected_position_zone_4->Draw("HIST SAME");
  hist_total_photon_detected_position_zone_5->Draw("HIST SAME");
  legend_total_photon_detected_position_zones->Draw("SAME");
  canvas->Print("Zone Division/total_detected_photons_position_ZONES_NORMALIZED.pdf");
  canvas->Clear();



  // Position of PRIMARY Detected Photons Divided by Zones
  TLegend* legend_primary_photon_detected_position_zones = new TLegend(0.75, 0.73, 0.9, 0.9);
  legend_primary_photon_detected_position_zones->SetBorderSize(1);
  legend_primary_photon_detected_position_zones->SetFillColor(0);

  legend_primary_photon_detected_position_zones->AddEntry(
    hist_primary_photon_detected_position_zone_1, "Zone 1", "F"
  );
  legend_primary_photon_detected_position_zones->AddEntry(
    hist_primary_photon_detected_position_zone_2, "Zone 2", "F"
  );
  legend_primary_photon_detected_position_zones->AddEntry(
    hist_primary_photon_detected_position_zone_3, "Zone 3", "F"
  );
  legend_primary_photon_detected_position_zones->AddEntry(
    hist_primary_photon_detected_position_zone_4, "Zone 4", "F"
  );
  legend_primary_photon_detected_position_zones->AddEntry(
    hist_primary_photon_detected_position_zone_5, "Zone 5", "F"
  );

  hist_primary_photon_detected_position_zone_1->GetYaxis()->SetRangeUser(0,410e3);
  hist_primary_photon_detected_position_zone_1->SetStats(false);
  hist_primary_photon_detected_position_zone_1->SetFillColorAlpha(kRed, 0.5);

  hist_primary_photon_detected_position_zone_2->SetStats(false);
  hist_primary_photon_detected_position_zone_2->SetFillColorAlpha(kBlue, 0.5);

  hist_primary_photon_detected_position_zone_3->SetStats(false);
  hist_primary_photon_detected_position_zone_3->SetFillColorAlpha(kMagenta, 0.5);

  hist_primary_photon_detected_position_zone_4->SetStats(false);
  hist_primary_photon_detected_position_zone_4->SetFillColorAlpha(kGreen, 0.5);

  hist_primary_photon_detected_position_zone_5->SetStats(false);
  hist_primary_photon_detected_position_zone_5->SetFillColorAlpha(kCyan, 0.5);

  hist_primary_photon_detected_position_zone_1->Draw("HIST");
  hist_primary_photon_detected_position_zone_2->Draw("HIST SAME");
  hist_primary_photon_detected_position_zone_3->Draw("HIST SAME");
  hist_primary_photon_detected_position_zone_4->Draw("HIST SAME");
  hist_primary_photon_detected_position_zone_5->Draw("HIST SAME");
  legend_primary_photon_detected_position_zones->Draw("SAME");
  canvas->Print("Zone Division/primary_detected_photons_position_ZONES.pdf");
  canvas->Clear();


  // Position of SECONDARY Detected Photons Divided by Zones
  TLegend* legend_secondary_photon_detected_position_zones = new TLegend(0.75, 0.73, 0.9, 0.9);
  legend_secondary_photon_detected_position_zones->SetBorderSize(1);
  legend_secondary_photon_detected_position_zones->SetFillColor(0);

  legend_secondary_photon_detected_position_zones->AddEntry(
    hist_secondary_photon_detected_position_zone_1, "Zone 1", "F"
  );
  legend_secondary_photon_detected_position_zones->AddEntry(
    hist_secondary_photon_detected_position_zone_2, "Zone 2", "F"
  );
  legend_secondary_photon_detected_position_zones->AddEntry(
    hist_secondary_photon_detected_position_zone_3, "Zone 3", "F"
  );
  legend_secondary_photon_detected_position_zones->AddEntry(
    hist_secondary_photon_detected_position_zone_4, "Zone 4", "F"
  );
  legend_secondary_photon_detected_position_zones->AddEntry(
    hist_secondary_photon_detected_position_zone_5, "Zone 5", "F"
  );

  hist_secondary_photon_detected_position_zone_1->GetYaxis()->SetRangeUser(0,15e3);
  hist_secondary_photon_detected_position_zone_1->SetStats(false);
  hist_secondary_photon_detected_position_zone_1->SetFillColorAlpha(kRed, 0.5);

  hist_secondary_photon_detected_position_zone_2->SetStats(false);
  hist_secondary_photon_detected_position_zone_2->SetFillColorAlpha(kBlue, 0.5);

  hist_secondary_photon_detected_position_zone_3->SetStats(false);
  hist_secondary_photon_detected_position_zone_3->SetFillColorAlpha(kMagenta, 0.5);

  hist_secondary_photon_detected_position_zone_4->SetStats(false);
  hist_secondary_photon_detected_position_zone_4->SetFillColorAlpha(kGreen, 0.5);

  hist_secondary_photon_detected_position_zone_5->SetStats(false);
  hist_secondary_photon_detected_position_zone_5->SetFillColorAlpha(kCyan, 0.5);

  hist_secondary_photon_detected_position_zone_1->Draw("HIST");
  hist_secondary_photon_detected_position_zone_2->Draw("HIST SAME");
  hist_secondary_photon_detected_position_zone_3->Draw("HIST SAME");
  hist_secondary_photon_detected_position_zone_4->Draw("HIST SAME");
  hist_secondary_photon_detected_position_zone_5->Draw("HIST SAME");
  legend_secondary_photon_detected_position_zones->Draw("SAME");
  canvas->Print("Zone Division/secondary_detected_photons_position_ZONES.pdf");
  canvas->Clear();


  // Position of TOTAL Detected Photons Normalized by Radius
  hist_total_photon_detected_position_radius->GetYaxis()->SetRangeUser(0,500e3);
  hist_total_photon_detected_position_radius->SetStats(false);
  hist_total_photon_detected_position_radius->SetFillColor(kYellow);
  hist_total_photon_detected_position_radius->Draw("HIST");
  canvas->Print("Zone Division/total_photon_detected_position_radius_norm.pdf");
  canvas->Clear();


  // Position of PRIMARY Detected Photons Normalized by Radius
  hist_primary_photon_detected_position_radius->GetYaxis()->SetRangeUser(0,500e3);
  hist_primary_photon_detected_position_radius->SetStats(false);
  hist_primary_photon_detected_position_radius->SetFillColor(kYellow);
  hist_primary_photon_detected_position_radius->Draw("HIST");
  canvas->Print("Zone Division/primary_photon_detected_position_radius_norm.pdf");
  canvas->Clear();


  // Position of SECONDARY Detected Photons Normalized by Radius
  hist_secondary_photon_detected_position_radius->GetYaxis()->SetRangeUser(0,20e3);
  hist_secondary_photon_detected_position_radius->SetStats(false);
  hist_secondary_photon_detected_position_radius->SetFillColor(kYellow);
  hist_secondary_photon_detected_position_radius->Draw("HIST");
  canvas->Print("Zone Division/secondary_photon_detected_position_radius_norm.pdf");
  canvas->Clear();

}
