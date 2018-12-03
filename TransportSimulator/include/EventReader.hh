/**
 * @file EventReader.hh
 * @author     Piotr Podlaski
 * @brief      Definition of EventReader class
 */

#ifndef EVENTREADER_H
#define EVENTREADER_H

/// \cond
#include <iostream>
#include <map>
#include <vector>
/// \endcond
#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "CentralConfig.hh"


/**
 * @brief      Class reads files with Ntuples outputed by Geant4 and builds
 *             SimEvent objects
 */
class EventReader
{
	typedef std::vector<double> vect;
public:

	/**
	 * @brief      Constructor
	 */
	EventReader(TString fname);
	
	/**
	 * @brief      Destructor
	 */
	~EventReader();

	/**
	 * @brief      Reads an event from a fie.
	 */
	void ReadEvent(SimEvent* event);

	/**
	 * @brief      Tells if input file is over
	 */
	bool EndOfFile();

	/**
	 * @brief      Builds an event form vectors describing energy deposits.
	 */
	static void BuildEvent(SimEvent* event, vect *vx, vect *vy, vect *vz, vect *vEdep);
private:
	TString file_name; ///< Name of the input file
	TFile *input_file; ///< Input file
	TTree *edep_tree; ///< ROOT tree with energy deposits
	TTree *primary_tree; ///< ROOT tree with primary particles
	CentralConfig *config; ///< Pointer to CentralConfig object
	std::map<int,Primaries> primaries_map; ///< Map with primary particles
	int nEntriesPrim; ///< number of entries in energy deposit tree
	int nEntriesEdep; ///< number of entries in primary particle tree
	int current_entry; ///< current entry in energy deposit tree
	int current_event; ///< ID of a current event
	std::vector<double> *x=0; ///< Vector with X position of energy deposit, to be used as a ROOT tree branch
	std::vector<double> *y=0; ///< Vector with Y position of energy deposit, to be used as a ROOT tree branch
	std::vector<double> *z=0; ///< Vector with Z position of energy deposit, to be used as a ROOT tree branch
	std::vector<double> *Edep=0; ///< Vector with values of energy deposit, to be used as a ROOT tree branch
	int event; ///< Event iD, to be used as a ROOT tree branch
	
	/**
	 * @brief      Read information about primaries from the files and puts them into primaries_map
	 */
	void ReadPrimaries();
	int nEventsToMerge; ///< Number of Geant4 events to be merged into single SimEvent, used for background events
	
};

#endif