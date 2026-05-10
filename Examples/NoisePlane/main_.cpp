#include "new.hpp"

// Debug
#include <iostream>
#include <sstream>
#include "Debug.hpp"
#include "ValueType/_Show.hpp"
#include "ValueType/_Include.hpp"

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
#include "Voxel/VoxelOrientation.hpp"
#include "Voxel/VoxelPallet.hpp"
#include "Voxel/ChunkVoxelIndex.hpp"
#include "Voxel/VoxelGeometryPallet.hpp"

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

// Math
#include <math.h>

#include "BlockList.hpp"

#include <thread>
#include <mutex>



struct InventoryShader : public ::PolyHedraFull::Shader
{
	Uniform::DisplaySize		DisplaySize;
	~InventoryShader()
	{ }
	InventoryShader()
		: ::PolyHedraFull::Shader()
		, DisplaySize(*this, "DisplaySize")
	{ }
};

struct PhysicsContext
{
	VectorF3	GravityDirection = VectorF3(0.0f, -1.0f, 0.0f);
	float		GravityAcl = 1.0f;

	VectorF3	CalcGravityVec() const
	{
		return GravityDirection * GravityAcl;
	}



	float	DragFluidDensity = 0.001f;
	float	DragCoefficient = 1.0f;

	float	CalcDragLimit(float mass, float area, float accel) const
	{
		return sqrt((2 * mass * accel) / (DragFluidDensity * area * DragCoefficient));
	}
	float	CalcTerminalVel(float mass, float area) const
	{
		return CalcDragLimit(mass, area, GravityAcl);
	}

	float		CalcDrag(float vel, float mass, float area) const
	{
		float force = 0.5f * DragFluidDensity * vel * vel * area * DragCoefficient;
		return force / mass;
	}
	VectorF3	CalcDragVec(VectorF3 vel, float mass, float area) const
	{
		float vel_len;
		vel = vel.normalize(vel_len);
		return vel * CalcDrag(vel_len, mass, area);
	}

/*
	uk: Kinetic Friciton Coefficient
	Fk: Kinetic Friciton
	Fn: Normal Force

	Fk = uk * Fn

	N: Normal Force
	mg: Weight (Mass * Gravity)

	P: External Force
	Py: "downward Component of External Force" (parallel to Normal Force ?)
	Px: horisontal Component of External Force (perpendicular to Normal Force ?)

	N = mg + Py

	Ff: Friciton Force
	Ff = -Px (not sliding)
	Ff = u * N (sliding)
*/
	// static Friction
	float	FrictionCoefficient = 0.5f; // kinetic Friction
	float		CalcFriction(float mass) const
	{
		float normal = mass * GravityAcl;
		return FrictionCoefficient * normal;
	}
	VectorF3	CalcFriction(VectorF3 force, float friction_force) const
	{
		float    force_length;
		VectorF3 force_normal = force.normalize(force_length);
		if (friction_force > force_length)
		{
			return force;
		}
		else
		{
			return force_normal * friction_force;
		}
	}

	VectorF3	CalculateVel(VectorF3 vel, float mass, float area) const
	{
		return CalcGravityVec() - CalcDragVec(vel, mass, area);
	}
};

/* this File is too big. organize
	View
	UI
	Threads
	PolyHedra
	static stuff
*/

#include "main_static.cpp"

