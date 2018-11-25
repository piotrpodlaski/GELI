
#ifndef GELISteppingAction_h
#define GELISteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4VPVParameterisation.hh"
#include "G4PVParameterised.hh"
#include "G4Tubs.hh"
#include "GELIAnalysisManager.hh"

class GELIDetectorConstruction;
class GELIAnalysisManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GELISteppingAction : public G4UserSteppingAction
{
public:
  GELISteppingAction(const GELIDetectorConstruction*, GELIAnalysisManager*);
  ~GELISteppingAction();
  
  void UserSteppingAction(const G4Step*);
  
private:
  const GELIDetectorConstruction* Detector; 
  GELIAnalysisManager* analysis;
  
};

#endif




