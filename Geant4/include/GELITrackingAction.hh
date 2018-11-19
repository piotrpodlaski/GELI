
#ifndef GELITrackingAction_h
#define GELITrackingAction_h 1

#include "G4UserTrackingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GELITrackingAction : public G4UserTrackingAction 
{

  public:  
    GELITrackingAction();
   ~GELITrackingAction() {};
   
    void PostUserTrackingAction(const G4Track*);

};

#endif
