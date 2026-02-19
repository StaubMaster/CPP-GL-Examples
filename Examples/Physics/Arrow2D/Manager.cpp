#include "Arrow2D/Manager.hpp"

#include "Arrow2D/Main/Data.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "Miscellaneous/Container/Binary.hpp"

#include "DirectoryInfo.hpp"



Arrow2D::Manager::~Manager()
{ }
Arrow2D::Manager::Manager()
{ }



void Arrow2D::Manager::GraphicsCreate()
{
	Shader.Create();
	Buffer.Create();
	Texture.Create();
}
void Arrow2D::Manager::GraphicsDelete()
{
	Shader.Delete();
	Buffer.Delete();
	Texture.Delete();
}



void Arrow2D::Manager::Draw()
{
	Shader.Bind();
	Texture.Bind();
	Buffer.Draw();
}
