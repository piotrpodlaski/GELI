/**
 * @file DiffusionSimulator.cc
 * @author     Piotr Podlaski
 * @brief      Implementation of DiffusionSimulator class
 */

#include "DiffusionSimulator.hh"
/// \cond
#include <cmath>
#include <iostream>
#include <algorithm>
/// \endcond
#include "TString.h"
#include "SimEvent.hh"
#include "CentralConfig.hh"




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
	kernelType=config->Get("diffusion","kernel_type");
	areKernelsBuilt=false;
}

Matrix3D DiffusionSimulator::BuildGaussianKernel(int radius,double sx, double sy, double sz)
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
	return kernel;
}

void DiffusionSimulator::BuildKernels()
{
	for(int iz=0;iz<nBinsZ;iz++)
	{
		double Dx=sqrt(D0_x*D0_x+alpha_x*iz*deltaz);
		double Dy=sqrt(D0_y*D0_y+alpha_y*iz*deltaz);
		double Dz=sqrt(D0_z*D0_z+alpha_z*iz*deltaz);
		if(kernelType=="ProperGaussian")
			kernels[iz]=BuildProperGaussianKernel(Dx/deltax,Dy/deltay,Dz/deltaz);
		else if(kernelType=="BinCenterGaussian")
			kernels[iz]=BuildGaussianKernel(Dx/deltax,Dy/deltay,Dz/deltaz);
	}
}

Matrix3D DiffusionSimulator::BuildGaussianKernel(double sx, double sy, double sz)
{
	//three sigma radius
	int radius;
	int rx=ceil(nSigmas*sx);
	int ry=ceil(nSigmas*sy);
	int rz=ceil(nSigmas*sz);
	radius=std::max(rx,std::max(ry,rz));
	BuildGaussianKernel(radius,sx,sy,sz);
	//BuildProperGaussianKernel(sx,sy,sz);
	return kernel;
}

Matrix3D DiffusionSimulator::BuildProperGaussianKernel(double sx, double sy, double sz)
{
	//three sigma radius
	int radius;
	int rx=ceil(nSigmas*sx);
	int ry=ceil(nSigmas*sy);
	int rz=ceil(nSigmas*sz);
	radius=std::max(rx,std::max(ry,rz));
	auto proper_gauss=[=](int x, int y, int z)->double
	{
		//integral of gaussian in single bin:
		double int_x=0.5*std::erf((x+deltax/2.)/(sx*sqrt(2)))-0.5*std::erf((x-deltax/2.)/(sx*sqrt(2)));
		double int_y=0.5*std::erf((y+deltay/2.)/(sy*sqrt(2)))-0.5*std::erf((y-deltay/2.)/(sy*sqrt(2)));
		double int_z=0.5*std::erf((z+deltaz/2.)/(sz*sqrt(2)))-0.5*std::erf((z-deltaz/2.)/(sz*sqrt(2)));
		return int_x*int_y*int_z;
	};

	kernel=Matrix3D::BuildMatrixFromFunction(radius,proper_gauss);
	kernelRadius=radius;
	kernelSize=kernel.GetSizeX();//sizes in all dimmensions are identical
	//cut bins outside radius
	double s2x=(rx-0.5)*(rx-0.5);
	double s2y=(ry-0.5)*(ry-0.5);
	double s2z=(rz-0.5)*(rz-0.5);
	for(int x=0;x<kernelSize;x++)
		for(int y=0;y<kernelSize;y++)
			for(int z=0;z<kernelSize;z++)
				if((x-radius+1.)*(x-radius+1.)/s2x+(y-radius+1.)*(y-radius+1.)/s2y+(z-radius+1)*(z-radius+1)/s2z>1)
					kernel(x,y,z)=0;
	
	kernel.Normalize();
	return kernel;
	//std::cout<<kernelRadius<<" "<<kernelSize<<" "<<sqrt(s2y)<<std::endl;

}

