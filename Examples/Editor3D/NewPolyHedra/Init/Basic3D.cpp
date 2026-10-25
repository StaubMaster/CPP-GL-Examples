#include "NewPolyHedra/Init/Basic3D.hpp"
#include "Special/Basic3D/Layout.hpp"

#include "NewPolyHedra/Base/Display/ObjectManager.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Multiform/General/Layout.hpp"

#include "Layout/Uniform/Light3D.hpp"
#include "Layout/Uniform/View3D.hpp"

void NewPolyHedra::Basic3D::ChangeMedia(const DirectoryInfo & media_dir, Multiform::Layout & multiform_layout, NewPolyHedra::BaseDisplayObjectManager & graphics)
{
			graphics.ShaderFull.Change({
				media_dir.File("Shaders/PolyHedra/Default.vert"),
				media_dir.File("Shaders/PolyHedra/UniformLight.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformLight3D();
				graphics.ShaderFull.AssignLayout(layout);
				multiform_layout.Find(layout);
			}
			{
				PalletFull::Layout & layout = graphics.BufferFullMainLayout;
				layout.Position.Change(0);
				layout.Normal.Change(1);
				layout.Texture.Change(2);
				layout.Color.Change(3);
			}
			{
				NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
				layout -> Trans.Change(4);
				layout -> Normal.Change(-1);
				graphics.BufferFullInstLayout = layout;
			}
			graphics.ShaderWire.Change({
				media_dir.File("Shaders/Basic3D/Wire.vert"),
				media_dir.File("Shaders/Basic3D/Wire.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformView3D();
				graphics.ShaderWire.AssignLayout(layout);
				multiform_layout.Find(layout);
			}
			{
				PalletWire::Layout & layout = graphics.BufferWireMainLayout;
				layout.Pos.Change(0);
				layout.Col.Change(1);
			}
			{
				NewPolyHedra::Basic3D::BufferLayout * layout = new NewPolyHedra::Basic3D::BufferLayout();
				layout -> Trans.Change(3);
				layout -> Normal.Change(-1);
				graphics.BufferWireInstLayout = layout;
			}
}
