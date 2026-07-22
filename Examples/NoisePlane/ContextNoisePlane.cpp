#include "ContextNoisePlane.hpp"
#include "new.hpp"

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

// Math
#include <math.h>





#ifndef DISABLE_INVENTORY
InventoryShader::~InventoryShader()
{ }
InventoryShader::InventoryShader()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }
#endif



ShaderLayoutView3D::~ShaderLayoutView3D()
{ }
ShaderLayoutView3D::ShaderLayoutView3D()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }



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





ContextNoisePlane::~ContextNoisePlane()
{ }
ContextNoisePlane::ContextNoisePlane()
	: ContextBase()
	, PolyHedraManager()
	, PalletManager_BufferFullLayout()
	, PalletManager_BufferWireLayout()
	, PalletManager()
	, ObjectManagerBasic_ShaderFullLayout()
	, ObjectManagerBasic_ShaderWireLayout()
	, ObjectManagerBasic_BufferFullLayout()
	, ObjectManagerBasic_BufferWireLayout()
	, ObjectManagerBasic()
	, ObjectManagerUI_ShaderFullLayout()
	, ObjectManagerUI_ShaderWireLayout()
	, ObjectManagerUI_BufferFullLayout()
	, ObjectManagerUI_BufferWireLayout()
	, ObjectManagerUI()
	, UIManager()
//	, PlaneManager()
	, ChunkManager()
	, MainMenu()
	, PauseMenu(*this)
	, OptionsMenu(*this)
	, DebugMenu(*this)
#ifndef DISABLE_INVENTORY
	, Inventory(VectorU2(10, 5))
	, HotBar(VectorU2(10, 1))
	, InventoryUI()
	, HotBarUI()
#endif
	, Multiform_DisplaySize("DisplaySize")
	, Multiform_View("View")
	, Multiform_Depth("Depth")
	, Multiform_FOV("FOV")
	, view()
	, AuxThread0(&ContextNoisePlane::AuxThread0Func, this)
	, AuxThread0Time(64)
{
	MediaDirectory = DirectoryInfo("../../media/");

	{
		{
			{
				PalletManager_BufferFullLayout.Position.Change(0);
				PalletManager_BufferFullLayout.Normal.Change(1);
				PalletManager_BufferFullLayout.Texture.Change(2);
				PalletManager.BufferFullLayout = &PalletManager_BufferFullLayout;
			}
			{
				PalletManager_BufferWireLayout.Pos.Change(0);
				PalletManager_BufferWireLayout.Col.Change(1);
				PalletManager.BufferWireLayout = &PalletManager_BufferWireLayout;
			}
			PolyHedraManager.PalletManager = &PalletManager;
		}
		{
			{
				ObjectManagerBasic.ShaderFull.Change({
					MediaDirectory.File("Shaders/PolyHedra/Default.vert"),
					MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag"),
				});
				ObjectManagerBasic.ShaderFull.UniformLayout = &ObjectManagerBasic_ShaderFullLayout;
				ObjectManagerBasic_ShaderFullLayout.Shader = &ObjectManagerBasic.ShaderFull;
			}
			{
				ObjectManagerBasic.ShaderWire.Change({
					MediaDirectory.File("Shaders/Basic3D/Wire.vert"),
					MediaDirectory.File("Shaders/Basic3D/Wire.frag"),
				});
				ObjectManagerBasic.ShaderWire.UniformLayout = &ObjectManagerBasic_ShaderWireLayout;
				ObjectManagerBasic_ShaderWireLayout.Shader = &ObjectManagerBasic.ShaderWire;
			}
			{
				ObjectManagerBasic_BufferFullLayout.Trans.Change(3);
				ObjectManagerBasic_BufferFullLayout.Normal.Change(7);
				ObjectManagerBasic.BufferFullLayout = &ObjectManagerBasic_BufferFullLayout;
			}
			{
				ObjectManagerBasic_BufferWireLayout.Trans.Change(3);
				ObjectManagerBasic_BufferWireLayout.Normal.Change(-1);
				ObjectManagerBasic.BufferWireLayout = &ObjectManagerBasic_BufferWireLayout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerBasic);
		}
		{
			{
				ObjectManagerUI.ShaderFull.Change({
					MediaDirectory.File("Shaders/UI/PHFull.vert"),
					MediaDirectory.File("Shaders/UI/PHFull.frag"),
				});
				ObjectManagerUI.ShaderFull.UniformLayout = &ObjectManagerUI_ShaderFullLayout;
				ObjectManagerUI_ShaderFullLayout.Shader = &ObjectManagerUI.ShaderFull;
			}
			{
				ObjectManagerUI.ShaderWire.UniformLayout = &ObjectManagerUI_ShaderWireLayout;
				ObjectManagerUI_ShaderWireLayout.Shader = &ObjectManagerUI.ShaderWire;
			}
			{
				ObjectManagerUI_BufferFullLayout.Size.Change(3);
				ObjectManagerUI_BufferFullLayout.Pos.Change(4);
				ObjectManagerUI_BufferFullLayout.Rot.Change(5);
				ObjectManagerUI.BufferFullLayout = &ObjectManagerUI_BufferFullLayout;
			}
			{
				ObjectManagerUI.BufferWireLayout = &ObjectManagerUI_BufferWireLayout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerUI);
		}
	}

	AuxThreadBase::ThreadName = "DrawThread";
	Container::Array<Uniform::Layout *> layouts({
		&ObjectManagerBasic_ShaderFullLayout,
		&ObjectManagerBasic_ShaderWireLayout,
		&UIManager.ControlManager.ShaderLayout,
		&UIManager.TextManager.ShaderLayout,
//		&PlaneManager.Shader,
		&ChunkManager.ShaderLayoutU,
		&ChunkManager.ShaderLayoutF,
#ifndef DISABLE_INVENTORY
//		&InventoryShader,
		&ObjectManagerUI_ShaderFullLayout,
		&ObjectManagerUI_ShaderWireLayout,
#endif
	});
	Multiform_DisplaySize.FindUniforms(layouts);
	Multiform_View.FindUniforms(layouts);
	Multiform_Depth.FindUniforms(layouts);
	Multiform_FOV.FindUniforms(layouts);
}



