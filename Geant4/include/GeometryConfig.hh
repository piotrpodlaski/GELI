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

/**
 * @brief      Class handles parsing and interface to geometry config file
 * @details    Implemented as a singleton
 */
class GeometryConfig
{
public:

	/**
	 * @brief      Access to instance of the class
	 */
	static GeometryConfig* GetInstance();

	/**
	 * @brief      Access to information about solids in the detector geometry
	 */
	std::vector<SolidDescriptor> GetSolids();

private:

	/**
	 * @brief      Constructor
	 */
	GeometryConfig();

	/**
	 * @brief      Parses geometry config file
	 */
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