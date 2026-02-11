#ifndef  ANCHOR_ENUM_HPP
# define ANCHOR_ENUM_HPP

enum class AnchorType : unsigned char
{
	None	= 0b00,
	Min		= 0b01,
	Max		= 0b10,
	Both	= 0b11,
};

#endif