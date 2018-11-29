#include "GELITPCDetector.hh"
#include "VolumeBuilder.hh"
#include "G4LogicalVolume.hh"

void GELITPCDetector::BuildTPCDetector(G4LogicalVolume* mother_log)
{
	VolumeBuilder* builder = new VolumeBuilder();
    builder->BuildVolumes(mother_log);
}