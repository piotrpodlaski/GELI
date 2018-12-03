/**
 * @file SimEvent.hh
 * @author     Piotr Podlaski
 * @brief      Definition of SimEvent class and PrimaryParticle struct
 */

#ifndef SIMEVENT_H
#define SIMEVENT_H

#include "TObject.h"
#include "TH3F.h"
#include "TString.h"
/// \cond
#include <vector>
/// \endcond

/**
 * @struct PrimaryParticle
 *
 * @brief      Holds information about primary particle
 */
struct PrimaryParticle
{
	double x; ///< X emission coordinate of the primary particle
	double y; ///< Y emission coordinate of the primary particle
	double z; ///< Z emission coordinate of the primary particle
	double px; ///< X momentum coordinate of the primary particle
	double py; ///< Y momentum coordinate of the primary particle
	double pz; ///< Z momentum coordinate of the primary particle
	double E; ///< energy of the primary particle
	int particleID; ///< PDG code of the primary particle
	int A; ///< Mass number of the primary particle
	int Z; ///< Atomic numberof the primary particle
};

typedef std::vector<PrimaryParticle> Primaries;

typedef Primaries::iterator PrimariesIterator;

/**
 * @class      SimEvent
 *
 * @brief      Class used to store information about simulated events.
 * @details    Object of the class store complete information about events
 *             simulated in the framework.
 */
class SimEvent : public TObject
{	
public:
	/**
	 * @brief      Constructor
	 */
	SimEvent();
	
	/**
	 * @brief      Destructor
	 */
	~SimEvent();

	/**
	 * @brief      Fills event with single energy deposit
	 */
	void Fill(double x, double y, double z, double Edep=1.);

	/**
	 * @brief      Access to primary energy deposit histogram.
	 */
	TH3F* GetPrimaryHisto();
	/**
	 * @brief      Access to energy deposit histogram after transport simulation.
	 */
	TH3F* GetAfterTransportHisto();

	/**
	 * @brief      Adds a primary particle to SimEvent.
	 */
	void AddPrimaryParticle(PrimaryParticle particle);

	/**
	 * @brief      Sets the parameters for enegy deposit histograms.
	 */
	static void SetHistogram(unsigned int nx, double x1, double x2, unsigned int ny, double y1, double y2, unsigned int nz, double z1, double z2);

	/**
	 * @brief      Access to primary particles in an event.
	 */
	Primaries GetPrimaries();

	/**
	 * @brief      Sets the primary particles.
	 */
	void SetPrimaries(Primaries prim);

	/**
	 * @brief      Iterator access to vector of PrimaryParticle
	 */
	PrimariesIterator PrimariesBegin();
	/**
	 * @brief      Iterator access to vector of PrimaryParticle
	 */
	PrimariesIterator PrimariesEnd();
	
	/**
	 * @brief      Clears the SimEvent object
	 */
	void Clear();

	/**
	 * @brief      Sets the simulated diffusion flag
	 */
	void SetDiffusion(bool diff=true){hasDiffusion=diff;}
	/**
	 * @brief      Sets the simlated attachment flag
	 */
	void SetAttachment(bool att=true){hasAttachment=att;}
	/**
	 * @brief      Sets the simlated gain flag
	 */
	void SetGain(bool gain=true){hasGain=gain;}
	/**
	 * @brief      Access to diffusion flag
	 */
	bool HasDiffusion(){ return hasDiffusion; }
	/**
	 * @brief      Access to attachment flag
	 */
	bool HasAttachment(){ return hasAttachment; }
	/**
	 * @brief      Access to gain flag
	 */
	bool HasGain(){ return hasGain; }
	
	/**
	 * @brief      Calculates integral of primary energy deposit histogram
	 */
	double PrimaryIntegral();
	/**
	 * @brief      Calculates integral of energy deposit histogram after
	 *             transport simulation
	 */
	double AfterTransportIntegral();
private:
	static unsigned int nBinsX; ///< Number of bins in X axis
	static unsigned int nBinsY; ///< Number of bins in Y axis
	static unsigned int nBinsZ; ///< Number of bins in Z axis
	static double xLow; ///< Low limit for X axis of energy deposit histogram
	static double xUp; ///< Up limit for X axis of energy deposit histogram
	static double yLow; ///< Low limit for Y axis of energy deposit histogram
	static double yUp; ///< Up limit for Y axis of energy deposit histogram
	static double zLow; ///< Low limit for Z axis of energy deposit histogram
	static double zUp; ///< Up limit for Z axis of energy deposit histogram
	static int eventID; //event ID used for unique histogram naming
	Primaries primaries; ///< Vector with primary particles
	TH3F* hPrimaryEnergyDeposit; ///< Primary energy deposit histogram
	TH3F* hEnergyDepositAfterTransport; ///< Energy deposit histogram after transport simulation
//	bool isBackground;
//	bool hasBackground;
	bool hasDiffusion; ///< Flag to tell if event has simulated diffusion
	bool hasAttachment; ///< Flag to tell if event has simulated attachment
	bool hasGain; ///< Flag to tell if event has simulated gain

	ClassDef(SimEvent,1); ///< ROOT macro to register SimEvent class
};




#endif