#include "Context.hpp"
#include "Window.hpp"
#include "FileInfo.hpp"

#include <iostream>

// Tiles
#include "Tile/Pallet.hpp"
#include "Tile/Parser.hpp"
#include "Tile/PalletDisplayOptions.hpp"
#include "Tile/Object.hpp"
#include "Tile/Feature/Pallet/DeathFall.hpp"
#include "Tile/Feature/Pallet/DeathWall.hpp"
#include "Tile/Feature/Pallet/CoinParabola.hpp"
#include "Tile/Feature/Object/Coin.hpp"



// PolyHedra
#include "PolyHedra/Data.hpp"
static void MakePolyHedraBoxEdges(PolyHedra & polyhedra, BoxF3 box)
{
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Min.Y, box.Min.Z))); // 000
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Min.Y, box.Min.Z))); // 001
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Max.Y, box.Min.Z))); // 010
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Max.Y, box.Min.Z))); // 011
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Min.Y, box.Max.Z))); // 100
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Min.Y, box.Max.Z))); // 101
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Max.Y, box.Max.Z))); // 110
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Max.Y, box.Max.Z))); // 111

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



void Context::ViewDefault()
{
	View.Trans = Trans3D(VectorF3(0, 75, -75), EulerAngle3D::Degrees(0, 5, 0));
}
void Context::ViewChange(FrameTime frame_time)
{
	if (Window.KeyBoardManager[Keys::Tab].State == State::Press) { Window.MouseManager.CursorModeToggle(); }
	if (Window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = Window.MoveSpinFromKeysCursor();

		if (Window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Position *= 10; }
		trans.Position *= 20;
		trans.Rotation *= View.FOV.ToRadians() * 0.05f;

		trans.Position *= frame_time.Delta;
		trans.Rotation *= frame_time.Delta;

		View.ChangeAbsoluteFlatY(trans);
	}
	MultiformLayout.View.ChangeData(Matrix4x4::TransformReverse(View.Trans));
}



#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"

#include "Graphics/Attribute/_Include.hpp"

void Context::NewPolyHedra_Create()
{
	// NewPolyHedra
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
	}

	// Object Manager Basic
	{
		{
			ObjectManagerBasic.ShaderFull.Change({
				MediaDirectory.File("Shader/Default.vert"),
				MediaDirectory.File("Shader/UniformLight.frag"),
			});
			/*{
				ObjectManagerBasic.ShaderFull.AssignLayout(ObjectManagerBasic_ShaderFullLayout);
			}*/
			{
				Uniform::Layout * layout = new Uniform::Layout(ObjectManagerBasic.ShaderFull);
				layout -> IsDynamic = true;
				new Uniform::DisplaySize	(*layout, "DisplaySize", true);
				new Uniform::Matrix4x4		(*layout, "View", true);
				new Uniform::Depth			(*layout, "Depth", true);
				new Uniform::Angle			(*layout, "FOV", true);
				ObjectManagerBasic.ShaderFull.AssignLayout(layout);
				MultiformLayout.Find(layout);
			}
			{
				Attribute::Layout * layout = new Attribute::Layout(1, sizeof(NewPolyHedra::Basic3D::InstanceData));
				layout -> IsDynamic = true;
				new Attribute::Matrix4x4	(*layout, 3, true);
				new Attribute::Matrix4x4	(*layout, 7, true);
				ObjectManagerBasic.BufferFullLayout = layout;
			}

			ObjectManagerBasic.ShaderWire.Change({
				MediaDirectory.File("Shader/Wire.vert"),
				MediaDirectory.File("Shader/Wire.frag"),
			});
			{
				Uniform::Layout * layout = new Uniform::Layout(ObjectManagerBasic.ShaderWire);
				layout -> IsDynamic = true;
				new Uniform::DisplaySize	(*layout, "DisplaySize", true);
				new Uniform::Matrix4x4		(*layout, "View", true);
				new Uniform::Depth			(*layout, "Depth", true);
				new Uniform::Angle			(*layout, "FOV", true);
				ObjectManagerBasic.ShaderWire.AssignLayout(layout);
				MultiformLayout.Find(layout);
			}
			{
				Attribute::Layout * layout = new Attribute::Layout(1, sizeof(NewPolyHedra::Basic3D::InstanceData));
				layout -> IsDynamic = true;
				new Attribute::Matrix4x4	(*layout, 3, true);
				new Attribute::Matrix4x4	(*layout, -1, true);
				ObjectManagerBasic.BufferWireLayout = layout;
			}
		}
	}
}



