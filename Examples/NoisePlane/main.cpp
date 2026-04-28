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
#include "Voxel/VoxelTemplate.hpp"
#include "Voxel/VoxelIndex.hpp"

#include "BoxEntity.hpp"

// Menus
#include "Menus/Main.hpp"
#include "Menus/Pause.hpp"
#include "Menus/Options.hpp"
#include "Menus/Debug.hpp"
#include "Menus/Inventory.hpp"
#include "Inventory/ItemVoxel.hpp"

// Math
#include <math.h>

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
::Inventory		Inventory;



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
	, Perlin2(Perlin2D::Random(Undex2D(8, 8)))
	, Perlin3(Perlin3D::Random(Undex3D(8, 8, 8)))
	, Multiform_DisplaySize("DisplaySize")
	, Multiform_View("View")
	, Multiform_Depth("Depth")
	, Multiform_FOV("FOV")
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
ContextNoisePlane::PhysicsContext	PhysicsContext;

// make a BoxEntity for Colliding stuff
void	DisplayBoxEntity(BoxEntity & box_entity)
{
	PolyHedraObject view_box_obj(box_entity.PolyHedra);
	view_box_obj.Trans().Position = box_entity.Pos;
	view_box_obj.ShowWire();
}
void	DisplayBoxEntityVoxels(BoxEntity & box_entity, FrameTime frame_time)
{
	unsigned int p = PolyHedraManager.FindPolyHedra(VoxelCube);

	BoxF3 box = box_entity.Box + box_entity.Pos;
	box.Consider(box_entity.Box.Min + box_entity.Pos + (box_entity.Vel * frame_time.Delta));
	box.Consider(box_entity.Box.Max + box_entity.Pos + (box_entity.Vel * frame_time.Delta));
	box = box - VectorF3(0.5f);

	LoopI3 loop(box.Min.round(), Bool3(false), box.Max.round(), Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		const Voxel * voxel = ChunkManager.FindVoxelOrNull(i);
		if (voxel != nullptr && voxel -> Template != nullptr)
		{
			PolyHedraObject voxel_obj(p);
			voxel_obj.Trans().Position = i;
			voxel_obj.ShowWire();
		}
	}
}



bool ViewBoxCollision = false;
float ViewDistance = 0.0f;

float	ViewSpeed = 0.1f;   // force when moving
float	ViewFaster = 3.0f; // force multiplier when moving faster
// force when moving in the air

// force when no physics
float	ViewSpeedNoClip = 10.0f;
float	ViewFasterNoClip = 10.0f;

BoxEntity		ViewEntity;
CollisionSide	ViewCollisionSide; // last Frame

void UpdateViewColliding(FrameTime frame_time)
{
	Trans3D change;

	// View Change
	if (window.MouseManager.CursorModeIsLocked())
	{
		change = window.MoveSpinFromKeysCursor();
		change.Rotation *= view.FOV.ToRadians() * 0.05f;
		{
			EulerAngle3D e(Angle(), Angle(), view.Trans.Rotation.Y2);
			change.Position = e.forward(change.Position);
		}
	}

	if (ViewBoxCollision)
	{
		if (ViewCollisionSide.PrevY)
		{
			change.Position *= ViewSpeed;
			if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { change.Position *= ViewFaster; }

			float jump = 0.0f;
			if (change.Position.Y > 0.0f) { jump = 15.0f; }
			change.Position.Y = 0.0f;

			float friction_force = PhysicsContext.CalcFriction(1.0f);
			if (change.Position.length2() != 0.0f)
			{
				change.Position = PhysicsContext.CalcFriction(change.Position * 1.0f, friction_force) / 1.0f;
			}
			else
			{
				ViewEntity.Vel -= PhysicsContext.CalcFriction(ViewEntity.Vel * 1.0f, friction_force) / 1.0f;
			}

			change.Position.Y = jump;
		}
		else
		{
			change.Position.Y = 0.0f;
			change.Position *= 0.1f;
		}

		ViewEntity.Vel += change.Position + PhysicsContext.CalculateVel(ViewEntity.Vel, 1.0f, 1.0f);
		DisplayBoxEntityVoxels(ViewEntity, frame_time);
		DisplayBoxEntity(ViewEntity);
		ViewCollisionSide = ViewEntity.Collide(ChunkManager, frame_time);
		DisplayBoxEntity(ViewEntity);
	}
	else
	{
		change.Position *= ViewSpeedNoClip;
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { change.Position *= ViewFasterNoClip; }
		ViewEntity.Vel = change.Position;
		ViewEntity.Pos += ViewEntity.Vel * frame_time.Delta;
	}
	view.Trans.Position = ViewEntity.Pos;
	view.Trans.Rotation += change.Rotation * frame_time.Delta;
	view.Trans.Rotation.X1.clampPI();

	// View Matrix
	if (ViewDistance == 0.0f)
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(view.Trans));
	}
	else
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(
			Trans3D(view.Trans.Position - view.Trans.Rotation.forward(Point3D(0, 0, ViewDistance)), view.Trans.Rotation)
		));
	}
}

