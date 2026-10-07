#include "ContextNoisePlane.hpp"
#include "new.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Parser.hpp"

// New PolyHedra
#include "NewPolyHedra/DataType/Basic3D/Layout.hpp"
#include "NewPolyHedra/DataType/Basic3D/Object.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/Layout.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/Object.hpp"

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Generics/Container/Array.hpp"

// Axis
#include "Axis/3D/Enums.hpp"
#include "Axis/3D/Show.hpp"
#include "Axis/3D/Funcs.hpp"
#include "Axis/2D/Enums.hpp"

// Threading
#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
//#include "Threading/ObjectTypeAccessSharedGuard.hpp"
#include "Threading/ObjectTypeAssignUniqueGuard.hpp"
//#include "Threading/ObjectTypeAssignSharedGuard.hpp"

// Voxel
#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Map.hpp"
#include "3D/Voxel/Pallet/Parser.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"
//#include "3D/Voxel/Pallet/Geometry/U.hpp"
//#include "3D/Voxel/Pallet/Geometry/F.hpp"
#include "3D/Voxel/Pallet/Geometry/Map.hpp"
#include "3D/Voxel/Pallet/Geometry/Parser.hpp"
#include "3D/Structure.hpp"
#include "3D/StructureMap.hpp"
#include "3D/StructureParser.hpp"

// Math
#include <math.h>

// Debug
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Debug.hpp"
#include "ValueType/_Show.hpp"
#include "ValueType/_Include.hpp"

// Telemetry
#include "Telemetry/StopWatch.hpp"

// ValueType
#include "ValueType/_Include.hpp"



__attribute__((unused)) static PolyHedra * MakePolyHedraBoxEdges(BoxF3 box)
{
	PolyHedra * polyhedra = new PolyHedra();

	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Min.Y, box.Min.Z))); // 000
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Min.Y, box.Min.Z))); // 001
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Max.Y, box.Min.Z))); // 010
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Max.Y, box.Min.Z))); // 011
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Min.Y, box.Max.Z))); // 100
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Min.Y, box.Max.Z))); // 101
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Max.Y, box.Max.Z))); // 110
	polyhedra -> Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Max.Y, box.Max.Z))); // 111

	polyhedra -> Edges.Insert(PolyHedra::Edge(0b000, 0b001));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b010, 0b011));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b100, 0b101));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b110, 0b111));

	polyhedra -> Edges.Insert(PolyHedra::Edge(0b000, 0b010));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b001, 0b011));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b100, 0b110));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b101, 0b111));

	polyhedra -> Edges.Insert(PolyHedra::Edge(0b000, 0b100));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b001, 0b101));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b010, 0b110));
	polyhedra -> Edges.Insert(PolyHedra::Edge(0b011, 0b111));

	return polyhedra;
}

__attribute__((unused)) static void PolyHedra_Display_Normalized(NewPolyHedra::Pallet & pallet, const BoxF3 & box)
{
	TransScaleColor3D::Object obj(&pallet);
	obj.Data().Trans.Position = box.Center();
	obj.Data().Scale = box.Size() * 0.5f;
	obj.HideFull();
	obj.ShowWire();
}
__attribute__((unused)) static void PolyHedra_Display_Normalized(NewPolyHedra::Pallet & pallet, const BoxEntity3D & box_entity)
{
	PolyHedra_Display_Normalized(pallet, box_entity.Box + box_entity.Pos);
}
__attribute__((unused)) static void PolyHedra_Display_Normalized(NewPolyHedra::Pallet & pallet, const Container::Array<BoxF3> & boxes)
{
	for (unsigned int i = 0; i < boxes.Length(); i++)
	{
		PolyHedra_Display_Normalized(pallet, boxes[i]);
		/*NewPolyHedra::Basic3D::Object voxel_obj(pallet);
		voxel_obj.Data().Trans.Position = boxes[i].Min;
		voxel_obj.HideFull();
		voxel_obj.ShowWire();*/
	}
}

__attribute__((unused)) static void Toggle(bool & value)
{
	value = !value;
}
__attribute__((unused)) static void Toggle(::PolyHedra * & polyhedra, ::PolyHedra * other)
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

