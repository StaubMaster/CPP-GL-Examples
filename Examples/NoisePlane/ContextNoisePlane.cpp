#include "ContextNoisePlane.hpp"
#include "new.hpp"

// PolyHedra
#include "PolyHedra/Parser.hpp"

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Generics/Container/Array.hpp"

// Debug
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Debug.hpp"
#include "ValueType/_Show.hpp"
#include "ValueType/_Include.hpp"

// Voxel
#include "ContainerLock/AccessTypeGuard.hpp"
#include "ContainerLock/AssignTypeGuard.hpp"

// Voxel
#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Map.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"
#include "3D/Voxel/Pallet/Geometry/Map.hpp"

// Math
#include <math.h>



#include "main_static.cpp"





static ValueAccumulator<float>		FrameTime_(64);
static ValueAccumulator<float>		FrameTime_Input(64);
static ValueAccumulator<float>		FrameTime_ViewUpdate(64);
static ValueAccumulator<float>		FrameTime_ChunkBoxes(64);
static ValueAccumulator<float>		FrameTime_ChunkHereBox(64);
static ValueAccumulator<float>		FrameTime_Text(64);
static ValueAccumulator<float>		FrameTime_Draw(64);
static ValueAccumulator<float>		FrameTime_DrawThread(64);

static ValueAccumulator<float>		FrameTime_ViewUpdate_CollisionTime(64);
static ValueAccumulator<float>		FrameTime_ViewUpdate_RayTime(64);

static ValueAccumulator<float>		FrameTime_Text_Assamble(64);
static ValueAccumulator<float>		FrameTime_Text_Instance(64);

static ValueAccumulator<float>		TextTime_TestFPS(64);
static ValueAccumulator<float>		TextTime_ThreadTime(64);
static ValueAccumulator<float>		TextTime_ChunkManagerTime(64);
static ValueAccumulator<float>		TextTime_View(64);
static ValueAccumulator<float>		TextTime_ChunkHere(64);
static ValueAccumulator<float>		TextTime_ChunkRange(64);
static ValueAccumulator<float>		TextTime_VoxelChunkMemory(64);
static ValueAccumulator<float>		TextTime_VoxelChunkMemory_Wait(64);
static ValueAccumulator<float>		TextTime_VoxelChunkMemory_Loop(64);
static ValueAccumulator<float>		TextTime_VoxelChunkMemory_Show(64);

static ValueAccumulator<float>		FrameTime_Draw_DrawTotal(64);
static ValueAccumulator<float>		FrameTime_Draw_DrawPolyHedra(64);
static ValueAccumulator<float>		FrameTime_Draw_UniformChunk(64);
static ValueAccumulator<float>		FrameTime_Draw_DrawChunk(64);
static ValueAccumulator<float>		FrameTime_Draw_DrawControl(64);
static ValueAccumulator<float>		FrameTime_Draw_MakeText(64);
static ValueAccumulator<float>		FrameTime_Draw_DrawText(64);



void ContextNoisePlane::NewPolyHedra_ChangeMedia()
{
	// NewPolyHedra
	{
		// PolyHedraManager
		{
			{
				PalletManager.BufferFullLayout.Position.Change(0);
				PalletManager.BufferFullLayout.Normal.Change(1);
				PalletManager.BufferFullLayout.Texture.Change(2);
				PalletManager.BufferFullLayout.Color.Change(15);
			}
			{
				PalletManager.BufferWireLayout.Pos.Change(0);
				PalletManager.BufferWireLayout.Col.Change(1);
			}
			PolyHedraManager.PalletManager = &PalletManager;
		}
		// ObjectManagerBasic
		{
			{
				ObjectManagerBasic.ShaderFull.Change({
					MediaDirectory.File("Shaders/PolyHedra/Default.vert"),
					MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag"),
				});
				ShaderLayoutView3D * layout = new ShaderLayoutView3D();
				ObjectManagerBasic.ShaderFull.AssignLayout(layout);
				MultiformLayout.Find(layout);
			}
			{
				ObjectManagerBasic.ShaderWire.Change({
					MediaDirectory.File("Shaders/Basic3D/Wire.vert"),
					MediaDirectory.File("Shaders/Basic3D/Wire.frag"),
				});
				ShaderLayoutView3D * layout = new ShaderLayoutView3D();
				ObjectManagerBasic.ShaderWire.AssignLayout(layout);
				MultiformLayout.Find(layout);
			}
			{
				NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(7);
				ObjectManagerBasic.BufferFullLayout = layout;
			}
			{
				NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(-1);
				ObjectManagerBasic.BufferWireLayout = layout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerBasic);
		}
		// ObjectManagerUI
		{
			{
				ObjectManagerUI.ShaderFull.Change({
					MediaDirectory.File("Shaders/UI/PHFull.vert"),
					MediaDirectory.File("Shaders/UI/PHFull.frag"),
				});
				ShaderLayoutDisplay * layout = new ShaderLayoutDisplay();
				ObjectManagerUI.ShaderFull.AssignLayout(layout);
				MultiformLayout.Find(layout);
			}
			{
				ShaderLayoutDisplay * layout = new ShaderLayoutDisplay();
				ObjectManagerUI.ShaderWire.AssignLayout(layout);
				MultiformLayout.Find(layout);
			}
			{
				NewPolyHedra::UserInterface::BufferLayout * layout = new NewPolyHedra::UserInterface::BufferLayout();
				layout -> Size.Change(3);
				layout -> Pos.Change(4);
				layout -> Rot.Change(5);
				layout -> Scale.Change(8);
				ObjectManagerUI.BufferFullLayout = layout;
			}
			{
				NewPolyHedra::UserInterface::BufferLayout * layout = new NewPolyHedra::UserInterface::BufferLayout();
				ObjectManagerUI.BufferWireLayout = layout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerUI);
		}
	}
}



ContextNoisePlane::~ContextNoisePlane()
{ }
ContextNoisePlane::ContextNoisePlane()
	: ContextBase()
	, MultiformLayout()
	, PolyHedraManager()
	, PalletManager()
	, ObjectManagerBasic()
	, ObjectManagerUI()
	, UIManager()
//	, PlaneManager()
	, ChunkManager()
	, MenuMain()
	, MenuPause(*this)
	, MenuOptions(*this)
	, MenuDebug(*this)
	, Inventory(VectorU2(10, 5))
	, InventoryUI()
	, HotBar(VectorU2(10, 1))
	, HotBarUI()
	, AuxThread0(&ContextNoisePlane::AuxThread0Func, this)
	, AuxThread0Time(64)
{
	MediaDirectory = DirectoryInfo("../../media/");

	NewPolyHedra_ChangeMedia();

	AuxThreadBase::ThreadName = "DrawThread";
	Container::Array<Uniform::Layout*> layouts({
		&UIManager.ControlManager.ShaderLayout,
		&UIManager.TextManager.ShaderLayout,
//		&PlaneManager.Shader,
		&ChunkManager.ShaderLayoutU,
		&ChunkManager.ShaderLayoutF,
	});
	MultiformLayout.Find(layouts);
}



bool ContextNoisePlane::VoxelClear_Is() const
{
	return (VoxelClear_Progress != 0xFFFFFFFF);
}
void ContextNoisePlane::VoxelClear_None()
{
	VoxelClear_Progress = 0xFFFFFFFF;
	VoxelClear_Pallet = nullptr;
	VoxelClear_Tool = nullptr;
}
void ContextNoisePlane::VoxelClear_Clear(ChunkVoxelIndex idx)
{
	VoxelClear_Progress = 0;
	VoxelClear_Index = idx;
	VoxelClear_Tool = dynamic_cast<ItemTool*>(HotBar.Items[0]);

	AccessLockedChunk chunk = ChunkManager.FindAccess(VoxelClear_Index.Chunk);
	const Voxel & voxel = (*chunk).Voxels[VoxelClear_Index.Voxel];
	if (!voxel.IsEmpty())
	{
		VoxelClear_Pallet = &voxel.ToPallet();
	}
	else
	{
		VoxelClear_Pallet = nullptr;
	}
}
void ContextNoisePlane::VoxelClear_Continue(const ChunkVoxelIndex & other)
{
	if (VoxelClear_Is())
	{
		if (
			(other.Chunk == VoxelClear_Index.Chunk).All(true) &&
			(other.Voxel == VoxelClear_Index.Voxel).All(true)
		)
		{
			if (VoxelClear_Progress >= VoxelClear_Required)
			{
				Voxel voxel;
				// why not .FindAssign() ?
				AccessLockedChunk chunk_access = ChunkManager.FindAccess(VoxelClear_Index.Chunk);
				if (chunk_access.Is())
				{
					AssignLockedChunk chunk_assign = chunk_access.ToAssign();
					(*chunk_assign).ClearVoxel(VoxelClear_Index.Voxel, voxel);
				}
				VoxelClear_None();
			}
			else
			{
				if (VoxelClear_Tool != nullptr && VoxelClear_Pallet != nullptr)
				{
					if (VoxelClear_Tool -> Material == VoxelClear_Pallet -> Material)
					{
						VoxelClear_Progress += VoxelClear_Tool -> Multiplier;
					}
					else
					{
						VoxelClear_Progress++;
					}
				}
				else
				{
					VoxelClear_Progress++;
				}
			}
		}
		else
		{
			VoxelClear_Clear(other);
		}
	}
	else
	{
		VoxelClear_Clear(other);
	}
}
void ContextNoisePlane::VoxelClear_Show(std::stringstream & ss) const
{
	if (VoxelClear_Is())
	{
		ss << "VoxelClear:\n";
		ss << VoxelClear_Index.Chunk << " :Chunk\n";
		ss << VoxelClear_Index.Voxel << " :Voxel\n";
		ss << VoxelClear_Progress << " :Progress\n";
	}
}



