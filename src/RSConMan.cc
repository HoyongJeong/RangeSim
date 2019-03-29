////////////////////////////////////////////////////////////////////////////////
//   RSConMan.cc                                                              //
//                                                                            //
//   Definitions of RSConMan class's member functions                         //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "G4SystemOfUnits.hh"

#include "RSConMan.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
RSConMan::RSConMan()
{
	SetDefault();
	Init();
}

RSConMan::RSConMan(const char* fileName)
{
	SetDefault();
	Init(fileName);
}

RSConMan::~RSConMan()
{
}

//////////////////////////////////////////////////
//   Initialization function                    //
//////////////////////////////////////////////////
void RSConMan::Init(const char* fileName)
{
	if ( !fileName ) SetDefault();
	else if ( !Load(fileName) ) SetDefault();
//	SetDefault();
}

void RSConMan::SetDefault()
{
	// When the class fails to find configuration file, this setup is applied.

	// Computing
	m_NofTRD   =           4;
	// World
	m_WorldX   = 6000.0 * mm;
	m_WorldY   = 6000.0 * mm;
	m_WorldZ   = 6000.0 * mm;
	m_WorldP   =       0.001;
	// Beam
	m_BeamKE   = 250.0 * MeV;
	m_BeamPar  =          22;
	// Target
	m_TarMat   =     "Scint";
}

//////////////////////////////////////////////////
//   Load configuration file                    //
//////////////////////////////////////////////////
bool RSConMan::Load(const char* fileName)
{
	// Open file
	std::ifstream file(fileName, std::ifstream::in);
	if ( !file.is_open() ) return false;

	// Read line by line
	std::string line;
	while ( std::getline(file, line) )
	{
		if ( StartsWith(line, "#") ) continue;

		// Read configuration: Computing
		if ( StartsWith(line, "NTHREADS") )
		{
			char hfile[1000];
			sscanf(line.data(), "NTHREADS %s", hfile);
			m_SNofTRD = hfile;
			m_NofTRD = std::stoi(m_SNofTRD);
		}
		// Read configurations: World
		if ( StartsWith(line, "WORLDX") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDX %s", hfile);
			m_SWorldX = hfile;
			m_WorldX = std::stod(m_SWorldX) * mm;
		}
		if ( StartsWith(line, "WORLDY") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDY %s", hfile);
			m_SWorldY = hfile;
			m_WorldY = std::stod(m_SWorldY) * mm;
		}
		if ( StartsWith(line, "WORLDZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDZ %s", hfile);
			m_SWorldZ = hfile;
			m_WorldZ = std::stod(m_SWorldZ) * mm;
		}
		if ( StartsWith(line, "WORLDP") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDP %s", hfile);
			m_SWorldP = hfile;
			m_WorldP = std::stod(m_SWorldP) * mm;
		}
		// Read configurations: Beam
		if ( StartsWith(line, "BEAMPARTICLE") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMPARTICLE %s", hfile);
			m_SBeamPar = hfile;
			m_BeamPar = std::stoi(m_SBeamPar);
		}
		if ( StartsWith(line, "BEAMKINETICENERGY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMKINETICENERGY %s", hfile);
			m_SBeamKE = hfile;
			m_BeamKE = std::stod(m_SBeamKE) * MeV;
		}
		// Read configurations: Target
		if ( StartsWith(line, "TARGETMATERIAL") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETMATERIAL %s", hfile);
			m_STarMat = hfile;
			m_TarMat = m_STarMat;
		}
	}

	PrintConfiguration();

	return true;
}

void RSConMan::PrintConfiguration()
{
	// Computing
	printf(" RSConMan::Load() => NTHREADS           %s    \n", m_SNofTRD.data() );
	// World                                            
	printf(" RSConMan::Load() => WORLDX             %s mm \n", m_SWorldX.data() );
	printf(" RSConMan::Load() => WORLDY             %s mm \n", m_SWorldY.data() );
	printf(" RSConMan::Load() => WORLDZ             %s mm \n", m_SWorldZ.data() );
	printf(" RSConMan::Load() => WORLDP             %s    \n", m_SWorldP.data() );
	// Beam                                             
	printf(" RSConMan::Load() => BEAMPARTICLE       %s    \n", m_SBeamPar.data());
	printf(" RSConMan::Load() => BEAMKINETICENERGY  %s MeV\n", m_SBeamKE.data() );
	// Target                                           
	printf(" RSConMan::Load() => TARGETMATERIAL     %s    \n", m_STarMat.data() );
}

//////////////////////////////////////////////////
//   Set & get configurations                   //
//////////////////////////////////////////////////
// Computing
void RSConMan::SetNofTRD(const G4int nofTRD)
{
	m_NofTRD = nofTRD;
}
G4int RSConMan::GetNofTRD() const
{	
	return m_NofTRD;
}

// World
void RSConMan::SetWorldX(const G4double worldX)
{
	m_WorldX = worldX;
}
G4double RSConMan::GetWorldX() const
{
	return m_WorldX;
}

void RSConMan::SetWorldY(const G4double worldY)
{
	m_WorldY = worldY;
}
G4double RSConMan::GetWorldY() const
{
	return m_WorldY;
}

void RSConMan::SetWorldZ(const G4double worldZ)
{
	m_WorldZ = worldZ;
}
G4double RSConMan::GetWorldZ() const
{
	return m_WorldZ;
}

void RSConMan::SetWorldP(const G4double worldP)
{
	m_WorldP = worldP;
}
G4double RSConMan::GetWorldP() const
{
	return m_WorldP;
}

// Beam
void RSConMan::SetBeamPar(const G4int beamPar)
{
	m_BeamPar = beamPar;
}
G4int RSConMan::GetBeamPar() const
{
	return m_BeamPar;
}
void RSConMan::SetBeamKE(const G4double beamKE)
{
	m_BeamKE = beamKE;
}
G4double RSConMan::GetBeamKE() const
{
	return m_BeamKE;
}

// Target
void RSConMan::SetTarMat(const G4String tarMat)
{
	m_TarMat = tarMat;
}
G4String RSConMan::GetTarMat() const
{
	return m_TarMat;
}

//////////////////////////////////////////////////
//   Test whether a line starts with ...        //
//////////////////////////////////////////////////
bool RSConMan::StartsWith(const std::string& text, const std::string& token)
{
	if ( text.length() < token.length() ) return false;
	return ( text.compare(0, token.length(), token) == 0 );
}
