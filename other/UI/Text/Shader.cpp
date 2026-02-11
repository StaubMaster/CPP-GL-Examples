#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"
//#include "Miscellaneous/Container/Fixed.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"



UI::Text::TextShader::TextShader()
	: Shader::Base(),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{ }
/*UI::Text::TextShader::TextShader(const DirectoryInfo & dir)
	: Shader::Base(),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{
	Container::Fixed<::Shader::Code> code(2);
	code.Insert(Shader::Code(dir.File("UI/Text.vert")));
	code.Insert(Shader::Code(dir.File("UI/Text.frag")));
	Change(code);
}*/
UI::Text::TextShader::~TextShader()
{ }
