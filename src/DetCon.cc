////////////////////////////////////////////////////////////////////////////////
//   DetCon.cc
//
//   Definitions of DetCon class's member functions. And it describes geometry
// of simulation.
//
//                        - Feb 5th 2025, Hoyong Jeong (hoyong5419@korea.ac.kr)
////////////////////////////////////////////////////////////////////////////////



#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include "DetCon.hh"



DetCon::DetCon()
{
	ConstructMaterials();
	DefineDimensions();
}



DetCon::~DetCon()
{
	DestructMaterials();
}



void DetCon::DefineDimensions()
{
	//------------------------------------------------
	// World dimensions: Laboratory size
	//------------------------------------------------
	labX   = 6000.0 * mm; // World x dimension
	labY   = 6000.0 * mm; // World y dimension
	labZ   = 6000.0 * mm; // World z dimension


	//------------------------------------------------
	// Target dimensions (wire)
	//------------------------------------------------
	tarD   =    1.0 * mm; // Target diameter
	tarL   =   20.0 * mm; // Target length


	//------------------------------------------------
	// Detector dimensions
	//------------------------------------------------
	zp16   = 2100.0 * mm; // z distance of the 16deg polarimeter
	rp16   =  610.0 * mm; // r distance of the 16deg polarimeter
	tp16s0 =    4.0 * mm; // P16-S0 thickness
	wp16s0 =    6.0 * mm; // P16-S0 width
	lp16s0 =    6.0 * mm; // P16-S0 length
	tp16s1 =    9.5 * mm; // P16-S1 thickness
	wp16s1 =   10.0 * mm; // P16-S1 width
	lp16s1 =   10.0 * mm; // P16-S1 length
}



G4VPhysicalVolume* DetCon::Construct()
{
	//------------------------------------------------
	// World
	//------------------------------------------------
	G4Box* labSolid = new G4Box("labSolid", labX / 2., labY / 2., labZ / 2.);
	G4LogicalVolume* labLV = new G4LogicalVolume(labSolid, matAir, "labLV");
	labLV -> SetVisAttributes(new G4VisAttributes(0));
	G4VPhysicalVolume* labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);


	//------------------------------------------------
	// Target
	//------------------------------------------------
	tarSolid = new G4Tubs("target", 0., tarD / 2., tarL / 2., 0., 360. * degree);
	tarLV = new G4LogicalVolume(tarSolid, matGraphite, "tarLV");
	G4RotationMatrix* tarRot = new G4RotationMatrix();
	tarRot -> rotateX(- 90. * degree);
	new G4PVPlacement(tarRot, G4ThreeVector(0., 0., 0.), "tarPV", tarLV, labPV, false, 0);


	//------------------------------------------------
	// 16deg polarimeter
	//------------------------------------------------
	// p16s0
	p16s0Solid = new G4Box("p16s0Solid", lp16s0 / 2., wp16s0 / 2., tp16s0 / 2.);
	p16ls0LV = new G4LogicalVolume(p16s0Solid, matScint, "p16ls0LV");
	p16rs0LV = new G4LogicalVolume(p16s0Solid, matScint, "p16rs0LV");
	p16ls0LV -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	p16rs0LV -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	G4RotationMatrix* p16ls0Rot = new G4RotationMatrix();
	G4RotationMatrix* p16rs0Rot = new G4RotationMatrix();
	p16ls0Rot -> rotateY(- 16.2 * degree);
	p16rs0Rot -> rotateY(  16.2 * degree);
	p16ls0PV = new G4PVPlacement(p16ls0Rot, G4ThreeVector(  rp16, 0., zp16), "p16ls0PV", p16ls0LV, labPV, false, 0);
	p16rs0PV = new G4PVPlacement(p16rs0Rot, G4ThreeVector(- rp16, 0., zp16), "p16rs0PV", p16rs0LV, labPV, false, 0);

	// p16s1
	p16s1Solid = new G4Box("p16s1Solid", lp16s1 / 2., wp16s1 / 2., tp16s1 / 2.);
	p16ls1LV = new G4LogicalVolume(p16s1Solid, matScint, "p16ls1LV");
	p16rs1LV = new G4LogicalVolume(p16s1Solid, matScint, "p16rs1LV");
	p16ls1LV -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	p16rs1LV -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	new G4PVPlacement(0, G4ThreeVector(0., 0., 42.), "p16ls1PV", p16ls1LV, p16ls0PV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(0., 0., 42.), "p16rs1PV", p16rs1LV, p16rs0PV, false, 0);


	return labPV;
}



void DetCon::ConstructMaterials()
{
	const G4double labTemp = 300.0 * kelvin;

	elN  = new G4Element("Nitrogen",  "N",  7, 14.00674*g/mole);
	elO  = new G4Element(  "Oxygen",  "O",  8, 15.9994 *g/mole);
	elAr = new G4Element(   "Argon", "Ar", 18, 39.948  *g/mole);
	elC  = new G4Element(  "Carbon",  "C",  6, 12.011  *g/mole);
	elH  = new G4Element("Hydrogen",  "H",  1,  1.00794*g/mole);

	matAir = new G4Material("Air", 1.2929e-10*g/cm3, 3, kStateGas, labTemp);
	matAir -> AddElement(elN, 75.47/99.95);
	matAir -> AddElement(elO, 23.20/99.95);
	matAir -> AddElement(elAr, 1.28/99.95);

	matGraphite = new G4Material("Graphite", 1.7*g/cm3, 3, kStateSolid, labTemp);
	matGraphite -> AddElement(elC, 99.0/100.0);
	matGraphite -> AddElement(elN,  0.7/100.0);
	matGraphite -> AddElement(elO,  0.3/100.0);

	matScint = new G4Material("Scintillator", 1.032*g/cm3, 2, kStateSolid, labTemp);
	matScint -> AddElement(elC, 10);
	matScint -> AddElement(elH, 11);
}



void DetCon::DestructMaterials()
{
	delete matScint;
	delete matGraphite;
	delete matAir;

	delete elH;
	delete elC;
	delete elAr;
	delete elO;
	delete elN;
}
