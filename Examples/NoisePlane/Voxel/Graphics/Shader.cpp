#include "Shader.hpp"



VoxelGraphics::Shader::~Shader() { }
VoxelGraphics::Shader::Shader()
	: ::Shader::Base()
{ }



VoxelGraphics::Layout::~Layout() { }
VoxelGraphics::Layout::Layout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }
