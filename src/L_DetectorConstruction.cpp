/*
 * L_DetectorConstruction.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#include "L_DetectorConstruction.h"


L_DetectorConstruction::L_DetectorConstruction() {
  // DefineMaterials();
}

L_DetectorConstruction::~L_DetectorConstruction() {

}

G4VPhysicalVolume* L_DetectorConstruction::Construct() {
  DefineMaterials();

  return DefineVolumes();
}

void L_DetectorConstruction::ConstructSDandField() {
  LSD = new L_SensitiveDetector("LSD", _eventAction);
  G4SDManager::GetSDMpointer()->AddNewDetector(LSD);

  detectorLogical->SetSensitiveDetector(LSD);
  windowLogical->SetSensitiveDetector(LSD);
  //    L2PlaneLogInner->SetSensitiveDetector(LSD);
  //    L1PlaneLogOuter->SetSensitiveDetector(LSD);
  //    L2PlaneLogOuter->SetSensitiveDetector(LSD);


  //    G4cout << "_____________________________________________Detectors are made" << G4endl;
}

// Defining materials
void L_DetectorConstruction::DefineMaterials() {
  G4String symbol;
  G4double a, z, density;
  G4int ncomponents, natoms;
  G4double fractionmass;

  G4NistManager* man = G4NistManager::Instance();

  G4Element* H =
  new G4Element("Hydrogen", symbol = "H", z = 1., a = 1.01*g/mole);
  G4Element* C =
  new G4Element("Carbon", symbol = "C", z = 6., a = 12.01*g/mole);
  G4Element* N =
  new G4Element("Nitrogen", symbol = "N", z = 7., a = 14.01*g/mole);
  G4Element* O =
  new G4Element("Oxygen", symbol = "O", z = 8., a = 16.00*g/mole);
  G4Element* Si =
  new G4Element("Silicon", symbol = "Si", z = 14., a = 28.09*g/mole);
  G4Element* Ni =
  new G4Element("Nickel", symbol = "Ni", z = 28., a = 58.69*g/mole);
  G4Element* Fe =
  new G4Element("Iron", symbol = "Fe", z = 26., a = 55.85*g/mole);

  Al  = man->FindOrBuildMaterial("G4_Al");

  Air =
  new G4Material("Air", density = 0.000290*mg/cm3, ncomponents = 2);

  Air->AddElement(N, fractionmass = 0.7);
  Air->AddElement(O, fractionmass = 0.3);
  worldMaterial = Air;

  Steel =
  new G4Material("Steel", density = 7.750*g/cm3, ncomponents = 2);

  Steel->AddElement(Fe, fractionmass = 0.98);
  Steel->AddElement(C, fractionmass = 0.02);

  Permalloy =
  new G4Material("Permalloy", density = 8.74*g/cm3, ncomponents = 2);

  Permalloy->AddElement(Ni, fractionmass = 0.8);
  Permalloy->AddMaterial(Steel, fractionmass = 0.2);

  G4Material* Scint = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  ScintMaterial = Scint;

  INOX = man->FindOrBuildMaterial("G4_STAINLESS-STEEL");

  Beryllium = man->FindOrBuildMaterial("G4_Be");
  Copper = man->FindOrBuildMaterial("G4_Cu");

  BPMaterial = Copper;
  //    BPMaterial = Beryllium;


  Vacuum = new G4Material(
    "Galactic", z=1., a=1.01*g/mole, density= universe_mean_density,
    kStateGas, 2.73*kelvin, 3.e-18*pascal
  );

  // Quartz Material (SiO2)
  SiO2 =
  new G4Material("quartz", density = 2.200*g/cm3, ncomponents = 2);
  SiO2->AddElement(Si, natoms = 1);
  SiO2->AddElement(O , natoms = 2);

  // PolyEtherEtherKetone - Coating Material (C19H13O3)
  Peek =
  new G4Material("PEEK", density = 1.32*g/cm3, ncomponents = 3);
  Peek->AddElement(H, natoms = 13);
  Peek->AddElement(C, natoms = 19);
  Peek->AddElement(O, natoms = 3);

  //
  // Generate and Add Material Properties Table
  //
  //    const G4int num = 36;
  const G4int num = 50;
  G4double WaveLength[num];
  G4double Absorption[num];      // Default value for absorption
  G4double AirAbsorption[num];
  G4double AirRefractiveIndex[num];
  G4double PhotonEnergy[num];

  // Absorption of Peek
  G4double PeekAbsorption[num];

  // Absorption of Aluminium
  G4double AluminiumAbsorption[num];

  // Absorption of Aluminium
  G4double PermalloyAbsorption[num];

  // Absorption of quartz per 1m
  G4double QuartzAbsorption[num] =
  {
    0.999572036,0.999572036,0.999572036,0.999572036,0.999572036,
    0.999544661,0.999515062,0.999483019,0.999448285,0.999410586,
    0.999369611,0.999325013,0.999276402,0.999223336,0.999165317,
    0.999101778,0.999032079,0.998955488,0.998871172,0.998778177,
    0.998675410,0.998561611,0.998435332,0.998294892,0.998138345,
    0.997963425,0.997767484,0.997547418,0.997299580,0.997019660,
    0.996702550,0.996342167,0.995931242,0.995461041,0.994921022,
    0.994298396,0.993577567,0.992739402,0.991760297,0.990610945,
    0.990610945,0.990610945,0.990610945,0.990610945,0.990610945,
    0.990610945,0.990610945,0.990610945,0.990610945,0.990610945
  };

  for (int i=0; i<num; i++) {
    WaveLength[i] = (200 + i*10)*nanometer;
    Absorption[i] = 100*m;      // Fake number for no absorption
    AirAbsorption[i] = 10.*m;   // If photon hits air, kill it
    AirRefractiveIndex[i] = 1.; // Rough air refraction
    PhotonEnergy[num - (i+1)] = twopi*hbarc/WaveLength[i];
    /* Absorption is given per length and G4 needs mean free path
    length, calculate it here
    mean free path length - taken as probablility equal 1/e
    that the photon will be absorbed */

    QuartzAbsorption[i] = (-1)/log(QuartzAbsorption[i])*100*cm;
    // QuartzAbsorption[i] = 10*cm;

    PeekAbsorption[i] = 0.01*mm;
    AluminiumAbsorption[i] = 0.01*mm;
    PermalloyAbsorption[i] = 0.01*mm;
  }

  G4double QuartzRefractiveIndex[num] =
  {
    1.455524, 1.455764, 1.456011, 1.456268, 1.456535, 1.456812,
    1.457100, 1.457399, 1.457712, 1.458038, 1.458378, 1.458735,
    1.459108, 1.459500, 1.459911, 1.460344, 1.460799, 1.461280,
    1.461789, 1.462326, 1.462897, 1.463502, 1.464146, 1.464833,
    1.465566, 1.466350, 1.467190, 1.468094, 1.469066, 1.470116,
    1.471252, 1.472485, 1.473826, 1.475289, 1.476891, 1.478651,
    1.480592, 1.482739, 1.485127, 1.487793, 1.490786, 1.494164,
    1.498000, 1.502388, 1.507446, 1.513328, 1.520237, 1.528452,
    1.538358, 1.550506
  };

  G4double PeekRefractiveIndex[num] =
  {
    2.522612251, 2.340513622, 2.22644993, 2.147598081, 2.089593646,
    2.045054001, 2.009759064, 1.981106048, 1.957395212, 1.937465894,
    1.920496644, 1.905888744, 1.893194965, 1.882074202, 1.872261595,
    1.863548263, 1.855767211, 1.848783311, 1.842486044, 1.836784141,
    1.831601573, 1.826874508, 1.822548964, 1.818578995, 1.814925252,
    1.811553852, 1.808435466, 1.805544586, 1.802858928, 1.800358946,
    1.798027425, 1.79584915, 1.793810627, 1.79189985, 1.790106105,
    1.788419801, 1.786832332, 1.785335953, 1.783923679, 1.782589194,
    1.781326776, 1.780131229, 1.778997823, 1.777922249, 1.77690057,
    1.775929183, 1.775004787, 1.774124352, 1.773285089, 1.772484434
  };

  G4double AluminiumRefractiveIndex[num] =
  {
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978, 1.1978, 1.1978, 1.1978, 1.1978,
    1.1978, 1.1978
  };

  G4double PermalloyRefractiveIndex[num] =
  {
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306, 2.4306, 2.4306, 2.4306, 2.4306,
    2.4306, 2.4306
  };

  // Assign absorption and refraction to materials

  // Quartz
  G4MaterialPropertiesTable* QuartzMPT = new G4MaterialPropertiesTable();
  QuartzMPT->AddProperty("RINDEX", PhotonEnergy, QuartzRefractiveIndex, num);
  QuartzMPT->AddProperty("ABSLENGTH", PhotonEnergy, QuartzAbsorption, num);

  SiO2->SetMaterialPropertiesTable(QuartzMPT);

  // Air
  G4MaterialPropertiesTable* AirMPT = new G4MaterialPropertiesTable();
  AirMPT->AddProperty("RINDEX", PhotonEnergy, AirRefractiveIndex, num);
  AirMPT->AddProperty("ABSLENGTH", PhotonEnergy, AirAbsorption, num);

  // Assign these properties to the world volume
  Air->SetMaterialPropertiesTable(AirMPT);
  // In our rough assumption
  Vacuum->SetMaterialPropertiesTable(AirMPT);

  // Peek
  G4MaterialPropertiesTable* PeekMPT = new G4MaterialPropertiesTable();
  PeekMPT->AddProperty("RINDEX", PhotonEnergy, PeekRefractiveIndex, num);
  PeekMPT->AddProperty("ABSLENGTH", PhotonEnergy, PeekAbsorption, num);

  Peek->SetMaterialPropertiesTable(PeekMPT);

  // Aluminium
  G4MaterialPropertiesTable*AluminiumMPT = new G4MaterialPropertiesTable();
 AluminiumMPT->AddProperty("RINDEX", PhotonEnergy,AluminiumRefractiveIndex, num);
 AluminiumMPT->AddProperty("ABSLENGTH", PhotonEnergy,AluminiumAbsorption, num);

 Al->SetMaterialPropertiesTable(AluminiumMPT);

 // Permalloy
 G4MaterialPropertiesTable* PermalloyMPT = new G4MaterialPropertiesTable();
 PermalloyMPT->AddProperty("RINDEX", PhotonEnergy, PermalloyRefractiveIndex, num);
 PermalloyMPT->AddProperty("ABSLENGTH", PhotonEnergy, PermalloyAbsorption, num);

 Permalloy->SetMaterialPropertiesTable(PermalloyMPT);
}

