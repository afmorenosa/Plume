/*
 * L_EventAction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

#include <vector>
#include <map>

#include <G4UserEventAction.hh>
#include "globals.hh"
#include "L_RunAction.h"
#include "L_Hit.h"
#include "L_SteppingAction.h"

class G4Event;

class L_RunAction;
class L_SteppingAction;
class L_PrimaryGeneratorAction;

class L_EventAction: public G4UserEventAction {
public:
  L_EventAction(L_RunAction*, L_SteppingAction*);
  virtual ~L_EventAction();

public:
  virtual void BeginOfEventAction(const G4Event* );
  virtual void EndOfEventAction(const G4Event* );

  inline void InsertPhoton(G4int secID){
    int id = (secID > 0) ? (secID-1) : (LConst::pmt_n_channels - secID - 1);
    _nPhot[id] ++;
  }

  // Set the zone
  void SetZone(G4int Zone) {_Zone = Zone;}

  // Photons counter
  void InsertPhotonCreation() {_nPhotCreated++;}
  void InsertSecondaryPhotonCreation() {_nSecondaryPhotCreated++;};

  void InsertPhotonCreationTablet1() {_nPhotCreated1++;}
  void InsertSecondaryPhotonCreationTablet1() {_nSecondaryPhotCreated1++;}
  void InsertPhotonCreationTablet2() {_nPhotCreated2++;}
  void InsertSecondaryPhotonCreationTablet2() {_nSecondaryPhotCreated2++;}

  void PhotonReflectedCount (G4int trackID) {
    if (track_reflected[trackID]) {
      _nPhotReflected ++;
      _nReflectionPerPhoton->push_back(track_reflected_counter[trackID]);
    } else {
      _nPhotonStraight ++;
    }
  }

  void PhotonDetected (
    G4int trackID,
    G4int parentTrackID,
    const G4ThreeVector PhotonDetectedPosition
  ) {

    if (
      track_detected.find(trackID) == track_detected.end()
    ) {
      track_detected[trackID] = true;
      _nPhotonDetected++;

      G4double hit_radius = std::sqrt(
        PhotonDetectedPosition.x()*PhotonDetectedPosition.x() +
        PhotonDetectedPosition.y()*PhotonDetectedPosition.y()
      );

      if (hit_radius < std::sqrt(5.)*mm) {
        _nPhotonZone0++;
      } else if (hit_radius < std::sqrt(10.)*mm) {
        _nPhotonZone1++;
      } else if (hit_radius < std::sqrt(15.)*mm) {
        _nPhotonZone2++;
      } else if (hit_radius < std::sqrt(20.)*mm) {
        _nPhotonZone3++;
      } else {
        _nPhotonZone4++;
      }


      _nPhotonDetectedPosition->push_back(hit_radius);

      if (parentTrackID != 1) {

        _nSecPhotonDetected++;
        _nSecPhotonDetectedPosition->push_back(hit_radius);

      } else {

        _nPriPhotonDetectedPosition->push_back(hit_radius);

      }

    }
  }

  // Reflections
  void InsertPhotonReflection() {_nPhotReflection++;}

  void AddReflection (G4int trackID) {
    track_reflected[trackID] = true;
    track_reflected_counter[trackID]++;
  }

  // Electrons counter
  void InsertElectronCreation() {_nElecCreated++;}

  void InsertSecondModuleElectron() {_nSecondModuleElecCreated++;}

  // Electrons energy
  void SecondaryElectronEnergy(G4double energy) {
    _secElecEnergy->push_back(energy);
  }

  void ElectronEnergyReach(
    G4double PreEnergy, G4double PostEnergy
  ) {
    _nPrePVElecEnergy = PreEnergy;
    _nPostPVElecEnergy = PostEnergy;
  }

  // Positions
  void ElectronPositionReach(
    const G4ThreeVector PrePoint, const G4ThreeVector PostPoint
  ) {
    _nPrePVxPosition = PrePoint.x();
    _nPrePVyPosition = PrePoint.y();

    _nPostPVxPosition = PostPoint.x();
    _nPostPVyPosition = PostPoint.y();
  }

  // Maps functions
  void AddKeyToMaps (G4int trackID) {

    if (track_reflected.find(trackID) == track_reflected.end()) {
      track_reflected[trackID] = false;
    }

    if (
      track_reflected_counter.find(trackID) == track_reflected_counter.end()
    ) {
      track_reflected_counter[trackID] = 0;
    }

  }

private:
  L_RunAction* runAction;
  L_SteppingAction* _steppingAction;

  G4int printModulo;
  G4int theCollectionID;

  // Zones
  G4int _Zone;

  // Counter of Photons in Zone Detector
  G4int _nPhotonZone0;
  G4int _nPhotonZone1;
  G4int _nPhotonZone2;
  G4int _nPhotonZone3;
  G4int _nPhotonZone4;

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

  //Positions of Detected Photons
  std::vector<G4double> *_nPhotonDetectedPosition{};
  std::vector<G4double> *_nPriPhotonDetectedPosition{};
  std::vector<G4double> *_nSecPhotonDetectedPosition{};

  // Photon Paths
  G4int _nPhotonStraight;
  G4int _nPhotReflected;

  // Reflections
  G4int _nPhotReflection;

  std::vector<G4int> *_nReflectionPerPhoton{};

  // Electrons counter
  G4int _nElecCreated;
  G4int _nSecondModuleElecCreated;

  // Electrons energy
  G4double _nPrePVElecEnergy;
  G4double _nPostPVElecEnergy;

  std::vector<G4double> *_secElecEnergy{};

  // Tablet Positions
  G4double _nPrePVxPosition;
  G4double _nPrePVyPosition;
  G4double _nPostPVxPosition;
  G4double _nPostPVyPosition;

  // Tracks maps
  std::map<G4int, bool> track_reflected;
  std::map<G4int, int> track_reflected_counter;

  std::map<G4int, bool> track_detected;
};