/*static void VectorComponents(const VectorF3 & vec, const VectorF3 & other, VectorF3 & parallel, VectorF3 & perpendicular)
{
	float dot = vec.dot(other);
	parallel = (vec / vec.length2()) * dot;
	perpendicular = other - parallel;
}*/



void ContextNoisePlane::ViewUpdate_Done()
{
	if (View_Distance == 0.0f)
	{
		MultiformLayout.View.ChangeData(Matrix4x4::TransformReverse(View.Trans));
	}
	else
	{
		MultiformLayout.View.ChangeData(Matrix4x4::TransformReverse(
			Trans3D(View.Trans.Position - View.Trans.Rotation.forward(VectorF3(0, 0, View_Distance)), View.Trans.Rotation)
		));
	}
}
void ContextNoisePlane::ViewUpdate_Intangible(Trans3D change, FrameTime frame_time)
{
	change.Position *= View_MoveSpeed;
	if (window[Keys::LeftControl] == State::Down)
	{
		change.Position *= View_MoveSpeedMultiplier;
	}

	View.Trans.Position += change.Position * frame_time.Delta;
	View.Trans.Rotation += change.Rotation * frame_time.Delta;
	View.Trans.Rotation.X1.clampPI();

	ViewEntity.Pos = View.Trans.Position;
	ViewEntity.Vel = change.Position;
}
void ContextNoisePlane::ViewUpdate_Physics(VectorF3 change)
{
	if (ViewEntity_CollisionSide.PrevY)
	{
		if (change.Y > 0.0f)
		{
			ViewEntity.Vel.Y += 16.0f;
		}
		change.Y = 0.0f;

		VectorF3 flat(ViewEntity.Vel.X, 0.0f, ViewEntity.Vel.Z);

		float limit = 0.0f;
		if (change.length() != 0.0f)
		{
			if (window[Keys::LeftControl] == State::Down)
			{
				limit = ViewEntity_MoveLimitFast;
			}
			else
			{
				limit = ViewEntity_MoveLimitSlow;
			}
		}
		(void)limit;

		/* accel and decel
			accel:
				should be change
				so it moves in the direction that is wanted
			decel:
				should slow you down
				when turing
				it currently slows you down based on how fast you turn
				so if you turn 90 degreees, your speed goes to 0
				this feels terrible
			the current speed should be redirected towards change

			just add change to speed and limit ?
			this feels floaty
		*/

		//VectorF3 accel;
		//VectorF3 decel;

		/*{
			float flat_len2 = flat.length2();
			if (flat_len2 != 0.0f)
			{
				float len2 = change.length2();
				if (len2 != 0.0f)
				{
					float dot = flat.dot(change);
					accel = change;
					decel = flat - (change / len2) * dot;
				}
				else
				{
					decel = flat;
				}
			}
			else
			{
				accel = change;
			}
		}*/

		/*{
			float accel_speed = ViewEntity_MoveChange;
			float decel_speed = ViewEntity_MoveChange * 8.0f;
			float flat_speed = flat.length();
			{
				float diff = limit - flat_speed;
				if (diff < 0.0f)
				{
					diff = 0.0f;
				}
				if (diff > accel_speed)
				{
					diff = accel_speed;
				}
				accel = accel.normalize() * diff;
			}
			{
				float diff = flat_speed;
				if (diff < 0.0f)
				{
					diff = 0.0f;
				}
				if (diff > decel_speed)
				{
					diff = decel_speed;
				}
				decel = decel.normalize() * diff;
			}
			// this feels terrible
		}*/

		//ViewEntity.Vel = ViewEntity.Vel + accel - decel;

		float flat_speed = flat.length();
		float change_speed = ViewEntity_MoveChange;
		float diff_speed = limit - flat_speed;
		if (diff_speed < 0.0f)
		{
			diff_speed = 0.0f;
		}
		if (diff_speed > change_speed)
		{
			diff_speed = change_speed;
		}
		change = change.normalize() * diff_speed;

		ViewEntity.Vel += change;
	}
	else
	{
		// use air friciton for movement
		change.Y = 0.0f;
		change *= 0.1f;
	}

	ViewEntity.Vel = ViewEntity.Vel
		- PhysicsContext_Fluid.Drag(ViewEntity.Vel, 1.0f, 1.0f)
		+ PhysicsContext_Gravity.Vector()
	;
}
void ContextNoisePlane::ViewUpdate_Colliding(FrameTime frame_time)
{
	DisplayBoxEntityVoxels(PalletManager.FindMakePallet(VoxelCube), ChunkManager, ViewEntity, frame_time);
	DisplayBoxEntity(ViewEntity, *ViewEntity_PolyHedra);
	{
		Container::Binary<BoxF3> boxes;

		BoxF3 collision_range = ViewEntity.Box + ViewEntity.Pos;
		collision_range.Consider(ViewEntity.Box.Min + ViewEntity.Pos + (ViewEntity.Vel * frame_time.Delta));
		collision_range.Consider(ViewEntity.Box.Max + ViewEntity.Pos + (ViewEntity.Vel * frame_time.Delta));
		collision_range = collision_range - VectorF3(0.5f);

		LoopI3 loop(collision_range.Min.round().ToI(), Bool3(false), collision_range.Max.round().ToI(), Bool3(false));
		for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
		{
			ChunkVoxelIndex idx(i);
			AccessLockedChunk chunk = ChunkManager.FindAccess(idx.Chunk);
			if (!chunk.Is()) { continue; }
			const Voxel * voxel = (*chunk).FindVoxelOrNull(idx.Voxel);
			if (voxel != nullptr && !(voxel -> IsEmpty()))
			{
				boxes.Insert(
					BoxF3(
						(i + VectorI3(0, 0, 0)).ToF(),
						(i + VectorI3(1, 1, 1)).ToF()
					)
				);
			}
		}

		ViewEntity_CollisionSide = ViewEntity.Collide(boxes.ToArray(), frame_time.Delta);
	}
	DisplayBoxEntity(ViewEntity, *ViewEntity_PolyHedra);
}

