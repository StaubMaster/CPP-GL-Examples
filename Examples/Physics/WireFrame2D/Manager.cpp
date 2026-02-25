#include "WireFrame2D/Manager.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/Container/Array.hpp"

#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"



Wire2D::Manager::~Manager() { }
Wire2D::Manager::Manager()
	: Shader()
	, Buffer(GL::DrawMode::Lines)
{ }



void Wire2D::Manager::InitExternal(const DirectoryInfo & shaderDir)
{
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(shaderDir.File("Wire/2D.vert")),
			::Shader::Code(shaderDir.File("Wire/2D.frag")),
		});
		Shader.Change(code);
	}

	{
		Buffer.Main.Pos.Change(0);
		Buffer.Main.Col.Change(1);
		Buffer.Inst.Now.Pos.Change(2);
		Buffer.Inst.Now.Rot.Change(3, 4);
	}
}
//void Wire2D::Manager::InitInternal() { }



void Wire2D::Manager::GraphicsCreate()
{
	Shader.Create();
	Buffer.Create();
}
void Wire2D::Manager::GraphicsDelete()
{
	Shader.Delete();
	Buffer.Delete();
}



void Wire2D::Manager::Draw()
{
	Shader.Bind();
	Buffer.Draw();
}
