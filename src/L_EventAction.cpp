/*
 * L_EventAction.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#include "L_EventAction.h"


#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"

//G4
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "globals.hh"

L_EventAction::L_EventAction(L_RunAction* runact,
        L_SteppingAction* steppingAction) :
		runAction(runact), _steppingAction(steppingAction), printModulo(100)
{
  std::cout << "Event action construction" << '\n';

  _nPhotCreated = 0;
  _nSecondaryPhotCreated = 0;

  _nPhotCreated1 = 0;
  _nSecondaryPhotCreated1 = 0;
  _nPhotCreated2 = 0;
  _nSecondaryPhotCreated2 = 0;

  _nPhotReflected = 0;
  _nElecCreated = 0;
  _nSecondModuleElecCreated = 0;
  _nPrePVxPosition = 0.0;
  _nPrePVyPosition = 0.0;
  _nPrePVElecEnergy = 0.0;
  _nPostPVxPosition = 0.0;
  _nPostPVyPosition = 0.0;
  _nPostPVElecEnergy = 0.0;
  _secElecEnergy = new std::vector<G4double>{};
  for (G4int i = 0; i < LConst::pmt_n_channels; ++i) {
    _nPhot[i] = 0;
  }

}

L_EventAction::~L_EventAction() {
}

void L_EventAction::BeginOfEventAction(const G4Event* event)
{


//    G4cout << "BeginOfEventAction" << G4endl;
    G4int eventNum = event->GetEventID();

    // Printing an event number
	if (eventNum%printModulo == 0) {
		G4cout << "\n---> Begin of Event: " << eventNum << G4endl;
	}

  _nPhotCreated = 0;
  _nSecondaryPhotCreated = 0;

  _nPhotCreated1 = 0;
  _nSecondaryPhotCreated1 = 0;
  _nPhotCreated2 = 0;
  _nSecondaryPhotCreated2 = 0;

  _nPhotReflected = 0;
  _nElecCreated = 0;
  _nSecondModuleElecCreated = 0;
  _nPrePVxPosition = 0.0;
  _nPrePVyPosition = 0.0;
  _nPrePVElecEnergy = 0.0;
  _nPostPVxPosition = 0.0;
  _nPostPVyPosition = 0.0;
  _nPostPVElecEnergy = 0.0;
  _secElecEnergy->clear();
  // Setting the number of photons in each sector to 0 for further counting
  for (G4int i = 0; i < LConst::pmt_n_channels; ++i) {
    runAction->_nPhot[i] = 0;
    _nPhot[i] = 0;
  }

    // Reset stepping
	_steppingAction->Reset();
	_steppingAction->ResetPerEvent();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void L_EventAction::EndOfEventAction(const G4Event* event)
{

//    G4cout << "End of event" << G4endl;
	// Print info about end of the event
	G4int eventNum = event->GetEventID();

    // Getting the number of sectors from the constant collection
    runAction->_nSec = LConst::pmt_n_channels;


    runAction->_nPhotCreated = _nPhotCreated;
    runAction->_nSecondaryPhotCreated = _nSecondaryPhotCreated;

    runAction->_nPhotCreated1 = _nPhotCreated1;
    runAction->_nSecondaryPhotCreated1 = _nSecondaryPhotCreated1;
    runAction->_nPhotCreated2 = _nPhotCreated2;
    runAction->_nSecondaryPhotCreated2 = _nSecondaryPhotCreated2;

    runAction->_nPhotReflected = _nPhotReflected;
    runAction->_nElecCreated = _nElecCreated;
    runAction->_nSecondModuleElecCreated = _nSecondModuleElecCreated;
    runAction->_nPrePVxPosition = _nPrePVxPosition;
    runAction->_nPrePVyPosition = _nPrePVyPosition;
    runAction->_nPrePVElecEnergy = _nPrePVElecEnergy;
    runAction->_nPostPVxPosition = _nPostPVxPosition;
    runAction->_nPostPVyPosition = _nPostPVyPosition;
    runAction->_nPostPVElecEnergy = _nPostPVElecEnergy;

    runAction->_secElecEnergy->clear();

    for (size_t i = 0; i < _secElecEnergy->size(); i++) {
      runAction->_secElecEnergy->push_back(_secElecEnergy->at(i));
    }

    for (G4int i = 0; i < LConst::pmt_n_channels; ++i)
      runAction->_nPhot[i] = _nPhot[i];

    runAction->_EventID = eventNum;

    runAction->tree->Fill();

	//	G4cout << "End of event" << G4endl;
}
