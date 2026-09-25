#ifndef  PLAYER_CHANGE_HPP
# define PLAYER_CHANGE_HPP

struct PlayerChange
{
	bool			DeathWall = false;
	bool			NotAboveGround = false;
	unsigned int	Coins = 0;

	~PlayerChange() = default;
	PlayerChange() = default;
	PlayerChange(const PlayerChange & other) = default;
	PlayerChange & operator=(const PlayerChange & other) = default;

	void	MakeDefault();
	void	Consider(const PlayerChange & other);
};

#endif