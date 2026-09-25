#ifndef  UNIFORM_LINTER_HPP
# define UNIFORM_LINTER_HPP

# include "Graphics/Uniform/General/TypeBase.hpp"
# include "Graphics/Uniform/TypeDefs/Float.hpp"

struct LInter;

namespace Uniform
{
class LInter : public Uniform::TypeBase<::LInter>
{
	private:
	Uniform::Float	T0;
	Uniform::Float	T1;

	public:
	LInter(std::string name, bool is_dynamic = false);
	LInter(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Put(const ::LInter & obj) override;
};
};

#endif