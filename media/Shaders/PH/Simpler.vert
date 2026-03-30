#version 330



struct Trans3D
{
	vec3 Pos;
	mat3 Rot;
};

struct WindowBufferSize2D
{
	vec2 WindowSize;
	vec2 BufferSize;
	vec2 Ratio;
};

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



uniform WindowBufferSize2D WindowSize;

uniform Trans3D View;

uniform DepthData Depth;

uniform float FOV;



layout(location = 0) in vec3 VPos;

layout(location = 3) in vec3 IPos;



out Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec3 Tex;
} vs_out;



void main()
{
	gl_Position = vec4(VPos, 1.0);
}
