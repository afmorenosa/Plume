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
  Int_t nPhotReflection = -1;

  Int_t Zone = -1;

  Int_t nPhotonStraight = -1;
  Int_t nPhotReflected = -1;

  Int_t nElecCreated = -1;

  tree->SetBranchAddress("nPhotCreated", &nPhotCreated);
  tree->SetBranchAddress("nSecondaryPhotCreated", &nSecondaryPhotCreated);
  tree->SetBranchAddress("nPhotReflection", &nPhotReflection);

  tree->SetBranchAddress("nElecCreated", &nElecCreated);

  tree->SetBranchAddress("Zone", &Zone);

  tree->SetBranchAddress("nPhotonStraight", &nPhotonStraight);
  tree->SetBranchAddress("nPhotReflected", &nPhotReflected);

  std::vector<Int_t> *nReflectionPerPhoton = {};

  tree->SetBranchAddress("nReflectionPerPhoton", &nReflectionPerPhoton);

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

  TH1I *hist_primary_photon_counter = new TH1I(
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

  TH1I *hist_photon_reflection_counter = new TH1I(
    "Reflection Photon Creation",
    "Reflection Photon Creation; n Reflections; Events",
    100,
    0,
    3000
  );

  TH1I *hist_secondary_electron_counter = new TH1I(
    "Secondary Electron Creation",
    "Secondary Electron Creation; n Electrons; Events",
    50,
    0,
    50
  );

  TH1I *hist_photon_straight_counter = new TH1I(
    "Straight Photon",
    "Straight Photon; n Photons; Events",
    100,
    0,
    800
  );

  TH1I *hist_photon_reflected_counter = new TH1I(
    "Reflected Photon",
    "Reflected Photon; n Photons; Events",
    100,
    0,
    400
  );

  TH1I *hist_reflections_per_photon_counter = new TH1I(
    "Reflection Per Photon",
    "Reflection Per Photon; n Reflections; Events",
    100,
    0,
    10000
  );

  //>>>>>>>>>>>>>>>>>>> Zones

  const int n_Zones = 10;

  std::map<int, TH1I *> hist_total_photon_counter_zones;
  std::map<int, TH1I *> hist_primary_photon_counter_zones;
  std::map<int, TH1I *> hist_secondary_photon_counter_zones;
  std::map<int, TH1I *> hist_photon_reflection_counter_zones;
  std::map<int, TH1I *> hist_secondary_electron_counter_zones;
  std::map<int, TH1I *> hist_photon_straight_counter_zones;
  std::map<int, TH1I *> hist_photon_reflected_counter_zones;
  std::map<int, TH1I *> hist_reflections_per_photon_counter_zones;

  for (size_t zone_i = 0; zone_i < n_Zones; zone_i++) {

    hist_total_photon_counter_zones[zone_i] = new TH1I(
      TString("Total Photon Creaton, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Total Photon Creaton; n Photons; Events",
      100,
      0,
      1000
    );

    hist_primary_photon_counter_zones[zone_i] = new TH1I(
      TString("Primary Photon Creation, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Primary Photon Creation; n Photons; Events",
      100,
      0,
      600
    );

    hist_secondary_photon_counter_zones[zone_i] = new TH1I(
      TString("Secondary Photon Creation, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Secondary Photon Creation; n Photons; Events",
      100,
      0,
      1200
    );

    hist_photon_reflection_counter_zones[zone_i] = new TH1I(
      TString("Reflection Photon Creation, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Reflection Photon Creation; n Reflections; Events",
      100,
      0,
      2000
    );

    hist_secondary_electron_counter_zones[zone_i] = new TH1I(
      TString("Secondary Electron Creation, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Secondary Electron Creation; n Electrons; Events",
      50,
      0,
      50
    );

    hist_photon_straight_counter_zones[zone_i] = new TH1I(
      TString("Straight Photon, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Straight Photon; n Photons; Events",
      100,
      0,
      800
    );

    hist_photon_reflected_counter_zones[zone_i] = new TH1I(
      TString("Reflected Photon, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Reflected Photon; n Photons; Events",
      100,
      0,
      400
    );

    hist_reflections_per_photon_counter_zones[zone_i] = new TH1I(
      TString("Reflection Per Photon, Zone: ") +
      TString(std::to_string(zone_i).c_str()),
      "Reflection Per Photon; n Reflections; Events",
      100,
      0,
      10000
    );


  }

  //--------------------------------------------------------------------//

  int nentries, nbytes;
  nentries = (Int_t)tree->GetEntries();

  for (int i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    if (Zone == -1) continue;

    // Fill histograms.

    hist_total_photon_counter->Fill(nPhotCreated + nSecondaryPhotCreated);
    hist_primary_photon_counter->Fill(nPhotCreated);
    hist_secondary_photon_counter->Fill(nSecondaryPhotCreated);

    hist_photon_reflection_counter->Fill(nPhotReflection);

    hist_photon_straight_counter->Fill(nPhotonStraight);
    hist_photon_reflected_counter->Fill(nPhotReflected);

    hist_secondary_electron_counter->Fill(nElecCreated);

    for (size_t i = 0; i < nReflectionPerPhoton->size(); i++) {
      hist_reflections_per_photon_counter->Fill(nReflectionPerPhoton->at(i));
    }

    // Fill zone histograms.

    hist_total_photon_counter_zones[Zone]->Fill(
      nPhotCreated + nSecondaryPhotCreated
    );
    hist_primary_photon_counter_zones[Zone]->Fill(
      nPhotCreated
    );
    hist_secondary_photon_counter_zones[Zone]->Fill(
      nSecondaryPhotCreated
    );

    hist_photon_reflection_counter_zones[Zone]->Fill(
      nPhotReflection
    );

    hist_photon_straight_counter_zones[Zone]->Fill(
      nPhotonStraight
    );
    hist_photon_reflected_counter_zones[Zone]->Fill(
      nPhotReflected
    );

    hist_secondary_electron_counter_zones[Zone]->Fill(
      nElecCreated
    );

    for (size_t i = 0; i < nReflectionPerPhoton->size(); i++) {
      hist_reflections_per_photon_counter_zones[Zone]->Fill(
        nReflectionPerPhoton->at(i)
      );
    }


  }


  //-------------------------- Darw Histograms --------------------------//

  //>>>>>>>>>>>>>>>>>>> Totals

  hist_total_photon_counter->SetFillColor(kYellow);
  hist_total_photon_counter->Draw();
  canvas->Print("Totals/total_photon_counter.pdf");
  canvas->Clear();

  hist_primary_photon_counter->SetFillColor(kYellow);
  hist_primary_photon_counter->Draw();
  canvas->Print("Totals/photon_counter.pdf");
  canvas->Clear();

  hist_photon_straight_counter->SetFillColor(kYellow);
  hist_photon_straight_counter->Draw();
  canvas->Print("Totals/photon_straight_counter.pdf");
  canvas->Clear();

  hist_photon_reflected_counter->SetFillColor(kYellow);
  hist_photon_reflected_counter->Draw();
  canvas->Print("Totals/photon_reflected_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(true);

  hist_secondary_electron_counter->SetFillColor(kYellow);
  hist_secondary_electron_counter->Draw();
  canvas->Print("Totals/electron_counter.pdf");
  canvas->Clear();

  hist_reflections_per_photon_counter->SetFillColor(kYellow);
  hist_reflections_per_photon_counter->Draw();
  canvas->Print("Totals/reflections_per_photon_counter.pdf");
  canvas->Clear();

  hist_secondary_photon_counter->SetFillColor(kYellow);
  hist_secondary_photon_counter->Draw();
  canvas->Print("Totals/secondary_photon_counter.pdf");
  canvas->Clear();

  hist_photon_reflection_counter->SetFillColor(kYellow);
  hist_photon_reflection_counter->Draw();
  canvas->Print("Totals/photon_reflection_counter.pdf");
  canvas->Clear();

  canvas->SetLogy(false);

  //>>>>>>>>>>>>>>>>>>> Zones

  double total_photon_integral[n_Zones];
  double total_photon_mean[n_Zones];
  double total_photon_stddev[n_Zones];

  double primary_photon_integral[n_Zones];
  double primary_photon_mean[n_Zones];
  double primary_photon_stddev[n_Zones];

  double secondary_photon_integral[n_Zones];
  double secondary_photon_mean[n_Zones];
  double secondary_photon_stddev[n_Zones];

  double photon_reflection_integral[n_Zones];
  double photon_reflection_mean[n_Zones];
  double photon_reflection_stddev[n_Zones];

  double secondary_electron_integral[n_Zones];
  double secondary_electron_mean[n_Zones];
  double secondary_electron_stddev[n_Zones];

  double photon_straight_integral[n_Zones];
  double photon_straight_mean[n_Zones];
  double photon_straight_stddev[n_Zones];

  double photon_reflected_integral[n_Zones];
  double photon_reflected_mean[n_Zones];
  double photon_reflected_stddev[n_Zones];

  double reflections_per_photon_integral[n_Zones];
  double reflections_per_photon_mean[n_Zones];
  double reflections_per_photon_stddev[n_Zones];

  double zones_pos[n_Zones] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (size_t zone_i = 0; zone_i < n_Zones; zone_i++) {

    hist_total_photon_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_total_photon_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/total_photon_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    hist_primary_photon_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_primary_photon_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/photon_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    hist_photon_straight_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_photon_straight_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/photon_straight_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    hist_photon_reflected_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_photon_reflected_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/photon_reflected_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    canvas->SetLogy(true);

    hist_secondary_electron_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_secondary_electron_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/electron_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    hist_reflections_per_photon_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_reflections_per_photon_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/reflections_per_photon_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    hist_secondary_photon_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_secondary_photon_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/secondary_photon_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    hist_photon_reflection_counter_zones[zone_i]->SetFillColor(kYellow);
    hist_photon_reflection_counter_zones[zone_i]->Draw();
    canvas->Print(
      TString("Zones/photon_reflection_counter_zone_") +
      TString(std::to_string(zone_i).c_str()) +
      TString(".pdf")
    );
    canvas->Clear();

    canvas->SetLogy(false);

    total_photon_integral[zone_i] =
    hist_total_photon_counter_zones[zone_i]->Integral();
    total_photon_mean[zone_i] =
    hist_total_photon_counter_zones[zone_i]->GetMean();
    total_photon_stddev[zone_i] =
    hist_total_photon_counter_zones[zone_i]->GetStdDev();

    primary_photon_integral[zone_i] =
    hist_primary_photon_counter_zones[zone_i]->Integral();
    primary_photon_mean[zone_i] =
    hist_primary_photon_counter_zones[zone_i]->GetMean();
    primary_photon_stddev[zone_i] =
    hist_primary_photon_counter_zones[zone_i]->GetStdDev();

    secondary_photon_integral[zone_i] =
    hist_secondary_photon_counter_zones[zone_i]->Integral();
    secondary_photon_mean[zone_i] =
    hist_secondary_photon_counter_zones[zone_i]->GetMean();
    secondary_photon_stddev[zone_i] =
    hist_secondary_photon_counter_zones[zone_i]->GetStdDev();

    photon_reflection_integral[zone_i] =
    hist_photon_reflection_counter_zones[zone_i]->Integral();
    photon_reflection_mean[zone_i] =
    hist_photon_reflection_counter_zones[zone_i]->GetMean();
    photon_reflection_stddev[zone_i] =
    hist_photon_reflection_counter_zones[zone_i]->GetStdDev();

    secondary_electron_integral[zone_i] =
    hist_secondary_electron_counter_zones[zone_i]->Integral();
    secondary_electron_mean[zone_i] =
    hist_secondary_electron_counter_zones[zone_i]->GetMean();
    secondary_electron_stddev[zone_i] =
    hist_secondary_electron_counter_zones[zone_i]->GetStdDev();

    photon_straight_integral[zone_i] =
    hist_photon_straight_counter_zones[zone_i]->Integral();
    photon_straight_mean[zone_i] =
    hist_photon_straight_counter_zones[zone_i]->GetMean();
    photon_straight_stddev[zone_i] =
    hist_photon_straight_counter_zones[zone_i]->GetStdDev();

    photon_reflected_integral[zone_i] =
    hist_photon_reflected_counter_zones[zone_i]->Integral();
    photon_reflected_mean[zone_i] =
    hist_photon_reflected_counter_zones[zone_i]->GetMean();
    photon_reflected_stddev[zone_i] =
    hist_photon_reflected_counter_zones[zone_i]->GetStdDev();

    reflections_per_photon_integral[zone_i] =
    hist_reflections_per_photon_counter_zones[zone_i]->Integral();
    reflections_per_photon_mean[zone_i] =
    hist_reflections_per_photon_counter_zones[zone_i]->GetMean();
    reflections_per_photon_stddev[zone_i] =
    hist_reflections_per_photon_counter_zones[zone_i]->GetStdDev();


  }

  TGraph *graph_total_photon_integral =
  new TGraph(n_Zones, zones_pos, total_photon_integral);
  graph_total_photon_integral->SetTitle("total_photon_integral");
  graph_total_photon_integral->SetMarkerColor(kRed);
  graph_total_photon_integral->SetMarkerSize(10);
  graph_total_photon_integral->SetMarkerSize(1);
  graph_total_photon_integral->SetMarkerStyle(21);
  graph_total_photon_integral->Draw("AP");
  canvas->Print("Graph/graph_total_photon_integral.pdf");
  canvas->Clear();

  TGraph *graph_total_photon_mean =
  new TGraph(n_Zones, zones_pos, total_photon_mean);
  graph_total_photon_mean->SetTitle("total_photon_mean");
  graph_total_photon_mean->SetMarkerColor(kRed);
  graph_total_photon_mean->SetMarkerSize(10);
  graph_total_photon_mean->SetMarkerSize(1);
  graph_total_photon_mean->SetMarkerStyle(21);
  graph_total_photon_mean->Draw("AP");
  canvas->Print("Graph/graph_total_photon_mean.pdf");
  canvas->Clear();

  TGraph *graph_total_photon_stddev =
  new TGraph(n_Zones, zones_pos, total_photon_stddev);
  graph_total_photon_stddev->SetTitle("total_photon_stddev");
  graph_total_photon_stddev->SetMarkerColor(kRed);
  graph_total_photon_stddev->SetMarkerSize(10);
  graph_total_photon_stddev->SetMarkerSize(1);
  graph_total_photon_stddev->SetMarkerStyle(21);
  graph_total_photon_stddev->Draw("AP");
  canvas->Print("Graph/graph_total_photon_stddev.pdf");
  canvas->Clear();

  TGraph *graph_primary_photon_integral =
  new TGraph(n_Zones, zones_pos, primary_photon_integral);
  graph_primary_photon_integral->SetTitle("primary_photon_integral");
  graph_primary_photon_integral->SetMarkerColor(kRed);
  graph_primary_photon_integral->SetMarkerSize(10);
  graph_primary_photon_integral->SetMarkerSize(1);
  graph_primary_photon_integral->SetMarkerStyle(21);
  graph_primary_photon_integral->Draw("AP");
  canvas->Print("Graph/graph_primary_photon_integral.pdf");
  canvas->Clear();

  TGraph *graph_primary_photon_mean =
  new TGraph(n_Zones, zones_pos, primary_photon_mean);
  graph_primary_photon_mean->SetTitle("primary_photon_mean");
  graph_primary_photon_mean->SetMarkerColor(kRed);
  graph_primary_photon_mean->SetMarkerSize(10);
  graph_primary_photon_mean->SetMarkerSize(1);
  graph_primary_photon_mean->SetMarkerStyle(21);
  graph_primary_photon_mean->Draw("AP");
  canvas->Print("Graph/graph_primary_photon_mean.pdf");
  canvas->Clear();

  TGraph *graph_primary_photon_stddev =
  new TGraph(n_Zones, zones_pos, primary_photon_stddev);
  graph_primary_photon_stddev->SetTitle("primary_photon_stddev");
  graph_primary_photon_stddev->SetMarkerColor(kRed);
  graph_primary_photon_stddev->SetMarkerSize(10);
  graph_primary_photon_stddev->SetMarkerSize(1);
  graph_primary_photon_stddev->SetMarkerStyle(21);
  graph_primary_photon_stddev->Draw("AP");
  canvas->Print("Graph/graph_primary_photon_stddev.pdf");
  canvas->Clear();

  TGraph *graph_secondary_photon_integral =
  new TGraph(n_Zones, zones_pos, secondary_photon_integral);
  graph_secondary_photon_integral->SetTitle("secondary_photon_integral");
  graph_secondary_photon_integral->SetMarkerColor(kRed);
  graph_secondary_photon_integral->SetMarkerSize(10);
  graph_secondary_photon_integral->SetMarkerSize(1);
  graph_secondary_photon_integral->SetMarkerStyle(21);
  graph_secondary_photon_integral->Draw("AP");
  canvas->Print("Graph/graph_secondary_photon_integral.pdf");
  canvas->Clear();

  TGraph *graph_secondary_photon_mean =
  new TGraph(n_Zones, zones_pos, secondary_photon_mean);
  graph_secondary_photon_mean->SetTitle("secondary_photon_mean");
  graph_secondary_photon_mean->SetMarkerColor(kRed);
  graph_secondary_photon_mean->SetMarkerSize(10);
  graph_secondary_photon_mean->SetMarkerSize(1);
  graph_secondary_photon_mean->SetMarkerStyle(21);
  graph_secondary_photon_mean->Draw("AP");
  canvas->Print("Graph/graph_secondary_photon_mean.pdf");
  canvas->Clear();

  TGraph *graph_secondary_photon_stddev =
  new TGraph(n_Zones, zones_pos, secondary_photon_stddev);
  graph_secondary_photon_stddev->SetTitle("secondary_photon_stddev");
  graph_secondary_photon_stddev->SetMarkerColor(kRed);
  graph_secondary_photon_stddev->SetMarkerSize(10);
  graph_secondary_photon_stddev->SetMarkerSize(1);
  graph_secondary_photon_stddev->SetMarkerStyle(21);
  graph_secondary_photon_stddev->Draw("AP");
  canvas->Print("Graph/graph_secondary_photon_stddev.pdf");
  canvas->Clear();

  TGraph *graph_photon_reflection_integral =
  new TGraph(n_Zones, zones_pos, photon_reflection_integral);
  graph_photon_reflection_integral->SetTitle("photon_reflection_integral");
  graph_photon_reflection_integral->SetMarkerColor(kRed);
  graph_photon_reflection_integral->SetMarkerSize(10);
  graph_photon_reflection_integral->SetMarkerSize(1);
  graph_photon_reflection_integral->SetMarkerStyle(21);
  graph_photon_reflection_integral->Draw("AP");
  canvas->Print("Graph/graph_photon_reflection_integral.pdf");
  canvas->Clear();

  TGraph *graph_photon_reflection_mean =
  new TGraph(n_Zones, zones_pos, photon_reflection_mean);
  graph_photon_reflection_mean->SetTitle("photon_reflection_mean");
  graph_photon_reflection_mean->SetMarkerColor(kRed);
  graph_photon_reflection_mean->SetMarkerSize(10);
  graph_photon_reflection_mean->SetMarkerSize(1);
  graph_photon_reflection_mean->SetMarkerStyle(21);
  graph_photon_reflection_mean->Draw("AP");
  canvas->Print("Graph/graph_photon_reflection_mean.pdf");
  canvas->Clear();

  TGraph *graph_photon_reflection_stddev =
  new TGraph(n_Zones, zones_pos, photon_reflection_stddev);
  graph_photon_reflection_stddev->SetTitle("photon_reflection_stddev");
  graph_photon_reflection_stddev->SetMarkerColor(kRed);
  graph_photon_reflection_stddev->SetMarkerSize(10);
  graph_photon_reflection_stddev->SetMarkerSize(1);
  graph_photon_reflection_stddev->SetMarkerStyle(21);
  graph_photon_reflection_stddev->Draw("AP");
  canvas->Print("Graph/graph_photon_reflection_stddev.pdf");
  canvas->Clear();

  TGraph *graph_secondary_electron_integral =
  new TGraph(n_Zones, zones_pos, secondary_electron_integral);
  graph_secondary_electron_integral->SetTitle("secondary_electron_integral");
  graph_secondary_electron_integral->SetMarkerColor(kRed);
  graph_secondary_electron_integral->SetMarkerSize(10);
  graph_secondary_electron_integral->SetMarkerSize(1);
  graph_secondary_electron_integral->SetMarkerStyle(21);
  graph_secondary_electron_integral->Draw("AP");
  canvas->Print("Graph/graph_secondary_electron_integral.pdf");
  canvas->Clear();

  TGraph *graph_secondary_electron_mean =
  new TGraph(n_Zones, zones_pos, secondary_electron_mean);
  graph_secondary_electron_mean->SetTitle("secondary_electron_mean");
  graph_secondary_electron_mean->SetMarkerColor(kRed);
  graph_secondary_electron_mean->SetMarkerSize(10);
  graph_secondary_electron_mean->SetMarkerSize(1);
  graph_secondary_electron_mean->SetMarkerStyle(21);
  graph_secondary_electron_mean->Draw("AP");
  canvas->Print("Graph/graph_secondary_electron_mean.pdf");
  canvas->Clear();

  TGraph *graph_secondary_electron_stddev =
  new TGraph(n_Zones, zones_pos, secondary_electron_stddev);
  graph_secondary_electron_stddev->SetTitle("secondary_electron_stddev");
  graph_secondary_electron_stddev->SetMarkerColor(kRed);
  graph_secondary_electron_stddev->SetMarkerSize(10);
  graph_secondary_electron_stddev->SetMarkerSize(1);
  graph_secondary_electron_stddev->SetMarkerStyle(21);
  graph_secondary_electron_stddev->Draw("AP");
  canvas->Print("Graph/graph_secondary_electron_stddev.pdf");
  canvas->Clear();

  TGraph *graph_photon_straight_integral =
  new TGraph(n_Zones, zones_pos, photon_straight_integral);
  graph_photon_straight_integral->SetTitle("photon_straight_integral");
  graph_photon_straight_integral->SetMarkerColor(kRed);
  graph_photon_straight_integral->SetMarkerSize(10);
  graph_photon_straight_integral->SetMarkerSize(1);
  graph_photon_straight_integral->SetMarkerStyle(21);
  graph_photon_straight_integral->Draw("AP");
  canvas->Print("Graph/graph_photon_straight_integral.pdf");
  canvas->Clear();

  TGraph *graph_photon_straight_mean =
  new TGraph(n_Zones, zones_pos, photon_straight_mean);
  graph_photon_straight_mean->SetTitle("photon_straight_mean");
  graph_photon_straight_mean->SetMarkerColor(kRed);
  graph_photon_straight_mean->SetMarkerSize(10);
  graph_photon_straight_mean->SetMarkerSize(1);
  graph_photon_straight_mean->SetMarkerStyle(21);
  graph_photon_straight_mean->Draw("AP");
  canvas->Print("Graph/graph_photon_straight_mean.pdf");
  canvas->Clear();

  TGraph *graph_photon_straight_stddev =
  new TGraph(n_Zones, zones_pos, photon_straight_stddev);
  graph_photon_straight_stddev->SetTitle("photon_straight_stddev");
  graph_photon_straight_stddev->SetMarkerColor(kRed);
  graph_photon_straight_stddev->SetMarkerSize(10);
  graph_photon_straight_stddev->SetMarkerSize(1);
  graph_photon_straight_stddev->SetMarkerStyle(21);
  graph_photon_straight_stddev->Draw("AP");
  canvas->Print("Graph/graph_photon_straight_stddev.pdf");
  canvas->Clear();

  TGraph *graph_photon_reflected_integral =
  new TGraph(n_Zones, zones_pos, photon_reflected_integral);
  graph_photon_reflected_integral->SetTitle("photon_reflected_integral");
  graph_photon_reflected_integral->SetMarkerColor(kRed);
  graph_photon_reflected_integral->SetMarkerSize(10);
  graph_photon_reflected_integral->SetMarkerSize(1);
  graph_photon_reflected_integral->SetMarkerStyle(21);
  graph_photon_reflected_integral->Draw("AP");
  canvas->Print("Graph/graph_photon_reflected_integral.pdf");
  canvas->Clear();

  TGraph *graph_photon_reflected_mean =
  new TGraph(n_Zones, zones_pos, photon_reflected_mean);
  graph_photon_reflected_mean->SetTitle("photon_reflected_mean");
  graph_photon_reflected_mean->SetMarkerColor(kRed);
  graph_photon_reflected_mean->SetMarkerSize(10);
  graph_photon_reflected_mean->SetMarkerSize(1);
  graph_photon_reflected_mean->SetMarkerStyle(21);
  graph_photon_reflected_mean->Draw("AP");
  canvas->Print("Graph/graph_photon_reflected_mean.pdf");
  canvas->Clear();

  TGraph *graph_photon_reflected_stddev =
  new TGraph(n_Zones, zones_pos, photon_reflected_stddev);
  graph_photon_reflected_stddev->SetTitle("photon_reflected_stddev");
  graph_photon_reflected_stddev->SetMarkerColor(kRed);
  graph_photon_reflected_stddev->SetMarkerSize(10);
  graph_photon_reflected_stddev->SetMarkerSize(1);
  graph_photon_reflected_stddev->SetMarkerStyle(21);
  graph_photon_reflected_stddev->Draw("AP");
  canvas->Print("Graph/graph_photon_reflected_stddev.pdf");
  canvas->Clear();

  TGraph *graph_reflections_per_photon_integral =
  new TGraph(n_Zones, zones_pos, reflections_per_photon_integral);
  graph_reflections_per_photon_integral->SetTitle("reflections_per_photon_integral");
  graph_reflections_per_photon_integral->SetMarkerColor(kRed);
  graph_reflections_per_photon_integral->SetMarkerSize(10);
  graph_reflections_per_photon_integral->SetMarkerSize(1);
  graph_reflections_per_photon_integral->SetMarkerStyle(21);
  graph_reflections_per_photon_integral->Draw("AP");
  canvas->Print("Graph/graph_reflections_per_photon_integral.pdf");
  canvas->Clear();

  TGraph *graph_reflections_per_photon_mean =
  new TGraph(n_Zones, zones_pos, reflections_per_photon_mean);
  graph_reflections_per_photon_mean->SetTitle("reflections_per_photon_mean");
  graph_reflections_per_photon_mean->SetMarkerColor(kRed);
  graph_reflections_per_photon_mean->SetMarkerSize(10);
  graph_reflections_per_photon_mean->SetMarkerSize(1);
  graph_reflections_per_photon_mean->SetMarkerStyle(21);
  graph_reflections_per_photon_mean->Draw("AP");
  canvas->Print("Graph/graph_reflections_per_photon_mean.pdf");
  canvas->Clear();

  TGraph *graph_reflections_per_photon_stddev =
  new TGraph(n_Zones, zones_pos, reflections_per_photon_stddev);
  graph_reflections_per_photon_stddev->SetTitle("reflections_per_photon_stddev");
  graph_reflections_per_photon_stddev->SetMarkerColor(kRed);
  graph_reflections_per_photon_stddev->SetMarkerSize(10);
  graph_reflections_per_photon_stddev->SetMarkerSize(1);
  graph_reflections_per_photon_stddev->SetMarkerStyle(21);
  graph_reflections_per_photon_stddev->Draw("AP");
  canvas->Print("Graph/graph_reflections_per_photon_stddev.pdf");
  canvas->Clear();

  //---------------------------------------------------------------------//

}
