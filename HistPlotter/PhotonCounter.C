void PhotonCounter() {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *plume_file = TFile::Open("quartz.root");

  TTree *tree = (TTree *) plume_file->Get("T");

  Int_t nPhotCreated = -1;
  Int_t nPhotReflected = -1;
  Int_t nSecondaryPhotCreated = -1;
  Int_t nElecCreated = -1;
  std::vector<double> *secElecEnergy = {};

  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nPhotReflected", &nPhotReflected);
  tree->SetBranchAddress("nSecondaryPhotCreated", &nSecondaryPhotCreated);
  tree->SetBranchAddress("nElecCreated", &nElecCreated);
  tree->SetBranchAddress("secElecEnergy", &secElecEnergy);

  TH1I *hist_photon_counter = new TH1I(
    "Photon Counter",
    "Photon Counter; n Photon; Events",
    100,
    200,
    800
  );

  TH1I *hist_photon_counter_totals = new TH1I(
    "Photon Counter Totals",
    "Photon Counter Totals; n Photon; Events",
    100,
    200,
    800
  );

  TH1I *hist_photon_reflected = new TH1I(
    "Photon Reflected",
    "Photon Reflected; Photons reflected; Events",
    200,
    0,
    200
  );

  TH1I *hist_secondary_photon_counter = new TH1I(
    "Secondary Photon Counter",
    "Secondary Photon Counter; n Photons; Events",
    100,
    0,
    400
  );

  TH1I *hist_secondary_photon_counter_tail = new TH1I(
    "Secondary Photon Counter tail",
    "Secondary Photon Counter tail; n Photons; Events",
    100,
    200,
    800
  );

  TH1I *hist_electron_counter = new TH1I(
    "Electron Counter",
    "Electron Counter; n Electrons; Events",
    30,
    0,
    30
  );

  TH1F *hist_electron = new TH1F(
    "Electron Energy",
    "Electron Energy; Energy [GeV]; Events",
    100,
    0,
    6
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);
    hist_photon_counter->Fill(nPhotCreated);
    hist_photon_reflected->Fill(nPhotReflected);

    hist_secondary_photon_counter->Fill(nSecondaryPhotCreated);
    hist_electron_counter->Fill(nElecCreated);

    hist_photon_counter_totals->Fill(nSecondaryPhotCreated + nPhotCreated);

    if (nSecondaryPhotCreated > 0) {
      hist_secondary_photon_counter_tail->Fill(
        nSecondaryPhotCreated + nPhotCreated
      );
    }

    for (size_t i = 0; i < secElecEnergy->size(); i++) {
      hist_electron->Fill(secElecEnergy->at(i)/1000);
    }
  }

  hist_photon_counter->SetFillColor(kYellow);
  hist_photon_counter->Draw();
  canvas->Print("quartz.pdf");
  canvas->Clear();

  hist_photon_counter->SetFillColorAlpha(kYellow, 1.0);
  hist_photon_counter_totals->SetFillColorAlpha(kRed, 0.5);
  hist_secondary_photon_counter_tail->SetFillColorAlpha(kCyan, 0.25);
  hist_photon_counter->Draw();
  hist_photon_counter_totals->Draw("SAME");
  hist_secondary_photon_counter_tail->Draw("SAME");
  canvas->Print("total_photons.pdf");
  canvas->Clear();

  hist_photon_reflected->SetFillColor(kYellow);
  hist_photon_reflected->Draw();
  canvas->Print("reflected.pdf");
  canvas->Clear();

  // Log y plots
  canvas->SetLogy();

  hist_electron->SetFillColor(kYellow);
  hist_electron->Draw();
  canvas->Print("electron.pdf");
  canvas->Clear();

  hist_secondary_photon_counter->SetFillColor(kYellow);
  hist_secondary_photon_counter->Draw();
  canvas->Print("secondary_photons.pdf");
  canvas->Clear();

  hist_electron_counter->SetFillColor(kYellow);
  hist_electron_counter->Draw();
  canvas->Print("electrons.pdf");
  canvas->Clear();

}
