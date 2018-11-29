#ifndef GELIDETECTORCONSTRUCTION_H
#define GELIDETECTORCONSTRUCTION_H

#include <string>
#include "G4MagneticField.hh"

#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"



class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;


class GELIDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    GELIDetectorConstruction();
    ~GELIDetectorConstruction();
    G4VPhysicalVolume* Construct();
    void ConstructSDandField();

  private:
    G4VSolid * world_solid;
    G4LogicalVolume* world_logical;
    G4VPhysicalVolume* world_physical;
    G4Cache<G4MagneticField*> magneticField;
};

#endif

