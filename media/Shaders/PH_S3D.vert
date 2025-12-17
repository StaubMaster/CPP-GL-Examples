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
	vec3		Color;
};



uniform WindowBufferSize2D WindowSize;

uniform Trans3D View;

uniform DepthData Depth;



layout(location = 0) in vec3 VPos;
layout(location = 1) in vec3 VNorm;
layout(location = 2) in vec2 VTex;

layout(location = 3) in vec3 IPos;
layout(location = 4) in mat3 IRot;
/*
	this also uses Locations 5 and 6
	but using something with those locations dosent give an error
	very odd
*/



out Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec2 Tex;
} vs_out;



vec4 proj(in vec3 p_inn)
{
	vec4 p_out;

	p_out.x = p_inn.x;
	p_out.y = p_inn.y;
	p_out.z = p_inn.z * Depth.Factors[5] - Depth.Factors[6];
	p_out.w = p_inn.z;

	p_out.x = p_out.x * WindowSize.Ratio.x;
	p_out.y = p_out.y * WindowSize.Ratio.y;

	return p_out;
}

void main()
{
	vs_out.Original = VPos;
	vs_out.Absolute = (vs_out.Original * IRot) + IPos;
	vs_out.Relative = (vs_out.Absolute - View.Pos) * View.Rot;

	gl_Position = proj(vs_out.Relative);

	vs_out.Normal = -(VNorm * IRot);
	vs_out.Tex = VTex;
}
