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
	TH2F* pyx, *pzy, *pxz;
	TH1F *px, *py, *pz;
	c->cd(1)->SetRightMargin(0.12);//->SetLogz();
	pyx=((TH2F*)h->Project3D("yx"));
	pyx->GetYaxis()->SetTitleOffset(1.5);
	pyx->Draw("colz");
	c->cd(2)->SetRightMargin(0.12);//->SetLogz();
	pzy=((TH2F*)h->Project3D("zy"));
	pzy->GetYaxis()->SetTitleOffset(1.5);
	pzy->Draw("colz");
	c->cd(3)->SetRightMargin(0.12);//->SetLogz();
	pxz=((TH2F*)h->Project3D("xz"));
	pxz->GetYaxis()->SetTitleOffset(1.5);
	pxz->Draw("colz");
	c->cd(4)->SetRightMargin(0.12);//->SetLogy();//->SetLogz();
	px=((TH1F*)h->ProjectionX());
	px->Draw("hist");
	c->cd(5)->SetRightMargin(0.12);//->SetLogy();//->SetLogz();
	py=((TH1F*)h->ProjectionY());
	py->Draw("hist");
	c->cd(6)->SetRightMargin(0.12);//->SetGridx();//->SetLogz();
	pz=((TH1F*)h->ProjectionZ());
	pz->Draw("hist");
}

int main()
{
	gStyle->SetOptStat(0);
	gStyle->SetNumberContours(999);
	//SimEvent::SetHistogram(200,-100,100,200,-100,100,200,-100,100);
	EventReader* ev_reader=new EventReader("test.root");
	SimEvent* ev=new SimEvent();
	int a=0;
	DiffusionSimulator diffusion;
	AttachmentSimulator attachment;
	if(0);
	int i=0;
		TCanvas* c=new TCanvas("c","",1024,768);
	c->Divide(3,2);

	c->Print("evs.pdf[");

	while(!ev_reader->EndOfFile())
	{

		std::cout<<"Reading event "<<i<<"...";
		ev_reader->ReadEvent(ev);
		TH3F* h=ev->GetPrimaryHisto();
		DrawProjs(c,h);
		c->Print("evs.pdf");
		diffusion.SimulateDiffusion(ev);
		attachment.SimulateAttachment(ev);
		h=ev->GetAfterTransportHisto();
		
		DrawProjs(c,h);
		c->Print("evs.pdf");
		i++;
		//break;
	}
	c->Print("evs.pdf]");
	delete c;
return 0;
	}
	/*
	std::cout<<i<<std::endl;


	//return 0;
	TCanvas* c=new TCanvas("c","",1024,768);
	TCanvas* c1=new TCanvas("c1","",1024,768);
	c->Divide(3,2);
	c->Print("evs.pdf[");
	//ev->Clear();
    //ev->Fill(0.5,0.5,0.5,1000);
	TH3F* h=ev->GetPrimaryHisto();
	
	//hhh=new TH3F("hh","",151,-250,250,151,-250,250,151,-250,250);
	//hhh_diff=new TH3F("hh","",151,-250, 250,151,-250,250,151,-250,250);

	//hhh->Fill(0.,0.,0.,1000.);
	//hhh->Fill(12.,0.,0.,123.);
	c1->cd();
	//h->Draw();
	//c1->Print("evs.pdf");
	
	DrawProjs(c,h);
	c->Print("evs.pdf");
	diffusion.SimulateDiffusion(ev);
	attachment.SimulateAttachment(ev);
	h=ev->GetAfterTransportHisto();
	
	DrawProjs(c,h);
	c->Print("evs.pdf");
	c->Print("evs.pdf]");
	delete c;
}

*/