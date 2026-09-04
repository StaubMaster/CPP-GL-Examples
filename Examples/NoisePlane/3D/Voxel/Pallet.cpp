#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"
#include "3D/Voxel.hpp"

#include "PolyHedra/Skin/Skin.hpp"



VoxelPallet::VoxelPallet(VoxelPalletIndex idx, const char * name, const VoxelPalletGeometry & geometry, VoxelMaterialType material)
	: Index(idx)
	, Name(name)
	, Geometry(&geometry)
	, Material(material)
	, Textures()
	, PolyHedra(nullptr)
{ }



TextureFileIndex VoxelPallet::FindTextureFileIndex(int idx) const
{
	if (idx >= 0 && idx < 6)
	{
		return Textures[idx];
	}
	TextureFileIndex tex;
	tex.Index = 0;
	return tex;
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
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGeometryDataF::Axis & data)
{
	Skin & skin = *polyhedra.Skin;
	VectorF3 off(0.5f);
	for (unsigned int i = 0; i < data.Data.Count(); i++)
	{
		const VoxelGraphicsDataF::Face & face = data.Data[i];

		unsigned int ph_i = polyhedra.Corners.Count();
		polyhedra.Insert_Corn(face.Vertexes[0].Pos - off);
		polyhedra.Insert_Corn(face.Vertexes[1].Pos - off);
		polyhedra.Insert_Corn(face.Vertexes[2].Pos - off);
		polyhedra.Insert_Face3(ph_i + 0, ph_i + 1, ph_i + 2);

		unsigned int sk_i = skin.Corners.Count();
		skin.Corners.Insert(Skin::Corner(face.Vertexes[0].Tex.X, face.Vertexes[0].Tex.Y, face.Vertexes[0].Tex.Z));
		skin.Corners.Insert(Skin::Corner(face.Vertexes[1].Tex.X, face.Vertexes[1].Tex.Y, face.Vertexes[1].Tex.Z));
		skin.Corners.Insert(Skin::Corner(face.Vertexes[2].Tex.X, face.Vertexes[2].Tex.Y, face.Vertexes[2].Tex.Z));
		skin.Insert_Face3(sk_i + 0, sk_i + 1, sk_i + 2);
	}
}
/*static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGeometryDataF::Full & voxel_graphics)
{
	PolyHedraVoxelData(polyhedra, voxel_graphics.Here);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevX);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevY);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevZ);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextX);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextY);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextZ);
}*/
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGeometryDataU::Face & data)
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

		unsigned int sk_i = skin.Corners.Count();
		skin.Corners.Insert(Skin::Corner(data.Vertexes[0].Tex.X, data.Vertexes[0].Tex.Y, data.Vertexes[0].Idx));
		skin.Corners.Insert(Skin::Corner(data.Vertexes[1].Tex.X, data.Vertexes[1].Tex.Y, data.Vertexes[1].Idx));
		skin.Corners.Insert(Skin::Corner(data.Vertexes[2].Tex.X, data.Vertexes[2].Tex.Y, data.Vertexes[2].Idx));
		skin.Corners.Insert(Skin::Corner(data.Vertexes[3].Tex.X, data.Vertexes[3].Tex.Y, data.Vertexes[3].Idx));
		skin.Insert_Face3(sk_i + 0, sk_i + 1, sk_i + 2);
		skin.Insert_Face3(sk_i + 2, sk_i + 1, sk_i + 3);
	}
}
/*static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelGeometryDataU::Cube & voxel_graphics)
{
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevX);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevY);
	PolyHedraVoxelData(polyhedra, voxel_graphics.PrevZ);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextX);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextY);
	PolyHedraVoxelData(polyhedra, voxel_graphics.NextZ);
}*/
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
	if (geometry.UseF_PrevX) { PolyHedraVoxelData(*PolyHedra, dataF.PrevX); } else { PolyHedraVoxelData(*PolyHedra, dataU.PrevX); }
	if (geometry.UseF_PrevY) { PolyHedraVoxelData(*PolyHedra, dataF.PrevY); } else { PolyHedraVoxelData(*PolyHedra, dataU.PrevY); }
	if (geometry.UseF_PrevZ) { PolyHedraVoxelData(*PolyHedra, dataF.PrevZ); } else { PolyHedraVoxelData(*PolyHedra, dataU.PrevZ); }
	if (geometry.UseF_NextX) { PolyHedraVoxelData(*PolyHedra, dataF.NextX); } else { PolyHedraVoxelData(*PolyHedra, dataU.NextX); }
	if (geometry.UseF_NextY) { PolyHedraVoxelData(*PolyHedra, dataF.NextY); } else { PolyHedraVoxelData(*PolyHedra, dataU.NextY); }
	if (geometry.UseF_NextZ) { PolyHedraVoxelData(*PolyHedra, dataF.NextZ); } else { PolyHedraVoxelData(*PolyHedra, dataU.NextZ); }
	PolyHedraVoxelData(*PolyHedra, dataF.Here);

	PolyHedra -> Done();
}

Voxel VoxelPallet::ToVoxel() const
{
	Voxel voxel;
	voxel.MakePallet(*this);
	return voxel;
}
Voxel VoxelPallet::ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	Voxel voxel;
	voxel.MakePallet(*this);
	voxel.Orientation = Geometry -> Orient(placeAxis0, placeAxis1);
	return voxel;
}
