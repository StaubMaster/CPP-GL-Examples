#ifndef  OBJECT_CONTROL_TRANS_3D_HPP
# define OBJECT_CONTROL_TRANS_3D_HPP

# include "Control/GroupBox.hpp"
# include "ObjectControl/VectorF3.hpp"

struct Trans3D;

namespace UI
{
namespace Control
{
struct Trans3D : public GroupBox
{
	VectorF3	Pos;
	~Trans3D();
	Trans3D();
	::Trans3D *	Object;
	void	Change(Trans3D * obj);

};
};
};

#endif