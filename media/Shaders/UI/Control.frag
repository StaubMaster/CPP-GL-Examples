#version 330



const float BoarderFactor = 0.05;
const float BoarderSize = 2;



in Vert_UI
{
	vec2	Min;
	vec2	Max;
	vec2	Pos;
	vec3	Col;
} fs_in;

out vec4 Pixel;



void main()
{
	vec3 col = fs_in.Col;

	vec2 diff_min = abs(fs_in.Min - fs_in.Pos);
	vec2 diff_max = abs(fs_in.Max - fs_in.Pos);

	float mul_min = min(diff_min.x, diff_min.y);
	float mul_max = min(diff_max.x, diff_max.y);

	float factor = 1.0;
	if (mul_min < BoarderSize && mul_max < BoarderSize)
	{
		if (mul_min < mul_max)	{ factor += BoarderFactor; }
		else					{ factor -= BoarderFactor; }
	}
	else if (mul_min < BoarderSize && mul_max > BoarderSize)
	{ factor += BoarderFactor; }
	else if (mul_min > BoarderSize && mul_max < BoarderSize)
	{ factor -= BoarderFactor; }

	col = col * factor;
	Pixel = vec4(col, 1);
}
