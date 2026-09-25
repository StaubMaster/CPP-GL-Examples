#ifndef  POLYHEDRA_HPP
# define POLYHEDRA_HPP

# include "Generics/Container/Binary.hpp"

# include "FileInfo.hpp"

# include <string>

class Skin;

struct BoxF3;

namespace ParsingVariable { struct FloatMemory; }

//struct Trans3D;
# include "ValueType/Trans/3D.hpp"

class PolyHedraFileCollection;

class PolyHedra
{
	public:
	struct Corner;
	struct Face;
	struct Edge;

	public:
	Container::Binary<Corner>	Corners;
	Container::Binary<Edge>		Edges;
	Container::Binary<Face>		Faces;

	public:
	BoxF3	CalcBound() const; // LimitBox()
	// LimitDist()
	// CenterAverage()

	public:
	void	Combine(const PolyHedra & other);
	void	Combine(const PolyHedra & other, const Trans3D & trans);

	public:
	::Skin *	Skin = nullptr;

	public:
	struct TransPolyHedra
	{
		const PolyHedra *	Object;
		Trans3D				Trans;
	};
	Container::Binary<TransPolyHedra>	OtherDynamic;

	public:
	FileInfo	File;

	public:
	bool	IsAutomatic = false;

	public:
	ParsingVariable::FloatMemory *	Parameters = nullptr;

	public:
	std::string		ToInfo() const;

	public:
	~PolyHedra();
	PolyHedra();

	public:
	PolyHedra(const PolyHedra & other) = delete;
	PolyHedra & operator=(const PolyHedra & other) = delete;



	public:
	void	Insert_Corn(float x, float y, float z);
	void	Insert_Corn(VectorF3 vec);

	public:
	void	Insert_Face3(unsigned int corn0, unsigned int corn1, unsigned int corn2);
	void	Insert_Face3(unsigned int corn0, unsigned int corn1, unsigned int corn2, unsigned int normal_group);
	void	Insert_Face4(unsigned int corn0, unsigned int corn1, unsigned int corn2, unsigned int corn3);
	void	Insert_Face4(unsigned int corn0, unsigned int corn1, unsigned int corn2, unsigned int corn3, unsigned int normal_group);

	public:
	void	Belt_Face(unsigned int temp[4], bool f_direction, unsigned int normal_group);
	void	Belt(unsigned int len, unsigned int list0[], unsigned int list1[], bool f_direction, bool f_closed, unsigned int normal_group);

	public:
	void	Fan_Face(unsigned int middle, unsigned int blade[2], bool f_direction, bool f_middle, unsigned int normal_group);
	void	Fan(unsigned int len, unsigned int middle, unsigned int blade[], bool f_direction, bool f_middle, bool f_closed, unsigned int normal_group);

	public:
	void	Done();
};

#endif