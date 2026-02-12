#include "Shader.hpp"
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Fixed.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"



UI::Control::Shader::Shader()
	: Shader::Base(),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{ }
/*UI::Control::Shader::Shader(const DirectoryInfo & dir)
	: Shader::Base(
		//Container::Base<::Shader::Code>(
		//	(Shader::Code[]) {
		//		Shader::Code(dir.File("UI/Control.vert")),
		//		Shader::Code(dir.File("UI/Control.frag"))
		//	}, 2
		//)
	),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{
	Container::Fixed<::Shader::Code> code(2);
	code.Insert(::Shader::Code(dir.File("UI/Control.vert")));
	code.Insert(::Shader::Code(dir.File("UI/Control.frag")));
	Change(code);
}*/
UI::Control::Shader::~Shader()
{ }
