/**
 * @file MT.cc
 * @author     Piotr Podlaski
 * @brief      Top level TransportSimulator application
 */


#include "EventReader.hh"
#include "Worker.hh"


int main(int argc, char** argv)
{
	if(argc<2)
	{
		std::cout<<"Usage: ./"<<argv[0]<<" <file with MC data>"<<std::endl;
		return 1;
	}	
	EventReader* ev_reader=new EventReader(argv[1]);
	Worker worker(ev_reader,argv[1]);
	worker.Run();


}

