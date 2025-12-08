#ifndef  UI_CONTROL_SHADER_HPP
# define UI_CONTROL_SHADER_HPP

#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"



class DirectoryContext;



namespace UI
{

namespace Control
{

class BaseShader : public Shader::Base
{
	public:
		Uniform::SizeRatio2D ViewPortSizeRatio;

	public:
		BaseShader(const DirectoryContext & dir);
		~BaseShader();
};

};

};

#endif