void ContextNoisePlane::ViewUpdateDone()
{
#ifndef DISABLE_VIEW_TANGIBLE
	if (ViewDistance == 0.0f)
#endif
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(view.Trans));
	}
#ifndef DISABLE_VIEW_TANGIBLE
	else
	{
		Multiform_View.ChangeData(Matrix4x4::TransformReverse(
			Trans3D(view.Trans.Position - view.Trans.Rotation.forward(VectorF3(0, 0, ViewDistance)), view.Trans.Rotation)
		));
	}
#endif
}
void ContextNoisePlane::ViewUpdateIntangible(Trans3D change, FrameTime frame_time)
{
	change.Position *= ViewSpeedNoClip;
	if (window[Keys::LeftControl] == State::Down) { change.Position *= ViewFasterNoClip; }
	view.Trans.Position += change.Position * frame_time.Delta;
#ifndef DISABLE_VIEW_TANGIBLE
	ViewEntity.Vel = change.Position;
	ViewEntity.Pos = view.Trans.Position;
#endif
	view.Trans.Rotation += change.Rotation * frame_time.Delta;
	view.Trans.Rotation.X1.clampPI();
}
#ifndef DISABLE_VIEW_TANGIBLE
void ContextNoisePlane::ViewUpdatePhysics(VectorF3 accel)
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
		if (window[Keys::LeftControl] == State::Down) { accel *= ViewFaster; }

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
void ContextNoisePlane::ViewUpdateColliding(FrameTime frame_time)
{
	DisplayBoxEntityVoxels(PalletManager.FindMakePallet(VoxelCube), ChunkManager, ViewEntity, frame_time);
	DisplayBoxEntity(ViewEntity);
	ViewCollisionSide = ViewEntity.Collide(ChunkManager, frame_time);
	DisplayBoxEntity(ViewEntity);
}
#endif
#ifndef DISABLE_VIEW_RAY
void ContextNoisePlane::ViewRayUpdate()
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
			//PolyHedraObject voxel_box_obj(VoxelCube);
			NewPolyHedra::Basic3D::Object voxel_box_obj(VoxelCube);
			//voxel_box_obj.Trans().Position = idx;
			//voxel_box_obj.Trans().Position = ViewHit.Index;
			voxel_box_obj.Data().Trans.Position = ViewHit.Index;
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
void ContextNoisePlane::ViewRayInfo()
{
	std::stringstream ss;
	ss << "ViewRay\n";
	ss << ViewRayAxis0 << " :RayAxis0\n";
	ss << ViewRayAxis1 << " :RayAxis1\n";
	ss << ViewRayAxis2 << " :RayAxis2\n";

	if (ViewHit.Valid())
	{
		ChunkVoxelIndex idx(ViewHit.Index);
		ss << ViewHit.Index << '\n';
		ss << idx.Chunk << '\n';
		ss << idx.Voxel << '\n';
		ss << ViewHitAxis0 << " :HitAxis0\n";
		ss << ViewHitAxis1 << " :HitAxis1\n";

		// Voxel Info
		{
			AccessLockedChunk chunk = ChunkManager.FindAccess(idx.Chunk);
			const Voxel * voxel = (*chunk).FindVoxelOrNull(idx.Voxel);
			if (voxel != nullptr)
			{
				const VoxelPallet * pallet = voxel -> ToPallet();
				ss << (voxel -> Orientation.GetDiag()) << " :Diag\n";
				ss << (voxel -> Orientation.GetFlip()) << " :Flip\n";
				ss << (pallet -> Name) << " :Pallet\n";
			}
			else
			{
				ss << "null";
			}
			ss << '\n';
		}
	}

	UI::Text::Object text; text.Create();
	text.Text() = ss.str();
	text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
	text.AlignTopRight(); // take DisplaySize
	text.Bound().Min = VectorF2();
	text.Bound().Max = window.Size.Buffer.Full;
	text.Color() = ColorF4(1, 1, 1);
}
void ContextNoisePlane::ViewRayDo()
{
#ifndef DISABLE_INVENTORY
	if (PauseMenu.IsInteractible() || OptionsMenu.IsInteractible() || InventoryUI.IsInteractible()) { return; }
#else
	if (PauseMenu.IsInteractible() || OptionsMenu.IsInteractible()) { return; }
#endif

	if (ViewHit.Valid())
	{
		// Side: make part of VoxelHit ?
		// determine place_axis_1 based on where on the face was clicked ?
		// top of face orients to point to top and so on

		if (window.MouseManager[MouseButtons::MouseL] == State::Press)
		{
			Voxel voxel;
			ChunkVoxelIndex idx(ViewHit.Index);
			//ChunkManager.ClearVoxel(hit.Index, voxel);
			std::cout << "main:" << __LINE__ << '\n';
			AccessLockedChunk chunk0 = ChunkManager.FindAccess(idx.Chunk);
			std::cout << "main:" << __LINE__ << '\n';
			if (chunk0.Is())
			{
				AssignLockedChunk chunk1 = chunk0.ToAssign();
				std::cout << "main:" << __LINE__ << '\n';
				(*chunk1).ClearVoxel(idx.Voxel, voxel);
				std::cout << "main:" << __LINE__ << '\n';
			}
			std::cout << "main:" << __LINE__ << '\n';
		}

		if (window.MouseManager[MouseButtons::MouseR] == State::Press)
		{
			if (ViewHitAxis0 == AxisRel::NextX) { ViewHit.Index.X += 1; }
			if (ViewHitAxis0 == AxisRel::NextY) { ViewHit.Index.Y += 1; }
			if (ViewHitAxis0 == AxisRel::NextZ) { ViewHit.Index.Z += 1; }
			if (ViewHitAxis0 == AxisRel::PrevX) { ViewHit.Index.X -= 1; }
			if (ViewHitAxis0 == AxisRel::PrevY) { ViewHit.Index.Y -= 1; }
			if (ViewHitAxis0 == AxisRel::PrevZ) { ViewHit.Index.Z -= 1; }

#ifndef DISABLE_INVENTORY
			if (HotBar.Items[VectorU2(0, 0)] != nullptr)
			{
				ItemVoxel * item = (ItemVoxel*)HotBar.Items[VectorU2(0, 0)];
				if (item -> VoxelPallet != nullptr)
				{
					Voxel voxel = item -> VoxelPallet -> ToVoxel(ViewHitAxis0, ViewHitAxis1);
					ChunkVoxelIndex idx(ViewHit.Index);
					//Chunk * chunk = ChunkManager.FindLockOrNull(idx.Chunk);
					AssignLockedChunk chunk = ChunkManager.FindAccess(idx.Chunk).ToAssign();
					//if (chunk != nullptr)
					if (chunk.Is())
					{
						//chunk -> PlaceVoxel(idx.Voxel, voxel);
						//chunk -> AccessU();
						(*chunk).PlaceVoxel(idx.Voxel, voxel);
					}
				}
			}
#endif
		}
	}
}
#endif
void ContextNoisePlane::ViewUpdateAround(Trans3D change, FrameTime frame_time)
{
	// sperate applying change and moving
	// when intangible, change view directly

	StopWatch sw;
	sw.Start();
#ifndef DISABLE_VIEW_TANGIBLE
	if (ViewTangible)
	{
		ViewUpdatePhysics(change.Position);
		view.Trans.Rotation += change.Rotation * frame_time.Delta;
		view.Trans.Rotation.X1.clampPI();
		ViewUpdateColliding(frame_time);
		view.Trans.Position = ViewEntity.Pos;
	}
	else
#endif
	{
		ViewUpdateIntangible(change, frame_time);
	}
	ViewUpdateDone();
	sw.Stop();
	FrameTime_ViewUpdate_CollisionTime.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
#ifndef DISABLE_VIEW_RAY
	ViewRayUpdate();
	ViewRayInfo();
	ViewRayDo();
#endif
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
			ChunkManager.ChangeCenter((view.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF());
			//ChunkManager.RemoveAround();
			//ChunkManager.InsertAround();
			ChunkManager.UpdateChunksContainer();
			sw.Stop();
			AuxThread0Time.NewValue(sw.ElapsedTime());
		}
	}
}



