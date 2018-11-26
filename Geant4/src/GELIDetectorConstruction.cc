
#include "GELIDetectorConstruction.hh"
#include "GELITabulatedField3D.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVParameterised.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EqMagElectricField.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4RotationMatrix.hh"

#include "G4ChordFinder.hh"
#include "G4UniformMagField.hh"
#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4NistManager.hh"
#include "CADMesh.hh"
//#include "G4GDMLParser.hh"

#include <glob.h>
#include <sstream>

#include "VolumeBuilder.hh"



// #include <boost/progress.hpp>
// #include <boost/timer.hpp>
// #include <vector>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
// Possibility to turn off (0) magnetic field and measurement volume. 
#define GAP 1          // Magnet geometric volume
#define MAG 1          // Magnetic field grid
#define MEASUREVOL 1   // Volume for measurement
//#define Active_Area 1
//#define WINDOW

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIDetectorConstruction::GELIDetectorConstruction()

  :physiWorld(NULL), logicWorld(NULL), solidWorld(NULL),
   physiGap1(NULL), logicGap1(NULL), solidGap1(NULL),
   physiGap2(NULL), logicGap2(NULL), solidGap2(NULL),
   physiMeasureVolume(NULL), logicMeasureVolume(NULL), 
   solidMeasureVolume(NULL),
    physiGas(NULL),solidGas(NULL),logicGas(NULL),
   physiGas2(NULL),solidGas2(NULL),logicGas2(NULL),
    physiTub(NULL),solidTub(NULL),logicTub(NULL),
    physiTub2(NULL),solidTub2(NULL),logicTub2(NULL),
     solidCloseActiveArea(NULL),  solidGas_x(NULL),
      physiActiveArea(NULL),solidActiveArea(NULL),logicActiveArea(NULL),
   WorldMaterial(NULL), 
   GapMaterial(NULL),
   WindowMaterial(NULL),
   GasMaterial(NULL),
   GermanMaterial(NULL),
   TubMaterial(NULL),AluminiumMaterial(NULL)//, fScoringVolume(0)
 
    
{
  fField.Put(0);
  WorldSizeXY=WorldSizeZ=0;
  GapSizeX1=GapSizeX2=GapSizeY1=GapSizeY2=GapSizeZ=0;
  MeasureVolumeSizeXY=MeasureVolumeSizeZ=0;
     filename = "";
    filetype = "";
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIDetectorConstruction::~GELIDetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* GELIDetectorConstruction::Construct()

{
  //DefineMaterials();
  //return ConstructCalorimeter();
  return ConstructPP();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELIDetectorConstruction::DefineMaterials()
{ 
  //This function illustrates the possible ways to define materials.
  //Density and mass per mole taken from Physics Handbook for Science
  //and engineering, sixth edition. This is a general material list
  //with extra materials for other examples.
  
  G4String name, symbol;             
  G4double density;            
  
  G4int ncomponents, natoms;
  G4double fractionmass;
  G4double temperature, pressure;
  
  // Define Elements  
  // Example: G4Element* Notation  = new G4Element ("Element", "Notation", z, a);
  G4Element*   H  = new G4Element ("Hydrogen", "H", 1. ,  1.01*g/mole);
  G4Element*   N  = new G4Element ("Nitrogen", "N", 7., 14.01*g/mole);
  G4Element*   O  = new G4Element ("Oxygen"  , "O", 8. , 16.00*g/mole);
  G4Element*   Ar = new G4Element ("Argon" , "Ar", 18., 39.948*g/mole );
  G4Element*   C = new G4Element ("Carbon" , "C", 6., 12.01*g/mole );
   G4Element* Fe = new G4Element("Iron","Fe", 26., 55.85*g/mole);
  G4Element* Cr = new G4Element("Chromium", "Cr", 24., 51.9961*g/mole);
  G4Element* Mn = new G4Element("Manganese", "Mn", 12., 54.938049*g/mole);
  G4Element* Ni = new G4Element("Nickel", "Ni", 28.,  58.6934*g/mole);
  G4Element*   Si = new G4Element("Silicon", "Si", 14., 28.09*g/mole);
  
  
   G4Material* germaniumMaterial=new G4Material("Germanium",32., 72.61*g/mole,5.323*g/cm3);
   G4Material* alu=new G4Material("Aluminium",13., 26.98*g/mole,2.7*g/cm3);
  // Define Material
  // Example: G4Material* Notation = new G4Material("Material", z, a, density);
  /* Not used in this setup, will be used in further development.
  G4Material* He = new G4Material("Helium", 2., 4.00*g/mole, 0.178*mg/cm3);
  G4Material* Be = new G4Material("Beryllium", 4., 9.01*g/mole, 1.848*g/cm3);
  G4Material* W  = new G4Material("Tungsten", 74., 183.85*g/mole, 19.30*g/cm3);
  G4Material* Cu = new G4Material("Copper", 29., 63.55*g/mole, 8.96*g/cm3);
  */
 G4Material* mFe = new G4Material("Iron", 26., 55.84*g/mole, 7.87*g/cm3);  

  // Define materials from elements.
  
  // Case 1: chemical molecule  
  // Water 
  density = 1.000*g/cm3;
  G4Material* H2O = new G4Material(name="H2O"  , density, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  
  // Case 2: mixture by fractional mass.
  // Air
  density = 1.290*mg/cm3;
  G4Material* Air = new G4Material(name="Air"  , density, ncomponents=2);
  Air->AddElement(N, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);
  
  //Kapton
  
  density = 1.42*g/cm3;
  G4Material* Kapton= new G4Material(name="Kapton",density, ncomponents=4);
  Kapton->AddElement(H, fractionmass = 0.0273);
  Kapton->AddElement(C, fractionmass = 0.7213);
  Kapton->AddElement(N, fractionmass = 0.0765);
  Kapton->AddElement(O, fractionmass = 0.1749);
  
  

  
    //StainlessSteel
  density= 8.06*g/cm3;
  G4Material* StainlessSteel = new G4Material(name="StainlessSteel", density, ncomponents=6);
	StainlessSteel->AddElement(C, fractionmass=0.001);
	StainlessSteel->AddElement(Si, fractionmass=0.007);
	StainlessSteel->AddElement(Cr, fractionmass=0.18);
	StainlessSteel->AddElement(Mn, fractionmass=0.01);
	StainlessSteel->AddElement(Fe, fractionmass=0.712);
	StainlessSteel->AddElement(Ni, fractionmass=0.09);
    
    // examples of CO2

//density = 0.1805*mg/cm3;//good
//density = 0.0001805*g/cm3;//good
//pressure    = 0.1*bar;
//temperature = 293.*kelvin;
G4Material* CO2 = new G4Material(name="Carbonic gas", density = 0.1805*mg/cm3, ncomponents=2,
                                     kStateGas,temperature=293.*kelvin, pressure    = 0.1*bar);




      //  G4Material* CO2  = new G4Material(name="CO2", density, ncomponents=2,kStateGas);
 	CO2->AddElement(C, natoms=1);
        CO2->AddElement(O, natoms=2);
      



  // Vacuum
  density     = 1.e-5*g/cm3;
  pressure    = 2.e-2*bar;
  temperature = STP_Temperature;         //from PhysicalConstants.h
  G4Material* vacuum = new G4Material(name="vacuum", density, ncomponents=1,
                                      kStateGas,temperature,pressure);
  vacuum->AddMaterial(Air, fractionmass=1.);


  // Laboratory vacuum: Dry air (average composition)
  density = 1.7836*mg/cm3 ;       // STP
  G4Material* Argon = new G4Material(name="Argon", density, ncomponents=1);
  Argon->AddElement(Ar, 1);
  
  density = 1.25053*mg/cm3 ;       // STP
  G4Material* Nitrogen = new G4Material(name="N2", density, ncomponents=1);
  Nitrogen->AddElement(N, 2);
  
  density = 1.4289*mg/cm3 ;       // STP
  G4Material* Oxygen = new G4Material(name="O2", density, ncomponents=1);
  Oxygen->AddElement(O, 2);
  
  
  density  = 1.2928*mg/cm3 ;       // STP
  density *= 1.0e-8 ;              // pumped vacuum
  
  temperature = STP_Temperature;
  pressure = 1.0e-8*STP_Pressure;

  G4Material* LaboratoryVacuum = new G4Material(name="LaboratoryVacuum",
						density,ncomponents=3,
						kStateGas,temperature,pressure);
  LaboratoryVacuum->AddMaterial( Nitrogen, fractionmass = 0.7557 ) ;
  LaboratoryVacuum->AddMaterial( Oxygen,   fractionmass = 0.2315 ) ;
  LaboratoryVacuum->AddMaterial( Argon,    fractionmass = 0.0128 ) ;
  

  G4cout << G4endl << *(G4Material::GetMaterialTable()) << G4endl;

  
  
  //kapton 2
 // G4NistManager* nist = G4NistManager::Instance();

  //      G4Material* Kapton = nist->FindOrBuildMaterial("G4_KAPTON"); 
  // Default materials in setup.
  WorldMaterial = LaboratoryVacuum;
  GapMaterial = mFe;
  WindowMaterial = Kapton;
  GasMaterial= CO2;
 TubMaterial = StainlessSteel;
 GermanMaterial=germaniumMaterial;
 AluminiumMaterial=alu;

}


G4VPhysicalVolume* GELIDetectorConstruction::ConstructPP()
{
    G4NistManager * nist_manager = G4NistManager::Instance();
    G4Material * air = nist_manager->FindOrBuildMaterial("G4_AIR");
    G4Material * water = nist_manager->FindOrBuildMaterial("G4_WATER");

    G4VSolid* world_solid = new G4Box("world_solid", 100*cm, 100*cm, 100*cm);
    G4LogicalVolume* world_logical = new G4LogicalVolume(world_solid, air,"world_logical",0,0,0);
    G4VPhysicalVolume* world_physical = new G4PVPlacement(0, G4ThreeVector(), world_logical,
                                       "world_physical", 0, false, 0);
    world_logical->SetVisAttributes(G4VisAttributes::Invisible);

    VolumeBuilder* builder = new VolumeBuilder();
    builder->BuildVolumes(world_logical);
    return world_physical;
    for(int i=0;i<100;i++)
      std::cout<<"dupa"<<std::endl;
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4VPhysicalVolume* GELIDetectorConstruction::ConstructCalorimeter()
{
  // Complete the parameters definition
  
  //The World
  WorldSizeXY  = 300.*cm;  // Cube
  WorldSizeZ   = 300.*cm;
  
  //Measurement volume
  MeasureVolumeSizeXY = 4.*cm;  // Cubic slice
  MeasureVolumeSizeZ  = 0.1*cm; 

  // Position of measurement volume. 
  // SSD is Source to Surface Distance. Source in origo and measurements 50 cm 
  // below in the z-direction (symbolizin a patient at SSD = 50 cm)
 
  SSD = 40.1*cm;
  MeasureVolumePosition = -(SSD + MeasureVolumeSizeZ/2); 
  

  // Geometric definition of the gap of the purging magnet. Approximation of
  // the shape of the pole gap.    

//   GapSizeY1 = 10.*cm;    // length along x at the surface positioned at -dz
//   GapSizeY2 = 10.*cm;    // length along x at the surface positioned at +dz
//   GapSizeX1 = 10.*cm;    // length along y at the surface positioned at -dz
//   GapSizeX2 = 18.37*cm;  // length along y at the surface positioned at +dz
//   GapSizeZ  = 11.5*cm;   // length along z axis

//   Gap1PosY = 0.*cm;
//   Gap1PosX = -3.0*cm;
//   Gap1PosZ = -5*cm;//-6.89
// 
//   Gap2PosY = 0.*cm;
//   Gap2PosX = 3.0*cm;
//   Gap2PosZ = -5*cm;//-6.89

  // Coordinate correction for field grif. 
  // Gap opening at z = -11.4 mm.
  // In field grid coordonates gap at z = -0.007m in field from z = 0.0m to 
  // z = 0.087m.
  // -> zOffset = -11.4-(-7) = 4.4 mm

  zOffset = 0*mm;  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// Some out prints of the setup. 
  
  G4cout << "\n-----------------------------------------------------------"
	 << "\n      Geometry and materials"
	 << "\n-----------------------------------------------------------"
	 << "\n ---> World:" 
	 << "\n ---> " << WorldMaterial->GetName() << " in World"
	 << "\n ---> " << "WorldSizeXY: " << G4BestUnit(WorldSizeXY,"Length")
	 << "\n ---> " << "WorldSizeZ: " << G4BestUnit(WorldSizeZ,"Length");
  
#if GAP
  G4cout << "\n-----------------------------------------------------------"
	 << "\n ---> Purging Magnet:" 
	 << "\n ---> " << "Gap made of "<< GapMaterial->GetName() 
	 << "\n ---> " << "GapSizeY1: " << G4BestUnit(GapSizeY1,"Length") 
	 << "\n ---> " << "GapSizeY2: " << G4BestUnit(GapSizeY2,"Length") 
	 << "\n ---> " << "GapSizeX1: " << G4BestUnit(GapSizeX1,"Length") 
	 << "\n ---> " << "GapSizeX2: " << G4BestUnit(GapSizeX2,"Length");
#endif
  
#if MEASUREVOL
  G4cout << "\n-----------------------------------------------------------"
	 << "\n ---> Measurement Volume:" 
	 << "\n ---> " << WorldMaterial->GetName() << " in Measurement volume"
	 << "\n ---> " << "MeasureVolumeXY: " << G4BestUnit(MeasureVolumeSizeXY,"Length") 
	 << "\n ---> " << "MeasureVolumeZ: " << G4BestUnit(MeasureVolumeSizeZ,"Length")
	 << "\n ---> " << "At SSD =  " << G4BestUnit(MeasureVolumePosition,"Length");
#endif
  
  G4cout << "\n-----------------------------------------------------------\n";
  
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  //     
  // World
  //
  

  solidWorld = new G4Box("World",				       //its name
			   WorldSizeXY/2,WorldSizeXY/2,WorldSizeZ/2);  //its size
  

  logicWorld = new G4LogicalVolume(solidWorld,	        //its solid
				   WorldMaterial,	//its material
				   "World");		//its name
  
  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 "World",		//its name
                                 logicWorld,		//its logical volume
                                 NULL,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number

  // Visualization attributes
  G4VisAttributes* simpleWorldVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); //White
  simpleWorldVisAtt->SetVisibility(true);
  logicWorld->SetVisAttributes(simpleWorldVisAtt);
 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  //     
  // Measurement Volume
  //
  
#if MEASUREVOL
  G4RotationMatrix *rm = new G4RotationMatrix();
rm->rotateY(90*deg);
solidMeasureVolume = new G4Tubs("MeasureVolume",
                	0*mm,20*mm,MeasureVolumeSizeZ/2,0*deg, 360*deg);
  
  logicMeasureVolume = new G4LogicalVolume(solidMeasureVolume,	        //its solid
				  WorldMaterial,          //its material
				  "MeasureVolume");             //its name
  physiMeasureVolume = new G4PVPlacement(rm,			                    //no rotation
				G4ThreeVector(600*mm,0,0),  //position
				    "MeasureVolume2",		             //its name
                                 logicMeasureVolume,		             //its logical volume
                                 physiWorld,			             //its mother  volume
                                 false,			                     //no boolean operation
                                 0);			                     //copy number


  // Visualization attributes
  G4VisAttributes* simpleMeasureVolumeVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); //White
  simpleMeasureVolumeVisAtt->SetVisibility(true);
  simpleMeasureVolumeVisAtt->SetForceSolid(true);
  logicMeasureVolume->SetVisAttributes(simpleMeasureVolumeVisAtt);

#endif
  
  

  
  
//#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  //                              
  //Gap cone. Opening 20 deg. Two separate trapezoids. Iron.
  // 

#if GAP

  //magnet



    solidGap1 = new G4Box("Gap1",
			25*mm,12.5*mm,25*mm);
     
  
  logicGap1 = new G4LogicalVolume(solidGap1,   	        //its solid
				  GapMaterial,          //its material
				  "Gap1");              //its name
  
  physiGap1 = new G4PVPlacement(rm,			                    //90 deg rotation
				G4ThreeVector(-450*mm,37.5*mm,0*mm),  //position
				"Gap1",		             		    //its name
				logicGap1,		                    //its logical volume
				physiWorld,		                    //its mother  volume
				false,			                    //no boolean operation
				0);			                    //copy number
  
  //magnet

 solidGap2 = new G4Box("Gap2",
                	25*mm,12.5*mm,25*mm);
  
  logicGap2 = new G4LogicalVolume(solidGap2,	        //its solid
				  GapMaterial,          //its material
				  "Gap2");              //its name
  
  physiGap2 = new G4PVPlacement(rm,			                    //no rotation
				G4ThreeVector(-450*mm,-37.5*mm,0*mm),  //position
				"Gap2",		                 	    //its name
				logicGap2,		             	    //its logical volume
				physiWorld,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number


  // Visualization attributes
  G4VisAttributes* simpleGap1VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0)); //yellow
  simpleGap1VisAtt->SetVisibility(true);
  simpleGap1VisAtt->SetForceSolid(true);
  logicGap1->SetVisAttributes(simpleGap1VisAtt);
  
  G4VisAttributes* simpleGap2VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0)); //yellow
  simpleGap2VisAtt->SetVisibility(true);
  simpleGap2VisAtt->SetForceSolid(true);  
  logicGap2->SetVisAttributes(simpleGap2VisAtt);

