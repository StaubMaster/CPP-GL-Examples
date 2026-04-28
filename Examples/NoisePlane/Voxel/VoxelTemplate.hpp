#ifndef  VOXEL_TEMPLATE_HPP
# define VOXEL_TEMPLATE_HPP

# include "Graphics/Voxel.hpp"
# include "VoxelOrientation.hpp"

# include "Miscellaneous/Container/Binary.hpp"

struct Voxel;
class PolyHedra;

struct VoxelTemplate
{
	static VoxelTemplate	OrientationCube;
	static VoxelTemplate	OrientationCylinder;
	static VoxelTemplate	OrientationSlope;

	static VoxelTemplate	Gray;
	static VoxelTemplate	Grass;
	static VoxelTemplate	RedLog;

	static VoxelTemplate	ConcreteCube;
	static VoxelTemplate	ConcreteCylinder;



	unsigned int	Texture;
	// FileInfo Texture ? could be multiple
	// know all File Names it wants to use

	bool	HidePrevX;
	bool	HidePrevY;
	bool	HidePrevZ;

	bool	HideNextX;
	bool	HideNextY;
	bool	HideNextZ;

	AxisRel	OrientationAxis0;
	AxisRel	OrientationAxis1;



	// dont store duplicate Meshes
	// Cubes have the same Meshes but different Textures
	// also Template should know what Texture they use
	// assamble Textures into TextureArray automatically ?
	// what if textures have differnt sizes ?
	// fixed allowed sizes

	Container::Binary<VoxelGraphics::MainTriangle>	Here;

	Container::Binary<VoxelGraphics::MainTriangle>	PrevX;
	Container::Binary<VoxelGraphics::MainTriangle>	PrevY;
	Container::Binary<VoxelGraphics::MainTriangle>	PrevZ;

	Container::Binary<VoxelGraphics::MainTriangle>	NextX;
	Container::Binary<VoxelGraphics::MainTriangle>	NextY;
	Container::Binary<VoxelGraphics::MainTriangle>	NextZ;

	::PolyHedra *		PolyHedra;

	const Container::Binary<VoxelGraphics::MainTriangle> &	AxisData(AxisRel axis) const;

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