bool	ViewRaySync = true;
Ray3D	ViewRay;
void ViewRayFunction()
{
	if (PauseMenu.Interactible() || OptionsMenu.Interactible()) { return; }
	// check is any Control is being hovered
	// cast Ray at mouse

	if (ViewRaySync)
	{
		ViewRay.Pos = view.Trans.Position;
		ViewRay.Dir = view.Trans.Rotation.forward(VectorF3(0, 0, 1));
	}

	// make part of VoxelHit ?
	AxisRel look_axis_0 = AxisRel::None;
	AxisRel look_axis_1 = AxisRel::None;
	AxisRel look_axis_2 = AxisRel::None;
	{
		VectorI3 ranks = ViewRay.Dir.abs().RankDimensions();
		     if (ranks.X == 0) { if (ViewRay.Dir.X > 0) { look_axis_0 = AxisRel::NextX; } else { look_axis_0 = AxisRel::PrevX; } }
		else if (ranks.Y == 0) { if (ViewRay.Dir.Y > 0) { look_axis_0 = AxisRel::NextY; } else { look_axis_0 = AxisRel::PrevY; } }
		else if (ranks.Z == 0) { if (ViewRay.Dir.Z > 0) { look_axis_0 = AxisRel::NextZ; } else { look_axis_0 = AxisRel::PrevZ; } }
		if      (ranks.X == 1) { if (ViewRay.Dir.X > 0) { look_axis_1 = AxisRel::NextX; } else { look_axis_1 = AxisRel::PrevX; } }
		else if (ranks.Y == 1) { if (ViewRay.Dir.Y > 0) { look_axis_1 = AxisRel::NextY; } else { look_axis_1 = AxisRel::PrevY; } }
		else if (ranks.Z == 1) { if (ViewRay.Dir.Z > 0) { look_axis_1 = AxisRel::NextZ; } else { look_axis_1 = AxisRel::PrevZ; } }
		if      (ranks.X == 2) { if (ViewRay.Dir.X > 0) { look_axis_2 = AxisRel::NextX; } else { look_axis_2 = AxisRel::PrevX; } }
		else if (ranks.Y == 2) { if (ViewRay.Dir.Y > 0) { look_axis_2 = AxisRel::NextY; } else { look_axis_2 = AxisRel::PrevY; } }
		else if (ranks.Z == 2) { if (ViewRay.Dir.Z > 0) { look_axis_2 = AxisRel::NextZ; } else { look_axis_2 = AxisRel::PrevZ; } }
		// what if same ranks ?
	}

	std::stringstream ss;
	{
		ss << "ViewRay\n";
		ss << look_axis_0 << " :Look0\n";
		ss << look_axis_1 << " :Look1\n";
		ss << look_axis_2 << " :Look2\n";
	}

	VoxelHit hit = ChunkManager.HitVoxel(ViewRay);
	if (hit.Valid())
	{
		// Voxel Indicator
		{
			PolyHedraObject voxel_box_obj(VoxelCube);
			//voxel_box_obj.Trans().Position = idx;
			voxel_box_obj.Trans().Position = hit.Index;
			voxel_box_obj.ShowWire();
		}
		// Hit Indicator
		/*{
			PolyHedraObject voxel_dir_obj(ViewRayPolyHedra);
			voxel_dir_obj.Trans().Position = hit.Pos;
			voxel_dir_obj.Trans().Rotation = EulerAngle3D::PointToZ(hit.Dir);
			voxel_dir_obj.ShowWire();
		}*/

		// Side: make part of VoxelHit ?
		AxisRel place_axis_0;
		AxisRel place_axis_1;
		{
			place_axis_0 = hit.Side;
			AxisAbs axis = AxisRelToAxisAbs(place_axis_0);
			if (axis == AxisAbs::None) { place_axis_1 = AxisRel::None; }
			else if (axis != AxisRelToAxisAbs(look_axis_2)) { place_axis_1 = look_axis_2; }
			else if (axis != AxisRelToAxisAbs(look_axis_1)) { place_axis_1 = look_axis_1; }
			else if (axis != AxisRelToAxisAbs(look_axis_0)) { place_axis_1 = look_axis_0; }
			else { place_axis_1 = AxisRel::None; }
		}
		// determine place_axis_1 based on where on the face was clicked ?
		// top of face orients to point to top and so on

		// Text
		{
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
		}

		if (window.MouseManager[MouseButtons::MouseL].State == State::Press)
		{
			Voxel voxel;
			ChunkManager.ClearVoxel(hit.Index, voxel);
		}
		if (window.MouseManager[MouseButtons::MouseR].State == State::Press)
		{
			if (place_axis_0 == AxisRel::NextX) { hit.Index.X += 1; }
			if (place_axis_0 == AxisRel::NextY) { hit.Index.Y += 1; }
			if (place_axis_0 == AxisRel::NextZ) { hit.Index.Z += 1; }
			if (place_axis_0 == AxisRel::PrevX) { hit.Index.X -= 1; }
			if (place_axis_0 == AxisRel::PrevY) { hit.Index.Y -= 1; }
			if (place_axis_0 == AxisRel::PrevZ) { hit.Index.Z -= 1; }
			//Voxel voxel = VoxelTemplate::ConcreteCube.ToVoxel(place_axis_0, place_axis_1);
			Voxel voxel = VoxelTemplate::ConcreteCylinder.ToVoxel(place_axis_0, place_axis_1);
			//Voxel voxel = VoxelTemplate::OrientationSlope.ToVoxel(place_axis_0, place_axis_1);
			ChunkManager.PlaceVoxel(hit.Index, voxel);
		}
	}

	{
		UI::Text::Object text; text.Create();
		text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
		text.AlignTopRight(); // take DisplaySize
		text.Bound().Min = Point2D();
		text.Bound().Max = window.Size.Buffer.Full;
		text.String() = ss.str();
		text.Color() = ColorF4(1, 1, 1);
	}

	if (window.KeyBoardManager[Keys::NumPadEnter].State == State::Press)
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
	}
}

