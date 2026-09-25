#ifndef  UNIFORM_UINT_N_BASE_HPP
# define UNIFORM_UINT_N_BASE_HPP

# include "Graphics/Uniform/General/Base.hpp"

# include "OpenGLTypes.hpp"

namespace Uniform
{
class UIntNBase : public Uniform::Base
{
	public:
	GL::UniformLocation		Index;

	protected:
	virtual ~UIntNBase();

	protected:
	UIntNBase(std::string name, bool is_dynamic);
	UIntNBase(Uniform::Layout & layout, std::string name, bool is_dynamic);

	public:
	void	Find(Shader::Base & shader) override;

	public:
	void			PutVoid(const void * val) override;
	virtual void	PutData(const unsigned int * val) = 0;

	public:
	void	LogInfo(bool self = true) const override;
};
};

#endif