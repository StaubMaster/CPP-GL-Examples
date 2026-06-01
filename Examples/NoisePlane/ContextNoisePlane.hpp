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
#include "Voxel/AxisOrientation.hpp"
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

// Threads
#include "Telemetry/AuxThreadBase.hpp"
#include "AuxThread1.hpp"

// 
#include "PhysicsContext.hpp"

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



/* organize
UI stuff
View stuff
	move / ray / collide
Voxel stuff
*/

/* PolyHedra Manager
store ObjectDatas in InstanceManagers ?
use DefaultVisibility properly

have a way to have multiple PolyHedra Managers
seperate based on Instance Data

template would mean putting everything into Header
generalize so lots of stuff can be put into Code files
*/

/* User Interface
the Menus have referances to Context to change stuff
Menus could easitly be moved somewhere else
they are already self contained

make UI Manager "constant"
so like Window, it stays during Context change
Clear on context change ?
should be cleared by Contexts

Loading stuff ?
this would require WindowFrameLoop to allways be active
this also means that Init and Free happen independently of WindowFrameLoop

so this would require change Window internals
probably just make FrameLoop to be independant of Window

Frequency/Intervals should be done with sleep
checking Time is busy waiting

just make a Ticker
that calls a function
this probably exists already

keep FrameLoop in window
remove Init and Free

Resize ?
UI wants Callback
but others also want Callback

inheriting and then call the Base first
Callback is done using Functino Pointer
make a Function Chain
that holds a linked list of Function Pointers
and calls all of them with Parameters
will also need to remove from List
*/

/* how to keep Loading Display seperate ?
Init/Free and such need to not be done on the DrawThread
this should be all fine
apart from Creating Graphics
use async/promise/... for this stuff ?

give Window seperate Loops for Frame and Update
put Update onto different Thread
make Update Thread outside for now
*/

/* Input from different Threads
the KeyStates are stored in an Array
this is safe to access from any thread
except when it changes

it is only changed from one place
and changing does not change Memory Location
this does not mean it is safe, but it should not cause any segfaults
just put a mutex in it that locks in operator[] and when changing
*/

struct ContextNoisePlane : public ContextBase
{
::PolyHedraManager		PolyHedraManager;
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;
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

/* View
	the generic View3D stuff
	Ray
	RayHit ?
	Physics Stuff
	Collision Stuff
*/

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

Ray3D		ViewRay;
AxisRel		ViewRayAxis0;
AxisRel		ViewRayAxis1;
AxisRel		ViewRayAxis2;

VoxelHit	ViewHit;
AxisRel		ViewHitAxis0;
AxisRel		ViewHitAxis1;
#endif

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



::LightBase		LightAmbient;
::LightSolar	LightSolar;
::LightSpot		LightSpot;



/* Draw Thread should focus on Drawing
	avoid locking
	move View stuff to another Thread ?
	Draw Thread needs to Create/Delete Graphics
	Input from different Thread ?
*/

std::thread				AuxThread0;
bool					AuxThread0Term = true;
bool					AuxThread0Idle = false;
ValueAverager<float>	AuxThread0Time;
void					AuxThread0Func();



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



// make these virtual and put them in Base
void MouseScroll(ScrollArgs args) override;
void MouseClick(ClickArgs args) override;
void MouseDrag(DragArgs args) override;

void KeyBoardKey(KeyArgs args) override;
};