void UpdateAroundView(FrameTime frame_time)
{
	UpdateViewColliding(frame_time);

	ChunkManager.RemoveAround(view.Trans.Position, ChunkRemoveRange);
	ChunkManager.InsertAround(view.Trans.Position, ChunkInsertRange);
	ChunkManager.GenerateAround(Perlin2, Perlin3, view.Trans.Position, ChunkInsertRange, 1);

	ViewRayFunction();

	ChunkManager.GraphicsUpdateDataAround(view.Trans.Position, 1);
}



PolyHedra *		VoxelCube;
PolyHedra *		VoxelChunkCube;
PolyHedra *		ViewRayPolyHedra;

static void PolyHedraBoxEdges(PolyHedra & polyhedra, BoxF3 box)
{
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Min.Y, box.Min.Z))); // 000
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Min.Y, box.Min.Z))); // 001
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Max.Y, box.Min.Z))); // 010
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Max.Y, box.Min.Z))); // 011
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Min.Y, box.Max.Z))); // 100
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Min.Y, box.Max.Z))); // 101
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Min.X, box.Max.Y, box.Max.Z))); // 110
	polyhedra.Corners.Insert(PolyHedra::Corner(Point3D(box.Max.X, box.Max.Y, box.Max.Z))); // 111

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b001));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b010, 0b011));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b100, 0b101));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b110, 0b111));

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b010));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b001, 0b011));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b100, 0b110));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b101, 0b111));

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b100));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b001, 0b101));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b010, 0b110));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b011, 0b111));
}
static void PolyHedraVoxelData(PolyHedra & polyhedra, const Container::Binary<VoxelGraphics::MainTriangle> & data)
{
	Skin2DA & skin = *((Skin2DA*)polyhedra.Skin);
	VectorF3 off(0.5f);
	for (unsigned int i = 0; i < data.Count(); i++)
	{
		const VoxelGraphics::MainTriangle & face = data[i];

		unsigned int ph_i = polyhedra.Corners.Count();
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Corners[0].Pos - off));
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Corners[1].Pos - off));
		polyhedra.Insert_Corn(PolyHedra::Corner(face.Corners[2].Pos - off));
		polyhedra.Insert_Face3(ph_i + 0, ph_i + 1, ph_i + 2);

		skin.Insert_Face3(
			Skin2DFaceCorner(face.Corners[0].Tex.X, face.Corners[0].Tex.Y, 0.0f),
			Skin2DFaceCorner(face.Corners[1].Tex.X, face.Corners[1].Tex.Y, 0.0f),
			Skin2DFaceCorner(face.Corners[2].Tex.X, face.Corners[2].Tex.Y, 0.0f)
		);
	}
}
static void PolyHedraVoxelData(PolyHedra & polyhedra, const VoxelTemplate & voxel_template)
{
	PolyHedraVoxelData(polyhedra, voxel_template.Here);
	PolyHedraVoxelData(polyhedra, voxel_template.PrevX);
	PolyHedraVoxelData(polyhedra, voxel_template.PrevY);
	PolyHedraVoxelData(polyhedra, voxel_template.PrevZ);
	PolyHedraVoxelData(polyhedra, voxel_template.NextX);
	PolyHedraVoxelData(polyhedra, voxel_template.NextY);
	PolyHedraVoxelData(polyhedra, voxel_template.NextZ);
}

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
		Image img(Undex2D(1, 1));
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
		PolyHedraBoxEdges(*VoxelChunkCube, BoxF3(VectorF3(), VectorF3(CHUNK_VALUES_PER_SIDE)));
		PolyHedraManager.PlacePolyHedra(VoxelChunkCube);
	}
	{
		ViewEntity.PolyHedra = new PolyHedra();
		PolyHedraBoxEdges(*ViewEntity.PolyHedra, ViewEntity.Box);
		PolyHedraManager.PlacePolyHedra(ViewEntity.PolyHedra);
	}

	// Voxels
	{
		VoxelTemplate::OrientationCube.InitCube(0);
		VoxelTemplate::OrientationCylinder.InitCylinder(0);
		VoxelTemplate::OrientationSlope.InitSlope(0);
		VoxelTemplate::Gray.InitCube(1);
		VoxelTemplate::Grass.InitCube(2);
		VoxelTemplate::RedLog.InitCylinder(3);
		VoxelTemplate::ConcreteCube.InitCube(4);
		VoxelTemplate::ConcreteCylinder.InitCylinder(4);
	}
	{
		VoxelTemplate::ConcreteCylinder.PolyHedra = new PolyHedra();
		VoxelTemplate::ConcreteCylinder.PolyHedra -> Skin = new Skin2DA();
		Skin2DA & skin = *((Skin2DA*)VoxelTemplate::ConcreteCylinder.PolyHedra -> Skin);
		skin.W = 128;
		skin.H = 64;
		skin.Images.Insert(MediaDirectory.File("Images/ConcreteCube.png").LoadImage());
		skin.Done();
		PolyHedraVoxelData(*VoxelTemplate::ConcreteCylinder.PolyHedra, VoxelTemplate::ConcreteCylinder);
	}

	{
		ViewRayPolyHedra = PolyHedra::Generate::ConeC(8, 0.01f, 0.1f);
		PolyHedraManager.PlacePolyHedra(ViewRayPolyHedra);
	}
	//Perlin2D::DebugShow();
	//TestRandom();
}



