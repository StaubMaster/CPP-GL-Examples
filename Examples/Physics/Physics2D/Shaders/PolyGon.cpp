#include "Physics2D/Shaders/PolyGon.hpp"



Physics2D::Shaders::PolyGon::~PolyGon()
{ }
Physics2D::Shaders::PolyGon::PolyGon()
	: ::Shader::Base()
	, WindowSize(*this, "WindowSize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }
