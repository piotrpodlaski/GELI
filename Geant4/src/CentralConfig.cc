#include <CentralConfig.hh>


CentralConfig* CentralConfig::instance=nullptr;

CentralConfig* CentralConfig::GetInstance()
{
	if(instance==nullptr)
		instance=new CentralConfig();
	return instance;
}

CentralConfig::CentralConfig()
{
	result = config.load_file(config_file.c_str());
	if (!result)
		std::cerr<<"\e[31mError opening central config file. Check if file exists!\e[0m"<<std::endl;
}

bool CentralConfig::Has(std::string field_name)
{
	return !GetChild(config,field_name.c_str()).empty();
}

pugi::xml_node CentralConfig::GetChild(pugi::xml_node parent, std::string field_name)
{
	return parent.child(field_name.c_str());
}

