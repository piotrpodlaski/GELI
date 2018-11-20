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
	Matrix3D m(2,2,2,1);
	//m(2,2,2)=12;
	std::cout<<m(1,1,1)<<std::endl;
	m.Normalize();
	std::cout<<m(1,1,1)<<std::endl;
	m.GetSizeX();
	m.GetSizeY();
	m.GetSizeZ();
	//SimEvent::SetHistogram(175,-175,175,100,-100,100,100,-100,100);
	EventReader* ev_reader=new EventReader("test.root");
	SimEvent* ev=new SimEvent();
	int a=0;

	auto f=[](int x, int y, int z)->double { return x*x; };
	m=Matrix3D::BuildMatrixFromFunction(5,f);
	// /std::cout<<m.GetSizeX();
	for(int i=0;i<m.GetSizeX();i++)
		std::cout<<m(i,0,0)<<std::endl;
	DiffusionSimulator s;
	if(0);
	while(!ev_reader->EndOfFile())
	{	
		ev_reader->ReadEvent(ev);
		//s.SimulateDiffusion(ev->GetPrimaryHisto(),ev->GetAfterTransportHisto());
		//m=Matrix3D::BuildMatrixFromTH3(ev->GetPrimaryHisto());
	}


	TCanvas* c=new TCanvas("c","",1024,768);
	c->Divide(2,2);
	c->Print("evs.pdf[");
	TH3F* hhh=ev->GetPrimaryHisto();
	TH3F* hhh_diff=ev->GetAfterTransportHisto();
	//hhh=new TH3F("hh","",51,-25,25,51,-25,25,51,-25,25);
	//hhh_diff=new TH3F("hh","",51,-25,25,51,-25,25,51,-25,25);

	hhh->Fill(0.,0.,0.,100.);
	c->cd(1);//->SetLogz();
	((TH2F*)hhh->Project3D("yz"))->Draw("colz0");
	c->cd(2);//->SetLogz();
	((TH2F*)hhh->Project3D("zx"))->Draw("colz0");
	c->cd(3);//->SetLogz();
	((TH2F*)hhh->Project3D("xy"))->Draw("colz0");
	c->cd(4);
	hhh->Draw();
	c->Print("evs.pdf");
	s.SimulateDiffusion(hhh,hhh_diff);
	c->cd(1);
	((TH2F*)hhh_diff->Project3D("yz"))->Draw("colz0");
	c->cd(2);
	((TH2F*)hhh_diff->Project3D("zx"))->Draw("colz0");
	c->cd(3);
	((TH2F*)hhh_diff->Project3D("xy"))->Draw("colz0	");
	c->cd(4);
	hhh_diff->Draw();
	c->Print("evs.pdf");
	c->Print("evs.pdf]");



}