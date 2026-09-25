#ifndef  IMAGE_HPP
# define IMAGE_HPP

# include "uint.hpp"

# include "ValueType/Color/U4.hpp"
# include "ValueType/Vector/U2.hpp"
# include "ValueType/Loop/U2.hpp"

# include "Generics/Container/Array2D.hpp"

// make this a Array2D from Engine
class Image
{
	private:
	Array2D<ColorU4>	Pixels;
//	ColorU4 *	_Data = nullptr;
//	uint64 *	_Know = nullptr;
//	VectorU2	_Size;

//	private:
//	void	mForget();
//	void	mDelete();
//	void	mNew(VectorU2 size);
//	void	mBind(const Image & other);

	public:
	bool			Empty() const;
	uint32			W() const;
	uint32			H() const;
	VectorU2		Size() const;
	const void *	Data() const;
	void *			Data();
	LoopU2			Loop() const;

	public:
	ColorU4 &			Pixel(VectorU2 udx);		// operator[]
	const ColorU4 &		Pixel(VectorU2 udx) const;	// operator[]
	ColorU4 &			Pixel(uint32 x, uint32 y);
	const ColorU4 &		Pixel(uint32 x, uint32 y) const;
	uint8 &				Pixel(uint32 x, uint32 y, uint8 col);
	const uint8 &		Pixel(uint32 x, uint32 y, uint8 col) const;
	ColorU4 &			Pixel(uint32 udx);			// operator[]
	const ColorU4 &		Pixel(uint32 udx) const;	// operator[]

	public:
	~Image();
	Image();
	Image(VectorU2 size);
	Image(uint32 w, uint32 h);

	Image(const Image & other);
	Image & operator=(const Image & other);

	public:
	void Init(VectorU2 size);
	void Init(uint32 w, uint32 h);
	void Dispose();

	public:
//	void Bind(const Image & other);
//	void Copy(const Image & other);
//	Image Bind();
//	Image Copy();

	void Scale(VectorU2 size);
	Image Scaled(VectorU2 size) const;

	public:
	static Image Missing(VectorU2 size);
};

#endif