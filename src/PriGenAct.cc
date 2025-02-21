////////////////////////////////////////////////////////////////////////////////
//   PriGenAct.cc
//
//   Definitions of PriGenAct class's member functions.
//
//                        - Feb 5th 2025, Hoyong Jeong (hoyong5419@korea.ac.kr)
////////////////////////////////////////////////////////////////////////////////



#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "PriGenAct.hh"



PriGenAct::PriGenAct()
{
	PG = new G4ParticleGun();

	//------------------------------------------------
	// Set particle definition
	//------------------------------------------------
	G4ParticleTable* PT = G4ParticleTable::GetParticleTable();
	par = PT -> FindParticle("proton");
	PG -> SetParticleDefinition(par);


	//------------------------------------------------
	// Momentum
	//------------------------------------------------
	momDir = G4ThreeVector(0., 0., 1.);
	PG -> SetParticleMomentumDirection(momDir);
	PG -> SetParticleEnergy(200.0 * MeV);


	//------------------------------------------------
	// Polarization: up
	//------------------------------------------------
	pol = G4ThreeVector(0.0, 1.0, 0.0);
	PG -> SetParticlePolarization(pol);
}



PriGenAct::~PriGenAct()
{
	delete PG;
}



void PriGenAct::GeneratePrimaries(G4Event* anEvent)
{
	//------------------------------------------------
	// Beam position
	//------------------------------------------------
	G4double x = ( 1. * G4UniformRand() -   .5) * mm;
	G4double y = (30. * G4UniformRand() - 15. ) * mm;
	G4cout << "x = " << x << ", y = " << y << G4endl; 


	//------------------------------------------------
	// Gun position
	//------------------------------------------------
	gunPos = G4ThreeVector(x, y, - 3000. * mm);
	PG -> SetParticlePosition(gunPos);


	//------------------------------------------------
	// Shoot
	//------------------------------------------------
	PG -> GeneratePrimaryVertex(anEvent);
}
