#ifndef  PHYSICS_2D_INSTANCES_MANAGER_HPP
# define PHYSICS_2D_INSTANCES_MANAGER_HPP

//# include "Physics2D/Manager.hpp"

# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/MainElemInst.hpp"

# include "Inst2D/Buffer.hpp"
# include "ValueType/Trans2D.hpp"

# include "PolyGon/Object.hpp"
# include "PolyGon/Graphics/Buffer.hpp"

# include "WireFrame2D/WireFrame2D.hpp"
# include "Graphics2D/Wire/Buffer.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "IntrinsicData.hpp"



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

	::PolyGon::Object *	PolyGon;
	::PolyGon::Object *	PolyGonBox;
	::WireFrame2D *		WireFrame;
	::WireFrame2D *		WireFrameBox;

	::PolyGon::Buffer																								Buffer_PolyGon;
	::BufferArray::MainElemInst<Graphics2D::Wire::Main::Buffer, Graphics2D::Wire::Elem::Buffer, Inst2D::Buffer>		Buffer_WireFrame;
	::BufferArray::MainElemInst<Graphics2D::Wire::Main::Buffer, Graphics2D::Wire::Elem::Buffer, Inst2D::Buffer>		Buffer_WireFrameBox;

	IntrinsicData	IntData;

	~InstanceManager();
	InstanceManager();
	InstanceManager(const InstanceManager & other);
	InstanceManager & operator=(const InstanceManager & other);
	void Dispose();

	void Changed();



	void GraphicsInitExternal();
	void GraphicsInitInternal();

	void GraphicsCreate();
	void GraphicsDelete();

	void GraphicsUpdateMain();
	void GraphicsUpdateInst();
};
};

#endif