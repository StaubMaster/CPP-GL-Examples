#include "Tile/Pallet.hpp"
#include "Tile/Feature/Pallet.hpp"
#include "Tile/PalletDisplayOptions.hpp"
#include "Player.hpp"
#include "PlayerChange.hpp"



TilePallet::~TilePallet()
{
	for (unsigned int i = 0; i < Features.Count(); i++)
	{
		delete Features[i];
	}
}

void TilePallet::Init()
{
	PathTo.LengthLimit = PathTo.LengthSum;
	TransEntry = PathTo.First();

	for (unsigned int i = 0; i < 3; i++)
	{
		if (HasPath((EPath)i))
		{
			LengthTo[i] = (PathTo.Last().Position - Path[i].First().Position).length();
			Path[i].LengthLimit = Path[i].LengthSum + PathTo.LengthSum + LengthTo[i];
			TransExit[i] = Path[i].Last();
		}
	}
}



bool TilePallet::HasPath(EPath path) const
{
	return Path[(unsigned int)path].Nodes.Count() != 0;
}
float TilePallet::PathLimit(EPath path) const
{
	return Path[(unsigned int)path].LengthLimit;
}
Trans3D TilePallet::Target(EPath path, float t) const
{
	Trans3D node0;
	Trans3D node1;

	if (!PathTo.Interpolate(t, node0, node1))
	{
		unsigned int path_idx = (unsigned int)path;
		if (t < LengthTo[path_idx])
		{
			t = t / LengthTo[path_idx];
			node0 = PathTo.Last();
			node1 = Path[path_idx].First();
		}
		else
		{
			t -= LengthTo[path_idx];
			if (!Path[path_idx].Interpolate(t, node0, node1))
			{
				return Path[path_idx].Last();
			}
		}
	}

	float t0 = t - 0.0f;
	float t1 = 1.0f - t;
	return Trans3D(
		((node0.Position * t1) + (node1.Position * t0)),
		((node0.Rotation * t1) + (node1.Rotation * t0))
	);
}



bool TilePallet::CanChoosePath(const Player & player) const
{
	return (!player.PathLocked && (player.TileDistance > PathTo.LengthSum));
}
#include <iostream>
EPath TilePallet::ChoosePath(EPath path_choice, const Player & player) const
{
	float t = player.TileDistance;
	if (t > PathTo.LengthSum)
	{
		t -= PathTo.LengthSum;
		if (
			(!HasPath(EPath::Middle) || t < LengthTo[0]) &&
			(!HasPath(EPath::Left)   || t < LengthTo[1]) &&
			(!HasPath(EPath::Right)  || t < LengthTo[2])
		) // is this check needed? when PathTo.LengthSum is crossed, the Path is chosen. there dosent need to be a limit
		{
			if (HasPath(path_choice))
			{
				return path_choice;
			}
			return EPath::Middle;
		}
	}
	return player.Path;
}



PlayerChange TilePallet::CheckPlayer(const Player & player) const
{
	PlayerChange h;
	for (unsigned int i = 0; i < Features.Count(); i++)
	{
		h.Consider(Features[i] -> CheckPlayer(player));
	}
	return h;
}



NewPolyHedra::Type_PalletObjectManager<NewPolyHedra::Basic3D::ObjectData, NewPolyHedra::Basic3D::InstanceData> * TilePallet::ObjectManagerEntry = nullptr;
NewPolyHedra::Type_PalletObjectManager<NewPolyHedra::Basic3D::ObjectData, NewPolyHedra::Basic3D::InstanceData> * TilePallet::ObjectManagerExit = nullptr;

void TilePallet::Display(const Trans3D & trans, const TilePalletDisplayOptions & display_options) const
{
	NewPolyHedra::Basic3D::ObjectData data;

	data.Trans = trans;
	Object -> InstancesFullPut(data);

	if (display_options.Connections)
	{
		data.Trans = trans.forward(TransEntry);
		ObjectManagerEntry -> InstancesFullPut(data);
		
		for (unsigned int i = 0; i < 3; i++)
		{
			if (HasPath((EPath)i))
			{
				data.Trans = trans.forward(TransExit[i]);
				ObjectManagerExit -> InstancesFullPut(data);
			}
		}
	}

	if (display_options.Paths)
	{
		PathTo.Display(trans);
		for (unsigned int i = 0; i < 3; i++)
		{
			Path[i].Display(trans);
		}
	}

	if (display_options.Features)
	{
		for (unsigned int i = 0; i < Features.Count(); i++)
		{
			Features[i] -> Display(*this, trans);
		}
	}
}



#include "Tile/Object.hpp"
TileObject * TilePallet::ToObject() const
{
	TileObject * object = new TileObject(*this);
	for (unsigned int i = 0; i < Features.Count(); i++)
	{
		Features[i] -> PutObjects(*object);
	}
	return object;
}
