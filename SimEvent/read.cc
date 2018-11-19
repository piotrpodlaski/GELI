#include "SimEvent.hh"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TCanvas.h"
#include "TH2F.h"


int main()
{
	TFile *f=new TFile("test.root");

	TTree *t;
	f->GetObject("t",t);
	SimEvent *ev=0;
	t->SetBranchAddress("evt",&ev);
	TH3F* h;
	TCanvas* c=new TCanvas("c","",1024,768);
	std::cout<<f<<" "<<t<<std::endl;
	c->Divide(2,2);
	t->GetEntry(0);
	c->Print("evs.pdf[");
	for(int i=0;i<t->GetEntries();i++)
	{

		t->GetEntry(i);
		if(!ev) continue;
		h=ev->GetPrimaryHisto();
		if(!h) continue;
		c->cd(1);
		((TH2F*)h->Project3D("yz"))->Draw("colz");
		c->cd(2);
		((TH2F*)h->Project3D("zx"))->Draw("colz");
		c->cd(3);
		((TH2F*)h->Project3D("xy"))->Draw("colz");
		c->cd(4);
		h->Draw();
		c->Print("evs.pdf");
	}
	c->Print("evs.pdf]");
}
