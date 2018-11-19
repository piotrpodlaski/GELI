

#ifndef GELIEventAction_h
#define GELIEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GELIEventAction : public G4UserEventAction
{
  public:
  
    GELIEventAction();
   ~GELIEventAction();

    void BeginOfEventAction(const G4Event*);
    void   EndOfEventAction(const G4Event*);
    
    void SetDrawFlag   (G4String val)  {drawFlag    = val;};
    void SetPrintModulo(G4int    val)  {printModulo = val;};
        
  private:
    G4String                 drawFlag;
    G4int                    printModulo;         
};

#endif

    
