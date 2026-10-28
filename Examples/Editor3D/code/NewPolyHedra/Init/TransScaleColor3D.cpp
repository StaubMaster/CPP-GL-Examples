#include "NewPolyHedra/Init/TransScaleColor3D.hpp"
#include "Special/TransScaleColor3D/Layout.hpp"

#include "NewPolyHedra/Base/Display/ObjectManager.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Multiform/General/Layout.hpp"

#include "Layout/Uniform/View3D.hpp"

void TransScaleColor3D::ChangeMedia(const DirectoryInfo & media_dir, Multiform::Layout & multiform_layout, NewPolyHedra::BaseDisplayObjectManager & graphics)
{
			graphics.ShaderFull.Change({
				media_dir.File("Shaders/PolyHedra/UserInterface.vert"),
				media_dir.File("Shaders/PolyHedra/TexturedNoLight.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformView3D();
				graphics.ShaderFull.AssignLayout(layout);
				multiform_layout.Find(layout);
			}
			{
				NewPolyHedra::PalletFull::Layout & layout = graphics.BufferFullMainLayout;
				layout.Position.Change(0);
				layout.Normal.Change(1);
				layout.Texture.Change(2);
				layout.Color.Change(3);
			}
			{
				TransScaleColor3D::BufferLayout * layout = new TransScaleColor3D::BufferLayout();
				layout -> Trans.Change(4);
				layout -> Normal.Change(-1);
				layout -> Scale.Change(8);
				layout -> Color.Change(9);
				graphics.BufferFullInstLayout = layout;
			}
			graphics.ShaderWire.Change({
				media_dir.File("Shaders/PolyHedra/TSC/Wire.vert"),
				media_dir.File("Shaders/PolyHedra/Color.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformView3D();
				graphics.ShaderWire.AssignLayout(layout);
				multiform_layout.Find(layout);
			}
			{
				NewPolyHedra::PalletWire::Layout & layout = graphics.BufferWireMainLayout;
				layout.Pos.Change(0);
				layout.Col.Change(1);
			}
			{
				TransScaleColor3D::BufferLayout * layout = new TransScaleColor3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(-1);
				layout -> Scale.Change(11);
				layout -> Color.Change(12);
				graphics.BufferWireInstLayout = layout;
			}
}
