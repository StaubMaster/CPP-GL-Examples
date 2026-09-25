#ifndef  TEXTURE_GEN_HPP
# define TEXTURE_GEN_HPP

class Image;

struct Color;

namespace Texture
{
namespace Generate
{
	Image NoSkin();

	Image Orientation2D();
	Image Orientation3D();

	Image GradiantX(Color col0, Color col1, unsigned int sections);
	Image Gradiant2D();

	Image Wood16x16();
};
};

#endif
