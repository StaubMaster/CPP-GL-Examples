#ifndef  UI_TEXT_ALIGNMENT_HPP
# define UI_TEXT_ALIGNMENT_HPP

namespace UI
{
namespace Text
{
enum class Alignment
{
	Min,
	Mid,
	Max,
};
};
};

/* Text Alignment

								Pos.X
X Min								|########################
X Mid					############|############
X Max		########################|

Y Min		###################
			##########
Y Mid		###############
			###################
Y Max		###########
*/

/* Character Alignment

   Min Mid Max
Min	0---1---2
	|		|
	|		|
Mid	3	4	5
	|		|
	|		|
Max	6---7---8

move the Character / Text so that Pos is at Number n
*/

#endif