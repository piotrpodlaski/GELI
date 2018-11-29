#ifndef GELITPCDETECTOR_H
#define GELITPCDETECTOR_H

class G4LogicalVolume;

class GELITPCDetector
{
public:
	
	static void BuildTPCDetector(G4LogicalVolume* mother_log);
	
};

#endif