#ifndef EFFICIENCYSIMULATOR_H
#define EFFICIENCYSIMULATOR_H

#include <map>
#include <utility>
#include "CentralConfig.hh"

class TH2F;
class SimEvent;


class EfficiencySimulator
{
public:
	EfficiencySimulator();
	EfficiencySimulator(TH2F* efficiencyHisto);
	void SimulateEfficiency(SimEvent *event);
private:
	void BuildEfficiency(TH2F* eff_histo);
	//TH2F* efficiencyHisto;
	CentralConfig *config;
	std::map<std::pair<int,int>,float> efficiency;
	bool hasEfficiency;
	int nBinsX, nBinsY, nBinsZ;
};


#endif