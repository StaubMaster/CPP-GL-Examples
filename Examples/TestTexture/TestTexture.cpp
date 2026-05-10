#include "TestTexture.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"

#include "Debug.hpp"
#include <sstream>

#include "ValueType/_Include.hpp"

#include "FileInfo.hpp"
#include "Image.hpp"



ContextTestTexture::~ContextTestTexture() { }
ContextTestTexture::ContextTestTexture(Window & window)
	: window(window)
	, MediaDirectory("../../media/")
	, Shader()
	, Buffer()
	, BufferArray(Buffer, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainData))
	, Attribute_Main_Pos(BufferArray)
	, Attribute_Main_Tex(BufferArray)
{
	Buffer.Buffers.Allocate(1);
	Buffer.Buffers.Insert(&BufferArray);
}



void ContextTestTexture::Init()
{
	{
		Container::Array<Shader::Code> code({
			::Shader::Code(FileInfo("Shader.vert")),
			::Shader::Code(FileInfo("Shader.frag")),
		});
		Shader.Change(code);
	}
	Shader.Create();

	{
		Attribute_Main_Pos.Change(0);
		Attribute_Main_Tex.Change(1);
	}
	Buffer.Create();
	BufferArray.Init();
	{
		Container::Array<MainData> data(6);

		data[0].Pos = VectorF2(-1, -1); data[0].Tex = VectorF2(0, 0);
		data[1].Pos = VectorF2(+1, -1); data[1].Tex = VectorF2(1, 0);
		data[2].Pos = VectorF2(-1, +1); data[2].Tex = VectorF2(0, 1);

		data[3].Pos = VectorF2(-1, +1); data[3].Tex = VectorF2(0, 1);
		data[4].Pos = VectorF2(+1, -1); data[4].Tex = VectorF2(1, 0);
		data[5].Pos = VectorF2(+1, +1); data[5].Tex = VectorF2(1, 1);

		BufferArray.Data(data);
	}

	Texture.Create();
	{
		Container::Binary<FileInfo> files;
		files.Insert(MediaDirectory.File("Images/Voxel/Grass.png"));
		files.Insert(MediaDirectory.File("Images/Voxel/Sand.png"));
		files.Insert(FileInfo("Image.png"));

		Texture.Bind();
		Texture.Assign(VectorU2(32, 32), files);
	}
}
void ContextTestTexture::Free()
{
	Shader.Delete();
	Buffer.Delete();
	Texture.Delete();
}



void ContextTestTexture::Resize(DisplaySize display_size)
{
	(void)display_size;
}

void ContextTestTexture::Frame(FrameTime frame_time)
{
	(void)frame_time;
	if (window.KeyBoardManager[Keys::Escape].State == State::Press)
	{
		window.ExitLoop();
		return;
	}

	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	Shader.Bind();
	Buffer.Bind();
	Texture.Bind();
	GL::DrawArrays(GL::DrawMode::Triangles, 0, 6);
}



void ContextTestTexture::MouseScroll(ScrollArgs args) { (void)args; }
void ContextTestTexture::MouseClick(ClickArgs args) { (void)args; }
void ContextTestTexture::MouseDrag(DragArgs args) { (void)args; }
void ContextTestTexture::KeyBoardKey(KeyArgs args) { (void)args; }

void ContextTestTexture::Run()
{
	window.CallBack_Init.Assign<ContextTestTexture>(this, &ContextTestTexture::Init);
	window.CallBack_Free.Assign<ContextTestTexture>(this, &ContextTestTexture::Free);
	window.CallBack_Resize.Assign<ContextTestTexture>(this, &ContextTestTexture::Resize);
	window.CallBack_Frame.Assign<ContextTestTexture>(this, &ContextTestTexture::Frame);

	window.MouseManager.Callback_ScrollEvent.Assign<ContextTestTexture>(this, &ContextTestTexture::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Assign<ContextTestTexture>(this, &ContextTestTexture::MouseClick);
	window.MouseManager.Callback_DragEvent.Assign<ContextTestTexture>(this, &ContextTestTexture::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign<ContextTestTexture>(this, &ContextTestTexture::KeyBoardKey);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.RunLoop();
	Debug::Log << ">>>> Run Window" << Debug::Done;
}
