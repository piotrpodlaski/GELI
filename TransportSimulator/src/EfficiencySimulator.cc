#include "EfficiencySimulator.hh"
#include "TH2F.h"
#include "TH3F.h"
#include "SimEvent.hh"

EfficiencySimulator::EfficiencySimulator()
{
	config=CentralConfig::GetInstance();
	hasEfficiency=false;

}

EfficiencySimulator::EfficiencySimulator(TH2F* efficiencyHisto)
{
	config=CentralConfig::GetInstance();
	hasEfficiency=true;
	nBinsX=efficiencyHisto->GetNbinsX();
	nBinsY=efficiencyHisto->GetNbinsY();
	nBinsZ=efficiencyHisto->GetNbinsZ();

	BuildEfficiency(efficiencyHisto);
}

void EfficiencySimulator::BuildEfficiency(TH2F* eff)
{
	for(int x=1;x<=nBinsX;x++)
		for(int y=1;y<=nBinsX;y++)
			efficiency[std::make_pair(x,y)]=eff->GetBinContent(eff->GetBin(x,y));
}

void EfficiencySimulator::SimulateEfficiency(SimEvent* ev)
{
	if(!hasEfficiency)
	{
		std::cerr<<"No Efficiency map histogram! Doing nothing!"<<std::endl;
		return;
	}
	TH3F* input;
	bool takeAfterTransportHisto=ev->HasDiffusion()||ev->HasAttachment();
	if(takeAfterTransportHisto)
		input=ev->GetAfterTransportHisto();
	else
		input=ev->GetPrimaryHisto();

	TH3F* output=ev->GetAfterTransportHisto();
	if(hasEfficiency)
	{
		for(int z=1;z<=nBinsX;z++)
			for(auto eff : efficiency)
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