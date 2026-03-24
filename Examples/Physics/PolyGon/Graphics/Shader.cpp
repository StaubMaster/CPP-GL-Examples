#include "PolyGon/Graphics/Shader.hpp"



PolyGon::Shader::~Shader()
{ }
PolyGon::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }
