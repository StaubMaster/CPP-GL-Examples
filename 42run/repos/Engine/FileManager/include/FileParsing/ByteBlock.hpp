#ifndef  BYTE_BLOCK_HPP
# define BYTE_BLOCK_HPP

# include "uint.hpp"
# include <string>

# include "Generics/Container/Array1D.hpp"

// make this a Array from Engine
// change Array in Engine to be like Array3D
class ByteBlock
{
	private:
	Array1D<uint8>	Bytes;



	public:
	uint32	Length() const;

			uint8 *	Data();
	const	uint8 *	Data() const;

			uint8 *	DataAt(uint64 idx);
	const	uint8 *	DataAt(uint64 idx) const;

			uint8 &	operator[](uint64 idx);
	const	uint8 &	operator[](uint64 idx) const;

	ByteBlock BlockAt(uint64 idx, uint64 size) const;



	public:
	~ByteBlock();

	ByteBlock();
	ByteBlock(uint64 size);
	ByteBlock(uint64 size, uint8 * data);
	ByteBlock(uint64 size, const uint8 * data);

	ByteBlock(const ByteBlock & other);
	ByteBlock operator=(const ByteBlock & other);



	public:
	void	Dispose();

	ByteBlock & Concatenation(uint64 size);
	ByteBlock & Concatenation(const ByteBlock & other);

	ByteBlock(const std::string & str);
	ByteBlock & Concatenation(const std::string & str);
};

#endif