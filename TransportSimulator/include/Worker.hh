/**
 * @file Worker.hh
 * @author     Piotr Podlaski
 * @brief      Definition of Worker class
 */

#ifndef WORKER_H
#define WORKER_H

#include <string>

class EventReader;
class CentralConfig;
class TTree;
class TFile;
class SimEvent;
class DiffusionSimulator;
class AttachmentSimulator;
class GainSimulator;

/**
 * @brief      Class that handles complete transport simulation
 */
class Worker
{
public:

	/**
	 * @brief      Construtor
	 */
	Worker(EventReader* ev_reader, std::string fname);
	
	/**
	 * @brief      Destructor
	 */
	~Worker();
	
	/**
	 * @brief      Starts the simulation
	 */
	void Run();
private:
	EventReader *reader; ///<Pointer to EventReader object
	CentralConfig *config; ///<Pointer to CentralConfig object
	DiffusionSimulator *diffusion; ///<Pointer to DiffusionSimulator object
	AttachmentSimulator *attachment; ///<Pointer to AttachmentSimulator object
	GainSimulator *gain; ///<Pointer to GainSimulator object
	bool simulateDiffusion; ///< Flag to tell if worker has to simulate diffusion
	bool simulateAttachment; ///< Flag to tell if worker has to simulate attachment
	bool simulateGain; ///< Flag to tell if worker has to simulate gain
	TTree* tree; ///< Output ROOT tree
	TFile* out_file; ///< Output ROOT file
	SimEvent *event; ///< Pointer to SimEvent object

};

#endif