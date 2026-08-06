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
const float BoarderSize = 2;



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
	diff.Min = abs(fs_inn.Box.Min - fs_inn.Pos);
	diff.Max = abs(fs_inn.Box.Max - fs_inn.Pos);

//	float mul_min = min(diff.Min.x, diff.Min.y);
//	float mul_max = min(diff.Max.x, diff.Max.y);

	bool min_x = (diff.Min.x < BoarderSize);
	bool min_y = (diff.Min.y < BoarderSize);
	bool max_x = (diff.Max.x < BoarderSize);
	bool max_y = (diff.Max.y < BoarderSize);

	vec4 col = fs_inn.Color;

	if (min_x) { col = vec4(0, 0, 0, 1); }
	if (min_y) { col = vec4(1, 0, 0, 1); }
	if (max_x) { col = vec4(0, 1, 0, 1); }
	if (max_y) { col = vec4(0, 0, 1, 1); }

	Pixel = col;

	/*float factor = 1.0;
	if (mul_min < BoarderSize && mul_max < BoarderSize)
	{
		if (mul_min < mul_max)
		{ factor += BoarderFactor; factor = 0.0f; }
		else
		{ factor -= BoarderFactor; factor = 0.0f; }
	}
	else if (mul_min < BoarderSize && mul_max > BoarderSize)
	{ factor += BoarderFactor; factor = 0.0f; }
	else if (mul_min > BoarderSize && mul_max < BoarderSize)
	{ factor -= BoarderFactor; factor = 0.0f; }
	Pixel = fs_inn.Color * factor;*/
}
