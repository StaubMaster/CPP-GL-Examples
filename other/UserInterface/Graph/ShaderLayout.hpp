#ifndef  UI_GRAPH_SHADER_HPP
# define UI_GRAPH_SHADER_HPP

#include "Graphics/Uniform/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"

namespace UI
{

namespace Graph
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