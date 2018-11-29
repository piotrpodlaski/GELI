
#include "GELIDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "GELITPCDetector.hh"
#include "CentralConfig.hh"
#include "G4FieldManager.hh"
#include "MaterialBuilder.hh"
#include "GELITabulatedField3D.hh"
#include "G4TransportationManager.hh"
#include <cmath>



GELIDetectorConstruction::GELIDetectorConstruction()
{

}

GELIDetectorConstruction::~GELIDetectorConstruction()
{
}

G4VPhysicalVolume* GELIDetectorConstruction::Construct()
{
    MaterialBuilder* mat_builder=MaterialBuilder::GetInstance();
    G4Material* mixture=mat_builder->GetMaterial("mixture");
    world_solid = new G4Box("world_solid", 100*cm, 100*cm, 100*cm);
    world_logical = new G4LogicalVolume(world_solid, mixture,"world_logical",0,0,0);
    world_physical = new G4PVPlacement(0, G4ThreeVector(), world_logical,
       "world_physical", 0, false, 0);
    world_logical->SetVisAttributes(G4VisAttributes::Invisible);

    GELITPCDetector::BuildTPCDetector(world_logical);

    return world_physical;
}

void GELIDetectorConstruction::ConstructSDandField()
{
//  Magnetic Field - Purging magnet
//

  if (magneticField.Get() == 0)
  {
    CentralConfig* config=CentralConfig::GetInstance();

    std::string mag_file_name=config->Get("magnetic_field_map");
    double mag_offset=config->GetD("magnetic_field_offset");
    G4MagneticField* GELIField= new GELITabulatedField3D(mag_file_name.c_str(), mag_offset*mm);
    magneticField.Put(GELIField);

  //This is thread-local
    G4FieldManager* pFieldMgr = 
    G4TransportationManager::GetTransportationManager()->GetFieldManager();

    G4cout<< "DeltaStep "<<pFieldMgr->GetDeltaOneStep()/mm <<"mm" <<endl;


    pFieldMgr->SetDetectorField(magneticField.Get());
    pFieldMgr->CreateChordFinder(magneticField.Get());
  }
}
