#ifndef  UI_TEXT_SHADER_HPP
# define UI_TEXT_SHADER_HPP

#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"



class DirectoryInfo;



namespace UI
{

namespace Text
{

/*	cannot change name from TextShader to Shader because compiler gets confused
	thinks that Shader namespace is meant
	change Shader::Base to Graphics::Shader::Base ?
	put all Graphics stuff into Graphics namespace
*/
class TextShader : public Shader::Base
{
	public:
	Uniform::WindowBufferSize2D WindowSize;

	public:
	TextShader();
	//TextShader(const DirectoryInfo & dir);
	~TextShader();
};

};

};

#endif