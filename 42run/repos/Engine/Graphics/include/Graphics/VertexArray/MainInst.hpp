#ifndef  VERTEX_ARRAY_MAIN_INST_HPP
# define VERTEX_ARRAY_MAIN_INST_HPP

# include "Graphics/VertexArray/Base.hpp"
# include "Graphics/Buffer/Array.hpp"

namespace VertexArray
{
class MainInst : public Base
{
	public:
	GL::DrawMode	Mode;

	public:
	::Buffer::Array		MainBuffer;
	::Buffer::Array		InstBuffer;

	public:
	~MainInst();
	MainInst();

	MainInst(const MainInst & other) = default;
	MainInst & operator=(const MainInst & other) = default;

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