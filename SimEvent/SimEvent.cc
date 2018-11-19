#include "SimEvent.hh"


//ClassImp(SimEvent);
unsigned int SimEvent::nBinsX;
unsigned int SimEvent::nBinsY;
unsigned int SimEvent::nBinsZ;
double SimEvent::xLow;
double SimEvent::xUp;
double SimEvent::yLow;
double SimEvent::yUp;
double SimEvent::zLow;
double SimEvent::zUp;

SimEvent::SimEvent()
{
		hPrimaryEnergyDeposit=nullptr;
		hEnergyDepositAfterTransport=nullptr;
}

SimEvent::~SimEvent()
{
	if(hPrimaryEnergyDeposit)
		delete hPrimaryEnergyDeposit;
	if(hEnergyDepositAfterTransport)
		delete hEnergyDepositAfterTransport;
}

	SimEvent::SimEvent(TString hname)
	{
		hPrimaryEnergyDeposit=new TH3F(hname,"Energy deposit",nBinsX,xLow,xUp,nBinsY,yLow,yUp,nBinsZ,zLow,zUp);
		hEnergyDepositAfterTransport=nullptr;

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