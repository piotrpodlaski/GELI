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

int Worker::nWorkers=0;
std::mutex Worker::write_mutex;

Worker::Worker(EventReader *ev_reader)
{
	workerID=nWorkers++;
	reader=ev_reader;
	config=CentralConfig::GetInstance();
	diffusion=new DiffusionSimulator();
	attachment=new AttachmentSimulator();
	simulateDiffusion=config->GetI("simulate_diffusion");
	simulateAttachment=config->GetI("simulate_attachment");
	event=new SimEvent();
	std::string out_name=config->Get("output_file_name");
	std::string thread_id_str="_";
	thread_id_str+=std::to_string(workerID);
	out_name.insert(out_name.find('.'),thread_id_str);
	out_file=new TFile(out_name.c_str(),"RECREATE");
	tree=new TTree(Form("t%d",workerID),"");
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
		tree->Fill();

	}
	out_file->cd();
	tree->Write("t");
	out_file->Close();
	//delete this;
}