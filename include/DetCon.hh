////////////////////////////////////////////////////////////////////////////////
//   DetCon.hh
//
//   This file is a header for DetCon class. It's for construction of whole
// geometry of simulation, which includes detector geometry.
//
// - Author: Hoyong Jeong     (hoyong5419@korea.ac.kr)
//           Antonino Cannavo (acannavo@bnl.gov      )
////////////////////////////////////////////////////////////////////////////////



#ifndef DETCON_h
#define DETCON_h 1



#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"



class G4VPhysicalVolume;



class DetCon: public G4VUserDetectorConstruction
{
  public:
	DetCon();
	virtual  ~DetCon();
	virtual G4VPhysicalVolume* Construct();


  private:
	void DefineDimensions();
	void ConstructMaterials();
	void DestructMaterials();


	//------------------------------------------------
	// Materials
	//------------------------------------------------
	G4Element* elN;
	G4Element* elO;
	G4Element* elAr;
	G4Element* elC;
	G4Element* elH;

	G4Material* matAir;
	G4Material* matGraphite;
	G4Material* matScint;


	//------------------------------------------------
	// World
	//------------------------------------------------
	// Dimensions
	G4double labX, labY, labZ;


	//------------------------------------------------
	// Target
	//------------------------------------------------
	// Dimensions
	G4double tarD, tarL;

	// Geometry
	G4Tubs* tarSolid;
	G4LogicalVolume* tarLV;


	//------------------------------------------------
	// Polarimter
	//------------------------------------------------
	// Dimensions
	G4double zp16, rp16;
	G4double tp16s0, wp16s0, lp16s0;
	G4double tp16s1, wp16s1, lp16s1;

	// Geometry
	G4Box* p16s0Solid; 
	G4LogicalVolume* p16ls0LV; // 16deg polarimeter, left , scintillator 0
	G4LogicalVolume* p16rs0LV; // 16deg polarimeter, right, scintillator 0
	G4VPhysicalVolume* p16ls0PV;
	G4VPhysicalVolume* p16rs0PV;
	G4Box* p16s1Solid;
	G4LogicalVolume* p16ls1LV; // 16deg polarimeter, left , scintillator 1
	G4LogicalVolume* p16rs1LV; // 16deg polarimeter, right, scintillator 1
};



#endif
