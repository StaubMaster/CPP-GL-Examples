#ifndef  CHANGE_3D_TRANS_3D_HPP
# define CHANGE_3D_TRANS_3D_HPP

# include "UI/Change3D/General/Collection.hpp"
# include "UI/Change3D/VectorF3.hpp"
# include "UI/Change3D/EulerAngle3D.hpp"

namespace Change3D
{
struct Trans3D : public Collection
{
	Change3D::VectorF3		Position;
	Change3D::EulerAngle3D	Rotation;

	~Trans3D() = default;
	Trans3D();
	Trans3D(const Trans3D & other) = delete;
	Trans3D & operator=(const Trans3D & other) = delete;

	public:
	::Trans3D	Get() const;
	void		Set(const ::Trans3D & val);

	public:
	void	ChangeValue(const RayF3 & ray) override;
};
};

#endif