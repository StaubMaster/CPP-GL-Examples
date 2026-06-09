#ifndef  LIGHT_3D_CONTEXT_HPP
# define LIGHT_3D_CONTEXT_HPP

# include "General/ContextBase.hpp"

//
#include <iostream>
#include "OpenGL.hpp"
#include "Debug.hpp"

#include "ValueType/_Include.hpp"
#include "ValueType/_Show.hpp"

#include "Graphics/Shader/Code.hpp"

// UniForm
#include "Graphics/Uniform/_Include.hpp"
#include "Graphics/Multiform/_Include.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"

// Containers
#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Binary.hpp"
//#include "Miscellaneous/EntryContainer/Binary.hpp"

//#include "Window.hpp"
//#include "Function/Object.hpp"
//#include "ValueType/View.hpp"

#include "FileInfo.hpp"
//#include "DirectoryInfo.hpp"
#include "Image.hpp"



struct SpotLightEntry
{
	VectorF3			Position;
	VectorF3			Target;
	LightSpot *			Light;
	PolyHedraObject		EntryLight;
	PolyHedraObject		EntryHolder;

	~SpotLightEntry();
	SpotLightEntry();

	void	LookFromTo(VectorF3 from, VectorF3 to);
	void	Update();

	void	Toggle();
};

class LightShaderLayout : public PolyHedraFull::ShaderLayout
{
	public:
	Uniform::LightBase								Light_Ambient;
	Uniform::LightSolar								Light_Solar;
	Uniform::GArray<Uniform::LightSpot, LightSpot>	Light_Spot_Array;
	Uniform::UInt									Light_Spot_Count;

	public:
	~LightShaderLayout();
	LightShaderLayout();
};

struct Light3DContext : public ContextBase
{
View3D	view;

::PolyHedraManager					PolyHedraManager;
Container::Binary<PolyHedraObject>	Objects;



~Light3DContext();
Light3DContext();



float Light_Ambient_Intensity;
LightBase Light_Ambient;

float Light_Solar_Intensity;
LightSolar Light_Solar;

#define Light_Spot_Limit 4
LightSpot * Light_Spot_Array;
SpotLightEntry * Light_Spot_Entry_Array;

unsigned int Light_Spot_Count;

void LightsInit();
void LightsFree();

::Shader::Base			LightShader;
::LightShaderLayout		LightShaderLayout;



void	ChangeMedia();
void	GraphicsCreate();
void	GraphicsDelete();



void	RandomCubes();
void	FancyLights();
void	Fancify();



void	Init() override;
void	Free() override;

void	User(FrameTime frame_time);
void	Draw();

void	ViewRay();

void	Frame(FrameTime frame_time) override;
void	Resize(DisplaySize display_size) override;

void	MouseMove(MoveArgs args) override;
void	MouseClick(ClickArgs args) override;
void	MouseScroll(ScrollArgs args) override;
void	MouseDrag(DragArgs args) override;
void	KeyBoardKey(KeyArgs args) override;
void	KeyBoardText(TextArgs args) override;
};

#endif