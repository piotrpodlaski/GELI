#include "GELIActionInitializer.hh"
#include "GELIDetectorConstruction.hh"
#include "GELIPrimaryGeneratorAction.hh"
#include "GELIRunAction.hh"
#include "GELIEventAction.hh"
#include "GELITrackingAction.hh"
#include "GELISteppingAction.hh"
#include "GELISteppingVerbose.hh"
#include "GELIAnalysisManager.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GELIActionInitializer::GELIActionInitializer() : 
  G4VUserActionInitialization()
{
  analysis = new GELIAnalysisManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GELIActionInitializer::Build() const 
{
//  const GELIDetectorConstruction* detector = 
//        static_cast<const GELIDetectorConstruction*>
//        (G4RunManager::GetRunManager()->GetUserDetectorConstruction()); 

  SetUserAction(new GELIPrimaryGeneratorAction());
  GELIAnalysisManager * analysis = new GELIAnalysisManager();
  //Optional user classes
  SetUserAction(new GELIRunAction(analysis));
  SetUserAction(new GELIEventAction(analysis));
  SetUserAction(new GELITrackingAction()); 
  SetUserAction(new GELISteppingAction(analysis));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GELIActionInitializer::BuildForMaster() const
{
  SetUserAction(new GELIRunAction(analysis));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VSteppingVerbose* GELIActionInitializer::InitializeSteppingVerbose() const
{
  // Verbose output class
  return new GELISteppingVerbose();
}

