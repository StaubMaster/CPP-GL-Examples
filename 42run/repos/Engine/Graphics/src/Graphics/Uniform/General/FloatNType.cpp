#include "Graphics/Uniform/General/FloatNType.hpp"
#include "OpenGL.hpp"



template<> void Uniform::FloatNFunc<1, 1>(unsigned int Index, unsigned int Count, const float * val) { GL::Uniform1fv(Index, Count, val); }
template<> void Uniform::FloatNFunc<2, 1>(unsigned int Index, unsigned int Count, const float * val) { GL::Uniform2fv(Index, Count, val); }
template<> void Uniform::FloatNFunc<3, 1>(unsigned int Index, unsigned int Count, const float * val) { GL::Uniform3fv(Index, Count, val); }
template<> void Uniform::FloatNFunc<4, 1>(unsigned int Index, unsigned int Count, const float * val) { GL::Uniform4fv(Index, Count, val); }

template<> void Uniform::FloatNFunc<2, 2>(unsigned int Index, unsigned int Count, const float * val) { GL::UniformMatrix2fv(Index, Count, false, val); }
template<> void Uniform::FloatNFunc<3, 3>(unsigned int Index, unsigned int Count, const float * val) { GL::UniformMatrix3fv(Index, Count, false, val); }
template<> void Uniform::FloatNFunc<4, 4>(unsigned int Index, unsigned int Count, const float * val) { GL::UniformMatrix4fv(Index, Count, false, val); }