struct ContextNoisePlane : public ContextBase
{
View3D	view;

::PolyHedraManager		PolyHedraManager;
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;
//::PlaneManager			PlaneManager;
::ChunkManager			ChunkManager;

::PolyHedraManager		InventoryPolyHedraManager;
::InventoryShader		InventoryShader;



::MainMenu		MainMenu;
::PauseMenu		PauseMenu;
::OptionsMenu	OptionsMenu;
::DebugMenu		DebugMenu;

::ItemContainer		Inventory;
::ItemContainer		HotBar;

::Inventory			InventoryUI;
::Inventory			HotBarUI;



Perlin2D	Perlin2;
Perlin3D	Perlin3;

Multiform::DisplaySize		Multiform_DisplaySize;
::Multiform::Matrix4x4		Multiform_View;
::Multiform::Depth			Multiform_Depth;
::Multiform::Angle			Multiform_FOV;

~ContextNoisePlane()
{ }
ContextNoisePlane()
	: ContextBase()
	, view()
	, PolyHedraManager()
	, ControlManager()
	, TextManager()
//	, PlaneManager()
	, ChunkManager()
	, MainMenu()
	, PauseMenu()
	, OptionsMenu()
	, DebugMenu()
	, Inventory(VectorU2(10, 5))
	, HotBar(VectorU2(10, 1))
	, InventoryUI()
	, HotBarUI()
	, Perlin2(Perlin2D::Random(VectorU2(8, 8)))
	, Perlin3(Perlin3D::Random(VectorU3(8, 8, 8)))
	, Multiform_DisplaySize("DisplaySize")
	, Multiform_View("View")
	, Multiform_Depth("Depth")
	, Multiform_FOV("FOV")
	, AuxThread0(&ContextNoisePlane::AuxThread0Func, this)
	, AuxThread0Time(64)
	, AuxThread1(&ContextNoisePlane::AuxThread1Func, this)
	, AuxThread1Time(64)
	, TimeDLTAverage(64)
	, TimeFPSAverage(64)
	, FrameDuration(64)
{
	PolyHedraManager.MakeCurrent();
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
	Container::Array<Shader::Base*> shaders({
		&PolyHedraManager.ShaderFullDefault,
		&PolyHedraManager.ShaderWireDefault,
		&ControlManager.Shader,
		&TextManager.Shader,
//		&PlaneManager.Shader,
		&ChunkManager.Shader,
		&InventoryShader,
	});
	Multiform_DisplaySize.FindUniforms(shaders);
	Multiform_View.FindUniforms(shaders);
	Multiform_Depth.FindUniforms(shaders);
	Multiform_FOV.FindUniforms(shaders);
}



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

float	ViewDistance = 0.0f;
bool	ViewTangible = false;

float	ViewSpeed = 0.1f;	// force when moving
float	ViewFaster = 3.0f;	// force multiplier when moving faster

float	ViewSpeedNoClip = 10.0f;
float	ViewFasterNoClip = 10.0f;

BoxEntity		ViewEntity;
CollisionSide	ViewCollisionSide;

bool		ViewRaySync = true;

Ray3D		ViewRay;
AxisRel		ViewRayAxis0;
AxisRel		ViewRayAxis1;
AxisRel		ViewRayAxis2;

VoxelHit	ViewHit;
AxisRel		ViewHitAxis0;
AxisRel		ViewHitAxis1;

void ViewUpdateDone()
{
	if (ViewDistance == 0.0f)
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(view.Trans));
	}
	else
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(
			Trans3D(view.Trans.Position - view.Trans.Rotation.forward(VectorF3(0, 0, ViewDistance)), view.Trans.Rotation)
		));
	}
}
void ViewUpdatePhysics(VectorF3 accel)
{
	VectorF3 decel;

	// Physics stuff
	float jump = 0.0f;
	if (ViewCollisionSide.PrevY && accel.Y > 0.0f) { jump = 15.0f; }
	accel.Y = 0.0f;

	if (ViewCollisionSide.PrevY)
	{
		accel *= ViewSpeed;
		// find this earlier, pass a bool
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { accel *= ViewFaster; }

		{
			float dot = VectorF3::dot(decel, accel);
			//if (dot < 0.0f)
			//if (dot != 0.0f)
			if (accel.length2() != 0.0f)
			{
				decel = decel - (accel * (dot / accel.length2()));
			}
			else
			{
				decel = ViewEntity.Vel;
			}
		}

		float friction_force = PhysicsContext.CalcFriction(1.0f);
		accel = PhysicsContext.CalcFriction(accel * 1.0f, friction_force) / 1.0f;
		decel = PhysicsContext.CalcFriction(decel * 1.0f, friction_force) / 1.0f;
	}
	else
	{
		// use air friciton for movement
		accel.Y = 0.0f;
		accel *= 0.1f;
	}

	if (ViewCollisionSide.PrevY) { accel.Y = jump; }

	ViewEntity.Vel += PhysicsContext.CalculateVel(ViewEntity.Vel, 1.0f, 1.0f) + accel - decel;
}
void ViewUpdateIntangible(Trans3D change, FrameTime frame_time)
{
	change.Position *= ViewSpeedNoClip;
	if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { change.Position *= ViewFasterNoClip; }
	ViewEntity.Vel = change.Position;
	ViewEntity.Pos += ViewEntity.Vel * frame_time.Delta;
	view.Trans.Position = ViewEntity.Pos;
	view.Trans.Rotation += change.Rotation * frame_time.Delta;
	view.Trans.Rotation.X1.clampPI();
}
void ViewUpdateColliding(FrameTime frame_time)
{
	DisplayBoxEntityVoxels(PolyHedraManager.FindPolyHedra(VoxelCube), ChunkManager, ViewEntity, frame_time);
	DisplayBoxEntity(ViewEntity);
	ViewCollisionSide = ViewEntity.Collide(ChunkManager, frame_time);
	DisplayBoxEntity(ViewEntity);
}
void ViewRayUpdate()
{
	if (ViewRaySync)
	{
		ViewRay.Pos = view.Trans.Position;
		ViewRay.Dir = view.Trans.Rotation.forward(VectorF3(0, 0, 1));
		{
			VectorI3 ranks = ViewRay.Dir.abs().RankDimensions();
			     if (ranks.X == 0) { if (ViewRay.Dir.X > 0) { ViewRayAxis0 = AxisRel::NextX; } else { ViewRayAxis0 = AxisRel::PrevX; } }
			else if (ranks.Y == 0) { if (ViewRay.Dir.Y > 0) { ViewRayAxis0 = AxisRel::NextY; } else { ViewRayAxis0 = AxisRel::PrevY; } }
			else if (ranks.Z == 0) { if (ViewRay.Dir.Z > 0) { ViewRayAxis0 = AxisRel::NextZ; } else { ViewRayAxis0 = AxisRel::PrevZ; } }
			if      (ranks.X == 1) { if (ViewRay.Dir.X > 0) { ViewRayAxis1 = AxisRel::NextX; } else { ViewRayAxis1 = AxisRel::PrevX; } }
			else if (ranks.Y == 1) { if (ViewRay.Dir.Y > 0) { ViewRayAxis1 = AxisRel::NextY; } else { ViewRayAxis1 = AxisRel::PrevY; } }
			else if (ranks.Z == 1) { if (ViewRay.Dir.Z > 0) { ViewRayAxis1 = AxisRel::NextZ; } else { ViewRayAxis1 = AxisRel::PrevZ; } }
			if      (ranks.X == 2) { if (ViewRay.Dir.X > 0) { ViewRayAxis2 = AxisRel::NextX; } else { ViewRayAxis2 = AxisRel::PrevX; } }
			else if (ranks.Y == 2) { if (ViewRay.Dir.Y > 0) { ViewRayAxis2 = AxisRel::NextY; } else { ViewRayAxis2 = AxisRel::PrevY; } }
			else if (ranks.Z == 2) { if (ViewRay.Dir.Z > 0) { ViewRayAxis2 = AxisRel::NextZ; } else { ViewRayAxis2 = AxisRel::PrevZ; } }
			// what if same ranks ?
		}
	}

	ViewHit = ChunkManager.HitVoxel(ViewRay);
	if (ViewHit.Valid())
	{
		{
			PolyHedraObject voxel_box_obj(VoxelCube);
			//voxel_box_obj.Trans().Position = idx;
			voxel_box_obj.Trans().Position = ViewHit.Index;
			voxel_box_obj.ShowWire();
		}
		{
			ViewHitAxis0 = ViewHit.Side;
			AxisAbs axis = AxisRelToAxisAbs(ViewHitAxis0);
			if (axis == AxisAbs::None) { ViewHitAxis1 = AxisRel::None; }
			else if (axis != AxisRelToAxisAbs(ViewRayAxis2)) { ViewHitAxis1 = ViewRayAxis2; }
			else if (axis != AxisRelToAxisAbs(ViewRayAxis1)) { ViewHitAxis1 = ViewRayAxis1; }
			else if (axis != AxisRelToAxisAbs(ViewRayAxis0)) { ViewHitAxis1 = ViewRayAxis0; }
			else { ViewHitAxis1 = AxisRel::None; }
		}
	}
}
void ViewRayDo()
{
	if (PauseMenu.IsInteractible() || OptionsMenu.IsInteractible() || InventoryUI.IsInteractible()) { return; }
	// check if any Control is being hovered
	// cast Ray at mouse

	std::stringstream ss;
	{
		ss << "ViewRay\n";
		ss << ViewRayAxis0 << " :Look0\n";
		ss << ViewRayAxis1 << " :Look1\n";
		ss << ViewRayAxis2 << " :Look2\n";
	}

	if (ViewHit.Valid())
	{
//		std::cout << "main:" << __LINE__ << '\n';
//		std::cout << "main:" << __LINE__ << '\n';
		// Hit Indicator
		/*{
			PolyHedraObject voxel_dir_obj(ViewRayPolyHedra);
			voxel_dir_obj.Trans().Position = hit.Pos;
			voxel_dir_obj.Trans().Rotation = EulerAngle3D::PointToZ(hit.Dir);
			voxel_dir_obj.ShowWire();
		}*/

//		std::cout << "main:" << __LINE__ << '\n';
		// Side: make part of VoxelHit ?
		// determine place_axis_1 based on where on the face was clicked ?
		// top of face orients to point to top and so on

//		std::cout << "main:" << __LINE__ << '\n';
		// Text
		/*{
			VoxelIndex idx = ChunkManager.FindVoxelIndex(hit.Index);
			ss << hit.Index << '\n';
			ss << idx.Chunk << '\n';
			ss << idx.Voxel << '\n';
			ss << place_axis_0 << " :Place0\n";
			ss << place_axis_1 << " :Place1\n";

			// Voxel Info
			{
				const Voxel * voxel = ChunkManager.FindVoxelOrNull(hit.Index);
				if (voxel != nullptr)
				{
					ss << (voxel -> Orientation.GetDiag()) << " :Diag\n";
					ss << (voxel -> Orientation.GetFlip()) << " :Flip\n";
				}
				else
				{
					ss << "null";
				}
				ss << '\n';
			}
		}*/

//		std::cout << "main:" << __LINE__ << '\n';
		if (window.MouseManager[MouseButtons::MouseL].State == State::Press)
		{
			Voxel voxel;
			ChunkVoxelIndex idx(ViewHit.Index);
			//ChunkManager.ClearVoxel(hit.Index, voxel);
//			std::cout << "main:" << __LINE__ << '\n';
			Chunk * chunk = ChunkManager.FindLockOrNull(idx.Chunk);
//			std::cout << "main:" << __LINE__ << '\n';
			if (chunk != nullptr)
			{
//				std::cout << "main:" << __LINE__ << '\n';
				chunk -> ClearVoxel(idx.Voxel, voxel);
//				std::cout << "main:" << __LINE__ << '\n';
				chunk -> unlock();
//				std::cout << "main:" << __LINE__ << '\n';
			}
		}
		if (window.MouseManager[MouseButtons::MouseR].State == State::Press)
		{
			if (ViewHitAxis0 == AxisRel::NextX) { ViewHit.Index.X += 1; }
			if (ViewHitAxis0 == AxisRel::NextY) { ViewHit.Index.Y += 1; }
			if (ViewHitAxis0 == AxisRel::NextZ) { ViewHit.Index.Z += 1; }
			if (ViewHitAxis0 == AxisRel::PrevX) { ViewHit.Index.X -= 1; }
			if (ViewHitAxis0 == AxisRel::PrevY) { ViewHit.Index.Y -= 1; }
			if (ViewHitAxis0 == AxisRel::PrevZ) { ViewHit.Index.Z -= 1; }

			if (HotBar[VectorU2(0, 0)] != nullptr)
			{
				ItemVoxel * item = (ItemVoxel*)HotBar[VectorU2(0, 0)];
				if (item -> VoxelPallet != nullptr)
				{
					Voxel voxel = item -> VoxelPallet -> ToVoxel(ViewHitAxis0, ViewHitAxis1);
					ChunkVoxelIndex idx(ViewHit.Index);
					Chunk * chunk = ChunkManager.FindLockOrNull(idx.Chunk);
					if (chunk != nullptr)
					{
						chunk -> PlaceVoxel(idx.Voxel, voxel);
						chunk -> unlock();
					}
				}
			}
		}
//		std::cout << "main:" << __LINE__ << '\n';
	}

	{
		UI::Text::Object text; text.Create();
		text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
		text.AlignTopRight(); // take DisplaySize
		text.Bound().Min = VectorF2();
		text.Bound().Max = window.Size.Buffer.Full;
		text.String() = ss.str();
		text.Color() = ColorF4(1, 1, 1);
	}

	/*if (window.KeyBoardManager[Keys::NumPadEnter].State == State::Press)
	{
		// make a struct for VoxelIndex
		// struct VoxelIndexAbs; VectorI3
		// struct VoxelIndexRel; VectorI3 and VectorU3
		// ChunkManager can convert between them
		Chunk * view_chunk = ChunkManager.FindChunkOrNull((view.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF());
		if (view_chunk != nullptr)
		{
			view_chunk -> TestOrientation();
		}
	}*/
}
void ViewUpdateAround(Trans3D change, FrameTime frame_time)
{
	StopWatch sw;
	sw.Start();

	if (ViewTangible)
	{
		ViewUpdatePhysics(change.Position);
		view.Trans.Rotation += change.Rotation * frame_time.Delta;
		view.Trans.Rotation.X1.clampPI();
		ViewUpdateColliding(frame_time);
		view.Trans.Position = ViewEntity.Pos;
	}
	else
	{
		ViewUpdateIntangible(change, frame_time);
	}
	ViewUpdateDone();

	ChunkManager.GraphicsUpdate();
	ChunkManager.ChangeCenter((view.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF());

	ViewRayUpdate();
	ViewRayDo();

	sw.Stop();
	FrameDuration.NewValue(sw.ElapsedTime());
}





bool		ThreadDelay = true;
bool		ThreadTerminate = false;
std::thread				AuxThread0;
ValueAverager<float>	AuxThread0Time;
void		AuxThread0Func()
{
	while (ThreadDelay) { }
	StopWatch sw;
	while (!ThreadTerminate)
	{
		sw.ReStart();
		if (!DontRemove) { ChunkManager.RemoveAround(view.Trans.Position, ChunkRemoveRange); }
		if (!DontInsert) { ChunkManager.InsertAround(view.Trans.Position, ChunkInsertRange); }
		ChunkManager.UpdateChunksContainer();
		sw.Stop();
		AuxThread0Time.NewValue(sw.ElapsedTime());
	}
}
std::thread				AuxThread1;
ValueAverager<float>	AuxThread1Time;
void		AuxThread1Func()
{
	while (ThreadDelay) { }
	StopWatch sw;
	while (!ThreadTerminate)
	{
		sw.ReStart();
		if (!DontGenerate) { ChunkManager.GenerateAround(view.Trans.Position, ChunkInsertRange, Perlin2, Perlin3); }
		if (!DontBuffer) { ChunkManager.GraphicsUpdateDataAround(view.Trans.Position); }
		sw.Stop();
		AuxThread1Time.NewValue(sw.ElapsedTime());
	}
}
/*	Threads
Insert/Remove Chunks
	this changes the Chunks Container
	make sure the Chunks Container isnt accessed / looped
	Chunks are Pointers, so accessing individual Chunks is fine ?
	when deleting a Chunks, make sure it is not currently being accessed
	what if a Chunks is returnd and then gets deleted ?
		when something is being done with the Chunk, it should be marked as in use
	Chunks dont need to be removed after deleting
		just make null
	Inserting Chunks could be put into temporary Storage
		when Chunks Container is busy

MainData
this reads ChunkData and changes ChunkMainData
	lock the Chunk
		do the thing
	unlock the Chunk
Outside
	Lock whenever Chunk is changed ?
*/



PolyHedra *		VoxelCube;
PolyHedra *		VoxelChunkCube;
PolyHedra *		ViewRayPolyHedra;

void Make()
{
	view.Trans.Position = VectorF3(0.5f, 0.5f, 0.5f);
	ViewEntity.Pos = VectorF3(0.5f, 0.5f, 0.5f);
	ViewEntity.Box = BoxF3(
		VectorF3(-0.4f, -1.7f, -0.4f),
		VectorF3(+0.4f, +0.1f, +0.4f)
	);

	{
		// this is needed to prevent compiler from complaining about multiple definitions of Bool2D
		Image img(VectorU2(1, 1));
		PolyHedra * picture = PolyHedra::Generate::DuoHedra(img);
		delete picture;
	}

	// 3 Cuboids. implement Scaling for Transformations
	{
		VoxelCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelCube, BoxF3(VectorF3(0.0f), VectorF3(1.0f)));
		PolyHedraManager.PlacePolyHedra(VoxelCube);
	}
	{
		VoxelChunkCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelChunkCube, BoxF3(VectorF3(0.1f), VectorF3(CHUNK_VALUES_PER_SIDE - 0.1f)));
		PolyHedraManager.PlacePolyHedra(VoxelChunkCube);
	}
	{
		ViewEntity.PolyHedra = new PolyHedra();
		PolyHedraBoxEdges(*ViewEntity.PolyHedra, ViewEntity.Box);
		PolyHedraManager.PlacePolyHedra(ViewEntity.PolyHedra);
	}

	// Voxels
	{
		VoxelGeometryPallet::Cube.InitCube();
		VoxelGeometryPallet::Cylinder.InitCylinder();
		VoxelGeometryPallet::Slope.InitSlope();

		VoxelPalletMap::All.Default(MediaDirectory);
		VoxelPalletMap::All.MakePolyHedra();
	}

	{
		ViewRayPolyHedra = PolyHedra::Generate::ConeC(8, 0.01f, 0.1f);
		PolyHedraManager.PlacePolyHedra(ViewRayPolyHedra);
	}
	//Perlin2D::DebugShow();
	//TestRandom();
}



