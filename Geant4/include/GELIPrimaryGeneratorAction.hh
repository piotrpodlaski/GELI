#ifndef GELIPrimaryGeneratorAction_h
#define GELIPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"
#include <string>
#include "CentralConfig.hh"



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
	void PrepareGeneratorPrimaries();
	CentralConfig* config;
	G4ParticleGun* particleGun;
	G4GeneralParticleSource *GPSGun;
	std::string generatorType;
	int gammaEnergy;
	double sourcePositionOffset;
	G4ParticleDefinition* gamma;
	G4ParticleDefinition* genericIon;
	unsigned int nGammasInEvent;
	//variables for gamma beam:
	std::vector<G4double> energies;
	std::vector<G4ThreeVector> positions;
	std::vector<G4ThreeVector> momenta;
	//variables for event generator:
	std::vector<G4double> theta1;
	std::vector<G4double> theta2;
	std::vector<G4double> phi1;
	std::vector<G4double> phi2;
	std::vector<G4double> energy1;
	std::vector<G4double> energy2;
	std::string generatorConfigName;
	int A1, A2, Z1, Z2;
	int nGammas;
	int nEvents;
};

#endif


