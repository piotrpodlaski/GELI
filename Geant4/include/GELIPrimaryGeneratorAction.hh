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
  void GeneratePrimaries(G4Event*);
  
private:
	static void PrepareGammaPrimaries();
	static void PrepareGeneratorPrimaries();
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
	static std::vector<G4double> energies;
	static std::vector<G4ThreeVector> positions;
	static std::vector<G4ThreeVector> momenta;
	static bool gammaPrepared;
	//variables for event generator:
	static std::vector<G4double> theta1;
	static std::vector<G4double> theta2;
	static std::vector<G4double> phi1;
	static std::vector<G4double> phi2;
	static std::vector<G4double> energy1;
	static std::vector<G4double> energy2;
	static bool generatorPrepared;
	std::string generatorConfigName;
	int A1, A2, Z1, Z2;
	int nGammas;
	int nEvents;
};

#endif


