#ifndef  UI_CONTROL_SHADER_HPP
# define UI_CONTROL_SHADER_HPP

#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"



namespace UI
{

namespace Control
{

class ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize	DisplaySize;
	public:
	~ShaderLayout();
	ShaderLayout();
};

};

};

#endif