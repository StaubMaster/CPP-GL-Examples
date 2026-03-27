#include "PolyGon/Graphics/Full/Shader.hpp"



PolyGonFull::Shader::~Shader()
{ }
PolyGonFull::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }
