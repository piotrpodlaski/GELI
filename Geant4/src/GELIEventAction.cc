/**
 * @file GELIEventAction.cc
 * @author     Piotr Podlaski
 * @brief      Implementation of GELIEventAction class
 */

#include "GELIEventAction.hh"

#include "GELIRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"

#include"GELIAnalysisManager.hh"


GELIEventAction::GELIEventAction(GELIAnalysisManager* ana)
  :printModulo(10000)
{
	analysis=ana;
}


GELIEventAction::~GELIEventAction()
{}


void GELIEventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
 if (evtNb%printModulo == 0) 
   G4cout << "\n---> Begin Of Event: " << evtNb << G4endl;
}


void GELIEventAction::EndOfEventAction(const G4Event* evt)
{
	G4int event_number=evt->GetEventID();
	for(int vtxId=0;vtxId<evt->GetNumberOfPrimaryVertex();vtxId++)
	{
		G4PrimaryVertex *vtx =evt->GetPrimaryVertex(vtxId);
		for(int primId=0;primId<vtx->GetNumberOfParticle();primId++)
		{
			G4PrimaryParticle* primPart =vtx->GetPrimary(primId);
			G4double x,y,z,px,py,pz, energy;
			G4int id, A,Z;
			x=vtx->GetX0();
			y=vtx->GetY0();
			z=vtx->GetZ0();
			px=primPart->GetMomentum().getX();
			py=primPart->GetMomentum().getY();
			pz=primPart->GetMomentum().getZ();
			energy=primPart->GetKineticEnergy();
			id=primPart->GetPDGcode();
			A=primPart->GetG4code()->GetAtomicMass();
			Z=primPart->GetG4code()->GetAtomicNumber();
			analysis->AddPrimary(x,y,z,px,py,pz,energy,id,event_number,A,Z);
		}

	}
  	analysis->SaveEvent(event_number);
}

















