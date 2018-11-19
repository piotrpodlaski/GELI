#ifndef SIMEVENT_H
#define SIMEVENT_H

#include "TObject.h"
#include "TH3F.h"
#include "TString.h"
#include <vector>

struct PrimaryParticle
{
	double x,y,z,px,py,pz,E;
	int particleID;
};

typedef std::vector<PrimaryParticle> Primaries;
typedef Primaries::iterator PrimariesIterator;

class SimEvent : public TObject
{	
public:
	SimEvent();
	~SimEvent();
	void Fill(double x, double y, double z, double w=1.);
	TH3F* GetPrimaryHisto();
	TH3F* GetAfterTransportHisto();
	void AddPrimaryParticle(PrimaryParticle particle);
	static void SetHistogram(unsigned int nx, double x1, double x2, unsigned int ny, double y1, double y2, unsigned int nz, double z1, double z2);
	Primaries GetPrimaries();
	void SetPrimaries(Primaries prim);
	PrimariesIterator PrimariesBegin();
	PrimariesIterator PrimariesEnd();
	void Clear();
private:
	static unsigned int nBinsX;
	static unsigned int nBinsY;
	static unsigned int nBinsZ;
	static double xLow;
	static double xUp;
	static double yLow;
	static double yUp;
	static double zLow;
	static double zUp;
	static int eventID; //event ID used for unique histogram naming
	Primaries primaries;
	TH3F* hPrimaryEnergyDeposit;
	TH3F* hEnergyDepositAfterTransport;
	bool isBackground;
	bool hasBackground;

	ClassDef(SimEvent,1);
};




#endif