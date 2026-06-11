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


// Hit
#include "Ray3D_Hit.hpp"

// 
#include "LightShaderLayout.hpp"
#include "SpotLightEntry.hpp"

// User Interface
#include "UIManager.hpp"
#include "UI/PolyHedraObject.hpp"
#include "UI/SpotLightEntry.hpp"



/* Objects
PolyHedraObject
	just a PolyHedra with a Transformation
LightAmbient
	the Ambient Light Contoller
	is an Object with a Position so it can be Selected ?
	or just have a list of Meta stuff ?
LightSolar
	the Solar Light Controller
	same as with LightAmbient
LightSpot
	is a Spot Light Controller
	there is a Limit for these
SpotLightEntry
	has a pointer to a LightSpot
	has 2 PolyHedraObjects
*/
struct SceneObject
{
	virtual ~SceneObject();
	SceneObject();
	virtual void	Update() = 0;
	virtual Ray3D_Hit	Hit(const Ray3D & ray) const = 0;
};
struct SceneObject_PolyHedraObject : public SceneObject
{
	PolyHedraObject		Object;
	~SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject(const PolyHedraObject & obj);
	void	Update() override;
	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};
struct SceneObject_SpotLightEntry : public SceneObject
{
	SpotLightEntry		Object;
	~SceneObject_SpotLightEntry();
	SceneObject_SpotLightEntry();
	void	Update() override;
	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};



struct Light3DContext : public ContextBase
{
View3D	view;

::PolyHedraManager		PolyHedraManager;

UI::Manager				UIManager;
UI::PolyHedraObject		UIPolyHedraObject;
UI::SpotLightEntry		UISpotLightEntry;

Container::Binary<SceneObject*>		Objects;



~Light3DContext();
Light3DContext();



SceneObject_PolyHedraObject		CenterCube;



float Light_Ambient_Intensity;
LightBase Light_Ambient;

float Light_Solar_Intensity;
LightSolar Light_Solar;

#define Light_Spot_Limit 4
LightSpot * Light_Spot_Array;
SceneObject_SpotLightEntry * Light_Spot_Entry_Array;

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



void	Make();
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