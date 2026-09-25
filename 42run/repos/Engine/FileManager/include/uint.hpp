
#ifndef  UINT_HPP
# define UINT_HPP

# include <stdint.h>
# include <string>

#define  UINT8_BYTE_COUNT 1
#define UINT16_BYTE_COUNT 2
#define UINT32_BYTE_COUNT 4
#define UINT64_BYTE_COUNT 8

#define  UINT8_BIT_COUNT (1 << 3)
#define UINT16_BIT_COUNT (1 << 4)
#define UINT32_BIT_COUNT (1 << 5)
#define UINT64_BIT_COUNT (1 << 6)

#define  UINT8_BIT_LIMIT ( UINT8_BIT_COUNT - 1)
#define UINT16_BIT_LIMIT (UINT16_BIT_COUNT - 1)
#define UINT32_BIT_LIMIT (UINT32_BIT_COUNT - 1)
#define UINT64_BIT_LIMIT (UINT64_BIT_COUNT - 1)

#define  UINT8_BIT_MASK 0xFF
#define UINT16_BIT_MASK 0xFFFF
#define UINT32_BIT_MASK 0xFFFFFFFF
#define UINT64_BIT_MASK 0xFFFFFFFFFFFFFFFF

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;



//	uint8
std::string	uint_Chr(uint8 val);

std::string	ToBase2(uint8 val, uint8 num = UINT8_BIT_LIMIT);
std::string	ToSBase2(uint8 val, char seperator, uint8 num = UINT16_BIT_LIMIT);
std::string	ToBase16(uint8 val);
std::string	ToSBase16(uint8 val, char seperator);

uint8 ReverseBits(uint8 val);
uint8 ReverseBytes(uint8 val);



//	uint16
std::string	ToBase2(uint16 val, uint8 num = UINT16_BIT_LIMIT);
std::string	ToSBase2(uint16 val, char seperator, uint8 num = UINT16_BIT_LIMIT);
std::string	ToBase16(uint16 val);
std::string	ToSBase16(uint16 val, char seperator);

uint16 ReverseBits(uint16 val);
uint16 ReverseBytes(uint16 val);



//	uint32
std::string	uint_Chr(uint32 val);

std::string	ToBase2(uint32 val, uint8 num = UINT32_BIT_LIMIT);
std::string	ToSBase2(uint32 val, char seperator, uint8 num = UINT32_BIT_LIMIT);
std::string	ToBase16(uint32 val);
std::string	ToSBase16(uint32 val, char seperator);

uint32 ReverseBits(uint32 val);
uint32 ReverseBytes(uint32 val);



//	uint64
std::string	ToBase2(uint64 val, uint8 num = UINT64_BIT_LIMIT);
std::string	ToSBase2(uint64 val, char seperator, uint8 num = UINT64_BIT_LIMIT);
std::string	ToBase16(uint64 val);
std::string	ToSBase16(uint64 val, char seperator);

uint64 ReverseBits(uint64 val);
uint64 ReverseBytes(uint64 val);



#endif
