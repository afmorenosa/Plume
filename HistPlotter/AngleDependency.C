
void AngleDependency () {

  TCanvas *canvas = new TCanvas(
    "canvas",
    "canvas",
    800,
    600
  );

  std::vector<TFile *> root_files;
  root_files.push_back(TFile::Open("angleA.root"));
  root_files.push_back(TFile::Open("angleB.root"));
  root_files.push_back(TFile::Open("angleC.root"));
  root_files.push_back(TFile::Open("angleD.root"));
  root_files.push_back(TFile::Open("angleE.root"));

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

  std::map<int, TH1I *> hist_total_photon_detected_counter_angle;

  for (size_t i = 0; i < trees.size(); i++) {

    hist_total_photon_detected_counter_angle[i] = new TH1I(
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
      hist_total_photon_detected_counter_angle[i]->Fill(nPhotonDetected[i]);
    }

  }

  //-------------------------- Draw Histograms --------------------------//

  const Int_t n_Angles = 5;

  // Detected Photons Counter
  double Angles[n_Angles] = {6, 18, 30, 42, 54};
  double Angles_err[n_Angles] = {6, 6, 6, 6, 6};
  double total_photon_detected_mean[n_Angles];
  double total_photon_detected_rms[n_Angles];

  for (size_t angle_i = 0; angle_i < n_Angles; angle_i++) {

    total_photon_detected_mean[angle_i] =
    hist_total_photon_detected_counter_angle[angle_i]->GetMean();
    total_photon_detected_rms[angle_i] =
    hist_total_photon_detected_counter_angle[angle_i]->GetRMS();

  }

  // Detected Photons Counter
  TGraph *graph_total_photon_detected_mean =
  new TGraph(n_Angles, Angles, total_photon_detected_mean);
  graph_total_photon_detected_mean->GetXaxis()->SetTitle("Angle [degrees]");
  graph_total_photon_detected_mean->GetYaxis()->SetTitle("Events");
  graph_total_photon_detected_mean->SetTitle("Total Photons Count Mean");
  graph_total_photon_detected_mean->SetMarkerColor(kRed);
  graph_total_photon_detected_mean->SetMarkerSize(10);
  graph_total_photon_detected_mean->SetMarkerSize(1);
  graph_total_photon_detected_mean->SetMarkerStyle(21);
  graph_total_photon_detected_mean->Draw("AP");
  canvas->Print("Graph_2/graph_total_photon_detected_mean.pdf");
  canvas->Clear();

  TGraphAsymmErrors *graph_total_photon_detected_mean_error =
  new TGraphAsymmErrors(
    n_Angles, Angles, total_photon_detected_mean,
    Angles_err, Angles_err, total_photon_detected_rms, total_photon_detected_rms
  );
  graph_total_photon_detected_mean_error->GetXaxis()->SetTitle("Angle [degrees]");
  graph_total_photon_detected_mean_error->GetYaxis()->SetTitle("Events");
  graph_total_photon_detected_mean_error->SetTitle("Total Photons Count [RMS errors]");
  graph_total_photon_detected_mean_error->SetMarkerColor(kRed);
  graph_total_photon_detected_mean_error->SetMarkerSize(10);
  graph_total_photon_detected_mean_error->SetMarkerSize(1);
  graph_total_photon_detected_mean_error->SetMarkerStyle(21);
  graph_total_photon_detected_mean_error->Draw("AP");
  canvas->Print("Graph_2/graph_total_photon_detected_mean_errors.pdf");
  canvas->Clear();

  TGraph *graph_total_photon_detected_rms =
  new TGraph(n_Angles, Angles, total_photon_detected_rms);
  graph_total_photon_detected_rms->GetXaxis()->SetTitle("Angle [degrees]");
  graph_total_photon_detected_rms->GetYaxis()->SetTitle("Events");
  graph_total_photon_detected_rms->GetYaxis()->SetRangeUser(20, 90);
  graph_total_photon_detected_rms->SetTitle("Total Photons Count RMS");
  graph_total_photon_detected_rms->SetMarkerColor(kRed);
  graph_total_photon_detected_rms->SetMarkerSize(10);
  graph_total_photon_detected_rms->SetMarkerSize(1);
  graph_total_photon_detected_rms->SetMarkerStyle(21);
  graph_total_photon_detected_rms->Draw("AP");
  canvas->Print("Graph_2/graph_total_photon_detected_rms.pdf");
  canvas->Clear();

  //---------------------------------------------------------------------//

}
