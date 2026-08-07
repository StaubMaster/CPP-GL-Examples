#version 330



struct BoxF2
{
	vec2	Min;
	vec2	Max;
};
vec2 center(BoxF2 box)
{
	return (box.Max + box.Min) / 2;
}
vec2 size(BoxF2 box)
{
	return (box.Max - box.Min);
}

struct PixelSize
{
	vec2 Full;
	vec2 Half;
};
struct sDisplaySize
{
	vec2 Ratio;
	PixelSize Window;
	PixelSize Buffer;
};

uniform sDisplaySize DisplaySize;



const float BoarderFactor = 0.05;
const float BoarderSize = 10;



in Vert_UI
{
	vec2	Pos;
	BoxF2	Box;
	vec4	Color;
	BoxF2	Bound;
} fs_inn;

out vec4 Pixel;



void main()
{
	if (fs_inn.Pos.x < fs_inn.Bound.Min.x) { discard; }
	if (fs_inn.Pos.y < fs_inn.Bound.Min.y) { discard; }
	if (fs_inn.Pos.x > fs_inn.Bound.Max.x) { discard; }
	if (fs_inn.Pos.y > fs_inn.Bound.Max.y) { discard; }

	BoxF2 diff;
	diff.Min = fs_inn.Pos - fs_inn.Box.Min;
	diff.Max = fs_inn.Box.Max - fs_inn.Pos;

	bool is_min_x = (diff.Min.x < BoarderSize);
	bool is_max_x = (diff.Max.x < BoarderSize);
	bool is_min_y = (diff.Min.y < BoarderSize);
	bool is_max_y = (diff.Max.y < BoarderSize);

	vec4 col = fs_inn.Color;

	if (is_min_x) { col = vec4(0, 0, 0, 1); }
	if (is_max_x) { col = vec4(1, 0, 0, 1); }
	if (is_min_y) { col = vec4(0, 1, 0, 1); }
	if (is_max_y) { col = vec4(0, 0, 1, 1); }

	if (is_min_x && is_min_y)
	{
		if (diff.Min.x < diff.Min.y)	{ col = vec4(0, 0, 0, 1); }
		else							{ col = vec4(0, 1, 0, 1); }
	}
	if (is_min_x && is_max_y)
	{
		if (diff.Min.x < diff.Max.y)	{ col = vec4(0, 0, 0, 1); }
		else							{ col = vec4(0, 0, 1, 1); }
	}
	if (is_max_x && is_min_y)
	{
		if (diff.Max.x < diff.Min.y)	{ col = vec4(1, 0, 0, 1); }
		else							{ col = vec4(0, 1, 0, 1); }
	}
	if (is_max_x && is_max_y)
	{
		if (diff.Max.x < diff.Max.y)	{ col = vec4(1, 0, 0, 1); }
		else							{ col = vec4(0, 0, 1, 1); }
	}

	Pixel = col;
}
