#include "Worker.hh"
#include "EventReader.hh"
#include "CentralConfig.hh"
#include "DiffusionSimulator.hh"
#include "AttachmentSimulator.hh"
#include "SimEvent.hh"

Worker::Worker(EventReader *ev_reader)
{
	reader=ev_reader;
	config=CentralConfig::GetInstance();
	diffusion=new DiffusionSimulator();
	attachment=new AttachmentSimulator();
	simulateDiffusion=config->GetI("simulate_diffusion");
	simulateAttachment=config->GetI("simulate_attachment");
	ev=new SimEvent();
}

void Worker::operator()()
{
	while(!reader->EndOfFile())
	{
		reader->ReadEvent(ev);
		if(simulateDiffusion)
			diffusion->SimulateDiffusion(ev);
		if(simulateAttachment)
			attachment->SimulateAttachment(ev);

	}
}