#endif

//#if WINDOW
  solidWindow = new G4Tubs("Windows",
			0*mm,  // 
			20*mm,  // 
			0.025*mm,  // 
			0*deg,  //
			360*deg ); 
  
  logicWindow = new G4LogicalVolume(solidWindow,   	        //its solid
				  WindowMaterial,          //its material
				  "Window");              //its name
  
  physiWindow = new G4PVPlacement(rm,			                    //90 deg rotation
				G4ThreeVector(-485.025*mm,0,0*mm),  //position
				//G4ThreeVector(0,0,40*mm),  //position
				"Window",		             		    //its name
				logicWindow,		                    //its logical volume
				physiWorld,		                    //its mother  volume
				false,			                    //no boolean operation
				0);			                    //copy number
     G4VisAttributes* simpleWindowVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0)); //magenta
  simpleWindowVisAtt->SetVisibility(true);
  simpleWindowVisAtt->SetForceSolid(true); 
   logicWindow->SetVisAttributes(simpleWindowVisAtt);
   
   
   
   //#if WINDOW end
   
     solidWindow2 = new G4Tubs("Windows2",
			0*mm,  // 
			20*mm,  // 
			0.025*mm,  // 
			0*deg,  //
			360*deg ); 
  
  logicWindow2 = new G4LogicalVolume(solidWindow2,   	        //its solid
				  WindowMaterial,          //its material
				  "Window2");              //its name
  
  physiWindow2 = new G4PVPlacement(rm,			                    //90 deg rotation
				G4ThreeVector(475.025,0,0*mm),  //position
				//G4ThreeVector(0,0,40*mm),  //position
				"Window2",		             		    //its name
				logicWindow2,		                    //its logical volume
				physiWorld,		                    //its mother  volume
				false,			                    //no boolean operation
				0);			                    //copy number
     G4VisAttributes* simpleWindow2VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0)); //magenta
  simpleWindow2VisAtt->SetVisibility(true);
  simpleWindow2VisAtt->SetForceSolid(true); 
   logicWindow2->SetVisAttributes(simpleWindow2VisAtt);
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
  