G4VPhysicalVolume* L_DetectorConstruction::DefineVolumes(){

  //////////////////////// World /////////////////////////////
  G4VSolid *worldSolid = new G4Box(
    "World",
    LConst::worldSizeX/2,
    LConst::worldSizeY/2,
    LConst::worldSizeZ/2
  );

  worldLogical = new G4LogicalVolume(
    worldSolid,
    Vacuum /*Air*/, // worldMaterial,
    "World"
  );

  G4VPhysicalVolume *worldPhysical = new G4PVPlacement(
    0,
    G4ThreeVector(),
    worldLogical,
    "World",
    0,
    false,
    0
  );
  ///////////////////////////////////////////////////////////

  G4VSolid *pmt_win_solid = new G4Tubs(
    "window",
    0.,
    pmt_window.radius,
    pmt_window.thickness / 2.,
    0.,
    twopi
  );

  G4VSolid *bar_solid = new G4Tubs(
    "sector",
    0.,
    tablet.radius,
    tablet.thickness / 2.,
    0.,
    twopi
  );

  ////////////////////////////////////////////////////////////

  ///////////// Photon detector at the surface ///////////////

  G4VSolid *photon_detector_solid = new G4Tubs(
    "sector",
    0.,
    pmt_detector.radius,
    pmt_detector.thickness / 2.,
    0.,
    twopi
  );

  ////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////

  ///////////// Coating Solids ///////////////

  G4VSolid *envelope_solid = new G4Tubs(
    "sector",
    light_envelope.innerRadius,
    light_envelope.outerRadius,
    light_envelope.thickness / 2.,
    0.,
    twopi
  );

  G4VSolid *shield_solid = new G4Tubs(
    "sector",
    magnetic_shield.innerRadius,
    magnetic_shield.outerRadius,
    magnetic_shield.thickness / 2.,
    0.,
    twopi
  );

  ///////////// Socket Solids Construction ///////////////

  G4VSolid *socket_tube_1 = new G4Tubs(
    "sector",
    cylindrical_socket.innerRadius_1,
    cylindrical_socket.outerRadius_1,
    cylindrical_socket.thickness_1 / 2.,
    0.,
    twopi
  );

  G4VSolid *socket_tube_2 = new G4Tubs(
    "sector",
    cylindrical_socket.innerRadius_2,
    cylindrical_socket.outerRadius_2,
    cylindrical_socket.thickness_2 / 2.,
    0.,
    twopi
  );

  G4VSolid *socket_tube_3 = new G4Tubs(
    "sector",
    cylindrical_socket.innerRadius_3,
    cylindrical_socket.outerRadius_3,
    cylindrical_socket.thickness_3 / 2.,
    0.,
    twopi
  );

  G4VSolid *socket_tube_4 = new G4Tubs(
    "sector",
    cylindrical_socket.innerRadius_4,
    cylindrical_socket.outerRadius_4,
    cylindrical_socket.thickness_4 / 2.,
    0.,
    twopi
  );

  G4VSolid *socket_tube_5 = new G4Tubs(
    "sector",
    cylindrical_socket.innerRadius_5,
    cylindrical_socket.outerRadius_5,
    cylindrical_socket.thickness_5 / 2.,
    0.,
    twopi
  );

  //--------------------------------------------------------//

  G4VSolid *socket_solid_1 = new G4UnionSolid(
    "Union Solid 1",
    socket_tube_1,
    socket_tube_2,
    0,
    G4ThreeVector(
      0,
      0,
      (cylindrical_socket.thickness_1 - cylindrical_socket.thickness_2)/2
    )
  );

  G4VSolid *socket_solid_2 = new G4UnionSolid(
    "Union Solid 2",
    socket_solid_1,
    socket_tube_3,
    0,
    G4ThreeVector(
      0,
      0,
      (cylindrical_socket.thickness_1 - cylindrical_socket.thickness_3)/2
    )
  );

  G4VSolid *socket_solid_3 = new G4UnionSolid(
    "Union Solid 3",
    socket_solid_2,
    socket_tube_4,
    0,
    G4ThreeVector(
      0,
      0,
      (cylindrical_socket.thickness_1 - cylindrical_socket.thickness_4)/2
    )
  );

  G4VSolid *socket_solid = new G4UnionSolid(
    "Union Solid",
    socket_solid_3,
    socket_tube_5,
    0,
    G4ThreeVector(
      0,
      0,
      (cylindrical_socket.thickness_1 - cylindrical_socket.thickness_5)/2
    )
  );

  ////////////////////////////////////////////////////////////


  tabletLogical   =  new G4LogicalVolume(bar_solid, SiO2, "tablet");
  windowLogical   =  new G4LogicalVolume(pmt_win_solid, SiO2, "window");
  detectorLogical =  new G4LogicalVolume(photon_detector_solid, SiO2, "detector");
  envelopeLogical =  new G4LogicalVolume(envelope_solid, Peek, "envelope");
  shieldLogical =  new G4LogicalVolume(shield_solid, Permalloy, "shield");
  socketLogical =  new G4LogicalVolume(socket_solid, Peek, "socket");
  // detectorLogical->SetSensitiveDetector(LSD);
  // windowLogical->SetSensitiveDetector(LSD);

  //---------------- First Module ------------------------------------------/

  G4VPhysicalVolume *tabletPhysical = new G4PVPlacement(
    0,
    G4ThreeVector(),
    tabletLogical,
    "tablet1",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *windowPhysical = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., -(tablet.thickness + pmt_window.thickness) / 2.),
    windowLogical,
    "window1",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *detectorPhysical = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., - pmt_window.thickness - (tablet.thickness + pmt_detector.thickness) / 2.),
    detectorLogical,
    "detector1",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *envelopePhysical = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., - light_envelope.z_pos),
    envelopeLogical,
    "envelope1",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *shieldPhysical = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., - magnetic_shield.z_pos),
    shieldLogical,
    "shield1",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *socketPhysical = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., - cylindrical_socket.z_pos),
    socketLogical,
    "socket1",
    worldLogical,
    false,
    0
  );

  /*
  //---------------- Second Module ------------------------------------------/

  G4VPhysicalVolume *tabletPhysical_2 = new G4PVPlacement(
    0,
    G4ThreeVector(0., 0., -220.*mm),
    tabletLogical,
    "tablet2",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *windowPhysical_2 = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., -220.*mm -(tablet.thickness + pmt_window.thickness) / 2.),
    windowLogical,
    "window2",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *detectorPhysical_2 = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., -220.*mm - pmt_window.thickness - (tablet.thickness + pmt_detector.thickness) / 2.),
    detectorLogical,
    "detector2",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *envelopePhysical_2 = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., -220.*mm - light_envelope.z_pos),
    envelopeLogical,
    "envelope2",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *shieldPhysical_2 = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., -220.*mm - magnetic_shield.z_pos),
    shieldLogical,
    "shield2",
    worldLogical,
    false,
    0
  );

  G4VPhysicalVolume *socketPhysical_2 = new G4PVPlacement(
    0,
    G4ThreeVector(0.,0., -220.*mm - cylindrical_socket.z_pos),
    socketLogical,
    "socket2",
    worldLogical,
    false,
    0
  );

  */


  DefineOpticalBorders();



  G4cout << "_____________________________________________Volumes are made" << G4endl;
  return worldPhysical;
}


