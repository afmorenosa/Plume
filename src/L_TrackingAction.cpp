/*
 * L_TrackingAction.cpp
 *
 *  Created on: Jul 13, 2021
 *      Author: afduquebr afmorenosa
 */

#include "L_TrackingAction.h"

L_TrackingAction::L_TrackingAction(L_EventAction* evAct):
_eventAction(evAct), G4UserTrackingAction() { }

L_TrackingAction::~L_TrackingAction() { }

void L_TrackingAction::PreUserTrackingAction(const G4Track* track) {

  G4VPhysicalVolume *Volume = track->GetVolume();

  const G4DynamicParticle *aParticle = track->GetDynamicParticle();

  if (aParticle->GetDefinition()->GetParticleName() == "opticalphoton"){
    CountPhotons(track, Volume);
  } else if (aParticle->GetDefinition()->GetParticleName() == "e-") {
    CountElectron(track);
  }

}

void L_TrackingAction::CountPhotons(
  const G4Track* track, G4VPhysicalVolume *Volume
) {

  if (Volume->GetLogicalVolume()->GetName() == "tablet") {

    if (track->GetParentID() == 1) {
      _eventAction->InsertPhotonCreation();
    } else {
      _eventAction->InsertSecondaryPhotonCreation();
    }

  }

  if (Volume->GetName() == "tablet1") {

    if (track->GetParentID() == 1) {
      _eventAction->InsertPhotonCreationTablet1();
    } else {
      _eventAction->InsertSecondaryPhotonCreationTablet1();
    }

  } else if (Volume->GetName() == "tablet2") {

    if (track->GetParentID() == 1) {
      _eventAction->InsertPhotonCreationTablet2();
    } else {
      _eventAction->InsertSecondaryPhotonCreationTablet2();
    }

  }

}

void L_TrackingAction::CountElectron(
  const G4Track* track
) {

  if (track->GetTrackID() != 1) {

    _eventAction->InsertElectronCreation();

    _eventAction->SecondaryElectronEnergy(track->GetTotalEnergy());

  }

}
