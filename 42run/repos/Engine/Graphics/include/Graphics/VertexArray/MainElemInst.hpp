#ifndef  VERTEX_ARRAY_MAIN_ELEM_INST_HPP
# define VERTEX_ARRAY_MAIN_ELEM_INST_HPP

# include "Graphics/VertexArray/Base.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Element.hpp"

namespace VertexArray
{
class MainElemInst : public Base
{
	public:
	GL::DrawMode	Mode;

	public:
	::Buffer::Array		MainBuffer;
	::Buffer::Element	ElemBuffer;
	::Buffer::Array		InstBuffer;

	public:
	~MainElemInst();
	MainElemInst();

	MainElemInst(const MainElemInst & other) = default;
	MainElemInst & operator=(const MainElemInst & other) = default;

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