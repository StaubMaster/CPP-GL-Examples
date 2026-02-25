#ifndef  PHYSICS_2D_MAIN_INSTANCES_HPP
# define PHYSICS_2D_MAIN_INSTANCES_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/MainElemInst.hpp"

# include "Inst/Physics2D/Buffer.hpp"
# include "Inst/Physics2D/Data.hpp"

# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "PolyGon/PolyGon.hpp"
# include "PolyGon/Graphics/Buffer.hpp"

# include "WireFrame2D/WireFrame2D.hpp"
# include "WireFrame2D/Main/Buffer.hpp"



namespace Physics2D
{
struct MainInstance
{
	::PolyGon *		PolyGon;
	::WireFrame2D *	WireFrame;
	::WireFrame2D *	WireFrameBox;
	EntryContainer::Binary<Physics2D::Inst::Data> *		Instances;

	::BufferArray::MainInst<PolyGonGraphics::Buffer, Physics2D::Inst::Buffer>							PolyGon_Buffer;
	::BufferArray::MainElemInst<Wire2D::Main::Buffer, Wire2D::Elem::Buffer, Physics2D::Inst::Buffer>	WireFrame_Buffer;
	::BufferArray::MainElemInst<Wire2D::Main::Buffer, Wire2D::Elem::Buffer, Physics2D::Inst::Buffer>	WireFrameBox_Buffer;

	~MainInstance();
	MainInstance();
	MainInstance(const MainInstance & other);
	MainInstance & operator=(const MainInstance & other);

	void Dispose();

	void UpdateMain();
	void UpdateInst();
};
};

#endif