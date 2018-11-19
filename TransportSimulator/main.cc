#include "EventReader.hh"
#include "Matrix3D.hh"

int main()
{
	Matrix3D m(2,2,2,1);
	//m(2,2,2)=12;
	std::cout<<m(1,1,1)<<std::endl;
	m.Normalize();
	std::cout<<m(1,1,1)<<std::endl;
	m.GetSizeX();
	m.GetSizeY();
	m.GetSizeZ();
	EventReader* ev_reader=new EventReader("test.root");
	SimEvent* ev=new SimEvent();
	int a=0;
	while(!ev_reader->EndOfFile())
	{	
		ev_reader->ReadEvent(ev);
		m=Matrix3D::BuildMatrixFromTH3(ev->GetPrimaryHisto());
	}
}