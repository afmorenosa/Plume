/*
 * L_TrackingAction.h
 *
 *  Created on: Jul 13, 2021
 *      Author: afduquebr afmorenosa
 */

#pragma once

#include <G4UserTrackingAction.hh>
// #include <G4DynamicParticle.hh>
#include "L_EventAction.h"

class L_TrackingAction: public G4UserTrackingAction {
public:
    L_TrackingAction(L_EventAction*);
    virtual ~L_TrackingAction();
public:
    virtual void PreUserTrackingAction(const G4Track*);

private:
    L_EventAction* _eventAction;
};
