////////////////////////////////////////////////////////////////////////////////
//   RSSteAct.cc                                                              //
//                                                                            //
//   Definitions of RSSteAct class's member functions. Details of user        //
// actions are here.                                                          //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

#include "RSSteAct.hh"
#include "RSEveAct.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
RSSteAct::RSSteAct(RSEveAct* EA): G4UserSteppingAction(), m_EA(EA)
{
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
RSSteAct::~RSSteAct()
{
}

//////////////////////////////////////////////////
//   User stepping action                       //
//////////////////////////////////////////////////
void RSSteAct::UserSteppingAction(const G4Step* step)
{
	// I wrote examples of some information which can be extracted from a step.
	// Uncomment whatever you want to use.

	// Who am I? Where am I? What am I undergoing?
	// // Track ID
	G4int trackID = step -> GetTrack() -> GetTrackID();
	// // Time
	G4double time = step -> GetTrack() -> GetGlobalTime();
	// // Particle name
//	G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();
	// // Particle ID
//	G4int parID = step -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
	// // Particle charge
//	G4int parCharge = step -> GetTrack() -> GetDefinition() -> GetPDGCharge();
	// // Process name
//	const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();
//	G4String procName = step -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
	// // Physical volume
	G4String namePrePV = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
//	G4String namePostPV;
//	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
//	if ( postPV != 0 ) namePostPV = postPV -> GetName();
//	else namePostPV = "outside";
	// // Status
//	G4StepStatus preStat = step -> GetPreStepPoint() -> GetStepStatus();
//	G4StepStatus postStat = step -> GetPostStepPoint() -> GetStepStatus();
	// // Position
	G4ThreeVector prePos = step -> GetPreStepPoint() -> GetPosition();
//	G4ThreeVector postPos = step -> GetPostStepPoint() -> GetPosition();
	G4ThreeVector deltaPos = step -> GetDeltaPosition();
	G4double length = deltaPos . mag();
	// // Momentum
//	G4ThreeVector preMom = step -> GetPreStepPoint() -> GetMomentum();
//	G4ThreeVector postMom = step -> GetPostStepPoint() -> GetMomentum();
	// // Kinetic energy
	G4double preKinEgy = step -> GetPreStepPoint() -> GetKineticEnergy();
//	G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();
	// // Energy deposition
	G4double eDep = step -> GetTotalEnergyDeposit();

	// Send information to the event action object.
	if ( namePrePV.contains("TarPV") )
	{
			m_EA -> AddEDep(eDep / MeV);
		if ( trackID == 1 ) // Primary
		{
			// Update final state
			m_EA -> AddPath(length / mm);
			m_EA -> SetPosXFinal(prePos.getX() / mm);
			m_EA -> SetPosYFinal(prePos.getY() / mm);
			m_EA -> SetPosZFinal(prePos.getZ() / mm);
			m_EA -> SetTimeFinal(time          / ns);

			// Add history
			m_EA -> AddEKinHistory(preKinEgy    / MeV);
			m_EA -> AddPosXHistory(prePos.getX() / mm);
			m_EA -> AddPosYHistory(prePos.getY() / mm);
			m_EA -> AddPosZHistory(prePos.getZ() / mm);
			m_EA -> AddTimeHistory(time          / ns);
		}
	}
}
