#ifndef  VOXEL_TEMPLATE_HPP
# define VOXEL_TEMPLATE_HPP

# include "Graphics/Voxel.hpp"

# include "Miscellaneous/Container/Binary.hpp"

struct VoxelTemplate
{
	static VoxelTemplate	Orientation;
	static VoxelTemplate	Gray;
	
	static VoxelTemplate	Grass;
	static VoxelTemplate	RedLog;

	unsigned int	Texture;

	bool	HidePrevX;
	bool	HidePrevY;
	bool	HidePrevZ;

	bool	HideNextX;
	bool	HideNextY;
	bool	HideNextZ;

	Container::Binary<VoxelGraphics::MainData>	Here;

	Container::Binary<VoxelGraphics::MainData>	PrevX;
	Container::Binary<VoxelGraphics::MainData>	PrevY;
	Container::Binary<VoxelGraphics::MainData>	PrevZ;

	Container::Binary<VoxelGraphics::MainData>	NextX;
	Container::Binary<VoxelGraphics::MainData>	NextY;
	Container::Binary<VoxelGraphics::MainData>	NextZ;

	~VoxelTemplate();
	VoxelTemplate();

	VoxelTemplate(const VoxelTemplate & other);
	VoxelTemplate & operator=(const VoxelTemplate & other);

	void	InitCube(unsigned int tex);
	void	InitCylinder(unsigned int tex);
};

#endif