#include "PolyHedra/Parser.hpp"

#include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"
void Context::TileFeaturesInit()
{
	PolyHedra * polyhedra;
	{
		// make Load defaults second and third parameter to nullptr
		// make function that returns Type Pointer

		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Meta/Entry.polyhedra"), nullptr, nullptr);
		TilePallet::ObjectManagerEntry = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);

		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Meta/Exit.polyhedra"), nullptr, nullptr);
		TilePallet::ObjectManagerExit = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);

		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Meta/Path.polyhedra"), nullptr, nullptr);
		NodePath::Object = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
	}
	// Pallet Features
	{
		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Meta/Danger.polyhedra"), nullptr, nullptr);
		TileFeaturePalletDeathFall::Object = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Meta/Danger.polyhedra"), nullptr, nullptr);
		TileFeaturePalletDeathWall::Object = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
	}
	// Object Features
	{
		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Coin.polyhedra"), nullptr, nullptr);
		TileFeatureObjectCoin::Object = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
		polyhedra = new PolyHedra;
		MakePolyHedraBoxEdges(*polyhedra, BoxF3(VectorF3(-2, -2, -2), VectorF3(+2, +2, +2)));
		TileFeatureObjectCoin::ObjectBox = (NewPolyHedra::Basic3D::PalletObjectManager*)ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
	}

	Player.MakeDefault();
}

void Context::TilePalletsInit()
{
	Container::Binary<TilePallet*> pallets;

	DirectoryInfo dir = MediaDirectory.Directory("Tile/Pallet/");
	Container::Array<FileInfo> files(
	{
		//dir.File("I.tile"),
		//dir.File("L_L.tile"),
		//dir.File("L_R.tile"),

		//dir.File("T.tile"),
		//dir.File("T_L.tile"),
		//dir.File("T_R.tile"),
		//dir.File("X.tile"),

		dir.File("I_Gap.tile"),
		//dir.File("I_Gap2.tile"),
		//dir.File("I_Gap_L.tile"),
		//dir.File("I_Gap_R.tile"),
		//dir.File("T_Gap_L.tile"),
		//dir.File("T_Gap_R.tile"),

		//dir.File("I_Obs.tile"),
	});
	for (unsigned int i = 0; i < files.Length(); i++)
	{
		pallets.Insert(TileParser::Parse(files[i], MediaDirectory, Player));
	}

	TileStart = TileParser::Parse(dir.File("Info.tile"), MediaDirectory, Player);
	TilePallets = pallets.ToArray();
}
void Context::TilePalletsFree()
{
	for (unsigned int i = 0; i < TilePallets.Length(); i++)
	{
		delete TilePallets[i];
	}
	TilePallets.Clear();

	delete TileStart;
	TileStart = nullptr;
}



#include "ValueGen/Random.hpp"
TileObject * Context::TileNewRandom()
{
	unsigned int val = Random::UInt32();
	TilePallet * pallet = TilePallets[val % TilePallets.Length()];
	return pallet -> ToObject();
}
void Context::TileNewRandomExit(TileObject * tile, unsigned int layers)
{
	if (tile == nullptr) { return; }
	if (layers == 0) { return; }
	layers--;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (tile -> Pallet.HasPath((EPath)i))
		{
			if (tile -> Exit[i] == nullptr)
			{
				tile -> ConnectExit(TileNewRandom(), (EPath)i);
			}
			if (layers != 0)
			{
				TileNewRandomExit(tile -> Exit[i], layers);
			}
		}
	}
	/*if (tile -> Pallet.HasExit(0))
	{
		if (tile -> Exit[0] == nullptr)
		{
			tile -> ConnectExit(TileNewRandom(), 0);
		}
		if (layers != 0)
		{
			TileNewRandomExit(tile -> Exit[0], layers);
		}
	}*/
	/*if (tile -> Pallet.HasExit(1))
	{
		if (tile -> Exit[1] == nullptr)
		{
			tile -> ConnectExit(TileNewRandom(), 1);
		}
		if (layers != 0)
		{
			TileNewRandomExit(tile -> Exit[1], layers);
		}
	}*/
}



void Context::TileInit()
{
	delete CurrentTile;
	CurrentTile = new TileObject(*TileStart);

	TileNewRandomExit(CurrentTile, 2);

	Player.MakeDefault();
}
void Context::TileFree()
{
	delete CurrentTile;
	CurrentTile = nullptr;
}

