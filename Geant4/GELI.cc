/**
 * @file GELI.cc
 * @author     Piotr Podlaski
 * @brief      Top level Geant4 application
 */

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "GELIDetectorConstruction.hh"
#include "GELIPhysicsList.hh"
#include "GELIActionInitializer.hh"
#include "CentralConfig.hh"
#include <string>
#include <time.h>

#include "GeometryConfig.hh"



int main(int argc,char** argv) {
  clock_t t1,t2;
  t1=clock();


  //choose the Random engine
  //G4Random::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
std::string configFileName="config.xml";
if(argc>2)
  configFileName=argv[2];
CentralConfig* config=CentralConfig::GetInstance(configFileName);
bool runMT;
//check if runMT is defined in config file
if(config->Has("run_mt")&&config->GetI("run_mt"))
{
  //check if saving custom event file is set ON in config file, if so run single threaded
  if(config->Has("save_custom_event_tree")&&config->GetI("save_custom_event_tree"))
    runMT=false;
  else
    runMT=true;  
}
else
{
  runMT=false;
}

G4RunManager* runManager;
  // Construct the default run manager
#ifdef G4MULTITHREADED
  
  if(runMT)
  {
    int nThreads;
    if(config->Has("number_mt_threads")&&config->GetI("number_mt_threads")>0)
    {
      nThreads=config->GetI("number_mt_threads");
    }
    else
    {
      nThreads=G4Threading::G4GetNumberOfCores();
    }
    runManager = new G4MTRunManager;
    static_cast<G4MTRunManager*>(runManager)->SetNumberOfThreads(nThreads);
  }
  else
  {
    runManager = new G4RunManager;
  }

//  G4MTRunManager* runManager = new G4MTRunManager;
//  runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
//  runManager->SetNumberOfThreads(3);
#else
  runManager = new G4RunManager;
#endif

  // set mandatory initialization classes
  runManager->SetUserInitialization(new GELIDetectorConstruction);
  runManager->SetUserInitialization(new GELIPhysicsList);  
  runManager->SetUserInitialization(new GELIActionInitializer());


#ifdef G4VIS_USE
  // visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  
  //Initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the User Interface manager 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();  


  if (argc==1)   // Define UI session for interactive mode.
  {
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute vis.mac");     
#endif
    ui->SessionStart();
    delete ui;
#endif
  }
  else           // Batch mode
  { 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  // job termination
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  t2=clock();
  float diff ((float)t2-(float)t1);
  float seconds = diff / CLOCKS_PER_SEC;
  std::cout<<"Total simulation time"<<"\t"<<seconds<<"\n";
  return 0;
}

