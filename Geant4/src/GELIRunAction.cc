#include "GELIRunAction.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include "GELIAnalysisManager.hh"
#include "CentralConfig.hh"



GELIRunAction::GELIRunAction()
{   
  saveRndm = 1;
  GELIAnalysisManager::ConfigureOutput();
   
}

GELIRunAction::~GELIRunAction()
{}


void GELIRunAction::BeginOfRunAction(const G4Run* aRun)
{  
  //Analysis must be handled by master and workers
  GELIAnalysisManager* analysis = GELIAnalysisManager::GetInstance();
  analysis->book();

  if (IsMaster())    
    G4cout << "---> Run " << aRun->GetRunID() << " (master) start." 
	   << G4endl;
  else
    G4cout << "---> Run " << aRun->GetRunID() << " (worker) start." 
	   << G4endl;

  
  // save Rndm status
  if (saveRndm > 0 && IsMaster())
    { 
      G4Random::showEngineStatus();
      G4Random::saveEngineStatus("beginOfRun.rndm");
    }
      
}



void GELIRunAction::EndOfRunAction(const G4Run* aRun)
{  
  
  GELIAnalysisManager* analysis = GELIAnalysisManager::GetInstance();
  analysis->finish();
  if (IsMaster())    
    G4cout << "Total number of event = " << aRun->GetNumberOfEvent() << G4endl;
  else
    G4cout << "Partial number of event in this worker = " 
	   << aRun->GetNumberOfEvent() << G4endl;
 
       
  if (IsMaster())
    {
      // save Rndm status
      if (saveRndm == 1)
	{ 
	  G4Random::showEngineStatus();
	  G4Random::saveEngineStatus("endOfRun.rndm");
	}             
    }            
}









