#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

struct BaseGraphicsInst;

template<typename TypeData> struct TypeLogicalData;

template<typename TypeData> struct Type_Object
{
	private:
	TypeLogicalData<TypeData> *	ObjectData = nullptr;

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
	const	BaseDisplayData *	Manager() const;
			BaseDisplayData *	Manager();

	public:
	~Type_Object();
	Type_Object() = default;
	Type_Object(const Type_Object & other) = delete;
	Type_Object & operator=(const Type_Object & other) = delete;

	public:
	Type_Object(Pallet * pallet);
	Type_Object(PolyHedra * polyhedra);

	public:
	void	Delete();
	void	Create(Pallet * pallet);
	void	Create(PolyHedra * polyhedra);
};
};

#endif