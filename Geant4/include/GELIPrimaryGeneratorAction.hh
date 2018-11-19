#ifndef GELIPrimaryGeneratorAction_h
#define GELIPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4DataVector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GELIPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  GELIPrimaryGeneratorAction();    
  ~GELIPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);
  void SetRndmVertex(G4bool val) { rndmVertex = val;} 
  
private:
  //G4ParticleGun*                  particleGun;
 G4GeneralParticleSource *particleGun;
  G4bool                       rndmVertex;      
};

#endif


