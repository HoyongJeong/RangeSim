#ifndef RSRUNACT_h
#define RSRUNACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSRunAct.hh                                                              //
//                                                                            //
//   This file is a header for RSRunAct class. In addition to the basic       //
// actions, user can add additional user-defined actions.                     //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserRunAction.hh"

#include "RSConMan.hh"
#include "RSEveAct.hh"

class G4Run;

class RSConMan;

class RSRunAct: public G4UserRunAction
{
  public:
	RSRunAct(RSConMan* CM, RSEveAct* EA);
	virtual ~RSRunAct();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(  const G4Run*);

  private:
	// Configuration
	RSConMan* m_CM;

	// Event action
	RSEveAct* m_EA;
};

#endif
