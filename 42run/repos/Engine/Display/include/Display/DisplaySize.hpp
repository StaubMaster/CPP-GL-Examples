#ifndef  DISPLAY_DISPLAY_SIZE_HPP
# define DISPLAY_DISPLAY_SIZE_HPP

# include "AspectRatio.hpp"
# include "PixelSize.hpp"

struct DisplayPosition;

struct DisplaySize
{
	AspectRatio	Ratio;
	PixelSize	Window;
	PixelSize	Buffer;
//	VectorF2		Scale;	// Window vs Buffer

	~DisplaySize();
	DisplaySize();

	DisplaySize(const DisplaySize & other);
	DisplaySize & operator=(const DisplaySize & other);

	DisplaySize(VectorF2 windowSize, VectorF2 bufferSize);

	void Change(VectorF2 windowSize, VectorF2 bufferSize);

	VectorF2 Convert(DisplayPosition pos) const;
	DisplayPosition Convert(VectorF2 pos) const;



	DisplayPosition		PosFromWindowFull(VectorF2 pos) const;
	DisplayPosition		PosFromBufferFull(VectorF2 pos) const;
	DisplayPosition		PosFromNormalRel(VectorF2 pos) const;
	DisplayPosition		PosFromNormalAbs(VectorF2 pos) const;

	//DisplaySize		SizeFromBufferFull(VectorF2 size) const;
	//DisplaySize		SizeFromNormalAbs(VectorF2 size) const;
	//DisplaySize		SizeFromNormalRel(VectorF2 size) const;
};

#endif