#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"
#include "3D/Voxel.hpp"

#include "PolyHedra/Skin/Skin.hpp"



VoxelPallet::VoxelPallet(VoxelPalletIndex idx, std::string name, const VoxelPalletGeometry & geometry, VoxelMaterialType material)
	: Index(idx)
	, Name(name)
	, Geometry(&geometry)
	, Material(material)
	, Textures()
	, PolyHedra(nullptr)
{ }



void VoxelPallet::TextureAxis(
	FileInfo prevX, Axis2D::Orientation prevX_orientation,
	FileInfo prevY, Axis2D::Orientation prevY_orientation,
	FileInfo prevZ, Axis2D::Orientation prevZ_orientation,
	FileInfo nextX, Axis2D::Orientation nextX_orientation,
	FileInfo nextY, Axis2D::Orientation nextY_orientation,
	FileInfo nextZ, Axis2D::Orientation nextZ_orientation
)
{
	Textures[0].Change(prevX); TextureOrientations[0] = prevX_orientation;
	Textures[1].Change(prevY); TextureOrientations[1] = prevY_orientation;
	Textures[2].Change(prevZ); TextureOrientations[2] = prevZ_orientation;
	Textures[3].Change(nextX); TextureOrientations[3] = nextX_orientation;
	Textures[4].Change(nextY); TextureOrientations[4] = nextY_orientation;
	Textures[5].Change(nextZ); TextureOrientations[5] = nextZ_orientation;
}
void VoxelPallet::TextureAxis(
	FileInfo prevX, FileInfo prevY, FileInfo prevZ,
	FileInfo nextX, FileInfo nextY, FileInfo nextZ
)
{
	Textures[0].Change(prevX);
	Textures[1].Change(prevY);
	Textures[2].Change(prevZ);
	Textures[3].Change(nextX);
	Textures[4].Change(nextY);
	Textures[5].Change(nextZ);
}
void VoxelPallet::TextureAxis(
	FileInfo axisX, FileInfo axisY, FileInfo axisZ
)
{
	Textures[0].Change(axisX);
	Textures[1].Change(axisY);
	Textures[2].Change(axisZ);
	Textures[3].Change(axisX);
	Textures[4].Change(axisY);
	Textures[5].Change(axisZ);
}
void VoxelPallet::TexturePrismY(FileInfo base, FileInfo belt)
{
	Textures[0].Change(belt);
	Textures[1].Change(base);
	Textures[2].Change(belt);
	Textures[3].Change(belt);
	Textures[4].Change(base);
	Textures[5].Change(belt);
}
void VoxelPallet::TextureAll(FileInfo tex)
{
	Textures[0].Change(tex);
	Textures[1].Change(tex);
	Textures[2].Change(tex);
	Textures[3].Change(tex);
	Textures[4].Change(tex);
	Textures[5].Change(tex);
}



