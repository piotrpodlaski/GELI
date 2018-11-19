

#ifndef GELIRunAction_h
#define GELIRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <iostream>
#include "GELIAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Run;

class GELIRunAction : public G4UserRunAction
{
public:
  
  GELIRunAction();
  ~GELIRunAction();

  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
    
  void  SetRndmFreq(G4int   val)  {saveRndm = val;}
  G4int GetRndmFreq()             {return saveRndm;}


private:
  G4int saveRndm;
  GELIAnalysisManager *analysisManager;

};

#endif













