#ifndef  NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_HPP
# define NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_HPP

# include "ValueType/Trans/3D.hpp"
# include "Instance/Basic3D/Data.hpp"
# include "Instance/Basic3D/Layout.hpp"

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"

namespace TestBasic3D
{
typedef Instance::Basic3D::Data InstanceData;
struct ObjectData
{
	Trans3D		Trans;
	InstanceData	ToData() const;
};
struct ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Matrix4x4			View;
	Uniform::Depth				Depth;
	Uniform::Angle				FOV;
	public:
	~ShaderLayout();
	ShaderLayout();
};
typedef Instance::Basic3D::Layout BufferLayout;
};

#endif