//#endif
  //gas
//     solidGas = new G4Tubs("gas",
//                 	0*mm,19*mm,200*mm,0*deg, 360*deg);
//   
//  logicGas = new G4LogicalVolume(solidGas,	        //its solid
// 				  GasMaterial,          //its material
// 				  "gas");              //its name
//   physiGas = new G4PVPlacement(0,			                    //no rotation
// 				G4ThreeVector(0,0,-200*mm),  //position
// 				"gas",		                 	    //its name
// 				logicGas,		             	    //its logical volume
// 				physiWorld,		             	    //its mother  volume
// 				false,			             	    //no boolean operation
// 				0);			             	    //copy number
//   
//    G4VisAttributes* simpleGasVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0)); //white
//   simpleGasVisAtt->SetVisibility(true);
//   simpleGasVisAtt->SetForceSolid(true); 
//    logicGas->SetVisAttributes(simpleGasVisAtt);
   
   
   
   
   
   
     //gas 2 maly z drugiej strony
//     solidGas2 = new G4Tubs("gas2",
//                 	0*mm,19*mm,100*mm,0*deg, 360*deg);
//   
//  logicGas2 = new G4LogicalVolume(solidGas2,	        //its solid
// 				  GasMaterial,          //its material
// 				  "gas2");              //its name
//   physiGas2 = new G4PVPlacement(0,			                    //no rotation
// 				G4ThreeVector(0,0,-1050*mm),  //position
// 				"gas2",		                 	    //its name
// 				logicGas2,		             	    //its logical volume
// 				physiWorld,		             	    //its mother  volume
// 				false,			             	    //no boolean operation
// 				0);			             	    //copy number
//   
//    G4VisAttributes* simpleGas2VisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
//   simpleGas2VisAtt->SetVisibility(true);
//   simpleGas2VisAtt->SetForceSolid(true); 
//    logicGas2->SetVisAttributes(simpleGas2VisAtt);
//    
   
