#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

struct PalletObjectManager;

template<typename TypeData> struct Type_PalletObjectData;

template<typename TypeData> struct Type_Object
{
	private:
	Type_PalletObjectData<TypeData> *		PalletObjectData;

	public:
	bool	Is() const;

	public:
	const	TypeData &	Data() const;
			TypeData &	Data();

	public:
	bool	VisibleFull() const;
	void	ShowFull();
	void	HideFull();

	public:
	bool	VisibleWire() const;
	void	ShowWire();
	void	HideWire();

	public:
	const	PalletObjectManager *	Manager() const;
			PalletObjectManager *	Manager();

	public:
	~Type_Object();
	Type_Object();
	Type_Object(Pallet * pallet);
	Type_Object(PolyHedra * polyhedra);

	public:
	Type_Object(const Type_Object & other) = delete;
	Type_Object & operator=(const Type_Object & other) = delete;

	public:
	void	Delete();
	void	Create(Pallet * pallet);
	void	Create(PolyHedra * polyhedra);
};
};

#endif