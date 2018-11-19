#include "GELIEventAction.hh"

#include "GELIRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"

#include"GELIAnalysisManager.hh"
#include "EventSaver.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIEventAction::GELIEventAction()
  :drawFlag("all"),printModulo(10000)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIEventAction::~GELIEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELIEventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
 //if (evtNb%printModulo == 0) 
   G4cout << "\n---> Begin Of Event: " << evtNb << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELIEventAction::EndOfEventAction(const G4Event* evt)
{
	GELIAnalysisManager *analysis= GELIAnalysisManager::GetInstance();
	G4int event_number=evt->GetEventID();
	for(int vtxId=0;vtxId<evt->GetNumberOfPrimaryVertex();vtxId++)
	{
		G4PrimaryVertex *vtx =evt->GetPrimaryVertex(vtxId);
		for(int primId=0;primId<vtx->GetNumberOfParticle();primId++)
		{
			G4PrimaryParticle* primPart =vtx->GetPrimary(primId);
			G4double x,y,z,px,py,pz, energy;
			G4int id;
			x=vtx->GetX0();
			y=vtx->GetY0();
			z=vtx->GetZ0();
			px=primPart->GetMomentum().getX();
			py=primPart->GetMomentum().getY();
			pz=primPart->GetMomentum().getZ();
			energy=primPart->GetKineticEnergy();
			id=primPart->GetPDGcode();
			analysis->AddPrimary(x,y,z,px,py,pz,energy,id,event_number);
		}

	}
  	analysis->SaveEvent();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

















