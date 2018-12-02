
#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4ios.hh"

#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * @brief      Class handles interface for magnetic field map
 * @details    It reads magnetic field map from the file, stores it in memory
 *             and handles interpolation for tracking purposes
 */
class GELITabulatedField3D : public G4MagneticField
{
  
  // Storage space for the table
  vector< vector< vector< G4double > > > xField;
  vector< vector< vector< G4double > > > yField;
  vector< vector< vector< G4double > > > zField;
  // The dimensions of the table
  int nx,ny,nz; 
  // The physical limits of the defined region
  double minx, maxx, miny, maxy, minz, maxz;
  // The physical extent of the defined region
  double dx, dy, dz;
  double fZoffset;
  bool invertX, invertY, invertZ;

public:

  /**
   * @brief      Constructor
   */
  GELITabulatedField3D(const char* filename, G4double xOffset );
  
  /**
   * @brief      Access to value of the magnetic field used for tracking
   */
  void  GetFieldValue( const  double Point[4],
		       double *Bfield          ) const;
};

