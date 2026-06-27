#include "Structure.hpp"
#include "Voxel/Pallet.hpp"

#include "ValueType/Loop/U3.hpp"



Structure Structure::Tree0;
Structure Structure::Tree1;

void Structure::Default()
{
	{
		Structure & structure = Tree0;

		structure.Center = VectorU3(1, 0, 1);
		structure.Voxels.Size(VectorU3(3, 24, 3));

		const VoxelPallet & pallet0 = VoxelPalletMap::All["Leaves"];
		const VoxelPallet & pallet1 = VoxelPalletMap::All["Log"];

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
		for (unsigned int i = 0; i < 22; i++)
		{
			structure.Voxels[VectorU3(1, i, 1)] = pallet1.ToVoxel();
		}
	}

	{
		Structure & structure = Tree1;

		structure.Center = VectorU3(2, 0, 2);
		structure.Voxels.Size(VectorU3(5, 12, 5));

		const VoxelPallet & pallet0 = VoxelPalletMap::All["Leaves"];
		const VoxelPallet & pallet1 = VoxelPalletMap::All["Log"];

		LoopU3 loop(VectorU3(0, 7, 0), VectorU3(5, 12, 5));
		for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			structure.Voxels[u] = pallet0.ToVoxel();
		}

		structure.Voxels[VectorU3(0,  7, 0)] = Voxel();
		structure.Voxels[VectorU3(4,  7, 0)] = Voxel();
		structure.Voxels[VectorU3(0,  7, 4)] = Voxel();
		structure.Voxels[VectorU3(4,  7, 4)] = Voxel();
		structure.Voxels[VectorU3(0, 11, 0)] = Voxel();
		structure.Voxels[VectorU3(4, 11, 0)] = Voxel();
		structure.Voxels[VectorU3(0, 11, 4)] = Voxel();
		structure.Voxels[VectorU3(4, 11, 4)] = Voxel();

		for (unsigned int i = 0; i < 10; i++)
		{
			structure.Voxels[VectorU3(2, i, 2)] = pallet1.ToVoxel();
		}
	}
}
