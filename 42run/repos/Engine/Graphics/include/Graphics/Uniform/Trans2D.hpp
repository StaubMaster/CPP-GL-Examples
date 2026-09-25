#ifndef  UNIFORM_TRANS_2D_HPP
# define UNIFORM_TRANS_2D_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/VectorF2.hpp"
# include "Graphics/Uniform/TypeDefs/Matrix2x2.hpp"

struct Trans2D;

namespace Uniform
{
class Trans2D : public Uniform::TypeBase<::Trans2D>
{
	private:
	Uniform::VectorF2	Pos;
	Uniform::Matrix2x2	Rot;

	public:
	Trans2D(std::string name, bool is_dynamic = false);
	Trans2D(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Put(const ::Trans2D & obj) override;
};
};

#endif