/*
 * L_EventAction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

#include <vector>

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
    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );

    void SetPrimGenerator(L_PrimaryGeneratorAction *gen){_primGenerator = gen;}
    inline void InsertPhoton(G4int secID){ int id = (secID > 0) ? (secID-1) : (LConst::pmt_n_channels - secID - 1); _nPhot[id] ++; }
    void InsertPhotonCreation() {_nPhotCreated++;}
    void InsertSecondaryPhotonCreation() {_nSecondaryPhotCreated++;};
    void InsertPhotonReflection() {_nPhotReflected++;}
    void InsertElectronCreation() {_nElecCreated++;}
    void SecondaryElectronEnergy(G4double energy) {
      _secElecEnergy->push_back(energy);
    }

private:
    L_RunAction* runAction;
    L_SteppingAction* _steppingAction;
    G4int printModulo;
    G4int theCollectionID;

    G4int _nPhot[LConst::pmt_n_channels];
    G4int _nPhotCreated;
    G4int _nSecondaryPhotCreated;
    G4int _nPhotReflected;
    G4int _nElecCreated;

    std::vector<G4double> *_secElecEnergy{};

    L_PrimaryGeneratorAction *_primGenerator;
};