//tub
//   solidTub = new G4Tubs("Tub",
//                 	19*mm,20*mm,200*mm,0*deg, 360*deg);
//   
//  logicTub = new G4LogicalVolume(solidTub,	        //its solid
// 				  TubMaterial,          //its material
// 				  "Tub");              //its name
//    physiTub = new G4PVPlacement(0,			                    //no rotation
// 				G4ThreeVector(0,0,-200*mm),  //position
// 				"Tub",		                 	    //its name
// 				logicTub,		             	    //its logical volume
// 				physiWorld,		             	    //its mother  volume
// 				false,			             	    //no boolean operation
// 				0);			             	    //copy number
//   
//    G4VisAttributes* simpleTubVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); 
//   simpleTubVisAtt->SetVisibility(true);
//   simpleTubVisAtt->SetForceSolid(true); 
//    logicTub->SetVisAttributes(simpleTubVisAtt);
  
   
   
   
   
   
//tub2
//   solidTub2 = new G4Tubs("Tub2",
//                 	19*mm,20*mm,100*mm,0*deg, 360*deg);
//   
//  logicTub2 = new G4LogicalVolume(solidTub2,	        //its solid
// 				  TubMaterial,          //its material
// 				  "Tub2");              //its name
//    physiTub2 = new G4PVPlacement(0,			                    //no rotation
// 				G4ThreeVector(0,0,-1050*mm),  //position
// 				"Tub2",		                 	    //its name
// 				logicTub2,		             	    //its logical volume
// 				physiWorld,		             	    //its mother  volume
// 				false,			             	    //no boolean operation
// 				0);			             	    //copy number
//   
//    G4VisAttributes* simpleTub2VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); 
//   simpleTub2VisAtt->SetVisibility(true);
//   simpleTub2VisAtt->SetForceSolid(true); 
//    logicTub2->SetVisAttributes(simpleTub2VisAtt);   
   
   
//////Active Area 
//    solidActiveArea= new G4Box(  "Active_Area",			350.0/2*mm,200.0/2*mm,200.0/2*mm);
//    logicActiveArea = new G4LogicalVolume(solidActiveArea,   	        //its solid
// 				  GasMaterial,          //its material
// 				  "Active_Area");              //its name
//    physiActiveArea= new G4PVPlacement(0,			                    //90 deg rotation
// 				G4ThreeVector(0*mm,0,0*mm),  //position
// 				"Active_Area",		             		    //its name
// 				logicActiveArea,		                    //its logical volume
// 				physiWorld,		                    //its mother  volume
// 				false,			                    //no boolean operation
// 				0);			                    //copy number 
//    
//           G4VisAttributes* simpleActiveAreaVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0)); 
//   simpleActiveAreaVisAtt->SetVisibility(true);
//   simpleActiveAreaVisAtt->SetForceSolid(true); 
//    logicActiveArea->SetVisAttributes(simpleActiveAreaVisAtt);
   
   ///vis/scene/add/axes 0 0 0 0.1
   
   
   
  // Gas Close Active Area
