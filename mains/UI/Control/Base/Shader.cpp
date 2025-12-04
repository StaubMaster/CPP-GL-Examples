#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"



Control::BaseShader::BaseShader(const DirectoryContext & dir)
	: Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(dir.File("UI/Control.vert")),
		Shader::Code::FromFile(dir.File("UI/Control.frag"))
	}, 2),
	ViewPortSizeRatio("ViewPortSizeRatio", *this)
{ }
Control::BaseShader::~BaseShader()
{ }
