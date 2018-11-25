#include "EventReader.hh"
#include "Worker.hh"
#include <thread>


int main()
{
	EventReader* ev_reader=new EventReader("test.root");
	std::vector<Worker*> workers;
	std::vector<std::thread*> threads;
	int nWorkers=8;
	for(int i=0;i<nWorkers;i++)
		workers.push_back(new Worker(ev_reader));
	//workers[0]->Run();
	//return 0;
	for(auto worker_ptr: workers)
		threads.push_back(new std::thread(&Worker::Run, worker_ptr));

	for(auto thread : threads)
		thread->join();

}

