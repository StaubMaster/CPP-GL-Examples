#ifndef  UI_CONTROL_SHADER_HPP
# define UI_CONTROL_SHADER_HPP

#include "Graphics/Shader/Base.hpp"

#include "Graphics/Uniform/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"



class DirectoryInfo;



namespace UI
{

namespace Control
{

class Shader : public ::Shader::Base
{
	public:
	~Shader();
	Shader();
};

class Layout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize	DisplaySize;

	public:
	~Layout();
	Layout();
};

};

};

#endif