//   solidCloseActiveArea= new G4Box(  "Gas_Close_Active_Area",
// 			550.0/2*mm,310.0/2*mm,310.0/2*mm);
//      
// 
//  
//   
//    G4VSolid* solid_subtract = new  G4SubtractionSolid ("Gas_Close_Active_Area-Active_Area", solidCloseActiveArea, solidActiveArea, 0, G4ThreeVector(0.*mm,0.,-40*mm)); 
// G4LogicalVolume* logic_substract =              
//  new G4LogicalVolume(solid_subtract,         //its solid
//                         GasMaterial,          //its material
//                         "Gas_Close_Active_Area-Active_Area");           //its name
// 
// new G4PVPlacement (0,			                    //90 deg rotation
// 				G4ThreeVector(0,0,40*mm),  //position
// 				"Gas_Close_Active_Area-Active_Area",		             		    //its name
// 				logic_substract,		                    //its logical volume
// 				physiWorld,		                    //its mother  volume
// 				false,			                    //no boolean operation
// 				0);			                    //copy number */
//   
//   //gas inside tub
    solidGas = new G4Tubs("gas",
                 	0*mm,20*mm,200*mm,0*deg, 360*deg);
       solidGas_x = new G4Tubs("gas",
                 	0*mm,22.5*mm,200*mm,0*deg, 360*deg);