unsigned int	ChunkInsertRange = 0;
unsigned int	ChunkRemoveRange = 0;

// make Lights
// store in File
void MakeControls()
{
	std::cerr << "MakeControls()\n";
	// Pause
	{
		PauseMenu.Continue.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Continue);
		PauseMenu.Options.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Options);
		PauseMenu.Debug.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Debug);
		PauseMenu.Exit.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Exit);

		PauseMenu.Show();
		ControlManager.Window.ChildInsert(PauseMenu);
	}
	// Options
	{
		OptionsMenu.FOV.ValueXChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_FOV);
		OptionsMenu.FOV.SetValueX(view.FOV.ToDegrees());

		OptionsMenu.Depth.ValueXChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Depth);
		OptionsMenu.Depth.SetValueX(100.0f); // get Depth. also depth works weirdly ?

		OptionsMenu.DepthRange.ValueXChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_DepthRange);
		OptionsMenu.DepthRange.SetValueX(view.Depth.Range.Min);

		// Remove range should never be less then Insert
		// make RemoveRange = InsertRange * 2 ?
		// make RemoveRange = InsertRange + n ?

		//ChunkInsertRange = 6;
		ChunkInsertRange = 4;
		//ChunkInsertRange = 1;
		OptionsMenu.ChunkInsert.ValueXChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Chunk_Insert);
		OptionsMenu.ChunkInsert.SetValueX(ChunkInsertRange);

		//ChunkRemoveRange = 12;
		ChunkRemoveRange = 8;
		//ChunkRemoveRange = 1;
		OptionsMenu.ChunkRemove.ValueXChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Chunk_Remove);
		OptionsMenu.ChunkRemove.SetValueX(ChunkRemoveRange);

		OptionsMenu.Back.ClickFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Back);

		OptionsMenu.Hide();
		ControlManager.Window.ChildInsert(OptionsMenu);
	}
	// Debug
	{
		DebugMenu.FPS.Check.Check(true);

		DebugMenu.VoxelChunkBoxes.Check.Check(true);

		DebugMenu.VoxelChunkMemory.Check.Check(true);

		DebugMenu.Generation3DComparison.ValueXChangedFunc.Assign(this, &ContextNoisePlane::DebugMenu_Generation3DComparison);
		DebugMenu.Generation3DComparison.SetValueX(Chunk::Generation3D_Comparison);

		DebugMenu.Generation3DFactor.ValueXChangedFunc.Assign(this, &ContextNoisePlane::DebugMenu_Generation3DFactor);
		DebugMenu.Generation3DFactor.SetValueX(Chunk::Generation3D_Factor);

		DebugMenu.Hide();
		ControlManager.Window.ChildInsert(DebugMenu);
	}
	// Inventory
	{
		InventoryPolyHedraManager.MakeCurrent();
		for (unsigned int i = 0; i < VoxelPalletMap::All.Data.Count(); i++)
		{
			Inventory[Inventory.Count.Convert(i)] = new ItemVoxel(VoxelPalletMap::All.Data[i]);
		}
		//Inventory[VectorU2(0, 0)] = new ItemVoxel(VoxelPalletMap::All["OrientationCube"]);
		//Inventory[VectorU2(1, 0)] = new ItemVoxel(VoxelPalletMap::All["OrientationCylinder"]);
		////Inventory[VectorU2(2, 0)] = new ItemVoxel(VoxelPalletMap::All["OrientationSlope"]);
		//Inventory[VectorU2(0, 1)] = new ItemVoxel(VoxelPalletMap::All["Gray"]);
		//Inventory[VectorU2(1, 1)] = new ItemVoxel(VoxelPalletMap::All["Grass"]);
		//Inventory[VectorU2(2, 1)] = new ItemVoxel(VoxelPalletMap::All["RedLog"]);
		//Inventory[VectorU2(0, 2)] = new ItemVoxel(VoxelPalletMap::All["ConcreteCube"]);
		//Inventory[VectorU2(1, 2)] = new ItemVoxel(VoxelPalletMap::All["ConcreteCylinder"]);
		InventoryUI.Change(&Inventory);
		InventoryUI.Hide();
		ControlManager.Window.ChildInsert(InventoryUI);
		PolyHedraManager.MakeCurrent();
	}
	// HotBar
	{
		InventoryPolyHedraManager.MakeCurrent();
		HotBarUI.Anchor.Y.AnchorMax(0);
		HotBarUI.Change(&HotBar);
		//HotBarUI.Hide();
		ControlManager.Window.ChildInsert(HotBarUI);
		PolyHedraManager.MakeCurrent();
	}
}

