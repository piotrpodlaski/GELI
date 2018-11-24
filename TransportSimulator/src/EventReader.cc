#include "EventReader.hh"

EventReader::EventReader(TString fname)
{
	input_file=new TFile(fname);
	input_file->GetObject("EDep",edep_tree);
	input_file->GetObject("prim",primary_tree);
	nEntriesPrim=primary_tree->GetEntries();
	nEntriesEdep=edep_tree->GetEntries();
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
	int id;
	PrimaryParticle particle;
	primary_tree->SetBranchAddress("x",&particle.x);
	primary_tree->SetBranchAddress("y",&particle.y);
	primary_tree->SetBranchAddress("z",&particle.z);
	primary_tree->SetBranchAddress("px",&particle.px);
	primary_tree->SetBranchAddress("py",&particle.py);
	primary_tree->SetBranchAddress("pz",&particle.pz);
	primary_tree->SetBranchAddress("E",&particle.E);
	primary_tree->SetBranchAddress("id",&particle.particleID);
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
	//std::cout<<"Entry: "<<current_entry<<std::endl;
	if(nEntriesEdep==0)
		return true;
	if(current_entry==nEntriesEdep-1)
		return true;
	else
		return false;
}

void EventReader::ReadEvent(SimEvent* evt)
{
	if(current_entry==0)
	{
		edep_tree->GetEntry(0);
		current_event=event;
	}
	evt->Clear();
	while(true)
	{
		edep_tree->GetEntry(current_entry++);
		if(current_event!=event||current_entry==nEntriesEdep)
		{
			evt->SetPrimaries(primaries_map[current_event]);
			current_event=event;
			current_entry--;
			break;
		}
		evt->Fill(x,y,z,Edep);
	}
	std::cout<<"Event reading done!"<<std::endl;
}

