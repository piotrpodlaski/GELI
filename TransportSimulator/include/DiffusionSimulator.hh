/**
 * @file DiffusionSimulator.hh
 * @author     Piotr Podlaski
 * @brief      Definition of DiffusionSimulator class
 */

#ifndef DIFFUSIONSIMULATOR_H
#define DIFFUSIONSIMULATOR_H

#include "Matrix3D.hh"
/// \cond
#include <functional>
#include <map>
/// \endcond
class CentralConfig;
class SimEvent;

/**
 * @brief      Class handles simulation of diffusion in gas
 */
class DiffusionSimulator
{
public:

	/**
	 * @brief      Constructor
	 */
	DiffusionSimulator();

	/**
	 * @brief      Builds a gaussian diffusion kernel.
	 * Kernel is built basing on values of gaussian distribution in bin centers
	 */
	Matrix3D BuildGaussianKernel(double sigma_x, double sigma_y, double sigma_z);
	/**
	 * @brief      Builds a priper gaussian diffusion kernel.
	 * Kernel is built basing on integrals of gaussian distribution across bins
	 */
	Matrix3D BuildProperGaussianKernel(double sigma_x, double sigma_y, double sigma_z);
	
	/**
	 * @brief      Simulates diffusion on input and stores result to output
	 */
	void SimulateDiffusion(TH3F* input, TH3F* output);

	/**
	 * @brief      Simulates diffusion in SimEvent object
	 */
	void SimulateDiffusion(SimEvent *ev);
private:

	/**
	 * @brief      Calculates diffusion of a single histogram bin.
	 */
	void ComputeSinglePoint(TH3F* output, int ix, int iy, int iz);
	/**
	 * @brief      Calculates diffusion of a single histogram line along X axis.
	 */
	void ComputeSingleLine(TH3F* output, int iy, int iz);
	/**
	 * @brief      Calculates diffusion of a single histogram XY plane.
	 */
	void ComputeSinglePlane(TH3F* output, int iz);
	
	/**
	 * @brief      Builds kernels for all Z slices
	 */
	void BuildKernels();
	
	/**
	 * @brief      Builds a gaussian kernel with given radius
	 */
	Matrix3D BuildGaussianKernel(int radius,double sigma_x, double sigma_y, double sigma_z);

	CentralConfig* config; ///< Pointer to CentraLConfig object
	Matrix3D kernel; ///< Diffusion kernel for current calculation
	Matrix3D input; ///< Input histogram converted to a Matrix3D
	std::map<int,Matrix3D> kernels; ///< Kernels for all Z slices
	int kernelRadius; ///< Radius of a kernel
	int kernelSize; ///< Size of a kernel, size=2*radius-1
	//size of input historgam:
	int nBinsX; ///< Number of bins fo X axis
	int nBinsY; ///< Number of bins fo Y axis
	int nBinsZ; ///< Number of bins fo Z axis
	double nSigmas; ///< Number of sigmas for kernel truncation
	double deltax; ///< Bin width for X axis
	double deltay; ///< Bin width for Y axis
	double deltaz; ///< Bin width for Z axis
	double minx; ///< Monimal value of X axis
	double miny; ///< Monimal value of Y axis
	double minz; ///< Monimal value of Z axis
	//Diffusion coefficient is defined as sigma of gauss (in mm),
	//which is a result of diffusion of point energy deposit
	//Diffusion coefficient depends on z with equation:
	//D_i(z)=D0_i+alpha_i*z (z is in mm)
	double D0_x; ///< Diffusion coefficient for X axis, for details see config file
	double D0_y; ///< Diffusion coefficient for Y axis, for details see config file
	double D0_z; ///< Diffusion coefficient for Z axis, for details see config file
	double alpha_x; ///< \f$\alpha_x\f$ parameter, for details see config file
	double alpha_y; ///< \f$\alpha_y\f$ parameter, for details see config file
	double alpha_z; ///< \f$\alpha_z\f$ parameter, for details see config file
	bool areKernelsBuilt; ///< Flag to tell if kernels are built
	/**
	 * @brief      Name of the kernel type
	 * @details    Allowed options are:
	 * <ul>
	 * <li> "BinCenterGaussian" </li>
	 * <li> "ProperGaussian" </li>
	 * </ul>
	 */
	std::string kernelType;

	
};


#endif