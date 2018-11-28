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
	c->cd(1);//->SetLogz();
	pyx=((TH2F*)h->Project3D("yx"));
	pyx->Draw("colz");
	c->cd(2);//->SetLogz();
	pzy=((TH2F*)h->Project3D("zy"));
	pzy->Draw("colz");
	c->cd(3);//->SetLogz();
	pxz=((TH2F*)h->Project3D("xz"));
	pxz->Draw("colz");
	c->cd(4);//->SetLogy();//->SetLogz();
	px=((TH1F*)h->ProjectionX());
	px->Draw("hist");
	c->cd(5);//->SetLogy();//->SetLogz();
	py=((TH1F*)h->ProjectionY());
	py->Draw("hist");
	c->cd(6);//->SetGridx();//->SetLogz();
	pz=((TH1F*)h->ProjectionZ());
	pz->Draw("hist");
}

int main()
{
	gStyle->SetOptStat(0);
	gStyle->SetNumberContours(999);
	SimEvent::SetHistogram(200,-100,100,200,-100,100,200,-100,100);
	SimEvent* ev=new SimEvent();
	int a=0;
	DiffusionSimulator diffusion;
	AttachmentSimulator attachment;


	//diffusion:
	TCanvas* c=new TCanvas("c","",1024,768);
	TCanvas* c1=new TCanvas("c1","",1024,768);
	c->Divide(3,2,0.02,0.02);
	c->Print("evs.pdf[");
    ev->Fill(0.5,0.5,-80,1000);
    ev->Fill(0.5,0.5,-40,1000);
    ev->Fill(0.5,0.5,0,1000);
    ev->Fill(0.5,0.5,40,1000);
    ev->Fill(0.5,0.5,80,1000);
	TH3F* hh=ev->GetPrimaryHisto();
	TH3F* h=ev->GetAfterTransportHisto();
	//hhh=new TH3F("hh","",151,-250,250,151,-250,250,151,-250,250);
	//hhh_diff=new TH3F("hh","",151,-250, 250,151,-250,250,151,-250,250);

	//hhh->Fill(0.,0.,0.,1000.);
	//hhh->Fill(12.,0.,0.,123.);
	c1->cd();
	diffusion.SimulateDiffusion(ev);
//	attachment.SimulateAttachment(ev);
	
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
	c->Print("evs.pdf");

	c1->Print("single.pdf[");
	c1->cd();
	pyx->Draw("colz");
	c1->Print("single.pdf[");

	pzy->Draw("colz");
	c1->Print("single.pdf[");

	pxz->Draw("colz");
	c1->Print("single.pdf[");

	px->Draw("colz");
	c1->Print("single.pdf[");

	py->Draw("colz");
	c1->Print("single.pdf[");

	pz->Draw("colz");
	c1->Print("single.pdf[");







	//attachment:
	ev->Clear();
	for(int x=1;x<=200;x++)
		for(int y=1;y<=200;y++)
			for(int z=1;z<=200;z++)
				ev->GetPrimaryHisto()->SetBinContent(x,y,z,1);

	c1->cd();
	//diffusion.SimulateDiffusion(ev);
	attachment.SimulateAttachment(ev);
	
	c1->cd();
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
	c->Print("evs.pdf");

	c->Print("evs.pdf]");

	c1->cd();
	pyx->Draw("colz");
	c1->Print("single.pdf[");

	pzy->Draw("colz");
	c1->Print("single.pdf[");

	pxz->Draw("colz");
	c1->Print("single.pdf[");

	px->Draw("colz");
	c1->Print("single.pdf[");

	py->Draw("colz");
	c1->Print("single.pdf[");

	pz->Draw("colz");
	c1->Print("single.pdf[");

	c1->Print("single.pdf]");
	delete c;
}