// Definition of absorbtion surfaces
void L_DetectorConstruction::DefineOpticalBorders()
{
  const G4int num1 = 2;
  G4double Ephoton[num1] = {1.7*eV, 6.2*eV};

  G4OpticalSurface* OpVolumeKillSurface =
  new G4OpticalSurface("VolumeKillSurface");
  OpVolumeKillSurface->SetType(dielectric_dielectric);
  OpVolumeKillSurface->SetFinish(polished);
  OpVolumeKillSurface->SetModel(glisur);

  G4double ReflectivityKill[num1] = {0., 0.};
  G4double EfficiencyKill[num1] = {1., 1.};
  G4MaterialPropertiesTable* VolumeKill = new G4MaterialPropertiesTable();
  VolumeKill->AddProperty("REFLECTIVITY", Ephoton, ReflectivityKill, num1);
  VolumeKill->AddProperty("EFFICIENCY",   Ephoton, EfficiencyKill,   num1);
  OpVolumeKillSurface->SetMaterialPropertiesTable(VolumeKill);

  G4OpticalSurface* quartzSurface = new G4OpticalSurface("quartzBorder");
  quartzSurface->SetFinish(polished);
  quartzSurface->SetType(dielectric_dielectric);

  G4OpticalSurface* peekSurface = new G4OpticalSurface("peekBorder");
  peekSurface->SetFinish(polished);
  //peekSurface->SetType(dielectric_dielectric);

  G4OpticalSurface* permalloySurface = new G4OpticalSurface("permalloyBorder");
  permalloySurface->SetFinish(polished);
  //permalloySurface->SetType(dielectric_dielectric);

  G4OpticalSurface* alluminiumSurface = new G4OpticalSurface("alluminiumBorder");
  alluminiumSurface->SetFinish(polished);
  //alluminiumSurface->SetType(dielectric_dielectric);

  new G4LogicalSkinSurface(
    "DetectorAbsSurface",
    detectorLogical, OpVolumeKillSurface
  );
  new G4LogicalSkinSurface(
    "sectorSurface",
    windowLogical, quartzSurface
  );
  new G4LogicalSkinSurface(
    "tabletSurface",
    tabletLogical, quartzSurface
  );
  new G4LogicalSkinSurface(
    "envelopeSurface",
    envelopeLogical, peekSurface
  );
  new G4LogicalSkinSurface(
    "shieldSurface",
    shieldLogical, permalloySurface
  );
  new G4LogicalSkinSurface(
    "socketSurface",
    socketLogical, alluminiumSurface
  );



}

// Visual attributes
void L_DetectorConstruction::SetVisAttributes() {

  G4Color blue        = G4Color(0., 0., 1.);
  G4Color green       = G4Color(0., 1., 0.);
  G4Color red         = G4Color(1., 0., 0.);
  G4Color white       = G4Color(1., 1., 1.);
  G4Color cyan        = G4Color(0., 1., 1.);
  G4Color DircColor   = G4Color(0.0, 0.0, 1.0, 0.2);
  G4Color SensColor   = G4Color(0.0, 1.0, 1.0, 0.1);

  G4VisAttributes *sectorVisAtt = new G4VisAttributes;
  sectorVisAtt->SetColor(green);
  sectorVisAtt->SetVisibility(true);
  for (int j = 0; j < LConst::pmt_n_channels*2; ++j) {
    LWindowOut[j]->SetVisAttributes(sectorVisAtt);
  }
}
