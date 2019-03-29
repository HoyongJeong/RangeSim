#ifndef RSSTEACT_h
#define RSSTEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSSetAct.hh                                                              //
//                                                                            //
//   This file is a header for RSSteAct class. User can add user-defined      //
// stepping action in this class. So this class works at every step.          //
// The most busiest class.                                                    //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserSteppingAction.hh"
#include "RSEveAct.hh"

class RSEveAct;

class RSSteAct: public G4UserSteppingAction
{
  public:
	RSSteAct(RSEveAct* EA);
	virtual ~RSSteAct();

	virtual void UserSteppingAction(const G4Step*);

  private:
	RSEveAct* m_EA;
};

#endif
