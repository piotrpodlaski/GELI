#include "GELIPrimaryGeneratorAction.hh"

#include "GELIDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"
#include "G4Alpha.hh"


#include "G4AutoLock.hh"
#include "TFile.h"
#include "TNtuple.h"
#include "TTree.h"
#include "G4String.hh"
#include "G4DataVector.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"
//Print position of primaries.
#define POSITION 0



namespace {
    G4bool isFileRead = false;
    G4Mutex mFileRead = G4MUTEX_INITIALIZER;
    //Primary kinematics
    G4DataVector fX;
    G4DataVector fY;
    G4DataVector fZ;

    

    
    G4DataVector fPx;
    G4DataVector fPy;
    G4DataVector fPz;
    G4DataVector fE;
    
    size_t nextEventId = 0;
    G4Mutex mNextEventId = G4MUTEX_INITIALIZER;

    size_t GetNextId() {
        G4AutoLock l(&mNextEventId);
        if ( nextEventId >= fX.size() ) //file data are over,  restart file
            {
                G4Exception("PrimaryGeneratorAction::GeneratePrimaries","ELITPC",
                            JustWarning,"Data file with kinematics is over, restart it");
                nextEventId=0;
            }
        return nextEventId++;
    }
    
    void ReadKinematicFromFile(G4double energy) {
        //Only one thread shoud read input file
        G4AutoLock l(&mFileRead);
        if ( isFileRead ) return;
        // Read Kinematics from file
	Double_t posX, posY,posZ,momentumX,momentumY,momentumZ,energyy;
// 	TFile *myfile= TFile::Open("parameters_to_gean4_8.3MeV.root");
	TFile *myfile= TFile::Open("out_8.3MeV.root");
	
	
	TTree *tree= (TTree*)myfile->Get("gammaBeam");
	tree->SetBranchAddress("posX",&posX);
	tree->SetBranchAddress("posY",&posY);
	tree->SetBranchAddress("posZ",&posZ);
	tree->SetBranchAddress("momentumX",&momentumX);
	tree->SetBranchAddress("momentumY",&momentumY);
	tree->SetBranchAddress("momentumZ",&momentumZ);
	tree->SetBranchAddress("energy",&energyy);
	float N_gamma=tree->GetEntries();
	std::cout<<N_gamma;
// 	G4String file_name = "parameters_to_gean4_17MeV.root";
// 	TFile in_file(file_name,"READ");
// 	TNtuple* my_tuple;
// 	in_file.GetObject("gammaBeam",my_tuple);
// 	float N_gamma=my_tuple->GetEntries();
// 	float* row_content;
   for(int irow=0;irow<N_gamma;++irow){
     tree->GetEntry(irow);


     //positions
     fX.push_back(posX);
     fY.push_back(posY);
     fZ.push_back(posZ);
    
          //momentum
     fPx.push_back(momentumX);
     fPy.push_back(momentumY);
     fPz.push_back(momentumZ);
     
     //energy
      fE.push_back(energyy*MeV);

   }
	
	G4cout << "Read " << fX.size() << " events from file " << myfile << G4endl;
	
	 
    
     
     

        isFileRead= true;

	


        return;
    }
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIPrimaryGeneratorAction::GELIPrimaryGeneratorAction()
  :rndmVertex(false)
{
  
  
  

  //default kinematic
  G4int n_particle = 1;
 /* particleGun  = new G4ParticleGun(n_particle);
  
  G4ParticleDefinition* particle
    = G4Alpha::Definition();

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleEnergy(6.*MeV);
 //  particleGun->SetParticleEnergy(20*MeV);
    particleGun->SetParticlePosition(G4ThreeVector(-175.*mm,0,0));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(1,
                  0,
                  0)); 
*/
    particleGun=new G4GeneralParticleSource();


  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GELIPrimaryGeneratorAction::~GELIPrimaryGeneratorAction()
{
  delete particleGun;
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GELIPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

   particleGun->GeneratePrimaryVertex(anEvent);


}



