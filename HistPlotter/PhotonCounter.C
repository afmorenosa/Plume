void PhotonCounter() {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *plume_file = TFile::Open("one.root");

  TTree *tree = (TTree *) plume_file->Get("T");

  // Hit Angle
  double hitAngle = 0.0;

  // Zones
  Int_t Zones = -1;

  // Detected Photons
  Int_t nPhotonDetected1 = -1;
  Int_t nPhotonDetected2 = -1;

  Int_t nSecPhotonDetected1 = -1;
  Int_t nSecPhotonDetected2 = -1;

  // Positions of Primary Electron
  Double_t nPostPVxPosition = -1.0;
  Double_t nPostPVyPosition = -1.0;

  // Hit Angle
  tree->SetBranchAddress("hitAngle", &hitAngle);

  // Detected Photons
  tree->SetBranchAddress("nPhotonDetected1", &nPhotonDetected1);
  tree->SetBranchAddress("nPhotonDetected2", &nPhotonDetected2);

  tree->SetBranchAddress("nSecPhotonDetected1", &nSecPhotonDetected1);
  tree->SetBranchAddress("nSecPhotonDetected2", &nSecPhotonDetected2);

  // Positions of Primary Electron
  tree->SetBranchAddress("nPostPVxPosition", &nPostPVxPosition);
  tree->SetBranchAddress("nPostPVyPosition", &nPostPVyPosition);

  // Hit Angle

  TH1I *hist_hit_angle = new TH1I(
    "Hit Angle",
    "Hit Angle; Angle [°]; Events",
    100,
    0,
    1.5
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

  // Detected Photons

  TH1I *hist_tot_detected_photons_1 = new TH1I(
    "Detected Photons Module 1",
    "Detected Photons Module 1; Number of Photons; Number of Events",
    100,
    0,
    4000
  );

  TH1I *hist_tot_detected_photons_2 = new TH1I(
    "Detected Photons Module 2",
    "Detected Photons Module 2; Number of Photons; Number of Events",
    100,
    0,
    4000
  );

  TH2I *hist_tot_detected_photons = new TH2I(
    "Detected Photons Module",
    "Detected Photons Module; Number of Photons; Number of Events",
    100,
    0,
    2000,
    100,
    0,
    2000
  );

  //-----//

  TH1I *hist_secondary_detected_photons_1 = new TH1I(
    "Secondary Detected Photons Module 1",
    "Secondary Detected Photons Module 1; Number of Photons; Number of Events",
    100,
    0,
    4000
  );

  TH1I *hist_secondary_detected_photons_2 = new TH1I(
    "Secondary Detected Photons Module 2",
    "Secondary Detected Photons Module 2; Number of Photons; Number of Events",
    100,
    0,
    4000
  );

  //>>>>>>>>>>>>>> Fill Histograms

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Hit Angle
    hist_hit_angle->Fill(hitAngle / M_PI * 180);
    std::cout << hitAngle / M_PI * 180 << '\n';

    // Detected Photons
    hist_tot_detected_photons_1->Fill(nPhotonDetected1);
    hist_tot_detected_photons_2->Fill(nPhotonDetected2);

    hist_tot_detected_photons->Fill(nPhotonDetected1, nPhotonDetected2);

    hist_secondary_detected_photons_1->Fill(nSecPhotonDetected1);
    hist_secondary_detected_photons_2->Fill(nSecPhotonDetected2);

    // Positions of Primary Electron
    hist_pos_PVPosition->Fill(nPostPVxPosition, nPostPVyPosition);

  }

  //>>>>>>>>>>>>>>>>> Set Canvas

  // Hit Angle

  hist_hit_angle->SetFillColor(kYellow);
  hist_hit_angle->Draw();
  canvas->Print("hit_angle.pdf");
  canvas->Clear();

  // -------------------------------------------------------------- //

  hist_pos_PVPosition->Draw("COLZ");
  hist_pos_PVPosition->SetStats(kFALSE);
  canvas->Print("pos_PVPosition.pdf");
  canvas->Clear();

  // -------------------------------------------------------------- //

  hist_tot_detected_photons->Draw("COLZ");
  hist_tot_detected_photons->SetStats(kFALSE);
  canvas->Print("tot_detected_photons.pdf");
  canvas->Clear();

  // Detected Photons

  hist_tot_detected_photons_1->SetFillColor(kYellow);
  hist_tot_detected_photons_1->Draw();
  canvas->Print("TotDetectedPhotons_1.pdf");
  canvas->Clear();

  hist_tot_detected_photons_2->SetFillColor(kYellow);
  hist_tot_detected_photons_2->Draw();
  canvas->Print("TotDetectedPhotons_2.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_detected_photons_1->SetFillColor(kYellow);
  hist_secondary_detected_photons_1->Draw();
  canvas->Print("SecondaryDetectedPhotons_1.pdf");
  canvas->Clear();

  hist_secondary_detected_photons_2->SetFillColor(kYellow);
  hist_secondary_detected_photons_2->Draw();
  canvas->Print("SecondaryDetectedPhotons_2.pdf");
  canvas->Clear();

}
