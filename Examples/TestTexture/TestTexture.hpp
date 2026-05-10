#ifndef  TEST_TEXTURE_HPP
# define TEST_TEXTURE_HPP

# include "DirectoryInfo.hpp"

# include "Window.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Buffer/VertexArray.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Attribute/_Include.hpp"
# include "Graphics/Texture/Array2D.hpp"

struct MainData
{
	VectorF2	Pos;
	VectorF2	Tex;
};

struct ContextTestTexture
{
Window &		window;
DirectoryInfo	MediaDirectory;

::Shader::Base		Shader;
::VertexArray		Buffer;

::Buffer::Array			BufferArray;
::Attribute::VectorF2	Attribute_Main_Pos;
::Attribute::VectorF2	Attribute_Main_Tex;

::Texture::Array2D		Texture;

~ContextTestTexture();
ContextTestTexture(Window & window);

void Make();

void Init(); // override;
void Free(); // override;

void Resize(DisplaySize display_size); // override;
void Frame(FrameTime frame_time); // override;

void MouseScroll(ScrollArgs args); // override;
void MouseClick(ClickArgs args); // override;
void MouseDrag(DragArgs args); // override;
void KeyBoardKey(KeyArgs args); // override;

void Run();
};

#endif