#ifndef  UI_POLYHEDRA_INSTANCE_MANAGER_HPP
# define UI_POLYHEDRA_INSTANCE_MANAGER_HPP

# include "PolyHedra/Graphics/Full/Buffer.hpp"
# include "PolyHedra/Graphics/Wire/Buffer.hpp"

# include "Instance/Basic3D/Data.hpp"

# include "Graphics/Texture/Array2D.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "ValueType/ColorF4.hpp"

class PolyHedra;
struct PolyHedraUIObjectData;
struct PolyHedraUIManager;

struct PolyHedraUIData
{
	Matrix4x4	Trans;
	Matrix4x4	Normal;
	float		Scale;
	ColorF4		Color;
};

struct PolyHedraUIPalletManager
{
	::PolyHedra *	Pallet;

	// Object Defaults
	bool	DefaultVisibilityFull;
	bool	DefaultVisibilityWire;



	public:
	~PolyHedraUIPalletManager();
	PolyHedraUIPalletManager() = delete;
	PolyHedraUIPalletManager(const PolyHedraUIPalletManager & other) = delete;
	PolyHedraUIPalletManager & operator=(const PolyHedraUIPalletManager & other) = delete;

	public:
	PolyHedraUIPalletManager(::PolyHedra * pallet);



	public:
	Container::Binary<PolyHedraUIObjectData*>	ObjectDatas;

	PolyHedraUIObjectData *		PlaceObject();
	PolyHedraUIObjectData *		CopyObject(const PolyHedraUIObjectData * other);

	static PolyHedraUIObjectData *	TryPlaceObject(PolyHedraUIPalletManager * pallet);
	static PolyHedraUIObjectData *	TryCopyObject(PolyHedraUIPalletManager * pallet, const PolyHedraUIObjectData * other);



	public:
	Container::Binary<PolyHedraUIData>	InstancesFull;
	Container::Binary<PolyHedraUIData>	InstancesWire;

	void	MakeInstances();



	public:
	::PolyHedraFull::Buffer		BufferFull;
	::PolyHedraWire::Buffer		BufferWire;

	public:
	Texture::Array2D	TextureFull;

	public:
	void	ChangeMedia(PolyHedraUIManager & manager);

	public:
	bool	GraphicsExist;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	void	UpdateFullBufferMain();
	public:
	void	DrawFull();

	private:
	void	UpdateWireBufferMain();
	public:
	void	DrawWire();
};

#endif