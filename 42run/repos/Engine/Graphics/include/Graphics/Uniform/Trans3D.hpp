#ifndef  UNIFORM_TRANS_3D_HPP
# define UNIFORM_TRANS_3D_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF3.hpp"
//# include "Graphics/Uniform/Angle3D.hpp"
# include "Graphics/Uniform/TypeDefs/Matrix3x3.hpp"

struct Trans3D;

namespace Uniform
{
class Trans3D : public Uniform::TypeBase<::Trans3D>
{
	private:
	Uniform::VectorF3	Pos;
	Uniform::Matrix3x3	Rot;

	public:
	Trans3D(std::string name, bool is_dynamic = false);
	Trans3D(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Put(const ::Trans3D & obj) override;
};
};

#endif