#ifndef ATTACHMENTSIMULATOR_H
#define ATTACHMENTSIMULATOR_H

#include "CentralConfig.hh"
#include <vector>

class SimEvent;

class AttachmentSimulator
{
public:
	AttachmentSimulator();
	void SimulateAttachment(SimEvent* ev);
private:
	CentralConfig* config;
	std::vector<double> attenuation;
	void BuildExpAttenuation();
	double startValue;
	double beta;
	int nBinsX;
	int nBinsY;
	int nBinsZ;
	double deltax,deltay,deltaz; //bin widths.
	bool isAttenuationBuilt;


};

#endif