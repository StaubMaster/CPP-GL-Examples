#include "Structure.hpp"
#include "VoxelPallet.hpp"



Structure Structure::Tree0;
void Structure::Default()
{
	{
		Structure & structure = Tree0;

		structure.Offset = VectorI3(-1, 0, -1);
		structure.Voxels.Size(VectorU3(3, 24, 3));

		const VoxelPallet & pallet0 = VoxelPalletMap::All["Leaves"];
		const VoxelPallet & pallet1 = VoxelPalletMap::All["Log"];

		for (unsigned int i = 0; i < 22; i++)
		{
			structure.Voxels[VectorU3(1, i, 1)] = pallet1.ToVoxel();
		}
		for (unsigned int i = 22; i < 24; i++)
		{
			structure.Voxels[VectorU3(1, i, 1)] = pallet0.ToVoxel();
		}
		for (unsigned int i = 4; i < 8; i++)
		{
			structure.Voxels[VectorU3(1, i, 0)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(1, i, 2)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(0, i, 1)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(2, i, 1)] = pallet0.ToVoxel();
		}
		for (unsigned int i = 8; i < 20; i++)
		{
			structure.Voxels[VectorU3(0, i, 0)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(1, i, 0)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(2, i, 0)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(2, i, 1)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(2, i, 2)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(1, i, 2)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(0, i, 2)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(0, i, 1)] = pallet0.ToVoxel();
		}
		for (unsigned int i = 20; i < 24; i++)
		{
			structure.Voxels[VectorU3(1, i, 0)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(1, i, 2)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(0, i, 1)] = pallet0.ToVoxel();
			structure.Voxels[VectorU3(2, i, 1)] = pallet0.ToVoxel();
		}
	}
	/*{
		Tree0.Offset = VectorI3(-2, 0, -2);
		Tree0.Voxels.ChangeSize(VectorU3(5, 7, 5));

		//VoxelPallet & pallet0 = &VoxelPalletMap::All["OrientationCube"];
		//VoxelPallet & pallet1 = &VoxelPalletMap::All["OrientationCylinder"];
		const VoxelPallet * pallet0 = &VoxelPalletMap::All["Leaves"];
		const VoxelPallet * pallet1 = &VoxelPalletMap::All["Log"];

		Tree0.Voxels[VectorU3(1, 3, 0)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 3, 0)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 3, 0)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 4, 0)] = pallet0.ToVoxel();

		Tree0.Voxels[VectorU3(0, 3, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 3, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 3, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 3, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(4, 3, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 4, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 4, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 4, 1)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 5, 1)] = pallet0.ToVoxel();

		Tree0.Voxels[VectorU3(0, 3, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 3, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 3, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 3, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(4, 3, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(0, 4, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 4, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 4, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 4, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(4, 4, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 5, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 5, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 5, 2)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 6, 2)] = pallet0.ToVoxel();
		
		Tree0.Voxels[VectorU3(0, 3, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 3, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 3, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 3, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(4, 3, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(1, 4, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 4, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 4, 3)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 5, 3)] = pallet0.ToVoxel();
		
		Tree0.Voxels[VectorU3(1, 3, 4)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 3, 4)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(3, 3, 4)] = pallet0.ToVoxel();
		Tree0.Voxels[VectorU3(2, 4, 4)] = pallet0.ToVoxel();
		
		Tree0.Voxels[VectorU3(2, 0, 2)] = pallet1.ToVoxel();
		Tree0.Voxels[VectorU3(2, 1, 2)] = pallet1.ToVoxel();
		Tree0.Voxels[VectorU3(2, 2, 2)] = pallet1.ToVoxel();
		Tree0.Voxels[VectorU3(2, 3, 2)] = pallet1.ToVoxel();
		Tree0.Voxels[VectorU3(2, 4, 2)] = pallet1.ToVoxel();
	}*/
}
