#ifndef DIFFUSIONSIMULATOR_H
#define DIFFUSIONSIMULATOR_H

#include "CentralConfig.hh"


class DiffusionSimulator
{
public:
	DiffusionSimulator();
	~DiffusionSimulator();
	void SimulateDiffusion();
private:
	CentralConfig* config;
	
};


#endif