void ContextNoisePlane::Make()
{
	{
		//window.DefaultColor = ColorF4(0.6f, 0.85f, 0.9f);
		//window.DefaultColor = ColorF4(0.5f, 0.5f, 0.5f);
		window.DefaultColor = ColorF4(0.25f, 0.25f, 0.25f);
		//window.DefaultColor = ColorF4(0.1f, 0.1f, 0.1f);
		view.Depth.Color = window.DefaultColor;
		view.Depth.Range.SetMin(0.5f);

		LightAmbient = LightBase(0.2f, ColorF4(1.0f, 1.0f, 1.0f));
		LightSolar = LightDirection(1.0f, ColorF4(1.0f, 1.0f, 1.0f), !VectorF3(1.0f, -1.0f, 0.0f));
		LightSpot = ::LightSpot(0.0f, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(), VectorF3(), RangeF(0.1f, 1.0f));
	}

#ifndef DISABLE_VIEW_TANGIBLE
	ViewEntity.Pos = VectorF3(0.5f, 0.5f, 0.5f);
	ViewEntity.Box = BoxF3(
		VectorF3(-0.4f, -1.7f, -0.4f),
		VectorF3(+0.4f, +0.1f, +0.4f)
	);
#endif

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
#ifndef DISABLE_VIEW_TANGIBLE
	{
		ViewEntity.PolyHedra = new PolyHedra();
		PolyHedraBoxEdges(*ViewEntity.PolyHedra, ViewEntity.Box);
		PalletManager.FindMakePallet(ViewEntity.PolyHedra);
	}
#endif

	// Voxels
	{
		VoxelGeometryPallet::GeometryCube.InitCube();
		VoxelGeometryPallet::GeometryCylinder.InitCylinder();
		VoxelGeometryPallet::GeometrySlope.InitSlope();

		VoxelPalletMap::All.Default(MediaDirectory);
		//VoxelPalletMap::All.MakePolyHedra();

		Structure::Default();
	}

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
		PauseMenu.Show();
		UIManager.WindowControl.ChildInsert(PauseMenu);
	}
	// Options
	{
		//OptionsMenu.FPS.SetValueX(window.FrameTime.WantedFramesPerSecond);
		OptionsMenu.FPS.SetValueX(64);
		OptionsMenu.FOV.SetValueX(view.FOV.ToDegrees());

		//OptionsMenu.Depth.SetValueX(100.0f); // get Depth. also depth works weirdly ?
		OptionsMenu.Depth.SetValueX(1000.0f); // get Depth. also depth works weirdly ?
		OptionsMenu.DepthRange.SetValueX(view.Depth.Range.GetMin());

		// Remove range should never be less then Insert
		// make RemoveRange = InsertRange * 2 ?
		// make RemoveRange = InsertRange + n ?

		OptionsMenu.Hide();
		UIManager.WindowControl.ChildInsert(OptionsMenu);
	}
	// Debug
	{
		DebugMenu.FPS.Check.Check(true);
		DebugMenu.VoxelChunkMemory.Check.Check(true);

		DebugMenu.Hide();
		UIManager.WindowControl.ChildInsert(DebugMenu);
	}
	// Inventory