//   
		             
  
  
  
  
  
   //tub
  solidTub = new G4Tubs("Tub",
                	20*mm,22.5*mm,105*mm,0*deg, 360*deg);
  
 logicTub = new G4LogicalVolume(solidTub,	        //its solid
				  AluminiumMaterial,          //its material
				  "Tub");              //its name

   physiTub = new G4PVPlacement(rm,			                    //no rotation
				G4ThreeVector(-380,0,0*mm),  //position
				"Tub",		                 	    //its name
				logicTub,		             	    //its logical volume
				physiWorld,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
//   
   G4VisAttributes* simpleTubVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); 
  simpleTubVisAtt->SetVisibility(true);
  simpleTubVisAtt->SetForceSolid(true); 
   logicTub->SetVisAttributes(simpleTubVisAtt);
       
       
       
       
       
       
       
       
       
       
       
   
     //gas inside tub redefi.

    solidGas = new G4Tubs("gas",
                	0*mm,20*mm,110*mm,0*deg, 360*deg);
  
 logicGas = new G4LogicalVolume(solidGas,	        //its solid
				  GasMaterial,          //its material
				  "gas");              //its name
/*  physiGas = new G4PVPlacement(rm,			                    //no rotation
				G4ThreeVector(-475,0,0*mm),  //position
				"gas",		                 	    //its name
				logicGas,		             	    //its logical volume
				physiWorld,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);*/	
//      G4VisAttributes* simpleGasVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0)); 
//   simpleGasVisAtt->SetVisibility(true);
//   simpleGasVisAtt->SetForceSolid(true); 
//    logicGas->SetVisAttributes(simpleGasVisAtt);

   
         //gas inside tub2
    solidGas2 = new G4Tubs("gas2",
                	0*mm,20*mm,100*mm,0*deg, 360*deg);
  
 logicGas2 = new G4LogicalVolume(solidGas2,	        //its solid
				  GasMaterial,          //its material
				  "gas2");              //its name
//   physiGas2 = new G4PVPlacement(rm,			                    //no rotation
// 				G4ThreeVector(375*mm,0,0*mm),  //position
// 				"gas2",		                 	    //its name
// 				logicGas2,		             	    //its logical volume
// 				physiWorld,		             	    //its mother  volume
// 				false,			             	    //no boolean operation
// 				0);			             	    //copy number
//   
//   
//        G4VisAttributes* simpleGas2VisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0)); 
//   simpleGas2VisAtt->SetVisibility(true);
//   simpleGas2VisAtt->SetForceSolid(true); 
//    logicGas2->SetVisAttributes(simpleGas2VisAtt);
  
   
   
   
   
   //#if Active_Area
     solidActiveArea= new G4Box(  "Active_Area",			550.0/2*mm,310.0/2*mm,310.0/2*mm);
   G4VSolid* solid_union =  new G4UnionSolid ("Active_Area_gas",  solidActiveArea, solidGas, rm, G4ThreeVector(-375.*mm,0.,-40.*mm));
    solid_union =  new G4UnionSolid ("Active_Area_gas2",  solid_union, solidGas2, rm, G4ThreeVector(375.*mm,0.,-40.*mm));  
   logicActiveArea = new G4LogicalVolume(solid_union,   	        //its solid
				  GasMaterial,          //its material
				  "Active_Area");              //its name
   physiActiveArea= new G4PVPlacement(0,			                    //90 deg rotation
				G4ThreeVector(0*mm,0,40*mm),  //position
				"Active_Area",		             		    //its name
				logicActiveArea,		                    //its logical volume
				physiWorld,		                    //its mother  volume
				false,			                    //no boolean operation
				0);			                    //copy number 
   
          G4VisAttributes* simpleActiveAreaVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.3)); 
  simpleActiveAreaVisAtt->SetVisibility(true);
  simpleActiveAreaVisAtt->SetForceSolid(true); 
   logicActiveArea->SetVisAttributes(simpleActiveAreaVisAtt);
  

  
  
  
  
  //steel box
    G4VSolid* outer_box = new G4Box(  "Box",			556.0/2*mm,317.0/2*mm,317.0/2*mm);
   G4VSolid* solid_subtract2 = new  G4SubtractionSolid ("Box-box", outer_box, solidActiveArea, 0, G4ThreeVector(0.*mm,0.,0.));  
  solid_subtract2 = new  G4SubtractionSolid ("Box-box", solid_subtract2, solidGas_x, rm, G4ThreeVector(-150.*mm,0.*mm,-40.*mm)); 
   solid_subtract2 = new  G4SubtractionSolid ("Box-box", solid_subtract2, solidGas_x, rm, G4ThreeVector(150.*mm,0.*mm,-40.*mm)); 
   
   G4LogicalVolume* logic_substract2 =              
  new G4LogicalVolume(solid_subtract2,         //its solid
                         TubMaterial,          //its material
                         "Box-box");           //its name
// // 
new G4PVPlacement (0,			                    //90 deg rotation
				G4ThreeVector(0,0,40*mm),  //position
				"Box-box",		             		    //its name
				logic_substract2,		                    //its logical volume
				physiWorld,		                    //its mother  volume
				false,			                    //no boolean operation
				0);			                    //copy number 
