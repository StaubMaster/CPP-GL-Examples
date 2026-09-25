#ifndef  VIEW_3D_HPP
# define VIEW_3D_HPP

# include "ValueType/Trans/3D.hpp"
# include "ValueType/Depth.hpp"

struct View3D
{
	Trans3D	Trans;
	::Depth	Depth;
	Angle	FOV;	//make a VectorF2 for different X and Y angle ?



	~View3D();
	View3D();

	View3D(const View3D & other) = default;
	View3D & operator=(const View3D & other) = default;

	static View3D Default();



	/* decide this internally
		maybe have a Normal Vector
		View tries to stay flat to the Normal
		if Normal is (0 0 0), then do Relative
	*/
	void ChangeRelative(const Trans3D & trans);
	void ChangeAbsoluteFlatY(const Trans3D & trans);



	//VectorF3	forward(VectorF3 p) const;
	//VectorF3	reverse(VectorF3 p) const;
};

#endif