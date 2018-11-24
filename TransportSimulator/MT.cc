#include "EventReader.hh"
#include "Worker.hh"


int main()
{
	EventReader* ev_reader=new EventReader("test.root");
	Worker worker(ev_reader);
	worker();

}

