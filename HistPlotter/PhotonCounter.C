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
  std::vector<double> *secElecEnergy = {};

  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nPhotReflected", &nPhotReflected);
  tree->SetBranchAddress("secElecEnergy", &secElecEnergy);

  TH1I *hist_photon_counter = new TH1I(
    "Photon Counter",
    "Phonton Counter; n Photon; Events",
    200,
    200,
    800
  );

  TH1I *hist_photon_reflected = new TH1I(
    "Photon Reflected",
    "Phonton Reflected; Photons reflected; Events",
    200,
    0,
    200
  );

  TH1F *hist_electron = new TH1F(
    "Electron Energy",
    "Electron Energy; Energy [GeV]; Events",
    100,
    0,
    50
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);
    hist_photon_counter->Fill(nPhotCreated);
    hist_photon_reflected->Fill(nPhotReflected);

    for (size_t i = 0; i < secElecEnergy->size(); i++) {
      hist_electron->Fill(secElecEnergy->at(i)/100);
    }
  }

  hist_photon_counter->SetFillColor(kYellow);
  hist_photon_counter->Draw();
  canvas->Print("quartz.pdf");
  canvas->Clear();

  hist_photon_reflected->SetFillColor(kYellow);
  hist_photon_reflected->Draw();
  canvas->Print("reflected.pdf");
  canvas->Clear();

  hist_electron->SetFillColor(kYellow);
  hist_electron->Draw();
  canvas->SetLogy();
  canvas->Print("electron.pdf");
  canvas->Clear();

}
