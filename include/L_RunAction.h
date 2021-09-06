/*
 * L_RunAction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

#include <vector>

#include <G4UserRunAction.hh>

#include "G4Run.hh"
#include "G4RunManager.hh"

//my
#include "HitDataStructure.hh"
#include "LConst.hh"

//G4
#include "G4Timer.hh"
#include "globals.hh"
#include "G4UserRunAction.hh"

//root
#include "TTree.h"
#include "TFile.h"


class L_RunAction: public G4UserRunAction {
public:
  L_RunAction();
  virtual ~L_RunAction();
public:
  virtual void BeginOfRunAction(const G4Run* run);
  virtual void EndOfRunAction(const G4Run* run);

public:
  void SetOutputFileName(G4String fileName) {_outputFileName = fileName;}
  G4String GetOutputFileName() { return _outputFileName;}
  TTree* tree;
  HitData HitInfo;

  //    G4int _nPart;
  G4int _EventID;
  G4int _nSec;

  // Zones
  G4int _Zone;

  // Photons counter
  G4int _nPhot[LConst::pmt_n_channels];

  G4int _nPhotCreated;
  G4int _nSecondaryPhotCreated;

  G4int _nPhotCreated1;
  G4int _nSecondaryPhotCreated1;
  G4int _nPhotCreated2;
  G4int _nSecondaryPhotCreated2;

  // Detected Photons
  G4int _nPhotonDetected;
  G4int _nSecPhotonDetected;

  // Positions of Detected Photons
  std::vector<G4double> *_nPhotonDetectedPosition{};
  std::vector<G4double> *_nSecPhotonDetectedPosition{};
  TBranch *_nPhotonDetectedPositionBranch;
  TBranch *_nSecPhotonDetectedPositionBranch;

  // Photon Paths
  G4int _nPhotonStraight;
  G4int _nPhotReflected;

  // Reflections
  G4int _nPhotReflection;

  std::vector<G4int> *_nReflectionPerPhoton{};
  TBranch *_nReflectionPerPhotonBranch;

  // Electrons counter
  G4int _nElecCreated;
  G4int _nSecondModuleElecCreated;

  // Electrons energy
  G4double _nPrePVElecEnergy;
  G4double _nPostPVElecEnergy;

  std::vector<G4double> *_secElecEnergy{};
  TBranch *_secElecEnergyBranch;

  // Positions
  G4double _nPrePVxPosition;
  G4double _nPrePVyPosition;
  G4double _nPostPVxPosition;
  G4double _nPostPVyPosition;

public:


  // static const G4int _nPartMax = 200000;
  // G4int _TrackID[_nPartMax];
  // G4int _ParentID[_nPartMax];
  // G4int _PdgID[_nPartMax];
  // G4int _StationID[_nPartMax];
  // G4double _Energy[_nPartMax];
  // G4double _Time[_nPartMax];
  // G4double _X[_nPartMax];
  // G4double _Y[_nPartMax];
  // G4double _Z[_nPartMax];
  // G4double _Px[_nPartMax];
  // G4double _Py[_nPartMax];
  // G4double _Pz[_nPartMax];
  // G4double _Momentum[_nPartMax];

private:
  G4Timer* timer;
  TFile* hfile;
  G4String _outputFileName = "data.root";

};
