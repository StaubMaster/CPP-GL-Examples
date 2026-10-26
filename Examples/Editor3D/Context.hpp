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

# include "Special/Basic3D/Manager.hpp"
# include "Special/Basic3D/Object.hpp"

# include "Special/TransScaleColor3D/Manager.hpp"
# include "Special/TransScaleColor3D/Object.hpp"

# include "NewPolyHedra/UserInterface/Manager.hpp"

struct Light3DContext : public ContextBase
{
Container::Array<FileInfo>	ArgumentFiles;

View3D		View;
RayF3		ViewRay;
Matrix4x4	ViewMatrix;



/* rename PolyHedraFileCollection
PolyHedraManager
PolyHedraOrganizer
*/
::PolyHedraFileCollection	PolyHedraFileCollection;

NewPolyHedra::Manager					NewPolyHedraManager;
NewPolyHedra::PalletManager				NewPolyHedraPalletManager;
NewPolyHedra::Basic3D::Manager			NewPolyHedraManagerBasic;
TransScaleColor3D::Manager				NewPolyHedraManagerTSC;
NewPolyHedra::UserInterface::Manager	NewPolyHedraManagerUI;

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