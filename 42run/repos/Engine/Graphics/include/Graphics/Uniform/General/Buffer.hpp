#ifndef  UNIFORM_BUFFER_HPP
# define UNIFORM_BUFFER_HPP

# include "Graphics/Uniform/General/Base.hpp"

struct DisplaySize;

namespace Uniform
{
class Buffer : public Base
{
	public:
	GL::BlockIndex	Index;

	public:
	Buffer(std::string name, bool is_dynamic = false);
	Buffer(Uniform::Layout & layout, std::string name, bool is_dynamic = false);

	public:
	void	Find(Shader::Base & shader) override;

	protected:
	void	PutVoid(const void * val) override;

	public:
	void	LogInfo(bool self = true) const override;
};
};

#endif