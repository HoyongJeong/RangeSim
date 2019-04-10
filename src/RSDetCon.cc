////////////////////////////////////////////////////////////////////////////////
//   RSDetCon.cc                                                            //
//                                                                            //
//   Definitions of RSDetCon class's member functions.                      //
// And it describes geometry of simulation.                                   //
//                                                                            //
//                    - 20. Oct. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UIcommand.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "RSDetCon.hh"

//////////////////////////////////////////////////
//   Constructor and destructor                 //
//////////////////////////////////////////////////
RSDetCon::RSDetCon(RSConMan* CM): m_CM(CM)
{
	ConstructMaterials();
	DefineDimensions();
}

RSDetCon::~RSDetCon()
{
	DestructMaterials();
}

//////////////////////////////////////////////////
//   Define dimensions                          //
//////////////////////////////////////////////////
void RSDetCon::DefineDimensions()
{

	// World dimensions: Laboratory size
	m_WorldX = m_CM -> GetWorldX(); // World x dimension
	m_WorldY = m_CM -> GetWorldY(); // World y dimension
	m_WorldZ = m_CM -> GetWorldZ(); // World z dimension
	m_WorldP = m_CM -> GetWorldP(); // Pressure
}

//////////////////////////////////////////////////
//   Construct everything                       //
//////////////////////////////////////////////////
G4VPhysicalVolume* RSDetCon::Construct()
{
	// World
	m_WorldSolid = new G4Box("WorldSolid", m_WorldX / 2., m_WorldY / 2., m_WorldZ / 2.);
	m_WorldLV    = new G4LogicalVolume(m_WorldSolid, m_AirMat, "WorldLV");
	m_WorldPV    = new G4PVPlacement(0, G4ThreeVector(), "WorldPV", m_WorldLV, 0, false, 0);

	// Target
	m_TarSolid = new G4Box("TarSolid", m_WorldX / 2., m_WorldY / 2., m_WorldZ / 4.);
	m_TarLV    = new G4LogicalVolume(m_TarSolid, m_TarMat, "TarLV");
	new G4PVPlacement(0, G4ThreeVector(0., 0., m_WorldZ / 4.), "TarPV", m_TarLV, m_WorldPV, false, 0);

	return m_WorldPV;
}

