#ifndef RSDETCON_h
#define RSDETCON_h 1

////////////////////////////////////////////////////////////////////////////////
//   RSDetCon.hh                                                              //
//                                                                            //
//   This file is a header for RSDetCon class. It's for construction of       //
// whole geometry of simulation, which includes target geometry and detector  //
// geometry. Details of configuration can be set at config.cfg file. The      //
// configuration is tranfered at main function and used here to generate      //
// world of simulation.                                                       //
//                                                                            //
//                    - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"

#include "RSConMan.hh"

class G4VPhysicalVolume;

class RSConMan;

class RSDetCon: public G4VUserDetectorConstruction
{
  public:
	RSDetCon(RSConMan* CM);
	virtual ~RSDetCon();
	virtual G4VPhysicalVolume* Construct();

  private:
	void DefineDimensions();
	void ConstructMaterials();
	void DestructMaterials();

  private:
	// Configuration manager
	RSConMan* m_CM;

	// Elements
	G4Element* m_ElH;
	G4Element* m_ElC;
	G4Element* m_ElN;
	G4Element* m_ElO;
	G4Element* m_ElF;
	G4Element* m_ElMg;
	G4Element* m_ElAl;
	G4Element* m_ElSi;
	G4Element* m_ElAr;
	G4Element* m_ElCr;
	G4Element* m_ElMn;
	G4Element* m_ElFe;
	G4Element* m_ElNi;
	G4Element* m_ElCu;
	G4Element* m_ElZn;
	G4Element* m_ElY;
	G4Element* m_ElSn;
	G4Element* m_ElCe;
	G4Element* m_ElLu;

	// Materials
	G4Material* m_AirMat;
	G4Material* m_TarMat;
	G4double m_atm;

	// Dimensions pressure
	G4double m_WorldX;
	G4double m_WorldY;
	G4double m_WorldZ;
	G4double m_WorldP;

	// Geometry objects: World
	G4Box*             m_WorldSolid;
	G4LogicalVolume*   m_WorldLV;
	G4VPhysicalVolume* m_WorldPV;

	// Geometry objects: Target
	G4Box*             m_TarSolid;
	G4LogicalVolume*   m_TarLV;
	G4VPhysicalVolume* m_TarPV;
};
#endif
