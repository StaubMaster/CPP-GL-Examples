#ifndef  ARROW_2D_OBJECT_HPP
# define ARROW_2D_OBJECT_HPP

# include "Arrow2D/Inst/Data.hpp"
# include "Miscellaneous/EntryContainer/Entry.hpp"

class DirectoryInfo;

namespace Arrow2D
{
struct Object
{
	EntryContainer::Entry<Arrow2D::Inst::Data> Data;

	~Object();
	Object();
	Object(unsigned int count);

	void Dispose();
	void Allocate(unsigned int count);
};
};

#endif