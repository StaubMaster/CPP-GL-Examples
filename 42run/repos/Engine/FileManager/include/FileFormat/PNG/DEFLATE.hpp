
#ifndef DEFLATE_HPP
# define DEFLATE_HPP

# include "uint.hpp"
# include "FileParsing/ByteStreamQueue.hpp"
# include "FileParsing/BitStreamGetter.hpp"

# include <exception>

class HuffmanTree;

class DEFLATE
{
	public:
	static uint8 *		dynamic_Huffman(BitStreamGetter & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN);

	static void			decode_Huffman(BitStreamGetter & bits, HuffmanTree & literal, HuffmanTree & distance, ByteStreamQueue & data);

	public:
	static void			decode_direct(BitStreamGetter & bits, ByteStreamQueue & data);
	static void			decode_static(BitStreamGetter & bits, ByteStreamQueue & data);
	static void			decode_dynamic(BitStreamGetter & bits, ByteStreamQueue & data);
	static ByteBlock	decode(ByteBlock data, uint32 size);

	private:
	class Exception_NotImplemented : public std::exception
	{
		private:
			std::string Text;
		public:
			Exception_NotImplemented(std::string head, std::string name);
		public: 
			const char * what() const noexcept;
	};
	class Exception_InvalidBlockType : public std::exception
	{
		private:
			std::string Text;
		public:
			Exception_InvalidBlockType(uint32 type);
		public:
			const char * what() const noexcept;
	};
	class Exception_InvalidData : public std::exception
	{
		private:
			std::string Text;
		public:
			Exception_InvalidData(std::string head, uint32 value);
		public:
			const char * what() const noexcept;
	};
};

#endif