//////////////////////////////////////////////////
//   Construct materials                        //
//////////////////////////////////////////////////
void RSDetCon::ConstructMaterials()
{
	const G4double labTemp = 300.0 * kelvin;

	// Elements to be used to construct materials
	m_ElH  = new G4Element( "Hydrogen",  "H",  1,   1.00794 *g/mole);
	m_ElC  = new G4Element(   "Carbon",  "C",  6,  12.0107  *g/mole);
	m_ElN  = new G4Element( "Nitrogen",  "N",  7,  14.00674 *g/mole);
	m_ElO  = new G4Element(   "Oxygen",  "O",  8,  15.9994  *g/mole);
	m_ElF  = new G4Element( "Fluorine",  "F",  9,  18.998403*g/mole);
	m_ElMg = new G4Element("Magnesium", "Mg", 12,  24.3050  *g/mole);
	m_ElAl = new G4Element( "Aluminum", "Al", 13,  26.981539*g/mole);
	m_ElSi = new G4Element(  "Silicon", "Si", 14,  28.0855  *g/mole);
	m_ElAr = new G4Element(    "Argon", "Ar", 18,  39.948   *g/mole);
	m_ElCr = new G4Element("Chromuium", "Cr", 24,  51.9961  *g/mole);
	m_ElMn = new G4Element("Manganese", "Mn", 25,  54.938044*g/mole);
	m_ElFe = new G4Element(     "Iron", "Fe", 26,  55.845   *g/mole);
	m_ElNi = new G4Element(   "Nickel", "Ni", 28,  58.6934  *g/mole);
	m_ElCu = new G4Element(   "Copper", "Cu", 29,  63.546   *g/mole);
	m_ElZn = new G4Element(     "Zinc", "Zn", 30,  65.38    *g/mole);
	m_ElY  = new G4Element(  "Yttrium",  "Y", 39,  88.90585 *g/mole);
	m_ElSn = new G4Element(      "Tin", "Sn", 50, 118.71    *g/mole);
	m_ElCe = new G4Element(   "Cerium", "Ce", 58, 140.116   *g/mole);
	m_ElLu = new G4Element( "Lutetium", "Lu", 71, 174.967   *g/mole);

	// Air material
	m_atm = 1.225e-3 * g/cm3;
	m_AirMat = new G4Material("Air", m_atm * m_WorldP, 3, kStateGas, labTemp);
	m_AirMat -> AddElement(m_ElN, 75.47/99.95);
	m_AirMat -> AddElement(m_ElO, 23.20/99.95);
	m_AirMat -> AddElement(m_ElAr, 1.28/99.95);

	// Target material
	G4String targetMaterial = m_CM -> GetTarMat();
	if ( targetMaterial == "Scint" )
	{
		m_TarMat = new G4Material("PlasticScint", 1.032*g/cm3, 2, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 0.915);
		m_TarMat -> AddElement(m_ElH, 0.085);
	}
	else if ( targetMaterial == "LYSO" )
	{
		m_TarMat = new G4Material("LYSO", 7.1*g/cm3, 5, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElLu, 71.43/100.0);
		m_TarMat -> AddElement(m_ElY,   4.03/100.0);
		m_TarMat -> AddElement(m_ElSi,  6.37/100.0);
		m_TarMat -> AddElement(m_ElO,  18.14/100.0);
		m_TarMat -> AddElement(m_ElCe,  0.02/100.0);
	}
	else if ( targetMaterial == "C" )
	{
		m_TarMat = new G4Material("Graphite", 1.7*g/cm3, 3, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 99.0/100.0);
		m_TarMat -> AddElement(m_ElN,  0.7/100.0);
		m_TarMat -> AddElement(m_ElO,  0.3/100.0);
	}
	else if ( targetMaterial == "Mg" )
	{
		m_TarMat = new G4Material("Magnesium", 1.738*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElMg, 1.0);
	}
	else if ( targetMaterial == "Al" )
	{
		m_TarMat = new G4Material("Aluminum", 2.70*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElAl, 1.0);
	}
	else if ( targetMaterial == "Sn" )
	{
		m_TarMat = new G4Material("Tin", 5.769*g/cm3, 1, kStateSolid, labTemp); // Gray tin?
		m_TarMat -> AddElement(m_ElSn, 1.0);
	}
	else if ( targetMaterial == "Si" )
	{
		m_TarMat = new G4Material("Silicon", 2.329*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElSi, 1.0);
	}
	else if ( targetMaterial == "Ni" )
	{
		m_TarMat = new G4Material("Nickel", 8.908*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElNi, 1.0);
	}
	else if ( targetMaterial == "Zn" )
	{
		m_TarMat = new G4Material("Zinc", 7.14*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElZn, 1.0);
	}
	else if ( targetMaterial == "CH2" )
	{
		m_TarMat = new G4Material("Polyethelene", 0.92*g/cm3, 2, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 1);
		m_TarMat -> AddElement(m_ElH, 2);
	}
	else
	{
		std::stringstream message;
		message << "Could not find target material with name " << targetMaterial;
		G4Exception("RSDetCon::ConstructMaterials()", "", FatalException, message.str().c_str());
	}
}

void RSDetCon::DestructMaterials()
{
	delete m_TarMat;
	delete m_AirMat;

	delete m_ElLu;
	delete m_ElCe;
	delete m_ElSn;
	delete m_ElY;
	delete m_ElZn;
	delete m_ElCu;
	delete m_ElNi;
	delete m_ElFe;
	delete m_ElMn;
	delete m_ElCr;
	delete m_ElAr;
	delete m_ElSi;
	delete m_ElAl;
	delete m_ElMg;
	delete m_ElF;
	delete m_ElO;
	delete m_ElN;
	delete m_ElC;
	delete m_ElH;
}