/*__attribute__((unused)) static VectorI3 Axis_Ranks(const VectorF3 & vec)
{
	VectorI3 ranks;

	const float *	value_ptr = (const float*)&vec;
	int *			ranks_ptr = (int*)&ranks;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (value_ptr[i] != value_ptr[i])
		{
			ranks_ptr[i] = -1;
		}
		else
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (i != j)
				{
					if (value_ptr[i] > value_ptr[j])
					{
						ranks_ptr[i]++;
					}
				}
			}
		}
	}

	return ranks;
}*/
/*__attribute__((unused)) static void RankAxis(const VectorF3 & vec, Axis3D::Abs & axis0, Axis3D::Abs & axis1, Axis3D::Abs & axis2)
{
	axis0 = Axis3D::Abs::None;
	if ((vec.X < vec.Y) && (vec.X < vec.Z)) { axis0 = Axis3D::Abs::X; }
	if ((vec.Y < vec.Z) && (vec.Y < vec.X)) { axis0 = Axis3D::Abs::Y; }
	if ((vec.Z < vec.X) && (vec.Z < vec.Y)) { axis0 = Axis3D::Abs::Z; }

	axis1 = Axis3D::Abs::None;
	if (((vec.X > vec.Y) && (vec.X < vec.Z)) || ((vec.X < vec.Y) && (vec.X > vec.Z))) { axis1 = Axis3D::Abs::X; }
	if (((vec.Y > vec.Z) && (vec.Y < vec.X)) || ((vec.Y < vec.Z) && (vec.Y > vec.X))) { axis1 = Axis3D::Abs::Y; }
	if (((vec.Z > vec.X) && (vec.Z < vec.Y)) || ((vec.Z < vec.X) && (vec.Z > vec.Y))) { axis1 = Axis3D::Abs::Z; }

	axis2 = Axis3D::Abs::None;
	if ((vec.X > vec.Y) && (vec.X > vec.Z)) { axis0 = Axis3D::Abs::X; }
	if ((vec.Y > vec.Z) && (vec.Y > vec.X)) { axis0 = Axis3D::Abs::Y; }
	if ((vec.Z > vec.X) && (vec.Z > vec.Y)) { axis0 = Axis3D::Abs::Z; }

	//axis0 = Axis3D::Abs::None;
	//axis1 = Axis3D::Abs::None;
	//axis2 = Axis3D::Abs::None;
	//if ((vec.X < vec.Y) && (vec.X < vec.Z) && (vec.Y < vec.Z)) { axis0 = Axis3D::Abs::X; axis1 = Axis3D::Abs::Y; axis2 = Axis3D::Abs::Z; } // X Y Z
	//if ((vec.X < vec.Y) && (vec.X < vec.Z) && (vec.Y < vec.Z)) { axis0 = Axis3D::Abs::X; axis1 = Axis3D::Abs::Y; axis2 = Axis3D::Abs::Z; } // X Z Y
	//if ((vec.X < vec.Y) && (vec.X < vec.Z) && (vec.Y < vec.Z)) { axis0 = Axis3D::Abs::X; axis1 = Axis3D::Abs::Y; axis2 = Axis3D::Abs::Z; } // Y Z X
	//if ((vec.X < vec.Y) && (vec.X < vec.Z) && (vec.Y < vec.Z)) { axis0 = Axis3D::Abs::X; axis1 = Axis3D::Abs::Y; axis2 = Axis3D::Abs::Z; } // Y X Z
	//if ((vec.X < vec.Y) && (vec.X < vec.Z) && (vec.Y < vec.Z)) { axis0 = Axis3D::Abs::X; axis1 = Axis3D::Abs::Y; axis2 = Axis3D::Abs::Z; } // Z X Y
	//if ((vec.X < vec.Y) && (vec.X < vec.Z) && (vec.Y < vec.Z)) { axis0 = Axis3D::Abs::X; axis1 = Axis3D::Abs::Y; axis2 = Axis3D::Abs::Z; } // Z Y X
}*/
/*__attribute__((unused)) static void RankAxis(const VectorF3 & vec, Axis3D::Rel & axis0, Axis3D::Rel & axis1, Axis3D::Rel & axis2)
{
	Axis3D::Abs axis0_abs;
	Axis3D::Abs axis1_abs;
	Axis3D::Abs axis2_abs;

	RankAxis(vec, axis0_abs, axis1_abs, axis2_abs);

	axis0 = Axis3D::Rel::None;
	if (axis0_abs == Axis3D::Abs::X) { if (vec.X > 0) { axis0 = Axis3D::Rel::NextX; } else { axis0 = Axis3D::Rel::PrevX; } }
	if (axis0_abs == Axis3D::Abs::Y) { if (vec.Y > 0) { axis0 = Axis3D::Rel::NextY; } else { axis0 = Axis3D::Rel::PrevY; } }
	if (axis0_abs == Axis3D::Abs::Z) { if (vec.Z > 0) { axis0 = Axis3D::Rel::NextZ; } else { axis0 = Axis3D::Rel::PrevZ; } }

	axis1 = Axis3D::Rel::None;
	if (axis1_abs == Axis3D::Abs::X) { if (vec.X > 0) { axis1 = Axis3D::Rel::NextX; } else { axis1 = Axis3D::Rel::PrevX; } }
	if (axis1_abs == Axis3D::Abs::Y) { if (vec.Y > 0) { axis1 = Axis3D::Rel::NextY; } else { axis1 = Axis3D::Rel::PrevY; } }
	if (axis1_abs == Axis3D::Abs::Z) { if (vec.Z > 0) { axis1 = Axis3D::Rel::NextZ; } else { axis1 = Axis3D::Rel::PrevZ; } }

	axis2 = Axis3D::Rel::None;
	if (axis2_abs == Axis3D::Abs::X) { if (vec.X > 0) { axis2 = Axis3D::Rel::NextX; } else { axis2 = Axis3D::Rel::PrevX; } }
	if (axis2_abs == Axis3D::Abs::Y) { if (vec.Y > 0) { axis2 = Axis3D::Rel::NextY; } else { axis2 = Axis3D::Rel::PrevY; } }
	if (axis2_abs == Axis3D::Abs::Z) { if (vec.Z > 0) { axis2 = Axis3D::Rel::NextZ; } else { axis2 = Axis3D::Rel::PrevZ; } }
}*/
/*__attribute__((unused)) static void RankAxis(const VectorF3 & vec, Axis3D::Rel & axis0, Axis3D::Rel & axis1, Axis3D::Rel & axis2)
{
	VectorI3 ranks = Axis_Ranks(vec.abs());

	if      (ranks.X == 0) { if (vec.X > 0) { axis0 = Axis3D::Rel::NextX; } else { axis0 = Axis3D::Rel::PrevX; } }
	else if (ranks.Y == 0) { if (vec.Y > 0) { axis0 = Axis3D::Rel::NextY; } else { axis0 = Axis3D::Rel::PrevY; } }
	else if (ranks.Z == 0) { if (vec.Z > 0) { axis0 = Axis3D::Rel::NextZ; } else { axis0 = Axis3D::Rel::PrevZ; } }
	else { axis0 = Axis3D::Rel::None; }

	if      (ranks.X == 1) { if (vec.X > 0) { axis1 = Axis3D::Rel::NextX; } else { axis1 = Axis3D::Rel::PrevX; } }
	else if (ranks.Y == 1) { if (vec.Y > 0) { axis1 = Axis3D::Rel::NextY; } else { axis1 = Axis3D::Rel::PrevY; } }
	else if (ranks.Z == 1) { if (vec.Z > 0) { axis1 = Axis3D::Rel::NextZ; } else { axis1 = Axis3D::Rel::PrevZ; } }
	else { axis1 = Axis3D::Rel::None; }

	if      (ranks.X == 2) { if (vec.X > 0) { axis2 = Axis3D::Rel::NextX; } else { axis2 = Axis3D::Rel::PrevX; } }
	else if (ranks.Y == 2) { if (vec.Y > 0) { axis2 = Axis3D::Rel::NextY; } else { axis2 = Axis3D::Rel::PrevY; } }
	else if (ranks.Z == 2) { if (vec.Z > 0) { axis2 = Axis3D::Rel::NextZ; } else { axis2 = Axis3D::Rel::PrevZ; } }
	else { axis2 = Axis3D::Rel::None; }

	// what if same ranks ?
}*/
__attribute__((unused)) static void RankAxis(const VectorF3 & vec, Axis3D::Rel & axis0, Axis3D::Rel & axis1, Axis3D::Rel & axis2)
{
	axis0 = Axis3D::Rel::None;
	axis1 = Axis3D::Rel::None;
	axis2 = Axis3D::Rel::None;

	Axis3D::Rel axisX = (vec.X > 0) ? Axis3D::Rel::NextX : Axis3D::Rel::PrevX;
	Axis3D::Rel axisY = (vec.Y > 0) ? Axis3D::Rel::NextY : Axis3D::Rel::PrevY;
	Axis3D::Rel axisZ = (vec.Z > 0) ? Axis3D::Rel::NextZ : Axis3D::Rel::PrevZ;

	bool XvsY = (vec.X < vec.Y);
	bool YvsX = (vec.X > vec.Y);

	bool YvsZ = (vec.Y < vec.Z);
	bool ZvsY = (vec.Y > vec.Z);

	bool ZvsX = (vec.Z < vec.X);
	bool XvsZ = (vec.Z > vec.X);

	if (XvsY && XvsZ) { axis0 = axisX; }
	if (YvsZ && YvsX) { axis0 = axisY; }
	if (ZvsX && ZvsY) { axis0 = axisZ; }

	if ((YvsX && XvsZ) || (XvsY && ZvsX)) { axis1 = axisX; }
	if ((ZvsY && YvsX) || (YvsZ && XvsY)) { axis1 = axisY; }
	if ((XvsZ && ZvsY) || (ZvsX && YvsZ)) { axis1 = axisZ; }

	if (YvsX && ZvsX) { axis2 = axisX; }
	if (ZvsY && XvsY) { axis2 = axisY; }
	if (XvsZ && YvsZ) { axis2 = axisZ; }
}

