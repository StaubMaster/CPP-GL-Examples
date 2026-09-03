#ifndef  VOXEL_PALLET_GEOMETRY_PARSER_HPP
# define VOXEL_PALLET_GEOMETRY_PARSER_HPP

/* another on of these

File contains an arbitrary number of Geometrys
Geometrys are put into Map
each Name only once, show Error if problems, keep loading

Map can be made from multiple Files
give Map to Parser


new "name"		# starts a new Geometry
done			# ends a Geometry
				# end automatically at end of File or if next begins

# only the U Corners are allowed, no need to specify ?
# DataU only has 1 Quad Face per side

# DataU.PrevX.Quad0(pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 0);
quad0   prevX   000 010 100 110   0.0 0.0 1.0 1.0   0

*/

//# include "3D/Voxel/Pallet/Geometry/Map.hpp"
struct VoxelPalletGeometryMap;
struct VoxelPalletGeometry;

# include "FileParsing/TextCommand/Loop.hpp"
# include "FileParsing/TextCommand/Func.hpp"

# include "FileInfo.hpp"

namespace VoxelGeometryDataU { struct Face; };
namespace VoxelGeometryDataF { struct Axis; };

# include "Generics/Container/Binary.hpp"

# include "ValueType/Vector/F3.hpp"

struct VoxelPalletGeometryMapParser : public TextCommand::Loop
{
	VoxelPalletGeometryMap &	Map;
	VoxelPalletGeometry *		Entry = nullptr;

	Container::Binary<VectorF3>		Corners;
	void		NewCorner(const TextCommand::Args & cmd_args);

	VoxelPalletGeometryMapParser() = delete;
	VoxelPalletGeometryMapParser(VoxelPalletGeometryMap & map);

	void	New(const TextCommand::Args & cmd_args);
	void	Done(const TextCommand::Args & cmd_args);

	void	ShowAxis(const TextCommand::Args & cmd_args);
	void	HideAxis(const TextCommand::Args & cmd_args);

	VoxelGeometryDataU::Face &	ToFaceU(std::string str);
	void	UQuad0(const TextCommand::Args & cmd_args);
	void	UQuad1(const TextCommand::Args & cmd_args);

	VoxelGeometryDataF::Axis &	ToFaceF(std::string str);
	void	FTri0(const TextCommand::Args & cmd_args);
	void	FTri1(const TextCommand::Args & cmd_args);
	void	FQuad0(const TextCommand::Args & cmd_args);
	void	FQuad1(const TextCommand::Args & cmd_args);

	static void		Parse(VoxelPalletGeometryMap & map, const FileInfo & file);
};

#endif