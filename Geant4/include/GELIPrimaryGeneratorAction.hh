#ifndef GELIPrimaryGeneratorAction_h
#define GELIPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"
#include <string>
#include "CentralConfig.hh"

#ifdef USE_GAMMA_BEAM_GENERATOR
	#include "GammaSource.h"
#endif


class G4ParticleGun;
class G4Event;
class G4DataVector;
class G4ParticleDefinition;


class GELIPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  GELIPrimaryGeneratorAction();    
  ~GELIPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);
  
private:
	void PrepareGammaPrimaries();
	CentralConfig* config;
	G4ParticleGun* particleGun;
	G4GeneralParticleSource *GPSGun;
	std::string generatorType;
	int gammaEnergy;
	double sourcePositionOffset;
	G4ParticleDefinition* gamma;
	unsigned int nGammasInEvent;
	std::vector<G4double> energies;
	std::vector<G4ThreeVector> positions;
	std::vector<G4ThreeVector> momenta;
	int nGammas;
};

#endif


