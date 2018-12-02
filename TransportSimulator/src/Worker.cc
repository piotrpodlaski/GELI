/**
 * @file Worker.cc
 * @author     Piotr Podlaski
 * @brief      Implementation of Worker class
 */

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
#include "GainSimulator.hh"


Worker::Worker(EventReader *ev_reader, std::string fname)
{
	reader=ev_reader;
	config=CentralConfig::GetInstance();
	diffusion=new DiffusionSimulator();
	attachment=new AttachmentSimulator();
	gain=new GainSimulator();
	simulateDiffusion=config->GetI("simulate_diffusion");
	simulateAttachment=config->GetI("simulate_attachment");
	simulateGain=config->GetI("simulate_gain");
	event=new SimEvent();
	fname="transport_"+fname;
	out_file=new TFile(fname.c_str(),"RECREATE");
	tree=new TTree("t","");
	tree->Branch("evt","SimEvent",event);
}


Worker::~Worker()
{


	//delete tree;
	//delete out_file;
}


void Worker::Run()
{
	while(!reader->EndOfFile())
	{
		reader->ReadEvent(event);
		if(simulateDiffusion)
			diffusion->SimulateDiffusion(event);
		if(simulateAttachment)
			attachment->SimulateAttachment(event);
		if(simulateGain)
			gain->SimulateGain(event);
		tree->Fill();

	}
	out_file->cd();
	tree->Write();
	out_file->Close();
	//delete this;
}