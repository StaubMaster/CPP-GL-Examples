#include "PolyGon/Graphics/Full/Shader.hpp"



PolyGon::Full::Shader::~Shader()
{ }
PolyGon::Full::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }
