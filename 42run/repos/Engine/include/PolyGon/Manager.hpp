#ifndef  POLYGON_MANAGER_HPP
# define POLYGON_MANAGER_HPP

# include "Graphics/Shader/Base.hpp"
# include "PolyGon/Graphics/Full/ShaderLayout.hpp"
# include "PolyGon/Graphics/Wire/ShaderLayout.hpp"
# include "PolyGon/InstanceManager.hpp"

# include "Generics/Container/Binary.hpp"

# include "ValueType/Undex.hpp"

class PolyGon;
struct PolyGonObjectData;
class DirectoryInfo;

struct PolyGonManager
{
	static PolyGonManager * CurrentPointer;
	static PolyGonManager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();



	Container::Binary<PolyGonObjectData*>		ObjectDatas;

	::Shader::Base							ShaderFullDefault;
	::Shader::Base							ShaderWireDefault;
	PolyGonFull::ShaderLayout				ShaderLayoutFullDefault;
	PolyGonWire::ShaderLayout				ShaderLayoutWireDefault;

	::Shader::Base *						ShaderFullOther;
	::Shader::Base *						ShaderWireOther;

	Container::Binary<PolyGonInstanceManager>	InstanceManagers;

	~PolyGonManager();
	PolyGonManager();
	PolyGonManager(const PolyGonManager & other) = delete;
	PolyGonManager & operator=(const PolyGonManager & other) = delete;

	void	GraphicsCreate();
	void	GraphicsDelete();

	void	InitExternal(DirectoryInfo & media_dir);
	void	InitInternal();

	unsigned int	FindPolyGon(::PolyGon * PolyGon);
	unsigned int	PlacePolyGon(::PolyGon * PolyGon);

	PolyGonObjectData *	PlaceObject(unsigned int PolyGon, Trans2D trans);
	PolyGonObjectData *	PlaceObject(::PolyGon * PolyGon, Trans2D trans);
	PolyGonObjectData *	CopyObject(const PolyGonObjectData * obj);

	void	ClearInstances();
	void	PlaceInstance(const PolyGonObjectData & obj);

	void	Update();
	void	DrawFull();
	void	DrawWire();
};

#endif
