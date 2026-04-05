#ifndef  PHYSICS_2D_INSTANCES_MANAGER_HPP
# define PHYSICS_2D_INSTANCES_MANAGER_HPP

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

	::PolyGon *	PolyGon;
	::PolyGon *	Bound;

	IntrinsicData	IntData;

	~InstanceManager();
	InstanceManager();
	InstanceManager(const InstanceManager & other);
	InstanceManager & operator=(const InstanceManager & other);
	void Dispose();

	void Changed();
};
};

#endif