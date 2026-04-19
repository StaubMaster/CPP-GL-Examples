#ifndef  VOXEL_TEMPLATE_HPP
# define VOXEL_TEMPLATE_HPP

# include "Graphics/Voxel.hpp"
# include "VoxelOrientation.hpp"

# include "Miscellaneous/Container/Binary.hpp"

struct VoxelTemplate
{
	static VoxelTemplate	OrientationCube;
	static VoxelTemplate	OrientationCylinder;

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

	const Container::Binary<VoxelGraphics::MainData> &	FindPrevX(VoxelOrientation orientation) const;
	const Container::Binary<VoxelGraphics::MainData> &	FindPrevY(VoxelOrientation orientation) const;
	const Container::Binary<VoxelGraphics::MainData> &	FindPrevZ(VoxelOrientation orientation) const;
	const Container::Binary<VoxelGraphics::MainData> &	FindNextX(VoxelOrientation orientation) const;
	const Container::Binary<VoxelGraphics::MainData> &	FindNextY(VoxelOrientation orientation) const;
	const Container::Binary<VoxelGraphics::MainData> &	FindNextZ(VoxelOrientation orientation) const;

	~VoxelTemplate();
	VoxelTemplate();

	VoxelTemplate(const VoxelTemplate & other) = delete;
	VoxelTemplate & operator=(const VoxelTemplate & other) = delete;

	void	InitCube(unsigned int tex);
	void	InitCylinder(unsigned int tex);
};

#endif