#ifndef  COLOR_F4_HPP
# define COLOR_F4_HPP

struct ColorU4;

struct ColorF4
{
	float	R;
	float	G;
	float	B;
	float	A;

	~ColorF4();
	ColorF4();

	ColorF4(float r, float g, float b);
	ColorF4(float r, float g, float b, float a);

	ColorF4(const ColorF4 & other) = default;
	ColorF4 & operator=(const ColorF4 & other) = default;

	static ColorF4	FromRGBA(unsigned int rgba);
	unsigned int	ToRGBA() const;

	static ColorF4	FromRGB(unsigned int rgb);

//	ColorF4(const ColorU4 & other);
//	ColorF4 & operator=(const ColorU4 & other);
	ColorU4		ToColorU4() const;
};

#endif