void Context::TileIterate()
{
	Player.Height += Player.JumpSpeed;

	Player.Side = EPath::Middle;
	if (Window[Keys::Left]  == State::Down) { Player.Side = EPath::Left; }
	if (Window[Keys::Right] == State::Down) { Player.Side = EPath::Right; }

	if (CurrentTile != nullptr)
	{
		Player.TotalDistance += Player.Speed;
		Player.TileDistance += Player.Speed;
		const TilePallet & pallet = CurrentTile -> Pallet;
		float limit = pallet.PathLimit(Player.Path);
		if (Player.TileDistance < limit)
		{
			Player.Change.Consider(CurrentTile -> CheckPlayer(Player));
			if (pallet.CanChoosePath(Player))
			{
				Player.Path = pallet.ChoosePath(Player.Side, Player);
				Player.PathLocked = true;
			}
		}
		else
		{
			Player.TileDistance -= limit;
			if (CurrentTile != nullptr)
			{
				CurrentTile -> TrimEntry();

				TileObject * exit = nullptr;
				if (Player.Path == EPath::Middle)
				{
					exit = CurrentTile -> Exit[0];
				}
				if (Player.Path == EPath::Left)
				{
					exit = CurrentTile -> Exit[1];
				}
				if (Player.Path == EPath::Right)
				{
					exit = CurrentTile -> Exit[2];
				}
				if (exit == nullptr)
				{
					exit = CurrentTile -> Exit[0];
				}
				CurrentTile = exit;
			}

			if (CurrentTile == nullptr)
			{
				std::cerr << "Missing Current Tile\n";
				CurrentTile = new TileObject(*TileStart);
			}

			TileNewRandomExit(CurrentTile, 2);
			Player.Path = EPath::Middle;
			Player.PathLocked = false;
		}
	}

	if (Player.Change.NotAboveGround || Player.Height > 0.0f)
	{
		Player.JumpSpeed -= Player.Gravity;
	}
	else
	{
		Player.Height = 0.0f;
		if (Window[Keys::Up] == State::Down)
		{
			// jump
			Player.JumpSpeed = Player.JumpImpulse;
		}
		else
		{
			// ground
			Player.JumpSpeed = 0.0f;
			// dont gound if falling to death
		}
	}
}
void Context::TileDisplay()
{
	if (CurrentTile != nullptr)
	{
		Trans3D trans = CurrentTile -> Pallet.Target(Player.Path, Player.TileDistance);
		trans.Position = trans.Rotation.reverse(trans.Position);
		trans = Trans3D(
			-trans.Position,
			-trans.Rotation
		);
		CurrentTile -> Display(trans, TilePalletDisplayOptions);
	}
}



Context::~Context()
{
	NewPolyHedra_Manager.GraphicsDelete();
	TextManager.GraphicsDelete();

	TileFree();
	TilePalletsFree();
}
Context::Context(::Window & window)
	: Window(window)
	, MediaDirectory("./media")
	, MultiformLayout()
{
	NewPolyHedra_Manager.PalletManager = &PalletManager;
	NewPolyHedra_Manager.ObjectManagers.Insert(&ObjectManagerBasic);

	TextManager.MakeCurrent();
	TextManager.ChangeMedia(MediaDirectory);
	TextManager.Font = UI::Text::Font::Parse(
		MediaDirectory.File("Text/Font0.atlas")
	);
	MultiformLayout.Find(TextManager.ShaderLayout);

	Window.CallBack_Frame.Assign(this, &Context::Frame);
	Window.CallBack_Resize.Assign(this, &Context::Resize);
	NewPolyHedra_Create();

	window.DefaultColor = ColorF4(0.5f, 0.5f, 0.5f);
	View.Depth.Color = window.DefaultColor;
	View.Depth.Factors.ChangeFar(500.0f);
	ViewDefault();

	Player.MakeDefault();

	{
		PolyHedra * polyhedra;
		polyhedra = PolyHedraParser::Load(MediaDirectory.File("PolyHedra/Player.polyhedra"), nullptr, nullptr);
		Player.Object.Manager = ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
		polyhedra = new PolyHedra();
		MakePolyHedraBoxEdges(*polyhedra, Player.Box);
		Player.ObjectBox.Manager = ObjectManagerBasic.PalletObjectManagersFindMake(polyhedra);
		Player.ObjectBox.HideFull();
		Player.ObjectBox.ShowWire();
	}

	TileFeaturesInit();
	TilePalletsInit();
	TileInit();

	MultiformLayout.Depth.ChangeData(View.Depth);
	MultiformLayout.FOV.ChangeData(View.FOV);

	NewPolyHedra_Manager.GraphicsCreate();

	TextManager.GraphicsCreate();
	TextManager.InitFont();
	TextManager.GraphicsInit();
}



