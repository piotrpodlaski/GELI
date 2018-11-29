#ifndef CENTRALCONFIG_H
#define CENTRALCONFIG_H

#include <iostream>
#include "pugixml.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string>

class CentralConfig
{
public:
	static CentralConfig* GetInstance();
	template<typename... Ts> //varidadic template to allow multi-level config parsing
	std::string Get(std::string field_name,Ts... args)
	{
		std::string res;
		res=GetChild(config, field_name,args...).text().as_string();
		//std::cout<<res<<std::endl;
		return res;
	}

	template<typename... Ts> //varidadic template to allow multi-level config parsing
	int GetI(std::string field_name,Ts... args)
	{
		std::string res;
		res=GetChild(config, field_name,args...).text().as_string();
		//std::cout<<res<<std::endl;
		return std::stoi(res);
	}

	template<typename... Ts> //varidadic template to allow multi-level config parsing
	double GetD(std::string field_name,Ts... args)
	{
		std::string res;
		res=GetChild(config, field_name,args...).text().as_string();
		//std::cout<<res<<std::endl;
		return std::stof(res);
	}

	bool Has(std::string field_name);

private:
	CentralConfig();
	pugi::xml_node GetChild(pugi::xml_node parent, std::string field_name);
	template<typename... Ts>
	pugi::xml_node GetChild(pugi::xml_node parent, std::string field_name, Ts... args)
	{
		return GetChild(parent.child(field_name.c_str()),args...);
	}

	static CentralConfig* instance;
	pugi::xml_document config;
	pugi::xml_parse_result result;
	std::string config_file="config.xml";
};

#endif
