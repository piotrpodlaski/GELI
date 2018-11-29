#include "GELIPrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"
#include "G4Alpha.hh"
#include "G4Gamma.hh"
#include <vector>

#include "G4String.hh"
#include "G4GeneralParticleSource.hh"

G4Mutex mPreparePrimaries = G4MUTEX_INITIALIZER;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIPrimaryGeneratorAction::GELIPrimaryGeneratorAction()
{
  gamma=G4Gamma::GammaDefinition();
  config=CentralConfig::GetInstance();
  sourcePositionOffset=config->GetD("primary_generator","GammaBeam","position_offset");
  gammaEnergy=config->GetI("primary_generator","GammaBeam","gamma_energy");
  generatorType=config->Get("primary_generator", "generator_type");
  nGammas=config->GetI("primary_generator","GammaBeam","n_gammas_to_prepare");

  if(generatorType=="GPS")
  {
    GPSGun=new G4GeneralParticleSource(); 
  }
  #ifdef USE_GAMMA_BEAM_GENERATOR
  else if(generatorType=="GammaBeam")
  {
    particleGun=new G4ParticleGun(1);
    particleGun->SetParticleDefinition(gamma);
    PrepareGammaPrimaries();
  }
  #endif
  else
    G4Exception("GELIPrimaryGeneratorAction::GELIGELIPrimaryGeneratorAction","ELITPC",FatalException,
      "Undefined primary generator, check config file.If GammaBeam is selected make sure that software is compiled with support for GammaBeam");
}


void GELIPrimaryGeneratorAction::PrepareGammaPrimaries()
{
  G4AutoLock l(&mPreparePrimaries);
  #ifdef USE_GAMMA_BEAM_GENERATOR
  GammaSource* gammaSource = new GammaSource(gammaEnergy,sourcePositionOffset);
  positions.clear();
  momenta.clear();
  positions.reserve(nGammas);
  momenta.reserve(nGammas);
  for(int i=0;i<nGammas;i++)
  {
    std::vector<double> momentum(3);
    std::vector<double> position(3);
    gammaSource->GetRandomMomentum(momentum, position);
    G4double energy= gammaSource->GetRandomEnergy()*MeV;
    positions.push_back(G4ThreeVector(position.at(0)*mm,position.at(1)*mm,position.at(2)*mm));
    momenta.push_back(G4ThreeVector(momentum.at(0),momentum.at(1),momentum.at(2)));
    energies.push_back(energy);
  }
  #endif 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIPrimaryGeneratorAction::~GELIPrimaryGeneratorAction()
{
  delete particleGun;
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELIPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  if(generatorType=="GPS")
  {
    GPSGun->GeneratePrimaryVertex(anEvent);
  }
  #ifdef USE_GAMMA_BEAM_GENERATOR
  else if(generatorType=="GammaBeam")
  {
    int eventId=anEvent->GetEventID();
    eventId=eventId%nGammas;
    particleGun->SetParticleEnergy(energies.at(eventId));
    particleGun->SetParticlePosition(positions.at(eventId));
    particleGun->SetParticleMomentumDirection(momenta.at(eventId));
    particleGun->GeneratePrimaryVertex(anEvent);
  }
  #endif


}



