#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"



UI::Control::BaseShader::BaseShader(const DirectoryContext & dir)
	: Shader::Base(
		Container::Base<Shader::Code>(
			(Shader::Code[]) {
				Shader::Code(dir.File("UI/Control.vert")),
				Shader::Code(dir.File("UI/Control.frag"))
			}, 2
		)
	),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{ }
UI::Control::BaseShader::~BaseShader()
{ }
