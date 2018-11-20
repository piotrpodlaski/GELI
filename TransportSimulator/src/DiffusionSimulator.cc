#include "DiffusionSimulator.hh"
#include <cmath>
#include <functional>
#include <algorithm>
#include "TString.h"
#include <iostream>


DiffusionSimulator::DiffusionSimulator()
{
	config=CentralConfig::GetInstance();
	nSigmas=config->GetD("diffusion","n_sigmas");
	D0_x=config->GetD("diffusion","Dx");
	D0_y=config->GetD("diffusion","Dy");
	D0_z=config->GetD("diffusion","Dz");
	alpha_x=config->GetD("diffusion","alpha_x");
	alpha_y=config->GetD("diffusion","alpha_y");
	alpha_z=config->GetD("diffusion","alpha_z");
}

void DiffusionSimulator::BuildGaussianKernel(int radius,double sx, double sy, double sz)
{
	auto gauss=[=](int x, int y, int z)->double
					{
						return exp(-x*x/(2.*sx*sx)-y*y/(2.*sy*sy)-z*z/(2.*sz*sz));
					};
	kernel=Matrix3D::BuildMatrixFromFunction(radius,gauss);
	kernelRadius=radius;
	kernelSize=kernel.GetSizeX();//sizes in all dimmensions are identical
	//cut bins outside radius
	double s2x=(nSigmas*sx-0.5)*(nSigmas*sx-0.5);
	double s2y=(nSigmas*sy-0.5)*(nSigmas*sy-0.5);
	double s2z=(nSigmas*sz-0.5)*(nSigmas*sz-0.5);
	for(int x=0;x<kernelSize;x++)
		for(int y=0;y<kernelSize;y++)
			for(int z=0;z<kernelSize;z++)
				if((x-radius+1.)*(x-radius+1.)/s2x+(y-radius+1.)*(y-radius+1.)/s2y+(z-radius+1)*(z-radius+1)/s2z>1)
					kernel(x,y,z)=0;
	
	kernel.Normalize();
}

void DiffusionSimulator::BuildGaussianKernel(double sx, double sy, double sz)
{
	//three sigma radius
	int radius;
	int rx=ceil(nSigmas*sx);
	int ry=ceil(nSigmas*sy);
	int rz=ceil(nSigmas*sz);
	radius=std::max(rx,std::max(ry,rz));
	BuildGaussianKernel(radius,sx,sy,sz);
}

double DiffusionSimulator::ComputeSinglePoint(int ix, int iy, int iz, double prev_val)
{
	double result=0;
	int ksize=kernel.GetSizeX();
	int x=0;
	if(prev_val==0)
	{
		//everything to the left is zero, because matrix has rounded corners we cannot use only last layer
		x=ksize/2;
	}
	for(;x<ksize;x++)
	{
		for(int y=0;y<kernelSize;y++)
		{
			for(int z=0;z<kernelSize;z++)
			{
				//std::cout<<"begin (x,y,z)=("<<x<<","<<y<<","<<z<<")"<<std::endl;
				int input_posx=x+ix-kernelRadius+1;
				int input_posy=y+iy-kernelRadius+1;
				int input_posz=z+iz-kernelRadius+1;
				//do nothing outside of the input matrix
				// /std::cout<<input_posx<<" "<<input_posy<<" "<<input_posz<<std::endl;
				if(input_posx<0||input_posx>=nBinsX)
					continue;
				if(input_posy<0||input_posy>=nBinsY)
					continue;
				if(input_posz<0||input_posz>=nBinsZ)
					continue;
				result+=kernel(x,y,z)*input(input_posx,input_posy,input_posz);
			}
		}
	}
	return result;

}

void DiffusionSimulator::SimulateDiffusion(TH3F* hInput, TH3F* output)
{
	input=Matrix3D::BuildMatrixFromTH3(hInput);
	nBinsX=input.GetSizeX();
	nBinsY=input.GetSizeY();
	nBinsZ=input.GetSizeZ();
	deltax=hInput->GetXaxis()->GetBinWidth(1);
	deltay=hInput->GetYaxis()->GetBinWidth(1);
	deltaz=hInput->GetZaxis()->GetBinWidth(1);
	std::cout<<nBinsX<<" "<<nBinsY<<" "<<nBinsZ<<std::endl;
	//std::cout<<"Kernel Done "<<kernelRadius<<" "<<kernelSize<< std::endl;
	//make sure that output histo exists
	for(int z=0;z<nBinsZ;z++)
	{
		std::cout<<"Begining z="<<z<<std::endl;
		ComputeSinglePlane(output, z);
		//std::cout<<"Done z="<<z<<std::endl;
	}
}

void DiffusionSimulator::ComputeSinglePlane(TH3F* output, int iz)
{
	for(int y=0;y<nBinsY;y++)
	{
		double Dx=D0_x+alpha_x*iz*deltaz;
		double Dy=D0_y+alpha_y*iz*deltaz;
		double Dz=D0_z+alpha_z*iz*deltaz;
		BuildGaussianKernel(Dx/deltax,Dy/deltay,Dz/deltaz);
		//std::cout<<"begining (x,y)=("<<x<<","<<y<<")"<<std::endl;
		ComputeSingleLine(output,y,iz);
		/*if(value!=0)
			std::cout<<value<<std::endl;*/
		//output->SetBinContent(output->GetBin(x+1,y+1,iz+1),value);
		//std::cout<<"Done (x,y)=("<<x<<","<<y<<")"<<std::endl;
	}
}

double DiffusionSimulator::ComputeSingleLine(TH3F* output, int iy, int iz)
{
	double value=1.;
	for(int x=0;x<nBinsX;x++)
	{
		value=ComputeSinglePoint(x,iy,iz, value);
		output->SetBinContent(output->GetBin(x+1,iy+1,iz+1),value);
	}
	return 0;
}

