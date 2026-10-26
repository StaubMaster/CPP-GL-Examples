#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

template<typename LogicalData> struct TypeLogicalObject;
template<typename LogicalData> struct DataDisplayObject;

template<typename LogicalData> struct TypeObject
{
	private:
	TypeLogicalObject<LogicalData> *	ObjectData = nullptr;

	public:
	bool	Is() const;

	public:
	const	LogicalData &	Data() const;
			LogicalData &	Data();

	public:
	const	DataDisplayObject<LogicalData> *	Graphics() const;
			DataDisplayObject<LogicalData> *	Graphics();

	public:
	bool	VisibleFull() const;
	void	ShowFull();
	void	HideFull();

	public:
	bool	VisibleWire() const;
	void	ShowWire();
	void	HideWire();

	public:
	~TypeObject();
	TypeObject() = default;
	TypeObject(const TypeObject & other) = delete;
	TypeObject & operator=(const TypeObject & other) = delete;

	public:
	TypeObject(Pallet & pallet);
	TypeObject(PolyHedra & polyhedra);

	public:
	//bool	Exists(); // same as Is(), but more in line with Delete() and Create()
	void	Delete();
	// Create()
	// Creates a new Object with the same Pallet
	void	Create(Pallet & pallet);
	void	Create(PolyHedra & polyhedra);
	// these 2 should Delete, then Create
	// right now if they already exist, they just dont do anything
};
};

#endif