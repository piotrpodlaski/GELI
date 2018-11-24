#ifndef WORKER_H
#define WORKER_H


class EventReader;
class CentralConfig;
class TTree;
class TFile;
class SimEvent;
class DiffusionSimulator;
class AttachmentSimulator;

class Worker
{
public:
	Worker(EventReader* ev_reader);
	void operator()();
private:
	EventReader *reader;
	CentralConfig *config;
	DiffusionSimulator *diffusion;
	AttachmentSimulator *attachment;
	bool simulateDiffusion;
	bool simulateAttachment;
	TTree* tree;
	TFile* out_file;
	SimEvent *ev;

};

#endif