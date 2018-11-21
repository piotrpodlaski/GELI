#include "EventReader.hh"
#include "Matrix3D.hh"
#include "DiffusionSimulator.hh"
#include "TCanvas.h"
#include "TH3F.h"
#include "TH2F.h"
#include "TStyle.h"
int main()
{
	gStyle->SetOptStat(1001111);
	gStyle->SetNumberContours(999);
	EventReader* ev_reader=new EventReader("test.root");
	SimEvent* ev=new SimEvent();
	int a=0;
	DiffusionSimulator s;
	if(0);
	int i=0;
	while(!ev_reader->EndOfFile())
	{	
		std::cout<<"Reading event "<<i<<"...";
		ev_reader->ReadEvent(ev);
		std::cout<<" done!"<<std::endl;
		std::cout<<"Simulating diffusion..."<<std::flush;
		s.SimulateDiffusion(ev->GetPrimaryHisto(),ev->GetAfterTransportHisto());
		std::cout<<" done!"<<std::endl;
		//m=Matrix3D::BuildMatrixFromTH3(ev->GetPrimaryHisto());
		i++;
	}
	std::cout<<i<<std::endl;


return 0;
	TCanvas* c=new TCanvas("c","",1024,768);
	c->Divide(2,2);
	c->Print("evs.pdf[");
	TH3F* hhh=ev->GetPrimaryHisto();
	TH3F* hhh_diff=ev->GetAfterTransportHisto();
	//hhh=new TH3F("hh","",151,-250,250,151,-250,250,151,-250,250);
	//hhh_diff=new TH3F("hh","",151,-250, 250,151,-250,250,151,-250,250);

	//hhh->Fill(0.,0.,0.,123.);
	//hhh->Fill(12.,0.,0.,123.);
	c->cd(1);//->SetLogz();
	((TH2F*)hhh->Project3D("yz"))->Draw("colz0");
	c->cd(2);//->SetLogz();
	((TH2F*)hhh->Project3D("zx"))->Draw("colz0");
	c->cd(3);//->SetLogz();
	((TH2F*)hhh->Project3D("xy"))->Draw("colz0");
	c->cd(4);
	hhh->Draw();
	c->Print("evs.pdf");
	//s.SimulateDiffusion(hhh,hhh_diff);
	c->cd(1);
	((TH2F*)hhh_diff->Project3D("yz"))->Draw("colz0");
	c->cd(2);
	((TH2F*)hhh_diff->Project3D("zx"))->Draw("colz0");
	c->cd(3);
	((TH2F*)hhh_diff->Project3D("xy"))->Draw("colz0	");
	c->cd(4);//->SetLogy();
	hhh_diff->Draw();
	c->Print("evs.pdf");
	c->Print("evs.pdf]");



}