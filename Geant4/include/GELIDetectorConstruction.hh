
#ifndef GELIDetectorConstruction_h
#define GELIDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Cache.hh"
#include "G4MagneticField.hh"
#include <string>

class G4Box;
class G4Trd;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class GELITabulatedField3D;
class G4VSolid;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GELIDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  GELIDetectorConstruction();
  ~GELIDetectorConstruction();

public:  
     
  G4VPhysicalVolume* Construct();
  void ConstructSDandField();
     
public:

  void PrintDetectorParameters();
                    
  G4double GetWorldSizeXY()  const       {return WorldSizeXY;};
  G4double GetWorldSizeZ() const          {return WorldSizeZ;}; 

  G4double GetMeasureVolumeSizeXY() const {return MeasureVolumeSizeXY;}; 
  G4double GetMeasureVolumeSizeZ() const  {return MeasureVolumeSizeZ;};

  G4double GetGapSizeX1()            {return GapSizeX1;}; 
  G4double GetGapSizeX2()            {return GapSizeX2;}; 
  G4double GetGapSizeY1()            {return GapSizeY1;}; 
  G4double GetGapSizeY2()            {return GapSizeY2;}; 
  G4double GetGapSizeZ()             {return GapSizeZ;};

  G4Material* GetWorldMaterial()         {return WorldMaterial;};
  G4Material* GetGapMaterial()           {return GapMaterial;};
  //G4Material* GetWindowMaterial()           {return WindowMaterial;};  

  const G4VPhysicalVolume* GetWorld() const          {return physiWorld;};           
  const G4VPhysicalVolume* GetMeasureVolume() const  {return physiMeasureVolume;};  
  const G4VPhysicalVolume* GetActive_Area() const  {return physiActiveArea;};          
  const G4VPhysicalVolume* GetGap1() const           {return physiGap1;};
  const G4VPhysicalVolume* GetGap2() const      {return physiGap2;};
  const G4VPhysicalVolume* GetWindow() const      {return physiWindow;};
void SetCADFilename(std::string name) {
        filename = name;
    };
void SetCADFiletype(std::string type) {
        filetype = type;
    };
 //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; };
private:
   

//G4LogicalVolume*  fScoringVolume;
  G4double           WorldSizeXY;
  G4double           WorldSizeZ;

  G4double           MeasureVolumeSizeXY;
  G4double           MeasureVolumeSizeZ;
  G4double           MeasureVolumePosition;

  G4double           GapSizeX1;
  G4double           GapSizeX2;
  G4double           GapSizeY1;
  G4double           GapSizeY2;
  G4double           GapSizeZ;
  G4double           Gap1PosX; 
  G4double           Gap1PosY; 
  G4double           Gap1PosZ; 
  G4double           Gap2PosX; 
  G4double           Gap2PosY; 
  G4double           Gap2PosZ; 

  G4double           SSD;
  G4double           zOffset;

  G4VPhysicalVolume* physiWorld;
  G4LogicalVolume*   logicWorld;  
  G4Box*             solidWorld;
  

  G4VPhysicalVolume* physiGap1;
  G4LogicalVolume*   logicGap1;
  G4Box*             solidGap1;


  G4VPhysicalVolume* physiGap2;
  G4LogicalVolume*   logicGap2;
  G4Box*             solidGap2;

  G4VPhysicalVolume* physiWindow;
  G4LogicalVolume*   logicWindow;
  G4Tubs*             solidWindow;

  G4VPhysicalVolume* physiWindow2;
  G4LogicalVolume*   logicWindow2;
  G4Tubs*             solidWindow2;

  G4VPhysicalVolume* physiMeasureVolume;
  G4LogicalVolume*   logicMeasureVolume;
  G4Tubs*             solidMeasureVolume;

  G4VPhysicalVolume* physiGas;
  G4LogicalVolume*   logicGas;
  G4Tubs*             solidGas;

  G4VPhysicalVolume* physiGas2;
  G4LogicalVolume*   logicGas2;
  G4Tubs*             solidGas2;

  G4VPhysicalVolume* physiTub;
  G4LogicalVolume*   logicTub;
  G4Tubs*             solidTub;


  G4Tubs*             solidGas_x;


  G4VPhysicalVolume* physiTub2;
  G4LogicalVolume*   logicTub2;
  G4Tubs*             solidTub2;




  G4VPhysicalVolume* physiActiveArea;
  G4LogicalVolume*   logicActiveArea;
  G4Box*             solidActiveArea;


//  G4VPhysicalVolume* physiCloseActiveArea;
//  G4LogicalVolume*   logicCloseActiveArea;
 G4Box*             solidCloseActiveArea;

  G4Material*        WorldMaterial;
  G4Material*        GapMaterial;
  G4Material*	     WindowMaterial;
  G4Material*	     GasMaterial;
  G4Material*	     TubMaterial;
  G4Material*	     GermanMaterial;
  G4Material*	     AluminiumMaterial;

  std::string filename;
    std::string filetype;
   G4ThreeVector offset;
    G4VSolid * cad_solid;
    G4LogicalVolume * cad_logical;
    G4VPhysicalVolume * cad_physical;


  G4Cache<G4MagneticField*> fField;  //pointer to the thread-local fields

private:
  


  void DefineMaterials();
  G4VPhysicalVolume* ConstructCalorimeter();     
  G4VPhysicalVolume* ConstructPP();     
};


#endif


