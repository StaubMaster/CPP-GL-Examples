#include "ContextNoisePlane.hpp"
#include "new.hpp"

// Debug
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Debug.hpp"
#include "ValueType/_Show.hpp"
#include "ValueType/_Include.hpp"

// Math
#include <math.h>



#ifndef DISABLE_INVENTORY
InventoryShader::~InventoryShader()
{ }
InventoryShader::InventoryShader()
	: ::PolyHedraFull::Shader()
	, DisplaySize(*this, "DisplaySize")
{ }
#endif



#include "main_static.cpp"





static ValueAverager<float>		FrameTime_(64);
static ValueAverager<float>		FrameTime_Input(64);
static ValueAverager<float>		FrameTime_ViewUpdate(64);
static ValueAverager<float>		FrameTime_ThreadUpdate(64);
static ValueAverager<float>		FrameTime_ChunkBoxes(64);
static ValueAverager<float>		FrameTime_ChunkHereBox(64);
static ValueAverager<float>		FrameTime_Text(64);
static ValueAverager<float>		FrameTime_Draw(64);
static ValueAverager<float>		FrameTime_DrawThread(64);

static ValueAverager<float>		FrameTime_ViewUpdate_CollisionTime(64);
static ValueAverager<float>		FrameTime_ViewUpdate_ChunksTime(64);
static ValueAverager<float>		FrameTime_ViewUpdate_RayTime(64);

static ValueAverager<float>		FrameTime_Text_Assamble(64);
static ValueAverager<float>		FrameTime_Text_Instance(64);

static ValueAverager<float>		TextTime_TestFPS(64);
static ValueAverager<float>		TextTime_ThreadTime(64);
static ValueAverager<float>		TextTime_ChunkManagerTime(64);
static ValueAverager<float>		TextTime_View(64);
static ValueAverager<float>		TextTime_ChunkHere(64);
static ValueAverager<float>		TextTime_ChunkRange(64);
static ValueAverager<float>		TextTime_VoxelChunkMemory(64);
static ValueAverager<float>		TextTime_VoxelChunkMemory_Wait(64);
static ValueAverager<float>		TextTime_VoxelChunkMemory_Loop(64);
static ValueAverager<float>		TextTime_VoxelChunkMemory_Show(64);

static ValueAverager<float>		FrameTime_Draw_DrawTotal(64);
static ValueAverager<float>		FrameTime_Draw_DrawPolyHedra(64);
static ValueAverager<float>		FrameTime_Draw_UniformChunk(64);
static ValueAverager<float>		FrameTime_Draw_DrawChunk(64);
static ValueAverager<float>		FrameTime_Draw_DrawControl(64);
static ValueAverager<float>		FrameTime_Draw_MakeText(64);
static ValueAverager<float>		FrameTime_Draw_DrawText(64);





ContextNoisePlane::~ContextNoisePlane()
{ }
ContextNoisePlane::ContextNoisePlane()
	: ContextBase()
	, PolyHedraManager()
	, ControlManager()
	, TextManager()
