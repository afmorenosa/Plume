
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
    "Secondary Photons Detected Counter tail",
    "Secondary Photons Detected Counter tail; n Photons; Events",
    100,
    0,
    1000
  );

  // Counter of Positions of Detected Photons

  TH1I *hist_total_photon_detected_position = new TH1I(
    "Positions of Total Detected Photons",
    "Positions of Total Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1I *hist_primary_photon_detected_position = new TH1I(
    "Positions of Primary Detected Photons",
    "Positions of Primary Detected Photons; Radius [mm]; Events",
    100,
    0,
    5
  );

  TH1I *hist_secondary_photon_detected_position = new TH1I(
    "Positions of Secondary Detected Photons",
    "Positions of Secondary Detected Photons; Radius [mm]; Events",
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
<<<<<<< HEAD

  // Position of Detected Photons Normalized
  TH1F *hist_total_photon_detected_position_zone_1 = new TH1F(
    "Positions of Total Detected Photons Test",
    "Positions of Total Detected Photons Test; Radius [mm]; Events",
=======

  /////////////------------------------------------------>>>>>>>>>>>>>>>>

  // Test
  TH1F *hist_total_photon_detected_position_test1 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 1]",
    "Positions of Total Detected Photons Normalized [Zone 1]; Radius [mm]; Events",
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8
    100,
    0,
    5
  );

<<<<<<< HEAD
  TH1F *hist_total_photon_detected_position_zone_2 = new TH1F(
    "Positions of Total Detected Photons Test",
    "Positions of Total Detected Photons Test; Radius [mm]; Events",
=======
  TH1F *hist_total_photon_detected_position_test2 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 2]",
    "Positions of Total Detected Photons Normalized [Zone 2]; Radius [mm]; Events",
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8
    100,
    0,
    5
  );

<<<<<<< HEAD
  TH1F *hist_total_photon_detected_position_zone_3 = new TH1F(
    "Positions of Total Detected Photons Test",
    "Positions of Total Detected Photons Test; Radius [mm]; Events",
=======
  TH1F *hist_total_photon_detected_position_test3 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 3]",
    "Positions of Total Detected Photons Normalized [Zone 3]; Radius [mm]; Events",
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8
    100,
    0,
    5
  );

<<<<<<< HEAD
  TH1F *hist_total_photon_detected_position_zone_4 = new TH1F(
    "Positions of Total Detected Photons Test",
    "Positions of Total Detected Photons Test; Radius [mm]; Events",
=======
  TH1F *hist_total_photon_detected_position_test4 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 4]",
    "Positions of Total Detected Photons Normalized [Zone 4]; Radius [mm]; Events",
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8
    100,
    0,
    5
  );

<<<<<<< HEAD
  TH1F *hist_total_photon_detected_position_zone_5 = new TH1F(
    "Positions of Total Detected Photons Test",
    "Positions of Total Detected Photons Test; Radius [mm]; Events",
=======
  TH1F *hist_total_photon_detected_position_test5 = new TH1F(
    "Positions of Total Detected Photons Normalized [Zone 5]",
    "Positions of Total Detected Photons Normalized By Zones; Radius [mm]; Events",
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8
    100,
    0,
    5
  );

  /////////////-------------------------------------------->>>>>>>>>>>>>>>>

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // if (Zone != 4) continue;

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

    // Positions of Primary Electron
    hist_pos_PVPosition->Fill(nPostPVxPosition, nPostPVyPosition);

<<<<<<< HEAD
    // Positions of Detected Photons Normalized
=======
    std::map<Int_t, Int_t> zones_counter;

    zones_counter[0] = nPhotonZone0;
    zones_counter[1] = nPhotonZone1;
    zones_counter[2] = nPhotonZone2;
    zones_counter[3] = nPhotonZone3;
    zones_counter[4] = nPhotonZone4;

    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {
      hist_total_photon_detected_position_normalized->Fill(
        nPhotonDetectedPosition->at(j), 1.0/(zones_counter[Zone]*1.0)
      );
    }

    // //////////// ------ TEST ------ >>>>>>>>>>>>>> >>
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8

    for (size_t j = 0; j < nPhotonDetectedPosition->size(); j++) {
      if (nPhotonDetectedPosition->at(j) < std::sqrt(5.)) {
        hist_total_photon_detected_position_zone_1->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(10.)) {
        hist_total_photon_detected_position_zone_2->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(15.)) {
        hist_total_photon_detected_position_zone_3->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else if (nPhotonDetectedPosition->at(j) < std::sqrt(20.)) {
        hist_total_photon_detected_position_zone_4->Fill(
          nPhotonDetectedPosition->at(j)
        );
      } else {
        hist_total_photon_detected_position_zone_5->Fill(
          nPhotonDetectedPosition->at(j)
        );
      }

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


<<<<<<< HEAD
// Position of Detected Photons Normalized
=======
// Test

hist_total_photon_detected_position_normalized->SetFillColor(kYellow);
hist_total_photon_detected_position_normalized->Draw();
canvas->Print("Totals/total_photon_detected_position_normalized.pdf");
canvas->Clear();

///////// Test 3 >>>>>>>>>>>>>>>>
>>>>>>> 6ae243952e8635b02908ceb9480cad1573ae81a8

hist_total_photon_detected_position_zone_1->Scale(
  1./hist_total_photon_detected_position_zone_1->Integral()
);
hist_total_photon_detected_position_zone_1->SetStats(false);
hist_total_photon_detected_position_zone_1->SetFillColor(kYellow);
hist_total_photon_detected_position_zone_2->Scale(
  1./hist_total_photon_detected_position_zone_2->Integral()
);
hist_total_photon_detected_position_zone_2->SetStats(false);
hist_total_photon_detected_position_zone_2->SetFillColor(kYellow);
hist_total_photon_detected_position_zone_3->Scale(
  1./hist_total_photon_detected_position_zone_3->Integral()
);
hist_total_photon_detected_position_zone_3->SetStats(false);
hist_total_photon_detected_position_zone_3->SetFillColor(kYellow);
hist_total_photon_detected_position_zone_4->Scale(
  1./hist_total_photon_detected_position_zone_4->Integral()
);
hist_total_photon_detected_position_zone_4->SetStats(false);
hist_total_photon_detected_position_zone_4->SetFillColor(kYellow);
hist_total_photon_detected_position_zone_5->Scale(
  1./hist_total_photon_detected_position_zone_5->Integral()
);
hist_total_photon_detected_position_zone_5->SetStats(false);
hist_total_photon_detected_position_zone_5->SetFillColor(kYellow);

hist_total_photon_detected_position_zone_5->Draw("HIST");
hist_total_photon_detected_position_zone_4->Draw("HIST SAME");
hist_total_photon_detected_position_zone_3->Draw("HIST SAME");
hist_total_photon_detected_position_zone_2->Draw("HIST SAME");
hist_total_photon_detected_position_zone_1->Draw("HIST SAME");
canvas->Print("Totals/total_photon__detected_position_normalized.pdf");
canvas->Clear();



}
