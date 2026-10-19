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
	virtual ~BaseLogicalObject() = default;
	BaseLogicalObject() = default;
	BaseLogicalObject(const BaseLogicalObject & other) = default;
	BaseLogicalObject & operator=(const BaseLogicalObject & other) = default;

	public:
	BaseLogicalObject(BaseDisplayObject * graphics);

	public:
	virtual void	InstancePut() const = 0;
};
};

#endif