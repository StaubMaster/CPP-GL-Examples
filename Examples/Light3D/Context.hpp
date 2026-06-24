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

// PolyHedraUI
#include "PolyHedraUI/Manager.hpp"
#include "PolyHedraUI/Object.hpp"

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

// User Interface
#include "UIManager.hpp"



// SceneObject
#include "SceneObject/SceneObject.hpp"
#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightSolar.hpp"
#include "SceneObject/LightSpot.hpp"
#include "SceneObject/UI/SceneObject.hpp"



#include "Graphics/Multiform/Layout.hpp"
#include "Graphics/Multiform/_Include.hpp"
struct MultiformLayout : public Multiform::Layout
{
	Multiform::DisplaySize	DisplaySize;
	Multiform::Matrix4x4	View;
	Multiform::Depth		Depth;
	Multiform::Angle		FOV;
	~MultiformLayout();
	MultiformLayout();
};



struct Light3DContext : public ContextBase
{
View3D		View;
Ray3D		ViewRay;
Matrix4x4	ViewMatrix;

::MultiformLayout	MultiformLayout;

::PolyHedraManager		PolyHedraManager;

UI::Manager				UIManager;
SceneObjectUI			UISceneObject;

bool	IsHoveringUI() const;

::PolyHedraUIManager	PolyHedraUIManager;



Container::Binary<SceneObject*>		Objects;
SceneObject *						Object_Selected;
SceneObject *						Object_Hovering;

SceneObject *	FindObject(const Ray3D & ray) const;
unsigned int	FindObjectIndex(const SceneObject *) const;



~Light3DContext();
Light3DContext();



SceneObject_PolyHedraObject		CenterCube;



LightBase		Light_Ambient;
LightSolar		Light_Solar;

static const unsigned int		Light_Spot_Limit = 4;
unsigned int			Light_Spot_Count;
LightSpot				Light_Spot_Array[Light_Spot_Limit];

SceneObject_LightAmbient	LightAmbientObject;
SceneObject_LightSolar		LightSolarObject;
SceneObject_LightSpot		LightSpotObjects[Light_Spot_Limit];



::Shader::Base			LightShader;
::LightShaderLayout		LightShaderLayout;



void	ChangeMedia();
void	GraphicsCreate();
void	GraphicsDelete();



void	LightsMake();
void	RandomCubes();
void	FancyLights();
void	Fancify();



void	Make();
void	Init() override;
void	Free() override;

void	User(FrameTime frame_time);
void	Draw();

void	ViewObjectFunc();
void	ViewChangeTransFunc();
void	ViewFunc();

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