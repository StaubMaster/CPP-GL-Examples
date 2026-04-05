#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"
//#include "Miscellaneous/Container/Fixed.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"



UI::Text::TextShader::~TextShader() { }

UI::Text::TextShader::TextShader()
	: Shader::Base()
	, DisplaySize(*this, "DisplaySize")
{ }
