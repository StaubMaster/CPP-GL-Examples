#ifndef  ARROW_2D_DATA_HPP
# define ARROW_2D_DATA_HPP

# include "Arrow2D/Inst/Data.hpp"
//# include "Miscellaneous/EntryContainer/Entry.hpp"
# include "Miscellaneous/Container/Array.hpp"

class DirectoryInfo;

namespace Arrow2D
{
struct Data
{
//	EntryContainer::Entry<Arrow2D::Inst::Data> Data;
	Container::Array<Arrow2D::Inst::Data> DataArray;
	bool DisplayThisFrame;
	bool DisposeThisFrame;

	~Data();
	Data();
	Data(unsigned int count);

	void Dispose();
	void Allocate(unsigned int count);
};
};

#endif