#ifndef  TEXTURE_ARRAY_2D_HPP
# define TEXTURE_ARRAY_2D_HPP

# include "Base.hpp"
# include "ValueType/Vector/U3.hpp"
# include "ValueType/Vector/U2.hpp"
# include "Generics/Container/Array.hpp"

/*	dont need Array2D as inherited class
make it a static nested class ?

put Init3D() and Sub3D() into Base.
make a struct for the wrapping stuff
the struct only stores a referance to the Base Texture
I think there are GL functions for getting this informations
make the struct have Wrapper funcitons to get/set or is/make that stuff
*/

class FileInfo;
class Image;

namespace Texture
{
class Array2D : public Base
{
	VectorU3	Size;



	public:
	Array2D();
	~Array2D();

	Array2D(const Array2D & other);
	Array2D & operator=(const Array2D & other);



	public:
	void	Assign(VectorU3 size);
	void	Assign(unsigned int offset, const Image & img);
	void	Assign(unsigned int offset, const FileInfo & file);

	void	Assign(const Image & img);
	void	Assign(const FileInfo & file);

	void	Assign(VectorU2 size, const Container::Array<Image> & imgs);
	void	Assign(VectorU2 size, const Container::Array<FileInfo> & files);
};
};

#endif
