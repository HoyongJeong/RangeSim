#ifndef RSEVEACT_h
#define RSEVEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSEveAct.hh                                                              //
//                                                                            //
//   This file is a header for RSEveAct class. User can add user-defined      //
// event action in this class.                                                //
//                                                                            //
//                    - 22. Oct. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <map>

#include "G4UserEventAction.hh"
#include "G4String.hh"

#include "RSConMan.hh"

class G4Event;

class RSConMan;

class RSEveAct: public G4UserEventAction
{
  public:
	RSEveAct(RSConMan* CM);
	virtual ~RSEveAct();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(  const G4Event*);

	// Add or set
	void AddEDep(G4double eDep);
	void AddPath(G4double path);
	void SetEDepTotal(G4double eDepTotal);
	void SetPathTotal(G4double pathTotal);
	void SetPosXFinal(G4double posXFinal);
	void SetPosYFinal(G4double posYFinal);
	void SetPosZFinal(G4double posZFinal);
	void SetTimeFinal(G4double timeFinal);
	void AddEKinHistory(G4double eKin);
	void AddPosXHistory(G4double posX);
	void AddPosYHistory(G4double posY);
	void AddPosZHistory(G4double posZ);
	void AddTimeHistory(G4double time);

	// Get
	G4double GetEDepTotal();
	G4double GetPathTotal();
	G4double GetPosXFinal();
	G4double GetPosYFinal();
	G4double GetPosZFinal();
	G4double GetTimeFinal();
	std::vector<G4double>& GetEKinHistory();
	std::vector<G4double>& GetPosXHistory();
	std::vector<G4double>& GetPosYHistory();
	std::vector<G4double>& GetPosZHistory();
	std::vector<G4double>& GetTimeHistory();

  private:
	RSConMan* m_CM;

	// Single numbers that store final state
	G4double m_EDepTotal;
	G4double m_PathTotal;
	G4double m_PosXFinal;
	G4double m_PosYFinal;
	G4double m_PosZFinal;
	G4double m_TimeFinal;

	// Tracking vectors
	std::vector<G4double> m_EKinHistory;
	std::vector<G4double> m_PosXHistory;
	std::vector<G4double> m_PosYHistory;
	std::vector<G4double> m_PosZHistory;
	std::vector<G4double> m_TimeHistory;
};

#endif
