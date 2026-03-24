#ifndef  PHYSICS_2D_INSTANCES_MANAGER_HPP
# define PHYSICS_2D_INSTANCES_MANAGER_HPP

//# include "Physics2D/Manager.hpp"

# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/MainElemInst.hpp"

# include "Inst2D/Buffer.hpp"
# include "ValueType/Trans2D.hpp"

# include "PolyGon/Object.hpp"
# include "PolyGon/Graphics/Full/Buffer.hpp"
# include "PolyGon/Graphics/Wire/Buffer.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "IntrinsicData.hpp"



namespace Physics2D
{
struct Manager;

// this dosent manage instances anymore
// its just the main data of a Object

// ObjectMain
// ObjectTemplate
// ObjectPattern
// Object

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
	::PolyGon::Object *	Bound;

	::PolyGon::Full::Buffer		Buffer_PolyGon_Full;
	::PolyGon::Wire::Buffer		Buffer_PolyGon_Wire;
	::PolyGon::Wire::Buffer		Buffer_Bound;

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