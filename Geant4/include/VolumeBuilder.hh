#ifndef VOLUMEBUILDER_H
#define VOLUMEBUILDER_H

#include <iostream>
#include <memory>
#include <map>
#include "G4String.hh"
#include "G4Material.hh"
#include "CADMesh.hh"


class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VisAttributes;
class MaterialBuilder;
struct SolidDescriptor;

class VolumeBuilder
{
public:
	VolumeBuilder();
	void BuildVolumes(G4LogicalVolume* world_phys);
private:
	G4VSolid* BuildSolid(SolidDescriptor solid);
	G4LogicalVolume* BuildLogical(SolidDescriptor solid);
	std::map<G4String,G4VSolid*> solids;
	std::map<G4String,G4LogicalVolume*> logical_volumes;
	std::map<G4String,G4VPhysicalVolume*> physical_volumes;
	std::map<G4String,G4VisAttributes*> vis_attributes;

	//TO DO:implement material store
	MaterialBuilder* material_builder;
	//std::map<G4String,G4Material*> materials;

};

#endif