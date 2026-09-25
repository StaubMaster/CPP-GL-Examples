#ifndef  PLAYER_HPP
# define PLAYER_HPP

//# include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"
# include "NewPolyHedra/DataType/Basic3D/PalletObjectData.hpp"

# include "EPath.hpp"

# include "PlayerChange.hpp"

# include "ValueType/Box/F3.hpp"

struct Player
{
	float	Multiplier = 1.0f;
	float	TotalDistance = 0.0f;
	BoxF3	Box;

	float	Speed = 0.0f;
	float	TileDistance = 0.0f;

	float	JumpImpulse = 0.0f;
	float	JumpSpeed = 0.0f;
	float	Gravity = 0.0f;
	float	Height = 0.0f;

	EPath	Side = EPath::Middle;
	EPath	Path = EPath::Middle;
	bool	PathLocked = false;

	PlayerChange	Change;

	NewPolyHedra::Basic3D::PalletObjectData		Object;
	NewPolyHedra::Basic3D::PalletObjectData		ObjectBox;

	~Player() = default;
	Player() = default;
	Player(const Player & other) = default;
	Player & operator=(const Player & other) = default;

	void	MakeDefault();
};

#endif