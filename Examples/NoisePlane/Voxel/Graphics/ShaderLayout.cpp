#include "ShaderLayout.hpp"



VoxelGraphics::ShaderLayout::~ShaderLayout() { }
VoxelGraphics::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
	, LightAmbient(*this, "Ambient")
	, LightSolar(*this, "Solar")
{ }
