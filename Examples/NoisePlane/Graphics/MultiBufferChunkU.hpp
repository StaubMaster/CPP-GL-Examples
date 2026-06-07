#ifndef  MULTI_BUFFER_CHUNK_U_HPP
# define MULTI_BUFFER_CHUNK_U_HPP

# include "Buffer.hpp"
# include "Main/Data.hpp"
# include "Main/Buffer.hpp"

class MultiBufferChunkU
{
	public:
	struct Entry
	{
		MultiBufferChunkU &		Buffer;
		unsigned int			Offset;
		unsigned int			Length;
		// put Array here
		// update Buffer
		//  check for Array, put Array, clear Array

		bool	IsEmpty() const;
		void	MakeEmpty();

		void	Put(const Container::Array<VoxelGraphics::MainFaceU> & data);

		~Entry();
		Entry() = delete;
		Entry(MultiBufferChunkU & buffer);
		Entry(const Entry & other) = delete;
		Entry & operator=(const Entry & other) = delete;
	};

	public:
	unsigned int					Size;
	VoxelGraphics::BufferU			Buffer;
	VoxelGraphics::MainLayoutU		Layout;

	public:
	~MultiBufferChunkU();
	MultiBufferChunkU();
	MultiBufferChunkU(const MultiBufferChunkU & other) = delete;
	MultiBufferChunkU & operator=(const MultiBufferChunkU & other) = delete;

	public:
	void	NewSize(unsigned int size);

	private:
	public:
	Container::Binary<Entry*>	Entrys;
	Container::Binary<int>		Offsets;
	Container::Binary<int>		Lengths;

	public:
	bool	CheckEntry(Entry & entry);
	void	Insert(Entry & entry);
	void	Remove(Entry & entry);

	public:
	void	Draw();
};

#endif