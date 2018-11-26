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
class EfficiencySimulator;

class Worker
{
public:
	Worker(EventReader* ev_reader, std::string fname);
	~Worker();
	void Run();
private:
	EventReader *reader;
	CentralConfig *config;
	DiffusionSimulator *diffusion;
	AttachmentSimulator *attachment;
	EfficiencySimulator *efficiency;
	bool simulateDiffusion;
	bool simulateAttachment;
	bool simulateEfficiency;
	TTree* tree;
	TFile* out_file;
	SimEvent *event;
	static int nWorkers;
	int workerID;
	static std::mutex write_mutex;

};

#endif