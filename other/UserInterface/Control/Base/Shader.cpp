#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"



UI::Control::Shader::~Shader()
{ }
UI::Control::Shader::Shader()
	: Shader::Base()
{ }



UI::Control::Layout::~Layout()
{ }
UI::Control::Layout::Layout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }
