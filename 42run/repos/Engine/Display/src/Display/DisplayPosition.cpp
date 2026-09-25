#include "Display/DisplayPosition.hpp"
#include "Display/DisplaySize.hpp"



DisplayPosition::~DisplayPosition()
{ }
DisplayPosition::DisplayPosition()
	: Normal()
	, Window()
	, Buffer()
{ }

DisplayPosition::DisplayPosition(const DisplayPosition & other)
	: Normal(other.Normal)
	, Window(other.Window)
	, Buffer(other.Buffer)
{ }
DisplayPosition & DisplayPosition::operator=(const DisplayPosition & other)
{
	Normal = other.Normal;
	Window = other.Window;
	Buffer = other.Buffer;
	return *this;
}



/*void DisplayPosition::ChangeWindowCorner(VectorF2 pos, DisplaySize size)
{
	Window.Corner = pos;
	Window.Center = Window.Corner - size.Window.Half;

	Normal.Abs = Window.Corner / size.Window.Full;
	Normal.Rel = Window.Center / size.Window.Half;

	Buffer.Corner = Normal.Abs * size.Buffer.Full;
	Buffer.Center = Normal.Rel * size.Buffer.Half;
}*/
void DisplayPosition::ChangeNormalRel(VectorF2 pos, DisplaySize size)
{
	Normal.Rel = pos;
	Normal.Abs = (pos + 1) / 2;

	Window.Corner = Normal.Abs * size.Window.Full;
	Window.Center = Normal.Rel * size.Window.Half;

	Buffer.Corner = Normal.Abs * size.Buffer.Full;
	Buffer.Center = Normal.Rel * size.Buffer.Half;
}

/*DisplayPosition DisplayPosition::FromWindowCorner(VectorF2 pos, DisplaySize size)
{
	DisplayPosition display_pos;
	display_pos.ChangeWindowCorner(pos, size);
	return display_pos;
}*/
DisplayPosition DisplayPosition::FromNormalRel(VectorF2 pos, DisplaySize size)
{
	DisplayPosition display_pos;
	display_pos.ChangeNormalRel(pos, size);
	return display_pos;
}
