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



layout(location = 0) in vec4	VPos;
layout(location = 1) in vec3	VTex;
layout(location = 2) in vec3	VNorm;

layout(location = 3) in vec4	VCol;

layout(location = 4) in vec4	VAmbientColor;
layout(location = 5) in vec4	VDiffuseColor;
layout(location = 6) in float	VSpecularPower;
layout(location = 7) in vec4	VSpecularColor;

layout(location = 8) in vec3	IPos;
layout(location = 9) in mat3	IRot;



out Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;

	vec4	Col;

	vec4	AmbientColor;
	vec4	DiffuseColor;
	float	SpecularPower;
	vec4	SpecularColor;
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
	vs_out.Original = VPos.xyz;
	vs_out.Absolute = (vs_out.Original * transpose(IRot)) + IPos;
	vs_out.Relative = (vs_out.Absolute - View.Pos) * View.Rot;

	gl_Position = proj(vs_out.Relative);

	vs_out.Normal = VNorm * transpose(IRot);
	vs_out.Tex = VTex;
	vs_out.Col = VCol;

	vs_out.AmbientColor = VAmbientColor;
	vs_out.DiffuseColor = VDiffuseColor;
	vs_out.SpecularPower = VSpecularPower;
	vs_out.SpecularColor = VSpecularColor;
}
