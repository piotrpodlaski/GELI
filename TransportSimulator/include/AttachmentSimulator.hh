/**
 * @file AttachmentSimulator.hh
 * @author     Piotr Podlaski
 * @brief      Definition of AttachmentSimulator class
 */

#ifndef ATTACHMENTSIMULATOR_H
#define ATTACHMENTSIMULATOR_H

#include "CentralConfig.hh"
/// \cond
#include <vector>
/// \endcond
class SimEvent;

/**
 * @brief      Class handles simulation of electron attachment in gas
 */
class AttachmentSimulator
{
public:

	/**
	 * @brief      Constructor
	 */
	AttachmentSimulator();

	/**
	 * @brief      Performs attachment simulation on SimEvent object
	 */
	void SimulateAttachment(SimEvent* ev);
private:
	CentralConfig* config; ///< Pointer to CentralConfg object
	std::vector<double> attenuation; ///< Vector with attenuation
	
	/**
	 * @brief      Builds exponential attenuation vector
	 * This method is invoked once per simulation to increase performance
	 */
	void BuildExpAttenuation();
	double startValue; ///< Value of the attenuation at parrt of active volume closest to amplification structure
	double beta; ///< Attenuation constant
	int nBinsX; ///< Number of bins on X axis
	int nBinsY; ///< Number of bins on Y axis
	int nBinsZ; ///< Number of bins on Z axis
	double deltax; ///< Bin width in X axis
	double deltay; ///< Bin width in Y axis
	double deltaz; ///< Bin width in Z axis
	bool isAttenuationBuilt; ///< Flag to tell if attenuation vector is built


};

#endif