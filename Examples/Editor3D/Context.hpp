#ifndef  LIGHT_3D_CONTEXT_HPP
# define LIGHT_3D_CONTEXT_HPP

# include "ContextBase.hpp"

// Layout
# include "Layout/Uniform/Light3D.hpp"
# include "Layout/Multiform/Light3D.hpp"

//
# include "Light/Manager.hpp"

// PolyHedra
# include "PolyHedra/PolyHedra.hpp"

// Containers
# include "Generics/Container/Array.hpp"
# include "Generics/Container/Binary.hpp"

// File Manager
# include "FileInfo.hpp"
# include "Image.hpp"

// Hit
# include "Ray3D_Hit.hpp"

// SceneObject
# include "SceneObject/SceneObject.hpp"
# include "SceneObject/UI/SceneObject.hpp"
# include "SceneObject/DisplayMode.hpp"
# include "SceneObject/Collection.hpp"

// User Interface
# include "UIManager.hpp"
# include "UI/ListForm.hpp"
//# include "UI/UserTrans3DChange.hpp"
# include "UI/Change3D/VectorF3.hpp"
# include "UI/Change3D/EulerAngle3D.hpp"
# include "UI/Change3D/Trans3D.hpp"

// PolyHedra
# include "PolyHedra/FileCollection.hpp"

// NewPolyHedra
# include "NewPolyHedra/Manager.hpp"

# include "NewPolyHedra/Pallet/.hpp"
# include "NewPolyHedra/Pallet/Manager.hpp"

# include "NewPolyHedra/Base/Manager.hpp"
# include "NewPolyHedra/Base/Logical/Object.hpp"
# include "NewPolyHedra/Base/Logical/ObjectManager.hpp"
# include "NewPolyHedra/Base/Display/Object.hpp"
# include "NewPolyHedra/Base/Display/ObjectManager.hpp"

# include "NewPolyHedra/Type/Manager.hpp"
# include "NewPolyHedra/Type/Logical/Object.hpp"
# include "NewPolyHedra/Type/Logical/ObjectManager.hpp"
# include "NewPolyHedra/Type/Display/Object.hpp"
# include "NewPolyHedra/Type/Display/ObjectManager.hpp"

# include "NewPolyHedra/Type/Object.hpp"

# include "NewPolyHedra/DataType/Basic3D/Layout.hpp"
# include "NewPolyHedra/DataType/Basic3D/Object.hpp"
# include "NewPolyHedra/DataType/Basic3D/Manager.hpp"

# include "NewPolyHedra/DataType/TransScaleColor3D/Layout.hpp"
# include "NewPolyHedra/DataType/TransScaleColor3D/Object.hpp"
# include "NewPolyHedra/DataType/TransScaleColor3D/Manager.hpp"

struct Light3DContext : public ContextBase
{
Container::Array<FileInfo>	ArgumentFiles;

View3D		View;
RayF3		ViewRay;
Matrix4x4	ViewMatrix;



::PolyHedraFileCollection	PolyHedraFileCollection;

NewPolyHedra::Manager		NewPolyHedra_Manager;

NewPolyHedra::PalletManager		PalletManager;

//ShaderLayoutLight3D						ObjectManagerBasic_ShaderFullLayout;
//ShaderLayoutView3D						ObjectManagerBasic_ShaderWireLayout;
//NewPolyHedra::Basic3D::BufferLayout		ObjectManagerBasic_BufferFullLayout;
//NewPolyHedra::Basic3D::BufferLayout		ObjectManagerBasic_BufferWireLayout;
NewPolyHedra::Basic3D::Manager				ObjectManagerBasic;

LayoutUniformView3D						ObjectManagerTSC_ShaderFullLayout;
LayoutUniformView3D						ObjectManagerTSC_ShaderWireLayout;
TransScaleColor3D::BufferLayout			ObjectManagerTSC_BufferFullLayout;
TransScaleColor3D::BufferLayout			ObjectManagerTSC_BufferWireLayout;
TransScaleColor3D::Manager				ObjectManagerTSC;

void	PolyHedra_ChangeMedia();



LayoutMultiformLight3D	LayoutMultiform;



UI::Manager			UIManager;
SceneObjectUI		UISceneObject;
bool	IsHoveringControl() const;



// Light
static GL::BlockBinding		BindingLight;

::LightManager		LightManager;
Buffer::Uniform		LightBuffer;

void InitLights();



// User Change
Change3D::Trans3D	UserChange;

void	UserChange_ChangeObject(SceneObject * obj);

void	UserChange_HoverSelect();
void	UserChange_Update();



ListForm	UIPolyHedraPalletList;
bool	DoPolyHedraPalletChange = false;
void	PolyHedraPalletChangeFunc(ClickArgs args);
void	PolyHedraPalletUpdate();



SceneObjectDisplayMode				DisplayMode;
SceneObjectCollection				Collection;
SceneObject *						Object_Selected = nullptr;
SceneObject *						Object_Hovering = nullptr;
SceneObject_PolyHedraObject *		CenterCube = nullptr;

void	Objects_Change();
void	Objects_Update();



void	SceneClear();

void	SceneLoad(FileInfo file);
void	SceneSave(FileInfo file);

void	SceneInitCubes();
void	SceneInitLights();

void	SceneReMake();



Light3DContext(const Container::Array<FileInfo> & files);



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