void ContextNoisePlane::ViewRay_Update()
{
	ViewRay.Pos = View.Trans.Position;
	ViewRay.Dir = View.Trans.Rotation.forward(VectorF3(0, 0, 1));
	{
		VectorI3 ranks = ViewRay.Dir.abs().RankDimensions();
		     if (ranks.X == 0) { if (ViewRay.Dir.X > 0) { ViewRay_Axis0 = AxisRel::NextX; } else { ViewRay_Axis0 = AxisRel::PrevX; } }
		else if (ranks.Y == 0) { if (ViewRay.Dir.Y > 0) { ViewRay_Axis0 = AxisRel::NextY; } else { ViewRay_Axis0 = AxisRel::PrevY; } }
		else if (ranks.Z == 0) { if (ViewRay.Dir.Z > 0) { ViewRay_Axis0 = AxisRel::NextZ; } else { ViewRay_Axis0 = AxisRel::PrevZ; } }
		if      (ranks.X == 1) { if (ViewRay.Dir.X > 0) { ViewRay_Axis1 = AxisRel::NextX; } else { ViewRay_Axis1 = AxisRel::PrevX; } }
		else if (ranks.Y == 1) { if (ViewRay.Dir.Y > 0) { ViewRay_Axis1 = AxisRel::NextY; } else { ViewRay_Axis1 = AxisRel::PrevY; } }
		else if (ranks.Z == 1) { if (ViewRay.Dir.Z > 0) { ViewRay_Axis1 = AxisRel::NextZ; } else { ViewRay_Axis1 = AxisRel::PrevZ; } }
		if      (ranks.X == 2) { if (ViewRay.Dir.X > 0) { ViewRay_Axis2 = AxisRel::NextX; } else { ViewRay_Axis2 = AxisRel::PrevX; } }
		else if (ranks.Y == 2) { if (ViewRay.Dir.Y > 0) { ViewRay_Axis2 = AxisRel::NextY; } else { ViewRay_Axis2 = AxisRel::PrevY; } }
		else if (ranks.Z == 2) { if (ViewRay.Dir.Z > 0) { ViewRay_Axis2 = AxisRel::NextZ; } else { ViewRay_Axis2 = AxisRel::PrevZ; } }
		// what if same ranks ?
	}
}
void ContextNoisePlane::ViewRay_Hit()
{
	ViewHit = ChunkManager.HitVoxel(ViewRay);
	if (ViewHit.Valid())
	{
		{
			//PolyHedraObject voxel_box_obj(VoxelCube);
			NewPolyHedra::Basic3D::Object voxel_box_obj(VoxelCube);
			//voxel_box_obj.Trans().Position = idx;
			//voxel_box_obj.Trans().Position = ViewHit.Index;
			voxel_box_obj.Data().Trans.Position = ViewHit.Index.ToF();
			voxel_box_obj.ShowWire();
		}
		{
			ViewHit_Axis0 = ViewHit.Side;
			AxisAbs axis = AxisRelToAxisAbs(ViewHit_Axis0);
			if (axis == AxisAbs::None) { ViewHit_Axis1 = AxisRel::None; }
			else if (axis != AxisRelToAxisAbs(ViewRay_Axis2)) { ViewHit_Axis1 = ViewRay_Axis2; }
			else if (axis != AxisRelToAxisAbs(ViewRay_Axis1)) { ViewHit_Axis1 = ViewRay_Axis1; }
			else if (axis != AxisRelToAxisAbs(ViewRay_Axis0)) { ViewHit_Axis1 = ViewRay_Axis0; }
			else { ViewHit_Axis1 = AxisRel::None; }
		}
	}
}
void ContextNoisePlane::ViewRay_HitDo()
{
	if (MenuPause.IsInteractible() || MenuOptions.IsInteractible() || InventoryUI.IsInteractible()) { return; }

	if (ViewHit.Valid())
	{
		// Side: make part of VoxelHit ?
		// determine place_axis_1 based on where on the face was clicked ?
		// top of face orients to point to top and so on

		/*if (window.MouseManager[MouseButtons::MouseL] == State::Press)
		{
			ChunkVoxelIndex idx = ViewHit.Index;
			Voxel voxel;
			// why not .FindAssign() ?
			AccessLockedChunk chunk0 = ChunkManager.FindAccess(idx.Chunk);
			if (chunk0.Is())
			{
				AssignLockedChunk chunk1 = chunk0.ToAssign();
				(*chunk1).ClearVoxel(idx.Voxel, voxel);
			}
			Voxel_Clear_Progress = 0;
		}*/
		if (window.MouseManager[MouseButtons::MouseL] == State::Down)
		{
			VoxelClear_Continue(ViewHit.Index);
		}
		else
		{
			VoxelClear_Clear(ViewHit.Index);
		}

		if (window.MouseManager[MouseButtons::MouseR] == State::Press)
		{
			VectorI3 hit_idx = ViewHit.Index;
			if (ViewHit_Axis0 == AxisRel::NextX) { hit_idx.X += 1; }
			if (ViewHit_Axis0 == AxisRel::NextY) { hit_idx.Y += 1; }
			if (ViewHit_Axis0 == AxisRel::NextZ) { hit_idx.Z += 1; }
			if (ViewHit_Axis0 == AxisRel::PrevX) { hit_idx.X -= 1; }
			if (ViewHit_Axis0 == AxisRel::PrevY) { hit_idx.Y -= 1; }
			if (ViewHit_Axis0 == AxisRel::PrevZ) { hit_idx.Z -= 1; }

			if (HotBar.Items[VectorU2(0, 0)] != nullptr)
			{
				{
					ItemVoxel * item = dynamic_cast<ItemVoxel*>(HotBar.Items[VectorU2(0, 0)]);
					if (item != nullptr && item -> VoxelPallet != nullptr)
					{
						Voxel voxel = item -> VoxelPallet -> ToVoxel(ViewHit_Axis0, ViewHit_Axis1);
						ChunkVoxelIndex idx(hit_idx);
						AssignLockedChunk chunk = ChunkManager.FindAccess(idx.Chunk).ToAssign();
						if (chunk.Is())
						{
							(*chunk).PlaceVoxel(idx.Voxel, voxel);
						}
					}
				}
			}
		}
	}
}
void ContextNoisePlane::ViewRay_Show()
{
	std::stringstream ss;
	ss << "ViewRay\n";
	ss << ViewRay_Axis0 << " :RayAxis0\n";
	ss << ViewRay_Axis1 << " :RayAxis1\n";
	ss << ViewRay_Axis2 << " :RayAxis2\n";

	if (ViewHit.Valid())
	{
		ChunkVoxelIndex idx(ViewHit.Index);
		ss << ViewHit.Index << '\n';
		ss << idx.Chunk << '\n';
		ss << idx.Voxel << '\n';
		ss << ViewHit_Axis0 << " :HitAxis0\n";
		ss << ViewHit_Axis1 << " :HitAxis1\n";

		// Voxel Info
		{
			AccessLockedChunk chunk = ChunkManager.FindAccess(idx.Chunk);
			const Voxel * voxel = (*chunk).FindVoxelOrNull(idx.Voxel);
			if (voxel != nullptr)
			{
				if (!(voxel -> IsEmpty()))
				{
					const VoxelPallet & pallet = voxel -> ToPallet();
					ss << (voxel -> Orientation.GetDiag()) << " :Diag\n";
					ss << (voxel -> Orientation.GetFlip()) << " :Flip\n";
					ss << (pallet.Name) << " :Pallet\n";
				}
				else
				{
					ss << "empty";
				}
			}
			else
			{
				ss << "null";
			}
			ss << '\n';
		}
	}

	VoxelClear_Show(ss);

	UI::Text::Object text; text.Create();
	text.Text() = ss.str();
	text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
	text.AlignTopRight(); // take DisplaySize
	text.Bound().Min = VectorF2();
	text.Bound().Max = window.Size.Buffer.Full;
	text.Color() = ColorF4(1, 1, 1);
}

void ContextNoisePlane::ViewUpdate(Trans3D change, FrameTime frame_time)
{
	// sperate applying change and moving
	// when intangible, change view directly

	StopWatch sw;
	sw.Start();
	if (View_IsTangible)
	{
		ViewUpdate_Physics(change.Position);
		View.Trans.Rotation += change.Rotation * frame_time.Delta;
		View.Trans.Rotation.X1.clampPI();
		ViewUpdate_Colliding(frame_time);
		View.Trans.Position = ViewEntity.Pos;
	}
	else
	{
		ViewUpdate_Intangible(change, frame_time);
	}
	ViewUpdate_Done();
	sw.Stop();
	FrameTime_ViewUpdate_CollisionTime.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	ViewRay_Update();
	ViewRay_Hit();
	ViewRay_HitDo();
	ViewRay_Show();
	sw.Stop();
	FrameTime_ViewUpdate_RayTime.NewValue(sw.ElapsedTime());
}





thread_local const char * AuxThreadBase::ThreadName = "ThreadName";