static void Toggle(bool & value)
{
	value = !value;
}

void Context::Draw()
{
	NewPolyHedra_Manager.InstancesClear();
	NewPolyHedra_Manager.InstancesMake();

	Player.Object.InstancePut();
	Player.ObjectBox.InstancePut();

	TileDisplay();



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	ObjectManagerBasic.GraphicsDrawFull();
	ObjectManagerBasic.GraphicsDrawWire();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	GL::Enable(GL::Capability::DepthClamp);

	TextManager.MakeInstances();
	TextManager.Shader.Bind();
	TextManager.ShaderLayout.DisplaySize.Put(Window.Size);
	TextManager.Draw();



	// Update

	NewPolyHedra_Manager.UpdatePalletObjectDatas();
}

#include "ValueType/_Show.hpp"
#include "UIText/Object.hpp"
void Context::Frame(FrameTime frame_time)
{
	{
		std::stringstream ss;
		ss << (int)(Player.TotalDistance / 10) << "m\n";
		ss << Player.Change.Coins << "Coins\n";
		ss << Player.Change.NotAboveGround << " NotAboveGround\n";
		ss << Player.Change.DeathWall << " DeathWall\n";
		ss << Window.MouseManager.CursorModeIsLocked() << " CursorLocked\n";
		ss << IsPaused << " Paused\n";

		UI::Text::Object text;
		text.Create();
		text.Color() = ColorF4(0, 0, 0);
		text.AlignTopRight();
		text.TextPosition().X = Window.Size.Buffer.Full.X - 10.0f;
		text.TextPosition().Y = 0 + 10.0f;
		text.CharacterSize() = VectorF2(20, 20);
		text.Text() = ss.str();
	}

	// Update

	ViewChange(frame_time);

	bool do_step = !IsPaused;
	if (Window[Keys::F1] == State::Press) { Toggle(IsPaused); }
	if (Window[Keys::F2] == State::Press) { do_step = true; }
	if (Window[Keys::F3] == State::Press) { ViewDefault(); }
	if (Window[Keys::F5] == State::Press)
	{
		TileFree();
		TilePalletsFree();
		TilePalletsInit();
		TileInit();
	}
	if (Window[Keys::F6] == State::Press) { Toggle(TilePalletDisplayOptions.Connections); }
	if (Window[Keys::F7] == State::Press) { Toggle(TilePalletDisplayOptions.Paths); }
	if (Window[Keys::F8] == State::Press) { Toggle(TilePalletDisplayOptions.Features); }

	if (IsDead && Window[Keys::Space] == State::Press)
	{
		IsDead = false;
		TileInit();
	}

	if (do_step)
	{
		if (Player.Height <= -32.0f || Player.Change.DeathWall)
		{
			IsDead = true;
		}
		else
		{
			TileIterate();
		}

		/*if (!Player.Change.DeathFall && !Player.Change.DeathWall)
		{
			TileIterate();
		}
		else if (Player.Change.DeathWall)
		{
			IsDead = true;
		}
		else if (Player.Change.DeathFall)
		{
			if (Player.Height > -32.0f)
			{
				Player.TotalDistance += Player.Speed;
				Player.TileDistance += Player.Speed;
				Player.Height += Player.JumpSpeed;
				Player.JumpSpeed -= Player.Gravity;
			}
			else
			{
				IsDead = true;
			}
		}*/
	}

	// Update Player Display
	{
		VectorF3 pos;
		if (Player.Side == EPath::Middle)	{ pos.X = 0.0f; }
		if (Player.Side == EPath::Left)		{ pos.X = -15.0f; }
		if (Player.Side == EPath::Right)	{ pos.X = +15.0f; }
		pos.Y = Player.Height;

		Player.Object.Data.Trans.Position = pos + VectorF3(0.0f, 16.0f, 0.0f);
		Player.ObjectBox.Data.Trans.Position = pos;
	}

	Draw();
}
void Context::Resize(DisplaySize display_size)
{
	MultiformLayout.DisplaySize.ChangeData(display_size);
}
