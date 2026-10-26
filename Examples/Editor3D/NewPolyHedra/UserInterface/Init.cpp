#include "NewPolyHedra/UserInterface/Init.hpp"
#include "NewPolyHedra/UserInterface/Layout.hpp"

#include "NewPolyHedra/Base/Display/ObjectManager.hpp"

#include "DirectoryInfo.hpp"
#include "Graphics/Multiform/General/Layout.hpp"

#include "Layout/Uniform/Display.hpp"

void NewPolyHedra::UserInterface::ChangeMedia(const DirectoryInfo & media_dir, Multiform::Layout & multiform_layout, NewPolyHedra::BaseDisplayObjectManager & graphics)
{
			graphics.ShaderFull.Change({
				media_dir.File("Shaders/UI/PHFull.vert"),
				media_dir.File("Shaders/UI/PHFull.frag"),
			});
			{
				Uniform::Layout * layout = new LayoutUniformDisplay();
				graphics.ShaderFull.AssignLayout(layout);
				multiform_layout.Find(layout);
			}
			{
				PalletFull::Layout & layout = graphics.BufferFullMainLayout;
				layout.Position.Change(0);
				layout.Normal.Change(1);
				layout.Texture.Change(2);
				layout.Color.Change(15);
			}
			{
				NewPolyHedra::UserInterface::BufferLayout * layout = new NewPolyHedra::UserInterface::BufferLayout();
				layout -> Size.Change(3);
				layout -> Pos.Change(4);
				layout -> Rot.Change(5);
				layout -> Scale.Change(8);
				graphics.BufferFullInstLayout = layout;
			}
			{
				Uniform::Layout * layout = new LayoutUniformDisplay();
				graphics.ShaderWire.AssignLayout(layout);
				multiform_layout.Find(layout);
			}
			{
				PalletWire::Layout & layout = graphics.BufferWireMainLayout;
				layout.Pos.Change(0);
				layout.Col.Change(1);
			}
			{
				NewPolyHedra::UserInterface::BufferLayout * layout = new NewPolyHedra::UserInterface::BufferLayout();
				graphics.BufferWireInstLayout = layout;
			}
}
