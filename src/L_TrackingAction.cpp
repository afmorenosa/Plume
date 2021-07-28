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

  G4String VolName = track->GetVolume()->GetLogicalVolume()->GetName();

  const G4DynamicParticle *aParticle = track->GetDynamicParticle();

  if (aParticle->GetDefinition()->GetParticleName() == "opticalphoton"){
    CountPhotons(track, VolName);
  } else if (aParticle->GetDefinition()->GetParticleName() == "e-") {
    CountElectron(track, VolName);
  }

}

void L_TrackingAction::CountPhotons(const G4Track* track, G4String VolName) {

  if (track->GetParentID() == 1 && VolName == "tablet") {
    _eventAction->InsertPhotonCreation();
  }

}

void L_TrackingAction::CountElectron(const G4Track* track, G4String VolName) {

  if (track->GetTrackID() != 1) {

    _eventAction->InsertElectronCreation();

    _eventAction->SecondaryElectronEnergy(track->GetTotalEnergy());

  }

}
