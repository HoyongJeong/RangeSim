#ifndef RSPRIGENACT_h
#define RSPRIGENACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSPriGenAct.hh                                                           //
//                                                                            //
//   This file is a header for RSPriGenAct class. You can set primary beam    //
// options in this class.                                                     //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"

#include "RSConMan.hh"

class G4ParticleGun;

class RSConMan;

class RSPriGenAct: public G4VUserPrimaryGeneratorAction
{
  public:
	RSPriGenAct(RSConMan* CM);
	~RSPriGenAct();

	virtual void GeneratePrimaries(G4Event* anEvent);

  private:
	RSConMan* m_CM;

	G4ParticleGun*   m_PG;
	G4ParticleTable* m_PT;
	G4ParticleDefinition* m_Par;

	G4int    m_BeamPar;
	G4double m_WorldZ;
	G4double m_KinEgy;
	G4ThreeVector m_GunPos;
	G4ThreeVector m_MomDir;
};

#endif
