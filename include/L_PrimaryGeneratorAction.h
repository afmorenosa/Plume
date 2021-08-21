/*
 * L_PrimaryGeneratorAction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

#include <G4VUserPrimaryGeneratorAction.hh>
#include "globals.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "TRandom3.h"
#include "G4Timer.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TChain.h"

// #include "Pythia8/Pythia.h"
#include "LConst.hh"
#include <time.h>

#include "L_VolumeStructures.h"

#include "Randomize.hh"


//class G4Hep
class G4HEPEvtInterface;
class G4VPrimaryGenerator;
class G4ParticleGun;
class G4Event;

class L_PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {
public:
    L_PrimaryGeneratorAction();
    virtual ~L_PrimaryGeneratorAction();
public:
    void GeneratePrimaries(G4Event* anEvent);

private:
    // bool GetEvent(Pythia8::Event event);

    PMT_tablet tablet;

    void CheckHit (G4double &x0, G4double &y0);

private:
    G4ParticleGun *_particleGun = new G4ParticleGun();

//    TChain *tree;

    // Data to be transported from pythia to gun
    G4int nEvents;
    G4int nParticles;
    G4int pdgID[20000];
    G4float X[20000];
    G4float Y[20000];
    G4float Z[20000];
    G4float pX[20000];
    G4float pY[20000];
    G4float pZ[20000];
    G4float T[20000];

    G4int iEv;

    // Pythia generator declaration
    // Pythia8::Pythia pythia;
    // // Pythia event declaration
    // Pythia8::Event& PythiaEvent = pythia.event;
};
