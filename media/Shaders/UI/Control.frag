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



const vec4 col_min_x = vec4(0, 0, 0, 1);
const vec4 col_min_y = vec4(1, 0, 0, 1);
const vec4 col_max_x = vec4(0, 1, 0, 1);
const vec4 col_max_y = vec4(0, 0, 1, 1);

const float factor_min_x = 1.0 + 0.05;
const float factor_min_y = 1.0 + 0.10;
const float factor_max_x = 1.0 - 0.05;
const float factor_max_y = 1.0 - 0.10;

void main()
{
	if (fs_inn.Pos.x < fs_inn.Bound.Min.x) { discard; }
	if (fs_inn.Pos.y < fs_inn.Bound.Min.y) { discard; }
	if (fs_inn.Pos.x > fs_inn.Bound.Max.x) { discard; }
	if (fs_inn.Pos.y > fs_inn.Bound.Max.y) { discard; }

	BoxF2 diff;
	diff.Min = fs_inn.Pos - fs_inn.Box.Min;
	diff.Max = fs_inn.Box.Max - fs_inn.Pos;

	bool min_x = (diff.Min.x < BoarderSize);
	bool min_y = (diff.Min.y < BoarderSize);
	bool max_x = (diff.Max.x < BoarderSize);
	bool max_y = (diff.Max.y < BoarderSize);

	/*vec4 col = fs_inn.Color;
	if (min_x) { col = col_min_x; }
	if (max_x) { col = col_max_x; }
	if (min_y) { col = col_min_y; }
	if (max_y) { col = col_max_y; }
	if (min_x && min_y) { col = (diff.Min.x < diff.Min.y) ? col_min_x : col_min_y; }
	if (min_x && max_y) { col = (diff.Min.x < diff.Max.y) ? col_min_x : col_max_y; }
	if (max_x && min_y) { col = (diff.Max.x < diff.Min.y) ? col_max_x : col_min_y; }
	if (max_x && max_y) { col = (diff.Max.x < diff.Max.y) ? col_max_x : col_max_y; }
	Pixel = col;*/

	float factor = 1.0f;
	if (min_x) { factor = factor_min_x; }
	if (max_x) { factor = factor_max_x; }
	if (min_y) { factor = factor_min_y; }
	if (max_y) { factor = factor_max_y; }
	if (min_x && min_y) { factor = (diff.Min.x < diff.Min.y) ? factor_min_x : factor_min_y; }
	if (min_x && max_y) { factor = (diff.Min.x < diff.Max.y) ? factor_min_x : factor_max_y; }
	if (max_x && min_y) { factor = (diff.Max.x < diff.Min.y) ? factor_max_x : factor_min_y; }
	if (max_x && max_y) { factor = (diff.Max.x < diff.Max.y) ? factor_max_x : factor_max_y; }
	Pixel = fs_inn.Color * factor;
}
