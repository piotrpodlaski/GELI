#ifndef MATERIALBUILDER_H
#define MATERIALBUILDER_H

#include "G4String.hh"
#include "G4Material.hh"
#include <map>

class  G4NistManager;

class MaterialBuilder
{
	typedef std::map<G4String,G4Material*> Materials;
public:
	static MaterialBuilder* GetInstance();
	Materials GetMaterials();
	G4Material* GetMaterial(G4String material_name);
private:
	static MaterialBuilder* instance;
	MaterialBuilder();
	void BuildMaterials();
	Materials materials;
	G4NistManager* nist_manager;
};

#endif