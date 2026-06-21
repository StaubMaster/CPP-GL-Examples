#ifndef  UI_POLYHEDRA_MANAGER_HPP
# define UI_POLYHEDRA_MANAGER_HPP

# include "Graphics/Shader/Base.hpp"

# include "PolyHedra/Graphics/Full/ShaderLayout.hpp"
# include "PolyHedra/Graphics/Wire/ShaderLayout.hpp"

# include "PolyHedra/Graphics/Full/Main/Layout.hpp"
# include "PolyHedra/Graphics/Wire/Main/Layout.hpp"

# include "Instance/Basic3D/Layout.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "ValueType/Undex.hpp"

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/Matrix4x4.hpp"
# include "Graphics/Attribute/TypeDefs/ColorF4.hpp"
# include "Graphics/Attribute/TypeDefs/Float.hpp"

class DirectoryInfo;

class PolyHedra;
struct PolyHedraUIObjectData;
struct PolyHedraUIPalletManager;

struct PolyHedraUIBufferLayoutInst : public ::Attribute::Layout
{
	public:
	::Attribute::Matrix4x4	Trans;
	::Attribute::Matrix4x4	Normal;
	::Attribute::Float		Scale;
	::Attribute::ColorF4	Color;
	public:
	~PolyHedraUIBufferLayoutInst();
	PolyHedraUIBufferLayoutInst();
	PolyHedraUIBufferLayoutInst(const PolyHedraUIBufferLayoutInst & other);
};

struct PolyHedraUIManager
{
	public:
	static PolyHedraUIManager * CurrentPointer;
	static PolyHedraUIManager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();



	public:
	~PolyHedraUIManager();
	PolyHedraUIManager();
	PolyHedraUIManager(const PolyHedraUIManager & other) = delete;
	PolyHedraUIManager & operator=(const PolyHedraUIManager & other) = delete;



	public:
	Container::Binary<PolyHedraUIPalletManager*>	InstanceManagers;

	public:
	void	MakeInstances();

	public:
	::PolyHedraUIPalletManager *	FindPallet(::PolyHedra * pallet);
	::PolyHedraUIPalletManager *	PlacePallet(::PolyHedra * pallet);



	public:
	PolyHedraUIObjectData *		PlaceObject(::PolyHedraUIPalletManager * pallet);
	PolyHedraUIObjectData *		PlaceObject(::PolyHedra * pallet);

	public:
	static PolyHedraUIObjectData *	TryPlaceObject(PolyHedraUIManager * manager, ::PolyHedraUIPalletManager * pallet);
	static PolyHedraUIObjectData *	TryPlaceObject(PolyHedraUIManager * manager, ::PolyHedra * pallet);



	public:
	bool				GraphicsExist;

	::Shader::Base		ShaderFullDefault;
	::Shader::Base		ShaderWireDefault;

	::Shader::Base *	ShaderFullOther;
	::Shader::Base *	ShaderWireOther;

	PolyHedraFull::ShaderLayout		ShaderLayoutFullDefault;
	::PolyHedraFull::Main::Layout	BufferLayoutFullMain;
	PolyHedraUIBufferLayoutInst		BufferLayoutFullInst;

	PolyHedraWire::ShaderLayout		ShaderLayoutWireDefault;
	::PolyHedraWire::Main::Layout	BufferLayoutWireMain;
	PolyHedraUIBufferLayoutInst		BufferLayoutWireInst;

	public:
	void	ChangeMedia(const DirectoryInfo & dir);

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	public:
	void	DrawFull();
	void	DrawWire();
};

#endif
