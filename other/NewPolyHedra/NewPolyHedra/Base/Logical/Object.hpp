#ifndef  NEW_POLYHEDRA_BASE_LOGICAL_OBJECT_HPP
# define NEW_POLYHEDRA_BASE_LOGICAL_OBJECT_HPP

namespace NewPolyHedra
{
struct BaseDisplayObject;
struct BaseLogicalObject
{
	public:
	bool	Remove = false;
	// make this private
	// make function that sets

	private:
	bool	DisplayFull = true;
	public:
	void	ShowFull();
	void	HideFull();
	bool	VisibleFull() const;

	private:
	bool	DisplayWire = false;
	public:
	void	ShowWire();
	void	HideWire();
	bool	VisibleWire() const;

	public:
	BaseDisplayObject *		Graphics = nullptr;
	// make function that returns Base referance
	// put DisplayData directly in LogicalObject ?
	// LogicalObject should not need DisplayData
	// make ObjectData that holds both LogicalObject and DisplayObject stuff

	public:
	virtual ~BaseLogicalObject() = default;
	BaseLogicalObject() = default;
	BaseLogicalObject(const BaseLogicalObject & other) = default;
	BaseLogicalObject & operator=(const BaseLogicalObject & other) = default;

	public:
	BaseLogicalObject(BaseDisplayObject * graphics);

	protected:
	virtual const void *	DataVoid() const = 0;

	public:
	void	InstancePut() const;
};
};

#endif