#include "ContextBase.hpp"

// ValueType
#include "ValueType/View3D.hpp"
#include "ValueType/LoopI3.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"
#include "PolyHedra/Data.hpp"

#include "PolyHedra/Skin/Skin2DA.hpp"
#include "PolyHedra/Skin/Skin2D_Data.hpp"

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"
#include "Graphics/Multiform/_Include.hpp"

// FileManager
#include "Image.hpp"

// Text
#include "Text/Manager.hpp"
#include "Text/Object.hpp"

// Controls
#include "Control/Base/Manager.hpp"
#include "ControlsInclude.hpp"

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
#include "Voxel/Chunk.hpp"
#include "Voxel/ChunkManager.hpp"
#include "Voxel/ChunkNeighbours.hpp"
#include "Voxel/VoxelOrientation.hpp"
#include "Voxel/VoxelPallet.hpp"
#include "Voxel/ChunkVoxelIndex.hpp"
#include "Voxel/VoxelGeometryPallet.hpp"
#include "Voxel/Structure.hpp"

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

// Telemetry
#include "Telemetry/ThreadInfo.hpp"

// 
#include "PhysicsContext.hpp"
#include "BlockList.hpp"

// Math
#include <thread>



#define DISABLE_INVENTORY
#define DISABLE_VIEW_TANGIBLE
#define DISABLE_VIEW_RAY





#ifndef DISABLE_INVENTORY
struct InventoryShader : public ::PolyHedraFull::Shader
{
	Uniform::DisplaySize		DisplaySize;
	~InventoryShader();
	InventoryShader();
};
#endif





struct ContextNoisePlane : public ContextBase
{
View3D	view;

::PolyHedraManager		PolyHedraManager;
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;
//::PlaneManager			PlaneManager;
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



Perlin2D	Perlin2;
Perlin3D	Perlin3;

Multiform::DisplaySize		Multiform_DisplaySize;
::Multiform::Matrix4x4		Multiform_View;
::Multiform::Depth			Multiform_Depth;
::Multiform::Angle			Multiform_FOV;

~ContextNoisePlane();
ContextNoisePlane();



::PhysicsContext	PhysicsContext;

/* View Update

Input
	regular Axis and EulerAngle
Physics
	ground movement
	ground friction
	air movement
	air friction
	jump
		only on ground
		uneffected by ground friciton
Collision

should movement speed depend on friction or a specified limit ?

allways do air movement/friction ?
you are allways in the air

movement is currently done using friction
it makes sense but also immedeatly cancels out
is that static friction ?
is movement force too weak ?
*/

/* View
	the generic View3D stuff
	Ray
	RayHit ?
	Physics Stuff
	Collision Stuff
*/

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

Ray3D		ViewRay;
AxisRel		ViewRayAxis0;
AxisRel		ViewRayAxis1;
AxisRel		ViewRayAxis2;

VoxelHit	ViewHit;
AxisRel		ViewHitAxis0;
AxisRel		ViewHitAxis1;
#endif

ValueAverager<float>	TimeUpdateView;
ValueAverager<float>	ViewUpdateCollisionTime;
ValueAverager<float>	ViewUpdateChunksTime;
ValueAverager<float>	ViewUpdateRayTime;

void ViewUpdateDone();
#ifndef DISABLE_VIEW_TANGIBLE
void ViewUpdatePhysics(VectorF3 accel);
#endif
void ViewUpdateIntangible(Trans3D change, FrameTime frame_time);
#ifndef DISABLE_VIEW_TANGIBLE
void ViewUpdateColliding(FrameTime frame_time);
#endif
#ifndef DISABLE_VIEW_RAY
void ViewRayUpdate();
#endif
#ifndef DISABLE_VIEW_RAY
void ViewRayDo();
#endif
void ViewUpdateAround(Trans3D change, FrameTime frame_time);






/* Draw Thread should focus on Drawing
	avoid locking
	move View stuff to another Thread ?
	Draw Thread needs to Create/Delete Graphics
	Input from different Thread ?
*/

bool		ThreadIdle = true;
bool		ThreadTerminate = false;

std::thread				AuxThread0;
bool					AuxThread0Idle = false;	// put in ThreadInfo
ValueAverager<float>	AuxThread0Time;			// put in ThreadInfo
void		AuxThread0Func();

std::thread				AuxThread1;
bool					AuxThread1Idle = false;
ValueAverager<float>	AuxThread1Time;
void		AuxThread1Func();

std::thread				AuxThread2;
bool					AuxThread2Idle = false;
ValueAverager<float>	AuxThread2Time;
void		AuxThread2Func();

void DrawThreadUpdate();



PolyHedra *		VoxelCube;
PolyHedra *		VoxelChunkCube;
PolyHedra *		ViewRayPolyHedra;

void Make();




/* why are these here ?
	to access ContextNoisePlane
	just have a Referance/Pointer to ContextNoisePlane ?
	all the Code is in the Header
	split main_.cpp into ContextNoisePlane.hpp and ContextNoisePlane.cpp
*/

void MakeControls();

void DebugMenu_Generation3DComparison(float val);
void DebugMenu_Generation3DFactor(float val);



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



// this is slow ?
ValueAverager<float>	TimeDrawTotal;
ValueAverager<float>	TimeDrawPolyHedra;
ValueAverager<float>	TimeDrawChunk;
ValueAverager<float>	TimeDrawControl;
ValueAverager<float>	TimeMakeText;
ValueAverager<float>	TimeDrawText;

void Draw();

// make Timing stuff static ?
ValueAverager<float>	DLTAverageTime;
ValueAverager<int>		FPSAverageTime;
ValueAverager<float>	TimeFrameTotal;
ValueAverager<float>	FrameInputTime;
ValueAverager<float>	TimeUpdateThread;
#ifndef DISABLE_INVENTORY
ValueAverager<float>	InventoryCursorTime;
#endif

unsigned int			TextCharCount = 0;
ValueAverager<float>	TextAssambleTime;
ValueAverager<float>	TextInstanceTime;

void FrameText(FrameTime frame_time);
#ifndef DISABLE_INVENTORY
void InventoryCursor(FrameTime frame_time);
#endif
// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void FrameInput();;

void Frame(FrameTime frame_time) override;

void Resize(DisplaySize display_size) override;



// make these virtual and put them in Base
void MouseScroll(ScrollArgs args) override;
void MouseClick(ClickArgs args) override;
void MouseDrag(DragArgs args) override;

void KeyBoardKey(KeyArgs args) override;
};
