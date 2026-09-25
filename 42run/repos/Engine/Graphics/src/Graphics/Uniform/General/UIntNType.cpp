#include "Graphics/Uniform/General/UIntNType.hpp"
#include "OpenGL.hpp"



template<> void Uniform::UIntNFunc<1, 1>(unsigned int Index, unsigned int Count, const unsigned int * val) { GL::Uniform1uiv(Index, Count, val); }
template<> void Uniform::UIntNFunc<2, 1>(unsigned int Index, unsigned int Count, const unsigned int * val) { GL::Uniform2uiv(Index, Count, val); }
template<> void Uniform::UIntNFunc<3, 1>(unsigned int Index, unsigned int Count, const unsigned int * val) { GL::Uniform3uiv(Index, Count, val); }
template<> void Uniform::UIntNFunc<4, 1>(unsigned int Index, unsigned int Count, const unsigned int * val) { GL::Uniform4uiv(Index, Count, val); }
