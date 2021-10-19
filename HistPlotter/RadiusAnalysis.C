
void RadiusAnalysis () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  std::vector<TFile *> root_files;
  root_files.push_back(TFile::Open("radius00.root"));
  root_files.push_back(TFile::Open("radius02.root"));
  root_files.push_back(TFile::Open("radius04.root"));
  root_files.push_back(TFile::Open("radius06.root"));
  root_files.push_back(TFile::Open("radius08.root"));
  root_files.push_back(TFile::Open("radius10.root"));
  root_files.push_back(TFile::Open("radius12.root"));
  root_files.push_back(TFile::Open("radius14.root"));
  root_files.push_back(TFile::Open("radius16.root"));
  root_files.push_back(TFile::Open("radius18.root"));
  root_files.push_back(TFile::Open("radius20.root"));
  root_files.push_back(TFile::Open("radius22.root"));
  root_files.push_back(TFile::Open("radius24.root"));
  root_files.push_back(TFile::Open("radius26.root"));
  root_files.push_back(TFile::Open("radius28.root"));
  root_files.push_back(TFile::Open("radius30.root"));
  root_files.push_back(TFile::Open("radius32.root"));
  root_files.push_back(TFile::Open("radius34.root"));
  root_files.push_back(TFile::Open("radius36.root"));
  root_files.push_back(TFile::Open("radius38.root"));
  root_files.push_back(TFile::Open("radius40.root"));
  root_files.push_back(TFile::Open("radius42.root"));
  root_files.push_back(TFile::Open("radius44.root"));
  root_files.push_back(TFile::Open("radius46.root"));
  root_files.push_back(TFile::Open("radius48.root"));

  std::vector<TTree *> trees;
  for (size_t i = 0; i < root_files.size(); i++) {
    trees.push_back((TTree *) root_files[i]->Get("T"));
  }

  //------------------------ Branches variables ------------------------//

  // Detected Photons Counter
  std::vector<Int_t> nPhotonDetected(trees.size(), -1);
  std::vector<Int_t> nSecPhotonDetected(trees.size(), -1);

  for (size_t i = 0; i < trees.size(); i++) {

    // Detected Photons Counter
    trees[i]->SetBranchAddress("nPhotonDetected", &nPhotonDetected[i]);

  }

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

  //--------------------------------------------------------------------//

  std::map<int, TH1I *> hist_total_photon_detected_counter_radius;

  for (size_t i = 0; i < trees.size(); i++) {

    hist_total_photon_detected_counter_radius[i] = new TH1I(
      "Total Detected Photons, Index: " +
      TString(std::to_string(i).c_str()),
      "Total Detected Photons; n Photons; Events",
      100,
      0,
      1000
    );

  }

  //--------------------------------------------------------------------//

  for (size_t i = 0; i < trees.size(); i++) {

    int nentries, nbytes;
    nentries = (Int_t)trees[i]->GetEntries();

    for (int k = 0; k < nentries; k++) {
      nbytes = trees[i]->GetEntry(k);

      // Fill histograms.

      // Detected Photons Counter
      hist_total_photon_detected_counter->Fill(nPhotonDetected[i]);
      hist_total_photon_detected_counter_radius[i]->Fill(nPhotonDetected[i]);
    }

  }

  //-------------------------- Draw Histograms --------------------------//

  const Int_t n_Radius = 25;

  // Detected Photons Counter
  double Radius[n_Radius] = {0., 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8,
    2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8};
  double total_photon_detected_mean[n_Radius];
  double total_photon_detected_rms[n_Radius];

  for (size_t radius_i = 0; radius_i < n_Radius; radius_i++) {

    total_photon_detected_mean[radius_i] =
    hist_total_photon_detected_counter_radius[radius_i]->GetMean();
    total_photon_detected_rms[radius_i] =
    hist_total_photon_detected_counter_radius[radius_i]->GetRMS();

  }

  // Detected Photons Counter
  TGraph *graph_total_photon_detected_mean =
  new TGraph(n_Radius, Radius, total_photon_detected_mean);
  graph_total_photon_detected_mean->GetXaxis()->SetTitle("Radius [mm]");
  graph_total_photon_detected_mean->GetYaxis()->SetTitle("Photons");
  graph_total_photon_detected_mean->SetTitle("Mean of Total Detected Photons");
  graph_total_photon_detected_mean->GetXaxis()->SetRangeUser(0, 5);
  graph_total_photon_detected_mean->GetYaxis()->SetRangeUser(300, 700);
  graph_total_photon_detected_mean->SetMarkerColor(kRed);
  graph_total_photon_detected_mean->SetMarkerSize(10);
  graph_total_photon_detected_mean->SetMarkerSize(1);
  graph_total_photon_detected_mean->SetMarkerStyle(21);
  graph_total_photon_detected_mean->Draw("AP");
  canvas->Print("Graph/graph_total_photon_detected_mean_radius.pdf");
  canvas->Clear();

  TGraphAsymmErrors *graph_total_photon_detected_mean_errors =
  new TGraphAsymmErrors(
    n_Radius, Radius, total_photon_detected_mean,
    0, 0, total_photon_detected_rms, total_photon_detected_rms
  );
  graph_total_photon_detected_mean_errors->GetXaxis()->SetTitle("Radius [mm]");
  graph_total_photon_detected_mean_errors->GetYaxis()->SetTitle("Photons");
  graph_total_photon_detected_mean_errors->SetTitle("Mean of Total Detected Photons");
  graph_total_photon_detected_mean_errors->GetXaxis()->SetRangeUser(0, 5);
  graph_total_photon_detected_mean_errors->GetYaxis()->SetRangeUser(300, 700);
  graph_total_photon_detected_mean_errors->SetMarkerColor(kRed);
  graph_total_photon_detected_mean_errors->SetMarkerSize(10);
  graph_total_photon_detected_mean_errors->SetMarkerSize(1);
  graph_total_photon_detected_mean_errors->SetMarkerStyle(21);
  graph_total_photon_detected_mean_errors->Draw("AP");
  canvas->Print("Graph/graph_total_photon_detected_mean_errors_radius.pdf");
  canvas->Clear();

  TGraph *graph_total_photon_detected_rms =
  new TGraph(n_Radius, Radius, total_photon_detected_rms);
  graph_total_photon_detected_rms->GetXaxis()->SetTitle("Radius [mm]");
  graph_total_photon_detected_rms->GetYaxis()->SetTitle("Photons");
  graph_total_photon_detected_rms->SetTitle("RMS of Total Detected Photons");
  graph_total_photon_detected_rms->GetYaxis()->SetRangeUser(20, 90);
  graph_total_photon_detected_rms->GetXaxis()->SetRangeUser(0, 5);
  graph_total_photon_detected_rms->SetMarkerColor(kRed);
  graph_total_photon_detected_rms->SetMarkerSize(10);
  graph_total_photon_detected_rms->SetMarkerSize(1);
  graph_total_photon_detected_rms->SetMarkerStyle(21);
  graph_total_photon_detected_rms->Draw("AP");
  canvas->Print("Graph/graph_total_photon_detected_rms_radius.pdf");
  canvas->Clear();

  //---------------------------------------------------------------------//

}
