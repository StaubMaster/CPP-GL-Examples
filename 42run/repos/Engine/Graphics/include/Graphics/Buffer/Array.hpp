#ifndef  BUFFER_ARRAY_HPP
# define BUFFER_ARRAY_HPP

# include "Graphics/Buffer/Base.hpp"

namespace Attribute { class Layout; };

namespace Buffer
{
class Array : public Base
{
	public:
	unsigned int	Count = 0;

	private:
	Attribute::Layout *		Layout = nullptr;



	public:
	~Array();
	Array() = delete;
	Array(GL::BufferDataUsage usage);

	Array(const Array & other) = default;
	Array & operator=(const Array & other) = default;



	public:
	void	Init();



	public:
	void	AssignLayout(Attribute::Layout & layout);
	void	AssignLayout(Attribute::Layout * layout);



	public:
	void	LogInfo(bool self = true) const override;
};
};

#endif