#include "NewPolyHedra/DataType/Basic3D/Init.hpp"
#include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"



void NewPolyHedra::Basic3D::Create(ObjectManager & manager)
{
	{
		manager.ShaderFull.Change({
			MediaDirectory.File("Shaders/PolyHedra/Default.vert"),
			MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag"),
		});
		ShaderLayoutView3D * layout = new ShaderLayoutView3D();
		manager.ShaderFull.UniformLayout = layout;
		layout -> Shader = &manager.ShaderFull;
	}
	{
		manager.ShaderWire.Change({
			MediaDirectory.File("Shaders/Basic3D/Wire.vert"),
			MediaDirectory.File("Shaders/Basic3D/Wire.frag"),
		});
		ShaderLayoutView3D * layout = new ShaderLayoutView3D();
		manager.ShaderWire.UniformLayout = layout;
		layout -> Shader = &manager.ShaderWire;
	}
	{
		NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
		layout -> Trans.Change(3);
		layout -> Normal.Change(7);
		manager.BufferFullLayout = layout;
	}
	{
		NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
		layout -> Trans.Change(3);
		layout -> Normal.Change(-1);
		manager.BufferWireLayout = layout;
	}
	PolyHedraManager.ObjectManagers.Insert(&ObjectManagerBasic);
}



void NewPolyHedra::Basic3D::Delete(ObjectManager & manager)
{
	delete manager.ShaderFull.UniformLayout;
	delete manager.ShaderWire.UniformLayout;
	delete manager.BufferFullLayout;
	delete manager.BufferWireLayout;
}
