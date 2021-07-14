/*
 * L_SensitiveDetector.cpp
 *
 *  Created on: Oct 3, 2018
 *      Author: vsevolod
 */

#include "L_SensitiveDetector.h"



L_SensitiveDetector::L_SensitiveDetector(G4String name, L_EventAction *evAct) :
    G4VSensitiveDetector(name), _eventAction(evAct){

    G4cout << "Sensitive detector created" << G4endl;
}

L_SensitiveDetector::~L_SensitiveDetector() {
}

void L_SensitiveDetector::Initialize()
{

    //  G4cout << "___________________________ Detector initialized" << G4endl;
}


G4bool L_SensitiveDetector::ProcessHitsL(G4Step* aStep, G4TouchableHistory* hist) {
    return ProcessHits(aStep, hist);
}

G4bool L_SensitiveDetector::ProcessHits(G4Step* aStep,
                                        G4TouchableHistory*)
{


//    G4cout << "Hit!" << G4endl;


    // Getting a track from hit
    G4Track* aTrack = aStep->GetTrack();
    // Getting the hit position
    G4ThreeVector globalPosition = aStep->GetPostStepPoint()->GetPosition();


    G4StepPoint *aPostPoint = aStep->GetPostStepPoint();
    G4StepPoint *aPrevPoint = aStep->GetPreStepPoint();
    if (!aPostPoint->GetPhysicalVolume()) return false;

    G4LogicalVolume *PostVolume = aPostPoint->GetPhysicalVolume()->GetLogicalVolume();
    G4LogicalVolume *PrevVolume = aPrevPoint->GetPhysicalVolume()->GetLogicalVolume();


    // Names of previous and next volume
    G4String PreName = PrevVolume->GetName();
    G4String PostName = PostVolume->GetName();
    // For simplicity of using long lines
    const G4DynamicParticle *aParticle = aTrack->GetDynamicParticle();

    // Handling only optical photons
    if (aParticle->GetDefinition()->GetParticleName() != "opticalphoton")
    return false;


    // Vectors of sector's and detector's names splitted into words
    std::vector<G4String> sectorWords;
    std::vector<G4String> detectorWords;

    // Splitting a string into words
    splitName(PreName, sectorWords);
    splitName(PostName, detectorWords);


    // // Sector ID discrimination for the hit
    // if (sectorWords[0] == "sector" && detectorWords[0] == "detector") {
    //   G4int stationID = atoi(detectorWords[2]);
    //   _eventAction->InsertPhoton(stationID);
    // }

    if (PreName == "window" && PostName == "detector") {
        // G4int stationID = atoi(detectorWords[2]);
        _eventAction->InsertPhoton(0);
        aTrack->SetTrackStatus(fStopAndKill);
    } else return false;


    return true;
}

void L_SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{}
