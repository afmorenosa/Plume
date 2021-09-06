/*
 * L_RunAction.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#include "L_RunAction.h"


L_RunAction::L_RunAction() {
  //	_outputFileName = "data.root";
  timer = new G4Timer();

  // Positions of Detected Photons
  _nPhotonDetectedPosition = new std::vector<G4double>{};
  _nSecPhotonDetectedPosition = new std::vector<G4double>{};

  // Reflections
  _nReflectionPerPhoton = new std::vector<G4int>{};

  // Electrons energy
  _secElecEnergy = new std::vector<G4double>{};

  G4cout << "Run action constructor" << G4endl;
}

L_RunAction::~L_RunAction() {
  delete tree;
  delete hfile;
}

void L_RunAction::BeginOfRunAction(const G4Run* run)
{

  G4cout << "BeginOfRunAction" << G4endl;

  timer->Start();

  // Histogramming

  hfile = new TFile(_outputFileName, "RECREATE", "LHCb Luminometer Simulation Data", 1);

  G4cout << "Output file created" << G4endl;
  if (hfile->IsZombie()) exit(-1);
  tree = new TTree("T", "LHCb Luminometer Data Tree");
  //	tree->SetAutoSave(1000000);

  // Create new event
  TTree::SetBranchStyle(0);

  // Branches filled for each EVENT

  // Event ID
  tree->Branch("EventID",  &_EventID,  "EventID/I");
  // Number of sectors (constant every event, just for array length)
  tree->Branch("nSec", &_nSec, "nSec/I");

  //--------------------------------- Zones ---------------------------------//
  // The zone of the detector in which the primary electron hits
  tree->Branch("Zone", &_Zone, "Zone/I");

  //---------------------------- Photons counter ----------------------------//
  // Number of photons detected in each sector
  tree->Branch("nPhot", _nPhot, "nPhot[nSec]/I");

  // Number of primary photons created in each sector
  tree->Branch("nPhotCreated", &_nPhotCreated, "nPhotCreated/I");
  // Number of secondary photons created in each sector
  tree->Branch("nSecondaryPhotCreated", &_nSecondaryPhotCreated, "nSecondaryPhotCreated/I");

  // Number of primary photons created in first module
  tree->Branch("nPhotCreated1", &_nPhotCreated1, "nPhotCreated1/I");
  // Number of secondary photons created in first module
  tree->Branch("nSecondaryPhotCreated1", &_nSecondaryPhotCreated1, "nSecondaryPhotCreated1/I");
  // Number of primary photons created in second module
  tree->Branch("nPhotCreated2", &_nPhotCreated2, "nPhotCreated2/I");
  // Number of secondary photons created in second module
  tree->Branch("nSecondaryPhotCreated2", &_nSecondaryPhotCreated2, "nSecondaryPhotCreated2/I");

  // Photons that reach the detector module
  tree->Branch("nPhotonDetected", &_nPhotonDetected, "nPhotonDetected/I");
  // Secondary photons that reach the detector module
  tree->Branch("nSecPhotonDetected", &_nSecPhotonDetected, "nSecPhotonDetected/I");

  // Positions of Photons that reach the detector module
  _nPhotonDetectedPositionBranch = tree->Branch("nPhotonDetectedPosition", _nPhotonDetectedPosition);
  // Positions of Secondary photons that reach the detector module
  _nSecPhotonDetectedPositionBranch = tree->Branch("nSecPhotonDetectedPosition", _nSecPhotonDetectedPosition);

  //----------------------------- Photon Paths -----------------------------//
  // Count of photons that reach the window without reflection
  tree->Branch("nPhotonStraight", &_nPhotonStraight, "nPhotonStraight/I");
  // Count of photons that reach the window with at least one reflection
  tree->Branch("nPhotReflected", &_nPhotReflected, "nPhotReflected/I");

  //------------------------------ Reflections ------------------------------//
  // Number of reflections in each sector
  tree->Branch("nPhotReflection", &_nPhotReflection, "nPhotReflection/I");

  // Reflections for each photon
  _nReflectionPerPhotonBranch = tree->Branch("nReflectionPerPhoton", _nReflectionPerPhoton);

  //--------------------------- Electrons counter ---------------------------//
  // Number of secondary electrons created each sector
  tree->Branch("nElecCreated", &_nElecCreated, "nElecCreated/I");
  // Number of secondary electrons in second module
  tree->Branch("nSecondModuleElecCreated", &_nSecondModuleElecCreated, "nSecondModuleElecCreated/I");

  //--------------------------- Electrons energy ---------------------------//
  // Energy of primary electron before Tablet2 in second module
  tree->Branch("nPrePVElecEnergy", &_nPrePVElecEnergy, "nPrePVElecEnergy/D");
  // Energy of primary electron after Tablet2 in second module
  tree->Branch("nPostPVElecEnergy", &_nPostPVElecEnergy, "nPostPVElecEnergy/D");

  // Energy each of the secondary electrons
  _secElecEnergyBranch = tree->Branch("secElecEnergy", _secElecEnergy);

  //------------------------------- Positions -------------------------------//
  // X Position of primary electron before Tablet2 in second module
  tree->Branch("nPrePVxPosition", &_nPrePVxPosition, "nPrePVxPosition/D");
  // Y Position of primary electron before Tablet2 in second module
  tree->Branch("nPrePVyPosition", &_nPrePVyPosition, "nPrePVyPosition/D");
  // X Position of primary electron after Tablet2 in second module
  tree->Branch("nPostPVxPosition", &_nPostPVxPosition, "nPostPVxPosition/D");
  // Y Position of primary electron after Tablet2 in second module
  tree->Branch("nPostPVyPosition", &_nPostPVyPosition, "nPostPVyPosition/D");

  // Branches filled for each HIT (commented due to "optimization")

  G4cout << "BeginOfRunAction end" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void L_RunAction::EndOfRunAction(const G4Run* )
{
  //	hfile = tree->GetCurrentFile();

  G4cout << "End of run action" << G4endl;
  tree->Write();
  hfile->Write();
  tree->Print();
  timer->Stop();
  hfile->Close();

  G4cout << "Time: " << *timer << G4endl;

}
