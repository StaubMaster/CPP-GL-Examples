#ifndef  DISPLAY_PIXEL_SIZE_HPP
# define DISPLAY_PIXEL_SIZE_HPP

# include "ValueType/Vector/F2.hpp"

struct PixelPosition;
struct NormalPosition;

struct PixelSize
{
	VectorF2		Full;
	VectorF2		Half;

	~PixelSize();
	PixelSize();

	PixelSize(const PixelSize & other);
	PixelSize & operator=(const PixelSize & other);

	void ChangeFull(VectorF2 size);

	static PixelSize FromFull(VectorF2 size);



	PixelPosition	PosFromFull(VectorF2 pos) const;
	PixelPosition	PosFromHalf(VectorF2 pos) const;

	PixelPosition	Convert(NormalPosition pos) const;
	NormalPosition	Convert(PixelPosition pos) const;



	VectorF2	PosFullToNormalAbs(VectorF2 pos) const;
	VectorF2	PosFullToNormalRel(VectorF2 pos) const;

	VectorF2	PosNormalAbsToFull(VectorF2 pos) const;
	VectorF2	PosNormalRelToFull(VectorF2 pos) const;



	VectorF2	SizeFullToNormalAbs(VectorF2 pos) const;
	VectorF2	SizeFullToNormalRel(VectorF2 pos) const;

	VectorF2	SizeNormalAbsToFull(VectorF2 pos) const;
	VectorF2	SizeNormalRelToFull(VectorF2 pos) const;
};

#endif