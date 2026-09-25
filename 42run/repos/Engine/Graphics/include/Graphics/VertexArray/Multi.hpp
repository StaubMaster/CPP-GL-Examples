#ifndef  VERTEX_ARRAY_MULTI_HPP
# define VERTEX_ARRAY_MULTI_HPP

# include "Graphics/VertexArray/Base.hpp"
# include "Graphics/Buffer/Array.hpp"

namespace VertexArray
{
class Multi : public Base
{
	public:
	struct Entry
	{
		public:
		VertexArray::Multi &	Buffer;

		public:
		unsigned int	Offset = 0;
		unsigned int	Length = 0;

		public:
		bool			IsEmpty() const;
		void			MakeEmpty();

		unsigned int	Limit() const;
		bool			Check(const Entry & other) const;

		public:
		~Entry();
		Entry() = delete;
		Entry(const Entry & other) = delete;
		Entry & operator=(const Entry & other) = delete;

		public:
		Entry(VertexArray::Multi & buffer);

		public:
		void	Put(const Container::Void & data);
	};

	public:
	GL::DrawMode	Mode;

	public:
	unsigned int		SizeOf = 0;

	public:
	::Buffer::Array		Buffer;

	public:
	~Multi();
	Multi();

	Multi(const Multi & other) = default;
	Multi & operator=(const Multi & other) = default;

	private:
	Container::Binary<VertexArray::Multi::Entry*>	Entrys;
	Container::Binary<int>		Offsets;
	Container::Binary<int>		Lengths;

	private:
	bool	CheckEntry(VertexArray::Multi::Entry & entry);
	void	Insert(VertexArray::Multi::Entry & entry);
	void	Remove(VertexArray::Multi::Entry & entry);

	public:
	void	NewSizeMemory(unsigned int memory);

	public:
	unsigned int	Count() const;
	unsigned int	LengthSum() const;

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