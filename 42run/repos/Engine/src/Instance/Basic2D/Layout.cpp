#include "Instance/Basic2D/Layout.hpp"
#include "Instance/Basic2D/Data.hpp"



Instance::Basic2D::Layout::~Layout() { }
Instance::Basic2D::Layout::Layout()
	: ::Attribute::Layout(1, sizeof(Basic2D::Data))
	, Trans(*this)
{ }
Instance::Basic2D::Layout::Layout(const Layout & other)
	: ::Attribute::Layout(other)
	, Trans(*this, other.Trans)
{ }
