#include "MultiformLayouts.hpp"



MultiformLayoutDisplay::~MultiformLayoutDisplay()
{ }
MultiformLayoutDisplay::MultiformLayoutDisplay()
	: ::MultiformLayout()
	, DisplaySize("DisplaySize")
{ }



MultiformLayoutView3D::~MultiformLayoutView3D()
{ }
MultiformLayoutView3D::MultiformLayoutView3D()
	: MultiformLayoutDisplay()
	, View("View")
	, Depth("Depth")
	, FOV("FOV")
{ }
