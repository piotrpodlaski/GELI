#ifndef WORKER_H
#define WORKER_H

#include <mutex>

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
	~Worker();
	void operator()();
	void Run();
private:
	EventReader *reader;
	CentralConfig *config;
	DiffusionSimulator *diffusion;
	AttachmentSimulator *attachment;
	bool simulateDiffusion;
	bool simulateAttachment;
	TTree* tree;
	TFile* out_file;
	SimEvent *event;
	static int nWorkers;
	int workerID;
	static std::mutex write_mutex;

};

#endif