/*
 * L_SteppingAction.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#include "L_SteppingAction.h"
#include "L_SensitiveDetector.h"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4SDManager.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

L_SteppingAction::L_SteppingAction(
  L_PrimaryGeneratorAction *genAction
) : _genAction(genAction){
    Reset();
    ResetPerEvent();
}

L_SteppingAction::~L_SteppingAction() {
}

void L_SteppingAction::SetEventAction(L_EventAction *eventAction) {
  _eventAction = eventAction;
}

void L_SteppingAction::UserSteppingAction(const G4Step* aStep) {
    //	G4cout << "_____________________________ step" << G4endl;
    G4Track* aTrack = aStep->GetTrack();
    // G4Track *aTrack = aStep->GetTrack();
    G4int trackID = aTrack->GetTrackID();
    //G4cout<<"trackID = "<<trackID<<G4endl;


    // Pre step point and physical volume
    G4StepPoint* aPrePoint = aStep->GetPreStepPoint();
    G4VPhysicalVolume* aPrePV = aPrePoint->GetPhysicalVolume();

    // Post step point and physical volume
    G4StepPoint* aPostPoint = aStep->GetPostStepPoint();
    G4VPhysicalVolume* aPostPV = aPostPoint->GetPhysicalVolume();


    // Further operations are only for optical photons
    G4ParticleDefinition* particleType = aTrack->GetDefinition();


    if (particleType->GetParticleName() == "e-")
    SecondModuleElectrons(aPrePoint, aPostPoint, aTrack);


    if (particleType != G4OpticalPhoton::OpticalPhotonDefinition())
        return;

    // Check if particle trying to escape the World
    if (!aPostPV) return;

    // TO BE REVIEWED, GONNA BE A MISTAKE HERE///////////////////////////////
//    if(!aPostPV->GetLogicalVolume()->GetSensitiveDetector()) return;
    ////////////////////////////////////////////////////////////////////////

    // Killing downstream particles
    if (aPrePoint->GetPosition().z() > 50.*cm) {
        aTrack->SetTrackStatus(fStopAndKill);
        return;
    }

    // Killing charged particles bellow 20 MeV
    if (aPrePoint->GetCharge() != 0. && aPrePoint->GetMomentum().mag() < 20.*MeV ) {
        aTrack->SetTrackStatus(fStopAndKill);
        return;
    }

    // Getting probability of internal reflection
    if (_particleID != trackID) {
        Reset();
        _particleID = trackID;
        InternalReflectionProbability(aTrack->GetTotalEnergy()/eV,
                                      _probOfReflection);
    }

    // Declaring boundary
    G4OpBoundaryProcessStatus boundaryStatus = Undefined;
    static G4OpBoundaryProcess* boundary = NULL;

    // Find boundary process
    if (!boundary) {
        G4ProcessManager* pm =
                aStep->GetTrack()->GetDefinition()->GetProcessManager();
        G4int nprocesses = pm->GetProcessListLength();
        G4ProcessVector* pv = pm->GetProcessList();
        for (G4int i = 0; i < nprocesses; i++) {
            if ((*pv)[i]->GetProcessName() == "OpBoundary") {
                boundary = (G4OpBoundaryProcess*)(*pv)[i];
                break;
            }
        }
    }

    // Only boundary processes are handling further
    if (!boundary) return;

    boundaryStatus = boundary->GetStatus();

    if (aPostPoint->GetStepStatus() == fGeomBoundary) {
        G4String sdName = "LSD";
        G4double flat = G4UniformRand();
        switch(boundaryStatus) {
        case Absorption:
            break;
        case FresnelReflection:
            // Reflections of surfaces of different media
            if (aPrePV->GetLogicalVolume()->GetName() == "tablet")
            _eventAction->InsertPhotonReflection();
            break;
        case TotalInternalReflection:
            // Actually check if particle is reflected
            if (flat > _probOfReflection) {
                G4Track* aNonConstTrack = const_cast<G4Track*>(aTrack);
                aNonConstTrack->SetTrackStatus(fStopAndKill);
//                G4cout << "KILL THAT BASTARD \n";
            }
            //            G4cout << "TOTAL INTERNAL REFLECTION"<< G4endl;
            if (aPrePV->GetLogicalVolume()->GetName() == "tablet")
            _eventAction->InsertPhotonReflection();
            break;
        case SpikeReflection:
          if (aPrePV->GetLogicalVolume()->GetName() == "tablet")
          _eventAction->InsertPhotonReflection();
            break;
        default:
            break;

        }

    }


    return;
}
void L_SteppingAction::ResetPerEvent(){

}

void L_SteppingAction::Reset()
{
    _probOfReflection = 1.;
    _particleID = 0.;
}

// This metod is stolen from Leonid's code
void L_SteppingAction::InternalReflectionProbability(G4double energy,
                                                     G4double& probability)
{
    probability = 1.0;

    /* this function simulate the internal reflection probability per one
     bounce - each time photon bounced this function is called
     and the reflection is tested if photon reflects or disappear -
     this function estimates loss of photons during imperfections
     of bar */

    G4double opticalPhotonEnergy[36] = {
        1.90744901082931,1.93725290162352,1.96800294768103,1.99974493070815,
        2.03252763449025,2.06640309506508,2.10142687633737,2.13765837420526,
        2.17516115270009,2.21400331614116,2.25425792188918,2.29600343896121,
        2.33932425856425,2.38431126353664,2.43106246478245,2.4796837140781,
        2.53028950416133,2.58300386883136,2.63796139795543,2.6953083848675,
        2.75520412675345,2.81782240236148,2.88335315590477,2.95200442152155,
        3.02400452936354,3.09960464259763,3.17908168471551,3.26274172905013,
        3.35092393794338,3.44400515844181,3.54240530582586,3.64659369717368,
        3.75709653648197,3.87450580324703,3.99948986141629,4.13280619013017};

    G4double internalReflectivity[36] = {
        0.999895281,0.999891334,0.999885743,0.999878696,0.999870426,
        0.9998612,0.999851309,0.999841055,0.999830735,0.999820635,0.999811012,
        0.999802084,0.999794018,0.999786917,0.999780807,0.999775625,
        0.999771209,0.999767282,0.999763441,0.999759146,0.999753706,
        0.999746266,0.999735798,0.999721084,0.999700708,0.99967304,
        0.999636227,0.999588178,0.999526552,0.999448747,0.999351887,
        0.999232808,0.99908805,0.998913839,0.998706078,0.998460335};

    G4int i;
    for(i = 0; i < 36;i++) {
        if(energy < opticalPhotonEnergy[i]) break;
    }


    probability = ((energy-opticalPhotonEnergy[i-1])/
            (opticalPhotonEnergy[i]-opticalPhotonEnergy[i-1]))*
            (internalReflectivity[i]-internalReflectivity[i-1]) +
            internalReflectivity[i-1];

    /* because the ratio between peak1 and peak2 did not correspond,
     the reflection probability was change to get the same
     ration 2.1:1 => the original probability is multiplied by .9992 */
    probability = probability*.9992;


    // probability = 0;
}

void L_SteppingAction::SecondModuleElectrons(
  G4StepPoint *PrePoint,
  G4StepPoint *PostPoint,
  G4Track *track
) {

  if (!PrePoint->GetPhysicalVolume()) return;
  if (!PostPoint->GetPhysicalVolume()) return;

  G4String PrePVname = PrePoint->GetPhysicalVolume()->GetName();
  G4String PostPVname = PostPoint->GetPhysicalVolume()->GetName();

  if (
    PrePVname == "World" &&
    PostPVname == "tablet2"
  ) {
    if (track->GetTrackID() == 1) {
      _eventAction->ElectronPositionReach(
        PrePoint->GetPosition(), PostPoint->GetPosition()
      );
      _eventAction->ElectronEnergyReach(
        PrePoint->GetTotalEnergy(), PostPoint->GetTotalEnergy()
      );
    } else {
      _eventAction->InsertSecondModuleElectron();
    }
  }
}
