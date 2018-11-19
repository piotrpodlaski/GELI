#include "GELIActionInitializer.hh"
#include "GELIDetectorConstruction.hh"
#include "GELIPrimaryGeneratorAction.hh"
#include "GELIRunAction.hh"
#include "GELIEventAction.hh"
#include "GELITrackingAction.hh"
#include "GELISteppingAction.hh"
#include "GELISteppingVerbose.hh"

#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GELIActionInitializer::GELIActionInitializer() : 
  G4VUserActionInitialization()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GELIActionInitializer::Build() const 
{
  const GELIDetectorConstruction* detector = 
        static_cast<const GELIDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction()); 

  SetUserAction(new GELIPrimaryGeneratorAction());

  //Optional user classes
  SetUserAction(new GELIRunAction());
  SetUserAction(new GELIEventAction());
  SetUserAction(new GELITrackingAction()); 
  SetUserAction(new GELISteppingAction(detector));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GELIActionInitializer::BuildForMaster() const
{
  SetUserAction(new GELIRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VSteppingVerbose* GELIActionInitializer::InitializeSteppingVerbose() const
{
  // Verbose output class
  return new GELISteppingVerbose();
}

