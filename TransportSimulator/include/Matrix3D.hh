#ifndef MATRIX3D_H
#define MATRIX3D_H
#include <vector>
#include "TH3F.h"

class Matrix3D
{
	typedef std::vector<double> dataType;
public:
	Matrix3D();
	~Matrix3D();
	Matrix3D(int sX,int sY,int sZ);
	Matrix3D(int sX,int sY,int sZ, double val);
	Matrix3D(const Matrix3D&);
	double& operator()(int ix,int iy,int iz);
	Matrix3D& operator=(Matrix3D);
	int GetSizeX();
	int GetSizeY();
	int GetSizeZ();
	void Normalize();
	static Matrix3D BuildMatrixFromTH3(TH3F* h);
private:
	int sizeX;
	int sizeY;
	int sizeZ;
	dataType data;
};

#endif