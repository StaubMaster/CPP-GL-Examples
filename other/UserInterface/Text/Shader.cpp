#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"
//#include "Miscellaneous/Container/Fixed.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"



UI::Text::Shader::~Shader() { }

UI::Text::Shader::Shader()
	: Shader::Base()
	, DisplaySize(*this, "DisplaySize")
{ }
