#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"



UI::Text::TextShader::TextShader(const DirectoryContext & dir)
	: Shader::Base(
		Container::Base<Shader::Code>(
			(Shader::Code [])
			{
				Shader::Code(dir.File("UI/Text.vert")),
				Shader::Code(dir.File("UI/Text.frag"))
			}, 2
		)
	),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{ }
UI::Text::TextShader::~TextShader()
{ }
