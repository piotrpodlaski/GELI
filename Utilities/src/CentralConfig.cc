#include <CentralConfig.hh>


CentralConfig* CentralConfig::instance=nullptr;

CentralConfig* CentralConfig::GetInstance(std::string configFileName)
{
	if(instance==nullptr)
		instance=new CentralConfig(configFileName);
	return instance;
}

CentralConfig::CentralConfig(std::string configFileName)
{
	if(configFileName=="")
		result = config.load_file("config.xml");
	else
		result = config.load_file(configFileName.c_str());
	
	if (!result)
		std::cerr<<"\e[31mError opening central config file: "<<configFileName<<". Check if file exists, and that the formatting is correct!!\e[0m"<<std::endl;
}

bool CentralConfig::Has(std::string field_name)
{
	return !GetChild(config,field_name.c_str()).empty();
}

pugi::xml_node CentralConfig::GetChild(pugi::xml_node parent, std::string field_name)
{
	return parent.child(field_name.c_str());
}

