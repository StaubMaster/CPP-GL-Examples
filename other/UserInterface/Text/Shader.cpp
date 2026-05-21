#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"
//#include "Miscellaneous/Container/Fixed.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"



UI::Text::Shader::~Shader() { }

UI::Text::Shader::Shader()
	: Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, PalletArrayMin(*this, "PalletArrayMin")
	, PalletArrayMax(*this, "PalletArrayMax")
	, TextBoundArrayMin(*this, "TextBoundArrayMin")
	, TextBoundArrayMax(*this, "TextBoundArrayMax")
	, TextColorArray(*this, "TextColorArray")
{ }
