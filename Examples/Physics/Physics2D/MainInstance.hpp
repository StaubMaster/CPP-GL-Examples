#ifndef  PHYSICS_2D_MAIN_INSTANCES_HPP
# define PHYSICS_2D_MAIN_INSTANCES_HPP

# include "PolyGon/PolyGon.hpp"
# include "PolyGon/Physics2D/BufferArray.hpp"
# include "Inst/Physics2D/Data.hpp"

# include "Miscellaneous/EntryContainer/Binary.hpp"

namespace Physics2D
{
struct MainInstance
{
	::PolyGon *		PolyGon;
	Physics2D::BufferArray		BufferArray;
	EntryContainer::Binary<Physics2D::Inst::Data> *	Instances;

	~MainInstance();
	MainInstance();
	MainInstance(const MainInstance & other);
	MainInstance & operator=(const MainInstance & other);

	void Dispose();

	void UpdateMain();
	void UpdateInst();
	void Draw();
};
};

#endif