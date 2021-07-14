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

  if (aParticle->GetDefinition()->GetParticleName() != "opticalphoton")
  return;

  if (VolName == "tablet") {
      // G4int stationID = atoi(detectorWords[2]);
      _eventAction->InsertPhotonCreation();
  }
}