void ContextNoisePlane::AuxThread0Func()
{
	// do CenterChange here

	AuxThreadBase::ThreadName = "AuxThread0";
	StopWatch sw;
	while (!AuxThread0Term)
	{
		if (!AuxThread0Idle)
		{
			sw.Clear(); sw.Start();
			ChunkManager.ChangeCenter((View.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF().ToI());
			//ChunkManager.RemoveAround();
			//ChunkManager.InsertAround();
			ChunkManager.UpdateChunksContainer();
			sw.Stop();
			AuxThread0Time.NewValue(sw.ElapsedTime());
		}
	}
}



void ContextNoisePlane::Init_Maps()
{
	// VoxelPalletGeometryMap
	{
		VoxelPalletGeometryMap & map = VoxelPalletGeometryMap::StaticMap;

		VoxelPalletGeometry & CubeDiag = map.New("CubeDiag");
		CubeDiag.InitU_CubeDiag();
		CubeDiag.InitF_CubeDiag();

		VoxelPalletGeometry & CubeAxisY = map.New("CubeAxisY");
		CubeAxisY.InitU_CubeAxisY();
		CubeAxisY.InitF_CubeAxisY();

		VoxelPalletGeometry & AxisStar = map.New("AxisStar");
		AxisStar.InitU_CubeDiag();
		AxisStar.InitF_AxisStar();

		VoxelPalletGeometry & PrismY8 = map.New("PrismY8");
		PrismY8.InitU_CubeAxisY();
		PrismY8.InitF_PrismY8();

		VoxelPalletGeometry & Slope = map.New("Slope");
		Slope.InitU_CubeDiag();
		Slope.InitF_Slope();
	}

	// VoxelPalletMap
	{
		VoxelPalletMap & map = VoxelPalletMap::StaticMap;

		const VoxelPalletGeometry & cube_diag   = VoxelPalletGeometryMap::StaticMap["CubeDiag"];
		const VoxelPalletGeometry & cube_axis_Y = VoxelPalletGeometryMap::StaticMap["CubeAxisY"];
		const VoxelPalletGeometry & axis_star   = VoxelPalletGeometryMap::StaticMap["AxisStar"];
		const VoxelPalletGeometry & cylinder    = VoxelPalletGeometryMap::StaticMap["PrismY8"];
		const VoxelPalletGeometry & slope       = VoxelPalletGeometryMap::StaticMap["Slope"];

		map.New("OrientationCube", cube_diag, VoxelMaterialType::None).TextureAxis(
			MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
		);
		map.New("OrientationAxisStar", axis_star, VoxelMaterialType::None).TextureAxis(
			MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
		);
		map.New("OrientationCylinder", cylinder, VoxelMaterialType::None).TextureAxis(
			MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
		);
		map.New("OrientationSlope", slope, VoxelMaterialType::None).TextureAxis(
			MediaDirectory.File("Images/Voxel/Orientation0/PrevX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/PrevZ.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextX.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextY.png"),
			MediaDirectory.File("Images/Voxel/Orientation0/NextZ.png")
		);

		map.New("DebugR", cube_diag, VoxelMaterialType::None).TextureAll(
			MediaDirectory.File("Images/Voxel/Debug/R.png")
		);
		map.New("DebugG", cube_diag, VoxelMaterialType::None).TextureAll(
			MediaDirectory.File("Images/Voxel/Debug/G.png")
		);
		map.New("DebugB", cube_diag, VoxelMaterialType::None).TextureAll(
			MediaDirectory.File("Images/Voxel/Debug/B.png")
		);

		map.New("Gray", cube_diag, VoxelMaterialType::Stone).TextureAll(
			MediaDirectory.File("Images/Voxel/Gray.png")
		);

		map.New("Grass", cube_diag, VoxelMaterialType::Dirt).TextureAll(
			MediaDirectory.File("Images/Voxel/Grass.png")
		);
		map.New("Dirt", cube_diag, VoxelMaterialType::Dirt).TextureAll(
			MediaDirectory.File("Images/Voxel/Dirt.png")
		);

		map.New("RedLog", cylinder, VoxelMaterialType::Wood).TexturePrismY(
			MediaDirectory.File("Images/Voxel/fancy_RedWood_Base.png"),
			MediaDirectory.File("Images/Voxel/fancy_RedWood_Belt.png")
		);
		map.New("Log", cube_axis_Y, VoxelMaterialType::Wood).TexturePrismY(
			MediaDirectory.File("Images/Voxel/Log_Base.png"),
			MediaDirectory.File("Images/Voxel/Log_Belt.png")
		);
		map.New("Leaves", cube_diag, VoxelMaterialType::None).TextureAll(
			MediaDirectory.File("Images/Voxel/Leave1.png")
		);

		map.New("Sand", cube_diag, VoxelMaterialType::Powder).TextureAll(
			MediaDirectory.File("Images/Voxel/Sand.png")
		);
		map.New("Snow", cube_diag, VoxelMaterialType::Powder).TextureAll(
			MediaDirectory.File("Images/Voxel/Snow.png")
		);
		map.New("Water", cube_diag, VoxelMaterialType::None).TextureAll(
			MediaDirectory.File("Images/Voxel/Water.png")
		);

		map.New("ConcreteCube", cube_diag, VoxelMaterialType::Stone).TextureAll(
			MediaDirectory.File("Images/Voxel/Concrete_0.png")
		);
		map.New("ConcreteCylinder", cylinder, VoxelMaterialType::Stone).TextureAll(
			MediaDirectory.File("Images/Voxel/Concrete_0.png")
		);
	}

	{
		Structure::Default();
	}
}

void ContextNoisePlane::Make()
{
	{
		//window.DefaultColor = ColorF4(0.6f, 0.85f, 0.9f);
		//window.DefaultColor = ColorF4(0.5f, 0.5f, 0.5f);
		window.DefaultColor = ColorF4(0.25f, 0.25f, 0.25f);
		//window.DefaultColor = ColorF4(0.1f, 0.1f, 0.1f);
		View.Depth.Color = window.DefaultColor;
		View.Depth.Range.SetMin(0.5f);

		LightAmbient = LightBase(0.2f, ColorF4(1.0f, 1.0f, 1.0f));
		LightSolar = LightDirection(1.0f, ColorF4(1.0f, 1.0f, 1.0f), !VectorF3(1.0f, -1.0f, 0.0f));
		LightSpot = ::LightSpot(0.0f, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(), VectorF3(), RangeF(0.1f, 1.0f));
	}

	ViewEntity.Pos = VectorF3(0.5f, 0.5f, 0.5f);
	ViewEntity.Box = BoxF3(
		VectorF3(-0.4f, -1.7f, -0.4f),
		VectorF3(+0.4f, +0.1f, +0.4f)
	);

	{
		// this is needed to prevent compiler from complaining about multiple definitions of Bool2D
		Image img(VectorU2(1, 1));
		PolyHedra * picture = PolyHedraGenerate::ImageQuad(img);
		delete picture;
	}

	// 3 Cuboids. implement Scaling for Transformations
	{
		VoxelCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelCube, BoxF3(VectorF3(0.0f), VectorF3(1.0f)));
		PalletManager.FindMakePallet(VoxelCube);
	}
	{
		VoxelChunkCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelChunkCube, BoxF3(VectorF3(0.1f), VectorF3(CHUNK_VALUES_PER_SIDE - 0.1f)));
		PalletManager.FindMakePallet(VoxelChunkCube);
	}
	{
		ViewEntity_PolyHedra = new PolyHedra();
		PolyHedraBoxEdges(*ViewEntity_PolyHedra, ViewEntity.Box);
		PalletManager.FindMakePallet(ViewEntity_PolyHedra);
	}

	Init_Maps();

	/*{
		ViewRayPolyHedra = PolyHedra::Generate::ConeC(8, 0.01f, 0.1f);
		PolyHedraManager.PlacePolyHedra(ViewRayPolyHedra);
	}*/
}



void ContextNoisePlane::MakeControls()
{
	std::cerr << "MakeControls()\n";
	// Pause
	{
		MenuPause.Show();
		UIManager.WindowControl.ChildInsert(MenuPause);
	}
	// Options
	{
		//MenuOptions.FPS.SetValueX(window.FrameTime.WantedFramesPerSecond);
		MenuOptions.FPS.SetValueX(64);
		MenuOptions.FOV.SetValueX(View.FOV.ToDegrees());

		//MenuOptions.Depth.SetValueX(100.0f); // get Depth. also depth works weirdly ?
		MenuOptions.Depth.SetValueX(1000.0f); // get Depth. also depth works weirdly ?
		MenuOptions.DepthRange.SetValueX(View.Depth.Range.GetMin());

		// Remove range should never be less then Insert
		// make RemoveRange = InsertRange * 2 ?
		// make RemoveRange = InsertRange + n ?

		MenuOptions.Hide();
		UIManager.WindowControl.ChildInsert(MenuOptions);
	}
	// Debug
	{
		MenuDebug.FPS.Check.Check(true);
		//MenuDebug.VoxelChunkMemory.Check.Check(true);

		MenuDebug.Hide();
		UIManager.WindowControl.ChildInsert(MenuDebug);
	}
	// Inventory
	{
		unsigned int idx = 0;
		for (unsigned int i = 0; i < VoxelPalletMap::StaticMap.Data.Count(); i++)
		{
			Inventory.Items[idx] = new ItemVoxel(VoxelPalletMap::StaticMap.Data[i]); idx++;
		}
		Inventory.Items[idx] = new ItemTool(PolyHedraParser::Load(MediaDirectory.File("YMT/Tools/Stick.polyhedra") , nullptr, nullptr),  VoxelMaterialType::None,  1.0f); idx++;
		Inventory.Items[idx] = new ItemTool(PolyHedraParser::Load(MediaDirectory.File("YMT/Tools/Spade.polyhedra") , nullptr, nullptr),  VoxelMaterialType::Dirt,  4.0f); idx++;
		Inventory.Items[idx] = new ItemTool(PolyHedraParser::Load(MediaDirectory.File("YMT/Tools/Pick.polyhedra")  , nullptr, nullptr),   VoxelMaterialType::Stone, 4.0f); idx++;
		Inventory.Items[idx] = new ItemTool(PolyHedraParser::Load(MediaDirectory.File("YMT/Tools/Hammer.polyhedra"), nullptr, nullptr), VoxelMaterialType::None,  4.0f); idx++;
		Inventory.Items[idx] = new ItemTool(PolyHedraGenerate::SphereY(6, 12, 4.0f), VoxelMaterialType::None, 1.0f); idx++;
		InventoryUI.IsResizable = false;
		InventoryUI.IsMovable = false;
		InventoryUI.Change(&Inventory);
		InventoryUI.Hide();
		UIManager.WindowControl.ChildInsert(InventoryUI);
	}
	// HotBar
	{
		HotBarUI.IsResizable = false;
		HotBarUI.IsMovable = false;
		HotBarUI.Anchor.Y.AnchorMax(0);
		HotBarUI.Change(&HotBar);
		//HotBarUI.Hide();
		UIManager.WindowControl.ChildInsert(HotBarUI);
	}

//	UIManager.WindowControl.UpdateDepth();
}



// a lot of the managers are siminal with the bool flags and function names
// make a Base ? to organize
void ContextNoisePlane::ChangeMedia()
{
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	/*{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.frag")),
		});
		PlaneManager.Shader.Change(code);
	}*/
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	ChunkManager.ChangeMedia(MediaDirectory);
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
}

// Valgrind is very slow here ?
void ContextNoisePlane::GraphicsCreate()
{
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	UIManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	//PlaneManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	ChunkManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
}
void ContextNoisePlane::GraphicsDelete()
{
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	UIManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	//PlaneManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	ChunkManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
}