#ifndef DISABLE_INVENTORY
	{
		for (unsigned int i = 0; i < VoxelPalletMap::All.Data.Count(); i++)
		{
			Inventory.Items[i] = new ItemVoxel(VoxelPalletMap::All.Data[i]);
		}
		InventoryUI.Change(&Inventory);
		InventoryUI.Hide();
		UIManager.WindowControl.ChildInsert(InventoryUI);
	}
#endif
	// HotBar
#ifndef DISABLE_INVENTORY
	{
		HotBarUI.Anchor.Y.AnchorMax(0);
		HotBarUI.Change(&HotBar);
		//HotBarUI.Hide();
		UIManager.WindowControl.ChildInsert(HotBarUI);
	}
#endif
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
	VoxelPalletMap::All.LoadTextures(ChunkManager);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	VoxelPalletMap::All.MakePolyHedra();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	VoxelGeometryPallet::Default();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	MakeControls();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	//ChunkManager.ChangeSize(0, 0);
	//ChunkManager.ChangeSize(2, 1);
	ChunkManager.ChangeSize(8, 6);
	//ChunkManager.ChangeSize(16, 8);
	//ChunkManager.ChangeSize(16, 12);
	//ChunkManager.ChangeSize(32, 16);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	Multiform_Depth.ChangeData(view.Depth);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	Multiform_FOV.ChangeData(view.FOV);
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



