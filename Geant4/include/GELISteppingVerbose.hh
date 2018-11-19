
class GELISteppingVerbose;

#ifndef GELISteppingVerbose_h
#define GELISteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

class GELISteppingVerbose : public G4SteppingVerbose {

public:   
  
  //Constructor/Destructor
  GELISteppingVerbose();
  ~GELISteppingVerbose();
  
  void StepInfo();
  void TrackingStarted();

};

#endif
