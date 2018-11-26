#include "Worker.hh"
#include "EventReader.hh"
#include "CentralConfig.hh"
#include "DiffusionSimulator.hh"
#include "AttachmentSimulator.hh"
#include "SimEvent.hh"
#include <string>
#include <thread>
#include <functional>
#include <iostream>
#include "TString.h"
#include <mutex>
#include "EfficiencySimulator.hh"

int Worker::nWorkers=0;
std::mutex Worker::write_mutex;

Worker::Worker(EventReader *ev_reader, std::string fname)
{
	workerID=nWorkers++;
	reader=ev_reader;
	config=CentralConfig::GetInstance();
	diffusion=new DiffusionSimulator();
	attachment=new AttachmentSimulator();
	efficiency=new EfficiencySimulator();
	simulateDiffusion=config->GetI("simulate_diffusion");
	simulateAttachment=config->GetI("simulate_attachment");
	simulateEfficiency=config->GetI("simulate_efficiency");
	event=new SimEvent();
	fname="transport_"+fname;
	out_file=new TFile(fname.c_str(),"RECREATE");
	tree=new TTree("t","");
	tree->Branch("evt","SimEvent",event);
}


Worker::~Worker()
{
	std::lock_guard<std::mutex> guard(write_mutex);

	//delete tree;
	//delete out_file;
}


void Worker::Run()
{
	std::cout<<workerID<<std::endl;
	while(!reader->EndOfFile())
	{
		reader->ReadEvent(event);
		if(simulateDiffusion)
			diffusion->SimulateDiffusion(event);
		if(simulateAttachment)
			attachment->SimulateAttachment(event);
		if(simulateEfficiency)
			efficiency->SimulateEfficiency(event);
		tree->Fill();

	}
	out_file->cd();
	tree->Write();
	out_file->Close();
	//delete this;
}