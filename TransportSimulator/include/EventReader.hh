#ifndef EVENTREADER_H
#define EVENTREADER_H

#include <iostream>
#include <map>
#include <vector>

#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "CentralConfig.hh"

class EventReader
{
	typedef std::vector<double> vect;
public:
	EventReader(TString fname);
	~EventReader();
	void ReadEvent(SimEvent* event);
	bool EndOfFile();
	static void BuildEvent(SimEvent* event, vect *vx, vect *vy, vect *vz, vect *vEdep);
private:
	TString file_name;
	TFile *input_file;
	TTree *edep_tree;
	TTree *primary_tree;
	CentralConfig *config;
	std::map<int,Primaries> primaries_map;
	int nEntriesPrim;
	int nEntriesEdep;
	int current_entry;
	int current_event;
	std::vector<double> *x=0,*y=0,*z=0,*Edep=0;//for energy deposit tree
	int event;
	void ReadPrimaries();
	int nEventsToMerge;
	
};

#endif