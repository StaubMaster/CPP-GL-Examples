#ifndef  BYTE_STREAM_GETTER_HPP
# define BYTE_STREAM_GETTER_HPP

# include "FileParsing/ByteStreamBase.hpp"
# include "FileParsing/ByteBlock.hpp"

struct ByteStreamGetter : public ByteStreamBase
{
	public:
	uint64		Index;

	public:
	~ByteStreamGetter();
	ByteStreamGetter() = delete;
	ByteStreamGetter(const ByteStreamGetter & other) = delete;
	ByteStreamGetter & operator=(const ByteStreamGetter & other) = delete;

	ByteStreamGetter(ByteBlock block);

	public:
	void Move(uint64 step = 1);

	public:
	uint8		Get1();
	uint16		Get2();
	uint32		Get4();
	uint64		Get8();
	ByteBlock	GetBlock(uint64 size);

	public:
	uint8		Get1(uint64 idx);
	uint16		Get2(uint64 idx);
	uint32		Get4(uint64 idx);
	uint64		Get8(uint64 idx);
	ByteBlock	GetBlock(uint64 idx, uint64 size);
};

#endif