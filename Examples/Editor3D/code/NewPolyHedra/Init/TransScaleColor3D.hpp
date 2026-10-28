#ifndef  LAYOUT_NEW_POLYHEDRA_TRANS_SCALE_COLOR_3D_HPP
# define LAYOUT_NEW_POLYHEDRA_TRANS_SCALE_COLOR_3D_HPP

class DirectoryInfo;
namespace Multiform { class Layout; };

namespace NewPolyHedra
{
	struct BaseDisplayObjectManager;
};

namespace TransScaleColor3D
{
	void	ChangeMedia(const DirectoryInfo & media_dir, Multiform::Layout & multiform_layout, NewPolyHedra::BaseDisplayObjectManager & graphics);
};

#endif