#pragma once

//G4
#include "G4Material.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Point3D.hh"
#include "G4TwoVector.hh"
#include "globals.hh"

#include "TMath.h"

//My
#include "LConst.hh"

// Base structure
struct VolumeStruct {
    G4Material*        material;
    G4VSolid*          solid;
    G4LogicalVolume*   logical;
    G4VPhysicalVolume* physical;
    VolumeStruct() :
        material(0),
        solid(0),
        logical(0),
        physical(0)
    {;}
    ~VolumeStruct() {;}
};

// Sector structure (inside beampipe)
struct TrapezeSectorStructIn: VolumeStruct {
    const G4double thickness;
    const G4double height;
    const G4double shortSide;
    const G4double longSide;
    const G4double angle;
    const G4double sides;
    const G4double middleLine;
    TrapezeSectorStructIn():
        thickness(LConst::sectorThicknessIn),
        height(LConst::outerRadIn * TMath::Cos(TMath::Pi() / LConst::nSecIn) -
               LConst::innerRadIn * TMath::Cos(TMath::Pi() / LConst::nSecIn)),
        shortSide(LConst::innerSideIn),
        longSide(LConst::outerSideIn),
        angle(atan((longSide-shortSide)/2./height)),
        sides(sqrt(height*height + (longSide-shortSide)*(longSide-shortSide)/4.)),
        middleLine((longSide+shortSide)/2.)
    {;}
};

// Sector structure (outside beampipe)
struct TrapezeSectorStructOut: VolumeStruct {
    const G4double thickness;
    const G4double height;
    const G4double shortSide;
    const G4double longSide;
    const G4double angle;
    const G4double sides;
    const G4double middleLine;
    TrapezeSectorStructOut():
        thickness(LConst::window_radius*2.),
        height(LConst::bar_length),
        shortSide(LConst::window_radius*2.),
        longSide(LConst::window_radius*2.),
        angle(atan((longSide-shortSide)/2./height)),
        sides(sqrt(height*height + (longSide-shortSide)*(longSide-shortSide)/4.)),
        middleLine((longSide+shortSide)/2.)
    {
        G4cout << "Short side: \t" << shortSide / mm << "\t mm" << G4endl;
        G4cout << "Long side: \t\t" << longSide / mm << "\t mm" << G4endl;
        G4cout << "Length: \t\t" << height / mm << "\t mm" << G4endl;

        G4cout << "Angle: \t\t" << LConst::angleOut / deg << "\t mm" << G4endl;
    }
};

// Optical insulation between sectors (inside beampipe)
struct TrapezeAbsStructIn: VolumeStruct {
    const G4double shortSide;
    const G4double longSide;
    const G4double thickness;
    const G4double height;
    const G4double angle;
    const G4double sides;
    const G4double middleLine;
    TrapezeAbsStructIn():
        shortSide(LConst::absInnerSideIn),
        longSide(LConst::absOuterSideIn),
        thickness(LConst::sectorThicknessIn),
        height(LConst::outerRadIn -
               LConst::innerRadIn),
        angle(atan((longSide-shortSide)/2./height)),
        sides(sqrt(height*height + (longSide-shortSide)*(longSide-shortSide)/4.)),
        middleLine((longSide+shortSide)/2.)
    {;}
};

// Optical insulation between sectors (outside beampipe)
struct TrapezeAbsStructOut: VolumeStruct {
    const G4double shortSide;
    const G4double longSide;
    const G4double thickness;
    const G4double height;
    const G4double angle;
    const G4double sides;
    const G4double middleLine;
    TrapezeAbsStructOut():
        shortSide(LConst::absInnerSideOut),
        longSide(LConst::absOuterSideOut),
        thickness(LConst::sectorThicknessOut * 1.2),
        height(LConst::lengthOut),
        angle(atan((longSide-shortSide)/2./height)),
        sides(sqrt(height*height + (longSide-shortSide)*(longSide-shortSide)/4.)),
        middleLine((longSide+shortSide)/2.)
    {;}
};

struct PMT_window: VolumeStruct {
    const G4double radius;
    const G4double thickness;
    PMT_window():
        radius(LConst::window_radius),
        thickness(LConst::window_thickness)
    {;}
};

struct PMT_tablet: VolumeStruct {
    const G4double radius;
    const G4double thickness;
    PMT_tablet():
        radius(LConst::window_radius),
        thickness(LConst::tablet_thickness)
    {;}
};


struct PMT_detector: VolumeStruct {
    const G4double radius;
    const G4double thickness;
    PMT_detector():
        radius(LConst::window_radius),
        thickness(LConst::pmt_detector_thickness)
    {;}
};

struct PMT_envelope: VolumeStruct {
    const G4double innerRadius;
    const G4double outerRadius;
    const G4double thickness;
    const G4double z_pos;
    PMT_envelope():
        innerRadius(LConst::envelope_inner_radius),
        outerRadius(LConst::envelope_outer_radius),
        thickness(LConst::envelope_thickness),
        z_pos(LConst::envelope_pos_z)
    {;}
};

struct PMT_shield: VolumeStruct {
  const G4double innerRadius;
  const G4double outerRadius;
  const G4double thickness;
  const G4double z_pos;
  PMT_shield():
      innerRadius(LConst::shield_inner_radius),
      outerRadius(LConst::shield_outer_radius),
      thickness(LConst::shield_thickness),
      z_pos(LConst::shield_pos_z)
  {;}
};

struct PMT_socket: VolumeStruct {
  const G4double innerRadius;
  const G4double outerRadius;
  const G4double thickness;
  const G4double z_pos;
  PMT_socket():
      innerRadius(LConst::socket_inner_radius),
      outerRadius(LConst::socket_outer_radius),
      thickness(LConst::socket_thickness),
      z_pos(LConst::socket_pos_z)
  {;}
};