//	, PlaneManager()
	, ChunkManager()
	, GenerationNoise()
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
	, AuxThread2(&ContextNoisePlane::AuxThread2Func, this)
	, AuxThread3(&ContextNoisePlane::AuxThread3Func, this)
{
	AuxThreadBase::ThreadName = "DrawThread";
	PolyHedraManager.MakeCurrent();
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
	Container::Array<Uniform::Layout *> layouts({
		&PolyHedraManager.ShaderLayoutFullDefault,
		&PolyHedraManager.ShaderLayoutWireDefault,
		&ControlManager.ShaderLayout,
		&TextManager.ShaderLayout,
//		&PlaneManager.Shader,
		&ChunkManager.ShaderLayoutU,
//		&ChunkManager.ShaderLayoutF,
#ifndef DISABLE_INVENTORY
		&InventoryShader,
#endif
	});
	Multiform_DisplaySize.FindUniforms(layouts);
	Multiform_View.FindUniforms(layouts);
	Multiform_Depth.FindUniforms(layouts);
	Multiform_FOV.FindUniforms(layouts);

	GenerationNoise.Plane = Perlin2D::Random(VectorU2(8, 8));
	GenerationNoise.Cave0 = Perlin3D::Random(VectorU3(8, 8, 8));
	GenerationNoise.Cave1 = Perlin3D::Random(VectorU3(8, 8, 8));
	GenerationNoise.Cave2 = Perlin3D::Random(VectorU3(8, 8, 8));
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
#ifndef DISABLE_VIEW_TANGIBLE
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
#endif
void ContextNoisePlane::ViewUpdateIntangible(Trans3D change, FrameTime frame_time)
{
	change.Position *= ViewSpeedNoClip;
	if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { change.Position *= ViewFasterNoClip; }
#ifndef DISABLE_VIEW_TANGIBLE
	ViewEntity.Vel = change.Position;
	ViewEntity.Pos += ViewEntity.Vel * frame_time.Delta;
	view.Trans.Position = ViewEntity.Pos;
#else
	view.Trans.Position += change.Position * frame_time.Delta;
#endif
	view.Trans.Rotation += change.Rotation * frame_time.Delta;
	view.Trans.Rotation.X1.clampPI();
}
#ifndef DISABLE_VIEW_TANGIBLE
void ContextNoisePlane::ViewUpdateColliding(FrameTime frame_time)
{
	DisplayBoxEntityVoxels(PolyHedraManager.FindPolyHedra(VoxelCube), ChunkManager, ViewEntity, frame_time);
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
#endif
#ifndef DISABLE_VIEW_RAY
void ContextNoisePlane::ViewRayDo()
{
#ifndef DISABLE_INVENTORY
	if (PauseMenu.IsInteractible() || OptionsMenu.IsInteractible() || InventoryUI.IsInteractible()) { return; }
#else
	if (PauseMenu.IsInteractible() || OptionsMenu.IsInteractible()) { return; }
#endif
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
				chunk -> AccessU();
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

#ifndef DISABLE_INVENTORY
			if (HotBar.Items[VectorU2(0, 0)] != nullptr)
			{
				ItemVoxel * item = (ItemVoxel*)HotBar.Items[VectorU2(0, 0)];
				if (item -> VoxelPallet != nullptr)
				{
					Voxel voxel = item -> VoxelPallet -> ToVoxel(ViewHitAxis0, ViewHitAxis1);
					ChunkVoxelIndex idx(ViewHit.Index);
					Chunk * chunk = ChunkManager.FindLockOrNull(idx.Chunk);
					if (chunk != nullptr)
					{
						chunk -> PlaceVoxel(idx.Voxel, voxel);
						chunk -> AccessU();
					}
				}
			}
#endif
		}
//		std::cout << "main:" << __LINE__ << '\n';
	}

	{
		UI::Text::Object text; text.Create();
		text.Text() = ss.str();
		text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
		text.AlignTopRight(); // take DisplaySize
		text.Bound().Min = VectorF2();
		text.Bound().Max = window.Size.Buffer.Full;
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
#endif
void ContextNoisePlane::ViewUpdateAround(Trans3D change, FrameTime frame_time)
{
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

	// needs new View Position
	// but Ray needs new Chunks ?
	// they dont need eachother in the same frame
	// so it should be fine to use a old View Position
	// or Ray into old Chunks

	sw.Clear(); sw.Start();
	ChunkManager.GraphicsUpdate(); // this has nothing to do with View. should be done in DrawThread
	//ChunkManager.ChangeCenter((view.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF()); // do this in Insert/Remove Thread
	//ChangeCenter segfaults
	sw.Stop();
	FrameTime_ViewUpdate_ChunksTime.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
#ifndef DISABLE_VIEW_RAY
	ViewRayUpdate();
	ViewRayDo();
#endif
	sw.Stop();
	FrameTime_ViewUpdate_RayTime.NewValue(sw.ElapsedTime());
}





/* Draw Thread should focus on Drawing
	avoid locking
	move View stuff to another Thread ?
	Draw Thread needs to Create/Delete Graphics
	Input from different Thread ?
*/

static ValueAverager<float>		TimeUpdateThread(64);

static WaitDoTime	TimeGenerateFind("TimeGenerateFind");
static WaitDoTime	TimeGenerate("TimeGenerate");

static WaitDoTime	TimeAssambleFind("TimeAssambleFind");
static WaitDoTime	TimeAssamble("TimeAssamble");

/*
put the Finding Functino into the Thread as well
condition_variable is basically just a Poke
move the condition_variable and Mutex into the Thread ?
then the Chunks/Manager need to know bout the Thread to .Poke() it
*/

thread_local const char * AuxThreadBase::ThreadName = "ThreadName";

void ContextNoisePlane::AuxThread0Func()
{
	AuxThreadBase::ThreadName = "AuxThread0";
	StopWatch sw;
	while (!AuxThread0Term)
	{
		if (!AuxThread0Idle)
		{
			sw.Clear(); sw.Start();
			//ChunkManager.RemoveAround();
			//ChunkManager.InsertAround();
			ChunkManager.UpdateChunksContainer();
			sw.Stop();
			AuxThread0Time.NewValue(sw.ElapsedTime());
		}
	}
}
void ContextNoisePlane::AuxThread2Func()
{
	AuxThreadBase::ThreadName = "AuxThread2";
	while (!AuxThread2Term)
	{
		StopWatch sw;
		AccessLockedChunk chunk;

		std::unique_lock<std::mutex> lk(ChunkManager.GenerateChunkConditionMutex);
		ChunkManager.GenerateChunkConditionVar.wait(lk, [&]
		{
			if (AuxThread2Term) { return true; }
			if (AuxThread2DoIdle) { return false; }

			ChunkManager.ChunksLock.AccessL(sw, TimeGenerateFind);
			chunk = ChunkManager.GenerateChunkFind();
			ChunkManager.ChunksLock.AccessU(sw, TimeGenerateFind);

			if (chunk.Is())
			{
				AuxThread2IsIdle = false;
				return true;
			}
			AuxThread2IsIdle = true;
			return false;
		});

		if (AuxThread2Term) { return; }

		if (!chunk.Is()) { continue; }

		AssignLockedChunk chunk2 = chunk.ToAssign();

		sw.Clear();
		sw.Start();
		(*chunk2).GenerateTerrain(GenerationNoise);
		(*chunk2).GenerateDecoration(GenerationNoise.Plane, GenerationNoise.Cave0);
		sw.Stop();
		TimeGenerate.DoTime.NewValue(sw.ElapsedTime());
		TimeGenerate.ThreadName = AuxThreadBase::ThreadName;
	}
}
void ContextNoisePlane::AuxThread3Func()
{
	AuxThreadBase::ThreadName = "AuxThread3";
	while (!AuxThread3Term)
	{
		StopWatch sw;
		AccessLockedChunk chunk;

		std::unique_lock<std::mutex> lk(ChunkManager.AssambleChunkConditionMutex);
		ChunkManager.AssambleChunkConditionVar.wait(lk, [&]
		{
			if (AuxThread3Term) { return true; }
			if (AuxThread3DoIdle) { return false; }

			ChunkManager.ChunksLock.AccessL(sw, TimeAssambleFind);
			chunk = ChunkManager.AssambleChunkFind();
			ChunkManager.ChunksLock.AccessU(sw, TimeAssambleFind);

			if (chunk.Is())
			{
				AuxThread3IsIdle = false;
				return true;
			}
			AuxThread3IsIdle = true;
			return false;
		});

		if (AuxThread3Term) { return; }

		if (!chunk.Is()) { continue; }

		AssignLockedChunk chunk2 = chunk.ToAssign();

		sw.Clear();
		sw.Start();
		(*chunk2).AssambleDecoration();
		sw.Stop();
		TimeAssamble.DoTime.NewValue(sw.ElapsedTime());
		TimeAssamble.ThreadName = AuxThreadBase::ThreadName;
	}
}
void ContextNoisePlane::DrawThreadUpdate()
{
	StopWatch sw;
	sw.Start();

	//ChunkManager.RemoveAround();
	//ChunkManager.InsertAround();
	//ChunkManager.UpdateChunksContainer();

	//ChunkManager.GenerateAround(Perlin2, Perlin3);

	//ChunkManager.GraphicsUpdateDataAround();

	sw.Stop();
	TimeUpdateThread.NewValue(sw.ElapsedTime());
}



CenterIndexLoop3D CenterIndexLoop;

static VectorI3 CenterIndexLoop_Center;
static Container::Binary<VectorI3> CenterIndexLoop_List;
static void CenterIndexLoop_Clear()
{
	CenterIndexLoop_Center = VectorI3(0, 0, 0);
	CenterIndexLoop_List.Clear();

	CenterIndexLoop.New(2);
}
static void CenterIndexLoop_Loop()
{
	if (!CenterIndexLoop.Done())
	{
		CenterIndexLoop_List.Insert(CenterIndexLoop.Index());
		CenterIndexLoop.Continue();
	}
}
static void CenterIndexLoop_Show(PolyHedra * polyhedra)
{
	for (unsigned int i = 0; i < CenterIndexLoop_List.Count(); i++)
	{
		PolyHedraObject obj(polyhedra);
		obj.ShowFull();
		obj.Trans().Position = (CenterIndexLoop_List[i] + CenterIndexLoop_Center);
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
		view.Depth.Range.ChangeMin(0.5f);

		LightAmbient = ::LightBase(0.2f, ColorF4(1.0f, 1.0f, 1.0f));
		LightSolar = ::LightSolar(1.0f, ColorF4(1.0f, 1.0f, 1.0f), !VectorF3(1.0f, -1.0f, 0.0f));
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
		PolyHedra * picture = PolyHedra::Generate::DuoHedra(img);
		delete picture;
	}

	// 3 Cuboids. implement Scaling for Transformations
	{
		//VoxelCube = new PolyHedra();
		VoxelCube = PolyHedra::Generate::HexaHedron(0.5f);
		//PolyHedraBoxEdges(*VoxelCube, BoxF3(VectorF3(0.0f), VectorF3(1.0f)));
		PolyHedraManager.PlacePolyHedra(VoxelCube);
	}
	{
		VoxelChunkCube = new PolyHedra();
		PolyHedraBoxEdges(*VoxelChunkCube, BoxF3(VectorF3(0.1f), VectorF3(CHUNK_VALUES_PER_SIDE - 0.1f)));
		PolyHedraManager.PlacePolyHedra(VoxelChunkCube);
	}
#ifndef DISABLE_VIEW_TANGIBLE
	{
		ViewEntity.PolyHedra = new PolyHedra();
		PolyHedraBoxEdges(*ViewEntity.PolyHedra, ViewEntity.Box);
		PolyHedraManager.PlacePolyHedra(ViewEntity.PolyHedra);
	}
#endif

	// Voxels
	{
		VoxelGeometryPallet::Cube.InitCube();
		VoxelGeometryPallet::Cylinder.InitCylinder();
		VoxelGeometryPallet::Slope.InitSlope();

		VoxelPalletMap::All.Default(MediaDirectory);
		//VoxelPalletMap::All.MakePolyHedra();

		Structure::Default();
	}

	{
		ViewRayPolyHedra = PolyHedra::Generate::ConeC(8, 0.01f, 0.1f);
		PolyHedraManager.PlacePolyHedra(ViewRayPolyHedra);
	}
	//Perlin2D::DebugShow();
	//TestRandom();

	CenterIndexLoop_Clear();
}



void ContextNoisePlane::MakeControls()
{
	std::cerr << "MakeControls()\n";
	// Pause
	{
		PauseMenu.Continue.ClickFunc.Assign(&PauseMenu, &PauseMenu::ContinueFunc);
		PauseMenu.Options.ClickFunc.Assign(&PauseMenu, &PauseMenu::OptionsFunc);
		PauseMenu.Debug.ClickFunc.Assign(&PauseMenu, &PauseMenu::DebugFunc);
		PauseMenu.Exit.ClickFunc.Assign(&PauseMenu, &PauseMenu::ExitFunc);

		PauseMenu.Show();
		ControlManager.Window.ChildInsert(PauseMenu);
	}
	// Options
	{
		OptionsMenu.FPS.ValueXChangedFunc.Assign(&OptionsMenu, &OptionsMenu::FPSFunc);
		//OptionsMenu.FPS.SetValueX(window.FrameTime.WantedFramesPerSecond);
		OptionsMenu.FPS.SetValueX(1024);

		OptionsMenu.FOV.ValueXChangedFunc.Assign(&OptionsMenu, &OptionsMenu::FOVFunc);
		OptionsMenu.FOV.SetValueX(view.FOV.ToDegrees());

		OptionsMenu.Depth.ValueXChangedFunc.Assign(&OptionsMenu, &OptionsMenu::DepthFunc);
		//OptionsMenu.Depth.SetValueX(100.0f); // get Depth. also depth works weirdly ?
		OptionsMenu.Depth.SetValueX(1000.0f); // get Depth. also depth works weirdly ?

		OptionsMenu.DepthRange.ValueXChangedFunc.Assign(&OptionsMenu, &OptionsMenu::DepthRangeFunc);
		OptionsMenu.DepthRange.SetValueX(view.Depth.Range.Min);

		// Remove range should never be less then Insert
		// make RemoveRange = InsertRange * 2 ?
		// make RemoveRange = InsertRange + n ?

		OptionsMenu.ChunkInsert.ValueXChangedFunc.Assign(&OptionsMenu, &OptionsMenu::Chunk_InsertFunc);
		OptionsMenu.ChunkRemove.ValueXChangedFunc.Assign(&OptionsMenu, &OptionsMenu::Chunk_RemoveFunc);

		OptionsMenu.Back.ClickFunc.Assign(&OptionsMenu, &OptionsMenu::BackFunc);

		OptionsMenu.Hide();
		ControlManager.Window.ChildInsert(OptionsMenu);
	}
	// Debug
	{
		DebugMenu.FPS.Check.Check(true);

		DebugMenu.VoxelChunkMemory.Check.Check(true);

		DebugMenu.Generation3DComparison.ValueXChangedFunc.Assign(this, &ContextNoisePlane::DebugMenu_Generation3DComparison);
		//DebugMenu.Generation3DComparison.SetValueX(Chunk::Generation3D_Comparison);

		DebugMenu.Generation3DFactor.ValueXChangedFunc.Assign(this, &ContextNoisePlane::DebugMenu_Generation3DFactor);
		//DebugMenu.Generation3DFactor.SetValueX(Chunk::Generation3D_Factor);

		DebugMenu.Hide();
		ControlManager.Window.ChildInsert(DebugMenu);
	}
	// Inventory
#ifndef DISABLE_INVENTORY
	{
		InventoryPolyHedraManager.MakeCurrent();
		for (unsigned int i = 0; i < VoxelPalletMap::All.Data.Count(); i++)
		{
			Inventory.Items[i] = new ItemVoxel(VoxelPalletMap::All.Data[i]);
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
#endif
	// HotBar
#ifndef DISABLE_INVENTORY
	{
		InventoryPolyHedraManager.MakeCurrent();
		HotBarUI.Anchor.Y.AnchorMax(0);
		HotBarUI.Change(&HotBar);
		//HotBarUI.Hide();
		ControlManager.Window.ChildInsert(HotBarUI);
		PolyHedraManager.MakeCurrent();
	}
#endif
}

void ContextNoisePlane::DebugMenu_Generation3DComparison(float val)
{
	(void)val;
	//Chunk::Generation3D_Comparison = val;
	//DebugMenu.Generation3DComparison.SetText("3D Comp:" + std::to_string(Chunk::Generation3D_Comparison));
	//ChunkManager.Clear();
}
void ContextNoisePlane::DebugMenu_Generation3DFactor(float val)
{
	(void)val;
	//Chunk::Generation3D_Factor = 1 << ((int)val);
	//DebugMenu.Generation3DFactor.SetText("3D Fact:" + std::to_string(Chunk::Generation3D_Factor));
	//ChunkManager.Clear();
}



// a lot of the managers are siminal with the bool flags and function names
// make a Base ? to organize
void ContextNoisePlane::ChangeMedia()
{
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	// PolyHedraManager
	PolyHedraManager.InitExternal(MediaDirectory);
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.frag")),
		});
		ControlManager.Shader.Change(code);
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		ControlManager.LayoutMain.Pos.Change(0);
		ControlManager.Buffer.MainBuffer.AttributeLayout = &ControlManager.LayoutMain;
		ControlManager.LayoutInst.Min.Change(1);
		ControlManager.LayoutInst.Max.Change(2);
		ControlManager.LayoutInst.Layer.Change(3);
		ControlManager.LayoutInst.Col.Change(4);
		ControlManager.Buffer.InstBuffer.AttributeLayout = &ControlManager.LayoutInst;
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		ControlManager.Window.ChangeManager(&ControlManager);
		ControlManager.Window.ChangeManager(&TextManager);
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;

	// TextManager
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(MediaDirectory.File("Shaders/UI/Text.vert")),
			::Shader::Code(MediaDirectory.File("Shaders/UI/Text.frag")),
		});
		TextManager.Shader.Change(code);
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		TextManager.LayoutMain.Pos.Change(0);
		TextManager.Buffer.MainBuffer.AttributeLayout = &TextManager.LayoutMain;
		TextManager.LayoutInst.Pos.Change(1);
		TextManager.LayoutInst.PalletIdx.Change(2);
		TextManager.LayoutInst.TextIdx.Change(3);
		TextManager.Buffer.InstBuffer.AttributeLayout = &TextManager.LayoutInst;
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		TextManager.TextFont = UI::Text::Font::Parse(
			MediaDirectory.File("Text/Font0.atlas")
		);

		std::cout << "TextFont\n";

		std::cout << "Characters\n";
		for (unsigned int i = 0; i < TextManager.TextFont -> Characters.Count(); i++)
		{
			std::cout << ' ' << (char)(TextManager.TextFont -> Characters[i].Code);
		}
		std::cout << '\n';

		std::cout << "CharacterRanges\n";
		for (unsigned int j = 0; j < TextManager.TextFont -> CharacterRanges.Count(); j++)
		{
			for (unsigned int i = 0; i < TextManager.TextFont -> CharacterRanges[j] -> Characters.Count(); i++)
			{
				std::cout << ' ' << (char)(TextManager.TextFont -> CharacterRanges[j] -> Characters[i].Code);
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;

	// PlaneManager
	/*{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Plane/Plane.frag")),
		});
		PlaneManager.Shader.Change(code);
	}*/

	// ChunkManager
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		Container::Array<::Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/Voxel/VoxelU.vert")),
			Shader::Code(MediaDirectory.File("Shaders/Voxel/Voxel.frag")),
		});
		ChunkManager.ShaderU.Change(code);
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	{
		ChunkManager.BufferU.Layout.Voxel.Change(0);
		ChunkManager.BufferU.Layout.Texture.Change(1);
		ChunkManager.BufferU.Layout.Chunk.Change(2);
		ChunkManager.BufferU.Buffer.MainBuffer.AttributeLayout = &ChunkManager.BufferU.Layout;
	}
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;

	// Inventory
#ifndef DISABLE_INVENTORY
	InventoryPolyHedraManager.InitExternal(MediaDirectory);
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/PHFull.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/PHFull.frag")),
		});
		InventoryShader.Change(code);
		InventoryPolyHedraManager.ShaderFullOther = &InventoryShader; // Others dosent need to be PolyHedraFullShader
	}
