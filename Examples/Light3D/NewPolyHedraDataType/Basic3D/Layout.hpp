#ifndef  NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_LAYOUT_HPP
# define NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_LAYOUT_HPP

# include "Instance/Basic3D/Layout.hpp"

# include "PolyHedra/Graphics/Wire/ShaderLayout.hpp"
# include "../../LightShaderLayout.hpp"

namespace Basic3D
{
typedef LightShaderLayout ShaderFullLayout;
typedef PolyHedraWire::ShaderLayout ShaderWireLayout;
typedef Instance::Basic3D::Layout BufferLayout;
};

#endif