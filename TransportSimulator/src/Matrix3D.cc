/**
 * @file Matrix3D.cc
 * @author     Piotr Podlaski
 * @brief      Implemetation of Matrix3D class
 */

#include "Matrix3D.hh"
/// \cond
#include <iostream>
#include <algorithm>
#include <numeric>
/// \endcond

Matrix3D::Matrix3D() :sizeX(0), sizeY(0), sizeZ(0)
{}

Matrix3D::~Matrix3D()
{}

Matrix3D::Matrix3D(int sX,int sY,int sZ) :sizeX(sX), sizeY(sY), sizeZ(sZ)
{
	data= std::vector<double>(sX*sY*sZ,0);
}

Matrix3D::Matrix3D(int sX,int sY,int sZ, double val) :sizeX(sX), sizeY(sY), sizeZ(sZ)
{
	data= std::vector<double>(sX*sY*sZ,val);
}

Matrix3D::Matrix3D(const Matrix3D &A) :sizeX(A.sizeX), sizeY(A.sizeY), sizeZ(A.sizeZ), data(A.data)
{}

int Matrix3D::GetSizeX()
{
	return sizeX;
}

int Matrix3D::GetSizeY()
{
	return sizeY;
}

int Matrix3D::GetSizeZ()
{
	return sizeZ;
}

double& Matrix3D::operator()(int x,int y, int z)
{
	return data[x*sizeZ*sizeY+y*sizeZ+z];
}

Matrix3D& Matrix3D::operator = (Matrix3D A)
{
	sizeX=A.sizeX;
	sizeY=A.sizeY;
	sizeZ=A.sizeZ;
	data=A.data;
	return *this;
}

Matrix3D Matrix3D::BuildMatrixFromTH3(TH3F* h)
{
	int nX=h->GetNbinsX();
	int nY=h->GetNbinsY();
	int nZ=h->GetNbinsZ();
	Matrix3D mat=Matrix3D(nX,nY,nZ);
	for(int ix=1; ix<=nX;ix++)
		for(int iy=1;iy<=nY;iy++)
			for(int iz=1;iz<=nZ;iz++)
				mat(ix-1,iy-1,iz-1)=h->GetBinContent(h->GetBin(ix,iy,iz));
	return mat;
}

Matrix3D Matrix3D::BuildMatrixFromFunction(int radius, std::function<double(int,int,int)> f)
{
	int size;
	//initialize matrix with odd number of cells in each direction so there is a central cell
	//radius=1 gives 1x1x1 matrix, radius=2 gives 3x3x3, radius=3 gives 5x5x5 etc.
	if(radius>0)
		size=2*radius-1;
	else
		size=1;
	Matrix3D mat=Matrix3D(size,size,size);
	for(int ix=0; ix<size;ix++)
		for(int iy=0;iy<size;iy++)
			for(int iz=0;iz<size;iz++)
			{
				//pass the distance from central cell to the function
				mat(ix,iy,iz)=f(ix-radius+1,iy-radius+1,iz-radius+1);
			}
	//mat.Normalize();
	return mat;
}

void Matrix3D::Normalize()
{

	double sum=std::accumulate(data.begin(), data.end(), 0.);//sum of elements
	std::for_each(data.begin(), data.end(), [=](double &x){ x=x/sum; });//divide by sum with lambda				
}

