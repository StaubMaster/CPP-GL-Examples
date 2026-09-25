#ifndef  BUFFER_ELEMENT_HPP
# define BUFFER_ELEMENT_HPP

# include "Graphics/Buffer/Base.hpp"

namespace Buffer
{
class Element : public Base
{
	public:
	GL::DrawIndexType	IndexType;

	public:
	unsigned int	Count = 0;



	public:
	~Element();
	Element() = delete;
	Element(GL::BufferDataUsage usage, GL::DrawIndexType index_type);

	Element(const Element & other) = default;
	Element & operator=(const Element & other) = default;



	public:
	void	LogInfo(bool self = true) const override;
};
};

#endif