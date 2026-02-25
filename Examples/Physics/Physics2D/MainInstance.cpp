#include "Physics2D/MainInstance.hpp"



Physics2D::MainInstance::~MainInstance()
{ }
Physics2D::MainInstance::MainInstance()
	: PolyGon(new ::PolyGon())
	, Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, PolyGon_Buffer(GL::DrawMode::Triangles)
{
	PolyGon_Buffer.Main.Pos.Change(0);
	PolyGon_Buffer.Main.Col.Change(1);
	PolyGon_Buffer.Inst.Now.Pos.Change(2);
	PolyGon_Buffer.Inst.Now.Rot.Change(3, 4);
	PolyGon_Buffer.Create();
}
Physics2D::MainInstance::MainInstance(const MainInstance & other)
	: PolyGon(other.PolyGon)
	, Instances(other.Instances)
	, PolyGon_Buffer(other.PolyGon_Buffer)
{ }
Physics2D::MainInstance & Physics2D::MainInstance::operator=(const MainInstance & other)
{
	PolyGon = other.PolyGon;
	Instances = other.Instances;
	PolyGon_Buffer = other.PolyGon_Buffer;
	return *this;
}



void Physics2D::MainInstance::Dispose()
{
	PolyGon_Buffer.Delete();
	delete PolyGon;
	delete Instances;
}



void Physics2D::MainInstance::UpdateMain()
{
	Container::Pointer<PolyGonGraphics::Main::Data> data = PolyGon -> ToMainData();
	PolyGon_Buffer.Bind();
	PolyGon_Buffer.Main.Change(data);
	data.Delete();
}
void Physics2D::MainInstance::UpdateInst()
{
	PolyGon_Buffer.Bind();
	PolyGon_Buffer.Inst.Change(*Instances);
}
void Physics2D::MainInstance::Draw()
{
	PolyGon_Buffer.Draw();
}
