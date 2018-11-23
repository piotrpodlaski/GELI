#include "EventReader.hh"
#include "Matrix3D.hh"
#include "DiffusionSimulator.hh"
#include "AttachmentSimulator.hh"
#include "TCanvas.h"
#include "TH3F.h"
#include "TH2F.h"
#include "TStyle.h"

void DrawProjs(TCanvas* c,TH3F* h)
{
	c->cd(1);//->SetLogz();
	((TH2F*)h->Project3D("yx"))->Draw("colz");
	c->cd(2);//->SetLogz();
	((TH2F*)h->Project3D("zy"))->Draw("colz");
	c->cd(3);//->SetLogz();
	((TH2F*)h->Project3D("xz"))->Draw("colz");
	c->cd(4);//->SetLogy();//->SetLogz();
	((TH1F*)h->ProjectionX())->Draw("hist");
	c->cd(5);//->SetLogy();//->SetLogz();
	((TH1F*)h->ProjectionY())->Draw("hist");
	c->cd(6);//->SetGridx();//->SetLogz();
	((TH1F*)h->ProjectionZ())->Draw("hist");
}

int main()
{
	gStyle->SetOptStat(1001111);
	gStyle->SetNumberContours(999);
	//SimEvent::SetHistogram(200,-100,100,200,-100,100,200,-100,100);
	EventReader* ev_reader=new EventReader("test.root");
	SimEvent* ev=new SimEvent();
	int a=0;
	DiffusionSimulator diffusion;
	AttachmentSimulator attachment;
	if(0);
	int i=0;
	while(!ev_reader->EndOfFile())
	{

		std::cout<<"Reading event "<<i<<"...";
		ev_reader->ReadEvent(ev);
		break;
		std::cout<<" done!"<<std::endl;
		std::cout<<"Simulating diffusion..."<<std::flush;
		diffusion.SimulateDiffusion(ev);
		attachment.SimulateAttachment(ev);
		std::cout<<" done!"<<std::endl;
		//m=Matrix3D::BuildMatrixFromTH3(ev->GetPrimaryHisto());
		i++;
		break;
	}
	std::cout<<i<<std::endl;


//return 0;
	TCanvas* c=new TCanvas("c","",1024,768);
	TCanvas* c1=new TCanvas("c1","",1024,768);
	c->Divide(3,2);
	c->Print("evs.pdf[");
	//ev->Clear();
    //ev->Fill(0.5,0.5,0.5,1000);
	TH3F* hhh=ev->GetPrimaryHisto();
	TH3F* hhh_diff=ev->GetAfterTransportHisto();
	//hhh=new TH3F("hh","",151,-250,250,151,-250,250,151,-250,250);
	//hhh_diff=new TH3F("hh","",151,-250, 250,151,-250,250,151,-250,250);

	//hhh->Fill(0.,0.,0.,1000.);
	//hhh->Fill(12.,0.,0.,123.);
	c1->cd();
	hhh->Draw();
	c1->Print("evs.pdf");
	
	DrawProjs(c,hhh);
	c->Print("evs.pdf");
	diffusion.SimulateDiffusion(ev);
	attachment.SimulateAttachment(ev);
	
	c1->cd();
	hhh_diff->Draw();
	c1->Print("evs.pdf");
	DrawProjs(c,hhh_diff);
	c->Print("evs.pdf");
	c->Print("evs.pdf]");
	delete c;
}

