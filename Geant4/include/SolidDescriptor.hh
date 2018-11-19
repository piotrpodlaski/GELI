/**
*\struct SolidDescriptor
*Structure to hold information about solids inside detector geometry.
*Information is parsed from geometry configuration file
*/
#ifndef SOLIDDESCRIPTOR_H
#define SOLIDDESCRIPTOR_H

#include <G4Color.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4String.hh>
#include <G4Types.hh>
#include <vector>
#include <iostream>

struct SolidDescriptor {
public:
	G4String name; ///< name of the solid
	G4String filename; ///< filename for .stl model
	std::vector<G4ThreeVector> pos; ///<vector with positions of solid's copies
	std::vector<G4RotationMatrix*> rot; ///<vector with rotations of solid's copies
	G4String material;
	G4Color color; ///<color of the solid
};

#endif