#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"



UI::Text::TextShader::TextShader(const DirectoryContext & dir)
	: Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(dir.File("UI/Text.vert")),
		Shader::Code::FromFile(dir.File("UI/Text.frag"))
	}, 2),
	WindowSize("WindowSize", *this)
{ }
UI::Text::TextShader::~TextShader()
{ }