static unsigned int				TextCharCount = 0;

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

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	sw.Clear(); sw.Start();
	ObjectManagerBasic.GraphicsDrawFull();
	ObjectManagerBasic.GraphicsDrawWire();
	sw.Stop(); FrameTime_Draw_DrawPolyHedra.NewValue(sw.ElapsedTime());

	//PlaneManager.Draw();

	sw.Clear(); sw.Start();
	ChunkManager.ShaderU.Bind();
	ChunkManager.ShaderLayoutU.LightAmbient.Put(LightAmbient);
	ChunkManager.ShaderLayoutU.LightSolar.Put(LightSolar);
	ChunkManager.ShaderLayoutU.LightSpot.Put(LightSpot);
	ChunkManager.ShaderLayoutU.LightSpotCount.Put(1);
	sw.Stop(); FrameTime_Draw_UniformChunk.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	ChunkManager.Draw();
	sw.Stop(); FrameTime_Draw_DrawChunk.NewValue(sw.ElapsedTime());
//	ChunkManager.UpdateChunksArrayDraw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	{
		sw.Clear(); sw.Start(); // sw.ClearStart(); clear while running should keep running
		UIManager.WindowControl.Update();
		UIManager.Resize(window.Size);
		UIManager.UpdateMouse(window.MouseManager.CursorPosition());
		UIManager.ControlManager.MakeInstances();
		UIManager.ControlManager.Draw();
		sw.Stop(); FrameTime_Draw_DrawControl.NewValue(sw.ElapsedTime()); // sw.StopElapsedTime(); dont need to stop to get time ?
	}

	sw.Clear(); sw.Start();
	UIManager.TextManager.MakeInstances();
	sw.Stop(); FrameTime_Draw_MakeText.NewValue(sw.ElapsedTime());

	UIManager.TextManager.ShowInstancesTime();

	sw.Clear(); sw.Start();
	UIManager.TextManager.Draw();
	TextCharCount = UIManager.TextManager.InstancesArray.Length();
	sw.Stop(); FrameTime_Draw_DrawText.NewValue(sw.ElapsedTime());

	UIManager.GraphManager.MakeInstances();
	UIManager.GraphManager.Draw();

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	ObjectManagerUI.GraphicsDrawFull();
	ObjectManagerUI.GraphicsDrawWire();

	sw_total.Stop(); FrameTime_Draw_DrawTotal.NewValue(sw_total.ElapsedTime());

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
#ifndef DISABLE_INVENTORY
static ValueAccumulator<float>		InventoryCursorTime(64);
#endif

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
		ss << Memory1000ToString(buffer_data_f_memory * sizeof(VoxelGeometryDataF::Face));
		ss << " / ";
		ss << Memory1000ToString(buffer_data_f_limit * sizeof(VoxelGeometryDataF::Face));
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
	if (DebugMenu.FPS.Check.IsChecked())
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
	if (DebugMenu.TimeThreads.Check.IsChecked())
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

