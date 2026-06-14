#ifndef  UI_POLYHEDRA_OBJECT_HPP
# define UI_POLYHEDRA_OBJECT_HPP

# include "ValueType/Trans3D.hpp"
# include "ValueType/ColorF4.hpp"

class PolyHedra;
struct PolyHedraUIObjectData;
struct PolyHedraUIPalletManager;

# include <exception>

struct PolyHedraUIObject
{
	private:
	PolyHedraUIObjectData *	Data;

	public:
	bool	Is() const;

	bool	VisFull() const;
	bool	VisWire() const;

	void	HideFull();
	void	HideWire();

	void	ShowFull();
	void	ShowWire();

	::PolyHedraUIPalletManager *	PalletManager() const;
	::PolyHedra *					Pallet() const;

	const Trans3D &	Trans() const;
	Trans3D &		Trans();

	const float &	Scale() const;
	float &			Scale();

	const ColorF4 &	Color() const;
	ColorF4 &		Color();

	public:
	~PolyHedraUIObject();
	PolyHedraUIObject();
	PolyHedraUIObject(const PolyHedraUIObject & other);
	PolyHedraUIObject & operator=(const PolyHedraUIObject & other);

	public:
	PolyHedraUIObject(::PolyHedraUIPalletManager * pallet);
	PolyHedraUIObject(::PolyHedraUIPalletManager * pallet, Trans3D trans);

	public:
	PolyHedraUIObject(::PolyHedra * pallet);
	PolyHedraUIObject(::PolyHedra * pallet, Trans3D trans);

	public:
	void	Delete();
	void	Create(::PolyHedraUIPalletManager * pallet);
	void	Create(::PolyHedra * pallet);

	private:
	class ExceptionNullObject : public std::exception
	{
		const char * what() const noexcept;
	};
};

#endif