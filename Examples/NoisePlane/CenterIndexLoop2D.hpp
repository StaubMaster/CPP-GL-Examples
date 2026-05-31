#ifndef  CENTER_INDEX_LOOP_2D_HPP
# define CENTER_INDEX_LOOP_2D_HPP

# include "ValueType/Vector/I2.hpp"

struct CenterIndexLoop2D
{
	unsigned int	Limit;

	bool			Done;
	unsigned int	Size;
	unsigned char	Control;
	VectorI2		Index;

	void	New(unsigned int layer);
	void	Continue();
};

#endif