void DebugMenu_Generation3DComparison(float val)
{
	Chunk::Generation3D_Comparison = val;
	DebugMenu.Generation3DComparison.SetText("3D Comp:" + std::to_string(Chunk::Generation3D_Comparison));
	ChunkManager.Clear();
}
void DebugMenu_Generation3DFactor(float val)
{
	Chunk::Generation3D_Factor = 1 << ((int)val);
	DebugMenu.Generation3DFactor.SetText("3D Fact:" + std::to_string(Chunk::Generation3D_Factor));
	ChunkManager.Clear();
}

void PauseMenu_Continue(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (!PauseMenu.IsVisible())
	{
		PauseMenu.Show();
	}
	else
	{
		PauseMenu.Hide();
	}
}
void PauseMenu_Options(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (!OptionsMenu.IsVisible())
	{
		OptionsMenu.Show();
	}
	if (PauseMenu.IsVisible())
	{
		PauseMenu.Hide();
	}
}
void PauseMenu_Debug(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (DebugMenu.IsVisible())
	{
		DebugMenu.Hide();
	}
	else
	{
		DebugMenu.Show();
	}
}
void PauseMenu_Exit(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	ContextBase::ChangeToContext0();
}

void OptionsMenu_FOV(float val)
{
	view.FOV = Angle::Degrees(val);
	Multiform_FOV.ChangeData(view.FOV);

	unsigned int v = val;
	OptionsMenu.FOV.SetText("FOV:" + std::to_string(v));
}
void OptionsMenu_Depth(float val)
{
	view.Depth.Factors.ChangeFar(val);
	Multiform_Depth.ChangeData(view.Depth);

	unsigned int v = val;
	OptionsMenu.Depth.SetText("Depth:" + std::to_string(v));
}
void OptionsMenu_DepthRange(float val)
{
	view.Depth.Range.ChangeMin(val);
	Multiform_Depth.ChangeData(view.Depth);
	OptionsMenu.DepthRange.SetText("DepthRange:" + std::to_string(val));
}
void OptionsMenu_Chunk_Insert(float val)
{
	ChunkInsertRange = val;
	OptionsMenu.ChunkInsert.SetText("Insert:" + std::to_string(ChunkInsertRange));
}
void OptionsMenu_Chunk_Remove(float val)
{
	ChunkRemoveRange = val;
	OptionsMenu.ChunkRemove.SetText("Remove:" + std::to_string(ChunkRemoveRange));
}
void OptionsMenu_Back(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (OptionsMenu.IsVisible())
	{
		OptionsMenu.Hide();
	}
	if (!PauseMenu.IsVisible())
	{
		PauseMenu.Show();
	}
}