#include "Texture/FileMap.hpp"
void ContextNoisePlane::Init()
{
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	PolyHedraManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	Make();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	ChangeMedia();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	GraphicsCreate();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	UIManager.TextManager.InitFont();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	UIManager.GraphicsInit();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	{
		TextureFileMap tex_map;
		std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
		VoxelPalletMap::StaticMap.TexturesAssign(tex_map);
		std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
		ChunkManager.Texture.Bind();
		ChunkManager.Texture.Assign(VectorU2(32, 32), tex_map.Files.ToArray());
	}
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	VoxelPalletMap::StaticMap.MakePolyHedras();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	MakeControls();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	//ChunkManager.ChangeSize(0, 0);
	//ChunkManager.ChangeSize(2, 1);
	ChunkManager.ChangeSize(4, 3);
//	ChunkManager.ChangeSize(8, 6);
	//ChunkManager.ChangeSize(16, 8);
	//ChunkManager.ChangeSize(16, 12);
	//ChunkManager.ChangeSize(32, 16);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	MultiformLayout.Depth.ChangeData(View.Depth);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	MultiformLayout.FOV.ChangeData(View.FOV);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	AuxThread0Idle = false;
	ChunkManager.AuxThread1.DoIdle = false;
	ChunkManager.AuxThread2.DoIdle = false;
	ChunkManager.AuxThread3.DoIdle = false;
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	ChunkManager.AuxThread1.Poke();
	ChunkManager.AuxThread2.Poke();
	ChunkManager.AuxThread3.Poke();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
}
void ContextNoisePlane::Free()
{
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	PolyHedraManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	GraphicsDelete();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	AuxThread0Term = true;
	ChunkManager.AuxThread1.Term = true;
	ChunkManager.AuxThread2.Term = true;
	ChunkManager.AuxThread3.Term = true;
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	while (
		!ChunkManager.AuxThread1.Done ||
		!ChunkManager.AuxThread2.Done ||
		!ChunkManager.AuxThread3.Done)
	{
		if (!ChunkManager.AuxThread1.Done) { ChunkManager.AuxThread1.Poke(); }
		if (!ChunkManager.AuxThread2.Done) { ChunkManager.AuxThread2.Poke(); }
		if (!ChunkManager.AuxThread3.Done) { ChunkManager.AuxThread3.Poke(); }
	}
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	AuxThread0.join();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	ChunkManager.AuxThread1.Join();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	ChunkManager.AuxThread2.Join();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	ChunkManager.AuxThread3.Join();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
}



static unsigned int		TextCharCount = 0;

void ContextNoisePlane::Draw()
{
	// should GraphicsManagers just know that they want Enabled/Disabled ?
	// GraphicsManagerBase so I dont need to call the Create/Delete individually
	// instead just put them in a Container
	// also Update/Draw all automatically

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw;



	PolyHedraManager.InstancesClear();
	PolyHedraManager.InstancesMake();

	UIManager.WindowControl.UpdateRecursive();
	UIManager.Resize(window.Size);
	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.ControlManager.InstancesClear();
	UIManager.ControlManager.InstancesMake();
	UIManager.WindowControl.PutDisplay();

	UIManager.GraphManager.MakeInstances();



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	GL::Enable(GL::Capability::DepthClamp);

	sw.Clear();
	ObjectManagerBasic.GraphicsDrawFull();
	ObjectManagerBasic.GraphicsDrawWire();
	FrameTime_Draw_DrawPolyHedra.NewValue(sw.ElapsedTime());

	//PlaneManager.Draw();

	sw.Clear();
	ChunkManager.ShaderU.Bind();
	ChunkManager.ShaderLayoutU.LightAmbient.Put(LightAmbient);
	ChunkManager.ShaderLayoutU.LightSolar.Put(LightSolar);
	ChunkManager.ShaderLayoutU.LightSpot.Put(LightSpot);
	ChunkManager.ShaderLayoutU.LightSpotCount.Put(1);
	FrameTime_Draw_UniformChunk.NewValue(sw.ElapsedTime());

	sw.Clear();
	ChunkManager.Draw();
	FrameTime_Draw_DrawChunk.NewValue(sw.ElapsedTime());

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	sw.Clear();
	UIManager.ControlManager.Draw();
	FrameTime_Draw_DrawControl.NewValue(sw.ElapsedTime());

	sw.Clear();
	UIManager.TextManager.MakeInstances();
	FrameTime_Draw_MakeText.NewValue(sw.ElapsedTime());

	UIManager.TextManager.ShowInstancesTime();

	sw.Clear();
	UIManager.TextManager.Draw();
	FrameTime_Draw_DrawText.NewValue(sw.ElapsedTime());

	TextCharCount = UIManager.TextManager.InstancesArray.Length();

	UIManager.GraphManager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	ObjectManagerUI.GraphicsDrawFull();
	ObjectManagerUI.GraphicsDrawWire();



	FrameTime_Draw_DrawTotal.NewValue(sw_total.ElapsedTime());



	PolyHedraManager.UpdatePalletObjectDatas();
}



static void ShowTimeFreq(std::stringstream & ss, float time, int freq)
{
	//ss << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(6) << time << 's' << ' ';
	ss << ToString(time) << 's' << ' ';
	ss << '(';
	ss << ToString(freq, 4) << "Hz";
	ss << ')';
}
/*static void ShowTimeFreq(std::stringstream & ss, float time)
{
	ShowTimeFreq(ss, time, 1.0f / time);
}*/
/*static void ShowNameTimeFreqLine(std::stringstream & ss, const char * name, const ValueAccumulator<float> & time)
{
	ss << name << ':';
	ShowTimeFreq(ss, time.Min()); ss << ' ';
	ShowTimeFreq(ss, time.Average()); ss << ' ';
	ShowTimeFreq(ss, time.Max()); ss << '\n';
}*/

static void ShowTime(std::stringstream & ss, float time)
{
	ss << ToString(time, 6) << 's';
}
static void ShowNameTimeLine(std::stringstream & ss, const char * name, const ValueAccumulator<float> & time)
{
	ss << name << ':';
	ShowTime(ss, time.Min()); ss << ' ';
	ShowTime(ss, time.Average()); ss << ' ';
	ShowTime(ss, time.Max()); ss << '\n';
}



static ValueAccumulator<float>		DLTAverageTime(1024);
static ValueAccumulator<float>		FPSAverageTime(1024);
static ValueAccumulator<float>		InventoryCursorTime(64);

struct VoxelChunkMemoryInfo
{
	unsigned int chunks_limit;
	unsigned int chunks_total;

	unsigned int chunks_gen_TD;
	unsigned int chunks_gen_DG;
	unsigned int chunks_gen_DA;
	unsigned int chunks_gen_done;

	unsigned int chunks_done_empty;
	unsigned int chunks_done_filled;

	unsigned int buffer_data_none;
	unsigned int buffer_data_have[2];
	unsigned int buffer_data_want[2];
	unsigned long long buffer_data_u_entrys;
	unsigned long long buffer_data_u_memory;
	unsigned long long buffer_data_u_limit;
	unsigned long long buffer_data_f_entrys;
	unsigned long long buffer_data_f_memory;
	unsigned long long buffer_data_f_limit;

