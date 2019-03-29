////////////////////////////////////////////////////////////////////////////////
//   RSPriGenAct.cc                                                           //
//                                                                            //
//   Definitions of RSPriGenAct class's member functions.                     //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "RSPriGenAct.hh"

//////////////////////////////////////////////////
//   Constructor and destructor                 //
//////////////////////////////////////////////////
RSPriGenAct::RSPriGenAct(RSConMan* CM): m_CM(CM)
{
	m_PG = new G4ParticleGun();

	// Gun position
	m_WorldZ = m_CM -> GetWorldZ();

	// Set particle definition
	m_PT = G4ParticleTable::GetParticleTable();
	m_BeamPar = m_CM -> GetBeamPar();
	m_Par = m_PT -> FindParticle(m_BeamPar);
	m_PG -> SetParticleDefinition(m_Par);

	// Momentum
	m_MomDir = G4ThreeVector(0., 0., 1.);
	m_PG -> SetParticleMomentumDirection(m_MomDir);

	// Kinetic energy
	m_KinEgy = m_CM -> GetBeamKE();
	m_PG -> SetParticleEnergy(m_KinEgy);
}

RSPriGenAct::~RSPriGenAct()
{
	delete m_PG;
}

//////////////////////////////////////////////////
//   Shoot!                                     //
//////////////////////////////////////////////////
void RSPriGenAct::GeneratePrimaries(G4Event* anEvent)
{
	m_GunPos = G4ThreeVector(0., 0., - m_WorldZ / 2.);
	m_PG -> SetParticlePosition(m_GunPos);
	m_PG -> GeneratePrimaryVertex(anEvent);
}
