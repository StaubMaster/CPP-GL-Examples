#ifndef  BIT_STREAM_GETTER_HPP
# define BIT_STREAM_GETTER_HPP

# include "FileParsing/BitStreamBase.hpp"

class BitStreamGetter : public BitStreamBase
{
	private:
	uint8			IndexGetBit;
	uint32			IndexGetByte;

	public:
	~BitStreamGetter();
	BitStreamGetter() = delete;

	private:
	BitStreamGetter(const BitStreamGetter & other) = delete;
	BitStreamGetter & operator=(const BitStreamGetter & other) = delete;

	public:
	BitStreamGetter(ByteBlock block);

	public:
	const uint8 *	DataAtIndex() const;

	public:
	void	MoveNextByte();
	void	MoveByte(uint32 step = 1);
	void	MoveBit(uint32 step = 1);

	public:
	uint8	Get8(uint8 bit_count = UINT8_BIT_COUNT) const;
	uint16	Get16(uint8 bit_count = UINT16_BIT_COUNT) const;
	uint32	Get32(uint8 bit_count = UINT32_BIT_COUNT) const;
	uint64	Get64(uint8 bit_count = UINT64_BIT_COUNT) const;

	uint8	Get8Move(uint8 bit_count = UINT8_BIT_COUNT);
	uint16	Get16Move(uint8 bit_count = UINT16_BIT_COUNT);
	uint32	Get32Move(uint8 bit_count = UINT32_BIT_COUNT);
	uint64	Get64Move(uint8 bit_count = UINT64_BIT_COUNT);

	private:
	class LenReachedException : public std::exception { public: const char * what() const throw(); };
};

#endif