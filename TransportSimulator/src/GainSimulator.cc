/**
 * @file GainSimulator.cc
 * @author     Piotr Podlaski
 * @brief      Implementation of GainSimulator class
 */

#include "GainSimulator.hh"
#include "TH2F.h"
#include "TH3F.h"
#include "SimEvent.hh"

GainSimulator::GainSimulator()
{
	config=CentralConfig::GetInstance();
	hasGain=false;

}

GainSimulator::GainSimulator(TH2F* gainHisto)
{
	config=CentralConfig::GetInstance();
	hasGain=true;
	nBinsX=gainHisto->GetNbinsX();
	nBinsY=gainHisto->GetNbinsY();
	nBinsZ=gainHisto->GetNbinsZ();

	BuildGain(gainHisto);
}

void GainSimulator::BuildGain(TH2F* eff)
{
	for(int x=1;x<=nBinsX;x++)
		for(int y=1;y<=nBinsX;y++)
			gain[std::make_pair(x,y)]=eff->GetBinContent(eff->GetBin(x,y));
}

void GainSimulator::SimulateGain(SimEvent* ev)
{
	if(!hasGain)
	{
		std::cerr<<"No Gain map histogram! Doing nothing!"<<std::endl;
		return;
	}
	TH3F* input;
	bool takeAfterTransportHisto=ev->HasDiffusion()||ev->HasAttachment();
	if(takeAfterTransportHisto)
		input=ev->GetAfterTransportHisto();
	else
		input=ev->GetPrimaryHisto();

	TH3F* output=ev->GetAfterTransportHisto();
	if(hasGain)
	{
		for(int z=1;z<=nBinsX;z++)
			for(auto eff : gain)
				{
					int x=eff.first.first;
					int y=eff.first.second;
					int bin=input->GetBin(x,y,z);
					double value=input->GetBinContent(bin);
					value=value*eff.second;
					output->SetBinContent(bin,value);
				}
	}
}