#ifndef DISABLE_INVENTORY
		ShowNameTimeLine(ss, "Inventory  Cursor", InventoryCursorTime);
#endif
		ShowNameTimeLine(ss, "AuxThread       0", AuxThread0Time);
		ss << '\n';
	}
	sw.Stop(); TextTime_ThreadTime.NewValue(sw.ElapsedTime());

	// ChunkManager Time
	sw.Clear(); sw.Start();
	if (DebugMenu.TimeWaitDo.Check.IsChecked())
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
	if (DebugMenu.View.Check.IsChecked())
	{
		ss << "View " << view.Trans.Position << '\n';
#ifndef DISABLE_VIEW_TANGIBLE
		ss << "View " << ViewEntity.Vel << ' ' << ViewEntity.Vel.length() << '\n';
		ss << "None : " << (ViewCollisionSide.None) << '\n';
		ss << "PrevX: " << (ViewCollisionSide.PrevX) << '\n';
		ss << "PrevY: " << (ViewCollisionSide.PrevY) << '\n';
		ss << "PrevZ: " << (ViewCollisionSide.PrevZ) << '\n';
		ss << "NextX: " << (ViewCollisionSide.NextX) << '\n';
		ss << "NextY: " << (ViewCollisionSide.NextY) << '\n';
		ss << "NextZ: " << (ViewCollisionSide.NextZ) << '\n';
#endif
		ss << '\n';
	}
	sw.Stop(); TextTime_View.NewValue(sw.ElapsedTime());

	// ChunkHere
	sw.Clear(); sw.Start();
	if (DebugMenu.ChunkHere.Check.IsChecked())
	{
		//VoxelIndex idx = ChunkManager.FindVoxelIndex(view.Trans.Position);
		ChunkVoxelIndex idx(view.Trans.Position.roundF());
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
	if (DebugMenu.ChunkRange.Check.IsChecked())
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
	if (DebugMenu.VoxelChunkMemory.Check.IsChecked())
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
		if (DebugMenu.IsVisible())
		{
			text.TextPosition().X = DebugMenu.Anchor.X.GetMinSize();
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
}
#ifndef DISABLE_INVENTORY
void ContextNoisePlane::InventoryCursor(FrameTime frame_time)
{
	StopWatch sw;
	sw.Start();

	static float time_sum = 0.0f;

	VectorF2	PixelSize(40, 40);
	VectorF2	PixelPos;

	if (HotBar.Items[VectorU2(0, 0)] != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)HotBar.Items[VectorU2(0, 0)];
		PixelPos.X = window.Size.Buffer.Full.X - 40;
		PixelPos.Y = 40;
		NewPolyHedra::UserInterface::Object obj(item -> VoxelPallet -> PolyHedra);
		obj.Data().Size = PixelSize;
		obj.Data().Pos = PixelPos;
		obj.Data().Rot.X1 = Angle::Degrees(15);
		obj.Data().Rot.Y2 = Angle::Radians(time_sum);
	}

	if (InventorySlot::StaticItem != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)InventorySlot::StaticItem;
		PixelPos = window.MouseManager.CursorPosition().Buffer.Corner;
		NewPolyHedra::UserInterface::Object obj(item -> VoxelPallet -> PolyHedra);
		obj.Data().Size = PixelSize;
		obj.Data().Pos = PixelPos;
		obj.Data().Rot.X1 = Angle::Degrees(15);
		obj.Data().Rot.Y2 = Angle::Radians(time_sum);
	}

	time_sum += frame_time.Delta;

	sw.Stop();
	InventoryCursorTime.NewValue(sw.ElapsedTime());
}
#endif
// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void ContextNoisePlane::FrameInput()
{
	//StopWatch sw;
	//sw.Start();

	if (window[Keys::Escape] == State::Press)
	{
		OptionsMenu.Hide();
#ifndef DISABLE_INVENTORY
		InventoryUI.Hide();
#endif
		//HotBarUI.Hide();
		if (PauseMenu.IsVisible())
		{
			//AuxThreadBase::Idle = false;
			PauseMenu.Hide();
		}
		else
		{
			//AuxThreadBase::Idle = true;
			PauseMenu.Show();
		}
	}
	if (window[Keys::E] == State::Press)
	{
		if (!PauseMenu.IsVisible() && !OptionsMenu.IsVisible())
		{
#ifndef DISABLE_INVENTORY
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
#endif
		}
	}

#ifndef DISABLE_VIEW_RAY
	if (window[Keys::D1] == State::Press) { Toggle(ViewRaySync); }
	//if (window[Keys::D2] == State::Press) { Toggle(ChunkManager.ViewRayPolyHedra, ViewRayPolyHedra); }
	//if (window[Keys::D3] == State::Press) { Toggle(ChunkManager.VoxelBoxPolyHedra, VoxelCube); }
#endif

	if (window[Keys::F7] == State::Press)
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

#ifndef DISABLE_VIEW_TANGIBLE
	if (window[Keys::F2] == State::Press) { Toggle(ViewTangible); }
#endif
	if (window[Keys::F3] == State::Press)
	{
#ifndef DISABLE_VIEW_TANGIBLE
		if (ViewDistance == 0.0f)
		{ ViewDistance = 2.0f; }
		else
		{ ViewDistance = 0.0f; }
#endif
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

#ifndef DISABLE_INVENTORY
	if (PauseMenu.IsVisible() || OptionsMenu.IsVisible() || InventoryUI.IsVisible())
#else
	if (PauseMenu.IsVisible() || OptionsMenu.IsVisible())
#endif
	{
		if (window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeFree(); }
	}
	else
	{
		if (!window.MouseManager.CursorModeIsLocked()) { window.MouseManager.CursorModeLock(); }
	}

	/*if (window[Keys::P] == State::Press)
	{
		ChunkVoxelIndex idx(view.Trans.Position.roundF());
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
	LightSpot.Pos = view.Trans.Position;
	LightSpot.Dir = view.Trans.Rotation.forward(VectorF3(0, 0, 1));

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw;

	// this is general Update, not Draw specific
	sw.Clear(); sw.Start();
	FrameInput();
	sw.Stop(); FrameTime_Input.NewValue(sw.ElapsedTime());

	// this is general Update, not Draw specific, except View Matrix Uniform
	sw.Clear(); sw.Start();
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
	if (DebugMenu.VoxelChunkBoxes.Check.IsChecked())
	{
		NewPolyHedra::Pallet * pallet = PalletManager.FindMakePallet(VoxelChunkCube);
		for (unsigned int i = 0; i < ChunkManager.Chunks.Length(); i++)
		{
			Chunk * chunk = ChunkManager.Chunks[i];
			if (chunk == nullptr) { continue; }
			NewPolyHedra::Basic3D::Object chunk_box(pallet);
			chunk_box.Data().Trans.Position = chunk -> Index * CHUNK_VALUES_PER_SIDE;
			chunk_box.ShowWire();
		}
	}
	sw.Stop(); FrameTime_ChunkBoxes.NewValue(sw.ElapsedTime());
	
	// rechnically not Draw related, but PolyHedraManager is currently not intended for different Threads
	sw.Clear(); sw.Start();
	if (DebugMenu.ChunkHere.Check.IsChecked())
	{
		ChunkVoxelIndex idx(view.Trans.Position.roundF());
		NewPolyHedra::Basic3D::Object chunk_box(VoxelChunkCube);
		chunk_box.Data().Trans.Position = idx.Chunk * CHUNK_VALUES_PER_SIDE;
		chunk_box.ShowWire();
	}
	sw.Stop(); FrameTime_ChunkHereBox.NewValue(sw.ElapsedTime());

	// rechnically not Draw related, but TextManager is currently not intended for different Threads
	sw.Clear(); sw.Start();
	FrameText(frame_time);
	sw.Stop(); FrameTime_Text.NewValue(sw.ElapsedTime());

#ifndef DISABLE_INVENTORY
	InventoryCursor(frame_time);
#endif

	sw.Clear(); sw.Start();
	Draw();
	sw.Stop(); FrameTime_Draw.NewValue(sw.ElapsedTime());

	sw_total.Stop(); FrameTime_.NewValue(sw_total.ElapsedTime());
}

void ContextNoisePlane::Resize(DisplaySize display_size)
{
	::InventorySlot::WindowSize = display_size;
	Multiform_DisplaySize.ChangeData(display_size);
}



// make these virtual and put them in Base
void ContextNoisePlane::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void ContextNoisePlane::MouseClick(ClickArgs args)
{
	UIManager.MouseClick(args);
}
void ContextNoisePlane::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void ContextNoisePlane::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void ContextNoisePlane::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void ContextNoisePlane::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
