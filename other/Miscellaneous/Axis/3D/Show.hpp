#ifndef  AXIS_3D_SHOW_HPP
# define AXIS_3D_SHOW_HPP

# include "Types.hpp"
# include "Orientation.hpp"

# include <iosfwd>

std::ostream & operator<<(std::ostream & s, const Axis3D::Abs & axis);
std::ostream & operator<<(std::ostream & s, const Axis3D::Rel & axis);

std::ostream & operator<<(std::ostream & s, const Axis3D::Diag & diag);
std::ostream & operator<<(std::ostream & s, const Axis3D::Flip & flip);

#endif