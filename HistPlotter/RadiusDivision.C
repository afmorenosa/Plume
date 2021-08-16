void RadiusDivision () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  TFile *root_file = TFile::Open("quartz.root");

  TTree *tree = (TTree *) root_file->Get("T");

  //------------------------ Branches variables ------------------------//

  Int_t nPhotCreated = -1;
  Int_t nSecondaryPhotCreated = -1;
  Int_t nPhotReflected = -1;
  Int_t Zone = -1;

  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nSecondaryPhotCreated", &nSecondaryPhotCreated);
  tree->SetBranchAddress("nPhotReflected", &nPhotReflected);
  tree->SetBranchAddress("Zone", &Zone);

  //--------------------------------------------------------------------//

  //---------------------------- Histograms ----------------------------//

  //>>>>>>>>>>>>>>>>>>> Totals

  TH1I *hist_total_photon_counter = new TH1I(
    "Total Photon Creaton",
    "Total Photon Creaton; n Photons; Events",
    100,
    0,
    1000
  );

  TH1I *hist_photon_counter = new TH1I(
    "Primary Photon Creation",
    "Primary Photon Creation; n Photons; Events",
    100,
    0,
    600
  );

  TH1I *hist_secondary_photon_counter = new TH1I(
    "Secondary Photon Creation",
    "Secondary Photon Creation; n Photons; Events",
    100,
    0,
    1200
  );

  TH1I *hist_photon_reflected_counter = new TH1I(
    "Reflected Photon Creation",
    "Reflected Photon Creation; n Photons; Events",
    100,
    0,
    2000
  );

  //>>>>>>>>>>>>>>>>>>> Zone_0

  TH1I *hist_total_photon_counter_0 = new TH1I(
    "Total Photon Creaton (Zone_0)",
    "Total Photon Creaton (Zone_0); n Photons; Events",
    100,
    300,
    1200
  );

  TH1I *hist_photon_counter_0 = new TH1I(
    "Primary Photon Creation (Zone_0)",
    "Primary Photon Creation (Zone_0); n Photons; Events",
    100,
    300,
    600
  );

  TH1I *hist_secondary_photon_counter_0 = new TH1I(
    "Secondary Photon Creation (Zone_0)",
    "Secondary Photon Creation (Zone_0); n Photons; Events",
    100,
    0,
    1100
  );

  TH1I *hist_photon_reflected_counter_0 = new TH1I(
    "Reflected Photon Creation (Zone_0)",
    "Reflected Photon Creation (Zone_0); n Photons; Events",
    100,
    0,
    1500
  );

  //>>>>>>>>>>>>>>>>>>> Zone_1

  TH1I *hist_total_photon_counter_1 = new TH1I(
    "Total Photon Creaton (Zone_1)",
    "Total Photon Creaton (Zone_1); n Photons; Events",
    100,
    300,
    1100
  );

  TH1I *hist_photon_counter_1 = new TH1I(
    "Primary Photon Creation (Zone_1)",
    "Primary Photon Creation (Zone_1); n Photons; Events",
    100,
    300,
    600
  );

  TH1I *hist_secondary_photon_counter_1 = new TH1I(
    "Secondary Photon Creation (Zone_1)",
    "Secondary Photon Creation (Zone_1); n Photons; Events",
    100,
    0,
    1200
  );

  TH1I *hist_photon_reflected_counter_1 = new TH1I(
    "Reflected Photon Creation (Zone_1)",
    "Reflected Photon Creation (Zone_1); n Photons; Events",
    100,
    0,
    2000
  );

  //>>>>>>>>>>>>>>>>>>> Zone_2

  TH1I *hist_total_photon_counter_2 = new TH1I(
    "Total Photon Creaton (Zone_2)",
    "Total Photon Creaton (Zone_2); n Photons; Events",
    100,
    0,
    1000
  );

  TH1I *hist_photon_counter_2 = new TH1I(
    "Primary Photon Creation (Zone_2)",
    "Primary Photon Creation (Zone_2); n Photons; Events",
    100,
    0,
    600
  );

  TH1I *hist_secondary_photon_counter_2 = new TH1I(
    "Secondary Photon Creation (Zone_2)",
    "Secondary Photon Creation (Zone_2); n Photons; Events",
    100,
    0,
    1200
  );

  TH1I *hist_photon_reflected_counter_2 = new TH1I(
    "Reflected Photon Creation (Zone_2)",
    "Reflected Photon Creation (Zone_2); n Photons; Events",
    100,
    0,
    2000
  );

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    // Fill histograms.

    hist_total_photon_counter->Fill(nPhotCreated + nSecondaryPhotCreated);
    hist_photon_counter->Fill(nPhotCreated);
    hist_secondary_photon_counter->Fill(nSecondaryPhotCreated);
    hist_photon_reflected_counter->Fill(nPhotReflected);

    if (Zone == 0) {

      hist_total_photon_counter_0->Fill(nPhotCreated + nSecondaryPhotCreated);
      hist_photon_counter_0->Fill(nPhotCreated);
      hist_secondary_photon_counter_0->Fill(nSecondaryPhotCreated);
      hist_photon_reflected_counter_0->Fill(nPhotReflected);

    } else if (Zone == 1) {

      hist_total_photon_counter_1->Fill(nPhotCreated + nSecondaryPhotCreated);
      hist_photon_counter_1->Fill(nPhotCreated);
      hist_secondary_photon_counter_1->Fill(nSecondaryPhotCreated);
      hist_photon_reflected_counter_1->Fill(nPhotReflected);

    } else if (Zone == 2) {

      hist_total_photon_counter_2->Fill(nPhotCreated + nSecondaryPhotCreated);
      hist_photon_counter_2->Fill(nPhotCreated);
      hist_secondary_photon_counter_2->Fill(nSecondaryPhotCreated);
      hist_photon_reflected_counter_2->Fill(nPhotReflected);

    }

  }


  //-------------------------- Darw Histograms --------------------------//

  //>>>>>>>>>>>>>>>>>>> Totals

  hist_total_photon_counter->SetFillColor(kYellow);
  hist_total_photon_counter->Draw();
  canvas->Print("total_photon_counter.pdf");
  canvas->Clear();

  hist_photon_counter->SetFillColor(kYellow);
  hist_photon_counter->Draw();
  canvas->Print("photon_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_photon_counter->SetFillColor(kYellow);
  hist_secondary_photon_counter->Draw();
  canvas->Print("secondary_photon_counter.pdf");
  canvas->Clear();

  hist_photon_reflected_counter->SetFillColor(kYellow);
  hist_photon_reflected_counter->Draw();
  canvas->Print("photon_reflected_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  //>>>>>>>>>>>>>>>>>>> Zone_0

  hist_total_photon_counter_0->SetFillColor(kYellow);
  hist_total_photon_counter_0->Draw();
  canvas->Print("total_photon_counter_0.pdf");
  canvas->Clear();

  hist_photon_counter_0->SetFillColor(kYellow);
  hist_photon_counter_0->Draw();
  canvas->Print("photon_counter_0.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_photon_counter_0->SetFillColor(kYellow);
  hist_secondary_photon_counter_0->Draw();
  canvas->Print("secondary_photon_counter_0.pdf");
  canvas->Clear();

  hist_photon_reflected_counter_0->SetFillColor(kYellow);
  hist_photon_reflected_counter_0->Draw();
  canvas->Print("photon_reflected_counter_0.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  //>>>>>>>>>>>>>>>>>>> Zone_1

  hist_total_photon_counter_1->SetFillColor(kYellow);
  hist_total_photon_counter_1->Draw();
  canvas->Print("total_photon_counter_1.pdf");
  canvas->Clear();

  hist_photon_counter_1->SetFillColor(kYellow);
  hist_photon_counter_1->Draw();
  canvas->Print("photon_counter_1.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_photon_counter_1->SetFillColor(kYellow);
  hist_secondary_photon_counter_1->Draw();
  canvas->Print("secondary_photon_counter_1.pdf");
  canvas->Clear();

  hist_photon_reflected_counter_1->SetFillColor(kYellow);
  hist_photon_reflected_counter_1->Draw();
  canvas->Print("photon_reflected_counter_1.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  //>>>>>>>>>>>>>>>>>>> Zone_2

  hist_total_photon_counter_2->SetFillColor(kYellow);
  hist_total_photon_counter_2->Draw();
  canvas->Print("total_photon_counter_2.pdf");
  canvas->Clear();

  hist_photon_counter_2->SetFillColor(kYellow);
  hist_photon_counter_2->Draw();
  canvas->Print("photon_counter_2.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_photon_counter_2->SetFillColor(kYellow);
  hist_secondary_photon_counter_2->Draw();
  canvas->Print("secondary_photon_counter_2.pdf");
  canvas->Clear();

  hist_photon_reflected_counter_2->SetFillColor(kYellow);
  hist_photon_reflected_counter_2->Draw();
  canvas->Print("photon_reflected_counter_2.pdf");
  canvas->Clear();

  canvas->SetLogy(false);


  //---------------------------------------------------------------------//

}
