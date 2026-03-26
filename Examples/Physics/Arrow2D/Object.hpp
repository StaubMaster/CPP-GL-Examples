#ifndef  ARROW_2D_OBJECT_HPP
# define ARROW_2D_OBJECT_HPP

# include "Arrow2D/Data.hpp"

class DirectoryInfo;

namespace Arrow2D
{
struct Object
{
	Arrow2D::Data * Data;

	bool Is() const;
	unsigned int Count() const;
	Arrow2D::Inst::Data & operator*();
	Arrow2D::Inst::Data & operator[](unsigned int idx);
	const Arrow2D::Inst::Data & operator*() const;
	const Arrow2D::Inst::Data & operator[](unsigned int idx) const;

	~Object();
	Object();
	Object(unsigned int count);

	void Dispose();
	void Allocate(unsigned int count);

	void Show();
	void Hide();
};
};

#endif