/**
 * @struct SolidDescriptor
 * @brief      Structure to hold information about solids inside detector
 *             geometry.
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
	G4String material; ///< material name of the solid
	G4Color color; ///< color of the solid
};

#endif