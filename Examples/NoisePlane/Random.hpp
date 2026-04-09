#ifndef  RANDOM_HPP
# define RANDOM_HPP

// rand() returns [ 0x0000 to 0x7FFF ]
// make my own that returns full 32Bits

namespace Random
{
	// Testing Random Number Generation
	unsigned int	Mutilate(unsigned int val);

	// random 32 Bits
	unsigned int	UInt32();

	// random float from 0 to 1
	// including 0 and including 1
	float	Float01In();

	// random float from 0 to 1
	// including 0 and excluding 1
	float	Float01Ex();
};

#endif