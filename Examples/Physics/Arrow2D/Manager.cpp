#include "Arrow2D/Manager.hpp"

#include "Arrow2D/Main/Data.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "DirectoryInfo.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/Container/Array.hpp"

#include "Graphics/Shader/Code.hpp"

#include "ValueType/AxisBox2D.hpp"



Arrow2D::Manager::~Manager() { }
Arrow2D::Manager::Manager()
	: Buffer(GL::DrawMode::Triangles)
{ }



void Arrow2D::Manager::InitExternal(const DirectoryInfo & shaderDir)
{
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(shaderDir.File("Arrow/2D.vert")),
			::Shader::Code(shaderDir.File("Arrow/2D.frag")),
		});
		Shader.Change(code);
	}

	{
		Buffer.Main.Pos.Change(0);
		Buffer.Main.Tex.Change(1);
		Buffer.Inst.Pos0.Change(2);
		Buffer.Inst.Pos1.Change(3);
		Buffer.Inst.Size.Change(4);
		Buffer.Inst.Col.Change(5);
	}
}
void Arrow2D::Manager::InitInternal(const DirectoryInfo & imageDir)
{
	{
		AxisBox2D	Pos;
		AxisBox2D	Tex;

		Container::Binary<Arrow2D::Main::Data> data;

		Pos = AxisBox2D(Point2D(-3, -1), Point2D(-1, +1));
		Tex = AxisBox2D(Point2D(0 / 96.0f, 0), Point2D(32 / 96.0f, 1));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

		Pos = AxisBox2D(Point2D(-1, -1), Point2D(+1, +1));
		Tex = AxisBox2D(Point2D(32 / 96.0f, 0), Point2D(64 / 96.0f, 1));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

		Pos = AxisBox2D(Point2D(+1, -1), Point2D(+3, +1));
		Tex = AxisBox2D(Point2D(64 / 96.0f, 0), Point2D(96 / 96.0f, 1));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

		Buffer.Main.Change(data);
		/*std::cout << "Main: " << data.Count() << '\n';
		for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Pos << ' ' << data[i].Tex << '\n';
		}*/
	}

	{
		Texture.Bind();
		Container::Binary<FileInfo> files;
		files.Insert(imageDir.File("Arrow/96x32.png"));
		Texture.Assign(96, 32, files);
	}
}



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
