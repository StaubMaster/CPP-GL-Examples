#ifndef  BUFFER_ELEMENT_HPP
# define BUFFER_ELEMENT_HPP

# include "Graphics/Buffer/Base.hpp"

# include "Miscellaneous/Container/Void.hpp"

# include "OpenGLEnums.hpp"

namespace Buffer
{
class Element : public Base
{
	public:
	GL::BufferDataUsage		Usage;
	GL::DrawIndexType		IndexType;
	unsigned int			ElemPerType;
	unsigned int			DrawCount;

	public:
	void LogInfo(bool self = true) const override;

	public:
	virtual ~Element();
	Element(::BufferArray::Base & buffer_array, GL::BufferDataUsage usage, GL::DrawIndexType index_type, unsigned int elem_per_type);

	Element(const Element & other);
	Element & operator=(const Element & other);

	public:
	void Init() override;

	public:
	void Change(const Container::Void & data);
};
};

#endif