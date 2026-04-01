#ifndef  POLYHEDRA_MANAGER_HPP
# define POLYHEDRA_MANAGER_HPP

# include "PolyHedra/Graphics/Full/Shader.hpp"
# include "PolyHedra/InstanceManager.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "ValueType/Undex.hpp"

class PolyHedra;
struct PolyHedraObjectData;
class DirectoryInfo;

struct PolyHedraManager
{
	Container::Binary<PolyHedraInstanceManager>	InstanceManagers;
	PolyHedraFull::Shader						FullShader;

	~PolyHedraManager();
	PolyHedraManager();
	PolyHedraManager(const PolyHedraManager & other) = delete;
	PolyHedraManager & operator=(const PolyHedraManager & other) = delete;

	void	GraphicsCreate();
	void	GraphicsDelete();

	void	InitExternal(DirectoryInfo & media_dir);
	void	InitInternal();

	Undex				Find(::PolyHedra * polyhedra);
	Undex				Place(::PolyHedra * polyhedra);

	PolyHedraObjectData	Place(Undex polyhedra_undex, Trans3D data);
	PolyHedraObjectData	Place(::PolyHedra * polyhedra, Trans3D data);

	void	ClearInstances();
	void	PlaceInstance(const PolyHedraObjectData & obj);
	void	PlaceInstance(const Container::Member<PolyHedraObjectData> & objs);
	void	Draw();
};

#endif
