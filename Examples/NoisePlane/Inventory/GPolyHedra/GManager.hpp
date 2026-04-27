#ifndef  POLYHEDRA_MANAGER_HPP
# define POLYHEDRA_MANAGER_HPP

# include "PolyHedra/InstanceManager.hpp"

# include "PolyHedra/Graphics/Full/Shader.hpp"
# include "PolyHedra/Graphics/Wire/Shader.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "ValueType/Undex.hpp"

class PolyHedra;
struct PolyHedraObjectData;
class DirectoryInfo;

struct PolyHedraManager
{
	static PolyHedraManager * CurrentPointer;
	static PolyHedraManager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();



	Container::Binary<PolyHedraObjectData*>		ObjectDatas;

	bool										GraphicsExist;
	PolyHedraFull::Shader						ShaderFullDefault;
	PolyHedraWire::Shader						ShaderWireDefault;
	PolyHedraFull::Shader *						ShaderFullOther;
	PolyHedraWire::Shader *						ShaderWireOther;

	Container::Binary<PolyHedraInstanceManager>	InstanceManagers;

	~PolyHedraManager();
	PolyHedraManager();
	PolyHedraManager(const PolyHedraManager & other) = delete;
	PolyHedraManager & operator=(const PolyHedraManager & other) = delete;

	void	GraphicsCreate();
	void	GraphicsDelete();

	void	InitExternal(DirectoryInfo & media_dir);
	void	InitInternal();

	unsigned int	FindPolyHedra(::PolyHedra * polyhedra);
	unsigned int	PlacePolyHedra(::PolyHedra * polyhedra);

	PolyHedraObjectData *	PlaceObject(unsigned int polyhedra, Trans3D trans);
	PolyHedraObjectData *	PlaceObject(::PolyHedra * polyhedra, Trans3D trans);
	PolyHedraObjectData *	CopyObject(const PolyHedraObjectData * obj);

	void	ClearInstances();
	void	PlaceInstance(const PolyHedraObjectData & obj);
	void	UpdateInstances();

	void	DrawFull();
	void	DrawWire();
};

#endif
