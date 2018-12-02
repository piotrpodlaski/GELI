#include "GELIActionInitializer.hh"
#include "GELIDetectorConstruction.hh"
#include "GELIPrimaryGeneratorAction.hh"
#include "GELIRunAction.hh"
#include "GELIEventAction.hh"
#include "GELISteppingAction.hh"
#include "GELISteppingVerbose.hh"
#include "GELIAnalysisManager.hh"
#include "G4RunManager.hh"


GELIActionInitializer::GELIActionInitializer() : 
  G4VUserActionInitialization()
{
}


void GELIActionInitializer::Build() const 
{

  SetUserAction(new GELIPrimaryGeneratorAction());
  GELIAnalysisManager * analysis = new GELIAnalysisManager();
  //Optional user classes
  SetUserAction(new GELIRunAction(analysis));
  SetUserAction(new GELIEventAction(analysis));
  SetUserAction(new GELISteppingAction(analysis));
}


void GELIActionInitializer::BuildForMaster() const
{
  GELIAnalysisManager * analysis = new GELIAnalysisManager();
  SetUserAction(new GELIRunAction(analysis));
}

G4VSteppingVerbose* GELIActionInitializer::InitializeSteppingVerbose() const
{
  return new GELISteppingVerbose();
}

