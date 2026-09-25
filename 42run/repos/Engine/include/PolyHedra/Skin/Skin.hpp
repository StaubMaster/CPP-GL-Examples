#ifndef  SKIN_HPP
# define SKIN_HPP

# include "Generics/Container/Binary.hpp"

# include "FileInfo.hpp"
# include "ValueType/Vector/U2.hpp"
# include "ValueType/Vector/F3.hpp"
# include "ValueType/Color/F4.hpp"
# include "Image.hpp"

# include <string>

namespace Texture { class Array2D; };

class Skin
{
	public:
	struct Corner;
	struct Face;

	public:
	VectorU2	Size;
	ColorF4		Color;

	public:
	Container::Binary<Image>	Images;
	Container::Binary<Corner>	Corners;
	Container::Binary<Face>		Faces;

	public: // Information stuff
	FileInfo	File;
	std::string	Name;

	public:
	~Skin();
	Skin();
	Skin(const Skin & other) = delete;
	Skin & operator=(const Skin & other) = delete;

	public:
	void				Done();
	Texture::Array2D	ToTexture() const; // To Texture Data ?



	public:
	void	Insert_Face3(unsigned int idx0, unsigned int idx1, unsigned int idx2);
	void	Insert_Face4(unsigned int idx0, unsigned int idx1, unsigned int idx2, unsigned int idx3);



	private:
	struct ParsingData;
	public:
	static Skin *	Load(const FileInfo & file);
};

#endif
