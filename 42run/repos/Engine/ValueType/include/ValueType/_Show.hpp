#ifndef  VALUE_TYPE_SHOW_HPP
# define VALUE_TYPE_SHOW_HPP

# include "ValueType/_Declare.hpp"

# include <iosfwd>

std::ostream & operator<<(std::ostream & os, const Bool2 & obj);
std::ostream & operator<<(std::ostream & os, const Bool3 & obj);
std::ostream & operator<<(std::ostream & os, const Bool4 & obj);

std::ostream & operator<<(std::ostream & os, const VectorF2 & obj);
std::ostream & operator<<(std::ostream & os, const VectorF3 & obj);
std::ostream & operator<<(std::ostream & os, const VectorF4 & obj);
std::ostream & operator<<(std::ostream & os, const VectorU2 & obj);
std::ostream & operator<<(std::ostream & os, const VectorU3 & obj);
std::ostream & operator<<(std::ostream & os, const VectorI2 & obj);
std::ostream & operator<<(std::ostream & os, const VectorI3 & obj);

std::ostream & operator<<(std::ostream & os, const BoxF1 & obj);
std::ostream & operator<<(std::ostream & os, const BoxF2 & obj);
std::ostream & operator<<(std::ostream & os, const BoxF3 & obj);
std::ostream & operator<<(std::ostream & os, const BoxU2 & obj);
std::ostream & operator<<(std::ostream & os, const BoxU3 & obj);
std::ostream & operator<<(std::ostream & os, const BoxI2 & obj);
std::ostream & operator<<(std::ostream & os, const BoxI3 & obj);

//std::ostream & operator<<(std::ostream & os, const Matrix2x2 & obj);
//std::ostream & operator<<(std::ostream & os, const Matrix3x3 & obj);
//std::ostream & operator<<(std::ostream & os, const Matrix4x4 & obj);

std::ostream & operator<<(std::ostream & os, const LineF2 & obj);
std::ostream & operator<<(std::ostream & os, const LineF3 & obj);

std::ostream & operator<<(std::ostream & os, const RayF2 & obj);
std::ostream & operator<<(std::ostream & os, const RayF3 & obj);

std::ostream & operator<<(std::ostream & os, const Angle & obj);
std::ostream & operator<<(std::ostream & os, const EulerAngle3D & obj);

std::ostream & operator<<(std::ostream & os, const Trans2D & obj);
std::ostream & operator<<(std::ostream & os, const Trans3D & obj);

//std::ostream & operator<<(std::ostream & os, const DepthFactors & obj);
//std::ostream & operator<<(std::ostream & os, const Depth & obj);

//std::ostream & operator<<(std::ostream & os, const Range & obj);
//std::ostream & operator<<(std::ostream & os, const LInter & obj);

std::ostream & operator<<(std::ostream & os, const ColorF4 & obj);
std::ostream & operator<<(std::ostream & os, const ColorU4 & obj);

std::ostream & operator<<(std::ostream & os, const NormalPlaneF3 & obj);
std::ostream & operator<<(std::ostream & os, const TriangleF3 & obj);
std::ostream & operator<<(std::ostream & os, const Undex & obj);

#endif
