#ifndef  VOXEL_TEMPLATE_HPP
# define VOXEL_TEMPLATE_HPP

# include "Graphics/Voxel.hpp"
# include "VoxelOrientation.hpp"

# include "Miscellaneous/Container/Binary.hpp"

struct Voxel;

struct VoxelTemplate
{
	static VoxelTemplate	OrientationCube;
	static VoxelTemplate	OrientationCylinder;
	static VoxelTemplate	OrientationSlope;

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

	AxisRel	OrientationAxis0;
	AxisRel	OrientationAxis1;

	Container::Binary<VoxelGraphics::MainData>	Here;

	Container::Binary<VoxelGraphics::MainData>	PrevX;
	Container::Binary<VoxelGraphics::MainData>	PrevY;
	Container::Binary<VoxelGraphics::MainData>	PrevZ;

	Container::Binary<VoxelGraphics::MainData>	NextX;
	Container::Binary<VoxelGraphics::MainData>	NextY;
	Container::Binary<VoxelGraphics::MainData>	NextZ;

	const Container::Binary<VoxelGraphics::MainData> &	AxisData(AxisRel axis) const;

	VoxelOrientation	Orient(AxisRel placeAxis0, AxisRel placeAxis1) const;

	Voxel	ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const;



	~VoxelTemplate();
	VoxelTemplate();

	VoxelTemplate(const VoxelTemplate & other) = delete;
	VoxelTemplate & operator=(const VoxelTemplate & other) = delete;

	void	InitCube(unsigned int tex);
	void	InitCylinder(unsigned int tex);
	void	InitSlope(unsigned int tex);
};

#endif