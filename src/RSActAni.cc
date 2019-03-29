////////////////////////////////////////////////////////////////////////////////
//   RSActIni.cc                                                              //
//                                                                            //
//   Definitions of RSActIni class's member functions.                        //
// All actions must be initialized here in order to use multi thread.         //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "RSActIni.hh"
#include "RSPriGenAct.hh"
#include "RSRunAct.hh"
#include "RSEveAct.hh"
#include "RSSteAct.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
RSActIni::RSActIni(RSConMan* CM): G4VUserActionInitialization(), m_CM(CM)
{
	// Pointer of configuration manager class is initialized
	// when this class is constructed. (CM object)
	// This pointer will be delivered to user actions.
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
RSActIni::~RSActIni()
{
}

//////////////////////////////////////////////////
//   Build For Master                           //
//////////////////////////////////////////////////
void RSActIni::BuildForMaster() const
{
	// So, this part is for master. This program is possible to do multithread.
	// A thread will care things as a master.

	// Master thread must have this.
	RSEveAct* EAM = new RSEveAct(m_CM);
	SetUserAction(new RSRunAct(m_CM, EAM));
}

//////////////////////////////////////////////////
//   Build                                      //
//////////////////////////////////////////////////
void RSActIni::Build() const
{
	// All user actions are here.
	SetUserAction(new RSPriGenAct(m_CM));
  
	RSEveAct* EA = new RSEveAct(m_CM);
	SetUserAction(EA);

	SetUserAction(new RSRunAct(m_CM, EA));
  
	SetUserAction(new RSSteAct(EA));
}