unsigned int	ChunkInsertRange;
unsigned int	ChunkRemoveRange;

void MakeControls()
{
	std::cerr << "MakeControls()\n";
	{
		PauseMenu.Continue.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Continue);
		PauseMenu.Options.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Options);
		PauseMenu.Debug.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Debug);
		PauseMenu.Exit.ClickFunc.Assign(this, &ContextNoisePlane::PauseMenu_Exit);

		PauseMenu.Show();
		ControlManager.Window.ChildInsert(PauseMenu);
	}
	{
		OptionsMenu.FOV.ValueChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_FOV);
		OptionsMenu.FOV.SetValue(view.FOV.ToDegrees());

		OptionsMenu.Depth.ValueChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Depth);
		OptionsMenu.Depth.SetValue(1000.0f);

		ChunkInsertRange = 3;
		OptionsMenu.ChunkInsert.ValueChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Chunk_Insert);
		OptionsMenu.ChunkInsert.SetValue(ChunkInsertRange);

		ChunkRemoveRange = 5;
		OptionsMenu.ChunkRemove.ValueChangedFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Chunk_Remove);
		OptionsMenu.ChunkRemove.SetValue(ChunkRemoveRange);

		OptionsMenu.Back.ClickFunc.Assign(this, &ContextNoisePlane::OptionsMenu_Back);

		OptionsMenu.Hide();
		ControlManager.Window.ChildInsert(OptionsMenu);
	}
	{
		DebugMenu.FPS.Check.Check(true);

		DebugMenu.Generation3DComparison.ValueChangedFunc.Assign(this, &ContextNoisePlane::DebugMenu_Generation3DComparison);
		DebugMenu.Generation3DComparison.SetValue(Chunk::Generation3D_Comparison);

		DebugMenu.Generation3DFactor.ValueChangedFunc.Assign(this, &ContextNoisePlane::DebugMenu_Generation3DFactor);
		DebugMenu.Generation3DFactor.SetValue(Chunk::Generation3D_Factor);

		DebugMenu.Hide();
		ControlManager.Window.ChildInsert(DebugMenu);
	}
	{
		ItemVoxel * item;

		item = new ItemVoxel();
		item -> VoxelTemplate = &VoxelTemplate::ConcreteCylinder;
		Inventory.Slots[0][0].Item = item;

		item = new ItemVoxel();
		item -> VoxelTemplate = &VoxelTemplate::ConcreteCylinder;
		Inventory.Slots[1][1].Item = item;

		Inventory.Hide();
		ControlManager.Window.ChildInsert(Inventory);
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

	{
		ChunkManager.Texture.Bind();
		Container::Array<FileInfo> files({
			MediaDirectory.File("Images/OrientationCorners.png"),	// 0
			MediaDirectory.File("Images/Gray6.png"),				// 1
			MediaDirectory.File("Images/fancy_GreenDirt.png"),		// 2
			MediaDirectory.File("Images/fancy_RedWood.png"),		// 3
			MediaDirectory.File("Images/ConcreteCube.png"),			// 4
		});
		ChunkManager.Texture.Assign(VectorU2(128, 64), files);
		window.DefaultColor = ColorF4(0.6f, 0.85f, 0.9f);
		view.Depth.Color = window.DefaultColor;
	}

	MakeControls();

	// View
	Multiform_Depth.ChangeData(view.Depth);
	Multiform_FOV.ChangeData(view.FOV);
}
void Free() override
{
	GraphicsDelete();
}