//   
//   
  
  //tub2
  solidTub2 = new G4Tubs("Tub2",
                	20*mm,22.5*mm,100*mm,0*deg, 360*deg);
  
 logicTub2 = new G4LogicalVolume(solidTub2,	        //its solid
				  AluminiumMaterial,          //its material
				  "Tub2");              //its name
   physiTub2 = new G4PVPlacement(rm,			                    //no rotation
				G4ThreeVector(375*mm,0,0*mm),  //position
				"Tub2",		                 	    //its name
				logicTub2,		             	    //its logical volume
				physiWorld,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
  
   G4VisAttributes* simpleTub2VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); 
  simpleTub2VisAtt->SetVisibility(true);
  simpleTub2VisAtt->SetForceSolid(true); 
   logicTub2->SetVisAttributes(simpleTub2VisAtt);
  
  

  
  
  
//        G4VisAttributes* simpleCloseActiveAreaVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0)); 
//   simpleCloseActiveAreaVisAtt->SetVisibility(true);
//   simpleCloseActiveAreaVisAtt->SetForceSolid(true); 
//    logicCloseActiveArea->SetVisAttributes(simpleCloseActiveAreaVisAtt);
  
  //pudelko stalowe
 /* 
  G4VSolid* outer_box = new G4Box(  "Box",			203*mm,203*mm,278*mm);

 
 G4VSolid* solid_subtract = new  G4SubtractionSolid ("Box-box", outer_box, solidDetector, 0, G4ThreeVector(0.*mm,0.,0.)); 
 solid_subtract = new  G4SubtractionSolid ("Box-box", solid_subtract, solidTub, 0, G4ThreeVector(0.*mm,0.,90.*mm)); 
  solid_subtract = new  G4SubtractionSolid ("Box-box", solid_subtract, solidGas, 0, G4ThreeVector(0.*mm,0.,90.*mm));
  solid_subtract = new  G4SubtractionSolid ("Box-box", solid_subtract, solidTub, 0, G4ThreeVector(0.*mm,0.,-90.*mm)); 
 solid_subtract = new  G4SubtractionSolid ("Box-box", solid_subtract, solidGas, 0, G4ThreeVector(0.*mm,0.,-90.*mm));

 
    G4LogicalVolume* logic_substract =              
 new G4LogicalVolume(solid_subtract,         //its solid
                        TubMaterial,          //its material
                        "Box-box");           //its name

new G4PVPlacement (0,			                    //90 deg rotation
				G4ThreeVector(0,0,-675*mm),  //position
				"Box-box",		             		    //its name
				logic_substract,		                    //its logical volume
				physiWorld,		                    //its mother  volume
				false,			                    //no boolean operation
				0);			                    //copy number */
  
 
 
 
 













   
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 

 
 

  
   
//cad Mesh
G4RotationMatrix * rot = new G4RotationMatrix();
rot->rotateZ(90*deg);
offset = G4ThreeVector(0*cm, 0, 0);


glob_t glob_result;
 //glob("/home/lukasz/Pulpit/do_usuniecia/cadMesh-build/export_for_GEANT/ALL/STL_multiple_binary/*.stl",GLOB_TILDE,NULL,&glob_result);// find stl files 

glob("/home/piotrek/praca/GELI/NULL_U_H_cpp/GEANT_elitpc_model_20180302/STL/*.stl",GLOB_TILDE,NULL,&glob_result);// find stl files 

   
string core, temp,file;
std::string::size_type k,l,m,n,o,p;
core="mesh_";
cout << "Loading Elements..." << endl; 
for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
  std:: ostringstream ssa;
  ssa << i;
  string str = ssa.str();
  temp=core+str;
  file=glob_result.gl_pathv[i];
