void PhotonCounter() {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *plume_file = TFile::Open("testbeamsimu.root");
  // TFile *plume_file = TFile::Open("conf_0_e-_5GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_e-_10GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_e-_15GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_e-_20GeV.root");
  //
  // TFile *plume_file = TFile::Open("conf_0_p_1GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_p_5GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_p_10GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_p_15GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_p_20GeV.root");
  //
  // TFile *plume_file = TFile::Open("conf_0_pi+_1GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_pi+_5GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_pi+_10GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_pi+_15GeV.root");
  // TFile *plume_file = TFile::Open("conf_0_pi+_20GeV.root");

  TTree *tree = (TTree *) plume_file->Get("T");

  // Zones
  Int_t Zones = -1;

  // Detected Photons
  Int_t nSecPhotonDetected1 = -1;
  Int_t nSecPhotonDetected2 = -1;

  // Detected Photons
  tree->SetBranchAddress("nSecPhotonDetected1", &nSecPhotonDetected1);
  tree->SetBranchAddress("nSecPhotonDetected2", &nSecPhotonDetected2);

  // Detected Photons

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

    // Detected Photons
    hist_secondary_detected_photons_1->Fill(nSecPhotonDetected1);
    hist_secondary_detected_photons_2->Fill(nSecPhotonDetected2);

  }

  //>>>>>>>>>>>>>>>>> Set Canvas

  canvas->SetLogy(true);

  // Detected Photons

  hist_secondary_detected_photons_1->SetFillColor(kYellow);
  hist_secondary_detected_photons_1->Draw();
  canvas->Print("TestBeam/Simu/SecondaryDetectedPhotons_1.pdf");
  canvas->Clear();

  hist_secondary_detected_photons_2->SetFillColor(kYellow);
  hist_secondary_detected_photons_2->Draw();
  canvas->Print("TestBeam/Simu/SecondaryDetectedPhotons_2.pdf");
  canvas->Clear();

}