void DiffusionSimulator::ComputeSinglePoint(TH3F* output, int ix, int iy, int iz)
{
	double value=input(ix,iy,iz);
	if(value==0)
		return;
	//build kernel only if it is needed
	/*
	if(!kernelBuiltForThisZ)
	{
		double Dx=D0_x+alpha_x*(nBinsZ-iz-1)*deltaz;
		double Dy=D0_y+alpha_y*(nBinsZ-iz-1)*deltaz;
		double Dz=D0_z+alpha_z*(nBinsZ-iz-1)*deltaz;
		if(kernelType=="ProperGaussian")
			BuildProperGaussianKernel(Dx/deltax,Dy/deltay,Dz/deltaz);
		else if(kernelType=="BinCenterGaussian")
			BuildGaussianKernel(Dx/deltax,Dy/deltay,Dz/deltaz);
		kernelBuiltForThisZ=true;
	}
	*/
	//build kernels only once
	if(!areKernelsBuilt)
	{
		BuildKernels();
		areKernelsBuilt=true;
	}
	kernel=kernels[iz];
	kernelSize=kernel.GetSizeX();
	kernelRadius=(kernelSize+1)/2;
	for(int x=0;x<kernelSize;x++)
	{
		for(int y=0;y<kernelSize;y++)
		{
			for(int z=0;z<kernelSize;z++)
			{
				//std::cout<<"begin (x,y,z)=("<<x<<","<<y<<","<<z<<")"<<std::endl;
				int output_posx=x+ix-kernelRadius+2;
				int output_posy=y+iy-kernelRadius+2;
				int output_posz=z+iz-kernelRadius+2;
				//do nothing outside of the output matrix
				// /std::cout<<input_posx<<" "<<input_posy<<" "<<input_posz<<std::endl;
				if(output_posx<0||output_posx>=nBinsX)
					continue;
				if(output_posy<0||output_posy>=nBinsY)
					continue;
				if(output_posz<0||output_posz>=nBinsZ)
					continue;
				double to_fill=kernel(x,y,z)*value;
				//double to_fillx=output_posx*deltax+minx+0.5*deltax;
				//double to_filly=output_posy*deltay+miny+0.5*deltay;
				//double to_fillz=output_posz*deltaz+minz+0.5*deltaz;
				//output->Fill(to_fillx,to_filly,to_fillz,to_fill);
				int bin=output->GetBin(output_posx,output_posy,output_posz);
				output->AddBinContent(bin,to_fill);
			}
		}
	}
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
	minx=hInput->GetXaxis()->GetBinLowEdge(1);
	miny=hInput->GetYaxis()->GetBinLowEdge(1);
	minz=hInput->GetZaxis()->GetBinLowEdge(1);
	//std::cout<<nBinsX<<" "<<nBinsY<<" "<<nBinsZ<<std::endl;
	//std::cout<<"Kernel Done "<<kernelRadius<<" "<<kernelSize<< std::endl;
	//clear output histo, just in case:
	output->Clear();	

	for(int z=0;z<nBinsZ;z++)
	{
		//std::cout<<"Begining z="<<z<<std::endl;
		ComputeSinglePlane(output, z);
		//std::cout<<"Done z="<<z<<std::endl;
	}
}

void DiffusionSimulator::SimulateDiffusion(SimEvent *ev)
{	
	SimulateDiffusion(ev->GetPrimaryHisto(), ev->GetAfterTransportHisto());
	ev->SetDiffusion();
}

void DiffusionSimulator::ComputeSinglePlane(TH3F* output, int iz)
{
	for(int y=0;y<nBinsY;y++)
	{
		// double Dx=D0_x+alpha_x*iz*deltaz;
		// double Dy=D0_y+alpha_y*iz*deltaz;
		// double Dz=D0_z+alpha_z*iz*deltaz;
		//BuildGaussianKernel(Dx/deltax,Dy/deltay,Dz/deltaz);
		//std::cout<<"begining (x,y)=("<<x<<","<<y<<")"<<std::endl;
		ComputeSingleLine(output,y,iz);
		/*if(value!=0)
			std::cout<<value<<std::endl;*/
		//output->SetBinContent(output->GetBin(x+1,y+1,iz+1),value);
		//std::cout<<"Done (x,y)=("<<x<<","<<y<<")"<<std::endl;
	}
}

void DiffusionSimulator::ComputeSingleLine(TH3F* output, int iy, int iz)
{
	for(int x=0;x<nBinsX;x++)
	{
		ComputeSinglePoint(output, x,iy,iz);
		//output->SetBinContent(output->GetBin(x+1,iy+1,iz+1),value);
	}
}

