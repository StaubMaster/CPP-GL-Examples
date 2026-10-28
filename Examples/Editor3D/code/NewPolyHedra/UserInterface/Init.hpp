#ifndef  NEW_POLYHEDRA_USER_INTERFACE_INIT_HPP
# define NEW_POLYHEDRA_USER_INTERFACE_INIT_HPP

class DirectoryInfo;
namespace Multiform { class Layout; };

namespace NewPolyHedra
{
	struct BaseDisplayObjectManager;
	namespace UserInterface
	{
		void	ChangeMedia(const DirectoryInfo & media_dir, Multiform::Layout & multiform_layout, NewPolyHedra::BaseDisplayObjectManager & graphics);
	};
};

#endif