__attribute__((unused)) static BoxF3 BoxEntity_RangeF(const BoxEntity3D & box_entity, const FrameTime & frame_time)
{
	BoxF3 range = box_entity.Box + box_entity.Pos;
	range.Consider(box_entity.Box.Min + box_entity.Pos + (box_entity.Vel * frame_time.Delta));
	range.Consider(box_entity.Box.Max + box_entity.Pos + (box_entity.Vel * frame_time.Delta));
	return range;
}
__attribute__((unused)) static BoxI3 BoxEntity_RangeI(const BoxEntity3D & box_entity, const FrameTime & frame_time)
{
	BoxF3 range = BoxEntity_RangeF(box_entity, frame_time);
	range = range - VectorF3(0.5f);
	return BoxI3(range.Min.round().ToI(), range.Max.round().ToI());
}

__attribute__((unused)) static Container::Array<BoxF3> Voxels_Boxes_Collect(ChunkContainer & container, const BoxI3 & range)
{
	Container::Binary<BoxF3> boxes;

	LoopI3 loop(range, Bool3(false), Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		ChunkVoxelIndex idx(i);
		AccessLockedChunk chunk = container.FindAbsoluteAccess(idx.Chunk);
		if (!chunk.Is()) { continue; }
		if (!(*chunk).IsDone()) { continue; }
		if ((*chunk).IsEmpty()) { continue; }
		const Voxel & voxel = (*chunk)[idx.Voxel];
		if (voxel.IsEmpty()) { continue; }
		boxes.Insert(
			BoxF3(
				(i + VectorI3(0, 0, 0)).ToF(),
				(i + VectorI3(1, 1, 1)).ToF()
			)
		);
	}

	return boxes.ToArray();
}