void Draw()
{
	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();
	//PlaneManager.Draw();
	ChunkManager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	{
		ControlManager.UpdateSize(window.Size);
		ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
		ControlManager.Window.UpdateEntrys();
		ControlManager.Draw();
	}
	TextManager.Draw();

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	InventoryPolyHedraManager.ClearInstances();
	InventoryPolyHedraManager.UpdateInstances();
	InventoryPolyHedraManager.DrawFull();
}

typedef ::PolyHedra * PolyHedraPointer;
static void Toggle(bool & value) { value = !value; }
static void Toggle(PolyHedraPointer & polyhedra, PolyHedraPointer other)
{
	if (polyhedra == nullptr)
	{
		polyhedra = other;
	}
	else
	{
		polyhedra = nullptr;
	}
}

/*static VectorF2 BufferFull_To_NormalRel_Pos(VectorF2 pos, DisplaySize display_size)
{
	pos = pos / display_size.Buffer.Full; // NormalAbs
	pos = (pos * VectorF2(2, 2)) - VectorF2(1, 1); // NormalRel
	return pos;
}*/
/*static VectorF2 BufferFull_To_NormalRel_Size(VectorF2 size, DisplaySize display_size)
{
	size = size / display_size.Buffer.Full; // NormalAbs
	size = (size * VectorF2(2, 2)); // NormalRel
	return size;
}*/

// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void Frame(FrameTime frame_time) override
{
	if (window.KeyBoardManager[Keys::Escape].State == State::Press)
	{
		OptionsMenu.Hide();
		Inventory.Hide();
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
			if (!Inventory.IsVisible())
			{
				InventoryPolyHedraManager.MakeCurrent();
				Inventory.Show();
				PolyHedraManager.MakeCurrent();
			}
			else
			{
				Inventory.Hide();
			}
		}
	}

	if (PauseMenu.IsVisible() || OptionsMenu.IsVisible() || Inventory.IsVisible())
	{
		if (window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeFree(); }
	}
	else
	{
		if (!window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeLock(); }
	}

	if (window.KeyBoardManager[Keys::D1].State == State::Press) { Toggle(ViewRaySync); }
	if (window.KeyBoardManager[Keys::D2].State == State::Press) { Toggle(ChunkManager.ViewRayPolyHedra, ViewRayPolyHedra); }
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { Toggle(ChunkManager.VoxelBoxPolyHedra, VoxelCube); }

	if (window.KeyBoardManager[Keys::F8].State == State::Press)
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

	if (window.KeyBoardManager[Keys::F2].State == State::Press) { ViewBoxCollision = !ViewBoxCollision; }
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

	if (window.KeyBoardManager[Keys::F11].State == State::Press) { Toggle(ChunkManager.DontRemove); }
	if (window.KeyBoardManager[Keys::F10].State == State::Press) { Toggle(ChunkManager.DontInsert); }
	if (window.KeyBoardManager[Keys::F9].State == State::Press) { Toggle(ChunkManager.DontGenerate); }

	if (!OptionsMenu.IsVisible())
	{
		UpdateAroundView(frame_time);
	}
	{
		float pixel_rad = 1;
		UI::Control::Object obj;
		obj.Create();
		obj.Box().Min = window.Size.Buffer.Half - Point2D(pixel_rad, pixel_rad);
		obj.Box().Max = window.Size.Buffer.Half + Point2D(pixel_rad, pixel_rad);
		obj.Color() = ColorF4(1, 0, 1);
	}
	if (DebugMenu.VoxelChunkBoxes.Check.IsChecked())
	{
		unsigned int p = PolyHedraManager.FindPolyHedra(VoxelChunkCube);
		for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
		{
			PolyHedraObject chunk_box(p);
			chunk_box.Create(VoxelChunkCube);
			chunk_box.Trans().Position = (ChunkManager.Chunks[i] -> Index) * CHUNK_VALUES_PER_SIDE;
			chunk_box.ShowWire();
		}
	}
	{
		std::stringstream ss;

		if (DebugMenu.FPS.Check.IsChecked())
		{
			ss << "Frame Hz(" << frame_time.WantedFramesPerSecond << '|' << frame_time.ActualFramesPerSecond << ")\n";
			ss << "Frame D(" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")\n";
			ss << '\n';
		}

		if (DebugMenu.View.Check.IsChecked())
		{
			ss << "View " << view.Trans.Position << '\n';
			ss << "View " << ViewEntity.Vel << ' ' << ViewEntity.Vel.length() << '\n';
			//ss << "Box " << (ViewBox + view.Trans.Position) << '\n';
			VectorI3 chunk_idx = (view.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF();
			VectorU3 voxel_idx = VectorI3(view.Trans.Position.roundF()) - (chunk_idx * CHUNK_VALUES_PER_SIDE);
			ss << "Voxel " << chunk_idx << ' ' << voxel_idx << '\n';
			ss << '\n';

			ss << "None : " << (ViewCollisionSide.None) << '\n';
			ss << "PrevX: " << (ViewCollisionSide.PrevX) << '\n';
			ss << "PrevY: " << (ViewCollisionSide.PrevY) << '\n';
			ss << "PrevZ: " << (ViewCollisionSide.PrevZ) << '\n';
			ss << "NextX: " << (ViewCollisionSide.NextX) << '\n';
			ss << "NextY: " << (ViewCollisionSide.NextY) << '\n';
			ss << "NextZ: " << (ViewCollisionSide.NextZ) << '\n';
			ss << '\n';
		}

		ss << "DontInsert: " << ChunkManager.DontInsert << '\n';
		ss << "DontRemove: " << ChunkManager.DontRemove << '\n';
		ss << "DontGenerate: " << ChunkManager.DontGenerate << '\n';

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
			unsigned int chunks_t = ChunkManager.Chunks.Count(); // total
			unsigned int chunks_u = 0; // ungenerated
			unsigned int chunks_f = 0; // filled
			unsigned int chunks_e = 0; // empty
			unsigned int voxel_count = 0;
			for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
			{
				Chunk & chunk = *ChunkManager.Chunks[i];
				if (chunk.Done())
				{
					if (chunk.Data != nullptr)
					{
						chunks_f++;
						voxel_count += CHUNK_VALUES_PER_VOLM;
					}
					else
					{
						chunks_e++;
					}
				}
				else
				{
					chunks_u++;
				}
			}
			ss << "Chunks"
			 << ':' << chunks_t << '['
			 << 'E' << chunks_e << '|'
			 << 'F' << chunks_f << '|'
			 << 'U' << chunks_u << ']'
			 << '\n';
			ss << "Voxels:" << Seperated1000(voxel_count);
			ss << " * " << Memory1000ToString(sizeof(Voxel));
			ss << " = " << Memory1000ToString(voxel_count * sizeof(Voxel)) << '\n';
			ss << '\n';
		}

		if (DebugMenu.VoxelChunkMemory.Check.IsChecked())
		{
			unsigned long long main_count = 0;
			for (unsigned int i = 0; i < ChunkManager.Chunks.Count(); i++)
			{
				main_count += ChunkManager.Chunks[i] -> Buffer.Main.DrawCount;
			}
			ss << "Voxel BufferData: " << Seperated1000(main_count);
			ss << " (" << Memory1000ToString(main_count * sizeof(VoxelGraphics::MainData)) <<")\n";
		}

		UI::Text::Object text; text.Create();
		if (DebugMenu.IsVisible())
		{
			text.TextPosition().X = DebugMenu.Anchor.X.GetMinSize();
		}
		text.Color() = ColorF4(1, 1, 1);
		text.Bound().Min = Point2D();
		text.Bound().Max = window.Size.Buffer.Full;
		text.String() = ss.str();
	}

	static float time_sum = 0.0f;
	{
		InventoryPolyHedraManager.MakeCurrent();

		// as Transformation
		// scale to PixelSize ?
		// rotate
		// move to PixelPos ?
		// scale depends on DisplySize
		// calculate Scale here ?
		// also rotation changes DisplaySize Axis
		// scale needs to be after rotation and before position

		// Display Scaling is basically just ViewScaling
		// so use a second Matrix

		// Matrix0
		//  dont scale
		//  rotate
		//  dont move
		// Matrix1
		//  scale to PixelSize (different per Instance)
		//  move to PixelPos (different per Instance)
		// this could all be done with a customn Matrix
		// but the PolyHedraManager cant do that

		VectorF2	PixelSize(40, 40); // hardcoded in Shader
		VectorF2	size = window.Size.Buffer.SizeFullToNormalRel(PixelSize);

		VectorF2	PixelPos;
		PixelPos.X = window.Size.Buffer.Full.X - 40;
		PixelPos.Y = 40;

		VectorF2	pos = window.Size.Buffer.PosFullToNormalRel(PixelPos);

		{
			PolyHedraObject obj(VoxelTemplate::ConcreteCylinder.PolyHedra);
			obj.Trans().Position.X = pos.X / size.X;
			obj.Trans().Position.Y = pos.Y / size.Y;
			obj.Trans().Rotation.X1 = Angle::Degrees(15);
			obj.Trans().Rotation.Y2 = Angle::Radians(time_sum);
		}

		/*PixelPos = window.MouseManager.CursorPosition().Buffer.Corner;
		{
			pos = window.Size.Buffer.PosFullToNormalRel(PixelPos);
			PolyHedraObject obj(VoxelTemplate_PolyHedra);
			obj.Trans().Position.X = +pos.X / size.X;
			obj.Trans().Position.Y = -pos.Y / size.Y;
			obj.Trans().Rotation.X1 = Angle::Degrees(15);
			obj.Trans().Rotation.Y2 = Angle::Radians(time_sum);
		}*/
	
		time_sum += frame_time.Delta;
		PolyHedraManager.MakeCurrent();
	}

	Draw();
}

void Resize(DisplaySize display_size) override
{
	::Inventory::WindowSize = display_size;
	Multiform_DisplaySize.ChangeData(display_size);
}



// make these virtual and put them in Base
void MouseScroll(ScrollArgs args) override { (void)args; }
void MouseClick(ClickArgs args) override { ControlManager.RelayClick(args); }
void MouseDrag(DragArgs args) override { ControlManager.RelayCursorDrag(args); }

void KeyBoardKey(KeyArgs args) override { (void)args; }
};

ContextBase * newContextNoisePlane()
{
	return new ContextNoisePlane();
}
