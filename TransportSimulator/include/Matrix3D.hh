/**
 * @file Matrix3D.hh
 * @author     Piotr Podlaski
 * @brief      Definition of Matrix3D class
 */

#ifndef MATRIX3D_H
#define MATRIX3D_H
/// \cond
#include <vector>
#include <functional>
/// \endcond
#include "TH3F.h"

/**
 * @brief      Simple class to represent 3D matrix
 */
class Matrix3D
{
	typedef std::vector<double> dataType;
public:

	/**
	 * @brief      Constructor
	 */
	Matrix3D();
	
	/**
	 * @brief      Destructor
	 */
	~Matrix3D();
	
	/**
	 * @brief      Constructor with size parameters
	 */
	Matrix3D(int sX,int sY,int sZ);
	
	/**
	 * @brief      Constructor with size parameters and initial value
	 */
	Matrix3D(int sX,int sY,int sZ, double val);
	
	/**
	 * @brief      Copy constructor
	 */
	Matrix3D(const Matrix3D&);
	double& operator()(int ix,int iy,int iz);
	Matrix3D& operator=(Matrix3D);
	
	/**
	 * @brief      Access to size along x coordinate.
	 */
	int GetSizeX();
	/**
	 * @brief      Access to size along y coordinate.
	 */
	int GetSizeY();
	/**
	 * @brief      Access to size along z coordinate.
	 */
	int GetSizeZ();
	
	/**
	 * @brief      Normalizes the matrix - scales it, such that sum of elements is equal to 1
	 */
	void Normalize();
	
	/**
	 * @brief      Builds Matrix3D from 3D histogram
	 */
	static Matrix3D BuildMatrixFromTH3(TH3F* h);
	
	/**
	 * @brief      Builds a matrix from a function.
	 * @details    Builds a matrix of size 2*radius-1. Values in the bins are
	 *             values of the function calculated as a distance from the
	 *             center matrix cell (odd dimension guarantees that there is a
	 *             central cell)
	 */
	static Matrix3D BuildMatrixFromFunction(int radius, std::function<double(int,int,int)> f);
private:
	int sizeX; ///< Size of the matrix along X axis
	int sizeY; ///< Size of the matrix along Y axis
	int sizeZ; ///< Size of the matrix along Z axis
	dataType data; ///< Storage for the matrix cell values
};

#endif