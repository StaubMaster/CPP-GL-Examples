#ifndef  BIT_STREAM_BASE_HPP
# define BIT_STREAM_BASE_HPP

# include "uint.hpp"
# include "FileParsing/ByteBlock.hpp"

class BitStreamBase
{
	public:
	ByteBlock	Block;

	protected:
	virtual ~BitStreamBase();
	BitStreamBase() = delete;

	private:
	BitStreamBase(const BitStreamBase & other) = delete;
	BitStreamBase & operator=(const BitStreamBase & other) = delete;

	protected:
	BitStreamBase(ByteBlock block);
};

#endif