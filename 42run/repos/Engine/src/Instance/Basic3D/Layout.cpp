#include "Instance/Basic3D/Layout.hpp"
#include "Instance/Basic3D/Data.hpp"



Instance::Basic3D::Layout::~Layout() { }
Instance::Basic3D::Layout::Layout()
	: ::Attribute::Layout(1, sizeof(Basic3D::Data))
	, Trans(*this)
	, Normal(*this)
{ }
Instance::Basic3D::Layout::Layout(const Layout & other)
	: ::Attribute::Layout(other)
	, Trans(*this, other.Trans)
	, Normal(*this, other.Normal)
{ }
