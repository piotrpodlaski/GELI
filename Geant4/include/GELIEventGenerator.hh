#ifndef GELIEVENTGENERATOR_H
#define GELIEVENTGENERATOR_H
#ifdef USE_EVENT_GENERATOR
#include "ReactionResult.hpp"
#include "SimulationSetup.hpp"
#include "ConfigFile.hpp"
#include "SimulationSetupFactory.hpp"
#include "SimulationSetup.hpp"
#include "Photodisintegration.hpp"
#include <vector>

class GELIEventGenerator
{
	typedef std::vector<double> vec;
public:
	GELIEventGenerator();
	~GELIEventGenerator();
	ReactionResult GetReactionProducts();
	int GetFirstProdMassNumber() {return firstProdMassNumber;}
	int GetFirstProdAtomicNumber() {return firstProdAtomicNumber;}
	int GetSecondProdMassNumber() {return secondProdMassNumber;}
	int GetSecondProdAtomicNumber() {return secondProdAtomicNumber;}
	void FillVectors(vec &theta1, vec &theta2, vec &phi1, vec &phi2, vec &E1, vec &E2);
private:
	SimulationSetup* setup;
	ConfigFile* configFile;
    SimulationSetupFactory* simulationSetupFactory;
    Photodisintegration *photodisintegration;
    double targetMass;
    double firstProdMassMass;
    double secProdMassMass;
    int firstProdMassNumber;
    int firstProdAtomicNumber;
    int secondProdMassNumber;
    int secondProdAtomicNumber;

};
#endif
#endif