#ifndef  BYTE_STREAM_SETTER_HPP
# define BYTE_STREAM_SETTER_HPP

# include "FileParsing/ByteStreamBase.hpp"

struct ByteStreamSetter : public ByteStreamBase
{
	public:
	uint64		Index;

	public:
	~ByteStreamSetter();
	ByteStreamSetter() = delete;
	ByteStreamSetter(const ByteStreamSetter & other) = delete;
	ByteStreamSetter & operator=(const ByteStreamSetter & other) = delete;

	ByteStreamSetter(ByteBlock block);

	public:
	void Move(uint64 step = 1);

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
};

#endif