// hardcode Shaders into Managers
// hardcode Attributes into Managers
// "Template" for Attributes in Managers with InstanceManagers
// also organize Shader Files
//
// a lot of the managers are siminal with the bool flags and function names
// make a Base ? to organize
void ChangeMedia()
{
	// PolyHedraManager
	PolyHedraManager.InitExternal(MediaDirectory);

	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.frag")),
		});
		ControlManager.Shader.Change(code);
	}
	{
		ControlManager.Buffer.Main.Pos.Change(0);
		ControlManager.Buffer.Inst.Min.Change(1);
		ControlManager.Buffer.Inst.Max.Change(2);
		ControlManager.Buffer.Inst.Layer.Change(3);
		ControlManager.Buffer.Inst.Col.Change(4);
	}
	{
		ControlManager.Window.ChangeManager(&ControlManager);
		ControlManager.Window.ChangeManager(&TextManager);
	}

	// TextManager
	TextManager.InitMedia(MediaDirectory);
	TextManager.TextFont = UI::Text::Font::Parse(
		MediaDirectory.File("Text/Font0.atlas")
	);

	// PlaneManager
	/*{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.frag")),
		});
		PlaneManager.Shader.Change(code);
	}*/

	// ChunkManager
	{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Voxel/Voxel.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Voxel/Voxel.frag")),
		});
		ChunkManager.Shader.Change(code);
	}

	// Inventory
	InventoryPolyHedraManager.InitExternal(MediaDirectory);
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/PHFull.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/PHFull.frag")),
		});
		InventoryShader.Change(code);
		InventoryPolyHedraManager.ShaderFullOther = &InventoryShader; // Others dosent need to be PolyHedraFullShader
	}
}

void GraphicsCreate()
{
	PolyHedraManager.GraphicsCreate();
	PolyHedraManager.InitInternal(); // do this in GraphicsCreate ?
	ControlManager.GraphicsCreate();
	TextManager.GraphicsCreate();
	//PlaneManager.GraphicsCreate();
	ChunkManager.GraphicsCreate();
	InventoryPolyHedraManager.GraphicsCreate();
	InventoryShader.Create();
}
void GraphicsDelete()
{
	PolyHedraManager.GraphicsDelete();
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	//PlaneManager.GraphicsDelete();
	ChunkManager.GraphicsCreate();
	InventoryPolyHedraManager.GraphicsDelete();
	InventoryShader.Delete();
}

void Init() override
{
	Make();

	ChangeMedia();

	GraphicsCreate();

	VoxelPalletMap::All.LoadTextures(ChunkManager);
	{
		window.DefaultColor = ColorF4(0.5f, 0.5f, 0.5f);
		//window.DefaultColor = ColorF4(0.6f, 0.85f, 0.9f);
		view.Depth.Color = window.DefaultColor;
		view.Depth.Range.ChangeMin(0.5f);
	}

	MakeControls();

	ChunkManager.ChangeChunksArraySize(8);
	//ChunkManager.ChangeChunksArraySize(1);

	Multiform_Depth.ChangeData(view.Depth);
	Multiform_FOV.ChangeData(view.FOV);

	ThreadDelay = false;
}
void Free() override
{
	GraphicsDelete();
	ThreadDelay = false;
	ThreadTerminate = true;
	AuxThread0.join();
	AuxThread1.join();
}



void Draw()
{
	// should GraphicsManagers just know that they want Enabled/Disabled ?
	// GraphicsManagerBase so I dont need to call the Create/Delete individually
	// instead just put them in a Container
	// also Update/Draw all automatically

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();
	//PlaneManager.Draw();
	ChunkManager.Draw();
//	ChunkManager.UpdateChunksArrayDraw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	{
		InventoryPolyHedraManager.MakeCurrent();
		ControlManager.UpdateSize(window.Size);
		ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
//		ControlManager.Window.UpdateEntrys();
		ControlManager.Draw();
		PolyHedraManager.MakeCurrent();
	}
	TextManager.Draw();

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	InventoryPolyHedraManager.ClearInstances();
	InventoryPolyHedraManager.UpdateInstances();
	InventoryPolyHedraManager.DrawFull();
}

bool	DontRemove = false;
bool	DontInsert = false;
bool	DontGenerate = false;
bool	DontBuffer = false;

