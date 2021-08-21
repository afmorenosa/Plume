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
  Int_t nSecondaryPhotCreated = -1;
  Int_t nPhotReflection = -1;

  Int_t nPhotCreated1 = -1;
  Int_t nSecondaryPhotCreated1 = -1;
  Int_t nPhotCreated2 = -1;
  Int_t nSecondaryPhotCreated2 = -1;

  Int_t Zone = -1;

  Int_t nElecCreated = -1;
  Double_t nPrePVxPosition = -1.0;
  Double_t nPrePVyPosition = -1.0;
  Double_t nPrePVElecEnergy = -1.0;
  Double_t nPostPVxPosition = -1.0;
  Double_t nPostPVyPosition = -1.0;
  Double_t nPostPVElecEnergy = -1.0;
  std::vector<double> *secElecEnergy = {};

  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nSecondaryPhotCreated", &nSecondaryPhotCreated);
  tree->SetBranchAddress("nPhotReflection", &nPhotReflection);

  tree->SetBranchAddress("nPhotCreated1", &nPhotCreated1);
  tree->SetBranchAddress("nSecondaryPhotCreated1", &nSecondaryPhotCreated1);
  tree->SetBranchAddress("nPhotCreated2", &nPhotCreated2);
  tree->SetBranchAddress("nSecondaryPhotCreated2", &nSecondaryPhotCreated2);

  tree->SetBranchAddress("Zone", &Zone);

  tree->SetBranchAddress("nElecCreated", &nElecCreated);
  tree->SetBranchAddress("secElecEnergy", &secElecEnergy);
  tree->SetBranchAddress("nPrePVxPosition", &nPrePVxPosition);
  tree->SetBranchAddress("nPrePVyPosition", &nPrePVyPosition);
  tree->SetBranchAddress("nPrePVElecEnergy", &nPrePVElecEnergy);
  tree->SetBranchAddress("nPostPVxPosition", &nPostPVxPosition);
  tree->SetBranchAddress("nPostPVyPosition", &nPostPVyPosition);
  tree->SetBranchAddress("nPostPVElecEnergy", &nPostPVElecEnergy);

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
    70,
    0,
    70
  );

  TH1F *hist_electron = new TH1F(
    "Electron Energy",
    "Electron Energy; Energy [GeV]; Events",
    100,
    0,
    6
  );

  // ------------------------------------------------------------------- //

  TH1F *hist_nPrePVxPosition = new TH1F(
    "Pre x",
    "Pre x; X [mm]; Events",
    100,
    -5,
    5
  );
  TH1F *hist_nPrePVyPosition = new TH1F(
    "Pre y",
    "Pre y; Y [mm]; Events",
    100,
    -5,
    5
  );
  TH1F *hist_nPrePVElecEnergy = new TH1F(
    "Pre Energy",
    "Pre Energy; Energy [GeV]; Events",
    100,
    0,
    6
  );

  // ------------------------------------------------------------------- //

  TH2D *hist_pre_PVPosition = new TH2D(
    "Pre Position",
    "Pre Position; X [mm]; Y[mm]; Events",
    100,
    -0.08,
    0.08,
    100,
    -0.08,
    0.08
  );

  TH2D *hist_pos_PVPosition = new TH2D(
    "Pos Position",
    "Pos Position; X [mm]; Y[mm]; Events",
    100,
    -5,
    5,
    100,
    -5,
    5
  );

  // Scatter plot

  TH1F *hist_photon_counter_first_primary = new TH1F(
    "Primary Photons Creation",
    "Primary Photons; n Photons; Events",
    180,
    360,
    540
  );

  TH1F *hist_photon_counter_second_primary = new TH1F(
    "Secondary Photons Creation",
    "Secondary Photons; n Photons; Events",
    180,
    360,
    540
  );

  TH2D *hist_photon_counter_2d_primary = new TH2D(
    "Primary Photons Creation per Module",
    "Primary Photons Creation per Module; n Photons tablet 1; n Photons tablet 2; Events",
    180,
    360,
    540,
    180,
    360,
    540
  );

  TH2D *hist_photon_counter_2d_totals = new TH2D(
    "Total Photons Creation",
    "Total Photons Creation; n Photons tablet 1; n Photons tablet 2; Events",
    180,
    0,
    1000,
    180,
    0,
    1000
  );

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    if (Zone == -1) continue;

    hist_photon_counter->Fill(nPhotCreated);
    hist_secondary_photon_counter->Fill(nSecondaryPhotCreated);

    hist_photon_reflected->Fill(nPhotReflection);

    hist_electron_counter->Fill(nElecCreated);

    hist_photon_counter_totals->Fill(nSecondaryPhotCreated + nPhotCreated);

    hist_pre_PVPosition->Fill(nPrePVxPosition, nPrePVyPosition);
    hist_pos_PVPosition->Fill(nPostPVxPosition, nPostPVyPosition);

    hist_nPrePVxPosition->Fill(nPostPVxPosition);
    hist_nPrePVyPosition->Fill(nPostPVyPosition);
    hist_nPrePVElecEnergy->Fill(nPrePVElecEnergy/1000);

    hist_photon_counter_first_primary->Fill(nPhotCreated1);
    hist_photon_counter_second_primary->Fill(nPhotCreated2);

    hist_photon_counter_2d_primary->Fill(nPhotCreated1, nPhotCreated2);
    hist_photon_counter_2d_totals->Fill(
      nPhotCreated1 + nSecondaryPhotCreated1,
      nPhotCreated2 + nSecondaryPhotCreated2
    );

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

  //hist_photon_counter->SetFillColorAlpha(kYellow, 1.0);
  hist_photon_counter_totals->SetFillColorAlpha(kYellow, 1.0);
  hist_secondary_photon_counter_tail->SetFillColorAlpha(kRed, 0.5);
  //hist_photon_counter->Draw();
  hist_photon_counter_totals->Draw();
  hist_secondary_photon_counter_tail->Draw("SAME");
  canvas->Print("total_photons.pdf");
  canvas->Clear();



  hist_photon_reflected->SetFillColor(kYellow);
  hist_photon_reflected->Draw();
  canvas->Print("reflected.pdf");
  canvas->Clear();

  hist_photon_counter_first_primary->SetFillColorAlpha(kYellow, 0.8);
  hist_photon_counter_first_primary->Draw();
  canvas->Print("photon_counter_first_primary.pdf");
  canvas->Clear();

  hist_photon_counter_second_primary->SetFillColorAlpha(kCyan, 0.5);
  hist_photon_counter_second_primary->Draw();
  canvas->Print("photon_counter_second_primary.pdf");
  canvas->Clear();

  hist_photon_counter_first_primary->SetFillColorAlpha(kYellow, 1.0);
  hist_photon_counter_second_primary->SetFillColorAlpha(kCyan, 0.3);
  hist_photon_counter_first_primary->Draw();
  hist_photon_counter_second_primary->Draw("SAME");
  canvas->Print("photon_counter_comparison_primary.pdf");
  canvas->Clear();

  hist_pre_PVPosition->Draw("COLZ");
  canvas->Print("pre_PVPosition.pdf");
  canvas->Clear();

  hist_pos_PVPosition->SetStats(false);
  hist_pos_PVPosition->Draw("COLZ");
  canvas->Print("pos_PVPosition.pdf");
  canvas->Clear();

  hist_photon_counter_2d_primary->Draw("COLZ");
  canvas->Print("photon_counter_2d_primary.pdf");
  canvas->Clear();

  hist_photon_counter_2d_totals->Draw("COLZ");
  canvas->Print("photon_counter_2d_totals.pdf");
  canvas->Clear();


  // -------------------------------------------------------------------- //

  Double_t par[6];

  TF1 *gauss_funcx = new TF1(
    "Gauss_x", "gaus", -0.02, 0.02
  );
  hist_nPrePVxPosition->Fit(gauss_funcx, "R");
  hist_nPrePVxPosition->SetFillColorAlpha(kCyan, 1.0);
  hist_nPrePVxPosition->Draw();
  gauss_funcx->Draw("SAME");
  canvas->Print("fit_nPrePVxPosition.pdf");
  canvas->Clear();

  gauss_funcx->GetParameters(&par[0]);

  TF1 *gauss_funcy = new TF1(
    "Gauss_y", "gaus", -0.02, 0.02
  );
  hist_nPrePVyPosition->Fit(gauss_funcy, "R");
  hist_nPrePVyPosition->SetFillColorAlpha(kCyan, 1.0);
  hist_nPrePVyPosition->Draw();
  gauss_funcy->Draw("SAME");
  canvas->Print("fit_nPrePVyPosition.pdf");
  canvas->Clear();

  gauss_funcy->GetParameters(&par[3]);

  std::cout << "parameters: " << '\n';
  std::cout << " ----------------> " << par[0] << '\n';
  std::cout << " ----------------> " << par[1] << '\n';
  std::cout << " ----------------> " << par[2] << '\n';
  std::cout << " ----------------> " << par[3] << '\n';
  std::cout << " ----------------> " << par[4] << '\n';
  std::cout << " ----------------> " << par[5] << '\n';

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
