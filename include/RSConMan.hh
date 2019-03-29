#ifndef RSCONMAN_h
#define RSCONMAN_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSConMan.hh                                                              //
//                                                                            //
//   This file is a header for RSConMan class. It's a configuration           //
// manager for simulation. The class contains all configuration parameters    //
// for simulation configuration from a file.                                  //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <string>

#include "globals.hh"

class RSConMan
{
  public:
	// Constructors and Destructor
	RSConMan();
	RSConMan(const char* fileName);
	~RSConMan();

	// Initialize
	void Init(const char* fileName = 0);

	// Load configuration file
	bool Load(const char* fileName);
	void PrintConfiguration();

	// Set & get configurations: Computing
	void SetNofTRD( const G4int    nofTRD );
	G4int    GetNofTRD()  const;
	// Set & get configurations: World
	void SetWorldX( const G4double worldX );
	G4double GetWorldX()  const;
	void SetWorldY( const G4double worldY );
	G4double GetWorldY()  const;
	void SetWorldZ( const G4double worldZ );
	G4double GetWorldZ()  const;
	void SetWorldP( const G4double worldP );
	G4double GetWorldP()  const;
	// Set & get configurations: Beam
	void SetBeamPar(const G4int    beamPar);
	G4int    GetBeamPar() const;
	void SetBeamKE( const G4double beamKE );
	G4double GetBeamKE()  const;
	// Set & get configurations: Target
	void SetTarMat( const G4String tarMat );
	G4String GetTarMat()  const;

	// Does the line start with specific word?
	bool StartsWith(const std::string& line, const std::string& token);

  private:
	void SetDefault();

	// Computing resource
	std::string m_SNofTRD;   G4int    m_NofTRD;
	// World
	std::string m_SWorldX;   G4double m_WorldX;
	std::string m_SWorldY;   G4double m_WorldY;
	std::string m_SWorldZ;   G4double m_WorldZ;
	std::string m_SWorldP;   G4double m_WorldP;
	// Beam
	std::string m_SBeamPar;  G4int    m_BeamPar;
	std::string m_SBeamKE;   G4double m_BeamKE;
	// Target
	std::string m_STarMat;   G4String m_TarMat;
};

#endif
