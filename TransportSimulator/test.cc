#include "SimEvent.hh"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include <iostream>
#include "TH1D.h"

int main(int argc, char** argv)
{
	if(argc<2)
	{
		std::cout<<"Usage: ./"<<argv[0]<<" <file with SimEvent tree>"<<std::endl;
		return 1;
	}
	TFile *f=new TFile(argv[1]);
	TTree *t;
	f->GetObject("t",t);
	SimEvent* event;
	t->SetBranchAddress("evt",&event);
	int nEntries=t->GetEntries();
	TFile fo("fout.root","RECREATE");
	fo.cd();
	TH1D* h=new TH1D("h","",100,14000,18000);
	for(int i=0;i<nEntries;i++)
	{
		t->GetEntry(i);
		double edep=event->PrimaryIntegral();
		std::cout<<edep<<std::endl;
		h->Fill(edep);
	}
	TCanvas*c=new TCanvas("c","",1024,768);
	h->Draw();
	c->Print("edep.pdf");
	h->Write();
	fo.Close();
}