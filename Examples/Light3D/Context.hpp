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
//#include "PolyHedraUI/Manager.hpp"
//#include "PolyHedraUI/Object.hpp"

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
#include "SceneObject/LightDirection.hpp"
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



#include "UI_Control_List.hpp"

#include "UserTrans3DChange.hpp"



// NewPolyHedra
#include "NewPolyHedra/Manager.hpp"
#include "NewPolyHedra/ObjectManager.hpp"
#include "NewPolyHedra/Pallet.hpp"
#include "NewPolyHedra/PalletManager.hpp"
#include "NewPolyHedra/PalletObjectData.hpp"
#include "NewPolyHedra/PalletObjectManager.hpp"
#include "NewPolyHedra/Type/ObjectManager.hpp"
#include "NewPolyHedra/Type/PalletObjectManager.hpp"
#include "NewPolyHedra/Type/Object.hpp"

#include "NewPolyHedra/DataType/Basic3D/Layout.hpp"
#include "NewPolyHedra/DataType/Basic3D/Object.hpp"
#include "NewPolyHedra/DataType/Basic3D/ObjectManager.hpp"

#include "NewPolyHedra/DataType/TransScaleColor3D/Layout.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/Object.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectManager.hpp"

struct Light3DContext : public ContextBase
{
View3D		View;
RayF3		ViewRay;
Matrix4x4	ViewMatrix;

::MultiformLayout	MultiformLayout;

//::PolyHedraManager	PolyHedraManager;

UI::Manager			UIManager;
SceneObjectUI		UISceneObject;

bool	IsHoveringUI() const;

//::PolyHedraUIManager	PolyHedraUIManager;



static const unsigned int	Light_Ambient_Limit = 1;
static const unsigned int	Light_Solar_Limit = 1;
static const unsigned int	Light_Spot_Limit = 4;

LightBase		Light_Ambient;
unsigned int	Light_Ambient_Count;

LightDirection	Light_Solar;
unsigned int	Light_Solar_Count;

LightSpot		Light_Spot_Array[Light_Spot_Limit];
unsigned int	Light_Spot_Count;

LightBase *			TakeLightAmbient();
LightDirection *	TakeLightSolar();
LightSpot *			TakeLightSpot();



SceneObject::DisplayMode			SceneObject_DisplayMode;
Container::Binary<SceneObject*>		Objects;
SceneObject *						Object_Selected;
SceneObject *						Object_Hovering;

SceneObject *	FindObject(const RayF3 & ray) const;
unsigned int	FindObjectIndex(const SceneObject *) const;

void	Objects_Change();
void	Objects_Update();



void	SceneClear();

void	SceneLoad(FileInfo file);
void	SceneSave(FileInfo file);

void	SceneInitCubes();
void	SceneInitLights();



::UserTrans3DChange UserTrans3DChange;

void	UserChange_Change();
void	UserChange_Update();



UI::Control::List	UIPolyHedraPalletList;
bool	DoPolyHedraPalletChange;
void	PolyHedraPalletChangeFunc(ClickArgs args);
void	PolyHedraPalletUpdate();



::NewPolyHedra_Manager		NewPolyHedra_Manager;

::PolyHedraFull::Main::Layout	PalletManager_BufferFullLayout;
::PolyHedraWire::Main::Layout	PalletManager_BufferWireLayout;
NewPolyHedra_PalletManager		PalletManager;

Basic3D::ShaderFullLayout	ObjectManagerBasic_ShaderFullLayout;
Basic3D::ShaderWireLayout	ObjectManagerBasic_ShaderWireLayout;
Basic3D::BufferLayout		ObjectManagerBasic_BufferFullLayout;
Basic3D::BufferLayout		ObjectManagerBasic_BufferWireLayout;
Basic3D::ObjectManager		ObjectManagerBasic;

TransScaleColor3D::ShaderFullLayout		ObjectManagerTSC_ShaderFullLayout;
TransScaleColor3D::ShaderWireLayout		ObjectManagerTSC_ShaderWireLayout;
TransScaleColor3D::BufferLayout			ObjectManagerTSC_BufferFullLayout;
TransScaleColor3D::BufferLayout			ObjectManagerTSC_BufferWireLayout;
TransScaleColor3D::ObjectManager		ObjectManagerTSC;



~Light3DContext();
Light3DContext();



SceneObject_PolyHedraObject		CenterCube;



Buffer::Uniform			LightBuffer;

::Shader::Base			LightShader;
::LightShaderLayout		LightShaderLayout;



void	ChangeMedia();
void	GraphicsCreate();
void	GraphicsDelete();



void	Make();
void	Init() override;
void	Free() override;

void	User(FrameTime frame_time);
void	Draw();

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