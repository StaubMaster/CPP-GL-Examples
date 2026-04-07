#ifndef  UI_TEXT_SHADER_HPP
# define UI_TEXT_SHADER_HPP

#include "Graphics/Shader/Base.hpp"

#include "Graphics/Uniform/_Include.hpp"



class DirectoryInfo;



namespace UI
{

namespace Text
{

class Shader : public ::Shader::Base
{
	public:
	Uniform::DisplaySize	DisplaySize;
	public:
	~Shader();
	Shader();
};

};

};

#endif