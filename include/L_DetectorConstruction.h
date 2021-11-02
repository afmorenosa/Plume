/*
 * H_DetectorConstruction.h
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#pragma once

#include <G4VUserDetectorConstruction.hh>
#include "L_SensitiveDetector.h"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Sphere.hh"
#include "G4ExtrudedSolid.hh"
#include "G4VSolid.hh"
#include "G4UnionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisAttributes.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Color.hh"
#include "G4TwoVector.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4LogicalBorderSurface.hh"

#include "LConst.hh"
#include "L_VolumeStructures.h"
#include "L_EventAction.h"

class L_DetectorConstruction: public G4VUserDetectorConstruction {
public:
  L_DetectorConstruction();
  virtual ~L_DetectorConstruction();

public:
  G4VPhysicalVolume* Construct();
  void ConstructSDandField();
  void DefineOpticalBorders();
  void SetVisAttributes();

  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();
  L_SensitiveDetector *LSD;

  // TrapezeSectorStructOut sectorOut;
  PMT_tablet tablet;

  PMT_window pmt_window;
  PMT_detector pmt_detector;

  PMT_coating coating;

  G4LogicalVolume *LWindowOut[LConst::pmt_n_channels*2];
  G4LogicalVolume *LBarOut[LConst::pmt_n_channels*2];

  G4LogicalVolume *LDetectorOut[LConst::pmt_n_channels*2];

  G4LogicalVolume *worldLogical;
  G4LogicalVolume *detectorLogical;
  G4LogicalVolume *tabletLogical;
  G4LogicalVolume *windowLogical;
  G4LogicalVolume *coatingLogical;

  inline void SetEventAction(L_EventAction* evAct){ _eventAction = evAct; };

private:
  G4Material *worldMaterial;
  G4Material *ScintMaterial;
  G4Material *Vacuum;
  G4Material *BPMaterial;
  G4Material *INOX;
  G4Material *SiO2;
  G4Material *Copper;
  G4Material *Beryllium;
  G4Material *Peek;

  G4Material *Air;

  L_EventAction *_eventAction;

};
