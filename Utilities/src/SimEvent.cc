#include "SimEvent.hh"

#include<iostream>

//ClassImp(SimEvent);
unsigned int SimEvent::nBinsX=350;
unsigned int SimEvent::nBinsY=200;
unsigned int SimEvent::nBinsZ=200;
double SimEvent::xLow=-175;
double SimEvent::xUp=175;
double SimEvent::yLow=-100;
double SimEvent::yUp=100;
double SimEvent::zLow=-100;
double SimEvent::zUp=100;

int SimEvent::eventID=0;

SimEvent::~SimEvent()
{
	
	if(hPrimaryEnergyDeposit!=nullptr)
		delete hPrimaryEnergyDeposit;
	if(hEnergyDepositAfterTransport!=nullptr)
		delete hEnergyDepositAfterTransport;
}

SimEvent::SimEvent()
{

	hPrimaryEnergyDeposit=new TH3F(TString(eventID++),"Energy deposit",nBinsX,xLow,xUp,nBinsY,yLow,yUp,nBinsZ,zLow,zUp);
	hEnergyDepositAfterTransport=new TH3F(TString(eventID++)+"_transport","Energy deposit",nBinsX,xLow,xUp,nBinsY,yLow,yUp,nBinsZ,zLow,zUp);
	hPrimaryEnergyDeposit->GetXaxis()->SetTitle("x [mm]");
	hPrimaryEnergyDeposit->GetYaxis()->SetTitle("y [mm]");
	hPrimaryEnergyDeposit->GetZaxis()->SetTitle("z [mm]");
	hEnergyDepositAfterTransport->GetXaxis()->SetTitle("x [mm]");
	hEnergyDepositAfterTransport->GetYaxis()->SetTitle("y [mm]");
	hEnergyDepositAfterTransport->GetZaxis()->SetTitle("z [mm]");
}

void SimEvent::SetHistogram(unsigned int nx, double x1, double x2, unsigned int ny, double y1, double y2, unsigned int nz, double z1, double z2)
	{
		xLow=x1;
		xUp=x2;
		yLow=y1;
		yUp=y2;
		zLow=z1;
		zUp=z2;
		nBinsX=nx;
		nBinsY=ny;
		nBinsZ=nz;
	}
void SimEvent::Fill(double x, double y, double z, double w) 
{
	hPrimaryEnergyDeposit->Fill(x,y,z,w);
}

TH3F* SimEvent::GetPrimaryHisto()
{
	return hPrimaryEnergyDeposit;
}
TH3F* SimEvent::GetAfterTransportHisto()
{
	return hEnergyDepositAfterTransport;
}
void SimEvent::AddPrimaryParticle(PrimaryParticle particle)
{
	primaries.push_back(particle);
}

Primaries SimEvent::GetPrimaries()
{
	return primaries;
}
PrimariesIterator SimEvent::PrimariesBegin()
{
	return primaries.begin();
}
PrimariesIterator SimEvent::PrimariesEnd()
{
	return primaries.end();
}
void SimEvent::Clear()
{
	if(hEnergyDepositAfterTransport)
		hEnergyDepositAfterTransport->Reset();
	if(hPrimaryEnergyDeposit)
		hPrimaryEnergyDeposit->Reset();
	primaries.clear();
}

void SimEvent::SetPrimaries(Primaries prim)
{
	primaries=prim;
}