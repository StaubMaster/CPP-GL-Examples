#ifndef  CONTEXT_HPP
# define CONTEXT_HPP

class Window;
struct FrameTime;
struct DisplaySize;

# include "DirectoryInfo.hpp"

# include "ValueType/View/3D.hpp"
# include "ValueType/Matrix/4x4.hpp"

# include "Layout/Multiform.hpp"

# include "NewPolyHedra/Manager.hpp"
# include "NewPolyHedra/PalletManager.hpp"

# include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"

# include "Generics/Container/Array.hpp"

struct TilePallet;
struct TileObject;
# include "Tile/PalletDisplayOptions.hpp"

# include "Player.hpp"
# include "PlayerChange.hpp"

# include "UIText/Manager.hpp"

struct Context
{
	::Window &			Window;
	::DirectoryInfo		MediaDirectory;

	View3D		View;
	Matrix4x4	ViewMatrix;
	void	ViewDefault();
	void	ViewChange(FrameTime frame_time);

	NewPolyHedra::Manager		NewPolyHedra_Manager;
	NewPolyHedra::PalletManager		PalletManager;
	NewPolyHedra::Basic3D::ObjectManager	ObjectManagerBasic;
	void	NewPolyHedra_Create();
	void	NewPolyHedra_Delete();

	UI::Text::Manager	TextManager;

	::MultiformLayout	MultiformLayout;

	bool	IsPaused = true;
	bool	IsDead = false;

	::Player		Player;

	void	TileFeaturesInit();

	// Pallets should have a Weight (for Random)
	TilePallet *					TileStart;
	Container::Array<TilePallet*>	TilePallets;
	void	TilePalletsInit();
	void	TilePalletsFree();

	TileObject *	TileNewRandom();

	void	TileNewRandomExit(TileObject * tile, unsigned int layers);

	TileObject *	CurrentTile = nullptr;
	::TilePalletDisplayOptions	TilePalletDisplayOptions;

	void	TileInit();
	void	TileFree();

	void	TileIterate();
	void	TileDisplay();



	//void	GraphicsDefine();
	//void	GraphicsChangeMedia();
	//void	GraphicsCreate();
	//void	GraphicsDelete();
	//void	GraphicsInit();

	~Context();
	Context(::Window & window);

	void	Draw();

	void	Frame(FrameTime frame_time);
	void	Resize(DisplaySize display_size);
};

#endif