	void	Clear()
	{
		chunks_limit = 0;
		chunks_total = 0;
		chunks_gen_TD = 0;
		chunks_gen_DG = 0;
		chunks_gen_DA = 0;
		chunks_gen_done = 0;
		chunks_done_empty = 0;
		chunks_done_filled = 0;
		buffer_data_none = 0;
		buffer_data_have[0] = 0;
		buffer_data_have[1] = 0;
		buffer_data_want[0] = 0;
		buffer_data_want[1] = 0;
		buffer_data_u_entrys = 0;
		buffer_data_u_memory = 0;
		buffer_data_u_limit = 0;
		buffer_data_f_entrys = 0;
		buffer_data_f_memory = 0;
		buffer_data_f_limit = 0;
	}
	void	Gather(ChunkManager & manager)
	{
		chunks_limit = manager.Chunks.Length();
		for (unsigned int i = 0; i < chunks_limit; i++)
		{
			if (manager.Chunks[i] == nullptr) { continue; }
			Chunk & chunk = *manager.Chunks[i];
			chunks_total++;

			if (chunk.TerrainDone) { chunks_gen_TD++; }
			if (chunk.DecorationsGenerated) { chunks_gen_DG++; }
			if (chunk.DecorationsAssambled) { chunks_gen_DA++; }
			if (chunk.GenerationDone())
			{
				chunks_gen_done++;
				if (chunk.IsEmpty())
				{ chunks_done_empty++; }
				else
				{ chunks_done_filled++; }
			}

			//main_f_count += chunk.BufferF.Main.Count;

			// Edge Chunks dont get BufferData because the outside Chunks are not done Decorating
			// Edge Chunks dont Decorate because the outside Chunks are out of Bounds and assumed null
			if (chunk.GenerationDone())
			{
				if (chunk.BufferData_Want)		{ buffer_data_want[0]++; }
				else							{ buffer_data_want[1]++; }
				if (chunk.BufferData_Have)		{ buffer_data_have[0]++; }
				else							{ buffer_data_have[1]++; }
			}
			else
			{
				// none should be if buffer if Data is empty ?
				buffer_data_none++;
			}
		}

		buffer_data_u_entrys = manager.BufferU.Entrys.Count();
		buffer_data_u_memory = 0;
		for (unsigned int i = 0; i < buffer_data_u_entrys; i++)
		{
			buffer_data_u_memory += manager.BufferU.Entrys[i] -> Length;
		}
		buffer_data_u_limit = manager.BufferU.Buffer.Count;

		buffer_data_f_entrys = manager.BufferF.Entrys.Count();
		buffer_data_f_memory = 0;
		for (unsigned int i = 0; i < buffer_data_f_entrys; i++)
		{
			buffer_data_f_memory += manager.BufferF.Entrys[i] -> Length;
		}
		buffer_data_f_limit = manager.BufferF.Buffer.Count;
	}
	void	Show(std::stringstream & ss)
	{
		ss << "Chunks:\n";
		ss << "Total:" << chunks_limit << ' ' << chunks_total << '\n';

		ss << "Gen:";
		ss << "TD" << chunks_gen_TD << ' ';
		ss << "DG" << chunks_gen_DG << ' ';
		ss << "DA" << chunks_gen_DA << ' ';
		ss << 'D' << chunks_gen_done << '\n';

		ss << "Done:";
		ss << 'E' << chunks_done_empty << ' ';
		ss << 'F' << chunks_done_filled << '\n';
		ss << '\n';

		ss << "Chunks: " << Memory1000ToString(sizeof(Chunk));
		ss << " * " << Seperated1000(chunks_total);
		ss << " = " << Memory1000ToString(chunks_total * sizeof(Chunk));
		ss << '\n';

		ss << "Voxels: " << Memory1000ToString(sizeof(Voxel));
		ss << " * " << Seperated1000(chunks_done_filled * CHUNK_VALUES_PER_VOLM);
		ss << " = " << Memory1000ToString(chunks_done_filled * CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
		ss << '\n';

		ss << "BufferState";
		ss << " None[" << buffer_data_none << ']';
		ss << " Want[" << buffer_data_want[0] << ':' << buffer_data_want[1] << ']';
		ss << " Have[" << buffer_data_have[0] << ':' << buffer_data_have[1] << ']';
		ss << '\n';

		ss << "DataU Entrys:" << buffer_data_u_entrys << '\n';
		ss << "DataU Memory: ";
		ss << Memory1000ToString(buffer_data_u_memory * sizeof(VoxelGeometryDataU::Face));
		ss << " / ";
		ss << Memory1000ToString(buffer_data_u_limit * sizeof(VoxelGeometryDataU::Face));
		ss << '\n';

		ss << "DataF Entrys:" << buffer_data_f_entrys << '\n';
		ss << "DataF Memory: ";
		ss << Memory1000ToString(buffer_data_f_memory * sizeof(VoxelGeometryDataF::Axis));
		ss << " / ";
		ss << Memory1000ToString(buffer_data_f_limit * sizeof(VoxelGeometryDataF::Axis));
		ss << '\n';

		/*ss << "DataU Memory:" << Memory1000ToString(sizeof(VoxelGraphics::MainFaceU));
		ss << " * " << Seperated1000(data_u_memory);
		ss << " = " << Memory1000ToString(data_u_memory * sizeof(VoxelGraphics::MainFaceU));
		ss << " / " << Memory1000ToString(ChunkManager.BufferU.Size * sizeof(VoxelGraphics::MainFaceU));
		ss << " / " << Seperated1000(ChunkManager.BufferU.Size);
		ss << '\n';*/

		/*ss << "DataF: " << Memory1000ToString(sizeof(VoxelGraphics::MainDataF));
		ss << " * " << Seperated1000(main_f_count);
		ss << " = " << Memory1000ToString(main_f_count * sizeof(VoxelGraphics::MainDataF));
		ss << '\n';*/

		ss << '\n';
	}
};

#include "Graph/ObjectData.hpp"
void ContextNoisePlane::FrameText(FrameTime frame_time)
{
	StopWatch sw_total;
	
	StopWatch sw;
	StopWatch sw_part;

	sw_total.Start();

	std::stringstream ss;

	// FPS
	sw.Clear(); sw.Start();
	if (MenuDebug.FPS.Check.IsChecked())
	{
		ss << "Frame (" << (int)frame_time.WantedFramesPerSecond << '|' << (int)frame_time.ActualFramesPerSecond << ")Hz\n";
		ss << "Frame (" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")s\n";
		ss << '\n';

		ss << "Min: "; ShowTimeFreq(ss, DLTAverageTime.Min(),     FPSAverageTime.Max());     ss << '\n';
		ss << "Avg: "; ShowTimeFreq(ss, DLTAverageTime.Average(), FPSAverageTime.Average()); ss << '\n';
		ss << "Max: "; ShowTimeFreq(ss, DLTAverageTime.Max(),     FPSAverageTime.Min());     ss << '\n';
		ss << '\n';

		UI::Graph::Object obj_graph;
		obj_graph.Create();
		obj_graph.Box().Min = VectorF2( 400,  75);
		obj_graph.Box().Max = VectorF2(1200, 175);
		//obj_graph.Data -> Center = 512;
		//obj_graph.Data -> Magnitede = 512;
		obj_graph.Data -> Center = 60;
		obj_graph.Data -> Magnitede = 8;
		obj_graph.Data -> Col = ColorF4(1, 0, 1);
		obj_graph.Data -> Values = &FPSAverageTime;
	}
	sw.Stop(); TextTime_TestFPS.NewValue(sw.ElapsedTime());

	// Thread Time
	sw.Clear(); sw.Start();
	if (MenuDebug.TimeThreads.Check.IsChecked())
	{
		ShowNameTimeLine(ss, "Frame           ", FrameTime_);
		ss << "{\n";
		ShowNameTimeLine(ss, "Input           ", FrameTime_Input);
		ShowNameTimeLine(ss, "ViewUpdate      ", FrameTime_ViewUpdate);
		/*ss << "{\n";
		ShowNameTimeLine(ss, "CollisionTime   ", FrameTime_ViewUpdate_CollisionTime);
		ss << "{\n";
		ss << ChunkManager::TimeGraphicsCreate << '\n';
		ss << ChunkManager::TimeGraphicsDelete << '\n';
		ss << "}\n";
		ShowNameTimeLine(ss, "RayTime         ", FrameTime_ViewUpdate_RayTime);
		ss << "}\n";*/
		ShowNameTimeLine(ss, "ChunkBoxes      ", FrameTime_ChunkBoxes);
		ShowNameTimeLine(ss, "ChunkHereBox    ", FrameTime_ChunkHereBox);
		ShowNameTimeLine(ss, "Text            ", FrameTime_Text);
		/*ss << "{\n";
		ShowNameTimeLine(ss, "Text Assamble   ", FrameTime_Text_Assamble);
		ss << "{\n";
		ShowNameTimeLine(ss, "TestFPS         ", TextTime_TestFPS);
		ShowNameTimeLine(ss, "ThreadTime      ", TextTime_ThreadTime);
		ShowNameTimeLine(ss, "ChunkManagerTime", TextTime_ChunkManagerTime);
		ShowNameTimeLine(ss, "View            ", TextTime_View);
		ShowNameTimeLine(ss, "ChunkHere       ", TextTime_ChunkHere);
		ShowNameTimeLine(ss, "ChunkRange      ", TextTime_ChunkRange);
		ShowNameTimeLine(ss, "VoxelChunkMemory", TextTime_VoxelChunkMemory);
		ss << "{\n";
		ShowNameTimeLine(ss, "            Wait", TextTime_VoxelChunkMemory_Wait);
		ShowNameTimeLine(ss, "            Loop", TextTime_VoxelChunkMemory_Loop);
		ShowNameTimeLine(ss, "            Show", TextTime_VoxelChunkMemory_Show);
		ss << "}\n";
		ShowNameTimeLine(ss, "Text Instance   ", FrameTime_Text_Instance);
		ss << "}\n";*/
		ShowNameTimeLine(ss, "Draw            ", FrameTime_Draw);
		ss << "{\n";
		ss << "Total       " << ToString(::ChunkManager::DrawTotal.Average(), 6) << '\n';
		ss << "Wait        " << ToString(::ChunkManager::DrawWait.Average(), 6) << '\n';
		ss << "TextureBind " << ToString(::ChunkManager::DrawTextureBind.Average(), 6) << '\n';
		ss << "ShaderBind  " << ToString(::ChunkManager::DrawShaderBind.Average(), 6) << '\n';
		ss << "UpdateBind  " << ToString(::ChunkManager::DrawUpdateBind.Average(), 6) << '\n';
		ss << "BufferDraw  " << ToString(::ChunkManager::DrawBufferDraw.Average(), 6) << '\n';
		ss << "}\n";
		ShowNameTimeLine(ss, "DrawThread      ", FrameTime_DrawThread);
		ss << "}\n";

		ShowNameTimeLine(ss, "Inventory  Cursor", InventoryCursorTime);
		ShowNameTimeLine(ss, "AuxThread       0", AuxThread0Time);
		ss << '\n';
	}
	sw.Stop(); TextTime_ThreadTime.NewValue(sw.ElapsedTime());

	// ChunkManager Time
	sw.Clear(); sw.Start();
	if (MenuDebug.TimeWaitDo.Check.IsChecked())
	{
		ss << ChunkManager::TimeInsert << '\n';
		ss << ChunkManager::TimeInsertNew << '\n';
		ss << ChunkManager::TimeInsertPut << '\n';
		ss << ChunkManager::TimeRemove << '\n';
		ss << ChunkManager::TimeUpdate << '\n';
		ss << ChunkManager::TimeUpdateInsert << '\n';
		ss << ChunkManager::TimeUpdateRemove << '\n';
		ss << '\n';
		ss << "AuxThread1 IsIdle: " << ChunkManager.AuxThread1.IsIdle << '\n';
		ss << ChunkManager.AuxThread1.TimeMakeBufferFind << '\n';
		ss << ChunkManager.AuxThread1.TimeMakeBuffer << '\n';
		ss << '\n';
		ss << "AuxThread2 IsIdle: " << ChunkManager.AuxThread2.IsIdle << '\n';
		ss << ChunkManager.AuxThread2.TimeGenerateFind << '\n';
		ss << ChunkManager.AuxThread2.TimeGenerate << '\n';
		ss << '\n';
		ss << "AuxThread3 IsIdle: " << ChunkManager.AuxThread3.IsIdle << '\n';
		ss << ChunkManager.AuxThread3.TimeAssambleFind << '\n';
		ss << ChunkManager.AuxThread3.TimeAssamble << '\n';
		ss << '\n';
		ss << ChunkManager::TimeGraphicsCreate << '\n';
		ss << ChunkManager::TimeGraphicsDelete << '\n';
		ss << ChunkManager::TimeDraw << '\n';
		ss << '\n';
	}
	sw.Stop(); TextTime_ChunkManagerTime.NewValue(sw.ElapsedTime());

	/*{
		ss << "CheckingCount: " << ChunkManager.ChunksLock.Count() << '\n';
		ss << "ToInsert: " << ChunkManager.ChunksToInsert.Count() << '\n';
		ss << "ToRemove: " << ChunkManager.ChunksToRemove.Count() << '\n';
		ss << '\n';
	}*/

	/*{
		ss << "DontInsert: " << DontInsert << '\n';
		ss << "DontRemove: " << DontRemove << '\n';
		ss << "DontGenerate: " << DontGenerate << '\n';
		ss << "DontBuffer: " << DontBuffer << '\n';
		ss << '\n';
	}*/

	// View
	sw.Clear(); sw.Start();
	if (MenuDebug.View.Check.IsChecked())
	{
		ss << "View.Pos.X: " << View.Trans.Position.X << '\n';
		ss << "View.Pos.Y: " << View.Trans.Position.Y << '\n';
		ss << "View.Pos.Z: " << View.Trans.Position.Z << '\n';
		ss << "ViewEntity.Pos.X: " << ViewEntity.Pos.X << '\n';
		ss << "ViewEntity.Pos.Y: " << ViewEntity.Pos.Y << '\n';
		ss << "ViewEntity.Pos.Z: " << ViewEntity.Pos.Z << '\n';
		ss << "ViewEntity.Vel.X: " << ViewEntity.Vel.X << '\n';
		ss << "ViewEntity.Vel.Y: " << ViewEntity.Vel.Y << '\n';
		ss << "ViewEntity.Vel.Z: " << ViewEntity.Vel.Z << '\n';
		ss << "ViewEntity.|Vel|: " << ViewEntity.Vel.length() << '\n';
		ss << "None : " << (ViewEntity_CollisionSide.None) << '\n';
		ss << "PrevX: " << (ViewEntity_CollisionSide.PrevX) << '\n';
		ss << "PrevY: " << (ViewEntity_CollisionSide.PrevY) << '\n';
		ss << "PrevZ: " << (ViewEntity_CollisionSide.PrevZ) << '\n';
		ss << "NextX: " << (ViewEntity_CollisionSide.NextX) << '\n';
		ss << "NextY: " << (ViewEntity_CollisionSide.NextY) << '\n';
		ss << "NextZ: " << (ViewEntity_CollisionSide.NextZ) << '\n';
		ss << '\n';
	}
	sw.Stop(); TextTime_View.NewValue(sw.ElapsedTime());

	// ChunkHere
	sw.Clear(); sw.Start();
	if (MenuDebug.ChunkHere.Check.IsChecked())
	{
		//VoxelIndex idx = ChunkManager.FindVoxelIndex(View.Trans.Position);
		ChunkVoxelIndex idx(View.Trans.Position.roundF().ToI());
		ss << "Here: " << idx.Chunk << ' ' << idx.Voxel << '\n';
		//ChunkManager.ChunksInUse.lock();
		AccessLockedChunk chunk = ChunkManager.FindAccess(idx.Chunk);
		//if (idx.ChunkMan != 0xFFFFFFFF)
		if (chunk.Is())
		{
			//ss << "Chunk: " << idx.ChunkMan << '\n';

			ss << "Data: ";
			if ((*chunk).IsEmpty()) { ss << "Empty"; } else
			{
				ss << Memory1000ToString(CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
			}
			ss << '\n';

			ss << "TerrainDone: " << (*chunk).TerrainDone << '\n';
			ss << "DecorationsGenerated: " << (*chunk).DecorationsGenerated << '\n';
			ss << "DecorationsAssambled: " << (*chunk).DecorationsAssambled << '\n';
			if ((*chunk).GenerationDone()) { ss << "Done"; }
			ss << '\n';

			ss << "BufferData_Want: " << (*chunk).BufferData_Want << '\n';
			ss << "BufferData_Have: " << (*chunk).BufferData_Have << '\n';

			//ss << "Buffer: ";
			//ss << Memory1000ToString(chunk.Buffer.Main.Count * sizeof(VoxelGraphics::MainDataU));
			//ss << '\n';

			/*ss << "BufferF: ";
			ss << Memory1000ToString((*chunk).BufferF.Main.Count * sizeof(VoxelGraphics::MainDataF));
			ss << '\n';*/

			ss << '\n';
		}
		else
		{
			ss << "No Chunk Info\n";
		}
		ss << '\n';
		//ChunkManager.ChunksInUse.unlock();
	}
	sw.Stop(); TextTime_ChunkHere.NewValue(sw.ElapsedTime());

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

	// ChunkRange
	sw.Clear(); sw.Start();
	if (MenuDebug.ChunkRange.Check.IsChecked())
	{
		ss << "Chunk Ranges:" << '\n';
		ss << "Chunk Know: " << ChunkManager.KnowSize << '\n';
		ss << "Chunk Care: " << ChunkManager.CareSize << '\n';

		VectorU3 know = ChunkManager.Chunks.Size();
		VectorU3 care((ChunkManager.CareSize * 2) + 1);

		ss << "Know: " << know << ' ' << know.Product() << '\n';
		ss << "Care: " << care << ' ' << care.Product() << '\n';

		ss << "ToInsert: " << ChunkManager.ChunksToInsert.Count() << '\n';
		ss << "ToRemove: " << ChunkManager.ChunksToRemove.Count() << '\n';

		ss << '\n';
	}
	sw.Stop(); TextTime_ChunkRange.NewValue(sw.ElapsedTime());

	// Queues
	{
		ss << "Queues:\n";

		ss << "BufferData Want " << ChunkManager.AuxThread1.QueueCount() << '\n';
		ss << "BufferData Have " << ChunkManager.BufferDataHave.QueueCount() << '\n';

		ss << "Generate Candidates " << ChunkManager.AuxThread2.FindCandidateCount << '\n';
		ss << "Assamble Candidates " << ChunkManager.AuxThread3.FindCandidateCount << '\n';

		ss << '\n';
	}

	// VoxelChunkMemory
	sw.Clear(); sw.Start();
	if (MenuDebug.VoxelChunkMemory.Check.IsChecked())
	{
		sw_part.Clear(); sw_part.Start();
		ChunkManager.ChunksLock.AccessL();
		sw_part.Stop(); TextTime_VoxelChunkMemory_Wait.NewValue(sw_part.ElapsedTime());

		/* Info refresh rate
			I dont need this every frame
			the Threads run independently anyway
			so 10Hz or so should be fine
		*/
		static VoxelChunkMemoryInfo info;
		static StopWatch info_sw;
		info_sw.Start();

		sw_part.Clear(); sw_part.Start();
		if (info_sw.ElapsedTime() > 1.0f)
		{
			info.Clear();
			info.Gather(ChunkManager);
			info_sw.Clear();
			info_sw.Start();
		}
		sw_part.Stop(); TextTime_VoxelChunkMemory_Loop.NewValue(sw_part.ElapsedTime());

		ChunkManager.ChunksLock.AccessU();

		sw_part.Clear(); sw_part.Start();
		info.Show(ss);
		sw_part.Stop(); TextTime_VoxelChunkMemory_Show.NewValue(sw_part.ElapsedTime());
	}
	sw.Stop(); TextTime_VoxelChunkMemory.NewValue(sw.ElapsedTime());

	sw_total.Stop(); FrameTime_Text_Assamble.NewValue(sw_total.ElapsedTime());

	sw_total.Clear(); sw_total.Start();
	{
		UI::Text::Object text; text.Create();
		text.Text() = ss.str();
		if (MenuDebug.IsVisible())
		{
			text.TextPosition().X = MenuDebug.Anchor.X.GetMinSize();
		}
		text.AlignTopLeft();
		text.Color() = ColorF4(1, 1, 1);
		text.Bound().Min = VectorF2();
		text.Bound().Max = window.Size.Buffer.Full;
	}
	sw_total.Stop(); FrameTime_Text_Instance.NewValue(sw_total.ElapsedTime());

	// CrossHair
	{
		UI::Text::Object text; text.Create();
		text.Text() = "[+]";
		text.AlignMiddleMiddle();
		text.TextPosition() = window.Size.Buffer.Half;
		text.Color() = ColorF4(1, 1, 1);
		text.Bound().Min = VectorF2();
		text.Bound().Max = window.Size.Buffer.Full;
	}
	if (VoxelClear_Is())
	{
		std::stringstream ss;
		ss << "\n\n";
		ss << VoxelClear_Progress << '/' << VoxelClear_Required;
		UI::Text::Object text; text.Create();
		text.Text() = ss.str();
		text.AlignMiddleMiddle();
		text.TextPosition() = window.Size.Buffer.Half;
		text.Color() = ColorF4(1, 1, 1);
		text.Bound().Min = VectorF2();
		text.Bound().Max = window.Size.Buffer.Full;
	}
}
void ContextNoisePlane::InventoryCursor(FrameTime frame_time)
{
	StopWatch sw;
	sw.Start();

	static float time_sum = 0.0f;

	ItemBase * item_base = HotBar.Items[VectorU2(0, 0)];
	if (item_base != nullptr)
	{
		NewPolyHedra::UserInterface::Object obj;
		{
			ItemVoxel * item = dynamic_cast<ItemVoxel*>(item_base);
			if (item != nullptr)
			{
				obj.Create(item -> VoxelPallet -> PolyHedra);
			}
		}
		{
			ItemTool * item = dynamic_cast<ItemTool*>(item_base);
			if (item != nullptr)
			{
				obj.Create(item -> Pallet);
				obj.Data().Scale = 0.25f;
			}
		}
		if (obj.Is())
		{
			obj.Data().Size = VectorF2(240, 240);
			obj.Data().Pos = VectorF2(window.Size.Buffer.Full.X - 120, window.Size.Buffer.Full.Y - 120);
			obj.Data().Rot = EulerAngle3D::Degrees(0, 30, time_sum * 45).reverse();
		}
	}

	if (ItemSlotUI::StaticItem != nullptr)
	{
		NewPolyHedra::UserInterface::Object obj;
		{
			ItemVoxel * item = dynamic_cast<ItemVoxel*>(ItemSlotUI::StaticItem);
			if (item != nullptr)
			{
				obj.Create(item -> VoxelPallet -> PolyHedra);
			}
		}
		{
			ItemTool * item = dynamic_cast<ItemTool*>(ItemSlotUI::StaticItem);
			if (item != nullptr)
			{
				obj.Create(item -> Pallet);
				obj.Data().Scale = 0.25f;
			}
		}
		if (obj.Is())
		{
			obj.Data().Size = VectorF2(40, 40);
			obj.Data().Pos = window.MouseManager.CursorPosition().Buffer.Corner;
			obj.Data().Rot = EulerAngle3D::Degrees(0, 30, time_sum * 45).reverse();
		}
	}

	time_sum += frame_time.Delta;

	sw.Stop();
	InventoryCursorTime.NewValue(sw.ElapsedTime());
}
// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void ContextNoisePlane::FrameInput()
{
	//StopWatch sw;
	//sw.Start();

	if (window[Keys::Escape] == State::Press)
	{
		MenuOptions.Hide();
		InventoryUI.Hide();
		//HotBarUI.Hide();
		if (MenuPause.IsVisible())
		{
			//AuxThreadBase::Idle = false;
			MenuPause.Hide();
		}
		else
		{
			//AuxThreadBase::Idle = true;
			MenuPause.Show();
		}
	}
	if (window[Keys::E] == State::Press)
	{
		if (!MenuPause.IsVisible() && !MenuOptions.IsVisible())
		{
			if (!InventoryUI.IsVisible())
			{
				InventoryUI.Show();
				//HotBarUI.Show();
			}
			else
			{
				InventoryUI.Hide();
				//HotBarUI.Hide();
			}
		}
	}

	//if (window[Keys::D1] == State::Press) { Toggle(ViewRaySync); }
	//if (window[Keys::D2] == State::Press) { Toggle(ChunkManager.ViewRayPolyHedra, ViewRayPolyHedra); }
	//if (window[Keys::D3] == State::Press) { Toggle(ChunkManager.VoxelBoxPolyHedra, VoxelCube); }

	if (window[Keys::F7] == State::Press)
	{
		if (MenuDebug.IsVisible())
		{
			MenuDebug.Hide();
		}
		else
		{
			MenuDebug.Show();
		}
	}

	if (window[Keys::F2] == State::Press) { Toggle(View_IsTangible); }
	if (window[Keys::F3] == State::Press)
	{
		if (View_Distance == 0.0f)
		{ View_Distance = 2.0f; }
		else
		{ View_Distance = 0.0f; }
	}
	/*if (window[Keys::F4] == State::Press)
	{
		//Toggle(PlaneManager.ShouldGenerate);
		Toggle(ChunkManager.DontGenerate);
	}*/
	if (window[Keys::F5] == State::Press)
	{
		//PlaneManager.Clear();
		ChunkManager.Clear();
	}

	if (MenuPause.IsVisible() || MenuOptions.IsVisible() || InventoryUI.IsVisible())
	{
		if (window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeFree(); }
	}
	else
	{
		if (!window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeLock(); }
	}

	/*if (window[Keys::P] == State::Press)
	{
		ChunkVoxelIndex idx(View.Trans.Position.roundF());
		Chunk * chunk = ChunkManager.FindLockOrNull(idx.Chunk);
		if (chunk != nullptr)
		{
			std::cout << "Chunk" << idx.Chunk << ".MakeNull()\n";
			chunk -> MakeNull();
			chunk -> MainBufferDataNew = true;
			chunk -> AccessU();
		}
	}*/

	//sw.Stop();
	//FrameInputTime.NewValue(sw.ElapsedTime());
}

void ContextNoisePlane::Frame(FrameTime frame_time)
{
	DLTAverageTime.NewValue(frame_time.ActualFrameTime);
	FPSAverageTime.NewValue(frame_time.ActualFramesPerSecond);

	// this is general Update, not Draw specific
	//LightSolar.Dir = EulerAngle3D::Degrees(0, 0, 90 * frame_time.Delta).forward(LightSolar.Dir);
	LightSpot.Pos = View.Trans.Position;
	LightSpot.Dir = View.Trans.Rotation.forward(VectorF3(0, 0, 1));

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw;

	// this is general Update, not Draw specific
	sw.Clear(); sw.Start();
	FrameInput();
	sw.Stop(); FrameTime_Input.NewValue(sw.ElapsedTime());

	// this is general Update, not Draw specific, except View Matrix Uniform
	sw.Clear(); sw.Start();
	if (!MenuOptions.IsVisible())
	{
		Trans3D change;
		if (window.MouseManager.CursorModeIsLocked())
		{
			change = window.MoveSpinFromKeysCursor();
			change.Rotation *= View.FOV.ToRadians() * 0.05f;
			{
				EulerAngle3D e(Angle(), Angle(), View.Trans.Rotation.Y2);
				change.Position = e.forward(change.Position);
			}
		}
		ViewUpdate(change, frame_time);
	}
	sw.Stop(); FrameTime_ViewUpdate.NewValue(sw.ElapsedTime());

	/*{
		float pixel_rad = 1;
		UI::Control::Object obj;
		obj.Create();
		obj.Box().Min = window.Size.Buffer.Half - VectorF2(pixel_rad, pixel_rad);
		obj.Box().Max = window.Size.Buffer.Half + VectorF2(pixel_rad, pixel_rad);
		obj.Color() = ColorF4(1, 0, 1);
	}*/

	// rechnically not Draw related, but PolyHedraManager is currently not intended for different Threads
	sw.Clear(); sw.Start();
	if (MenuDebug.VoxelChunkBoxes.Check.IsChecked())
	{
		NewPolyHedra::Pallet * pallet = PalletManager.FindMakePallet(VoxelChunkCube);
		for (unsigned int i = 0; i < ChunkManager.Chunks.Length(); i++)
		{
			Chunk * chunk = ChunkManager.Chunks[i];
			if (chunk == nullptr) { continue; }
			NewPolyHedra::Basic3D::Object chunk_box(pallet);
			chunk_box.Data().Trans.Position = (chunk -> Index * CHUNK_VALUES_PER_SIDE).ToF();
			chunk_box.ShowWire();
		}
	}
	sw.Stop(); FrameTime_ChunkBoxes.NewValue(sw.ElapsedTime());
	
	// rechnically not Draw related, but PolyHedraManager is currently not intended for different Threads
	sw.Clear(); sw.Start();
	if (MenuDebug.ChunkHere.Check.IsChecked())
	{
		ChunkVoxelIndex idx(View.Trans.Position.roundF().ToI());
		NewPolyHedra::Basic3D::Object chunk_box(VoxelChunkCube);
		chunk_box.Data().Trans.Position = (idx.Chunk * CHUNK_VALUES_PER_SIDE).ToF();
		chunk_box.ShowWire();
	}
	sw.Stop(); FrameTime_ChunkHereBox.NewValue(sw.ElapsedTime());

	// rechnically not Draw related, but TextManager is currently not intended for different Threads
	sw.Clear(); sw.Start();
	FrameText(frame_time);
	sw.Stop(); FrameTime_Text.NewValue(sw.ElapsedTime());

	InventoryCursor(frame_time);

	sw.Clear(); sw.Start();
	Draw();
	sw.Stop(); FrameTime_Draw.NewValue(sw.ElapsedTime());

	sw_total.Stop(); FrameTime_.NewValue(sw_total.ElapsedTime());
}

void ContextNoisePlane::Resize(DisplaySize display_size)
{
	::ItemSlotUI::WindowSize = display_size;
	MultiformLayout.DisplaySize.ChangeData(display_size);
}



// make these virtual and put them in Base
void ContextNoisePlane::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void ContextNoisePlane::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void ContextNoisePlane::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void ContextNoisePlane::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void ContextNoisePlane::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void ContextNoisePlane::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
