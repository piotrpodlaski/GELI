#ifndef EVENTSAVER_H
#define EVENTSAVER_H

#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include "G4String.hh"
#include "CentralConfig.hh"

class EventSaver
{
public:
	~EventSaver();
	static EventSaver* GetInstance();
	bool IsFileOpen();
	void Init();
	void Close();
	void FillEvent(double x, double y, double z, double eDep);
	void FillTree();
private:
	EventSaver();
	static EventSaver* instance;
	SimEvent *event;
	TFile* file;
	TTree* tree;
	bool isInitialized;
	CentralConfig *config;

};


#endif