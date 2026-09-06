#ifndef  AXIS_2D_SHOW_HPP
# define AXIS_2D_SHOW_HPP

# include "Types.hpp"
# include "Orientation.hpp"

# include <iosfwd>

std::ostream & operator<<(std::ostream & s, const Axis2D::Abs & axis);
std::ostream & operator<<(std::ostream & s, const Axis2D::Rel & axis);

std::ostream & operator<<(std::ostream & s, const Axis2D::Diag & diag);
std::ostream & operator<<(std::ostream & s, const Axis2D::Flip & flip);

#endif