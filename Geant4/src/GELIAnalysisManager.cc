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
    if(config->GetI("save_ntuple"))
    {
      saveNtuple=true;
    }
    else
    {
      saveNtuple=false;
    }
  }
  else
    saveNtuple=false; 

  if(config->Has("save_custom_event_tree"))
  {
    if(config->GetI("save_custom_event_tree"))
    {
      saveCustomTree=true;
    }
    else
    {
      saveCustomTree=false;
    }
  }
  else
  {
    saveCustomTree=false; 
  }

  if(config->Has("energy_deposit_limits"))
  {
    xL=config->GetD("energy_deposit_limits", "xLow");
    xU=config->GetD("energy_deposit_limits", "xUp");
    yL=config->GetD("energy_deposit_limits", "yLow");
    yU=config->GetD("energy_deposit_limits", "yUp");
    zL=config->GetD("energy_deposit_limits", "zLow");
    zU=config->GetD("energy_deposit_limits", "zUp");
    HasEdepLimits=true;
  }
  else
  {
    HasEdepLimits=false;
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
    vx=new std::vector<G4double>;
    vy=new std::vector<G4double>;
    vz=new std::vector<G4double>;
    vEdep=new std::vector<G4double>;
    //ntuple to store energy deposit
    analysisManager->CreateNtuple("EDep", "EDep");
    analysisManager->CreateNtupleDColumn("x", *vx);
    analysisManager->CreateNtupleDColumn("y", *vy);
    analysisManager->CreateNtupleDColumn("z", *vz);
    analysisManager->CreateNtupleDColumn("Edep", *vEdep);
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
    unsigned int nBinsY=config->GetI("energy_deposit_histogram", "nBinsX");
    unsigned int nBinsX=config->GetI("energy_deposit_histogram", "nBinsY");
    unsigned int nBinsZ=config->GetI("energy_deposit_histogram", "nBinsZ");
    double xLow=config->GetD("energy_deposit_histogram", "xLow");
    double xUp=config->GetD("energy_deposit_histogram", "xUp");
    double yLow=config->GetD("energy_deposit_histogram", "yLow");
    double yUp=config->GetD("energy_deposit_histogram", "yUp");
    double zLow=config->GetD("energy_deposit_histogram", "zLow");
    double zUp=config->GetD("energy_deposit_histogram", "zUp");
    SimEvent::SetHistogram(nBinsX,xLow,xUp,nBinsY,yLow,yUp,nBinsZ,zLow,zUp);
    event=new SimEvent();
    tree->Branch("evt","SimEvent",event);
  }
}


//this function fills N-tuple with energy deposit and its positions
void GELIAnalysisManager::Fill(G4double x,G4double y,G4double z,G4double Edep, G4int event_number)
{
  if(HasEdepLimits&&(x<xL||x>xU||y<yL||y>yU||z<zL||z>zU))
    return;

  if(saveNtuple)
  {
    // G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    // analysisManager->FillNtupleDColumn(1,0, x);
    // analysisManager->FillNtupleDColumn(1,1, y);
    // analysisManager->FillNtupleDColumn(1,2, z);
    // analysisManager->FillNtupleDColumn(1,3, Edep);
    // analysisManager->FillNtupleIColumn(1,4, event_number);
    // analysisManager->AddNtupleRow(1);
    vx->push_back(x);
    vy->push_back(y);
    vz->push_back(z);
    vEdep->push_back(Edep);
  }

  if(saveCustomTree)
  {
    event->Fill(x,y,z,Edep);
  } 

}
void GELIAnalysisManager::finish() 
{  
  if(0);
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

void GELIAnalysisManager::SaveEvent(G4int eventID)
{
  if(0);
  if(saveNtuple)
  {
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    //analysisManager->FillNtupleIColumn(1,4, eventID);
    analysisManager->AddNtupleRow(1);
    vx->clear();
    vy->clear();
    vz->clear();
    vEdep->clear(); 
  }
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


