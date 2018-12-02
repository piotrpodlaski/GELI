#ifndef GELIANALYSISMANAGER_H
#define GELIANALYSISMANAGER_H

#include "globals.hh"
#include <vector>
#include "G4ThreeVector.hh"
#include "g4root.hh"
#include "CentralConfig.hh"
#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include <vector>



/**
 * @brief      Class to handle simulation output to files
 */
class GELIAnalysisManager
{
public:

	/**
	 * @brief      Constructor
	 */
	GELIAnalysisManager();

 	/**
 	 * @brief      Destructor
 	 */
 	~GELIAnalysisManager();
 	//For MT mode output files have to be opened in RunAction constructor,
 	//not in AnalysisManager constructor - without it merging of the Ntuples does not work
 	
 	/**
 	 * @brief      Configures simulation output
 	 */
 	static void ConfigureOutput();

 	/**
 	 * @brief      Prepare simulation output
 	 * @details    Opens output files, creates Ntuples and ROOT tree accordignly
 	 *             to config file
 	 */
 	void book();

 	/**
 	 * @brief      Finishes simulation output
 	 * @details    Saves Ntuples and ROOT tree to file and closes the file. If
 	 *             selected in config it also merges output files created by
 	 *             each thread into single output file.
 	 */
 	void finish();

 	/**
 	 * @brief      Fills output with single energy deposit
 	 * @details    Method is called in each  tracking step. It adds energy
 	 *             deposit to Ntuples and custom SimEvent objects. Energy
 	 *             deposit Ntuple is made of vectors to hold deposit positions
 	 *             and value. Each event has single entry in energy deposit
 	 *             NTuple. This method adds deposit info to vectors.
 	 */
 	void Fill(G4double x, G4double y, G4double z,G4double eDep, G4int event_number);

 	/**
 	 * @brief      Saves current event to file
 	 * @details    For Ntuple it adds one Ntuple row, in SimEvent mode it fills
 	 *             the ROOT tree with current event object
 	 */
 	void SaveEvent(G4int eventID);


 	/**
 	 * @brief      Adds information about primary particle to current event
 	 */
 	void AddPrimary(G4double x, G4double y, G4double z,
 					G4double px, G4double py, G4double pz,
 					G4double energy, G4int id, G4int event_number, G4int A=0, G4int Z=0);

  
private:
	SimEvent *event;
	TFile* file;
	TTree* tree;
	CentralConfig *config;
	bool saveNtuple;
	bool saveCustomTree;
	bool HasEdepLimits; //flag for presence of Edep limits
	bool isBackground;
	double xL, xU, yL, yU, zL, zU;//limits for Edep storage
	std::vector<G4double> *vx;
	std::vector<G4double> *vy;
	std::vector<G4double> *vz;
	std::vector<G4double> *vEdep;
};
#endif