__attribute__((unused)) static void VectorComponents(const VectorF3 & vec, const VectorF3 & other, VectorF3 & parallel, VectorF3 & perpendicular)
{
	float dot = vec.dot(other);
	parallel = (vec / vec.length2()) * dot;
	perpendicular = other - parallel;
}



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
		// Basic3D
		{
			ObjectManagerBasic.ShaderFull.Change({
				MediaDirectory.File("Shaders/PolyHedra/Default.vert"),
				MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformLight3D();
				ObjectManagerBasic.ShaderFull.AssignLayout(layout);
				LayoutMultiform.Find(layout);
			}
			{
				NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(7);
				ObjectManagerBasic.BufferFullLayout = layout;
			}
			ObjectManagerBasic.ShaderWire.Change({
				MediaDirectory.File("Shaders/Basic3D/Wire.vert"),
				MediaDirectory.File("Shaders/Basic3D/Wire.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformView3D();
				ObjectManagerBasic.ShaderWire.AssignLayout(layout);
				LayoutMultiform.Find(layout);
			}
			{
				NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(-1);
				ObjectManagerBasic.BufferWireLayout = layout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerBasic);
		}
		// TransScaleColor3D
		{
			ObjectManagerTSC.ShaderFull.Change({
				MediaDirectory.File("Shaders/PolyHedra/UserInterface.vert"),
				MediaDirectory.File("Shaders/PolyHedra/TexturedNoLight.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformView3D();
				ObjectManagerTSC.ShaderFull.AssignLayout(layout);
				LayoutMultiform.Find(layout);
			}
			{
				TransScaleColor3D::BufferLayout * layout = new TransScaleColor3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(7);
				layout -> Scale.Change(11);
				layout -> Color.Change(12);
				ObjectManagerTSC.BufferFullLayout = layout;
			}
			ObjectManagerTSC.ShaderWire.Change({
				MediaDirectory.File("Shaders/PolyHedra/TSC/Wire.vert"),
				MediaDirectory.File("Shaders/PolyHedra/Fixed.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformView3D();
				ObjectManagerTSC.ShaderWire.AssignLayout(layout);
				LayoutMultiform.Find(layout);
			}
			{
				TransScaleColor3D::BufferLayout * layout = new TransScaleColor3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(-1);
				layout -> Scale.Change(11);
				layout -> Color.Change(-1);
				ObjectManagerTSC.BufferWireLayout = layout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerTSC);
		}
		// UI
		{
			ObjectManagerUI.ShaderFull.Change({
				MediaDirectory.File("Shaders/UI/PHFull.vert"),
				MediaDirectory.File("Shaders/UI/PHFull.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformDisplay();
				ObjectManagerUI.ShaderFull.AssignLayout(layout);
				LayoutMultiform.Find(layout);
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
				Uniform::Layout * layout = new LayoutUniformDisplay();
				ObjectManagerUI.ShaderWire.AssignLayout(layout);
				LayoutMultiform.Find(layout);
			}
			{
				NewPolyHedra::UserInterface::BufferLayout * layout = new NewPolyHedra::UserInterface::BufferLayout();
				ObjectManagerUI.BufferWireLayout = layout;
			}
			PolyHedraManager.ObjectManagers.Insert(&ObjectManagerUI);
		}
	}
}

void ContextNoisePlane::MakeControls()
{
	std::cerr << "MakeControls()\n";
	// Pause
	{
		MenuPause.Show();
		UIManager.Window.ChildInsert(MenuPause);
	}
	// Options
	{
		//MenuOptions.FPS.SetValueX(window.FrameTime.WantedFramesPerSecond);
		MenuOptions.FPS.SetValueX(64);
		MenuOptions.FOV.SetValueX(View.FOV.ToDegrees());

		MenuOptions.Depth.SetValueX(View.Depth.Factors.GetFar());
		MenuOptions.DepthRange.SetValueX(View.Depth.Range.GetMin());

		// Remove range should never be less then Insert
		// make RemoveRange = InsertRange * 2 ?
		// make RemoveRange = InsertRange + n ?

		MenuOptions.Hide();
		UIManager.Window.ChildInsert(MenuOptions);
	}
	// Debug
	{
		MenuDebug.FPS.Check.Check(true);
		MenuDebug.View.Check.Check(true);
		MenuDebug.VoxelChunkMemory.Check.Check(true);

		MenuDebug.Hide();
		UIManager.Window.ChildInsert(MenuDebug);
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
		UIManager.Window.ChildInsert(InventoryUI);
	}
	// HotBar
	{
		HotBarUI.IsResizable = false;
		HotBarUI.IsMovable = false;
		HotBarUI.Anchor.Y.AnchorMax(0);
		HotBarUI.Change(&HotBar);
		//HotBarUI.Hide();
		UIManager.Window.ChildInsert(HotBarUI);
	}

//	UIManager.Window.UpdateDepth();
}



ContextNoisePlane::~ContextNoisePlane()
{ }
ContextNoisePlane::ContextNoisePlane()
	: ContextBase()
	, LayoutMultiform()
	, PolyHedraManager()
	, PalletManager()
	, ObjectManagerBasic()
	, ObjectManagerTSC()
	, ObjectManagerUI()
	, AuxThreadCollection(*this)
	, UIManager()
//	, PlaneManager()
	, ChunkManager(AuxThreadCollection)
	, MenuMain()
	, MenuPause(*this)
	, MenuOptions(*this)
	, MenuDebug(*this)
	, Inventory(VectorU2(10, 5))
	, InventoryUI()
	, HotBar(VectorU2(10, 1))
	, HotBarUI()
	, VoxelClear(ChunkManager.Container)
	, LightBuffer(GL::BufferDataUsage::StreamDraw)
{
	MediaDirectory = DirectoryInfo("../../media/");
	IdleLoopThread::ThreadName = "DrawThread";

	Box_PolyHedra = PolyHedraGenerate::RegularHexaHedron();
	Box_Pallet = PalletManager.FindMakePallet(Box_PolyHedra);

	PhysicsContext_Gravity.Acceleration = 0.5f;

	Container::Array<Uniform::Layout*> layouts({
		&UIManager.ControlManager.ShaderLayout,
		&UIManager.TextManager.ShaderLayout,
//		&PlaneManager.Shader,
		&ChunkManager.Graphics.ShaderLayoutU,
		&ChunkManager.Graphics.ShaderLayoutF,
	});
	LayoutMultiform.Find(layouts);
}



void ContextNoisePlane::ViewEntityUpdate_Intangible(Trans3D change, FrameTime frame_time)
{
	float speed = 0.0f;
	if (window[Keys::LeftControl] == State::Down)
	{
		speed = ViewMove_SpeedFast;
	}
	else
	{
		speed = ViewMove_SpeedSlow;
	}
	change.Position *= speed;

	View.Trans.Position += change.Position * frame_time.Delta;
	View.Trans.Rotation += change.Rotation * frame_time.Delta;
	View.Trans.Rotation.X1.clampPI();

	ViewEntity.Pos = View.Trans.Position;
	ViewEntity.Vel = change.Position;
}
void ContextNoisePlane::ViewEntityUpdate_Physics(VectorF3 change, FrameTime frame_time)
{
	(void)frame_time;

	float accel_factor = 0.0f;
	if (window[Keys::LeftControl] == State::Down)
	{
		accel_factor = ViewMove_AccelFast;
	}
	else
	{
		accel_factor = ViewMove_AccelSlow;
	}
	float decel_factor = ViewMove_Decel;

	VectorF2 change_hori(change.X, change.Z);
	float change_vert = change.Y;

	VectorF3 jump;
	if (ViewEntity_CollisionSide.PrevY)
	{
		if (change_vert > 0.0f)
		{
			//jump.Y = 16.0f;
			jump.Y = 10.0f;
		}
	}

	VectorF3 accel = VectorF3(change_hori.X, 0.0f, change_hori.Y);
	VectorF3 decel = VectorF3(ViewEntity.Vel.X, 0.0f, ViewEntity.Vel.Z);

	accel *= accel_factor;
	decel *= decel_factor;

	ViewEntity.Vel = ViewEntity.Vel + accel - decel + jump + PhysicsContext_Gravity.Vector();
}
/*void ContextNoisePlane::ViewEntityUpdate_Physics(VectorF3 change)
{
	float limit = 0.0f;
	if (window[Keys::LeftControl] == State::Down)
	{
		limit = ViewEntity_MoveLimitFast;
	}
	else
	{
		limit = ViewEntity_MoveLimitSlow;
	}
	ViewEntity.Vel = change * limit;
}*/
/*void ContextNoisePlane::ViewEntityUpdate_Physics(VectorF3 change)
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

		// accel and decel
		//	accel:
		//		should be change
		//		so it moves in the direction that is wanted
		//	decel:
		//		should slow you down
		//		when turing
		//		it currently slows you down based on how fast you turn
		//		so if you turn 90 degreees, your speed goes to 0
		//		this feels terrible
		//	the current speed should be redirected towards change
		//	just add change to speed and limit ?
		//	this feels floaty
		//

		//VectorF3 accel;
		//VectorF3 decel;

		//{
		//	float flat_len2 = flat.length2();
		//	if (flat_len2 != 0.0f)
		//	{
		//		float len2 = change.length2();
		//		if (len2 != 0.0f)
		//		{
		//			float dot = flat.dot(change);
		//			accel = change;
		//			decel = flat - (change / len2) * dot;
		//		}
		//		else
		//		{
		//			decel = flat;
		//		}
		//	}
		//	else
		//	{
		//		accel = change;
		//	}
		//}

		//{
		//	float accel_speed = ViewEntity_MoveChange;
		//	float decel_speed = ViewEntity_MoveChange * 8.0f;
		//	float flat_speed = flat.length();
		//	{
		//		float diff = limit - flat_speed;
		//		if (diff < 0.0f)
		//		{
		//			diff = 0.0f;
		//		}
		//		if (diff > accel_speed)
		//		{
		//			diff = accel_speed;
		//		}
		//		accel = accel.normalize() * diff;
		//	}
		//	{
		//		float diff = flat_speed;
		//		if (diff < 0.0f)
		//		{
		//			diff = 0.0f;
		//		}
		//		if (diff > decel_speed)
		//		{
		//			diff = decel_speed;
		//		}
		//		decel = decel.normalize() * diff;
		//	}
		//	// this feels terrible
		//}

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
}*/
void ContextNoisePlane::ViewEntityUpdate_Colliding(FrameTime frame_time)
{
	BoxI3 range = BoxEntity_RangeI(ViewEntity, frame_time);
	Container::Array<BoxF3> boxes = Voxels_Boxes_Collect(ChunkManager.Container, range);
	PolyHedra_Display_Normalized(*Box_Pallet, boxes);
	PolyHedra_Display_Normalized(*Box_Pallet, ViewEntity);
	ViewEntity_CollisionSide = ViewEntity.Collide(boxes, frame_time.Delta);
	PolyHedra_Display_Normalized(*Box_Pallet, ViewEntity);
}
void ContextNoisePlane::ViewEntityUpdate_Done()
{
	if (View_Distance == 0.0f)
	{
		LayoutMultiform.View.ChangeData(Matrix4x4::TransformReverse(View.Trans));
	}
	else
	{
		LayoutMultiform.View.ChangeData(Matrix4x4::TransformReverse(
			Trans3D(View.Trans.Position - View.Trans.Rotation.forward(VectorF3(0, 0, View_Distance)), View.Trans.Rotation)
		));
	}
}
void ContextNoisePlane::ViewEntityUpdate(Trans3D change, FrameTime frame_time)
{
	if (View_IsTangible)
	{
		ViewEntityUpdate_Physics(change.Position, frame_time);
		View.Trans.Rotation += change.Rotation * frame_time.Delta;
		View.Trans.Rotation.X1.clampPI();
		ViewEntityUpdate_Colliding(frame_time);
		View.Trans.Position = ViewEntity.Pos;
	}
	else
	{
		ViewEntityUpdate_Intangible(change, frame_time);
	}
	ViewEntityUpdate_Done();
}

void ContextNoisePlane::ViewRayUpdate_Sync()
{
	ViewRay.Pos = View.Trans.Position;
	ViewRay.Dir = View.Trans.Rotation.forward(VectorF3(0, 0, 1));
	RankAxis(ViewRay.Dir, ViewRay_Axis0, ViewRay_Axis1, ViewRay_Axis2);
}
void ContextNoisePlane::ViewRayUpdate_Hit()
{
	ViewHit = ChunkManager.Container.HitVoxel(ViewRay);
	if (ViewHit.Valid())
	{
		ViewHit_Axis0 = ViewHit.Side;
		Axis3D::Abs axis = Axis3D::RelToAbs(ViewHit_Axis0);
		if      (axis == Axis3D::Abs::None) { ViewHit_Axis1 = Axis3D::Rel::None; }
		else if (axis != Axis3D::RelToAbs(ViewRay_Axis2)) { ViewHit_Axis1 = ViewRay_Axis2; }
		else if (axis != Axis3D::RelToAbs(ViewRay_Axis1)) { ViewHit_Axis1 = ViewRay_Axis1; }
		else if (axis != Axis3D::RelToAbs(ViewRay_Axis0)) { ViewHit_Axis1 = ViewRay_Axis0; }
		else { ViewHit_Axis1 = Axis3D::Rel::None; }
	}
}
void ContextNoisePlane::ViewRayUpdate_HitDo()
{
	if (MenuPause.IsInteractible() || MenuOptions.IsInteractible() || InventoryUI.IsInteractible()) { return; }

	const ItemBase * item = HotBar.Items[VectorU2(0, 0)];
	const ItemTool * item_tool = dynamic_cast<const ItemTool *>(item);
	const ItemVoxel * item_voxel = dynamic_cast<const ItemVoxel *>(item);

	VoxelClear.ChangeTool(item_tool);

	if (ViewHit.Valid())
	{
		if (window.MouseManager[MouseButtons::MouseL] == State::Down)
		{
			VoxelClear.Continue(ViewHit.Index);
		}
		else
		{
			VoxelClear.Change(ViewHit.Index);
		}

		if (window.MouseManager[MouseButtons::MouseR] == State::Press)
		{
			// Side: make part of VoxelHit ?
			// determine place_axis_1 based on where on the face was clicked ?
			// top of face orients to point to top and so on

			VectorI3 hit_idx = ViewHit.Index;
			if (ViewHit_Axis0 == Axis3D::Rel::NextX) { hit_idx.X += 1; }
			if (ViewHit_Axis0 == Axis3D::Rel::NextY) { hit_idx.Y += 1; }
			if (ViewHit_Axis0 == Axis3D::Rel::NextZ) { hit_idx.Z += 1; }
			if (ViewHit_Axis0 == Axis3D::Rel::PrevX) { hit_idx.X -= 1; }
			if (ViewHit_Axis0 == Axis3D::Rel::PrevY) { hit_idx.Y -= 1; }
			if (ViewHit_Axis0 == Axis3D::Rel::PrevZ) { hit_idx.Z -= 1; }

			if (item_voxel != nullptr && item_voxel -> VoxelPallet != nullptr)
			{
				ChunkVoxelIndex idx(hit_idx);
				AssignLockedChunk chunk = ChunkManager.Container.FindAbsoluteAccess(idx.Chunk).ToAssign();
				if (chunk.Is())
				{
					Voxel voxel = item_voxel -> VoxelPallet -> ToVoxel(ViewHit_Axis0, ViewHit_Axis1);
					(*chunk).PlaceVoxel(idx.Voxel, voxel);
				}
			}
		}
	}
}
void ContextNoisePlane::ViewRayUpdate_Show()
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
			AccessLockedChunk chunk = ChunkManager.Container.FindAbsoluteAccess(idx.Chunk);
			if (chunk.Is() && (*chunk).IsDone() && (*chunk).IsEmpty())
			{
				const Voxel & voxel = (*chunk)[idx.Voxel];
				if (!voxel.IsEmpty())
				{
					const VoxelPallet & pallet = voxel.ToPallet();
					ss << (voxel.Orientation.GetDiag()) << " :Diag\n";
					ss << (voxel.Orientation.GetFlip()) << " :Flip\n";
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
		}
		ss << '\n';

		{
			NewPolyHedra::Basic3D::Object voxel_box_obj(VoxelCube);
			voxel_box_obj.Data().Trans.Position = ViewHit.Index.ToF();
			voxel_box_obj.HideFull();
			voxel_box_obj.ShowWire();
		}
	}

	VoxelClear.Show(ss);

	UI::Text::Object text; text.Create();
	text.Text() = ss.str();
	text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
	text.AlignTopRight(); // take DisplaySize
	text.Bound().Min = VectorF2();
	text.Bound().Max = window.Size.Buffer.Full;
	text.Color() = ColorF4(1, 1, 1);
}
void ContextNoisePlane::ViewRayUpdate()
{
	if (View_IsTangible)
	{
		ViewRayUpdate_Sync();
		ViewRayUpdate_Hit();
		ViewRayUpdate_HitDo();
		ViewRayUpdate_Show();
	}
	else
	{
		ViewHit = VoxelHit();
	}
}

void ContextNoisePlane::ViewUpdate(Trans3D change, FrameTime frame_time)
{
	StopWatch sw;

	sw.Start();
	ViewEntityUpdate(change, frame_time);
	sw.Stop();
	FrameTime_ViewUpdate_CollisionTime.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	ViewRayUpdate();
	sw.Stop();
	FrameTime_ViewUpdate_RayTime.NewValue(sw.ElapsedTime());
}



GL::BlockBinding ContextNoisePlane::LightBufferBinding = 3;

#include "Texture/FileMap.hpp"

void ContextNoisePlane::MakeVoxels()
{
	// VoxelPalletGeometryMap
	{
		VoxelPalletGeometryMap & map = VoxelPalletGeometryMap::StaticMap;

		VoxelPalletGeometryMapParser::Parse(map, MediaDirectory.File("Voxel/Geometry/Cube.file"));
		VoxelPalletGeometryMapParser::Parse(map, MediaDirectory.File("Voxel/Geometry/Star.file"));

		VoxelPalletGeometry & PrismY8 = map.New("PrismY8");
		PrismY8.InitU_CubeAxisY();
		PrismY8.InitF_PrismY8();
		//VoxelPalletGeometryMapParser::Parse(map, MediaDirectory.File("Voxel/Geometry/PrismY8.file"));

		VoxelPalletGeometry & PrismY12 = map.New("PrismY12");
		PrismY12.InitU_CubeDiag();
		PrismY12.InitF_PrismY12();

		VoxelPalletGeometry & Slope = map.New("Slope");
		Slope.InitU_CubeDiag();
		Slope.InitF_Slope();
	}

	// VoxelPalletMap
	{
		VoxelPalletMap & map = VoxelPalletMap::StaticMap;

		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Orientation/Cube.file"));
		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Orientation/Star.file"));
		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Orientation/PrismY8.file"));
		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Orientation/PrismY12.file"));

		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/CardBoard/_.file"));

		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Debug/_.file"));
		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Tree/_.file"));
		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Terrain/_.file"));
		VoxelPalletMapParser::Parse(map, MediaDirectory.File("Voxel/Concrete/_.file"));
	}

	// StructureMap
	{
		StructureMap & map = StructureMap::StaticMap;

		StructureMapParser::Parse(map, MediaDirectory.File("Voxel/Structure/Tree0"));
		StructureMapParser::Parse(map, MediaDirectory.File("Voxel/Structure/Tree1"));
	}

	// Texture
	{
		TextureFileMap tex_map;
		std::cout << "ContextNoisePlane::Make:" << __LINE__ << '\n';
		VoxelPalletMap::StaticMap.TexturesAssign(tex_map);
		std::cout << "ContextNoisePlane::Make:" << __LINE__ << '\n';
		ChunkManager.Graphics.Texture.Bind();
		ChunkManager.Graphics.Texture.Assign(VectorU2(32, 32), tex_map.Files.ToArray());
	}

	// PolyHedras
	{
		VoxelPalletMap::StaticMap.MakePolyHedras();

		// these are all Cuboids.
		// make 1 Cube PolyHedra then scale that
		VoxelCube = MakePolyHedraBoxEdges(BoxF3(VectorF3(0.0f), VectorF3(1.0f)));
		VoxelChunkCube = MakePolyHedraBoxEdges(BoxF3(VectorF3(0.1f), VectorF3(CHUNK_VALUES_PER_SIDE - 0.1f)));
		ViewEntity_PolyHedra = MakePolyHedraBoxEdges(ViewEntity.Box);
		PalletManager.FindMakePallet(VoxelCube);
		PalletManager.FindMakePallet(VoxelChunkCube);
		PalletManager.FindMakePallet(ViewEntity_PolyHedra);
	}
}

void ContextNoisePlane::Make()
{
	std::cout << "ContextNoisePlane::Make:" << __LINE__ << '\n';
	MakeVoxels();
	std::cout << "ContextNoisePlane::Make:" << __LINE__ << '\n';
	MakeControls();
	std::cout << "ContextNoisePlane::Make:" << __LINE__ << '\n';
	//ChunkManager.Container.ChangeSize(4, 2);
	//ChunkManager.Container.ChangeSize(8, 4);
	//ChunkManager.Container.ChangeSize(16, 4);
	//ChunkManager.Container.ChangeSize(16, 6);
	ChunkManager.Container.ChangeSize(16, 8);
	//ChunkManager.Container.ChangeSize(16, 12);
	//ChunkManager.Container.ChangeSize(32, 16);
	std::cout << "ContextNoisePlane::Make:" << __LINE__ << '\n';
}



// a lot of the managers are siminal with the bool flags and function names
// make a Base ? to organize
void ContextNoisePlane::ChangeMedia()
{
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
	NewPolyHedra_ChangeMedia();
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
	ChunkManager.Graphics.ChangeMedia(MediaDirectory);
	std::cout << "ContextNoisePlane::ChangeMedia() " << __LINE__ << '\n' << std::flush;
}

// Valgrind is very slow here ?
void ContextNoisePlane::GraphicsCreate()
{
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	PolyHedraManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	UIManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	//PlaneManager.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	ChunkManager.Graphics.GraphicsCreate();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
	LightBuffer.Create();
	std::cout << "ContextNoisePlane::GraphicsCreate() " << __LINE__ << '\n' << std::flush;
}
void ContextNoisePlane::GraphicsDelete()
{
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	PolyHedraManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	UIManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	//PlaneManager.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	ChunkManager.Graphics.GraphicsDelete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
	LightBuffer.Delete();
	std::cout << "ContextNoisePlane::GraphicsDelete() " << __LINE__ << '\n' << std::flush;
}

void ContextNoisePlane::Init()
{
	{
	std::cout << "ContextNoisePlane::Default:" << __LINE__ << '\n';
	window.DefaultColor = ColorF4(0.6f, 0.85f, 0.9f);

	LightManager.Clear();

	LightManager.Ambient = LightBase(0.8f, ColorF4(1.0f, 1.0f, 1.0f));
	LightManager.Solar = LightDirection(0.8f, ColorF4(1.0f, 1.0f, 1.0f), !VectorF3(+2.0f, -3.0f, +1.0f));
	LightManager.Spot_Array[0] = LightSpot(1.0f, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(), VectorF3(), RangeF(0.1f, 1.0f));

	LightManager.Ambient_Count = 1;
	LightManager.Solar_Count = 1;
	LightManager.Spot_Count = 0;

	View.Depth.Color = window.DefaultColor;
	View.Depth.Range.SetMin(0.5f);
	ViewEntity.Pos = VectorF3(0.5f, 0.5f, 0.5f);
	ViewEntity.Box = BoxF3(
		VectorF3(-0.4f, -1.6f, -0.4f),
		VectorF3(+0.4f, +0.2f, +0.4f)
	);
	std::cout << "ContextNoisePlane::Default:" << __LINE__ << '\n';
	View_Distance = 0.0f;
	View_IsTangible = false;
	ViewMove_SpeedSlow = 10.0f;
	ViewMove_SpeedFast = 100.0f;
	// Target = Accel / Decel
	// Target * Decel = Accel
	// Slow: Target = 5.0; Accel = 5.0 * 0.2 = 1.0
	// Slow: Target = 10.0; Accel = 10.0 * 0.2 = 2.0
	ViewMove_AccelSlow = 1.0f;
	ViewMove_AccelFast = 2.0f;
	ViewMove_Decel = 0.2f;
	std::cout << "ContextNoisePlane::Default:" << __LINE__ << '\n';
	}

	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	ChangeMedia();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	GraphicsCreate();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	UIManager.TextManager.InitFont();
	UIManager.GraphicsInit();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	Shader::Base::BindNone();
	LightBuffer.BindBase(LightBufferBinding);
	LayoutMultiform.Lights.ChangeData(LightBufferBinding);
	LayoutMultiform.Depth.ChangeData(View.Depth);
	LayoutMultiform.FOV.ChangeData(View.FOV);
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	Make();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
	AuxThreadCollection.Run();
	std::cout << "ContextNoisePlane::Init:" << __LINE__ << '\n';
}
void ContextNoisePlane::Free()
{
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	AuxThreadCollection.Terminate();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
	GraphicsDelete();
	std::cout << "ContextNoisePlane::Free:" << __LINE__ << '\n';
}



static unsigned int		TextCharCount = 0;

#include "Light/BufferData.hpp"
void ContextNoisePlane::Draw()
{
//	LayoutMultiform.Depth.ChangeData(View.Depth);

	StopWatch sw_total;
	sw_total.Start();

	StopWatch sw;



	VertexArray::Base::BindNone();
	LightBuffer.DataFull(Container::Void(LightManager.ToBufferData()));



	PolyHedraManager.InstancesClear();
	PolyHedraManager.InstancesMake();

	UIManager.Resize(window.Size);
	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Window.UpdateRecursive();
	UIManager.ControlManager.InstancesClear();
	UIManager.ControlManager.InstancesMake();
	UIManager.Window.WindowPutDisplay();

	UIManager.GraphManager.MakeInstances();



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	GL::Enable(GL::Capability::DepthClamp);

	sw.Clear();
	ObjectManagerBasic.GraphicsDrawFull();
	ObjectManagerBasic.GraphicsDrawWire();
	FrameTime_Draw_DrawPolyHedra.NewValue(sw.ElapsedTime());

	ObjectManagerTSC.GraphicsDrawFull();
	ObjectManagerTSC.GraphicsDrawWire();

	//PlaneManager.Draw();

	sw.Clear();
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

// seperate ChunkContainer and ChunkGraphics
struct ChunkContainerInfo
{
	VectorI3		Center;

	unsigned int	Know_Want = 0;
	unsigned int	Know_Have = 0;
	unsigned int	Know_Done = 0;

	unsigned int	Care_Want = 0;
	unsigned int	Care_Have = 0;
	unsigned int	Care_Done = 0;

	unsigned int	Limit = 0;
	unsigned int	Total = 0;

	unsigned int	Generation_None = 0;
	unsigned int	Generation_TerrainDone = 0;
	unsigned int	Generation_Decoration_Generated = 0;
	unsigned int	Generation_Decoration_Assambled = 0;
	unsigned int	Generation_Done = 0;

	unsigned int	Done_Empty = 0;
	unsigned int	Done_Filled = 0;

	unsigned int	Memory_Chunks = 0;
	unsigned int	Memory_Voxels = 0;

	void	Gather(ChunkContainer & container)
	{
		Center = container.Center;

		Know_Want = (container.KnowBox.Size() + 1).Product();
		Know_Have = 0;
		Know_Done = 0;

		Care_Want = (container.CareBox.Size() + 1).Product();
		Care_Have = 0;
		Care_Done = 0;

		Limit = container.Chunks.Length();
		Total = 0;

		Generation_None = 0;
		Generation_TerrainDone = 0;
		Generation_Decoration_Generated = 0;
		Generation_Decoration_Assambled = 0;
		Generation_Done = 0;

		Done_Empty = 0;
		Done_Filled = 0;

		Memory_Chunks = 0;
		Memory_Voxels = 0;

		for (unsigned int i = 0; i < Limit; i++)
		{
			if (container.Chunks[i] == nullptr) { continue; }
			Chunk & chunk = *container.Chunks[i];
			Total++;
			Memory_Chunks++;

			bool is_care = container.AbsoluteCheckCareBox(chunk.Index);

			Know_Have++;
			Care_Have += is_care;

			if (chunk.IsDone())
			{
				Generation_Done++;

				Know_Done++;
				Care_Done += is_care;

				if (chunk.IsEmpty())	{ Done_Empty++; }
				else					{ Done_Filled++; }
			}
			else if (chunk.DecorationsAssambled)	{ Generation_Decoration_Assambled++; }
			else if (chunk.DecorationsGenerated)	{ Generation_Decoration_Generated++; }
			else if (chunk.TerrainDone)				{ Generation_TerrainDone++; }
			else									{ Generation_None++; }

			if (!chunk.IsEmpty())
			{
				Memory_Voxels++;
			}
		}
	}
	void	Show(std::stringstream & ss)
	{
		ss << "ChunkContainer:\n";

		ss << "Center: " << Center << '\n';

		ss << "Know: " << Know_Want << ' ' << Know_Have << ' ' << Know_Done << '\n';
		ss << "Care: " << Care_Want << ' ' << Care_Have << ' ' << Care_Done << '\n';

		ss << "Limit: " << Limit << '\n';
		ss << "Total: " << Total << '\n';

		ss << "None   : " << Generation_None << '\n';
		ss << "Terrain: " << Generation_TerrainDone << '\n';
		ss << "DecGen : " << Generation_Decoration_Generated << '\n';
		ss << "DecAss : " << Generation_Decoration_Assambled << '\n';
		ss << "Done   : " << Generation_Done;
		ss << " ( ";
		ss << Done_Empty;
		ss << " | ";
		ss << Done_Filled;
		ss << " )\n";

		ss << "Memory: Chunks: ";
		//ss << Memory1000ToString(sizeof(Chunk));
		//ss << " * ";
		//ss << Seperated1000(Memory_Chunks);
		//ss << " = ";
		ss << Memory1000ToString(Memory_Chunks * sizeof(Chunk));
		ss << '\n';

		ss << "Memory: Voxels: ";
		//ss << Memory1000ToString(CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
		//ss << " * ";
		//ss << Seperated1000(Memory_Voxels);
		//ss << " = ";
		ss << Memory1000ToString(Memory_Voxels * CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
		ss << '\n';
	}
};
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
	unsigned long long buffer_data_u_total;
	unsigned long long buffer_data_u_limit;
	unsigned long long buffer_data_f_entrys;
	unsigned long long buffer_data_f_total;
	unsigned long long buffer_data_f_limit;

	VectorI3	ContainerCenter;
	BoxI3		ContainerKnowBox;
	BoxI3		ContainerCareBox;

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
		buffer_data_u_total = 0;
		buffer_data_u_limit = 0;
		buffer_data_f_entrys = 0;
		buffer_data_f_total = 0;
		buffer_data_f_limit = 0;
	}
	void	Gather(ChunkManager & manager)
	{
		chunks_limit = manager.Container.Chunks.Length();
		for (unsigned int i = 0; i < chunks_limit; i++)
		{
			if (manager.Container.Chunks[i] == nullptr) { continue; }
			Chunk & chunk = *manager.Container.Chunks[i];
			chunks_total++;

			if (chunk.TerrainDone) { chunks_gen_TD++; }
			if (chunk.DecorationsGenerated) { chunks_gen_DG++; }
			if (chunk.DecorationsAssambled) { chunks_gen_DA++; }
			if (chunk.IsDone())
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
			if (chunk.IsDone())
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

		buffer_data_u_entrys = manager.Graphics.BufferU.Count();
		buffer_data_u_total = manager.Graphics.BufferU.LengthSum();
		buffer_data_u_limit = manager.Graphics.BufferU.Buffer.Count;

		buffer_data_f_entrys = manager.Graphics.BufferF.Count();
		buffer_data_f_total = manager.Graphics.BufferF.LengthSum();
		buffer_data_f_limit = manager.Graphics.BufferF.Buffer.Count;

		ContainerCenter = manager.Container.Center;
		ContainerKnowBox = manager.Container.KnowBox;
		ContainerCareBox = manager.Container.CareBox;
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

		ss << "BufferState";
		ss << " None[" << buffer_data_none << ']';
		ss << " Want[" << buffer_data_want[0] << ':' << buffer_data_want[1] << ']';
		ss << " Have[" << buffer_data_have[0] << ':' << buffer_data_have[1] << ']';
		ss << '\n';

		ss << "Memory: Chunks: ";
		//ss << Memory1000ToString(sizeof(Chunk));
		//ss << " * ";
		//ss << Seperated1000(chunks_total);
		//ss << " = ";
		ss << Memory1000ToString(chunks_total * sizeof(Chunk));
		ss << '\n';

		ss << "Memory: Voxels: ";
		//ss << Memory1000ToString(sizeof(Voxel));
		//ss << " * ";
		//ss << Seperated1000(chunks_done_filled * CHUNK_VALUES_PER_VOLM);
		//ss << " = ";
		ss << Memory1000ToString(chunks_done_filled * CHUNK_VALUES_PER_VOLM * sizeof(Voxel));
		ss << '\n';

		ss << "Container: Center: " << ContainerCenter << '\n';
		ss << "Know: Box: " << ContainerKnowBox << ' ' << (ContainerKnowBox.Size() + 1) << ' ' << (ContainerKnowBox.Size() + 1).Product() << '\n';
		ss << "Care: Box: " << ContainerCareBox << ' ' << (ContainerCareBox.Size() + 1) << ' ' << (ContainerCareBox.Size() + 1).Product() << '\n';
		// Know: Total / Limit
		// Care: Total / Limit

		ss << "Entrys: DataU: ";
		ss << buffer_data_u_entrys;
		ss << " ( ";
		ss << buffer_data_u_total;
		ss << " / ";
		ss << buffer_data_u_limit;
		ss << " )\n";

		ss << "Entrys: DataF: ",
		ss << buffer_data_f_entrys;
		ss << " ( ";
		ss << buffer_data_f_total;
		ss << " / ";
		ss << buffer_data_f_limit;
		ss << " )\n";

		ss << "Memory: DataU: ";
		ss << Memory1000ToString(buffer_data_u_total * sizeof(VoxelGraphicsDataU::Vertex));
		ss << " / ";
		ss << Memory1000ToString(buffer_data_u_limit * sizeof(VoxelGraphicsDataU::Vertex));
		ss << '\n';

		ss << "Memory: DataF: ";
		ss << Memory1000ToString(buffer_data_f_total * sizeof(VoxelGraphicsDataF::Vertex));
		ss << "/";
		ss << Memory1000ToString(buffer_data_f_limit * sizeof(VoxelGraphicsDataF::Vertex));
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
		ss << "Total       " << ToString(::ChunkGraphics::DrawTotal.Average(), 6) << '\n';
		ss << "Wait        " << ToString(::ChunkGraphics::DrawWait.Average(), 6) << '\n';
		ss << "TextureBind " << ToString(::ChunkGraphics::DrawTextureBind.Average(), 6) << '\n';
		ss << "ShaderBind  " << ToString(::ChunkGraphics::DrawShaderBind.Average(), 6) << '\n';
		ss << "UpdateBind  " << ToString(::ChunkGraphics::DrawUpdateBind.Average(), 6) << '\n';
		ss << "BufferDraw  " << ToString(::ChunkGraphics::DrawBufferDraw.Average(), 6) << '\n';
		ss << "}\n";
		ShowNameTimeLine(ss, "DrawThread      ", FrameTime_DrawThread);
		ss << "}\n";

		ShowNameTimeLine(ss, "Inventory  Cursor", InventoryCursorTime);
		//ShowNameTimeLine(ss, "AuxThread       0", AuxThread0Time);
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
		ss << "AuxThread1 DoIdle: " << AuxThreadCollection.AuxThread1.DoIdle << '\n';
		ss << AuxThreadCollection.AuxThread1.TimeFind << '\n';
		ss << AuxThreadCollection.AuxThread1.TimeDo << '\n';
		ss << '\n';
		ss << "AuxThread2 DoIdle: " << AuxThreadCollection.AuxThread2.DoIdle << '\n';
		ss << AuxThreadCollection.AuxThread2.TimeGenerateFind << '\n';
		ss << AuxThreadCollection.AuxThread2.TimeGenerate << '\n';
		ss << '\n';
		ss << "AuxThread3 DoIdle: " << AuxThreadCollection.AuxThread3.DoIdle << '\n';
		ss << AuxThreadCollection.AuxThread3.TimeAssambleFind << '\n';
		ss << AuxThreadCollection.AuxThread3.TimeAssamble << '\n';
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
		AccessLockedChunk chunk = ChunkManager.Container.FindAbsoluteAccess(idx.Chunk);
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
			if ((*chunk).IsDone()) { ss << "Done"; }
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
		ss << "Chunk Know: " << ChunkManager.Container.KnowSize << '\n';
		ss << "Chunk Care: " << ChunkManager.Container.CareSize << '\n';

		VectorU3 know = ChunkManager.Container.Chunks.Size();
		VectorU3 care((ChunkManager.Container.CareSize * 2) + 1);

		ss << "Know: " << know << ' ' << know.Product() << '\n';
		ss << "Care: " << care << ' ' << care.Product() << '\n';

		ss << "ToInsert: " << ChunkManager.Container.ChunksToInsert.Count() << '\n';
		ss << "ToRemove: " << ChunkManager.Container.ChunksToRemove.Count() << '\n';

		ss << '\n';
	}
	sw.Stop(); TextTime_ChunkRange.NewValue(sw.ElapsedTime());

	// Queues
	{
		ss << "Queues:\n";

		ss << "BufferData Have " << ChunkManager.Graphics.Queue.Count() << '\n';
		ss << "BufferData Want " << AuxThreadCollection.AuxThread1.QueueCount() << '\n';
		ss << "Completed    : " << AuxThreadCollection.AuxThread1.Completed << '\n';
		ss << "Removed Null : " << AuxThreadCollection.AuxThread1.RemovedNull << '\n';
		ss << "Removed Check: " << AuxThreadCollection.AuxThread1.RemovedCheck << '\n';

		ss << "Generate Candidates " << AuxThreadCollection.AuxThread2.FindCandidateCount << '\n';
		ss << "Assamble Candidates " << AuxThreadCollection.AuxThread3.FindCandidateCount << '\n';

		ss << '\n';
	}

	// VoxelChunkMemory
	sw.Clear(); sw.Start();
	if (MenuDebug.VoxelChunkMemory.Check.IsChecked())
	{
		sw_part.Clear(); sw_part.Start();
		ChunkManager.Container.ChunksLock.AccessL();
		sw_part.Stop(); TextTime_VoxelChunkMemory_Wait.NewValue(sw_part.ElapsedTime());

		/* Info refresh rate
			I dont need this every frame
			the Threads run independently anyway
			so 10Hz or so should be fine
		*/
		//static VoxelChunkMemoryInfo info;
		static ChunkContainerInfo info;
		static StopWatch info_sw;
		info_sw.Start();

		sw_part.Clear(); sw_part.Start();
		if (info_sw.ElapsedTime() > 1.0f)
		{
			//info.Gather(ChunkManager);
			info.Gather(ChunkManager.Container);
			info_sw.Clear();
			info_sw.Start();
		}
		sw_part.Stop(); TextTime_VoxelChunkMemory_Loop.NewValue(sw_part.ElapsedTime());

		ChunkManager.Container.ChunksLock.AccessU();

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
	if (VoxelClear.Is())
	{
		std::stringstream ss;
		ss << "\n\n";
		ss << VoxelClear.Progress << '/' << VoxelClear.Required;
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
		ChunkManager.Container.Clear();
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
	//LightSpot.Pos = View.Trans.Position;
	//LightSpot.Dir = View.Trans.Rotation.forward(VectorF3(0, 0, 1));

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
		//LightManager.Spot_Array[0].Pos = ViewRay.Pos;
		//LightManager.Spot_Array[0].Dir = ViewRay.Dir;
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
		for (unsigned int i = 0; i < ChunkManager.Container.Chunks.Length(); i++)
		{
			Chunk * chunk = ChunkManager.Container.Chunks[i];
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
	LayoutMultiform.DisplaySize.ChangeData(display_size);
}



// make these virtual and put them in Base
void ContextNoisePlane::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void ContextNoisePlane::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void ContextNoisePlane::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void ContextNoisePlane::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void ContextNoisePlane::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void ContextNoisePlane::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
