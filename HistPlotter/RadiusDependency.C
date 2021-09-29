
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

  // Hit Angle
  tree->SetBranchAddress("hitAngle", &hitAngle);
  // Positions of Primary Electron
  Double_t nPostPVxPosition = -1.0;
  Double_t nPostPVyPosition = -1.0;

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
    "Secondary Photons Detected Counter tail",
    "Secondary Photons Detected Counter tail; n Photons; Events",
    100,
    0,
    1000
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


  // 2D Positions Histogram of Primary Electron

  TH2D *hist_pos_PVPosition = new TH2D(
    "Electron Entrance Position",
    "Electron Entrance Position; X [mm]; Y[mm]; ",
    100,
    -5,
    5,
    100,
    -5,
    5
  );

  /////////////------------------------------------------

  // Test
  TH1F *hist_total_photon_detected_position_test1 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 1]",
    "Positions of Total Detected Photons Normalized [Zone 1]; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_test2 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 2]",
    "Positions of Total Detected Photons Normalized [Zone 2]; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_test3 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 3]",
    "Positions of Total Detected Photons Normalized [Zone 3]; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_test4 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 4]",
    "Positions of Total Detected Photons Normalized [Zone 4]; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1F *hist_total_photon_detected_position_test5 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 5]",
    "Positions of Total Detected Photons Normalized By Zones; Radius [mm]; Events",
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


  /////////////-------------------------------------------->>>>>>>>>>>>>>>>

  //--------------------------------------------------------------------//
  Double_t totalPhotonsZone0 = 0.;
  Double_t totalPhotonsZone1 = 0.;
  Double_t totalPhotonsZone2 = 0.;
  Double_t totalPhotonsZone3 = 0.;
  Double_t totalPhotonsZone4 = 0.;

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {

      if (nPhotonDetectedPosition->at(j) < std::sqrt(5.)) {
        totalPhotonsZone0++;
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(10.)) {
        totalPhotonsZone1++;
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(15.)) {
        totalPhotonsZone2++;
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(20.)) {
        totalPhotonsZone3++;
      } else {
        totalPhotonsZone4++;
      }

    }

  }

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Hit Angle
    hist_hit_angle->Fill(hitAngle / M_PI * 180);
    // if (Zone != 4) continue;

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

    // Positions of Primary Electron
    hist_pos_PVPosition->Fill(nPostPVxPosition, nPostPVyPosition);

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
      } else if (nPhotonDetectedPosition ->at(j)< std::sqrt(10.0)) {
        phtoton_zone = 1;
      } else if (nPhotonDetectedPosition ->at(j)< std::sqrt(15.0)) {
        phtoton_zone = 2;
      } else if (nPhotonDetectedPosition ->at(j)< std::sqrt(20.0)) {
        phtoton_zone = 3;
      } else {
        phtoton_zone = 4;
      }

      hist_total_photon_detected_position_normalized->Fill(
        nPhotonDetectedPosition->at(j), 1.0/(zones_counter[phtoton_zone]*1.0)
      );
    }

    // //////////// ------ TEST ------
    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {

      // Positions of Detected Photons

      hist_total_photon_detected_position->Fill(
        nPhotonDetectedPosition->at(j)
      );


      // Positions of Detected Photons Normalized by Zones

      if (nPhotonDetectedPosition->at(j) < std::sqrt(5.)) {
        hist_total_photon_detected_position_test1->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(10.)) {
        hist_total_photon_detected_position_test2->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(15.)) {
        hist_total_photon_detected_position_test3->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(20.)) {
        hist_total_photon_detected_position_test4->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else {
        hist_total_photon_detected_position_test5->Fill(
          nPhotonDetectedPosition->at(j)
        );
      }


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

// -------------------------------------------------------------- //

hist_pos_PVPosition->Draw("COLZ");
hist_pos_PVPosition->SetStats(kFALSE);
TEllipse *elip1 = new TEllipse(0, 0, std::sqrt(5*1), std::sqrt(5*1));
TEllipse *elip2 = new TEllipse(0, 0, std::sqrt(5*2), std::sqrt(5*2));
TEllipse *elip3 = new TEllipse(0, 0, std::sqrt(5*3), std::sqrt(5*3));
TEllipse *elip4 = new TEllipse(0, 0, std::sqrt(5*4), std::sqrt(5*4));
TEllipse *elip5 = new TEllipse(0, 0, std::sqrt(5*5), std::sqrt(5*5));

elip1->SetLineWidth(2);
elip2->SetLineWidth(2);
elip3->SetLineWidth(2);
elip4->SetLineWidth(2);
elip5->SetLineWidth(2);

elip1->SetLineColor(kRed);
elip2->SetLineColor(kRed);
elip3->SetLineColor(kRed);
elip4->SetLineColor(kRed);
elip5->SetLineColor(kRed);

elip1->SetFillColorAlpha(kRed, 0.0);
elip2->SetFillColorAlpha(kRed, 0.0);
elip3->SetFillColorAlpha(kRed, 0.0);
elip4->SetFillColorAlpha(kRed, 0.0);
elip5->SetFillColorAlpha(kRed, 0.0);

elip5->Draw("same");
elip4->Draw("same");
elip3->Draw("same");
elip2->Draw("same");
elip1->Draw("same");

TText *text1 = new TText(0.8, 1.4, "Zone 1");
TText *text2 = new TText(1.4, 2.1, "Zone 2");
TText *text3 = new TText(1.9, 2.7, "Zone 3");
TText *text4 = new TText(2.4, 3.2, "Zone 4");
TText *text5 = new TText(2.8, 3.6, "Zone 5");

text1->SetTextSize(0.03);
text2->SetTextSize(0.03);
text3->SetTextSize(0.03);
text4->SetTextSize(0.03);
text5->SetTextSize(0.03);

text1->SetTextAngle(-45.0);
text2->SetTextAngle(-45.0);
text3->SetTextAngle(-45.0);
text4->SetTextAngle(-45.0);
text5->SetTextAngle(-45.0);

text1->Draw("same");
text2->Draw("same");
text3->Draw("same");
text4->Draw("same");
text5->Draw("same");

canvas->Print("pos_PVPosition.pdf");
canvas->Clear();


// Test

hist_total_photon_detected_position_normalized->SetFillColor(kYellow);
hist_total_photon_detected_position_normalized->Draw("hist");
canvas->Print("Totals/total_photon_detected_position_normalized.pdf");
canvas->Clear();

///////// Test 3 \\\\\\\\\\\\

hist_total_photon_detected_position_test1->Scale(
  1./hist_total_photon_detected_position_test1->Integral()
);
hist_total_photon_detected_position_test1->SetStats(false);
hist_total_photon_detected_position_test1->SetFillColor(kYellow);
hist_total_photon_detected_position_test2->Scale(
  1./hist_total_photon_detected_position_test2->Integral()
);
hist_total_photon_detected_position_test2->SetStats(false);
hist_total_photon_detected_position_test2->SetFillColor(kYellow);
hist_total_photon_detected_position_test3->Scale(
  1./hist_total_photon_detected_position_test3->Integral()
);
hist_total_photon_detected_position_test3->SetStats(false);
hist_total_photon_detected_position_test3->SetFillColor(kYellow);
hist_total_photon_detected_position_test4->Scale(
  1./hist_total_photon_detected_position_test4->Integral()
);
hist_total_photon_detected_position_test4->SetStats(false);
hist_total_photon_detected_position_test4->SetFillColor(kYellow);
hist_total_photon_detected_position_test5->Scale(
  1./hist_total_photon_detected_position_test5->Integral()
);
hist_total_photon_detected_position_test5->SetStats(false);
hist_total_photon_detected_position_test5->SetFillColor(kYellow);

hist_total_photon_detected_position_test5->Draw("HIST");
hist_total_photon_detected_position_test4->Draw("HIST SAME");
hist_total_photon_detected_position_test3->Draw("HIST SAME");
hist_total_photon_detected_position_test2->Draw("HIST SAME");
hist_total_photon_detected_position_test1->Draw("HIST SAME");
canvas->Print("Totals/total_photon__detected_position_test3.pdf");
canvas->Clear();

// Position of Detected Photons Normalized by Radius
hist_total_photon_detected_position_radius->GetYaxis()->SetRangeUser(0,500e3);
hist_total_photon_detected_position_radius->SetFillColor(kYellow);
hist_total_photon_detected_position_radius->Draw("HIST");
canvas->Print("total_photon_detected_position_radius_norm.pdf");
canvas->Clear();

}
