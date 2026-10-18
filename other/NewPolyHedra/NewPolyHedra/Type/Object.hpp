#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

struct BaseDisplayObject;

template<typename LogicalData> struct TypeLogicalObject;

template<typename LogicalData> struct Type_Object
{
	private:
	TypeLogicalObject<LogicalData> *	ObjectData = nullptr;

	public:
	bool	Is() const;

	public:
	const	LogicalData &	Data() const;
			LogicalData &	Data();

	public:
	const	BaseDisplayObject *		Manager() const;
			BaseDisplayObject *		Manager();

	public:
	bool	VisibleFull() const;
	void	ShowFull();
	void	HideFull();

	public:
	bool	VisibleWire() const;
	void	ShowWire();
	void	HideWire();

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