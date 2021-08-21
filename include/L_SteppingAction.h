/*
 * L_SteppingAction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

#include <G4UserSteppingAction.hh>
#include "L_PrimaryGeneratorAction.h"
#include "L_EventAction.h"

class L_PrimaryGeneratorAction;

class L_EventAction;

class L_SteppingAction: public G4UserSteppingAction {
public:
    L_SteppingAction(L_PrimaryGeneratorAction*);
    virtual ~L_SteppingAction();
	void UserSteppingAction(const G4Step*);

  void SetEventAction(L_EventAction *eventAction);

	void Reset();
	void ResetPerEvent();

private:
    L_PrimaryGeneratorAction* _genAction;
    L_EventAction* _eventAction;

    G4double _probOfReflection;
    G4double _particleID;

    void InternalReflectionProbability(
      G4double energy,
      G4double& probability
    );

    void PhotonsPath(
      G4StepPoint *PrePoint,
      G4StepPoint *PostPoint,
      G4int trackID
    );

    void SecondModuleElectrons(
      G4StepPoint *PrePoint,
      G4StepPoint *PostPoint,
      G4int trackID
    );
};
