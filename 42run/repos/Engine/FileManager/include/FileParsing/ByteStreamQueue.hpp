#ifndef  BYTE_STREAM_QUEUE_HPP
# define BYTE_STREAM_QUEUE_HPP

# include "FileParsing/ByteStreamBase.hpp"

struct ByteStreamQueue : public ByteStreamBase
{
	public:
	uint64		IndexSet;
	uint64		IndexGet;

	public:
	~ByteStreamQueue();
	ByteStreamQueue() = delete;
	ByteStreamQueue(const ByteStreamQueue & other) = delete;
	ByteStreamQueue & operator=(const ByteStreamQueue & other) = delete;

	ByteStreamQueue(ByteBlock block);

	public:
	void MoveSet();
	void MoveGet();
	void MoveSet(uint64 move);
	void MoveGet(uint64 move);

	public:
	void	Set1(uint8 val);
	void	Set2(uint16 val);
	void	Set4(uint32 val);
	void	Set8(uint64 val);
	void	SetBlock(const ByteBlock & block);

	public:
	void	Set1(uint64 idx, uint8 val);
	void	Set2(uint64 idx, uint16 val);
	void	Set4(uint64 idx, uint32 val);
	void	Set8(uint64 idx, uint64 val);
	void	SetBlock(uint64 idx, const ByteBlock & block);

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