/**
 * @file EventReader.cc
 * @author     Piotr Podlaski
 * @brief      Implementation of EventReader class
 */


#include "EventReader.hh"


EventReader::EventReader(TString fname)
{
	file_name=fname;
	config=CentralConfig::GetInstance();
	nEventsToMerge=config->GetI("n_background_events");
	input_file=new TFile(file_name);
	input_file->GetObject("EDep",edep_tree);
	input_file->GetObject("prim",primary_tree);
	nEntriesPrim=primary_tree->GetEntries();
	nEntriesEdep=edep_tree->GetEntries();
	if(nEventsToMerge==1)
		ReadPrimaries();
	current_entry=0;

	edep_tree->SetBranchAddress("x",&x);
	edep_tree->SetBranchAddress("y",&y);
	edep_tree->SetBranchAddress("z",&z);
	edep_tree->SetBranchAddress("Edep",&Edep);
	edep_tree->SetBranchAddress("event",&event);
	
}

void EventReader::ReadPrimaries()
{
	if(nEntriesPrim==0)
		return;
	int prev_event;
	int prim_event;
	PrimaryParticle particle;
	primary_tree->SetBranchAddress("x",&particle.x);
	primary_tree->SetBranchAddress("y",&particle.y);
	primary_tree->SetBranchAddress("z",&particle.z);
	primary_tree->SetBranchAddress("px",&particle.px);
	primary_tree->SetBranchAddress("py",&particle.py);
	primary_tree->SetBranchAddress("pz",&particle.pz);
	primary_tree->SetBranchAddress("E",&particle.E);
	primary_tree->SetBranchAddress("id",&particle.particleID);
	primary_tree->SetBranchAddress("A",&particle.A);
	primary_tree->SetBranchAddress("Z",&particle.Z);
	primary_tree->SetBranchAddress("event",&prim_event);
	
	primary_tree->GetEntry(0);
	prev_event=prim_event;
	Primaries prim_vect;
	for(int i=0;i<nEntriesPrim;i++)
	{
		primary_tree->GetEntry(i);
		if(prev_event!=prim_event)
		{
			primaries_map[prev_event]=prim_vect;
			prim_vect.clear();
		}
		prim_vect.push_back(particle);
		prev_event=prim_event;
		
	}
	primaries_map[prim_event]=prim_vect;
}


bool EventReader::EndOfFile()
{
	//std::cout<<"Getting entry: "<<current_entry<<std::endl;
	if(nEntriesEdep==0)
		return true;
	if(current_entry==nEntriesEdep)
		return true;
	else
		return false;
}



void EventReader::ReadEvent(SimEvent* evt)
{
	std::cout<<"Reading event "<<current_entry<<" from "<<file_name<<std::flush;
	evt->Clear();
	for(int event=0;event<nEventsToMerge;event++)
	{
		if(current_entry==nEntriesEdep)
			break;
		edep_tree->GetEntry(current_entry++);
		for(int i=0;i<x->size();i++)
		{
			evt->Fill(x->at(i),y->at(i),z->at(i),Edep->at(i));
		}
		if(nEventsToMerge==1)
			evt->SetPrimaries(primaries_map[event]);
	}
	std::cout<<" done!"<<std::endl;
}

void EventReader::BuildEvent(SimEvent* evt, vect *vx, vect *vy, vect *vz, vect *vEdep)
{
	evt->Clear();
	for(int i=0;i<vx->size();i++)
	{
		evt->Fill(vx->at(i),vy->at(i),vz->at(i),vEdep->at(i));
	}

	std::cout<<"Event building done!"<<std::endl;
}

