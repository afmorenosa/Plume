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

  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nPhotReflected", &nPhotReflected);

  TH1F *hist_photon_counter = new TH1F(
    "Photon Counter",
    "Phonton Counter; n Photon; Events",
    100,
    200,
    800
  );

  TH1F *hist_photon_reflected = new TH1F(
    "Photon Reflected",
    "Phonton Reflected; Photons reflected; Events",
    100,
    0,
    200
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);
    hist_photon_counter->Fill(nPhotCreated);
    hist_photon_reflected->Fill(nPhotReflected);
  }

  hist_photon_counter->SetFillColor(kYellow);
  hist_photon_counter->Draw();
  canvas->Print("quartz.pdf");
  canvas->Clear();

  hist_photon_reflected->SetFillColor(kYellow);
  hist_photon_reflected->Draw();
  canvas->Print("reflected.pdf");
  canvas->Clear();

}
