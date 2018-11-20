#ifndef DIFFUSIONSIMULATOR_H
#define DIFFUSIONSIMULATOR_H


#include "CentralConfig.hh"
#include "Matrix3D.hh"


class DiffusionSimulator
{
public:
	DiffusionSimulator();
	void BuildGaussianKernel(int radius,double sigma_x, double sigma_y, double sigma_z);
	void BuildGaussianKernel(double sigma_x, double sigma_y, double sigma_z);
	void SimulateDiffusion(TH3F* input, TH3F* output);
private:
	double ComputeSinglePoint(int ix, int iy, int iz, double prev_val);
	double ComputeSingleLine(TH3F* output, int iy, int iz);
	void ComputeSinglePlane(TH3F* output, int iz);

	CentralConfig* config;
	Matrix3D kernel;
	Matrix3D input;
	int kernelRadius;
	int kernelSize;
	//size of input historgam:
	int nBinsX;
	int nBinsY;
	int nBinsZ;
	double nSigmas;
	double deltax,deltay,deltaz; //bin widths, used to calculate diffusion coef.
	//Diffusion coefficient is defined as sigma of gauss (in mm),
	//which is a result of diffusion of point energy deposit
	//Diffusion coefficient depends on z with equation:
	//D_i(z)=D0_i+alpha_i*z (z is in mm)
	double D0_x, D0_y, D0_z; //diffusion coeficients along all directions
	double alpha_x, alpha_y, alpha_z; //slope for diffusion coefficient


	
};


#endif