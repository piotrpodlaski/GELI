#ifndef EVENTREADER_H
#define EVENTREADER_H

#include <iostream>
#include <map>

#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "CentralConfig.hh"

class EventReader
{
public:
	EventReader(TString fname);
	~EventReader();
	void ReadEvent(SimEvent* event);
	bool EndOfFile();
private:
	TFile *input_file;
	TTree *edep_tree;
	TTree *primary_tree;
	CentralConfig *config;
	std::map<int,Primaries> primaries_map;
	int nEntriesPrim;
	int nEntriesEdep;
	int current_entry;
	int current_event;
	double x,y,z,Edep;//for energy deposit tree
	int event;
	void ReadPrimaries();
	
};

#endif