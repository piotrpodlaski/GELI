#ifndef GEOMETRYCONFIG_H
#define GEOMETRYCONFIG_H

#include <iostream>
#include <SolidDescriptor.hh>
#include <G4String.hh>
#include <fstream>
#include <sstream>
#include <string>
#include <G4ThreeVector.hh>
#include <G4Color.hh>
#include <CentralConfig.hh>
#include "globals.hh"
#include "pugixml.hh"
#include <map>

class GeometryConfig
{
public:
	static GeometryConfig* GetInstance();
	std::vector<SolidDescriptor> GetSolids();

private:
	GeometryConfig();
	void ParseGeometry();
	static GeometryConfig* instance;
	std::vector<SolidDescriptor> solids;
	//void ParseGeometry();
	std::string config_name="geometry.xml";
	CentralConfig* central_config;
	pugi::xml_document config;
	pugi::xml_parse_result result;
	std::map<std::string, G4Color> material_colors;
	std::string path_to_stl;
	
};

#endif