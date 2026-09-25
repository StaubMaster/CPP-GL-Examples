#ifndef  BUFFER_UNIFORM_HPP
# define BUFFER_UNIFORM_HPP

# include "Graphics/Buffer/Base.hpp"

# include "OpenGLEnums.hpp"

namespace Buffer
{
class Uniform : public Base
{
	public:
	~Uniform();
	Uniform() = delete;
	Uniform(GL::BufferDataUsage usage);

	Uniform(const Uniform & other) = default;
	Uniform & operator=(const Uniform & other) = default;



	public:
	void	BindBase(GL::BlockBinding binding);



	public:
	void	LogInfo(bool self = true) const override;
};
};

#endif