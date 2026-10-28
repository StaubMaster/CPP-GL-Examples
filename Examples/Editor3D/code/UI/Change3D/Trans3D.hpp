#ifndef  CHANGE_3D_TRANS_3D_HPP
# define CHANGE_3D_TRANS_3D_HPP

# include "Base.hpp"

# include "UI/Change3D/VectorF3.hpp"
# include "UI/Change3D/EulerAngle3D.hpp"

namespace Change3D
{
struct Trans3D
{
	Change3D::VectorF3		VectorF3;
	Change3D::EulerAngle3D	EulerAngle3D;

	public:
	void	IndicatorsInit(const DirectoryInfo & dir);

	public:
	void	IndicatorsHide();
	void	IndicatorsShow();

	public:
	unsigned int	IndicatorsFind(const RayF3 & ray);

	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size);

	public:
	bool	IsNone() const;

	public:
	bool	HoveringIsNone() const;
	void	HoveringMakeNone();
	void	HoveringMakeOther();

	public:
	bool	SelectedIsNone() const;
	void	SelectedMakeNone();

	public:
	void	SelectedMakeL(unsigned int idx);
	void	SelectedMakeR(unsigned int idx);

	public:
	void	ChangeValue(const RayF3 & ray);
};
};

#endif