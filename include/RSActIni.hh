#ifndef RSACTINI_h
#define RSACTINI_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSActIni.hh                                                              //
//                                                                            //
//   This file is a header for RSActIni class. Every actions are              //
// initialized through this class.                                            //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

#include "RSConMan.hh"
#include "RSEveAct.hh"

class RSConMan;

class RSActIni: public G4VUserActionInitialization
{
  public:
	RSActIni(RSConMan* CM);
	virtual ~RSActIni();

	virtual void BuildForMaster() const;
	virtual void Build() const;

  private:
	// Configuration manager
	RSConMan* m_CM;
};

#endif
