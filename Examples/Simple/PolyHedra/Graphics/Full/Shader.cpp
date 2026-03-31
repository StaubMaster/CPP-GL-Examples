#include "PolyHedra/Graphics/Full/Shader.hpp"



PolyHedraFull::Shader::~Shader()
{ }
PolyHedraFull::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }
