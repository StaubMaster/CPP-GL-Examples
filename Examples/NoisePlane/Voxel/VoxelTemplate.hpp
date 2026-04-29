#ifndef  VOXEL_TEMPLATE_HPP
# define VOXEL_TEMPLATE_HPP

# include "FileInfo.hpp"

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

	FileInfo		TextureFile;
	unsigned int	TextureIndex;

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