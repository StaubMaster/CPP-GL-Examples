#ifndef  BUFFER_ARRAY_MAIN_ELEM_INST_HPP
# define BUFFER_ARRAY_MAIN_ELEM_INST_HPP

# include "Graphics/Buffer/ArrayBase.hpp"
# include "Graphics/Buffer/Attribute.hpp"
# include "Graphics/Buffer/Element.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Base.hpp"
# include "OpenGL.hpp"

namespace BufferArray
{
template<typename MainBufferType, typename ElemBufferType, typename InstBufferType>
class MainElemInst : public BufferArray::Base
{
	public:
	GL::DrawMode	Mode;
	MainBufferType	Main;
	ElemBufferType	Elem;
	InstBufferType	Inst;

	public:
	Container::Binary<Texture::Base *>	Textures;

	public:
	virtual ~MainElemInst() { }
	MainElemInst(GL::DrawMode mode, unsigned int elem_per_type)
		: BufferArray::Base()
		, Mode(mode)
		, Main(*this)
		, Elem(*this, elem_per_type)
		, Inst(*this)
	{
		Buffers.Allocate(3);
		Buffers.Insert(&Main);
		Buffers.Insert(&Elem);
		Buffers.Insert(&Inst);
	}

	public:
	void Draw()
	{
		for (unsigned int i = 0; i < Textures.Count(); i++)
		{
			Textures[i] -> Bind();
		}
		Bind();
		GL::DrawElementsInstanced(Mode, Elem.DrawCount, Elem.IndexType, Inst.DrawCount);
	}
};
};

#endif