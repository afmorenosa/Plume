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
  _nPhotReflected = 0;
  _nElecCreated = 0;
  _secElecEnergy = {};
  for (G4int i = 0; i < LConst::pmt_n_channels; ++i) {
    _nPhot[i] = 0;
  }

}

L_EventAction::~L_EventAction() {
}

void L_EventAction::BeginOfEventAction(const G4Event* event)
{

  std::cout << "A" << '\n';

//    G4cout << "BeginOfEventAction" << G4endl;
    G4int eventNum = event->GetEventID();

    std::cout << "B" << '\n';
    // Printing an event number
	if (eventNum%printModulo == 0) {
		G4cout << "\n---> Begin of Event: " << eventNum << G4endl;
	}
  std::cout << "C" << '\n';

  _nPhotCreated = 0;
  _nPhotReflected = 0;
  _nElecCreated = 0;
  _secElecEnergy.clear();
  // Setting the number of photons in each sector to 0 for further counting
  for (G4int i = 0; i < LConst::pmt_n_channels; ++i) {
    runAction->_nPhot[i] = 0;
    _nPhot[i] = 0;
  }
  std::cout << "D" << '\n';

    // Reset stepping
	_steppingAction->Reset();
	_steppingAction->ResetPerEvent();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void L_EventAction::EndOfEventAction(const G4Event* event)
{

  std::cout << "E" << '\n';
//    G4cout << "End of event" << G4endl;
	// Print info about end of the event
	G4int eventNum = event->GetEventID();

  std::cout << "F" << '\n';
    // Getting the number of sectors from the constant collection
    runAction->_nSec = LConst::pmt_n_channels;
    std::cout << "F.1" << '\n';


    runAction->_nPhotCreated = _nPhotCreated;
    std::cout << "F.2" << '\n';
    runAction->_nPhotReflected = _nPhotReflected;
    std::cout << "F.3" << '\n';
    runAction->_nElecCreated = _nElecCreated;
    std::cout << "F.4" << '\n';

    runAction->_secElecEnergy.clear();
    std::cout << "F.5" << '\n';
    runAction->_secElecEnergyBranch->SetAddress(&_secElecEnergy);
    std::cout << "F.6" << '\n';
    runAction->_secElecEnergy = _secElecEnergy;
    std::cout << "F.7" << '\n';

    for (G4int i = 0; i < LConst::pmt_n_channels; ++i)
      runAction->_nPhot[i] = _nPhot[i];
      std::cout << "F.8" << '\n';

    runAction->_EventID = eventNum;
    std::cout << "F.9  " << _secElecEnergy.size() << '\t' << runAction->_secElecEnergy.size() << '\n';

    runAction->tree->Fill();

  std::cout << "G" << '\n';
	//	G4cout << "End of event" << G4endl;
}
