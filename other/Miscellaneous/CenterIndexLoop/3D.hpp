#ifndef  CENTER_INDEX_LOOP_3D_HPP
# define CENTER_INDEX_LOOP_3D_HPP

# include "ValueType/Vector/I3.hpp"

# include "CenterIndexLoop/2D.hpp"

struct CenterIndexLoop3D
{
	unsigned int		Limit;
	
	CenterIndexLoop2D	Layer0;
	
	bool				Layer1Done;
	unsigned int		Layer1Size;
	unsigned char		Layer1Control;
	VectorI2			Layer1Index;
	
	void	Layer1New(unsigned int layer);
	void	Layer1Loop();
	
	bool		Done() const;
	VectorI3	Index() const;
	
	void	New(unsigned int limit);
	void	Continue();
};

#endif