#ifndef  UI_TEXT_DATA
# define UI_TEXT_DATA

# include "DataInclude.hpp"

/*	for now:
Main is just a small Box where the Texture gets drawn ?
Inst is the Texture Coords and Letter Pos / Size ?
*/

/*	in the future:
have a seperate Main for every Character ?
and then use Instances for the Position / Scaling ?
*/

namespace UI
{

namespace Text
{

struct Main_Data
{
	Point2D Pos;

	Main_Data();
	Main_Data(Point2D pos);
};

struct Inst_Data
{
	Point2D Pos;
	Point2D Pallet;

	Inst_Data();
	Inst_Data(Point2D pos, Point2D pallet);
};

};

};

#endif