#ifndef  DISPLAY_HELP_NORMALIZED_HPP
# define DISPLAY_HELP_NORMALIZED_HPP

class PolyHedra;
namespace NewPolyHedra
{
	struct	Pallet;
};

namespace Container
{
	template<typename T> struct Array;
};

struct BoxF3;
struct BoxEntity3D;

namespace DisplayHelp
{
	extern PolyHedra *				Box_PolyHedra;
	extern NewPolyHedra::Pallet *	Box_Pallet;

	void	Normalized(NewPolyHedra::Pallet & pallet, const BoxF3 & box);
	void	Normalized(NewPolyHedra::Pallet & pallet, const Container::Array<BoxF3> & boxes);
	void	Normalized(NewPolyHedra::Pallet & pallet, const BoxEntity3D & box);

	void	Normalized(const BoxF3 & box);
	void	Normalized(const Container::Array<BoxF3> & boxes);
	void	Normalized(const BoxEntity3D & box);
};

#endif