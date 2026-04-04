#include "PolyGon/Graphics/Wire/Shader.hpp"



PolyGonWire::Shader::~Shader()
{ }
PolyGonWire::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this,"DisplaySize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }
