#version 330



struct RangeData
{
	float Min;
	float Len;
	float Max;
};

struct DepthData
{
	float[7]	Factors;
	RangeData	Range;
	vec4		Color;
};



struct LightBase
{
	float	Intensity;
	vec4	Color;
};

struct LightSolar
{
	LightBase	Base;
	vec3		Direction;
};

struct LightSpot
{
	LightBase	Base;
	vec3		Position;
	vec3		Direction;
	RangeData	Range;
};



uniform DepthData Depth;

uniform sampler2DArray texture0;



in Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec3 Tex;
} fs_inn;



out vec4 Color;



void main()
{
	//vec4 col = texture(texture0, fs_inn.Tex);
	//Color = col;
	Color = vec4(1, 1, 1, 1);
}
