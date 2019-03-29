////////////////////////////////////////////////////////////////////////////////
//   RSEveAct.cc                                                              //
//                                                                            //
//   Definitions of RSEveAct class's member functions. Details of user        //
// actions are here.                                                          //
//                                                                            //
//                    - 20. Oct. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <ctime>

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "RSEveAct.hh"
#include "RSAna.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
RSEveAct::RSEveAct(RSConMan* CM): m_CM(CM)
{
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
RSEveAct::~RSEveAct()
{
}

//////////////////////////////////////////////////
//   Begin of event action                      //
//////////////////////////////////////////////////
void RSEveAct::BeginOfEventAction(const G4Event* /* anEvent */)
{
	// Initialize
	m_EDepTotal = 0.;
	m_PathTotal = 0.;
	m_PosXFinal = 0.;
	m_PosYFinal = 0.;
	m_PosZFinal = 0.;
	m_TimeFinal = 0.;
	m_EKinHistory . clear();
	m_PosXHistory . clear();
	m_PosYHistory . clear();
	m_PosZHistory . clear();
	m_TimeHistory . clear();
}

//////////////////////////////////////////////////
//   End of event action                        //
//////////////////////////////////////////////////
void RSEveAct::EndOfEventAction(const G4Event* anEvent)
{
	// Get event ID
	G4int eventID = anEvent -> GetEventID();

	// Get analysis manager
	G4AnalysisManager* AM = G4AnalysisManager::Instance();

	// Fill ntuple
	AM -> FillNtupleIColumn(0, eventID);
	AM -> FillNtupleDColumn(1, m_EDepTotal);
	AM -> FillNtupleDColumn(2, m_PathTotal);
	AM -> FillNtupleDColumn(3, m_PosXFinal);
	AM -> FillNtupleDColumn(4, m_PosYFinal);
	AM -> FillNtupleDColumn(5, m_PosZFinal);
	AM -> FillNtupleDColumn(6, m_TimeFinal);
	AM -> AddNtupleRow();

	// Print message
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[80];
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeInfo);
	std::string sTime(buffer);
	if ( (eventID + 1) % 100000 == 0 )
	{
		G4cout << "[Notice] " << eventID + 1 << "-th event processed at " << sTime << G4endl;
	}
}

//////////////////////////////////////////////////
//   Add or set                                 //
//////////////////////////////////////////////////
void RSEveAct::AddEDep(G4double eDep)
{
	m_EDepTotal += eDep;
}

void RSEveAct::AddPath(G4double path)
{
	m_PathTotal += path;
}

void RSEveAct::SetEDepTotal(G4double eDepTotal)
{
	m_EDepTotal = eDepTotal;
}

void RSEveAct::SetPathTotal(G4double pathTotal)
{
	m_PathTotal = pathTotal;
}

void RSEveAct::SetPosXFinal(G4double posXFinal)
{
	m_PosXFinal = posXFinal;
}

void RSEveAct::SetPosYFinal(G4double posYFinal)
{
	m_PosYFinal = posYFinal;
}

void RSEveAct::SetPosZFinal(G4double posZFinal)
{
	m_PosZFinal = posZFinal;
}

void RSEveAct::SetTimeFinal(G4double timeFinal)
{
	m_TimeFinal = timeFinal;
}

void RSEveAct::AddEKinHistory(G4double eKin)
{
	m_EKinHistory.push_back(eKin);
}

void RSEveAct::AddPosXHistory(G4double posX)
{
	m_PosXHistory.push_back(posX);
}

void RSEveAct::AddPosYHistory(G4double posY)
{
	m_PosYHistory.push_back(posY);
}

void RSEveAct::AddPosZHistory(G4double posZ)
{
	m_PosZHistory.push_back(posZ);
}

void RSEveAct::AddTimeHistory(G4double time)
{
	m_TimeHistory.push_back(time);
}

//////////////////////////////////////////////////
//   Get                                        //
//////////////////////////////////////////////////
G4double RSEveAct::GetEDepTotal()
{
	return m_EDepTotal;
}

G4double RSEveAct::GetPathTotal()
{
	return m_PathTotal;
}

G4double RSEveAct::GetPosXFinal()
{
	return m_PosXFinal;
}

G4double RSEveAct::GetPosYFinal()
{
	return m_PosYFinal;
}

G4double RSEveAct::GetPosZFinal()
{
	return m_PosZFinal;
}

G4double RSEveAct::GetTimeFinal()
{
	return m_TimeFinal;
}

std::vector<G4double>& RSEveAct::GetEKinHistory()
{
	return m_EKinHistory;
}

std::vector<G4double>& RSEveAct::GetPosXHistory()
{
	return m_PosXHistory;
}

std::vector<G4double>& RSEveAct::GetPosYHistory()
{
	return m_PosYHistory;
}

std::vector<G4double>& RSEveAct::GetPosZHistory()
{
	return m_PosZHistory;
}

std::vector<G4double>& RSEveAct::GetTimeHistory()
{
	return m_TimeHistory;
}
