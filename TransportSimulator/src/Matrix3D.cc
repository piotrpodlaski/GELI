#include "Matrix3D.hh"
#include <iostream>
#include <algorithm>
#include <numeric>

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

void Matrix3D::Normalize()
{
	double sum=std::accumulate(data.begin(), data.end(), 0);//sum of elements
	std::for_each(data.begin(), data.end(), [=](double &x){ x=x/sum; });//divide by sum with lambda				
}
