#include "AttachmentSimulator.hh"
#include "SimEvent.hh"
#include <cmath>

AttachmentSimulator::AttachmentSimulator()
{
	config=CentralConfig::GetInstance();
	startValue=config->GetD("attachment","A0");
	beta=config->GetD("attachment","beta");
}

void AttachmentSimulator::SimulateAttachment(SimEvent *ev, bool takeAfterTransportHisto)
{
	TH3F* input;
	if(takeAfterTransportHisto)
		input=ev->GetAfterTransportHisto();
	else
		input=ev->GetPrimaryHisto();

	TH3F* output=ev->GetAfterTransportHisto();
	nBinsX=input->GetNbinsX();
	nBinsY=input->GetNbinsY();
	nBinsZ=input->GetNbinsZ();
	deltax=input->GetXaxis()->GetBinWidth(1);
	deltay=input->GetYaxis()->GetBinWidth(1);
	deltaz=input->GetZaxis()->GetBinWidth(1);
	BuildExpAttenuation();
	//minx=innput->GetXaxis()->GetBinLowEdge(1);
	//miny=innput->GetYaxis()->GetBinLowEdge(1);
	//minz=innput->GetZaxis()->GetBinLowEdge(1);
	for(int x=1;x<=nBinsX;x++)
		for(int y=1;y<=nBinsY;y++)
			for(int z=1;z<=nBinsZ;z++)
			{
				int bin=input->GetBin(x,y,z);
				double value=input->GetBinContent(bin);
				value=value*attenuation[nBinsZ-z];//beacuse readout is on the top of the active volume
				output->SetBinContent(bin,value);
			}
}

void AttachmentSimulator::BuildExpAttenuation()
{
	for(int i=0;i<nBinsZ;i++)
	{
		double value;
		//compute attenuation, tske value in the center of the bin
		value=startValue*exp(-beta*(i*deltaz+deltaz/2.));
		attenuation.push_back(value);
	}
}
