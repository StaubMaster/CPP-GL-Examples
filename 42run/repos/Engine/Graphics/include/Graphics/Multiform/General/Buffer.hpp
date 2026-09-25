#ifndef  MULTIFORM_BUFFER_HPP
# define MULTIFORM_BUFFER_HPP

# include "Graphics/Multiform/General/Base.hpp"

# include "OpenGLTypes.hpp"

namespace Multiform
{
class Buffer : public Base
{
	public:
	GL::BlockBinding	Binding = 0;

	public:
	~Buffer();
	Buffer(std::string name);

	public:
	void	PutData(Uniform::Base & uniform) override;
	void	PutData(Uniform::Base & uniform, Shader::Base & shader) override;

	public:
	void	ChangeData(GL::BlockBinding binding);
};
};

#endif