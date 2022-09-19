/*
 * L_TrackingAction.cpp
 *
 *  Created on: Jul 13, 2021
 *      Author: afduquebr ccatamorenos
 */

#include "L_TrackingAction.h"

L_TrackingAction::L_TrackingAction(L_EventAction* evAct):
_eventAction(evAct), G4UserTrackingAction() { }

L_TrackingAction::~L_TrackingAction() { }

void L_TrackingAction::PreUserTrackingAction(const G4Track* track) {

  // Get the volume in which the particle is created
  G4VPhysicalVolume *Volume = track->GetVolume();

  // Get the particle definition
  const G4DynamicParticle *aParticle = track->GetDynamicParticle();

  if (aParticle->GetDefinition()->GetParticleName() == "opticalphoton"){

    // Optical photons
    CountPhotons(track, Volume);

  } else if (aParticle->GetDefinition()->GetParticleName() == "e-") {

    // Electrons
    CountElectron(track);

  }

}

void L_TrackingAction::CountPhotons(
  const G4Track* track, G4VPhysicalVolume *Volume
) {


  if (Volume->GetLogicalVolume()->GetName() == "tablet") {

    // Photons generated in the quartz
    if (track->GetParentID() == 1) {

      // Primary photons
      _eventAction->InsertPhotonCreation();

    } else {

      // Secondary photons
      _eventAction->InsertSecondaryPhotonCreation();

    }

  }

  if (Volume->GetName() == "tablet1") {

    // Photons generated in the quartz of the first module
    if (track->GetParentID() == 1) {

      // Primary photons
      _eventAction->InsertPhotonCreationTablet1();

    } else {

      // Secondary photons
      _eventAction->InsertSecondaryPhotonCreationTablet1();

    }

  } else if (Volume->GetName() == "tablet2") {

    // Photons generated in the quartz of the second module
    if (track->GetParentID() == 1) {

      // Primary photons
      _eventAction->InsertPhotonCreationTablet2();

    } else {

      // Secondary photons
      _eventAction->InsertSecondaryPhotonCreationTablet2();

    }

  }

}

void L_TrackingAction::CountElectron(
  const G4Track* track
) {

  // Search for the secondary electrons only
  if (track->GetTrackID() != 1) {

    // Count electron
    _eventAction->InsertElectronCreation();

    // Add secondary electron energy
    _eventAction->SecondaryElectronEnergy(track->GetTotalEnergy());

  } else {

    // Add secondary electron energy
    _eventAction->HitAngle(track->GetMomentumDirection());

  }

}
