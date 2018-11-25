#include <iostream>
#include <fstream>
#include "GELISteppingAction.hh"
#include "GELIRunAction.hh"
#include "GELIDetectorConstruction.hh"

#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"

#include "GELIAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"


#include "G4RunManager.hh"
#include <iostream>
#include <fstream>
#include "TH3D.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELISteppingAction::GELISteppingAction(const 
					     GELIDetectorConstruction* det, GELIAnalysisManager *ana)
:Detector(det)
{ analysis=ana;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELISteppingAction::~GELISteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELISteppingAction::UserSteppingAction(const G4Step* aStep)
  
{ 
  //Collection at SSD in N-tuples. Electrons and photons separated
  //Prestep point in World, next volume MeasureVolume, process transportation
 	G4double x, y, z, Edep; 
 	G4int event_number;
 	G4ThreeVector v1;
	G4ThreeVector v2;
	v1 = aStep->GetPreStepPoint()->GetPosition();
	v2 = aStep->GetPostStepPoint()->GetPosition();
	G4double x1, y1, x2, y2,z1,z2; //point coordinates in mm
	
 
	x1 = v1.getX()/mm;
	y1 = v1.getY()/mm;
	z1 = v1.getZ()/mm;
	x2 = v2.getX()/mm;
	y2 = v2.getY()/mm;
	z2 = v2.getZ()/mm;
	
	x = (x1 + x2) / 2;
	y = (y1 + y2) / 2;
	z = (z1 + z2) / 2;
	
	
	if (x>=-175 && x<=175 && y>=-100&& y<=100&& z>=-100&& z<=100&&aStep->GetTotalEnergyDeposit()>0){
	  
	  
	
	Edep=aStep->GetTotalEnergyDeposit()/keV;
	event_number=G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

	  analysis->Fill(x,y,z,Edep,event_number);
	}
	
	
	
 
 
 
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
