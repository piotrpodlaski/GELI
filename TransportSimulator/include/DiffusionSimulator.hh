#ifndef DIFFUSIONSIMULATOR_H
#define DIFFUSIONSIMULATOR_H

#include "Matrix3D.hh"
#include <functional>
#include <map>

class CentralConfig;
class SimEvent;

class DiffusionSimulator
{
public:
	DiffusionSimulator();
	Matrix3D BuildGaussianKernel(double sigma_x, double sigma_y, double sigma_z);
	Matrix3D BuildProperGaussianKernel(double sigma_x, double sigma_y, double sigma_z);
	void SimulateDiffusion(TH3F* input, TH3F* output);
	void SimulateDiffusion(SimEvent *ev);
private:
	void ComputeSinglePoint(TH3F* output, int ix, int iy, int iz);
	void ComputeSingleLine(TH3F* output, int iy, int iz);
	void ComputeSinglePlane(TH3F* output, int iz);
	void BuildKernels();
	Matrix3D BuildGaussianKernel(int radius,double sigma_x, double sigma_y, double sigma_z);

	CentralConfig* config;
	Matrix3D kernel;
	Matrix3D input;
	std::map<int,Matrix3D> kernels;
	int kernelRadius;
	int kernelSize;
	//size of input historgam:
	int nBinsX;
	int nBinsY;
	int nBinsZ;
	double nSigmas;
	double deltax,deltay,deltaz; //bin widths, used to calculate diffusion coef.
	double minx,miny,minz;
	//Diffusion coefficient is defined as sigma of gauss (in mm),
	//which is a result of diffusion of point energy deposit
	//Diffusion coefficient depends on z with equation:
	//D_i(z)=D0_i+alpha_i*z (z is in mm)
	double D0_x, D0_y, D0_z; //diffusion coeficients along all directions
	double alpha_x, alpha_y, alpha_z; //slope for diffusion coefficient
	bool kernelBuiltForThisZ;
	bool areKernelsBuilt;
	std::string kernelType;

	
};


#endif