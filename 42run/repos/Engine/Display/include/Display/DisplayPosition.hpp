#ifndef  DISPLAY_DISPLAY_POSITION_HPP
# define DISPLAY_DISPLAY_POSITION_HPP

# include "NormalPosition.hpp"
# include "PixelPosition.hpp"

# include "ValueType/Vector/F2.hpp"

struct DisplaySize;

// allways from Bottom Right
struct DisplayPosition
{
	NormalPosition	Normal;
	PixelPosition	Window;
	PixelPosition	Buffer;

	~DisplayPosition();
	DisplayPosition();

	DisplayPosition(const DisplayPosition & other);
	DisplayPosition & operator=(const DisplayPosition & other);

//	void ChangeWindowCorner(VectorF2 pos, DisplaySize size);
	void ChangeNormalRel(VectorF2 pos, DisplaySize size);

//	static DisplayPosition FromWindowCorner(VectorF2 pos, DisplaySize size);
	static DisplayPosition FromNormalRel(VectorF2 pos, DisplaySize size);
};

#endif