#endif
}

// Valgrind is very slow here ?
void ContextNoisePlane::GraphicsCreate()
{
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	PolyHedraManager.GraphicsCreate();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	PolyHedraManager.InitInternal(); // do this in GraphicsCreate ?
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	ControlManager.GraphicsCreate();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	TextManager.GraphicsCreate();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	//PlaneManager.GraphicsCreate();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	ChunkManager.GraphicsCreate();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
#ifndef DISABLE_INVENTORY
	InventoryPolyHedraManager.GraphicsCreate();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
	InventoryShader.Create();
//	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n';
#endif
}
void ContextNoisePlane::GraphicsDelete()
{
	PolyHedraManager.GraphicsDelete();
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	//PlaneManager.GraphicsDelete();
	ChunkManager.GraphicsDelete();
#ifndef DISABLE_INVENTORY
	InventoryPolyHedraManager.GraphicsDelete();
	InventoryShader.Delete();
#endif
}

void ContextNoisePlane::Init()
{
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	Make();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	ChangeMedia();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	GraphicsCreate();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	TextManager.InitFont();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	VoxelPalletMap::All.LoadTextures(ChunkManager);
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	VoxelPalletMap::All.MakePolyHedra();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	VoxelGeometryPallet::Default();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	MakeControls();
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	//ChunkManager.ChangeSize(0, 0);
	//ChunkManager.ChangeSize(2, 1);
	//ChunkManager.ChangeSize(8, 6);
	//ChunkManager.ChangeSize(16, 8);
	ChunkManager.ChangeSize(16, 12);
	//ChunkManager.ChangeSize(32, 16);
	std::cout << "ContextNoisePlane::Init() " << __LINE__ << '\n';
	Multiform_Depth.ChangeData(view.Depth);
	Multiform_FOV.ChangeData(view.FOV);

	AuxThread0Idle = false;
	ChunkManager.AuxThread1.DoIdle = false;
	AuxThread2DoIdle = false;
	AuxThread3DoIdle = false;

	ChunkManager.AuxThread1.Poke();
	ChunkManager.GenerateChunkConditionVar.notify_all();
	ChunkManager.AssambleChunkConditionVar.notify_all();
}
void ContextNoisePlane::Free()
{
	GraphicsDelete();

	AuxThread0Term = true;
	ChunkManager.AuxThread1.Term = true;
	AuxThread2Term = true;
	AuxThread3Term = true;

	ChunkManager.AuxThread1.Poke();
	ChunkManager.GenerateChunkConditionVar.notify_all();
	ChunkManager.AssambleChunkConditionVar.notify_all();

	AuxThread0.join();
	ChunkManager.AuxThread1.Join();
	AuxThread2.join();
	AuxThread3.join();
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

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	sw.Clear(); sw.Start();
	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();
	sw.Stop(); FrameTime_Draw_DrawPolyHedra.NewValue(sw.ElapsedTime());

	//PlaneManager.Draw();

	sw.Clear(); sw.Start();
	ChunkManager.ShaderLayoutU.LightAmbient.Put(LightAmbient);
	ChunkManager.ShaderLayoutU.LightSolar.Put(LightSolar);
	sw.Stop(); FrameTime_Draw_UniformChunk.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	ChunkManager.Draw();
	sw.Stop(); FrameTime_Draw_DrawChunk.NewValue(sw.ElapsedTime());
//	ChunkManager.UpdateChunksArrayDraw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	{
#ifndef DISABLE_INVENTORY
		InventoryPolyHedraManager.MakeCurrent();
#endif
		sw.Clear(); sw.Start();
		ControlManager.UpdateSize(window.Size);
		ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
//		ControlManager.Window.UpdateEntrys();
		ControlManager.Draw();
		PolyHedraManager.MakeCurrent();
		sw.Stop(); FrameTime_Draw_DrawControl.NewValue(sw.ElapsedTime());
	}

	sw.Clear(); sw.Start();
	TextManager.MakeInstances();
	sw.Stop(); FrameTime_Draw_MakeText.NewValue(sw.ElapsedTime());

	TextManager.ShowInstancesTime();

	sw.Clear(); sw.Start();
	TextManager.Draw();
	TextCharCount = TextManager.InstancesArray.Length();
	sw.Stop(); FrameTime_Draw_DrawText.NewValue(sw.ElapsedTime());

