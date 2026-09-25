#include "Tile/Object.hpp"
#include "Tile/Pallet.hpp"

#include "Tile/Feature/Pallet.hpp"
#include "Tile/Feature/Object.hpp"

#include "PlayerChange.hpp"

#include "ValueType/_Show.hpp"
#include <iostream>



TileObject::~TileObject()
{
	if (Entry != nullptr)
	{
		Entry -> Exit[(unsigned int)EntryExit] = nullptr;
	}
	for (unsigned int i = 0; i < 3; i++)
	{
		if (Exit[i] != nullptr)
		{
			Exit[i] -> Entry = nullptr;
		}
	}

	delete Entry;
	for (unsigned int i = 0; i < 3; i++)
	{
		delete Exit[i];
	}

	for (unsigned int i = 0; i < Features.Count(); i++)
	{
		delete Features[i];
	}
}
TileObject::TileObject(const TilePallet & pallet)
	: Pallet(pallet)
{ }



PlayerChange TileObject::CheckPlayer(const Player & player) const
{
	PlayerChange h;
	h.Consider(Pallet.CheckPlayer(player));
	for (unsigned int i = 0; i < Features.Count(); i++)
	{
		h.Consider(Features[i] -> CheckPlayer(player));
	}
	return h;
}



void TileObject::TrimEntry()
{
	if (Entry != nullptr)
	{
		Entry -> Exit[(unsigned int)EntryExit] = nullptr;
		delete Entry;
		Entry = nullptr;
	}
}
void TileObject::TrimExit(EPath path)
{
	if (Exit[(unsigned int)path] != nullptr)
	{
		Exit[(unsigned int)path] -> Entry = nullptr;
	}
	delete Exit[(unsigned int)path];
	Exit[(unsigned int)path] = nullptr;
}

//void TileObject::ConnectEntry(TileObject * tile, EPath path) { }
void TileObject::ConnectExit(TileObject * tile, EPath path)
{
	if (tile == nullptr) { return; }

	TrimExit(path);
	Exit[(unsigned int)path] = tile;
	tile -> Entry = this;
	tile -> EntryExit = path;
}



static Trans3D TransForwardPls(const Trans3D & trans, const Trans3D & other)
{
	return Trans3D(
		trans.forward(         +other.Position),
		trans.Rotation.forward(+other.Rotation)
	);
}
static Trans3D TransForwardMns(const Trans3D & trans, const Trans3D & other)
{
	return Trans3D(
		trans.forward(         -other.Position),
		trans.Rotation.forward(-other.Rotation)
	);
}

void TileObject::DisplayThis(Trans3D trans, const TilePalletDisplayOptions & display_options) const
{
	Pallet.Display(trans, display_options);
	for (unsigned int i = 0; i < Features.Count(); i++)
	{
		Features[i] -> Display(*this, trans);
	}
}
void TileObject::Display(Trans3D trans, const TilePalletDisplayOptions & display_options) const
{
	DisplayThis(trans, display_options);
	if (Entry != nullptr)
	{
		Entry -> DisplayEntry(TransForwardPls(trans, Pallet.TransEntry), EntryExit, display_options);
	}
	for (unsigned int i = 0; i < 3; i++)
	{
		if (Exit[i] != nullptr)
		{
			Exit[i] -> DisplayExit(TransForwardPls(trans, Pallet.TransExit[i]), display_options);
		}
	}
}
void TileObject::DisplayEntry(Trans3D trans, EPath path, const TilePalletDisplayOptions & display_options) const
{
	unsigned int idx = (unsigned int)path;
	trans = Trans3D(
		trans.Position -      (-Pallet.TransExit[idx].Rotation).forward(trans.Rotation.forward((Pallet.TransExit[idx].Position))),
		trans.Rotation.forward(-Pallet.TransExit[idx].Rotation)
	);

	DisplayThis(trans, display_options);
	if (Entry != nullptr)
	{
		Entry -> DisplayEntry(TransForwardPls(trans, Pallet.TransEntry), EntryExit, display_options);
	}
}
void TileObject::DisplayExit(Trans3D trans, const TilePalletDisplayOptions & display_options) const
{
	trans = TransForwardMns(trans, Pallet.TransEntry);

	DisplayThis(trans, display_options);
	for (unsigned int i = 0; i < 3; i++)
	{
		if (Exit[i] != nullptr)
		{
			Exit[i] -> DisplayExit(TransForwardPls(trans, Pallet.TransExit[i]), display_options);
		}
	}
}
