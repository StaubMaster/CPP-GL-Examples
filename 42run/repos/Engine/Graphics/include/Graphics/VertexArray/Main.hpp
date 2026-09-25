#ifndef  VERTEX_ARRAY_MAIN_HPP
# define VERTEX_ARRAY_MAIN_HPP

# include "Graphics/VertexArray/Base.hpp"
# include "Graphics/Buffer/Array.hpp"

namespace VertexArray
{
class Main : public Base
{
	public:
	GL::DrawMode	Mode;

	public:
	::Buffer::Array		MainBuffer;

	public:
	~Main();
	Main();

	Main(const Main & other) = default;
	Main & operator=(const Main & other) = default;

	public:
	void	Create() override;
	void	Delete() override;

	public:
	void	Init();

	public:
	void	Draw();
};
};

#endif