#ifndef DISABLE_INVENTORY
	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	InventoryPolyHedraManager.ClearInstances();
	InventoryPolyHedraManager.UpdateInstances();
	InventoryPolyHedraManager.DrawFull();
#endif

	sw_total.Stop(); FrameTime_Draw_DrawTotal.NewValue(sw_total.ElapsedTime());
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
/*static void ShowNameTimeFreqLine(std::stringstream & ss, const char * name, const ValueAverager<float> & time)
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
static void ShowNameTimeLine(std::stringstream & ss, const char * name, const ValueAverager<float> & time)
{
	ss << name << ':';
	ShowTime(ss, time.Min()); ss << ' ';
	ShowTime(ss, time.Average()); ss << ' ';
	ShowTime(ss, time.Max()); ss << '\n';
}



static ValueAverager<float>		DLTAverageTime(64);
static ValueAverager<int>		FPSAverageTime(64);
#ifndef DISABLE_INVENTORY
static ValueAverager<float>		InventoryCursorTime(64);
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
	unsigned long long buffer_data_entrys;
	unsigned long long buffer_data_memory;
	unsigned long long buffer_data_limit;

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
		buffer_data_entrys = 0;
		buffer_data_memory = 0;
		buffer_data_limit = 0;
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
				if (chunk.BufferUData_Want)		{ buffer_data_want[0]++; }
				else							{ buffer_data_want[1]++; }
				if (chunk.BufferUData_Have)		{ buffer_data_have[0]++; }
				else							{ buffer_data_have[1]++; }
			}
			else
			{
				// none should be if buffer if Data is empty ?
				buffer_data_none++;
			}
		}

		buffer_data_entrys = manager.BufferU.Entrys.Count();
		buffer_data_memory = 0;
		for (unsigned int i = 0; i < buffer_data_entrys; i++)
		{
			buffer_data_memory += manager.BufferU.Entrys[i] -> Length;
		}
		buffer_data_limit = manager.BufferU.Size;
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

		ss << "DataU Entrys:" << buffer_data_entrys << '\n';
		ss << "DataU Memory: ";
		ss << Memory1000ToString(buffer_data_memory * sizeof(VoxelGraphics::MainFaceU));
		ss << " / ";
		ss << Memory1000ToString(buffer_data_limit * sizeof(VoxelGraphics::MainFaceU));
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
		ss << "Min: "; ShowTimeFreq(ss, DLTAverageTime.Min(), FPSAverageTime.Max()); ss << '\n';
		ss << "Avg: "; ShowTimeFreq(ss, DLTAverageTime.Average(), FPSAverageTime.Average()); ss << '\n';
		ss << "Max: "; ShowTimeFreq(ss, DLTAverageTime.Max(), FPSAverageTime.Min()); ss << '\n';
		ss << '\n';
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
		ShowNameTimeLine(ss, "ChunksTime      ", FrameTime_ViewUpdate_ChunksTime);
		ss << "{\n";
		ss << ChunkManager::TimeGraphicsCreate << '\n';
		ss << ChunkManager::TimeGraphicsDelete << '\n';
		ss << "}\n";
		ShowNameTimeLine(ss, "RayTime         ", FrameTime_ViewUpdate_RayTime);
		ss << "}\n";*/
		ShowNameTimeLine(ss, "ThreadUpdate    ", FrameTime_ThreadUpdate);
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
		ss << "AuxThread2 IsIdle: " << AuxThread2IsIdle << '\n';
		ss << TimeGenerateFind << '\n';
		ss << TimeGenerate << '\n';
		ss << '\n';
		ss << "AuxThread3 IsIdle: " << AuxThread3IsIdle << '\n';
		ss << TimeAssambleFind << '\n';
		ss << TimeAssamble << '\n';
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

			ss << "BufferUData_Want: " << (*chunk).BufferUData_Want << '\n';
			ss << "BufferUData_Have: " << (*chunk).BufferUData_Have << '\n';

			//ss << "BufferU: ";
			//ss << Memory1000ToString(chunk.BufferU.Main.Count * sizeof(VoxelGraphics::MainDataU));
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

		ss << '\n';
	}
	sw.Stop(); TextTime_ChunkRange.NewValue(sw.ElapsedTime());

	// Queues
	{
		ss << "Queues:\n";

		ss << "BufferData Want " << ChunkManager.AuxThread1.QueueCount() << '\n';

		ChunkManager.BufferDataHaveQueueMutex.lock();
		ss << "BufferData Have " << ChunkManager.BufferDataHaveQueue.Count() << '\n';
		ChunkManager.BufferDataHaveQueueMutex.unlock();

		ss << "Generate Candidates " << ChunkManager.GenerateChunkFindCandidateCount << '\n';
		ss << "Assamble Candidates " << ChunkManager.AssambleChunkFindCandidateCount << '\n';

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
	sw_total.Stop(); FrameTime_Text_Instance.NewValue(sw_total.ElapsedTime());
}
#ifndef DISABLE_INVENTORY
void ContextNoisePlane::InventoryCursor(FrameTime frame_time)
{
	StopWatch sw;
	sw.Start();

	static float time_sum = 0.0f;
	InventoryPolyHedraManager.MakeCurrent();

	VectorF2	PixelSize(40, 40); // hardcoded in Shader
	VectorF2	size = window.Size.Buffer.SizeFullToNormalRel(PixelSize);

	VectorF2	PixelPos;
	VectorF2	pos;

	if (HotBar.Items[VectorU2(0, 0)] != nullptr)
	{
		ItemVoxel * item = (ItemVoxel*)HotBar.Items[VectorU2(0, 0)];
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

	sw.Stop();
	InventoryCursorTime.NewValue(sw.ElapsedTime());
}
#endif
// !!!! F12 is used by gdb to cause a BreakPoint. dont use it as input
void ContextNoisePlane::FrameInput()
{
	//StopWatch sw;
	//sw.Start();

	if (window.KeyBoardManager[Keys::Escape].State == State::Press)
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
	if (window.KeyBoardManager[Keys::E].State == State::Press)
	{
		if (!PauseMenu.IsVisible() && !OptionsMenu.IsVisible())
		{
#ifndef DISABLE_INVENTORY
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
#endif
		}
	}

#ifndef DISABLE_VIEW_RAY
	if (window.KeyBoardManager[Keys::D1].State == State::Press) { Toggle(ViewRaySync); }
	//if (window.KeyBoardManager[Keys::D2].State == State::Press) { Toggle(ChunkManager.ViewRayPolyHedra, ViewRayPolyHedra); }
	//if (window.KeyBoardManager[Keys::D3].State == State::Press) { Toggle(ChunkManager.VoxelBoxPolyHedra, VoxelCube); }
#endif

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

#ifndef DISABLE_VIEW_TANGIBLE
	if (window.KeyBoardManager[Keys::F2].State == State::Press) { Toggle(ViewTangible); }
#endif
	if (window.KeyBoardManager[Keys::F3].State == State::Press)
	{
#ifndef DISABLE_VIEW_TANGIBLE
		if (ViewDistance == 0.0f)
		{ ViewDistance = 2.0f; }
		else
		{ ViewDistance = 0.0f; }
#endif
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

	/*if (window.KeyBoardManager[Keys::P].State == State::Press)
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

	LightSolar.Dir = EulerAngle3D::Degrees(0, 0, 90 * frame_time.Delta).forward(LightSolar.Dir);

	if (window.KeyBoardManager[Keys::Delete].State == State::Press) { CenterIndexLoop_Clear(); }
	if (window.KeyBoardManager[Keys::Insert].State == State::Press) { CenterIndexLoop_Loop(); }
	CenterIndexLoop_Show(VoxelCube);

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw;

	sw.Clear(); sw.Start();
	FrameInput();
	sw.Stop(); FrameTime_Input.NewValue(sw.ElapsedTime());

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

	sw.Clear(); sw.Start();
	DrawThreadUpdate();
	sw.Stop(); FrameTime_ThreadUpdate.NewValue(sw.ElapsedTime());

	/*{
		float pixel_rad = 1;
		UI::Control::Object obj;
		obj.Create();
		obj.Box().Min = window.Size.Buffer.Half - VectorF2(pixel_rad, pixel_rad);
		obj.Box().Max = window.Size.Buffer.Half + VectorF2(pixel_rad, pixel_rad);
		obj.Color() = ColorF4(1, 0, 1);
	}*/

	sw.Clear(); sw.Start();
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
	sw.Stop(); FrameTime_ChunkBoxes.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	if (DebugMenu.ChunkHere.Check.IsChecked())
	{
		ChunkVoxelIndex idx(view.Trans.Position.roundF());
		PolyHedraObject chunk_box(VoxelChunkCube);
		chunk_box.Trans().Position = idx.Chunk * CHUNK_VALUES_PER_SIDE;
		chunk_box.ShowWire();
	}
	sw.Stop(); FrameTime_ChunkHereBox.NewValue(sw.ElapsedTime());

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
void ContextNoisePlane::MouseScroll(ScrollArgs args) { (void)args; }
void ContextNoisePlane::MouseClick(ClickArgs args)
{
#ifndef DISABLE_INVENTORY
	InventoryPolyHedraManager.MakeCurrent();
#endif
	ControlManager.RelayClick(args);
#ifndef DISABLE_INVENTORY
	PolyHedraManager.MakeCurrent();
#endif
}
void ContextNoisePlane::MouseDrag(DragArgs args) { ControlManager.RelayCursorDrag(args); }
void ContextNoisePlane::KeyBoardKey(KeyArgs args) { (void)args; }



ContextBase * newContextNoisePlane()
{
	return new ContextNoisePlane();
}