#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Skin/Data.hpp"
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelPallet & pallet, const VoxelGeometryDataU::Face & data)
{
	Skin & skin = *polyhedra.Skin;
	VectorF3 off(0.5f);
	{
		unsigned int ph_i = polyhedra.Corners.Count();
		polyhedra.Insert_Corn(data.Vertexes[0].Pos.ToF() - off);
		polyhedra.Insert_Corn(data.Vertexes[1].Pos.ToF() - off);
		polyhedra.Insert_Corn(data.Vertexes[2].Pos.ToF() - off);
		polyhedra.Insert_Corn(data.Vertexes[3].Pos.ToF() - off);
		polyhedra.Insert_Face3(ph_i + 0, ph_i + 1, ph_i + 2);
		polyhedra.Insert_Face3(ph_i + 2, ph_i + 1, ph_i + 3);

		const Axis2D::Orientation & tex_orientation = pallet.TextureOrientations[data.Tex];

		unsigned int tex_idx;
		tex_idx = data.Tex;

		VectorU2 tex[4];
		tex[0] = tex_orientation.absolute(data.Vertexes[0].Tex);
		tex[1] = tex_orientation.absolute(data.Vertexes[1].Tex);
		tex[2] = tex_orientation.absolute(data.Vertexes[2].Tex);
		tex[3] = tex_orientation.absolute(data.Vertexes[3].Tex);

		unsigned int sk_i = skin.Corners.Count();
		skin.Corners.Insert(Skin::Corner(tex[0].X, tex[0].Y, tex_idx));
		skin.Corners.Insert(Skin::Corner(tex[1].X, tex[1].Y, tex_idx));
		skin.Corners.Insert(Skin::Corner(tex[2].X, tex[2].Y, tex_idx));
		skin.Corners.Insert(Skin::Corner(tex[3].X, tex[3].Y, tex_idx));
		skin.Insert_Face3(sk_i + 0, sk_i + 1, sk_i + 2);
		skin.Insert_Face3(sk_i + 2, sk_i + 1, sk_i + 3);
	}
	(void)pallet;
}
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelPallet & pallet, const VoxelGeometryDataF::Axis & data)
{
	Skin & skin = *polyhedra.Skin;
	VectorF3 off(0.5f);
	for (unsigned int i = 0; i < data.Data.Count(); i++)
	{
		const VoxelGeometryDataF::Face & face = data.Data[i];

		const Axis2D::Orientation & tex_orientation = pallet.TextureOrientations[face.Tex];

		unsigned int tex_idx;
		tex_idx = face.Tex;

		VectorF2 tex[4];
		tex[0] = tex_orientation.absolute(face.Vertexes[0].Tex);
		tex[1] = tex_orientation.absolute(face.Vertexes[1].Tex);
		tex[2] = tex_orientation.absolute(face.Vertexes[2].Tex);
		tex[3] = tex_orientation.absolute(face.Vertexes[3].Tex);

		unsigned int ph_i = polyhedra.Corners.Count();
		polyhedra.Insert_Corn(face.Vertexes[0].Pos - off);
		polyhedra.Insert_Corn(face.Vertexes[1].Pos - off);
		polyhedra.Insert_Corn(face.Vertexes[2].Pos - off);
		polyhedra.Insert_Face3(ph_i + 0, ph_i + 1, ph_i + 2);

		unsigned int sk_i = skin.Corners.Count();
		skin.Corners.Insert(Skin::Corner(tex[0].X, tex[0].Y, tex_idx));
		skin.Corners.Insert(Skin::Corner(tex[1].X, tex[1].Y, tex_idx));
		skin.Corners.Insert(Skin::Corner(tex[2].X, tex[2].Y, tex_idx));
		skin.Insert_Face3(sk_i + 0, sk_i + 1, sk_i + 2);
	}
	(void)pallet;
}
void VoxelPallet::MakePolyHedra()
{
	PolyHedra = new ::PolyHedra();
	Skin * skin = new ::Skin();
	skin -> Size = VectorU2(128, 64);
	for (unsigned int i = 0; i < 6; i++)
	{
		skin -> Images.Insert(Textures[i].File.LoadImage());
	}
	skin -> Done();
	PolyHedra -> Skin = skin;

	const VoxelPalletGeometry & geometry = *Geometry;
	const VoxelGeometryDataU::Cube & dataU = geometry.DataU;
	const VoxelGeometryDataF::Full & dataF = geometry.DataF;
	if (geometry.UseF_PrevX) { PolyHedraVoxelData(*PolyHedra, *this, dataF.PrevX); } else { PolyHedraVoxelData(*PolyHedra, *this, dataU.PrevX); }
	if (geometry.UseF_PrevY) { PolyHedraVoxelData(*PolyHedra, *this, dataF.PrevY); } else { PolyHedraVoxelData(*PolyHedra, *this, dataU.PrevY); }
	if (geometry.UseF_PrevZ) { PolyHedraVoxelData(*PolyHedra, *this, dataF.PrevZ); } else { PolyHedraVoxelData(*PolyHedra, *this, dataU.PrevZ); }
	if (geometry.UseF_NextX) { PolyHedraVoxelData(*PolyHedra, *this, dataF.NextX); } else { PolyHedraVoxelData(*PolyHedra, *this, dataU.NextX); }
	if (geometry.UseF_NextY) { PolyHedraVoxelData(*PolyHedra, *this, dataF.NextY); } else { PolyHedraVoxelData(*PolyHedra, *this, dataU.NextY); }
	if (geometry.UseF_NextZ) { PolyHedraVoxelData(*PolyHedra, *this, dataF.NextZ); } else { PolyHedraVoxelData(*PolyHedra, *this, dataU.NextZ); }
	PolyHedraVoxelData(*PolyHedra, *this, dataF.Here);

	PolyHedra -> Done();
}

Voxel VoxelPallet::ToVoxel() const
{
	Voxel voxel;
	voxel.MakePallet(*this);
	return voxel;
}
Voxel VoxelPallet::ToVoxel(Axis3D::Rel placeAxis0, Axis3D::Rel placeAxis1) const
{
	Voxel voxel;
	voxel.MakePallet(*this);
	voxel.Orientation = Geometry -> Orient(placeAxis0, placeAxis1);
	return voxel;
}
