#ifndef  UNIFORM_FLOAT_N_BASE_HPP
# define UNIFORM_FLOAT_N_BASE_HPP

# include "Graphics/Uniform/General/Base.hpp"

# include "OpenGLTypes.hpp"

namespace Uniform
{
class FloatNBase : public Uniform::Base
{
	public:
	GL::UniformLocation		Index;

	protected:
	virtual ~FloatNBase();

	protected:
	FloatNBase(std::string name, bool is_dynamic);
	FloatNBase(Uniform::Layout & layout, std::string name, bool is_dynamic);

	public:
	void	Find(Shader::Base & shader) override;

	public:
	void			PutVoid(const void * val) override;
	virtual void	PutData(const float * val) = 0;

	public:
	void	LogInfo(bool self = true) const override;};
};

#endif