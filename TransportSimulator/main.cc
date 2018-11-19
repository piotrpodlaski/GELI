#include "EventReader.hh"

int main()
{
	EventReader* ev_reader=new EventReader("test.root");
	SimEvent* ev=new SimEvent();
	int a=0;
	while(!ev_reader->EndOfFile())
	{
		ev_reader->ReadEvent(ev);
	}
}