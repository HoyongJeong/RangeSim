////////////////////////////////////////////////////////////////////////////////
//   RSRunAct.cc                                                              //
//                                                                            //
//   Definitions of RSRunAct class's member functions. Details of user        //
// actions are here.                                                          //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <ctime>

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcommand.hh"

#include "RSRunAct.hh"
#include "RSAna.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
RSRunAct::RSRunAct(RSConMan* CM, RSEveAct* EA): G4UserRunAction(), m_CM(CM), m_EA(EA)
{
	// Create analysis manager
	// The choice of analysis technology is done via selection of a namespace
	// in RSAna.hh
	G4AnalysisManager* AM = G4AnalysisManager::Instance();
	G4cout << "Using " << AM -> GetType() << G4endl;

	// Default settings
	// I don't like chatterbox...
	AM -> SetVerboseLevel(0);

	// Creating ntuple
	AM -> CreateNtuple("data", "data");
	AM -> CreateNtupleIColumn("eventID"                              ); // Column ID =  0
	AM -> CreateNtupleDColumn("eDepTotal"                            ); // Column ID =  1
	AM -> CreateNtupleDColumn("pathTotal"                            ); // Column ID =  2
	AM -> CreateNtupleDColumn("posXFinal"                            ); // Column ID =  3
	AM -> CreateNtupleDColumn("posYFinal"                            ); // Column ID =  4
	AM -> CreateNtupleDColumn("posZFinal"                            ); // Column ID =  5
	AM -> CreateNtupleDColumn("timeFinal"                            ); // Column ID =  6
	AM -> CreateNtupleDColumn("eKinHistory", m_EA -> GetEKinHistory()); // Column ID =  7
	AM -> CreateNtupleDColumn("posXHistory", m_EA -> GetPosXHistory()); // Column ID =  8
	AM -> CreateNtupleDColumn("posYHistory", m_EA -> GetPosYHistory()); // Column ID =  9
	AM -> CreateNtupleDColumn("posZHistory", m_EA -> GetPosZHistory()); // Column ID = 10
	AM -> CreateNtupleDColumn("timeHistory", m_EA -> GetTimeHistory()); // Column ID = 11
	AM -> FinishNtuple();
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
RSRunAct::~RSRunAct()
{
	delete G4AnalysisManager::Instance();
}

//////////////////////////////////////////////////
//   Begin of run action                        //
//////////////////////////////////////////////////
void RSRunAct::BeginOfRunAction(const G4Run* /*run*/)
{
	// All actions defined here will be excuted at the beginning of every run.
	// What is a run? You may type "/run/beamOn [someNumber]".
	// Whenever you do this, "one run" runs.

	// Get analysis manager
	G4AnalysisManager* AM = G4AnalysisManager::Instance();

	// Get current time to include it to file name
	// This time info is going to be used to generate output file name.
	time_t rawTime;
	struct tm* timeInfo;
	char buffer[80];
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeInfo);
	std::string sTime(buffer);

	// Get kinetic energy to include it to file name
	G4double dKE = m_CM -> GetBeamKE();
	G4int iKE = dKE / MeV;

	// Open an output file
	// The default file name is set in RSRunAct::RSRunAct(),
	// and it can be overwritten in a macro
	G4String fileName;
	fileName = m_CM -> GetTarMat();
	fileName += "-";
	fileName += std::to_string(iKE);
	fileName += "-";
	fileName += sTime;

	AM -> OpenFile(fileName);
}

//////////////////////////////////////////////////
//   End of run action                          //
//////////////////////////////////////////////////
void RSRunAct::EndOfRunAction(const G4Run* run)
{
	// save histograms & ntuple
	G4AnalysisManager* AM = G4AnalysisManager::Instance();
	// You must save. Otherwise, file will be just empty...
	AM -> Write();
	// You must close the file. Otherwise, file will be crahsed...
	AM -> CloseFile();
}
