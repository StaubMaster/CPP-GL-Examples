#include "ContextBase.hpp"

// ValueType
#include "ValueType/View/3D.hpp"
#include "ValueType/Loop/I3.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
//#include "PolyHedra/Manager.hpp"
//#include "PolyHedra/Object.hpp"
//#include "PolyHedra/Data.hpp"
#include "PolyHedra/Graphics/Full/Main/Layout.hpp"
#include "PolyHedra/Graphics/Wire/Main/Layout.hpp"

#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Skin/Data.hpp"

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Generics/Container/Array.hpp"
#include "Graphics/Multiform/_Include.hpp"

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
#include "Voxel/GeometryPallet.hpp"

#include "ChunkVoxelIndex.hpp"
#include "VoxelHit.hpp"

#include "Structure.hpp"

#include "BoxEntity.hpp"

// Menus
#include "Menus/Main.hpp"
#include "Menus/Pause.hpp"
#include "Menus/Options.hpp"
#include "Menus/Debug.hpp"

// Item
#include "Item/ItemBase.hpp"
#include "Item/ItemVoxel.hpp"
#include "Item/ItemContainer.hpp"
#include "Menus/Item/Inventory.hpp"

// Threads
#include "AuxThreadBase.hpp"

// 
#include "PhysicsContext.hpp"

// Math
#include <thread>



#define DISABLE_INVENTORY
//#define DISABLE_VIEW_TANGIBLE
//#define DISABLE_VIEW_RAY





# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"
class ShaderLayoutView3D : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;
	Uniform::Matrix4x4			View;
	Uniform::Depth				Depth;
	Uniform::Angle				FOV;
	public:
	~ShaderLayoutView3D();
	ShaderLayoutView3D();
};


#ifndef DISABLE_INVENTORY
struct InventoryShader : public ::PolyHedraFull::Shader
{
	Uniform::DisplaySize		DisplaySize;
	~InventoryShader();
	InventoryShader();
};
#endif



// New PolyHedra
# include "NewPolyHedra/Manager.hpp"
# include "NewPolyHedra/PalletManager.hpp"

# include "NewPolyHedra/DataType/Basic3D/Layout.hpp"
# include "NewPolyHedra/DataType/Basic3D/Object.hpp"
# include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"



struct ContextNoisePlane : public ContextBase
{
NewPolyHedra::Manager	PolyHedraManager;

::PolyHedraFull::Main::Layout	PalletManager_BufferFullLayout; // put these directly in PalletManager ?
::PolyHedraWire::Main::Layout	PalletManager_BufferWireLayout;
NewPolyHedra::PalletManager		PalletManager;

ShaderLayoutView3D						ObjectManagerBasic_ShaderFullLayout;
ShaderLayoutView3D						ObjectManagerBasic_ShaderWireLayout;
NewPolyHedra::Basic3D::BufferLayout		ObjectManagerBasic_BufferFullLayout;
NewPolyHedra::Basic3D::BufferLayout		ObjectManagerBasic_BufferWireLayout;
NewPolyHedra::Basic3D::ObjectManager	ObjectManagerBasic;

//::PolyHedraManager		PolyHedraManager;
UI::Manager				UIManager;
//::PlaneManager		PlaneManager;
::ChunkManager			ChunkManager;

#ifndef DISABLE_INVENTORY
::PolyHedraManager		InventoryPolyHedraManager;
::InventoryShader		InventoryShader;
#endif



::MainMenu		MainMenu;
::PauseMenu		PauseMenu;
::OptionsMenu	OptionsMenu;
::DebugMenu		DebugMenu;

#ifndef DISABLE_INVENTORY
::ItemContainer		Inventory;
::ItemContainer		HotBar;

::Inventory			InventoryUI;
::Inventory			HotBarUI;
#endif



// make a Layout for Multiforms
// it takes an array of shaders
// or singular shaders, one a fter another
// and tries to get the names
Multiform::DisplaySize		Multiform_DisplaySize;
::Multiform::Matrix4x4		Multiform_View;
::Multiform::Depth			Multiform_Depth;
::Multiform::Angle			Multiform_FOV;

~ContextNoisePlane();
ContextNoisePlane();



::PhysicsContext	PhysicsContext;

View3D	view;

#ifndef DISABLE_VIEW_TANGIBLE
float	ViewDistance = 0.0f;
bool	ViewTangible = false;

float	ViewSpeed = 0.1f;	// force when moving
float	ViewFaster = 3.0f;	// force multiplier when moving faster

BoxEntity		ViewEntity;
CollisionSide	ViewCollisionSide;
#endif

float	ViewSpeedNoClip = 10.0f;
float	ViewFasterNoClip = 10.0f;

#ifndef DISABLE_VIEW_RAY
bool		ViewRaySync = true;

RayF3		ViewRay;
AxisRel		ViewRayAxis0;
AxisRel		ViewRayAxis1;
AxisRel		ViewRayAxis2;

VoxelHit	ViewHit;
AxisRel		ViewHitAxis0;
AxisRel		ViewHitAxis1;
#endif

void ViewUpdateDone();
void ViewUpdateIntangible(Trans3D change, FrameTime frame_time);
#ifndef DISABLE_VIEW_TANGIBLE
void ViewUpdatePhysics(VectorF3 accel);
void ViewUpdateColliding(FrameTime frame_time);
#endif
#ifndef DISABLE_VIEW_RAY
void ViewRayUpdate();
void ViewRayInfo();
void ViewRayDo();
#endif
void ViewUpdateAround(Trans3D change, FrameTime frame_time);



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
#ifndef DISABLE_INVENTORY
void InventoryCursor(FrameTime frame_time);
#endif
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