//    cout << file << endl; 

  
  k = file.find("spacer");
   if (k == std::string::npos) {
//         std::cout << "not found\n";
    } else {
        std::cout << "found spacer: " << file.substr(k) << '\n';
        CADMesh * temp = new CADMesh(glob_result.gl_pathv[i], mm, offset, false);
  cad_solid = temp->TessellatedMesh();
  cad_logical = new G4LogicalVolume(cad_solid, AluminiumMaterial, "cad_logical");
  cad_physical = new G4PVPlacement(0,			                    //no rotation
				G4ThreeVector(0*mm,0*mm,-40*mm),  //position
				"cad_logical",		                 	    //its name
				cad_logical,		             	    //its logical volume
				physiActiveArea,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
   G4VisAttributes* spacer = new G4VisAttributes(G4Color(1.0, 1.0, 0, 1));
   spacer->SetVisibility(true);
   spacer->SetForceSolid(true); 
   cad_logical->SetVisAttributes(spacer);
        
    }
l = file.find("screw"); 
 if (l == std::string::npos) {
//         std::cout << "not found\n";
    } else {
        std::cout << "found screw: " << file.substr(l) << '\n';
        CADMesh * temp = new CADMesh(glob_result.gl_pathv[i], mm, offset, false);
  cad_solid = temp->TessellatedMesh();
  cad_logical = new G4LogicalVolume(cad_solid, TubMaterial, "cad_logical_screw");
  cad_physical = new G4PVPlacement(0,			                    //no rotation
				G4ThreeVector(0*mm,0*mm,-40*mm),  //position
				"cad_logical_screw",		                 	    //its name
				cad_logical,		             	    //its logical volume
				physiActiveArea,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
   G4VisAttributes* screw = new G4VisAttributes(G4Color(0.0, 1.0, 0, 1));
   screw->SetVisibility(true);
   screw->SetForceSolid(true); 
   cad_logical->SetVisAttributes(screw);
        
    }  

    
    
    
m = file.find("rod"); 
 if (m == std::string::npos) {
//         std::cout << "not found\n";
    } else {
        std::cout << "found rod: " << file.substr(m) << '\n';
        CADMesh * temp = new CADMesh(glob_result.gl_pathv[i], mm, offset, false);
  cad_solid = temp->TessellatedMesh();
  cad_logical = new G4LogicalVolume(cad_solid, AluminiumMaterial, "cad_logical");
  cad_physical = new G4PVPlacement(0,			                    //no rotation
				G4ThreeVector(0*mm,0*mm,-40*mm),  //position
				"cad_logical",		                 	    //its name
				cad_logical,		             	    //its logical volume
				physiActiveArea,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
   G4VisAttributes* rod = new G4VisAttributes(G4Color(0.5, 0.5, 0.5, 1));
   rod->SetVisibility(true);
   rod->SetForceSolid(true); 
   cad_logical->SetVisAttributes(rod);
        
    } 
  
  
  
  
 n = file.find("conn"); 
 if (n == std::string::npos) {
//         std::cout << "not found\n";
    } else {
        std::cout << "found conn: " << file.substr(n) << '\n';
        CADMesh * temp = new CADMesh(glob_result.gl_pathv[i], mm, offset, false);
  cad_solid = temp->TessellatedMesh();
  cad_logical = new G4LogicalVolume(cad_solid,TubMaterial, "cad_logical");
  cad_physical = new G4PVPlacement(0,			                    //no rotation
				G4ThreeVector(0*mm,0*mm,-40*mm),  //position
				"cad_logical",		                 	    //its name
				cad_logical,		             	    //its logical volume
				physiActiveArea,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
   G4VisAttributes* conn = new G4VisAttributes(G4Color(0.5, 0.8, 1, 1));
   conn->SetVisibility(true);
   conn->SetForceSolid(true); 
   cad_logical->SetVisAttributes(conn);
        
    } 
  
  
 
 
  o = file.find("M2 x 5"); 
 if (o == std::string::npos) {
//         std::cout << "not found\n";
    } else {
        std::cout << "found M2 x 5: " << file.substr(o) << '\n';
        CADMesh * temp = new CADMesh(glob_result.gl_pathv[i], mm, offset, false);
  cad_solid = temp->TessellatedMesh();
  cad_logical = new G4LogicalVolume(cad_solid, TubMaterial, "cad_logical_M2");
  cad_physical = new G4PVPlacement(0,			                    //no rotation
				G4ThreeVector(0*mm,0*mm,-40*mm),  //position
				"cad_logical_M2",		                 	    //its name
				cad_logical,		             	    //its logical volume
				physiActiveArea,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
   G4VisAttributes* M2 = new G4VisAttributes(G4Color(0.5, 0.3, 1, 1));
   M2->SetVisibility(true);
   M2->SetForceSolid(true); 
   cad_logical->SetVisAttributes(M2);
        
    } 
 
  
  
   p = file.find("strip"); 
 if (p == std::string::npos) {
//         std::cout << "not found\n";
    } else {
        std::cout << "found strip: " << file.substr(p) << '\n';
        CADMesh * temp = new CADMesh(glob_result.gl_pathv[i], mm, offset, false);
  cad_solid = temp->TessellatedMesh();
  cad_logical = new G4LogicalVolume(cad_solid, AluminiumMaterial, "cad_logical");
  cad_physical = new G4PVPlacement(0,			                    //no rotation
				G4ThreeVector(0*mm,0*mm,-40*mm),  //position
				"cad_logical",		                 	    //its name
				cad_logical,		             	    //its logical volume
				physiActiveArea,		             	    //its mother  volume
				false,			             	    //no boolean operation
				0);			             	    //copy number
   G4VisAttributes* M2 = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 1));
   M2->SetVisibility(true);
   M2->SetForceSolid(true); 
   cad_logical->SetVisAttributes(M2);
        
    }  
  

  


}   
   
cout << "\033[0;107;31mRead OK!: \033[0m" << endl<<endl;   
   

   


   
   
   
   
   
   
   
   
   
//    G4GDMLParser parser;  
//     parser.Write("xxx4.gdml", physiActiveArea);
   // fParser.Write(fWriteFile, fWorldPhysVol, "your-path-to-schema/gdml.xsd");
   
 //   parser.Read("pTube.gdml",true);
//    physiWorld = parser.GetWorldVolume();
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   

    
    
  

 // fScoringVolume = logicActiveArea;

  
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

  return physiWorld;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELIDetectorConstruction::ConstructSDandField()
{
//  Magnetic Field - Purging magnet
//
#if MAG
  
  if (fField.Get() == 0)
    {
      //Field grid in A9.TABLE. File must be in accessible from run urn directory. 
      G4MagneticField* GELIField= new GELITabulatedField3D("PurgMag3D.TABLE", zOffset);
      fField.Put(GELIField);
      
      //This is thread-local
      G4FieldManager* pFieldMgr = 
	G4TransportationManager::GetTransportationManager()->GetFieldManager();
           
      G4cout<< "DeltaStep "<<pFieldMgr->GetDeltaOneStep()/mm <<"mm" <<endl;
      //G4ChordFinder *pChordFinder = new G4ChordFinder(GELIField);

      pFieldMgr->SetDetectorField(fField.Get());
      pFieldMgr->CreateChordFinder(fField.Get());
      
    }
#endif
}
