#ifndef  PHYSICS_2D_INSTANCES_MANAGER_HPP
# define PHYSICS_2D_INSTANCES_MANAGER_HPP

//# include "Physics2D/Manager.hpp"

# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/MainElemInst.hpp"

# include "Inst/Physics2D/Buffer.hpp"
# include "Inst/Physics2D/Data.hpp"

# include "PolyGon/PolyGon.hpp"
# include "PolyGon/Graphics/Buffer.hpp"

# include "WireFrame2D/WireFrame2D.hpp"
# include "WireFrame2D/Main/Buffer.hpp"



namespace Physics2D
{
struct Manager;

struct InstanceManager
{
	static InstanceManager * CurrentPointer;
	static InstanceManager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();



	::Physics2D::Manager *	Manager;

	::PolyGon *		PolyGon;
	::WireFrame2D *	WireFrame;
	::WireFrame2D *	WireFrameBox;

//	::EntryContainer::Binary<Physics2D::Inst::Data> *		Instances_PolyGon;
//	::EntryContainer::Binary<Physics2D::Inst::Data> *		Instances_WireFrame;
//	::EntryContainer::Binary<Physics2D::Inst::Data> *		Instances_WireFrameBox;

	::BufferArray::MainInst<PolyGonGraphics::Buffer, Physics2D::Inst::Buffer>							Buffer_PolyGon;
	::BufferArray::MainElemInst<Wire2D::Main::Buffer, Wire2D::Elem::Buffer, Physics2D::Inst::Buffer>	Buffer_WireFrame;
	::BufferArray::MainElemInst<Wire2D::Main::Buffer, Wire2D::Elem::Buffer, Physics2D::Inst::Buffer>	Buffer_WireFrameBox;

	~InstanceManager();
	InstanceManager();
	InstanceManager(const InstanceManager & other);
	InstanceManager & operator=(const InstanceManager & other);

	void Dispose();

	void InitExternal();
	void InitInternal();

	void GraphicsCreate();
	void GraphicsDelete();

	void UpdateMain();
	void UpdateInst();
};
};

#endif