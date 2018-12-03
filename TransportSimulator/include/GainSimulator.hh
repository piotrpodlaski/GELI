/**
 * @file GainSimulator.hh
 * @author     Piotr Podlaski
 * @brief      Definition of GainSimulator class
 */

#ifndef GAINSIMULATOR_H
#define GAINSIMULATOR_H

/// \cond
#include <map>
#include <utility>
/// \endcond
#include "CentralConfig.hh"

class TH2F;
class SimEvent;


/**
 * @brief      Class handles simulation of gain
 */
class GainSimulator
{
public:

	/**
	 * @brief      Constructor
	 */
	GainSimulator();

	/**
	 * @brief      Constructor with gain histogram as an argument
	 */
	GainSimulator(TH2F* gainHisto);

	/**
	 * @brief      Simulates gain for SimEvent object
	 */
	void SimulateGain(SimEvent *event);
private:

	/**
	 * @brief      Builds gain for XY plane.
	 */
	void BuildGain(TH2F* gain_histo);
	//TH2F* GainHisto;
	CentralConfig *config; ///< Pointer to CentralConfig object
	std::map<std::pair<int,int>,float> gain; ///< Map woth gain, pair indexing used for performace
	bool hasGain; ///< Flag to tell if simulator has a gain map
	int nBinsX; ///<Number of bins in X axis
	int nBinsY; ///<Number of bins in Y axis
	int nBinsZ; ///<Number of bins in Z axis
};


#endif