ValueAverager<float>	TimeDLTAverage;
ValueAverager<int>		TimeFPSAverage;
ValueAverager<float>	FrameDuration;

void BlockListTest()
{
	BlockList<4, unsigned int> list;

	unsigned int count = Random::UInt32() & 0xF;
	std::cout << "count " << count << '\n';
	for (unsigned int c = 0; c < count; c++)
	{
		unsigned int item = Random::UInt32() & 0xF;
		std::cout << '[' << c << ']' << item << '\n';
		list.Insert(item);
	}
	std::cout << '\n';

	std::cout << "count " << list.BlockCount() << '\n';
	for (unsigned int b = 0; b < list.BlockCount(); b++)
	{
		std::cout << '[' << b << ']';
		const BlockList<4, unsigned int>::Block & block = list.BlockIndex(b);
		for (unsigned int i = 0; i < 4; i++)
		{
			std::cout << ' ' << block.Data[i];
		}
		std::cout << '\n';
	}
	std::cout << '\n';

	std::cout << "count " << list.Count() << '\n';
	for (unsigned int i = 0; i < list.Count(); i++)
	{
		std::cout << '[' << i << ']' << list[i] << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';
}
void FrameText(FrameTime frame_time)
{
	TimeDLTAverage.NewValue(frame_time.ActualFrameTime);
	TimeFPSAverage.NewValue(frame_time.ActualFramesPerSecond);

	std::stringstream ss;

	//BlockListTest();

	if (DebugMenu.FPS.Check.IsChecked())
	{
		ss << "Frame (" << frame_time.WantedFramesPerSecond << '|' << frame_time.ActualFramesPerSecond << ")Hz\n";
		ss << "Frame (" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")s\n";
		ss << '\n';
		ss << "Min: " << TimeFPSAverage.Min() << "Hz " << TimeDLTAverage.Min() << "s\n";
		ss << "Avg: " << TimeFPSAverage.Average() << "Hz " << TimeDLTAverage.Average() << "s\n";
		ss << "Max: " << TimeFPSAverage.Max() << "Hz " << TimeDLTAverage.Max() << "s\n";
		ss << '\n';
	}

	// Time
	/*{
		ss << "Time\n";

		ss << "Duration:\n";
		ss << "  Min: " << FrameDuration.Min() << '\n';
		ss << "  Avg: " << FrameDuration.Average() << '\n';
		ss << "  Max: " << FrameDuration.Max() << '\n';
		ss << '\n';
		ss << "  GraphicsCreate: " << ChunkManager::TimeGraphicsCreate << '\n';
		ss << "  GraphicsDelete: " << ChunkManager::TimeGraphicsDelete << '\n';
		ss << "            Draw: " << ChunkManager::TimeDraw << '\n';
		ss << '\n';

		ss << "Thread0:\n";
		ss << "  Min: " << AuxThread0Time.Min() << '\n';
		ss << "  Avg: " << AuxThread0Time.Average() << '\n';
		ss << "  Max: " << AuxThread0Time.Max() << '\n';
		ss << '\n';
		ss << "Insert          : " << ChunkManager::TimeInsert << '\n';
		ss << "InsertNeighbours: " << ChunkManager::TimeInsertNeighbours << '\n';
		ss << "Remove          : " << ChunkManager::TimeRemove << '\n';
		ss << "Update          : " << ChunkManager::TimeUpdate << '\n';
		ss << "Update    Insert: " << ChunkManager::TimeUpdateInsert << '\n';
		ss << "Update    Change: " << ChunkManager::TimeUpdateChange << '\n';
		ss << "Update    Remove: " << ChunkManager::TimeUpdateRemove << '\n';
		ss << '\n';

		ss << "Thread1:\n";
		ss << "  Min: " << AuxThread1Time.Min() << '\n';
		ss << "  Avg: " << AuxThread1Time.Average() << '\n';
		ss << "  Max: " << AuxThread1Time.Max() << '\n';
		ss << '\n';
		ss << "        Generate: " << ChunkManager::TimeGenerate << '\n';
		ss << "        Graphics: " << ChunkManager::TimeGraphics << '\n';
		ss << '\n';
	}*/

	{
		ss << "CheckingCount: " << ChunkManager.ChunksLock.Count() << '\n';
		ss << "ToInsert: " << ChunkManager.ChunksToInsert.Count() << '\n';
		ss << "ToRemove: " << ChunkManager.ChunksToRemove.Count() << '\n';
		ss << '\n';
	}

	// Text
	{
		ss << "TextManager.Instances.Count(): " << TextManager.Instances.Count() << '\n';
		ss << '\n';
	}

	if (DebugMenu.View.Check.IsChecked())
	{
		ss << "View " << view.Trans.Position << '\n';
		ss << "View " << ViewEntity.Vel << ' ' << ViewEntity.Vel.length() << '\n';
		ss << "None : " << (ViewCollisionSide.None) << '\n';
		ss << "PrevX: " << (ViewCollisionSide.PrevX) << '\n';
		ss << "PrevY: " << (ViewCollisionSide.PrevY) << '\n';
		ss << "PrevZ: " << (ViewCollisionSide.PrevZ) << '\n';
		ss << "NextX: " << (ViewCollisionSide.NextX) << '\n';
		ss << "NextY: " << (ViewCollisionSide.NextY) << '\n';
		ss << "NextZ: " << (ViewCollisionSide.NextZ) << '\n';
		ss << '\n';
	}

	ss << "DontInsert: " << DontInsert << '\n';
	ss << "DontRemove: " << DontRemove << '\n';
	ss << "DontGenerate: " << DontGenerate << '\n';
	ss << "DontBuffer: " << DontBuffer << '\n';
	ss << '\n';

	if (DebugMenu.ChunkHere.Check.IsChecked())
	{
		//VoxelIndex idx = ChunkManager.FindVoxelIndex(view.Trans.Position);
		ChunkVoxelIndex idx(view.Trans.Position.roundF());
		ss << "Here: " << idx.Chunk << ' ' << idx.Voxel << '\n';
		//ChunkManager.ChunksInUse.lock();
		Chunk * chunk_ptr = ChunkManager.FindLockOrNull(idx.Chunk);
		//if (idx.ChunkMan != 0xFFFFFFFF)
		if (chunk_ptr != nullptr)
		{
			//ss << "Chunk: " << idx.ChunkMan << '\n';
			//Chunk & chunk = *ChunkManager.Chunks[idx.ChunkMan];
			Chunk & chunk = *chunk_ptr;

			ss << "Data: ";
			if (chunk.IsEmpty()) { ss << "Empty"; } else
			{
				ss << Memory1000ToString(CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
			}
			ss << '\n';

			ss << "GenerationState: ";
			{
				switch (chunk.GenerationState)
				{
					case GenerationState::None: ss << "None"; break;
					case GenerationState::Generated: ss << "Generated"; break;
				};
			}
			if (chunk.GenerationDone()) { ss << "(Done)"; }
			ss << '\n';

			ss << "MainBufferState: ";
			switch (chunk.MainBufferState)
			{
				case BufferDataState::None: ss << "None"; break;
				case BufferDataState::Needed : ss << "Needed"; break;
				case BufferDataState::Ready: ss << "Ready"; break;
				case BufferDataState::Drawable: ss << "Drawable"; break;
			}
			ss << '\n';

			ss << "Buffer: ";
			ss << Memory1000ToString(chunk.Buffer.Main.Count * sizeof(VoxelGraphics::MainData));
			ss << '\n';

			chunk.unlock();
			ss << '\n';
		}
		else
		{
			ss << "No Chunk Info\n";
		}
		ss << '\n';
		//ChunkManager.ChunksInUse.unlock();
	}

	/*{
		unsigned int count = PolyHedraManager.InstanceManagers.Count();
		unsigned int all_count = PolyHedraManager.ObjectDatas.Count();
		unsigned int full_count = 0;
		unsigned int wire_count = 0;
		for (unsigned int i = 0; i < count; i++)
		{
			full_count += PolyHedraManager.InstanceManagers[i].InstancesFull.Count();
			wire_count += PolyHedraManager.InstanceManagers[i].InstancesWire.Count();
		}
		ss << "PolyHedra Main|Inst " << count << '|' << all_count << '\n';
		ss << "Full|Wire" << ' ' << full_count << '|' << wire_count << '\n';
		ss << '\n';
	}*/

	/*{
		unsigned int count_planes = PlaneManager.Planes.Count();
		unsigned int count_tiles = count_planes * PLANE_VALUES_PER_AREA;
		ss << "Planes|Tiles:" << count_planes << '|' << count_tiles;
		ss << " (" << Memory1000ToString(count_tiles * sizeof(float)) << ")\n";
		ss << '\n';
	}*/

	if (DebugMenu.VoxelChunkMemory.Check.IsChecked())
	{
		//ChunkManager.ChunksChanging.lock();
		ChunkManager.ChunksLock.Checking0();

		unsigned int chunks_t = 0; // total
		unsigned int chunks_u = 0; // ungenerated
		unsigned int chunks_f = 0; // filled
		unsigned int chunks_e = 0; // empty
		for (unsigned int i = 0; i < ChunkManager.Chunks.Length(); i++)
		{
			if (ChunkManager.Chunks[i] == nullptr) { continue; }
			chunks_t++;
			Chunk & chunk = *ChunkManager.Chunks[i];
			if (chunk.GenerationDone())
			{
				if (!chunk.IsEmpty())
				{ chunks_f++; }
				else
				{ chunks_e++; }
			}
			else
			{ chunks_u++; }
		}

		ss << "Chunks:" << ChunkManager.Chunks.Length();
		ss << '|' << chunks_t << '[';
		ss << 'U' << chunks_u << '|';
		ss << 'E' << chunks_e << '|';
		ss << 'F' << chunks_f << ']';
		ss << '\n';

		ss << "ChunkSize\n";
		ss << "sizeof(Chunk)" << ' ' << sizeof(Chunk) << '\n';
		ss << "sizeof(VectorI3)" << ' ' << sizeof(VectorI3) << '\n';
		ss << "sizeof(VectorU3)" << ' ' << sizeof(VectorU3) << '\n';
		ss << "sizeof(Array3D<Voxel>)" << ' ' << sizeof(Array3D<Voxel>) << '\n';
		ss << "sizeof(Chunk*)" << ' ' << sizeof(Chunk*) << '\n';
		ss << "sizeof(VoxelGraphics::Buffer)" << ' ' << sizeof(VoxelGraphics::Buffer) << '\n';
		ss << "sizeof(ChunkGraphicsData)" << ' ' << sizeof(ChunkGraphicsData) << '\n';
		ss << "sizeof(std::mutex)" << ' ' << sizeof(std::mutex) << '\n';
		ss << "Chunks:" << Memory1000ToString(sizeof(Chunk));
		ss << " * " << Seperated1000(chunks_t);
		ss << " = " << Memory1000ToString(chunks_t * sizeof(Chunk));
		ss << '\n';

		ss << "Voxels:" << Memory1000ToString(sizeof(Voxel));
		ss << " * " << Seperated1000(chunks_f * CHUNK_VALUES_PER_VOLM);
		ss << " = " << Memory1000ToString(chunks_f * CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
		ss << '\n';
		ss << '\n';

		ChunkManager.ChunksLock.Checking1();
		//ChunkManager.ChunksChanging.unlock();
	}

	if (DebugMenu.VoxelChunkMemory.Check.IsChecked())
	{
		//ChunkManager.ChunksChanging.lock();
		ChunkManager.ChunksLock.Checking0();

		unsigned long long main_count = 0;
		unsigned int buffer__ = 0;
		unsigned int buffer_n = 0;
		unsigned int buffer_r = 0;
		for (unsigned int i = 0; i < ChunkManager.Chunks.Length(); i++)
		{
			if (ChunkManager.Chunks[i] == nullptr) { continue; }
			Chunk & chunk = *ChunkManager.Chunks[i];
			main_count += chunk.Buffer.Main.Count;
			if (chunk.MainBufferState == BufferDataState::None)   { buffer__++; }
			if (chunk.MainBufferState == BufferDataState::Needed) { buffer_n++; }
			if (chunk.MainBufferState == BufferDataState::Ready)  { buffer_r++; }
		}

		ss << "State";
		ss << ':' << buffer__ << ' ';
		ss << 'N' << buffer_n << ' ';
		ss << 'R' << buffer_r << '\n';

		ss << "BufferData:" << Memory1000ToString(sizeof(VoxelGraphics::MainData));
		ss << " * " << Seperated1000(main_count);
		ss << " = " << Memory1000ToString(main_count * sizeof(VoxelGraphics::MainData));
		ss << '\n';

		ChunkManager.ChunksLock.Checking1();
		//ChunkManager.ChunksChanging.unlock();
	}

	UI::Text::Object text; text.Create();
	if (DebugMenu.IsVisible())
	{
		text.TextPosition().X = DebugMenu.Anchor.X.GetMinSize();
	}
	text.AlignTopLeft();
	text.Color() = ColorF4(1, 1, 1);
	text.Bound().Min = VectorF2();
	text.Bound().Max = window.Size.Buffer.Full;
	text.String() = ss.str();
}
void InventoryCursor(FrameTime frame_time)
{
	static float time_sum = 0.0f;
	InventoryPolyHedraManager.MakeCurrent();

	VectorF2	PixelSize(40, 40); // hardcoded in Shader
	VectorF2	size = window.Size.Buffer.SizeFullToNormalRel(PixelSize);

	VectorF2	PixelPos;
	VectorF2	pos;

	if (HotBar[VectorU2(0, 0)] != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)HotBar[VectorU2(0, 0)];
		PixelPos.X = window.Size.Buffer.Full.X - 40;
		PixelPos.Y = 40;
		pos = window.Size.Buffer.PosFullToNormalRel(PixelPos);
		PolyHedraObject obj(item -> VoxelPallet -> PolyHedra);
		obj.Trans().Position.X = pos.X / size.X;
		obj.Trans().Position.Y = pos.Y / size.Y;
		obj.Trans().Rotation.X1 = Angle::Degrees(15);
		obj.Trans().Rotation.Y2 = Angle::Radians(time_sum);
	}

	if (InventorySlot::StaticItem != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)InventorySlot::StaticItem;
		PixelPos = window.MouseManager.CursorPosition().Buffer.Corner;
		pos = window.Size.Buffer.PosFullToNormalRel(PixelPos);
		PolyHedraObject obj(item -> VoxelPallet -> PolyHedra);
		obj.Trans().Position.X = +pos.X / size.X;
		obj.Trans().Position.Y = -pos.Y / size.Y;
		obj.Trans().Rotation.X1 = Angle::Degrees(15);
		obj.Trans().Rotation.Y2 = Angle::Radians(time_sum);
	}

	time_sum += frame_time.Delta;
	PolyHedraManager.MakeCurrent();
}
// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void FrameInput()
{
	if (window.KeyBoardManager[Keys::Escape].State == State::Press)
	{
		OptionsMenu.Hide();
		InventoryUI.Hide();
		//HotBarUI.Hide();
		if (PauseMenu.IsVisible())
		{
			PauseMenu.Hide();
		}
		else
		{
			PauseMenu.Show();
		}
	}
	if (window.KeyBoardManager[Keys::E].State == State::Press)
	{
		if (!PauseMenu.IsVisible() && !OptionsMenu.IsVisible())
		{
			if (!InventoryUI.IsVisible())
			{
				InventoryPolyHedraManager.MakeCurrent();
				InventoryUI.Show();
				//HotBarUI.Show();
				PolyHedraManager.MakeCurrent();
			}
			else
			{
				InventoryUI.Hide();
				//HotBarUI.Hide();
			}
		}
	}

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { Toggle(ViewRaySync); }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { Toggle(ChunkManager.ViewRayPolyHedra, ViewRayPolyHedra); }
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { Toggle(ChunkManager.VoxelBoxPolyHedra, VoxelCube); }

	if (window.KeyBoardManager[Keys::F7].State == State::Press)
	{
		if (DebugMenu.IsVisible())
		{
			DebugMenu.Hide();
		}
		else
		{
			DebugMenu.Show();
		}
	}

	if (window.KeyBoardManager[Keys::F2].State == State::Press) { Toggle(ViewTangible); }
	if (window.KeyBoardManager[Keys::F3].State == State::Press)
	{
		if (ViewDistance == 0.0f)
		{ ViewDistance = 2.0f; }
		else
		{ ViewDistance = 0.0f; }
	}
	/*if (window.KeyBoardManager[Keys::F4].State == State::Press)
	{
		//Toggle(PlaneManager.ShouldGenerate);
		Toggle(ChunkManager.DontGenerate);
	}*/
	if (window.KeyBoardManager[Keys::F5].State == State::Press)
	{
		//PlaneManager.Clear();
		ChunkManager.Clear();
	}

	if (window.KeyBoardManager[Keys::F11].State == State::Press) { Toggle(DontRemove); }
	if (window.KeyBoardManager[Keys::F10].State == State::Press) { Toggle(DontInsert); }
	if (window.KeyBoardManager[Keys::F9].State == State::Press) { Toggle(DontGenerate); }
	if (window.KeyBoardManager[Keys::F8].State == State::Press) { Toggle(DontBuffer); }

	if (PauseMenu.IsVisible() || OptionsMenu.IsVisible() || InventoryUI.IsVisible())
	{
		if (window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeFree(); }
	}
	else
	{
		if (!window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeLock(); }
	}
}
void Frame(FrameTime frame_time) override
{
//	std::cout << "Frame:" << __LINE__ << '\n';
	FrameInput();

	if (!OptionsMenu.IsVisible())
	{
		Trans3D change;
		if (window.MouseManager.CursorModeIsLocked())
		{
			change = window.MoveSpinFromKeysCursor();
			change.Rotation *= view.FOV.ToRadians() * 0.05f;
			{
				EulerAngle3D e(Angle(), Angle(), view.Trans.Rotation.Y2);
				change.Position = e.forward(change.Position);
			}
		}
		ViewUpdateAround(change, frame_time);
	}

	/*{
		float pixel_rad = 1;
		UI::Control::Object obj;
		obj.Create();
		obj.Box().Min = window.Size.Buffer.Half - VectorF2(pixel_rad, pixel_rad);
		obj.Box().Max = window.Size.Buffer.Half + VectorF2(pixel_rad, pixel_rad);
		obj.Color() = ColorF4(1, 0, 1);
	}*/

	if (DebugMenu.VoxelChunkBoxes.Check.IsChecked())
	{
		unsigned int p = PolyHedraManager.FindPolyHedra(VoxelChunkCube);
		for (unsigned int i = 0; i < ChunkManager.Chunks.Length(); i++)
		{
			Chunk * chunk = ChunkManager.Chunks[i];
			if (chunk == nullptr) { continue; }
			PolyHedraObject chunk_box(p);
			chunk_box.Trans().Position = chunk -> Index * CHUNK_VALUES_PER_SIDE;
			chunk_box.ShowWire();
		}
	}

	/*if (DebugMenu.ChunkHere.Check.IsChecked())
	{
		VoxelIndex idx = ChunkManager.FindVoxelIndex(view.Trans.Position);

		PolyHedraObject chunk_box(VoxelChunkCube);
		chunk_box.Trans().Position = idx.Chunk * CHUNK_VALUES_PER_SIDE;
		chunk_box.ShowWire();
	}*/

	FrameText(frame_time);

	InventoryCursor(frame_time);

	Draw();
}

void Resize(DisplaySize display_size) override
{
	::InventorySlot::WindowSize = display_size;
	Multiform_DisplaySize.ChangeData(display_size);
}



// make these virtual and put them in Base
void MouseScroll(ScrollArgs args) override { (void)args; }
void MouseClick(ClickArgs args) override
{
	InventoryPolyHedraManager.MakeCurrent();
	ControlManager.RelayClick(args);
	PolyHedraManager.MakeCurrent();
}
void MouseDrag(DragArgs args) override { ControlManager.RelayCursorDrag(args); }

void KeyBoardKey(KeyArgs args) override { (void)args; }
};

ContextBase * newContextNoisePlane()
{
	return new ContextNoisePlane();
}
