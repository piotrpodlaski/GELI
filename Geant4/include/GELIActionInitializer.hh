#ifndef GELIActionInitializer_h
#define GELIActionInitializer_h 1

#include "G4VUserActionInitialization.hh"
#include "G4VSteppingVerbose.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GELIActionInitializer : public G4VUserActionInitialization
{
public:

  GELIActionInitializer();
  ~GELIActionInitializer(){;};
  
  void Build() const;
  void BuildForMaster() const;
  G4VSteppingVerbose* InitializeSteppingVerbose() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

