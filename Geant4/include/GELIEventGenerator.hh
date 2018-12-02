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


/**
 * @class      GELIEventGenerator
 *
 * @brief      Wrapper class that creates interface to custom EventGenerator
 *             written by A. Fijłkowska
 */
class GELIEventGenerator
{
	/** for shorter syntax */
	typedef std::vector<double> vec;
public:

	/**
	 * @brief Constructor
	 */
	GELIEventGenerator();

	/**
	 * @brief     Destructor
	 */
	~GELIEventGenerator();

	

	/**
	 * @brief      Access to mass number (A) of first reaction product
	 */
	int GetFirstProdMassNumber() {return firstProdMassNumber;}
	/**
	 * @brief      Access to mass number (A) of fsecod reaction product
	 */
	int GetFirstProdAtomicNumber() {return firstProdAtomicNumber;}
	/**
	 * @brief      Access to atomic number (Z) of first reaction product
	 */
	int GetSecondProdMassNumber() {return secondProdMassNumber;}
	/**
	 * @brief      Access to atomic number (Z) of second reaction product
	 */
	int GetSecondProdAtomicNumber() {return secondProdAtomicNumber;}
	/**
	 * @brief      Fills vectors with information about products of the single reaction
	 */
	void FillVectors(vec &theta1, vec &theta2, vec &phi1, vec &phi2, vec &E1, vec &E2);
private:
	/**
	 * @brief      Generates reaction products
	 *
	 * @details    Method generates single reaction and returns its products, it
	 *             invokes EventGenertorMethods
	 */
	ReactionResult GetReactionProducts();
	
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