#include "ContextBase.hpp"

// ValueType
#include "ValueType/View/3D.hpp"
#include "ValueType/Loop/I3.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"

#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Skin/Data.hpp"

// FileManager
#include "Image.hpp"

// UI
#include "UIManager.hpp"
#include "Text/Object.hpp"

// Units
#include "UnitToString.hpp"

// ValueGen
#include "ValueGen/Random.hpp"
#include "ValueGen/Perlin2D.hpp"
#include "ValueGen/Perlin3D.hpp"

// Plane
//#include "Plane/Plane.hpp"
//#include "Plane/PlaneGraphics.hpp"
//#include "Plane/PlaneManager.hpp"

// Voxel
#include "Axis/3D/Orientation.hpp"

#include "3D/Chunk.hpp"
#include "3D/Chunk/Manager.hpp"
#include "3D/Chunk/Neighbours.hpp"

#include "3D/ChunkVoxelIndex.hpp"
#include "3D/VoxelHit.hpp"

#include "3D/Structure.hpp"

#include "BoxEntity3D.hpp"

// Menus
#include "Menus/Main.hpp"
#include "Menus/Pause.hpp"
#include "Menus/Options.hpp"
#include "Menus/Debug.hpp"

// Item
#include "Item/ItemBase.hpp"
#include "Item/ItemTool.hpp"
#include "Item/ItemVoxel.hpp"
#include "Item/ItemContainer.hpp"
#include "Menus/Item/ItemContainerUI.hpp"

// Threads
# include "AuxThread/Collection.hpp"

// 
#include "PhysicsContext.hpp"



// New PolyHedra
# include "NewPolyHedra/Manager.hpp"
# include "NewPolyHedra/PalletManager.hpp"

# include "NewPolyHedra/DataType/Basic3D/Layout.hpp"
# include "NewPolyHedra/DataType/Basic3D/Object.hpp"
# include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"

# include "NewPolyHedraUI.hpp"

// Layout
# include "Layout/Uniform/Light3D.hpp"
# include "Layout/Multiform/Light3D.hpp"

// other
# include "VoxelClear.hpp"

// Light
# include "Light/Manager.hpp"

struct ContextNoisePlane : public ContextBase
{
LayoutMultiformLight3D	LayoutMultiform;



NewPolyHedra::Manager							PolyHedraManager;
NewPolyHedra::PalletManager						PalletManager;
NewPolyHedra::Basic3D::ObjectManager			ObjectManagerBasic;
NewPolyHedra::UserInterface::ObjectManager		ObjectManagerUI;

void	NewPolyHedra_ChangeMedia();



::AuxThreadCollection	AuxThreadCollection;



UI::Manager			UIManager;
//::PlaneManager	PlaneManager;
::ChunkManager		ChunkManager;



::MainMenu		MenuMain;
::PauseMenu		MenuPause;
::OptionsMenu	MenuOptions;
::DebugMenu		MenuDebug;



::ItemContainer		Inventory;
::ItemContainerUI	InventoryUI;
/* HotBar Index
scroll should loop
Slot Indicator
Item Indicator
*/
::ItemContainer		HotBar;
::ItemContainerUI	HotBarUI;

void	MakeControls();



Physics::GravityContext		PhysicsContext_Gravity;
Physics::FluidContext		PhysicsContext_Fluid;
Physics::SurfaceContext		PhysicsContext_Surface;



::VoxelClear	VoxelClear;



~ContextNoisePlane();
ContextNoisePlane();



View3D	View;

float	View_Distance;
bool	View_IsTangible;

float	ViewMove_SpeedSlow;
float	ViewMove_SpeedFast;

float	ViewMove_AccelSlow;
float	ViewMove_AccelFast;
float	ViewMove_Decel;

BoxEntity3D					ViewEntity;
BoxEntity3D_CollisionSide	ViewEntity_CollisionSide;
PolyHedra *					ViewEntity_PolyHedra = nullptr;

RayF3			ViewRay;
Axis3D::Rel		ViewRay_Axis0;
Axis3D::Rel		ViewRay_Axis1;
Axis3D::Rel		ViewRay_Axis2;

VoxelHit		ViewHit;
Axis3D::Rel		ViewHit_Axis0;
Axis3D::Rel		ViewHit_Axis1;

void	ViewEntityUpdate_Intangible(Trans3D change, FrameTime frame_time);
void	ViewEntityUpdate_Physics(VectorF3 change, FrameTime frame_time);
void	ViewEntityUpdate_Colliding(FrameTime frame_time);
void	ViewEntityUpdate_Done();
void	ViewEntityUpdate(Trans3D change, FrameTime frame_time);

void	ViewRayUpdate_Sync();
void	ViewRayUpdate_Hit();
void	ViewRayUpdate_HitDo();
void	ViewRayUpdate_Show();
void	ViewRayUpdate();

void	ViewUpdate(Trans3D change, FrameTime frame_time);



static GL::BlockBinding		LightBufferBinding;
::LightManager				LightManager;
Buffer::Uniform				LightBuffer;



PolyHedra *		VoxelCube; // put this in PolyHedra Geometry Pallet
PolyHedra *		VoxelChunkCube;

void	MakeVoxels();

void	Make();



// hardcode Shaders into Managers
// hardcode Attributes into Managers
// "Template" for Attributes in Managers with InstanceManagers
// also organize Shader Files
//
// a lot of the managers are siminal with the bool flags and function names
// make a Base ? to organize
void	ChangeMedia();

// Valgrind is very slow here ?
void	GraphicsCreate();
void	GraphicsDelete();

void	Init() override;
void	Free() override;



void	Draw();



void	FrameText(FrameTime frame_time);
void	InventoryCursor(FrameTime frame_time);
void	FrameInput();

void	Frame(FrameTime frame_time) override;
void	Resize(DisplaySize display_size) override;



void	MouseMove(MoveArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseScroll(ScrollArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
void	KeyBoardText(TextArgs args) override;
};
