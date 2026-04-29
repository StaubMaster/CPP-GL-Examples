#ifndef  VOXEL_TEMPLATE_HPP
# define VOXEL_TEMPLATE_HPP

# include "VoxelOrientation.hpp"

struct Voxel;
struct VoxelGraphicsData;
struct VoxelGraphicsTemplate;
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



	const VoxelGraphicsTemplate &	GraphicsTemplate;

	unsigned int	Texture;
	// FileInfo Texture ? could be multiple
	// know all File Names it wants to use

	::PolyHedra *		PolyHedra;

	const VoxelGraphicsData &	AxisData(AxisRel axis) const;
	bool	Visible(AxisRel axis) const;

	Voxel	ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const;



	~VoxelTemplate();
	VoxelTemplate(VoxelGraphicsTemplate & graphics_template);

	VoxelTemplate(const VoxelTemplate & other) = delete;
	VoxelTemplate & operator=(const VoxelTemplate & other) = delete;

//	void	InitCube(unsigned int tex);
//	void	InitCylinder(unsigned int tex);
//	void	InitSlope(unsigned int tex);
};

#endif