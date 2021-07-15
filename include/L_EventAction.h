/*
 * L_EventAction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

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
    void InsertPhotonReflection() {_nPhotReflected++;}

private:
    L_RunAction* runAction;
    L_SteppingAction* _steppingAction;
    G4int printModulo;
    G4int theCollectionID;

    G4int _nPhot[LConst::pmt_n_channels];
    G4int _nPhotCreated;
    G4int _nPhotReflected;
    

    L_PrimaryGeneratorAction* _primGenerator;
};
