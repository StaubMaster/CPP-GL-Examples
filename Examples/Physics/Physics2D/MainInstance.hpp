#ifndef  PHYSICS_2D_MAIN_INSTANCES_HPP
# define PHYSICS_2D_MAIN_INSTANCES_HPP

# include "Graphics/Buffer/MainInst.hpp"

# include "Inst/Physics2D/Buffer.hpp"
# include "Inst/Physics2D/Data.hpp"

# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "PolyGon/PolyGon.hpp"
# include "PolyGon/Main/Buffer.hpp"



namespace Physics2D
{
struct MainInstance
{
	::PolyGon *		PolyGon;
	EntryContainer::Binary<Physics2D::Inst::Data> *	Instances;

	::BufferArray::MainInst<PolyGonGraphics::Main::Buffer, Physics2D::Inst::Buffer>	PolyGon_Buffer;

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