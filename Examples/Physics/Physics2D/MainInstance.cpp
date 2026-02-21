#include "Physics2D/MainInstance.hpp"



Physics2D::MainInstance::~MainInstance()
{ }
Physics2D::MainInstance::MainInstance()
	: PolyGon(new ::PolyGon())
	, BufferArray()
	, Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
{
	BufferArray.Main.Pos.Change(0);
	BufferArray.Main.Col.Change(1);
	BufferArray.Inst.Now.Pos.Change(2);
	BufferArray.Inst.Now.Rot.Change(3, 4);
	BufferArray.Create();
}
Physics2D::MainInstance::MainInstance(const MainInstance & other)
	: PolyGon(other.PolyGon)
	, BufferArray(other.BufferArray)
	, Instances(other.Instances)
{ }
Physics2D::MainInstance & Physics2D::MainInstance::operator=(const MainInstance & other)
{
	PolyGon = other.PolyGon;
	BufferArray = other.BufferArray;
	Instances = other.Instances;
	return *this;
}



void Physics2D::MainInstance::Dispose()
{
	BufferArray.Delete();
	delete PolyGon;
	delete Instances;
}



void Physics2D::MainInstance::UpdateMain()
{
	Container::Pointer<Physics2D::Main::Data> data = PolyGon -> ToPhysics2D();
	BufferArray.Bind();
	BufferArray.Main.Change(data);
	data.Delete();
}
void Physics2D::MainInstance::UpdateInst()
{
	BufferArray.Bind();
	BufferArray.Inst.Change(*Instances);
}
void Physics2D::MainInstance::Draw()
{
	BufferArray.Draw();
}
