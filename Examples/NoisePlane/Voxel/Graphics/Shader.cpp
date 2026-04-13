#include "Shader.hpp"



VoxelGraphics::Shader::~Shader() { }
VoxelGraphics::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }
