#include "GELIAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
//#include "SimEvent.hh"

GELIAnalysisManager* GELIAnalysisManager::instance = nullptr;

GELIAnalysisManager::GELIAnalysisManager() 
{
  G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
  config=CentralConfig::GetInstance();
  if(config->Has("save_ntuple"))
  {
    if(config->Get("save_ntuple")=="1")
        saveNtuple=true;
    else
      saveNtuple=false;
  }
  if(config->Has("save_custom_event_tree"))
  {
    if(config->Get("save_custom_event_tree")=="1")
      saveCustomTree=true;
    else
      saveCustomTree=false;
  }
}


void GELIAnalysisManager::ConfigureOutput()
{
  G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
}


GELIAnalysisManager::~GELIAnalysisManager() 
{;}

GELIAnalysisManager* GELIAnalysisManager::GetInstance()
{
  if (!instance) instance = new GELIAnalysisManager;
  return instance;
}

void GELIAnalysisManager::book() 
{
  if(saveNtuple)
  {
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    std::string file_name;
    if(config->Has("ntuple_file_name"))
      file_name=config->Get("ntuple_file_name");
    else
      file_name="ntuple.root";
    analysisManager->OpenFile(file_name.c_str());
    analysisManager->SetFirstNtupleId(1);
    //ntuple to store energy deposit
    analysisManager->CreateNtuple("EDep", "EDep");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->CreateNtupleIColumn("event");
    analysisManager->FinishNtuple();

    //ntuple to store primaries
    analysisManager->CreateNtuple("prim","prim");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("px");
    analysisManager->CreateNtupleDColumn("py");
    analysisManager->CreateNtupleDColumn("pz");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleIColumn("id");
    analysisManager->CreateNtupleIColumn("event");
    analysisManager->FinishNtuple();

    G4cout << "Ntuples created" << G4endl;
  }

  if(saveCustomTree)
  {
    std::string file_name;
    if(config->Has("output_file_name"))
      file_name=config->Get("output_file_name");
    else
      file_name="out.root";
    file= new TFile(file_name.c_str(),"RECREATE");
    tree=new TTree("t","");
    //read parameters of the histogram from config file
    unsigned int nBinsY=std::stoi(config->Get("energy_deposit_histogram", "nBinsX"));
    unsigned int nBinsX=std::stoi(config->Get("energy_deposit_histogram", "nBinsY"));
    unsigned int nBinsZ=std::stoi(config->Get("energy_deposit_histogram", "nBinsZ"));
    double xLow=std::stof(config->Get("energy_deposit_histogram", "xLow"));
    double xUp=std::stof(config->Get("energy_deposit_histogram", "xUp"));
    double yLow=std::stof(config->Get("energy_deposit_histogram", "yLow"));
    double yUp=std::stof(config->Get("energy_deposit_histogram", "yUp"));
    double zLow=std::stof(config->Get("energy_deposit_histogram", "zLow"));
    double zUp=std::stof(config->Get("energy_deposit_histogram", "zUp"));
    SimEvent::SetHistogram(nBinsX,xLow,xUp,nBinsY,yLow,yUp,nBinsZ,zLow,zUp);
    event=new SimEvent("aa");
    tree->Branch("evt","SimEvent",event);
  }
}


//this function fills N-tuple with energy deposit and its positions
void GELIAnalysisManager::Fill(G4double x,G4double y,G4double z,G4double Edep, G4int event_number)
{

  if(saveNtuple)
  {
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(1,0, x);
    analysisManager->FillNtupleDColumn(1,1, y);
    analysisManager->FillNtupleDColumn(1,2, z);
    analysisManager->FillNtupleDColumn(1,3, Edep);
    analysisManager->FillNtupleIColumn(1,4, event_number);
    analysisManager->AddNtupleRow(1);
  }

  if(saveCustomTree)
  {
    event->Fill(x,y,z,Edep);
  } 

}
void GELIAnalysisManager::finish() 
{  
  if(saveNtuple)
  {
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
  }

  if(saveCustomTree)
  {
    tree->Write();
    file->Close();
  }
  // Complete clean-up
//  delete analysisManager;
}

void GELIAnalysisManager::SaveEvent()
{
  if(saveCustomTree)
  {
    tree->Fill();
    event->Clear();
  }
}

void GELIAnalysisManager::AddPrimary(G4double x, G4double y, G4double z,
          G4double px, G4double py, G4double pz,
          G4double energy, G4int id, G4int event_number)
{
  if(saveCustomTree)
  {
    PrimaryParticle primary;
    primary.x=x/mm;
    primary.y=y/mm;
    primary.z=z/mm;
    primary.px=px;
    primary.py=py;
    primary.pz=pz;
    primary.E=energy;
    primary.particleID=id;
    event->AddPrimaryParticle(primary);
  }

  if(saveNtuple)
  {
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(2,0, x);
    analysisManager->FillNtupleDColumn(2,1, y);
    analysisManager->FillNtupleDColumn(2,2, z);
    analysisManager->FillNtupleDColumn(2,3, px);
    analysisManager->FillNtupleDColumn(2,4, py);
    analysisManager->FillNtupleDColumn(2,5, pz);
    analysisManager->FillNtupleDColumn(2,6, energy);
    analysisManager->FillNtupleIColumn(2,7, id);
    analysisManager->FillNtupleIColumn(2,8, event_number);
    analysisManager->AddNtupleRow(2);
  }
}


