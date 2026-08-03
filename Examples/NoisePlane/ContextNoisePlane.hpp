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
#include "Axis/Orientation.hpp"

#include "Chunk.hpp"
#include "Chunk/Manager.hpp"
#include "Chunk/Neighbours.hpp"

#include "Voxel/Pallet.hpp"
#include "Voxel/PalletMap.hpp"
#include "Voxel/PalletGeometry.hpp"

#include "ChunkVoxelIndex.hpp"
#include "VoxelHit.hpp"

#include "Structure.hpp"

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
#include "AuxThreadBase.hpp"
#include <thread>

// 
#include "PhysicsContext.hpp"



// New PolyHedra
# include "NewPolyHedra/Manager.hpp"
# include "NewPolyHedra/PalletManager.hpp"

# include "NewPolyHedra/DataType/Basic3D/Layout.hpp"
# include "NewPolyHedra/DataType/Basic3D/Object.hpp"
# include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"

# include "NewPolyHedraUI.hpp"

// Graphics
# include "ShaderLayouts.hpp"
# include "MultiformLayouts.hpp"



struct ContextNoisePlane : public ContextBase
{
MultiformLayoutView3D	MultiformLayout;

NewPolyHedra::Manager	PolyHedraManager;
NewPolyHedra::PalletManager		PalletManager;
NewPolyHedra::Basic3D::ObjectManager	ObjectManagerBasic;
NewPolyHedra::UserInterface::ObjectManager		ObjectManagerUI;

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



Physics::GravityContext		PhysicsContext_Gravity;
Physics::FluidContext		PhysicsContext_Fluid;
Physics::SurfaceContext		PhysicsContext_Surface;



~ContextNoisePlane();
ContextNoisePlane();



View3D	View;
float	View_Distance = 0.0f;
float	View_MoveSpeed = 10.0f;
float	View_MoveSpeedMultiplier = 10.0f;
bool	View_IsTangible = false;

BoxEntity3D					ViewEntity;
BoxEntity3D_CollisionSide	ViewEntity_CollisionSide;
PolyHedra *					ViewEntity_PolyHedra = nullptr;
float						ViewEntity_MoveChange = 0.1f;
float						ViewEntity_MoveLimitSlow = 5.0f;
float						ViewEntity_MoveLimitFast = 10.0f;

RayF3		ViewRay;
AxisRel		ViewRay_Axis0;
AxisRel		ViewRay_Axis1;
AxisRel		ViewRay_Axis2;

VoxelHit	ViewHit;
AxisRel		ViewHit_Axis0;
AxisRel		ViewHit_Axis1;

// VoxelClear
unsigned int			VoxelClear_Progress = 0xFFFFFFFF;
unsigned int			VoxelClear_Required = 64;
ChunkVoxelIndex			VoxelClear_Index;
const VoxelPallet *		VoxelClear_Pallet = nullptr;
const ItemTool *		VoxelClear_Tool = nullptr;

bool	VoxelClear_Is() const;
void	VoxelClear_None();
void	VoxelClear_Clear(ChunkVoxelIndex idx);
void	VoxelClear_Continue(const ChunkVoxelIndex & other);
void	VoxelClear_Show(std::stringstream & ss) const;

void	ViewUpdate_Done();
void	ViewUpdate_Intangible(Trans3D change, FrameTime frame_time);
void	ViewUpdate_Physics(VectorF3 change);
void	ViewUpdate_Colliding(FrameTime frame_time);

void	ViewRay_Update();
void	ViewRay_Hit();
void	ViewRay_HitDo();
void	ViewRay_Show();

void	ViewUpdate(Trans3D change, FrameTime frame_time);



::LightBase			LightAmbient;
::LightDirection	LightSolar;
::LightSpot			LightSpot;



/* Draw Thread should focus on Drawing
	avoid locking
	move View stuff to another Thread ?
	Draw Thread needs to Create/Delete Graphics
	Input from different Thread ?
*/

std::thread					AuxThread0;
bool						AuxThread0Term = false;
bool						AuxThread0Idle = true;
ValueAccumulator<float>		AuxThread0Time;
void						AuxThread0Func();



PolyHedra *		VoxelCube; // put this in PolyHedra Geometry Pallet
PolyHedra *		VoxelChunkCube;

void Make();



/* why are these here ?
	to access ContextNoisePlane
	just have a Referance/Pointer to ContextNoisePlane ?
	all the Code is in the Header
	split main_.cpp into ContextNoisePlane.hpp and ContextNoisePlane.cpp
*/

void MakeControls();



// hardcode Shaders into Managers
// hardcode Attributes into Managers
// "Template" for Attributes in Managers with InstanceManagers
// also organize Shader Files
//
// a lot of the managers are siminal with the bool flags and function names
// make a Base ? to organize
void ChangeMedia();

// Valgrind is very slow here ?
void GraphicsCreate();
void GraphicsDelete();

void Init() override;
void Free() override;



void Draw();



void FrameText(FrameTime frame_time);
void InventoryCursor(FrameTime frame_time);
// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void FrameInput();;

void Frame(FrameTime frame_time) override;
void Resize(DisplaySize display_size) override;



void	MouseMove(MoveArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseScroll(ScrollArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
void	KeyBoardText(TextArgs args) override;
};
