#include "AttachmentSimulator.hh"
#include "SimEvent.hh"
#include <cmath>

AttachmentSimulator::AttachmentSimulator()
{
	config=CentralConfig::GetInstance();
	startValue=config->GetD("attachment","A0");
	beta=config->GetD("attachment","beta");
	isAttenuationBuilt=false;
}

void AttachmentSimulator::SimulateAttachment(SimEvent *ev)
{
	TH3F* input;
	bool takeAfterTransportHisto=ev->HasDiffusion();
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
	if(!isAttenuationBuilt)
	{
		BuildExpAttenuation();
		isAttenuationBuilt=true;
	}
	//minx=innput->GetXaxis()->GetBinLowEdge(1);
	//miny=innput->GetYaxis()->GetBinLowEdge(1);
	//minz=innput->GetZaxis()->GetBinLowEdge(1);
	for(int x=1;x<=nBinsX;x++)
		for(int y=1;y<=nBinsY;y++)
			for(int z=1;z<=nBinsZ;z++)
			{
				int bin=input->GetBin(x,y,z);
				double value=input->GetBinContent(bin);
				value=value*attenuation[z];
				output->SetBinContent(bin,value);
			}
	ev->SetAttachment();
}

void AttachmentSimulator::BuildExpAttenuation()
{
	for(int i=0;i<nBinsZ;i++)
	{
		double value;
		//compute attenuation, take value in the center of the bin
		value=startValue*exp(-beta*(i*deltaz+deltaz/2.));
		attenuation.push_back(value);
		//std::cout<<value<<std::endl;
	}
}
