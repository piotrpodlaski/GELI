#ifndef GELIANALYSISMANAGER_HH
#define GELIANALYSISMANAGER_HH

#include "globals.hh"
#include <vector>
#include "G4ThreeVector.hh"
#include "g4root.hh"
#include "CentralConfig.hh"
#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include <vector>
//#include "G4AnalysisManager.hh"

class GELIAnalysisManager
{
public:
	GELIAnalysisManager(); 
 	~GELIAnalysisManager();
 	//For MT mode output files have to be opened in RunAction constructor,
 	//not in AnalysisManager constructor - without it merging of the Ntuples does not work
 	static void ConfigureOutput();
 	void book();
 	void finish();
 	static GELIAnalysisManager* GetInstance();
 	void Fill(G4double x, G4double y, G4double z,G4double eDep, G4int event_number);
 	void SaveEvent(G4int eventID);
 	void AddPrimary(G4double x, G4double y, G4double z,
 					G4double px, G4double py, G4double pz,
 					G4double energy, G4int id, G4int event_number, G4int A=0, G4int Z=0);
private:  
 	static GELIAnalysisManager* instance;
  
private:
// 	G4AnalysisManager* analysisManager;
	SimEvent *event;
	TFile* file;
	TTree* tree;
	CentralConfig *config;
	bool saveNtuple;
	bool saveCustomTree;
	bool HasEdepLimits; //flag for presence of Edep limits
	double xL, xU, yL, yU, zL, zU;//limits for Edep storage
	std::vector<G4double> *vx;
	std::vector<G4double> *vy;
	std::vector<G4double> *vz;
	std::vector<G4double> *vEdep;
};
#endif




